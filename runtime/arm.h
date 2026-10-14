/* An ARMv5TE (ARM946E-S) interpreter for the ARM and Thumb instruction sets.
 *
 * Memory is the host's: an address the DS maps to RAM is a host pointer here (see memory.h),
 * so loads and stores go straight to it. Addresses outside RAM (I/O registers) go to the
 * io_read / io_write callbacks.
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
    ARM_HOOK_STOP     /* a hook asked to stop */
};

typedef struct ArmCpu ArmCpu;

/* Called before the instruction at a hooked address executes (bit 0 clear). Return nonzero to
 * stop with ARM_HOOK_STOP; a hook may change registers and pc to run something else instead,
 * for example a host implementation of the function that returns to lr. */
typedef int (*ArmHook)(ArmCpu *cpu, void *user);

struct ArmCpu {
    uint32_t r[16];   /* r[15] is the address of the next instruction to execute */
    uint32_t cpsr;    /* N Z C V Q in bits 31..27, T in bit 5, mode in bits 4..0 */
    uint64_t steps;   /* instructions executed */
    uint32_t stop_pc; /* where execution stopped */
    uint32_t fault_address;
    uint32_t swi;

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
#define ARM_CPSR_T (1u << 5)
#define ARM_MODE_SYSTEM 0x1f

/* The return address arm_call puts in lr. It sits past the end of the ARM9 BIOS, where no
 * game or SDK code lives, so a branch to it in either state can only be the function
 * returning. */
#define ARM_RETURN_ADDRESS 0xfffffff0u

/* A CPU in system mode, all registers zero, no callbacks. */
void arm_init(ArmCpu *cpu);

/* Call the function at `address` (bit 0 set for Thumb) with arguments r0-r3 already in
 * cpu->r and the stack pointer in r13: sets lr to ARM_RETURN_ADDRESS and runs until the
 * function returns there, something stops it, or `max_steps` instructions have run
 * (0 for no limit).
 *
 * On return, stop_pc is where execution stopped and r15 is where it would resume: after an
 * ARM_SWI it is the instruction following the SWI; after ARM_UNDEFINED, ARM_BREAKPOINT and
 * ARM_BAD_ADDRESS it is the instruction itself (a faulting multi-register transfer may have
 * updated some registers already); after ARM_HOOK_STOP it is the hooked address. */
enum ArmStop arm_call(ArmCpu *cpu, uint32_t address, uint64_t max_steps);

/* Run from r15 (Thumb when cpsr T is set) until `until` (bit 0 ignored) is about to execute,
 * which stops with ARM_RETURNED, or something else stops it. A branch to ARM_RETURN_ADDRESS
 * stops with ARM_RETURNED as well. */
enum ArmStop arm_run(ArmCpu *cpu, uint32_t until, uint64_t max_steps);

#endif
