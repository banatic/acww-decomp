/* func_ov004_0223635c @ 0x0223635c, 0xbc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223635c {
    u8 pad_00[0x158];
    int unk_158;
    u8 pad_15C[0x164 - 0x15c];
    u8 unk_164;
    u8 pad_165[0x1a8 - 0x165];
    int unk_1A8;
    u8 pad_1AC[0x1c0 - 0x1ac];
    s16 unk_1C0;
    u8 pad_1C2[0x1c4 - 0x1c2];
    s16 unk_1C4;
    u8 pad_1C6[0x1ee - 0x1c6];
    u8 unk_1EE;
    u8 pad_1EF[0x1fd - 0x1ef];
    u8 unk_1FD;
    u8 pad_1FE[0x24c - 0x1fe];
    s16 unk_24C;
    u8 pad_24E[0x253 - 0x24e];
    u8 unk_253;
    u8 unk_254;
};

extern int func_0200322c(void *a, void *b);
extern int func_ov004_02239460(int a, int b);
extern void func_ov004_022397ec(struct UnkStruct_0223635c *self);

void func_ov004_0223635c(struct UnkStruct_0223635c *self, void *p)
{
    if (self->unk_253 != 0) {
        return;
    }
    self->unk_1C4 = 0;
    self->unk_1EE = 1;
    self->unk_158 = 0;
    if ((u8) (self->unk_164 + 0xfc) <= 1) {
        if (self->unk_254 >= 0x7d) {
            self->unk_24C = func_0200322c(p, &self->unk_1A8);
        } else if (self->unk_1C0 >= 0) {
            self->unk_24C = func_ov004_02239460(0x38e4, 0x471c);
        } else {
            self->unk_24C = -func_ov004_02239460(0x38e4, 0x471c);
        }
    } else {
        self->unk_24C = func_0200322c(p, &self->unk_1A8);
    }
    if (self->unk_1FD == 1) {
        func_ov004_022397ec(self);
    }
}
