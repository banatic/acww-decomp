/* func_020082ac @ 0x020082ac, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Field298 {
    u32 v[12];
};

struct UnkStruct_020082ac {
    u8 pad_00[0x5c];
    u8 unk_5C;
    u8 pad_5D[0xc4 - 0x5c - 1];
    u8 unk_C4;
    u8 pad_C5[0xd0 - 0xc4 - 1];
    u16 unk_D0;
    u8 pad_D2[0x298 - 0xd0 - 2];
    struct Field298 unk_298;
};

extern u16 func_0203f8d0(void *p0, void *p1);
extern void func_020031d4(void *self, void *buf);

void func_020082ac(struct UnkStruct_020082ac *self)
{
    struct Field298 local;
    self->unk_D0 = func_0203f8d0(&self->unk_C4, &self->unk_5C);
    func_020031d4(self, &local);
    self->unk_298 = local;
}
