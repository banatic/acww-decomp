/* An ARMv5TE interpreter: the ARM946E-S as the game sees it.
 *
 * Execution is one instruction at a time from cpu->r[15]. While an instruction runs, r[15]
 * already holds the address of the next one; reads of r15 as an operand see the pipeline
 * value (the instruction's address + 8 in ARM state, + 4 in Thumb state) as the hardware does.
 *
 * Every instruction handler returns CONTINUE or an ArmStop. Memory goes through the helpers
 * at the top, which fall back to the I/O callbacks and record the faulting address.
 *
 * Choices where the architecture leaves room (ARM DDI 0100I is "the ARM ARM" below):
 *   - A word load from an unaligned address rotates the aligned word right by 8 * (address & 3)
 *     (ARM ARM A2.8, "Unaligned data access" with alignment checking off, as the DS runs).
 *   - Halfword loads and stores, including LDRSH, force the address even: the ARM ARM calls an
 *     unaligned halfword access UNPREDICTABLE, and the ARM946E-S ignores address bit 0 (GBATEK,
 *     "Mis-aligned LDRH, LDRSH" for the ARM9). This differs from the ARM7, which sign-extends a
 *     byte for an odd LDRSH.
 *   - A store of r15 (STR, STM) writes the instruction's address + 12, the value the ARM9
 *     pipeline exposes (ARM ARM A2.4.3 allows + 8 or + 12).
 *   - Data-processing results written to r15 stay in the current state with bits 1:0 cleared
 *     (ARMv5 does not interwork there; ARM ARM A4.1.x "if S == 0 and Rd == R15"). LDR, LDM and
 *     Thumb POP into r15 do interwork on v5T (ARM ARM A4.1.23, A4.1.20).
 *   - STM with writeback and the base in the list stores the original base when the base is the
 *     lowest register, the written-back value otherwise (ARM ARM A4.1.97: UNPREDICTABLE in the
 *     second case; this is what the ARM9 does). LDM with the base in the list keeps the loaded
 *     value.
 *   - The seven processor modes have their banked registers and SPSRs (ARM ARM A2.3, A2.5):
 *     cpu->r is always the current mode's view and the others' registers wait in the banks.
 *     A mode change (MSR, an exception, a CPSR restore) swaps r13 and r14, r8-r14 for FIQ.
 *     A CPSR restore (data-processing with S and Rd == r15, LDM with ^ and r15) in user or
 *     system mode, which have no SPSR, is UNPREDICTABLE; here it leaves the CPSR alone.
 *   - An MSR that writes the mode bits with a value that is not a mode (the game's crt0 never
 *     does) is UNPREDICTABLE; here such a value banks like user mode.
 *   - Exceptions are entered through arm_enter_exception; IRQs are taken between instructions
 *     when irq_line is set and CPSR I clear. SWI and undefined instructions stop the run
 *     instead of vectoring (the BIOS is in C, see bios.c), but a caller can vector them.
 *   - CP15 is a register file: MCR stores, MRC reads back, c0 is the ARM946E-S identification,
 *     c7 operations are cache maintenance (ignored) and "wait for interrupt" (ARM_HALT). The
 *     coprocessor is privileged: user mode gets the undefined instruction. Other coprocessors
 *     are undefined.
 */
#include "arm.h"

#include <stdio.h>
#include <string.h>

#include "memory.h"

enum { CONTINUE = -1 };

/* Modes and banks --------------------------------------------------------------------------- */

/* The bank arrays and SPSR of a mode other than user/system, or NULL for those two. */
static uint32_t *bank_of(ArmCpu *cpu, uint32_t mode, uint32_t **spsr)
{
    switch (mode & ARM_MODE_MASK) {
        case ARM_MODE_FIQ:
            *spsr = &cpu->spsr_fiq;
            return cpu->bank_fiq;
        case ARM_MODE_IRQ:
            *spsr = &cpu->spsr_irq;
            return cpu->bank_irq;
        case ARM_MODE_SVC:
            *spsr = &cpu->spsr_svc;
            return cpu->bank_svc;
        case ARM_MODE_ABORT:
            *spsr = &cpu->spsr_abt;
            return cpu->bank_abt;
        case ARM_MODE_UNDEFINED:
            *spsr = &cpu->spsr_und;
            return cpu->bank_und;
        default: /* user, system, and values that are not a mode */
            *spsr = NULL;
            return NULL;
    }
}

static int is_fiq(uint32_t mode)
{
    return (mode & ARM_MODE_MASK) == ARM_MODE_FIQ;
}

/* The modes with an SPSR are the five that have a bank. */
static int has_spsr(ArmCpu *cpu, uint32_t mode)
{
    uint32_t *spsr;
    return bank_of(cpu, mode, &spsr) != NULL;
}

/* Parks the current mode's registers in its bank and brings in `mode`'s (ARM ARM A2.3: r13,
 * r14 and the SPSR per mode; FIQ also r8-r12). user and system share one set. */
static void switch_mode(ArmCpu *cpu, uint32_t mode)
{
    uint32_t from = cpu->cpsr & ARM_MODE_MASK, to = mode & ARM_MODE_MASK;
    uint32_t *from_spsr, *to_spsr;
    uint32_t *from_bank = bank_of(cpu, from, &from_spsr);
    uint32_t *to_bank = bank_of(cpu, to, &to_spsr);
    if (from == to || (from_bank == NULL && to_bank == NULL)) {
        return;
    }
    /* Leave: user/system park r13 and r14 in bank_usr, which keeps them for as long as another
       mode runs; a mode with a bank parks its own there, and FIQ also gives r8-r12 back to
       user, whose copies it displaced on entry. */
    if (from_bank == NULL) {
        cpu->bank_usr[5] = cpu->r[13];
        cpu->bank_usr[6] = cpu->r[14];
    } else if (is_fiq(from)) {
        memcpy(cpu->bank_fiq, cpu->r + 8, 7 * sizeof(uint32_t));
        memcpy(cpu->r + 8, cpu->bank_usr, 5 * sizeof(uint32_t));
    } else {
        from_bank[0] = cpu->r[13];
        from_bank[1] = cpu->r[14];
    }
    if (from_spsr != NULL) {
        *from_spsr = cpu->spsr;
    }
    /* Enter: the mirror image. r8-r12 are user's whenever FIQ is not running. */
    if (to_bank == NULL) {
        cpu->r[13] = cpu->bank_usr[5];
        cpu->r[14] = cpu->bank_usr[6];
    } else if (is_fiq(to)) {
        memcpy(cpu->bank_usr, cpu->r + 8, 5 * sizeof(uint32_t));
        memcpy(cpu->r + 8, cpu->bank_fiq, 7 * sizeof(uint32_t));
    } else {
        cpu->r[13] = to_bank[0];
        cpu->r[14] = to_bank[1];
    }
    if (to_spsr != NULL) {
        cpu->spsr = *to_spsr;
    }
}

void arm_set_cpsr(ArmCpu *cpu, uint32_t cpsr)
{
    switch_mode(cpu, cpsr);
    cpu->cpsr = cpsr;
}

/* The user-mode register `index` (8-14) as seen from the current mode: cpu->r when the
 * current mode shares it, else the parked copy (for LDM/STM with ^, ARM ARM A4.1.21, A4.1.98). */
static uint32_t *user_register(ArmCpu *cpu, uint32_t index)
{
    uint32_t mode = cpu->cpsr & ARM_MODE_MASK;
    if (index < 8 || mode == ARM_MODE_USER || mode == ARM_MODE_SYSTEM || mode < ARM_MODE_USER) {
        return cpu->r + index;
    }
    if (index >= 13 || is_fiq(mode)) {
        return cpu->bank_usr + (index - 8);
    }
    return cpu->r + index;
}

uint32_t arm_banked_get(const ArmCpu *cpu, uint32_t mode, int index)
{
    ArmCpu *c = (ArmCpu *) cpu;
    uint32_t current = cpu->cpsr & ARM_MODE_MASK;
    uint32_t *spsr;
    mode &= ARM_MODE_MASK;
    if (mode == ARM_MODE_SYSTEM) {
        mode = ARM_MODE_USER;
    }
    if (current == ARM_MODE_SYSTEM) {
        current = ARM_MODE_USER;
    }
    if (mode == current) {
        return cpu->r[index];
    }
    uint32_t *bank = bank_of(c, mode, &spsr);
    if (bank == NULL) {
        return *user_register(c, (uint32_t) index);
    }
    if (is_fiq(mode)) {
        return bank[index - 8];
    }
    return index >= 13 ? bank[index - 13] : *user_register(c, (uint32_t) index);
}

