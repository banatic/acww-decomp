/* func_020fec0c @ 0x020fec0c, 0x160 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

#define FX_MUL(a, b) ((fx32) (((s64) (a) * (b) + 0x800) >> 12))

typedef struct {
    fx32 x, y, z;
} VecFx32;
typedef struct {
    fx16 x, y, z;
} VecFx16;

typedef struct SPLEmitter {
    u8 pad_00[0x6c];
    VecFx16 crossAxis1;
    VecFx16 crossAxis2;
} SPLEmitter;

extern void VEC_Fx16CrossProduct(const VecFx16 *a, const VecFx16 *b, VecFx16 *axb);
extern void VEC_Fx16Normalize(const VecFx16 *src, VecFx16 *dst);

void func_020fec0c(VecFx32 *ptclPos, const VecFx32 *pos, SPLEmitter *emtr)
{
    VecFx16 vec;

    VEC_Fx16CrossProduct(&emtr->crossAxis1, &emtr->crossAxis2, &vec);
    VEC_Fx16Normalize(&vec, &vec);

    ptclPos->x = FX_MUL(pos->x, emtr->crossAxis1.x) + FX_MUL(pos->y, emtr->crossAxis2.x) + FX_MUL(pos->z, vec.x);
    ptclPos->y = FX_MUL(pos->x, emtr->crossAxis1.y) + FX_MUL(pos->y, emtr->crossAxis2.y) + FX_MUL(pos->z, vec.y);
    ptclPos->z = FX_MUL(pos->x, emtr->crossAxis1.z) + FX_MUL(pos->y, emtr->crossAxis2.z) + FX_MUL(pos->z, vec.z);
}
