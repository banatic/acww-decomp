/* The visitors of a gathering (collision_visitor.h). */
#include "collision_visitor.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "collision_cylinder.h"
#include "collision_post_source.h"
#include "collision_triangle.h"

/* The base class's vtable. */
extern const u8 data_020da1c0[];
/* (0, 1.0, 0): the normal of a post's top. */
extern Vec3 data_021c317c;

/* How far down a wall reaches as the segment test sees it (-8.0). */
#define COLLISION_VISITOR_WALL_BOTTOM (-0x8000)

/* func_02031e5c: the base class's method for the posts (slot 2): nothing. */
void CollisionVisitor_NoPosts(void) {}
CLEAN_AS(func_02031e5c, CollisionVisitor_NoPosts)

/* func_02031e60: the base class's method for the floors (slot 1): nothing. */
void CollisionVisitor_NoFloors(void) {}
CLEAN_AS(func_02031e60, CollisionVisitor_NoFloors)

/* func_02031e64: the base class's method for the walls (slot 0): nothing. */
void CollisionVisitor_NoWalls(void) {}
CLEAN_AS(func_02031e64, CollisionVisitor_NoWalls)

/* func_02031e68: the base class's destructor: puts its vtable back. */
void CollisionVisitor_Destruct(CollisionVisitor *visitor)
{
    visitor->vtable = (const CollisionVisitorVtable *) (const void *) data_020da1c0;
}
CLEAN_AS(func_02031e68, CollisionVisitor_Destruct)

/* func_02031e74: the base class's constructor. */
void CollisionVisitor_Construct(CollisionVisitor *visitor)
{
    visitor->vtable = (const CollisionVisitorVtable *) (const void *) data_020da1c0;
}
CLEAN_AS(func_02031e74, CollisionVisitor_Construct)

/* Whether `item` comes before the end of the `count` items of `size` bytes from `first`, the
 * end's address worked out in 32 bits as the ARM does (a count too large for the address space
 * wraps it round, below `first`). */
static int collision_visitor_before(const void *item, const void *first, u32 count, u32 size)
{
    u32 end = (u32) (uintptr_t) first + count * size;
    return (u32) (uintptr_t) item < end;
}

/* Records what the segment test met: the shape's tag, its normal there and its attribute. */
static void collision_visitor_record(CollisionSegmentTest *test, const CollisionTag *tag, const Vec3 *normal)
{
    CollisionTag_Copy(&test->tag, tag);
    test->normal = *normal;
    test->attr = tag->attr;
    test->hit = 1;
}

/* func_02032788: the segment test's method for the posts (slot 2): a path from the start that
 * reaches a post's top (CollisionCylinder_HitTop) ends there, with the top's normal (up); one
 * that reaches its side below the top (CollisionCylinder_HitSideBelowTop) ends there, with the
 * normal from the post's axis to the new end, level. Both are tried on every post. */
void CollisionVisitor_TestPosts(CollisionSegmentTest *test, CollisionPostList *posts)
{
    test->post_count = posts->count;
    for (CollisionPost *post = posts->posts; collision_visitor_before(post, posts->posts, test->post_count, sizeof(*post));
         post++) {
        if (CollisionCylinder_HitTop((CollisionCylinder *) post, test->end, &test->start) != 0) {
            collision_visitor_record(test, &post->tag, &data_021c317c);
        }
        if (CollisionCylinder_HitSideBelowTop((CollisionCylinder *) post, test->end, &test->start) != 0) {
            CollisionTag_Copy(&test->tag, &post->tag);
            test->normal.x = test->end->x - post->position.x;
            test->normal.y = 0;
            test->normal.z = test->end->z - post->position.z;
            Vec_NormalizeNonZero(&test->normal);
            test->attr = post->tag.attr;
            test->hit = 1;
        }
    }
}
CLEAN_AS(func_02032788, CollisionVisitor_TestPosts)

/* func_02032844: the segment test's method for the floors (slot 1): a path that goes from the
 * front of a floor (or on it) to behind it and crosses it ends where it crosses, with the
 * floor's normal. */
void CollisionVisitor_TestFloors(CollisionSegmentTest *test, CollisionFloorList *floors)
{
    test->floor_count = floors->count;
    for (CollisionFloor *floor = floors->floors;
         collision_visitor_before(floor, floors->floors, test->floor_count, sizeof(*floor)); floor++) {
        if (CollisionTriangle_Distance(&floor->triangle, &test->start) < 0) {
            continue;
        }
        if (CollisionTriangle_Distance(&floor->triangle, test->end) >= 0) {
            continue;
        }
        Vec3 crossing;
        if (CollisionTriangle_SegmentHit(&floor->triangle, &crossing, &test->start, test->end) == 0) {
            continue;
        }
        *test->end = crossing;
        collision_visitor_record(test, &floor->tag, &floor->triangle.normal);
    }
}
CLEAN_AS(func_02032844, CollisionVisitor_TestFloors)

