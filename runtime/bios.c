/* The ARM9 BIOS; see bios.h. The SWI functions follow GBATEK ("BIOS Functions").
 *
 * What the BIOS ROM runs with the CPU in an exception mode is ARM code here too, served at
 * 0xffff0000 like the ROM (bios_io_read): the IRQ vector's handler, which calls the address the
 * SDK stored at DTCM+0x3ffc and returns with "subs pc, lr, #4", and the waits of IntrWait and
 * Halt, which run in SVC mode on the SVC stack like the ROM's so that a thread switched out
 * while waiting (the SDK keeps sp_svc per thread) resumes its wait when switched back. The
 * CPU enters the exceptions itself with the banked registers of each mode (arm.c), so the
 * SDK's OS_SaveContext, OS_LoadContext, OS_IrqHandler_ThreadSwitch and OS_Halt run as the ROM
 * has them. */
#include "bios.h"

#include <string.h>

#include "io.h"

static uint64_t swi_count[256];
static uint32_t swi_first_pc[256];
static uint64_t irq_by_bit[32];

/* The BIOS image ---------------------------------------------------------------------------- */

static uint32_t bios_image[BIOS_SIZE / 4];

static void emit(uint32_t address, const uint32_t *code, size_t count)
{
    memcpy(bios_image + (address - BIOS_BASE) / 4, code, count * 4);
}

/* A "b target" at `at`. */
static void emit_branch(uint32_t at, uint32_t target)
{
    uint32_t word = 0xea000000u | (((target - at - 8) >> 2) & 0x00ffffffu);
    emit(at, &word, 1);
}

static void build_image(void)
{
    /* Every vector spins on itself but the IRQ one: SWIs and undefined instructions stop the
       CPU before vectoring (arm.h), and the game raises no other exception. */
    for (uint32_t v = 0; v < 8; v++) {
        emit_branch(BIOS_BASE + 4 * v, BIOS_BASE + 4 * v);
    }
    emit_branch(BIOS_IRQ_VECTOR, BIOS_IRQ_HANDLER_CODE);

    /* The IRQ handler (GBATEK, "BIOS IRQ handler" for the ARM9): saves the registers a C
       handler may clobber on the IRQ stack, finds the DTCM from CP15 and calls the handler
       address at its end, then returns to the interrupted instruction. */
    static const uint32_t irq_handler[] = {
        0xe92d500fu, /* stmfd sp!, {r0-r3, r12, lr} */
        0xee190f11u, /* mrc p15, 0, r0, c9, c1, 0     ; DTCM region: base in bits 31:12 */
        0xe1a00620u, /* mov r0, r0, lsr #12 */
        0xe1a00600u, /* mov r0, r0, lsl #12 */
        0xe2800901u, /* add r0, r0, #0x4000           ; the end of DTCM */
        0xe5101004u, /* ldr r1, [r0, #-4]             ; DTCM+0x3ffc: the SDK's handler */
        0xe1a0e00fu, /* mov lr, pc                    ; BIOS_IRQ_RETURN */
        0xe12fff11u, /* bx r1 */
        0xe8bd500fu, /* ldmfd sp!, {r0-r3, r12, lr}   ; BIOS_IRQ_RETURN */
        0xe25ef004u, /* subs pc, lr, #4               ; CPSR = SPSR_irq */
    };
    emit(BIOS_IRQ_HANDLER_CODE, irq_handler, sizeof(irq_handler) / 4);

    /* IntrWait(r0 = discard, r1 = flags), entered in SVC mode by the SWI exception with lr
       the return address and SPSR the caller's CPSR; both go on the SVC stack since neither
       survives a thread switch. Turns IME on, drops the flags from the IRQ check bits if
       asked, then waits until a handler sets one of them (the SDK's OS_IrqHandler ORs the
       serviced bit into DTCM+0x3ff8). The test and the wait run with IRQs off so a request
       cannot slip between them: "wait for interrupt" wakes on IE & IF whatever CPSR I says,
       and the request is taken when I is cleared after it (ARM946E-S TRM 2.3.8). */
    static const uint32_t intr_wait[] = {
        0xe14f2000u, /* mrs r2, spsr */
        0xe92d4004u, /* stmfd sp!, {r2, lr} */
        0xe3a02301u, /* mov r2, #0x04000000 */
        0xe3a03001u, /* mov r3, #1 */
        0xe1c232b8u, /* strh r3, [r2, #0x208]         ; IME = 1 */
        0xee192f11u, /* mrc p15, 0, r2, c9, c1, 0 */
        0xe1a02622u, /* mov r2, r2, lsr #12 */
        0xe1a02602u, /* mov r2, r2, lsl #12 */
        0xe2822901u, /* add r2, r2, #0x4000 */
        0xe2422008u, /* sub r2, r2, #8                ; DTCM+0x3ff8: the IRQ check bits */
        0xe3500000u, /* cmp r0, #0 */
        0x0a000002u, /* beq loop */
        0xe5923000u, /* ldr r3, [r2] */
        0xe1c33001u, /* bic r3, r3, r1 */
        0xe5823000u, /* str r3, [r2] */
        0xe321f093u, /* loop: msr cpsr_c, #0x93       ; SVC, IRQs off */
        0xe5923000u, /* ldr r3, [r2] */
        0xe0133001u, /* ands r3, r3, r1 */
        0x1a000002u, /* bne done */
        0xee070f90u, /* mcr p15, 0, r0, c7, c0, 4     ; wait for interrupt */
        0xe321f013u, /* msr cpsr_c, #0x13             ; IRQs on: the request is taken here */
        0xeafffff8u, /* b loop */
        0xe5923000u, /* done: ldr r3, [r2] */
        0xe1c33001u, /* bic r3, r3, r1 */
        0xe5823000u, /* str r3, [r2] */
        0xe8bd4004u, /* ldmfd sp!, {r2, lr} */
        0xe169f002u, /* msr spsr_cf, r2 */
        0xe1b0f00eu, /* movs pc, lr                   ; CPSR = SPSR_svc */
    };
    emit(BIOS_INTR_WAIT, intr_wait, sizeof(intr_wait) / 4);

    /* Halt: one wait, then back to the caller, whose CPSR decides whether the request that
       woke the CPU is taken. */
    static const uint32_t halt[] = {
        0xee070f90u, /* mcr p15, 0, r0, c7, c0, 4 */
        0xe1b0f00eu, /* movs pc, lr */
    };
    emit(BIOS_HALT, halt, sizeof(halt) / 4);
}