void arm_banked_set(ArmCpu *cpu, uint32_t mode, int index, uint32_t value)
{
    uint32_t current = cpu->cpsr & ARM_MODE_MASK;
    uint32_t *spsr;
    mode &= ARM_MODE_MASK;
    if (mode == ARM_MODE_SYSTEM) {
        mode = ARM_MODE_USER;
    }
    if (current == ARM_MODE_SYSTEM) {
        current = ARM_MODE_USER;
    }
    if (mode == current) {
        cpu->r[index] = value;
        return;
    }
    uint32_t *bank = bank_of(cpu, mode, &spsr);
    if (bank == NULL) {
        *user_register(cpu, (uint32_t) index) = value;
    } else if (is_fiq(mode)) {
        bank[index - 8] = value;
    } else if (index >= 13) {
        bank[index - 13] = value;
    } else {
        *user_register(cpu, (uint32_t) index) = value; /* r8-r12 are user's outside FIQ */
    }
}

/* Restores the CPSR from the SPSR: the S-bit forms with Rd == r15 and LDM with ^ and r15. In
 * user and system mode there is none (UNPREDICTABLE); the CPSR is left alone. */
static void restore_cpsr(ArmCpu *cpu)
{
    if (has_spsr(cpu, cpu->cpsr)) {
        arm_set_cpsr(cpu, cpu->spsr);
    }
}

/* Memory --------------------------------------------------------------------------------- */

/* Each access helper returns nonzero on success. The DS address is the host address (see
 * memory.h); what memory_host does not map goes to the I/O callbacks. */

static int read_word(ArmCpu *cpu, uint32_t address, uint32_t *value)
{
    address &= ~3u;
    uint8_t *p = memory_host(address, 4);
    if (p) {
        memcpy(value, p, 4);
        return 1;
    }
    if (cpu->io_read && cpu->io_read(cpu->io_user, address, 4, value)) {
        return 1;
    }
    cpu->fault_address = address;
    return 0;
}

static int read_half(ArmCpu *cpu, uint32_t address, uint32_t *value)
{
    address &= ~1u;
    uint8_t *p = memory_host(address, 2);
    if (p) {
        *value = (uint32_t) p[0] | ((uint32_t) p[1] << 8);
        return 1;
    }
    if (cpu->io_read && cpu->io_read(cpu->io_user, address, 2, value)) {
        *value &= 0xffffu;
        return 1;
    }
    cpu->fault_address = address;
    return 0;
}

static int read_byte(ArmCpu *cpu, uint32_t address, uint32_t *value)
{
    uint8_t *p = memory_host(address, 1);
    if (p) {
        *value = *p;
        return 1;
    }
    if (cpu->io_read && cpu->io_read(cpu->io_user, address, 1, value)) {
        *value &= 0xffu;
        return 1;
    }
    cpu->fault_address = address;
    return 0;
}

/* A word load as the ARM9 does it: the aligned word, rotated so the addressed byte lands in the
 * low byte. An aligned address loads the word unchanged. */
static int load_word(ArmCpu *cpu, uint32_t address, uint32_t *value)
{
    uint32_t word;
    if (!read_word(cpu, address, &word)) {
        return 0;
    }
    uint32_t rotate = (address & 3u) * 8;
    *value = rotate ? (word >> rotate) | (word << (32 - rotate)) : word;
    return 1;
}

static int write_word(ArmCpu *cpu, uint32_t address, uint32_t value)
{
    address &= ~3u;
    uint8_t *p = memory_host(address, 4);
    if (p) {
        memcpy(p, &value, 4);
        return 1;
    }
    if (cpu->io_write && cpu->io_write(cpu->io_user, address, 4, value)) {
        return 1;
    }
    cpu->fault_address = address;
    return 0;
}

static int write_half(ArmCpu *cpu, uint32_t address, uint32_t value)
{
    address &= ~1u;
    uint8_t *p = memory_host(address, 2);
    if (p) {
        p[0] = (uint8_t) value;
        p[1] = (uint8_t) (value >> 8);
        return 1;
    }
    if (cpu->io_write && cpu->io_write(cpu->io_user, address, 2, value & 0xffffu)) {
        return 1;
    }
    cpu->fault_address = address;
    return 0;
}

static int write_byte(ArmCpu *cpu, uint32_t address, uint32_t value)
{
    uint8_t *p = memory_host(address, 1);
    if (p) {
        *p = (uint8_t) value;
        return 1;
    }
    if (cpu->io_write && cpu->io_write(cpu->io_user, address, 1, value & 0xffu)) {
        return 1;
    }
    cpu->fault_address = address;
    return 0;
}

/* Flags and arithmetic ------------------------------------------------------------------- */

static int condition_passed(uint32_t cpsr, uint32_t cond)
{
    uint32_t n = (cpsr >> 31) & 1, z = (cpsr >> 30) & 1, c = (cpsr >> 29) & 1, v = (cpsr >> 28) & 1;
    switch (cond) {
        case 0x0:
            return z;
        case 0x1:
            return !z;
        case 0x2:
            return c;
        case 0x3:
            return !c;
        case 0x4:
            return n;
        case 0x5:
            return !n;
        case 0x6:
            return v;
        case 0x7:
            return !v;
        case 0x8:
            return c && !z;
        case 0x9:
            return !c || z;
        case 0xa:
            return n == v;
        case 0xb:
            return n != v;
        case 0xc:
            return !z && n == v;
        case 0xd:
            return z || n != v;
        default:
            /* AL, and NV which ARMv5 reuses for unconditional instructions */
            return 1;
    }
}

static void set_nz(ArmCpu *cpu, uint32_t result)
{
    uint32_t cpsr = cpu->cpsr & ~(ARM_CPSR_N | ARM_CPSR_Z);
    cpsr |= result & ARM_CPSR_N;
    if (result == 0) {
        cpsr |= ARM_CPSR_Z;
    }
    cpu->cpsr = cpsr;
}

/* N Z C from a logical result, with the shifter's carry-out; V is untouched. */
static void set_nzc(ArmCpu *cpu, uint32_t result, uint32_t carry)
{
    uint32_t cpsr = cpu->cpsr & ~(ARM_CPSR_N | ARM_CPSR_Z | ARM_CPSR_C);
    cpsr |= result & ARM_CPSR_N;
    if (result == 0) {
        cpsr |= ARM_CPSR_Z;
    }
    cpsr |= carry << 29;
    cpu->cpsr = cpsr;
}

static void set_nzcv(ArmCpu *cpu, uint32_t result, uint32_t carry, uint32_t overflow)
{
    uint32_t cpsr = cpu->cpsr & ~(ARM_CPSR_N | ARM_CPSR_Z | ARM_CPSR_C | ARM_CPSR_V);
    cpsr |= result & ARM_CPSR_N;
    if (result == 0) {
        cpsr |= ARM_CPSR_Z;
    }
    cpsr |= (carry << 29) | (overflow << 28);
    cpu->cpsr = cpsr;
}

/* a + b + carry_in, setting all four flags. */
static uint32_t add_with_flags(ArmCpu *cpu, uint32_t a, uint32_t b, uint32_t carry_in)
{
    uint64_t wide = (uint64_t) a + b + carry_in;
    uint32_t result = (uint32_t) wide;
    uint32_t overflow = (~(a ^ b) & (a ^ result)) >> 31;
    set_nzcv(cpu, result, (uint32_t) (wide >> 32), overflow);
    return result;
}

/* a - b - !carry_in: the ARM subtract, whose C flag is "no borrow". */
static uint32_t sub_with_flags(ArmCpu *cpu, uint32_t a, uint32_t b, uint32_t carry_in)
{
    uint64_t wide = (uint64_t) a - b - (carry_in ^ 1);
    uint32_t result = (uint32_t) wide;
    uint32_t overflow = ((a ^ b) & (a ^ result)) >> 31;
    set_nzcv(cpu, result, (uint32_t) ((wide >> 32) & 1) ^ 1, overflow);
    return result;
}

static uint32_t rotate_right(uint32_t value, uint32_t amount)
{
    amount &= 31;
    return amount ? (value >> amount) | (value << (32 - amount)) : value;
}

