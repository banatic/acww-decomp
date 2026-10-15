/* The host side of the Native run: faults, fibers, code patching (native_os.h). */
#ifndef _WIN32
#define _GNU_SOURCE /* REG_EIP, MAP_ANONYMOUS */
#endif

#include "native_os.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#include <sys/mman.h>
#include <ucontext.h>
#include <unistd.h>
#endif

/* Each fiber's stack: Native code, the interpreter it calls, and the Native code that calls
 * again, nest on it. */
#define FIBER_STACK (16u << 20)

#ifdef _WIN32

/* A call to a DS address faults on the instruction fetch: an access violation whose kind
 * (ExceptionInformation[0]) is 8, "execute", at the instruction pointer itself. */
static LONG CALLBACK on_fault(EXCEPTION_POINTERS *info)
{
    EXCEPTION_RECORD *r = info->ExceptionRecord;
    CONTEXT *c = info->ContextRecord;
    if (r->ExceptionCode == EXCEPTION_SINGLE_STEP && (c->Dr6 & 1)) {
        /* RUN_NATIVE_HWWATCH: a write to the watched word */
        native_watch_hit((uint32_t) c->Eip);
        c->Dr6 = 0;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    if (r->ExceptionCode != EXCEPTION_ACCESS_VIOLATION || r->NumberParameters < 2) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    uint32_t address = (uint32_t) r->ExceptionInformation[1];
    if ((r->ExceptionInformation[0] == 8 || address == c->Eip) && native_fault_is_ds(c->Eip)) {
        uint32_t eax = (uint32_t) c->Eax;
        c->Eip = (DWORD) native_fault_execute((uint32_t) c->Eip, &eax, (uint32_t) c->Ecx);
        c->Eax = eax;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    native_fault_data((uint32_t) c->Eip, address, (uint32_t) c->Esp);
    fprintf(stderr, "native: the host faulted at eip %08x, address %08x\n", (uint32_t) c->Eip, address);
    /* the words on the stack that look like return addresses into the program, for the map */
    const uint32_t *sp = (const uint32_t *) (uintptr_t) c->Esp;
    fprintf(stderr, "native: stack");
    for (int i = 0, n = 0; i < 256 && n < 16; i++) {
        if (sp[i] >= 0x00401000u && sp[i] < 0x00f00000u) {
            fprintf(stderr, " %08x", sp[i]);
            n++;
        }
    }
    fprintf(stderr, "\n");
    return EXCEPTION_CONTINUE_SEARCH;
}

/* A crash anywhere: where, and the words on the stack that look like return addresses into
 * the program (the link map names them). */
static LONG WINAPI on_crash(EXCEPTION_POINTERS *info)
{
    CONTEXT *c = info->ContextRecord;
    fprintf(
        stderr, "crash: exception %08lx at eip %08lx, address %08lx; stack", info->ExceptionRecord->ExceptionCode,
        (unsigned long) c->Eip,
        (unsigned long) (info->ExceptionRecord->NumberParameters > 1 ? info->ExceptionRecord->ExceptionInformation[1] : 0));
    MEMORY_BASIC_INFORMATION m;
    const uint32_t *sp = (const uint32_t *) (uintptr_t) c->Esp;
    for (int i = 0, n = 0; i < 1024 && n < 16; i++) {
        if (VirtualQuery(sp + i, &m, sizeof(m)) == 0 || m.State != MEM_COMMIT) {
            break;
        }
        if (sp[i] >= 0x00401000u && sp[i] < 0x01000000u) {
            fprintf(stderr, " %08x", sp[i]);
            n++;
        }
    }
    fprintf(stderr, "\n");
    return EXCEPTION_CONTINUE_SEARCH;
}

void native_os_report_crashes(void)
{
    SetUnhandledExceptionFilter(on_crash);
}

int native_os_init(void)
{
    if (AddVectoredExceptionHandler(1, on_fault) == NULL) {
        return -1;
    }
    const char *hw = getenv("RUN_NATIVE_HWWATCH");
    if (hw != NULL) {
        /* debugging: a hardware breakpoint on writes to one word (DR0, 4 bytes) */
        CONTEXT c;
        memset(&c, 0, sizeof(c));
        c.ContextFlags = CONTEXT_DEBUG_REGISTERS;
        c.Dr0 = (DWORD) strtoul(hw, NULL, 16);
        c.Dr7 = 1u | (1u << 16) | (3u << 18);
        SetThreadContext(GetCurrentThread(), &c);
    }
    return ConvertThreadToFiber(NULL) == NULL ? -1 : 0;
}

static HANDLE watched_thread;
static int (*watch_progress)(void);
static void (*watch_stuck)(uint32_t eip);
static int watch_seconds;

static DWORD WINAPI watchdog(LPVOID unused)
{
    (void) unused;
    for (int idle = 0;;) {
        Sleep(1000);
        idle = watch_progress() ? 0 : idle + 1;
        if (idle >= watch_seconds) {
            /* the run's thread is stopped where it loops; it never runs again */
            CONTEXT c;
            memset(&c, 0, sizeof(c));
            c.ContextFlags = CONTEXT_CONTROL;
            SuspendThread(watched_thread);
            GetThreadContext(watched_thread, &c);
            watch_stuck((uint32_t) c.Eip);
        }
    }
}

int native_os_watchdog(int seconds, int (*progress)(void), void (*stuck)(uint32_t eip))
{
    watch_progress = progress;
    watch_stuck = stuck;
    watch_seconds = seconds;
    if (!DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &watched_thread, 0, FALSE,
                         DUPLICATE_SAME_ACCESS)) {
        return -1;
    }
    return CreateThread(NULL, 0, watchdog, NULL, 0, NULL) == NULL ? -1 : 0;
}

void *native_os_fiber_current(void)
{
    return GetCurrentFiber();
}

static VOID CALLBACK fiber_start(LPVOID param)
{
    void (*entry)(void) = (void (*)(void)) param;
    entry();
}

void *native_os_fiber_create(void (*entry)(void))
{
    return CreateFiberEx(64u << 10, FIBER_STACK, 0, fiber_start, (LPVOID) entry);
}

void native_os_fiber_switch(void *fiber)
{
    SwitchToFiber(fiber);
}

int native_os_patch(void *at, const void *bytes, size_t size)
{
    DWORD old;
    if (!VirtualProtect(at, size, PAGE_EXECUTE_READWRITE, &old)) {
        return -1;
    }
    memcpy(at, bytes, size);
    VirtualProtect(at, size, old, &old);
    FlushInstructionCache(GetCurrentProcess(), at, size);
    return 0;
}

void *native_os_code_alloc(size_t size)
{
    return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

int native_os_accessible(uint32_t address, uint32_t size, int write)
{
    MEMORY_BASIC_INFORMATION m;
    if (VirtualQuery((void *) (uintptr_t) address, &m, sizeof(m)) == 0 || m.State != MEM_COMMIT ||
        (m.Protect & (PAGE_GUARD | PAGE_NOACCESS)) != 0) {
        return 0;
    }
    if ((uintptr_t) address + size > (uintptr_t) m.BaseAddress + m.RegionSize) {
        return 0;
    }
    DWORD writable = PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
    return !write || (m.Protect & writable) != 0;
}

uint32_t native_os_reserve(uint32_t base, uint32_t size)
{
    /* Reserved, never committed: any access faults. Piece by piece (Windows reserves in
       64 KiB units), so a piece already taken leaves the others reserved. */
    uint32_t missed = 0;
    for (uint32_t a = base; a < base + size; a += 0x10000u) {
        if (VirtualAlloc((void *) (uintptr_t) a, 0x10000u, MEM_RESERVE, PAGE_NOACCESS) == NULL) {
            MEMORY_BASIC_INFORMATION m;
            if (VirtualQuery((void *) (uintptr_t) a, &m, sizeof(m)) == 0 || m.State != MEM_RESERVE ||
                m.AllocationProtect != PAGE_NOACCESS) {
                missed += 0x10000u;
            }
        }
    }
    return missed;
}

#else

/* The kernel starts the heap (brk) right after the image, at a random offset of up to 32 MiB:
 * after an image at 0x00400000 that can be the DS's main memory (0x02000000), taken before
 * memory_init maps it. tools/run.py links this section at 0x10000000, above every DS address,
 * so the image ends, and the heap starts, there. */
__attribute__((section(".heap_floor"), used)) static char heap_floor = 1;

static void on_fault(int sig, siginfo_t *info, void *context)
{
    ucontext_t *uc = context;
    greg_t *g = uc->uc_mcontext.gregs;
    uint32_t eip = (uint32_t) g[REG_EIP];
    uint32_t address = (uint32_t) (uintptr_t) info->si_addr;
    if (sig == SIGSEGV && address == eip && native_fault_is_ds(eip)) {
        uint32_t eax = (uint32_t) g[REG_EAX];
        g[REG_EIP] = (greg_t) native_fault_execute(eip, &eax, (uint32_t) g[REG_ECX]);
        g[REG_EAX] = (greg_t) eax;
        return;
    }
    native_fault_data(eip, address, (uint32_t) g[REG_ESP]);
    fprintf(stderr, "native: the host faulted at eip %08x, address %08x\n", eip, address);
    /* not Native code's: crash as the process would have */
    signal(sig, SIG_DFL);
}

static pthread_t watched_thread;
static int (*watch_progress)(void);
static void (*watch_stuck)(uint32_t eip);
static int watch_seconds;

/* Delivered to the run's thread by the watchdog: report where it loops. */
static void on_stuck(int sig, siginfo_t *info, void *context)
{
    (void) sig;
    (void) info;
    ucontext_t *uc = context;
    watch_stuck((uint32_t) uc->uc_mcontext.gregs[REG_EIP]);
}

static void *watchdog(void *unused)
{
    (void) unused;
    for (int idle = 0;;) {
        sleep(1);
        idle = watch_progress() ? 0 : idle + 1;
        if (idle >= watch_seconds) {
            pthread_kill(watched_thread, SIGUSR1);
            sleep(60);
        }
    }
    return NULL;
}

int native_os_watchdog(int seconds, int (*progress)(void), void (*stuck)(uint32_t eip))
{
    watch_progress = progress;
    watch_stuck = stuck;
    watch_seconds = seconds;
    watched_thread = pthread_self();
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = on_stuck;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    pthread_t t;
    if (sigaction(SIGUSR1, &sa, NULL) != 0 || pthread_create(&t, NULL, watchdog, NULL) != 0) {
        return -1;
    }
    return 0;
}

static void on_crash(int sig, siginfo_t *info, void *context)
{
    ucontext_t *uc = context;
    fprintf(stderr, "crash: signal %d at eip %08x, address %08x\n", sig, (uint32_t) uc->uc_mcontext.gregs[REG_EIP],
            (uint32_t) (uintptr_t) info->si_addr);
    signal(sig, SIG_DFL);
}

void native_os_report_crashes(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = on_crash;
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
}

int native_os_init(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = on_fault;
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGSEGV, &sa, NULL) != 0 || sigaction(SIGBUS, &sa, NULL) != 0) {
        return -1;
    }
    return 0;
}

