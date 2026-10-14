/* Calling Native code from the runtime: the PC's calling conventions and its faults. */
#ifndef RUNTIME_HOST_H
#define RUNTIME_HOST_H

#include <stdint.h>

/* Calls `fn` with `count` 32-bit arguments as the PC's compiler expects them: all on the stack
 * (cdecl), or with the first in ecx when `thiscall` is set (C++ member functions on 32-bit
 * Windows). Returns edx:eax, which holds a 64-bit result or a 32-bit one in the low half. */
uint64_t host_invoke(const void *fn, const uint32_t *args, int count, int thiscall);

/* Runs host_invoke, but returns nonzero instead of crashing when the code faults (an access to
 * memory the process does not have); *fault is then the faulting data address, if known. */
int host_guarded_invoke(const void *fn, const uint32_t *args, int count, int thiscall, uint64_t *result, uint32_t *fault);

#endif
