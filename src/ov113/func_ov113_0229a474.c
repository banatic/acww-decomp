/* func_ov113_0229a474 @ 0x0229a474, 0x30 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229a474 {
    u8 pad_00[0x94];
    u32 unk_94;
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 unk_9C;
    u8 unk_9D;
};

extern void func_ov113_02299a80(struct UnkStruct_0229a474 *self);

void func_ov113_0229a474(struct UnkStruct_0229a474 *self)
{
    self->unk_94 = 0;
    self->unk_98 = 0;
    self->unk_9B = 3;
    func_ov113_02299a80(self);
    self->unk_9A = self->unk_9D - 1;
}
