/* x86 code for blocks (included by arm.c, on 32-bit x86 hosts).
 *
 * A block that has run a few times is translated into a function of its own:
 *
 *     int code(ArmCpu *cpu, uint32_t n, uint32_t *last);
 *
 * which runs at most n of its instructions as block_run's loop does and returns what the loop
 * would (CONTINUE or a stop), with *last the index of the last instruction it executed. Each
 * instruction is either inline x86 code or a call of its handler, the same function the loop
 * calls: the common data-processing instructions and the loads and stores whose address is
 * main RAM or the DTCM are inline; everything else, and a load or store that is not plainly
 * one of those (another region, I/O, an unaligned word, a store a watcher sees or that lands
 * in the block's own code), calls the handler, which does the whole instruction. Around a
 * call the code keeps what the loop keeps: r15 is the next instruction's address before it,
 * the step is counted after it, and the block ends when the handler stops, branches or sets
 * block_exit. ARM registers live in the ArmCpu throughout, so a handler, a callback or a hook
 * sees them as the loop leaves them.
 *
 * The flags come from the host's: x86's add and sub set SF, ZF, CF and OF as ARM's set N, Z, C
 * and V, but for C after a subtraction, which is ARM's "no borrow" and x86's borrow.
 *
 * The code goes in executable memory that is never writable at the same time: pages are made
 * writable to add a block's code and executable again before it runs. Code is never freed (a
 * run may be suspended inside it, in a hook) but all at once, when the arena is full and no
 * run is inside it: the blocks then run untranslated until they are hot again. */

#include <stddef.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

#define X86_ARENA (32u << 20) /* bytes of code at most, in all */
#define X86_BLOCK_MAX 8192    /* bytes of code one block may take */

typedef int (*BlockCode)(ArmCpu *cpu, uint32_t n, uint32_t *last);

static uint8_t *x86_arena;
static uint32_t x86_used, x86_page;
static int x86_failed;
static uint64_t x86_blocks, x86_flushes;
static int x86_active; /* runs inside code: a hook can suspend one there */

enum { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI };

typedef struct {
    uint8_t *p, *end;
    uint32_t fixups[BLOCK_MAX_OPS * 8][2]; /* (offset of a rel32, index of its exit stub) */
    uint32_t fixup_count;
} Emit;

#define CPU_R(n) ((uint32_t) (offsetof(ArmCpu, r) + 4 * (n)))
#define CPU_CPSR ((uint32_t) offsetof(ArmCpu, cpsr))
#define CPU_STEPS ((uint32_t) offsetof(ArmCpu, steps))
#define CPU_EXIT ((uint32_t) offsetof(ArmCpu, block_exit))
#define CPU_OBSERVE ((uint32_t) offsetof(ArmCpu, observe_word_store))

static void e8(Emit *e, uint32_t v)
{
    if (e->p < e->end) {
        *e->p++ = (uint8_t) v;
    }
}

static void e32(Emit *e, uint32_t v)
{
    e8(e, v);
    e8(e, v >> 8);
    e8(e, v >> 16);
    e8(e, v >> 24);
}

/* mov reg, [ebx + disp]; mov [ebx + disp], reg */
static void load_cpu(Emit *e, int reg, uint32_t disp)
{
    e8(e, 0x8b);
    e8(e, 0x80 | (reg << 3) | EBX);
    e32(e, disp);
}

static void store_cpu(Emit *e, int reg, uint32_t disp)
{
    e8(e, 0x89);
    e8(e, 0x80 | (reg << 3) | EBX);
    e32(e, disp);
}

/* mov dword [ebx + disp], imm */
static void store_cpu_imm(Emit *e, uint32_t disp, uint32_t imm)
{
    e8(e, 0xc7);
    e8(e, 0x83);
    e32(e, disp);
    e32(e, imm);
}

/* add, or, adc, sbb, and, sub, xor, cmp (digit 0-7) reg, imm */
static void alu_imm(Emit *e, int digit, int reg, uint32_t imm)
{
    e8(e, 0x81);
    e8(e, 0xc0 | (digit << 3) | reg);
    e32(e, imm);
}

