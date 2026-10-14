/* An ARMv5TE (ARM946E-S) interpreter for the ARM and Thumb instruction sets.
 *
 * Memory is the host's: an address the DS maps to RAM is a host pointer here (see memory.h),
 * so loads and stores go straight to it. Addresses outside RAM (I/O registers) go to the
 * io_read / io_write callbacks.
 *
 * The processor modes are real: each has its banked registers and SPSR, so the game's own
 * exception, context-switch and interrupt code runs as it does on the console. An interrupt
 * request arrives on irq_line and is taken between instructions as an exception.
 */
#ifndef RUNTIME_ARM_H
#define RUNTIME_ARM_H

#include <stdint.h>

enum ArmStop {
    ARM_RETURNED = 0, /* reached the return address given to arm_call */
    ARM_UNDEFINED,    /* an undefined or unsupported instruction at stop_pc */
    ARM_SWI,          /* a software interrupt: its immediate in swi (all 24 bits in ARM state, of
                         which the DS BIOS reads bits 23:16; 8 bits in Thumb), r15 after it */
    ARM_BREAKPOINT,   /* BKPT */
    ARM_STEP_LIMIT,   /* the instruction budget ran out */
    ARM_BAD_ADDRESS,  /* an access no memory or callback serves, at fault_address */
    ARM_HOOK_STOP,    /* a hook asked to stop */
    ARM_HALT          /* "wait for interrupt" (MCR p15, 0, Rd, c7, c0, 4): the CPU sleeps until
                         IE & IF is nonzero, whatever IME, CPSR I and F say; r15 is after it */
};

/* The exceptions arm_enter_exception takes, numbered by vector (ARM ARM A2.6). */
enum ArmException {
    ARM_EXC_RESET = 0,
    ARM_EXC_UNDEFINED,
    ARM_EXC_SWI,
    ARM_EXC_PREFETCH_ABORT,
    ARM_EXC_DATA_ABORT,
    ARM_EXC_IRQ = 6,
    ARM_EXC_FIQ
};

typedef struct ArmCpu ArmCpu;

/* Called before the instruction at a hooked address executes (bit 0 clear). Return nonzero to
 * stop with ARM_HOOK_STOP; a hook may change registers and pc to run something else instead,
 * for example a host implementation of the function that returns to lr. */
typedef int (*ArmHook)(ArmCpu *cpu, void *user);

struct ArmCpu {
    uint32_t r[16];   /* the current mode's registers; r[15] is the next instruction to execute */
    uint32_t cpsr;    /* N Z C V Q in bits 31..27, I F T in bits 7..5, mode in bits 4..0 */
    uint32_t spsr;    /* the current mode's SPSR (meaningless in user and system mode) */
    uint64_t steps;   /* instructions executed */
    uint32_t stop_pc; /* where execution stopped */
    uint32_t fault_address;
    uint32_t swi;

    /* The interrupt line: the platform sets it nonzero while an enabled request is pending
     * (IME, IE & IF on the DS) and clears it when none is. Checked before every instruction;
     * when CPSR I is clear the IRQ exception is taken there and then, and irq_taken counts
     * it. The line stays as the platform left it (level-sensitive, as nIRQ is). */
    uint32_t irq_line;
    uint64_t irq_taken;

    /* The registers of the modes other than the current one (ARM ARM A2.3). bank_usr holds
     * r8-r14 of user/system mode: r13 and r14 whenever another mode is current, r8-r12 only
     * while FIQ is. The others hold their mode's r13 and r14 (r8-r14 for FIQ) and SPSR. */
    uint32_t bank_usr[7];
    uint32_t bank_fiq[7], spsr_fiq;
    uint32_t bank_svc[2], spsr_svc;
    uint32_t bank_abt[2], spsr_abt;
    uint32_t bank_irq[2], spsr_irq;
    uint32_t bank_und[2], spsr_und;

    /* The CP15 register file (ARM946E-S TRM chapter 2), by CRn, CRm (0-7) and opcode2: what
     * MCR stores, MRC reads back. c0 is read-only identification; c7 (cache operations, wait
     * for interrupt) is not stored. */
    uint32_t cp15[16][8][8];

    /* I/O: called for addresses memory_host() does not map. size is 1, 2 or 4. Return 0 when
     * the address is not served either. */
    int (*io_read)(void *user, uint32_t address, int size, uint32_t *value);
    int (*io_write)(void *user, uint32_t address, int size, uint32_t value);
    void *io_user;

    /* Hooks, looked up by address on every branch target (not on every instruction). */
    ArmHook (*hook_at)(void *user, uint32_t address, void **hook_user);
    void *hook_user;
};

