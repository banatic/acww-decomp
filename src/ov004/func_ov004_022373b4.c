/* func_ov004_022373b4 @ 0x022373b4, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022373b4 {
    u8 pad_00[0x50];
    int unk_50;
    u8 pad_54[0x15c - 0x54];
    int unk_15C;
    u8 pad_160[0x1e8 - 0x160];
    u8 unk_1E8;
    u8 unk_1E9;
    u8 pad_1EA[0x258 - 0x1ea];
    int unk_258;
    int unk_25C;
    int unk_260;
    int unk_264;
    int unk_268;
    int unk_26C;
};

extern void func_ov004_022354e0(struct UnkStruct_022373b4 *self);

void func_ov004_022373b4(struct UnkStruct_022373b4 *self)
{
    self->unk_50 = (int) self;
    self->unk_1E8 = self->unk_15C;
    self->unk_1E9 = self->unk_15C;
    if (self->unk_15C == 0x26) {
        self->unk_258 = 0x9e00;
        self->unk_25C = 0x1000;
        self->unk_260 = 0x14700;
        self->unk_264 = 0xa100;
        self->unk_268 = 0xb00;
        self->unk_26C = 0x14a00;
    } else if (self->unk_15C == 0xc) {
        self->unk_258 = 0x15900;
        self->unk_25C = 0x1000;
        self->unk_260 = 0x13900;
    }
    func_ov004_022354e0(self);
}
