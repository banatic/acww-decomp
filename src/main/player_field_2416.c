/* player_field_2416: 29 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02088bdc @ 0x02088bdc, 0x4 bytes, Thumb
 * func_02088bd8 @ 0x02088bd8, 0x4 bytes, Thumb
 * func_02088bd4 @ 0x02088bd4, 0x4 bytes, Thumb
 * func_02088bc4 @ 0x02088bc4, 0xe bytes, Thumb
 * func_02088bc0 @ 0x02088bc0, 0x4 bytes, Thumb
 * func_02088bac @ 0x02088bac, 0x12 bytes, Thumb
 * func_02088ba8 @ 0x02088ba8, 0x4 bytes, Thumb
 * func_02088b98 @ 0x02088b98, 0xe bytes, Thumb
 * func_02088b94 @ 0x02088b94, 0x4 bytes, Thumb
 * func_02088b80 @ 0x02088b80, 0x12 bytes, Thumb
 * func_02088b7c @ 0x02088b7c, 0x4 bytes, Thumb
 * func_02088b68 @ 0x02088b68, 0x12 bytes, Thumb
 * func_02088b64 @ 0x02088b64, 0x4 bytes, Thumb
 * func_02088b50 @ 0x02088b50, 0x12 bytes, Thumb
 * func_02088b48 @ 0x02088b48, 0x8 bytes, Thumb
 * func_02088b38 @ 0x02088b38, 0xe bytes, Thumb
 * func_02088b30 @ 0x02088b30, 0x8 bytes, Thumb
 * func_02088b1c @ 0x02088b1c, 0x12 bytes, Thumb
 * func_02088b14 @ 0x02088b14, 0x8 bytes, Thumb
 * func_02088ad4 @ 0x02088ad4, 0x40 bytes, Thumb
 * func_02088ac8 @ 0x02088ac8, 0xa bytes, Thumb
 * func_02088ac0 @ 0x02088ac0, 0x8 bytes, Thumb
 * func_02088ab8 @ 0x02088ab8, 0x8 bytes, Thumb
 * func_02088aac @ 0x02088aac, 0xa bytes, Thumb
 * func_02088aa0 @ 0x02088aa0, 0xa bytes, Thumb
 * func_02088a9c @ 0x02088a9c, 0x2 bytes, Thumb
 * func_02088a78 @ 0x02088a78, 0x22 bytes, Thumb
 * func_02088a74 @ 0x02088a74, 0x4 bytes, Thumb
 * func_02088a60 @ 0x02088a60, 0x12 bytes, Thumb
 */

struct UnkStruct_02088b80 {
    unsigned char pad_00[12];
    unsigned char value;
};

struct UnkStruct_02088b38 {
    unsigned char pad_00[0x10];
    unsigned char flag;
};

typedef struct {
    unsigned char lo : 2;
    unsigned char val : 4;
    unsigned char hi : 2;
} Bits;

typedef struct {
    unsigned char pad_00[0x10];
    Bits bits;
} UnkStruct_02088ad4;

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char flags;
} UnkStruct_02088aac;

typedef struct {
    unsigned char pad_00[0x10];
    unsigned char flags;
} UnkStruct_02088aa0;

extern void func_0209df64(void *);

int func_02088bdc(unsigned char *p0)
{
    return p0[8];
}

void func_02088bd8(unsigned char *p0, int p1)
{
    p0[8] = p1;
}

int func_02088bd4(unsigned char *p0)
{
    return p0[9];
}

void func_02088bc4(volatile unsigned char *field, unsigned char value)
{
    field[9] = value;
    if (field[9] > 0xf) {
        field[9] = 0xf;
    }
}

int func_02088bc0(unsigned char *p0)
{
    return p0[10];
}

void func_02088bac(void *r0, int r1)
{
    unsigned char r2;
    unsigned char r1b;

    r2 = *(unsigned char *) ((char *) r0 + 0xa);
    r1b = (unsigned char) (r2 + r1);
    *(unsigned char *) ((char *) r0 + 0xa) = r1b;
    r1b = *(unsigned char *) ((char *) r0 + 0xa);
    if (r1b > 0x10) {
        *(unsigned char *) ((char *) r0 + 0xa) = 0x10;
    }
}

int func_02088ba8(unsigned char *p0)
{
    return p0[11];
}

void func_02088b98(unsigned char *r0, int r1)
{
    unsigned char r2;
    int r1_temp;

    r2 = r0[0xb];
    r1_temp = r2 + r1;
    if (r1_temp > 0xff) {
        r1_temp = 0xff;
    }
    r0[0xb] = (unsigned char) r1_temp;
}

int func_02088b94(unsigned char *p0)
{
    return p0[12];
}

void func_02088b80(struct UnkStruct_02088b80 *p)
{
    p->value = p->value + 1;
    if (p->value > 12) {
        p->value = 12;
    }
}

int func_02088b7c(unsigned char *p0)
{
    return p0[13];
}

void func_02088b68(unsigned char *p)
{
    p[13] += 1;
    if (p[13] > 6) {
        p[13] = 6;
    }
}

int func_02088b64(unsigned char *p0)
{
    return p0[14];
}

void func_02088b50(unsigned char *r0, unsigned char r1)
{
    unsigned char r2;
    unsigned char r1b;

    r2 = r0[0xe];
    r1b = r2 + r1;
    r0[0xe] = r1b;
    r1b = r0[0xe];
    if (r1b > 0x64) {
        r1b = 0x64;
        r0[0xe] = r1b;
    }
}

int func_02088b48(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[16] << 31)) >> 31);
}

void func_02088b38(struct UnkStruct_02088b38 *s, int val)
{
    s->flag = (s->flag & ~1) | (val & 1);
}

int func_02088b30(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[16] << 30)) >> 31);
}

void func_02088b1c(unsigned char *p, unsigned int v)
{
    p[0x10] = (p[0x10] & ~2) | ((v & 1) << 1);
}

int func_02088b14(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[16] << 26)) >> 28);
}

void func_02088ad4(UnkStruct_02088ad4 *p)
{
    Bits *b = &p->bits;
    p->bits.val = p->bits.val + 1;
    if ((unsigned int) p->bits.val > 0xA) {
        b->val = 0xA;
    }
}

void func_02088ac8(unsigned char *p)
{
    p[16] = (unsigned char) (p[16] & ~60);
}

void func_02088ac0(unsigned char *p0)
{
    p0[11] = 0;
    p0[12] = 0;
}

int func_02088ab8(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[16] << 25)) >> 31);
}

void func_02088aac(UnkStruct_02088aac *p)
{
    p->flags |= 0x40;
}

void func_02088aa0(UnkStruct_02088aa0 *p)
{
    p->flags &= ~0x40;
}

void *func_02088a9c(void *record)
{
    return record;
}

void func_02088a78(void *param)
{
    unsigned char local[3];
    func_0209df64(local);
    ((unsigned char *) param)[2] = local[2];
    ((unsigned char *) param)[1] = local[1];
    ((unsigned char *) param)[0] = local[0];
}

int func_02088a74(unsigned char *p0)
{
    return p0[15];
}

void func_02088a60(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned char v;

    v = p[0xf];
    v++;
    p[0xf] = v;

    v = p[0xf];
    if (v < 0xff) {
        // nothing
    } else {
        p[0xf] = 0xff;
    }
}