enum { X_ADD = 0, X_OR = 1, X_AND = 4, X_SUB = 5, X_XOR = 6, X_CMP = 7 };

/* op dst, src for add (0x01), or (0x09), and (0x21), sub (0x29), xor (0x31), cmp (0x39), mov
 * (0x89), test (0x85) */
static void alu_reg(Emit *e, uint32_t opcode, int dst, int src)
{
    e8(e, opcode);
    e8(e, 0xc0 | (src << 3) | dst);
}

static void mov_imm(Emit *e, int reg, uint32_t imm)
{
    e8(e, 0xb8 + reg);
    e32(e, imm);
}

/* shl (4), shr (5), sar (7), ror (1) reg, amount */
static void shift_imm(Emit *e, int digit, int reg, uint32_t amount)
{
    e8(e, 0xc1);
    e8(e, 0xc0 | (digit << 3) | reg);
    e8(e, amount);
}

/* jcc rel32 (cc the low nibble of 0f 8x) or jmp rel32 (cc -1) to exit stub `stub` */
static void jump_stub(Emit *e, int cc, uint32_t stub)
{
    if (cc < 0) {
        e8(e, 0xe9);
    } else {
        e8(e, 0x0f);
        e8(e, 0x80 | cc);
    }
    if (e->fixup_count < sizeof(e->fixups) / sizeof(e->fixups[0])) {
        e->fixups[e->fixup_count][0] = (uint32_t) (uintptr_t) e->p;
        e->fixups[e->fixup_count][1] = stub;
        e->fixup_count++;
    } else {
        e->p = e->end; /* too many: the block keeps no code */
    }
    e32(e, 0);
}

enum { CC_O = 0x0, CC_B = 0x2, CC_AE = 0x3, CC_E = 0x4, CC_NE = 0x5, CC_BE = 0x6, CC_A = 0x7 };

/* A forward jcc rel32 to be patched by `land` */
static uint8_t *jump_forward(Emit *e, int cc)
{
    if (cc < 0) {
        e8(e, 0xe9);
    } else {
        e8(e, 0x0f);
        e8(e, 0x80 | cc);
    }
    uint8_t *at = e->p;
    e32(e, 0);
    return at;
}

static void land(Emit *e, uint8_t *at)
{
    if (e->p < e->end && at + 4 <= e->end) {
        uint32_t rel = (uint32_t) (e->p - (at + 4));
        memcpy(at, &rel, 4);
    }
}

/* The steps: add dword [ebx + steps], 1; adc dword [ebx + steps + 4], 0 */
static void count_step(Emit *e)
{
    e8(e, 0x83);
    e8(e, 0x83);
    e32(e, CPU_STEPS);
    e8(e, 1);
    e8(e, 0x83);
    e8(e, 0x93);
    e32(e, CPU_STEPS + 4);
    e8(e, 0);
}

/* Skips to the returned jump unless op's condition passes: eax = cpsr >> 28,
 * ecx = condition_pass[cond], bt ecx, eax */
static uint8_t *condition_skip(Emit *e, const BlockOp *op)
{
    load_cpu(e, EAX, CPU_CPSR);
    shift_imm(e, 5, EAX, 28);
    mov_imm(e, ECX, condition_pass[op->cond]);
    e8(e, 0x0f);
    e8(e, 0xa3);
    e8(e, 0xc0 | (EAX << 3) | ECX);
    return jump_forward(e, CC_AE); /* CF clear: the bit is clear */
}

