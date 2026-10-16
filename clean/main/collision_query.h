/* Questions to the field's collision (field_collision.h): gathering the shapes in a box and
 * handing them to a visitor, moving an actor out of walls and onto the ground, a segment test
 * along a path, the ground's height and attribute under a point, posts, water around a point
 * and whether a step between neighbouring units is open.
 *
 * Positions are 20.12 fixed point and a unit is 2.0 wide (COLLISION_UNIT_SHIFT). */
#ifndef CLEAN_MAIN_COLLISION_QUERY_H
#define CLEAN_MAIN_COLLISION_QUERY_H

#include "autoload_2/vector.h"
#include "field_collision.h"
#include "types.h"

/* The flags of a gathering (CollisionQuery_Gather) and of the moves and tests built on it.
 * Posts are gathered with any of the first three; fences and cliffs with 0x02 or 0x04; floors
 * only when the caller asks for them, with any flag. */
#define COLLISION_QUERY_GROUND 0x01 /* CollisionQuery_Move: the position is put on the ground */
#define COLLISION_QUERY_WALLS 0x02  /* fences and cliffs */
/* fences and cliffs, also the back faces of cliffs, posts of kind 2 and the extra posts;
 * CollisionQuery_Move: the position goes back to the previous one where the ground is raised
 * or a post stands */
#define COLLISION_QUERY_ALL 0x04
#define COLLISION_QUERY_STORE 0x08     /* the position found is written back */
#define COLLISION_QUERY_NO_FENCES 0x10 /* no fences between posts */
#define COLLISION_QUERY_NO_POSTS 0x20  /* no posts */
#define COLLISION_QUERY_NO_LISTED 0x40 /* not the walls and floors of the listed objects (func_02031ecc) */
#define COLLISION_QUERY_MODE_1 0x80    /* CollisionQuery_Move: the ground is asked in mode 1 */

struct CollisionVisitor;

/* What a gathering hands its lists to (a C++ object; the push-out of func_02031288 and the
 * segment test of func_020311bc are two). */
typedef struct CollisionVisitorVtable {
    void (*walls)(struct CollisionVisitor *visitor, CollisionWallList *walls);
    void (*floors)(struct CollisionVisitor *visitor, CollisionFloorList *floors);
    void (*posts)(struct CollisionVisitor *visitor, CollisionPostList *posts);
} CollisionVisitorVtable;

typedef struct CollisionVisitor {
    const CollisionVisitorVtable *vtable;
} CollisionVisitor;

/* The segment test (vtable 0x020da1d4): the first shape the path from `start` to `*end` meets
 * moves `*end` to the meeting point and is recorded. */
typedef struct CollisionSegmentTest {
    const void *vtable;
    Vec3 *end;        /* 0x04 */
    Vec3 start;       /* 0x08 */
    u32 flags;        /* 0x14 */
    u8 hit;           /* 0x18 */
    u8 unk_19[3];     /* 0x19 */
    CollisionTag tag; /* 0x1c: the shape met */
    Vec3 normal;      /* 0x24: its normal there */
    int attr;         /* 0x30 */
    u32 wall_count;   /* 0x34: the lists' counts as the test saw them */
    u32 floor_count;  /* 0x38 */
    u32 post_count;   /* 0x3c */
} CollisionSegmentTest;

/* The result of a segment test for its caller: the tag and the normal of the shape met. */
typedef struct CollisionTraceHit {
    CollisionSegmentHit hit;
    Vec3 normal; /* 0x08 */
} CollisionTraceHit;

void CollisionQuery_Gather(const Vec3 *min, const Vec3 *max, CollisionVisitor *visitor, int flags, u8 with_floors,
                           u8 alternate);
int CollisionQuery_HasPostAtPoint(const Vec3 *point);
int CollisionQuery_HasPostAt(int x, int z);
int CollisionQuery_PostAt(int x, int z, fx32 *radius, fx32 *height, int *kind);
int CollisionQuery_FloorHeight(int unused);
int CollisionQuery_GroundY(const Vec3 *point, int *attr, int flags);
int CollisionQuery_ClampToRect(Vec3 *point, fx32 inset, const Vec3 *centre, fx32 width, fx32 depth);
int CollisionQuery_Trace(CollisionTraceHit *result, Vec3 *end, const Vec3 *start, int flags);
void CollisionQuery_Move(CollisionContacts *contacts, Vec3 *position, const Vec3 *previous, int facing, fx32 radius,
                         void *owner, int flags);
int CollisionQuery_FindSpotInBlock(int *x, int *z, int block_x, int block_z);
void CollisionQuery_DestructCell(void *cell);
int CollisionQuery_IsWaterAroundPoint(const Vec3 *point);
int CollisionQuery_FindWaterAhead(Vec3 *out, const Vec3 *from, int angle, int distance, fx32 radius, int steps);
int CollisionQuery_FindWaterAlong(Vec3 *out, const Vec3 *from, u32 distance, int angle, u32 steps, fx32 radius, int mode);
int CollisionQuery_IsWaterAround(const Vec3 *point, fx32 radius, fx32 *surface, int mode);
int CollisionQuery_CanStep(int from_x, int from_z, int x, int z, u8 strict);
int CollisionQuery_Byte08IfNoPost(int x, int z);
int CollisionQuery_Byte08IfFree(int x, int z);
int CollisionQuery_IsRaisedOrPost(const Vec3 *position);

#endif
