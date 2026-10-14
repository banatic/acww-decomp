/* Tests for the ARMv5TE interpreter: hand-assembled instructions in RAM with expected results
 * and flags, then a few of the ROM's own leaf functions with results derived from their sources.
 *
 * Usage: arm_test [rom-directory]   (default build/adm-kr/rom, relative to the repository root)
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arm.h"
#include "memory.h"

/* Scratch areas inside main RAM, past everything the ROM's modules load. */
#define CODE 0x02300000u
#define DATA 0x02310000u
#define STACK_TOP 0x02321000u

#define N ARM_CPSR_N
#define Z ARM_CPSR_Z
#define C ARM_CPSR_C
#define V ARM_CPSR_V
#define Q ARM_CPSR_Q
#define FLAGS (cpu.cpsr & 0xf8000000u)

static ArmCpu cpu;
static int checks, failures;
static const char *current;

static void check(int ok, const char *what)
{
    checks++;
    if (!ok) {
        failures++;
        printf("FAIL %s: %s\n", current, what);
    }
}

static void check_eq(uint32_t got, uint32_t want, const char *what)
{
    checks++;
    if (got != want) {
        failures++;
        printf("FAIL %s: %s = 0x%08x, want 0x%08x\n", current, what, got, want);
    }
}

#define CHECK(x) check((x), #x)
#define CHECK_EQ(a, b) check_eq((uint32_t) (a), (uint32_t) (b), #a)

static uint32_t *word(uint32_t address)
{
    return (uint32_t *) memory_host(address, 4);
}

static uint16_t *half(uint32_t address)
{
    return (uint16_t *) memory_host(address, 2);
}

static uint8_t *byte(uint32_t address)
{
    return memory_host(address, 1);
}

static void begin(const char *name)
{
    current = name;
    arm_init(&cpu);
    cpu.r[13] = STACK_TOP;
    memset(memory_host(DATA, 0x100), 0, 0x100);
}

/* Run ARM code placed at CODE and ended with "bx lr". */
static enum ArmStop run_arm(const uint32_t *code, size_t count)
{
    memcpy(memory_host(CODE, 0x100), code, count * 4);
    *word(CODE + count * 4) = 0xe12fff1eu;
    return arm_call(&cpu, CODE, 10000);
}

/* Run Thumb code placed at CODE and ended with "bx lr". */
static enum ArmStop run_thumb(const uint16_t *code, size_t count)
{
    memcpy(memory_host(CODE, 0x100), code, count * 2);
    *half(CODE + count * 2) = 0x4770u;
    return arm_call(&cpu, CODE | 1, 10000);
}

#define ARM(...) run_arm((const uint32_t[]){__VA_ARGS__}, sizeof((const uint32_t[]){__VA_ARGS__}) / 4)
#define THUMB(...) run_thumb((const uint16_t[]){__VA_ARGS__}, sizeof((const uint16_t[]){__VA_ARGS__}) / 2)

/* The 12-bit immediate field encoding `value`, which must be expressible. */
static uint32_t arm_imm(uint32_t value)
{
    for (uint32_t rot = 0; rot < 16; rot++) {
        uint32_t left = rot * 2;
        uint32_t rotated = left ? (value << left) | (value >> (32 - left)) : value;
        if (rotated < 256) {
            return (rot << 8) | rotated;
        }
    }
    printf("cannot encode 0x%08x\n", value);
    exit(2);
}

/* ARM data processing ------------------------------------------------------------------- */

static void test_arm_immediates(void)
{
    begin("movs immediate");
    ARM(0xe3b00000u); /* movs r0, #0 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z);

    begin("movs immediate rotated sets C from bit 31");
    ARM(0xe3b004ffu); /* movs r0, #0xff000000 */
    CHECK_EQ(cpu.r[0], 0xff000000u);
    CHECK_EQ(FLAGS, N | C);

    begin("movs immediate rotated clears C");
    cpu.cpsr |= C;
    ARM(0xe3b00fffu); /* movs r0, #0x3fc */
    CHECK_EQ(cpu.r[0], 0x3fc);
    CHECK_EQ(FLAGS, 0);

    begin("movs immediate unrotated keeps C");
    cpu.cpsr |= C;
    ARM(0xe3b00001u); /* movs r0, #1 */
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(FLAGS, C);

    begin("mvn and bic");
    cpu.r[1] = 0xf0f0f0f0u;
    ARM(0xe1e00001u,  /* mvn r0, r1 */
        0xe3c22a0fu); /* bic r2, r2, #0xf000 */
    CHECK_EQ(cpu.r[0], 0x0f0f0f0fu);
}

static void test_arm_shifter(void)
{
    begin("lsl #4 carry out");
    cpu.r[1] = 0x90000000u;
    ARM(0xe1b00201u); /* movs r0, r1, lsl #4 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z | C);

    begin("lsl #0 keeps C");
    cpu.r[1] = 5;
    cpu.cpsr |= C;
    ARM(0xe1b00001u); /* movs r0, r1 */
    CHECK_EQ(cpu.r[0], 5);
    CHECK_EQ(FLAGS, C);

    begin("lsr #32");
    cpu.r[1] = 0x80000000u;
    ARM(0xe1b00021u); /* movs r0, r1, lsr #32 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z | C);

    begin("lsr #1");
    cpu.r[1] = 3;
    ARM(0xe1b000a1u); /* movs r0, r1, lsr #1 */
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(FLAGS, C);

    begin("asr #32");
    cpu.r[1] = 0x80000000u;
    ARM(0xe1b00041u); /* movs r0, r1, asr #32 */
    CHECK_EQ(cpu.r[0], 0xffffffffu);
    CHECK_EQ(FLAGS, N | C);

    begin("asr #3");
    cpu.r[1] = 0xfffffff4u;
    ARM(0xe1b001c1u); /* movs r0, r1, asr #3 */
    CHECK_EQ(cpu.r[0], 0xfffffffeu);
    CHECK_EQ(FLAGS, N | C);

    begin("rrx");
    cpu.r[1] = 3;
    cpu.cpsr |= C;
    ARM(0xe1b00061u); /* movs r0, r1, rrx */
    CHECK_EQ(cpu.r[0], 0x80000001u);
    CHECK_EQ(FLAGS, N | C);

    begin("rrx with C clear");
    cpu.r[1] = 2;
    ARM(0xe1b00061u);
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(FLAGS, 0);

    begin("ror #4");
    cpu.r[1] = 0x12345678u;
    ARM(0xe1b00261u); /* movs r0, r1, ror #4 */
    CHECK_EQ(cpu.r[0], 0x81234567u);
    CHECK_EQ(FLAGS, N | C);

    /* register-specified shift amounts: 0, below 32, 32, above 32, and only the low byte */
    begin("lsl by register 0 keeps C");
    cpu.r[1] = 0x80000001u;
    cpu.r[2] = 0;
    cpu.cpsr |= C;
    ARM(0xe1b00211u); /* movs r0, r1, lsl r2 */
    CHECK_EQ(cpu.r[0], 0x80000001u);
    CHECK_EQ(FLAGS, N | C);

    begin("lsl by register 32");
    cpu.r[1] = 0x80000001u;
    cpu.r[2] = 32;
    ARM(0xe1b00211u);
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z | C);

    begin("lsl by register 33");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 33;
    cpu.cpsr |= C;
    ARM(0xe1b00211u);
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z);

    begin("lsl by register uses the low byte only");
    cpu.r[1] = 1;
    cpu.r[2] = 0x100;
    ARM(0xe1b00211u);
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(FLAGS, 0);

    begin("lsl by register 31");
    cpu.r[1] = 3;
    cpu.r[2] = 31;
    ARM(0xe1b00211u);
    CHECK_EQ(cpu.r[0], 0x80000000u);
    CHECK_EQ(FLAGS, N | C);

    begin("lsr by register 32");
    cpu.r[1] = 0x80000000u;
    cpu.r[2] = 32;
    ARM(0xe1b00231u); /* movs r0, r1, lsr r2 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z | C);

    begin("lsr by register 40");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 40;
    cpu.cpsr |= C;
    ARM(0xe1b00231u);
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z);

    begin("asr by register 40");
    cpu.r[1] = 0x80000000u;
    cpu.r[2] = 40;
    ARM(0xe1b00251u); /* movs r0, r1, asr r2 */
    CHECK_EQ(cpu.r[0], 0xffffffffu);
    CHECK_EQ(FLAGS, N | C);

    begin("asr by register 40 positive");
    cpu.r[1] = 0x7fffffffu;
    cpu.r[2] = 40;
    cpu.cpsr |= C;
    ARM(0xe1b00251u);
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z);

    begin("ror by register 32");
    cpu.r[1] = 0x80000001u;
    cpu.r[2] = 32;
    ARM(0xe1b00271u); /* movs r0, r1, ror r2 */
    CHECK_EQ(cpu.r[0], 0x80000001u);
    CHECK_EQ(FLAGS, N | C);

    begin("ror by register 36");
    cpu.r[1] = 0x12345678u;
    cpu.r[2] = 36;
    ARM(0xe1b00271u);
    CHECK_EQ(cpu.r[0], 0x81234567u);
    CHECK_EQ(FLAGS, N | C);

    begin("ror by register 0 keeps C");
    cpu.r[1] = 0x12345678u;
    cpu.r[2] = 0;
    cpu.cpsr |= C;
    ARM(0xe1b00271u);
    CHECK_EQ(cpu.r[0], 0x12345678u);
    CHECK_EQ(FLAGS, C);

    begin("ands with shifted operand carry");
    cpu.r[1] = 1;
    cpu.r[2] = 3;
    ARM(0xe01100a2u); /* ands r0, r1, r2, lsr #1 */
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(FLAGS, C);

    begin("r15 reads as the instruction address + 8");
    ARM(0xe1a0000fu,  /* mov r0, pc */
        0xe08f1001u); /* add r1, pc, r1 */
    CHECK_EQ(cpu.r[0], CODE + 8);
    CHECK_EQ(cpu.r[1], CODE + 4 + 8);
}

