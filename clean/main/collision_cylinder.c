/* An upright cylinder of the collision code (collision_cylinder.h). */
#include "collision_cylinder.h"

#include "clean.h"
#include "collision_segment.h"

static_assert(sizeof(CollisionCylinder) == 0x14, "CollisionCylinder size");

/* The parameter of a path's point at its end (1.0). */
#define PATH_END 0x1000

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 value);

static fx32 abs_fx(fx32 value)
{
    return value < 0 ? -value : value;
}

/* `value` shifted left as the ARM does, bits leaving at the top. */
static fx32 shift_left(fx32 value, int shift)
{
    return (fx32) ((u32) value << shift);
}

/* Whether a path parameter `t` is on the path (0 to PATH_END), or about 0. */
static int on_path(fx32 t)
{
    return abs_fx(t) < COLLISION_EPSILON || (t >= 0 && t <= PATH_END);
}

/* The point of the path from `from` along `direction` at parameter `t` (Z, Y then X). */
static void path_point(Vec3 *point, const Vec3 *from, const Vec3 *direction, fx32 t)
{
    fx32 z = from->z + FX_MulFunc(t, direction->z);
    fx32 y = from->y + FX_MulFunc(t, direction->y);
    point->x = from->x + FX_MulFunc(t, direction->x);
    point->y = y;
    point->z = z;
}

/* Where the path from `*from` by `*direction` (end less start, parameter 0 to 1.0) meets the
 * cylinder's infinite side seen from above, as the roots of a t^2 + b t + c = 0 in `t[0]`
 * (the nearer) and `t[1]`; 0 when the path has no length across the axis or misses. */
static int side_crossings(const CollisionCylinder *cylinder, const Vec3 *from, const Vec3 *to, Vec3 *direction, fx32 t[2])
{
    Vec3 centre = cylinder->base;
    fx32 radius = cylinder->radius;
    Vec_Subtract(direction, to, from);

    fx32 zz = FX_MulFunc(direction->z, direction->z);
    fx32 xx = FX_MulFunc(direction->x, direction->x);
    fx32 a = xx + zz;
    if (abs_fx(a) < COLLISION_EPSILON) {
        return 0;
    }
    fx32 off_x = from->x - centre.x;
    fx32 off_z = from->z - centre.z;
    fx32 b = FX_MulFunc(direction->x, off_x);
    b += FX_MulFunc(direction->z, off_z);
    b = shift_left(FX_Div(b, a), 1);

    fx32 oz = FX_MulFunc(off_z, off_z);
    fx32 ox = FX_MulFunc(off_x, off_x);
    fx32 rr = FX_MulFunc(radius, radius);
    fx32 c = FX_Div(ox + oz - rr, a);

    fx32 discriminant = FX_MulFunc(b, b) - shift_left(c, 2);
    if (discriminant < 0) {
        return 0;
    }
    fx32 root = abs_fx(FX_Sqrt(discriminant));
    t[0] = -(b + root) >> 1;
    t[1] = (root - b) >> 1;
    return 1;
}

/* func_0203006c: when the path from `start` (outside the cylinder seen from above) to `*end`
 * meets the cylinder's side between its base and top, `*end` becomes the first such meeting
 * and the result is 1; else 0. */
