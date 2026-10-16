/* Collision boxes (collision_box.h). */
#include "collision_box.h"

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "collision_query.h"
#include "collision_segment.h"
#include "itcm/vector.h"

static_assert(sizeof(CollisionBox) == 0x9c, "collision box");
static_assert(offsetof(CollisionBox, next) == 0x2c && offsetof(CollisionBox, side_normal) == 0x60 &&
                  offsetof(CollisionBox, active) == 0x98,
              "collision box fields");

/* The boxes in the world, the last one added first. */
extern CollisionBox *data_021c30e4;
/* The class vtable of a box. */
extern const u8 data_020da1b4[];
/* The matrix the corners are turned with. */
extern Mtx43 data_021fbe48;
/* (0, 1.0, 0): the normal of a box's top. */
extern Vec3 data_021c317c;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void MTX_MultVec43(const Vec3 *vec, const Mtx43 *mtx, Vec3 *dst);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* The members' constructors and destructors, as the game hands them to the array helpers: the
 * corners' (which do nothing) and the side normals' (CollisionBox_ConstructNormal and
 * CollisionPoint_Destruct). */
extern void func_020012e8(void *corner);
extern void func_020012dc(void *corner);
extern void func_0202f2f0(void *normal);
extern void *func_02032550(void *normal);

/* The scale a box gets when it is added without one (1.0 on each axis). */
#define COLLISION_BOX_UNIT_SCALE 0x1000
/* Side n's normal is (0, 1.0) turned by the box's angle and n quarter turns. */
#define COLLISION_BOX_QUARTER_TURN 0x4000

/* func_02031e08: `*bound` becomes the smaller of itself and `point`, axis by axis. */
void CollisionBox_KeepMin(Vec3 *bound, const Vec3 *point)
{
    if (point->x < bound->x) {
        bound->x = point->x;
    }
    if (point->y < bound->y) {
        bound->y = point->y;
    }
    if (point->z < bound->z) {
        bound->z = point->z;
    }
}
CLEAN_AS(func_02031e08, CollisionBox_KeepMin)

/* func_02031e28: `*bound` becomes the larger of itself and `point`, axis by axis. */
void CollisionBox_KeepMax(Vec3 *bound, const Vec3 *point)
{
    if (point->x > bound->x) {
        bound->x = point->x;
    }
    if (point->y > bound->y) {
        bound->y = point->y;
    }
    if (point->z > bound->z) {
        bound->z = point->z;
    }
}
CLEAN_AS(func_02031e28, CollisionBox_KeepMax)

/* func_02031ecc: adds the boxes whose bounds overlap (seen from above) the box of `centre` and
 * half size `half`: with COLLISION_QUERY_WALLS their sides as walls to `walls` (those not
 * wholly outside that box, CollisionBox_SideOutside), up to the box's scaled height above its
 * position, and with COLLISION_QUERY_GROUND their tops as two floor triangles to `floors`.
 * Each wall and floor has kind and attribute 1 and the box as handler. Pass 0 takes the boxes
 * standing above height 0, pass 1 the others. `list` is not read.
 * QUIRK: a flat box's top is two triangles with a repeated corner.
 * REQUIRES: a box has at most four corners (corner_count is 0, 2 or 4). */
