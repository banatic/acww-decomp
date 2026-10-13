/* func_0200cf50 @ 0x0200cf50, 0x160 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200cf50 {
    int x, y, z;
} UnkStruct_0200cf50;

typedef struct UnkStruct_0200cf50_3 {
    u8 pad_00[0x5c];
    UnkStruct_0200cf50 v;
    u8 pad_68[0x8e - 0x68];
    short unk_8E;
    u8 pad_90[0x98 - 0x90];
    int unk_98;
} UnkStruct_0200cf50_3;

typedef struct UnkStruct_0200cf50_2 {
    u8 unk_00;
    u8 unk_01;
    short unk_02;
    short unk_04;
    short unk_06;
} UnkStruct_0200cf50_2;

extern short FX_SinCosTable_[];

extern int func_0200e9a8(UnkStruct_0200cf50_3 *s, UnkStruct_0200cf50_2 *a, int *b, int *c, short *d);
extern int func_020b65c4(void);
extern int FX_MulFunc(int a, int b);
extern int func_0200e93c(UnkStruct_0200cf50_3 *s, int a, int b, int c, int d, short *e);
extern void func_020113e0(short *a, int b);
extern void func_020110a0(UnkStruct_0200cf50_3 *s, short *p);
extern int FX_Sqrt(int a);
extern int FX_Div(int a, int b);
extern int func_020113b0(int s, int a);
extern int func_02011398(int s, int a);
extern void func_0201107c(UnkStruct_0200cf50_3 *s, int *p);

int func_0200cf50(UnkStruct_0200cf50_3 *self)
{
    UnkStruct_0200cf50_2 s;
    int v10;
    int v14;
    int cur;
    int dx;
    int dz;
    int acc;
    int mag;
    int lim;
    int k;
    int tv;
    int tt;
    int j;

    if (func_0200e9a8(self, &s, &v10, &v14, &s.unk_02) == 0) {
        return 1;
    }
    if (s.unk_00 != func_020b65c4()) {
        return 1;
    }
    dx = v10 - self->v.x;
    dz = v14 - self->v.z;
    acc = FX_MulFunc(dx, dx);
    acc = acc + FX_MulFunc(dz, dz);
    if (func_0200e93c(self, dx, dz, acc, s.unk_02, &s.unk_04) == 0) {
        return 1;
    }
    s.unk_06 = self->unk_8E;
    func_020113e0(&s.unk_06, s.unk_04);
    func_020110a0(self, &s.unk_06);
    cur = self->unk_98;
    mag = FX_Sqrt(acc);
    lim = mag;
    if (mag > 0x6e2) {
        lim = 0x6e2;
    }
    k = (int) (unsigned short) (short) (s.unk_06 - s.unk_04) >> 4;
    j = (k << 1) + 1;
    tv = FX_SinCosTable_[j];
    if (tv < 0) {
        tv = 0;
    }
    acc = FX_MulFunc(lim, tv);
    if (mag >= 0x2666) {
        if (mag >= 0xe000) {
            self->v.x = v10;
            self->v.z = v14;
            self->unk_8E = s.unk_02;
            return 1;
        }
    } else {
        tt = FX_MulFunc(mag - 0x108, FX_Div(0x5da, 0x255e));
        tt = tt + 0x108;
        if (tt < 0x108) {
            tt = 0x108;
        }
        if (acc > tt) {
            acc = tt;
        }
    }
    if (cur < acc) {
        cur = func_020113b0(cur, acc);
    } else if (cur > acc) {
        cur = func_02011398(cur, acc);
    }
    func_0201107c(self, &cur);
    return 0;
}
