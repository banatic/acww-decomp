/* func_02056bb4 @ 0x02056bb4, 0x6c bytes, ARM, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x, y, z;
} VecFx32;

void func_02056bb4(const VecFx32 *a, const VecFx32 *b, VecFx32 *out, fx32 t)
{
    fx32 s = 0x1000 - t;
    out->x = (fx32) ((((long long) t * a->x) + ((long long) s * b->x)) >> 12);
    out->y = (fx32) ((((long long) t * a->y) + ((long long) s * b->y)) >> 12);
    out->z = (fx32) ((((long long) t * a->z) + ((long long) s * b->z)) >> 12);
}
