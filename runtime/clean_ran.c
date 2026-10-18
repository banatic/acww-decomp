/* Which Clean functions ran (tools/run.py --clean-ran), however they were entered: from the
 * interpreter, from Native code or from other Clean code. That build compiles the Clean code
 * with -finstrument-functions, so every Clean function calls __cyg_profile_func_enter with its
 * own address on entry; the entry of clean_functions with that host address is marked. At the
 * exit, with RUN_CLEAN_RAN set (the Native run only), every entry is written to that file as
 * "address module 0|1". Linked only into that build; nothing here is instrumented, so the hooks
 * cannot call themselves.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "native_table.h"

#define NO_HOOK __attribute__((no_instrument_function))

static const char *ran_path;
static uint32_t *order; /* indices into clean_functions, by host address */
static uint8_t *ran;    /* by index into clean_functions */

NO_HOOK static uintptr_t host_of(uint32_t i)
{
    return (uintptr_t) clean_functions[i].host;
}

NO_HOOK static int by_host(const void *a, const void *b)
{
    uintptr_t x = host_of(*(const uint32_t *) a), y = host_of(*(const uint32_t *) b);
    return x < y ? -1 : x > y;
}

NO_HOOK static void write_ran(void)
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

NO_HOOK __attribute__((constructor)) static void clean_ran_init(void)
{
    ran_path = getenv("RUN_CLEAN_RAN");
    if (ran_path == NULL || *ran_path == 0 || clean_function_count == 0) {
        return;
    }
    order = malloc(sizeof(*order) * clean_function_count);
    uint8_t *marks = calloc(clean_function_count, 1);
    if (order == NULL || marks == NULL) {
        return;
    }
    for (uint32_t i = 0; i < clean_function_count; i++) {
        order[i] = i;
    }
    qsort(order, clean_function_count, sizeof(*order), by_host);
    ran = marks;
    atexit(write_ran);
}

NO_HOOK void __cyg_profile_func_enter(void *fn, void *site)
{
    (void) site;
    if (ran == NULL) {
        return;
    }
    uintptr_t want = (uintptr_t) fn;
    uint32_t lo = 0, hi = clean_function_count;
    while (lo < hi) {
        uint32_t mid = lo + (hi - lo) / 2;
        if (host_of(order[mid]) < want) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    /* one Clean function may stand for several game functions */
    for (; lo < clean_function_count && host_of(order[lo]) == want; lo++) {
        ran[order[lo]] = 1;
    }
}

NO_HOOK void __cyg_profile_func_exit(void *fn, void *site)
{
    (void) fn;
    (void) site;
}