static void test_arm_arithmetic_flags(void)
{
    begin("adds overflow");
    cpu.r[1] = 0x7fffffffu;
    cpu.r[2] = 1;
    ARM(0xe0910002u); /* adds r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0x80000000u);
    CHECK_EQ(FLAGS, N | V);

    begin("adds carry");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 1;
    ARM(0xe0910002u);
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z | C);

    begin("adcs");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 0;
    cpu.cpsr |= C;
    ARM(0xe0b10002u); /* adcs r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(FLAGS, Z | C);

    begin("subs borrow");
    cpu.r[1] = 0;
    cpu.r[2] = 1;
    ARM(0xe0510002u); /* subs r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0xffffffffu);
    CHECK_EQ(FLAGS, N);

    begin("subs overflow");
    cpu.r[1] = 0x80000000u;
    cpu.r[2] = 1;
    ARM(0xe0510002u);
    CHECK_EQ(cpu.r[0], 0x7fffffffu);
    CHECK_EQ(FLAGS, C | V);

    begin("subs equal");
    cpu.r[1] = 9;
    cpu.r[2] = 9;
    ARM(0xe0510002u);
    CHECK_EQ(FLAGS, Z | C);

    begin("sbcs with borrow in");
    cpu.r[1] = 5;
    cpu.r[2] = 3;
    ARM(0xe0d10002u); /* sbcs r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(FLAGS, C);

    begin("sbcs borrowing");
    cpu.r[1] = 3;
    cpu.r[2] = 3;
    ARM(0xe0d10002u);
    CHECK_EQ(cpu.r[0], 0xffffffffu);
    CHECK_EQ(FLAGS, N);

    begin("rsbs");
    cpu.r[1] = 5;
    cpu.r[2] = 3;
    ARM(0xe0710002u); /* rsbs r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0xfffffffeu);
    CHECK_EQ(FLAGS, N);

    begin("rscs");
    cpu.r[1] = 3;
    cpu.r[2] = 5;
    cpu.cpsr |= C;
    ARM(0xe0f10002u); /* rscs r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 2);
    CHECK_EQ(FLAGS, C);

    begin("cmp cmn tst teq");
    cpu.r[1] = 0x80000000u;
    cpu.r[2] = 0x80000000u;
    ARM(0xe1510002u); /* cmp r1, r2 */
    CHECK_EQ(FLAGS, Z | C);
    ARM(0xe1710002u); /* cmn r1, r2 */
    CHECK_EQ(FLAGS, Z | C | V);
    ARM(0xe3110102u);           /* tst r1, #0x80000000 */
    CHECK_EQ(FLAGS, N | C | V); /* C from the rotated immediate's bit 31, V left by cmn */
    ARM(0xe1310002u);           /* teq r1, r2 */
    CHECK_EQ(FLAGS, Z | C | V); /* teq by register leaves C and V */
    CHECK_EQ(cpu.r[0], 0);

    begin("eors orrs");
    cpu.r[1] = 0xff00ff00u;
    cpu.r[2] = 0x0ff00ff0u;
    ARM(0xe0310002u,  /* eors r0, r1, r2 */
        0xe1913002u); /* orrs r3, r1, r2 */
    CHECK_EQ(cpu.r[0], 0xf0f0f0f0u);
    CHECK_EQ(cpu.r[3], 0xfff0fff0u);
    CHECK_EQ(FLAGS, N);
}

static void test_arm_conditions(void)
{
    /* r1 = 5, r2 = 7: each condition ors its own bit into r0 */
    begin("condition codes after cmp");
    cpu.r[1] = 5;
    cpu.r[2] = 7;
    uint32_t code[15];
    code[0] = 0xe1510002u; /* cmp r1, r2 */
    for (uint32_t cond = 0; cond < 14; cond++) {
        code[1 + cond] = (cond << 28) | 0x03800000u | arm_imm(1u << cond); /* orr<cond> r0, r0, #bit */
    }
    run_arm(code, 15);
    uint32_t want = (1u << 1) | (1u << 3) | (1u << 4) | (1u << 7) | (1u << 9) | (1u << 11) | (1u << 13);
    CHECK_EQ(cpu.r[0], want);

    begin("condition codes after equal cmp");
    cpu.r[1] = 7;
    cpu.r[2] = 7;
    run_arm(code, 15);
    want = (1u << 0) | (1u << 2) | (1u << 5) | (1u << 7) | (1u << 9) | (1u << 10) | (1u << 13);
    CHECK_EQ(cpu.r[0], want);
}

