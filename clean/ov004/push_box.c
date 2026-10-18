/* The box a room object pushes back with (push_box.h). */
#include "push_box.h"

#include <assert.h>
#include <stddef.h>

#include "autoload_2/fx_math.h" /* Math_Atan2 */
#include "autoload_2/matrix.h"  /* Mtx43_RotY */
#include "clean.h"
#include "room_object.h"
#include "main/collision_box.h"
#include "main/collision_segment.h"
#include "main/field_collision.h"
#include "main/session_players.h"
#include "room_object_body.h"
#include "room_object_map.h"
#include "room_objects.h"
#include "room_pushes.h"

static_assert(offsetof(PushingActor, position) == 0x5c, "actor position");
static_assert(offsetof(PushingActor, unk_68) == 0x68, "actor point");
static_assert(offsetof(PushingActor, angle) == 0x8e, "actor angle");
static_assert(offsetof(PushBox, owner) == 0x9c, "box owner");
static_assert(sizeof(PushBox) == 0xa0, "box");

#define ONE 0x1000            /* 1 in 20.12 fixed point */
#define CELL 0x2000           /* the side of a cell of the map */
#define HALF_TURN 0x8000      /* an angle (fx_math.h) */
#define FACING_LIMIT 0x1700   /* how far from straight at the side the actor may face */
#define SIDE_MARGIN 0x666     /* how far from either end of the side the actor must be */
#define LONG_SIDE 0x3000      /* sides longer than this are pushed at a point near the actor */
#define PLAYER 4              /* the actor SessionPlayers_ActorOf is asked for */
#define LAYER_FLOOR 0         /* the object stands on the floor */
#define LAYER_ON_TOP 1        /* the object stands on another one */
#define FOOTPRINT_TWO_CELLS 1 /* unk_784 of an object whose pivot can be at either end */

/* The vtable of this class. */
extern const u8 data_ov004_0224fe0c[];

/* The function-local statics of PushBox_SettlePivot: three guards, the vectors and their
 * records in the C++ runtime's list of objects to destroy. */
extern u32 data_ov004_02256c80;
extern u32 data_ov004_02256c64;
extern u32 data_ov004_02256c8c;
extern Vec3 data_ov004_02256e28[2]; /* the two pivots: (0, 0, 0) and (-CELL, 0, 0) */
extern Vec3 data_ov004_02256e40[2]; /* the object's two ends: (0, 0, 0) and (CELL, 0, 0) */
extern Vec3 data_ov004_02256db0;    /* one cell along the object's X axis: (CELL, 0, 0) */
extern u8 data_ov004_02256cc0[];
extern u8 data_ov004_02256d08[];
extern u8 data_ov004_02256d5c[];
extern u8 data_ov004_02256d68[];
extern u8 data_ov004_02256da4[];

/* The scratch matrix of overlay 4's objects. */
extern Mtx43 data_021fbe48;

extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020012dc(void *object);
extern void MTX_MultVec43(const Vec3 *vector, const Mtx43 *mtx, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *difference);

extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static void set_vec(Vec3 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* The distance between two points on the ground.
 * QUIRK: the squared distance is cut to 32 bits before the square root. */
static fx32 distance2(const CollisionPoint *a, const CollisionPoint *b)
{
    return FX_Sqrt((s32) CollisionPoint_DistanceSquared(a, b));
}

/* func_ov004_0220dbac: for an object two cells long, puts its pivot at the end nearer the
 * actor, moving its position by a cell so that it stays where it was.
 * QUIRK: the first call builds the three function-local static vectors and registers them for
 * destruction (TrivialObject_Destruct, which does nothing). */
void PushBox_SettlePivot(PushBox *box, PushingActor *actor)
{
    if (box->owner->unk_784 != FOOTPRINT_TWO_CELLS) {
        return;
    }
    if ((data_ov004_02256c80 & 1) == 0) {
        set_vec(&data_ov004_02256e28[0], 0, 0, 0);
        __register_global_object(&data_ov004_02256e28[0], (void *) func_020012dc, data_ov004_02256cc0);
        set_vec(&data_ov004_02256e28[1], -CELL, 0, 0);
        __register_global_object(&data_ov004_02256e28[1], (void *) func_020012dc, data_ov004_02256d08);
        data_ov004_02256c80 |= 1;
    }
    if ((data_ov004_02256c64 & 1) == 0) {
        set_vec(&data_ov004_02256e40[0], 0, 0, 0);
        __register_global_object(&data_ov004_02256e40[0], (void *) func_020012dc, data_ov004_02256d5c);
        set_vec(&data_ov004_02256e40[1], CELL, 0, 0);
        __register_global_object(&data_ov004_02256e40[1], (void *) func_020012dc, data_ov004_02256d68);
        data_ov004_02256c64 |= 1;
    }
    if ((data_ov004_02256c8c & 1) == 0) {
        set_vec(&data_ov004_02256db0, CELL, 0, 0);
        __register_global_object(&data_ov004_02256db0, (void *) func_020012dc, data_ov004_02256da4);
        data_ov004_02256c8c |= 1;
    }

    RoomObject *owner = box->owner;
    Mtx43_RotY(&data_021fbe48, owner->angle);
    Vec3 step;
    MTX_MultVec43(&data_ov004_02256db0, &data_021fbe48, &step);

    Vec3 end;
    RoomObject_ToWorld(owner, &end, &data_ov004_02256e40[0]);
    fx32 to_first = Vec_Distance(&actor->position, &end);
    RoomObject_ToWorld(owner, &end, &data_ov004_02256e40[1]);
    if (to_first < Vec_Distance(&actor->position, &end)) {
        if (Vec_Differ(&owner->pivot, &data_ov004_02256e28[0])) {
            owner->pivot = data_ov004_02256e28[0];
            VEC_Subtract(&owner->position, &step, &owner->position);
        }
    } else {
        if (Vec_Differ(&owner->pivot, &data_ov004_02256e28[1])) {
            owner->pivot = data_ov004_02256e28[1];
            VEC_Add(&owner->position, &step, &owner->position);
        }
    }
}
CLEAN_AS(func_ov004_0220dbac, PushBox_SettlePivot)

/* func_ov004_0220dd80 (the box's virtual function): when the player runs into `side` of its
 * idle owner, facing the side within FACING_LIMIT, at least SIDE_MARGIN from either end,
 * starts a push of the owner. The player is to stand `standoff` out from the side's middle, or
 * for a side longer than LONG_SIDE from the point it hit, kept between one and three units from
 * the side's start. The side pushed (Angle_Side) is the side's angle relative to the
 * owner, or for an owner standing on another object, relative to that object's angle and the
 * owner's angle on it. */
void PushBox_OnSideHit(PushBox *box, CollisionWall *side, PushingActor *actor, fx32 standoff)
{
    PushingActor *player = SessionPlayers_ActorOf(PLAYER);
    if (actor == NULL || actor != player) {
        return;
    }
    if (box->owner == NULL) {
        return;
    }
    if (!RoomObject_IsInState(box->owner, ROOM_OBJECT_IDLE)) {
        return;
    }

    int angle = Math_Atan2(side->segment.normal.x, side->segment.normal.z);
    int facing = angle + HALF_TURN; /* the way into the side */
    u16 difference = (u16) (facing - actor->angle);
    Vec3 from = actor->unk_68;
    CollisionPoint a;
    CollisionPoint b;
    CollisionPoint crossing;
    CollisionPoint_Set(&a, from.x, from.z);
    CollisionPoint_Set(&b, from.x + side->segment.normal.x, from.z + side->segment.normal.z);
    CollisionPoint_Set(&crossing, 0, 0);
    if (!(difference < FACING_LIMIT || difference > 0x10000 - FACING_LIMIT)) {
        return;
    }
    if (!CollisionSegment_Intersect(&side->segment, &crossing, &a, &b)) {
        return;
    }
    fx32 along = distance2(&side->segment.start, &crossing);
    fx32 length = distance2(&side->segment.start, &side->segment.end);
    if (along < SIDE_MARGIN || along > length - SIDE_MARGIN) {
        return;
    }
    if (!CollisionSegment_SpansPoint(&side->segment, &crossing)) {
        return;
    }

    CollisionPoint middle;
    CollisionWall_GetMiddle(&middle, side);
    Vec3 centre;
    centre.z = middle.z + FX_MulFunc(side->segment.normal.z, standoff);
    centre.x = middle.x + FX_MulFunc(side->segment.normal.x, standoff);
    centre.y = 0;
    Vec3 destination = centre;
    if (length > LONG_SIDE) {
        if (along < ONE) {
            CollisionPoint direction;
            CollisionPoint_Difference(&direction, &side->segment.end, &side->segment.start);
            CollisionPoint_Normalize(&direction);
            crossing.x = side->segment.start.x + FX_MulFunc(direction.x, ONE);
            crossing.z = side->segment.start.z + FX_MulFunc(direction.z, ONE);
        } else if (along > LONG_SIDE) {
            CollisionPoint direction;
            CollisionPoint_Difference(&direction, &side->segment.end, &side->segment.start);
            CollisionPoint_Normalize(&direction);
            crossing.x = side->segment.start.x + FX_MulFunc(direction.x, LONG_SIDE);
            crossing.z = side->segment.start.z + FX_MulFunc(direction.z, LONG_SIDE);
        }
        destination.z = crossing.z + FX_MulFunc(side->segment.normal.z, standoff);
        destination.x = crossing.x + FX_MulFunc(side->segment.normal.x, standoff);
        destination.y = 0;
    }

    PushBox_SettlePivot(box, actor);
    int index = RoomObjects_IndexOf(RoomObjects_Table(), box->owner);
    s16 relative = (s16) (angle - box->owner->angle);
    if (RoomObject_Layer(box->owner) == LAYER_ON_TOP) {
        Vec3 owner_centre;
        RoomObject_Centre(box->owner, &owner_centre);
        RoomObject *below = RoomObjects_GridObjectAtPoint(RoomObjects_Grid(), &owner_centre, LAYER_FLOOR);
        if (below != NULL) {
            relative = (s16) (angle - below->angle - Mount_Angle(&box->owner->mount));
        }
    }
    int pushed_side = Angle_Side(relative);
    RoomPushes_Record(RoomPushes_Records(), index, &actor->unk_68, &actor->position, standoff, &centre, &destination,
                      (s16) facing, pushed_side);
}
CLEAN_AS(func_ov004_0220dd80, PushBox_OnSideHit)

/* func_ov004_0220dfe0: no owner (the box was taken out of the world). */
void PushBox_ClearOwner(PushBox *box)
{
    box->owner = NULL;
}
CLEAN_AS(func_ov004_0220dfe0, PushBox_ClearOwner)

/* func_ov004_0220dfe8 */
void PushBox_SetOwner(PushBox *box, RoomObject *owner)
{
    box->owner = owner;
}
CLEAN_AS(func_ov004_0220dfe8, PushBox_SetOwner)

/* func_ov004_0220dff0 */
PushBox *PushBox_Destruct(PushBox *box)
{
    box->base.vtable = data_ov004_0224fe0c;
    CollisionBox_DestructBase(&box->base);
    return box;
}
CLEAN_AS(func_ov004_0220dff0, PushBox_Destruct)

/* func_ov004_0220e008 */
PushBox *PushBox_Construct(PushBox *box)
{
    CollisionBox_ConstructBase(&box->base);
    box->base.vtable = data_ov004_0224fe0c;
    PushBox_ClearOwner(box);
    return box;
}
CLEAN_AS(func_ov004_0220e008, PushBox_Construct)
