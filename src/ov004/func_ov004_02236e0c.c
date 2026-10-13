/* func_ov004_02236e0c @ 0x02236e0c, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02236e0c {
    u8 pad_00[0x110];
    int unk_110;
    u8 pad_114[0x158 - 0x114];
    int unk_158;
    u8 pad_15C[0x1ac - 0x15c];
    int unk_1AC;
    u8 pad_1B0[0x1c0 - 0x1b0];
    s16 unk_1C0;
    u8 pad_1C2[0x20c - 0x1c2];
    int unk_20C;
    u8 unk_210;
    u8 pad_211[1];
    s16 unk_212;
    u8 pad_214[0x218 - 0x214];
    int unk_218;
    u8 unk_21C;
};

extern int func_ov004_02239474(int a, int b);
extern int func_ov004_02239460(int a, int b);
extern int func_ov004_022394ac(int a, int b);
extern int _s32_div_f(int a, int b);

void func_ov004_02236e0c(struct UnkStruct_02236e0c *self)
{
    self->unk_1C0 = self->unk_1C0 + func_ov004_02239474(0x5a, 0);
    self->unk_210 = func_ov004_02239460(0x14, 0x78);
    self->unk_212 = func_ov004_02239460(0x3c, 0xf0);
    self->unk_20C = _s32_div_f(func_ov004_022394ac(2, 4), 0x64);
    self->unk_158 = 0;
    self->unk_1AC = 0x700;
    self->unk_218 = 0x1000;
    self->unk_110 = self->unk_218;
    self->unk_21C = 4;
}
