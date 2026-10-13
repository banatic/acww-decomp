/* func_ov004_02239524 @ 0x02239524, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02239524 {
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
    u8 pad_1EF[0x228 - 0x1ef];
    int unk_228;
    u8 pad_22C[0x24e - 0x22c];
    u8 unk_24E;
};

extern void func_020e8a94(void *p, int a, int b, int c);

void func_ov004_02239524(struct UnkStruct_02239524 *self, int n)
{
    int d;

    if ((u8) (self->unk_1EE + 0xff) <= 1) {
        return;
    }
    if (self->unk_24E != 0) {
        if (self->unk_1C4 == 0) {
            return;
        }
        func_020e8a94(&self->unk_1C4, 0, 3, 0x186);
    } else {
        func_020e8a94(&self->unk_1C4, (s16) (-n * self->unk_1CA), 4, 0x186);
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
