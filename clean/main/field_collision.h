/* Collision on the field: what stops a moving actor, and what it stands on.
 *
 * Each move (func_02031288, func_020311bc) gathers the shapes near the path into four global
 * lists and hands them to a visitor (a C++ object with three methods: walls, floors, posts):
 * - a grid of up to 7 by 7 units around the path (data_021c4c7c), each unit with the height
 *   and attribute of its four sides from the unit's type (CollisionCell);
 * - walls (data_021c3bac): vertical segments seen from above, built where the sides of
 *   neighbouring units differ in height (cliffs), between neighbouring posts (fences) and by
 *   other code;
 * - floors (data_021c4030): triangles over the units' tops;
 * - posts (data_021c4a34): upright cylinders asked of the map's post source unit by unit.
 * The push-out visitor (vtable 0x020da1e8) moves the actor's position out of the walls and
 * posts it touches and records the touches in the actor's CollisionContacts.
 *
 * Positions are 20.12 fixed point; a unit is 0x2000 (2.0) wide and unit n spans
 * [n * 0x2000, (n + 1) * 0x2000) on X and Z. Points seen from above (CollisionPoint) keep X and
 * Z. Angles are 16-bit fractions of a turn (autoload_2/fx_math.h).
 *
 * A row of the table at 0x020c907c (CollisionTypeInfo) is looked up both by a unit's type
 * (itcm/field_units.h) and by the attribute of a side; rows past 0x7b read as zero. */
#ifndef CLEAN_MAIN_FIELD_COLLISION_H
#define CLEAN_MAIN_FIELD_COLLISION_H

#include "autoload_2/vector.h"
#include "types.h"

#define COLLISION_UNIT_SHIFT 13
#define COLLISION_HALF_UNIT 0x1000
#define COLLISION_TYPE_COUNT 0x7c

#define COLLISION_GRID_SIZE 7
#define COLLISION_MAX_WALLS 24
#define COLLISION_MAX_FLOORS 40
#define COLLISION_MAX_POSTS 16
#define COLLISION_MAX_CONTACTS 2

/* The kinds of walls and posts. Kind 1 and kind 2 touches are kept apart in the contact flags;
 * a kind 3 wall pushes but records nothing. */
#define COLLISION_KIND_1 1
#define COLLISION_KIND_2 2
#define COLLISION_KIND_SILENT 3

/* CollisionContacts.flags. The wall bits say where a touched wall's normal points compared
 * with the actor's facing: AHEAD when it points back at the actor (the wall is in front),
 * BEHIND when it points the way the actor faces, SIDE_PLUS and SIDE_MINUS a quarter turn off
 * (the normal's angle minus the facing's opposite is about +0x4000 or -0x4000). */
#define COLLISION_ON_GROUND 0x0001   /* pushed up onto the ground's height */
#define COLLISION_BELOW_LIMIT 0x0002 /* CollisionGround_IsBelowLimit */
#define COLLISION_TOUCH_1 0x0004     /* touching a wall or post of kind other than 2 */
#define COLLISION_TOUCH_1_AHEAD 0x0008
#define COLLISION_TOUCH_1_SIDE_MINUS 0x0010
#define COLLISION_TOUCH_1_SIDE_PLUS 0x0020
#define COLLISION_TOUCH_1_BEHIND 0x0040
#define COLLISION_TOUCH_2 0x0080 /* touching a wall or post of kind 2 */
#define COLLISION_TOUCH_2_AHEAD 0x0100
#define COLLISION_TOUCH_2_SIDE_MINUS 0x0200
#define COLLISION_TOUCH_2_SIDE_PLUS 0x0400
#define COLLISION_TOUCH_2_BEHIND 0x0800
#define COLLISION_IN_CORNER 0x1000 /* two touches whose mean normal is about against the facing */
#define COLLISION_OPPOSITE 0x2000  /* two touches whose angles sum to 0 */

/* A point seen from above (NitroSDK-style 2D vector of X and Z). */
typedef struct CollisionPoint {
    fx32 x;
    fx32 z;
} CollisionPoint;

struct CollisionWall;
struct CollisionHandler;

/* The object a wall may name to be told when something touches it. */
typedef struct CollisionHandlerVtable {
    void (*touch)(struct CollisionHandler *handler, struct CollisionWall *wall, void *owner, fx32 radius);
} CollisionHandlerVtable;

