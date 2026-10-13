/* func_ov004_022395d0 @ 0x022395d0, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022395d0 {
    u8 pad_00[0x1ac];
    int unk_1AC;
    u8 pad_1B0[0x1c4 - 0x1b0];
    s16 unk_1C4;
    u8 pad_1C6[0x1ca - 0x1c6];
    signed char unk_1CA;
    u8 pad_1CB[0x1cc - 0x1cb];
    int unk_1CC;
    u8 pad_1D0[0x1ee - 0x1d0];
    u8 unk_1EE;
    u8 pad_1EF[0x20c - 0x1ef];
    int unk_20C;
    u8 pad_210[0x228 - 0x210];
    int unk_228;
    u8 pad_22C[0x23c - 0x22c];
    int unk_23C;
    u8 pad_240[0x24e - 0x240];
    u8 unk_24E;
};

void func_ov004_022395d0(struct UnkStruct_022395d0 *self, int lim, int m)
{
    int d;

    if ((u8) (self->unk_1EE + 0xff) <= 1) {
        return;
    }
    self->unk_1C4 = (-self->unk_23C * self->unk_1CA) * ((self->unk_20C * m) >> 12);
    if (self->unk_1C4 <= -lim) {
        self->unk_1C4 = -lim;
    } else if (self->unk_1C4 >= lim) {
        self->unk_1C4 = lim;
    }
    if (self->unk_24E != 0) {
        if (self->unk_1C4 == 0) {
            return;
        }
        self->unk_23C = self->unk_23C - 1;
    } else {
        self->unk_23C = self->unk_23C + 1;
        if (self->unk_1EE == 5) {
            self->unk_24E = 1;
        } else {
            d = self->unk_1CA;
            if ((d == 1 && self->unk_1AC == self->unk_1CC) || (d == -1 && self->unk_1AC == self->unk_228)) {
                self->unk_24E = 1;
            }
        }
    }
}
