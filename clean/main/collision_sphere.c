/* A sphere of the collision code (collision_sphere.h). */
#include "collision_sphere.h"

#include "clean.h"
#include "itcm/vector.h"
#include "collision_line.h"

static_assert(sizeof(CollisionSphere) == 0x10, "CollisionSphere size");
static_assert(offsetof(CollisionLine, direction) == 0x18, "CollisionLine layout");

extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* func_0202f1cc: when the line passes within the sphere's radius of its center, `*out` is the
 * nearer to the line's start of two points, and the result is 1; else 0 and `*out` is left.
 * The first point is the center moved by the radius along the line's direction (z, y, then x
 * computed).
 * BUG: the second point should be the center moved back by as much, but is the center less the
 * first point: the offset alone (-direction * radius), a point near the origin. */
int CollisionSphere_HitLine(CollisionSphere *sphere, Vec3 *out, CollisionLine *line)
{
    fx32 radius = sphere->radius;
    if (CollisionLine_Distance(line, &sphere->center) > radius) {
        return 0;
    }
    Vec3 ahead;
    ahead.z = sphere->center.z + FX_MulFunc(line->direction.z, sphere->radius);
    ahead.y = sphere->center.y + FX_MulFunc(line->direction.y, sphere->radius);
    ahead.x = sphere->center.x + FX_MulFunc(line->direction.x, sphere->radius);
    Vec3 behind;
#ifdef BUGFIX
    behind.x = sphere->center.x - (ahead.x - sphere->center.x);
    behind.y = sphere->center.y - (ahead.y - sphere->center.y);
    behind.z = sphere->center.z - (ahead.z - sphere->center.z);
#else
    behind.x = sphere->center.x - ahead.x;
    behind.y = sphere->center.y - ahead.y;
    behind.z = sphere->center.z - ahead.z;
#endif
    s64 to_ahead = Vec_DistanceSquared(&line->start, &ahead);
    s64 to_behind = Vec_DistanceSquared(&line->start, &behind);
    *out = to_ahead < to_behind ? ahead : behind;
    return 1;
}
CLEAN_AS(func_0202f1cc, CollisionSphere_HitLine)

/* func_0202f268 */
void CollisionSphere_Set(CollisionSphere *sphere, const Vec3 *center, u32 radius)
{
    sphere->center.x = center->x;
    sphere->center.y = center->y;
    sphere->center.z = center->z;
    sphere->radius = (fx32) radius;
}
CLEAN_AS(func_0202f268, CollisionSphere_Set)

/* func_0202f278: nothing to do. */
void CollisionSphere_Destruct(void) {}
CLEAN_AS(func_0202f278, CollisionSphere_Destruct)

/* func_0202f27c: the center at the origin and no radius. */
void CollisionSphere_Construct(CollisionSphere *sphere)
{
    sphere->center.x = 0;
    sphere->center.y = 0;
    sphere->center.z = 0;
    sphere->radius = 0;
}
CLEAN_AS(func_0202f27c, CollisionSphere_Construct)