/* cpsr's N and Z from eax, with C from edi when `carry` (edi 0 or 1), V kept. Uses ecx, edx. */
static void flags_nz(Emit *e, int carry)
{
    load_cpu(e, EDX, CPU_CPSR);
    alu_imm(e, X_AND, EDX, carry ? 0x1fffffffu : 0x3fffffffu);
    alu_reg(e, 0x89, ECX, EAX);
    alu_imm(e, X_AND, ECX, 0x80000000u);
    alu_reg(e, 0x09, EDX, ECX);
    alu_reg(e, 0x85, EAX, EAX);
    e8(e, 0x0f); /* setz cl */
    e8(e, 0x94);
    e8(e, 0xc1);
    e8(e, 0x0f); /* movzx ecx, cl */
    e8(e, 0xb6);
    e8(e, 0xc9);
    shift_imm(e, 4, ECX, 30);
    alu_reg(e, 0x09, EDX, ECX);
    if (carry) {
        shift_imm(e, 4, EDI, 29);
        alu_reg(e, 0x09, EDX, EDI);
    }
    store_cpu(e, EDX, CPU_CPSR);
}

/* After an x86 add or sub (nothing in between): cpsr's N Z C V from the host's flags, C
 * inverted after a subtraction. Uses ecx, edx, edi; eax is kept. */
static void flags_nzcv(Emit *e, int subtract)
{
    e8(e, 0x9c);       /* pushfd */
    e8(e, 0x58 + EDX); /* pop edx */
    alu_reg(e, 0x89, ECX, EDX);
    alu_imm(e, X_AND, ECX, 0x80);
    shift_imm(e, 4, ECX, 24); /* SF -> N */
    alu_reg(e, 0x89, EDI, EDX);
    alu_imm(e, X_AND, EDI, 0x40);
    shift_imm(e, 4, EDI, 24); /* ZF -> Z */
    alu_reg(e, 0x09, ECX, EDI);
    alu_reg(e, 0x89, EDI, EDX);
    alu_imm(e, X_AND, EDI, 1);
    if (subtract) {
        alu_imm(e, X_XOR, EDI, 1);
    }
    shift_imm(e, 4, EDI, 29); /* CF -> C */
    alu_reg(e, 0x09, ECX, EDI);
    alu_imm(e, X_AND, EDX, 0x800);
    shift_imm(e, 4, EDX, 17); /* OF -> V */
    alu_reg(e, 0x09, ECX, EDX);
    load_cpu(e, EDX, CPU_CPSR);
    alu_imm(e, X_AND, EDX, 0x0fffffffu);
    alu_reg(e, 0x09, EDX, ECX);
    store_cpu(e, EDX, CPU_CPSR);
}

/* A call of op's handler, as block_run makes it, and the block's end after it when the loop
 * would end there: r15 is set before, the step counted after. */
static void call_handler(Emit *e, const BlockOp *op, uint32_t next, uint32_t index)
{
    store_cpu_imm(e, CPU_R(15), next);
    e8(e, 0x89); /* mov [esp], ebx */
    e8(e, 0x1c);
    e8(e, 0x24);
    e8(e, 0xc7); /* mov dword [esp + 4], op */
    e8(e, 0x44);
    e8(e, 0x24);
    e8(e, 0x04);
    e32(e, (uint32_t) (uintptr_t) op);
    e8(e, 0xe8); /* call rel32 */
    uint32_t target = (uint32_t) (uintptr_t) op->fn;
    e32(e, target - (uint32_t) (uintptr_t) (e->p + 4));
    count_step(e);
    alu_imm(e, X_CMP, EAX, (uint32_t) CONTINUE);
    jump_stub(e, CC_NE, index * 2);
    e8(e, 0x83); /* cmp dword [ebx + block_exit], 0 */
    e8(e, 0xbb);
    e32(e, CPU_EXIT);
    e8(e, 0);
    jump_stub(e, CC_NE, index * 2);
    e8(e, 0x81); /* cmp dword [ebx + r15], next */
    e8(e, 0xbb);
    e32(e, CPU_R(15));
    e32(e, next);
    jump_stub(e, CC_NE, index * 2);
}

/* The handler call of a load or store whose fast path did not apply: `slow` jumps here. */
typedef struct {
    uint8_t *slow[8];
    int count;
} SlowPaths;

