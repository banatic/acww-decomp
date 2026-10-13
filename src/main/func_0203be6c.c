/* func_0203be6c @ 0x0203be6c, 0x1c4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct UnkStruct_0203be6c {
    u8 pad_00[0xc8];
    fx32 unk_C8; // 0x0c8
    u8 pad_CC[0xfc - 0xcc];
    s16 unk_FC;      // 0x0fc
    s16 unk_FE;      // 0x0fe
    fx32 unk_100;    // 0x100
    VecFx32 unk_104; // 0x104
    VecFx32 unk_110; // 0x110
    u8 pad_11C[0x148 - 0x11c];
    s16 unk_148;     // 0x148
    s16 unk_14A;     // 0x14a
    fx32 unk_14C;    // 0x14c
    VecFx32 unk_150; // 0x150
    VecFx32 unk_15C; // 0x15c
    u8 pad_168[0x1e4 - 0x168];
    fx32 unk_1E4; // 0x1e4
    fx32 unk_1E8; // 0x1e8
} UnkStruct_0203be6c;

extern int func_0203ad88(UnkStruct_0203be6c *self);
extern int func_0203c528(UnkStruct_0203be6c *self);
extern int func_0203c4e4(UnkStruct_0203be6c *self);
extern int func_0203c4d0(UnkStruct_0203be6c *self);
extern int func_0203c4bc(UnkStruct_0203be6c *self);
extern fx32 func_020643dc(fx32 a, int b, int c, int d, int e);

extern void func_020eaca0(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b);
extern void func_020eabc8(VecFx32 *v, fx32 t);
extern void func_01ffd070(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

void func_0203be6c(UnkStruct_0203be6c *self)
{
    VecFx32 delta0;
    VecFx32 delta1;
    VecFx32 res0;
    VecFx32 res1;
    fx32 t;

    if (func_0203ad88(self)) {
        int a = func_0203c528(self);
        int b = func_0203c4e4(self);
        int c = func_0203c4d0(self);
        int d = func_0203c4bc(self);

        t = func_020643dc(self->unk_C8, a, b, c, d);

        func_020eaca0(&delta0, &self->unk_110, &self->unk_15C);
        func_020eabc8(&delta0, t);
        func_01ffd070(&res0, &self->unk_15C, &delta0);
        self->unk_15C.x = res0.x;
        self->unk_15C.y = res0.y;
        self->unk_15C.z = res0.z;

        func_020eaca0(&delta1, &self->unk_104, &self->unk_150);
        func_020eabc8(&delta1, t);
        func_01ffd070(&res1, &self->unk_150, &delta1);
        self->unk_150.x = res1.x;
        self->unk_150.y = res1.y;
        self->unk_150.z = res1.z;

        self->unk_14A = (s16) (self->unk_14A + FX_MulFunc(self->unk_FE - self->unk_14A, t));
        self->unk_148 = (s16) (self->unk_148 + FX_MulFunc(self->unk_FC - self->unk_148, t));
        self->unk_14C += FX_MulFunc(self->unk_100 - self->unk_14C, t);
        self->unk_1E8 += FX_MulFunc(self->unk_1E4 - self->unk_1E8, t);

        self->unk_C8 = self->unk_C8 + 0x1000;
    } else {
        self->unk_15C.x = self->unk_110.x;
        self->unk_15C.y = self->unk_110.y;
        self->unk_15C.z = self->unk_110.z;
        self->unk_150.x = self->unk_104.x;
        self->unk_150.y = self->unk_104.y;
        self->unk_150.z = self->unk_104.z;
        self->unk_14A = self->unk_FE;
        self->unk_148 = self->unk_FC;
        self->unk_14C = self->unk_100;
        self->unk_1E8 = self->unk_1E4;
    }
}
