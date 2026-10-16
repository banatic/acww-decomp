/* A line of the collision code (collision_line.h). */
#include "collision_line.h"

#include "clean.h"

static_assert(sizeof(CollisionLine) == 0x24, "CollisionLine size");

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 VEC_DotProduct(const Vec3 *a, const Vec3 *b);

/* func_0202ff14: whether `point` is between the planes square to the line through its ends
 * (or on one of them). */
int CollisionLine_Spans(const CollisionLine *line, const Vec3 *point)
{
    fx32 start = VEC_DotProduct(&line->direction, &line->start);
    fx32 from_start = VEC_DotProduct(&line->direction, point);
    fx32 end = VEC_DotProduct(&line->direction, &line->end);
    fx32 from_end = VEC_DotProduct(&line->direction, point);
    return FX_MulFunc(from_start - start, from_end - end) > 0 ? 0 : 1;
}
CLEAN_AS(func_0202ff14, CollisionLine_Spans)

/* func_0202ff68: `*nearest` is the point of the (infinite) line nearest `point`: the start
 * moved along the direction by the projection of start-to-point. */
void CollisionLine_NearestPoint(const CollisionLine *line, Vec3 *nearest, const Vec3 *point)
{
    fx32 along = VEC_DotProduct(&line->direction, point);
    along -= VEC_DotProduct(&line->direction, &line->start);
    fx32 z = FX_MulFunc(line->direction.z, along) + line->start.z;
    fx32 y = FX_MulFunc(line->direction.y, along) + line->start.y;
    fx32 x = FX_MulFunc(line->direction.x, along) + line->start.x;
    nearest->x = x;
    nearest->y = y;
    nearest->z = z;
}
CLEAN_AS(func_0202ff68, CollisionLine_NearestPoint)

/* func_0202ffbc: the distance from `point` to the line, and in `*nearest` the line's point
 * nearest it. */
fx32 CollisionLine_NearestDistance(const CollisionLine *line, Vec3 *nearest, const Vec3 *point)
{
    Vec3 found;
    CollisionLine_NearestPoint(line, &found, point);
    *nearest = found;
    return Vec_Distance(&found, point);
}
CLEAN_AS(func_0202ffbc, CollisionLine_NearestDistance)

/* func_0202ffe8: the line from `start` to `end`. */
void CollisionLine_Set(CollisionLine *line, const Vec3 *start, const Vec3 *end)
{
    line->start.x = start->x;
    line->start.y = start->y;
    line->start.z = start->z;
    line->end.x = end->x;
    line->end.y = end->y;
    line->end.z = end->z;
    CollisionLine_SetDirection(line, &line->direction);
}
CLEAN_AS(func_0202ffe8, CollisionLine_Set)

/* func_0203000c: the distance from `point` to the (infinite) line. */
fx32 CollisionLine_Distance(const CollisionLine *line, const Vec3 *point)
{
    Vec3 nearest;
    CollisionLine_NearestPoint(line, &nearest, point);
    return Vec_Distance(&nearest, point);
}
CLEAN_AS(func_0203000c, CollisionLine_Distance)

/* func_0203002c: `*direction` is the unit direction from the line's start to its end (the
 * difference itself when they are the same point). */
void CollisionLine_SetDirection(const CollisionLine *line, Vec3 *direction)
{
    Vec3 difference;
    Vec_Subtract(&difference, &line->end, &line->start);
    *direction = difference;
    Vec_NormalizeNonZero(direction);
}
CLEAN_AS(func_0203002c, CollisionLine_SetDirection)

/* func_02030058: nothing to do. */
void CollisionLine_Destruct(CollisionLine *line)
{
    (void) line;
}
CLEAN_AS(func_02030058, CollisionLine_Destruct)

/* func_0203005c: constructs the line from `start` to `end`. */
CollisionLine *CollisionLine_Construct(CollisionLine *line, const Vec3 *start, const Vec3 *end)
{
    CollisionLine_Set(line, start, end);
    return line;
}
CLEAN_AS(func_0203005c, CollisionLine_Construct)