/* The ARM shifter with an immediate amount (ARM ARM A5.1.5 to A5.1.13). Amount 0 encodes LSL
 * #0 (no change), LSR #32, ASR #32 and RRX. `carry` holds C on entry and the carry-out on exit. */
static uint32_t shift_immediate(uint32_t type, uint32_t value, uint32_t amount, uint32_t *carry)
{
    switch (type) {
        case 0:
            if (amount) {
                *carry = (value >> (32 - amount)) & 1;
                value <<= amount;
            }
            return value;
        case 1:
            if (amount == 0) {
                *carry = value >> 31;
                return 0;
            }
            *carry = (value >> (amount - 1)) & 1;
            return value >> amount;
        case 2:
            if (amount == 0) {
                *carry = value >> 31;
                return (uint32_t) ((int32_t) value >> 31);
            }
            *carry = (value >> (amount - 1)) & 1;
            return (uint32_t) ((int32_t) value >> amount);
        default:
            if (amount == 0) {
                uint32_t result = (*carry << 31) | (value >> 1);
                *carry = value & 1;
                return result;
            }
            *carry = (value >> (amount - 1)) & 1;
            return rotate_right(value, amount);
    }
}

/* The shifter with a register amount, 0..255 (ARM ARM A5.1.6, 8, 10, 12). */
static uint32_t shift_register(uint32_t type, uint32_t value, uint32_t amount, uint32_t *carry)
{
    if (amount == 0) {
        return value;
    }
    switch (type) {
        case 0:
            if (amount < 32) {
                *carry = (value >> (32 - amount)) & 1;
                return value << amount;
            }
            *carry = amount == 32 ? value & 1 : 0;
            return 0;
        case 1:
            if (amount < 32) {
                *carry = (value >> (amount - 1)) & 1;
                return value >> amount;
            }
            *carry = amount == 32 ? value >> 31 : 0;
            return 0;
        case 2:
            if (amount < 32) {
                *carry = (value >> (amount - 1)) & 1;
                return (uint32_t) ((int32_t) value >> amount);
            }
            *carry = value >> 31;
            return (uint32_t) ((int32_t) value >> 31);
        default:
            amount &= 31;
            if (amount == 0) {
                *carry = value >> 31;
                return value;
            }
            *carry = (value >> (amount - 1)) & 1;
            return rotate_right(value, amount);
    }
}

/* Signed 32-bit saturation for the DSP instructions; sets Q when it clips. */
static int32_t saturate_add(ArmCpu *cpu, int32_t a, int32_t b)
{
    int64_t sum = (int64_t) a + b;
    if (sum > INT32_MAX) {
        cpu->cpsr |= ARM_CPSR_Q;
        return INT32_MAX;
    }
    if (sum < INT32_MIN) {
        cpu->cpsr |= ARM_CPSR_Q;
        return INT32_MIN;
    }
    return (int32_t) sum;
}

static int32_t saturate_sub(ArmCpu *cpu, int32_t a, int32_t b)
{
    int64_t diff = (int64_t) a - b;
    if (diff > INT32_MAX) {
        cpu->cpsr |= ARM_CPSR_Q;
        return INT32_MAX;
    }
    if (diff < INT32_MIN) {
        cpu->cpsr |= ARM_CPSR_Q;
        return INT32_MIN;
    }
    return (int32_t) diff;
}

/* a + b, wrapping, with Q set on signed overflow: the accumulate step of SMLAxy and SMLAWy
 * (ARM ARM A4.1.76: "the result is not saturated"). */
static int32_t add_setting_q(ArmCpu *cpu, int32_t a, int32_t b)
{
    uint32_t result = (uint32_t) a + (uint32_t) b;
    if ((~((uint32_t) a ^ (uint32_t) b) & ((uint32_t) a ^ result)) >> 31) {
        cpu->cpsr |= ARM_CPSR_Q;
    }
    return (int32_t) result;
}

static uint32_t count_leading_zeros(uint32_t value)
{
    uint32_t n = 0;
    if (value == 0) {
        return 32;
    }
    while (!(value & 0x80000000u)) {
        value <<= 1;
        n++;
    }
    return n;
}

static uint32_t count_bits(uint32_t value)
{
    uint32_t n = 0;
    while (value) {
        value &= value - 1;
        n++;
    }
    return n;
}

/* Branching ------------------------------------------------------------------------------ */

/* Continue at `target` in the current state. Stops when the target is the private return
 * address, or when a hook there asks to. A hook may redirect execution; the new target is
 * checked in turn so a redirect to the return address, or to another hooked function, works. */
static int jump(ArmCpu *cpu, uint32_t target)
{
    for (;;) {
        target &= ~1u;
        cpu->r[15] = target;
        if (target == ARM_RETURN_ADDRESS) {
            cpu->stop_pc = target;
            return ARM_RETURNED;
        }
        if (!cpu->hook_at) {
            return CONTINUE;
        }
        void *user = NULL;
        ArmHook hook = cpu->hook_at(cpu->hook_user, target, &user);
        if (!hook) {
            return CONTINUE;
        }
        int asked = hook(cpu, user);
        if (asked == 1) {
            cpu->stop_pc = target;
            return ARM_HOOK_STOP;
        }
        if (asked != ARM_HOOK_AGAIN && cpu->r[15] == target) {
            return CONTINUE;
        }
        target = cpu->r[15];
    }
}

/* BX semantics: bit 0 selects Thumb (ARM ARM A4.1.10). An ARM target ignores bit 1 as well. */
static int jump_interworking(ArmCpu *cpu, uint32_t target)
{
    if (target & 1) {
        cpu->cpsr |= ARM_CPSR_T;
        return jump(cpu, target & ~1u);
    }
    cpu->cpsr &= ~ARM_CPSR_T;
    return jump(cpu, target & ~3u);
}

/* A jump after a CPSR restore: the state comes from the restored T bit, not from the address
 * (ARM ARM A4.1.35 "if S == 1 and Rd == R15", A4.1.22 LDM(3)). */
static int jump_in_state(ArmCpu *cpu, uint32_t target)
{
    return jump(cpu, (cpu->cpsr & ARM_CPSR_T) ? target & ~1u : target & ~3u);
}

/* ARM state ------------------------------------------------------------------------------ */

/* An operand read of r15 sees the instruction address + 8. */
#define ARM_REG(n) ((n) == 15 ? pc + 8 : cpu->r[n])

static int arm_data_processing(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t opcode = (instr >> 21) & 15;
    uint32_t s = (instr >> 20) & 1;
    uint32_t rn = (instr >> 16) & 15;
    uint32_t rd = (instr >> 12) & 15;
    uint32_t carry = (cpu->cpsr >> 29) & 1;
    uint32_t operand;

    if (instr & (1u << 25)) {
        uint32_t rotate = (instr >> 7) & 0x1e;
        operand = rotate_right(instr & 0xff, rotate);
        if (rotate) {
            carry = operand >> 31;
        }
    } else {
        uint32_t type = (instr >> 5) & 3;
        uint32_t rm = instr & 15;
        if (instr & (1u << 4)) {
            uint32_t amount = cpu->r[(instr >> 8) & 15] & 0xff;
            operand = shift_register(type, ARM_REG(rm), amount, &carry);
        } else {
            operand = shift_immediate(type, ARM_REG(rm), (instr >> 7) & 31, &carry);
        }
    }

    uint32_t a = ARM_REG(rn);
    uint32_t result;
    int writes_rd = 1;

    /* With Rd == r15 the flags are not set: S there means "CPSR = SPSR" after the result
     * (ARM ARM A4.1.35 and the others), done below. The flag-setting helpers run only for
     * s && rd != 15. */
    int flags = s && rd != 15;
    uint32_t c_in = (cpu->cpsr >> 29) & 1;

    switch (opcode) {
        case 0x0: /* AND */
            result = a & operand;
            goto logical;
        case 0x1: /* EOR */
            result = a ^ operand;
            goto logical;
        case 0x2: /* SUB */
            result = flags ? sub_with_flags(cpu, a, operand, 1) : a - operand;
            break;
        case 0x3: /* RSB */
            result = flags ? sub_with_flags(cpu, operand, a, 1) : operand - a;
            break;
        case 0x4: /* ADD */
            result = flags ? add_with_flags(cpu, a, operand, 0) : a + operand;
            break;
        case 0x5: /* ADC */
            result = flags ? add_with_flags(cpu, a, operand, c_in) : a + operand + c_in;
            break;
        case 0x6: /* SBC */
            result = flags ? sub_with_flags(cpu, a, operand, c_in) : a - operand - (c_in ^ 1);
            break;
        case 0x7: /* RSC */
            result = flags ? sub_with_flags(cpu, operand, a, c_in) : operand - a - (c_in ^ 1);
            break;
        case 0x8: /* TST */
            result = a & operand;
            writes_rd = 0;
            goto logical;
        case 0x9: /* TEQ */
            result = a ^ operand;
            writes_rd = 0;
            goto logical;
        case 0xa: /* CMP */
            result = sub_with_flags(cpu, a, operand, 1);
            writes_rd = 0;
            break;
        case 0xb: /* CMN */
            result = add_with_flags(cpu, a, operand, 0);
            writes_rd = 0;
            break;
        case 0xc: /* ORR */
            result = a | operand;
            goto logical;
        case 0xd: /* MOV */
            result = operand;
            goto logical;
        case 0xe: /* BIC */
            result = a & ~operand;
            goto logical;
        default: /* MVN */
            result = ~operand;
        logical:
            if (flags) {
                set_nzc(cpu, result, carry);
            }
            break;
    }

    if (!writes_rd) {
        return CONTINUE;
    }
    if (rd == 15) {
        if (s) {
            /* the exception return: "subs pc, lr, #4", "movs pc, lr" */
            restore_cpsr(cpu);
            return jump_in_state(cpu, result);
        }
        return jump(cpu, result & ~3u);
    }
    cpu->r[rd] = result;
    return CONTINUE;
}