static void test_arm_multiply(void)
{
    begin("mul mla");
    cpu.r[1] = 0x10001u;
    cpu.r[2] = 0x10001u;
    cpu.r[3] = 5;
    ARM(0xe0000291u,  /* mul r0, r1, r2 */
        0xe0243291u); /* mla r4, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 0x20001u);
    CHECK_EQ(cpu.r[4], 0x20006u);

    begin("muls flags");
    cpu.r[1] = 0x80000000u;
    cpu.r[2] = 1;
    cpu.cpsr |= C;
    ARM(0xe0100291u); /* muls r0, r1, r2 */
    CHECK_EQ(FLAGS, N | C);
    cpu.r[2] = 2;
    ARM(0xe0100291u);
    CHECK_EQ(FLAGS, Z | C);

    begin("umull");
    cpu.r[2] = 0xffffffffu;
    cpu.r[3] = 0xffffffffu;
    ARM(0xe0810392u); /* umull r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(cpu.r[1], 0xfffffffeu);

    begin("umlal");
    cpu.r[0] = 0xffffffffu;
    cpu.r[1] = 1;
    cpu.r[2] = 2;
    cpu.r[3] = 3;
    ARM(0xe0a10392u); /* umlal r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 5);
    CHECK_EQ(cpu.r[1], 2);

    begin("smull");
    cpu.r[2] = 0xffffffffu; /* -1 */
    cpu.r[3] = 7;
    ARM(0xe0c10392u); /* smull r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 0xfffffff9u);
    CHECK_EQ(cpu.r[1], 0xffffffffu);

    begin("smlals flags");
    cpu.r[0] = 7;
    cpu.r[1] = 0;
    cpu.r[2] = 0xffffffffu;
    cpu.r[3] = 7;
    ARM(0xe0f10392u); /* smlals r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(cpu.r[1], 0);
    CHECK_EQ(FLAGS, Z);
}

static void test_arm_dsp(void)
{
    begin("smulxy");
    cpu.r[1] = 0x80007fffu;
    cpu.r[2] = 0x00020003u;
    ARM(0xe1600281u,  /* smulbb r0, r1, r2 */
        0xe16302c1u,  /* smulbt r3, r1, r2 */
        0xe16402a1u,  /* smultb r4, r1, r2 */
        0xe16502e1u); /* smultt r5, r1, r2 */
    CHECK_EQ(cpu.r[0], 0x7fff * 3);
    CHECK_EQ(cpu.r[3], 0x7fff * 2);
    CHECK_EQ(cpu.r[4], (uint32_t) (-32768 * 3));
    CHECK_EQ(cpu.r[5], (uint32_t) (-32768 * 2));

    begin("smlabb sets Q on overflow, result wraps");
    cpu.r[1] = 0x8000;
    cpu.r[2] = 0x8000;
    cpu.r[3] = 0x40000000u;
    ARM(0xe1003281u); /* smlabb r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 0x80000000u);
    CHECK_EQ(FLAGS, Q);

    begin("smlabb without overflow");
    cpu.r[1] = 3;
    cpu.r[2] = 4;
    cpu.r[3] = 10;
    ARM(0xe1003281u);
    CHECK_EQ(cpu.r[0], 22);
    CHECK_EQ(FLAGS, 0);

    begin("smulwb smlawb");
    cpu.r[1] = 0x00018000u; /* 1.5 in 16.16 */
    cpu.r[2] = 0x4000;      /* 0.25 in 1.15 */
    cpu.r[3] = 1;
    ARM(0xe12002a1u,  /* smulwb r0, r1, r2 */
        0xe1243281u); /* smlawb r4, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 0x6000);
    CHECK_EQ(cpu.r[4], 0x6001);
    CHECK_EQ(FLAGS, 0);

    begin("smulwb negative");
    cpu.r[1] = 0xffff0000u; /* -1.0 */
    cpu.r[2] = 0x4000;
    ARM(0xe12002a1u);
    CHECK_EQ(cpu.r[0], 0xffffc000u);

    begin("smlawb sets Q");
    cpu.r[1] = 0x7fff0000u;
    cpu.r[2] = 0x7fff;
    cpu.r[3] = 0x7fffffffu;
    ARM(0xe1243281u);
    CHECK_EQ(FLAGS, Q);

    begin("smlalbb");
    cpu.r[0] = 0xffffffffu;
    cpu.r[1] = 0;
    cpu.r[2] = 2;
    cpu.r[3] = 3;
    ARM(0xe1410382u); /* smlalbb r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 5);
    CHECK_EQ(cpu.r[1], 1);

    begin("smlaltt negative product");
    cpu.r[0] = 0;
    cpu.r[1] = 0;
    cpu.r[2] = 0xffff0000u;
    cpu.r[3] = 0x00030000u;
    ARM(0xe14103e2u); /* smlaltt r0, r1, r2, r3 */
    CHECK_EQ(cpu.r[0], 0xfffffffdu);
    CHECK_EQ(cpu.r[1], 0xffffffffu);

    begin("qadd saturates");
    cpu.r[1] = 0x7fffffffu;
    cpu.r[2] = 1;
    ARM(0xe1020051u); /* qadd r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0x7fffffffu);
    CHECK_EQ(FLAGS, Q);

    begin("qadd plain");
    cpu.r[1] = 0x7ffffffeu;
    cpu.r[2] = 1;
    ARM(0xe1020051u);
    CHECK_EQ(cpu.r[0], 0x7fffffffu);
    CHECK_EQ(FLAGS, 0);

    begin("qsub saturates low");
    cpu.r[1] = 0x80000000u;
    cpu.r[2] = 1;
    ARM(0xe1220051u); /* qsub r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0x80000000u);
    CHECK_EQ(FLAGS, Q);

    begin("qdadd doubles with saturation");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 0x40000000u;
    ARM(0xe1420051u); /* qdadd r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0x7ffffffeu);
    CHECK_EQ(FLAGS, Q);

    begin("qdadd plain");
    cpu.r[1] = 1;
    cpu.r[2] = 0x10000000u;
    ARM(0xe1420051u);
    CHECK_EQ(cpu.r[0], 0x20000001u);
    CHECK_EQ(FLAGS, 0);

    begin("qdsub");
    cpu.r[1] = 0;
    cpu.r[2] = 0xc0000000u; /* -2^30, doubled is -2^31 exactly; 0 - that saturates */
    ARM(0xe1620051u);       /* qdsub r0, r1, r2 */
    CHECK_EQ(cpu.r[0], 0x7fffffffu);
    CHECK_EQ(FLAGS, Q);

    begin("qdsub plain");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 0xc0000000u;
    ARM(0xe1620051u);
    CHECK_EQ(cpu.r[0], 0x7fffffffu);
    CHECK_EQ(FLAGS, 0);

    begin("Q is sticky");
    cpu.cpsr |= Q;
    cpu.r[1] = 1;
    cpu.r[2] = 1;
    ARM(0xe1020051u, 0xe0910002u); /* qadd then adds */
    CHECK_EQ(FLAGS, Q);

    begin("clz");
    cpu.r[1] = 1;
    cpu.r[2] = 0;
    cpu.r[3] = 0x80000000u;
    ARM(0xe16f0f11u,  /* clz r0, r1 */
        0xe16f4f12u,  /* clz r4, r2 */
        0xe16f5f13u); /* clz r5, r3 */
    CHECK_EQ(cpu.r[0], 31);
    CHECK_EQ(cpu.r[4], 32);
    CHECK_EQ(cpu.r[5], 0);
}

/* ARM memory ---------------------------------------------------------------------------- */

static void test_arm_load_store(void)
{
    begin("ldr str addressing modes");
    *word(DATA) = 0x11111111u;
    *word(DATA + 4) = 0x22222222u;
    *word(DATA + 8) = 0x33333333u;
    cpu.r[1] = DATA;
    cpu.r[2] = 1;
    cpu.r[4] = DATA + 8;
    ARM(0xe5910000u,  /* ldr r0, [r1] */
        0xe5b13004u,  /* ldr r3, [r1, #4]! */
        0xe4915004u,  /* ldr r5, [r1], #4 */
        0xe7146102u,  /* ldr r6, [r4, -r2, lsl #2] */
        0xe5017004u,  /* str r7, [r1, #-4] */
        0xe7818002u); /* str r8, [r1, r2] (r1 = DATA + 8, r2 = 1: aligned down) */
    CHECK_EQ(cpu.r[0], 0x11111111u);
    CHECK_EQ(cpu.r[3], 0x22222222u);
    CHECK_EQ(cpu.r[5], 0x22222222u);
    CHECK_EQ(cpu.r[1], DATA + 8);
    CHECK_EQ(cpu.r[6], 0x22222222u);
    CHECK_EQ(*word(DATA + 4), 0);
    CHECK_EQ(*word(DATA + 8), 0);

    begin("unaligned ldr rotates");
    *word(DATA) = 0x44332211u;
    cpu.r[1] = DATA + 1;
    cpu.r[2] = DATA + 3;
    ARM(0xe5910000u,  /* ldr r0, [r1] */
        0xe5923000u); /* ldr r3, [r2] */
    CHECK_EQ(cpu.r[0], 0x11443322u);
    CHECK_EQ(cpu.r[3], 0x33221144u);

    begin("unaligned str aligns down");
    cpu.r[0] = 0xaabbccddu;
    cpu.r[1] = DATA + 6;
    ARM(0xe5810000u); /* str r0, [r1] */
    CHECK_EQ(*word(DATA + 4), 0xaabbccddu);

    begin("ldrb strb with writeback");
    *word(DATA) = 0x44332211u;
    cpu.r[1] = DATA;
    cpu.r[2] = 0x99;
    ARM(0xe5d10001u,  /* ldrb r0, [r1, #1] */
        0xe4c12001u,  /* strb r2, [r1], #1 */
        0xe5d13000u); /* ldrb r3, [r1] */
    CHECK_EQ(cpu.r[0], 0x22);
    CHECK_EQ(cpu.r[1], DATA + 1);
    CHECK_EQ(*word(DATA), 0x44332299u);
    CHECK_EQ(cpu.r[3], 0x22);

    begin("halfword and signed loads");
    *word(DATA) = 0x8001fff2u;
    *word(DATA + 4) = 0x00007fffu;
    cpu.r[1] = DATA;
    cpu.r[2] = 2;
    ARM(0xe1d100b0u,  /* ldrh r0, [r1] */
        0xe1d130f0u,  /* ldrsh r3, [r1] */
        0xe1d140f2u,  /* ldrsh r4, [r1, #2] */
        0xe1d150d3u,  /* ldrsb r5, [r1, #3] */
        0xe1d160d4u,  /* ldrsb r6, [r1, #4] */
        0xe19170b2u,  /* ldrh r7, [r1, r2] */
        0xe1d180f1u); /* ldrsh r8, [r1, #1]: odd address, forced even on the ARM9 */
    CHECK_EQ(cpu.r[0], 0xfff2);
    CHECK_EQ(cpu.r[3], 0xfffffff2u);
    CHECK_EQ(cpu.r[4], 0xffff8001u);
    CHECK_EQ(cpu.r[5], 0xffffff80u);
    CHECK_EQ(cpu.r[6], 0xffffffffu);
    CHECK_EQ(cpu.r[7], 0x8001);
    CHECK_EQ(cpu.r[8], 0xfffffff2u);

    begin("strh aligns and writeback");
    cpu.r[0] = 0x12345678u;
    cpu.r[1] = DATA + 1;
    ARM(0xe0c100b2u); /* strh r0, [r1], #2 */
    CHECK_EQ(*word(DATA), 0x00005678u);
    CHECK_EQ(cpu.r[1], DATA + 3);

    begin("ldrd strd");
    *word(DATA) = 0x11111111u;
    *word(DATA + 4) = 0x22222222u;
    cpu.r[1] = DATA;
    cpu.r[2] = 0xaaaaaaaau;
    cpu.r[3] = 0xbbbbbbbbu;
    ARM(0xe1c140d0u,  /* ldrd r4, [r1] */
        0xe1c120f8u); /* strd r2, [r1, #8] */
    CHECK_EQ(cpu.r[4], 0x11111111u);
    CHECK_EQ(cpu.r[5], 0x22222222u);
    CHECK_EQ(*word(DATA + 8), 0xaaaaaaaau);
    CHECK_EQ(*word(DATA + 12), 0xbbbbbbbbu);

    begin("swp swpb");
    *word(DATA) = 0x44332211u;
    cpu.r[1] = DATA;
    cpu.r[2] = 0x99999999u;
    cpu.r[4] = 0x77;
    ARM(0xe1010092u,  /* swp r0, r2, [r1] */
        0xe1413094u); /* swpb r3, r4, [r1] */
    CHECK_EQ(cpu.r[0], 0x44332211u);
    CHECK_EQ(cpu.r[3], 0x99);
    CHECK_EQ(*word(DATA), 0x99999977u);

    begin("str pc stores the address + 12");
    cpu.r[1] = DATA;
    ARM(0xe581f000u); /* str pc, [r1] */
    CHECK_EQ(*word(DATA), CODE + 12);

    begin("str with base as data after post-index stores the old base");
    cpu.r[1] = DATA;
    ARM(0xe4811004u); /* str r1, [r1], #4 */
    CHECK_EQ(*word(DATA), DATA);
    CHECK_EQ(cpu.r[1], DATA + 4);

    begin("ldr into pc interworks");
    *half(CODE + 0x40) = 0x2009; /* movs r0, #9 */
    *half(CODE + 0x42) = 0x4770; /* bx lr */
    *word(DATA) = (CODE + 0x40) | 1;
    cpu.r[1] = DATA;
    CHECK_EQ(ARM(0xe591f000u), ARM_RETURNED); /* ldr pc, [r1] */
    CHECK_EQ(cpu.r[0], 9);                    /* the Thumb code ran; its bx lr cleared T again */
}