/* ecx: the address. Jumps to a slow path unless [ecx, ecx + size) is in main RAM or the DTCM
 * (and, for a store, outside the block's own code and with no watcher of stores). */
static void fast_range(Emit *e, SlowPaths *s, uint32_t size, int store, const Block *b)
{
    if (size > 1) {
        e8(e, 0xf7); /* test ecx, size - 1 */
        e8(e, 0xc1);
        e32(e, size - 1);
        s->slow[s->count++] = jump_forward(e, CC_NE);
    }
    /* edx = ecx - main; cmp edx, size of main - size; jbe ok; edx = ecx - dtcm; cmp; ja slow */
    e8(e, 0x8d); /* lea edx, [ecx - MEM_MAIN_BASE] */
    e8(e, 0x91);
    e32(e, 0u - MEM_MAIN_BASE);
    alu_imm(e, X_CMP, EDX, MEM_MAIN_SIZE - size);
    uint8_t *in_main = jump_forward(e, CC_BE);
    e8(e, 0x8d); /* lea edx, [ecx - MEM_DTCM_BASE] */
    e8(e, 0x91);
    e32(e, 0u - MEM_DTCM_BASE);
    alu_imm(e, X_CMP, EDX, MEM_DTCM_SIZE - size);
    s->slow[s->count++] = jump_forward(e, CC_A);
    land(e, in_main);
    if (store) {
        /* the block's own code: lea edx, [ecx + size - 1 - start]; cmp edx, bytes + size - 1 */
        e8(e, 0x8d);
        e8(e, 0x91);
        e32(e, size - 1 - b->start);
        alu_imm(e, X_CMP, EDX, b->bytes + size - 1);
        s->slow[s->count++] = jump_forward(e, CC_B);
        e8(e, 0x83); /* cmp dword [check_logging], 0 */
        e8(e, 0x3d);
        e32(e, (uint32_t) (uintptr_t) &check_logging);
        e8(e, 0);
        s->slow[s->count++] = jump_forward(e, CC_NE);
        if (size == 4) {
            e8(e, 0x83); /* cmp dword [ebx + observe_word_store], 0 */
            e8(e, 0xbb);
            e32(e, CPU_OBSERVE);
            e8(e, 0);
            s->slow[s->count++] = jump_forward(e, CC_NE);
        }
    }
}

/* ecx = base register (or the pipeline pc) + offset */
static void address_into_ecx(Emit *e, uint32_t base_reg, uint32_t base_value, uint32_t offset)
{
    if (base_reg == 15) {
        mov_imm(e, ECX, base_value + offset);
        return;
    }
    load_cpu(e, ECX, CPU_R(base_reg));
    if (offset) {
        alu_imm(e, X_ADD, ECX, offset);
    }
}

/* A load or store: the fast path inline, the handler call otherwise. */
static void load_store(Emit *e, const Block *b, const BlockOp *op, uint32_t next, uint32_t index, uint32_t base_reg,
                       uint32_t base_value, uint32_t size, int store)
{
    SlowPaths s = {{0}, 0};
    address_into_ecx(e, base_reg, base_value, op->imm);
    fast_range(e, &s, size, store, b);
    if (store) {
        load_cpu(e, EAX, CPU_R(op->rd));
        if (size == 4) {
            e8(e, 0x89); /* mov [ecx], eax */
            e8(e, 0x01);
        } else if (size == 2) {
            e8(e, 0x66); /* mov [ecx], ax */
            e8(e, 0x89);
            e8(e, 0x01);
        } else {
            e8(e, 0x88); /* mov [ecx], al */
            e8(e, 0x01);
        }
    } else {
        if (size == 4) {
            e8(e, 0x8b); /* mov eax, [ecx] */
            e8(e, 0x01);
        } else {
            e8(e, 0x0f); /* movzx eax, word/byte [ecx] */
            e8(e, size == 2 ? 0xb7 : 0xb6);
            e8(e, 0x01);
        }
        store_cpu(e, EAX, CPU_R(op->rd));
    }
    count_step(e);
    uint8_t *done = jump_forward(e, -1);
    for (int i = 0; i < s.count; i++) {
        land(e, s.slow[i]);
    }
    call_handler(e, op, next, index);
    land(e, done);
}

