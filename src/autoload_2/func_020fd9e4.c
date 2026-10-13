/* func_020fd9e4 @ 0x020fd9e4, 0xac bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#define FX32_ONE 0x1000
#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> 12))

typedef struct {
    fx32 unk_00, unk_04, unk_08;
    fx32 unk_0C, unk_10, unk_14;
    fx32 unk_18, unk_1C, unk_20;
    fx32 unk_24, unk_28, unk_2C;
} MtxFx43;

void func_020fd9e4(fx32 sinVal, fx32 cosVal, MtxFx43 *mtx)
{
    fx32 a, b, d, p, m;

    a = FX_MUL(FX32_ONE - cosVal, 0x555);
    b = FX_MUL(sinVal, 0x93d);
    p = a + b;
    m = a - b;
    d = a + cosVal;

    mtx->unk_00 = d;
    mtx->unk_0C = p;
    mtx->unk_18 = m;
    mtx->unk_24 = 0;
    mtx->unk_04 = m;
    mtx->unk_10 = d;
    mtx->unk_1C = p;
    mtx->unk_28 = 0;
    mtx->unk_08 = p;
    mtx->unk_14 = m;
    mtx->unk_20 = d;
    mtx->unk_2C = 0;
}
