/* func_ov068_02273ff0 @ 0x02273ff0, 0x108 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02273ff0 {
    u8 pad_00[0x652];
    u16 unk_652;
    u32 unk_654;
    u8 pad1[0x730 - 0x658];
    u32 unk_730;
    u8 unk_734[0x14];
    u16 unk_748;
    u8 pad_74A[0x74b - 0x74a];
    u8 unk_74B;
} UnkStruct_02273ff0;

typedef struct UnkStruct_02273ff0_2 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad1[0xb4 - 0x44];
    UnkStruct_02273ff0 *base;
} UnkStruct_02273ff0_2;

extern void *func_0206fc44(UnkStruct_02273ff0_2 *self);
extern void MI_CpuCopy8(void *dst, const void *src, u32 size);
extern void func_02062fbc(void *p);
extern void func_02062e50(void *p);
extern void func_020a8874(void *dst, const void *src, u32 count);
extern void func_020a8a70(void *a, void *b, u32 c, u32 d);
extern void func_020683b4(void *a, u32 b, void *c, u32 d);
extern int func_0206fc6c(void);
extern u32 func_0206fc8c(void);
extern void func_02015de4(UnkStruct_02273ff0_2 *self, u16 *half, u32 a, u32 b);
extern u16 func_ov068_02273980(UnkStruct_02273ff0 *base);
extern void func_0206844c(void *a, void *b, u32 c);
extern void func_02062e00(void *p);
extern void func_02062f4c(void *p);

extern u32 data_ov068_02277ca4[];

void func_ov068_02273ff0(UnkStruct_02273ff0_2 *self)
{
    u8 byte0;
    u16 half0;
    u8 buf1[0x28];
    u8 buf2[0x24];
    u32 ret;
    u16 val;

    MI_CpuCopy8(func_0206fc44(self), self->base->unk_734, 0x14);
    func_02062fbc(buf1);
    func_02062e50(buf2);
    func_020a8874(buf2, self->base->unk_734, 10);
    func_020a8a70(buf1, buf2, 0, 0);
    func_020683b4(self->unk_40, 0, buf1, 7);

    if (func_0206fc6c() != 0) {
        self->base->unk_74B = 0;
        ret = func_0206fc8c();
        if (ret < 70) {
            val = (u16) (ret + 0x1323);
        } else {
            val = 0x1323;
        }
        self->base->unk_652 = val;
        half0 = self->base->unk_652;
        func_02015de4(self, &half0, 1, 7);
    } else {
        self->base->unk_74B = 1;
        self->base->unk_652 = func_ov068_02273980(self->base);
    }

    byte0 = 8;
    func_0206844c(self->unk_40, &byte0, data_ov068_02277ca4[self->base->unk_730]);
    func_02062e00(buf2);
    func_02062f4c(buf1);
}
