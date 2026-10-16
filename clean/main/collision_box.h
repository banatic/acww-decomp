/* Collision boxes: upright boxes that objects of the overlays put on the field (a room object's
 * push box, the ATM). A box is a C++ object (0x9c bytes, class vtable 0x020da1b4) kept in the
 * list at data_021c30e4 while it is in the world; a gathering of the field's collision
 * (CollisionQuery_Gather) adds the sides of the boxes near its box as walls and their tops as
 * floors, each naming the box as its handler (field_collision.h, CollisionHandler), so that the
 * box's one virtual method is told when an actor runs into one of its sides.
 *
 * A box stands on `position`, turned by `angle` about Y and scaled by `scale`; before that it
 * is `width` along X, `depth` along Z and `height` high. Its corners (the corners of its top,
 * in the world) and the bounds around them are worked out each time it moves
 * (CollisionBox_Place). A box of no width or no depth is flat: one side, seen from both faces.
 *
 * Positions are 20.12 fixed point; angles are 16-bit fractions of a turn. */
#ifndef CLEAN_MAIN_COLLISION_BOX_H
#define CLEAN_MAIN_COLLISION_BOX_H

#include "autoload_2/vector.h"
#include "field_collision.h"
#include "types.h"

#define COLLISION_BOX_CORNERS 4
/* The corners of a flat box. */
#define COLLISION_BOX_FLAT_CORNERS 2
/* What a box's sides and top are, as walls and floors. */
#define COLLISION_BOX_KIND COLLISION_KIND_1
#define COLLISION_BOX_ATTR 1

typedef struct CollisionBox {
    const void *vtable; /* data_020da1b4 */
    Vec3 position;      /* 0x04: the middle of its bottom */
    fx32 width;         /* 0x10: along X before turning */
    fx32 depth;         /* 0x14: along Z before turning */
    fx32 height;        /* 0x18 */
    Vec3 scale;         /* 0x1c */
    s16 angle;          /* 0x28 */
    /* 0x2a: 4, 2 for a flat box, 0 before it was first placed */
    s16 corner_count;
    struct CollisionBox *next;                         /* 0x2c: the next box of the list */
    Vec3 corners[COLLISION_BOX_CORNERS];               /* 0x30: side n goes from corner n to n + 1 */
    CollisionPoint side_normal[COLLISION_BOX_CORNERS]; /* 0x60: the outward normal of side n */
    Vec3 centre;                                       /* 0x80: the middle of the corners' bounds */
    Vec3 half;                                         /* 0x8c: half the size of those bounds */
    u8 active;                                         /* 0x98: set by CollisionBox_Init */
    u8 unk_99[3];
} CollisionBox;

void CollisionBox_KeepMin(Vec3 *bound, const Vec3 *point);
void CollisionBox_KeepMax(Vec3 *bound, const Vec3 *point);
void CollisionBox_GatherAll(void *list, const Vec3 *centre, const Vec3 *half, CollisionWallList *walls,
                            CollisionFloorList *floors, int flags, int pass);
int CollisionBox_SideOutside(const Vec3 *centre, const Vec3 *half, const Vec3 *start, const Vec3 *end);
int CollisionBox_Remove(CollisionBox *box);
int CollisionBox_Add(CollisionBox *box, fx32 width, fx32 depth, fx32 height, const Vec3 *position, s16 angle,
                     const Vec3 *scale);
int CollisionBox_Place(CollisionBox *box, const Vec3 *position, s16 angle, const Vec3 *scale);
void CollisionBox_ClearList(void *list);
void CollisionBox_ListDestruct(void *list);
void CollisionBox_ListConstruct(void *list);
void CollisionBox_IgnoreHit(void);
int CollisionBox_Init(CollisionBox *box, fx32 width, fx32 depth, fx32 height, const Vec3 *position, s16 angle,
                      const Vec3 *scale);
CollisionBox *CollisionBox_DestructBase(CollisionBox *box);
CollisionBox *CollisionBox_Destruct(CollisionBox *box);
CollisionBox *CollisionBox_Construct(CollisionBox *box);
CollisionPoint *CollisionBox_ConstructNormal(CollisionPoint *normal);
CollisionBox *CollisionBox_ConstructBase(CollisionBox *box);
void CollisionBox_Reset(CollisionBox *box);

#endif
