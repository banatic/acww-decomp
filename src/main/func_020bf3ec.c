/* func_020bf3ec @ 0x020bf3ec, 0x128 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern Vec data_021c67d0;
extern fx32 data_020ca0ec;
extern int data_020ca0e8;
extern int data_021c67a4;
extern s16 FX_SinCosTable_[];

extern fx32 FX_Div(fx32 a, fx32 b);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_InvA(fx32 a);
extern fx32 func_0203adb0(void);

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
