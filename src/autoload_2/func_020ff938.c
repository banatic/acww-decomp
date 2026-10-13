/* func_020ff938 @ 0x020ff938, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;

extern u32 data_021fd278;
extern void VEC_Normalize(VecFx32 *src, VecFx32 *dst);

static __inline u32 SPLRandom_Next(void)
{
    data_021fd278 = data_021fd278 * 0x5eedf715 + 0x1b0cb173;
    return data_021fd278;
}

void func_020ff938(VecFx32 *vec)
{
    vec->x = (s32) SPLRandom_Next() >> 8;
    vec->y = (s32) SPLRandom_Next() >> 8;
    vec->z = 0;
    VEC_Normalize(vec, vec);
}
