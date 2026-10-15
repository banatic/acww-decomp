/* func_ov068_0226f178 @ 0x0226f178, 0xb8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0226f178 {
    u8 pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    u8 pad_68[0x204];
    int unk_26C;
    u8 pad_270[0x9c];
    int unk_30C;
    u8 pad_310[0x86];
    s16 unk_396;
};

extern int func_02034270(int *dst, int *src, int a, int b);
extern void func_0203423c(int *buf);
extern int FX_MulFunc(int a, int b);
extern void func_020ee470(struct UnkStruct_0226f178 *self);
extern const short FX_SinCosTable_[];

void func_ov068_0226f178(struct UnkStruct_0226f178 *self)
{
    int buf[0x10];
    int *p;

    func_02034270(buf, &self->unk_5C, 0, 0);
    p = &buf[9];
    self->unk_5C += p[0] >> 5;
    self->unk_64 += p[2] >> 5;
    self->unk_26C = FX_MulFunc(self->unk_26C, 0xf85);
    self->unk_30C = FX_MulFunc(0x100, FX_SinCosTable_[((unsigned short) self->unk_396 >> 4) * 2]);
    self->unk_396 += 0x400;
    if (self->unk_26C < 0x100) {
        self->unk_26C = 0;
        func_020ee470(self);
    }
    {
        int t = buf[15] - self->unk_26C - 0x200;
        self->unk_60 -= 0x400;
        if (self->unk_60 < t) {
            self->unk_60 = t;
        }
    }
    func_0203423c(buf);
}