void CollisionBox_GatherAll(void *list, const Vec3 *centre, const Vec3 *half, CollisionWallList *walls,
                            CollisionFloorList *floors, int flags, int pass)
{
    (void) list;
    for (CollisionBox *box = data_021c30e4; box != NULL; box = box->next) {
        int above = box->position.y > 0;
        if (pass == 0 ? !above : above) {
            continue;
        }

        Vec3 box_centre = box->centre;
        Vec3 offset;
        Vec_Subtract(&offset, &box_centre, centre);
        fx32 dx = offset.x < 0 ? -offset.x : offset.x;
        if (dx >= box->half.x + half->x) {
            continue;
        }
        fx32 dz = offset.z < 0 ? -offset.z : offset.z;
        if (dz >= box->half.z + half->z) {
            continue;
        }

        if ((flags & COLLISION_QUERY_WALLS) != 0) {
            u8 outside[COLLISION_BOX_CORNERS];
            int mask = box->corner_count - 1;
            for (int i = 0; i < box->corner_count; i++) {
                outside[i] =
                    (u8) CollisionBox_SideOutside(centre, half, &box->corners[i & mask], &box->corners[(i + 1) & mask]);
            }
            fx32 top = box->position.y + FX_MulFunc(box->height, box->scale.y);
            for (int i = 0; i < box->corner_count; i++) {
                if (outside[i & 3] != 0) {
                    continue;
                }
                const Vec3 *from = &box->corners[i & mask];
                const Vec3 *to = &box->corners[(i + 1) & mask];
                CollisionPoint start;
                CollisionPoint end;
                CollisionWall wall;
                CollisionPoint_Set(&start, from->x, from->z);
                CollisionPoint_Set(&end, to->x, to->z);
                CollisionWall_ConstructInit(&wall, &start, &end, &box->side_normal[i & mask], top, COLLISION_BOX_KIND,
                                            COLLISION_BOX_ATTR, (CollisionHandler *) box);
                CollisionWalls_Add(walls, &wall);
                CollisionWall_Destroy(&wall);
            }
        }

        if ((flags & COLLISION_QUERY_GROUND) != 0) {
            int last = box->corner_count - 1;
            CollisionFloors_Add(floors, &box->corners[0], &box->corners[last & 1], &box->corners[last & 3], &data_021c317c,
                                COLLISION_BOX_ATTR, (CollisionHandler *) box);
            CollisionFloors_Add(floors, &box->corners[last & 1], &box->corners[last & 2], &box->corners[last & 3],
                                &data_021c317c, COLLISION_BOX_ATTR, (CollisionHandler *) box);
        }
    }
}
CLEAN_AS(func_02031ecc, CollisionBox_GatherAll)

/* Which sides of the box from `min` to `max` (seen from above) `point` is past: 1 low X, 2 high
 * X, 4 low Z, 8 high Z. */
static int collision_box_outcode(const Vec3 *point, const Vec3 *min, const Vec3 *max)
{
    int code = 0;
    if (point->x < min->x) {
        code |= 1;
    } else if (point->x > max->x) {
        code |= 2;
    }
    if (point->z < min->z) {
        code |= 4;
    } else if (point->z > max->z) {
        code |= 8;
    }
    return code;
}

/* func_020320e0: whether the side from `start` to `end` is wholly outside the box of `centre`
 * and half size `half` seen from above, both ends being past the same one of its four sides.
 * The test is cautious: ends past the same corner (past two sides at once) or past different
 * sides do not count, though such a side may miss the box too. */
int CollisionBox_SideOutside(const Vec3 *centre, const Vec3 *half, const Vec3 *start, const Vec3 *end)
{
    Vec3 min;
    Vec3 max;
    Vec_Subtract(&min, centre, half);
    Vec_Add(&max, centre, half);

    int start_code = collision_box_outcode(start, &min, &max);
    if (start_code == 0) {
        return 0;
    }
    int end_code = collision_box_outcode(end, &min, &max);
    if (end_code == 0) {
        return 0;
    }
    int common = start_code & end_code;
    return common == 1 || common == 2 || common == 4 || common == 8;
}
CLEAN_AS(func_020320e0, CollisionBox_SideOutside)

/* func_02032180: takes `box` out of the list and resets it; whether it was in the list. */
int CollisionBox_Remove(CollisionBox *box)
{
    CollisionBox *previous = NULL;
    for (CollisionBox *current = data_021c30e4; current != NULL; current = current->next) {
        if (current == box) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                data_021c30e4 = current->next;
            }
            CollisionBox_Reset(box);
            return 1;
        }
        previous = current;
    }
    return 0;
}
CLEAN_AS(func_02032180, CollisionBox_Remove)

/* func_020321bc: sets `box` up (CollisionBox_Init; `scale` NULL for 1.0 on each axis) and puts
 * it at the head of the list; 1. */