#define ARM_CPSR_N (1u << 31)
#define ARM_CPSR_Z (1u << 30)
#define ARM_CPSR_C (1u << 29)
#define ARM_CPSR_V (1u << 28)
#define ARM_CPSR_Q (1u << 27)
#define ARM_CPSR_I (1u << 7)
#define ARM_CPSR_F (1u << 6)
#define ARM_CPSR_T (1u << 5)
#define ARM_MODE_MASK 0x1fu
#define ARM_MODE_USER 0x10u
#define ARM_MODE_FIQ 0x11u
#define ARM_MODE_IRQ 0x12u
#define ARM_MODE_SVC 0x13u
#define ARM_MODE_ABORT 0x17u
#define ARM_MODE_UNDEFINED 0x1bu
#define ARM_MODE_SYSTEM 0x1fu

/* CP15 c1 control register: bit 13 (V) selects the high vectors (ARM946E-S TRM 2.3.3). The
 * reset value has bits 3-6 (which read as one) and V, since the DS ARM9 boots with its
 * vectors at 0xffff0000, where its BIOS is. */
#define ARM_CP15_CONTROL_HIGH_VECTORS (1u << 13)
#define ARM_CP15_CONTROL_RESET 0x00002078u
#define ARM_HIGH_VECTORS 0xffff0000u

/* The return address arm_call puts in lr. It sits past the end of the ARM9 BIOS, where no
 * game or SDK code lives, so a branch to it in either state can only be the function
 * returning. */
#define ARM_RETURN_ADDRESS 0xfffffff0u

/* A CPU in system mode with IRQ and FIQ enabled, all registers zero, CP15 at its reset
 * values, no callbacks. */
void arm_init(ArmCpu *cpu);

/* Writes the CPSR, switching the register banks and the SPSR when the mode changes. Direct
 * writes of cpu->cpsr are fine as long as they keep the mode bits. */
void arm_set_cpsr(ArmCpu *cpu, uint32_t cpsr);

/* A banked register of `mode`, read or written from any mode: r13 and r14 of the user, SVC,
 * abort, IRQ and undefined modes (`index` 13 or 14), r8-r14 of FIQ. System mode shares the
 * user registers. When `mode` is the current mode this is cpu->r. */
uint32_t arm_banked_get(const ArmCpu *cpu, uint32_t mode, int index);
void arm_banked_set(ArmCpu *cpu, uint32_t mode, int index, uint32_t value);

/* Takes an exception as the hardware does (ARM ARM A2.6): the new mode's SPSR gets the CPSR,
 * its r14 the return address, the CPSR switches to the mode in ARM state with I set (and F for
 * FIQ and reset), and r15 goes to the vector, at 0xffff0000 when CP15 control bit 13 (V) is
 * set, else 0. The return address comes from r15, which must hold:
 *   - IRQ, FIQ: the next instruction to execute (r14 = r15 + 4);
 *   - SWI: the instruction after the SWI, as it does after an ARM_SWI stop (r14 = r15);
 *   - undefined: the undefined instruction, as after an ARM_UNDEFINED stop (r14 = r15 + 4 in
 *     ARM state, + 2 in Thumb state);
 *   - prefetch abort: the faulting instruction (r14 = r15 + 4);
 *   - data abort: the faulting instruction (r14 = r15 + 8).
 * A hook at the vector is consulted when the run loop next fetches, not here. */
void arm_enter_exception(ArmCpu *cpu, enum ArmException exception);

/* Takes the IRQ exception now if CPSR I is clear, whatever irq_line says. Returns 1 when it
 * was taken (r15 is the vector), 0 when I is set. */
int arm_raise_irq(ArmCpu *cpu);

/* The CP15 register at CRn, CRm, opcode2 as MRC would read it. */
uint32_t arm_cp15_get(const ArmCpu *cpu, int crn, int crm, int op2);

/* Call the function at `address` (bit 0 set for Thumb) with arguments r0-r3 already in
 * cpu->r and the stack pointer in r13: sets lr to ARM_RETURN_ADDRESS and runs until the
 * function returns there, something stops it, or `max_steps` instructions have run
 * (0 for no limit).
 *
 * On return, stop_pc is where execution stopped and r15 is where it would resume: after an
 * ARM_SWI or ARM_HALT it is the instruction following the SWI or the MCR; after ARM_UNDEFINED,
 * ARM_BREAKPOINT and ARM_BAD_ADDRESS it is the instruction itself (a faulting multi-register
 * transfer may have updated some registers already); after ARM_HOOK_STOP it is the hooked
 * address.
 *
 * A pending IRQ (irq_line set, CPSR I clear) is taken inside the run, before the next
 * instruction, and execution carries on in the handler; the run does not stop for it. */
enum ArmStop arm_call(ArmCpu *cpu, uint32_t address, uint64_t max_steps);

/* Run from r15 (Thumb when cpsr T is set) until `until` (bit 0 ignored) is about to execute,
 * which stops with ARM_RETURNED, or something else stops it. A branch to ARM_RETURN_ADDRESS
 * stops with ARM_RETURNED as well. */
enum ArmStop arm_run(ArmCpu *cpu, uint32_t until, uint64_t max_steps);

#endif
