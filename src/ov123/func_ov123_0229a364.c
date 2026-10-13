/* func_ov123_0229a364 @ 0x0229a364, 0xd4 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229a364 {
    u8 pad_00[0xa2];
    u8 unk_A2;
    u8 pad_A3;
    u8 unk_A4;
    u8 pad_A5[3];
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[3];
    u8 unk_AD;
    u8 unk_AE;
} UnkStruct_0229a364;
extern int func_ov123_02299650(UnkStruct_0229a364 *self, int a);
extern void func_ov123_02299e28(UnkStruct_0229a364 *self);
extern void func_ov123_0229ab80(UnkStruct_0229a364 *self, u8 a, u8 b, u8 c, u8 d, u8 e, int f);
extern void func_ov123_0229ab18(UnkStruct_0229a364 *self, int a, int b, int c, int d, u8 e);
extern void func_ov123_0229a9b0(UnkStruct_0229a364 *self, int a, int b, int c, int d, u8 e, int f);
extern void func_ov123_02299640(UnkStruct_0229a364 *self, int a);
extern void RtcSendPxiCommand(int a);
inline u8 inline_fn(UnkStruct_0229a364 *arg0)
{
    return arg0->unk_AD;
}

void func_ov123_0229a364(UnkStruct_0229a364 *self)
{
    u8 a8;
    u8 a9;
    u8 ad;
    u8 ae;
    int x0;
    int x1;
    int y0;
    int y1;
    if (func_ov123_02299650(self, 0x100) == 0) {
        return;
    }
    if ((self->unk_A4 < 6) || (self->unk_A4 > 8)) {
        return;
    }
    func_ov123_02299e28(self);
    a8 = self->unk_A8;
    ad = inline_fn(self);
    if (ad >= a8) {
        x0 = a8;
        x1 = ad;
    } else {
        x1 = a8;
        x0 = ad;
    }
    a9 = self->unk_A9;
    ae = self->unk_AE;
    if (ae >= self->unk_A9) {
        y1 = a9;
        y0 = ae;
    } else {
        y0 = a9;
        y1 = ae;
    }
    switch (self->unk_A4) {
        case 8:
            func_ov123_0229ab80(self, ad, ae, a8, a9, self->unk_A2, 0);
            break;

        case 6:
            func_ov123_0229ab18(self, x0, y1, x1, y0, self->unk_A2);
            break;

        case 7:
            func_ov123_0229a9b0(self, x0, y1, x1, y0, self->unk_A2, 0);
            break;
    }

    func_ov123_02299640(self, 0x40);
    RtcSendPxiCommand(0x867);
}