int CollisionBox_Add(CollisionBox *box, fx32 width, fx32 depth, fx32 height, const Vec3 *position, s16 angle,
                     const Vec3 *scale)
{
    Vec3 used = {COLLISION_BOX_UNIT_SCALE, COLLISION_BOX_UNIT_SCALE, COLLISION_BOX_UNIT_SCALE};
    if (scale != NULL) {
        used = *scale;
    }
    if (CollisionBox_Init(box, width, depth, height, position, angle, &used) != 0) {
        box->next = data_021c30e4;
        data_021c30e4 = box;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020321bc, CollisionBox_Add)

/* Turns corner `corner` (in the box's own space) into the world as side `side`'s start and
 * works out that side's normal; the first corner of the box starts the bounds. */
static void collision_box_place_corner(const Vec3 *corner, Vec3 *world, CollisionPoint *normal, int side, int first, Vec3 *max,
                                       Vec3 *min, s16 angle)
{
    MTX_MultVec43(corner, &data_021fbe48, world);
    if (first) {
        *max = *world;
        *min = *world;
    } else {
        CollisionBox_KeepMax(max, world);
        CollisionBox_KeepMin(min, world);
    }
    CollisionPoint_Set(normal, 0, 0x1000);
    CollisionPoint_RotateY(normal, (s16) (angle + side * COLLISION_BOX_QUARTER_TURN));
}

/* func_02032214: moves `box` to `position`, turned by `angle` and scaled by `scale`: its
 * corners in the world (by the matrix data_021fbe48), its sides' normals and the bounds of its
 * corners. Nothing is done, and the result is 0, when none of the three changed; else 1.
 * A box of no width or no depth gets two corners only, the ends of its one side (along X when
 * it has no depth, else along Z). */
int CollisionBox_Place(CollisionBox *box, const Vec3 *position, s16 angle, const Vec3 *scale)
{
    if (angle == box->angle && Vec_Differ(&box->position, position) == 0 && Vec_Differ(&box->scale, scale) == 0) {
        return 0;
    }

    box->position = *position;
    box->scale = *scale;
    box->angle = angle;

    fx32 half_width = box->width >> 1;
    fx32 half_depth = box->depth >> 1;
    fx32 height = box->height;
    Vec3 local[COLLISION_BOX_CORNERS] = {
        {-half_width, height, half_depth},
        {half_width, height, half_depth},
        {half_width, height, -half_depth},
        {-half_width, height, -half_depth},
    };

    Mtx43_Translation(&data_021fbe48, position->x, position->y, position->z);
    Mtx43_RotateY(&data_021fbe48, angle);
    Mtx43_Scale(&data_021fbe48, scale->x, scale->y, scale->z);

    Vec3 max;
    Vec3 min;
    if (box->width == 0 || box->depth == 0) {
        /* The corners 1 and 3 (a side along Z), or 0 and 2 without depth (a side along X). */
        int odd = box->depth == 0 ? 0 : 1;
        int n = 0;
        box->corner_count = COLLISION_BOX_FLAT_CORNERS;
        for (int i = 0; i < COLLISION_BOX_CORNERS; i++) {
            if ((i & 1) == odd) {
                collision_box_place_corner(&local[i], &box->corners[n], &box->side_normal[n], i, i == odd, &max, &min, angle);
                n++;
            }
        }
    } else {
        box->corner_count = COLLISION_BOX_CORNERS;
        for (int i = 0; i < box->corner_count; i++) {
            collision_box_place_corner(&local[i], &box->corners[i], &box->side_normal[i], i, i == 0, &max, &min, angle);
        }
    }

    box->centre.x = (max.x + min.x) >> 1;
    box->centre.y = (max.y + min.y) >> 1;
    box->centre.z = (max.z + min.z) >> 1;
    box->half.x = max.x - box->centre.x;
    box->half.y = max.y - box->centre.y;
    box->half.z = max.z - box->centre.z;
    return 1;
}
CLEAN_AS(func_02032214, CollisionBox_Place)

/* func_0203242c: empties the list. `list` (the world's byte at 0x1a90) is not read. */
void CollisionBox_ClearList(void *list)
{
    (void) list;
    data_021c30e4 = NULL;
}
CLEAN_AS(func_0203242c, CollisionBox_ClearList)

/* func_02032438: the list object's destructor; nothing to do. */
void CollisionBox_ListDestruct(void *list)
{
    (void) list;
}
CLEAN_AS(func_02032438, CollisionBox_ListDestruct)

/* func_0203243c: the list object's constructor; nothing to do. */
void CollisionBox_ListConstruct(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203243c, CollisionBox_ListConstruct)

/* func_02032440: the box's virtual method (slot 0), called when an actor runs into one of its
 * sides; a plain box does nothing (the room objects' push box overrides it). */
void CollisionBox_IgnoreHit(void) {}
CLEAN_AS(func_02032440, CollisionBox_IgnoreHit)

/* func_02032444: gives `box` its size and places it (CollisionBox_Place), then sets its
 * position, angle and scale again and marks it active; 1.
 * QUIRK: a box first placed where a reset box stands (position 0, angle 0, scale 1.0) keeps
 * no corners, CollisionBox_Place seeing nothing changed. */
int CollisionBox_Init(CollisionBox *box, fx32 width, fx32 depth, fx32 height, const Vec3 *position, s16 angle,
                      const Vec3 *scale)
{
    box->width = width;
    box->depth = depth;
    box->height = height;
    CollisionBox_Place(box, position, angle, scale);
    box->position = *position;
    box->scale = *scale;
    box->angle = angle;
    box->active = 1;
    return 1;
}
CLEAN_AS(func_02032444, CollisionBox_Init)

/* Puts the class vtable in and destroys the members, the side normals first. */
static CollisionBox *collision_box_destruct(CollisionBox *box)
{
    box->vtable = data_020da1b4;
    __cxa_vec_cleanup(box->side_normal, COLLISION_BOX_CORNERS, sizeof(CollisionPoint), func_0202f2f0);
    __cxa_vec_cleanup(box->corners, COLLISION_BOX_CORNERS, sizeof(Vec3), func_020012dc);
    return box;
}

/* func_0203248c: a box's destructor (the room objects' push box calls this one). */
CollisionBox *CollisionBox_DestructBase(CollisionBox *box)
{
    return collision_box_destruct(box);
}
CLEAN_AS(func_0203248c, CollisionBox_DestructBase)

/* func_020324c4: the same as CollisionBox_DestructBase (the ATM calls this one). */
CollisionBox *CollisionBox_Destruct(CollisionBox *box)
{
    return collision_box_destruct(box);
}
CLEAN_AS(func_020324c4, CollisionBox_Destruct)

/* Puts the class vtable in, builds the members and resets the box. */
static CollisionBox *collision_box_construct(CollisionBox *box)
{
    box->vtable = data_020da1b4;
    __cxa_vec_ctor(box->corners, COLLISION_BOX_CORNERS, sizeof(Vec3), func_020012e8, func_020012dc);
    __cxa_vec_ctor(box->side_normal, COLLISION_BOX_CORNERS, sizeof(CollisionPoint),
                   (void (*)(void *))(uintptr_t) func_02032550, func_0202f2f0);
    CollisionBox_Reset(box);
    return box;
}

/* func_020324fc: a box's constructor (the ATM calls this one). */
CollisionBox *CollisionBox_Construct(CollisionBox *box)
{
    return collision_box_construct(box);
}
CLEAN_AS(func_020324fc, CollisionBox_Construct)

/* func_02032550: a side normal's constructor: (0, 0). */
CollisionPoint *CollisionBox_ConstructNormal(CollisionPoint *normal)
{
    CollisionPoint_Set(normal, 0, 0);
    return normal;
}
CLEAN_AS(func_02032550, CollisionBox_ConstructNormal)

/* func_02032564: the same as CollisionBox_Construct (the room objects' push box calls this
 * one). */
CollisionBox *CollisionBox_ConstructBase(CollisionBox *box)
{
    return collision_box_construct(box);
}
CLEAN_AS(func_02032564, CollisionBox_ConstructBase)

/* func_020325b8: a box with no corners, no size, scale 1.0, at 0, out of any list and not
 * active. */
void CollisionBox_Reset(CollisionBox *box)
{
    box->corner_count = 0;
    box->position.x = 0;
    box->position.y = 0;
    box->position.z = 0;
    box->width = 0;
    box->depth = 0;
    box->height = 0;
    box->scale.x = COLLISION_BOX_UNIT_SCALE;
    box->scale.y = COLLISION_BOX_UNIT_SCALE;
    box->scale.z = COLLISION_BOX_UNIT_SCALE;
    box->angle = 0;
    box->next = NULL;
    box->active = 0;
    for (int i = 0; i < COLLISION_BOX_CORNERS; i++) {
        box->corners[i].x = 0;
        box->corners[i].y = 0;
        box->corners[i].z = 0;
        CollisionPoint_Set(&box->side_normal[i], 0, 0);
    }
}
CLEAN_AS(func_020325b8, CollisionBox_Reset)
