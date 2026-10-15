/* func_ov121_0229ba60 @ 0x0229ba60, 0xf4 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x64];
    u32 unk_64;
} PtrStruct;

typedef struct {
    u8 pad_00[0x9c];
    u32 unk_9C;
    u8 pad_A0[0xa2 - 0xa0];
    u16 unk_A2;
    u8 pad_A4[0xac - 0xa4];
    u8 unk_AC;
    u8 pad_AD[0xb0 - 0xad];
    u8 unk_B0;
    u8 unk_B1;
    u8 pad_B2[0x528 - 0xb2];
    u8 unk_528;
    u8 pad_529[0x118c - 0x529];
    u8 arr[8];
} UnkStruct_0229ba60;

extern u8 data_020e54a8;
extern PtrStruct *data_020ccf94;
extern void func_ov121_0229adc0(UnkStruct_0229ba60 *self, int val);
extern int func_ov121_0229ba2c(void *receiver);
extern int func_02073d90(PtrStruct *p);
extern void func_ov002_02209984(void *addr, int a, int b, int c);

void func_ov121_0229ba60(UnkStruct_0229ba60 *self)
{
    u8 i;
    unsigned int flag;
    PtrStruct *p;

    for (i = 0; i < 8; i++) {
        self->arr[i] = i;
    }
    self->unk_A2 = 0;
    self->unk_9C = 0;

    flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        self->unk_AC = 0;
        func_ov121_0229adc0(self, 9);
        func_ov121_0229adc0(self, 10);
        func_ov121_0229adc0(self, 11);

        p = data_020ccf94;
        if (func_02073d90(p) != 0 && p->unk_64 != 0) {
            func_ov121_0229adc0(self, 15);
        }
    } else {
        if (func_ov121_0229ba2c(self) != 0) {
            self->unk_AC = 1;
            func_ov121_0229adc0(self, 15);
        } else {
            self->unk_AC = 2;
            func_ov121_0229adc0(self, 9);
            func_ov121_0229adc0(self, 10);
            func_ov121_0229adc0(self, 11);
            func_ov121_0229adc0(self, 14);
            func_ov121_0229adc0(self, 15);
        }
    }

    func_ov002_02209984(&self->unk_528, 3, 1, 0);
    self->unk_B0 = 0x18;
    self->unk_B1 = 0;
}