static int arm_multiply(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t s = (instr >> 20) & 1;
    uint32_t rd = (instr >> 16) & 15; /* RdHi for the long forms */
    uint32_t rn = (instr >> 12) & 15; /* RdLo for the long forms */
    uint32_t rs = (instr >> 8) & 15;
    uint32_t rm = instr & 15;
    (void) pc;

    switch ((instr >> 21) & 7) {
        case 0: { /* MUL */
            uint32_t result = cpu->r[rm] * cpu->r[rs];
            cpu->r[rd] = result;
            if (s) {
                set_nz(cpu, result);
            }
            return CONTINUE;
        }
        case 1: { /* MLA */
            uint32_t result = cpu->r[rm] * cpu->r[rs] + cpu->r[rn];
            cpu->r[rd] = result;
            if (s) {
                set_nz(cpu, result);
            }
            return CONTINUE;
        }
        case 4:   /* UMULL */
        case 5:   /* UMLAL */
        case 6:   /* SMULL */
        case 7: { /* SMLAL */
            uint64_t product;
            if (instr & (1u << 22)) {
                product = (uint64_t) ((int64_t) (int32_t) cpu->r[rm] * (int32_t) cpu->r[rs]);
            } else {
                product = (uint64_t) cpu->r[rm] * cpu->r[rs];
            }
            if (instr & (1u << 21)) {
                product += ((uint64_t) cpu->r[rd] << 32) | cpu->r[rn];
            }
            cpu->r[rn] = (uint32_t) product;
            cpu->r[rd] = (uint32_t) (product >> 32);
            if (s) {
                uint32_t cpsr = cpu->cpsr & ~(ARM_CPSR_N | ARM_CPSR_Z);
                cpsr |= cpu->r[rd] & ARM_CPSR_N;
                if (product == 0) {
                    cpsr |= ARM_CPSR_Z;
                }
                cpu->cpsr = cpsr;
            }
            return CONTINUE;
        }
        default:
            return ARM_UNDEFINED;
    }
}

/* The ARMv5TE signed multiplies: SMLAxy, SMLAWy, SMULWy, SMLALxy, SMULxy (ARM ARM A4.1.76+). */
static int arm_dsp_multiply(ArmCpu *cpu, uint32_t instr)
{
    uint32_t rd = (instr >> 16) & 15;
    uint32_t rn = (instr >> 12) & 15;
    uint32_t rs = (instr >> 8) & 15;
    uint32_t rm = instr & 15;
    int x = (instr >> 5) & 1;
    int y = (instr >> 6) & 1;
    int32_t m_half = (int16_t) (x ? cpu->r[rm] >> 16 : cpu->r[rm]);
    int32_t s_half = (int16_t) (y ? cpu->r[rs] >> 16 : cpu->r[rs]);

    switch ((instr >> 21) & 3) {
        case 0: /* SMLAxy: Q on overflow of the accumulate */
            cpu->r[rd] = (uint32_t) add_setting_q(cpu, m_half * s_half, (int32_t) cpu->r[rn]);
            return CONTINUE;
        case 1: { /* SMLAWy (x == 0), SMULWy (x == 1): the top 32 bits of a 48-bit product */
            int64_t product = (int64_t) (int32_t) cpu->r[rm] * s_half;
            int32_t high = (int32_t) (product >> 16);
            if (x) {
                cpu->r[rd] = (uint32_t) high;
            } else {
                cpu->r[rd] = (uint32_t) add_setting_q(cpu, high, (int32_t) cpu->r[rn]);
            }
            return CONTINUE;
        }
        case 2: { /* SMLALxy: 64-bit accumulate, no flags */
            uint64_t acc = ((uint64_t) cpu->r[rd] << 32) | cpu->r[rn];
            acc += (uint64_t) (int64_t) (m_half * s_half);
            cpu->r[rn] = (uint32_t) acc;
            cpu->r[rd] = (uint32_t) (acc >> 32);
            return CONTINUE;
        }
        default: /* SMULxy */
            cpu->r[rd] = (uint32_t) (m_half * s_half);
            return CONTINUE;
    }
}

/* Address of an LDR/STR/LDRB/STRB with writeback applied as the instruction asks. */
static uint32_t arm_address(ArmCpu *cpu, uint32_t pc, uint32_t instr, uint32_t offset)
{
    uint32_t rn = (instr >> 16) & 15;
    uint32_t base = ARM_REG(rn);
    uint32_t moved = (instr & (1u << 23)) ? base + offset : base - offset;
    if (instr & (1u << 24)) {
        /* pre-indexed, with writeback when W is set */
        if (instr & (1u << 21)) {
            cpu->r[rn] = moved;
        }
        return moved;
    }
    /* post-indexed: the base is always written back; W here only selects the user-mode form */
    cpu->r[rn] = moved;
    return base;
}

static int arm_load_store(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t offset;
    if (instr & (1u << 25)) {
        uint32_t carry = (cpu->cpsr >> 29) & 1;
        offset = shift_immediate((instr >> 5) & 3, cpu->r[instr & 15], (instr >> 7) & 31, &carry);
    } else {
        offset = instr & 0xfff;
    }
    uint32_t rd = (instr >> 12) & 15;
    int byte = (instr >> 22) & 1;
    uint32_t rn = (instr >> 16) & 15;
    uint32_t base_before = cpu->r[rn];
    uint32_t address = arm_address(cpu, pc, instr, offset);

    if (instr & (1u << 20)) {
        uint32_t value;
        int ok = byte ? read_byte(cpu, address, &value) : load_word(cpu, address, &value);
        if (!ok) {
            cpu->r[rn] = base_before;
            return ARM_BAD_ADDRESS;
        }
        if (rd == 15) {
            return jump_interworking(cpu, value);
        }
        cpu->r[rd] = value;
        return CONTINUE;
    }

    /* A store reads Rd before any writeback; r15 stores the instruction address + 12. */
    uint32_t value = rd == 15 ? pc + 12 : rd == rn ? base_before : cpu->r[rd];
    int ok = byte ? write_byte(cpu, address, value) : write_word(cpu, address, value);
    if (!ok) {
        cpu->r[rn] = base_before;
        return ARM_BAD_ADDRESS;
    }
    return CONTINUE;
}

/* LDRH, STRH, LDRSB, LDRSH, LDRD, STRD: the "extra" load/stores with an 8-bit immediate or a
 * register offset (ARM ARM A5.3). */
