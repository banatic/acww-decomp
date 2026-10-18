/* Running the game with Native functions (docs/runtime.md, M4): the matching sources compiled
 * for the PC take the place of their Reference in the interpreted run, and the two kinds of
 * code call each other freely.
 *
 * Calls between the two
 *   Reference -> Native: a hook at the function's entry (every branch target is looked up)
 *   calls the PC function with r0-r3 and the words on the DS stack as its arguments, puts the
 *   result in r0 (r1), and continues at lr.
 *   Native -> Reference: Native code reaches the DS's code by calling a DS address: a function
 *   without a Native (a library), one kept Reference, or any call through a pointer, a vtable
 *   or a member-function pointer. DS memory is not executable, so the call faults on its
 *   first instruction fetch; the fault handler (native_os.c) sends the CPU to
 *   native_trampoline (native_tramp.S), which hands the arguments to the interpreter and
 *   returns its result in edx:eax. A target that has a Native of its own is jumped to
 *   directly instead. Native functions kept Reference are patched at their entry to go the
 *   same way, so their Native callers reach the ROM's code too.
 *
 * Threads
 *   The game switches DS threads with the SDK's own code (OS_SaveContext / OS_LoadContext,
 *   OS_IrqHandler_ThreadSwitch), run by the interpreter. While a Native function waits in a
 *   call into the Reference (the main loop's wait for VBlank), its frames are on the host
 *   stack; the next thread must not run on top of them. So every DS thread has its own host
 *   stack (a fiber): when OSi_ThreadInfo.current changes, which the SDK writes just before it
 *   loads the next thread's context, the run continues on that thread's fiber (created on its
 *   first switch, with the run loop at its base). The interpreter's own state is global, so
 *   which fiber interprets the few scheduler instructions between the write and the context
 *   load does not matter; what matters is that a return into Native code (the end of a nested
 *   call) always happens on the fiber that holds the Native frames, and that is the fiber of
 *   the thread whose code makes that return.
 *
 * Time
 *   The DS's clock advances with interpreted instructions, and the game's frames depend on it
 *   (the title renders its 3D scene every second to fourth frame, as fast as its code runs).
 *   Native code takes no instructions, so on its own it would run the game faster than the
 *   Reference and produce other frames. A Native run therefore takes its time from a
 *   Reference run of the same recording: the Reference pass (native_record) notes, for every
 *   crossing between code that would be Native and code that would be interpreted, the step
 *   count at that moment, per thread and for interrupt handlers; the Native pass reads them
 *   back and stalls the CPU (ArmCpu.stall_until) until each crossing's step count, so its
 *   clock, slices and interrupts fall where the Reference's do. The crossings also check the
 *   Native run: a crossing that differs from the Reference's (another function, another kind)
 *   is the first divergence, reported with both sides.
 *
 * Hardware
 *   I/O registers, VRAM and the other areas the interpreter serves through io.c are not
 *   memory in this process. A Native function that touches one faults; the run stops, names
 *   the function, and (RUN_NATIVE_LEARN) adds it to a file of functions kept Reference.
 */
#ifndef RUNTIME_NATIVE_RUN_H
#define RUNTIME_NATIVE_RUN_H

#include <stdint.h>
#include <stdio.h>

#include "arm.h"

/* First thing in main, before the host allocates memory: with RUN_NATIVE, reserves the DS's
 * address ranges that are not memory here (I/O, VRAM, ...), so that Native code faults there
 * and host pointers never look like DS addresses. -1 when they are taken already. */
int native_reserve(void);

/* Reads the environment: RUN_NATIVE_POLICY (the functions and what each may do, written by
 * tools/run.py), RUN_NATIVE (1: run Native functions), RUN_NATIVE_RECORD / RUN_NATIVE_REPLAY
 * (the crossing trace to write in a Reference run / to follow in a Native run),
 * RUN_NATIVE_LEARN (where a Native function that touches hardware is noted), RUN_RAM_HASH
 * (frames after which memory is hashed). `manifest` lists the modules (for the overlay
 * checks). Returns 0 when nothing is asked for, 1 when active, -1 on an error. */
int native_init(ArmCpu *cpu, const char *manifest);

/* Runs `loop` (the run loop; it does not return). With Native functions, it runs on a host
 * stack of its own: Native code hands the interpreter pointers to its locals, and those must
 * not fall in the DS's address ranges (on Linux the process stack sits where the DS has its
 * BIOS). */
void native_start(void (*loop)(void));

/* Native functions run (RUN_NATIVE): the interpreter only fills in for them. */
int native_running(void);

/* The resident modules are in place (the crt0 has unpacked them): their functions may run
 * as Native from now on. */
void native_resident_ready(void);

/* At every branch target, after the thread check: the hook that runs the Native function at
 * `address` (Native run), or NULL. In a Reference run with RUN_NATIVE_RECORD this follows
 * the crossings instead and returns NULL. */
ArmHook native_hook_at(uint32_t address, void **hook_user);

/* The running DS thread is now `thread` (OSi_ThreadInfo.current); `previous` was. Returns
 * the hook that moves the run to that thread's fiber, or NULL when nothing needs to move. */
ArmHook native_thread_changed(uint32_t previous, uint32_t thread);

/* A frame has ended (memory hashes are taken at the next quiet crossing after it). */
void native_frame_ended(uint32_t frame);

/* The counts for the run's report. */
void native_report(FILE *out);

/* Provided by run.c: runs the interpreter, with the clock and the hardware, until the CPU
 * branches to ARM_RETURN_ADDRESS. */
void run_until_return(void);

/* Commit an already completed shared slice before a Native publication store.
 * Preserve a partial slice, its deadline, and unaccounted instruction time.
 * Return 0 if hardware time is already ahead of the CPU's requested step. */
int run_native_store_boundary(void);

/* Provided by run.c: the run loop at the base of a thread's fiber; does not return. */
void run_forever(void);

/* Provided by run.c: sets the step count back to `steps` (the clock does not run backwards:
 * the open slice still ends at its step count); returns the steps taken back. */
uint64_t run_rewind(uint64_t steps);

/* Provided by run.c: ends the run with a report (exit status `status`). */
void run_finish(const char *reason, int status);

#endif
