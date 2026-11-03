/* wfc_host_list_rows_2: 4 functions, module ov146
 * mwccarm 1.2/base -O4,s
 * func_ov146_02299fbc @ 0x02299fbc, 0x13c bytes, Thumb
 * func_ov146_02299f08 @ 0x02299f08, 0xb4 bytes, Thumb
 * func_ov146_02299ee8 @ 0x02299ee8, 0x1e bytes, Thumb
 * func_ov146_02299e9c @ 0x02299e9c, 0x4c bytes, Thumb
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

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned char pad_02[30];
    unsigned char unk_20;
} UnkStruct_02299ee8;

extern unsigned int func_ov146_0229a174(void *receiver);
extern void MI_CpuCopy8(void *dst, void *src, int n); // func_021175fc
extern int func_ov146_0229a42c(UnkStruct_02299fbc *s);
extern void func_020708e4(int a, short *s, int n);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_02070a04(int a, int b, int c);

int func_ov146_02299ee8(int unused, UnkStruct_02299ee8 *ptr);

void func_ov146_02299fbc(UnkStruct_02299fbc *self)
{
    u8 *buf;
    int i;
    int count;
    u8 *src;
    int disp;
    int off;
    u16 digits[3];

    buf = (u8 *) func_ov146_0229a174(self);
    count = 0;
    for (i = 0; i < 0x20; i++) {
        off = i * 0x23;
        src = buf + 0x180 + off;
        if (func_ov146_02299ee8((int) self, (UnkStruct_02299ee8 *) src)) {
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
        func_02070a98((void *) disp, 8, 0x1f4, 2, 9, 0, 1);
        func_02070a04(disp, 0, 0);
    }
}

int func_ov146_02299f08(u8 *self)
{
    int changed;
    int i;
    int n;
    u8 *p;

    n = 0;
    changed = 0;
    p = (u8 *) func_ov146_0229a174(self);
    for (i = 0; i < 0x20; i++) {
        if (*(self + i * 0x23 + 0x14a) != 6) {
            continue;
        }
        if (i != *(self + n + 0xea)) {
            changed = 1;
            *(self + n + 0xea) = (u8) i;
        }
        if (func_ov146_02299ee8((int) self, (UnkStruct_02299ee8 *) (p + 0x180 + i * 0x23)) != 0) {
            *(self + i * 0x23 + 0x14c) = *(p + i * 0x23 + 0x1a2);
        }
        *(self + n + 0xca) = *(p + i * 0x23 + 0x1a2);
        n++;
    }
    for (; n < 0x20; n++) {
        if (*(self + n + 0xea) != 0x20) {
            changed = 1;
            *(self + n + 0xea) = 0x20;
            *(self + n + 0xca) = 0;
        }
    }
    return changed;
}

int func_ov146_02299ee8(int unused, UnkStruct_02299ee8 *ptr)
{
    if (ptr->unk_20 == 6 && (ptr->unk_00 != 0 || ptr->unk_01 != 0)) {
        return 1;
    }
    return 0;
}

int func_ov146_02299e9c(int a, int b)
{
    int v;
    int idx;

    if (b >= 0x20) {
        return 0;
    }

    v = func_ov146_0229a174((void *) a);
    idx = 35 * b;
    if (func_ov146_02299ee8(a, (UnkStruct_02299ee8 *) (v + 0x180 + idx))) {
        unsigned char c = *(unsigned char *) (v + idx + 0x1a2);
        if (c < 4) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
