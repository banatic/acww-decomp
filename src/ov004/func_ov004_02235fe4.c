/* func_ov004_02235fe4 @ 0x02235fe4, 0x94 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02235fe4 {
    u8 pad_00[0x158];
    int unk_158;
    u8 pad_15C[0x164 - 0x15c];
    u8 unk_164;
    u8 pad_165[0x1a8 - 0x165];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
    u8 pad_1C2[0x1ee - 0x1c2];
    u8 unk_1EE;
    u8 pad_1EF[0x20c - 0x1ef];
    int unk_20C;
    int unk_210;
    u8 pad_214[0x24c - 0x214];
    s16 unk_24C;
    u8 pad_24E[0x253 - 0x24e];
    u8 unk_253;
};

extern void func_020e8a94(void *p, int a, int b, int c);
extern void func_ov004_02239bb4(void *p, int a, int b);

void func_ov004_02235fe4(struct UnkStruct_02235fe4 *self)
{
    if (self->unk_158 <= 0x28) {
        if ((u8) (self->unk_164 + 0xfc) <= 1) {
            func_020e8a94(&self->unk_1C0, self->unk_24C, 3, 0xaaa);
        } else {
            func_020e8a94(&self->unk_1C0, self->unk_24C, 2, 0x4000);
        }
        self->unk_20C = self->unk_210;
        func_ov004_02239bb4(&self->unk_1A8, self->unk_20C, self->unk_1C0);
    } else {
        self->unk_253 = 0;
        self->unk_1EE = 2;
    }
}
