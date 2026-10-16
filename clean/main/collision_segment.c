/* Points seen from above and the segments through them (collision_segment.h). */
#include "collision_segment.h"

#include "autoload_2/vector.h"
#include "clean.h"

static_assert(sizeof(CollisionPoint) == 8, "CollisionPoint size");
static_assert(offsetof(CollisionSegment, normal) == 0x14, "CollisionSegment normal");
static_assert(offsetof(CollisionSegment, offset) == 0x1c, "CollisionSegment offset");

/* The segment class's vtable. */
extern const u8 data_020da1a4[];
/* (0, 0): the origin of CollisionPoint distances. */
extern CollisionPoint data_021c30b8;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_Sqrt(fx32 value);

static fx32 abs_fx(fx32 value)
{
    return value < 0 ? -value : value;
}

/* ---- Pushing a point out of a wall */

/* func_0202f288: when `from` is in front of the segment and the move from `from` to `moved`
 * crosses it, `moved` is pushed along the normal by |radius - its distance| (from behind the
 * line, that puts it `radius` in front) and the result is 1; else 0.
 * QUIRK: the crossing point CollisionSegment_Crossing works out is not used. */
int CollisionSegment_PushBackCrossing(CollisionSegment *segment, CollisionPoint *moved, const CollisionPoint *from,
                                      fx32 radius)
{
    if (CollisionSegment_Distance(segment, from) <= 0) {
        return 0;
    }
    CollisionPoint crossing;
    CollisionPoint_Set(&crossing, 0, 0);
    if (CollisionSegment_Crossing(segment, &crossing, moved, from) == 0) {
        return 0;
    }
    fx32 push = abs_fx(radius - CollisionSegment_Distance(segment, moved));
    CollisionPoint offset = segment->normal;
    CollisionPoint_Scale(&offset, push);
    CollisionPoint_Add(moved, &offset);
    return 1;
}
CLEAN_AS(func_0202f288, CollisionSegment_PushBackCrossing)

/* func_0202f2f0: nothing to do. */
void CollisionPoint_Destruct(CollisionPoint *point)
{
    (void) point;
}
CLEAN_AS(func_0202f2f0, CollisionPoint_Destruct)

/* func_0202f2f4: when touching the segment is recorded (its vtable's slot 0), `moved` is in
 * front of its line by less than `radius` plus COLLISION_TOUCH_MARGIN and `from` is in front:
 * the result is 1 when `moved` is at least `radius` in front; else, when `moved` is within
 * `radius` of an end (start first), it is pushed away from that end to `radius` from it (along
 * the normal by `radius` when it is on the end itself) and the result is 1. Else 0.
 * QUIRK: whether `from` is in front is asked twice. */
