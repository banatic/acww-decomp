/* func_ov068_0226f648 @ 0x0226f648, 0xe8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0226f648 {
    u8 pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    u8 pad_68[0xa8 - 0x68];
    int unk_A8;
    u8 pad_AC[0x26c - 0xac];
    int unk_26C;
    u8 unk_270;
    u8 pad_271[0x278 - 0x271];
    int unk_278;
    u8 pad_27C[0x2f0 - 0x27c];
    int unk_2F0;
    int unk_2F4;
    u8 pad_2F8[0x368 - 0x2f8];
    unsigned char unk_368;
};

struct UnkStruct_0226f648_2 {
    u8 lpad[0x3c];
    int value;
};

extern void func_020e8b60(void *dst, int a, int b, int c);
extern int FX_Div(int a, int b);
extern void func_ov068_0226fc48(struct UnkStruct_0226f648 *self);
extern void func_ov003_0221a35c(struct UnkStruct_0226f648 *self, int a);
extern void func_02034270(void *a, void *b, int c, int d);
extern void func_0203423c(void *a);

void func_ov068_0226f648(struct UnkStruct_0226f648 *self)
{
    int v;
    int ret;
    struct UnkStruct_0226f648_2 local;
    int r;

    v = self->unk_26C;
    v += v >> 1;
    func_020e8b60(&self->unk_270, v, 0xcc, v);

    self->unk_5C += self->unk_2F0;
    self->unk_64 += self->unk_2F4;

    if (self->unk_368 < 0xc) {
        self->unk_A8++;
        self->unk_60 -= 0x100;
        self->unk_368++;
    } else {
        ret = FX_Div(0, 0x02710000);
        self->unk_A8 += ret + 0xe9;
        self->unk_60 -= self->unk_A8;
    }

    if (self->unk_278 & 2) {
        func_02034270(&local, &self->unk_5C, 0, 0);
        r = (local.value - self->unk_26C) - 0x200;
        if (self->unk_60 < r) {
            func_ov068_0226fc48(self);
            self->unk_60 = r;
            func_ov003_0221a35c(self, 2);
        }
        func_0203423c(&local);
    }
}
