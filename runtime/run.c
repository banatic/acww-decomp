/* Boots the game's ARM9 code in the interpreter and reports how far it gets; built and run
 * by tools/run.py.
 *
 *     run <rom.nds> <modules.txt> <symbols.txt> [max_instructions] [max_frames]
 *
 * The CPU runs in slices; between slices the clock advances and the ARM7 model answers. An
 * interrupt request raises the CPU's line (io.c) and the CPU takes it before its next
 * instruction. A stop is an unsupported instruction or BIOS call, a bad address, a CPU that
 * halts with nothing to wake it, a busy-wait loop (the same register state again and again
 * with no interrupt taken), or the instruction or frame budget.
 *
 * RUN_TRACE (card, pxi, irq), RUN_CALLS (function names) and RUN_BRANCHES (a count) in the
 * environment add traces to stderr and size the final branch list; see tools/run.py. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm.h"
#include "arm7.h"
#include "bios.h"
#include "boot.h"
#include "frame.h"
#include "gpu2d.h"
#include "input.h"
#include "io.h"
#include "memory.h"
#include "native_run.h"
#include "render.h"

#define SLICE 512
#define DMA_SLICE 32 /* while a DMA waits to run: its completion and interrupt come soon */
#define RING 4096
#define STUCK_WINDOW_SLICES 8192 /* about 4 million instructions */
#define STUCK_SLOTS 16384
#define STUCK_REPEATS 256
#define HALT_LIMIT_FRAMES 20

#define SDK_AUTOLOAD_DONE 0x02000a58u           /* _start_AutoloadDoneCallback: the images are in place */
#define SDK_OSI_THREAD_INFO_CURRENT 0x02204270u /* OSi_ThreadInfo.current: the running thread */

/* Symbols ---------------------------------------------------------------------------------- */

typedef struct Symbol {
    uint32_t address, size;
    char *name;
} Symbol;
static Symbol *symbols;
static int symbol_count, symbol_capacity;
static uint64_t *symbol_hits; /* branch targets per symbol: where the time goes */
static void symbol_blocks_build(void);

/* RUN_CALLS: a comma-separated list of function names whose calls are printed with their
 * first four arguments and the frame, to follow a flow (scene requests, overlay loads). */
#define TRACED_MAX 32
static uint32_t traced[TRACED_MAX];
static int traced_count;

static int compare_symbol(const void *a, const void *b)
{
    const Symbol *x = a, *y = b;
    return x->address < y->address ? -1 : x->address > y->address ? 1 : 0;
}

static void load_symbols(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        return;
    }
    char line[512], name[256];
    unsigned address, size;
    while (fgets(line, sizeof(line), f) != NULL) {
        if (sscanf(line, "%x %x %255s", &address, &size, name) != 3) {
            continue;
        }
        if (symbol_count == symbol_capacity) {
            symbol_capacity = symbol_capacity ? symbol_capacity * 2 : 1024;
            symbols = realloc(symbols, (size_t) symbol_capacity * sizeof(Symbol));
        }
        symbols[symbol_count].address = address;
        symbols[symbol_count].size = size;
        symbols[symbol_count].name = strdup(name);
        symbol_count++;
    }
    fclose(f);
    qsort(symbols, (size_t) symbol_count, sizeof(Symbol), compare_symbol);
    symbol_hits = calloc((size_t) symbol_count + 1, sizeof(uint64_t));
    symbol_blocks_build();
    const char *calls = getenv("RUN_CALLS");
    if (calls != NULL) {
        char *copy = strdup(calls);
        for (char *tok = strtok(copy, ","); tok != NULL && traced_count < TRACED_MAX; tok = strtok(NULL, ",")) {
            for (int i = 0; i < symbol_count; i++) {
                if (strcmp(symbols[i].name, tok) == 0) {
                    traced[traced_count++] = symbols[i].address;
                    break;
                }
            }
        }
        free(copy);
        fprintf(stderr, "run: tracing calls of %d functions\n", traced_count);
    }
}

