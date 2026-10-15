/* func_ov004_022355f4 @ 0x022355f4, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022355f4 {
    u8 pad_00[0x40];
    u8 unk_40;
    u8 pad_41[0x1c0 - 0x41];
    s16 unk_1C0;
    u8 pad_1C2[0x1f0 - 0x1c2];
    u8 unk_1F0;
    u8 pad_1F1[0x22f - 0x1f1];
    u8 unk_22F;
};

extern int func_020e89dc(void *p, int a, int b);

void func_ov004_022355f4(struct UnkStruct_022355f4 *self)
{
    int v;

    if (self->unk_40 != 0) {
        return;
    }
    if (self->unk_22F != 0) {
        return;
    }
    if (self->unk_1F0 == 0) {
        return;
    }
    v = self->unk_1C0;
    if (v >= 0) {
        if (v < 0) {
            v = -v;
        }
        if (v >= 0x4000) {
            func_020e89dc(&self->unk_1C0, 0x471c, 0x222);
        } else {
            func_020e89dc(&self->unk_1C0, 0x38e4, 0x222);
        }
    } else {
        if (v < 0) {
            v = -v;
        }
        if (v <= -0x4000) {
            func_020e89dc(&self->unk_1C0, -0x471c, 0x222);
        } else {
            func_020e89dc(&self->unk_1C0, -0x38e4, 0x222);
        }
    }
}