static void test_arm_block_transfer(void)
{
    begin("stmia stmdb stmib stmda");
    memset(memory_host(DATA, 0x80), 0, 0x80);
    cpu.r[2] = 2;
    cpu.r[3] = 3;
    cpu.r[4] = 4;
    cpu.r[1] = DATA;
    cpu.r[5] = DATA + 0x40;
    cpu.r[6] = DATA + 0x20;
    cpu.r[7] = DATA + 0x30;
    ARM(0xe8a1001cu,  /* stmia r1!, {r2-r4} */
        0xe925001cu,  /* stmdb r5!, {r2-r4} */
        0xe986000cu,  /* stmib r6, {r2, r3} */
        0xe807000cu); /* stmda r7, {r2, r3} */
    CHECK_EQ(*word(DATA), 2);
    CHECK_EQ(*word(DATA + 4), 3);
    CHECK_EQ(*word(DATA + 8), 4);
    CHECK_EQ(cpu.r[1], DATA + 12);
    CHECK_EQ(*word(DATA + 0x34), 2);
    CHECK_EQ(*word(DATA + 0x3c), 4);
    CHECK_EQ(cpu.r[5], DATA + 0x34);
    CHECK_EQ(*word(DATA + 0x20), 0);
    CHECK_EQ(*word(DATA + 0x24), 2);
    CHECK_EQ(*word(DATA + 0x28), 3);
    CHECK_EQ(cpu.r[6], DATA + 0x20);
    CHECK_EQ(*word(DATA + 0x2c), 2);
    CHECK_EQ(*word(DATA + 0x30), 3);
    CHECK_EQ(cpu.r[7], DATA + 0x30);

    begin("ldmia ldmdb ldmib ldmda");
    for (uint32_t i = 0; i < 16; i++) {
        *word(DATA + i * 4) = 0x100 + i;
    }
    cpu.r[1] = DATA;
    cpu.r[5] = DATA + 0x40;
    cpu.r[6] = DATA + 0x20;
    cpu.r[7] = DATA + 0x30;
    ARM(0xe8b1001cu,  /* ldmia r1!, {r2-r4} */
        0xe9350300u,  /* ldmdb r5!, {r8, r9} */
        0xe9960c00u,  /* ldmib r6, {r10, r11} */
        0xe8171000u); /* ldmda r7, {r12} */
    CHECK_EQ(cpu.r[2], 0x100);
    CHECK_EQ(cpu.r[4], 0x102);
    CHECK_EQ(cpu.r[1], DATA + 12);
    CHECK_EQ(cpu.r[8], 0x10e);
    CHECK_EQ(cpu.r[9], 0x10f);
    CHECK_EQ(cpu.r[5], DATA + 0x38);
    CHECK_EQ(cpu.r[10], 0x109);
    CHECK_EQ(cpu.r[11], 0x10a);
    CHECK_EQ(cpu.r[12], 0x10c);

    begin("stm with the base first in the list stores the old base");
    cpu.r[1] = DATA;
    cpu.r[2] = 7;
    ARM(0xe8a10006u); /* stmia r1!, {r1, r2} */
    CHECK_EQ(*word(DATA), DATA);
    CHECK_EQ(*word(DATA + 4), 7);
    CHECK_EQ(cpu.r[1], DATA + 8);

    begin("stm with the base later in the list stores the new base");
    cpu.r[0] = 6;
    cpu.r[1] = DATA;
    ARM(0xe8a10003u); /* stmia r1!, {r0, r1} */
    CHECK_EQ(*word(DATA), 6);
    CHECK_EQ(*word(DATA + 4), DATA + 8);

    begin("ldm with the base in the list keeps the loaded value");
    *word(DATA) = 0x1234;
    *word(DATA + 4) = 0x5678;
    cpu.r[1] = DATA;
    ARM(0xe8b10006u); /* ldmia r1!, {r1, r2} */
    CHECK_EQ(cpu.r[1], 0x1234);
    CHECK_EQ(cpu.r[2], 0x5678);

    begin("ldm pc interworks to Thumb");
    *half(CODE + 0x40) = 0x200a; /* movs r0, #10 */
    *half(CODE + 0x42) = 0x4770; /* bx lr */
    *word(DATA) = 0x55;
    *word(DATA + 4) = (CODE + 0x40) | 1;
    cpu.r[1] = DATA;
    CHECK_EQ(ARM(0xe8918004u), ARM_RETURNED); /* ldmia r1, {r2, pc} */
    CHECK_EQ(cpu.r[2], 0x55);
    CHECK_EQ(cpu.r[0], 10);

    begin("push pop returns through pc");
    cpu.r[4] = 0x44;
    CHECK_EQ(ARM(0xe92d4010u,  /* push {r4, lr} */
                 0xe3a04000u,  /* mov r4, #0 */
                 0xe8bd8010u), /* pop {r4, pc} */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[4], 0x44);
    CHECK_EQ(cpu.r[13], STACK_TOP);
    CHECK_EQ(cpu.cpsr & ARM_CPSR_T, 0);

    begin("stm of pc stores the address + 12");
    cpu.r[1] = DATA;
    ARM(0xe8818000u); /* stmia r1, {pc} */
    CHECK_EQ(*word(DATA), CODE + 12);
}

/* ARM control flow ---------------------------------------------------------------------- */

