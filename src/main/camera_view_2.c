/* camera_view_2: 22 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203c76c @ 0x0203c76c, 0x28 bytes, Thumb
 * func_0203c610 @ 0x0203c610, 0x15c bytes, Thumb
 * func_0203c600 @ 0x0203c600, 0x10 bytes, Thumb
 * func_0203c5a8 @ 0x0203c5a8, 0x56 bytes, Thumb
 * func_0203c59c @ 0x0203c59c, 0xc bytes, Thumb
 * func_0203c590 @ 0x0203c590, 0xc bytes, Thumb
 * func_0203c57c @ 0x0203c57c, 0x14 bytes, Thumb
 * func_0203c568 @ 0x0203c568, 0x14 bytes, Thumb
 * func_0203c558 @ 0x0203c558, 0x10 bytes, Thumb
 * func_0203c548 @ 0x0203c548, 0x10 bytes, Thumb
 * func_0203c53c @ 0x0203c53c, 0xc bytes, Thumb
 * func_0203c528 @ 0x0203c528, 0x14 bytes, Thumb
 * func_0203c4e4 @ 0x0203c4e4, 0x44 bytes, Thumb
 * func_0203c4d0 @ 0x0203c4d0, 0x14 bytes, Thumb
 * func_0203c4bc @ 0x0203c4bc, 0x14 bytes, Thumb
 * func_0203c40c @ 0x0203c40c, 0xb0 bytes, Thumb
 * func_0203c3ec @ 0x0203c3ec, 0x20 bytes, Thumb
 * func_0203c3c4 @ 0x0203c3c4, 0x26 bytes, Thumb
 * func_0203c2d4 @ 0x0203c2d4, 0xf0 bytes, Thumb
 * func_0203c23c @ 0x0203c23c, 0x98 bytes, Thumb
 * func_0203c210 @ 0x0203c210, 0x2c bytes, Thumb
 * func_0203c1e0 @ 0x0203c1e0, 0x30 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0203c610 {
    u8 pad_00[0x50];
    u8 sub50[0x40];
    u32 unk_90;
    u32 unk_94;
    s16 unk_98;
    u8 pad_9A[0x188 - 0x9A];
    u32 unk_188;
    u32 unk_18C;
    u32 unk_190;
    u32 unk_194;
    u32 unk_198;
    u32 unk_19C;
    u32 unk_1A0;
    u32 unk_1A4;
    u32 unk_1A8;
    u8 pad_1AC[0x1b0 - 0x1ac];
    u32 unk_1B0;
    u32 unk_1B4;
    u32 unk_1B8;
    u8 pad_1BC[0x1c8 - 0x1bc];
    s16 unk_1C8;
};

struct UnkStruct_0203c57c {
    char pad_00[0x9a];
    short unk_9A;
    char pad_9C[0xae];
    short unk_14A;
};

typedef struct UnkStruct_0203c568 {
    char pad_00[0x9c];
    short unk_9C;
    char pad_9E[0xaa];
    short unk_148;
} UnkStruct_0203c568;

typedef struct {
    char pad_00[0xAC];
    int unk_AC;
    char pad_B0[0x0C];
    int unk_BC;
} Func0203c4e4Ctx;

typedef struct {
    unsigned char pad_00[0x90];
    int unk_90;
    int unk_94;
    short unk_98;
    unsigned char pad_9A[0x1b0 - 0x9a];
    int unk_1B0;
    int unk_1B4;
    int unk_1B8;
    int unk_1BC;
    int unk_1C0;
    int unk_1C4;
    short unk_1C8;
} UnkStruct_0203c40c;

struct func_0203c3ec_obj {
    char pad_00[0x194];
    char data[0x18];
    short result;
};

typedef struct {
    u8 pad_00[4];
    u8 flag;
} UnkStruct_0203c2d4;

typedef struct {
    u8 pad_00[0x178];
    int unk_178;
    int unk_17C;
    int unk_180;
    int unk_184;
} UnkStruct_0203c2d4_2;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
} CondStruct;

typedef struct {
    unsigned char pad[0x178];
    int a;
    int b;
    int c;
    int d;
} Input;

typedef struct {
    int v;
    int pad;
    int w;
} Output;

typedef struct {
    unsigned int words[3];
} Source;

typedef struct {
    char pad_00[0x14];
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Dest;

struct UnkStruct_0203c1e0 {
    char pad_00[0x178];
    int unk_178;
    int unk_17C;
};

extern void func_0203c068(void *);
extern void func_0203f684(void *dst, void *src);
extern void func_01ffcbb0(void *dst, void *src);
extern unsigned char data_021c749c[];
extern void G3i_PerspectiveW_(int a, int b, int c, int d, int e, int f, int g, void *h);
extern void G3i_LookAt_(void *a, void *b, void *c, int d, void *e);
extern int MTX_Inverse43(void *a, void *b);
extern int func_020b9464(void *self);
extern s16 FX_SinCosTable_[];
extern struct {
    u8 pad_00[0x7c];
    u32 unk_7C;
} data_027e0148;
extern u32 data_027e02c8[];
extern char data_027e00d0[];
extern char data_027e0114[];
extern int data_021c67a4;
extern int FX_InvA(int);
extern int FX_MulFunc(int, int);
extern void func_0203a958(void *, int, int, int, int);
extern int data_021f6a6c;
extern short func_0203f768(void *);
extern UnkStruct_0203c2d4 *data_021f6948;
extern int data_020ca0e8;
extern CondStruct *data_021c80bc;
extern int func_02030738(void *, void *, void *, void *);
extern int func_020b65c4(void);
extern int func_02037e84(u32);
extern void func_0203caa4(void *p, int a, int b);

int func_0203c4d0(int *param);
int func_0203c4bc(void *ptr);

int func_0203c76c(void *arg0)
{
    char sp[0x10];
    func_0203c068(arg0);
    func_01ffcbb0(sp, arg0);
    func_0203f684((void *) data_021c749c, sp);
    return 1;
}

void func_0203c610(struct UnkStruct_0203c610 *self)
{
    int idx1 = self->unk_1C8 >> 5;
    u32 val;
    val = self->unk_1B8;
    G3i_PerspectiveW_(FX_SinCosTable_[idx1 * 2], FX_SinCosTable_[(idx1 * 2) + 1], self->unk_1B0, self->unk_1B4, val, 0x1000, 1,
                      0);
    G3i_LookAt_(&self->unk_194, &self->unk_1A0, &self->unk_188, 1, self->sub50);
    MTX_Inverse43(self->sub50, (void *) (((u8 *) self) + 0xcc));
    {
        short sum2 = (short) (self->unk_1C8 + self->unk_98);
        int idx2 = sum2 >> 5;
        G3i_PerspectiveW_(FX_SinCosTable_[idx2 * 2], FX_SinCosTable_[(idx2 * 2) + 1], self->unk_1B0,
                          self->unk_1B4 + self->unk_90, self->unk_1B8 + self->unk_94, 0x1000, 0, data_027e00d0);
    }
    data_027e0148.unk_7C = data_027e0148.unk_7C & ~0x50;
    {
        u32 *dst = data_027e02c8;
        dst[0x40 / 4] = self->unk_194;
        dst[0x44 / 4] = self->unk_198;
        dst[0x48 / 4] = self->unk_19C;
        dst[0x4c / 4] = self->unk_1A0;
        dst[0x50 / 4] = self->unk_1A4;
        dst[0x54 / 4] = self->unk_1A8;
        dst[0x58 / 4] = self->unk_188;
        dst[0x5c / 4] = self->unk_18C;
        dst[0x60 / 4] = self->unk_190;
    }
    G3i_LookAt_(&self->unk_194, &self->unk_1A0, &self->unk_188, 0, data_027e0114);
    data_027e0148.unk_7C = data_027e0148.unk_7C & ~0xe8;
    func_020b9464(self);
}

int func_0203c600(void)
{
    data_021c67a4 = 0;
    return 1;
}

void func_0203c5a8(void *p)
{
    *(int *) ((char *) p + 0x80) = 0;
    *(short *) ((char *) p + 0x9a) = 0;
    *(short *) ((char *) p + 0x9c) = 0;
    *(int *) ((char *) p + 0x84) = 0;
    *(int *) ((char *) p + 0x88) = 0;
    *(int *) ((char *) p + 0x8c) = 0;
    *(short *) ((char *) p + 0x98) = 0;
    *(int *) ((char *) p + 0x90) = 0;
    *(int *) ((char *) p + 0x94) = 0;
    *(int *) ((char *) p + 0xa0) = 0;
    *(int *) ((char *) p + 0xa8) = 0;
    *(int *) ((char *) p + 0xac) = 0;
    *(int *) ((char *) p + 0xb0) = 0;
    *(int *) ((char *) p + 0xb4) = 0;
}

unsigned int func_0203c59c(unsigned int arg0)
{
    return arg0 + 0x168;
}

short func_0203c590(char *r0)
{
    return *(short *) (r0 + 0x1ac);
}

short func_0203c57c(struct UnkStruct_0203c57c *arg)
{
    return arg->unk_14A + arg->unk_9A;
}

short func_0203c568(UnkStruct_0203c568 *p)
{
    return (short) (p->unk_148 + p->unk_9C);
}

unsigned int func_0203c558(unsigned int *arg0)
{
    unsigned int *ptr;
    unsigned int value;
    unsigned int result;

    ptr = (unsigned int *) ((unsigned int) arg0 + 0xa0);
    value = *ptr;
    result = value + 0xf0a;
    return result;
}

int func_0203c548(void *self)
{
    unsigned int offset = 0x14c;
    int value1 = *(int *) ((char *) self + offset);
    int value2 = *(int *) ((char *) self + 0x80);
    return value1 + value2;
}

unsigned int func_0203c53c(unsigned int *param0)
{
    return param0[0x71];
}

int func_0203c528(void *param)
{
    int result;
    int *ptr1;
    int *ptr2;

    ptr1 = (int *) ((char *) param + 0xb8);
    ptr2 = (int *) ((char *) param + 0xa8);
    result = *ptr1 + *ptr2;
    if (result < 0) {
        result = 0;
    }
    return result;
}

int func_0203c4e4(Func0203c4e4Ctx *p)
{
    int a, b, c, total, sum;
    a = func_0203c4bc((void *) p);
    b = func_0203c528((void *) p);
    c = func_0203c4d0((int *) p);
    total = a + (b + c);
    if (p->unk_BC < total) {
        p->unk_BC = total;
    }
    sum = p->unk_BC + p->unk_AC;
    if (sum < total) {
        return total;
    }
    return sum;
}

int func_0203c4d0(int *param)
{
    int r1;
    int r0;
    int result;

    r1 = *(int *) ((char *) param + 0xc0);
    r0 = *(int *) ((char *) param + 0xb0);
    result = r1 + r0;
    if (result < 0) {
        result = 0;
    }
    return result;
}

int func_0203c4bc(void *ptr)
{
    int sum;
    sum = *(int *) ((char *) ptr + 0xC4) + *(int *) ((char *) ptr + 0xB4);
    if (sum < 0) {
        return 0;
    }
    return sum;
}

void func_0203c40c(UnkStruct_0203c40c *self, short val)
{
    int sum1, sum2;
    unsigned int u1, u2;
    int i, j;
    int arg5;

    self->unk_1C8 = val;

    sum1 = (int) self->unk_1C8 + (int) self->unk_98;
    u1 = (unsigned int) ((sum1 << 16) >> 1);
    u2 = u1 >> 16;
    i = (int) u2 >> 4;
    self->unk_1BC = ((short *) FX_SinCosTable_)[2 * i];

    sum2 = (int) self->unk_1C8 + (int) self->unk_98;
    u1 = (unsigned int) ((sum2 << 16) >> 1);
    u2 = u1 >> 16;
    j = (int) u2 >> 4;
    self->unk_1C0 = ((short *) FX_SinCosTable_)[2 * j + 1];

    self->unk_1C4 = FX_MulFunc(self->unk_1BC, FX_InvA(self->unk_1C0));

    arg5 = self->unk_1B8 + self->unk_94;
    func_0203a958(&data_021f6a6c, self->unk_1B0, (short) (self->unk_1C8 + self->unk_98), self->unk_1B4 + self->unk_90, arg5);
}

void func_0203c3ec(struct func_0203c3ec_obj *s)
{
    s->result = func_0203f768(&s->data);
}

void func_0203c3c4(const void *src, int *out1, int *out2)
{
    int stack[3];
    func_01ffcbb0(stack, (void *) src);
    *out1 = stack[0] >> 17;
    *out2 = stack[2] >> 17;
}

void func_0203c2d4(UnkStruct_0203c2d4_2 *self)
{
    if (data_021f6948->flag == 0) {
        func_02030738(&self->unk_178, &self->unk_17C, &self->unk_180, &self->unk_184);
        if (self->unk_184 < data_020ca0e8) {
            self->unk_184 = data_020ca0e8;
        }
    }
    if (func_020b65c4() == 0x29) {
        self->unk_17C += 0x4000;
        self->unk_184 += 0x4000;
    } else {
        u32 arg;
        u32 zero = 0;
        if (data_021c80bc->unk_04 > zero && data_021c80bc->unk_08 > zero && data_021c80bc->unk_00 != 0) {
            arg = data_021c80bc->unk_00;
        } else {
            arg = 0;
        }
        switch (func_02037e84(arg)) {
            case 0x1009:
            case 0x100c:
                self->unk_178 += 0x2000;
                break;
            case 0x100a:
                self->unk_17C -= 0x2000;
                break;
            case 0x100b:
            case 0x100d:
                self->unk_178 += 0x2000;
                self->unk_17C -= 0x2000;
                break;
            default:
                break;
        }
    }
}

int func_0203c23c(Input *in, Output *out)
{
    int changed = 0;
    int a, b, c, d;
    int diff, diff_y;
    int max, cur, min;
    int max_y, cur_y, min_y;

    a = in->a;
    b = in->b;
    diff = b - a;
    if (diff <= 0xa000) {
        out->v = (b + a) >> 1;
        changed = 1;
    } else {
        max = a + 0x5000;
        cur = out->v;
        if (cur < max) {
            out->v = max;
            changed = 1;
        } else {
            min = b - 0x5000;
            if (cur > min) {
                out->v = min;
                changed = 1;
            }
        }
    }

    c = in->c;
    d = in->d;
    diff_y = d - c;
    if (diff_y <= 0x7000) {
        out->w = (d + c) >> 1;
        changed = 1;
    } else {
        max_y = c + 0x2000;
        cur_y = out->w;
        if (cur_y < max_y) {
            out->w = max_y;
            changed = 1;
        } else {
            min_y = d - 0x5000;
            if (cur_y > min_y) {
                out->w = min_y;
                changed = 1;
            }
        }
    }

    return changed;
}

void func_0203c210(char *r0, Dest *r1, Source *r2)
{
    Dest *r5 = r1;
    if (r5 == 0) {
        r5 = (Dest *) (r0 + 0xfc);
    }
    func_0203caa4(r0, 0xb, 0);
    r5->a = r2->words[0];
    r5->b = r2->words[1];
    r5->c = r2->words[2];
}

int func_0203c1e0(struct UnkStruct_0203c1e0 *A, int *B)
{
    int val = *B;
    if (val < A->unk_178 + 0x5000) {
        return 1;
    }
    if (val > A->unk_17C - 0x5000) {
        return 2;
    }
    return 0;
}
