/* Exercise the production run loop, including a return at a slice boundary. */
#define main publication_game_main
#define io_advance publication_io_advance
#define io_frame publication_io_frame
#define arm7_step publication_arm7_step
#include "../../runtime/run.c"
#undef main

static unsigned advances, old_selector_seen, irq_requested;
static int request_irq;

void publication_io_advance(uint32_t cycles)
{
    (void) cycles;
    advances++;
    old_selector_seen += *(uint32_t *) (uintptr_t) 0x021f6f70u == 0;
    if (request_irq) {
        cpu.irq_line = 1;
        request_irq = 0;
        irq_requested++;
    }
}

uint32_t publication_io_frame(void) { return 0; }
void publication_arm7_step(void) { }

ArmCpu *publication_cpu(void) { return &cpu; }

void publication_reset_clock(uint64_t now, uint64_t end, int irq)
{
    arm_init(&cpu);
    cpu.steps = now;
    slice_end = end;
    accounted = now;
    max_steps = UINT64_MAX;
    max_frames = 0;
    halted = 0;
    advances = old_selector_seen = irq_requested = 0;
    request_irq = irq;
}

unsigned publication_advances(void) { return advances; }
unsigned publication_old_seen(void) { return old_selector_seen; }
unsigned publication_irq_requested(void) { return irq_requested; }

int publication_nested_return(int old_boundary)
{
    publication_reset_clock(511, 512, 0);
    cpu.cpsr |= ARM_CPSR_T;
    cpu.r[15] = MEM_MAIN_BASE;
    cpu.r[14] = ARM_RETURN_ADDRESS;
    *(uint16_t *) (uintptr_t) MEM_MAIN_BASE = 0x4770; /* bx lr */
    *(uint32_t *) (uintptr_t) 0x021f6f70u = 0;
    run_until_return();
    if (cpu.steps != 512 || slice_end != 512 || accounted != 511 || advances != 0) {
        return 2;
    }
    if (old_boundary) {
        *(uint32_t *) (uintptr_t) 0x021f6f70u = 1;
    }
    run_native_store_boundary();
    if (advances != 1 || old_selector_seen != 1 || slice_end != 0 || accounted != 512) {
        return 2;
    }
    run_native_store_boundary();
    return advances == 1 ? 0 : 2;
}
