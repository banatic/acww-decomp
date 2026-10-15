/* Native against Reference: every function that calls nothing, run from random entry states
 * as the ROM's code (interpreted) and as its matching source compiled for the PC.
 *
 *     nativecheck <manifest> <differences file> [cases] [address...]
 *
 * For each function and each state: the arguments are small numbers, random words or pointers
 * into a block of random bytes; the Reference runs first, and a state it cannot finish (a fault
 * on a random pointer, a software interrupt) is skipped. A function that branches out of
 * itself calls something and is left to later checks. The return value (as wide as the source
 * declares it) and every byte written outside the stack must agree.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm.h"
#include "diffcheck.h"
#include "host.h"
#include "loader.h"
#include "memory.h"
#include "native_params.h"
#include "native_table.h"

#define STACK_TOP 0x027e3f00u
#define STACK_SIZE 0x1000u
#define MAX_STEPS 2000000u
#define MAX_WRITES 64
#define RANDOM_BYTES 0x1000u
#define MAX_ARGS 16

typedef struct Effects {
    uint64_t ret;
    int count;
    int overflow;
    struct {
        uint32_t address;
        uint32_t size;
        uint8_t bytes[16];
    } writes[MAX_WRITES];
} Effects;

static void record_write(void *user, uint32_t address, const uint8_t *was, const uint8_t *now, size_t size)
{
    (void) was;
    Effects *e = user;
    while (size > 0) {
        if (e->count == MAX_WRITES) {
            e->overflow = 1;
            return;
        }
        uint32_t n = size < 16 ? (uint32_t) size : 16;
        e->writes[e->count].address = address;
        e->writes[e->count].size = n;
        memcpy(e->writes[e->count].bytes, now, n);
        e->count++;
        address += n;
        now += n;
        size -= n;
    }
}

/* Drops the writes into the function's own static data (see NativePrivate). */
static void drop_private(Effects *e, uint32_t function)
{
    int kept = 0;
    for (int i = 0; i < e->count; i++) {
        int private = 0;
        for (uint32_t k = 0; k < native_private_count; k++) {
            const NativePrivate *p = &native_private[k];
            private |= p->function == function && e->writes[i].address >= p->start && e->writes[i].address < p->end;
        }
        if (!private) {
            e->writes[kept++] = e->writes[i];
        }
    }
    e->count = kept;
}

static int same_writes(const Effects *a, const Effects *b)
{
    if (a->count != b->count || a->overflow != b->overflow) {
        return 0;
    }
    for (int i = 0; i < a->count; i++) {
        if (a->writes[i].address != b->writes[i].address || a->writes[i].size != b->writes[i].size ||
            memcmp(a->writes[i].bytes, b->writes[i].bytes, a->writes[i].size) != 0) {
            return 0;
        }
    }
    return 1;
}

/* The returned value as the source's type sees it. */
static uint64_t narrow(int kind, uint64_t value)
{
    switch (kind) {
        case NATIVE_RET_U8:
            return (uint8_t) value;
        case NATIVE_RET_S8:
            return (uint32_t) (int32_t) (int8_t) value;
        case NATIVE_RET_U16:
            return (uint16_t) value;
        case NATIVE_RET_S16:
            return (uint32_t) (int32_t) (int16_t) value;
        case NATIVE_RET_32:
            return (uint32_t) value;
        case NATIVE_RET_64:
            return value;
        default:
            return 0;
    }
}

typedef struct Watch {
    uint32_t lo, hi;
} Watch;

static int stop(ArmCpu *cpu, void *user)
{
    (void) cpu;
    (void) user;
    return 1;
}

static ArmHook watch_calls(void *user, uint32_t address, void **hook_user)
{
    Watch *w = user;
    address &= ~1u;
    *hook_user = w;
    return address >= w->lo && address < w->hi ? NULL : stop;
}