/* func_020328dc: the segment test's method for the walls (slot 0): each wall is seen as an
 * upright rectangle from its top down to -8.0, in two triangles facing along its normal; a
 * path that goes from the front of one (or on it) to behind it and crosses it ends where it
 * crosses, with the triangle's normal.
 * QUIRK: only X and Z of the end move to the crossing; its height stays. */
void CollisionVisitor_TestWalls(CollisionSegmentTest *test, CollisionWallList *walls)
{
    test->wall_count = walls->count;
    for (CollisionWall *wall = walls->walls; collision_visitor_before(wall, walls->walls, test->wall_count, sizeof(*wall));
         wall++) {
        const CollisionSegment *segment = &wall->segment;
        Vec3 normal = {segment->normal.x, 0, segment->normal.z};
        Vec3 top_start = {segment->start.x, wall->top, segment->start.z};
        Vec3 bottom_start = {segment->start.x, COLLISION_VISITOR_WALL_BOTTOM, segment->start.z};
        Vec3 bottom_end = {segment->end.x, COLLISION_VISITOR_WALL_BOTTOM, segment->end.z};
        Vec3 top_end = {segment->end.x, wall->top, segment->end.z};
        CollisionTriangle halves[2];

        CollisionTriangle_ConstructSet(&halves[0], &top_start, &bottom_start, &bottom_end, &normal);
        CollisionTriangle_ConstructSet(&halves[1], &top_start, &bottom_end, &top_end, &normal);
        for (int h = 0; h < 2; h++) {
            CollisionTriangle *half = &halves[h];
            if (CollisionTriangle_Distance(half, &test->start) < 0) {
                continue;
            }
            if (CollisionTriangle_Distance(half, test->end) >= 0) {
                continue;
            }
            Vec3 crossing;
            if (CollisionTriangle_SegmentHit(half, &crossing, &test->start, test->end) == 0) {
                continue;
            }
            Vec3 end = {crossing.x, test->end->y, crossing.z};
            *test->end = end;
            collision_visitor_record(test, &wall->tag, &half->normal);
        }
        CollisionTriangle_Destruct(&halves[1]);
        CollisionTriangle_Destruct(&halves[0]);
    }
}
CLEAN_AS(func_020328dc, CollisionVisitor_TestWalls)

/* func_020329ec: the push-out visitor's method for the posts (slot 2): with
 * COLLISION_QUERY_GROUND the position lands on a post's top under it (CollisionPosts_Land),
 * which puts it on the ground with the post's attribute; with COLLISION_QUERY_WALLS or
 * COLLISION_QUERY_ALL it is pushed out of the posts it touches (CollisionPosts_PushOut). The
 * owner and the current post source (CollisionPostSource_Current, asked each time) go to both
 * as their last two arguments, which they do not use. */
void CollisionVisitor_PushOutPosts(CollisionPushOut *visitor, CollisionPostList *posts)
{
    if ((visitor->flags & COLLISION_QUERY_GROUND) != 0) {
        int attr;
        if (CollisionPosts_Land(posts, visitor->position, &visitor->previous, &attr, (u32) (uintptr_t) visitor->owner,
                                (int) (uintptr_t) CollisionPostSource_Current()) != 0) {
            visitor->contacts->flags |= COLLISION_ON_GROUND;
            visitor->contacts->ground_attr = attr;
        }
    }
    if ((visitor->flags & (COLLISION_QUERY_WALLS | COLLISION_QUERY_ALL)) != 0) {
        CollisionPosts_PushOut(posts, visitor->position, visitor->radius, visitor->contacts, (u32) (uintptr_t) visitor->owner,
                               (int) (uintptr_t) CollisionPostSource_Current());
    }
}
CLEAN_AS(func_020329ec, CollisionVisitor_PushOutPosts)

/* func_02032a54: the push-out visitor's method for the floors (slot 1): a position below the
 * first corner of a floor it is over (seen from above) is lifted to that corner's height and
 * put on the ground with the floor's attribute.
 * QUIRK: each floor is taken as level, at the height of its first corner. */
void CollisionVisitor_PushOutFloors(CollisionPushOut *visitor, CollisionFloorList *floors)
{
    u32 count = floors->count;
    for (CollisionFloor *floor = floors->floors; collision_visitor_before(floor, floors->floors, count, sizeof(*floor));
         floor++) {
        if (visitor->position->y < floor->triangle.corner[0].y &&
            CollisionTriangle_ContainsXZ(&floor->triangle, visitor->position) != 0) {
            visitor->position->y = floor->triangle.corner[0].y;
            visitor->contacts->flags |= COLLISION_ON_GROUND;
            visitor->contacts->ground_attr = floor->tag.attr;
        }
    }
}
CLEAN_AS(func_02032a54, CollisionVisitor_PushOutFloors)
