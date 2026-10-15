/* func_ov146_02299fbc @ 0x02299fbc, 0x13c bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Rec {
    u8 d[0x20];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
} Rec;
typedef struct UnkStruct_02299fbc {
    u8 pad_00[0xb6];
    u8 unk_B6;
    u8 pad_B7[0x10a - 0xb7];
    u8 cnt[0x20];
    Rec rec[0x20];
} UnkStruct_02299fbc;
extern void *func_ov146_0229a174(void);
extern int func_ov146_02299ee8(UnkStruct_02299fbc *s, u8 *p);
extern void MI_CpuCopy8(void *dst, void *src, int n); // func_021175fc
extern int func_ov146_0229a42c(UnkStruct_02299fbc *s);
extern void func_020708e4(int a, short *s, int n);
extern void func_02070a98(int a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(int a, int b, int c);
void func_ov146_02299fbc(UnkStruct_02299fbc *self)
{
    u8 *buf;
    int i;
    int count;
    u8 *src;
    int disp;
    int off;
    u16 digits[3];

    buf = (u8 *) func_ov146_0229a174();
    count = 0;
    for (i = 0; i < 0x20; i++) {
        off = i * 0x23;
        src = buf + 0x180 + off;
        if (func_ov146_02299ee8(self, src)) {
            if (*((u8 *) self + off + 0x14a) == 6) {
                if (self->cnt[i] < 0x14) {
                    self->cnt[i]++;
                }
            } else {
                self->cnt[i] = 0;
                MI_CpuCopy8(buf + 0x180 + off, &self->rec[i], 0x23);
            }
            count++;
        } else if (*((u8 *) self + off + 0x14a) == 6) {
            if (self->cnt[i] != 0) {
                self->cnt[i]--;
            } else {
                *((u8 *) self + off + 0x14a) = 0;
            }
        }
    }
    if (count != self->unk_B6) {
        self->unk_B6 = count;
        disp = func_ov146_0229a42c(self);
        if (self->unk_B6 < 10) {
            digits[0] = self->unk_B6 + 0xff10;
            digits[1] = 0;
            digits[2] = 0;
        } else {
            digits[0] = self->unk_B6 / 10 + 0xff10;
            digits[1] = self->unk_B6 % 10 + 0xff10;
            digits[2] = 0;
        }
        func_020708e4(disp, (short *) digits, 3);
        func_02070a98(disp, 8, 0x1f4, 2, 9, 0, 1);
        func_02070a04(disp, 0, 0);
    }
}
