/* fish_shadow_swim_4: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222bec4 @ 0x0222bec4, 0x28 bytes, Thumb
 * func_ov003_0222be98 @ 0x0222be98, 0x2c bytes, Thumb
 * func_ov003_0222be78 @ 0x0222be78, 0x1e bytes, Thumb
 */

#include "types.h"

extern short FX_SinCosTable_[];
int FX_MulFunc(int a, int b);

void func_ov003_0222bec4(int *out, int a, int ang)
{
    *out = *out + FX_MulFunc(a, FX_SinCosTable_[((u16) ang >> 4) << 1]);
}

void func_ov003_0222be98(int *out, int a, int ang)
{
    *out = *out + FX_MulFunc(a, FX_SinCosTable_[(((u16) ang >> 4) << 1) + 1]);
}

void func_ov003_0222be78(char *self, int a, u16 ang)
{
    func_ov003_0222bec4((int *) self, a, (u16) ang);
    func_ov003_0222be98((int *) (self + 8), a, (u16) ang);
}
