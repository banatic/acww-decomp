/* func_ov004_02221270 @ 0x02221270, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void func_02019d0c(char *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0203e020(char *self);
extern void func_ov004_02221550(char *self, int n);
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern u16 data_020c80f8;

int func_ov004_02221270(char *self)
{
    // DECLS
    volatile Vec3 v;
    int b;
    int t;
    // ENDDECLS

    *(u16 *) (self + 0x8c) = 0;
    *(short *) (self + 0x8e) = -0x8000;
    *(u16 *) (self + 0x90) = 0;
    *(u16 *) (self + 0x92) = 0;
    *(short *) (self + 0x94) = -0x8000;
    *(u16 *) (self + 0x96) = 0;
    b = *(u8 *) (self + 0xadc);
    if (b == 1) {
        func_02019d0c(self + 0x564, 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        func_0203e020(self);
        func_ov004_02221550(self, 8);
        return 1;
    }
    if (b == 0) {
        v.x = 0;
        v.y = 0;
        v.z = 0;
        t = FX_MulFunc(0x4000, FX_SinCosTable_[(*(u16 *) (self + 0x8e) >> 4) * 2]);
        v.x = t + *(int *) (self + 0x5c);
        t = FX_MulFunc(0x4000, FX_SinCosTable_[(*(u16 *) (self + 0x8e) >> 4) * 2 + 1]);
        t = t + *(int *) (self + 0x64);
        v.z = t;
        func_02019d0c(self + 0x564, 1, 2, v.x, t, 0, 0, 0, 0, data_020c80f8, 0);
        *(u8 *) (self + 0xadc) = 0x1e;
        return 1;
    }
    *(u8 *) (self + 0xadc) = (u8) (b - 1);
    return 1;
}
