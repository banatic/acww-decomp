/* func_ov134_02299ecc @ 0x02299ecc, 0xa8 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02002808(int, int, int, int, int);

struct UnkStruct_02299ecc {
    u8 pad_00[0x80];
    s32 unk_80;
    u8 pad_84[0x2a];
    u8 unk_AE;
    u8 unk_AF;
    u8 pad_B0[5];
    u8 unk_B5;
    u8 unk_B6;
};

void func_ov134_02299ecc(struct UnkStruct_02299ecc *self)
{
    if (self->unk_AF) {
        self->unk_B5 = (self->unk_AE - 8 + self->unk_B5) >> 1;
        self->unk_B6 = (self->unk_AE + 8 + self->unk_B6) >> 1;
    } else {
        self->unk_B5 = self->unk_AE - 8;
        self->unk_B6 = self->unk_AE + 8;
    }
    func_02002808(2, 0, self->unk_B5, 0xff, self->unk_B6);
    if (self->unk_80 < self->unk_B5) {
        self->unk_80 = self->unk_B5;
    }
    if (self->unk_80 > self->unk_B6 - 8) {
        self->unk_80 = self->unk_B6 - 8;
    }
}
