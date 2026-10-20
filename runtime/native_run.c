/* The Native run: dispatch between Native and Reference code, the crossing trace that gives
 * Native code the Reference's timing, and the memory hashes. See native_run.h. */
#include "native_run.h"

#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "host.h"
#include "io.h"
#include "memory.h"
#include "native_guest.h"
#include "native_publish.h"
#include "native_os.h"
#include "native_table.h"
#include "native_aggregate.h"

/* OSi_ThreadInfo (NitroSDK OSThreadInfo: two halfwords, then current, list). */
#define THREAD_INFO_CURRENT 0x02204270u
#define THREAD_INFO_LIST 0x02204274u
/* OSThread fields: the next thread in the list, the low and high ends of its stack. */
#define THREAD_NEXT 0x68u
#define THREAD_CONTEXT_SIZE 0x64u
#define THREAD_STACK_LOW 0x90u
#define THREAD_STACK_HIGH 0x94u
/* The stacks the crt0 puts in DTCM below the BIOS words (IRQ, SVC; bios.h). */
#define DTCM_STACKS_HIGH 0x027e3fc0u

/* The stream of crossings of interrupt handlers; a thread's is its OSThread address. */
#define STREAM_IRQ 1u

/* Words of the DS stack passed on beyond r0-r3: more than any function takes, so arguments
 * past the fourth and structures passed by value arrive whatever the prototype says. */
#define STACK_WORDS 12
#define ARG_WORDS (4 + STACK_WORDS)

/* Member functions take `this` on the stack on both hosts (tools/native.py builds the Windows
 * objects for i686-pc-windows-itanium), so a vtable may hold C functions and members alike. */
#define HOST_THISCALL 0

static int is_member(const NativeFunction *n)
{
    return HOST_THISCALL && native_member(n);
}

/* The functions ------------------------------------------------------------------------- */

/* What a function may do (tools/run.py writes the letter per function):
 *   N  runs Native, whoever calls it
 *   C  runs Native for Native callers only: its result does not fit r0/r1 (a float, a
 *      structure by value), so the interpreter cannot take it
 *   R  has a Native but is kept Reference (its Native is patched to call the ROM's code)
 *   H  a compiler helper of the ROM's code (division, ...): no Native, and its time belongs
 *      to the code that calls it, since Native code does the same work inline
 *   -  no Native */
typedef struct Fn {
    uint32_t address; /* bit 0 set for Thumb */
    uint32_t size;
    uint16_t module;
    char status;
    const NativeFunction *native;
    char *name;
    int params;                              /* parameters with `this`, as the source declares them; -1 unknown */
    int arg_words;                           /* proven ARM words, including audited aggregates; -1 for an unknown ABI */
    uint32_t argument_contract;              /* audited word count (low byte), pointer roles (next16 bits); zero: legacy */
    int guest_frame;                         /* audited constant ROM call extent; -1 when unproved */
    int guest_spill_arg, guest_spill_offset; /* audited entry spill; -1 when absent */
    uint64_t calls_in;                       /* from the interpreter, run as Native */
    uint64_t calls_out;                      /* from Native code, run by the interpreter */
} Fn;

typedef struct Module {
    char name[16];
    uint32_t base, size;
    uint8_t *image;
    int resident;
} Module;

#define MAX_MODULES 160
static Module modules[MAX_MODULES];
static int module_count;
static Fn *fns; /* sorted by address (bit 0 clear) */
static int fn_count;
static const NativeFunction **by_host; /* the Native functions by host address */
static uint32_t by_host_count;
static Fn **guest_functions; /* Native/Clean table index to policy function, including its module */

/* One bit per halfword from ITCM to the end of main RAM: a function starts there. Every
 * branch target is looked up, so most must be rejected without a search. */
#define ENTRY_BASE MEM_ITCM_BASE
#define ENTRY_END (MEM_MAIN_BASE + MEM_MAIN_SIZE)
static uint8_t *entry_bits;

static ArmCpu *cpu;
static int running, recording, replaying, resident_ready;

static uint32_t ds_word(uint32_t address)
{
    uint32_t v = 0;
    bus_read(address, 4, &v);
    return v;
}

static int fn_compare(const void *a, const void *b)
{
    uint32_t x = ((const Fn *) a)->address & ~1u, y = ((const Fn *) b)->address & ~1u;
    if (x != y) {
        return x < y ? -1 : 1;
    }
    return (int) ((const Fn *) a)->module - (int) ((const Fn *) b)->module;
}

static int host_compare(const void *a, const void *b)
{
    uintptr_t x = (uintptr_t) (*(const NativeFunction *const *) a)->host;
    uintptr_t y = (uintptr_t) (*(const NativeFunction *const *) b)->host;
    return x < y ? -1 : x > y;
}

