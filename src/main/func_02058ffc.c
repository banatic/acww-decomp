/* func_02058ffc @ 0x02058ffc, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02058ffc {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x0e];
    u32 unk_60;
    u8 pad_64[0x04]; // extra 4 bytes to align unk_68 at 0x68
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u8 pad_78[0x18];
    u32 unk_90;
    u32 unk_94;
    u32 unk_98;
    u32 unk_9C;
    u32 unk_A0;
    u32 unk_A4;
    u8 pad_A8[0x24];
    void *unk_CC;
    u8 pad_D0[0x06];
    u16 unk_D6;
} UnkStruct_02058ffc;

extern u32 data_021c93e4[3];

extern void func_0205967c(UnkStruct_02058ffc *self, u8 *dst);
extern int func_0204fd3c(int x);
extern int func_02059cf8(void *p, int x);
extern void func_02059598(u32 *dst, UnkStruct_02058ffc *self, int x);
extern void func_020595fc(UnkStruct_02058ffc *self, u32 *dst, u32 *src, int x);
extern void func_02059674(UnkStruct_02058ffc *self, int x);
extern void VEC_Add(void *a, void *b, void *c);

void func_02058ffc(UnkStruct_02058ffc *self)
{
    u8 local0[12];
    u32 buf[3];
    u32 buf2[3];
    unsigned int flag;
    int t, delta1, delta2;

    func_0205967c(self, local0);

    flag = 0;
    self->unk_9C = flag;
    self->unk_A0 = flag;
    self->unk_A4 = flag;

    buf[0] = data_021c93e4[0];
    buf[1] = data_021c93e4[1];
    buf[2] = data_021c93e4[2];

    if ((u32) self->unk_50 >= 0x12e8 && (u32) self->unk_50 <= 0x131f) {
        flag = 1;
    }

    if (flag != 0) {
        t = func_0204fd3c((int) (self->unk_50 - 0x12e8));
        t = func_02059cf8(self->unk_CC, t);
        VEC_Add(buf, (void *) t, buf);
    }

    func_02059598(buf2, self, 0);
    VEC_Add(buf, buf2, buf);

    func_020595fc(self, &self->unk_9C, buf, 0);

    self->unk_6C = self->unk_9C;
    self->unk_70 = self->unk_A0;
    self->unk_74 = self->unk_A4;

    delta1 = (int) (self->unk_74 - self->unk_68) / 2;
    if (delta1 < 0) {
        delta1 = -delta1;
    }
    delta2 = (int) (self->unk_6C - self->unk_60) / 2;
    if (delta2 < 0) {
        delta2 = -delta2;
    }

    self->unk_90 = delta2;
    self->unk_94 = 0;
    self->unk_98 = delta1;
    self->unk_D6 = 0;

    func_02059674(self, 1);
}
