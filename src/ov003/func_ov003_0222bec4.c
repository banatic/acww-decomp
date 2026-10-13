/* func_ov003_0222bec4 @ 0x0222bec4, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern short FX_SinCosTable_[];
int FX_MulFunc(int a, int b);

void func_ov003_0222bec4(int *out, int a, int ang)
{
    *out = *out + FX_MulFunc(a, FX_SinCosTable_[((u16) ang >> 4) << 1]);
}
