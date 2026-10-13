/* func_ov003_0222b9b4 @ 0x0222b9b4, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern void func_ov003_022277fc(char *self, int k);

void func_ov003_0222b9b4(char *self)
{

    int x;
    int h;
    int a;
    int z;
    short *pa;
    int t142;
    int t138;
    int u142;
    int u138;

    a = *(int *) (self + 0x13c) << 3;
    pa = (short *) (self + 0x142);
    *pa += 0x2000;
    t142 = FX_SinCosTable_[(*(u16 *) pa >> 4) << 1];
    t138 = FX_SinCosTable_[(*(u16 *) (self + 0x138) >> 4) << 1];
    h = a >> 2;
    x = FX_MulFunc(a, t138) + FX_MulFunc(h, t142);
    u142 = FX_SinCosTable_[(*(u16 *) (self + 0x142) >> 4) << 1];
    u138 = FX_SinCosTable_[((*(u16 *) (self + 0x138) >> 4) << 1) + 1];
    z = FX_MulFunc(a, u138) + FX_MulFunc(h, u142);
    *(int *) (self + 0x120) += x;
    *(int *) (self + 0x128) += z;
    if (*(int *) (self + 0x13c) >= 0xa) {
        func_ov003_022277fc(self, 0x20);
    } else {
        func_ov003_022277fc(self, 0x10);
    }
    if (a > 0x19a) {
        *(u8 *) (self + 0x200) = 2;
    }
}
