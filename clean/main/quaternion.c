/* Rotation quaternions (quaternion.h). Sums wrap at 32 bits, as the ARM's do. */
#include "quaternion.h"

#include "clean.h"

/* One in 20.12 fixed point. */
#define QUAT_ONE 0x1000

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_InvSqrt(fx32 value);

static fx32 quat_add(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

static fx32 quat_sub(fx32 a, fx32 b)
{
    return (fx32) ((u32) a - (u32) b);
}

static fx32 quat_twice(fx32 a)
{
    return (fx32) ((u32) a << 1);
}

/* a x b, rounded as fixed point: bits 12-43 of the 64-bit product with half a unit added. */
static fx32 quat_scale(fx32 a, fx32 b)
{
    u64 product = (u64) ((s64) a * b) + 0x800;
    return (fx32) (u32) (product >> 12);
}

/* func_0209a204: the product a b. `product` may be a or b. The products are taken in this
 * order (FX_MulFunc). */
void Quat_Multiply(const Quat *a, const Quat *b, Quat *product)
{
    fx32 ww = FX_MulFunc(a->w, b->w);
    fx32 xx = FX_MulFunc(a->x, b->x);
    fx32 yy = FX_MulFunc(a->y, b->y);
    fx32 zz = FX_MulFunc(a->z, b->z);
    fx32 w = quat_sub(quat_sub(quat_sub(ww, xx), yy), zz);

    fx32 yz = FX_MulFunc(a->y, b->z);
    fx32 wx = FX_MulFunc(a->w, b->x);
    fx32 xw = FX_MulFunc(a->x, b->w);
    fx32 zy = FX_MulFunc(a->z, b->y);
    fx32 x = quat_sub(quat_add(quat_add(wx, xw), yz), zy);

    fx32 zx = FX_MulFunc(a->z, b->x);
    fx32 wy = FX_MulFunc(a->w, b->y);
    fx32 yw = FX_MulFunc(a->y, b->w);
    fx32 xz = FX_MulFunc(a->x, b->z);
    fx32 y = quat_sub(quat_add(quat_add(wy, yw), zx), xz);

    fx32 xy = FX_MulFunc(a->x, b->y);
    fx32 wz = FX_MulFunc(a->w, b->z);
    fx32 zw = FX_MulFunc(a->z, b->w);
    fx32 yx = FX_MulFunc(a->y, b->x);
    fx32 z = quat_sub(quat_add(quat_add(wz, zw), xy), yx);

    product->x = x;
    product->y = y;
    product->z = z;
    product->w = w;
}
CLEAN_AS(func_0209a204, Quat_Multiply)

/* func_0209a2ec: the rotation of `q` in the matrix's 3x3 part, and no translation. */
void Quat_ToMtx43(const Quat *q, Mtx43 *mtx)
{
    /* The first nine words of a 4x3 matrix are its 3x3 part. */
    Quat_ToMtx33(q, (Mtx33 *) mtx);
    mtx->m[3][0] = 0;
    mtx->m[3][1] = 0;
    mtx->m[3][2] = 0;
}
CLEAN_AS(func_0209a2ec, Quat_ToMtx43)

/* func_0209a304: the rotation matrix of the unit quaternion `q`. The products are taken in
 * this order (FX_MulFunc). */
void Quat_ToMtx33(const Quat *q, Mtx33 *mtx)
{
    fx32 xx = FX_MulFunc(q->x, q->x);
    fx32 xy = FX_MulFunc(q->x, q->y);
    fx32 xz = FX_MulFunc(q->x, q->z);
    fx32 zz = FX_MulFunc(q->z, q->z);
    fx32 zy = FX_MulFunc(q->z, q->y);
    fx32 yy = FX_MulFunc(q->y, q->y);
    fx32 wx = FX_MulFunc(q->w, q->x);
    fx32 wy = FX_MulFunc(q->w, q->y);
    fx32 wz = FX_MulFunc(q->w, q->z);

    mtx->m[0][0] = quat_sub(QUAT_ONE, quat_twice(quat_add(yy, zz)));
    mtx->m[0][1] = quat_twice(quat_add(xy, wz));
    mtx->m[0][2] = quat_twice(quat_sub(xz, wy));
    mtx->m[1][0] = quat_twice(quat_sub(xy, wz));
    mtx->m[1][1] = quat_sub(QUAT_ONE, quat_twice(quat_add(xx, zz)));
    mtx->m[1][2] = quat_twice(quat_add(zy, wx));
    mtx->m[2][0] = quat_twice(quat_add(wy, xz));
    mtx->m[2][1] = quat_twice(quat_sub(zy, wx));
    mtx->m[2][2] = quat_sub(QUAT_ONE, quat_twice(quat_add(xx, yy)));
}
CLEAN_AS(func_0209a304, Quat_ToMtx33)

/* func_0209a3c8: `q` scaled to unit length by FX_InvSqrt of its squared length. The squared
 * length is summed in 64 bits and cut to bits 12-43; each part is then scaled with rounding. */
void Quat_Normalize(Quat *q)
{
    u64 sum = (u64) ((s64) q->y * q->y);
    sum += (u64) ((s64) q->x * q->x);
    sum += (u64) ((s64) q->z * q->z);
    sum += (u64) ((s64) q->w * q->w);
    fx32 inverse = FX_InvSqrt((fx32) (u32) (sum >> 12));

    q->x = quat_scale(inverse, q->x);
    q->y = quat_scale(inverse, q->y);
    q->z = quat_scale(inverse, q->z);
    q->w = quat_scale(inverse, q->w);
}
CLEAN_AS(func_0209a3c8, Quat_Normalize)
