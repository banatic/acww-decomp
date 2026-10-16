/* Points seen from above (CollisionPoint: X and Z) and the lines through them
 * (CollisionSegment, class vtable 0x020da1a4) of the field's collision code
 * (field_collision.h): setting, adding, scaling and normalizing points, a segment's signed
 * distance to a point, where two segments cross, and the tests that push a point moving towards
 * a wall back out of it.
 *
 * A segment's normal is of unit length and its offset is -(normal . start), so
 * CollisionSegment_Distance is positive on the side the normal points to (the wall's front). */
#ifndef CLEAN_MAIN_COLLISION_SEGMENT_H
#define CLEAN_MAIN_COLLISION_SEGMENT_H

#include "field_collision.h"
#include "types.h"

/* The virtual methods of a segment: whether touching it is recorded (a wall's
 * CollisionWall_IsRecorded overrides it). */
typedef struct CollisionSegmentVtable {
    int (*is_recorded)(CollisionSegment *segment);
} CollisionSegmentVtable;

/* A point closer to a segment's line than this past the pushing distance still counts as
 * touching it (1/8). */
#define COLLISION_TOUCH_MARGIN 0x200
/* A length or determinant below this (4/4096) counts as zero. */
#define COLLISION_EPSILON 4

int CollisionSegment_PushBackCrossing(CollisionSegment *segment, CollisionPoint *moved, const CollisionPoint *from,
                                      fx32 radius);
void CollisionPoint_Destruct(CollisionPoint *point);
int CollisionSegment_PushOutEnds(CollisionSegment *segment, CollisionPoint *moved, const CollisionPoint *from, fx32 radius);
int CollisionSegment_IsRecorded(void);
int CollisionSegment_PushOutNear(CollisionSegment *segment, CollisionPoint *moved, const CollisionPoint *from, fx32 radius);
int CollisionSegment_SpansPoint(CollisionSegment *segment, const CollisionPoint *point);
int CollisionSegment_Crossing(CollisionSegment *segment, CollisionPoint *crossing, const CollisionPoint *start,
                              const CollisionPoint *end);
int CollisionSegment_Intersect(CollisionSegment *segment, CollisionPoint *crossing, const CollisionPoint *start,
                               const CollisionPoint *end);
fx32 CollisionSegment_Distance(const CollisionSegment *segment, const CollisionPoint *point);
fx32 CollisionSegment_ComputeOffset(const CollisionSegment *segment);
void CollisionSegment_Set(CollisionSegment *segment, const CollisionPoint *start, const CollisionPoint *end,
                          const CollisionPoint *normal);
void CollisionSegment_DestructBase(CollisionSegment *segment);
void CollisionSegment_Destruct(CollisionSegment *segment);
CollisionSegment *CollisionSegment_Construct(CollisionSegment *segment, const CollisionPoint *start, const CollisionPoint *end,
                                             const CollisionPoint *normal);
CollisionSegment *CollisionSegment_ConstructThrough(CollisionSegment *segment, const CollisionPoint *start,
                                                    const CollisionPoint *end);
void CollisionPoint_LineNormal(CollisionPoint *normal, const CollisionPoint *a, const CollisionPoint *b);
void CollisionPoint_RotateY(CollisionPoint *point, int angle);
int CollisionPoint_Normalize(CollisionPoint *v);
s64 CollisionPoint_DistanceSquared(const CollisionPoint *a, const CollisionPoint *b);
CollisionPoint *CollisionPoint_Scale(CollisionPoint *point, fx32 scale);
void CollisionPoint_Difference(CollisionPoint *difference, const CollisionPoint *a, const CollisionPoint *b);
void CollisionPoint_Add(CollisionPoint *point, const CollisionPoint *offset);
void CollisionPoint_Sum(CollisionPoint *sum, const CollisionPoint *a, const CollisionPoint *b);
CollisionPoint *CollisionPoint_Copy(CollisionPoint *point, const CollisionPoint *from);
void CollisionPoint_Set(CollisionPoint *point, fx32 x, fx32 z);

#endif
