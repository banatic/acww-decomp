/* Points and vectors in 20.12 fixed point: rotating one about an axis, normalizing, distances
 * and lengths (whole or in the ground plane XZ), comparing, scaling and shifting, and the
 * hardware square root the lengths use. Angles are 16-bit fractions of a turn (fx_math.h). */
#ifndef CLEAN_AUTOLOAD_2_VECTOR_H
#define CLEAN_AUTOLOAD_2_VECTOR_H

#include "types.h"

/* A point or vector in 20.12 fixed point (NitroSDK's VecFx32). */
typedef struct Vec3 {
    fx32 x;
    fx32 y;
    fx32 z;
} Vec3;

void Vec_RotateZ(Vec3 *v, int angle);
void Vec_RotateY(Vec3 *v, int angle);
void Vec_RotateX(Vec3 *v, int angle);
int Vec_NormalizeNonZero(Vec3 *v);
void Vec_NormalizeCopy(Vec3 *dst, Vec3 *v);
void Vec_CrossProductCopy(Vec3 *dst, Vec3 *product, const Vec3 *a, const Vec3 *b);
fx32 Vec_DotXZ(const Vec3 *a, const Vec3 *b);
s64 Vec_DistanceSquaredXZ(const Vec3 *a, const Vec3 *b);
s64 Vec_LengthSquaredXZ(const Vec3 *v);
fx32 Vec_DistanceXZ(const Vec3 *a, const Vec3 *b);
fx32 Vec_LengthXZ(const Vec3 *v);
fx32 Vec_Distance(const Vec3 *a, const Vec3 *b);
int Vec_Differ(const Vec3 *a, const Vec3 *b);
int Vec_Equal(const Vec3 *a, const Vec3 *b);
void Vec_ShiftRight(Vec3 *v, int shift);
void Vec_ShiftRightCopy(Vec3 *dst, const Vec3 *src, int shift);
void Vec_Divide(Vec3 *v, fx32 divisor);
void Vec_Scale(Vec3 *v, fx32 scale);
void Vec_ScaleCopy(Vec3 *dst, const Vec3 *src, fx32 scale);
void Vec_Subtract(Vec3 *difference, const Vec3 *a, const Vec3 *b);
void Math_InitSqrt(void);
fx32 Math_SqrtRounded(s64 value);

#endif