typedef struct CollisionHandler {
    const CollisionHandlerVtable *vtable;
} CollisionHandler;

/* What a shape tells of itself: an attribute and an optional handler. */
typedef struct CollisionTag {
    u8 attr;
    u8 unk_01[3];
    CollisionHandler *handler;
} CollisionTag;

/* A line seen from above through `start` and `end`, with its unit `normal` and the line's
 * offset (-(normal . start)), so that normal . p + offset is a point's signed distance
 * (class vtable 0x020da1a4). */
typedef struct CollisionSegment {
    const void *vtable;
    CollisionPoint start;  /* 0x04 */
    CollisionPoint end;    /* 0x0c */
    CollisionPoint normal; /* 0x14 */
    fx32 offset;           /* 0x1c */
} CollisionSegment;

/* A wall: a segment up to a height (class vtable 0x020da210). */
typedef struct CollisionWall {
    CollisionSegment segment;
    CollisionTag tag; /* 0x20 */
    int kind;         /* 0x28 */
    fx32 top;         /* 0x2c: the height of its top */
} CollisionWall;

typedef struct CollisionWallList {
    CollisionWall walls[COLLISION_MAX_WALLS];
    u32 count; /* 0x480 */
} CollisionWallList;

/* A triangle with its normal and plane offset (class vtable 0x020da18c). */
typedef struct CollisionTriangle {
    const void *vtable;
    Vec3 corner[3]; /* 0x04 */
    Vec3 normal;    /* 0x28 */
    fx32 offset;    /* 0x34 */
} CollisionTriangle;

/* A floor triangle (class vtable 0x020da21c). */
typedef struct CollisionFloor {
    CollisionTriangle triangle;
    CollisionTag tag; /* 0x38 */
} CollisionFloor;

typedef struct CollisionFloorList {
    CollisionFloor floors[COLLISION_MAX_FLOORS];
    u32 count; /* 0xa00 */
} CollisionFloorList;

/* An upright cylinder standing on `position`. */
typedef struct CollisionPost {
    Vec3 position;
    fx32 radius;      /* 0x0c */
    fx32 height;      /* 0x10 */
    CollisionTag tag; /* 0x14 */
    int kind;         /* 0x1c */
    s16 unit_x;       /* 0x20 */
    s16 unit_z;       /* 0x22 */
} CollisionPost;

typedef struct CollisionPostList {
    u32 count;
    CollisionPost posts[COLLISION_MAX_POSTS]; /* 0x04 */
} CollisionPostList;

/* The object that tells which units hold a post (the map's at 0x120, else a default). */
struct CollisionPostSource;
typedef struct CollisionPostSourceVtable {
    const void *unk_00[2];
    int (*post_at)(struct CollisionPostSource *source, fx32 *radius, fx32 *height, int *kind, int x, int z); /* 0x08 */
} CollisionPostSourceVtable;

typedef struct CollisionPostSource {
    const CollisionPostSourceVtable *vtable;
} CollisionPostSource;

/* A unit of the grid: its sides' heights and attributes, north (low Z), west (low X), south,
 * east, and the unit's type. */
#define COLLISION_NORTH 0
#define COLLISION_WEST 1
#define COLLISION_SOUTH 2
#define COLLISION_EAST 3
typedef struct CollisionCell {
    fx32 side_height[4];
    u8 side_attr[4]; /* 0x10 */
    u8 type;         /* 0x14 */
    u8 unk_15[3];
} CollisionCell;

typedef struct CollisionCellGrid {
    CollisionCell cells[COLLISION_GRID_SIZE][COLLISION_GRID_SIZE];
    int min_x; /* 0x498 */
    int max_x;
    int min_z;
    int max_z;
} CollisionCellGrid;

/* Up to two touches of walls or posts in a frame. */
typedef struct CollisionContactList {
    s16 angle[COLLISION_MAX_CONTACTS]; /* the angle of the wall's normal, or from the post */
    u8 count;                          /* 0x04 */
    u8 unk_05[3];
    int attr[COLLISION_MAX_CONTACTS]; /* 0x08 */
    int kind[COLLISION_MAX_CONTACTS]; /* 0x10 */
} CollisionContactList;