static const char *symbolize(uint32_t address);

static int hook_trace_call(ArmCpu *c, void *user)
{
    (void) user;
    fprintf(stderr, "call: frame %u step %llu %s(%08x, %08x, %08x, %08x) from %s\n", io_frame(), (unsigned long long) c->steps,
            symbolize(c->r[15]), c->r[0], c->r[1], c->r[2], c->r[3], symbolize(c->r[14] & ~1u));
    return 0;
}

/* For every 64-byte block from the first symbol to the last: the last symbol starting at or
 * before the block (-1 for none). hook_at looks a symbol up at every branch, so the lookup
 * starts there and steps forward over the few symbols inside the block. */
#define SYMBOL_BLOCK_SHIFT 6
static int *symbol_block;
static uint32_t symbol_block_base, symbol_block_count;

static int symbol_index_search(uint32_t address);

static void symbol_blocks_build(void)
{
    if (symbol_count == 0) {
        return;
    }
    symbol_block_base = symbols[0].address & ~((1u << SYMBOL_BLOCK_SHIFT) - 1);
    symbol_block_count = ((symbols[symbol_count - 1].address - symbol_block_base) >> SYMBOL_BLOCK_SHIFT) + 1;
    symbol_block = malloc(symbol_block_count * sizeof(int));
    for (uint32_t b = 0; b < symbol_block_count; b++) {
        symbol_block[b] = symbol_index_search(symbol_block_base + (b << SYMBOL_BLOCK_SHIFT));
    }
}

/* The index of the symbol containing `address`, or -1: the last one starting at or before it. */
static int symbol_index(uint32_t address)
{
    uint32_t b = (address - symbol_block_base) >> SYMBOL_BLOCK_SHIFT;
    if (symbol_block == NULL || address < symbol_block_base || b >= symbol_block_count) {
        return symbol_index_search(address);
    }
    int i = symbol_block[b];
    while (i + 1 < symbol_count && symbols[i + 1].address <= address) {
        i++;
    }
    return i;
}

static int symbol_index_search(uint32_t address)
{
    int lo = 0, hi = symbol_count - 1, best = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (symbols[mid].address <= address) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return best;
}

/* The symbol containing `address`, as "name+offset". */
static const char *symbolize(uint32_t address)
{
    static char bufs[4][320];
    static int which;
    char *buf = bufs[which++ & 3]; /* a few results stay valid at once, for one printf */
    int lo = 0, hi = symbol_count - 1, best = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (symbols[mid].address <= address) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (address >= 0xfff00000u) {
        snprintf(buf, 320, "(boot)");
        return buf;
    }
    if (best < 0) {
        snprintf(buf, 320, "%08x", address);
        return buf;
    }
    uint32_t off = address - symbols[best].address;
    if (symbols[best].size != 0 && off >= symbols[best].size && off >= 0x1000) {
        snprintf(buf, 320, "%08x (%s+%#x?)", address, symbols[best].name, off);
    } else if (off == 0) {
        snprintf(buf, 320, "%s", symbols[best].name);
    } else {
        snprintf(buf, 320, "%s+%#x", symbols[best].name, off);
    }
    return buf;
}

/* The branch target ring --------------------------------------------------------------------- */

static uint32_t ring[RING];
static uint64_t ring_count;
static ArmCpu cpu;
static const char *manifest_path;
static int verified = -1;

/* Thread switches, for the report: the SDK changes OSi_ThreadInfo.current a few instructions
 * before it branches into the new thread, so a look at every branch target sees every change.
 * The ones seen in IRQ mode are OS_IrqHandler_ThreadSwitch's; the rest are the scheduler's
 * (OS_SaveContext / OS_LoadContext from OS_RescheduleThread). */
static uint32_t last_thread;
static uint64_t thread_switches, thread_switches_in_irq;