static void test_arm_branches(void)
{
    begin("b skips");
    CHECK_EQ(ARM(0xea000000u,  /* b +8 */
                 0xe3a00001u,  /* mov r0, #1 (skipped) */
                 0xe3a01002u), /* mov r1, #2 */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(cpu.r[1], 2);

    begin("b backwards");
    cpu.r[0] = 0;
    ARM(0xe2800001u,  /* add r0, r0, #1 */
        0xe3500005u,  /* cmp r0, #5 */
        0x1afffffcu); /* bne -16 */
    CHECK_EQ(cpu.r[0], 5);

    begin("bl sets lr and bx returns");
    ARM(0xe1a0400eu,  /* mov r4, lr */
        0xeb000000u,  /* bl +8 */
        0xe12fff14u,  /* bx r4 */
        0xe3a00001u,  /* mov r0, #1 */
        0xe12fff1eu); /* bx lr */
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(cpu.r[14], CODE + 8);

    begin("blx immediate to Thumb and back");
    *half(CODE + 0x40) = 0x2011; /* movs r0, #0x11 */
    *half(CODE + 0x42) = 0x4770; /* bx lr */
    cpu.r[14] = 0;
    ARM(0xe1a0400eu,  /* mov r4, lr */
        0xfa00000du,  /* blx CODE + 0x40 from CODE + 4: pc + 8 + 0x34 */
        0xe12fff14u); /* bx r4 */
    CHECK_EQ(cpu.r[0], 0x11);
    CHECK_EQ(cpu.r[14], CODE + 8);
    CHECK_EQ(cpu.cpsr & ARM_CPSR_T, 0);

    begin("blx immediate with the halfword bit");
    *half(CODE + 0x42) = 0x2012; /* movs r0, #0x12 */
    *half(CODE + 0x44) = 0x4770; /* bx lr */
    ARM(0xe1a0400eu,             /* mov r4, lr */
        0xfb00000du,             /* blx CODE + 0x42 */
        0xe12fff14u);            /* bx r4 */
    CHECK_EQ(cpu.r[0], 0x12);

    begin("blx register");
    *half(CODE + 0x40) = 0x2013; /* movs r0, #0x13 */
    *half(CODE + 0x42) = 0x4770; /* bx lr */
    cpu.r[1] = (CODE + 0x40) | 1;
    ARM(0xe1a0400eu,  /* mov r4, lr */
        0xe12fff31u,  /* blx r1 */
        0xe12fff14u); /* bx r4 */
    CHECK_EQ(cpu.r[0], 0x13);
    CHECK_EQ(cpu.r[14], CODE + 8);

    begin("mov pc does not interwork");
    cpu.r[1] = (CODE + 8) | 1;
    CHECK_EQ(ARM(0xe1a0f001u,  /* mov pc, r1 */
                 0xe3a00001u,  /* mov r0, #1 (skipped) */
                 0xe3a00007u), /* mov r0, #7 */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 7);
    CHECK_EQ(cpu.cpsr & ARM_CPSR_T, 0);

    begin("bx to Thumb then mov pc, lr returns");
    *half(CODE + 0x40) = 0x2014; /* movs r0, #0x14 */
    *half(CODE + 0x42) = 0x46f7; /* mov pc, lr: stays Thumb, lr = ARM_RETURN_ADDRESS */
    cpu.r[1] = (CODE + 0x40) | 1;
    CHECK_EQ(ARM(0xe12fff11u), ARM_RETURNED); /* bx r1 */
    CHECK_EQ(cpu.r[0], 0x14);
}

static void test_arm_system(void)
{
    begin("mrs msr");
    cpu.r[1] = 0xf0000000u;
    cpu.r[2] = 0x800000d3u;
    ARM(0xe10f0000u,  /* mrs r0, cpsr */
        0xe128f001u,  /* msr cpsr_f, r1 */
        0xe10f3000u,  /* mrs r3, cpsr */
        0xe121f002u,  /* msr cpsr_c, r2 */
        0xe10f4000u,  /* mrs r4, cpsr */
        0xe328f20fu,  /* msr cpsr_f, #0xf0000000 */
        0xe32ff000u); /* msr cpsr_fc, #0 */
    CHECK_EQ(cpu.r[0], ARM_MODE_SYSTEM);
    CHECK_EQ(cpu.r[3], 0xf0000000u | ARM_MODE_SYSTEM);
    CHECK_EQ(cpu.r[4], 0xf00000d3u);
    CHECK_EQ(cpu.cpsr, 0);

    begin("mcr mrc on cp15");
    cpu.r[0] = 0x55;
    ARM(0xee070f15u,  /* mcr p15, 0, r0, c7, c5, 0 */
        0xee110f10u); /* mrc p15, 0, r0, c1, c0, 0 */
    CHECK_EQ(cpu.r[0], 0);

    begin("swi stops after the instruction");
    CHECK_EQ(ARM(0xef00000eu, 0xe3a00001u), ARM_SWI);
    CHECK_EQ(cpu.swi, 0xe);
    CHECK_EQ(cpu.stop_pc, CODE);
    CHECK_EQ(cpu.r[15], CODE + 4);
    CHECK_EQ(arm_run(&cpu, ARM_RETURN_ADDRESS, 100), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 1);

    begin("bkpt");
    CHECK_EQ(ARM(0xe3a00001u, 0xe1200070u), ARM_BREAKPOINT);
    CHECK_EQ(cpu.stop_pc, CODE + 4);
    CHECK_EQ(cpu.r[15], CODE + 4);

    begin("undefined");
    CHECK_EQ(ARM(0xe7f000f0u), ARM_UNDEFINED);
    CHECK_EQ(cpu.stop_pc, CODE);
    CHECK_EQ(ARM(0xee000000u), ARM_UNDEFINED); /* cdp */
    CHECK_EQ(ARM(0xec100000u), ARM_UNDEFINED); /* ldc */
    CHECK_EQ(ARM(0xf7000000u), ARM_UNDEFINED); /* unconditional space */

    begin("pld is a nop");
    cpu.r[1] = DATA;
    CHECK_EQ(ARM(0xf5d1f000u, 0xe3a00003u), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 3);

    begin("conditional swi not taken");
    cpu.cpsr |= Z;
    CHECK_EQ(ARM(0x1f000001u), ARM_RETURNED); /* swine 1 */

    begin("step limit");
    memcpy(memory_host(CODE, 4), (const uint32_t[]){0xeafffffeu}, 4); /* b . */
    CHECK_EQ(arm_call(&cpu, CODE, 50), ARM_STEP_LIMIT);
    CHECK_EQ(cpu.steps, 50);
    CHECK_EQ(cpu.stop_pc, CODE);

    begin("bad address without io");
    cpu.r[1] = 0x04000004u;
    CHECK_EQ(ARM(0xe5910000u), ARM_BAD_ADDRESS); /* ldr r0, [r1] */
    CHECK_EQ(cpu.fault_address, 0x04000004u);
    CHECK_EQ(cpu.stop_pc, CODE);
    CHECK_EQ(cpu.r[15], CODE);

    begin("bad fetch");
    cpu.r[1] = 0x06000000u;
    CHECK_EQ(ARM(0xe12fff11u), ARM_BAD_ADDRESS); /* bx r1 */
    CHECK_EQ(cpu.fault_address, 0x06000000u);
}

/* I/O callbacks: a 32-bit register at 0x04000000 and a 16-bit one at 0x04000004. */
static uint32_t io_register, io_half;
static int io_read(void *user, uint32_t address, int size, uint32_t *value)
{
    (void) user;
    if (address == 0x04000000u && size == 4) {
        *value = io_register;
        return 1;
    }
    if (address == 0x04000004u && size == 2) {
        *value = io_half;
        return 1;
    }
    return 0;
}

static int io_write(void *user, uint32_t address, int size, uint32_t value)
{
    (void) user;
    if (address == 0x04000000u && size == 4) {
        io_register = value;
        return 1;
    }
    if (address == 0x04000004u && size == 2) {
        io_half = value;
        return 1;
    }
    return 0;
}

static void test_io(void)
{
    begin("io callbacks");
    cpu.io_read = io_read;
    cpu.io_write = io_write;
    io_register = 0x12345678u;
    io_half = 0xabcd;
    cpu.r[1] = 0x04000000u;
    cpu.r[2] = 0x1111;
    CHECK_EQ(ARM(0xe5910000u,  /* ldr r0, [r1] */
                 0xe1d130b4u,  /* ldrh r3, [r1, #4] */
                 0xe1c120b4u,  /* strh r2, [r1, #4] */
                 0xe5812000u), /* str r2, [r1] */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0x12345678u);
    CHECK_EQ(cpu.r[3], 0xabcd);
    CHECK_EQ(io_half, 0x1111);
    CHECK_EQ(io_register, 0x1111);

    begin("io callback refusing");
    cpu.io_read = io_read;
    cpu.io_write = io_write;
    cpu.r[1] = 0x04000008u;
    CHECK_EQ(ARM(0xe5910000u), ARM_BAD_ADDRESS);
    CHECK_EQ(cpu.fault_address, 0x04000008u);
}

/* Thumb ----------------------------------------------------------------------------------- */

static void test_thumb_alu(void)
{
    begin("thumb shifts by immediate");
    cpu.r[1] = 0x90000000u;
    cpu.r[2] = 0x80000000u;
    THUMB(0x0108,  /* lsls r0, r1, #4 */
          0x4603,  /* mov r3, r0 (hi-reg form: no flags) */
          0x0813,  /* lsrs r3, r2, #32 */
          0x1014); /* asrs r4, r2, #32 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(cpu.r[3], 0);
    CHECK_EQ(cpu.r[4], 0xffffffffu);
    CHECK_EQ(FLAGS, N | C);

    begin("thumb lsls #0 keeps C");
    cpu.r[1] = 5;
    cpu.cpsr |= C;
    THUMB(0x0008); /* lsls r0, r1, #0 */
    CHECK_EQ(cpu.r[0], 5);
    CHECK_EQ(FLAGS, C);

    begin("thumb add sub three-register and imm3");
    cpu.r[1] = 0xffffffffu;
    cpu.r[2] = 1;
    THUMB(0x1888,   /* adds r0, r1, r2 */
          0x1a53,   /* subs r3, r2, r1 */
          0x1cccu,  /* adds r4, r1, #3 */
          0x1fcdu); /* subs r5, r1, #7 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(cpu.r[3], 2);
    CHECK_EQ(cpu.r[4], 2);
    CHECK_EQ(cpu.r[5], 0xfffffff8u);
    CHECK_EQ(FLAGS, N | C);

    begin("thumb imm8 forms");
    THUMB(0x2000,  /* movs r0, #0 */
          0x30c8,  /* adds r0, #200 */
          0x3801,  /* subs r0, #1 */
          0x28c7); /* cmp r0, #199 */
    CHECK_EQ(cpu.r[0], 199);
    CHECK_EQ(FLAGS, Z | C);

    begin("thumb movs sets Z");
    THUMB(0x2000);
    CHECK_EQ(FLAGS, Z);

    begin("thumb format 4 logic");
    cpu.r[0] = 0xff00ff00u;
    cpu.r[1] = 0x0ff00ff0u;
    cpu.r[2] = 0xff00ff00u;
    cpu.r[3] = 0xff00ff00u;
    cpu.r[4] = 0xff00ff00u;
    cpu.r[5] = 0x0f;
    THUMB(0x4008,  /* ands r0, r1 */
          0x404a,  /* eors r2, r1 */
          0x430b,  /* orrs r3, r1 */
          0x438c,  /* bics r4, r1 */
          0x43ed); /* mvns r5, r5 */
    CHECK_EQ(cpu.r[0], 0x0f000f00u);
    CHECK_EQ(cpu.r[2], 0xf0f0f0f0u);
    CHECK_EQ(cpu.r[3], 0xfff0fff0u);
    CHECK_EQ(cpu.r[4], 0xf000f000u);
    CHECK_EQ(cpu.r[5], 0xfffffff0u);
    CHECK_EQ(FLAGS, N);

    begin("thumb format 4 register shifts");
    cpu.r[0] = 0x80000001u;
    cpu.r[1] = 32;
    cpu.r[2] = 0x80000001u;
    cpu.r[3] = 0x80000000u;
    cpu.r[4] = 0x12345678u;
    cpu.r[5] = 36;
    THUMB(0x4088,  /* lsls r0, r1 */
          0x40ca,  /* lsrs r2, r1 */
          0x410b,  /* asrs r3, r1 */
          0x41ec); /* rors r4, r5 */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(cpu.r[2], 0);
    CHECK_EQ(cpu.r[3], 0xffffffffu);
    CHECK_EQ(cpu.r[4], 0x81234567u);
    CHECK_EQ(FLAGS, N | C);

    begin("thumb adcs sbcs");
    cpu.r[0] = 0xffffffffu;
    cpu.r[1] = 0;
    cpu.r[2] = 5;
    cpu.r[3] = 3;
    cpu.cpsr |= C;
    THUMB(0x4148,  /* adcs r0, r1 */
          0x419a); /* sbcs r2, r3 (C set by the adc) */
    CHECK_EQ(cpu.r[0], 0);
    CHECK_EQ(cpu.r[2], 2);
    CHECK_EQ(FLAGS, C);

    begin("thumb tst neg cmp cmn mul");
    cpu.r[0] = 5;
    cpu.r[1] = 2;
    cpu.r[2] = 0x7fffffffu;
    cpu.r[3] = 0x7fffffffu;
    cpu.r[4] = 1;
    cpu.r[5] = 0xffffffffu;
    cpu.r[6] = 6;
    cpu.r[7] = 7;
    THUMB(0x4208,  /* tst r0, r1 */
          0x4249,  /* negs r1, r1 */
          0x4293,  /* cmp r3, r2 */
          0x42ec,  /* cmn r4, r5 */
          0x437e); /* muls r6, r7 */
    CHECK_EQ(cpu.r[1], 0xfffffffeu);
    CHECK_EQ(cpu.r[6], 42);
    CHECK_EQ(FLAGS, C); /* from cmn 1 + -1 (Z, C), then muls clears Z and leaves C */

    begin("thumb neg flags");
    cpu.r[1] = 0;
    THUMB(0x4249); /* negs r1, r1 */
    CHECK_EQ(FLAGS, Z | C);

    begin("thumb high register ops");
    cpu.r[0] = 1;
    cpu.r[8] = 10;
    cpu.r[9] = 0xffffffffu;
    cpu.cpsr |= Z;
    THUMB(0x4440,  /* add r0, r8 (no flags) */
          0x4481,  /* add r9, r0 */
          0x4648,  /* mov r0, r9 */
          0x4688,  /* mov r8, r1 */
          0x4541,  /* cmp r1, r8 */
          0x4478); /* add r0, pc */
    CHECK_EQ(cpu.r[9], 10);
    CHECK_EQ(cpu.r[8], cpu.r[1]);
    CHECK_EQ(cpu.r[0], 10 + CODE + 10 + 4);
    CHECK_EQ(FLAGS, Z | C);
}