typedef struct Fiber {
    ucontext_t context;
    void (*entry)(void);
} Fiber;

static Fiber first_fiber;
static Fiber *current_fiber = &first_fiber;

void *native_os_fiber_current(void)
{
    return current_fiber;
}

static void fiber_start(void)
{
    current_fiber->entry();
}

void *native_os_fiber_create(void (*entry)(void))
{
    Fiber *f = calloc(1, sizeof(*f));
    void *stack = mmap(NULL, FIBER_STACK, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (f == NULL || stack == MAP_FAILED || getcontext(&f->context) != 0) {
        return NULL;
    }
    f->entry = entry;
    f->context.uc_stack.ss_sp = stack;
    f->context.uc_stack.ss_size = FIBER_STACK;
    f->context.uc_link = NULL;
    makecontext(&f->context, fiber_start, 0);
    return f;
}

void native_os_fiber_switch(void *fiber)
{
    Fiber *from = current_fiber;
    current_fiber = fiber;
    swapcontext(&from->context, &current_fiber->context);
}

int native_os_patch(void *at, const void *bytes, size_t size)
{
    uintptr_t page = (uintptr_t) sysconf(_SC_PAGESIZE);
    uintptr_t start = (uintptr_t) at & ~(page - 1);
    uintptr_t end = ((uintptr_t) at + size + page - 1) & ~(page - 1);
    if (mprotect((void *) start, end - start, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
        return -1;
    }
    memcpy(at, bytes, size);
    mprotect((void *) start, end - start, PROT_READ | PROT_EXEC);
    return 0;
}

int native_os_accessible(uint32_t address, uint32_t size, int for_write)
{
    /* The kernel reads the bytes for write() to a pipe and fails with EFAULT where it cannot:
       a page nothing maps, or a guard page (PROT_NONE, which mincore counts as mapped). The
       reserved DS ranges never get here (native_fault_is_ds). Writability is not checked:
       host memory Native code hands over is its stack or its data, both writable. */
    static int probe[2] = {-1, -1};
    (void) for_write;
    if (probe[0] < 0 && pipe(probe) != 0) {
        return 0;
    }
    char sink[8];
    uint32_t done = 0;
    while (done < size) {
        size_t n = size - done < sizeof(sink) ? size - done : sizeof(sink);
        if (write(probe[1], (const void *) (uintptr_t) (address + done), n) != (ssize_t) n) {
            return 0;
        }
        if (read(probe[0], sink, n) != (ssize_t) n) {
            return 0;
        }
        done += (uint32_t) n;
    }
    return 1;
}

void *native_os_code_alloc(size_t size)
{
    void *p = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return p == MAP_FAILED ? NULL : p;
}

uint32_t native_os_reserve(uint32_t base, uint32_t size)
{
    /* MAP_FIXED_NOREPLACE fails when any page is taken: reserve in 1 MiB pieces, and the
       pieces that fail page by page */
    uint32_t missed = 0;
    uint32_t page = (uint32_t) sysconf(_SC_PAGESIZE);
    for (uint32_t a = base; a < base + size; a += 0x100000u) {
        uint32_t n = base + size - a < 0x100000u ? base + size - a : 0x100000u;
        int flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE | MAP_NORESERVE;
        if (mmap((void *) (uintptr_t) a, n, PROT_NONE, flags, -1, 0) == (void *) (uintptr_t) a) {
            continue;
        }
        for (uint32_t b = a; b < a + n; b += page) {
            if (mmap((void *) (uintptr_t) b, page, PROT_NONE, flags, -1, 0) != (void *) (uintptr_t) b) {
                missed += page;
            }
        }
    }
    return missed;
}

#endif
