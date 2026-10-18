/* Which Clean functions ran (tools/run.py --clean-ran), however they were entered: from the
 * interpreter, from Native code or from other Clean code. The Clean code is the usual build's,
 * byte for byte: with RUN_CLEAN_RAN set (the Native run only), the first byte of each entry of
 * clean_functions becomes a breakpoint (int3) before main. The first time a function is
 * entered the breakpoint traps; the handler marks the function, puts its byte back and
 * resumes at the entry with every register and flag as they were, so the function then runs
 * its own code as in the usual run, and is not stopped again. Instrumenting the code at
 * compile time changed it: -finstrument-functions passes its hooks' arguments in eax and edx,
 * which Clean functions declared void leave holding the game's r0 for their callers (on Linux
 * gcc's `pop %eax` after the entry hook left the function's own address there, and the run
 * took other paths); -pg -mfentry is refused by 32-bit gcc with -fpie; and gcc allocates
 * registers differently around a function with -fpatchable-function-entry, which changed what
 * void Clean functions leave in eax. An entry the runtime then patches (native_run.c,
 * patch_clean: a Clean function on standby jumps on) is not marked, as it does not run. At the
 * exit every entry is written to that file as "address module 0|1". Linked only into that
 * build.
 */
#ifdef _WIN32
#include <windows.h>
#else
#define _GNU_SOURCE /* REG_EIP */
#include <signal.h>
#include <string.h>
#include <ucontext.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "native_os.h"
#include "native_table.h"

static const char *ran_path;
static uint32_t *order;   /* indices into clean_functions, by host address */
static uint8_t *ran;      /* by index into clean_functions */
static uint8_t *original; /* by position in `order`: the entry's first byte */

static uintptr_t host_of(uint32_t i)
{
    return (uintptr_t) clean_functions[i].host;
}

static int by_host(const void *a, const void *b)
{
    uintptr_t x = host_of(*(const uint32_t *) a), y = host_of(*(const uint32_t *) b);
    return x < y ? -1 : x > y;
}

static void write_ran(void)
{
    FILE *out = fopen(ran_path, "w");
    if (out == NULL) {
        fprintf(stderr, "clean ran: cannot write %s\n", ran_path);
        return;
    }
    uint32_t count = 0;
    for (uint32_t i = 0; i < clean_function_count; i++) {
        fprintf(out, "%08x %s %d\n", clean_functions[i].address & ~1u, native_module(&clean_functions[i]), ran[i]);
        count += ran[i];
    }
    fclose(out);
    printf("native: %u of %u Clean functions ran (%s)\n", count, clean_function_count, ran_path);
    fflush(stdout);
}

/* A breakpoint at `site`: 1 when it is one of ours, then marked, its byte put back. */
static int hit(uintptr_t site)
{
    uint32_t lo = 0, hi = clean_function_count;
    while (lo < hi) {
        uint32_t mid = lo + (hi - lo) / 2;
        if (host_of(order[mid]) < site) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo == clean_function_count || host_of(order[lo]) != site || *(const uint8_t *) site != 0xcc) {
        return 0;
    }
    if (native_os_patch((void *) site, &original[lo], 1) != 0) {
        return 0;
    }
    /* one Clean function may stand for several game functions */
    for (; lo < clean_function_count && host_of(order[lo]) == site; lo++) {
        ran[order[lo]] = 1;
    }
    return 1;
}

#ifdef _WIN32
static LONG CALLBACK on_breakpoint(EXCEPTION_POINTERS *info)
{
    if (info->ExceptionRecord->ExceptionCode != EXCEPTION_BREAKPOINT) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    uintptr_t site = (uintptr_t) info->ExceptionRecord->ExceptionAddress;
    if (!hit(site)) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    info->ContextRecord->Eip = (DWORD) site;
    return EXCEPTION_CONTINUE_EXECUTION;
}

static int install(void)
{
    return AddVectoredExceptionHandler(1, on_breakpoint) != NULL;
}

/* Memory at the top of the address space: before main the heap is still small, and memory it
 * took here could leave it growing into the DS's addresses (the runtime reserves them in main). */
static void *zeroed(size_t size)
{
    return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);
}
#else
static void on_breakpoint(int sig, siginfo_t *info, void *context)
{
    (void) info;
    ucontext_t *uc = context;
    uintptr_t site = (uintptr_t) uc->uc_mcontext.gregs[REG_EIP] - 1; /* past the int3 */
    if (!hit(site)) {
        signal(sig, SIG_DFL);
        raise(sig);
        return;
    }
    uc->uc_mcontext.gregs[REG_EIP] = (greg_t) site;
}

static int install(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = on_breakpoint;
    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    return sigaction(SIGTRAP, &sa, NULL) == 0;
}

static void *zeroed(size_t size)
{
    return calloc(size, 1);
}
#endif

__attribute__((constructor)) static void clean_ran_init(void)
{
    ran_path = getenv("RUN_CLEAN_RAN");
    if (ran_path == NULL || *ran_path == 0 || clean_function_count == 0) {
        return;
    }
    order = zeroed(sizeof(*order) * clean_function_count);
    original = zeroed(clean_function_count);
    uint8_t *marks = zeroed(clean_function_count);
    if (order == NULL || original == NULL || marks == NULL || !install()) {
        fprintf(stderr, "clean ran: cannot set up the breakpoints\n");
        return;
    }
    for (uint32_t i = 0; i < clean_function_count; i++) {
        order[i] = i;
    }
    qsort(order, clean_function_count, sizeof(*order), by_host);
    ran = marks;
    static const uint8_t int3 = 0xcc;
    for (uint32_t i = 0; i < clean_function_count; i++) {
        uintptr_t host = host_of(order[i]);
        original[i] = host != 0 ? *(const uint8_t *) host : 0;
        /* each host once: several entries may share one (the first keeps the byte) */
        if (host == 0 || (i > 0 && host == host_of(order[i - 1]))) {
            continue;
        }
        if (original[i] == int3 || native_os_patch((void *) host, &int3, 1) != 0) {
            fprintf(stderr, "clean ran: cannot place a breakpoint at %08x\n", (uint32_t) host);
        }
    }
    atexit(write_ran);
}
