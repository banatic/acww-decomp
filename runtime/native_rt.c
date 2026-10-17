/* Helpers the PC's compiler calls from Native code on 32-bit x86 that the host's C runtime
 * does not provide under these names (they come from libgcc / compiler-rt elsewhere). */
#include <stdint.h>
#include <stdlib.h>
#include "native_guest.h"

void (*native_guest_enter_hook)(uint32_t index, uintptr_t caller, const uint32_t *args);
uintptr_t (*native_guest_return_hook)(uint32_t index);
uint32_t (*native_guest_slot_hook)(uint32_t owner, uint32_t offset, uint32_t size);

uint32_t native_guest_stack_slot(uint32_t owner, uint32_t offset, uint32_t size)
{
    if (native_guest_slot_hook == NULL) {
        abort();
    }
    return native_guest_slot_hook(owner, offset, size);
}

void native_guest_enter(uint32_t index, uintptr_t caller, const uint32_t *args)
{
    native_guest_enter_hook(index, caller, args);
}

__attribute__((target("general-regs-only"))) uintptr_t native_guest_return(uint32_t index)
{
    if (native_guest_return_hook == NULL) {
        abort();
    }
    return native_guest_return_hook(index);
}

/* Elsewhere libgcc has these; defined there, `a / b` below would call itself. */
#ifdef _WIN32
uint64_t __udivdi3(uint64_t a, uint64_t b);
uint64_t __umoddi3(uint64_t a, uint64_t b);
int64_t __divdi3(int64_t a, int64_t b);
int64_t __moddi3(int64_t a, int64_t b);

uint64_t __udivdi3(uint64_t a, uint64_t b)
{
    return a / b;
}
uint64_t __umoddi3(uint64_t a, uint64_t b)
{
    return a % b;
}
int64_t __divdi3(int64_t a, int64_t b)
{
    return a / b;
}
int64_t __moddi3(int64_t a, int64_t b)
{
    return a % b;
}
#endif

/* A C++ function-local static with a dynamic initializer is guarded by these (the Itanium C++
 * ABI); Native code runs on one thread, so the guard's first byte is all they need. */
int __cxa_guard_acquire(uint64_t *guard);
void __cxa_guard_release(uint64_t *guard);
void __cxa_guard_abort(uint64_t *guard);

int __cxa_guard_acquire(uint64_t *guard)
{
    return *(uint8_t *) guard == 0;
}
void __cxa_guard_release(uint64_t *guard)
{
    *(uint8_t *) guard = 1;
}
void __cxa_guard_abort(uint64_t *guard)
{
    (void) guard;
}

#ifdef _WIN32
/* The objects tools/native.py builds for i686-pc-windows-itanium call the C++ runtime through
 * import pointers (`__imp_` names), as if it were a DLL; these are those pointers. */
int (*_imp____cxa_guard_acquire)(uint64_t *guard) = __cxa_guard_acquire;
void (*_imp____cxa_guard_release)(uint64_t *guard) = __cxa_guard_release;
void (*_imp____cxa_guard_abort)(uint64_t *guard) = __cxa_guard_abort;
#endif
