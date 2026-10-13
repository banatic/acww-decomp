/* func_ov004_0223592c @ 0x0223592c, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223592c {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1c0 - 0x160];
    s16 unk_1C0;
    s16 unk_1C2;
    u8 pad_1C4[0x1ee - 0x1c4];
    u8 unk_1EE;
    u8 pad_1EF[0x20c - 0x1ef];
    int unk_20C;
    u8 pad_210[0x22f - 0x210];
    u8 unk_22F;
};

extern u8 data_ov004_02247924[];
extern int func_020e89dc(void *p, int a, int b);

void func_ov004_0223592c(struct UnkStruct_0223592c *self)
{
    int ok;

    if ((self->unk_20C <= 0x99a && self->unk_1EE == 5) || self->unk_1EE == 1 || self->unk_22F == 0) {
        return;
    }
    if (data_ov004_02247924[self->unk_15C * 0x11] >= 4) {
        ok = func_020e89dc(&self->unk_1C0, self->unk_1C2, 0x88) != 0;
    } else {
        ok = func_020e89dc(&self->unk_1C0, self->unk_1C2, 0x16c) != 0;
    }
    if (ok) {
        self->unk_22F = 0;
    }
}