int CollisionCylinder_HitSide(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start)
{
    if (CollisionCylinder_ContainsXZ(cylinder, start) != 0) {
        return 0;
    }
    Vec3 from = *start;
    Vec3 to = *end;
    Vec3 direction;
    fx32 t[2];
    if (side_crossings(cylinder, &from, &to, &direction, t) == 0) {
        return 0;
    }
    fx32 bottom = cylinder->base.y;
    fx32 top = bottom + cylinder->height;
    for (int i = 0; i < 2; i++) {
        if (on_path(t[i])) {
            Vec3 point;
            path_point(&point, &from, &direction, t[i]);
            if (point.y >= bottom && point.y <= top) {
                *end = point;
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_0203006c, CollisionCylinder_HitSide)

/* The point `along` from `start` in the unit `direction` (Z, Y then X). */
static void at_height(Vec3 *point, const Vec3 *start, const Vec3 *direction, fx32 along)
{
    fx32 z = start->z + FX_MulFunc(direction->z, along);
    fx32 y = start->y + FX_MulFunc(direction->y, along);
    fx32 x = start->x + FX_MulFunc(direction->x, along);
    point->x = x;
    point->y = y;
    point->z = z;
}

/* func_0203021c: when the path from `start` to `*end` goes down through the cylinder's top, or
 * up through height 0, within its radius, `*end` becomes that crossing and the result is 1;
 * else 0. The top is tried first; the bottom only when the path does not start above and end
 * below the top.
 * QUIRK: the bottom is height 0, not the base's height. */
int CollisionCylinder_HitCaps(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start)
{
    Vec3 from = *start;
    Vec3 to = *end;
    Vec3 direction;
    Vec_Subtract(&direction, &to, &from);
    if (Vec_NormalizeNonZero(&direction) == 0 || abs_fx(direction.y) < COLLISION_EPSILON) {
        return 0;
    }
    fx32 top = cylinder->base.y + cylinder->height;
    fx32 along;
    if (from.y > top && to.y < top) {
        along = FX_Div(top - from.y, direction.y);
    } else if (from.y < 0 && to.y > 0) {
        along = FX_Div(-from.y, direction.y);
    } else {
        return 0;
    }
    Vec3 point;
    at_height(&point, &from, &direction, along);
    if (CollisionCylinder_ContainsXZ(cylinder, &point) != 0) {
        *end = point;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0203021c, CollisionCylinder_HitCaps)

/* func_02030324: CollisionCylinder_HitSide with no bottom: a meeting anywhere below the top
 * counts. */
int CollisionCylinder_HitSideBelowTop(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start)
{
    if (CollisionCylinder_ContainsXZ(cylinder, start) != 0) {
        return 0;
    }
    Vec3 from = *start;
    Vec3 to = *end;
    Vec3 direction;
    fx32 t[2];
    fx32 top = cylinder->base.y + cylinder->height;
    if (side_crossings(cylinder, &from, &to, &direction, t) == 0) {
        return 0;
    }
    for (int i = 0; i < 2; i++) {
        if (on_path(t[i])) {
            Vec3 point;
            path_point(&point, &from, &direction, t[i]);
            if (point.y <= top) {
                *end = point;
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_02030324, CollisionCylinder_HitSideBelowTop)

/* func_020304d4: when the path from `start` to `*end` goes down through the cylinder's top
 * within its radius, `*end` becomes that crossing and the result is 1; else 0. */
int CollisionCylinder_HitTop(CollisionCylinder *cylinder, Vec3 *end, const Vec3 *start)
{
    fx32 top = cylinder->base.y + cylinder->height;
    Vec3 from = *start;
    if (from.y <= top) {
        return 0;
    }
    Vec3 to = *end;
    if (to.y >= top) {
        return 0;
    }
    Vec3 direction;
    Vec_Subtract(&direction, &to, &from);
    if (Vec_NormalizeNonZero(&direction) == 0 || abs_fx(direction.y) < COLLISION_EPSILON) {
        return 0;
    }
    Vec3 point;
    at_height(&point, &from, &direction, FX_Div(top - from.y, direction.y));
    if (CollisionCylinder_ContainsXZ(cylinder, &point) != 0) {
        *end = point;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020304d4, CollisionCylinder_HitTop)

/* func_02030580: when `position` came from `previous`, at the top's height or above, to below
 * it within the radius, it is put on the top and the result is 1; else 0. */
int CollisionCylinder_LandOnTop(CollisionCylinder *cylinder, Vec3 *position, const Vec3 *previous)
{
    fx32 top = cylinder->base.y + cylinder->height;
    if (previous->y >= top && position->y < top && CollisionCylinder_ContainsXZ(cylinder, position) != 0) {
        position->y = top;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02030580, CollisionCylinder_LandOnTop)

/* func_020305b0: for a point of `radius` below the top: when it overlaps the cylinder seen from
 * above, it is pushed straight away from the axis until they touch (not moved when it is on
 * the axis, and then the result is 0); the result is 1 when it was pushed, or when it is
 * outside but by no more than COLLISION_TOUCH_MARGIN. */
int CollisionCylinder_PushOut(CollisionCylinder *cylinder, Vec3 *position, fx32 radius)
{
    fx32 distance = Vec_DistanceXZ(&cylinder->base, position);
    if (distance < radius + cylinder->radius) {
        if (position->y >= cylinder->base.y + cylinder->height) {
            return 0;
        }
        Vec3 away;
        away.x = position->x - cylinder->base.x;
        away.y = 0;
        away.z = position->z - cylinder->base.z;
        if (Vec_NormalizeNonZero(&away) == 0) {
            return 0;
        }
        fx32 overlap = radius + cylinder->radius - distance;
        position->x += FX_MulFunc(away.x, overlap);
        position->z += FX_MulFunc(away.z, overlap);
        return 1;
    }
    if (distance > radius + cylinder->radius + COLLISION_TOUCH_MARGIN) {
        return 0;
    }
    return position->y < cylinder->base.y + cylinder->height;
}
CLEAN_AS(func_020305b0, CollisionCylinder_PushOut)

/* func_02030640 */
void CollisionCylinder_Set(CollisionCylinder *cylinder, const Vec3 *base, fx32 radius, fx32 height)
{
    CollisionCylinder_SetCircle(cylinder, base, (u32) radius);
    cylinder->height = height;
}
CLEAN_AS(func_02030640, CollisionCylinder_Set)

/* func_02030658: the base destructor (of a post's cylinder). */
CollisionCylinder *CollisionCylinder_DestructBase(CollisionCylinder *cylinder)
{
    CollisionCylinder_DestructCircle();
    return cylinder;
}
CLEAN_AS(func_02030658, CollisionCylinder_DestructBase)

/* func_02030668: the destructor. */
CollisionCylinder *CollisionCylinder_Destruct(CollisionCylinder *cylinder)
{
    CollisionCylinder_DestructCircle();
    return cylinder;
}
CLEAN_AS(func_02030668, CollisionCylinder_Destruct)

/* ---- The base class (the base and the radius) and the constructors ---- */

/* func_02030678: constructs the cylinder with its base, radius and height. */
CollisionCylinder *CollisionCylinder_ConstructSet(CollisionCylinder *cylinder, const Vec3 *base, fx32 radius, fx32 height)
{
    CollisionCylinder_ConstructCircleSet(cylinder, base, (u32) radius);
    cylinder->height = height;
    return cylinder;
}
CLEAN_AS(func_02030678, CollisionCylinder_ConstructSet)

/* func_02030690: constructs an empty cylinder (all zero). */
CollisionCylinder *CollisionCylinder_Construct(CollisionCylinder *cylinder)
{
    CollisionCylinder_ConstructCircle(cylinder);
    cylinder->height = 0;
    return cylinder;
}
CLEAN_AS(func_02030690, CollisionCylinder_Construct)

/* func_020306a4: whether `point` is within the radius of the cylinder's axis seen from above
 * (on the circle counts). Each axis is first compared alone, then the squares are.
 * QUIRK: the squares are 20.12 products that wrap in 32 bits. */
int CollisionCylinder_ContainsXZ(const CollisionCylinder *cylinder, const Vec3 *point)
{
    fx32 dx = point->x - cylinder->base.x;
    fx32 dz = point->z - cylinder->base.z;
    if (abs_fx(dx) > cylinder->radius || abs_fx(dz) > cylinder->radius) {
        return 0;
    }
    fx32 zz = FX_MulFunc(dz, dz);
    fx32 xx = FX_MulFunc(dx, dx);
    fx32 rr = FX_MulFunc(cylinder->radius, cylinder->radius);
    return xx + zz <= rr;
}
CLEAN_AS(func_020306a4, CollisionCylinder_ContainsXZ)

/* func_02030708: the base class's setter. The base is copied a word at a time from X to Z, as
 * the game does, which matters only when it overlaps the cylinder. */
void CollisionCylinder_SetCircle(CollisionCylinder *cylinder, const Vec3 *base, u32 radius)
{
    cylinder->base.x = base->x;
    cylinder->base.y = base->y;
    cylinder->base.z = base->z;
    cylinder->radius = (fx32) radius;
}
CLEAN_AS(func_02030708, CollisionCylinder_SetCircle)

/* func_02030718: the base class's destructor; nothing to do. */
void CollisionCylinder_DestructCircle(void) {}
CLEAN_AS(func_02030718, CollisionCylinder_DestructCircle)

/* func_0203071c: constructs the base class with a base and a radius; the object. */
int CollisionCylinder_ConstructCircleSet(CollisionCylinder *cylinder, const Vec3 *base, u32 radius)
{
    CollisionCylinder_SetCircle(cylinder, base, radius);
    return (int) (uintptr_t) cylinder;
}
CLEAN_AS(func_0203071c, CollisionCylinder_ConstructCircleSet)

/* func_0203072c: constructs the base class empty: base (0, 0, 0), radius 0. */
void CollisionCylinder_ConstructCircle(CollisionCylinder *cylinder)
{
    cylinder->base.x = 0;
    cylinder->base.y = 0;
    cylinder->base.z = 0;
    cylinder->radius = 0;
}
CLEAN_AS(func_0203072c, CollisionCylinder_ConstructCircle)