static void test_thumb_memory(void)
{
    begin("thumb register offset loads and stores");
    memset(memory_host(DATA, 0x20), 0, 0x20);
    cpu.r[0] = 0x8765fedcu;
    cpu.r[1] = DATA;
    cpu.r[2] = 4;
    cpu.r[3] = 6;
    cpu.r[4] = 9;
    THUMB(0x5088,                           /* str r0, [r1, r2] */
          0x52c8,                           /* strh r0, [r1, r3] */
          0x5508,                           /* strb r0, [r1, r4] */
          0x588d,                           /* ldr r5, [r1, r2] */
          0x5ace,                           /* ldrh r6, [r1, r3] */
          0x5d0f,                           /* ldrb r7, [r1, r4] */
          0x5ec8,                           /* ldrsh r0, [r1, r3] */
          0x570c);                          /* ldrsb r4, [r1, r4] */
    CHECK_EQ(*word(DATA + 4), 0xfedcfedcu); /* the strh at DATA + 6 overwrote the top half */
    CHECK_EQ(*word(DATA + 8), 0x0000dc00u);
    CHECK_EQ(cpu.r[5], 0xfedcfedcu);
    CHECK_EQ(cpu.r[6], 0xfedc);
    CHECK_EQ(cpu.r[7], 0xdc);
    CHECK_EQ(cpu.r[0], 0xfffffedcu);
    CHECK_EQ(cpu.r[4], 0xffffffdcu);

    begin("thumb immediate offset loads and stores");
    memset(memory_host(DATA, 0x20), 0, 0x20);
    cpu.r[0] = 0x12345678u;
    cpu.r[1] = DATA;
    THUMB(0x6048,  /* str r0, [r1, #4] */
          0x7248,  /* strb r0, [r1, #9] */
          0x8148,  /* strh r0, [r1, #10] */
          0x684a,  /* ldr r2, [r1, #4] */
          0x7a4b,  /* ldrb r3, [r1, #9] */
          0x894c); /* ldrh r4, [r1, #10] */
    CHECK_EQ(*word(DATA + 4), 0x12345678u);
    CHECK_EQ(*word(DATA + 8), 0x56787800u);
    CHECK_EQ(cpu.r[2], 0x12345678u);
    CHECK_EQ(cpu.r[3], 0x78);
    CHECK_EQ(cpu.r[4], 0x5678);

    begin("thumb unaligned ldr rotates");
    *word(DATA) = 0x44332211u;
    cpu.r[1] = DATA + 2;
    THUMB(0x6808); /* ldr r0, [r1] */
    CHECK_EQ(cpu.r[0], 0x22114433u);

    begin("thumb sp-relative and address forms");
    cpu.r[0] = 0x77;
    THUMB(0x9001,  /* str r0, [sp, #4] */
          0x9901,  /* ldr r1, [sp, #4] */
          0xa202,  /* add r2, pc, #8 */
          0xaa02,  /* add r2, sp, #8 (overwrites) */
          0xa302,  /* add r3, pc, #8 */
          0xb082,  /* sub sp, #8 */
          0xac00,  /* add r4, sp, #0 */
          0xb002); /* add sp, #8 */
    CHECK_EQ(*word(STACK_TOP + 4), 0x77);
    CHECK_EQ(cpu.r[1], 0x77);
    CHECK_EQ(cpu.r[2], STACK_TOP + 8);
    CHECK_EQ(cpu.r[3], ((CODE + 8 + 4) & ~3u) + 8);
    CHECK_EQ(cpu.r[4], STACK_TOP - 8);
    CHECK_EQ(cpu.r[13], STACK_TOP);

    begin("thumb push pop");
    cpu.r[0] = 1;
    cpu.r[1] = 2;
    cpu.r[2] = 3;
    cpu.r[4] = 4;
    CHECK_EQ(THUMB(0xb510,  /* push {r4, lr} */
                   0xb407,  /* push {r0-r2} */
                   0x2000,  /* movs r0, #0 */
                   0x2400,  /* movs r4, #0 */
                   0xbc07,  /* pop {r0-r2} */
                   0xbd10), /* pop {r4, pc} */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 1);
    CHECK_EQ(cpu.r[2], 3);
    CHECK_EQ(cpu.r[4], 4);
    CHECK_EQ(cpu.r[13], STACK_TOP);
    CHECK_EQ(*word(STACK_TOP - 4), ARM_RETURN_ADDRESS);

    begin("thumb pop pc interworks to ARM");
    *word(CODE + 0x40) = 0xe3a00021u; /* mov r0, #0x21 */
    *word(CODE + 0x44) = 0xe12fff1eu; /* bx lr */
    *word(STACK_TOP - 4) = CODE + 0x40;
    cpu.r[13] = STACK_TOP - 4;
    CHECK_EQ(THUMB(0xbd00), ARM_RETURNED); /* pop {pc} */
    CHECK_EQ(cpu.r[0], 0x21);
    CHECK_EQ(cpu.cpsr & ARM_CPSR_T, 0);

    begin("thumb stmia ldmia");
    cpu.r[1] = DATA;
    cpu.r[2] = 0x22;
    cpu.r[3] = 0x33;
    THUMB(0xc10c,  /* stmia r1!, {r2, r3} */
          0x3908,  /* subs r1, #8 */
          0xc930); /* ldmia r1!, {r4, r5} */
    CHECK_EQ(*word(DATA), 0x22);
    CHECK_EQ(*word(DATA + 4), 0x33);
    CHECK_EQ(cpu.r[4], 0x22);
    CHECK_EQ(cpu.r[5], 0x33);
    CHECK_EQ(cpu.r[1], DATA + 8);

    begin("thumb ldmia with base in list");
    *word(DATA) = 0x1234;
    *word(DATA + 4) = 0x5678;
    cpu.r[1] = DATA;
    THUMB(0xc906); /* ldmia r1!, {r1, r2} */
    CHECK_EQ(cpu.r[1], 0x1234);
    CHECK_EQ(cpu.r[2], 0x5678);
}

