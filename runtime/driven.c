/* Driven calls (driven.h). */
#include "driven.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "native_run.h"

typedef struct DrivenCall {
    uint32_t frame;
    int through_vtable;
    uint32_t target; /* call: the function; vcall: the slot's byte offset */
    uint32_t r[4];
    uint8_t earlier[4];          /* nonzero: r[i] is the result of the call that many before */
    uint32_t guard, guard_value; /* call: the guard word; vcall: the object's vtable pointer */
} DrivenCall;

#define MOMENT_CALLS 256 /* the results kept for "rN" */

static int enabled = -1;
static DrivenCall *calls;
static int call_count, next_call;
static uint32_t arm_address, arm_value;
static int end_after; /* the run ends after the last calls' memory image */
static uint32_t results[MOMENT_CALLS];
static int results_count;

enum { IDLE, ARMED, CALLING };
static int state = IDLE;
static uint32_t armed_thread;
static uint32_t saved[16], saved_cpsr;
static uint32_t fire_frame;
static uint32_t current_target;

/* The branch targets the calls reached (on their thread, outside IRQ mode), for the report:
 * an open-addressed set, cleared at each arm point. */
#define SEEN_SLOTS 65536
static uint32_t seen[SEEN_SLOTS];
static int seen_count;

static void note_seen(uint32_t address)
{
    uint32_t key = address | 1u; /* 0 is an empty slot */
    uint32_t i = (key * 2654435761u) >> 16;
    for (int n = 0; n < SEEN_SLOTS; n++, i = (i + 1) & (SEEN_SLOTS - 1)) {
        if (seen[i] == key) {
            return;
        }
        if (seen[i] == 0) {
            if (seen_count < SEEN_SLOTS / 2) {
                seen[i] = key;
                seen_count++;
            }
            return;
        }
    }
}

static void bad_file(const char *path, int line, const char *why)
{
    fprintf(stderr, "driven: %s:%d: %s\n", path, line, why);
    exit(2);
}

static void load(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        bad_file(path, 0, "cannot be read");
    }
    char text[512];
    int line = 0, capacity = 0;
    while (fgets(text, sizeof(text), f) != NULL) {
        line++;
        char *hash = strchr(text, '#');
        if (hash != NULL) {
            *hash = 0;
        }
        char word[16];
        if (sscanf(text, "%15s", word) != 1) {
            continue;
        }
        if (strcmp(word, "arm") == 0) {
            if (sscanf(text, "%*s %x %x", &arm_address, &arm_value) != 2) {
                bad_file(path, line, "arm ADDRESS VALUE");
            }
            arm_address &= ~1u;
            continue;
        }
        if (strcmp(word, "end") == 0) {
            end_after = 1;
            continue;
        }
        DrivenCall c = {0};
        if (strcmp(word, "call") != 0 && strcmp(word, "vcall") != 0) {
            bad_file(path, line, "a line is arm, call, vcall or end");
        }
        c.through_vtable = word[0] == 'v';
        /* the fields in order: FRAME, then TARGET or VPTR SLOT, R0-R3, then GUARD_ADDRESS
           GUARD_VALUE or VTABLE */
        uint32_t field[9];
        int n = 0;
        char *rest = text + strspn(text, " \t") + strlen(word);
        for (char *tok = strtok(rest, " \t\r\n"); tok != NULL && n < 9; tok = strtok(NULL, " \t\r\n"), n++) {
            int reg = c.through_vtable ? n - 3 : n - 2;
            char *end = NULL;
            if (tok[0] == 'r' && reg >= 0 && reg < 4) {
                long back = strtol(tok + 1, &end, 10);
                if (*end != 0 || back < 1 || back > MOMENT_CALLS) {
                    bad_file(path, line, "rN names the result of the call N before (1 to 256)");
                }
                c.earlier[reg] = (uint8_t) back;
                field[n] = 0;
                continue;
            }
            field[n] = (uint32_t) strtoul(tok, &end, n == 0 ? 10 : 16);
            if (*end != 0) {
                bad_file(path, line, "a field is not a number");
            }
        }
        if (n != 8) {
            bad_file(path, line, "a call has eight fields");
        }
        c.frame = field[0];
        if (c.through_vtable) {
            c.guard = field[1];
            c.target = field[2];
            memcpy(c.r, &field[3], sizeof(c.r));
            c.guard_value = field[7];
        } else {
            c.target = field[1];
            memcpy(c.r, &field[2], sizeof(c.r));
            c.guard = field[6];
            c.guard_value = field[7];
        }
        if (call_count > 0 && c.frame < calls[call_count - 1].frame) {
            bad_file(path, line, "the calls are in frame order");
        }
        if (call_count == capacity) {
            capacity = capacity ? capacity * 2 : 64;
            calls = realloc(calls, (size_t) capacity * sizeof(DrivenCall));
        }
        calls[call_count++] = c;
    }
    fclose(f);
    if (arm_address == 0) {
        bad_file(path, line, "no arm line");
    }
    printf("driven: %d calls, armed at %08x with r0 %08x\n", call_count, arm_address, arm_value);
}

