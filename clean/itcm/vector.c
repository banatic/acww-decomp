/* Vector functions in the ITCM (vector.h). */
#include "vector.h"

#include <stdint.h>

#include "clean.h"

/* Sums and differences kept to 32 bits, as the ARM computes them. */
static fx32 add32(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

static fx32 sub32(fx32 a, fx32 b)
{
    return (fx32) ((u32) a - (u32) b);
}

/* The square of `value` as an unsigned 64-bit number (sums of these wrap at 64 bits). */
static u64 square64(fx32 value)
{
    return (u64) ((s64) value * value);
}

/* A 64-bit number shifted right by `n` with its sign kept (the ARM's ASR on the high word). */
static s64 asr64(u64 value, int n)
{
    u64 shifted = value >> n;
    if (value >> 63) {
        shifted |= ~(~(u64) 0 >> n);
    }
    return (s64) shifted;
}

/* func_01ffd028: the square of the distance between `a` and `b`, in 20.12 kept to 64 bits.
 * QUIRK: each difference is kept to 32 bits and the sum of the squares wraps at 64 bits. */
s64 Vec_DistanceSquared(const Vec3 *a, const Vec3 *b)
{
    u64 sum = square64(sub32(a->y, b->y)) + square64(sub32(a->x, b->x)) + square64(sub32(a->z, b->z));
    return asr64(sum, 12);
}
CLEAN_AS(func_01ffd028, Vec_DistanceSquared)

/* func_01ffd070: `sum` = `a` + `b`; `sum` may be `a` or `b`. */
void Vec_Add(Vec3 *sum, const Vec3 *a, const Vec3 *b)
{
    Vec3 result = {add32(a->x, b->x), add32(a->y, b->y), add32(a->z, b->z)};
    *sum = result;
}
CLEAN_AS(func_01ffd070, Vec_Add)