static ArmHook hook_at(void *user, uint32_t address, void **hook_user)
{
    ring[ring_count++ % RING] = address;
    int index = symbol_index(address);
    if (index >= 0) {
        symbol_hits[index]++;
    }
    uint32_t thread;
    memcpy(&thread, memory_host(SDK_OSI_THREAD_INFO_CURRENT, 4), 4);
    if (thread != last_thread) {
        if (last_thread != 0) {
            thread_switches++;
            if ((cpu.cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ) {
                thread_switches_in_irq++;
            }
        }
        uint32_t previous = last_thread;
        last_thread = thread;
        /* with Native functions, the run continues on the new thread's host stack */
        ArmHook move = native_thread_changed(previous, thread);
        if (move != NULL) {
            return move;
        }
    }
    for (int i = 0; i < traced_count; i++) {
        if (traced[i] == address) {
            return hook_trace_call;
        }
    }
    if (address == SDK_AUTOLOAD_DONE && verified < 0) {
        verified = boot_verify(manifest_path, stdout);
        native_resident_ready();
    }
    ArmHook native = native_hook_at(address, hook_user);
    if (native != NULL) {
        return native;
    }
    return bios_hook_at(user, address, hook_user);
}

/* Reports ---------------------------------------------------------------------------------- */

static const char *area_of(uint32_t address)
{
    if ((address >> 24) == 0x06) {
        return "VRAM";
    }
    if ((address >> 24) == 0x05) {
        return "palette";
    }
    if ((address >> 24) == 0x07) {
        return "OAM";
    }
    if (address >= 0x08000000u && address < 0x0b000000u) {
        return "GBA slot";
    }
    if (address == 0x04100000u) {
        return "IPC/PXI";
    }
    if (address == 0x04100010u) {
        return "card";
    }
    if (address >= 0xffff0000u) {
        return "BIOS";
    }
    uint32_t o = address - 0x04000000u;
    if (o < 0x60 || (o >= 0x1000 && o < 0x1070)) {
        return "display/2D";
    }
    if (o < 0x70) {
        return "display/3D control";
    }
    if (o >= 0xb0 && o < 0xf0) {
        return "DMA";
    }
    if (o >= 0x100 && o < 0x110) {
        return "timers";
    }
    if (o >= 0x130 && o < 0x134) {
        return "input";
    }
    if (o >= 0x180 && o < 0x18c) {
        return "IPC/PXI";
    }
    if (o >= 0x1a0 && o < 0x1c0) {
        return "card";
    }
    if (o == 0x204 || o == 0x247) {
        return "memory control";
    }
    if (o >= 0x208 && o < 0x218) {
        return "IRQ";
    }
    if (o >= 0x240 && o < 0x24a) {
        return "VRAM control";
    }
    if (o >= 0x280 && o < 0x2c0) {
        return "math";
    }
    if (o >= 0x300 && o < 0x308) {
        return "power";
    }
    if (o >= 0x320 && o < 0x6a4) {
        return "3D";
    }
    return "other";
}

static const char *const areas[] = {
    "display/2D", "display/3D control", "3D",           "DMA",  "timers",  "IRQ", "IPC/PXI",  "card", "math", "power",
    "input",      "memory control",     "VRAM control", "VRAM", "palette", "OAM", "GBA slot", "BIOS", "other"};

static void report_registers(void)
{
    int n = io_access_count();
    printf("\n== registers accessed (%d distinct address/size/direction entries) ==\n", n);
    for (size_t a = 0; a < sizeof(areas) / sizeof(areas[0]); a++) {
        int any = 0;
        for (int i = 0; i < n; i++) {
            const IoAccess *x = io_access(i);
            if (strcmp(area_of(x->address), areas[a]) != 0) {
                continue;
            }
            if (!any) {
                printf("-- %s\n", areas[a]);
                any = 1;
            }
            printf("  %08x %-18s %s%d %10llu  first at %s\n", x->address, io_register_name(x->address), x->write ? "w" : "r",
                   x->size * 8, (unsigned long long) x->count, symbolize(x->first_pc));
        }
    }
}

/* The functions branched to most: where the run spent its time. */
static void report_hot(int limit)
{
    printf("\n== most branched-to functions ==\n");
    for (int n = 0; n < limit; n++) {
        int best = -1;
        for (int i = 0; i < symbol_count; i++) {
            if (symbol_hits[i] && (best < 0 || symbol_hits[i] > symbol_hits[best])) {
                best = i;
            }
        }
        if (best < 0) {
            break;
        }
        printf("  %12llu  %s\n", (unsigned long long) symbol_hits[best], symbols[best].name);
        symbol_hits[best] = 0;
    }
}

static void report_display(void)
{
    printf("\n== display state ==\n");
    printf("DISPCNT %08x DISPSTAT %04x POWCNT1 %04x DISPCNT_B %08x MASTER_BRIGHT %04x/%04x\n", io_reg(0x04000000),
           io_reg(0x04000004) & 0xffff, io_reg(0x04000304) & 0xffff, io_reg(0x04001000), io_reg(0x0400006c) & 0xffff,
           io_reg(0x0400106c) & 0xffff);
    printf("VRAMCNT A-D %02x %02x %02x %02x E-G %02x %02x %02x H-I %02x %02x\n", io_reg(0x04000240) & 0xff,
           (io_reg(0x04000240) >> 8) & 0xff, (io_reg(0x04000240) >> 16) & 0xff, io_reg(0x04000240) >> 24,
           io_reg(0x04000244) & 0xff, (io_reg(0x04000244) >> 8) & 0xff, (io_reg(0x04000244) >> 16) & 0xff,
           io_reg(0x04000248) & 0xff, (io_reg(0x04000248) >> 8) & 0xff);
    printf("IRQ handlers (OS_IRQTable in DTCM):");
    for (uint32_t i = 0; i < 22; i++) {
        uint32_t h = 0;
        bus_read(0x027e0000u + 4 * i, 4, &h);
        if (h) {
            printf(" %u=%s", i, symbolize(h & ~1u));
        }
    }
    printf("\n");
    printf("BG0-3CNT A %04x %04x %04x %04x  B %04x %04x %04x %04x\n", io_reg(0x04000008) & 0xffff, io_reg(0x04000008) >> 16,
           io_reg(0x0400000c) & 0xffff, io_reg(0x0400000c) >> 16, io_reg(0x04001008) & 0xffff, io_reg(0x04001008) >> 16,
           io_reg(0x0400100c) & 0xffff, io_reg(0x0400100c) >> 16);
}

static void report_branches(int limit)
{
    printf("\n== last branch targets (newest last; x N = consecutive repeats) ==\n");
    uint64_t start = ring_count > (uint64_t) limit ? ring_count - (uint64_t) limit : 0;
    uint32_t last = 0;
    int repeat = 0;
    for (uint64_t i = start; i < ring_count; i++) {
        uint32_t t = ring[i % RING];
        if (i > start && t == last) {
            repeat++;
            continue;
        }
        if (i > start) {
            printf("  %08x %s%s", last, symbolize(last), repeat ? "" : "\n");
            if (repeat) {
                printf(" x %d\n", repeat + 1);
            }
        }
        last = t;
        repeat = 0;
    }
    if (ring_count > start) {
        printf("  %08x %s%s", last, symbolize(last), repeat ? "" : "\n");
        if (repeat) {
            printf(" x %d\n", repeat + 1);
        }
    }
}

static void report_cpu(const char *reason)
{
    printf("\n== stop: %s ==\n", reason);
    printf("instructions %llu, pc %08x %s (%s), cpsr %08x, lr %08x %s, sp %08x\n", (unsigned long long) cpu.steps, cpu.r[15],
           symbolize(cpu.r[15]), (cpu.cpsr & ARM_CPSR_T) ? "thumb" : "arm", cpu.cpsr, cpu.r[14], symbolize(cpu.r[14] & ~1u),
           cpu.r[13]);
    printf("r0-r3 %08x %08x %08x %08x  r4-r7 %08x %08x %08x %08x\n", cpu.r[0], cpu.r[1], cpu.r[2], cpu.r[3], cpu.r[4],
           cpu.r[5], cpu.r[6], cpu.r[7]);
    printf("r8-r12 %08x %08x %08x %08x %08x  fault %08x swi %06x\n", cpu.r[8], cpu.r[9], cpu.r[10], cpu.r[11], cpu.r[12],
           cpu.fault_address, cpu.swi);
    uint32_t frame = io_frame();
    printf("frame %u, %llu bus cycles\n", frame, (unsigned long long) io_cycles());
}

/* The run -------------------------------------------------------------------------------- */

static uint64_t max_steps;
static uint32_t max_frames;

/* The execution state shared by every level of the run: the top loop, the calls Native code
 * makes into the interpreter, and the loops at the base of each thread's host stack
 * (native_run.h). A slice is the stretch of instructions after which the clock advances. It
 * is global, not per call: a call from Native code continues the slice the interpreter was
 * in, so the clock advances at the same step counts as in a run without Native code. */
static uint64_t slice_end; /* the step count where the open slice ends; 0: none open */
static uint64_t accounted; /* steps already turned into bus time */
static int halted;
static uint64_t halt_slices;
static uint32_t state_hash[STUCK_SLOTS], state_count[STUCK_SLOTS];
static int window_slices;
static uint64_t irqs_at_window_start;
static char reason_buf[256];

/* Tells the Native side when a frame has begun (memory hashes are taken after one). */
static void frame_check(void)
{
    static uint32_t seen;
    if (io_frame() != seen) {
        seen = io_frame();
        native_frame_ended(seen);
    }
}

/* "Wait for interrupt": the CPU sleeps until IE & IF is nonzero, whatever IME and CPSR I say
 * (a masked request ends the wait too); until then time passes. */
static void wait_for_interrupt(void)
{
    while (halted) {
        if (max_frames && io_frame() >= max_frames) {
            run_finish("frame budget reached", 0);
        }
        if (io_reg(0x04000210) & io_reg(0x04000214)) {
            halted = 0;
            halt_slices = 0;
            return;
        }
        io_advance(IO_CYCLES_PER_LINE);
        arm7_step();
        frame_check();
        if (++halt_slices > (uint64_t) HALT_LIMIT_FRAMES * IO_LINES_PER_FRAME) {
            snprintf(reason_buf, sizeof(reason_buf),
                     "halted for %d frames with no interrupt (IME %x IE %08x IF %08x, cpsr I %d)", HALT_LIMIT_FRAMES,
                     io_reg(0x04000208), io_reg(0x04000210), io_reg(0x04000214), (cpu.cpsr >> 7) & 1);
            run_finish(reason_buf, 0);
        }
    }
}

/* Busy-wait detection: a loop that makes no progress reaches the same register state again
 * and again; count identical slice-end states over a window and stop when one recurs often
 * with no interrupt taken meanwhile. A long but honest loop (the crt0's decompressor) never
 * repeats a state. A slice spent stalled for Native code (native_run.h) repeats its state
 * too, and is not counted. */
static void check_stuck(uint64_t slice_start)
{
    if (cpu.stall_until[0] > slice_start || cpu.stall_until[1] > slice_start) {
        return;
    }
    uint32_t h = cpu.cpsr;
    for (int i = 0; i < 16; i++) {
        h = (h ^ cpu.r[i]) * 16777619u;
    }
    uint32_t slot = h % STUCK_SLOTS;
    for (int probe = 0; probe < 64; probe++) {
        uint32_t k = (slot + (uint32_t) probe) % STUCK_SLOTS;
        if (state_hash[k] == 0) {
            state_hash[k] = h | 1;
            state_count[k] = 1;
            break;
        }
        if (state_hash[k] == (h | 1)) {
            if (++state_count[k] >= STUCK_REPEATS && cpu.irq_taken == irqs_at_window_start) {
                snprintf(reason_buf, sizeof(reason_buf), "busy-wait loop at %08x (%s): the same state %d times", cpu.r[15],
                         symbolize(cpu.r[15]), STUCK_REPEATS);
                run_finish(reason_buf, 0);
            }
            break;
        }
    }
    if (++window_slices == STUCK_WINDOW_SLICES) {
        memset(state_hash, 0, sizeof(state_hash));
        window_slices = 0;
        irqs_at_window_start = cpu.irq_taken;
    }
}

static void finish_slice(void)
{
    slice_end = 0;
    if (cpu.steps > accounted) { /* not after run_rewind took back accounted steps */
        io_advance((uint32_t) (cpu.steps - accounted) * IO_CYCLES_PER_INSTRUCTION);
        accounted = cpu.steps;
    }
    arm7_step();
    frame_check();
}

/* A nested return can leave a completed slice pending. A new Native store
 * belongs after that slice's hardware effects, just as the next ARM store
 * would. An open partial slice must retain its original boundary. */
int run_native_store_boundary(void)
{
    if (accounted > cpu.steps) {
        return 0; /* hardware has already seen a later time; rewinding cannot undo it */
    }
    if (slice_end != 0 && cpu.steps >= slice_end) {
        finish_slice();
    }
    return 1;
}

/* Runs slices until the CPU branches to ARM_RETURN_ADDRESS, the end of a call Native code
 * made (returns), or, with `forever`, until the run ends (a branch there is then an error). */
static void execute(int forever)
{
    for (;;) {
        if (max_frames && io_frame() >= max_frames) {
            run_finish("frame budget reached", 0);
        }
        if (halted) {
            wait_for_interrupt();
            continue;
        }
        if (cpu.steps >= max_steps) {
            run_finish("instruction budget reached", 0);
        }
        if (slice_end == 0) {
            slice_end = cpu.steps + (io_dma_pending() ? DMA_SLICE : SLICE);
        }
        uint64_t slice_start = accounted;
        enum ArmStop stop = ARM_STEP_LIMIT;
        if (cpu.steps < slice_end) {
            stop = arm_run(&cpu, ARM_RETURN_ADDRESS, slice_end - cpu.steps);
            if (stop == ARM_STEP_LIMIT && cpu.steps < slice_end) {
                /* a run that was suspended in a hook while nested runs ended its slice stops
                   at that old slice's limit; the slice open now goes on */
                continue;
            }
            if (stop == ARM_RETURNED && !forever) {
                /* the end of a call from Native code, in the middle of a slice */
                return;
            }
        }
        /* else the slice ran out at the branch into Native code that now calls back: it ends
           here, before the next instruction, as it does between the two in the Reference */
        finish_slice();

        switch (stop) {
            case ARM_STEP_LIMIT:
                break;
            case ARM_SWI:
                if (bios_swi(&cpu) < 0) {
                    snprintf(reason_buf, sizeof(reason_buf), "unsupported SWI 0x%02x",
                             (cpu.cpsr & ARM_CPSR_T) ? cpu.swi & 0xff : (cpu.swi >> 16) & 0xff);
                    run_finish(reason_buf, 0);
                }
                break;
            case ARM_HALT:
                halted = 1;
                break;
            case ARM_HOOK_STOP:
                run_finish("a hook stopped the CPU", 0);
                break;
            case ARM_RETURNED:
                run_finish("branched to the return sentinel", 0);
                break;
            case ARM_UNDEFINED:
                run_finish("undefined instruction", 0);
                break;
            case ARM_BREAKPOINT:
                run_finish("breakpoint", 0);
                break;
            case ARM_BAD_ADDRESS:
                run_finish("access to an address nothing serves", 0);
                break;
        }
        check_stuck(slice_start);
    }
}

uint64_t run_rewind(uint64_t steps)
{
    /* The clock only advances at the end of a slice, by the steps since the last one; the
       slice ends at the same step count as before. Bus time already given for the steps
       taken back stays given (it may run ahead of the steps until the slice ends), and the
       slice's end puts both back in step with a run that never ran ahead. */
    if (cpu.steps <= steps) {
        return 0;
    }
    uint64_t back = cpu.steps - steps;
    cpu.steps = steps;
    return back;
}

void run_until_return(void)
{
    execute(0);
}

void run_forever(void)
{
    execute(1);
}

/* Ends the run from wherever it is (any thread's host stack, any depth of calls): the
 * report, then the process exits. */
void run_finish(const char *reason, int status)
{
    render_finish(); /* the frames still being drawn */
    report_cpu(reason);
    printf("interrupts taken %llu, thread switches %llu (%llu in interrupt handlers), modules verified: %s\n",
           (unsigned long long) cpu.irq_taken, (unsigned long long) thread_switches,
           (unsigned long long) thread_switches_in_irq,
           verified < 0    ? "not reached"
           : verified == 0 ? "all match"
                           : "MISMATCH");
    io_report(stdout);
    bios_report(&cpu, stdout);
    arm7_report(stdout);
    frame_report(stdout);
    render_report(stdout);
    report_display();
    report_registers();
    report_hot(40);
    report_branches(getenv("RUN_BRANCHES") ? atoi(getenv("RUN_BRANCHES")) : 300);
    native_report(stdout);
    fflush(stdout);
    exit(status);
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "usage: run <rom.nds> <modules.txt> <symbols.txt> [max_instructions] [max_frames]\n");
        return 2;
    }
    if (native_reserve() != 0) {
        return 1;
    }
    const char *rom = argv[1];
    manifest_path = argv[2];
    load_symbols(argv[3]);
    max_steps = argc > 4 ? strtoull(argv[4], NULL, 0) : 200000000ull;
    if (max_steps == 0) {
        max_steps = UINT64_MAX; /* no budget: frames or getting stuck end the run */
    }
    max_frames = argc > 5 ? (uint32_t) strtoul(argv[5], NULL, 0) : 0;

    if (memory_init() != 0) {
        fprintf(stderr, "cannot map the DS memory\n");
        return 1;
    }
    arm_init(&cpu);
    if (io_init(rom, &cpu) != 0) {
        fprintf(stderr, "cannot read %s\n", rom);
        return 1;
    }
    if (boot_init(rom, &cpu) != 0) {
        fprintf(stderr, "cannot load the ARM9 program from %s\n", rom);
        return 1;
    }
    bios_init(&cpu);
    /* the screens, the frame output (RUN_PNG, RUN_PNG_FRAMES, RUN_HASH) and the input
       recording (RUN_INPUT), before the ARM7 publishes its first button and touch state */
    gpu2d_init();
    frame_output_init();
    render_init();
    const char *recording = getenv("RUN_INPUT");
    if (recording != NULL && *recording && input_load(recording) != 0) {
        fprintf(stderr, "cannot read the input recording %s\n", recording);
        return 1;
    }
    arm7_init();
    cpu.io_read = bios_io_read;
    cpu.io_write = io_write;
    cpu.hook_at = hook_at;
    if (getenv("RUN_STEPS") != NULL) {
        /* RUN_STEPS=<from>,<count>: print those instructions as they execute */
        unsigned long long from = 0, count = 0;
        sscanf(getenv("RUN_STEPS"), "%llu,%llu", &from, &count);
        cpu.trace_from = from;
        cpu.trace_count = count;
    }
    printf("boot: entry %08x %s\n", boot_entry(), symbolize(boot_entry()));

    if (native_init(&cpu, manifest_path) < 0) {
        return 1;
    }
    native_start(run_forever);
    return 0;
}
