/* func_ov146_022996f4 @ 0x022996f4, 0xd4 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x158a];
    u16 src[15];
    u16 unk_15A8;
    u16 out[16];
} UnkStruct_022996f4;

extern void func_ov146_02299660(UnkStruct_022996f4 *self, int a);

void func_ov146_022996f4(UnkStruct_022996f4 *self, int a, int t, int idx)
{
    u16 c1;
    int d;
    u8 r1;
    u8 g1;
    u8 b1;
    u16 c2;
    u8 g;
    u8 b;
    u8 r;

    c1 = self->unk_15A8;
    r1 = (u8) (c1 & 0x1f);
    g1 = (u8) ((c1 & 0x3e0) >> 5);
    b1 = (u8) ((c1 & 0x7c00) >> 10);
    d = 0x14 - t;
    c2 = self->src[idx];
    r = (u8) (((u8) (c2 & 0x1f) * t + r1 * d) / 0x14);
    g = (u8) (((u8) ((c2 & 0x3e0) >> 5) * t + g1 * d) / 0x14);
    b = (u8) (((u8) ((c2 & 0x7c00) >> 10) * t + b1 * d) / 0x14);
    self->out[(u8) (0xe - a)] = r | (g << 5) | (b << 10);
    func_ov146_02299660(self, 8);
}