int CollisionSegment_PushOutEnds(CollisionSegment *segment, CollisionPoint *moved, const CollisionPoint *from, fx32 radius)
{
    const CollisionSegmentVtable *vtable = (const CollisionSegmentVtable *) segment->vtable;
    if (vtable->is_recorded(segment) == 0) {
        return 0;
    }
    fx32 distance = CollisionSegment_Distance(segment, moved);
    if (distance < 0 || distance >= radius + COLLISION_TOUCH_MARGIN || CollisionSegment_Distance(segment, from) <= 0) {
        return 0;
    }
    if (distance >= radius) {
        return 1;
    }
    if (CollisionSegment_Distance(segment, from) <= 0) {
        return 0;
    }
    CollisionPoint ends[2];
    ends[0] = segment->start;
    ends[1] = segment->end;
    for (int i = 0; i < 2; i++) {
        fx32 to_end = FX_Sqrt((fx32) CollisionPoint_DistanceSquared(&ends[i], moved));
        if (to_end < radius) {
            CollisionPoint away;
            CollisionPoint_Difference(&away, moved, &ends[i]);
            fx32 push = radius;
            if (CollisionPoint_Normalize(&away) == 0) {
                CollisionPoint_Set(&away, segment->normal.x, segment->normal.z);
            } else {
                push = radius - to_end;
            }
            away.x = FX_MulFunc(away.x, push);
            away.z = FX_MulFunc(away.z, push);
            moved->x += away.x;
            moved->z += away.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0202f2f4, CollisionSegment_PushOutEnds)

/* func_0202f3e0: a segment's vtable slot 0: touching it is always recorded. */
int CollisionSegment_IsRecorded(void)
{
    return 1;
}
CLEAN_AS(func_0202f3e0, CollisionSegment_IsRecorded)

/* func_0202f3e4: when `from` is not behind the segment and `moved` is within `radius` of its
 * line (on either side), and `from` or `moved` (in that order) is between its ends: `moved`
 * goes along the normal by `radius` less its distance and the result is 1. When `moved` is
 * farther than `radius` in front but by less than COLLISION_TOUCH_MARGIN more, the result is 1
 * with nothing moved. Else 0.
 * QUIRK: a `moved` behind the line by more than `radius` also gives 1 with nothing moved, as
 * its signed distance is below radius + COLLISION_TOUCH_MARGIN. */
int CollisionSegment_PushOutNear(CollisionSegment *segment, CollisionPoint *moved, const CollisionPoint *from, fx32 radius)
{
    fx32 distance = CollisionSegment_Distance(segment, moved);
    if (CollisionSegment_Distance(segment, from) < 0) {
        return 0;
    }
    if (abs_fx(distance) <= radius) {
        if (CollisionSegment_SpansPoint(segment, from) != 0 || CollisionSegment_SpansPoint(segment, moved) != 0) {
            CollisionPoint offset = segment->normal;
            CollisionPoint_Scale(&offset, radius - distance);
            CollisionPoint_Add(moved, &offset);
            return 1;
        }
        return 0;
    }
    return distance < radius + COLLISION_TOUCH_MARGIN;
}
CLEAN_AS(func_0202f3e4, CollisionSegment_PushOutNear)

/* func_0202f464: whether `point` is between the lines through the segment's ends square to it
 * (or on one of them). FALSE when the segment has no length. */
int CollisionSegment_SpansPoint(CollisionSegment *segment, const CollisionPoint *point)
{
    CollisionPoint outward_start;
    CollisionPoint_Difference(&outward_start, &segment->start, &segment->end);
    if (CollisionPoint_Normalize(&outward_start) == 0) {
        return 0;
    }
    CollisionPoint outward_end;
    CollisionPoint_Set(&outward_end, -outward_start.x, -outward_start.z);

    /* The two square lines, each with its normal pointing away from the segment. */
    CollisionPoint start_side;
    CollisionPoint_Sum(&start_side, &segment->start, &segment->normal);
    CollisionSegment at_start;
    CollisionSegment_Construct(&at_start, &segment->start, &start_side, &outward_start);
    CollisionPoint end_side;
    CollisionPoint_Sum(&end_side, &segment->end, &segment->normal);
    CollisionSegment at_end;
    CollisionSegment_Construct(&at_end, &segment->end, &end_side, &outward_end);

    fx32 past_start = CollisionSegment_Distance(&at_start, point);
    fx32 past_end = CollisionSegment_Distance(&at_end, point);
    int result = (past_start >= 0 && past_end >= 0) || (past_start <= 0 && past_end <= 0);
    CollisionSegment_Destruct(&at_end);
    CollisionSegment_Destruct(&at_start);
    return result;
}
CLEAN_AS(func_0202f464, CollisionSegment_SpansPoint)

/* func_0202f520: when the segment from `start` to `end` crosses this one (each one's ends on
 * opposite sides of the other's line), `*crossing` is where their lines meet and the result is
 * CollisionSegment_Intersect's; else 0. */
int CollisionSegment_Crossing(CollisionSegment *segment, CollisionPoint *crossing, const CollisionPoint *start,
                              const CollisionPoint *end)
{
    fx32 start_side = CollisionSegment_Distance(segment, start);
    fx32 end_side = CollisionSegment_Distance(segment, end);
    if (FX_MulFunc(start_side, end_side) >= 0) {
        return 0;
    }
    CollisionSegment path;
    CollisionSegment_ConstructThrough(&path, start, end);
    fx32 own_start_side = CollisionSegment_Distance(&path, &segment->start);
    fx32 own_end_side = CollisionSegment_Distance(&path, &segment->end);
    int result = 0;
    if (FX_MulFunc(own_start_side, own_end_side) < 0) {
        result = CollisionSegment_Intersect(segment, crossing, start, end);
    }
    CollisionSegment_Destruct(&path);
    return result;
}
CLEAN_AS(func_0202f520, CollisionSegment_Crossing)

/* func_0202f59c: where the segment's line meets the line from `start` to `end`: `*crossing`
 * and 1, or 0 when they are about parallel. Z comes from the two lines' equations by Cramer's
 * rule and X from the equation of whichever line has an X coefficient (this one first); 0 with
 * Z alone written when neither has. */
int CollisionSegment_Intersect(CollisionSegment *segment, CollisionPoint *crossing, const CollisionPoint *start,
                               const CollisionPoint *end)
{
    CollisionSegment path;
    CollisionSegment_ConstructThrough(&path, start, end);
    fx32 det_a = FX_MulFunc(segment->normal.x, path.normal.z);
    fx32 det = det_a - FX_MulFunc(path.normal.x, segment->normal.z);
    if (abs_fx(det) < COLLISION_EPSILON) {
        CollisionSegment_Destruct(&path);
        return 0;
    }
    fx32 path_offset = path.offset;
    fx32 numerator = FX_MulFunc(path.normal.x, segment->offset);
    numerator -= FX_MulFunc(segment->normal.x, path_offset);
    crossing->z = FX_Div(numerator, det);

    const CollisionSegment *line = segment;
    if (abs_fx(segment->normal.x) < COLLISION_EPSILON) {
        line = &path;
        if (abs_fx(path.normal.x) < COLLISION_EPSILON) {
            CollisionSegment_Destruct(&path);
            return 0;
        }
    }
    fx32 normal_x = line->normal.x;
    fx32 offset = line->offset;
    crossing->x = FX_Div(-(FX_MulFunc(line->normal.z, crossing->z) + offset), normal_x);
    CollisionSegment_Destruct(&path);
    return 1;
}
CLEAN_AS(func_0202f59c, CollisionSegment_Intersect)

/* ---- Segments */

/* func_0202f660: the signed distance from the segment's line to `point`. */
fx32 CollisionSegment_Distance(const CollisionSegment *segment, const CollisionPoint *point)
{
    fx32 offset = segment->offset;
    fx32 x = FX_MulFunc(segment->normal.x, point->x);
    fx32 z = FX_MulFunc(segment->normal.z, point->z);
    return x + z + offset;
}
CLEAN_AS(func_0202f660, CollisionSegment_Distance)

/* func_0202f688: the offset of the line through the start along the normal. */
fx32 CollisionSegment_ComputeOffset(const CollisionSegment *segment)
{
    fx32 x = FX_MulFunc(segment->normal.x, segment->start.x);
    fx32 z = FX_MulFunc(segment->normal.z, segment->start.z);
    return -(x + z);
}
CLEAN_AS(func_0202f688, CollisionSegment_ComputeOffset)

/* func_0202f6ac */
void CollisionSegment_Set(CollisionSegment *segment, const CollisionPoint *start, const CollisionPoint *end,
                          const CollisionPoint *normal)
{
    CollisionPoint_Copy(&segment->start, start);
    CollisionPoint_Copy(&segment->end, end);
    CollisionPoint_Copy(&segment->normal, normal);
    segment->offset = CollisionSegment_ComputeOffset(segment);
}
CLEAN_AS(func_0202f6ac, CollisionSegment_Set)

/* func_0202f6dc: the base destructor (of a wall's segment). */
void CollisionSegment_DestructBase(CollisionSegment *segment)
{
    segment->vtable = data_020da1a4;
}
CLEAN_AS(func_0202f6dc, CollisionSegment_DestructBase)

/* func_0202f6e8: the destructor. */
void CollisionSegment_Destruct(CollisionSegment *segment)
{
    segment->vtable = data_020da1a4;
}
CLEAN_AS(func_0202f6e8, CollisionSegment_Destruct)

/* func_0202f6f4: constructs the segment and sets it. */
CollisionSegment *CollisionSegment_Construct(CollisionSegment *segment, const CollisionPoint *start, const CollisionPoint *end,
                                             const CollisionPoint *normal)
{
    segment->vtable = data_020da1a4;
    CollisionPoint_Set(&segment->start, 0, 0);
    CollisionPoint_Set(&segment->end, 0, 0);
    CollisionPoint_Set(&segment->normal, 0, 0);
    CollisionSegment_Set(segment, start, end, normal);
    return segment;
}
CLEAN_AS(func_0202f6f4, CollisionSegment_Construct)

/* func_0202f740: constructs the segment from `start` to `end`, with the normal a quarter turn
 * from its direction (CollisionPoint_LineNormal). */
CollisionSegment *CollisionSegment_ConstructThrough(CollisionSegment *segment, const CollisionPoint *start,
                                                    const CollisionPoint *end)
{
    segment->vtable = data_020da1a4;
    CollisionPoint_Set(&segment->start, 0, 0);
    CollisionPoint_Set(&segment->end, 0, 0);
    CollisionPoint_Set(&segment->normal, 0, 0);
    CollisionPoint normal;
    CollisionPoint_Set(&normal, 0, 0);
    CollisionPoint_LineNormal(&normal, start, end);
    CollisionSegment_Set(segment, start, end, &normal);
    return segment;
}
CLEAN_AS(func_0202f740, CollisionSegment_ConstructThrough)

/* ---- Points */

/* func_0202f7a0: `*normal` is the direction from `a` to `b` turned a quarter turn (x, z) to
 * (-z, x), normalized (left as it is when `a` and `b` are the same). */
void CollisionPoint_LineNormal(CollisionPoint *normal, const CollisionPoint *a, const CollisionPoint *b)
{
    CollisionPoint direction;
    CollisionPoint_Difference(&direction, b, a);
    normal->x = -direction.z;
    normal->z = direction.x;
    CollisionPoint_Normalize(normal);
}
CLEAN_AS(func_0202f7a0, CollisionPoint_LineNormal)

/* func_0202f7cc: `point` turned by `angle` about Y (Vec_RotateY). */
void CollisionPoint_RotateY(CollisionPoint *point, int angle)
{
    Vec3 v;
    v.x = point->x;
    v.y = 0;
    v.z = point->z;
    Vec_RotateY(&v, angle);
    point->x = v.x;
    point->z = v.z;
}
CLEAN_AS(func_0202f7cc, CollisionPoint_RotateY)

/* func_0202f7f4: `v` divided by its length, and 1; 0, with `v` left, when the length is below
 * COLLISION_EPSILON. QUIRK: the squared length is cut to 32 bits before the square root. */
int CollisionPoint_Normalize(CollisionPoint *v)
{
    fx32 length = FX_Sqrt((fx32) CollisionPoint_DistanceSquared(v, &data_021c30b8));
    if (abs_fx(length) < COLLISION_EPSILON) {
        return 0;
    }
    v->x = FX_Div(v->x, length);
    v->z = FX_Div(v->z, length);
    return 1;
}
CLEAN_AS(func_0202f7f4, CollisionPoint_Normalize)

/* func_0202f838: the squared distance from `b` to `a` (20.12).
 * QUIRK: the sum is taken in 32 bits, then widened. */
s64 CollisionPoint_DistanceSquared(const CollisionPoint *a, const CollisionPoint *b)
{
    CollisionPoint d;
    CollisionPoint_Set(&d, a->x - b->x, a->z - b->z);
    fx32 x = FX_MulFunc(d.x, d.x);
    fx32 z = FX_MulFunc(d.z, d.z);
    return (s64) (fx32) (x + z);
}
CLEAN_AS(func_0202f838, CollisionPoint_DistanceSquared)

/* func_0202f874 */
CollisionPoint *CollisionPoint_Scale(CollisionPoint *point, fx32 scale)
{
    point->x = FX_MulFunc(point->x, scale);
    point->z = FX_MulFunc(point->z, scale);
    return point;
}
CLEAN_AS(func_0202f874, CollisionPoint_Scale)

/* func_0202f898: `*difference` = `a` - `b`. */
void CollisionPoint_Difference(CollisionPoint *difference, const CollisionPoint *a, const CollisionPoint *b)
{
    CollisionPoint_Set(difference, a->x - b->x, a->z - b->z);
}
CLEAN_AS(func_0202f898, CollisionPoint_Difference)

/* func_0202f8b4: `point` += `offset`. */
void CollisionPoint_Add(CollisionPoint *point, const CollisionPoint *offset)
{
    point->x += offset->x;
    point->z += offset->z;
}
CLEAN_AS(func_0202f8b4, CollisionPoint_Add)

/* func_0202f8c8: `*sum` = `a` + `b`. */
void CollisionPoint_Sum(CollisionPoint *sum, const CollisionPoint *a, const CollisionPoint *b)
{
    CollisionPoint_Set(sum, a->x + b->x, a->z + b->z);
}
CLEAN_AS(func_0202f8c8, CollisionPoint_Sum)

/* func_0202f8e4 */
CollisionPoint *CollisionPoint_Copy(CollisionPoint *point, const CollisionPoint *from)
{
    CollisionPoint_Set(point, from->x, from->z);
    return point;
}
CLEAN_AS(func_0202f8e4, CollisionPoint_Copy)

/* func_0202f8fc */
void CollisionPoint_Set(CollisionPoint *point, fx32 x, fx32 z)
{
    point->x = x;
    point->z = z;
}
CLEAN_AS(func_0202f8fc, CollisionPoint_Set)
