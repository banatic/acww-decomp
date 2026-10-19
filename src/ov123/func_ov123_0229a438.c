/* func_ov123_0229a438 @ 0x0229a438, 0x84 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229a438 {
    u8 pad_00[0xa4];
    u8 unk_A4;
    u8 pad_A5[3];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0xaf - 0xa9 - 1];
    u8 unk_AF;
    u8 unk_B0;
} UnkStruct_0229a438;

extern void func_ov123_02299f08(UnkStruct_0229a438 *self);
extern unsigned char *func_ov002_02208098(UnkStruct_0229a438 *self, unsigned char value);
extern void func_ov123_02299e28(UnkStruct_0229a438 *self);
extern void func_ov123_0229a538(UnkStruct_0229a438 *self, u8 a, u8 b);
extern void func_0200467c(int a);
extern void func_ov123_02299640(UnkStruct_0229a438 *self, int a);

void func_ov123_0229a438(UnkStruct_0229a438 *self)
{
    self->unk_A8 = self->unk_AF;
    self->unk_A9 = self->unk_B0;

    if (self->unk_A4 >= 6 && self->unk_A4 <= 8) {
        func_ov123_02299f08(self);
        func_ov002_02208098(self, 6);
    } else {
        func_ov123_02299e28(self);
        func_ov123_0229a538(self, self->unk_A8, self->unk_A9);
        if (self->unk_A4 <= 2) {
            func_0200467c(0x85f);
            func_0200467c(0x861);
            func_ov002_02208098(self, 5);
        }
        func_ov123_02299640(self, 0x40);
    }
}