static int module_index(const char *name)
{
    for (int i = 0; i < module_count; i++) {
        if (strcmp(modules[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

static int load_manifest(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }
    char line[640], file[512];
    while (module_count < MAX_MODULES && fgets(line, sizeof(line), f) != NULL) {
        Module *m = &modules[module_count];
        if (sscanf(line, "%15s %x %511[^\r\n]", m->name, &m->base, file) != 3) {
            continue;
        }
        m->resident = strncmp(m->name, "ov", 2) != 0;
        FILE *img = fopen(file, "rb");
        if (img != NULL) {
            fseek(img, 0, SEEK_END);
            m->size = (uint32_t) ftell(img);
            fseek(img, 0, SEEK_SET);
            m->image = malloc(m->size ? m->size : 1);
            if (fread(m->image, 1, m->size, img) != m->size) {
                m->size = 0;
            }
            fclose(img);
        }
        module_count++;
    }
    fclose(f);
    return 0;
}

static int load_policy(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return -1;
    }
    int capacity = 0;
    char line[512], module[32], status[4], name[400];
    unsigned address, size;
    while (fgets(line, sizeof(line), f) != NULL) {
        int params = -1, arg_words = -1, guest_frame = -1, spill_arg = -1, spill_offset = -1;
        unsigned contract = 0;
        int end = 0;
        if (sscanf(line, "%x %31s %x %3s %399s%n %d%n %d%n %d%n %d%n %d%n %x%n", &address, module, &size, status, name, &end,
                   &params, &end, &arg_words, &end, &guest_frame, &end, &spill_arg, &end, &spill_offset, &end, &contract,
                   &end) < 5) {
            continue;
        }
        if (line[end + strspn(line + end, " \t\r\n")] != '\0') {
            fclose(f);
            return -1; /* A malformed optional field must not silently remove a contract. */
        }
        int m = module_index(module);
        if (m < 0) {
            continue;
        }
        unsigned words = contract & 0xffu;
        if (contract && (words == 0 || words > ARG_WORDS || arg_words != (int) words || (contract >> 8) >= (1u << words) ||
                         strncmp(module, "ov", 2) == 0)) {
            fclose(f);
            return -1; /* These audited contracts have unique, permanently resident addresses. */
        }
        if (fn_count == capacity) {
            capacity = capacity ? capacity * 2 : 4096;
            fns = realloc(fns, (size_t) capacity * sizeof(Fn));
        }
        Fn *fn = &fns[fn_count++];
        memset(fn, 0, sizeof(*fn));
        fn->address = address;
        fn->size = size;
        fn->module = (uint16_t) m;
        fn->status = status[0];
        fn->name = strdup(name);
        fn->params = params;
        fn->arg_words = arg_words;
        fn->argument_contract = contract;
        fn->guest_frame = guest_frame;
        fn->guest_spill_arg = spill_arg;
        fn->guest_spill_offset = spill_offset;
    }
    fclose(f);
    qsort(fns, (size_t) fn_count, sizeof(Fn), fn_compare);
    for (int i = 1; i < fn_count; i++) {
        if ((fns[i - 1].address & ~1u) == (fns[i].address & ~1u) &&
            (fns[i - 1].argument_contract || fns[i].argument_contract)) {
            return -1;
        }
    }
    entry_bits = calloc((ENTRY_END - ENTRY_BASE) / 16, 1);
    for (int i = 0; i < fn_count; i++) {
        uint32_t a = fns[i].address & ~1u;
        if (a >= ENTRY_BASE && a < ENTRY_END) {
            uint32_t bit = (a - ENTRY_BASE) >> 1;
            entry_bits[bit >> 3] |= (uint8_t) (1u << (bit & 7));
        }
    }
    return 0;
}

/* The first of the functions starting at `address`, or NULL. */
static Fn *first_at(uint32_t address)
{
    address &= ~1u;
    if (address >= ENTRY_BASE && address < ENTRY_END) {
        uint32_t bit = (address - ENTRY_BASE) >> 1;
        if (!(entry_bits[bit >> 3] & (1u << (bit & 7)))) {
            return NULL;
        }
    }
    int lo = 0, hi = fn_count;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if ((fns[mid].address & ~1u) < address) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo < fn_count && (fns[lo].address & ~1u) == address ? &fns[lo] : NULL;
}

/* Whether the function's module is in memory: a resident one once the crt0 has unpacked it,
 * an overlay when the bytes there are its own (overlays share addresses). */
static int is_loaded(const Fn *f)
{
    const Module *m = &modules[f->module];
    if (m->resident) {
        return resident_ready;
    }
    uint32_t a = f->address & ~1u;
    const uint8_t *p = memory_host(a, f->size);
    return p != NULL && m->image != NULL && a >= m->base && a - m->base + f->size <= m->size &&
           memcmp(p, m->image + (a - m->base), f->size) == 0;
}

/* The function whose code is at `address` now, or NULL. */
static Fn *loaded_at(uint32_t address)
{
    Fn *f = first_at(address);
    if (f == NULL) {
        return NULL;
    }
    for (Fn *end = fns + fn_count; f < end && (f->address & ~1u) == (address & ~1u); f++) {
        if (is_loaded(f)) {
            return f;
        }
    }
    return NULL;
}

static int native_for_interpreter(const Fn *f)
{
    return f != NULL && f->status == 'N' && f->native != NULL;
}

static int native_for_native(const Fn *f)
{
    return f != NULL && (f->status == 'N' || f->status == 'C') && f->native != NULL;
}

/* Whether the code at `address` belongs to a function that runs Native (for Native callers):
 * the loaded function whose bytes contain it. */
static int inside_native(uint32_t address)
{
    address &= ~1u;
    int lo = 0, hi = fn_count;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if ((fns[mid].address & ~1u) <= address) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    /* overlays overlap: look back over the functions starting a little lower */
    for (int i = lo - 1; i >= 0; i--) {
        Fn *f = &fns[i];
        uint32_t start = f->address & ~1u;
        if (address - start < f->size && native_for_native(f) && is_loaded(f)) {
            return 1;
        }
        if (address - start >= 0x10000u) {
            break;
        }
    }
    return 0;
}

/* The loaded function whose bytes contain `address`, or NULL. */
static Fn *containing(uint32_t address)
{
    address &= ~1u;
    /* most targets are in the function the last one was in (loops) */
    static Fn *last;
    if (last != NULL && address - (last->address & ~1u) < last->size && is_loaded(last)) {
        return last;
    }
    int lo = 0, hi = fn_count;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if ((fns[mid].address & ~1u) <= address) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    for (int i = lo - 1; i >= 0; i--) {
        Fn *f = &fns[i];
        uint32_t start = f->address & ~1u;
        if (address - start >= 0x10000u) {
            break;
        }
        if (address - start < f->size && is_loaded(f)) {
            return last = f;
        }
    }
    return NULL;
}

static const char *fn_name(uint32_t address)
{
    static char buf[4][420];
    static int which;
    char *b = buf[which++ & 3];
    Fn *f = first_at(address);
    if (f == NULL) {
        snprintf(b, 420, "%08x", address & ~1u);
    } else {
        Fn *l = loaded_at(address);
        snprintf(b, 420, "%s (%08x %s)", (l ? l : f)->name, address & ~1u, modules[(l ? l : f)->module].name);
    }
    return b;
}

/* Statistics ------------------------------------------------------------------------------- */

static uint64_t calls_in, calls_out, calls_pointer, calls_host, thread_moves, fibers_made;
static uint64_t replay_events, drift_events, drift_max, drift_rewound;
static int depth, depth_max;

/* The Native functions the interpreter has entered and that have not returned, innermost
 * last (for a fault report). Calls between Native functions do not show here. */
#define MAX_ACTIVE 256
static Fn *active[MAX_ACTIVE];

/* The crossing trace ---------------------------------------------------------------------- */

enum Crossing {
    CROSS_CALL,     /* the interpreter calls a Native function */
    CROSS_CALL_OUT, /* Native code calls the interpreter */
    CROSS_BACK,     /* ...which returns to Native code */
    CROSS_RETURN,   /* the Native function returns to the interpreter */
    CROSS_SNAPSHOT, /* memory is hashed here (a quiet moment after a requested frame) */
    CROSS_PUBLISH,  /* an audited RAM store publishes a completed buffer */
    CROSS_ARGUMENTS /* extra audited words; attached to a parent, never an independent crossing */
};
static const char *const crossing_names[] = {"call", "call-out", "back", "return", "snapshot", "publish", "arguments"};

/* One crossing: the stream (thread or interrupt), the kind, the function, the step count as
 * the hook saw it (the branching instruction not yet counted), and a value both runs must
 * agree on: a hash of r0-r3 at a call, the result at a return (as wide as the source declares
 * it). A snapshot carries the frame in `function` and the first 8 bytes of the hash in
 * `steps`. */
#define RECORD_WORDS 10
typedef struct Record {
    uint32_t stream, kind, function;
    uint32_t steps_lo, steps_hi;
    uint32_t check;
    uint32_t args[4]; /* r0-r3 at the crossing */
    uint32_t next;    /* replay: the stream's next record (index + 1) */
} Record;

static FILE *record_out;
static Record *records;
static uint32_t record_count;

typedef struct Stream {
    uint32_t key;
    uint32_t next; /* replay: index + 1 of the record to meet next, 0 at the end */
    uint32_t last; /* replay: while loading, the last record so far */
    uint64_t seen;
    /* record: the shadow call stack of crossings still open */
    struct Frame {
        uint32_t ret, sp, function;
        int native;
        Fn *fn;
    } *frames;
    int depth, capacity;
} Stream;

#define MAX_STREAMS 256
static Stream streams[MAX_STREAMS];
static int stream_count;
static int diverged;
static uint32_t frame_now;

/* Actual host calls carry only audited ROM frame extents. Unknown ancestors
 * invalidate a slot calculation; no first-call estimate or Reference value
 * substitutes for proof. Interpreter re-entry establishes a fresh anchor.
 * IRQ and each host fiber have independent call stacks. */
typedef struct GuestFrame {
    uint32_t index;
    uintptr_t caller;
    uint32_t sp;
    int valid;
} GuestFrame;

typedef struct GuestContext {
    GuestFrame *frames;
    unsigned depth, capacity, anchor_depth;
    uint32_t anchor_sp;
    Fn *anchor;
} GuestContext;

static GuestContext guest_contexts[MAX_STREAMS + 1];
__attribute__((target("general-regs-only"))) static GuestContext *guest_current(void);
static uint32_t guest_trace_targets[16];
static unsigned guest_trace_count;

static const NativeFunction *guest_entry(uint32_t index)
{
    return index < native_function_count ? &native_functions[index] : &clean_functions[index - native_function_count];
}

static void guest_trace(GuestContext *g, const uint32_t *args)
{
    Fn *f = guest_functions[g->frames[g->depth - 1].index];
    unsigned target = 0;
    while (target < guest_trace_count && guest_trace_targets[target] != (f->address & ~1u)) {
        ++target;
    }
    if (target == guest_trace_count) {
        return;
    }
    /* Log each exact path and interpreter SP once; bound diagnostics without
     * merging paths on a hash collision or treating stack data as return PCs. */
    static struct SeenPath {
        uint32_t *indices, sp;
        unsigned count;
        Fn *anchor;
    } seen[128];
    static unsigned seen_count;
    unsigned count = g->depth - g->anchor_depth;
    for (unsigned p = 0; p < seen_count; ++p) {
        if (seen[p].count != count || seen[p].sp != g->anchor_sp || seen[p].anchor != g->anchor) {
            continue;
        }
        unsigned i = 0;
        while (i < count && seen[p].indices[i] == g->frames[g->anchor_depth + i].index) {
            ++i;
        }
        if (i == count) {
            return;
        }
    }
    if (seen_count == 128) {
        fprintf(stderr, "native: guest trace exceeds 128 distinct paths\n");
        exit(2);
    }
    struct SeenPath *path = &seen[seen_count++];
    path->indices = malloc(count * sizeof(*path->indices));
    if (path->indices == NULL) {
        abort();
    }
    path->count = count;
    path->sp = g->anchor_sp;
    path->anchor = g->anchor;
    printf("native: GUEST_PATH frame %u root %s sp %08x", frame_now, g->anchor != NULL ? g->anchor->name : "unknown",
           g->anchor_sp);
    for (unsigned i = 0; i < count; ++i) {
        uint32_t index = g->frames[g->anchor_depth + i].index;
        path->indices[i] = index;
        Fn *entry = guest_functions[index];
        printf(" -> %s:%08x", modules[entry->module].name, entry->address & ~1u);
    }
    printf(" body %08x valid %d args", g->frames[g->depth - 1].sp, g->frames[g->depth - 1].valid);
    unsigned words = native_params(guest_entry(g->frames[g->depth - 1].index));
    for (unsigned i = 0; i < words && i < 4; ++i) {
        printf(" %08x", args[i]);
    }
    printf("\n");
    fflush(stdout);
}

static void guest_stack_failure(GuestContext *g, const char *why)
{
    fprintf(stderr, "native: unproved guest stack (%s), frame %u, root %s sp %08x", why, frame_now,
            g->anchor ? g->anchor->name : "unknown", g->anchor_sp);
    for (unsigned i = g->anchor_depth; i < g->depth; ++i) {
        Fn *f = guest_functions[g->frames[i].index];
        fprintf(stderr, " -> %s[extent=%d]", f->name, f->guest_frame);
    }
    fprintf(stderr, "\n");
    exit(7);
}

static uint32_t guest_stack_slot(uint32_t owner, uint32_t offset, uint32_t size)
{
    GuestContext *g = guest_current();
    if (g->depth <= g->anchor_depth) {
        guest_stack_failure(g, "no active owner");
    }
    GuestFrame *frame = &g->frames[g->depth - 1];
    Fn *f = guest_functions[frame->index];
    if (!frame->valid || (f->address & ~1u) != (owner & ~1u) || f->guest_frame < 0 || offset > (uint32_t) f->guest_frame ||
        size > (uint32_t) f->guest_frame - offset) {
        guest_stack_failure(g, "slot outside a proved frame");
    }
    return frame->sp + offset;
}

static void guest_enter(uint32_t index, uintptr_t caller, const uint32_t *args)
{
    GuestContext *g = guest_current();
    if (index >= native_function_count + clean_function_count || guest_functions[index] == NULL) {
        fprintf(stderr, "native: invalid guest function index %u\n", index);
        exit(2);
    }
    if (g->depth == g->capacity) {
        unsigned capacity = g->capacity ? 2 * g->capacity : 64;
        GuestFrame *frames = realloc(g->frames, capacity * sizeof(*frames));
        if (frames == NULL || capacity > 4096) {
            abort();
        }
        g->frames = frames;
        g->capacity = capacity;
    }
    Fn *f = guest_functions[index];
    uint32_t sp = g->anchor_sp;
    int valid = f == g->anchor;
    if (g->depth > g->anchor_depth) {
        sp = g->frames[g->depth - 1].sp;
        valid = g->frames[g->depth - 1].valid;
    }
    valid = valid && f->guest_frame >= 0 && sp >= (uint32_t) f->guest_frame;
    if (valid) {
        sp -= (uint32_t) f->guest_frame;
    }
    g->frames[g->depth++] = (GuestFrame){index, caller, sp, valid};
    guest_trace(g, args);
    if (f->guest_spill_arg >= 0) {
        if (f->guest_spill_arg >= ARG_WORDS || f->guest_spill_offset < 0) {
            guest_stack_failure(g, "invalid entry spill");
        }
        uint32_t slot = guest_stack_slot(f->address, (uint32_t) f->guest_spill_offset, 4);
        bus_write(slot, 4, args[f->guest_spill_arg]);
    }
}

__attribute__((target("general-regs-only"))) static uintptr_t guest_return(uint32_t index)
{
    GuestContext *g = guest_current();
    if (g->depth == 0 || g->frames[g->depth - 1].index != index) {
        abort();
    }
    return g->frames[--g->depth].caller;
}

static uint32_t stream_key(void)
{
    if ((cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ) {
        return STREAM_IRQ;
    }
    return ds_word(THREAD_INFO_CURRENT);
}

static Stream *stream_for(uint32_t key)
{
    for (int i = 0; i < stream_count; i++) {
        if (streams[i].key == key) {
            return &streams[i];
        }
    }
    if (stream_count == MAX_STREAMS) {
        fprintf(stderr, "native: more than %d threads\n", MAX_STREAMS);
        exit(2);
    }
    Stream *s = &streams[stream_count++];
    memset(s, 0, sizeof(*s));
    s->key = key;
    return s;
}

/* RUN_NATIVE_PEEK=<stream>,<crossing>,<address>,<length>: print that memory at that crossing
 * (both runs number a stream's crossings the same way), to compare the two runs' memory at
 * the same moment. */
static uint32_t peek_stream, peek_address, peek_length;
static unsigned long long peek_crossing;

static void hash_memory(uint32_t frame, char hex[41]);

static void peek(uint32_t stream, unsigned long long crossing)
{
    if (peek_length == 0 || stream != peek_stream || crossing != peek_crossing) {
        return;
    }
    if (peek_length == 0xffffffffu) {
        /* length -1: the whole memory as --ram-dump writes it (RUN_RAM_DUMP), then stop; for
           finding the first crossing after which the two runs' memory differs */
        char hex[41];
        hash_memory((uint32_t) crossing, hex);
        printf("native: memory at stream %08x crossing %llu: %s\n", stream, crossing, hex);
        fflush(stdout);
        _Exit(5);
    }
    printf("native: peek %s stream %08x crossing %llu (steps %llu, bus cycles %llu):", recording ? "reference" : "native",
           stream, crossing, (unsigned long long) cpu->steps, (unsigned long long) io_clock());
    for (uint32_t i = 0; i < peek_length; i++) {
        uint32_t v = 0;
        bus_read(peek_address + i, 1, &v);
        printf("%s%02x", i % 32 == 0 ? "\n  " : (i % 4 == 0 ? " " : ""), v);
    }
    printf("\n");
    fflush(stdout);
}

static Stream *stream_for(uint32_t key);

static unsigned contract_words(const Fn *f)
{
    return f != NULL ? f->argument_contract & 0xffu : 0;
}

/* Unlike loaded_at, this also works before replay has loaded the resident ROM.
 * Policy loading rejects ambiguous addresses and overlay contracts. */
static Fn *contract_at(uint32_t address)
{
    address &= ~1u;
    int lo = 0, hi = fn_count;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if ((fns[mid].address & ~1u) < address) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo < fn_count && (fns[lo].address & ~1u) == address && fns[lo].argument_contract ? &fns[lo] : NULL;
}

static uint32_t argument_word(unsigned index)
{
    if (index < 4) {
        return cpu->r[index];
    }
    uint32_t value;
    if (!bus_read(cpu->r[13] + 4u * (index - 4), 4, &value)) {
        fprintf(stderr, "native: cannot read audited argument %u at stack %08x\n", index + 1, cpu->r[13]);
        exit(7);
    }
    return value;
}

static void write_record(uint32_t stream, uint32_t kind, uint32_t function, uint64_t steps, uint32_t check)
{
    uint32_t r[RECORD_WORDS] = {stream, kind,      function,  (uint32_t) steps, (uint32_t) (steps >> 32),
                                check,  cpu->r[0], cpu->r[1], cpu->r[2],        cpu->r[3]};
    fwrite(r, 4, RECORD_WORDS, record_out);
    record_count++;
    if (kind == CROSS_CALL || kind == CROSS_CALL_OUT) {
        unsigned count = contract_words(contract_at(function));
        uint32_t parent = record_count; /* one-based physical parent record */
        for (unsigned first = 4; first < count; first += 3) {
            unsigned n = count - first < 3 ? count - first : 3;
            uint32_t extra[RECORD_WORDS] = {stream, CROSS_ARGUMENTS, function, parent, kind, first, n, 0, 0, 0};
            for (unsigned i = 0; i < n; i++) {
                extra[7 + i] = argument_word(first + i);
            }
            fwrite(extra, 4, RECORD_WORDS, record_out);
            record_count++;
        }
    }
    if (kind != CROSS_SNAPSHOT) {
        peek(stream, ++stream_for(stream)->seen);
    }
}

/* The exact ROM store is guarded by tools/native_publish.py. Ordinary writes
 * to the selector, including initialization, are not publication events. */
static uint32_t publication_owner(uint32_t pc, uint32_t address)
{
    if (pc == 0x020bb16eu && address == 0x021f6f70u) {
        return 0x020bb090u; /* completed gradient */
    }
    if (pc == 0x020ba348u && address == 0x021f8accu) {
        return 0x020ba340u; /* line shift sampled by HBlank */
    }
    if (pc == 0x020bb040u && address == 0x021f75b4u) {
        return 0x020bae60u; /* the cloud tables' set shown */
    }
    return 0;
}

static void record_publication(ArmCpu *c, uint32_t address, uint32_t value)
{
    uint32_t pc = c->r[15] - ((c->cpsr & ARM_CPSR_T) ? 2u : 4u);
    uint32_t owner_address = publication_owner(pc, address);
    if (owner_address == 0 || !resident_ready) {
        return;
    }
    Fn *owner = loaded_at(owner_address);
    Stream *s = stream_for(stream_key());
    if (!native_for_native(owner) || s->depth == 0 || !s->frames[s->depth - 1].native) {
        return;
    }
    /* Publication args describe the store, not the ARM argument registers. */
    uint32_t r[RECORD_WORDS] = {
        s->key, CROSS_PUBLISH, pc, (uint32_t) c->steps, (uint32_t) (c->steps >> 32), value, address, 4, 0, 0};
    fwrite(r, 4, RECORD_WORDS, record_out);
    record_count++;
    peek(s->key, ++s->seen);
}

/* The registers a function takes its arguments in: r0 up to its parameter count (with
 * `this`). The others may hold anything, and do differ after Native code, which leaves r1-r3
 * as they were. */
static int argument_registers(const Fn *f)
{
    unsigned words = contract_words(f);
    if (words) {
        return words < 4 ? (int) words : 4;
    }
    if (f == NULL || f->native == NULL) {
        return 0;
    }
    int n = native_params(f->native) + native_member(f->native);
    return n < 4 ? n : 4;
}

static uint32_t hash_words(const uint32_t *w, int n)
{
    uint32_t h = 2166136261u;
    for (int i = 0; i < n; i++) {
        h = (h ^ w[i]) * 16777619u;
    }
    return h;
}

static uint32_t argument_hash(const Fn *f)
{
    unsigned n = contract_words(f);
    if (!n) {
        return hash_words(cpu->r, argument_registers(f));
    }
    uint32_t words[ARG_WORDS];
    for (unsigned i = 0; i < n; i++) {
        words[i] = argument_word(i);
    }
    return hash_words(words, (int) n);
}

/* A function's result as its source declares it: the ROM's code may leave other bits in
 * r0 above a narrow type, which no caller reads. */
static uint32_t narrow_result(const Fn *f, uint32_t r0, uint32_t r1)
{
    switch (f != NULL && f->native != NULL ? native_return(f->native) : NATIVE_RET_SKIP) {
        case NATIVE_RET_U8:
            return (uint8_t) r0;
        case NATIVE_RET_S8:
            return (uint32_t) (int32_t) (int8_t) r0;
        case NATIVE_RET_U16:
            return (uint16_t) r0;
        case NATIVE_RET_S16:
            return (uint32_t) (int32_t) (int16_t) r0;
        case NATIVE_RET_32:
        case NATIVE_RET_STRUCT3:
        case NATIVE_RET_UNION4:
        case NATIVE_RET_STRUCT4:
            return r0;
        case NATIVE_RET_64:
        case NATIVE_RET_PAIR8:
            return r0 ^ (r1 * 16777619u);
        default:
            return 0;
    }
}

static int load_replay(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size < 0 || size % (4 * RECORD_WORDS) != 0) {
        fclose(f);
        return -1;
    }
    uint32_t n = (uint32_t) (size / (4 * RECORD_WORDS));
    uint32_t *raw = malloc((size_t) n * 4 * RECORD_WORDS + 4);
    if (raw == NULL || fread(raw, 4 * RECORD_WORDS, n, f) != n) {
        fclose(f);
        return -1;
    }
    fclose(f);
    records = malloc((size_t) n * sizeof(Record) + 1);
    if (records == NULL) {
        free(raw);
        return -1;
    }
    for (uint32_t i = 0; i < n; i++) {
        Record *r = &records[i];
        memcpy(r, raw + RECORD_WORDS * i, 4 * RECORD_WORDS);
        r->next = 0;
    }
    /* Argument records must immediately follow their exact physical parent.
     * An IRQ/thread event cannot fill a hole, and all unused payload is zero. */
    for (uint32_t i = 0; i < n; i++) {
        Record *r = &records[i];
        if (r->kind >= CROSS_ARGUMENTS) {
            goto malformed;
        }
        unsigned count = (r->kind == CROSS_CALL || r->kind == CROSS_CALL_OUT) ? contract_words(contract_at(r->function)) : 0;
        uint32_t parent = i + 1;
        for (unsigned first = 4; first < count; first += 3) {
            if (++i >= n) {
                goto malformed;
            }
            Record *extra = &records[i];
            unsigned words = count - first < 3 ? count - first : 3;
            if (extra->kind != CROSS_ARGUMENTS || extra->stream != r->stream || extra->function != r->function ||
                extra->steps_lo != parent || extra->steps_hi != r->kind || extra->check != first || extra->args[0] != words) {
                goto malformed;
            }
            for (unsigned word = words; word < 3; word++) {
                if (extra->args[1 + word] != 0) {
                    goto malformed;
                }
            }
        }
    }
    for (uint32_t i = 0; i < n; i++) {
        Record *r = &records[i];
        if (r->kind == CROSS_ARGUMENTS) {
            continue;
        }
        Stream *s = stream_for(r->stream);
        if (s->last) {
            records[s->last - 1].next = i + 1;
        } else {
            s->next = i + 1;
        }
        s->last = i + 1;
    }
    free(raw);
    record_count = n;
    return 0;
malformed:
    fprintf(stderr, "native: malformed audited argument records\n");
    free(raw);
    free(records);
    records = NULL;
    record_count = 0;
    return -1;
}

/* Memory hashes ---------------------------------------------------------------------------- */

static uint32_t *hash_frames;
static int hash_frame_count, hash_next;
static const char *dump_dir;

/* Main RAM, ITCM and DTCM, with what cannot agree between a Native and a Reference run
 * zeroed: the stacks (Native functions keep their frames on the host stack, and the calls
 * they make into the interpreter put their frames elsewhere), the threads' saved registers,
 * and the static data of functions that run Native (the PC's copy of it is the one in use). */
static uint8_t *snapshot;

static void hash_memory(uint32_t frame, char hex[41])
{
    uint8_t *buf = snapshot;
    const uint32_t itcm = 0, main = MEM_ITCM_SIZE, dtcm = MEM_ITCM_SIZE + MEM_MAIN_SIZE;
    const uint32_t total = MEM_ITCM_SIZE + MEM_MAIN_SIZE + MEM_DTCM_SIZE;
    if (buf == NULL) {
        buf = snapshot = malloc(total);
    }
    memcpy(buf + itcm, memory_host(MEM_ITCM_BASE, MEM_ITCM_SIZE), MEM_ITCM_SIZE);
    memcpy(buf + main, memory_host(MEM_MAIN_BASE, MEM_MAIN_SIZE), MEM_MAIN_SIZE);
    memcpy(buf + dtcm, memory_host(MEM_DTCM_BASE, MEM_DTCM_SIZE), MEM_DTCM_SIZE);
#define CLEAR(lo, hi)                                                                                                         \
    do {                                                                                                                      \
        uint32_t lo_ = (lo), hi_ = (hi);                                                                                      \
        for (uint32_t a_ = lo_; a_ < hi_; a_++) {                                                                             \
            if (a_ - MEM_ITCM_BASE < MEM_ITCM_SIZE) {                                                                         \
                buf[itcm + a_ - MEM_ITCM_BASE] = 0;                                                                           \
            } else if (a_ - MEM_MAIN_BASE < MEM_MAIN_SIZE) {                                                                  \
                buf[main + a_ - MEM_MAIN_BASE] = 0;                                                                           \
            } else if (a_ - MEM_DTCM_BASE < MEM_DTCM_SIZE) {                                                                  \
                buf[dtcm + a_ - MEM_DTCM_BASE] = 0;                                                                           \
            }                                                                                                                 \
        }                                                                                                                     \
    } while (0)
    uint32_t lowest = DTCM_STACKS_HIGH;
    uint32_t t = ds_word(THREAD_INFO_LIST);
    for (int n = 0; t != 0 && n < 64; n++) {
        /* the thread's saved registers (OSContext): Native code leaves other values in
           registers and on the stack than the ROM's code does */
        CLEAR(t, t + THREAD_CONTEXT_SIZE);
        uint32_t lo = ds_word(t + THREAD_STACK_LOW), hi = ds_word(t + THREAD_STACK_HIGH);
        if (lo < hi && hi - lo < 0x100000u) {
            CLEAR(lo, hi);
            if (hi > MEM_DTCM_BASE && hi <= DTCM_STACKS_HIGH && lo < lowest) {
                lowest = lo;
            }
        }
        t = ds_word(t + THREAD_NEXT);
    }
    /* the IRQ and SVC stacks above the launcher thread's */
    CLEAR(lowest < MEM_DTCM_BASE ? MEM_DTCM_BASE : lowest, DTCM_STACKS_HIGH);
    if (running || recording || replaying) {
        for (uint32_t i = 0; i < native_private_count; i++) {
            Fn *f = loaded_at(native_private[i].function);
            if (native_for_native(f)) {
                CLEAR(native_private[i].start, native_private[i].end);
            }
        }
    }
#undef CLEAR
    sha1_hex(buf, total, hex);
    if (dump_dir != NULL) {
        char path[600];
        snprintf(path, sizeof(path), "%s/ram-%u-%s.bin", dump_dir, frame, running ? "native" : "reference");
        FILE *f = fopen(path, "wb");
        if (f != NULL) {
            fwrite(buf, 1, total, f);
            fclose(f);
        }
    }
}

/* The Native run's memory against the Reference's at the same moment (the image the
 * Reference pass wrote to RUN_RAM_DUMP): the words that differ, except where the Native run
 * holds a PC address the ROM's code was handed and kept (a pointer to a variable on the host
 * stack, or to a source's wrapper function), which cannot be the Reference's. Returns the
 * count, -1 without the image; prints the first few. */
/* What Native code's uninitialized locals hold (tools/native.py, -ftrivial-auto-var-init=pattern):
 * clang fills them with 0xff bytes on a 32-bit target, gcc with 0xfe. The runtime is built by
 * the same compiler as the Native objects (tools/run.py). */
#ifdef __clang__
#define NATIVE_UNINIT_BYTE 0xffu
#else
#define NATIVE_UNINIT_BYTE 0xfeu
#endif

static long compare_with_reference(uint32_t frame)
{
    char path[600];
    snprintf(path, sizeof(path), "%s/ram-%u-reference.bin", dump_dir, frame);
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return -1;
    }
    const uint32_t total = MEM_ITCM_SIZE + MEM_MAIN_SIZE + MEM_DTCM_SIZE;
    uint8_t *ref = malloc(total);
    size_t got = fread(ref, 1, total, f);
    fclose(f);
    long differ = 0, host = 0, uninit = 0;
    for (uint32_t i = 0; got == total && i < total; i += 4) {
        uint32_t a, b;
        memcpy(&a, ref + i, 4);
        memcpy(&b, snapshot + i, 4);
        if (a == b) {
            continue;
        }
        /* a PC address the ROM's code was handed and kept */
        if (b >= 0x10000u && !native_fault_is_ds(b)) {
            host++;
            continue;
        }
        /* bytes of a Native's uninitialized local passed on into the game's memory (a structure
           filled in part and copied): the ROM's code leaves there what its stack held, Native
           code the fill tools/native.py asks the compiler for */
        uint32_t other = 0;
        for (int k = 0; k < 4; k++) {
            uint32_t byte_a = (a >> (8 * k)) & 0xffu, byte_b = (b >> (8 * k)) & 0xffu;
            other |= (uint32_t) (byte_a != byte_b && byte_b != NATIVE_UNINIT_BYTE) << k;
        }
        if (other == 0) {
            uninit++;
            continue;
        }
        if (differ++ < 8) {
            uint32_t at = i < MEM_ITCM_SIZE                   ? MEM_ITCM_BASE + i
                          : i < MEM_ITCM_SIZE + MEM_MAIN_SIZE ? MEM_MAIN_BASE + i - MEM_ITCM_SIZE
                                                              : MEM_DTCM_BASE + i - MEM_ITCM_SIZE - MEM_MAIN_SIZE;
            printf("native: memory after frame %u differs at %08x: Reference %08x, Native %08x\n", frame, at, a, b);
        }
    }
    free(ref);
    printf("native: memory after frame %u: %ld words differ from the Reference's, %ld more hold PC addresses, %ld "
           "uninitialized bytes\n",
           frame, got == total ? differ : -1, host, uninit);
    return got == total ? differ : -1;
}

static void print_hash(uint32_t frame, const char *hex)
{
    printf("ram frame %u %s %s (steps %llu)\n", frame, hex, running ? "native" : "reference", (unsigned long long) cpu->steps);
    fflush(stdout);
}

void native_frame_ended(uint32_t frame)
{
    frame_now = frame;
    /* without a trace there are no crossings to wait for: hash at the frame's end */
    if (!recording && !replaying && hash_next < hash_frame_count && frame >= hash_frames[hash_next]) {
        char hex[41];
        hash_memory(hash_frames[hash_next], hex);
        print_hash(hash_frames[hash_next], hex);
        hash_next++;
    }
}

/* In a recorded Reference run: a snapshot is due and no stream is inside code that would be
 * Native (where the Native run is ahead of the Reference, its effects already made). */
static int snapshot_due(void)
{
    if (hash_next >= hash_frame_count || frame_now < hash_frames[hash_next]) {
        return 0;
    }
    for (int i = 0; i < stream_count; i++) {
        Stream *s = &streams[i];
        if (s->depth > 0 && s->frames[s->depth - 1].native) {
            return 0;
        }
    }
    return 1;
}

/* Crossings, as both runs see them -------------------------------------------------------- */

/* For the reports: the Native function a call out of Native code came from (by the host
 * return address the trampoline was given), or NULL. */
static const char *out_caller;

static const NativeFunction *native_by_host(uint32_t eip);

static const char *caller_of(uint32_t host_return)
{
    const NativeFunction *n = native_by_host(host_return);
    if (n == NULL || host_return - (uintptr_t) n->host > 0x4000u) {
        return NULL;
    }
    /* past the next Native function's start it is someone else's code */
    uint32_t lo = 0, hi = by_host_count;
    while (lo < hi) {
        uint32_t mid = (lo + hi) / 2;
        if ((uintptr_t) by_host[mid]->host <= host_return) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo < by_host_count && host_return >= (uintptr_t) by_host[lo]->host) {
        return NULL;
    }
    Fn *f = first_at(n->address);
    for (Fn *end = fns + fn_count; f != NULL && f < end && (f->address & ~1u) == (n->address & ~1u); f++) {
        if (f->module == module_index(native_module(n))) {
            return f->name;
        }
    }
    return NULL;
}

static const char *learn_path;

/* With RUN_NATIVE_LEARN: the Native function whose own code the first difference points at
 * is noted, to be kept Reference, and the run ends (tools/run.py --learn runs it again). */
static void blame(const char *name, const char *why)
{
    if (learn_path == NULL || name == NULL || strncmp(name, "host ", 5) == 0) {
        return;
    }
    char plain[400];
    snprintf(plain, sizeof(plain), "%s", name);
    char *at = strstr(plain, " at host ");
    if (at != NULL) {
        *at = 0; /* "<name> at host <address>": the name */
    }
    name = plain;
    if (0) {
        return;
    }
    FILE *out = fopen(learn_path, "a");
    if (out != NULL) {
        fprintf(out, "%s %s\n", name, why);
        fclose(out);
    }
    printf("native: %s %s; it has to stay Reference\n", name, why);
    fflush(stdout);
    _Exit(3);
}

static int record_ended; /* the record ran out in the last frame (not a divergence) */

/* Where the program's code is (the image is linked at a fixed address: tools/run.py). */
#define HOST_CODE_LOW 0x00400000u
#define HOST_CODE_HIGH 0x01000000u

/* The Native functions whose return addresses are on the host stack from `esp` up: the
 * calls that led there. */
static void print_callers(uint32_t esp)
{
    printf("native: called from");
    const uint32_t *sp = (const uint32_t *) (uintptr_t) esp;
    for (int i = 0, n = 0; i < 1024 && n < 16 && native_os_accessible(esp + 4u * (uint32_t) i, 4, 0); i++) {
        const char *name = sp[i] >= 0x00401000u && sp[i] < HOST_CODE_HIGH ? caller_of(sp[i]) : NULL;
        if (name != NULL) {
            printf(" %s", name);
            n++;
        }
    }
    printf("\n");
    fflush(stdout);
}

static void report_divergence(Stream *s, const Record *r, uint32_t kind, uint32_t function)
{
    uint32_t left = 0;
    for (int i = 0; i < stream_count; i++) {
        left += streams[i].next != 0;
    }
    if (r == NULL && left == 0) {
        /* every stream's record is used up: the Reference run stopped here (its last frame),
           a few steps before the Native run, which ends with the frame */
        printf("native: the record ends at frame %u, stream %08x crossing %llu (where the Reference run stopped)\n", frame_now,
               s->key, (unsigned long long) s->seen);
        record_ended = 1;
        return;
    }
    printf("native: DIVERGED at frame %u, steps %llu, stream %08x crossing %llu: Reference %s %s", frame_now,
           (unsigned long long) cpu->steps, s->key, (unsigned long long) s->seen, r ? crossing_names[r->kind] : "(none)",
           r ? (r->kind == CROSS_SNAPSHOT ? "" : fn_name(r->function)) : "");
    if (r) {
        printf(" at steps %llu", (unsigned long long) (((uint64_t) r->steps_hi << 32) | r->steps_lo));
    }
    printf(", Native %s %s%s%s\n", crossing_names[kind], fn_name(function),
           out_caller && (kind == CROSS_CALL_OUT || kind == CROSS_BACK) ? " from " : "",
           out_caller && (kind == CROSS_CALL_OUT || kind == CROSS_BACK) ? out_caller : "");
    if (kind == CROSS_CALL_OUT || kind == CROSS_BACK) {
        /* the Native code that made the call is on the host stack above this frame */
        volatile uint32_t here = 0;
        print_callers((uint32_t) (uintptr_t) &here);
    }
    fflush(stdout);
}

/* RUN_NATIVE_WATCH=<address>: report every crossing (and Native call from the interpreter)
 * at which the word there has changed (debugging a memory difference). */
static uint32_t watch_address, watch_value;

static uint64_t value_differences;
/* RUN_NATIVE_DRIFT_FRAME=<frame>: print the first OFF-STEP calls, and the VALUE differences,
 * from that frame on (the default prints the run's first ten OFF-STEP calls) */
static uint32_t drift_from_frame;
static int drift_printed;
/* The function of a crossing into PC code (call_host): matches the Reference's whatever it is */
#define HOST_FUNCTION 0xfffffffeu
/* RUN_NATIVE_DEBUG=<stream>,<count>: print the first crossings of one stream */
static uint32_t debug_stream;
static int debug_left;
static unsigned long long debug_from;

/* A call from Native code into the ROM's code: the arguments it declares must be the
 * Reference's, except where the Native run passes a PC address (a variable on the host stack,
 * a string) and the Reference one on its stack (r->check is its stack pointer then). */
static void check_arguments(const Record *r, uint32_t function)
{
    Fn *f = loaded_at(function);
    if (f == NULL && contract_at(function) != NULL) {
        fprintf(stderr, "native: ARGUMENT audited owner %08x is not resident\n", function);
        exit(7);
    }
    unsigned words = contract_words(f);
    if (words) {
        uintptr_t start = (uintptr_t) records, current = (uintptr_t) r;
        unsigned extra = words > 4 ? (words - 4 + 2) / 3 : 0;
        if ((r->kind != CROSS_CALL && r->kind != CROSS_CALL_OUT) || r->function != (function & ~1u) ||
            (extra && (records == NULL || current < start || (current - start) % sizeof(Record) != 0 ||
                       (current - start) / sizeof(Record) + extra >= record_count))) {
            fprintf(stderr, "native: ARGUMENT audited parent or attachment is unavailable\n");
            exit(7);
        }
        for (unsigned i = 0; i < words; i++) {
            uint32_t a = i < 4 ? r->args[i] : r[1 + (i - 4) / 3].args[1 + (i - 4) % 3];
            uint32_t b = argument_word(i);
            int pointer = (f->argument_contract >> (8 + i)) & 1u;
            /* Only an explicitly declared pointer may refer to a readable PC
             * object instead of a mapped ROM object. Scalars never use this. */
            if (a == b ||
                (pointer && a != 0 && memory_host(a, 1) != NULL && !native_fault_is_ds(b) && native_os_accessible(b, 1, 0))) {
                continue;
            }
            fprintf(stderr,
                    "native: ARGUMENT audited %s word %u: Native %08x, Reference %08x "
                    "(frame %u, stream %08x, %s)\n",
                    fn_name(function), i + 1, b, a, frame_now, r->stream, crossing_names[r->kind]);
            exit(7);
        }
        replay_events += extra;
        return;
    }
    int n = f != NULL ? f->params : -1;
    if (n <= 0) {
        return;
    }
    for (int i = 0; i < n && i < 4; i++) {
        uint32_t a = r->args[i], b = cpu->r[i];
        if (a == b || (b >= 0x10000u && !native_fault_is_ds(b)) || a - r->check < 0x4000u) {
            continue;
        }
        char why[300];
        snprintf(why, sizeof(why), "passes %s argument %d as %08x where the ROM's code passes %08x (frame %u)",
                 fn_name(function), i + 1, b, a, frame_now);
        printf("native: ARGUMENT %s%s%s\n", why, out_caller ? ", from " : "", out_caller ? out_caller : "");
        fflush(stdout);
        blame(out_caller, why);
        return;
    }
}

/* A crossing happened in the Native run: compared with the Reference's, whose step count
 * then sets the Native run's clock. */
static void crossing(uint32_t kind, uint32_t function, uint32_t check, uint32_t resume)
{
    function &= ~1u;
    uint32_t key = stream_key();
    if (!replaying || diverged) {
        return;
    }
    Stream *s = stream_for(key);
    Record *r = s->next ? &records[s->next - 1] : NULL;
    if (r != NULL && r->kind == CROSS_SNAPSHOT && kind == CROSS_CALL) {
        char hex[41];
        hash_memory(r->function, hex);
        print_hash(r->function, hex);
        if (dump_dir != NULL) {
            compare_with_reference(r->function);
        }
        s->next = r->next;
        r = s->next ? &records[s->next - 1] : NULL;
    }
    s->seen++;
    peek(s->key, s->seen);
    if (watch_address != 0 && ds_word(watch_address) != watch_value) {
        printf("native: WATCH %08x: %08x -> %08x by crossing %llu of stream %08x (%s %s, frame %u, step %llu)\n",
               watch_address, watch_value, ds_word(watch_address), (unsigned long long) s->seen, s->key, crossing_names[kind],
               fn_name(function), frame_now, (unsigned long long) cpu->steps);
        watch_value = ds_word(watch_address);
    }
    if (debug_stream != 0 && s->key == debug_stream && debug_left > 0 && s->seen >= debug_from) {
        debug_left--;
        printf("native: debug stream %08x crossing %llu %s %s at step %llu, Reference %llu, r0-r3 %08x %08x %08x "
               "%08x, check %08x/%08x, inside %s, from %s\n",
               s->key, (unsigned long long) s->seen, crossing_names[kind], fn_name(function), (unsigned long long) cpu->steps,
               r ? (unsigned long long) (((uint64_t) r->steps_hi << 32) | r->steps_lo) : 0ull, cpu->r[0], cpu->r[1], cpu->r[2],
               cpu->r[3], r ? r->check : 0, check, depth > 0 && depth <= MAX_ACTIVE ? active[depth - 1]->name : "-",
               (kind == CROSS_CALL_OUT || kind == CROSS_BACK) && out_caller ? out_caller : "-");
    }
    /* HOST_FUNCTION: PC code the interpreter called (call_host), which stands for the Native
       function the ROM's code calls there; its name is the Reference's */
    if (r == NULL || r->kind != kind || (r->function != function && function != HOST_FUNCTION)) {
        /* Another call than the Reference's is usually data both runs read differently,
           made by Native code earlier: it is reported, not blamed (bisecting the Native set
           on memory or frames finds the cause), and the timing from the record ends here. */
        report_divergence(s, r, kind, function);
        diverged = 1;
        return;
    }
    s->next = r->next;
    replay_events++;
    if (kind == CROSS_CALL_OUT || (kind == CROSS_CALL && contract_at(r->function))) {
        check_arguments(r, function == HOST_FUNCTION ? r->function : function);
    }
    if (r->check != check && kind != CROSS_CALL_OUT && function != HOST_FUNCTION) {
        /* Same function, other values: a Native that computes something else, or one that
           got other arguments. The first ones are the place to look. */
        if (frame_now >= drift_from_frame && value_differences++ < 100000) {
            printf("native: VALUE at frame %u, stream %08x crossing %llu, %s %s%s%s: Reference %08x, Native %08x\n", frame_now,
                   s->key, (unsigned long long) s->seen, crossing_names[kind], fn_name(function),
                   out_caller && kind == CROSS_BACK ? " from " : "", out_caller && kind == CROSS_BACK ? out_caller : "",
                   r->check, check);
            fflush(stdout);
        }
        /* A result that is a PC address (a buffer on the host stack handed back) is expected;
           any other differs because the Native caller passed other arguments, or because the
           Native function computed another result. Differences in r0-r3 at a call are not
           blamed: arguments narrower than a word leave the rest of the register undefined. */
        int host_value = !native_fault_is_ds(check) && native_os_accessible(check, 1, 0);
        char why[300];
        /* r0 after a function declared void is whatever it left there */
        Fn *callee = loaded_at(function);
        int declared_void = callee != NULL && callee->native != NULL && native_return(callee->native) == NATIVE_RET_VOID;
        /* A Native's own result that differs is not blamed: a function the source declares
           void leaves what it last computed in r0, and the ROM's code another value. */
        if (kind == CROSS_BACK && !host_value && !declared_void) {
            snprintf(why, sizeof(why),
                     "calls %s with other arguments than the ROM's code (it returns %08x, not %08x; frame %u)",
                     fn_name(function), check, r->check, frame_now);
            blame(out_caller, why);
        }
    }
    uint64_t at = ((uint64_t) r->steps_hi << 32) | r->steps_lo;
    int irq = (cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
    if (kind == CROSS_CALL) {
        /* the interpreter got here by itself: it should be where the Reference was */
        if (cpu->steps != at) {
            uint64_t d = cpu->steps > at ? cpu->steps - at : at - cpu->steps;
            if (frame_now >= drift_from_frame && drift_printed < (drift_from_frame ? 5000 : 10)) {
                drift_printed++;
                printf("native: OFF-STEP at frame %u, stream %08x crossing %llu, call %s: Reference step %llu, "
                       "Native %llu\n",
                       frame_now, s->key, (unsigned long long) s->seen, fn_name(function), (unsigned long long) at,
                       (unsigned long long) cpu->steps);
            }
            drift_events++;
            if (d > drift_max) {
                drift_max = d;
            }
            /* Late: the interpreted code since the last crossing took more steps than the
               Reference's, because it worked on Native data laid out at other (host)
               addresses, e.g. a copy into a host stack buffer taking another alignment path.
               Native time is the Reference's at every crossing, so the extra steps not yet
               turned into bus time are taken back; an early arrival is not possible here (the
               stall at the last crossing holds the interpreter until the Reference's step). */
            if (cpu->steps > at) {
                drift_rewound += run_rewind(at);
            }
        }
        return;
    }
    /* Native code that runs late (call_native) gets here at the Reference's step, or after it
       by the time of the compiler helpers it called (interpreted, without crossings: the
       Reference counts their time as the Native function's); that time is taken back. */
    if (cpu->steps > at) {
        drift_rewound += run_rewind(at);
    }
    /* The next interpreted instruction, at `resume`, is the one the Reference executed after
       the branching instruction it was in at `at` (counted after the hook, so at + 1). */
    if (resume != 0) {
        cpu->stall_until[irq] = at + 1;
        cpu->stall_pc[irq] = resume & ~1u;
    }
}

/* The stack pointer the Reference called `target` with, when the next crossing of the
 * running stream is that call; else 0. */
static uint32_t replay_call_sp(uint32_t target)
{
    if (!replaying || diverged) {
        return 0;
    }
    Stream *s = stream_for(stream_key());
    Record *r = s->next ? &records[s->next - 1] : NULL;
    if (r == NULL || r->kind != CROSS_CALL_OUT || r->function != (target & ~1u)) {
        return 0;
    }
    return r->check;
}

/* Recording: the Reference run follows what the Native run would do at every branch target. */
static void record_branch(uint32_t address)
{
    uint32_t key = stream_key();
    if (key != 0 && key != STREAM_IRQ && streams[0].key == 0 && stream_count > 0 && streams[0].depth > 0) {
        /* OS_InitThread made the code that was running the first thread: its open crossings
           (made before there were threads, as stream 0) are that thread's from now on */
        int known = 0;
        for (int i = 0; i < stream_count; i++) {
            known |= streams[i].key == key;
        }
        if (!known) {
            streams[0].key = key;
            streams[0].seen = 0; /* the Native run counts the thread's crossings from here */
        }
    }
    Stream *s = stream_for(key);
    /* returns: the target is the open crossing's return address with its stack pointer */
    while (s->depth > 0) {
        struct Frame *t = &s->frames[s->depth - 1];
        if ((t->ret & ~1u) != address || t->sp != cpu->r[13]) {
            break;
        }
        s->depth--;
        write_record(key, t->native ? CROSS_RETURN : CROSS_BACK, t->function, cpu->steps,
                     t->native ? narrow_result(t->fn, cpu->r[0], cpu->r[1]) : cpu->r[0]);
    }
    int inside = s->depth > 0 && s->frames[s->depth - 1].native;
    Fn *f = first_at(address);
    if (f == NULL) {
        /* No function starts here. From Native code, a call to such an address (a veneer
           the linker put between two functions, which goes on to its target) is a call out
           as the Native run makes it; the branches inside Native code and inside the helpers
           it calls are not. */
        Fn *c = containing(address);
        if (!inside || (c != NULL && (native_for_native(c) || c->status == 'H')) || !inside_native(cpu->r[14]) ||
            (cpu->r[14] & ~1u) - (address & ~1u) < 8u) {
            return;
        }
        write_record(key, CROSS_CALL_OUT, address & ~1u, cpu->steps, cpu->r[13]);
        struct Frame out = {cpu->r[14], cpu->r[13], address & ~1u, 0, NULL};
        if (s->depth == s->capacity) {
            s->capacity = s->capacity ? s->capacity * 2 : 16;
            s->frames = realloc(s->frames, (size_t) s->capacity * sizeof(struct Frame));
        }
        s->frames[s->depth++] = out;
        return;
    }
    f = loaded_at(address);
    struct Frame frame = {cpu->r[14], cpu->r[13], address & ~1u, 0, f};
    if (!inside) {
        if (!native_for_interpreter(f)) {
            return;
        }
        if (snapshot_due()) {
            char hex[41];
            hash_memory(hash_frames[hash_next], hex);
            print_hash(hash_frames[hash_next], hex);
            uint64_t h = 0;
            for (int i = 0; i < 16; i++) {
                h = h << 4 | (uint64_t) (hex[i] <= '9' ? hex[i] - '0' : hex[i] - 'a' + 10);
            }
            write_record(key, CROSS_SNAPSHOT, hash_frames[hash_next], h, 0);
            hash_next++;
        }
        write_record(key, CROSS_CALL, address & ~1u, cpu->steps, argument_hash(f));
        frame.native = 1;
    } else {
        /* inside Native code: calls to other Native functions and to the compiler's helpers
           stay inside; a call to anything else is a call out */
        if (f == NULL || native_for_native(f) || f->status == 'H') {
            return;
        }
        /* A call from Native code returns into it (lr in a Native function), or, for a tail
           call, where the Native function itself returns. Anything else is code that runs
           in this thread's name without being its own: the scheduler between writing
           OSi_ThreadInfo.current and loading the thread's context, when the thread was
           interrupted inside Native code (which the Native run never is). */
        struct Frame *top = &s->frames[s->depth - 1];
        if (!inside_native(cpu->r[14]) && !((cpu->r[14] & ~1u) == (top->ret & ~1u) && cpu->r[13] == top->sp)) {
            return;
        }
        /* the callee's stack pointer: the Native run calls it with the same one */
        write_record(key, CROSS_CALL_OUT, address & ~1u, cpu->steps, cpu->r[13]);
    }
    if (s->depth == s->capacity) {
        s->capacity = s->capacity ? s->capacity * 2 : 16;
        s->frames = realloc(s->frames, (size_t) s->capacity * sizeof(struct Frame));
    }
    s->frames[s->depth++] = frame;
}

/* Reference -> Native ----------------------------------------------------------------------- */

/* Native code runs late: at the end of each stretch of time the Reference spent in it (the
 * step count of the next crossing it makes), not at the start. The interpreter idles first,
 * taking interrupts and running other threads as the Reference did meanwhile, then the Native
 * code runs at once. Its stores become visible when the Reference's whole stretch is done,
 * not before the Reference made its first one: the ROM's code mostly ends such a stretch
 * with the store that publishes the work (a buffer index flipped after filling the other
 * buffer, which the display reads line by line). */
static uint32_t deferred_pc[2]; /* the entry of a Native call waiting for its stall (per mode) */

/* The step count of the running stream's next crossing in the record; 0 without one. */
static uint64_t next_crossing_step(void)
{
    if (!replaying || diverged) {
        return 0;
    }
    Stream *s = stream_for(stream_key());
    Record *r = s->next ? &records[s->next - 1] : NULL;
    return r != NULL ? ((uint64_t) r->steps_hi << 32) | r->steps_lo : 0;
}

/* Where the interpreter idles when Native code waits between a call out and its next
 * crossing: an address no code has, hooked (native_hook_at) to end the run there. */
#define IDLE_ADDRESS 0xffffffe0u

static int idle_over(ArmCpu *c, void *user)
{
    (void) user;
    int mode = (c->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
    if (c->stall_branch[mode] && c->stall_pc[mode] == IDLE_ADDRESS) {
        return 0; /* still waiting (the start of a slice, or back from an interrupt) */
    }
    c->r[15] = ARM_RETURN_ADDRESS;
    return ARM_HOOK_AGAIN;
}

/* Native code that called out: idle until the Reference's next crossing (see above). */
static void idle_until(uint64_t at)
{
    int mode = (cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
    if (at <= cpu->steps) {
        return;
    }
    uint32_t saved[16], saved_cpsr = cpu->cpsr;
    memcpy(saved, cpu->r, sizeof(saved));
    cpu->r[15] = IDLE_ADDRESS;
    cpu->r[14] = ARM_RETURN_ADDRESS;
    cpu->stall_until[mode] = at;
    cpu->stall_pc[mode] = IDLE_ADDRESS;
    cpu->stall_branch[mode] = 1;
    run_until_return();
    memcpy(cpu->r, saved, sizeof(saved));
    cpu->cpsr = saved_cpsr;
}

static uint64_t publications;

static void publish_word(uint32_t pc, uint32_t *pointer, uint32_t value)
{
    uint32_t address = (uint32_t) (uintptr_t) pointer;
    if (publication_owner(pc, address) == 0) {
        fprintf(stderr, "native: unaudited publication %08x -> %08x\n", pc, address);
        exit(7);
    }
    if (replaying && !diverged) {
        Stream *s = stream_for(stream_key());
        Record *r = s->next ? &records[s->next - 1] : NULL;
        if (r == NULL || r->kind != CROSS_PUBLISH || r->function != pc) {
            report_divergence(s, r, CROSS_PUBLISH, pc);
            if (!record_ended) {
                exit(7);
            }
            diverged = 1;
        } else {
            if (r->args[0] != address || r->args[1] != 4 || r->check != value) {
                fprintf(stderr,
                        "native: publication mismatch at frame %u, pc %08x: "
                        "Native [%08x]=%08x, Reference [%08x]/%u=%08x\n",
                        frame_now, pc, address, value, r->args[0], r->args[1], r->check);
                exit(7);
            }
            uint64_t at = ((uint64_t) r->steps_hi << 32) | r->steps_lo;
            idle_until(at);
            if (cpu->steps > at) {
                drift_rewound += run_rewind(at);
            }
            if (!run_native_store_boundary()) {
                fprintf(stderr, "native: publication at %08x arrived after its hardware time\n", pc);
                exit(7);
            }
            crossing(CROSS_PUBLISH, pc, value, 0);
        }
    }
    /* The value is supplied by the compiled body, never taken from a record. */
    if (!bus_write(address, 4, value)) {
        fprintf(stderr, "native: publication address is not writable: %08x\n", address);
        exit(7);
    }
    publications++;
    idle_until(next_crossing_step());
}

static int call_native(ArmCpu *c, void *user)
{
    Fn *f = user;
    int mode = (c->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
    uint32_t entry = f->address & ~1u;
    if (deferred_pc[mode] == entry && c->stall_branch[mode]) {
        return 0; /* waiting to run late (the start of a slice, or back from an interrupt) */
    }
    int late = deferred_pc[mode] == entry;
    deferred_pc[mode] = 0;
    uint32_t lr = c->r[14];
    uint32_t args[ARG_WORDS];
    memcpy(args, c->r, 16);
    for (int i = 0; i < STACK_WORDS; i++) {
        args[4 + i] = ds_word(c->r[13] + 4u * (uint32_t) i);
    }
    if (!late) {
        crossing(CROSS_CALL, f->address, argument_hash(f), 0);
        /* the interpreter waits at the entry, as for any stall; it comes back here when the
           time is up (ArmCpu.stall_branch). The branch that got here is counted by then. */
        uint64_t at = next_crossing_step();
        if (at > c->steps + 1) {
            deferred_pc[mode] = entry;
            c->stall_until[mode] = at;
            c->stall_pc[mode] = entry;
            c->stall_branch[mode] = 1;
            return 0;
        }
    }
    f->calls_in++;
    calls_in++;
    if (depth < MAX_ACTIVE) {
        active[depth] = f;
    }
    if (++depth > depth_max) {
        depth_max = depth;
    }
    /* The branch that got here is counted when this hook returns; the Reference counts it
       before the function's first instruction, so the interpreted code this call reaches
       (calls out, interrupts during their stalls) starts one step later. Count it now. */
    int inside = !c->hook_between;
    c->steps += (uint64_t) inside;
    GuestContext *guest = guest_current();
    unsigned saved_anchor_depth = guest->anchor_depth;
    uint32_t saved_anchor_sp = guest->anchor_sp;
    Fn *saved_anchor = guest->anchor;
    guest->anchor_depth = guest->depth;
    guest->anchor_sp = c->r[13];
    guest->anchor = f;
    int return_kind = native_return(f->native);
    uint64_t v = native_aggregate_kind(return_kind) ? native_aggregate_invoke(return_kind, f->native->host, args)
                                                    : host_invoke(f->native->host, args, ARG_WORDS, is_member(f->native));
    if (guest->depth != guest->anchor_depth) {
        fprintf(stderr, "native: unbalanced guest call stack at %s\n", f->name);
        abort();
    }
    guest->anchor_depth = saved_anchor_depth;
    guest->anchor_sp = saved_anchor_sp;
    guest->anchor = saved_anchor;
    c->steps -= (uint64_t) inside;
    c->hook_between = !inside;
    depth--;
    if (watch_address != 0 && ds_word(watch_address) != watch_value) {
        printf("native: WATCH %08x: %08x -> %08x after %s at frame %u step %llu (r0-r3 %08x %08x %08x %08x)\n", watch_address,
               watch_value, ds_word(watch_address), f->name, frame_now, (unsigned long long) c->steps, args[0], args[1],
               args[2], args[3]);
        watch_value = ds_word(watch_address);
    }
    crossing(CROSS_RETURN, f->address, narrow_result(f, (uint32_t) v, (uint32_t) (v >> 32)), lr);
    switch (native_return(f->native)) {
        case NATIVE_RET_U8:
            c->r[0] = (uint8_t) v;
            break;
        case NATIVE_RET_S8:
            c->r[0] = (uint32_t) (int32_t) (int8_t) v;
            break;
        case NATIVE_RET_U16:
            c->r[0] = (uint16_t) v;
            break;
        case NATIVE_RET_S16:
            c->r[0] = (uint32_t) (int32_t) (int16_t) v;
            break;
        case NATIVE_RET_64:
        case NATIVE_RET_PAIR8:
            c->r[0] = (uint32_t) v;
            c->r[1] = (uint32_t) (v >> 32);
            break;
        case NATIVE_RET_VOID:
            /* Some callers use r0 after a function their source calls void: the ROM's code
               leaves there what its last call returned (a factory that allocates and
               constructs an object hands the object back), and the PC's leaves that in eax
               too. An empty function (`bx lr`) hands back its first argument instead. */
            if (f->size > 4) {
                c->r[0] = (uint32_t) v;
            }
            break;
        default:
            c->r[0] = (uint32_t) v;
            break;
    }
    if (lr & 1) {
        c->cpsr |= ARM_CPSR_T;
    } else {
        c->cpsr &= ~ARM_CPSR_T;
    }
    c->r[15] = lr & ~1u;
    return 0;
}

/* The ROM's code calling PC code: a function pointer Native code handed it that is not a
 * DS address. These are the small wrappers some sources pass where the ROM's code passes a
 * function of another type (`#ifndef __MWERKS__`: a constructor for __cxa_vec_ctor, a
 * destructor for __register_global_object); each calls one function with the object. The
 * interpreter goes to that function's DS address instead, as the ROM's code does, and the
 * function then runs Native or not like any other. */

static uint32_t wrapped_function(uint32_t host)
{
    static uint32_t cache_host[64], cache_ds[64];
    for (int i = 0; i < 64; i++) {
        if (cache_host[i] == host) {
            return cache_ds[i];
        }
    }
    uint32_t ds = 0;
    /* A Clean function itself: Clean code that hands the game a function by its game symbol
       gets the Clean function when that symbol is registered (CLEAN_AS). */
    for (uint32_t c = 0; c < clean_function_count && ds == 0; c++) {
        if ((uint32_t) (uintptr_t) clean_functions[c].host == host) {
            ds = clean_functions[c].address;
        }
    }
    const uint8_t *code = (const uint8_t *) (uintptr_t) host;
    for (int i = 0; i < 64 && ds == 0; i++) {
        if (code[i] != 0xe8 && code[i] != 0xe9) { /* call / jmp rel32 */
            continue;
        }
        int32_t rel;
        memcpy(&rel, code + i + 1, 4);
        uint32_t target = host + (uint32_t) i + 5u + (uint32_t) rel;
        if (native_fault_is_ds(target) && target >= 0x01000000u) {
            ds = target; /* a function kept out of the Native set: its DS address */
        } else if (target - HOST_CODE_LOW < HOST_CODE_HIGH - HOST_CODE_LOW) {
            const NativeFunction *n = native_by_host(target);
            if (n != NULL && (uintptr_t) n->host == target) {
                ds = n->address;
            }
        }
    }
    static int next;
    cache_host[next & 63] = host;
    cache_ds[next & 63] = ds;
    next++;
    return ds;
}

static int call_host(ArmCpu *c, void *user)
{
    (void) user;
    uint32_t ds = wrapped_function(c->r[15]);
    if (ds == 0) {
        printf("native: the ROM's code called PC code at %08x that wraps no known function\n", c->r[15]);
        run_finish("a call into PC code", 1);
    }
    calls_host++;
    if (ds & 1) {
        c->cpsr |= ARM_CPSR_T;
    } else {
        c->cpsr &= ~ARM_CPSR_T;
    }
    c->r[15] = ds & ~1u;
    return ARM_HOOK_AGAIN;
}

ArmHook native_hook_at(uint32_t address, void **hook_user)
{
    if (recording) {
        record_branch(address);
        return NULL;
    }
    if (running && address - HOST_CODE_LOW < HOST_CODE_HIGH - HOST_CODE_LOW) {
        return call_host;
    }
    if (running && address == IDLE_ADDRESS) {
        return idle_over;
    }
    if (!running || first_at(address) == NULL) {
        return NULL;
    }
    Fn *f = loaded_at(address);
    if (!native_for_interpreter(f)) {
        return NULL;
    }
    *hook_user = f;
    return call_native;
}

/* Native -> Reference ----------------------------------------------------------------------- */

uint32_t native_pop_bytes;
uint32_t native_return_floating;

uint64_t native_call_reference(uint32_t target, const uint32_t *args, uint32_t self);

/* Called by native_trampoline (native_tramp.S): Native code called `target` with `args` on
 * its stack (and `self` in ecx). */
uint64_t native_call_reference(uint32_t target, const uint32_t *args, uint32_t self)
{
    (void) self; /* the Native objects pass `this` on the stack (HOST_THISCALL) */
    Fn *f = loaded_at(target);
    uint32_t words[ARG_WORDS];
    memcpy(words, args, ARG_WORDS * 4);
    int aggregate_kind = f != NULL && f->native != NULL ? native_return(f->native) : NATIVE_RET_SKIP;
    NativeAggregateCall aggregate;
    if (native_aggregate_kind(aggregate_kind)) {
        native_aggregate_prepare(aggregate_kind, args, words, &aggregate);
    }
    uint32_t saved[16], saved_cpsr = cpu->cpsr;
    memcpy(saved, cpu->r, sizeof(saved));
    uint32_t sp = (cpu->r[13] - 4u * STACK_WORDS) & ~7u;
    uint32_t same_sp = replay_call_sp(target);
    if (same_sp != 0 && same_sp < cpu->r[13] && cpu->r[13] - same_sp < 0x2000u) {
        /* The ROM's code is called where the Reference's stack pointer was: its frames, and
           pointers into them that it keeps (a request it queues with a buffer on its stack),
           are where the Reference has them. */
        sp = same_sp;
    }
    /* Write only proven arguments past r0-r3. Copying the unused host words
       overwrites ROM stack residue that later game code can observe. Unknown
       signatures retain the legacy extent until their ABI is audited. */
    uint32_t stack_words = STACK_WORDS;
    if (f != NULL && f->arg_words >= 0) {
        stack_words = f->arg_words > 4 ? (uint32_t) f->arg_words - 4 : 0;
        if (stack_words > STACK_WORDS) {
            stack_words = STACK_WORDS;
        }
    }
    for (uint32_t i = 0; i < stack_words && sp + 4u * i < cpu->r[13]; i++) {
        bus_write(sp + 4u * i, 4, words[4 + i]);
    }
    memcpy(cpu->r, words, 16);
    cpu->r[13] = sp;
    cpu->r[14] = ARM_RETURN_ADDRESS;
    cpu->r[15] = target & ~1u;
    if (target & 1) {
        cpu->cpsr |= ARM_CPSR_T;
    } else {
        cpu->cpsr &= ~ARM_CPSR_T;
    }
    /* the caller, by name and by host address (the link map names code no table entry has,
       such as an inline function of a header) */
    static char where[4][440];
    static int which;
    const char *known_caller = caller_of(args[-1]);
    snprintf(where[which & 3], sizeof(where[0]), "%s%shost %08x", known_caller ? known_caller : "", known_caller ? " at " : "",
             args[-1]);
    const char *caller = where[which++ & 3];
    out_caller = caller;
    /* A compiler helper (status H) the source calls by name: the Reference counts its time as
       the calling Native function's (it has no crossing there), so none is made here either;
       the next crossing's step count takes up its time. */
    int quiet = f != NULL && f->status == 'H';
    if (!quiet) {
        crossing(CROSS_CALL_OUT, target, 0, target);
    }
    calls_out++;
    if (f != NULL) {
        f->calls_out++;
    }
    run_until_return();
    uint64_t v = ((uint64_t) cpu->r[1] << 32) | cpu->r[0];
    out_caller = caller;
    if (!quiet) {
        crossing(CROSS_BACK, target, cpu->r[0], 0);
        /* the callee is back; the Native caller goes on late, as it started (call_native) */
        uint32_t r0 = cpu->r[0], r1 = cpu->r[1];
        idle_until(next_crossing_step());
        cpu->r[0] = r0;
        cpu->r[1] = r1;
    }
    /* The callee kept r4-r11 and sp, as the calling convention says; the rest goes back to
       what the interpreted caller of the Native function had, which it does not rely on.
       CPSR stays as the callee left it (OS_DisableInterrupts changes it on purpose), except
       for the state bit of the code that was running. */
    memcpy(cpu->r, saved, sizeof(saved));
    cpu->cpsr = (cpu->cpsr & ~ARM_CPSR_T) | (saved_cpsr & ARM_CPSR_T);
    native_pop_bytes = 0;
    native_return_floating = f != NULL && f->native != NULL ? (uint32_t) native_floating(f->native) : 0;
    if (native_aggregate_kind(aggregate_kind)) {
        v = native_aggregate_finish(aggregate_kind, &aggregate, v, &native_pop_bytes);
    }
    return v;
}

int native_fault_is_ds(uint32_t address)
{
    /* the DS's memory map from ITCM's mirrors to the GBA slot, and its BIOS */
    return address < 0x10000000u && (address >= 0x01000000u || address < 0x00010000u) ? 1 : address >= 0xffff0000u;
}

uintptr_t native_fault_execute(uint32_t target, uint32_t *eax, uint32_t ecx)
{
    (void) ecx; /* only a thiscall would need it (HOST_THISCALL) */
    Fn *f = loaded_at(target);
    if ((target & ~1u) == 0x020404b4u && f != NULL && f->native != NULL && native_return(f->native) == NATIVE_RET_32) {
        /* A DS function pointer has the Native declaration's union ABI. The
         * selected Clean entry has a scalar ABI, so go through the Native
         * public entry patched by patch_clean, including when Clean is forced
         * back through the interpreter. */
        for (uint32_t i = 0; i < native_function_count; i++) {
            const NativeFunction *n = &native_functions[i];
            if ((n->address & ~1u) == (target & ~1u) && native_return(n) == NATIVE_RET_UNION4 &&
                (n->info >> 16) == (f->native->info >> 16)) {
                calls_pointer++;
                return (uintptr_t) n->host;
            }
        }
    }
    if (native_for_native(f)) {
        /* a pointer to a function that has a Native: go straight there, the arguments are
           already where its convention wants them */
        calls_pointer++;
        return (uintptr_t) f->native->host;
    }
    *eax = target;
    return (uintptr_t) native_trampoline;
}

/* Hardware ---------------------------------------------------------------------------------- */

/* Each body's copy keeps the actual host start for fault-offset bounds. Its
 * address and module still identify the original Native function. */
static NativeFunction *body_entries;

static const NativeFunction *native_by_host(uint32_t eip)
{
    uint32_t lo = 0, hi = by_host_count;
    while (lo < hi) {
        uint32_t mid = (lo + hi) / 2;
        if ((uintptr_t) by_host[mid]->host <= eip) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo ? by_host[lo - 1] : NULL;
}

int native_fault_data(uint32_t eip, uint32_t address, uint32_t esp)
{
    if (depth == 0 || depth > MAX_ACTIVE) {
        return 0;
    }
    /* The function at fault: the Native function the host code belongs to when it is one,
       else (a C library routine it called) the innermost one the interpreter entered. */
    const NativeFunction *n = NULL;
    if (by_host_count != 0 && eip >= (uintptr_t) by_host[0]->host) {
        n = native_by_host(eip);
        if (n != NULL && eip - (uintptr_t) n->host > 0x4000u) {
            n = NULL;
        }
    }
    Fn *f = n != NULL ? loaded_at(n->address) : NULL;
    if (f == NULL) {
        f = active[depth - 1];
    }
    /* the DS's I/O, palettes, VRAM, OAM and GBA slot; anything else is a bad pointer */
    int hardware = address >= 0x04000000u && address < 0x0a000000u;
    printf("native: %s (%08x %s) %s %08x (host eip %08x, frame %u, entered as %s)%s\n", f->name, f->address & ~1u,
           modules[f->module].name, hardware ? "touches" : "faults at", address, eip, frame_now, active[depth - 1]->name,
           diverged   ? ", after the run diverged"
           : hardware ? "; it has to stay Reference"
                      : "");
    print_callers(esp);
    /* Only what a run still in step with the Reference finds is the function's own doing. */
    if (learn_path != NULL && !diverged) {
        FILE *out = fopen(learn_path, "a");
        if (out != NULL) {
            fprintf(out, "%s %s %08x\n", f->name, hardware ? "touches the hardware at" : "faults (wild pointer) at", address);
            fclose(out);
        }
    }
    exit(3);
}

/* A Native function that loops waiting for something only interrupts or other threads do
 * (a flag an IRQ handler sets) never returns: nothing interpreted runs while it does. The
 * watchdog notices the step count standing still and names the function. */
static uint64_t watch_last_steps = ~0ull;

static int making_progress(void)
{
    uint64_t now = cpu->steps;
    int moved = now != watch_last_steps;
    watch_last_steps = now;
    return moved;
}

static void stuck_in(uint32_t eip)
{
    const NativeFunction *n = native_by_host(eip);
    Fn *f = n != NULL && eip - (uintptr_t) n->host < 0x4000u ? loaded_at(n->address) : NULL;
    if (f == NULL && depth > 0 && depth <= MAX_ACTIVE) {
        f = active[depth - 1];
    }
    printf("native: %s does not return: it loops at host eip %08x (frame %u, step %llu), waiting for what only "
           "interpreted code does; it has to stay Reference\n",
           f ? f->name : "?", eip, frame_now, (unsigned long long) cpu->steps);
    fflush(stdout);
    if (learn_path != NULL && f != NULL && !diverged) {
        FILE *out = fopen(learn_path, "a");
        if (out != NULL) {
            fprintf(out, "%s loops waiting for interrupts or other threads\n", f->name);
            fclose(out);
        }
    }
    _Exit(3);
}

int native_fault_divide(uint32_t eip)
{
    const NativeFunction *n = running ? native_by_host(eip) : NULL;
    if (n == NULL || eip - (uintptr_t) n->host >= 0x4000u) {
        return 0;
    }
    /* each function once (the first few) */
    static const NativeFunction *seen[16];
    static int seen_count;
    int known = 0;
    for (int i = 0; i < seen_count; i++) {
        known |= seen[i] == n;
    }
    if (!known && seen_count < 16) {
        seen[seen_count++] = n;
        printf("native: %s divides by zero at frame %u; it goes on with the ROM's helpers' result (the dividend, "
               "remainder 0)\n",
               caller_of(eip), frame_now);
        fflush(stdout);
    }
    return 1;
}

void native_watch_hit(uint32_t eip)
{
    const NativeFunction *n = native_by_host(eip);
    const char *name = n != NULL && eip - (uintptr_t) n->host < 0x4000u ? caller_of(eip) : NULL;
    printf("native: HWWATCH written by host eip %08x (%s) at frame %u step %llu, pc %08x\n", eip, name ? name : "the runtime",
           frame_now, (unsigned long long) cpu->steps, cpu->r[15]);
    fflush(stdout);
}

/* Threads ------------------------------------------------------------------------------------ */

typedef struct Flow {
    uint32_t thread;
    void *fiber;
    uint64_t stall;
    uint32_t stall_pc;
    int stall_branch;
    uint32_t deferred; /* deferred_pc[0] of the thread */
    int counted;       /* left inside an instruction, which was counted then (see move_to_thread) */
    int between;       /* left from hooks between instructions (ArmCpu.hook_between) */
} Flow;

static Flow flows[MAX_STREAMS];
static int flow_count, flow_now;

__attribute__((target("general-regs-only"))) static GuestContext *guest_current(void)
{
    int irq = (cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
    return &guest_contexts[irq ? MAX_STREAMS : flow_now];
}

static void fiber_main(void)
{
    run_forever();
}

static int move_to_thread(ArmCpu *c, void *user)
{
    (void) user;
    uint32_t thread = ds_word(THREAD_INFO_CURRENT);
    Flow *from = &flows[flow_now];
    from->stall = c->stall_until[0];
    from->stall_pc = c->stall_pc[0];
    from->stall_branch = c->stall_branch[0];
    from->deferred = deferred_pc[0];
    int to = -1;
    for (int i = 0; i < flow_count; i++) {
        if (flows[i].thread == thread) {
            to = i;
        }
    }
    if (to < 0) {
        if (flow_count == MAX_STREAMS) {
            fprintf(stderr, "native: more than %d threads\n", MAX_STREAMS);
            exit(2);
        }
        to = flow_count++;
        flows[to].thread = thread;
        flows[to].fiber = NULL;
        flows[to].stall = 0;
        flows[to].stall_branch = 0;
        flows[to].deferred = 0;
    }
    if (to == flow_now) {
        return 0;
    }
    if (flows[to].fiber == NULL) {
        flows[to].fiber = native_os_fiber_create(fiber_main);
        if (flows[to].fiber == NULL) {
            fprintf(stderr, "native: cannot make a host stack for thread %08x\n", thread);
            exit(2);
        }
        fibers_made++;
    }
    c->stall_until[0] = flows[to].stall;
    c->stall_pc[0] = flows[to].stall_pc;
    c->stall_branch[0] = flows[to].stall_branch;
    deferred_pc[0] = flows[to].deferred;
    /* The branching instruction this hook runs in is counted when the hook returns, which on
       this stack happens only when the thread comes back. The run goes on meanwhile, so the
       instruction is counted now, as in a run without fibers, and not again on the return. */
    from->between = c->hook_between;
    from->counted = !c->hook_between;
    c->steps += (uint64_t) from->counted;
    flow_now = to;
    thread_moves++;
    native_os_fiber_switch(flows[to].fiber);
    /* Back on this thread's stack: the run moved on while it was away, so the hooks at the
       current pc are looked up again (jump() in arm.c). */
    c->steps -= (uint64_t) flows[flow_now].counted;
    c->hook_between = flows[flow_now].between;
    flows[flow_now].counted = 0;
    return ARM_HOOK_AGAIN;
}

ArmHook native_thread_changed(uint32_t previous, uint32_t thread)
{
    if (!running) {
        return NULL;
    }
    if (previous == 0) {
        /* the first thread (OS_InitThread) is the code that was running all along */
        flows[flow_now].thread = thread;
        return NULL;
    }
    return move_to_thread;
}

/* The PC's memory, as the interpreter sees it: Native code hands the ROM's code pointers to
 * its strings and to variables on its own stack. Counted: every such address is one that
 * differs from the Reference's. */
static uint64_t host_accesses;

static int host_access(uint32_t address, int size, uint32_t *value, int write)
{
    if (native_fault_is_ds(address) || !native_os_accessible(address, (uint32_t) size, write)) {
        return 0;
    }
    host_accesses++;
    void *p = (void *) (uintptr_t) address;
    if (write) {
        memcpy(p, value, (size_t) size);
    } else {
        *value = 0;
        memcpy(value, p, (size_t) size);
    }
    return 1;
}

/* Setup -------------------------------------------------------------------------------------- */

int native_running(void)
{
    return running;
}

void native_resident_ready(void)
{
    resident_ready = 1;
}

/* Native functions that may not run: their entry jumps to a stub that calls the trampoline
 * with their DS address, so Native callers reach the ROM's code. */
/* Whether the function's ROM code is a lone `bx lr`. */
static int only_returns(const Fn *f)
{
    const Module *m = &modules[f->module];
    uint32_t a = f->address & ~1u;
    if (m->image == NULL || a < m->base || a - m->base + f->size > m->size) {
        return 0;
    }
    const uint8_t *code = m->image + (a - m->base);
    if (f->address & 1) {
        return f->size == 2 && code[0] == 0x70 && code[1] == 0x47; /* bx lr */
    }
    return f->size == 4 && code[0] == 0x1e && code[1] == 0xff && code[2] == 0x2f && code[3] == 0xe1;
}

static int patch_kept(void)
{
    int count = 0;
    for (int i = 0; i < fn_count; i++) {
        count += fns[i].native != NULL && !native_for_native(&fns[i]);
    }
    uint8_t *stubs = native_os_code_alloc((size_t) count * 16 + 16);
    if (stubs == NULL) {
        return -1;
    }
    int n = 0;
    for (int i = 0; i < fn_count; i++) {
        Fn *f = &fns[i];
        if (native_for_native(f) && native_return(f->native) == NATIVE_RET_VOID && only_returns(f)) {
            /* An empty function (`bx lr`) hands its first argument back in r0, and callers
               that declare it as returning a value use that; the PC's empty function returns
               nothing. It becomes `return first argument`, what the ROM's code does. */
            static const uint8_t identity[5] = {0x8b, 0x44, 0x24, 0x04, 0xc3}; /* mov eax,[esp+4]; ret */
            if (native_os_patch((void *) f->native->host, identity, sizeof(identity)) != 0) {
                return -1;
            }
            continue;
        }
        if (f->native == NULL || native_for_native(f)) {
            continue;
        }
        uint8_t *stub = stubs + 16 * n++;
        uint32_t target = f->address;
        stub[0] = 0xb8; /* mov eax, target */
        memcpy(stub + 1, &target, 4);
        stub[5] = 0xe9; /* jmp native_trampoline */
        int32_t rel = (int32_t) ((uintptr_t) native_trampoline - ((uintptr_t) stub + 10));
        memcpy(stub + 6, &rel, 4);
        uint8_t jmp[5] = {0xe9};
        rel = (int32_t) ((uintptr_t) stub - ((uintptr_t) f->native->host + 5));
        memcpy(jmp + 1, &rel, 4);
        if (native_os_patch((void *) f->native->host, jmp, 5) != 0) {
            return -1;
        }
    }
    return 0;
}

/* Native code calls a Native function directly, not through the table: each Native function
 * with a Clean version jumps to it, so every caller runs the Clean code. Both take the
 * arguments on the stack and return in eax. */
static int is_clean(const Fn *f)
{
    return f != NULL && f->native >= clean_functions && f->native < clean_functions + clean_function_count;
}

static int patch_clean(void)
{
    uint8_t *stubs = native_os_code_alloc((size_t) clean_function_count * 16 + 16);
    uint8_t *wrappers = NULL; /* 48 bytes for each Clean function with a narrow result */
    if (stubs == NULL) {
        return -1;
    }
    for (uint32_t c = 0; c < clean_function_count; c++) {
        const NativeFunction *clean = &clean_functions[c];
        if (clean->info & CLEAN_STANDBY) {
            /* Not selected: Clean code calling it gets what its function's callers get, its
               Native version (itself patched when that stays Reference) or else the ROM's code. */
            const void *to = NULL;
            for (uint32_t i = 0; i < native_function_count && to == NULL; i++) {
                const NativeFunction *n = &native_functions[i];
                if (n->address == clean->address && (n->info >> 16) == (clean->info >> 16)) {
                    to = n->host;
                    if ((n->address & ~1u) == 0x020404b4u && native_return(n) == NATIVE_RET_UNION4 &&
                        native_return(clean) == NATIVE_RET_32) {
                        to = native_aggregate_clean_bridge(NATIVE_RET_32, NATIVE_RET_UNION4, to);
                    }
                }
            }
            if (to == NULL) {
                uint8_t *stub = stubs + 16 * c;
                uint32_t target = clean->address;
                stub[0] = 0xb8; /* mov eax, target */
                memcpy(stub + 1, &target, 4);
                stub[5] = 0xe9; /* jmp native_trampoline */
                int32_t rel = (int32_t) ((uintptr_t) native_trampoline - ((uintptr_t) stub + 10));
                memcpy(stub + 6, &rel, 4);
                to = stub;
            }
            uint8_t jmp[5] = {0xe9};
            int32_t rel = (int32_t) ((uintptr_t) to - ((uintptr_t) clean->host + 5));
            memcpy(jmp + 1, &rel, 4);
            if (native_os_patch((void *) clean->host, jmp, 5) != 0) {
                return -1;
            }
            continue;
        }
        for (uint32_t i = 0; i < native_function_count; i++) {
            const NativeFunction *n = &native_functions[i];
            if (n->address != clean->address || (n->info >> 16) != (clean->info >> 16)) {
                continue;
            }
            const void *to = clean->host;
            int kind = native_return(n);
            if ((n->address & ~1u) == 0x020404b4u && kind == NATIVE_RET_UNION4 && native_return(clean) == NATIVE_RET_32) {
                to = native_aggregate_clean_bridge(NATIVE_RET_UNION4, NATIVE_RET_32, to);
            }
            if (kind == NATIVE_RET_U8 || kind == NATIVE_RET_S8 || kind == NATIVE_RET_U16 || kind == NATIVE_RET_S16) {
                /* A char or short result: Native callers (many declare such a function as
                   returning int) take eax whole, which the Native's wrapper extended as the
                   ROM's code does (tools/native.py, widen) and the PC's compiler leaves as it
                   is. The Clean function is called through a wrapper of the same kind: the
                   argument words copied down, the result extended. */
                static const uint8_t extend[][3] = {
                    [NATIVE_RET_U8] = {0x0f, 0xb6, 0xc0},  /* movzbl %al, %eax */
                    [NATIVE_RET_S8] = {0x0f, 0xbe, 0xc0},  /* movsbl %al, %eax */
                    [NATIVE_RET_U16] = {0x0f, 0xb7, 0xc0}, /* movzwl %ax, %eax */
                    [NATIVE_RET_S16] = {0x0f, 0xbf, 0xc0}, /* movswl %ax, %eax */
                };
                if (wrappers == NULL && (wrappers = native_os_code_alloc((size_t) clean_function_count * 48)) == NULL) {
                    return -1;
                }
                uint8_t *w = wrappers + 48 * c;
                static const uint8_t head[] = {
                    0x55,                         /* push %ebp */
                    0x89, 0xe5,                   /* mov %esp, %ebp */
                    0x56,                         /* push %esi */
                    0x57,                         /* push %edi */
                    0x83, 0xec, 0x40,             /* sub $64, %esp */
                    0x8d, 0x75, 0x08,             /* lea 8(%ebp), %esi */
                    0x89, 0xe7,                   /* mov %esp, %edi */
                    0xb9, 0x10, 0x00, 0x00, 0x00, /* mov $16, %ecx */
                    0xf3, 0xa5,                   /* rep movsl */
                    0xe8,                         /* call clean */
                };
                static const uint8_t tail[] = {
                    0x83, 0xc4, 0x40, /* add $64, %esp */
                    0x5f,             /* pop %edi */
                    0x5e,             /* pop %esi */
                    0x5d,             /* pop %ebp */
                    0xc3,             /* ret */
                };
                size_t at = 0;
                memcpy(w, head, sizeof(head));
                at += sizeof(head);
                int32_t call = (int32_t) ((uintptr_t) clean->host - ((uintptr_t) w + at + 4));
                memcpy(w + at, &call, 4);
                at += 4;
                memcpy(w + at, extend[kind], 3);
                at += 3;
                memcpy(w + at, tail, sizeof(tail));
                to = w;
            }
            uint8_t jmp[5] = {0xe9}; /* jmp clean */
            int32_t rel = (int32_t) ((uintptr_t) to - ((uintptr_t) n->host + 5));
            memcpy(jmp + 1, &rel, 4);
            if (native_os_patch((void *) n->host, jmp, 5) != 0) {
                return -1;
            }
        }
    }
    return 0;
}

static void parse_frames(const char *list)
{
    for (const char *p = list; p && *p;) {
        char *end;
        unsigned long v = strtoul(p, &end, 10);
        if (end == p) {
            break;
        }
        hash_frames = realloc(hash_frames, sizeof(uint32_t) * (size_t) (hash_frame_count + 1));
        hash_frames[hash_frame_count++] = (uint32_t) v;
        p = *end == ',' ? end + 1 : end;
    }
}

void native_start(void (*loop)(void))
{
    if (running) {
        flows[0].fiber = native_os_fiber_create(loop);
        if (flows[0].fiber == NULL) {
            fprintf(stderr, "native: cannot make a host stack\n");
            exit(2);
        }
        native_os_fiber_switch(flows[0].fiber);
    }
    loop();
}

int native_reserve(void)
{
    native_os_report_crashes();
    if (getenv("RUN_NATIVE") == NULL || atoi(getenv("RUN_NATIVE")) == 0) {
        return 0;
    }
    /* The DS's address ranges outside its memory (between the regions, the hardware, the GBA
       slot) must never become host memory: a Native access there has to fault, and a host
       pointer handed to the interpreter must not look like a DS address. The hardware's
       range must be free entirely; elsewhere a piece the host already uses is reported by
       the interpreter's accesses (native_fault_is_ds) and harmless otherwise. */
    native_os_reserve(0x01000000u, 0x00ff0000u);
    native_os_reserve(0x02400000u, 0x003e0000u);
    native_os_reserve(0x02800000u, 0x01800000u);
    if (native_os_reserve(0x04000000u, 0x06000000u) != 0) {
        fprintf(stderr, "native: the host already uses memory at the DS's hardware addresses\n");
        return -1;
    }
    native_os_reserve(0x0a000000u, 0x06000000u);
    return 0;
}

int native_init(ArmCpu *c, const char *manifest)
{
    cpu = c;
    const char *policy = getenv("RUN_NATIVE_POLICY");
    const char *record = getenv("RUN_NATIVE_RECORD");
    const char *replay = getenv("RUN_NATIVE_REPLAY");
    const char *frames = getenv("RUN_RAM_HASH");
    dump_dir = getenv("RUN_RAM_DUMP");
    learn_path = getenv("RUN_NATIVE_LEARN");
    if (getenv("RUN_NATIVE_PEEK") != NULL) {
        sscanf(getenv("RUN_NATIVE_PEEK"), "%x,%llu,%x,%x", &peek_stream, &peek_crossing, &peek_address, &peek_length);
    }
    if (getenv("RUN_NATIVE_DRIFT_FRAME") != NULL) {
        drift_from_frame = (uint32_t) strtoul(getenv("RUN_NATIVE_DRIFT_FRAME"), NULL, 10);
    }
    if (getenv("RUN_NATIVE_WATCH") != NULL) {
        watch_address = (uint32_t) strtoul(getenv("RUN_NATIVE_WATCH"), NULL, 16);
    }
    if (getenv("RUN_NATIVE_DEBUG") != NULL) {
        sscanf(getenv("RUN_NATIVE_DEBUG"), "%x,%d,%llu", &debug_stream, &debug_left, &debug_from);
    }
    running = getenv("RUN_NATIVE") != NULL && atoi(getenv("RUN_NATIVE")) != 0;
    parse_frames(frames);
    if (policy == NULL || *policy == 0) {
        return hash_frame_count ? 1 : 0;
    }
    if (load_manifest(manifest) != 0 || load_policy(policy) != 0) {
        fprintf(stderr, "native: cannot read %s or %s\n", manifest, policy);
        return -1;
    }
    /* the Native functions of the policy's functions, by DS address and module */
    uint32_t body_count = native_body_count + clean_body_count;
    by_host = malloc(sizeof(*by_host) * (native_function_count + clean_function_count + body_count + 1));
    guest_functions = calloc(native_function_count + clean_function_count, sizeof(*guest_functions));
    for (uint32_t i = 0; i < native_function_count + clean_function_count; i++) {
        /* a Clean function comes after its Native one and takes its place */
        const NativeFunction *n =
            i < native_function_count ? &native_functions[i] : &clean_functions[i - native_function_count];
        int m = module_index(native_module(n));
        Fn *f = first_at(n->address);
        for (; f && f < fns + fn_count && (f->address & ~1u) == (n->address & ~1u); f++) {
            if (f->module == m) {
                if (!(n->info & CLEAN_STANDBY)) {
                    f->native = n;
                }
                guest_functions[i] = f;
            }
        }
        by_host[by_host_count++] = n;
    }
    /* the bodies: the code a fault or a return address is in belongs to the wrapper's function */
    body_entries = calloc(body_count + 1, sizeof(*body_entries));
    uint32_t tables = by_host_count;
    qsort(by_host, tables, sizeof(*by_host), host_compare);
    for (uint32_t b = 0; b < body_count; b++) {
        const NativeBody *body = b < native_body_count ? &native_bodies[b] : &clean_bodies[b - native_body_count];
        uint32_t lo = 0, hi = tables;
        while (lo < hi) {
            uint32_t mid = (lo + hi) / 2;
            if ((uintptr_t) by_host[mid]->host < (uintptr_t) body->wrapper) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        if (lo == tables || by_host[lo]->host != body->wrapper) {
            fprintf(stderr, "native: missing wrapper for body %u\n", b);
            return -1;
        }
        body_entries[b] = *by_host[lo];
        body_entries[b].host = body->body;
        by_host[by_host_count++] = &body_entries[b];
    }
    qsort(by_host, by_host_count, sizeof(*by_host), host_compare);
    if (record != NULL && *record) {
        record_out = fopen(record, "wb");
        if (record_out == NULL) {
            return -1;
        }
        setvbuf(record_out, NULL, _IOFBF, 1 << 20);
        recording = 1;
        running = 0;
        c->observe_word_store = record_publication;
    }
    if (running) {
        if (replay != NULL && *replay) {
            if (load_replay(replay) != 0) {
                fprintf(stderr, "native: cannot read the trace %s\n", replay);
                return -1;
            }
            replaying = 1;
        }
        if (native_os_init() != 0 || patch_kept() != 0 || patch_clean() != 0) {
            fprintf(stderr, "native: cannot set up the fault handler or the patches\n");
            return -1;
        }
        flow_count = 1;
        const char *trace = getenv("RUN_NATIVE_CALL_TRACE");
        while (trace != NULL && *trace != 0 && guest_trace_count < 16) {
            char *end;
            uint32_t target = (uint32_t) strtoul(trace, &end, 16);
            if (end == trace || (*end != 0 && *end != ',')) {
                fprintf(stderr, "native: invalid RUN_NATIVE_CALL_TRACE address list\n");
                return -1;
            }
            guest_trace_targets[guest_trace_count++] = target & ~1u;
            trace = *end == ',' ? end + 1 : end;
        }
        native_guest_return_hook = guest_return;
        native_guest_slot_hook = guest_stack_slot;
        native_guest_enter_hook = guest_enter;
        native_publish_hook = publish_word;
        io_unmapped = host_access;
        if (native_os_watchdog(10, making_progress, stuck_in) != 0) {
            fprintf(stderr, "native: cannot start the watchdog\n");
            return -1;
        }
    }
    return 1;
}

void native_report(FILE *out)
{
    if (record_out != NULL) {
        fflush(record_out);
        fprintf(out, "native: recorded %u crossings for a Native run\n", record_count);
        return;
    }
    if (!running) {
        return;
    }
    int ran = 0, by_interp = 0, kept = 0, have = 0, clean = 0, clean_ran = 0;
    for (int i = 0; i < fn_count; i++) {
        Fn *f = &fns[i];
        clean += is_clean(f);
        clean_ran += is_clean(f) && f->calls_in != 0;
        have += f->native != NULL;
        kept += f->native != NULL && !native_for_native(f);
        ran += f->calls_in != 0;
        by_interp += f->calls_out != 0;
    }
    fprintf(out,
            "native: %d functions with a Native, %d kept Reference; %d entered Native from the interpreter; "
            "calls Reference->Native %llu, Native->Reference %llu (%d functions), through a pointer to Native "
            "%llu, from the interpreter to PC code %llu; deepest nesting %d; %llu thread moves on %llu fibers; %llu "
            "interpreted accesses to PC memory\n",
            have, kept, ran, (unsigned long long) calls_in, (unsigned long long) calls_out, by_interp,
            (unsigned long long) calls_pointer, (unsigned long long) calls_host, depth_max, (unsigned long long) thread_moves,
            (unsigned long long) fibers_made + 1, (unsigned long long) host_accesses);
    if (clean_function_count != 0) {
        fprintf(out, "native: %d Clean functions in place of their Native ones, %d entered from the interpreter\n", clean,
                clean_ran);
    }
    fprintf(out, "native: %llu audited buffer publications\n", (unsigned long long) publications);
    if (replaying) {
        uint32_t left = 0;
        for (int i = 0; i < stream_count; i++) {
            for (uint32_t r = streams[i].next; r; r = records[r - 1].next) {
                left++;
            }
        }
        fprintf(out,
                "native: followed %llu of %u Reference crossings (%u left)%s; %llu with other values; %llu calls "
                "entered off the Reference's step (by at most %llu; %llu late steps taken back)\n",
                (unsigned long long) replay_events, record_count, left,
                record_ended ? ", to its end"
                : diverged   ? ", DIVERGED"
                             : "",
                (unsigned long long) value_differences, (unsigned long long) drift_events, (unsigned long long) drift_max,
                (unsigned long long) drift_rewound);
    }
}