static int arm_load_store_extra(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t offset = (instr & (1u << 22)) ? ((instr >> 4) & 0xf0) | (instr & 15) : cpu->r[instr & 15];
    uint32_t rd = (instr >> 12) & 15;
    uint32_t rn = (instr >> 16) & 15;
    uint32_t base_before = cpu->r[rn];
    uint32_t address = arm_address(cpu, pc, instr, offset);
    uint32_t op = (instr >> 5) & 3;
    int load = (instr >> 20) & 1;
    uint32_t value;
    int ok;

    if (load) {
        switch (op) {
            case 1:
                ok = read_half(cpu, address, &value);
                break;
            case 2:
                ok = read_byte(cpu, address, &value);
                value = (uint32_t) (int32_t) (int8_t) value;
                break;
            default:
                ok = read_half(cpu, address, &value);
                value = (uint32_t) (int32_t) (int16_t) value;
                break;
        }
        if (!ok) {
            cpu->r[rn] = base_before;
            return ARM_BAD_ADDRESS;
        }
        if (rd == 15) {
            return jump(cpu, value & ~3u);
        }
        cpu->r[rd] = value;
        return CONTINUE;
    }

    switch (op) {
        case 1: /* STRH */
            value = rd == 15 ? pc + 12 : rd == rn ? base_before : cpu->r[rd];
            ok = write_half(cpu, address, value);
            break;
        case 2: { /* LDRD: Rd even, Rd+1 loaded from the next word */
            uint32_t low, high;
            address &= ~3u;
            ok = read_word(cpu, address, &low) && read_word(cpu, address + 4, &high);
            if (ok) {
                cpu->r[rd] = low;
                cpu->r[(rd + 1) & 15] = high;
            }
            break;
        }
        default: { /* STRD */
            uint32_t low = rd == rn ? base_before : cpu->r[rd];
            uint32_t high = ((rd + 1) & 15) == rn ? base_before : cpu->r[(rd + 1) & 15];
            address &= ~3u;
            ok = write_word(cpu, address, low) && write_word(cpu, address + 4, high);
            break;
        }
    }
    if (!ok) {
        cpu->r[rn] = base_before;
        return ARM_BAD_ADDRESS;
    }
    return CONTINUE;
}

/* The start address and writeback value of an LDM/STM, from the P and U bits. */
static void block_addresses(uint32_t instr, uint32_t base, uint32_t count, uint32_t *start, uint32_t *writeback)
{
    uint32_t bytes = count * 4;
    if (instr & (1u << 23)) {
        *start = (instr & (1u << 24)) ? base + 4 : base;
        *writeback = base + bytes;
    } else {
        *start = (instr & (1u << 24)) ? base - bytes : base - bytes + 4;
        *writeback = base - bytes;
    }
}

/* LDM/STM for ARM, and Thumb's PUSH/POP/LDMIA/STMIA, which pass an equivalent ARM encoding.
 * The S bit (^) with r15 in an LDM list restores the CPSR from the SPSR (ARM ARM A4.1.22,
 * LDM(3)); without r15 it transfers the user-mode registers (A4.1.21 LDM(2), A4.1.98 STM(2)).
 * Writeback with those is UNPREDICTABLE in the ARM ARM; the ARM946E-S writes the base back in
 * the current mode's register, and the SDK's OS_IrqHandler_ThreadSwitch ("stmib r0!, {...}^",
 * then r0 again) relies on it. */
static int arm_block_transfer(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t rn = (instr >> 16) & 15;
    uint32_t list = instr & 0xffff;
    uint32_t base = cpu->r[rn];
    uint32_t start, writeback;
    int write_back = (instr >> 21) & 1;
    int s = (instr >> 22) & 1;
    int user_bank = s && !(list & (1u << 15));
    block_addresses(instr, base, count_bits(list), &start, &writeback);

    if (instr & (1u << 20)) {
        uint32_t address = start;
        int base_loaded = 0;
        for (uint32_t i = 0; i < 15; i++) {
            if (!(list & (1u << i))) {
                continue;
            }
            uint32_t value;
            if (!read_word(cpu, address, &value)) {
                return ARM_BAD_ADDRESS;
            }
            uint32_t *target = user_bank ? user_register(cpu, i) : cpu->r + i;
            *target = value;
            if (target == cpu->r + rn) {
                base_loaded = 1; /* a user-bank copy of a banked base is another register */
            }
            address += 4;
        }
        uint32_t new_pc = 0;
        int loads_pc = (list >> 15) & 1;
        if (loads_pc && !read_word(cpu, address, &new_pc)) {
            return ARM_BAD_ADDRESS;
        }
        /* The loaded value wins over writeback when the base is in the list. */
        if (write_back && !base_loaded) {
            cpu->r[rn] = writeback;
        }
        if (loads_pc) {
            if (s) {
                restore_cpsr(cpu);
                return jump_in_state(cpu, new_pc);
            }
            return jump_interworking(cpu, new_pc);
        }
        return CONTINUE;
    }

    uint32_t address = start;
    int first = 1;
    for (uint32_t i = 0; i < 16; i++) {
        if (!(list & (1u << i))) {
            continue;
        }
        uint32_t value;
        if (i == 15) {
            value = pc + 12;
        } else if (i == rn && write_back && !first) {
            value = writeback;
        } else if (user_bank) {
            value = *user_register(cpu, i);
        } else {
            value = cpu->r[i];
        }
        if (!write_word(cpu, address, value)) {
            return ARM_BAD_ADDRESS;
        }
        first = 0;
        address += 4;
    }
    if (write_back) {
        cpu->r[rn] = writeback;
    }
    return CONTINUE;
}

/* MSR: the fields it may write are flags (f) and control (c); the x and s fields hold no
 * defined bits on ARMv5. Bit 22 selects the SPSR, whose T bit is written like any other (that
 * is how OS_LoadContext resumes a Thumb thread); the CPSR's T bit is left alone since changing
 * it through MSR is UNPREDICTABLE (ARM ARM A4.1.39). In user mode the control field of the
 * CPSR is not written, and there is no SPSR to write. */
static void write_status(ArmCpu *cpu, uint32_t instr, uint32_t value)
{
    uint32_t mask = 0;
    int privileged = (cpu->cpsr & ARM_MODE_MASK) != ARM_MODE_USER;
    if (instr & (1u << 19)) {
        mask |= 0xff000000u;
    }
    if ((instr & (1u << 16)) && privileged) {
        mask |= 0xffu;
    }
    if (instr & (1u << 22)) {
        if (has_spsr(cpu, cpu->cpsr)) {
            cpu->spsr = (cpu->spsr & ~mask) | (value & mask);
        }
        return;
    }
    mask &= ~ARM_CPSR_T;
    arm_set_cpsr(cpu, (cpu->cpsr & ~mask) | (value & mask));
}

/* MRS: the CPSR, or the SPSR (which reads as the CPSR where there is none: UNPREDICTABLE). */
static uint32_t read_status(ArmCpu *cpu, uint32_t instr)
{
    if ((instr & (1u << 22)) && has_spsr(cpu, cpu->cpsr)) {
        return cpu->spsr;
    }
    return cpu->cpsr;
}

/* The instructions that share the data-processing space with S == 0 for TST/TEQ/CMP/CMN:
 * MRS, MSR, BX, BLX, CLZ, BKPT, the saturating adds and the signed multiplies (ARM ARM A3.4). */
static int arm_miscellaneous(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t op = (instr >> 21) & 3;
    uint32_t rd = (instr >> 12) & 15;
    uint32_t rm = instr & 15;

    if (instr & (1u << 25)) {
        /* MSR with an immediate operand */
        if (op & 1) {
            write_status(cpu, instr, rotate_right(instr & 0xff, (instr >> 7) & 0x1e));
            return CONTINUE;
        }
        return ARM_UNDEFINED;
    }

    switch ((instr >> 4) & 15) {
        case 0x0:
            if (op & 1) {
                write_status(cpu, instr, cpu->r[rm]);
            } else {
                cpu->r[rd] = read_status(cpu, instr);
            }
            return CONTINUE;
        case 0x1:
            if (op == 1) { /* BX */
                return jump_interworking(cpu, ARM_REG(rm));
            }
            if (op == 3) { /* CLZ */
                cpu->r[rd] = count_leading_zeros(cpu->r[rm]);
                return CONTINUE;
            }
            return ARM_UNDEFINED;
        case 0x3:
            if (op == 1) { /* BLX register */
                uint32_t target = ARM_REG(rm);
                cpu->r[14] = pc + 4;
                return jump_interworking(cpu, target);
            }
            return ARM_UNDEFINED;
        case 0x5: { /* QADD, QSUB, QDADD, QDSUB: Rd = Rm op Rn, the doubling saturates too */
            int32_t m = (int32_t) cpu->r[rm];
            int32_t n = (int32_t) cpu->r[(instr >> 16) & 15];
            if (op & 2) {
                n = saturate_add(cpu, n, n);
            }
            cpu->r[rd] = (uint32_t) ((op & 1) ? saturate_sub(cpu, m, n) : saturate_add(cpu, m, n));
            return CONTINUE;
        }
        case 0x7:
            if (op == 1) {
                return ARM_BREAKPOINT;
            }
            return ARM_UNDEFINED;
        case 0x8:
        case 0xa:
        case 0xc:
        case 0xe:
            return arm_dsp_multiply(cpu, instr);
        default:
            return ARM_UNDEFINED;
    }
}

