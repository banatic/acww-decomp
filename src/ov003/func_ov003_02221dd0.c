/* func_ov003_02221dd0 @ 0x02221dd0, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x0a];
    u16 unk_0A;
    u8 pad_0C[0x18 - 0x0c];
    u8 unk_18[1];
    u8 pad_19[0x1c - 0x19];
    int unk_1C;
    u8 pad_20[0x30 - 0x20];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    u8 pad_40[0x44 - 0x40];
    int unk_44;
    u8 pad_48[0x4c - 0x48];
    s16 unk_4C;
    u8 pad_4E[0x60 - 0x4e];
    u8 unk_60[1];
} UnkStruct_02221dd0;

extern void VEC_Add(void *a, void *b, void *c);
extern void func_020044c0(void *a, int b, int c, int d);
extern void func_ov003_02222860(void *a);

void func_ov003_02221dd0(UnkStruct_02221dd0 *self)
{
    self->unk_3C += 0x19a;
    if (self->unk_3C >= 0x1000) {
        self->unk_3C = 0x1000;
    }
    self->unk_44 = self->unk_3C;
    self->unk_34 -= 0x400;
    VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
    if (self->unk_1C < 0) {
        int flag = 0;
        self->unk_1C = flag;
        self->unk_30 = flag;
        self->unk_34 = flag;
        self->unk_38 = flag;
        if (self->unk_4C == 0) {
            volatile unsigned short val;
            unsigned short a, b;
            val = 0xfff1;
            val = self->unk_0A;
            a = val;
            b = val;
            if (b >= 0x1492 && a <= 0x14fd) {
                flag = 1;
            }
            if (flag != 0) {
                func_020044c0(&self->unk_60, 0x70, 0x7f, 0);
            }
        }
        self->unk_4C = 1;
        func_ov003_02222860(self);
    }
}
