/* Actual ARM dispatch owners; source zeros differ from the ROM's table keys. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arm.h"
#include "memory.h"
#include "native_os.h"
#include "keyed_rom.h"
#define CHECK(x)                                                                                                              \
    do {                                                                                                                      \
        if (!(x)) {                                                                                                           \
            fprintf(stderr, "Failed %d: %s\n", __LINE__, #x);                                                                 \
            exit(2);                                                                                                          \
        }                                                                                                                     \
    } while (0)
#define SELF 0x023c0000u
#define HANDLE 0x023d0000u
extern void keyed_invoke(void *);
uint32_t native_pop_bytes, native_return_floating;
static uint32_t events[64][3], callback_target;
static unsigned count, faults;
static int number, mutate;
static void event(unsigned kind, uint32_t a, uint32_t b)
{
    CHECK(count < 64);
    events[count][0] = kind;
    events[count][1] = a;
    events[count++][2] = b;
}
unsigned func_0206837c(unsigned handle)
{
    CHECK(handle == HANDLE);
    event(1, handle, 0);
    return handle;
}
int func_020ab504(unsigned handle)
{
    CHECK(handle == HANDLE);
    event(2, handle, (uint32_t) number);
    return number;
}
static void callback(void *object, int argument)
{
    CHECK((uintptr_t) object == SELF);
    event(3, callback_target, HAS_ARGUMENT ? (uint32_t) argument : 0);
    *(uint32_t *) (uintptr_t) (SELF + 0x10) ^= callback_target;
    if (mutate) {
        unsigned current = 0;
        while (current < KEY_COUNT && keys[current] != *(uint8_t *) (uintptr_t) (SELF + 0x1e)) {
            current++;
        }
        *(uint8_t *) (uintptr_t) (SELF + 0x1e) = (uint8_t) keys[(current + 1) % KEY_COUNT];
    }
}
uintptr_t native_fault_execute(uint32_t at, uint32_t *eax, uint32_t ecx)
{
    (void) eax;
    (void) ecx;
    CHECK(at >= MODULE_BASE && at < MODULE_BASE + sizeof(module_rom));
    callback_target = at;
    faults++;
    return (uintptr_t) callback;
}
int native_fault_is_ds(uint32_t at)
{
    return at >= 0x01000000u && at < 0x10000000u;
}
int native_fault_data(uint32_t eip, uint32_t at, uint32_t esp)
{
    fprintf(stderr, "Unexpected data fault %08x/%08x/%08x\n", eip, at, esp);
    exit(2);
}
int native_fault_divide(uint32_t eip)
{
    (void) eip;
    CHECK(0);
    return 0;
}
void native_watch_hit(uint32_t eip)
{
    (void) eip;
    CHECK(0);
}
int __cxa_guard_acquire(uint64_t *p)
{
    return (*p & 1) == 0;
}
void __cxa_guard_release(uint64_t *p)
{
    *p |= 1;
}
static int helper(ArmCpu *cpu, void *user)
{
    uint32_t at = (uint32_t) (uintptr_t) user;
    if (at == 0x0206837c) {
        cpu->r[0] = func_0206837c(cpu->r[0]);
    } else if (at == 0x020ab504) {
        cpu->r[0] = (uint32_t) func_020ab504(cpu->r[0]);
    } else {
        callback_target = at | 1u;
        callback((void *) (uintptr_t) cpu->r[0], (int) cpu->r[1]);
    }
    cpu->r[15] = cpu->r[14] & ~1u;
    if (cpu->r[14] & 1) {
        cpu->cpsr |= ARM_CPSR_T;
    } else {
        cpu->cpsr &= ~ARM_CPSR_T;
    }
    return 0;
}
static ArmHook hooks(void *user, uint32_t at, void **hook_user)
{
    (void) user;
    *hook_user = (void *) (uintptr_t) at;
    return at >= OWNER && at < OWNER + OWNER_SIZE ? NULL : helper;
}
int main(void)
{
    CHECK(memory_init() == 0 && native_os_init() == 0);
    unsigned cases = 0, expected_faults = 0;
    const int arguments[] = {0, 3, -1, (int) 0x80000001u};
    for (unsigned mode = 0; mode < 256; mode++) {
        for (unsigned a = 0; a < 4; a++) {
            for (mutate = 0; mutate < 2; mutate++) {
                memcpy((void *) (uintptr_t) MODULE_BASE, module_rom, sizeof(module_rom));
                memset((void *) (uintptr_t) (MODULE_BASE + sizeof(module_rom)), 0, MODULE_BSS);
                memset((void *) (uintptr_t) SELF, 0xa5, 0x80);
                *(uint8_t *) (uintptr_t) (SELF + 0x1e) = (uint8_t) mode;
                *(uint32_t *) (uintptr_t) (SELF + 0x40) = HANDLE;
                uint8_t initial[0x80], expected[0x80];
                memcpy(initial, (void *) (uintptr_t) SELF, sizeof(initial));
                number = arguments[a];
                count = 0;
                ArmCpu cpu;
                arm_init(&cpu);
                cpu.hook_at = hooks;
                cpu.r[0] = SELF;
                cpu.r[1] = 0;
                cpu.r[13] = 0x023f0000;
                for (unsigned r = 4; r <= 11; r++) {
                    cpu.r[r] = 0x55550000 + r;
                }
                CHECK(arm_call(&cpu, OWNER | 1u, 20000) == ARM_RETURNED);
                CHECK(cpu.r[13] == 0x023f0000);
                for (unsigned r = 4; r <= 11; r++) {
                    CHECK(cpu.r[r] == 0x55550000 + r);
                }
                uint32_t expected_events[64][3];
                unsigned expected_count = count;
                memcpy(expected_events, events, sizeof(events));
                for (unsigned i = 0; i < count; i++) {
                    expected_faults += events[i][0] == 3;
                }
                memcpy(expected, (void *) (uintptr_t) SELF, sizeof(expected));
                memcpy((void *) (uintptr_t) SELF, initial, sizeof(initial));
                count = 0;
                keyed_invoke((void *) (uintptr_t) SELF);
                CHECK(count == expected_count && memcmp(events, expected_events, count * sizeof(events[0])) == 0);
                CHECK(memcmp(expected, (void *) (uintptr_t) SELF, sizeof(expected)) == 0);
                cases++;
            }
        }
    }
    CHECK(cases == 2048 && faults == expected_faults && faults > 0);
    printf("%u actual ARM/PC keyed-table cases agree in ov%d; %u callback faults; all byte modes, signed arguments, callback "
           "mode changes, object memory and call order\n",
           cases, CASE_ID, faults);
    return 0;
}
