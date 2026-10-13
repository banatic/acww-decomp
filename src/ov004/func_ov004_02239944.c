/* func_ov004_02239944 @ 0x02239944, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02239944 {
    u8 pad_00[0x1c0];
    u16 unk_1C0;
    u8 pad_1C2[0x1fe - 0x1c2];
    u8 unk_1FE;
    u8 pad_1FF[1];
    s16 unk_200;
};

extern s16 FX_SinCosTable_[];
extern int func_ov004_02239460(int a, int b);
extern int FX_MulFunc(int a, int b);

void func_ov004_02239944(struct UnkStruct_02239944 *self, int flag, int a, int b)
{
    int k;
    unsigned int neg;

    neg = 0xffffffff;
    self->unk_200 = func_ov004_02239460((u16) a, (u16) b) * 0xb6;
    if (flag != 0) {
        k = (((int) self->unk_1C0) >> 4) * 2;
        if (FX_MulFunc(FX_SinCosTable_[k], FX_SinCosTable_[k + 1]) >= 0) {
            self->unk_200 = self->unk_200 * neg;
            self->unk_1FE = 0xa;
        } else {
            self->unk_1FE = 3;
        }
    } else {
        k = (((int) self->unk_1C0) >> 4) * 2;
        if (FX_MulFunc(FX_SinCosTable_[k], FX_SinCosTable_[k + 1]) >= 0) {
            self->unk_1FE = 3;
        } else {
            self->unk_200 = self->unk_200 * neg;
            self->unk_1FE = 0xa;
        }
    }
}
