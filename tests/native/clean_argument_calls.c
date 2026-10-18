/* Public entry hooks must see arguments even when the visible body ignores them. */
#include <stdint.h>
#ifdef PROFILE_BODIES
#define CLEAN_AS(symbol, function)
uint32_t CleanUnused(uint32_t a, uint32_t b)
{
    (void) a;
    return b + 1;
}
CLEAN_AS(probe_unused, CleanUnused)
uint32_t CleanUnusedCaller(uint32_t a, uint32_t b)
{
    return CleanUnused(a, b) ^ 0x13579bdfu;
}
CLEAN_AS(probe_unused_caller, CleanUnusedCaller)
uint32_t CleanUnusedTail(uint32_t a, uint32_t b)
{
    return CleanUnused(a, b);
}
CLEAN_AS(probe_unused_tail, CleanUnusedTail)
#else
#include "native_guest.h"
extern int puts(const char *);
extern void abort(void);
extern uint32_t CleanUnusedCaller(uint32_t, uint32_t);
extern uint32_t CleanUnusedTail(uint32_t, uint32_t);
static uint32_t expected_a, expected_b, mismatch, entries, exits, depth;
static struct { uint32_t index; uintptr_t caller; } frames[4];
static void enter(uint32_t index, uintptr_t caller, const uint32_t *args)
{
    if (index >= 3 || depth >= 4 || !caller) abort();
    if (args[0] != expected_a || args[1] != expected_b) ++mismatch;
    frames[depth].index = index;
    frames[depth++].caller = caller;
    ++entries;
    __asm__ volatile("movl $0xdeadbeef, %%eax\n\tmovl $0xabababab, %%ecx\n\tmovl $0xcdcdcdcd, %%edx"
                     : : : "eax", "ecx", "edx");
}
__attribute__((target("general-regs-only"))) static uintptr_t leave(uint32_t index)
{
    if (!depth || frames[depth-1].index != index) abort();
    ++exits;
    return frames[--depth].caller;
}
int main(void)
{
    native_guest_enter_hook = enter;
    native_guest_return_hook = leave;
    uint32_t (*volatile indirect)(uint32_t, uint32_t) = CleanUnusedCaller;
    for (unsigned i = 0; i < 1024; ++i) {
        expected_a = 0xa5000000u + i;
        expected_b = 0xf0000000u ^ (i * 0x12345u);
        if (indirect(expected_a, expected_b) != ((expected_b+1) ^ 0x13579bdfu)) abort();
        if (CleanUnusedTail(expected_a, expected_b) != expected_b+1 || depth) abort();
    }
    if (entries != 4096 || exits != entries) abort();
    puts(mismatch ? "Clean argument mismatches detected" :
         "4096 observed Clean calls, 0 argument mismatches; ignored arguments, indirect calls and optimized tail returns");
    return mismatch ? 2 : 0;
}
#endif
