/* func_ov002_0220b1a4 @ 0x0220b1a4, 0xdc bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220b1a4 {
    u8 pad_00[0x70];
    char *unk_70;
    u8 pad_74[1];
    u8 unk_75;
    u8 unk_76;
};

extern int func_ov002_0220b280(struct UnkStruct_0220b1a4 *self);
extern int func_ov002_0220b2bc(struct UnkStruct_0220b1a4 *self, int mask);
extern void func_02088df8(int a0, char *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

void func_ov002_0220b1a4(struct UnkStruct_0220b1a4 *self, int x, int y, int a)
{
    int base;
    int c;
    int px;
    int py;

    base = func_ov002_0220b280(self);
    c = -1;
    if (func_ov002_0220b2bc(self, 4)) {
        c = 2;
    }
    py = y + 0x60 + base;
    px = x + 0x80 + base;
    func_02088df8(1, self->unk_70, px, py, c, a, 0x1000, 0x1000, 0, -1, 0, 0);
    if (func_ov002_0220b2bc(self, 2)) {
        func_02088df8(1, self->unk_70, px, py, -1, a, 0x1000, 0x1000, 0, 2, 0, 0);
    }
    if (!func_ov002_0220b2bc(self, 1) && self->unk_75 + 1 != 3) {
        x += 0x83;
        y += 0x63;
        func_02088df8(1, self->unk_70 + self->unk_76 * 8, x, y, 1, a, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}
