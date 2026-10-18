/* Actual ARM caller versus its PC copy. Callback bodies are controlled so every
 * argument, hidden output, this adjustment and branch can be checked separately. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arm.h"
#include "memory.h"
#include "native_os.h"
#include "member_pair_rom.h"

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "Failed %d: %s\n", __LINE__, #x); exit(2); } } while (0)
extern void func_02013948(void *, void *, unsigned, int, int);
uint32_t native_pop_bytes, native_return_floating;
static uint32_t object, argument, number, expected_this, target, first, second;
static unsigned event_count, faults, callbacks;
static uint32_t events[4][3];

static void event(uint32_t kind, uint32_t a, uint32_t b)
{
    CHECK(event_count < 4);
    events[event_count][0] = kind;
    events[event_count][1] = a;
    events[event_count++][2] = b;
}
void func_020139bc(void *self)
{
    CHECK((uintptr_t) self == object);
    event(1, object, 0);
}
void func_02012e58(void *self, void *arg)
{
    CHECK((uintptr_t) self == object && (uintptr_t) arg == argument);
    event(3, object, argument);
}
static void callback(uint32_t *out, void *self, void *arg, int n)
{
    CHECK(out != NULL && (uintptr_t) self == expected_this);
    CHECK((uintptr_t) arg == argument && (uint32_t) n == number);
    out[0] = first;
    out[1] = second;
    event(2, target, expected_this);
    callbacks++;
}
uintptr_t native_fault_execute(uint32_t address, uint32_t *eax, uint32_t ecx)
{
    (void) eax;
    (void) ecx;
    CHECK(address == target);
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
    if (address == 0x020139bc) {
        func_020139bc((void *) (uintptr_t) cpu->r[0]);
    } else if (address == 0x02012e58) {
        func_02012e58((void *) (uintptr_t) cpu->r[0], (void *) (uintptr_t) cpu->r[1]);
    } else {
        CHECK(address == (target & ~1u));
        callback((uint32_t *) (uintptr_t) cpu->r[0], (void *) (uintptr_t) cpu->r[1],
                 (void *) (uintptr_t) cpu->r[2], (int) cpu->r[3]);
        /* The caller must use the pointed-to result, never these registers. */
        cpu->r[0] = 0xdeadbeef;
        cpu->r[1] = 0xcafebabe;
    }
    cpu->r[15] = cpu->r[14] & ~1u;
    if (cpu->r[14] & 1) cpu->cpsr |= ARM_CPSR_T;
    else cpu->cpsr &= ~ARM_CPSR_T;
    return 0;
}
static ArmHook hooks(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    *hook_user = (void *) (uintptr_t) address;
    return address == 0x020139bc || address == 0x02012e58 || address == (target & ~1u) ? helper : NULL;
}

int main(void)
{
    CHECK(memory_init() == 0 && native_os_init() == 0);
    memcpy((void *) (uintptr_t) 0x02013948, member_pair_rom, sizeof(member_pair_rom));
    const int offsets[] = {-32, -16, 0, 16, 32};
    unsigned cases = 0, calls = 0;
    object = 0x023c0080;
    argument = 0x023d1000;
    uint32_t *table = (uint32_t *) (uintptr_t) 0x021c1914;
    uint8_t initial[512], expected[512];
    for (unsigned repeat = 0; repeat < 16; repeat++) {
        for (unsigned index = 0; index < 9; index++) {
            for (unsigned offset_index = 0; offset_index < 5; offset_index++) {
                for (unsigned kind = 0; kind < 6; kind++) {
                    int offset = offsets[offset_index];
                    expected_this = object + (uint32_t) offset;
                    target = kind == 3 || kind == 5 ? 0x02012340 : member_pair_targets[index % 7];
                    number = 0x80000000u ^ (repeat * 0x12345u + index);
                    first = 0x81230000u + repeat * 64 + index;
                    second = 0x76540000u - repeat * 32 - index;
                    memset((void *) (uintptr_t) (object - 128), 0xa5, sizeof(initial));
                    memset(table, 0x5a, 7 * 0x40);
                    unsigned slot = (index % 7) * 16 + 2;
                    int virtual_call = kind == 1 || kind >= 4;
                    uint32_t state = virtual_call && offset == 0 ? 0x023e0000 : 0x12345678;
                    table[slot] = kind <= 1 ? 0 : kind >= 4 ? 4 : target;
                    table[slot + 1] = (uint32_t) (offset * 2) | (uint32_t) virtual_call;
                    if (virtual_call) {
                        *(uint32_t *) (uintptr_t) expected_this = 0x023e0000;
                        *(uint32_t *) (uintptr_t) 0x023e0000 = target;
                        *(uint32_t *) (uintptr_t) 0x023e0004 = target;
                    }
                    memcpy(initial, (void *) (uintptr_t) (object - 128), sizeof(initial));
                    ArmCpu cpu;
                    arm_init(&cpu);
                    cpu.hook_at = hooks;
                    cpu.r[0] = object;
                    cpu.r[1] = argument;
                    cpu.r[2] = index;
                    cpu.r[3] = state;
                    cpu.r[13] = 0x023f0000;
                    *(uint32_t *) (uintptr_t) cpu.r[13] = number;
                    for (unsigned reg = 4; reg <= 11; reg++) cpu.r[reg] = 0x55550000 + reg;
                    event_count = 0;
                    CHECK(arm_call(&cpu, 0x02013949, 1000) == ARM_RETURNED);
                    CHECK(cpu.r[13] == 0x023f0000);
                    for (unsigned reg = 4; reg <= 11; reg++) CHECK(cpu.r[reg] == 0x55550000 + reg);
                    memcpy(expected, (void *) (uintptr_t) (object - 128), sizeof(expected));
                    unsigned expected_events = event_count;
                    uint32_t expected_log[4][3];
                    memcpy(expected_log, events, sizeof(events));
                    memcpy((void *) (uintptr_t) (object - 128), initial, sizeof(initial));
                    event_count = 0;
                    func_02013948((void *) (uintptr_t) object, (void *) (uintptr_t) argument,
                                  index, (int) state, (int) number);
                    CHECK(memcmp(expected, (void *) (uintptr_t) (object - 128), sizeof(expected)) == 0);
                    CHECK(event_count == expected_events);
                    CHECK(memcmp(events, expected_log, event_count * sizeof(events[0])) == 0);
                    calls += index < 7 && kind >= 2;
                    cases++;
                }
            }
        }
    }
    CHECK(cases == 4320 && calls == 2240 && faults == calls && callbacks == 2 * calls);
    puts("4320 actual ARM/PC Pair caller cases agree; 2240 DS callback faults; hidden output first, adjusted this second, stack argument, signed results, seven table targets, null, virtual and invalid indices");
    return 0;
}