static void test_thumb_branches(void)
{
    begin("thumb conditional branches");
    cpu.r[0] = 0;
    THUMB(0x2905,  /* cmp r1, #5 (r1 = 0: ne, cc, mi, lt) */
          0xd100,  /* bne +0 (skips one) */
          0x3001,  /* adds r0, #1 */
          0x2905,  /* cmp r1, #5 */
          0xd000,  /* beq +0 */
          0x3002,  /* adds r0, #2 */
          0x2905,  /* cmp r1, #5 */
          0xdb00,  /* blt +0 */
          0x3004,  /* adds r0, #4 */
          0x2905,  /* cmp r1, #5 */
          0xd200,  /* bcs +0 */
          0x3008,  /* adds r0, #8 */
          0x2905,  /* cmp r1, #5 */
          0xd400,  /* bmi +0 */
          0x3010,  /* adds r0, #16 */
          0x2905,  /* cmp r1, #5 */
          0xdd00,  /* ble +0 */
          0x3020); /* adds r0, #32 */
    CHECK_EQ(cpu.r[0], 2 + 8);
    CHECK_EQ(cpu.r[1], 0);

    begin("thumb loop with backward branch");
    cpu.r[0] = 0;
    THUMB(0x3001,  /* adds r0, #1 */
          0x2805,  /* cmp r0, #5 */
          0xd1fc); /* bne -8 */
    CHECK_EQ(cpu.r[0], 5);

    begin("thumb unconditional branch");
    THUMB(0xe001,  /* b +2 */
          0x2001,  /* movs r0, #1 (skipped) */
          0x2002,  /* movs r0, #2 (skipped) */
          0x2003); /* movs r0, #3 */
    CHECK_EQ(cpu.r[0], 3);

    begin("thumb bl pair");
    CHECK_EQ(THUMB(0x4674,  /* mov r4, lr */
                   0xf000,  /* bl prefix */
                   0xf802,  /* bl suffix: target = CODE + 2 + 4 + 4 = CODE + 10 */
                   0x4720,  /* bx r4 */
                   0x46c0,  /* nop */
                   0x2003,  /* movs r0, #3 */
                   0x4770), /* bx lr */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 3);
    CHECK_EQ(cpu.r[14], (CODE + 6) | 1);

    begin("thumb bl pair backwards");
    cpu.r[0] = 0;
    CHECK_EQ(THUMB(0xe002,  /* b +4 -> CODE + 8 */
                   0x3001,  /* adds r0, #1 */
                   0x4770,  /* bx lr */
                   0x46c0,  /* nop */
                   0x4674,  /* mov r4, lr */
                   0xf7ff,  /* bl prefix: -4096 */
                   0xfffa,  /* suffix: lr + 0xff4 -> CODE + 10 + 4 - 0x1000 + 0xff4 = CODE + 2 */
                   0x4720), /* bx r4 */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 1);

    begin("thumb blx pair to ARM");
    *word(CODE + 0x40) = 0xe3a00021u; /* mov r0, #0x21 */
    *word(CODE + 0x44) = 0xe12fff1eu; /* bx lr */
    CHECK_EQ(THUMB(0x4674,            /* mov r4, lr */
                   0xf000,            /* blx prefix */
                   0xe81d,            /* blx suffix: (CODE + 6 + 0x3a) & ~3 = CODE + 0x40 */
                   0x4720),           /* bx r4 */
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0x21);
    CHECK_EQ(cpu.r[14], (CODE + 6) | 1);

    begin("thumb blx register");
    *word(CODE + 0x40) = 0xe3a00022u; /* mov r0, #0x22 */
    *word(CODE + 0x44) = 0xe12fff1eu; /* bx lr */
    cpu.r[1] = CODE + 0x40;
    THUMB(0x4674,  /* mov r4, lr */
          0x4788,  /* blx r1 */
          0x4720); /* bx r4 */
    CHECK_EQ(cpu.r[0], 0x22);
    CHECK_EQ(cpu.r[14], (CODE + 4) | 1);

    begin("thumb bx pc goes to ARM");
    CHECK_EQ(THUMB(0x4778,         /* bx pc: ARM state at CODE + 4 */
                   0x46c0,         /* nop */
                   0x0023,         /* mov r0, #0x23 as two halfwords */
                   0xe3a0, 0xff1e, /* bx lr */
                   0xe12f),
             ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0x23);

    begin("thumb mov pc stays Thumb");
    cpu.r[1] = CODE + 4; /* bit 0 clear, still Thumb */
    THUMB(0x468f,        /* mov pc, r1 */
          0x2001,        /* movs r0, #1 (skipped) */
          0x2005);       /* movs r0, #5 */
    CHECK_EQ(cpu.r[0], 5);

    begin("thumb swi bkpt undefined");
    CHECK_EQ(THUMB(0xdf05), ARM_SWI);
    CHECK_EQ(cpu.swi, 5);
    CHECK_EQ(cpu.r[15], CODE + 2);
    CHECK(cpu.cpsr & ARM_CPSR_T);
    CHECK_EQ(arm_run(&cpu, ARM_RETURN_ADDRESS, 10), ARM_RETURNED);
    CHECK_EQ(THUMB(0x46c0, 0xbe01), ARM_BREAKPOINT);
    CHECK_EQ(cpu.stop_pc, CODE + 2);
    CHECK_EQ(THUMB(0xde00), ARM_UNDEFINED);
    CHECK_EQ(THUMB(0xb200), ARM_UNDEFINED); /* sxth, ARMv6 */
    CHECK_EQ(THUMB(0xba00), ARM_UNDEFINED); /* rev, ARMv6 */
}

/* Hooks ----------------------------------------------------------------------------------- */

static uint32_t hooked_address;
static int hook_calls;
static int hook_mode; /* 0: stop, 1: act as the function and return to lr */

static int hook(ArmCpu *c, void *user)
{
    hook_calls++;
    CHECK_EQ((uint32_t) (uintptr_t) user, 0x1234);
    if (hook_mode == 0) {
        return 1;
    }
    c->r[0] = 0x4242;
    c->r[15] = c->r[14] & ~1u;
    if (c->r[14] & 1) {
        c->cpsr |= ARM_CPSR_T;
    } else {
        c->cpsr &= ~ARM_CPSR_T;
    }
    return 0;
}

static ArmHook hook_at(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    if (address == hooked_address) {
        *hook_user = (void *) (uintptr_t) 0x1234;
        return hook;
    }
    return NULL;
}

static void test_hooks(void)
{
    begin("hook at the entry stops");
    cpu.hook_at = hook_at;
    hooked_address = CODE;
    hook_mode = 0;
    hook_calls = 0;
    CHECK_EQ(ARM(0xe3a00001u), ARM_HOOK_STOP);
    CHECK_EQ(hook_calls, 1);
    CHECK_EQ(cpu.stop_pc, CODE);
    CHECK_EQ(cpu.r[0], 0);

    begin("hook on a bl target replaces the function");
    cpu.hook_at = hook_at;
    hooked_address = CODE + 0x40;
    hook_mode = 1;
    hook_calls = 0;
    *word(CODE + 0x40) = 0xe3a00001u; /* mov r0, #1: never runs */
    *word(CODE + 0x44) = 0xe12fff1eu;
    CHECK_EQ(ARM(0xe1a0400eu,  /* mov r4, lr */
                 0xeb00000du,  /* bl CODE + 0x40 */
                 0xe12fff14u), /* bx r4 */
             ARM_RETURNED);
    CHECK_EQ(hook_calls, 1);
    CHECK_EQ(cpu.r[0], 0x4242);

    begin("hook reached by a Thumb pop pc");
    cpu.hook_at = hook_at;
    hooked_address = CODE + 0x40;
    hook_mode = 1;
    hook_calls = 0;
    *half(CODE + 0x40) = 0x2001; /* movs r0, #1: never runs */
    *half(CODE + 0x42) = 0x4770;
    *word(STACK_TOP - 4) = (CODE + 0x40) | 1;
    cpu.r[13] = STACK_TOP - 4;
    CHECK_EQ(THUMB(0xbd00), ARM_RETURNED); /* pop {pc}: the hook returns to lr */
    CHECK_EQ(hook_calls, 1);
    CHECK_EQ(cpu.r[0], 0x4242);

    begin("hook redirecting to another hooked address");
    cpu.hook_at = hook_at;
    hooked_address = CODE + 0x40;
    hook_mode = 0;
    hook_calls = 0;
    cpu.r[1] = CODE + 0x40;
    CHECK_EQ(ARM(0xe12fff11u), ARM_HOOK_STOP); /* bx r1 */
    CHECK_EQ(cpu.stop_pc, CODE + 0x40);
    CHECK_EQ(cpu.r[15], CODE + 0x40);
}