/* Data processing in x86: eax = a, ecx = the operand, edi = the carry-out when it changes.
 * Returns 0 when the instruction is not one of these. */
static int arm_dp_inline(Emit *e, const BlockOp *op)
{
    uint32_t opcode = op->rs, s = (op->instr >> 20) & 1;
    int carry = 0; /* edi holds the shifter's carry-out */
    if (opcode == 0x5 || opcode == 0x6 || opcode == 0x7) {
        return 0; /* ADC, SBC, RSC: the handler */
    }
    if (op->fn == op_arm_dp_imm) {
        mov_imm(e, ECX, op->imm);
        if (op->rm) {
            mov_imm(e, EDI, op->imm >> 31);
            carry = 1;
        }
    } else {
        uint32_t type = (op->instr >> 5) & 3, amount = op->imm;
        if (type != 0 && amount == 0) {
            return 0; /* LSR #32, ASR #32, RRX */
        }
        load_cpu(e, ECX, CPU_R(op->rm));
        if (amount != 0) {
            alu_reg(e, 0x89, EDI, ECX);
            shift_imm(e, 5, EDI, type == 0 ? 32 - amount : amount - 1);
            alu_imm(e, X_AND, EDI, 1);
            carry = 1;
            shift_imm(e, type == 0 ? 4 : type == 1 ? 5 : type == 2 ? 7 : 1, ECX, amount);
        }
    }
    int logical = 1, writes = 1;
    load_cpu(e, EAX, CPU_R(op->rn));
    switch (opcode) {
        case 0x0: /* AND */
            alu_reg(e, 0x21, EAX, ECX);
            break;
        case 0x1: /* EOR */
            alu_reg(e, 0x31, EAX, ECX);
            break;
        case 0x2: /* SUB */
        case 0xa: /* CMP */
            alu_reg(e, 0x29, EAX, ECX);
            logical = 0;
            writes = opcode == 0x2;
            break;
        case 0x3: /* RSB: operand - a */
            alu_reg(e, 0x89, EDX, EAX);
            alu_reg(e, 0x89, EAX, ECX);
            alu_reg(e, 0x29, EAX, EDX);
            logical = 0;
            break;
        case 0x4: /* ADD */
        case 0xb: /* CMN */
            alu_reg(e, 0x01, EAX, ECX);
            logical = 0;
            writes = opcode == 0x4;
            break;
        case 0x8: /* TST */
            alu_reg(e, 0x21, EAX, ECX);
            writes = 0;
            break;
        case 0x9: /* TEQ */
            alu_reg(e, 0x31, EAX, ECX);
            writes = 0;
            break;
        case 0xc: /* ORR */
            alu_reg(e, 0x09, EAX, ECX);
            break;
        case 0xd: /* MOV */
            alu_reg(e, 0x89, EAX, ECX);
            break;
        case 0xe:        /* BIC */
            e8(e, 0xf7); /* not ecx */
            e8(e, 0xd1);
            alu_reg(e, 0x21, EAX, ECX);
            break;
        default: /* MVN */
            alu_reg(e, 0x89, EAX, ECX);
            e8(e, 0xf7); /* not eax */
            e8(e, 0xd0);
            break;
    }
    if (s || !writes) {
        if (logical) {
            flags_nz(e, carry);
        } else {
            flags_nzcv(e, opcode == 0x2 || opcode == 0xa || opcode == 0x3);
        }
    }
    if (writes) {
        store_cpu(e, EAX, CPU_R(op->rd));
    }
    return 1;
}

