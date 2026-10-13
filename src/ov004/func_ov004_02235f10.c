/* func_ov004_02235f10 @ 0x02235f10, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02235f10 {
    u8 pad_00[0x158];
    int unk_158;
    int unk_15C;
    u8 pad_160[0x1ac - 0x160];
    int unk_1AC;
    u8 pad_1B0[0x1c2 - 0x1b0];
    s16 unk_1C2;
    u8 pad_1C4[0x1ca - 0x1c4];
    signed char unk_1CA;
    u8 pad_1CB[0x1cc - 0x1cb];
    int unk_1CC;
    u8 pad_1D0[0x1e8 - 0x1d0];
    u8 unk_1E8;
    u8 pad_1E9[0x1ee - 0x1e9];
    u8 unk_1EE;
    u8 pad_1EF[0x1f1 - 0x1ef];
    u8 unk_1F1;
    u8 pad_1F2[0x202 - 0x1f2];
    u8 unk_202;
    u8 unk_203;
    u8 unk_204;
    u8 unk_205;
    u8 pad_206[0x228 - 0x206];
    int unk_228;
    u8 pad_22C[0x23c - 0x22c];
    int unk_23C;
};

extern int func_ov004_02239460(int a, int b);
extern int func_ov004_02239474(int a, int b);

void func_ov004_02235f10(struct UnkStruct_02235f10 *self)
{
    int v;

    self->unk_158 = 1;
    self->unk_202 = func_ov004_02239460(self->unk_205, self->unk_204);
    self->unk_203 = 0;
    self->unk_23C = 0;
    if (self->unk_1F1 != 0) {
        self->unk_1C2 = self->unk_1C2 + func_ov004_02239474(0x1e, 0xf);
    }
    if (self->unk_1E8 == self->unk_15C) {
        if (self->unk_1AC >= self->unk_1CC) {
            self->unk_1CA = -1;
        } else if (self->unk_1AC <= self->unk_228) {
            self->unk_1CA = 1;
        } else {
            if (func_ov004_02239460(0, 2) > 0) {
                v = 1;
            } else {
                v = -1;
            }
            self->unk_1CA = v;
        }
    }
    self->unk_1EE = 3;
}
