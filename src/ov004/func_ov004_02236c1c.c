/* func_ov004_02236c1c @ 0x02236c1c, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02236c1c {
    u8 pad_00[0x110];
    int unk_110;
    u8 pad_114[0x158 - 0x114];
    int unk_158;
    u8 pad_15C[0x1a8 - 0x15c];
    int unk_1A8;
    u8 pad_1AC[0x1b0 - 0x1ac];
    int unk_1B0;
    u8 pad_1B4[0x1c0 - 0x1b4];
    u16 unk_1C0;
    u8 pad_1C2[0x208 - 0x1c2];
    s16 unk_208;
    u8 pad_20A[0x20c - 0x20a];
    int unk_20C;
    u8 pad_210[0x21c - 0x210];
    u8 unk_21C;
};

extern s16 FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern int _s32_div_f(int a, int b);

void func_ov004_02236c1c(struct UnkStruct_02236c1c *self)
{
    int v;
    int w;

    v = self->unk_20C - (self->unk_158 << 3);
    if (v < 0) {
        v = 0;
        self->unk_158 = 0;
        self->unk_110 = 0;
        self->unk_21C = 6;
    }
    self->unk_1A8 = self->unk_1A8 + FX_MulFunc(v, FX_SinCosTable_[(self->unk_1C0 >> 4) * 2]);
    self->unk_1B0 = self->unk_1B0 + FX_MulFunc(v, FX_SinCosTable_[(self->unk_1C0 >> 4) * 2 + 1]);
    self->unk_208 = self->unk_208 + 0x2000;
    w = _s32_div_f(v * 7, 0xa);
    self->unk_1A8 = self->unk_1A8 + FX_MulFunc(w, FX_SinCosTable_[((u16) self->unk_208 >> 4) * 2]);
    self->unk_1B0 = self->unk_1B0 + FX_MulFunc(w, FX_SinCosTable_[((u16) self->unk_208 >> 4) * 2]);
}