/* ROM functions --------------------------------------------------------------------------- */

static int load_module(const char *dir, const char *name, uint32_t base)
{
    char path[512];
    snprintf(path, sizeof path, "%s/%s", dir, name);
    FILE *f = fopen(path, "rb");
    if (!f) {
        printf("cannot open %s\n", path);
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *dest = memory_host(base, (uint32_t) size);
    if (!dest || fread(dest, 1, (size_t) size, f) != (size_t) size) {
        printf("cannot read %s\n", path);
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

static int rom_hook_calls;
static int rom_hook(ArmCpu *c, void *user)
{
    (void) c;
    (void) user;
    rom_hook_calls++;
    return 1;
}

static ArmHook rom_hook_at(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    (void) hook_user;
    return address == 0x01ffd070u ? rom_hook : NULL;
}

static void test_rom(const char *dir)
{
    /* bases from build/adm-kr/rom/modules.json */
    if (!load_module(dir, "main.bin", 0x02000000u) || !load_module(dir, "autoload_2.bin", 0x020e8840u) ||
        !load_module(dir, "itcm.bin", 0x01ff8000u)) {
        current = "rom";
        check(0, "modules loaded");
        return;
    }

    /* func_02050be0 (Thumb): walks {key, value} pairs until the key matches or a key is 0 */
    begin("rom func_02050be0 key lookup");
    uint16_t *table = half(DATA);
    table[0] = 1;
    table[1] = 10;
    table[2] = 2;
    table[3] = 20;
    table[4] = 3;
    table[5] = 30;
    table[6] = 0;
    table[7] = 0;
    cpu.r[0] = 2;
    cpu.r[1] = 1;
    cpu.r[2] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x02050be1u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 20);
    cpu.r[0] = 1;
    cpu.r[1] = 1;
    cpu.r[2] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x02050be1u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 10);
    cpu.r[0] = 3;
    cpu.r[1] = 1;
    cpu.r[2] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x02050be1u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 30);
    cpu.r[0] = 5;
    cpu.r[1] = 1;
    cpu.r[2] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x02050be1u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 5); /* not found: returns the key */

    /* func_02037e0c (ARM): ip = table[r3] ? table[r3] + 2 * (r1 + 16 * r2) : 0, with ranges */
    begin("rom func_02037e0c");
    *word(DATA + 0x18) = 0x1000;
    *word(DATA + 0x1c) = 0x2000;
    cpu.r[0] = DATA;
    cpu.r[1] = 3;
    cpu.r[2] = 5;
    cpu.r[3] = 1;
    CHECK_EQ(arm_call(&cpu, 0x02037e0cu, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0x2000 + 2 * (3 + 5 * 16));
    cpu.r[0] = DATA;
    cpu.r[1] = 3;
    cpu.r[2] = 5;
    cpu.r[3] = 0;
    CHECK_EQ(arm_call(&cpu, 0x02037e0cu, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0x1000 + 2 * (3 + 5 * 16));
    cpu.r[0] = DATA;
    cpu.r[1] = 16;
    cpu.r[2] = 5;
    cpu.r[3] = 0;
    CHECK_EQ(arm_call(&cpu, 0x02037e0cu, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);
    *word(DATA + 0x18) = 0;
    cpu.r[0] = DATA;
    cpu.r[1] = 0;
    cpu.r[2] = 0;
    cpu.r[3] = 0;
    CHECK_EQ(arm_call(&cpu, 0x02037e0cu, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);

    /* MATH_CountPopulation (ARM, autoload_2): a bit count */
    begin("rom MATH_CountPopulation");
    cpu.r[0] = 0xffffffffu;
    CHECK_EQ(arm_call(&cpu, 0x021289d0u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 32);
    cpu.r[0] = 0x12345678u;
    CHECK_EQ(arm_call(&cpu, 0x021289d0u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 13);
    cpu.r[0] = 0;
    CHECK_EQ(arm_call(&cpu, 0x021289d0u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);

    /* func_0205ba70 (ARM): sums the population of 56 words through a BL, times 7777 */
    begin("rom func_0205ba70");
    for (uint32_t i = 0; i < 56; i++) {
        *word(DATA + i * 4) = 1u << (i % 32);
    }
    cpu.r[0] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x0205ba70u, 10000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 56 * 7777);
    CHECK_EQ(cpu.r[13], STACK_TOP);

    /* func_01ffd3e8 (ARM, ITCM): p[0xf] == 0 && (p[0x13] & 8) == 0 */
    begin("rom func_01ffd3e8");
    memset(memory_host(DATA, 0x20), 0, 0x20);
    cpu.r[0] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x01ffd3e8u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 1);
    *byte(DATA + 0x13) = 8;
    cpu.r[0] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x01ffd3e8u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);
    *byte(DATA + 0x13) = 0;
    *byte(DATA + 0x0f) = 1;
    cpu.r[0] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x01ffd3e8u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);

    /* func_01ffcc10 (Thumb, ITCM): (p->unk_00->tag & 0x1f) == 6 && p->p1->unk_34 != 0 ? 0 : 1 */
    begin("rom func_01ffcc10");
    memset(memory_host(DATA, 0x80), 0, 0x80);
    *word(DATA) = DATA + 0x10;     /* unk_00 */
    *word(DATA + 4) = DATA + 0x20; /* p1 */
    *byte(DATA + 0x10) = 0x26;     /* tag: low five bits 6 */
    *word(DATA + 0x20 + 0x34) = 1;
    cpu.r[1] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x01ffcc11u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0);
    *word(DATA + 0x20 + 0x34) = 0;
    cpu.r[1] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x01ffcc11u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 1);
    *byte(DATA + 0x10) = 0x27;
    *word(DATA + 0x20 + 0x34) = 1;
    cpu.r[1] = DATA;
    CHECK_EQ(arm_call(&cpu, 0x01ffcc11u, 1000), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 1);

    /* func_01ffcb9c (Thumb, ITCM): tail-calls func_01ffd070(a, b + 0x150, b + 0x84) via bx */
    begin("rom func_01ffcb9c tail call into a hook");
    cpu.hook_at = rom_hook_at;
    rom_hook_calls = 0;
    cpu.r[0] = 0x11;
    cpu.r[1] = 0x1000;
    CHECK_EQ(arm_call(&cpu, 0x01ffcb9du, 1000), ARM_HOOK_STOP);
    CHECK_EQ(rom_hook_calls, 1);
    CHECK_EQ(cpu.stop_pc, 0x01ffd070u);
    CHECK_EQ(cpu.r[0], 0x11);
    CHECK_EQ(cpu.r[1], 0x1150);
    CHECK_EQ(cpu.r[2], 0x1084);

    /* GetCRC16 (Thumb): swi 0x0e; bx lr */
    begin("rom GetCRC16 is a BIOS call");
    cpu.r[0] = 0xffff;
    CHECK_EQ(arm_call(&cpu, 0x020005c3u, 1000), ARM_SWI);
    CHECK_EQ(cpu.swi, 0xe);
    CHECK_EQ(cpu.stop_pc, 0x020005c2u);
    CHECK_EQ(cpu.r[15], 0x020005c4u);
    cpu.r[0] = 0x1234; /* what the BIOS would return */
    CHECK_EQ(arm_run(&cpu, ARM_RETURN_ADDRESS, 10), ARM_RETURNED);
    CHECK_EQ(cpu.r[0], 0x1234);
}

int main(int argc, char **argv)
{
    const char *rom_dir = argc > 1 ? argv[1] : "build/adm-kr/rom";
    if (memory_init() != 0) {
        printf("memory_init failed\n");
        return 1;
    }

    test_arm_immediates();
    test_arm_shifter();
    test_arm_arithmetic_flags();
    test_arm_conditions();
    test_arm_multiply();
    test_arm_dsp();
    test_arm_load_store();
    test_arm_block_transfer();
    test_arm_branches();
    test_arm_system();
    test_io();
    test_thumb_alu();
    test_thumb_memory();
    test_thumb_branches();
    test_hooks();
    test_rom(rom_dir);

    printf("%d checks, %d failures\n", checks, failures);
    return failures ? 1 : 0;
}
