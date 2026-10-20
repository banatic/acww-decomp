/* A ROM owner of block-scope statics against its PC copy (tools/test_native_statics.py).
 *
 * Both run from the same memory: the owner's module image at its address, an object of zeros
 * whose first word points at a table of method addresses (for virtual members). Every call out
 * returns 0 and is recorded. The sequence loads the overlay (its .bss statics and guards zero,
 * its .data statics the image's), runs the owner twice, loads it again with a guard word whose
 * other bits are set, runs it, and loads it again and runs it: after each run the statics, their
 * guards and the calls must be the ROM's. A PC copy with storage of its own fails at the first
 * reload. Last, the ROM's owner runs and the PC copy runs on after it, as when the two share the
 * overlay's memory: the PC copy must call what the ROM's second run calls.
 *
 *     rom_statics <module.bin> <base> <owner> <size> <thumb> <a1> <a2> <a3> <a4> <address:size:kind>...
 *
 * a1-a3 go in r1-r3 and a4 on the stack (the object is r0); kind is b (.bss), d (.data), g (a
 * guard word in .bss) or i (a library function the PC copy calls on the host, whose ROM code
 * runs in the interpreter, not recorded as a call). An item m=<file>@<base> loads that module's
 * image too (the library function's).
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arm.h"
#include "memory.h"
#include "native_os.h"
#define CHECK(x)                                                                                                              \
    do {                                                                                                                      \
        if (!(x)) {                                                                                                           \
            fprintf(stderr, "Failed %d: %s\n", __LINE__, #x);                                                                 \
            exit(2);                                                                                                          \
        }                                                                                                                     \
    } while (0)
#define SELF 0x023c0000u
#define VTABLE 0x023c8000u
#define SELF_SIZE 0x2000u
#define MAX_CALLS 64
#define MAX_STATICS 8
extern uintptr_t (*const native_owner)(uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t);
uint32_t native_pop_bytes, native_return_floating;
static uint32_t base, owner, owner_size, thumb, args[4], module_size;
#define MAX_LIBRARY 8
static uint32_t library[MAX_LIBRARY][2], libraries;
static uint8_t *image;
static unsigned statics;
static uint32_t at[MAX_STATICS], size[MAX_STATICS];
static char kind[MAX_STATICS];
static uint32_t calls[MAX_CALLS], count;

static void call(uint32_t target)
{
    CHECK(count < MAX_CALLS);
    calls[count++] = target & ~1u;
}
static uintptr_t stub(void)
{
    return 0;
}
uintptr_t native_fault_execute(uint32_t target, uint32_t *eax, uint32_t ecx)
{
    (void) eax;
    (void) ecx;
    call(target);
    return (uintptr_t) stub;
}
int native_fault_is_ds(uint32_t address)
{
    /* a call through a null member pointer (a table the harness left zero) is a call too */
    return address < 0x1000u || (address >= 0x01000000u && address < 0x10000000u);
}
int native_fault_data(uint32_t eip, uint32_t address, uint32_t esp)
{
    fprintf(stderr, "Unexpected data fault %08x/%08x/%08x\n", eip, address, esp);
    exit(3);
}
int native_fault_divide(uint32_t eip)
{
    (void) eip;
    return 0;
}
void native_watch_hit(uint32_t eip)
{
    (void) eip;
    CHECK(0);
}
/* Only the former private copies (the baseline) use the PC's guards. */
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
    call((uint32_t) (uintptr_t) user);
    cpu->r[0] = 0;
    cpu->r[15] = cpu->r[14] & ~1u;
    if (cpu->r[14] & 1) {
        cpu->cpsr |= ARM_CPSR_T;
    } else {
        cpu->cpsr &= ~ARM_CPSR_T;
    }
    return 0;
}
static ArmHook hooks(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    *hook_user = (void *) (uintptr_t) address;
    for (unsigned i = 0; i < libraries; i++) {
        if (address >= library[i][0] && address < library[i][0] + library[i][1]) {
            return NULL;
        }
    }
    return address >= owner && address < owner + owner_size ? NULL : helper;
}
/* The overlay loaded again: .bss statics and guards cleared, .data statics the image's. */
static void load(uint32_t guard_bits)
{
    for (unsigned i = 0; i < statics; i++) {
        uint8_t *p = (uint8_t *) (uintptr_t) at[i];
        if (kind[i] == 'd') {
            CHECK(at[i] >= base && at[i] + size[i] <= base + module_size);
            memcpy(p, image + (at[i] - base), size[i]);
        } else {
            memset(p, 0, size[i]);
            if (kind[i] == 'g') {
                *(uint32_t *) p = guard_bits;
            }
        }
    }
}
static void object(void)
{
    memset((void *) (uintptr_t) SELF, 0, SELF_SIZE);
    *(uint32_t *) (uintptr_t) SELF = VTABLE;
    for (unsigned i = 0; i < 0x100; i++) {
        ((uint32_t *) (uintptr_t) VTABLE)[i] = (base + 0x100 + i * 4) | thumb;
    }
}
static void run_rom(void)
{
    ArmCpu cpu;
    arm_init(&cpu);
    cpu.hook_at = hooks;
    cpu.r[0] = SELF;
    cpu.r[1] = args[0];
    cpu.r[2] = args[1];
    cpu.r[3] = args[2];
    cpu.r[13] = 0x023f0000;
    *(uint32_t *) (uintptr_t) 0x023f0000u = args[3];
    for (unsigned r = 4; r <= 11; r++) {
        cpu.r[r] = 0x55550000 + r;
    }
    count = 0;
    object();
    CHECK(arm_call(&cpu, owner | thumb, 100000) == ARM_RETURNED);
    CHECK(cpu.r[13] == 0x023f0000);
    for (unsigned r = 4; r <= 11; r++) {
        CHECK(cpu.r[r] == 0x55550000 + r);
    }
}
static void run_pc(void)
{
    count = 0;
    object();
    native_owner(SELF, args[0], args[1], args[2], args[3]);
}
struct State {
    uint32_t calls[MAX_CALLS], count;
    uint8_t *storage[MAX_STATICS];
};
static void save(struct State *s)
{
    memcpy(s->calls, calls, sizeof(calls));
    s->count = count;
    for (unsigned i = 0; i < statics; i++) {
        s->storage[i] = malloc(size[i]);
        memcpy(s->storage[i], (void *) (uintptr_t) at[i], size[i]);
    }
}
static void compare(const struct State *rom, const char *step)
{
    if (rom->count != count || memcmp(rom->calls, calls, count * sizeof(calls[0]))) {
        fprintf(stderr, "%s: the PC copy made %u calls, the ROM %u:", step, count, rom->count);
        for (unsigned i = 0; i < count || i < rom->count; i++) {
            fprintf(stderr, " %08x/%08x", i < count ? calls[i] : 0, i < rom->count ? rom->calls[i] : 0);
        }
        fprintf(stderr, "\n");
        exit(2);
    }
    for (unsigned i = 0; i < statics; i++) {
        if (memcmp(rom->storage[i], (void *) (uintptr_t) at[i], size[i])) {
            fprintf(stderr, "%s: expected_storage at %08x (%u bytes) differs\n", step, at[i], size[i]);
            exit(2);
        }
    }
}
int main(int argc, char **argv)
{
    CHECK(argc >= 11);
    CHECK(memory_init() == 0 && native_os_init() == 0);
    FILE *f = fopen(argv[1], "rb");
    CHECK(f != NULL);
    fseek(f, 0, SEEK_END);
    module_size = (uint32_t) ftell(f);
    fseek(f, 0, SEEK_SET);
    image = malloc(module_size);
    CHECK(fread(image, 1, module_size, f) == module_size);
    fclose(f);
    base = (uint32_t) strtoul(argv[2], NULL, 16);
    owner = (uint32_t) strtoul(argv[3], NULL, 16);
    owner_size = (uint32_t) strtoul(argv[4], NULL, 0);
    thumb = (uint32_t) strtoul(argv[5], NULL, 0);
    for (unsigned i = 0; i < 4; i++) {
        args[i] = (uint32_t) strtoul(argv[6 + i], NULL, 0);
    }
    for (int i = 10; i < argc; i++) {
        if (strncmp(argv[i], "m=", 2) == 0) {
            continue;
        }
        char *rest;
        uint32_t address = (uint32_t) strtoul(argv[i], &rest, 16);
        CHECK(*rest == ':');
        uint32_t bytes = (uint32_t) strtoul(rest + 1, &rest, 0);
        CHECK(*rest == ':' && (rest[1] == 'b' || rest[1] == 'd' || rest[1] == 'g' || rest[1] == 'i') && !rest[2]);
        if (rest[1] == 'i') {
            CHECK(libraries < MAX_LIBRARY);
            library[libraries][0] = address;
            library[libraries++][1] = bytes;
            continue;
        }
        CHECK(statics < MAX_STATICS);
        at[statics] = address;
        size[statics] = bytes;
        kind[statics++] = rest[1];
    }
    for (int i = 10; i < argc; i++) {
        if (strncmp(argv[i], "m=", 2) == 0) {
            char *at_sign = strrchr(argv[i], '@');
            CHECK(at_sign != NULL);
            *at_sign = 0;
            FILE *m = fopen(argv[i] + 2, "rb");
            CHECK(m != NULL);
            uint32_t where = (uint32_t) strtoul(at_sign + 1, NULL, 16);
            fseek(m, 0, SEEK_END);
            long bytes = ftell(m);
            fseek(m, 0, SEEK_SET);
            CHECK(bytes > 0 && fread((void *) (uintptr_t) where, 1, (size_t) bytes, m) == (size_t) bytes);
            fclose(m);
        }
    }
    memcpy((void *) (uintptr_t) base, image, module_size);
    /* load, run, run; load with other guard bits, run; load, run */
    static const uint32_t loads[4][2] = {{1, 0}, {0, 0}, {1, 0x80000002u}, {1, 0}};
    struct State rom[4];
    for (unsigned step = 0; step < 4; step++) {
        if (loads[step][0]) {
            load(loads[step][1]);
        }
        run_rom();
        save(&rom[step]);
    }
    for (unsigned step = 0; step < 4; step++) {
        if (loads[step][0]) {
            load(loads[step][1]);
        }
        run_pc();
        static const char *names[] = {"first run", "second run", "after a reload with guard bits set", "after a reload"};
        compare(&rom[step], names[step]);
    }
    /* the ROM's owner first, then the PC copy on the same memory */
    load(0);
    run_rom();
    run_pc();
    compare(&rom[1], "after the ROM's run");
    printf("%u calls, %u statics agree over loads, reloads and a ROM run first\n", rom[0].count, statics);
    return 0;
}