int bios_io_read(void *user, uint32_t address, int size, uint32_t *value)
{
    if (address - BIOS_BASE < BIOS_SIZE) {
        uint32_t word = bios_image[(address - BIOS_BASE) / 4];
        uint32_t shift = (address & 3) * 8;
        *value = size == 4 ? word : (word >> shift) & (size == 2 ? 0xffffu : 0xffu);
        return 1;
    }
    return io_read(user, address, size, value);
}

static uint32_t rd32(uint32_t address)
{
    uint32_t v = 0;
    bus_read(address, 4, &v);
    return v;
}

static uint32_t rd16(uint32_t address)
{
    uint32_t v = 0;
    bus_read(address, 2, &v);
    return v;
}

static uint32_t rd8(uint32_t address)
{
    uint32_t v = 0;
    bus_read(address, 1, &v);
    return v;
}

static void wr32(uint32_t address, uint32_t v)
{
    bus_write(address, 4, v);
}

static void wr16(uint32_t address, uint32_t v)
{
    bus_write(address, 2, v);
}

static void wr8(uint32_t address, uint32_t v)
{
    bus_write(address, 1, v);
}

void bios_init(ArmCpu *cpu)
{
    build_image();
    cpu->cpsr = (cpu->cpsr & ~ARM_MODE_MASK) | ARM_MODE_SYSTEM | ARM_CPSR_I | ARM_CPSR_F;
    arm_banked_set(cpu, ARM_MODE_IRQ, 13, BIOS_IRQ_STACK);
    arm_banked_set(cpu, ARM_MODE_SVC, 13, BIOS_SVC_STACK);
}

/* Interrupts: the vector is hooked only to count which request is being serviced (the SDK
 * takes the lowest pending bit first). */
static int hook_irq_vector(ArmCpu *cpu, void *user)
{
    (void) cpu;
    (void) user;
    uint32_t pending = io_irq_pending();
    for (int bit = 0; bit < 32; bit++) {
        if (pending & (1u << bit)) {
            irq_by_bit[bit]++;
            break;
        }
    }
    return 0;
}

ArmHook bios_hook_at(void *user, uint32_t address, void **hook_user)
{
    (void) user;
    (void) hook_user;
    return address == BIOS_IRQ_VECTOR ? hook_irq_vector : NULL;
}

/* SWI functions ---------------------------------------------------------------------------- */

static void cpu_set(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1], ctl = cpu->r[2];
    uint32_t count = ctl & 0x1fffffu;
    int fill = (ctl >> 24) & 1, words = (ctl >> 26) & 1;
    uint32_t v = words ? rd32(src) : rd16(src);
    for (uint32_t i = 0; i < count; i++) {
        if (words) {
            wr32(dst + 4 * i, fill ? v : rd32(src + 4 * i));
        } else {
            wr16(dst + 2 * i, fill ? v : rd16(src + 2 * i));
        }
    }
}

