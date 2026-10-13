/* func_ov004_02239790 @ 0x02239790, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02239790 {
    u8 pad_00[0x1ac];
    int unk_1AC;
    u8 pad_1B0[0x1ca - 0x1b0];
    signed char unk_1CA;
    u8 pad_1CB[0x1cc - 0x1cb];
    int unk_1CC;
    u8 pad_1D0[0x228 - 0x1d0];
    int unk_228;
};

extern void func_020e88dc(int *p, int v, int step);

void func_ov004_02239790(struct UnkStruct_02239790 *self, int step, int hi, int lo)
{
    int *p;

    p = &self->unk_1AC;
    *p = *p + step * self->unk_1CA;
    if (*p > hi) {
        func_020e88dc(p, self->unk_1CC, step);
    } else if (*p < lo) {
        func_020e88dc(p, self->unk_228, step);
    }
}
