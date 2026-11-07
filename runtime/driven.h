/* Driven calls (docs/verification.md, "Driven calls"): the run calls game functions that no
 * game path calls, on objects that are alive in it, at a chosen frame.
 *
 * With RUN_DRIVEN=FILE (tools/run.py --driven, written by tools/driven.py), the run reads lines
 *
 *     arm ADDRESS VALUE      where calls are made: the next branch target after the function
 *                            at ADDRESS is entered with r0 == VALUE (0: any r0), on the same
 *                            thread, outside IRQ mode and not where a stall is pending
 *     call FRAME TARGET R0 R1 R2 R3 GUARD_ADDRESS GUARD_VALUE
 *                            from frame FRAME on, at the arm point: TARGET (bit 0 set for
 *                            Thumb) with r0-r3, if the word at GUARD_ADDRESS is GUARD_VALUE
 *                            (no guard when GUARD_ADDRESS is 0)
 *     vcall FRAME VPTR SLOT R0 R1 R2 R3 VTABLE
 *                            the same through the object's own vtable: if the word at VPTR is
 *                            VTABLE, the function at VTABLE + SLOT (a byte offset)
 *     end                    the run ends after the last calls (and their memory image)
 *
 * (hex numbers, FRAME decimal; # starts a comment; in place of R0-R3, rN is the r0 the call
 * made N calls before at the same moment returned). The calls of one frame run one after
 * another at one arm point, each as the game's own code would make it: the interpreter
 * branches to the target with lr at DRIVEN_RETURN_ADDRESS, so the target runs as Reference,
 * Native or Clean as the run's choices say, and the Reference pass records it among its
 * crossings like any call (native_run.h); at that address the registers of the arm point are
 * put back and the game goes on from there. After the calls of a moment, memory is hashed
 * (DRIVEN_SNAPSHOT), and each branch target they reached is printed ("driven: entered", from
 * the Reference: the functions they ran, each with the module loaded there, as overlays at one
 * address can share bytes). Each call prints a line "driven: ..." with what it
 * did (or why it was skipped), in both passes. Without RUN_DRIVEN nothing changes. */
#ifndef RUNTIME_DRIVEN_H
#define RUNTIME_DRIVEN_H

#include <stdint.h>

#include "arm.h"

/* Where a driven call returns to: no code is there (below native_run.c's IDLE_ADDRESS, above
 * the BIOS). */
#define DRIVEN_RETURN_ADDRESS 0xffffffd0u

/* After the calls of an arm point, memory is hashed (and compared in the Native run) as
 * after a frame numbered DRIVEN_SNAPSHOT + the frame of the calls (native_snapshot_now). */
#define DRIVEN_SNAPSHOT 900000000u

/* Nonzero when RUN_DRIVEN names a file of calls (read once; the run ends on a bad file). */
int driven_enabled(void);

/* At every branch target, after the thread check, with the running DS thread: the hook that
 * starts the next driven calls, or NULL. */
ArmHook driven_hook_at(ArmCpu *cpu, uint32_t address, uint32_t thread);

/* The hook at DRIVEN_RETURN_ADDRESS: the next call of the same moment, or the arm point's
 * registers back. */
int driven_returned(ArmCpu *cpu, void *user);

#endif
