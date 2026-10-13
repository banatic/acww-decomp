/* func_ov004_02237094 @ 0x02237094, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02237094 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1e8 - 0x160];
    u8 unk_1E8;
    u8 pad_1E9[0x252 - 0x1e9];
    u8 unk_252;
    u8 pad_253[0x256 - 0x253];
    u8 unk_256;
};

extern void func_ov004_02236fa0(struct UnkStruct_02237094 *self, int k);
extern void func_ov004_02236f34(struct UnkStruct_02237094 *self);

void func_ov004_02237094(struct UnkStruct_02237094 *self)
{
    u8 st;
    u8 v;

    st = self->unk_256;
    switch (st) {
        case 1:
            func_ov004_02236fa0(self, 0);
            v = self->unk_1E8;
            if (self->unk_252 != v && v != self->unk_15C) {
                self->unk_252 = v;
                self->unk_256 = 2;
            }
            break;
        case 2:
            func_ov004_02236fa0(self, 1);
            break;
        case 3:
            func_ov004_02236f34(self);
            break;
    }
}
