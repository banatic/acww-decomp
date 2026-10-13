/* func_ov114_0229ce18 @ 0x0229ce18, 0xc8 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x94c];
    u16 unk_94C;
    u16 unk_94E;
    char pad_950[0x96c - 0x950];
    u16 unk_96C;
} UnkStruct_0229ce18;

extern void func_ov114_0229c190(UnkStruct_0229ce18 *self, int a);

void func_ov114_0229ce18(UnkStruct_0229ce18 *self, int a1, int a2)
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

    c1 = self->unk_94E;
    r1 = (u8) (c1 & 0x1f);
    g1 = (u8) ((c1 & 0x3e0) >> 5);
    b1 = (u8) ((c1 & 0x7c00) >> 10);
    d = a2 - a1;
    c2 = self->unk_94C;
    r = (u8) (((u8) (c2 & 0x1f) * a1 + r1 * d) / a2);
    g = (u8) (((u8) ((c2 & 0x3e0) >> 5) * a1 + g1 * d) / a2);
    b = (u8) (((u8) ((c2 & 0x7c00) >> 10) * a1 + b1 * d) / a2);
    self->unk_96C = r | (g << 5) | (b << 10);
    func_ov114_0229c190(self, 1);
}