/* What an actor's moves met (the field actor's at 0x7a4). */
typedef struct CollisionContacts {
    u32 previous_flags;
    u32 flags;                  /* 0x04: COLLISION_* bits */
    int ground_attr;            /* 0x08: the ground's attribute when pushed up onto it */
    CollisionContactList walls; /* 0x0c */
    Vec3 moved;                 /* 0x24: how far the move's checks moved the position */
} CollisionContacts;

/* The push-out visitor (vtable 0x020da1e8) that func_02031288 hands the lists to. */
typedef struct CollisionPushOut {
    const void *vtable;
    CollisionContacts *contacts; /* 0x04 */
    Vec3 *position;              /* 0x08 */
    Vec3 previous;               /* 0x0c */
    u16 facing;                  /* 0x18 */
    u8 unk_1A[2];
    fx32 radius; /* 0x1c */
    void *owner; /* 0x20: handed to the walls' handlers */
    u32 flags;   /* 0x24 */
} CollisionPushOut;

/* What the ground at a point is (func_02034270). */
typedef struct CollisionGround {
    u8 has_point; /* the unit is a corner slope; `point` is set */
    u8 unk_01[3];
    Vec3 point;    /* 0x04: the middle of the corner slope's edge */
    Vec3 position; /* 0x10: the point asked about */
    int unit_x;    /* 0x1c */
    int unit_z;    /* 0x20 */
    Vec3 normal;   /* 0x24: (0, 0, 1) turned about Y */
    int unk_30;    /* 0x30: byte 0x14 of the attribute's row, or 0 */
    int attr;      /* 0x34 */
    fx32 height;   /* 0x38 */
    fx32 limit;    /* 0x3c: -18.0, or -1.0 where unk_30 is not 0 */
} CollisionGround;

/* The start of the result of a segment test (func_020311bc). */
typedef struct CollisionSegmentHit {
    CollisionTag tag;
} CollisionSegmentHit;

/* A row of the table at 0x020c907c (0x1e bytes). */
typedef struct CollisionTypeInfo {
    u8 unk_00[0x0b];
    u8 normal_turns;     /* 0x0b: bit n turns the ground's normal by n eighths of a turn */
    u8 side_attr[4];     /* 0x0c: the attributes of a unit's sides */
    u8 side_attr_alt[4]; /* 0x10: the same in the other set */
    u8 unk_14;           /* 0x14 */
    u8 flat;             /* 0x15: the unit's top is one level, at its north side's height */
    u8 unk_16[6];
    s16 height; /* 0x1c: in 1/256 */
} CollisionTypeInfo;

int CollisionPushOut_Walls(CollisionPushOut *visitor, CollisionWallList *walls);
int CollisionSegmentHit_Destroy(CollisionSegmentHit *hit);
CollisionSegmentHit *CollisionSegmentHit_Construct(CollisionSegmentHit *hit);
void CollisionContacts_ClassifyWalls(CollisionContacts *contacts, int facing);
CollisionContacts *CollisionContacts_Destroy(CollisionContacts *contacts);
CollisionContacts *CollisionContacts_Construct(CollisionContacts *contacts);
void CollisionContacts_Clear(CollisionContacts *contacts);
int CollisionContacts_StartFrame(CollisionContacts *contacts);
int CollisionContactList_Add(CollisionContactList *list, s16 angle, int kind, int attr);
void CollisionContactList_Clear(CollisionContactList *list);
void CollisionContactList_Destroy(CollisionContactList *list);
int CollisionContactList_Construct(CollisionContactList *list);
void CollisionPosts_AddFences(CollisionPostList *posts, CollisionWallList *walls);
void CollisionPosts_Gather(CollisionPostList *posts, CollisionPostSource *source, int x0, int x1, int z0, int z1, int all);
int CollisionPosts_Add(CollisionPostList *posts, const Vec3 *position, fx32 radius, fx32 height, int kind, int attr);
int CollisionPosts_Land(CollisionPostList *posts, Vec3 *position, const Vec3 *previous, int *attr, u32 unused_mode,
                        int unused);
int CollisionPosts_PushOut(CollisionPostList *posts, Vec3 *position, fx32 radius, CollisionContacts *contacts, u32 unused_mode,
                           int unused);
