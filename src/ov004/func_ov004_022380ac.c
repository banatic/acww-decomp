/* func_ov004_022380ac @ 0x022380ac, 0xcc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022380ac {
    u8 unk_00[0x11];
};

struct UnkStruct_022380ac_2 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1c8 - 0x160];
    u8 unk_1C8;
    u8 pad_1C9[0x1e8 - 0x1c9];
    u8 unk_1E8;
    u8 unk_1E9;
    u8 pad_1EA[0x204 - 0x1ea];
    u8 unk_204;
    u8 unk_205;
    u8 unk_206;
    u8 unk_207;
    u8 pad_208[0x210 - 0x208];
    int unk_210;
    int unk_214;
    int unk_218;
    u8 pad_21C[0x230 - 0x21c];
    s16 unk_230;
    u8 pad_232[0x258 - 0x232];
    int unk_258;
    int unk_25C;
    int unk_260;
};

extern struct UnkStruct_022380ac data_ov004_02247924[];

void func_ov004_022380ac(struct UnkStruct_022380ac_2 *self)
{
    self->unk_1E8 = self->unk_15C;
    self->unk_1E9 = self->unk_15C;
    self->unk_1C8 = 0;
    self->unk_210 = 0x51;
    self->unk_214 = 2;
    self->unk_218 = 2;
    self->unk_230 = 0x3c;
    self->unk_258 = 0x7000;
    self->unk_25C = 0;
    self->unk_260 = 0x14a00;
    self->unk_204 = data_ov004_02247924[self->unk_15C].unk_00[8];
    self->unk_205 = data_ov004_02247924[self->unk_15C].unk_00[9];
    self->unk_206 = data_ov004_02247924[self->unk_15C].unk_00[0xa];
    self->unk_207 = data_ov004_02247924[self->unk_15C].unk_00[0xb];
}
