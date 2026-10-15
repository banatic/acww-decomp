/* func_ov093_02299630 @ 0x02299630, 0x13a bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02299630 {
    u8 pad_00[5];
    u8 state;
    u8 unk_06;
    u8 pad_07[0xc - 7];
    int unk_0C;
    u8 pad_10[0x14 - 0x10];
    int unk_14;
} UnkStruct_02299630;

extern void func_ov093_02299048(UnkStruct_02299630 *self);
extern void func_ov093_02299514(void *self);
extern void func_ov093_022990b8(UnkStruct_02299630 *self, int a);
extern void func_ov093_02298fdc(void *self);
extern void func_ov093_02299490(UnkStruct_02299630 *self);
extern void func_ov093_02298f84(UnkStruct_02299630 *self, int a);
extern void func_02002708(int a);
extern void func_0200284c(int a, int b, int c);
extern void func_020019dc(int a, int b, int c);
extern void func_020019cc(void);
extern void func_02001ba4(int a);
extern void func_02001d1c(int a);
extern void func_02002808(int a, int b, int c, int d, int e);

void func_ov093_02299630(UnkStruct_02299630 *self)
{
    int t;
    unsigned int v;

    func_ov093_02299048(self);
    switch (self->state) {
        case 1:
            self->state = 2;
            func_02002708(4);
            func_02002708(0);
            func_0200284c(4, 8, -0xc0);
            func_0200284c(0, 8, -0xc0);
            func_ov093_02299514(self);
            break;
        case 2:
            func_ov093_022990b8(self, 1);
            break;
        case 3:
            func_ov093_022990b8(self, 0);
            func_02002708(0);
            func_020019dc(2, 0x21, 0);
            func_ov093_02298fdc(self);
            self->state = 5;
            break;
        case 4:
            func_ov093_022990b8(self, 0);
            func_02002708(0);
            func_ov093_02298fdc(self);
            self->state = 6;
            break;
        case 5:
            func_ov093_022990b8(self, 0);
            v = self->unk_06;
            if (v < 0x48) {
                if (v >= 0x10) {
                    if (v < 0x38) {
                        v = 0x10;
                    } else {
                        v = 0x48 - v;
                    }
                }
                self->unk_06++;
                func_020019dc(2, 0x21, v);
            } else {
                func_ov093_02299490(self);
                func_020019cc();
                func_ov093_02298f84(self, 8);
            }
            break;
        case 6:
            func_ov093_022990b8(self, 0);
            self->unk_0C = self->unk_0C + self->unk_14;
            t = self->unk_0C >> 12;
            if (t >= 0) {
                t = 0;
                self->unk_06 = 0x10;
                func_02001ba4(1);
                func_02001d1c(0x1f);
                self->state = 5;
            } else {
                func_02002808(0, 0, -t, 0xfe, 0xbf);
            }
            func_0200284c(0, 0, t);
            break;
    }
}