void *CollisionPosts_Destroy(CollisionPostList *posts);
CollisionPostList *CollisionPosts_Construct(CollisionPostList *posts);
int CollisionPost_AddFence(CollisionPost *post, CollisionWallList *walls, CollisionPost *other);
void CollisionPost_Init(CollisionPost *post, const Vec3 *position, fx32 radius, fx32 height, int kind, int attr);
void *CollisionPost_Destroy(CollisionPost *post);
void *CollisionPost_Construct(CollisionPost *post);
void CollisionWalls_AddCliffs(CollisionWallList *walls, CollisionCellGrid *grid, int x0, int x1, int z0, int z1, int back);
void *CollisionWalls_AddWall(CollisionWallList *walls, const CollisionPoint *start, const CollisionPoint *end,
                             const CollisionPoint *normal, fx32 top, int kind, int attr, CollisionHandler *handler);
int CollisionWalls_Add(CollisionWallList *walls, const CollisionWall *wall);
int CollisionWalls_PushOut(CollisionWallList *walls, Vec3 *position, const Vec3 *previous, fx32 radius,
                           CollisionContacts *contacts, void *owner);
void *CollisionWalls_Destroy(CollisionWallList *walls);
void *CollisionWalls_Construct(CollisionWallList *walls);
int CollisionWall_Init(CollisionWall *wall, const CollisionPoint *start, const CollisionPoint *end,
                       const CollisionPoint *normal, fx32 top, int kind, int attr, CollisionHandler *handler);
int CollisionWall_Copy(CollisionWall *wall, const CollisionWall *from);
void CollisionWall_GetMiddle(CollisionPoint *middle, const CollisionWall *wall);
CollisionWall *CollisionWall_ConstructInit(CollisionWall *wall, const CollisionPoint *start, const CollisionPoint *end,
                                           const CollisionPoint *normal, fx32 top, int kind, int attr,
                                           CollisionHandler *handler);
CollisionWall *CollisionWall_Destroy(CollisionWall *wall);
void *CollisionWall_Construct(CollisionWall *wall);
int CollisionFloors_Add(CollisionFloorList *floors, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal, int attr,
                        CollisionHandler *handler);
void CollisionFloors_AddCells(CollisionFloorList *floors, CollisionCellGrid *grid, int x0, int x1, int z0, int z1);
int CollisionFloors_Destroy(CollisionFloorList *floors);
CollisionFloorList *CollisionFloors_Construct(CollisionFloorList *floors);
int CollisionFloor_Init(CollisionFloor *floor, const Vec3 *a, const Vec3 *b, const Vec3 *c, const Vec3 *normal, int attr,
                        CollisionHandler *handler);
void *CollisionFloor_Destroy(CollisionFloor *floor);
void *CollisionFloor_Construct(CollisionFloor *floor);
void CollisionGround_Query(CollisionGround *ground, const Vec3 *position, int alternate, int mode);
void CollisionGround_SetSlopeNormal(CollisionGround *ground, int from, int level, int angle);
int CollisionGround_IsBelowLimit(const CollisionGround *ground, fx32 y);
fx32 CollisionGround_GetLimit(const CollisionGround *ground);
fx32 CollisionGround_GetHeight(const CollisionGround *ground, int with_post);
void CollisionGround_Destroy(CollisionGround *ground);
int CollisionGround_InitAtUnit(CollisionGround *ground, int x, int z, int alternate, int mode);
int CollisionGround_Init(CollisionGround *ground, const Vec3 *position, int alternate, int mode);
void CollisionTag_Copy(CollisionTag *tag, const CollisionTag *from);
void CollisionTag_Set(CollisionTag *tag, int attr, CollisionHandler *handler);
void CollisionTag_Destroy(CollisionTag *tag);
void CollisionHitTag_Destroy(CollisionTag *tag);
void CollisionHitTag_Clear(CollisionTag *tag);
void CollisionTag_Clear(CollisionTag *tag);
int CollisionMaps_SetIndex(int *index, int value);
CollisionCell *CollisionCellGrid_Get(CollisionCellGrid *grid, int x, int z);
void CollisionCellGrid_Load(CollisionCellGrid *grid, int x0, int x1, int z0, int z1, int alternate);
void CollisionCell_Construct(CollisionCell *cell);

#endif
