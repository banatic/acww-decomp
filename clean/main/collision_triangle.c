/* Triangles of the collision code (collision_triangle.h). */
#include "collision_triangle.h"

#include "clean.h"
#include "collision_line.h"
#include "collision_segment.h"
#include "itcm/vector.h"

static_assert(offsetof(CollisionTriangle, normal) == 0x28, "CollisionTriangle normal");
static_assert(offsetof(CollisionTriangle, offset) == 0x34, "CollisionTriangle offset");

/* The triangle class's vtable. */
extern const u8 data_020da18c[];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

static fx32 abs_fx(fx32 value)
{
    return value < 0 ? -value : value;
}

static const CollisionTriangleVtable *vtable_of(const CollisionTriangle *triangle)
{
    return (const CollisionTriangleVtable *) triangle->vtable;
}

/* Whether the cross products of the corners' offsets from a point, taken in one plane of the
 * axes, all have the same sign (or are zero): the point is inside the triangle seen square to
 * that plane. */
static int same_signs(fx32 a, fx32 b, fx32 c)
{
    return (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);
}

/* func_0202f904: where the line through `start` and `end` meets the triangle's plane, in
 * `*hit` (written whenever the line is not about parallel to the plane); the result is 1 when
 * that point is inside the triangle seen along Y, X or Z (asked in that order, each only when
 * the normal has a part along that axis). */
