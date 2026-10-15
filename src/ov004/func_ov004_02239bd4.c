/* func_ov004_02239bd4 @ 0x02239bd4, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern short FX_SinCosTable_[];
int FX_MulFunc(int a, int b);

int func_ov004_02239bd4(int *out, int a, int ang)
{
    int valueResult;

    valueResult = *out + FX_MulFunc(a, FX_SinCosTable_[(((u16) ang >> 4) << 1) + 1]);
    *out = valueResult;
    return valueResult;
}
