/* aquarium_swim_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02239944 @ 0x02239944, 0xa8 bytes, Thumb
 * func_ov004_022398a8 @ 0x022398a8, 0x9c bytes, Thumb
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

struct UnkStruct_022398a8 {
    u8 pad_00[0x100];
    int unk_100;
    int unk_104;
    int unk_108;
    u8 pad_10C[0x1c6 - 0x10c];
    u8 unk_1C6;
    u8 pad_1C7[0x22e - 0x1c7];
    u8 unk_22E;
};

extern s16 FX_SinCosTable_[];
extern int func_ov004_02239460(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_02056f28(void *p, int a);
extern void func_ov004_02239820(struct UnkStruct_022398a8 *self, int k);

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

void func_ov004_022398a8(struct UnkStruct_022398a8 *self, int n)
{
    if (self->unk_1C6 != 0) {
        if (self->unk_22E != 0) {
            if (func_02056f28(&self->unk_100, n) != 0) {
                self->unk_108 = (u16) (n - 1) << 12;
            }
        } else {
            if (func_02056f28(&self->unk_100, (u16) ((((unsigned int) self->unk_104 << 4) >> 16) - 1)) != 0) {
                if (n == 0xa) {
                    func_ov004_02239820(self, 2);
                } else {
                    func_ov004_02239820(self, 1);
                }
                self->unk_22E = 1;
            }
        }
    } else {
        if (func_02056f28(&self->unk_100, n) != 0) {
            self->unk_108 = (u16) (n - 1) << 12;
        }
    }
}
