#ifndef _WIN32
#define _GNU_SOURCE
#endif

#include "host.h"

#include <setjmp.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <signal.h>
#include <string.h>
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "host_invoke is written for 32-bit x86"
#endif

#define HOST_MAX_ARGS 16

/* Every Native function takes its arguments on the stack and returns in eax (edx for the high
 * word of a 64-bit result), members too: tools/native.py builds the Windows objects for
 * i686-pc-windows-itanium, whose members take `this` like any first argument, so `thiscall`
 * changes nothing on either host. The call passes HOST_MAX_ARGS words, of which the callee
 * reads the ones it takes; the caller removes them, as cdecl does, and the compiler keeps the
 * stack aligned and the registers the callee may change accounted for. */
typedef uint64_t (*HostFunction)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                 uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

uint64_t host_invoke(const void *fn, const uint32_t *args, int count, int thiscall)
{
    (void) thiscall;
    uint32_t a[HOST_MAX_ARGS] = {0};
    for (int i = 0; i < count && i < HOST_MAX_ARGS; i++) {
        a[i] = args[i];
    }
    HostFunction f = (HostFunction) (uintptr_t) fn;
    return f(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);
}

#ifdef _WIN32

static jmp_buf *guard_jump;
static uint32_t guard_fault;

static LONG CALLBACK on_fault(EXCEPTION_POINTERS *info)
{
    DWORD code = info->ExceptionRecord->ExceptionCode;
    if (guard_jump == NULL || (code != EXCEPTION_ACCESS_VIOLATION && code != EXCEPTION_INT_DIVIDE_BY_ZERO &&
                               code != EXCEPTION_ILLEGAL_INSTRUCTION && code != EXCEPTION_STACK_OVERFLOW)) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    guard_fault = code == EXCEPTION_ACCESS_VIOLATION ? (uint32_t) info->ExceptionRecord->ExceptionInformation[1] : 0;
    jmp_buf *jump = guard_jump;
    guard_jump = NULL;
    longjmp(*jump, 1);
}

int host_guarded_invoke(const void *fn, const uint32_t *args, int count, int thiscall, uint64_t *result, uint32_t *fault)
{
    static void *handler;
    if (handler == NULL) {
        handler = AddVectoredExceptionHandler(1, on_fault);
    }
    jmp_buf jump;
    if (setjmp(jump) != 0) {
        *fault = guard_fault;
        return 1;
    }
    guard_jump = &jump;
    *result = host_invoke(fn, args, count, thiscall);
    guard_jump = NULL;
    return 0;
}

#else

static sigjmp_buf *guard_jump;
static uint32_t guard_fault;

static void on_fault(int sig, siginfo_t *info, void *context)
{
    (void) context;
    if (guard_jump == NULL) {
        signal(sig, SIG_DFL);
        raise(sig);
        return;
    }
    guard_fault = (uint32_t) (uintptr_t) info->si_addr;
    sigjmp_buf *jump = guard_jump;
    guard_jump = NULL;
    siglongjmp(*jump, 1);
}

int host_guarded_invoke(const void *fn, const uint32_t *args, int count, int thiscall, uint64_t *result, uint32_t *fault)
{
    static int installed;
    if (!installed) {
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_sigaction = on_fault;
        sa.sa_flags = SA_SIGINFO | SA_NODEFER;
        sigaction(SIGSEGV, &sa, NULL);
        sigaction(SIGBUS, &sa, NULL);
        sigaction(SIGFPE, &sa, NULL);
        sigaction(SIGILL, &sa, NULL);
        installed = 1;
    }
    sigjmp_buf jump;
    if (sigsetjmp(jump, 1) != 0) {
        *fault = guard_fault;
        return 1;
    }
    guard_jump = &jump;
    *result = host_invoke(fn, args, count, thiscall);
    guard_jump = NULL;
    return 0;
}

#endif