static uint32_t random_arg(DiffRng *rng)
{
    switch (diff_rand(rng) % 5) {
        case 0:
        case 1:
            return DIFF_SCRATCH + (diff_rand(rng) % (RANDOM_BYTES / 2) & ~3u);
        case 2:
            return diff_rand(rng) % 16;
        case 3:
            return (uint32_t) diff_range(rng, -1, 255);
        default:
            return diff_rand(rng);
    }
}

/* The parameters' kinds of the function at `address` in `module`, or NULL (native_param_kinds
 * is sorted by address). */
static const NativeParams *params_of(uint32_t address, const char *module)
{
    uint32_t lo = 0, hi = native_param_kinds_count;
    while (lo < hi) {
        uint32_t mid = (lo + hi) / 2;
        if (native_param_kinds[mid].address < address) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    for (; lo < native_param_kinds_count && native_param_kinds[lo].address == address; lo++) {
        if (strcmp(native_param_kinds[lo].module, module) == 0) {
            return &native_param_kinds[lo];
        }
    }
    return NULL;
}

/* A value of the parameter's kind: as mwccarm's callers pass it, widened to 32 bits. */
static uint32_t typed_arg(DiffRng *rng, int kind)
{
    switch (kind) {
        case PARAM_U8:
            return diff_rand(rng) & 0xff;
        case PARAM_S8:
            return (uint32_t) (int32_t) (int8_t) diff_rand(rng);
        case PARAM_U16:
            return diff_rand(rng) & 0xffff;
        case PARAM_S16:
            return (uint32_t) (int32_t) (int16_t) diff_rand(rng);
        case PARAM_POINTER:
            return DIFF_SCRATCH + (diff_rand(rng) % (RANDOM_BYTES / 2) & ~3u);
        default:
            return random_arg(rng);
    }
}

static int is_known(uint32_t address)
{
    for (uint32_t i = 0; i < native_known_count; i++) {
        if (native_known[i] == address) {
            return 1;
        }
    }
    return 0;
}

enum Outcome { SAME, DIFFERENT, CALLS, NO_STATE, KNOWN };

static enum Outcome check(const NativeFunction *f, int cases, const MemorySnapshot *loaded, FILE *log)
{
    DiffRng rng = {0x2545f491u ^ f->address};
    /* Always sixteen words: a structure or 64-bit value passed by value takes several, laid
     * out the same way in r0-r3 and on the DS stack as on the PC's stack, and host_invoke
     * puts the stack pointer back however many the callee expected. */
    int nargs = MAX_ARGS;
    int ran = 0;
    for (int n = 0; n < cases; n++) {
        memory_restore(loaded);
        uint8_t *scratch = memory_host(DIFF_SCRATCH, RANDOM_BYTES);
        for (uint32_t i = 0; i < RANDOM_BYTES; i += 4) {
            uint32_t v = diff_rand(&rng);
            memcpy(scratch + i, &v, 4);
        }
        uint32_t args[MAX_ARGS];
        for (int i = 0; i < MAX_ARGS; i++) {
            args[i] = random_arg(&rng);
        }
        const NativeParams *kinds = params_of(f->address & ~1u, native_module(f));
        if (kinds && !(kinds->kinds >> 31)) {
            for (uint32_t i = 0; i < kinds->count && i < MAX_ARGS; i++) {
                args[i] = typed_arg(&rng, (int) ((kinds->kinds >> (3 * i)) & 7));
            }
        }
        /* arguments past the fourth are on the stack */
        uint32_t sp = STACK_TOP - 4 * MAX_ARGS;
        memcpy(memory_host(sp, 4 * (MAX_ARGS - 4)), args + 4, 4 * (MAX_ARGS - 4));
        MemorySnapshot *entry = memory_snapshot();

        ArmCpu cpu;
        arm_init(&cpu);
        memcpy(cpu.r, args, 16);
        cpu.r[13] = sp;
        Watch watch = {f->address & ~1u, (f->address & ~1u) + f->size};
        cpu.hook_at = watch_calls;
        cpu.hook_user = &watch;
        enum ArmStop why = arm_call(&cpu, f->address, MAX_STEPS);
        if (why == ARM_HOOK_STOP) {
            memory_snapshot_free(entry);
            return CALLS;
        }
        if (why != ARM_RETURNED) {
            memory_snapshot_free(entry);
            continue;
        }
        Effects ref = {0};
        ref.ret = narrow(native_return(f), ((uint64_t) cpu.r[1] << 32) | cpu.r[0]);
        memory_diff(entry, STACK_TOP - STACK_SIZE, STACK_TOP, record_write, &ref);

        memory_restore(entry);
        Effects nat = {0};
        uint64_t value = 0;
        uint32_t fault = 0;
        int crashed = host_guarded_invoke(f->host, args, nargs, native_member(f), &value, &fault);
        nat.ret = narrow(native_return(f), value);
        memory_diff(entry, STACK_TOP - STACK_SIZE, STACK_TOP, record_write, &nat);
        memory_snapshot_free(entry);
        ran++;
        drop_private(&ref, f->address & ~1u);
        drop_private(&nat, f->address & ~1u);
        if (crashed || nat.ret != ref.ret || !same_writes(&ref, &nat)) {
            fprintf(log, "%08x %s case %d: args", f->address & ~1u, native_module(f), n);
            for (int i = 0; i < nargs; i++) {
                fprintf(log, " %08x", args[i]);
            }
            if (crashed) {
                fprintf(log, "; native faulted at %08x\n", fault);
            } else {
                fprintf(log, "; returns %llx / %llx, writes %d / %d\n", (unsigned long long) ref.ret,
                        (unsigned long long) nat.ret, ref.count, nat.count);
            }
            return DIFFERENT;
        }
    }
    return ran ? SAME : NO_STATE;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: nativecheck <manifest> [cases] [address...]\n");
        return 2;
    }
    int cases = argc > 3 ? atoi(argv[3]) : 16;
    if (memory_init() != 0 || loader_init(argv[1]) != 0) {
        fprintf(stderr, "cannot set up the DS's memory\n");
        return 2;
    }
    FILE *log = fopen(argv[2], "w");
    if (log == NULL) {
        log = stdout;
    }
    int counts[5] = {0, 0, 0, 0, 0};
    int skipped_returns = 0;
    for (uint32_t m = 0; m < native_module_count; m++) {
        int any = 0;
        MemorySnapshot *loaded = NULL;
        for (uint32_t i = 0; i < native_function_count; i++) {
            const NativeFunction *f = &native_functions[i];
            if ((f->info >> 16) != m) {
                continue;
            }
            if (argc > 4) {
                int wanted = 0;
                for (int k = 4; k < argc; k++) {
                    wanted |= (strtoul(argv[k], NULL, 16) & ~1u) == (f->address & ~1u);
                }
                if (!wanted) {
                    continue;
                }
            }
            if (native_return(f) == NATIVE_RET_SKIP) {
                skipped_returns++;
                continue;
            }
            if (!any) {
                if (loader_load(native_module_names[m]) != 0) {
                    break;
                }
                loaded = memory_snapshot();
                any = 1;
            }
            enum Outcome outcome = check(f, cases, loaded, log);
            if (outcome == DIFFERENT && is_known(f->address & ~1u)) {
                outcome = KNOWN;
            }
            counts[outcome]++;
        }
        if (loaded) {
            memory_restore(loaded);
            memory_snapshot_free(loaded);
        }
    }
    if (log != stdout) {
        fclose(log);
    }
    printf("functions that call nothing: %d agree, %d differ (%s), %d without a "
           "state the reference finishes\n",
           counts[SAME], counts[DIFFERENT], argv[2], counts[NO_STATE]);
    printf("explained in tests/native/known.txt: %d\n", counts[KNOWN]);
    printf("not checked here: %d call other functions, %d return a float or a structure\n", counts[CALLS], skipped_returns);
    return counts[DIFFERENT] ? 1 : 0;
}
