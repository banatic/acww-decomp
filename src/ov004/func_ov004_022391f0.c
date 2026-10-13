/* func_ov004_022391f0 @ 0x022391f0, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022391f0 {
    u8 pad_00[0x50];
    int unk_50;
    u8 pad_54[0x15c - 0x54];
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
};

struct UnkStruct_022391f0_2 {
    u8 unk_00[0x11];
};
extern struct UnkStruct_022391f0_2 data_ov004_02247924[];
extern struct UnkStruct_022391f0 *data_ov004_022593b4;

void func_ov004_022391f0(struct UnkStruct_022391f0 *self)
{
    self->unk_50 = (int) self;
    self->unk_1E8 = self->unk_15C;
    self->unk_1E9 = self->unk_15C;
    self->unk_1C8 = 0;
    self->unk_210 = 0x5e;
    self->unk_214 = 1;
    self->unk_218 = 1;
    self->unk_230 = 0x96;
    self->unk_204 = data_ov004_02247924[self->unk_15C].unk_00[8];
    self->unk_205 = data_ov004_02247924[self->unk_15C].unk_00[9];
    self->unk_206 = data_ov004_02247924[self->unk_15C].unk_00[10];
    self->unk_207 = data_ov004_02247924[self->unk_15C].unk_00[11];
    data_ov004_022593b4 = self;
}