int CollisionTriangle_LineHit(CollisionTriangle *triangle, Vec3 *hit, const Vec3 *start, const Vec3 *end)
{
    fx32 start_distance = CollisionTriangle_Distance(triangle, start);
    fx32 difference = start_distance - CollisionTriangle_Distance(triangle, end);
    if (abs_fx(difference) < COLLISION_EPSILON) {
        return 0;
    }
    Vec3 direction;
    Vec_Subtract(&direction, end, start);
    fx32 along = FX_Div(start_distance, difference);
    fx32 z = start->z + FX_MulFunc(along, direction.z);
    fx32 y = start->y + FX_MulFunc(along, direction.y);
    hit->x = start->x + FX_MulFunc(along, direction.x);
    hit->y = y;
    hit->z = z;

    if (abs_fx(triangle->normal.y) >= COLLISION_EPSILON && CollisionTriangle_ContainsXZ(triangle, hit) != 0) {
        return 1;
    }
    if (abs_fx(triangle->normal.x) >= COLLISION_EPSILON && CollisionTriangle_ContainsYZ(triangle, hit) != 0) {
        return 1;
    }
    if (abs_fx(triangle->normal.z) >= COLLISION_EPSILON && CollisionTriangle_ContainsXY(triangle, hit) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0202f904, CollisionTriangle_LineHit)

/* func_0202f9d0: CollisionTriangle_LineHit when `start` and `end` are on opposite sides of the
 * plane; else 0. */
int CollisionTriangle_SegmentHit(CollisionTriangle *triangle, Vec3 *hit, const Vec3 *start, const Vec3 *end)
{
    fx32 start_distance = CollisionTriangle_Distance(triangle, start);
    fx32 end_distance = CollisionTriangle_Distance(triangle, end);
    if (FX_MulFunc(start_distance, end_distance) < 0) {
        return CollisionTriangle_LineHit(triangle, hit, start, end);
    }
    return 0;
}
CLEAN_AS(func_0202f9d0, CollisionTriangle_SegmentHit)

/* The corners' offsets from `point`. */
static void corner_offsets(const CollisionTriangle *triangle, const Vec3 *point, Vec3 offsets[3])
{
    Vec_Subtract(&offsets[0], &triangle->corner[0], point);
    Vec_Subtract(&offsets[1], &triangle->corner[1], point);
    Vec_Subtract(&offsets[2], &triangle->corner[2], point);
}

/* func_0202fa10: whether `point` is inside the triangle seen along X. */
int CollisionTriangle_ContainsYZ(const CollisionTriangle *triangle, const Vec3 *point)
{
    Vec3 v[3];
    corner_offsets(triangle, point, v);
    fx32 a = FX_MulFunc(v[0].y, v[1].z);
    a -= FX_MulFunc(v[0].z, v[1].y);
    fx32 b = FX_MulFunc(v[1].y, v[2].z);
    b -= FX_MulFunc(v[1].z, v[2].y);
    fx32 c = FX_MulFunc(v[2].y, v[0].z);
    c -= FX_MulFunc(v[2].z, v[0].y);
    return same_signs(a, b, c);
}
CLEAN_AS(func_0202fa10, CollisionTriangle_ContainsYZ)

/* func_0202fa9c: whether `point` is inside the triangle seen along Z. */
int CollisionTriangle_ContainsXY(const CollisionTriangle *triangle, const Vec3 *point)
{
    Vec3 v[3];
    corner_offsets(triangle, point, v);
    fx32 a = FX_MulFunc(v[0].x, v[1].y);
    a -= FX_MulFunc(v[0].y, v[1].x);
    fx32 b = FX_MulFunc(v[1].x, v[2].y);
    b -= FX_MulFunc(v[1].y, v[2].x);
    fx32 c = FX_MulFunc(v[2].x, v[0].y);
    c -= FX_MulFunc(v[2].y, v[0].x);
    return same_signs(a, b, c);
}
CLEAN_AS(func_0202fa9c, CollisionTriangle_ContainsXY)

/* func_0202fb28: the signed distance from the triangle's plane to `point`. */
fx32 CollisionTriangle_Distance(const CollisionTriangle *triangle, const Vec3 *point)
{
    fx32 z = FX_MulFunc(triangle->normal.z, point->z);
    fx32 x = FX_MulFunc(triangle->normal.x, point->x);
    fx32 y = FX_MulFunc(triangle->normal.y, point->y);
    return triangle->offset + (z + (x + y));
}
CLEAN_AS(func_0202fb28, CollisionTriangle_Distance)

/* func_0202fb60: the offset of the plane through corner 0 square to the normal. */
fx32 CollisionTriangle_ComputeOffset(const CollisionTriangle *triangle)
{
    fx32 z = FX_MulFunc(triangle->normal.z, triangle->corner[0].z);
    fx32 x = FX_MulFunc(triangle->normal.x, triangle->corner[0].x);
    fx32 y = FX_MulFunc(triangle->normal.y, triangle->corner[0].y);
    return -(z + (x + y));
}
CLEAN_AS(func_0202fb60, CollisionTriangle_ComputeOffset)

/* func_0202fb8c: whether `point` is inside the triangle seen along Y (from above). */
int CollisionTriangle_ContainsXZ(const CollisionTriangle *triangle, const Vec3 *point)
{
    Vec3 v[3];
    corner_offsets(triangle, point, v);
    fx32 a = FX_MulFunc(v[0].z, v[1].x);
    a -= FX_MulFunc(v[0].x, v[1].z);
    fx32 b = FX_MulFunc(v[1].z, v[2].x);
    b -= FX_MulFunc(v[1].x, v[2].z);
    fx32 c = FX_MulFunc(v[2].z, v[0].x);
    c -= FX_MulFunc(v[2].x, v[0].z);
    return same_signs(a, b, c);
}
CLEAN_AS(func_0202fb8c, CollisionTriangle_ContainsXZ)

/* func_0202fc18: the corners and normal, and the plane's offset from them; always 1. */
int CollisionTriangle_Set(CollisionTriangle *triangle, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal)
{
    triangle->corner[0].x = a->x;
    triangle->corner[0].y = a->y;
    triangle->corner[0].z = a->z;
    triangle->corner[1].x = b->x;
    triangle->corner[1].y = b->y;
    triangle->corner[1].z = b->z;
    triangle->corner[2].x = c->x;
    triangle->corner[2].y = c->y;
    triangle->corner[2].z = c->z;
    triangle->normal.x = normal->x;
    triangle->normal.y = normal->y;
    triangle->normal.z = normal->z;
    triangle->offset = CollisionTriangle_ComputeOffset(triangle);
    return 1;
}
CLEAN_AS(func_0202fc18, CollisionTriangle_Set)

/* func_0202fc5c: `*normal` is the unit normal of corners `a`, `b`, `c` ((b - a) x (c - a));
 * the result is whether it had a length (else it is left zero). */
int CollisionTriangle_CornerNormal(Vec3 *normal, const Vec3 *a, const Vec3 *b, const Vec3 *c)
{
    Vec3 ab;
    Vec3 ac;
    Vec3 copy;
    Vec_Subtract(&ab, b, a);
    Vec_Subtract(&ac, c, a);
    Vec_CrossProductCopy(&copy, normal, &ab, &ac);
    return Vec_NormalizeNonZero(normal);
}
CLEAN_AS(func_0202fc5c, CollisionTriangle_CornerNormal)

/* func_0202fc94: vtable slot 2. When `previous` and `position` are both in front of the plane
 * and `position` nearer than `distance`, the first edge (corners 0-1, 1-2, 2-0) that
 * `position` is within `distance` of, and between the ends of, pushes it away from the edge's
 * nearest point to `distance` from it (along the normal by `distance` when it is on the edge);
 * the result is 1 when one did. */
int CollisionTriangle_PushOffEdges(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance)
{
    if (CollisionTriangle_Distance(triangle, previous) < 0) {
        return 0;
    }
    fx32 above = CollisionTriangle_Distance(triangle, position);
    if (above < 0) {
        return 0;
    }
    int result = 0;
    if (above < distance) {
        CollisionLine edges[3];
        CollisionLine_Construct(&edges[0], &triangle->corner[0], &triangle->corner[1]);
        CollisionLine_Construct(&edges[1], &triangle->corner[1], &triangle->corner[2]);
        CollisionLine_Construct(&edges[2], &triangle->corner[2], &triangle->corner[0]);
        for (int i = 0; i < 3; i++) {
            Vec3 nearest;
            fx32 to_edge = CollisionLine_NearestDistance(&edges[i], &nearest, position);
            if (to_edge >= distance || CollisionLine_Spans(&edges[i], position) == 0) {
                continue;
            }
            Vec3 away;
            Vec_Subtract(&away, position, &nearest);
            if (Vec_NormalizeNonZero(&away) == 0) {
                away = triangle->normal;
                Vec_Scale(&away, distance);
            } else {
                Vec_Scale(&away, distance - to_edge);
            }
            VEC_Add(position, &away, position);
            result = 1;
            break;
        }
        CollisionLine_Destruct(&edges[2]);
        CollisionLine_Destruct(&edges[1]);
        CollisionLine_Destruct(&edges[0]);
    }
    return result;
}
CLEAN_AS(func_0202fc94, CollisionTriangle_PushOffEdges)

/* func_0202fd78: vtable slot 0. When `position` is in front of the plane by no more than
 * `distance` plus COLLISION_TOUCH_MARGIN the result is 1; when it is nearer than `distance`
 * it is also pushed along the normal to `distance` in front, but only when it is over the
 * triangle (the line along the normal through it hits it; else the result is 0). `previous`
 * is not used. */
int CollisionTriangle_PushAbove(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance)
{
    (void) previous;
    fx32 above = CollisionTriangle_Distance(triangle, position);
    if (above < 0 || above > distance + COLLISION_TOUCH_MARGIN) {
        return 0;
    }
    if (above >= distance) {
        return 1;
    }
    Vec3 along_normal;
    Vec3 hit;
    Vec_Add(&along_normal, position, &triangle->normal);
    if (CollisionTriangle_LineHit(triangle, &hit, position, &along_normal) == 0) {
        return 0;
    }
    fx32 push = distance - above;
    position->x += FX_MulFunc(push, triangle->normal.x);
    position->y += FX_MulFunc(push, triangle->normal.y);
    position->z += FX_MulFunc(push, triangle->normal.z);
    return 1;
}
CLEAN_AS(func_0202fd78, CollisionTriangle_PushAbove)

/* func_0202fe00: vtable slot 1. When `position` is behind the plane (or on it), `previous` in
 * front, and the path between them crosses the triangle, `position` is put at the crossing
 * moved `distance` along the normal, and the result is 1; else 0. */
int CollisionTriangle_PushThrough(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance)
{
    Vec3 hit;
    if (CollisionTriangle_Distance(triangle, position) <= 0 && CollisionTriangle_Distance(triangle, previous) > 0 &&
        CollisionTriangle_SegmentHit(triangle, &hit, position, previous) != 0) {
        position->x = hit.x + FX_MulFunc(distance, triangle->normal.x);
        position->y = hit.y + FX_MulFunc(distance, triangle->normal.y);
        position->z = hit.z + FX_MulFunc(distance, triangle->normal.z);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_0202fe00, CollisionTriangle_PushThrough)

/* func_0202fe68: vtable slot 3: the three tests through the vtable, slot 1, 0 then 2, all run;
 * 1 when any touched. */
int CollisionTriangle_PushOut(CollisionTriangle *triangle, Vec3 *position, Vec3 *previous, fx32 distance)
{
    int result = 0;
    if (vtable_of(triangle)->push_through(triangle, position, previous, distance) != 0) {
        result = 1;
    }
    if (vtable_of(triangle)->push_above(triangle, position, previous, distance) != 0) {
        result = 1;
    }
    if (vtable_of(triangle)->push_off_edges(triangle, position, previous, distance) != 0) {
        result = 1;
    }
    return result;
}
CLEAN_AS(func_0202fe68, CollisionTriangle_PushOut)

/* func_0202feb4: constructs the triangle and sets it (CollisionTriangle_Set). */
CollisionTriangle *CollisionTriangle_ConstructSet(CollisionTriangle *triangle, const Vec3 *a, const Vec3 *b, const Vec3 *c,
                                                  const Vec3 *normal)
{
    triangle->vtable = data_020da18c;
    CollisionTriangle_Set(triangle, a, b, c, normal);
    return triangle;
}
CLEAN_AS(func_0202feb4, CollisionTriangle_ConstructSet)

/* func_0202fed4: the base destructor (of a floor's triangle). */
void CollisionTriangle_DestructBase(CollisionTriangle *triangle)
{
    triangle->vtable = data_020da18c;
}
CLEAN_AS(func_0202fed4, CollisionTriangle_DestructBase)

/* func_0202fee0: the destructor. */
void CollisionTriangle_Destruct(CollisionTriangle *triangle)
{
    triangle->vtable = data_020da18c;
}
CLEAN_AS(func_0202fee0, CollisionTriangle_Destruct)

/* func_0202feec: the constructor: no normal and no offset (the corners are left). */
void CollisionTriangle_Construct(CollisionTriangle *triangle)
{
    triangle->vtable = data_020da18c;
    triangle->normal.x = 0;
    triangle->normal.y = 0;
    triangle->normal.z = 0;
    triangle->offset = 0;
}
CLEAN_AS(func_0202feec, CollisionTriangle_Construct)

/* func_0202ff00: the base constructor (of a floor's triangle), the same. */
void CollisionTriangle_ConstructBase(CollisionTriangle *triangle)
{
    triangle->vtable = data_020da18c;
    triangle->normal.x = 0;
    triangle->normal.y = 0;
    triangle->normal.z = 0;
    triangle->offset = 0;
}
CLEAN_AS(func_0202ff00, CollisionTriangle_ConstructBase)
