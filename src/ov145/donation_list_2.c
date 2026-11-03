/* donation_list_2: 17 functions, module ov145
 * mwccarm 1.2/base -O4,s
 * func_ov145_02299e2c @ 0x02299e2c, 0x18 bytes, Thumb
 * func_ov145_02299e08 @ 0x02299e08, 0x24 bytes, Thumb
 * func_ov145_02299dd0 @ 0x02299dd0, 0x38 bytes, Thumb
 * func_ov145_02299da4 @ 0x02299da4, 0x2c bytes, Thumb
 * func_ov145_02299c40 @ 0x02299c40, 0x164 bytes, Thumb
 * func_ov145_02299bd0 @ 0x02299bd0, 0x70 bytes, Thumb
 * func_ov145_02299b94 @ 0x02299b94, 0x3a bytes, Thumb
 * func_ov145_02299b1c @ 0x02299b1c, 0x78 bytes, Thumb
 * func_ov145_02299aac @ 0x02299aac, 0x70 bytes, Thumb
 * func_ov145_02299a34 @ 0x02299a34, 0x78 bytes, Thumb
 * func_ov145_02299a24 @ 0x02299a24, 0x10 bytes, Thumb
 * func_ov145_022999c4 @ 0x022999c4, 0x60 bytes, Thumb
 * func_ov145_0229996c @ 0x0229996c, 0x56 bytes, Thumb
 * func_ov145_02299954 @ 0x02299954, 0x18 bytes, Thumb
 * func_ov145_022998f0 @ 0x022998f0, 0x64 bytes, Thumb
 * func_ov145_022998c4 @ 0x022998c4, 0x2c bytes, Thumb
 * func_ov145_022997d0 @ 0x022997d0, 0xf4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xb6];
    s16 unk_B6;
    char pad_B8[0xcb4 - 0xb8];
    u16 arr[9];
} UnkStruct_02299c40;

typedef struct {
    int b[10];
} UnkStruct_02299c40_2;

typedef struct {
    int b[8];
} Ctx2;

typedef struct {
    char pad_00[0xb6];
    short unk_B6;
    char pad_B8[0xc0e];
    unsigned char dest[9][128];
    char pad_1146[0x380];
    unsigned char src[16][128];
} UnkStruct_02299b1c;

typedef struct {
    char pad_00[0x9c];
    int A;
    int B;
} UnkStruct_02299a34;

typedef struct {
    char pad_00[0xA0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0x18];
    unsigned char unk_C0;
} UnkStruct_0229996c;

typedef struct UnkSub {
    char pad_00;
} UnkSub;

typedef struct UnkStruct_022998f0 {
    char pad_00[0xc1];
    unsigned char unk_C1;
    char pad_C2[0x6a];
    UnkSub unk_12C;
} UnkStruct_022998f0;

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0xc2 - 0xa8];
    volatile u8 unk_C2;
} UnkStruct_022997d0;

extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);
extern void func_02070b84(void *);
extern char data_021f38f8[];
extern void *func_02094fd4(Ctx2 *c);
extern void *func_02094fbc(Ctx2 *c);
extern void *func_02062fbc(UnkStruct_02299c40_2 *c);
extern void *func_02062f4c(UnkStruct_02299c40_2 *c);
extern void func_020a8c1c(void *h);
extern int func_02062ea4(UnkStruct_02299c40_2 *c, u16 *p);
extern void *func_020a8bb8(void *h, void *c);
extern int func_02070fe4(char *t, Ctx2 *c, u16 *p);
extern int func_0207094c(void *h, int a);
extern void func_02070adc(void *h, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *h, int a, int b);
extern int func_ov145_02299668(char *, int);
extern int func_020b9bbc(const char *, const char *, int, int, int);
extern void func_ov145_02299648(char *, int);
extern void func_0200284c(int, int, int);
extern void func_ov145_02299658(void *, int);
extern void MIi_CpuClear16(int, void *, int);
extern void MIi_CpuCopy16(void *, const void *, int);
extern void func_0206fdd4(char *ptr, int a, int b, int c, int d, int e);
extern void func_ov145_0229a0d0(UnkStruct_02299a34 *p);
extern void func_ov145_0229a134(UnkStruct_0229996c *self);
extern void func_0200467c(int cmd);
extern void func_ov145_0229a2e0(UnkStruct_022998f0 *self);
extern void func_ov002_0220a574(UnkSub *sub);
extern void func_ov002_0220a4bc(void *receiver);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_0220889c(void *p);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088bc(void *p);

void func_ov145_02299b1c(UnkStruct_02299b1c *self);
void func_ov145_02299aac(char *self);
short func_ov145_02299a24(unsigned char *arg0);
void *func_ov145_022999c4(void *self, int off);

void func_ov145_02299e2c(void *self)
{
    func_ov002_0220a1dc((char *) self + 0xc8);
    func_ov002_02208098((void *) (self), 7);
}

void func_ov145_02299e08(void *self)
{
    unsigned char b;

    func_ov002_0220a164((char *) self + 0xc8);
    b = *(unsigned char *) ((char *) self + 0x8d);
    *(unsigned char *) ((char *) self + 0xc3) = b;
    func_ov002_02208098((void *) (self), 8);
}

unsigned char *func_ov145_02299dd0(unsigned char *param)
{
    volatile unsigned char *p = param;
    if (p[0xc4] >= 0x12) {
        return param + 0xa6c;
    }
    p[0xc4] = p[0xc4] + 1;
    return param + 0x340 + 108 * (p[0xc4] - 1);
}

void func_ov145_02299da4(void *self)
{
    int i;
    char *p;

    p = (char *) self + 0xc4;
    *p = 0;
    for (i = 0; i < 0x12; i++) {
        func_02070b84((char *) self + 0x340 + i * 0x6c);
    }
}

void func_ov145_02299c40(UnkStruct_02299c40 *self)
{
    Ctx2 ctx2;
    UnkStruct_02299c40_2 ctx;
    u16 tmp[2];
    int i;
    void *h;
    void *h2;
    int limit;
    int row;
    int col;
    u16 *src;

    func_02094fd4(&ctx2);
    func_02062fbc(&ctx);
    row = self->unk_B6;
    src = (u16 *) func_ov145_022999c4((void *) self, row);
    col = (row + 9) % 9;
    limit = (int) func_ov145_02299a24((unsigned char *) self);
    for (i = 0; i < 9; i++) {
        h = 0;
        if (row < 0 || row >= limit) {
            self->arr[col] = 0xfff1;
            h = (void *) func_ov145_02299dd0((unsigned char *) self);
            func_020a8c1c(h);
            h2 = (void *) func_ov145_02299dd0((unsigned char *) self);
            func_020a8c1c(h2);
        } else {
            if (*src != self->arr[col]) {
                self->arr[col] = *src;
                h = (void *) func_ov145_02299dd0((unsigned char *) self);
                tmp[0] = *src;
                func_02062ea4(&ctx, &tmp[0]);
                func_020a8bb8(h, &ctx);
                h2 = (void *) func_ov145_02299dd0((unsigned char *) self);
                tmp[1] = *src;
                if (func_02070fe4(data_021f38f8, &ctx2, &tmp[1]) != 0) {
                    func_020a8bb8(h2, &ctx2);
                } else {
                    func_0207094c(h2, 0xcc);
                }
            }
            src++;
        }
        if (h != 0) {
            func_02070adc(h, 4, col * 0x1a + 0x184, 0xd, 0xf, 7, 0);
            func_02070a04(h, 0, 0);
            func_02070adc(h2, 4, col * 0x10 + 0xf4, 8, 0xf, 7, 0);
            func_02070a04(h2, 0, 0);
        }
        row++;
        col++;
        if (col >= 9) {
            col = 0;
        }
    }
    func_02062f4c(&ctx);
    func_02094fbc(&ctx2);
}

void func_ov145_02299bd0(char *arg)
{
    if (func_ov145_02299668(arg, 8)) {
        func_ov145_02299aac(arg);
    }

    if (func_ov145_02299668(arg, 2)) {
        if (func_020b9bbc(arg + 0xafc, arg + 0x1cc6, 6, 0x800, 0)) {
            func_ov145_02299648(arg, 2);
        }
    }

    if (func_ov145_02299668(arg, 4)) {
        func_ov145_02299648(arg, 4);
        func_ov145_02299c40((UnkStruct_02299c40 *) arg);
    }
}

void func_ov145_02299b94(void *self, int value)
{
    int *p;
    int *q;
    int tmp;

    p = (int *) ((char *) self + 0x9c);
    *p = value;
    tmp = *p - 0x18;
    func_0200284c(4, 0, tmp);
    *(unsigned short *) ((char *) self + 0xb6) = (short) (value >> 4);
    func_ov145_02299b1c((UnkStruct_02299b1c *) self);
    func_ov145_02299658(self, 4);
}

void func_ov145_02299b1c(UnkStruct_02299b1c *self)
{
    int rem = (self->unk_B6 + 9) % 9;
    int sub = self->unk_B6 & 0xF;
    volatile unsigned short v = 0x10;
    int zero = 0;
    int i;

    MIi_CpuClear16(v, (void *) self->src, 0x800);

    i = 0;
    do {
        MIi_CpuCopy16(&self->dest[rem], &self->src[sub], 0x80);
        rem++;
        if (rem >= 9) {
            rem = zero;
        }
        sub = (sub + 1) & 0xF;
        i++;
    } while (i < 9);

    func_ov145_02299658(self, 8);
}

void func_ov145_02299aac(char *self)
{
    int zero = 0;

    func_0206fdd4(self + 0x14c6, zero, zero, 31, 31, 3);
    {
        int ret = (int) func_ov145_02299a24((unsigned char *) self);
        if (ret < 9) {
            func_0206fdd4(self + 0x14c6, zero, ret * 2, 31, 18, 4);
        }
    }
    if (func_020b9bbc((const char *) (self + 0xad8), (const char *) (self + 0x14c6), 4, 0x800, 0) != 0) {
        func_ov145_02299648(self, 8);
    }
}

void func_ov145_02299a34(UnkStruct_02299a34 *p)
{
    if (p->A == p->B) {
        return;
    }
    if (p->A > p->B) {
        p->A = p->A - 4;
        if (p->A < p->B) {
            p->A = p->B;
        }
    } else {
        p->A = p->A + 4;
        if (p->A > p->B) {
            p->A = p->B;
        }
    }
    func_ov145_02299b94((void *) p, p->A);
    func_ov145_0229a0d0(p);
}

short func_ov145_02299a24(unsigned char *arg0)
{
    unsigned char val;
    short val2;

    val = *(unsigned char *) (arg0 + 0xc0);
    val2 = *(short *) (arg0 + (val << 1) + 0xb8);
    return val2;
}

void *func_ov145_022999c4(void *self, int off)
{
    static int inited = 0;
    static void *table[4];
    unsigned char sel;
    void *base;

    if (!(inited & 1)) {
        table[0] = (char *) self + 0xc8c;
        table[1] = (char *) self + 0xbac;
        table[2] = (char *) self + 0xc1c;
        table[3] = (char *) self + 0xb44;
        inited |= 1;
    }
    if (off < 0) {
        off = 0;
    }
    sel = *((unsigned char *) self + 0xc0);
    base = table[sel];
    return (char *) base + off * 2;
}

void func_ov145_0229996c(UnkStruct_0229996c *self, unsigned char value)
{
    if (self->unk_C0 == value) {
        return;
    }
    self->unk_C0 = value;
    self->unk_A4 = ((int) func_ov145_02299a24((unsigned char *) self) - 8) << 4;
    if (self->unk_A4 < 0) {
        self->unk_A4 = 0;
    }
    func_ov145_02299b94((void *) self, 0);
    self->unk_A0 = 0;
    func_ov145_0229a0d0((UnkStruct_02299a34 *) self);
    func_ov145_0229a134(self);
}

void func_ov145_02299954(unsigned char *p, unsigned char v)
{
    if (v != p[0xc1]) {
        p[0xc1] = v;
        p[0xc6] = 1;
    }
}

int func_ov145_022998f0(UnkStruct_022998f0 *self, unsigned int param)
{
    if (param <= 3) {
        if (param != self->unk_C1) {
            func_0200467c(0xc);
            func_ov145_02299954((unsigned char *) self, (unsigned char) param);
        }
        return 0;
    } else {
        switch (param) {
            case 4:
                func_ov145_0229a2e0(self);
                return 1;
            case 5:
                func_ov002_0220a574(&self->unk_12C);
                func_ov002_0220a4bc(&self->unk_12C);
                func_ov002_02208098((void *) (self), 4);
                return 1;
            default:
                return 0;
        }
    }
}

int func_ov145_022998c4(int unused, int target, int val)
{
    int i;
    int low;

    if (val >= 0x9d && val < 0xbd) {
        for (low = 0x84, i = 0; i < 4; low -= 0x24, i++) {
            if (low > target || low + 0x20 <= target) {
                continue;
            }
            return (unsigned char) i;
        }
    }
    return 6;
}

int func_ov145_022997d0(UnkStruct_022997d0 *self, void *pad)
{
    u8 st = self->unk_C2;

    if (st <= 3) {
        if (func_ov002_022088ac(pad) != 0) {
            if (self->unk_C2 < 3) {
                self->unk_C2 = self->unk_C2 + 1;
            }
        } else if (func_ov002_0220889c(pad) != 0) {
            if (self->unk_C2 != 0) {
                self->unk_C2 = self->unk_C2 - 1;
            } else {
                self->unk_C2 = 4;
            }
        } else if (func_ov002_022088cc(pad) != 0) {
            if (self->unk_A4 > 0) {
                self->unk_C2 = 5;
            }
        }
    } else {
        switch (st) {
            case 4:
                if (func_ov002_022088cc(pad) != 0) {
                    if (self->unk_A4 > 0) {
                        self->unk_C2 = 5;
                    }
                } else if (func_ov002_022088ac(pad) != 0) {
                    self->unk_C2 = 0;
                }
                break;
            case 5:
                if (func_ov002_022088bc(pad) != 0) {
                    self->unk_C2 = 4;
                } else if (func_ov002_022088ac(pad) != 0) {
                    self->unk_C2 = 0;
                }
                break;
        }
    }
    if (st != self->unk_C2) {
        return 1;
    } else {
        return 0;
    }
}
