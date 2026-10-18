/* The actual ARM caller retains its object pointer in r0 at func_020819bc.
 * Compare its PC copy, including both actual flag-reader bodies. Other calls
 * are controlled to cover every branch and check their arguments and order. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arm.h"
#include "memory.h"
#include "native_os.h"
#include "member_register_rom.h"

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "Failed %d: %s\n", __LINE__, #x); exit(2); } } while (0)
#define SELF 0x023c0000u
#define CHILD 0x023c1000u
#define ITEM 0x023c2000u
#define TARGET 0x02012341u
extern void func_0201f40c(void *, int);
extern int native_flag_body(void *);
uint32_t native_pop_bytes, native_return_floating;
static unsigned scenario, rng, count, faults;
static uint32_t argument, events[16][3];
static void event(uint32_t kind, uint32_t a, uint32_t b)
{
    CHECK(count < 16);
    events[count][0] = kind;
    events[count][1] = a;
    events[count++][2] = b;
}
int func_020644cc(int maximum)
{
    CHECK(maximum == 10 && rng < 2);
    unsigned value = (scenario >> (2 + rng++)) & 1;
    event(1, (uint32_t) maximum, value);
    return (int) value;
}
int func_02020a5c(void *self, int arg)
{
    CHECK((uintptr_t) self == SELF && (uint32_t) arg == argument);
    event(2, SELF, argument);
    return (int) (scenario & 1);
}
void func_0202d8f8(void *self, uint32_t *item, uint32_t *state, void *x, int zero)
{
    CHECK((uintptr_t) self == SELF && (uintptr_t) item == SELF + 0x12c);
    CHECK((uintptr_t) state == SELF + 0x128 && (uintptr_t) x == 0x023d0000 && zero == 0);
    event(3, *item, *state);
    *state ^= 0x76543210;
    if (argument & 1) *item = 0;
}
int func_020819bc(void *item)
{
    CHECK((uintptr_t) item == ITEM);
    int value = native_flag_body(item);
    event(4, ITEM, (uint32_t) value);
    return value;
}
void func_0202da88(void *self, void *table)
{
    CHECK((uintptr_t) self == SELF);
    event(5, SELF, (uint32_t) (uintptr_t) table);
    *(uint32_t *) (uintptr_t) (SELF + 0xe0) = (uint32_t) (uintptr_t) table;
}
int func_0201f550(unsigned short *p) { (void) p; CHECK(0); return 0; }
int func_02099f1c(void *out, int (*predicate)(unsigned short *))
{
    CHECK(predicate == func_0201f550 || (uintptr_t) predicate == 0x0201f551);
    unsigned char value[3] = {0x23, 0x81, 7};
    memcpy(out, value, sizeof(value));
    event(6, 0x0201f551, (scenario >> 4) & 1);
    return (scenario & 16) ? 1 : -1;
}
void func_020819e0(unsigned short *item)
{
    CHECK((uintptr_t) item == ITEM);
    event(7, ITEM, *item);
    *item ^= 0x9876;
}
static void callback(void *self, int arg)
{
    CHECK((uintptr_t) self == SELF && (uint32_t) arg == argument);
    event(8, SELF, argument);
    *(uint32_t *) (uintptr_t) (SELF + 0xf0) ^= argument;
}
uintptr_t native_fault_execute(uint32_t address, uint32_t *eax, uint32_t ecx)
{
    (void) eax; (void) ecx;
    CHECK(address == TARGET);
    faults++;
    return (uintptr_t) callback;
}
int native_fault_is_ds(uint32_t address) { return address >= 0x01000000u && address < 0x10000000u; }
int native_fault_data(uint32_t eip, uint32_t address, uint32_t esp)
{
    fprintf(stderr, "Unexpected data fault %08x at %08x sp %08x\n", address, eip, esp);
    exit(2);
}
int native_fault_divide(uint32_t eip) { (void) eip; CHECK(0); return 0; }
void native_watch_hit(uint32_t eip) { (void) eip; CHECK(0); }
static int helper(ArmCpu *cpu, void *user)
{
    uint32_t address = (uint32_t) (uintptr_t) user;
    switch (address) {
    case 0x020644cc: cpu->r[0] = (uint32_t) func_020644cc((int) cpu->r[0]); break;
    case 0x02020a5c: cpu->r[0] = (uint32_t) func_02020a5c((void *)(uintptr_t)cpu->r[0], (int)cpu->r[1]); break;
    case 0x0202d8f8:
        func_0202d8f8((void *)(uintptr_t)cpu->r[0], (uint32_t *)(uintptr_t)cpu->r[1],
                     (uint32_t *)(uintptr_t)cpu->r[2], (void *)(uintptr_t)cpu->r[3],
                     *(int *)(uintptr_t)cpu->r[13]);
        break;
    case 0x020819bc: {
        CHECK(cpu->r[0] == ITEM);
        ArmCpu leaf;
        arm_init(&leaf);
        leaf.r[0] = cpu->r[0];
        leaf.r[13] = 0x023e0000;
        CHECK(arm_call(&leaf, 0x020819bd, 100) == ARM_RETURNED);
        cpu->r[0] = leaf.r[0];
        event(4, ITEM, leaf.r[0]);
        break;
    }
    case 0x0202da88: func_0202da88((void *)(uintptr_t)cpu->r[0], (void *)(uintptr_t)cpu->r[1]); break;
    case 0x02099f1c:
        cpu->r[0] = (uint32_t) func_02099f1c((void *)(uintptr_t)cpu->r[0],
                                           (int (*)(unsigned short *))(uintptr_t)cpu->r[1]);
        break;
    case 0x020819e0: func_020819e0((unsigned short *)(uintptr_t)cpu->r[0]); break;
    case TARGET & ~1u: callback((void *)(uintptr_t)cpu->r[0], (int)cpu->r[1]); break;
    default: CHECK(0);
    }
    cpu->r[15] = cpu->r[14] & ~1u;
    if (cpu->r[14] & 1) cpu->cpsr |= ARM_CPSR_T;
    else cpu->cpsr &= ~ARM_CPSR_T;
    return 0;
}
static ArmHook hooks(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    *hook_user = (void *)(uintptr_t)address;
    switch (address) {
    case 0x020644cc: case 0x02020a5c: case 0x0202d8f8: case 0x020819bc:
    case 0x0202da88: case 0x02099f1c: case 0x020819e0: case TARGET & ~1u:
        return helper;
    default: return NULL;
    }
}
int main(void)
{
    CHECK(memory_init() == 0 && native_os_init() == 0);
    memcpy((void *)(uintptr_t)0x0201f40c, member_register_rom, sizeof(member_register_rom));
    memcpy((void *)(uintptr_t)0x020819bc, member_flag_rom, sizeof(member_flag_rom));
    const uint32_t arguments[] = {0, 1, 0x80000000, 0xffffffff};
    unsigned cases = 0;
    for (scenario = 0; scenario < 128; scenario++) {
        for (unsigned index = 0; index < 4; index++) {
            uint8_t initial[0x2080], expected[0x2080];
            argument = arguments[index];
            memset((void *)(uintptr_t)SELF, 0xa5, sizeof(initial));
            *(uint32_t *)(uintptr_t)(SELF + 0x100) = CHILD;
            *(uint32_t *)(uintptr_t)(CHILD + 0x830) = 0x023d0000;
            *(uint32_t *)(uintptr_t)(SELF + 0x12c) = (scenario & 2) ? ITEM : 0;
            *(uint32_t *)(uintptr_t)(SELF + 0xb0) = (scenario & 32) ? TARGET : 0;
            *(uint32_t *)(uintptr_t)(SELF + 0xb4) = 0;
            *(uint16_t *)(uintptr_t)(ITEM + 0x7c) = (uint16_t)(0xffbf | ((scenario & 64) ? 64 : 0));
            memcpy(initial, (void *)(uintptr_t)SELF, sizeof(initial));
            ArmCpu cpu;
            arm_init(&cpu);
            cpu.hook_at = hooks;
            cpu.r[0] = SELF;
            cpu.r[1] = argument;
            cpu.r[13] = 0x023f0000;
            for (unsigned reg = 4; reg <= 11; reg++) cpu.r[reg] = 0x55550000 + reg;
            count = rng = 0;
            CHECK(arm_call(&cpu, 0x0201f40d, 1000) == ARM_RETURNED);
            CHECK(cpu.r[13] == 0x023f0000);
            for (unsigned reg = 4; reg <= 11; reg++) CHECK(cpu.r[reg] == 0x55550000 + reg);
            memcpy(expected, (void *)(uintptr_t)SELF, sizeof(expected));
            unsigned expected_count = count;
            uint32_t expected_events[16][3];
            memcpy(expected_events, events, sizeof(events));
            memcpy((void *)(uintptr_t)SELF, initial, sizeof(initial));
            count = rng = 0;
            func_0201f40c((void *)(uintptr_t)SELF, (int)argument);
            CHECK(count == expected_count && memcmp(events, expected_events, count * sizeof(events[0])) == 0);
            CHECK(memcmp(expected, (void *)(uintptr_t)SELF, sizeof(expected)) == 0);
            cases++;
        }
    }
    CHECK(cases == 512 && faults == 128);
    puts("512 actual ARM/PC register-argument caller cases agree; actual flag bodies, 128 callback faults, early return, all table branches, five-argument cleanup, full object memory and call order");
    return 0;
}
