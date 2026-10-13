/* func_ov068_0226f730 @ 0x0226f730, 0x124 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0226f730 UnkStruct_0226f730;
struct UnkStruct_0226f730 {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[0x5c - 0xc];
    int unk_5C;
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    u8 pad_74[0xa8 - 0x74];
    int unk_A8;
    u8 pad_AC[0x270 - 0xac];
    u32 unk_270;
    u8 pad_274[0x2f0 - 0x274];
    int unk_2F0;
    int unk_2F4;
    u8 pad_2F8[0x368 - 0x2f8];
    u8 unk_368;
    u8 pad_369[0x378 - 0x369];
    u16 unk_378;
};

typedef struct {
    u32 unk_00;
    u32 w1;
    u32 w2;
    u32 w3;
} FourInts;

extern FourInts *func_020b03f8(void);
extern int FX_MulFunc(int, int);
extern int func_020ea9c8(int *);
extern void *func_020961a8(int);
extern short FX_SinCosTable_[];
extern int FX_Div(int, int);

int func_ov068_0226f730(UnkStruct_0226f730 *self)
{
    u32 bit;
    FourInts *arr;
    int args[3];
    int result;
    u16 *p;
    int angle;
    int v;
    int *p2f4;
    int z;
    int x;

    self->unk_378 |= 0x10;
    self->unk_378 &= ~0x20;
    self->unk_270 = 0;

    bit = self->unk_08 & 1;
    arr = func_020b03f8();
    bit &= 1;
    arr[bit].unk_00 = 0;
    arr[bit].w1 = 0;
    arr[bit].w2 = 0;
    arr[bit].w3 = 0x800;

    self->unk_60 = 0;
    self->unk_A8 = 0;

    self->unk_2F0 = FX_MulFunc(self->unk_2F0, 0x119a);
    p2f4 = &self->unk_2F4;
    *p2f4 = FX_MulFunc(*p2f4, 0x119a);

    self->unk_368 = 0;

    z = *p2f4;
    x = self->unk_2F0;
    args[0] = x;
    args[1] = 0;
    args[2] = z;
    result = func_020ea9c8(args);

    if (result < 0x2b8) {
        if (result == 0) {
            p = (u16 *) func_020961a8(4);
            if (p != 0) {
                p = (u16 *) ((char *) p + 0x8e);
                angle = ((int) *p >> 4) * 2;
                self->unk_2F0 = FX_MulFunc(0x2b8, FX_SinCosTable_[angle]);
                self->unk_2F4 = FX_MulFunc(0x2b8, FX_SinCosTable_[angle + 1]);
                self->unk_5C = self->unk_68 + self->unk_2F0;
                self->unk_64 = self->unk_70 + self->unk_2F4;
            }
        } else {
            v = FX_Div(0x2b8, result);
            self->unk_2F0 = FX_MulFunc(self->unk_2F0, v);
            self->unk_2F4 = FX_MulFunc(self->unk_2F4, v);
        }
    }

    return 1;
}