/* Thumb's ALU forms with an immediate or low registers: eax = a, ecx = b. */
static int thumb_inline(Emit *e, const BlockOp *op)
{
    if (op->fn == op_thumb_mov8) {
        load_cpu(e, EDX, CPU_CPSR);
        alu_imm(e, X_AND, EDX, 0x3fffffffu);
        if (op->imm == 0) {
            alu_imm(e, X_OR, EDX, ARM_CPSR_Z);
        }
        store_cpu(e, EDX, CPU_CPSR);
        store_cpu_imm(e, CPU_R(op->rd), op->imm);
        return 1;
    }
    if (op->fn == op_thumb_cmp8 || op->fn == op_thumb_add8 || op->fn == op_thumb_sub8) {
        load_cpu(e, EAX, CPU_R(op->rd));
        alu_imm(e, op->fn == op_thumb_add8 ? X_ADD : X_SUB, EAX, op->imm);
        flags_nzcv(e, op->fn != op_thumb_add8);
        if (op->fn != op_thumb_cmp8) {
            store_cpu(e, EAX, CPU_R(op->rd));
        }
        return 1;
    }
    if (op->fn == op_thumb_add3 || op->fn == op_thumb_sub3) {
        if (op->rm == 8) {
            mov_imm(e, ECX, op->imm);
        } else {
            load_cpu(e, ECX, CPU_R(op->rm));
        }
        load_cpu(e, EAX, CPU_R(op->rn));
        alu_reg(e, op->fn == op_thumb_add3 ? 0x01 : 0x29, EAX, ECX);
        flags_nzcv(e, op->fn == op_thumb_sub3);
        store_cpu(e, EAX, CPU_R(op->rd));
        return 1;
    }
    if (op->fn == op_thumb_shift) {
        uint32_t type = op->rs, amount = op->imm;
        if (type != 0 && amount == 0) {
            return 0; /* LSR #32, ASR #32 */
        }
        load_cpu(e, EAX, CPU_R(op->rn));
        if (amount != 0) {
            alu_reg(e, 0x89, EDI, EAX);
            shift_imm(e, 5, EDI, type == 0 ? 32 - amount : amount - 1);
            alu_imm(e, X_AND, EDI, 1);
            shift_imm(e, type == 0 ? 4 : type == 1 ? 5 : 7, EAX, amount);
        }
        flags_nz(e, amount != 0);
        store_cpu(e, EAX, CPU_R(op->rd));
        return 1;
    }
    if (op->fn == op_thumb_add_sp) {
        load_cpu(e, EAX, CPU_R(13));
        alu_imm(e, X_ADD, EAX, op->imm);
        store_cpu(e, EAX, CPU_R(op->rd));
        return 1;
    }
    if (op->fn == op_thumb_add_pc) {
        store_cpu_imm(e, CPU_R(op->rd), op->imm);
        return 1;
    }
    if (op->fn == op_thumb_sp) {
        load_cpu(e, EAX, CPU_R(13));
        alu_imm(e, X_ADD, EAX, op->imm);
        store_cpu(e, EAX, CPU_R(13));
        return 1;
    }
    if (op->fn == op_thumb_bl_high) {
        store_cpu_imm(e, CPU_R(14), op->imm);
        return 1;
    }
    return 0;
}

/* The fields of a load or store the fast path does: its base register, the pipeline pc for a
 * base of r15, its size and direction. 0 when it is not one. */
static int load_store_kind(const BlockOp *op, uint32_t *base_reg, uint32_t *base_value, uint32_t *size, int *store)
{
    static const struct {
        BlockFn fn;
        uint32_t size;
        int store;
    } kinds[] = {
        {op_arm_ldr_imm, 4, 0}, {op_arm_ldrb_imm, 1, 0}, {op_arm_str_imm, 4, 1}, {op_arm_strb_imm, 1, 1},
        {op_thumb_ldr, 4, 0},   {op_thumb_str, 4, 1},    {op_thumb_ldrb, 1, 0},  {op_thumb_strb, 1, 1},
        {op_thumb_ldrh, 2, 0},  {op_thumb_strh, 2, 1},
    };
    for (size_t i = 0; i < sizeof(kinds) / sizeof(kinds[0]); i++) {
        if (op->fn == kinds[i].fn) {
            *base_reg = op->rn;
            *base_value = op->pc + 8;
            *size = kinds[i].size;
            *store = kinds[i].store;
            return 1;
        }
    }
    return 0;
}

