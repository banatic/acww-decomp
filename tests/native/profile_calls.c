/* Exercise the production object rewriter and generated i386 wrappers. */
#include <stdint.h>

typedef struct Triple {
    uint32_t a, b, c;
} Triple;

#ifdef PROFILE_BODIES
uint32_t probe_args(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    return a + b * 3 + c * 5 + d * 7 + e * 11 + f * 13;
}

uint64_t probe_wide(uint32_t a, uint32_t b)
{
    return ((uint64_t) a << 32) | b;
}

__attribute__((naked)) void probe_void(void)
{
    __asm__("movl $0x12345678, %eax\n\tmovl $0x76543210, %edx\n\tret");
}

signed char probe_signed(int x)
{
    return x;
}
unsigned short probe_unsigned(int x)
{
    return x;
}
double probe_double(double x)
{
    return x + 0.25;
}

Triple probe_struct(uint32_t a, uint32_t b)
{
    Triple result = {a, b, a ^ b};
    return result;
}

__attribute__((noinline)) uint32_t probe_recurse(uint32_t n)
{
    return n == 0 ? 7 : n + probe_recurse(n - 1);
}

uint32_t probe_tail_target(uint32_t n)
{
    return n + 19;
}
__attribute__((naked)) uint32_t probe_tail(uint32_t n)
{
#ifdef _WIN32
    __asm__("jmp _probe_tail_target");
#else
    __asm__("jmp probe_tail_target");
#endif
}
#else
#include "native_guest.h"
#ifdef PROFILE_SIGNAL_CHECK
#include <signal.h>
#include <ucontext.h>
#endif

/* The Native Windows target deliberately has no host C library headers. */
extern void abort(void);
extern int puts(const char *);
extern int fflush(void *);
#define assert(test)                                                                                                          \
    do {                                                                                                                      \
        if (!(test)) {                                                                                                        \
            puts("Failed: " #test);                                                                                           \
            fflush(0);                                                                                                        \
            abort();                                                                                                          \
        }                                                                                                                     \
    } while (0)

uint32_t native_probe_args(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
uint64_t native_probe_wide(uint32_t, uint32_t);
/* Observe meaningful registers even though the matching definition is void. */
uint64_t native_probe_void(void);
int native_probe_signed(int);
unsigned native_probe_unsigned(int);
double native_probe_double(double);
Triple native_probe_struct(uint32_t, uint32_t);
uint32_t native_probe_recurse(uint32_t);
uint32_t native_probe_tail(uint32_t);

static struct Frame {
    uint32_t index;
    uintptr_t caller;
} frames[32];
static unsigned depth, peak, entries, exits, calls[10];

#ifdef PROFILE_SIGNAL_CHECK
static volatile sig_atomic_t signals;

static void interrupted(int signal_number, siginfo_t *info, void *context)
{
    (void) signal_number;
    (void) info;
    ucontext_t *uc = context;
    uintptr_t sp = uc->uc_mcontext.gregs[REG_ESP];
    /* The test traps immediately before each tracked return. Storage below
       this SP is expired on i386; a resumed signal must not lose the PC there. */
    *(volatile uint32_t *) (sp - 20) = 0xdeadbeef;
    ++signals;
}
#endif

static void enter(uint32_t index, uintptr_t caller, const uint32_t *args)
{
    assert(index < 10 && depth < 32 && caller != 0);
    if (index == 0) {
        for (unsigned i = 0; i < 6; ++i) {
            assert(args[i] == i + 1);
        }
    }
    frames[depth].index = index;
    frames[depth++].caller = caller;
    if (depth > peak) {
        peak = depth;
    }
    ++entries;
    ++calls[index];
    __asm__ volatile("movl $0xdeadbeef, %%eax\n\tmovl $0xabababab, %%ecx\n\tmovl $0xcdcdcdcd, %%edx"
                     :
                     :
                     : "eax", "ecx", "edx");
}

__attribute__((target("general-regs-only"))) static uintptr_t leave(uint32_t index)
{
    assert(depth > 0 && frames[depth - 1].index == index);
    ++exits;
    __asm__ volatile("movl $0xeeeeeeee, %%ecx\n\tmovl $0xdddddddd, %%edx" : : : "ecx", "edx");
    return frames[--depth].caller;
}

static void exercise(void)
{
    volatile uint32_t canary[4] = {0x12345678, 0xabcdef01, 0x87654321, 0x10fedcba};
    assert(native_probe_args(1, 2, 3, 4, 5, 6) == 183);
    assert(native_probe_wide(0xaabbccdd, 0x11223344) == 0xaabbccdd11223344ULL);
    assert(native_probe_void() == 0x7654321012345678ULL);
    assert(native_probe_signed(0x80) == -128);
    assert(native_probe_unsigned(0x1234fedc) == 0xfedc);
    assert(native_probe_double(3.5) == 3.75);
    Triple triple = native_probe_struct(0x11223344, 0x55667788);
    assert(triple.a == 0x11223344 && triple.b == 0x55667788 && triple.c == 0x444444cc);
    assert(native_probe_recurse(6) == 28);
    assert(native_probe_tail(23) == 42);
    assert(canary[0] == 0x12345678 && canary[1] == 0xabcdef01);
    assert(canary[2] == 0x87654321 && canary[3] == 0x10fedcba);
}

int main(void)
{
#ifdef PROFILE_SIGNAL_CHECK
    struct sigaction action = {0};
    action.sa_sigaction = interrupted;
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    assert(sigaction(SIGTRAP, &action, 0) == 0);
#endif
    exercise();
    assert(entries == 0 && exits == 0);
    native_guest_return_hook = leave;
    native_guest_enter_hook = enter;
    for (unsigned i = 0; i < 1000; ++i) {
        exercise();
        assert(depth == 0);
    }
    assert(peak == 7 && entries == 16000 && exits == entries);
#ifdef PROFILE_SIGNAL_CHECK
    assert(signals == 16000);
#endif
    for (unsigned i = 0; i < 10; ++i) {
        assert(calls[i] == (i == 7 ? 7000 : 1000));
    }
    native_guest_enter_hook = 0;
    native_guest_return_hook = 0;
    exercise();
    puts("Native wrappers preserve arguments, integer/x87/aggregate results, recursion and tail returns");
    return 0;
}
#endif
