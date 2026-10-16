/* What the Native run needs from the host system (native_os.c): the fault handler that turns
 * a call to a DS address into a call into the interpreter, host stacks for the DS threads
 * (fibers), and patching code. See native_run.h for the design. */
#ifndef RUNTIME_NATIVE_OS_H
#define RUNTIME_NATIVE_OS_H

#include <stddef.h>
#include <stdint.h>

/* Prints where the program crashes (an access violation in the runtime or in Native code that
 * nothing handles), for the link map. */
void native_os_report_crashes(void);

/* Installs the fault handler and makes the calling host thread the first fiber. */
int native_os_init(void);

/* Called by the fault handler (native_run.c), on the faulting stack:
 *   native_fault_execute: Native code called `target`, a DS address, with `ecx` (`this` of a
 *     thiscall). Returns where execution continues (a Native function, or native_trampoline
 *     with *eax = target).
 *   native_fault_data: Native code at host address `eip` read or wrote `address`, which the
 *     process does not have. Returns 0 when the fault is not Native code's (the handler then
 *     lets the process crash as usual); otherwise it ends the run and does not return.
 *   native_fault_is_ds: the address belongs to the DS (a call there is a call into the ROM's
 *     code), not to the host. */
uintptr_t native_fault_execute(uint32_t target, uint32_t *eax, uint32_t ecx);
int native_fault_data(uint32_t eip, uint32_t address, uint32_t esp);
int native_fault_is_ds(uint32_t address);
/* Native code at host address `eip` divided by zero (or INT_MIN by -1): 1 when it is Native
 * code's, which then goes on with the ROM's helpers' result (native_os.c), else 0. */
int native_fault_divide(uint32_t eip);
/* Debugging (RUN_NATIVE_HWWATCH, Windows): code at host address `eip` wrote the watched word. */
void native_watch_hit(uint32_t eip);

/* Starts a thread that calls `progress` every second and, after `seconds` calls in a row
 * that return 0, stops the calling thread and passes `stuck` its instruction pointer (on
 * Linux, from a signal handler on that thread). `stuck` does not return. */
int native_os_watchdog(int seconds, int (*progress)(void), void (*stuck)(uint32_t eip));

/* A host stack that runs `entry` when first switched to, and switching to one. */
void *native_os_fiber_current(void);
void *native_os_fiber_create(void (*entry)(void));
void native_os_fiber_switch(void *fiber);

/* Overwrites `size` bytes of code at `at`. 0 on success. */
int native_os_patch(void *at, const void *bytes, size_t size);

/* Whether the host's memory at [address, address + size) can be read (or written). The
 * interpreter asks before it serves a host address: a wild pointer in the ROM's code must
 * stop the run as on a Reference run, not crash it. */
int native_os_accessible(uint32_t address, uint32_t size, int write);

/* `size` bytes of memory that can hold code. */
void *native_os_code_alloc(size_t size);

/* Reserves an address range so the host never places memory there: an address in it always
 * means the DS's. Returns how many bytes of it were already taken. */
uint32_t native_os_reserve(uint32_t base, uint32_t size);

/* The entry of the trampoline (native_tramp.S), the bytes the callee it stands for pops, and
 * whether its result is a float (1) or a double (2). */
void native_trampoline(void);
extern uint32_t native_pop_bytes;
extern uint32_t native_return_floating;

#endif
