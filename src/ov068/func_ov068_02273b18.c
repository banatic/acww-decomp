/* func_ov068_02273b18 @ 0x02273b18, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02273b18 {
    u8 pad_00[0x40];
    u32 *unk_40;
    u8 pad_44[0x70];
    u32 unk_B4;
};

extern __arm int func_020e8840(u32);
extern void func_0201acbc(u32, u32, u32, u32, u32, u32);
extern void func_ov068_022740f8(struct UnkStruct_02273b18 *, u32);

void func_ov068_02273b18(struct UnkStruct_02273b18 *self)
{
    if (func_020e8840(self->unk_B4 + 0x748) != 0) {
        return;
    }
    func_0201acbc(self->unk_B4 + 0x3b0, 0, 0, 0x1000, 0x276, 0x276);
    self->unk_40[2] = 1;
    func_ov068_022740f8(self, 0);
}
