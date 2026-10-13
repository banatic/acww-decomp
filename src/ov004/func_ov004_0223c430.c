/* func_ov004_0223c430 @ 0x0223c430, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern short FX_SinCosTable_[];
extern int FX_MulFunc(int a, int b);
extern int func_ov004_0223c5a4(int *v);
extern int func_ov004_0220fe24(void *self, int a1, int a2, int a3, int a4);
extern int func_02030890(int *v);

int func_ov004_0223c430(int *self, int ang, int scale)
{
    int yval;
    int xplus;
    int zplus;
    int i2;
    int v[3];

    i2 = ((u16) ang >> 4) << 1;
    zplus = self[2] + FX_MulFunc(scale, FX_SinCosTable_[i2 + 1]);
    yval = self[1];
    xplus = self[0] + FX_MulFunc(scale, FX_SinCosTable_[i2]);
    v[0] = xplus;
    v[1] = yval;
    v[2] = zplus;

    if (func_ov004_0223c5a4(v) != 0) {
        return 0;
    }

    if (func_ov004_0220fe24(v, 0x800, 0x2000, 0x800, 0) == 0) {
        return 1;
    }

    if (func_02030890(v) == -1) {
        goto ret2;
    }
    return 0;
ret2:
    return 2;
}
