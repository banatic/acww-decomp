/* func_020bfb20 @ 0x020bfb20, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void VEC_Add(int *a, int *b, int *c);

typedef struct {
    u8 pad_00[0x04];
    int unk_04;
    u8 pad_08[0x28];
    u8 unk_30;
    u8 unk_31;
    u8 pad_32[0x02];
    int unk_34;
    int unk_38;
    u8 pad_3C[0x04];
    int unk_40;
    u8 pad_44[0x1c];
    int unk_60;
    u8 pad_64[0x04];
    u32 unk_68;
} UnkStruct_020bfb20;

void func_020bfb20(UnkStruct_020bfb20 *self)
{
    int *v;
    int *p40;
    int flag3, flag2, flag1;
    int y;
    u32 f68;
    u32 kind;
    u32 bit;

    f68 = self->unk_68;
    self->unk_60--;

    if (self->unk_60 < 0) {
        v = &self->unk_34;
        p40 = &self->unk_40;

        if (self->unk_60 == -2) {
            kind = (f68 >> 4) & 0xf;
            if (kind == 1) {
                *p40 = 0x2800;
            } else if (kind == 2) {
                *p40 = 0xffffd800;
            }
        }

        VEC_Add(v, p40, v);

        flag3 = 1;
        flag2 = flag3;
        flag1 = flag3;
        y = v[1];
        if (y >= -0xa000 && y <= 0xca000) {
            flag1 = 0;
        }
        if (flag1 == 0 && v[0] >= -0xa000) {
            flag2 = 0;
        }
        if (flag2 == 0 && v[0] <= 0x10a000) {
            flag3 = 0;
        }
        if (flag3 != 0 || self->unk_30 != 0) {
            self->unk_04 = 3;
        }
    }

    if (self->unk_31 != 0) {
        bit = (f68 >> 31) & 1;
        if (bit == 0 && self->unk_38 < 0x000c0000) {
            self->unk_31 = 0;
        }
    }
}