static void cpu_fast_set(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1], ctl = cpu->r[2];
    uint32_t count = ctl & 0x1fffffu;
    int fill = (ctl >> 24) & 1;
    uint32_t v = rd32(src);
    /* the word count is used as given; the GBA's rounding up to 8 is not the DS's */
    for (uint32_t i = 0; i < count; i++) {
        wr32(dst + 4 * i, fill ? v : rd32(src + 4 * i));
    }
}

static uint32_t crc16(uint32_t crc, uint32_t address, uint32_t length)
{
    crc &= 0xffffu;
    length &= ~1u; /* lengths are even on the DS BIOS; an odd byte is not read */
    for (uint32_t i = 0; i < length; i++) {
        crc ^= rd8(address + i);
        for (int k = 0; k < 8; k++) {
            uint32_t carry = crc & 1;
            crc >>= 1;
            if (carry) {
                crc ^= 0xa001u;
            }
        }
    }
    return crc & 0xffffu;
}

static void bit_unpack(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1], info = cpu->r[2];
    uint32_t len = rd16(info), sw = rd8(info + 2), dw = rd8(info + 3), off = rd32(info + 4);
    uint32_t zero_flag = off >> 31, base = off & 0x7fffffffu;
    uint32_t mask = (1u << sw) - 1u, acc = 0, bits = 0;
    for (uint32_t i = 0; i < len; i++) {
        uint32_t b = rd8(src + i);
        for (uint32_t k = 0; k < 8; k += sw) {
            uint32_t v = (b >> k) & mask;
            if (v != 0 || zero_flag) {
                v += base;
            }
            acc |= v << bits;
            bits += dw;
            if (bits >= 32) {
                wr32(dst, acc);
                dst += 4;
                acc = 0;
                bits = 0;
            }
        }
    }
    if (bits) {
        wr32(dst, acc);
    }
}

static void lz77(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1];
    uint32_t size = rd32(src) >> 8, out = 0;
    src += 4;
    while (out < size) {
        uint32_t flags = rd8(src++);
        for (int k = 0; k < 8 && out < size; k++, flags <<= 1) {
            if (flags & 0x80) {
                uint32_t b0 = rd8(src), b1 = rd8(src + 1);
                uint32_t len = (b0 >> 4) + 3, disp = (((b0 & 15) << 8) | b1) + 1;
                src += 2;
                for (uint32_t j = 0; j < len && out < size; j++, out++) {
                    wr8(dst + out, rd8(dst + out - disp));
                }
            } else {
                wr8(dst + out, rd8(src++));
                out++;
            }
        }
    }
}

static void rl(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1];
    uint32_t size = rd32(src) >> 8, out = 0;
    src += 4;
    while (out < size) {
        uint32_t f = rd8(src++);
        if (f & 0x80) {
            uint32_t len = (f & 0x7f) + 3, v = rd8(src++);
            for (uint32_t j = 0; j < len && out < size; j++, out++) {
                wr8(dst + out, v);
            }
        } else {
            uint32_t len = (f & 0x7f) + 1;
            for (uint32_t j = 0; j < len && out < size; j++, out++) {
                wr8(dst + out, rd8(src++));
            }
        }
    }
}

static void diff8(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1];
    uint32_t size = rd32(src) >> 8, prev = 0;
    src += 4;
    for (uint32_t i = 0; i < size; i++) {
        prev = (prev + rd8(src + i)) & 0xffu;
        wr8(dst + i, prev);
    }
}

static void diff16(ArmCpu *cpu)
{
    uint32_t src = cpu->r[0], dst = cpu->r[1];
    uint32_t size = rd32(src) >> 8, prev = 0;
    src += 4;
    for (uint32_t i = 0; i + 1 < size; i += 2) {
        prev = (prev + rd16(src + i)) & 0xffffu;
        wr16(dst + i, prev);
    }
}