int driven_enabled(void)
{
    if (enabled < 0) {
        const char *path = getenv("RUN_DRIVEN");
        enabled = path != NULL && *path;
        if (enabled) {
            load(path);
        }
    }
    return enabled;
}

static uint32_t word_at(uint32_t address)
{
    uint32_t v = 0;
    bus_read(address, 4, &v);
    return v;
}

/* Starts calls[next_call] or the first one after it whose guard holds and that is due; returns
 * 0 when none is left for this moment. */
static int start_next(ArmCpu *cpu)
{
    while (next_call < call_count && calls[next_call].frame <= fire_frame) {
        const DrivenCall *c = &calls[next_call++];
        uint32_t target = c->target, held = word_at(c->guard), r[4];
        for (int i = 0; i < 4; i++) {
            r[i] = c->earlier[i] == 0 ? c->r[i] : c->earlier[i] <= results_count ? results[results_count - c->earlier[i]] : 0;
        }
        if (c->through_vtable) {
            if (held != c->guard_value) {
                printf("driven: frame %u skip vcall %08x+%x on %08x: the vtable pointer at %08x is %08x, not %08x\n",
                       fire_frame, c->guard_value, c->target, c->r[0], c->guard, held, c->guard_value);
                continue;
            }
            target = word_at(held + c->target);
        } else if (c->guard != 0 && held != c->guard_value) {
            printf("driven: frame %u skip call %08x on %08x: the word at %08x is %08x, not %08x\n", fire_frame, target,
                   c->r[0], c->guard, held, c->guard_value);
            continue;
        }
        printf("driven: frame %u call %08x(%08x, %08x, %08x, %08x) at step %llu\n", fire_frame, target, r[0], r[1], r[2], r[3],
               (unsigned long long) cpu->steps);
        fflush(stdout);
        current_target = target;
        memcpy(cpu->r, saved, sizeof(saved));
        cpu->cpsr = saved_cpsr;
        memcpy(cpu->r, r, sizeof(r));
        cpu->r[13] = saved[13] & ~7u;
        cpu->r[14] = DRIVEN_RETURN_ADDRESS;
        if (target & 1) {
            cpu->cpsr |= ARM_CPSR_T;
        } else {
            cpu->cpsr &= ~ARM_CPSR_T;
        }
        cpu->r[15] = target & ~1u;
        return 1;
    }
    return 0;
}

static void finish(ArmCpu *cpu)
{
    /* each target with its first 8 bytes, which tell an overlay's function from another's at
       the same address (tools/driven.py keeps the function entries) */
    for (int i = 0; i < SEEN_SLOTS; i++) {
        if (seen[i] != 0) {
            uint32_t a = seen[i] & ~1u;
            printf("driven: entered %08x %08x %08x\n", a, word_at(a), word_at(a + 4));
            seen[i] = 0;
        }
    }
    seen_count = 0;
    native_snapshot_now(DRIVEN_SNAPSHOT + fire_frame);
    memcpy(cpu->r, saved, sizeof(saved));
    cpu->cpsr = saved_cpsr;
    state = IDLE;
    printf("driven: frame %u back at %08x (frame %u now)\n", fire_frame, cpu->r[15], io_frame());
    fflush(stdout);
    if (end_after && next_call >= call_count) {
        run_finish("the driven calls are done", 0);
    }
}

static int fire(ArmCpu *cpu, void *user)
{
    (void) user;
    memcpy(saved, cpu->r, sizeof(saved));
    saved_cpsr = cpu->cpsr;
    fire_frame = io_frame();
    state = CALLING;
    results_count = 0;
    if (!start_next(cpu)) {
        finish(cpu); /* every call of the moment was skipped */
    }
    return 0;
}

int driven_returned(ArmCpu *cpu, void *user)
{
    (void) user;
    if (state != CALLING) {
        fprintf(stderr, "driven: a branch to the driven calls' return address outside one\n");
        exit(2);
    }
    printf("driven: frame %u returned from %08x: r0 %08x\n", fire_frame, current_target, cpu->r[0]);
    if (results_count < MOMENT_CALLS) {
        results[results_count++] = cpu->r[0];
    }
    if (!start_next(cpu)) {
        finish(cpu);
    }
    return 0;
}

ArmHook driven_hook_at(ArmCpu *cpu, uint32_t address, uint32_t thread)
{
    if (state == CALLING) {
        if ((cpu->cpsr & ARM_MODE_MASK) != ARM_MODE_IRQ && thread == armed_thread) {
            note_seen(address);
        }
        return NULL;
    }
    if (next_call >= call_count) {
        return NULL;
    }
    if (state == IDLE) {
        if (address == arm_address && (arm_value == 0 || cpu->r[0] == arm_value) && io_frame() >= calls[next_call].frame) {
            state = ARMED;
            armed_thread = thread;
        }
        return NULL;
    }
    /* armed: the first branch target after the entry that the interpreter reaches by itself,
       as at this moment of the Reference (a stall at the entry, the Native run's time for the
       code before it, is not that) */
    int mode = (cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
    if (address == arm_address || mode || thread != armed_thread ||
        (address == cpu->stall_pc[0] && (cpu->steps < cpu->stall_until[0] || cpu->stall_branch[0]))) {
        return NULL;
    }
    return fire;
}
