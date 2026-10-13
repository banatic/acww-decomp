/* func_ov003_02235990 @ 0x02235990, 0xe4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern short FX_SinCosTable_[];

int func_ov003_02235990(char *self, int r, int d)
{
    int *src;
    int *dst;
    short h;
    int i;
    int j;

    src = (int *) (self + 0x204);
    if (*(signed char *) (self + 0x24d) == 0x35) {
        h = *(short *) (self + 0x23c);
    } else {
        h = *(short *) (self + 0x23a);
    }
    dst = (int *) (self + 0x1ec);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    i = ((u16) (short) (h + d) >> 4) * 2;
    *(int *) (self + 0x1ec) += FX_SinCosTable_[i] * r / 0x64;
    dst[2] += FX_SinCosTable_[i + 1] * r / 0x64;
    dst[3] = src[0];
    dst[4] = src[1];
    dst[5] = src[2];
    j = ((u16) (short) (h - d) >> 4) * 2;
    dst[3] += FX_SinCosTable_[j] * r / 0x64;
    dst[5] += FX_SinCosTable_[j + 1] * r / 0x64;
    return 1;
}