/* CP15 ------------------------------------------------------------------------------------- */

uint32_t arm_cp15_get(const ArmCpu *cpu, int crn, int crm, int op2)
{
    if (crn == 0) {
        /* identification (ARM946E-S TRM 2.3.1, 2.3.2): ID code, cache type, TCM size */
        switch (op2) {
            case 1:
                return 0x0f0d2112u;
            case 2:
                return 0x00140180u;
            default:
                return 0x41059461u;
        }
    }
    if (crm < 0 || crm >= 8 || op2 < 0 || op2 >= 8 || crn < 0 || crn >= 16) {
        return 0;
    }
    return cpu->cp15[crn][crm][op2];
}

/* MCR / MRC. Only cp15 exists, and only to privileged modes (ARM ARM A4.1.32: the coprocessor
 * may refuse, which the ARM946E-S does for user mode by taking the undefined instruction). An
 * MRC into r15 sets the flags from the value's top four bits. */
static int arm_coprocessor_transfer(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    int crn = (instr >> 16) & 15, crm = instr & 15, op2 = (instr >> 5) & 7;
    uint32_t rd = (instr >> 12) & 15;
    if (((instr >> 8) & 15) != 15 || (cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_USER) {
        return ARM_UNDEFINED;
    }
    if (instr & (1u << 20)) {
        uint32_t value = arm_cp15_get(cpu, crn, crm, op2);
        if (rd == 15) {
            cpu->cpsr = (cpu->cpsr & 0x0fffffffu) | (value & 0xf0000000u);
        } else {
            cpu->r[rd] = value;
        }
        return CONTINUE;
    }
    uint32_t value = ARM_REG(rd);
    switch (crn) {
        case 0: /* read-only */
            return CONTINUE;
        case 7: /* cache and write buffer operations (TRM 2.3.8); c7, c0, 4 waits for an interrupt */
            if (crm == 0 && op2 == 4) {
                return ARM_HALT;
            }
            return CONTINUE;
        default:
            if (crm < 8) {
                cpu->cp15[crn][crm][op2] = value;
            }
            return CONTINUE;
    }
}

static int arm_execute(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    uint32_t cond = instr >> 28;

    if (cond == 0xf) {
        /* The unconditional space: BLX immediate and PLD; the rest is undefined. */
        if ((instr & 0x0e000000u) == 0x0a000000u) {
            int32_t offset = ((int32_t) (instr << 8) >> 6) | (int32_t) (((instr >> 24) & 1) << 1);
            cpu->r[14] = pc + 4;
            cpu->cpsr |= ARM_CPSR_T;
            return jump(cpu, pc + 8 + (uint32_t) offset);
        }
        if ((instr & 0x0d70f000u) == 0x0550f000u) {
            return CONTINUE; /* PLD: a cache hint */
        }
        return ARM_UNDEFINED;
    }
    if (!condition_passed(cpu->cpsr, cond)) {
        return CONTINUE;
    }

    switch ((instr >> 25) & 7) {
        case 0:
            if ((instr & 0x90u) == 0x90u) {
                if (instr & 0x60u) {
                    return arm_load_store_extra(cpu, pc, instr);
                }
                if (instr & (1u << 24)) {
                    /* SWP / SWPB: the load rotates like LDR, the store aligns like STR */
                    if ((instr & 0x0fb00ff0u) != 0x01000090u) {
                        return ARM_UNDEFINED;
                    }
                    uint32_t address = cpu->r[(instr >> 16) & 15];
                    uint32_t new_value = cpu->r[instr & 15];
                    uint32_t old_value;
                    int ok;
                    if (instr & (1u << 22)) {
                        ok = read_byte(cpu, address, &old_value) && write_byte(cpu, address, new_value);
                    } else {
                        ok = load_word(cpu, address, &old_value) && write_word(cpu, address, new_value);
                    }
                    if (!ok) {
                        return ARM_BAD_ADDRESS;
                    }
                    cpu->r[(instr >> 12) & 15] = old_value;
                    return CONTINUE;
                }
                return arm_multiply(cpu, pc, instr);
            }
            if ((instr & 0x01900000u) == 0x01000000u) {
                return arm_miscellaneous(cpu, pc, instr);
            }
            return arm_data_processing(cpu, pc, instr);
        case 1:
            if ((instr & 0x01900000u) == 0x01000000u) {
                return arm_miscellaneous(cpu, pc, instr);
            }
            return arm_data_processing(cpu, pc, instr);
        case 2:
            return arm_load_store(cpu, pc, instr);
        case 3:
            if (instr & (1u << 4)) {
                return ARM_UNDEFINED; /* the architecturally undefined space */
            }
            return arm_load_store(cpu, pc, instr);
        case 4:
            return arm_block_transfer(cpu, pc, instr);
        case 5: {
            int32_t offset = (int32_t) (instr << 8) >> 6;
            if (instr & (1u << 24)) {
                cpu->r[14] = pc + 4;
            }
            return jump(cpu, pc + 8 + (uint32_t) offset);
        }
        case 6:
            return ARM_UNDEFINED; /* LDC / STC: no coprocessor has them */
        default:
            if (instr & (1u << 24)) {
                cpu->swi = instr & 0xffffffu;
                return ARM_SWI;
            }
            if (instr & 0x10u) {
                return arm_coprocessor_transfer(cpu, pc, instr);
            }
            return ARM_UNDEFINED; /* CDP: no coprocessor has data operations */
    }
}

/* Thumb state ---------------------------------------------------------------------------- */

#define THUMB_REG(n) ((n) == 15 ? pc + 4 : cpu->r[n])

/* The Thumb ALU operations of format 4, by the 4-bit opcode. */
static int thumb_alu(ArmCpu *cpu, uint32_t instr)
{
    uint32_t rd = instr & 7;
    uint32_t rs = (instr >> 3) & 7;
    uint32_t a = cpu->r[rd];
    uint32_t b = cpu->r[rs];
    uint32_t carry = (cpu->cpsr >> 29) & 1;
    uint32_t result;

    switch ((instr >> 6) & 15) {
        case 0x0:
            result = a & b;
            break;
        case 0x1:
            result = a ^ b;
            break;
        case 0x2:
            result = shift_register(0, a, b & 0xff, &carry);
            break;
        case 0x3:
            result = shift_register(1, a, b & 0xff, &carry);
            break;
        case 0x4:
            result = shift_register(2, a, b & 0xff, &carry);
            break;
        case 0x5:
            cpu->r[rd] = add_with_flags(cpu, a, b, carry);
            return CONTINUE;
        case 0x6:
            cpu->r[rd] = sub_with_flags(cpu, a, b, carry);
            return CONTINUE;
        case 0x7:
            result = shift_register(3, a, b & 0xff, &carry);
            break;
        case 0x8:
            set_nzc(cpu, a & b, carry);
            return CONTINUE;
        case 0x9:
            cpu->r[rd] = sub_with_flags(cpu, 0, b, 1);
            return CONTINUE;
        case 0xa:
            sub_with_flags(cpu, a, b, 1);
            return CONTINUE;
        case 0xb:
            add_with_flags(cpu, a, b, 0);
            return CONTINUE;
        case 0xc:
            result = a | b;
            break;
        case 0xd:
            result = a * b;
            cpu->r[rd] = result;
            set_nz(cpu, result);
            return CONTINUE;
        case 0xe:
            result = a & ~b;
            break;
        default:
            result = ~b;
            break;
    }
    cpu->r[rd] = result;
    set_nzc(cpu, result, carry);
    return CONTINUE;
}

static int thumb_execute(ArmCpu *cpu, uint32_t pc, uint32_t instr)
{
    switch (instr >> 12) {
        case 0x0:
        case 0x1: {
            uint32_t rd = instr & 7;
            uint32_t rs = (instr >> 3) & 7;
            if ((instr & 0x1800u) == 0x1800u) {
                /* ADD / SUB with a register or a 3-bit immediate */
                uint32_t b = (instr & (1u << 10)) ? (instr >> 6) & 7 : cpu->r[(instr >> 6) & 7];
                if (instr & (1u << 9)) {
                    cpu->r[rd] = sub_with_flags(cpu, cpu->r[rs], b, 1);
                } else {
                    cpu->r[rd] = add_with_flags(cpu, cpu->r[rs], b, 0);
                }
                return CONTINUE;
            }
            /* LSL / LSR / ASR by immediate: the ARM shifter rules, LSL #0 leaves C */
            uint32_t carry = (cpu->cpsr >> 29) & 1;
            uint32_t result = shift_immediate((instr >> 11) & 3, cpu->r[rs], (instr >> 6) & 31, &carry);
            cpu->r[rd] = result;
            set_nzc(cpu, result, carry);
            return CONTINUE;
        }
        case 0x2:
        case 0x3: {
            /* MOV / CMP / ADD / SUB with an 8-bit immediate */
            uint32_t rd = (instr >> 8) & 7;
            uint32_t imm = instr & 0xff;
            switch ((instr >> 11) & 3) {
                case 0:
                    cpu->r[rd] = imm;
                    set_nz(cpu, imm);
                    break;
                case 1:
                    sub_with_flags(cpu, cpu->r[rd], imm, 1);
                    break;
                case 2:
                    cpu->r[rd] = add_with_flags(cpu, cpu->r[rd], imm, 0);
                    break;
                default:
                    cpu->r[rd] = sub_with_flags(cpu, cpu->r[rd], imm, 1);
                    break;
            }
            return CONTINUE;
        }
        case 0x4: {
            if (instr & (1u << 11)) {
                /* LDR Rd, [pc, #imm]: from the word-aligned pipeline pc */
                uint32_t address = ((pc + 4) & ~3u) + (instr & 0xff) * 4;
                uint32_t value;
                if (!load_word(cpu, address, &value)) {
                    return ARM_BAD_ADDRESS;
                }
                cpu->r[(instr >> 8) & 7] = value;
                return CONTINUE;
            }
            if (!(instr & (1u << 10))) {
                return thumb_alu(cpu, instr);
            }
            /* The high-register forms: ADD, CMP, MOV, BX / BLX */
            uint32_t rd = (instr & 7) | ((instr >> 4) & 8);
            uint32_t rm = (instr >> 3) & 15;
            uint32_t b = THUMB_REG(rm);
            switch ((instr >> 8) & 3) {
                case 0: {
                    uint32_t result = THUMB_REG(rd) + b;
                    if (rd == 15) {
                        return jump(cpu, result & ~1u);
                    }
                    cpu->r[rd] = result;
                    return CONTINUE;
                }
                case 1:
                    sub_with_flags(cpu, THUMB_REG(rd), b, 1);
                    return CONTINUE;
                case 2:
                    if (rd == 15) {
                        return jump(cpu, b & ~1u);
                    }
                    cpu->r[rd] = b;
                    return CONTINUE;
                default:
                    if (instr & (1u << 7)) {
                        cpu->r[14] = (pc + 2) | 1; /* BLX */
                    }
                    return jump_interworking(cpu, b);
            }
        }
        case 0x5: {
            uint32_t rd = instr & 7;
            uint32_t address = cpu->r[(instr >> 3) & 7] + cpu->r[(instr >> 6) & 7];
            uint32_t value;
            int ok;
            switch ((instr >> 9) & 7) {
                case 0:
                    ok = write_word(cpu, address, cpu->r[rd]);
                    break;
                case 1:
                    ok = write_half(cpu, address, cpu->r[rd]);
                    break;
                case 2:
                    ok = write_byte(cpu, address, cpu->r[rd]);
                    break;
                case 3:
                    ok = read_byte(cpu, address, &value);
                    value = (uint32_t) (int32_t) (int8_t) value;
                    break;
                case 4:
                    ok = load_word(cpu, address, &value);
                    break;
                case 5:
                    ok = read_half(cpu, address, &value);
                    break;
                case 6:
                    ok = read_byte(cpu, address, &value);
                    break;
                default:
                    ok = read_half(cpu, address, &value);
                    value = (uint32_t) (int32_t) (int16_t) value;
                    break;
            }
            if (!ok) {
                return ARM_BAD_ADDRESS;
            }
            if (instr & (1u << 11) || ((instr >> 9) & 7) == 3) {
                cpu->r[rd] = value;
            }
            return CONTINUE;
        }
        case 0x6:
        case 0x7: {
            /* LDR / STR / LDRB / STRB with a 5-bit immediate */
            uint32_t rd = instr & 7;
            uint32_t imm = (instr >> 6) & 31;
            uint32_t base = cpu->r[(instr >> 3) & 7];
            uint32_t value;
            int ok;
            if (instr & (1u << 12)) {
                if (instr & (1u << 11)) {
                    ok = read_byte(cpu, base + imm, &value);
                } else {
                    ok = write_byte(cpu, base + imm, cpu->r[rd]);
                }
            } else if (instr & (1u << 11)) {
                ok = load_word(cpu, base + imm * 4, &value);
            } else {
                ok = write_word(cpu, base + imm * 4, cpu->r[rd]);
            }
            if (!ok) {
                return ARM_BAD_ADDRESS;
            }
            if (instr & (1u << 11)) {
                cpu->r[rd] = value;
            }
            return CONTINUE;
        }
        case 0x8: {
            uint32_t rd = instr & 7;
            uint32_t address = cpu->r[(instr >> 3) & 7] + ((instr >> 6) & 31) * 2;
            if (instr & (1u << 11)) {
                uint32_t value;
                if (!read_half(cpu, address, &value)) {
                    return ARM_BAD_ADDRESS;
                }
                cpu->r[rd] = value;
                return CONTINUE;
            }
            if (!write_half(cpu, address, cpu->r[rd])) {
                return ARM_BAD_ADDRESS;
            }
            return CONTINUE;
        }
        case 0x9: {
            uint32_t rd = (instr >> 8) & 7;
            uint32_t address = cpu->r[13] + (instr & 0xff) * 4;
            if (instr & (1u << 11)) {
                uint32_t value;
                if (!load_word(cpu, address, &value)) {
                    return ARM_BAD_ADDRESS;
                }
                cpu->r[rd] = value;
                return CONTINUE;
            }
            if (!write_word(cpu, address, cpu->r[rd])) {
                return ARM_BAD_ADDRESS;
            }
            return CONTINUE;
        }
        case 0xa: {
            /* ADD Rd, pc/sp, #imm: the pc form uses the word-aligned pipeline value */
            uint32_t rd = (instr >> 8) & 7;
            uint32_t base = (instr & (1u << 11)) ? cpu->r[13] : (pc + 4) & ~3u;
            cpu->r[rd] = base + (instr & 0xff) * 4;
            return CONTINUE;
        }
        case 0xb:
            switch ((instr >> 8) & 15) {
                case 0x0: { /* ADD / SUB sp, #imm */
                    uint32_t imm = (instr & 0x7f) * 4;
                    cpu->r[13] = (instr & (1u << 7)) ? cpu->r[13] - imm : cpu->r[13] + imm;
                    return CONTINUE;
                }
                case 0x4:
                case 0x5: { /* PUSH {list, lr}: STMDB sp! */
                    uint32_t list = (instr & 0xff) | ((instr & (1u << 8)) ? 1u << 14 : 0);
                    return arm_block_transfer(cpu, pc, 0xe92d0000u | list);
                }
                case 0xc:
                case 0xd: { /* POP {list, pc}: LDMIA sp!, interworking on v5T */
                    uint32_t list = (instr & 0xff) | ((instr & (1u << 8)) ? 1u << 15 : 0);
                    return arm_block_transfer(cpu, pc, 0xe8bd0000u | list);
                }
                case 0xe:
                    return ARM_BREAKPOINT;
                default:
                    return ARM_UNDEFINED;
            }
        case 0xc: {
            /* STMIA / LDMIA Rn!, {list} */
            uint32_t rn = (instr >> 8) & 7;
            uint32_t list = instr & 0xff;
            uint32_t op = (instr & (1u << 11)) ? 0xe8b00000u : 0xe8a00000u;
            return arm_block_transfer(cpu, pc, op | (rn << 16) | list);
        }
        case 0xd: {
            uint32_t cond = (instr >> 8) & 15;
            if (cond == 0xf) {
                cpu->swi = instr & 0xff;
                return ARM_SWI;
            }
            if (cond == 0xe) {
                return ARM_UNDEFINED;
            }
            if (!condition_passed(cpu->cpsr, cond)) {
                return CONTINUE;
            }
            int32_t offset = (int32_t) (int8_t) (instr & 0xff) * 2;
            return jump(cpu, pc + 4 + (uint32_t) offset);
        }
        case 0xe: {
            if (instr & (1u << 11)) {
                /* BLX suffix: to ARM state at a word-aligned address */
                uint32_t target = (cpu->r[14] + ((instr & 0x7ff) << 1)) & ~3u;
                cpu->r[14] = (pc + 2) | 1;
                cpu->cpsr &= ~ARM_CPSR_T;
                return jump(cpu, target);
            }
            int32_t offset = ((int32_t) (instr << 21) >> 20);
            return jump(cpu, pc + 4 + (uint32_t) offset);
        }
        default: {
            if (instr & (1u << 11)) {
                /* BL suffix */
                uint32_t target = cpu->r[14] + ((instr & 0x7ff) << 1);
                cpu->r[14] = (pc + 2) | 1;
                return jump(cpu, target & ~1u);
            }
            /* BL / BLX prefix: the high part of the offset goes to lr */
            int32_t high = ((int32_t) (instr << 21) >> 9);
            cpu->r[14] = pc + 4 + (uint32_t) high;
            return CONTINUE;
        }
    }
}

/* The run loop ---------------------------------------------------------------------------- */

static enum ArmStop run(ArmCpu *cpu, uint32_t until, uint64_t max_steps)
{
    uint64_t limit = max_steps ? cpu->steps + max_steps : UINT64_MAX;
    until &= ~1u;

    /* The first address is a branch target too: the function's entry may be hooked. */
    cpu->hook_between = 1;
    int result = jump(cpu, cpu->r[15]);
    cpu->hook_between = 0;
    if (result != CONTINUE) {
        return (enum ArmStop) result;
    }

    for (;;) {
        uint32_t pc = cpu->r[15];
        if (pc == until) {
            cpu->stop_pc = pc;
            return ARM_RETURNED;
        }
        if (cpu->steps >= limit) {
            cpu->stop_pc = pc;
            return ARM_STEP_LIMIT;
        }
        if (cpu->irq_line && !(cpu->cpsr & ARM_CPSR_I)) {
            /* The interrupt is taken before this instruction, which the handler returns to.
               The vector is a branch target: a hook there runs as for any branch. */
            arm_enter_exception(cpu, ARM_EXC_IRQ);
            cpu->irq_taken++;
            cpu->hook_between = 1;
            result = jump(cpu, cpu->r[15]);
            cpu->hook_between = 0;
            if (result != CONTINUE) {
                return (enum ArmStop) result;
            }
            pc = cpu->r[15];
        }
        int mode = (cpu->cpsr & ARM_MODE_MASK) == ARM_MODE_IRQ;
        uint64_t stall = cpu->stall_until[mode];
        if (cpu->steps < stall && pc == cpu->stall_pc[mode]) {
            /* Nothing that executes can raise the interrupt line, so the whole stall up to
               the slice's limit passes at once. */
            cpu->steps = stall < limit ? stall : limit;
            continue;
        }
        if (cpu->stall_branch[mode] && pc == cpu->stall_pc[mode]) {
            /* the stall is over: its hooks run again at the instruction it held up */
            cpu->stall_branch[mode] = 0;
            cpu->hook_between = 1;
            result = jump(cpu, pc);
            cpu->hook_between = 0;
            if (result != CONTINUE) {
                return (enum ArmStop) result;
            }
            continue;
        }
        if (cpu->steps - cpu->trace_from < cpu->trace_count) {
            fprintf(stderr,
                    "step %llu pc %08x %c cpsr %08x r0-r3 %08x %08x %08x %08x r4-r7 %08x %08x %08x %08x sp %08x lr %08x\n",
                    (unsigned long long) cpu->steps, pc, (cpu->cpsr & ARM_CPSR_T) ? 't' : 'a', cpu->cpsr, cpu->r[0], cpu->r[1],
                    cpu->r[2], cpu->r[3], cpu->r[4], cpu->r[5], cpu->r[6], cpu->r[7], cpu->r[13], cpu->r[14]);
        }
        if (cpu->cpsr & ARM_CPSR_T) {
            uint32_t instr;
            if (!read_half(cpu, pc, &instr)) {
                cpu->stop_pc = pc;
                return ARM_BAD_ADDRESS;
            }
            cpu->r[15] = pc + 2;
            result = thumb_execute(cpu, pc, instr);
        } else {
            uint32_t instr;
            if (!read_word(cpu, pc, &instr)) {
                cpu->stop_pc = pc;
                return ARM_BAD_ADDRESS;
            }
            cpu->r[15] = pc + 4;
            result = arm_execute(cpu, pc, instr);
        }
        cpu->steps++;
        if (result == CONTINUE) {
            continue;
        }
        switch (result) {
            case ARM_RETURNED:
            case ARM_HOOK_STOP:
                /* jump() recorded the target as stop_pc and set r15 */
                break;
            case ARM_SWI:
            case ARM_HALT:
                /* r15 already points after the instruction, where a handler would return */
                cpu->stop_pc = pc;
                break;
            default:
                /* undefined, breakpoint, bad address: leave r15 on the instruction */
                cpu->stop_pc = pc;
                cpu->r[15] = pc;
                break;
        }
        return (enum ArmStop) result;
    }
}

void arm_init(ArmCpu *cpu)
{
    memset(cpu, 0, sizeof(*cpu));
    cpu->cpsr = ARM_MODE_SYSTEM;
    cpu->cp15[1][0][0] = ARM_CP15_CONTROL_RESET;
}

/* Exception entry (ARM ARM A2.6.2 to A2.6.8): each saves the CPSR in the new mode's SPSR, the
 * return address in its r14, enters the mode in ARM state with IRQs disabled (FIQ and reset
 * also disable FIQs) and branches to the vector. */
void arm_enter_exception(ArmCpu *cpu, enum ArmException exception)
{
    static const uint8_t modes[8] = {ARM_MODE_SVC,   ARM_MODE_UNDEFINED, ARM_MODE_SVC, ARM_MODE_ABORT,
                                     ARM_MODE_ABORT, ARM_MODE_SVC,       ARM_MODE_IRQ, ARM_MODE_FIQ};
    uint32_t old = cpu->cpsr;
    uint32_t pc = cpu->r[15];
    uint32_t lr;
    switch (exception) {
        case ARM_EXC_UNDEFINED:
            lr = pc + ((old & ARM_CPSR_T) ? 2 : 4);
            break;
        case ARM_EXC_SWI:
            lr = pc;
            break;
        case ARM_EXC_DATA_ABORT:
            lr = pc + 8;
            break;
        default: /* prefetch abort, IRQ, FIQ; reset's is UNPREDICTABLE */
            lr = pc + 4;
            break;
    }
    uint32_t cpsr = (old & ~(ARM_MODE_MASK | ARM_CPSR_T)) | modes[exception & 7] | ARM_CPSR_I;
    if (exception == ARM_EXC_FIQ || exception == ARM_EXC_RESET) {
        cpsr |= ARM_CPSR_F;
    }
    arm_set_cpsr(cpu, cpsr);
    cpu->spsr = old;
    cpu->r[14] = lr;
    uint32_t base = (cpu->cp15[1][0][0] & ARM_CP15_CONTROL_HIGH_VECTORS) ? ARM_HIGH_VECTORS : 0;
    cpu->r[15] = base + 4 * (uint32_t) exception;
}

int arm_raise_irq(ArmCpu *cpu)
{
    if (cpu->cpsr & ARM_CPSR_I) {
        return 0;
    }
    arm_enter_exception(cpu, ARM_EXC_IRQ);
    cpu->irq_taken++;
    return 1;
}

enum ArmStop arm_call(ArmCpu *cpu, uint32_t address, uint64_t max_steps)
{
    cpu->r[14] = ARM_RETURN_ADDRESS;
    if (address & 1) {
        cpu->cpsr |= ARM_CPSR_T;
    } else {
        cpu->cpsr &= ~ARM_CPSR_T;
    }
    cpu->r[15] = address & ~1u;
    return run(cpu, ARM_RETURN_ADDRESS, max_steps);
}

enum ArmStop arm_run(ArmCpu *cpu, uint32_t until, uint64_t max_steps)
{
    return run(cpu, until, max_steps);
}
