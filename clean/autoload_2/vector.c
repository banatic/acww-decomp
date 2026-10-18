/* Points and vectors (vector.h).
 *
 * Products of two 20.12 numbers are taken in 64 bits and rounded to nearest (+0x800) before
 * they drop back to 20.12; sums and differences wrap at 32 bits as the ARM's do. */
#include "vector.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

static_assert(sizeof(Vec3) == 12, "VecFx32");

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
/* NitroSDK: `dst` = `src` scaled to length 1 (`src` must not be zero). */
extern void VEC_Normalize(const Vec3 *src, Vec3 *dst);
/* NitroSDK: `product` = `a` x `b`. */
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *product);

/* Sine and cosine of each of 4096 angles, interleaved (NitroSDK's table). */
extern const fx16 FX_SinCosTable_[4096 * 2];

/* The hardware square-root unit. */
#define REG_SQRTCNT (*(volatile u16 *) 0x040002b0)
#define REG_SQRT_RESULT (*(volatile u32 *) 0x040002b4)
#define REG_SQRT_PARAM_L (*(volatile u32 *) 0x040002b8)
#define REG_SQRT_PARAM_H (*(volatile u32 *) 0x040002bc)
#define SQRT_MODE_64BIT 1
#define SQRT_BUSY 0x8000