int bios_swi(ArmCpu *cpu)
{
    uint32_t n = (cpu->cpsr & ARM_CPSR_T) ? (cpu->swi & 0xffu) : ((cpu->swi >> 16) & 0xffu);
    if (swi_count[n]++ == 0) {
        swi_first_pc[n] = cpu->r[15] - ((cpu->cpsr & ARM_CPSR_T) ? 2 : 4);
    }
    switch (n) {
        case 0x03: /* WaitByLoop(r0): a 4-cycle loop per count on the 66 MHz core */
            io_advance(cpu->r[0] * 2);
            return 0;
        case 0x04: /* IntrWait(discard, flags) */
        case 0x05: /* VBlankIntrWait = IntrWait(1, 1) */
            if (n == 5) {
                cpu->r[0] = 1;
                cpu->r[1] = 1;
            }
            arm_enter_exception(cpu, ARM_EXC_SWI);
            cpu->r[15] = BIOS_INTR_WAIT;
            return 0;
        case 0x06: /* Halt */
            arm_enter_exception(cpu, ARM_EXC_SWI);
            cpu->r[15] = BIOS_HALT;
            return 0;
        case 0x09: { /* Div(num, den): r0 quotient, r1 remainder, r3 |quotient| */
            int32_t num = (int32_t) cpu->r[0], den = (int32_t) cpu->r[1];
            if (den == 0) {
                return -1; /* the BIOS loops forever; the game never does this */
            }
            int32_t q = (num == INT32_MIN && den == -1) ? INT32_MIN : num / den;
            int32_t m = (num == INT32_MIN && den == -1) ? 0 : num % den;
            cpu->r[0] = (uint32_t) q;
            cpu->r[1] = (uint32_t) m;
            cpu->r[3] = q < 0 ? 0u - (uint32_t) q : (uint32_t) q;
            return 0;
        }
        case 0x0b:
            cpu_set(cpu);
            return 0;
        case 0x0c:
            cpu_fast_set(cpu);
            return 0;
        case 0x0d: { /* Sqrt */
            uint32_t v = cpu->r[0], res = 0, bit = 1u << 30;
            while (bit > v) {
                bit >>= 2;
            }
            while (bit) {
                if (v >= res + bit) {
                    v -= res + bit;
                    res = (res >> 1) + bit;
                } else {
                    res >>= 1;
                }
                bit >>= 2;
            }
            cpu->r[0] = res;
            return 0;
        }
        case 0x0e:
            cpu->r[0] = crc16(cpu->r[0], cpu->r[1], cpu->r[2]);
            return 0;
        case 0x0f: /* IsDebugger: a retail unit */
            cpu->r[0] = 0;
            return 0;
        case 0x10:
            bit_unpack(cpu);
            return 0;
        case 0x11:
            lz77(cpu);
            return 0;
        case 0x14:
            rl(cpu);
            return 0;
        case 0x16:
            diff8(cpu);
            return 0;
        case 0x18:
            diff16(cpu);
            return 0;
        default: /* 0x00 SoftReset, 0x12/0x13/0x15 the callback decompressors, and the rest */
            return -1;
    }
}

static const char *swi_name(uint32_t n)
{
    switch (n) {
        case 0x00:
            return "SoftReset";
        case 0x03:
            return "WaitByLoop";
        case 0x04:
            return "IntrWait";
        case 0x05:
            return "VBlankIntrWait";
        case 0x06:
            return "Halt";
        case 0x09:
            return "Div";
        case 0x0b:
            return "CpuSet";
        case 0x0c:
            return "CpuFastSet";
        case 0x0d:
            return "Sqrt";
        case 0x0e:
            return "GetCRC16";
        case 0x0f:
            return "IsDebugger";
        case 0x10:
            return "BitUnPack";
        case 0x11:
            return "LZ77UnCompReadNormalWrite8bit";
        case 0x12:
            return "LZ77UnCompReadByCallbackWrite16bit";
        case 0x13:
            return "HuffUnCompReadByCallback";
        case 0x14:
            return "RLUnCompReadNormalWrite8bit";
        case 0x15:
            return "RLUnCompReadByCallbackWrite16bit";
        case 0x16:
            return "Diff8bitUnFilterWram";
        case 0x18:
            return "Diff16bitUnFilter";
        case 0x1f:
            return "CustomPost";
        default:
            return "?";
    }
}

void bios_report(const ArmCpu *cpu, FILE *out)
{
    fprintf(out, "bios: %llu interrupts taken\n", (unsigned long long) cpu->irq_taken);
    fprintf(out, "  interrupts by lowest pending bit:");
    for (int bit = 0; bit < 32; bit++) {
        if (irq_by_bit[bit]) {
            fprintf(out, " %d:%llu", bit, (unsigned long long) irq_by_bit[bit]);
        }
    }
    fprintf(out, "\n");
    for (uint32_t n = 0; n < 256; n++) {
        if (swi_count[n]) {
            fprintf(out, "  swi 0x%02x %-36s %10llu  first at %08x\n", n, swi_name(n), (unsigned long long) swi_count[n],
                    swi_first_pc[n]);
        }
    }
}