static void x86_forget(Block **table, uint32_t slots)
{
    for (uint32_t i = 0; table != NULL && i < slots; i++) {
        if (table[i] != NULL) {
            table[i]->code = NULL;
            table[i]->runs = 0;
        }
    }
}

/* Where the next block's code goes, writable: NULL when the arena is used up (and a run is
 * inside some code, which keeps it). */
static uint8_t *x86_reserve(void)
{
    if (x86_arena == NULL && !x86_failed) {
#ifdef _WIN32
        x86_arena = VirtualAlloc(NULL, X86_ARENA, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        x86_page = info.dwPageSize;
#else
        void *p = mmap(NULL, X86_ARENA, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        x86_arena = p == MAP_FAILED ? NULL : p;
        x86_page = 4096;
#endif
        x86_failed = x86_arena == NULL;
    }
    if (x86_arena != NULL && x86_used + X86_BLOCK_MAX > X86_ARENA && x86_active == 0) {
        /* full, and no run is inside any code: start again, every block untranslated */
        x86_forget(main_blocks, MEM_MAIN_SIZE / 2);
        x86_forget(itcm_blocks, MEM_ITCM_SIZE / 2);
        x86_used = 0;
        x86_flushes++;
    }
    if (x86_arena == NULL || x86_used + X86_BLOCK_MAX > X86_ARENA) {
        return NULL;
    }
    return x86_arena + x86_used;
}

/* Pages [from, to) of the arena writable (1) or executable (0). */
static void x86_protect(uint8_t *from, uint8_t *to, int writable)
{
    uintptr_t lo = (uintptr_t) from & ~(uintptr_t) (x86_page - 1);
    uintptr_t hi = ((uintptr_t) to + x86_page - 1) & ~(uintptr_t) (x86_page - 1);
#ifdef _WIN32
    DWORD old;
    VirtualProtect((void *) lo, hi - lo, writable ? PAGE_READWRITE : PAGE_EXECUTE_READ, &old);
#else
    mprotect((void *) lo, hi - lo, writable ? PROT_READ | PROT_WRITE : PROT_READ | PROT_EXEC);
#endif
}

/* The code of block `b`, or NULL (no room, or more code than a block may take). */
static BlockCode x86_translate(const Block *b)
{
    uint8_t *start = x86_reserve();
    if (start == NULL) {
        return NULL;
    }
    x86_protect(start, start + X86_BLOCK_MAX, 1);
    static Emit emit;
    Emit *e = &emit;
    e->p = start;
    e->end = start + X86_BLOCK_MAX;
    e->fixup_count = 0;
    uint32_t size = b->thumb ? 2 : 4;

    /* push ebp, ebx, esi, edi; sub esp, 28 (16-byte aligned calls, two argument words);
       ebx = cpu, esi = n */
    e8(e, 0x55);
    e8(e, 0x53);
    e8(e, 0x56);
    e8(e, 0x57);
    alu_imm(e, X_SUB, ESP, 28);
    e8(e, 0x8b); /* mov ebx, [esp + 48] */
    e8(e, 0x5c);
    e8(e, 0x24);
    e8(e, 48);
    e8(e, 0x8b); /* mov esi, [esp + 52] */
    e8(e, 0x74);
    e8(e, 0x24);
    e8(e, 52);

    for (uint32_t i = 0; i < b->count; i++) {
        const BlockOp *op = &b->ops[i];
        uint32_t next = op->pc + size, base_reg, base_value, bytes;
        int store;
        uint8_t *mark = e->p;
        int inline_op = 0;
        uint8_t *skip = NULL;
        if (!b->thumb && op->cond != 0xe &&
            (op->fn == op_arm_dp_imm || op->fn == op_arm_dp_reg ||
             load_store_kind(op, &base_reg, &base_value, &bytes, &store))) {
            skip = condition_skip(e, op);
        }
        if (!b->thumb && (op->fn == op_arm_dp_imm || op->fn == op_arm_dp_reg)) {
            inline_op = arm_dp_inline(e, op);
        } else if (b->thumb) {
            inline_op = thumb_inline(e, op);
        }
        if (inline_op) {
            if (skip != NULL) {
                land(e, skip);
            }
            count_step(e);
        } else if (load_store_kind(op, &base_reg, &base_value, &bytes, &store)) {
            load_store(e, b, op, next, i, base_reg, base_value, bytes, store);
            if (skip != NULL) {
                /* the condition failed: the step and r15 as the handler's CONTINUE leaves them */
                uint8_t *over = jump_forward(e, -1);
                land(e, skip);
                count_step(e);
                land(e, over);
            }
        } else {
            e->p = mark; /* (a condition test emitted for nothing) */
            call_handler(e, op, next, i);
        }
        /* dec esi; jz the stub that ends the block here */
        e8(e, 0x4e);
        jump_stub(e, CC_E, i * 2 + 1);
    }
    /* (the last instruction's dec esi always reaches zero or the block's end) */
    jump_stub(e, -1, (b->count - 1) * 2 + 1);

    /* The exits: exit_seq when the block ends after instruction ecx in sequence (r15 the next
       one's, the result CONTINUE), exit_common after a handler's stop or branch (eax its
       result, r15 as the handler left it). Stub 2i jumps to exit_common and 2i + 1 to
       exit_seq, with ecx = i. */
    uint8_t *exit_seq = e->p;
    e8(e, 0x8d); /* lea edx, [ecx * size + start + size] */
    e8(e, 0x14);
    e8(e, size == 4 ? 0x8d : 0x4d);
    e32(e, b->start + size);
    store_cpu(e, EDX, CPU_R(15));
    mov_imm(e, EAX, (uint32_t) CONTINUE);
    uint8_t *exit_common = e->p;
    e8(e, 0x8b); /* mov edx, [esp + 56]; mov [edx], ecx */
    e8(e, 0x54);
    e8(e, 0x24);
    e8(e, 56);
    e8(e, 0x89);
    e8(e, 0x0a);
    alu_imm(e, X_ADD, ESP, 28);
    e8(e, 0x5f);
    e8(e, 0x5e);
    e8(e, 0x5b);
    e8(e, 0x5d);
    e8(e, 0xc3);
    uint8_t *stubs[BLOCK_MAX_OPS * 2];
    for (uint32_t i = 0; i < 2 * b->count; i++) {
        stubs[i] = e->p;
        mov_imm(e, ECX, i / 2);
        uint8_t *to = (i & 1) ? exit_seq : exit_common;
        int32_t back = (int32_t) (to - (e->p + 2));
        if (back >= -128) {
            e8(e, 0xeb);
            e8(e, (uint32_t) back);
        } else {
            e8(e, 0xe9);
            e32(e, (uint32_t) (to - (e->p + 4)));
        }
    }

    if (e->p >= e->end) {
        x86_protect(start, start + X86_BLOCK_MAX, 0);
        return NULL;
    }
    for (uint32_t i = 0; i < e->fixup_count; i++) {
        uint8_t *at = (uint8_t *) (uintptr_t) e->fixups[i][0];
        uint32_t rel = (uint32_t) (stubs[e->fixups[i][1]] - (at + 4));
        memcpy(at, &rel, 4);
    }
    uint32_t used = (uint32_t) (e->p - start);
    x86_used += (used + 15) & ~15u;
    x86_protect(start, start + X86_BLOCK_MAX, 0);
#ifdef _WIN32
    FlushInstructionCache(GetCurrentProcess(), start, used);
#endif
    x86_blocks++;
    return (BlockCode) (uintptr_t) start;
}