static int add32(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

/* `a` times `b` in 20.12, rounded to nearest, kept to 32 bits. */
static fx32 mul_round(int a, int b)
{
    return (fx32) (u32) ((u64) ((s64) a * b + 0x800) >> 12);
}

/* The square of `value` as an unsigned 64-bit number (sums of these wrap at 64 bits). */
static u64 square64(int value)
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

/* The ARM's ASR by a register: only the shift's low byte counts, and from 32 on every bit is
 * the sign. */
static int asr_register(int value, int shift)
{
    int amount = shift & 0xff;
    if (amount >= 32) {
        return value < 0 ? -1 : 0;
    }
    return value >> amount;
}

/* The table's entry for `angle`: its top 12 bits; sine first, then cosine. */
static fx16 angle_sin(int angle)
{
    return FX_SinCosTable_[2 * ((u16) angle >> 4)];
}

static fx16 angle_cos(int angle)
{
    return FX_SinCosTable_[2 * ((u16) angle >> 4) + 1];
}

/* func_020ea634: `v` rotated by `angle` about Z, from +X towards +Y. */
void Vec_RotateZ(Vec3 *v, int angle)
{
    int sin = angle_sin(angle);
    int cos = angle_cos(angle);
    fx32 x = v->x;
    fx32 y = v->y;
    v->x = sub32(mul_round(cos, x), mul_round(sin, y));
    v->y = add32(mul_round(sin, x), mul_round(cos, y));
}
CLEAN_AS(func_020ea634, Vec_RotateZ)

/* func_020ea6e0: `v` rotated by `angle` about Y, from +Z towards +X. */
void Vec_RotateY(Vec3 *v, int angle)
{
    int sin = angle_sin(angle);
    int cos = angle_cos(angle);
    fx32 x = v->x;
    fx32 z = v->z;
    v->x = add32(mul_round(sin, z), mul_round(cos, x));
    v->z = sub32(mul_round(cos, z), mul_round(sin, x));
}
CLEAN_AS(func_020ea6e0, Vec_RotateY)

/* func_020ea78c: `v` rotated by `angle` about X, from +Y towards +Z. */
void Vec_RotateX(Vec3 *v, int angle)
{
    int sin = angle_sin(angle);
    int cos = angle_cos(angle);
    fx32 y = v->y;
    fx32 z = v->z;
    v->y = sub32(mul_round(cos, y), mul_round(sin, z));
    v->z = add32(mul_round(sin, y), mul_round(cos, z));
}
CLEAN_AS(func_020ea78c, Vec_RotateX)

/* func_020ea838: `v` normalized in place; FALSE, with `v` unchanged, when it is zero and has no
 * direction. */
int Vec_NormalizeNonZero(Vec3 *v)
{
    if (v->x == 0 && v->y == 0 && v->z == 0) {
        return FALSE;
    }
    Vec3 copy;
    Vec_NormalizeCopy(&copy, v);
    return TRUE;
}
CLEAN_AS(func_020ea838, Vec_NormalizeNonZero)

/* func_020ea88c: `v` normalized in place, and copied to `dst`. */
void Vec_NormalizeCopy(Vec3 *dst, Vec3 *v)
{
    VEC_Normalize(v, v);
    dst->x = v->x;
    dst->y = v->y;
    dst->z = v->z;
}
CLEAN_AS(func_020ea88c, Vec_NormalizeCopy)

/* func_020ea8c8: `product` = `a` x `b`, and copied to `dst`. */
void Vec_CrossProductCopy(Vec3 *dst, Vec3 *product, const Vec3 *a, const Vec3 *b)
{
    VEC_CrossProduct(a, b, product);
    dst->x = product->x;
    dst->y = product->y;
    dst->z = product->z;
}
CLEAN_AS(func_020ea8c8, Vec_CrossProductCopy)

/* func_020ea90c: the dot product of `a` and `b` in the ground plane, truncated (not rounded) to
 * 20.12. */
fx32 Vec_DotXZ(const Vec3 *a, const Vec3 *b)
{
    u64 sum = (u64) ((s64) a->x * b->x) + (u64) ((s64) a->z * b->z);
    return (fx32) (u32) (sum >> 12);
}
CLEAN_AS(func_020ea90c, Vec_DotXZ)

/* func_020ea940: the square of the ground-plane distance from `a` to `b`, in 20.12 kept to 64
 * bits. QUIRK: the differences wrap at 32 bits. */
s64 Vec_DistanceSquaredXZ(const Vec3 *a, const Vec3 *b)
{
    return asr64(square64(sub32(a->x, b->x)) + square64(sub32(a->z, b->z)), 12);
}
CLEAN_AS(func_020ea940, Vec_DistanceSquaredXZ)

/* func_020ea970: the square of `v`'s ground-plane length, in 20.12 kept to 64 bits. */
s64 Vec_LengthSquaredXZ(const Vec3 *v)
{
    return asr64(square64(v->x) + square64(v->z), 12);
}
CLEAN_AS(func_020ea970, Vec_LengthSquaredXZ)

/* func_020ea990: the ground-plane distance from `a` to `b`. QUIRK: the differences wrap at 32
 * bits. */
fx32 Vec_DistanceXZ(const Vec3 *a, const Vec3 *b)
{
    return Math_SqrtRounded((s64) (square64(sub32(a->x, b->x)) + square64(sub32(a->z, b->z))));
}
CLEAN_AS(func_020ea990, Vec_DistanceXZ)

/* func_020ea9c8: `v`'s length in the ground plane. */
fx32 Vec_LengthXZ(const Vec3 *v)
{
    return Math_SqrtRounded((s64) (square64(v->x) + square64(v->z)));
}
CLEAN_AS(func_020ea9c8, Vec_LengthXZ)

/* func_020ea9e4: the distance from `a` to `b`. QUIRK: the differences wrap at 32 bits. */
fx32 Vec_Distance(const Vec3 *a, const Vec3 *b)
{
    u64 sum = square64(sub32(a->x, b->x)) + square64(sub32(a->y, b->y)) + square64(sub32(a->z, b->z));
    return Math_SqrtRounded((s64) sum);
}
CLEAN_AS(func_020ea9e4, Vec_Distance)

/* func_020eaa2c: TRUE when `a` and `b` differ. */
int Vec_Differ(const Vec3 *a, const Vec3 *b)
{
    return a->x != b->x || a->y != b->y || a->z != b->z;
}
CLEAN_AS(func_020eaa2c, Vec_Differ)

/* func_020eaa6c: TRUE when `a` and `b` are the same point. */
int Vec_Equal(const Vec3 *a, const Vec3 *b)
{
    return a->x == b->x && a->y == b->y && a->z == b->z;
}
CLEAN_AS(func_020eaa6c, Vec_Equal)

/* func_020eaaa8: each component of `v` shifted right by `shift` bits, keeping its sign (a
 * division by a power of two rounded down). */
void Vec_ShiftRight(Vec3 *v, int shift)
{
    v->x = asr_register(v->x, shift);
    v->y = asr_register(v->y, shift);
    v->z = asr_register(v->z, shift);
}
CLEAN_AS(func_020eaaa8, Vec_ShiftRight)

/* func_020eaad0: `dst` = `src` shifted as Vec_ShiftRight does. */
void Vec_ShiftRightCopy(Vec3 *dst, const Vec3 *src, int shift)
{
    Vec3 shifted = {
        asr_register(src->x, shift),
        asr_register(src->y, shift),
        asr_register(src->z, shift),
    };
    dst->x = shifted.x;
    dst->y = shifted.y;
    dst->z = shifted.z;
}
CLEAN_AS(func_020eaad0, Vec_ShiftRightCopy)

/* The value a division by zero gives: the largest number of `value`'s sign; 0 stays (and is
 * not written back). */
static void saturate(fx32 *value)
{
    if (*value > 0) {
        *value = 0x7fffffff;
    } else if (*value < 0) {
        *value = -0x7fffffff - 1;
    }
}

/* func_020eab08: `v` divided by `divisor` in 20.12. A divisor of 0 sends each component that is
 * not 0 to the largest value of its sign instead. */
void Vec_Divide(Vec3 *v, fx32 divisor)
{
    if (divisor == 0) {
        saturate(&v->x);
        saturate(&v->y);
        saturate(&v->z);
    } else {
        v->x = FX_Div(v->x, divisor);
        v->y = FX_Div(v->y, divisor);
        v->z = FX_Div(v->z, divisor);
    }
}
CLEAN_AS(func_020eab08, Vec_Divide)

/* func_020eabc8: `v` scaled by `scale` (20.12). */
void Vec_Scale(Vec3 *v, fx32 scale)
{
    v->x = mul_round(v->x, scale);
    v->y = mul_round(v->y, scale);
    v->z = mul_round(v->z, scale);
}
CLEAN_AS(func_020eabc8, Vec_Scale)

/* func_020eac34: `dst` = `src` scaled by `scale` (20.12). */
void Vec_ScaleCopy(Vec3 *dst, const Vec3 *src, fx32 scale)
{
    Vec3 scaled = {
        mul_round(src->x, scale),
        mul_round(src->y, scale),
        mul_round(src->z, scale),
    };
    dst->x = scaled.x;
    dst->y = scaled.y;
    dst->z = scaled.z;
}
CLEAN_AS(func_020eac34, Vec_ScaleCopy)

/* func_020eaca0: `difference` = `a` - `b` (it may be either of them). */
void Vec_Subtract(Vec3 *difference, const Vec3 *a, const Vec3 *b)
{
    Vec3 result = {
        sub32(a->x, b->x),
        sub32(a->y, b->y),
        sub32(a->z, b->z),
    };
    difference->x = result.x;
    difference->y = result.y;
    difference->z = result.z;
}
CLEAN_AS(func_020eaca0, Vec_Subtract)

/* func_020eace4: the square-root unit set to take 64-bit numbers; the start-up (func_020b1b84)
 * does it once. HW: a write to SQRTCNT. */
void Math_InitSqrt(void)
{
    REG_SQRTCNT = SQRT_MODE_64BIT;
}
CLEAN_AS(func_020eace4, Math_InitSqrt)

/* func_020eacf8: the square root of `value`, rounded to nearest: the unit takes the root of
 * 4 * `value`, which has one more bit, and the result is halved rounding up. With `value` a
 * sum of squares of 20.12 numbers (24 fraction bits), the root is in 20.12.
 * QUIRK: the top two bits of `value` are lost, so values of 2^62 or more (lengths of 2^31 or
 * more, 2^19 units in 20.12) come out wrong.
 * HW: SQRTCNT is set to 64-bit mode, the parameter written low word first, then the busy bit is
 * polled before the result is read. */
fx32 Math_SqrtRounded(s64 value)
{
    u64 parameter = (u64) value << 2;
    REG_SQRTCNT = SQRT_MODE_64BIT;
    REG_SQRT_PARAM_L = (u32) parameter;
    REG_SQRT_PARAM_H = (u32) (parameter >> 32);
    while (REG_SQRTCNT & SQRT_BUSY) {
    }
    return asr_register(add32((int) REG_SQRT_RESULT, 1), 1);
}
CLEAN_AS(func_020eacf8, Math_SqrtRounded)
