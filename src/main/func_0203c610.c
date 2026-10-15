/* func_0203c610 @ 0x0203c610, 0x15c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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
