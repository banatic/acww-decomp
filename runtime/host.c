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

#define HOST_MEMBERS_THISCALL 0

#if !defined(__i386__) && !defined(_M_IX86)
#error "host_invoke is written for 32-bit x86"
#endif

uint64_t host_invoke(const void *fn, const uint32_t *args, int count, int thiscall)
{
    uint32_t lo, hi;
    /* The Native objects are built so that member functions take `this` on the stack, like
       any first argument (tools/native.py: i686-pc-windows-itanium, not windows-gnu, whose
       members are thiscall), so `thiscall` changes nothing on either host. The ecx path is
       kept for code built the other way. */
    thiscall = thiscall && HOST_MEMBERS_THISCALL;
    int first = thiscall ? 1 : 0;
    uint32_t self = thiscall && count > 0 ? args[0] : 0;
    /* Push the arguments right to left, call, and put the stack pointer back whether the
     * callee popped its arguments (thiscall) or not (cdecl). */
    __asm__ volatile("movl %%esp, %%edi\n\t"
                     "1:\n\t"
                     "cmpl %%ebx, %%esi\n\t"
                     "jle 2f\n\t"
                     "decl %%esi\n\t"
                     "pushl (%%edx,%%esi,4)\n\t"
                     "jmp 1b\n\t"
                     "2:\n\t"
                     "call *%%eax\n\t"
                     "movl %%edi, %%esp\n\t"
                     : "=a"(lo), "=d"(hi), "+S"(count)
                     : "a"(fn), "d"(args), "b"(first), "c"(self)
                     : "edi", "memory", "cc");
    return ((uint64_t) hi << 32) | lo;
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
