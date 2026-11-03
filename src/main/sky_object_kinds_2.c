/* sky_object_kinds_2: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bf5b8 @ 0x020bf5b8, 0x38 bytes, Thumb
 * func_020bf590 @ 0x020bf590, 0x28 bytes, Thumb
 * func_020bf568 @ 0x020bf568, 0x28 bytes, Thumb
 * func_020bf514 @ 0x020bf514, 0x54 bytes, Thumb
 * func_020bf3ec @ 0x020bf3ec, 0x128 bytes, Thumb
 * func_020bf3c8 @ 0x020bf3c8, 0x24 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020bf5b8_2 {
    char pad_00[0xC];
    int idx;
    int sub;
};

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_020bf590;

typedef struct {
    char data[12];
} UnkStruct_020bf590_2;

struct UnkStruct_020bf514 {
    char pad_00[0x28];
    int unk_28;
    short sfield;
    unsigned char flag;
};

typedef struct Vec {
    fx32 x, y, z;
} Vec;

typedef struct UnkStruct_020bf3ec {
    unsigned char pad_00[0x2c];
    u16 unk_2C;
    unsigned char pad_2E[0x34 - 0x2e];
    fx32 unk_34;
    fx32 unk_38;
    fx32 unk_3C;
    unsigned char pad_40[0x4c - 0x40];
    fx32 unk_4C;
    fx32 unk_50;
} UnkStruct_020bf3ec;

struct Param0Struct {
    char pad_00[0x28];
    int unk_28;
};

struct UnkStruct_020bf3c8 {
    int a;
    int b;
    int c;
};

extern struct UnkStruct_020bf5b8 {
    int a;
    int b;
    int c;
} data_020e7880[];
extern void func_0208a1f0(void *dst, struct UnkStruct_020bf5b8 *e);
extern void func_0208a1ec(void *dst, int c);
extern void *func_0208a144(void *dst);
extern UnkStruct_020bf590_2 data_021fa678[];
extern void func_020bee3c(void *);
extern void func_020bf924(void *);
extern int data_021f6cdc;
extern Vec data_021c67d0;
extern fx32 data_020ca0ec;
extern int data_020ca0e8;
extern int data_021c67a4;
extern s16 FX_SinCosTable_[];
extern fx32 FX_Div(fx32 a, fx32 b);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_InvA(fx32 a);
extern fx32 func_0203adb0(void);

void func_020bf3c8(struct Param0Struct *param0, int param1);

/* FAKEMATCH: the empty if keeps self->idx loaded before the table address; the plain expression loads the address first */
void func_020bf5b8(struct UnkStruct_020bf5b8_2 *self)
{
    int idx;
    struct UnkStruct_020bf5b8 *e;

    idx = self->idx;
    if ((idx && idx) && idx) {
    }
    e = &data_020e7880[idx];
    func_0208a1f0(&self->sub, e);
    func_0208a1ec(&self->sub, e->c);
    func_0208a144(&self->sub);
}

void func_020bf590(UnkStruct_020bf590 *param)
{
    int field = param->unk_24;
    if (field != 6) {
        func_020bee3c(&data_021fa678[field]);
    }
    func_020bf924(param);
}

void func_020bf568(unsigned char *p0, unsigned char p1, int p2)
{
    int v;

    p0[0x2e] = p1;
    if (p0[0x2e] != 0) {
        v = 0;
    } else {
        v = data_021f6cdc;
    }
    *(int *) (p0 + 0x28) = v;
    func_020bf3c8((struct Param0Struct *) p0, p2);
}

int func_020bf514(struct UnkStruct_020bf514 *s, int a1, int a2, int a3)
{
    int flag = 0;

    if (s->flag) {
        s->unk_28 += a1;
        if (s->unk_28 > data_021f6cdc) {
            flag = 1;
        }
    } else {
        s->unk_28 -= a1;
        if (s->unk_28 < 0) {
            flag = 1;
        }
    }

    if (!flag) {
        s->sfield = s->sfield + a3;
        func_020bf3c8((struct Param0Struct *) s, a2);
    }

    return flag;
}

void func_020bf3ec(UnkStruct_020bf3ec *self, Vec *a, fx32 p)
{
    volatile Vec v;
    fx32 dx, dz, sx, sz, k, t, x, val, q, h, u;

    v.x = data_021c67d0.x;
    v.y = data_021c67d0.y;
    v.z = data_021c67d0.z;
    dz = data_021c67d0.z - a->z;
    dx = a->x - data_021c67d0.x;
    sx = FX_Div(dx, data_020ca0ec);
    sz = FX_Div(dz, data_020ca0e8 << 2);
    k = FX_MulFunc(-0x1000, sz - 0x1000);
    h = FX_MulFunc(sz, k + 0x1000);
    u = FX_MulFunc(-0x666, h) + 0xe66;
    u = FX_MulFunc(sx, u) + 0x800;
    val = FX_MulFunc(u, 0x1000) << 8;
    q = FX_MulFunc(0x50000, h) + 0x50000;
    t = 0x1000 - h;
    if (data_021c67a4 != 0) {
        x = FX_MulFunc(func_0203adb0(), t);
    } else {
        x = 0;
    }
    x = FX_MulFunc(x, 0x10000);
    self->unk_34 = val;
    self->unk_38 = q - x;
    self->unk_3C = 0;
    val = FX_MulFunc(-0xc00, h) + 0x1000;
    if (val < 0x400) {
        val = 0x400;
    } else if (val > 0x1000) {
        val = 0x1000;
    }
    q = FX_InvA(val);
    self->unk_4C = q;
    self->unk_50 = q;
    self->unk_38 = self->unk_38 + FX_MulFunc(FX_MulFunc(FX_SinCosTable_[(self->unk_2C >> 4) * 2], p), val);
}

void func_020bf3c8(struct Param0Struct *param0, int param1)
{
    struct UnkStruct_020bf3c8 local;
    local.a = param0->unk_28;
    local.b = 0;
    local.c = data_020ca0e8;
    func_020bf3ec((UnkStruct_020bf3ec *) param0, (Vec *) (&local), param1);
}
