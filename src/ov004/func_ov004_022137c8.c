/* func_ov004_022137c8 @ 0x022137c8, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int FX_MulFunc(int a, int b);
extern s16 FX_SinCosTable_[];

void func_ov004_022137c8(char *self, int flag)
{
    *(s16 *) (self + 0x846) = (s16) (*(s16 *) (self + 0x846) + 1);
    if (*(s16 *) (self + 0x846) == 8) {
        *(u16 *) (self + 0x848) = 0;
        if (flag != 0) {
            *(int *) (self + 0x84c) =
                FX_MulFunc(*(int *) (self + 0x84c), FX_SinCosTable_[(*(u16 *) (self + 0x848) >> 4) * 2]) + 0x2d000;
            if (*(int *) (self + 0x84c) > 0x2d000) {
                *(int *) (self + 0x84c) = 0x2d000;
            }
        } else {
            *(int *) (self + 0x84c) =
                FX_MulFunc(*(int *) (self + 0x84c), FX_SinCosTable_[(*(u16 *) (self + 0x848) >> 4) * 2]) - 0x2d000;
            if (*(int *) (self + 0x84c) < -0x2d000) {
                *(int *) (self + 0x84c) = -0x2d000;
            }
        }
    }
}
