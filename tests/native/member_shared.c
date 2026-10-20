/* Actual ROM owners versus PC copies of aliased or retained DS tables. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arm.h"
#include "memory.h"
#include "native_os.h"
#include "shared_rom.h"
#define CHECK(x)                                                                                                              \
    do {                                                                                                                      \
        if (!(x)) {                                                                                                           \
            fprintf(stderr, "Failed %d: %s\n", __LINE__, #x);                                                                 \
            exit(2);                                                                                                          \
        }                                                                                                                     \
    } while (0)
#define SELF 0x023c0000u
#define HANDLE 0x023d0000u
#define CHILD 0x023d1000u
extern void shared_invoke(void *, unsigned);
uint32_t native_pop_bytes, native_return_floating;
static unsigned count, faults, callback_target, number, page;
static int b, c;
static uint32_t events[16][3];
static void event(unsigned kind, uint32_t a, uint32_t v)
{
    CHECK(count < 16);
    events[count][0] = kind;
    events[count][1] = a;
    events[count++][2] = v;
}
void *func_020160b4(void *p)
{
    CHECK((uintptr_t) p == SELF);
    event(1, SELF, 0);
    return (void *) (uintptr_t) HANDLE;
}
void *func_020682e0(int n)
{
    CHECK(n == 0);
    event(1, 0, 0);
    return (void *) (uintptr_t) HANDLE;
}
void *func_0206837c(void *p)
{
    CHECK((uintptr_t) p == HANDLE);
    event(2, HANDLE, 0);
    return p;
}
int func_020ab504(void *p)
{
    CHECK((uintptr_t) p == HANDLE);
    event(3, HANDLE, number);
    return (int) number;
}
int func_02098880(void *p)
{
    CHECK((uintptr_t) p == 0x021dc7bc);
    event(4, 0x021dc7bc, (uint32_t) b);
    return b;
}
int func_0209f180(void *p)
{
    CHECK((uintptr_t) p == 0x021dc7a8);
    event(5, 0x021dc7a8, (uint32_t) c);
    return c;
}
void func_0206844c(void *p, uint8_t *flag, int n)
{
    CHECK((uintptr_t) p == HANDLE && (uintptr_t) flag == 0x021f43e8 && n == 0);
    event(6, HANDLE, 0);
    *flag = 0x37;
}
void func_ov147_02299fc8(void *p, int n)
{
    CHECK((uintptr_t) p == CHILD);
    event(7, CHILD, (uint32_t) n);
}
void func_ov147_02299374(void *p)
{
    CHECK((uintptr_t) p == SELF);
    event(8, SELF, 0);
}
/* Returns its object, as the ROM's r0 is left: the int-returning ov009 members are tested. */
static uintptr_t callback(void *p)
{
    CHECK((uintptr_t) p == SELF);
    event(9, callback_target, SELF);
    *(uint32_t *) (uintptr_t) (SELF + 0x10) ^= callback_target;
    return (uintptr_t) p;
}
int func_020b30e8(unsigned short a, unsigned int b)
{
    event(10, a, b);
    return (int) (number & 1);
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
/* Only used to demonstrate the uncorrected source's missing DS writes. */
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
    void *p = (void *) (uintptr_t) cpu->r[0];
    switch (at) {
        case 0x020160b4:
            cpu->r[0] = (uint32_t) (uintptr_t) func_020160b4(p);
            break;
        case 0x020682e0:
            cpu->r[0] = (uint32_t) (uintptr_t) func_020682e0((int) cpu->r[0]);
            break;
        case 0x0206837c:
            cpu->r[0] = (uint32_t) (uintptr_t) func_0206837c(p);
            break;
        case 0x020ab504:
            cpu->r[0] = (uint32_t) func_020ab504(p);
            break;
        case 0x02098880:
            cpu->r[0] = (uint32_t) func_02098880(p);
            break;
        case 0x0209f180:
            cpu->r[0] = (uint32_t) func_0209f180(p);
            break;
        case 0x0206844c:
            func_0206844c(p, (uint8_t *) (uintptr_t) cpu->r[1], (int) cpu->r[2]);
            break;
        case 0x02299fc8:
            func_ov147_02299fc8(p, (int) cpu->r[1]);
            break;
        case 0x02299374:
            func_ov147_02299374(p);
            break;
        case 0x020b30e8:
            cpu->r[0] = (uint32_t) func_020b30e8((unsigned short) cpu->r[0], cpu->r[1]);
            break;
        default:
            callback_target = at | 1u;
            callback(p);
            break;
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
    if (at >= OWNER && at < OWNER + OWNER_SIZE) {
        return NULL;
    }
    return helper;
}
int main(void)
{
    CHECK(memory_init() == 0 && native_os_init() == 0);
    memcpy((void *) (uintptr_t) MODULE_BASE, module_rom, sizeof(module_rom));
    const uint32_t guards[] = {0, 2, 0x80000000u, 1, 0x80000001u, 0xffffffffu};
    unsigned cases = 0, expected_faults = 0;
    for (unsigned repeat = 0; repeat < 4; repeat++) {
        for (unsigned g = 0; g < 6; g++) {
            for (page = 0; page < PAGES; page++) {
                for (number = 0; number < 6; number++) {
                    uint8_t initial_storage[STORAGE_SIZE], expected_storage[STORAGE_SIZE];
                    uint8_t initial_object[0x300], expected_object[0x300];
                    memset((void *) (uintptr_t) STORAGE_BASE, 0x5a, STORAGE_SIZE);
                    memset((void *) (uintptr_t) SELF, 0xa5, sizeof(initial_object));
#if STATE_TABLE
                    *(uint32_t *) (uintptr_t) (SELF + 4) = page;
#elif CASE_ID == 147
                    static const unsigned char states[] = {0x2d, 0x2e, 0x2f, 0x31, 0x30, 0x35, 0, 3, 1};
                    *(uint8_t *) (uintptr_t) (SELF + 0x1e) = states[page];
                    *(uint32_t *) (uintptr_t) (SELF + 0x40) = HANDLE;
                    *(uint32_t *) (uintptr_t) (SELF + 0x48) = CHILD;
                    b = repeat == 0 ? -1 : repeat == 2 ? 4 : 1;
                    c = repeat == 1 ? 0 : 1;
                    unsigned selected = repeat;
                    if (page < 4 && number >= tables[selected].count) {
                        continue;
                    }
#elif defined(STATE_OFFSET)
#if STATE_BYTES == 4
                    *(uint32_t *) (uintptr_t) (SELF + STATE_OFFSET) = page;
#elif STATE_BYTES == 1
                    *(uint8_t *) (uintptr_t) (SELF + STATE_OFFSET) = (uint8_t) page;
#endif
#else
                    *(uint32_t *) (uintptr_t) (SELF + 0xb4) = page;
#endif
                    *(uint8_t *) (uintptr_t) 0x021f43e8 = 0x55;
                    for (unsigned t = 0; t < TABLE_COUNT; t++) {
                        const struct Table *tab = &tables[t];
                        *(uint32_t *) (uintptr_t) tab->guard = guards[(g + t) % 6];
                        for (unsigned i = 0; i < tab->count; i++) {
                            unsigned shifted = (i + repeat) % tab->count;
                            *(uint32_t *) (uintptr_t) (tab->address + i * 8) = tab->words[shifted * 2];
                            *(uint32_t *) (uintptr_t) (tab->address + i * 8 + 4) = tab->words[shifted * 2 + 1];
                        }
                    }
                    memcpy(initial_storage, (void *) (uintptr_t) STORAGE_BASE, STORAGE_SIZE);
                    memcpy(initial_object, (void *) (uintptr_t) SELF, sizeof(initial_object));
                    ArmCpu cpu;
                    arm_init(&cpu);
                    cpu.hook_at = hooks;
                    cpu.r[0] = SELF;
#if defined(STATE_OFFSET) && STATE_BYTES == 0
                    cpu.r[1] = page;
#else
                    cpu.r[1] = 0x80000001;
#endif
                    cpu.r[13] = 0x023f0000;
                    for (unsigned r = 4; r <= 11; r++) {
                        cpu.r[r] = 0x55550000 + r;
                    }
                    count = 0;
                    CHECK(arm_call(&cpu, OWNER | 1u, 2000) == ARM_RETURNED);
                    CHECK(cpu.r[13] == 0x023f0000);
                    for (unsigned r = 4; r <= 11; r++) {
                        CHECK(cpu.r[r] == 0x55550000 + r);
                    }
                    uint32_t expected_events[16][3];
                    unsigned expected_count = count;
                    memcpy(expected_events, events, sizeof(events));
                    for (unsigned i = 0; i < count; i++) {
                        expected_faults += events[i][0] == 9;
                    }
                    uint8_t expected_flag = *(uint8_t *) (uintptr_t) 0x021f43e8;
                    memcpy(expected_storage, (void *) (uintptr_t) STORAGE_BASE, STORAGE_SIZE);
                    memcpy(expected_object, (void *) (uintptr_t) SELF, sizeof(expected_object));
                    memcpy((void *) (uintptr_t) STORAGE_BASE, initial_storage, STORAGE_SIZE);
                    memcpy((void *) (uintptr_t) SELF, initial_object, sizeof(initial_object));
                    *(uint8_t *) (uintptr_t) 0x021f43e8 = 0x55;
                    count = 0;
                    shared_invoke((void *) (uintptr_t) SELF, page);
                    CHECK(memcmp(expected_storage, (void *) (uintptr_t) STORAGE_BASE, STORAGE_SIZE) == 0);
                    CHECK(memcmp(expected_object, (void *) (uintptr_t) SELF, sizeof(expected_object)) == 0);
                    CHECK(expected_flag == *(uint8_t *) (uintptr_t) 0x021f43e8);
                    CHECK(count == expected_count && memcmp(events, expected_events, count * sizeof(events[0])) == 0);
                    for (unsigned t = 0; t < TABLE_COUNT; t++) {
                        CHECK(*(uint32_t *) (uintptr_t) tables[t].guard == (guards[(g + t) % 6] | 1u));
                    }
                    cases++;
                }
            }
        }
    }
    CHECK(cases > 400 && faults == expected_faults && faults > 100);
    printf("%u actual ROM/PC shared-storage cases agree in ov%d; %u callback faults; every table, mixed guards, high bits, "
           "repeated initialization, object memory and call order\n",
           cases, CASE_ID, faults);
    return 0;
}
