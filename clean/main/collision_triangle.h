/* Triangles of the collision code (CollisionTriangle of field_collision.h, class vtable
 * 0x020da18c; a floor's vtable 0x020da21c has the same methods): the plane through the
 * corners, whether a point is inside the triangle seen along an axis, where a path crosses it,
 * and the three tests (the vtable's methods) that push a point out of it.
 *
 * The plane's normal is of unit length and its offset is -(normal . corner 0), so
 * CollisionTriangle_Distance is positive on the side the normal points to (the front). */
#ifndef CLEAN_MAIN_COLLISION_TRIANGLE_H
#define CLEAN_MAIN_COLLISION_TRIANGLE_H

#include "autoload_2/vector.h"
#include "field_collision.h"
#include "types.h"

/* The virtual methods of a triangle; each pushes `position`, moved from `previous`, out of it
 * to `distance` from it and says whether it touched. */
typedef struct CollisionTriangleVtable {
    int (*push_above)(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
    int (*push_through)(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
    int (*push_off_edges)(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
    int (*push_out)(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
} CollisionTriangleVtable;

int CollisionTriangle_LineHit(CollisionTriangle *triangle, Vec3 *hit, const Vec3 *start, const Vec3 *end);
int CollisionTriangle_SegmentHit(CollisionTriangle *triangle, Vec3 *hit, const Vec3 *start, const Vec3 *end);
int CollisionTriangle_ContainsYZ(const CollisionTriangle *triangle, const Vec3 *point);
int CollisionTriangle_ContainsXY(const CollisionTriangle *triangle, const Vec3 *point);
fx32 CollisionTriangle_Distance(const CollisionTriangle *triangle, const Vec3 *point);
fx32 CollisionTriangle_ComputeOffset(const CollisionTriangle *triangle);
int CollisionTriangle_ContainsXZ(const CollisionTriangle *triangle, const Vec3 *point);
int CollisionTriangle_Set(CollisionTriangle *triangle, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal);
int CollisionTriangle_CornerNormal(Vec3 *normal, const Vec3 *a, const Vec3 *b, const Vec3 *c);
int CollisionTriangle_PushOffEdges(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
int CollisionTriangle_PushAbove(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
int CollisionTriangle_PushThrough(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
int CollisionTriangle_PushOut(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance);
CollisionTriangle *CollisionTriangle_ConstructSet(CollisionTriangle *triangle, const Vec3 *a, const Vec3 *b, const Vec3 *c,
                                                  const Vec3 *normal);
void CollisionTriangle_DestructBase(CollisionTriangle *triangle);
void CollisionTriangle_Destruct(CollisionTriangle *triangle);
void CollisionTriangle_Construct(CollisionTriangle *triangle);
void CollisionTriangle_ConstructBase(CollisionTriangle *triangle);

#endif
