/* func_ov139_02299888 @ 0x02299888, 0xdc bytes, Thumb, module ov139
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x960];
    u16 src[15];
    u16 unk_97E;
    u16 out[16];
} UnkStruct_02299888;

extern unsigned short *func_ov139_022995b0(UnkStruct_02299888 *self, int a);

void func_ov139_02299888(UnkStruct_02299888 *self, int a, int a1, int a2, int idx)
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

    c1 = self->unk_97E;
    r1 = (u8) (c1 & 0x1f);
    g1 = (u8) ((c1 & 0x3e0) >> 5);
    b1 = (u8) ((c1 & 0x7c00) >> 10);
    d = a2 - a1;
    c2 = self->src[idx];
    r = (u8) (((u8) (c2 & 0x1f) * a1 + r1 * d) / a2);
    g = (u8) (((u8) ((c2 & 0x3e0) >> 5) * a1 + g1 * d) / a2);
    b = (u8) (((u8) ((c2 & 0x7c00) >> 10) * a1 + b1 * d) / a2);
    self->out[(u8) (0xe - a)] = r | (g << 5) | (b << 10);
    func_ov139_022995b0(self, 1);
}
