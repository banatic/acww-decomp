/* The room's two pushes (room_pushes.h). */
#include "room_pushes.h"

#include "clean.h"
#include "main/scene_kinds.h"
#include "main/scene_query.h"
#include "autoload_2/vector.h"
#include "main/furniture_info.h"
#include "room_object.h"
#include "room_object_body.h"
#include "room_object_map.h"
#include "room_objects.h"
#include "room_manager.h"

static_assert(sizeof(RoomPush) == 0x40, "push");
static_assert(offsetof(RoomPush, standoff) == 0x1c, "standoff");
static_assert(offsetof(RoomPush, facing) == 0x38, "facing");
static_assert(offsetof(RoomPush, side) == 0x3c, "side");

/* The C++ constructor and destructor of the array's elements (RoomPushes_ConstructOne and
 * RoomPushes_DestructOne), handed to the C++ runtime. */
extern void func_ov004_0223cbe4(void *push);
extern void func_ov004_0223cbe0(void *push);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

/* func_ov004_0223c700: whether objects may be pushed (RoomPushes_Enabled), or the scene is
 * 0x1f, 0x21 or 0x22. */
int RoomPushes_Allowed(void)
{
    if (RoomPushes_Enabled() != 0) {
        return 1;
    }
    switch (SceneQuery_Current()) {
        case 0x1f:
        case 0x21:
        case 0x22:
            return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c700, RoomPushes_Allowed)

/* func_ov004_0223c72c: unless RoomManager_ShopMode says no, whether the scene is a house's room
 * (SceneKinds_CurrentIsHouseRoom) or of kind 11 (SceneQuery_CurrentIn11). */
int RoomPushes_Enabled(void)
{
    if (RoomManager_ShopMode() != 0) {
        return 0;
    }
    if (SceneKinds_CurrentIsHouseRoom() != 0 || SceneQuery_CurrentIn11() != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c72c, RoomPushes_Enabled)

/* func_ov004_0223c758: records a push of the object of index `object` (not -1) in the record
 * of its layer (RoomObject_Layer, its low bit); whether the object was there. */
int RoomPushes_Record(RoomPush *pushes, s32 object, Vec3 *from, Vec3 *position, s32 standoff, Vec3 *centre, Vec3 *destination,
                      short facing, s32 side)
{
    if (object == ROOM_PUSH_NO_OBJECT) {
        return 0;
    }
    RoomObject *pushed = RoomObjects_At(RoomObjects_Table(), (unsigned int) object);
    if (pushed == NULL) {
        return 0;
    }
    RoomPushes_Set(&pushes[RoomObject_Layer(pushed) & 1], object, from, position, standoff, centre, destination, facing, side);
    return 1;
}
CLEAN_AS(func_ov004_0223c758, RoomPushes_Record)

/* func_ov004_0223c7b8: resets both records (no object, no side). */
void RoomPushes_Reset(RoomPush *pushes)
{
    for (u32 i = 0; i < ROOM_PUSHES_COUNT; i++) {
        RoomPushes_Clear(&pushes[i]);
    }
}
CLEAN_AS(func_ov004_0223c7b8, RoomPushes_Reset)

/* func_ov004_0223c7d8: the C++ destructor of the array. */
RoomPush *RoomPushes_Destruct(RoomPush *pushes)
{
    __cxa_vec_cleanup(pushes, ROOM_PUSHES_COUNT, sizeof(RoomPush), func_ov004_0223cbe0);
    return pushes;
}
CLEAN_AS(func_ov004_0223c7d8, RoomPushes_Destruct)

/* func_ov004_0223c7f4: the C++ constructor of the array, which also resets both records. */
RoomPush *RoomPushes_Construct(RoomPush *pushes)
{
    __cxa_vec_ctor(pushes, ROOM_PUSHES_COUNT, sizeof(RoomPush), func_ov004_0223cbe4, func_ov004_0223cbe0);
    RoomPushes_Reset(pushes);
    return pushes;
}
CLEAN_AS(func_ov004_0223c7f4, RoomPushes_Construct)

/* ---- What a pushing or pulling actor does to the object on the floor it pushes. */

/* The step RoomPushes_StepAlong gives: one cell (0x2000) along z, turned by its angle. It is a
 * local static object of the original, built on every call and registered for destruction
 * (TrivialObject_Destruct, which does nothing) on the first (bit 0 of the guard). */
extern u32 data_ov004_022595dc;
extern Vec3 data_ov004_02259628;
extern u8 data_ov004_0225961c[];
extern void func_020012dc(void *object);
extern void __register_global_object(void *object, void *destruct, void *record);

#define ROOM_PUSHES_CELL 0x2000
#define ROOM_PUSHES_HALF_TURN (-0x8000)
#define ROOM_PUSHES_QUARTER_TURN 0x4000

/* The record of the floor, the one an actor pushes with its hands. */
#define ROOM_PUSHES_FLOOR 0

/* func_ov004_0223c820: moves the object pushed back towards the actor, against its facing
 * (RoomObject_TryMoveBack); whether it moves, 0 without a push. */
int RoomPushes_TryPull(RoomPush *pushes)
{
    RoomPush *push = RoomPushes_Get(pushes, ROOM_PUSHES_FLOOR);
    RoomObject *object = RoomPushes_ObjectOf(pushes, ROOM_PUSHES_FLOOR);
    if (push != NULL && object != NULL) {
        return RoomObject_TryMoveBack(object, (u16) RoomPushes_Facing(push));
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c820, RoomPushes_TryPull)

/* func_ov004_0223c85c: whether the object pushed may move one cell against the actor's facing. */
int RoomPushes_CanPull(RoomPush *pushes)
{
    return RoomPushes_CanMoveTurned(pushes, ROOM_PUSHES_HALF_TURN);
}
CLEAN_AS(func_ov004_0223c85c, RoomPushes_CanPull)

/* func_ov004_0223c86c: moves the object pushed along the actor's facing (RoomObject_TryMove);
 * whether it moves, 0 without a push. */
int RoomPushes_TryPush(RoomPush *pushes)
{
    RoomPush *push = RoomPushes_Get(pushes, ROOM_PUSHES_FLOOR);
    RoomObject *object = RoomPushes_ObjectOf(pushes, ROOM_PUSHES_FLOOR);
    if (push != NULL && object != NULL) {
        return RoomObject_TryMove(object, (u16) RoomPushes_Facing(push));
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c86c, RoomPushes_TryPush)

/* func_ov004_0223c8a8: whether the object pushed may move one cell along the actor's facing. */
int RoomPushes_CanPush(RoomPush *pushes)
{
    return RoomPushes_CanMoveTurned(pushes, 0);
}
CLEAN_AS(func_ov004_0223c8a8, RoomPushes_CanPush)

/* func_ov004_0223c8b4: one cell along z turned by `angle` (Vec_RotateY), in a static vector. */
Vec3 *RoomPushes_StepAlong(void *unused, int angle)
{
    (void) unused;
    if ((data_ov004_022595dc & 1) == 0) {
        __register_global_object(&data_ov004_02259628, (void *) func_020012dc, data_ov004_0225961c);
        data_ov004_022595dc |= 1;
    }
    data_ov004_02259628.x = 0;
    data_ov004_02259628.y = 0;
    data_ov004_02259628.z = ROOM_PUSHES_CELL;
    Vec_RotateY(&data_ov004_02259628, angle);
    return &data_ov004_02259628;
}
CLEAN_AS(func_ov004_0223c8b4, RoomPushes_StepAlong)

/* func_ov004_0223c908: whether the object pushed may move one cell along the actor's facing
 * turned by `turn` (RoomObject_CanMove); 0 without a push. */
int RoomPushes_CanMoveTurned(RoomPush *pushes, int turn)
{
    RoomPush *push = RoomPushes_Get(pushes, ROOM_PUSHES_FLOOR);
    RoomObject *object = RoomPushes_ObjectOf(pushes, ROOM_PUSHES_FLOOR);
    if (push != NULL && object != NULL) {
        s16 angle = (s16) (turn + RoomPushes_Facing(push));
        return RoomObject_CanMove(object, RoomPushes_StepAlong(pushes, angle));
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c908, RoomPushes_CanMoveTurned)

/* func_ov004_0223c954: turns the object pushed a quarter turn up (RoomPushes_TryTurn). */
void RoomPushes_TryTurnPlus(RoomPush *pushes)
{
    RoomPushes_TryTurn(pushes, ROOM_PUSHES_QUARTER_TURN);
}
CLEAN_AS(func_ov004_0223c954, RoomPushes_TryTurnPlus)

/* func_ov004_0223c964: whether it may turn a quarter turn up (RoomPushes_CanTurn). */
int RoomPushes_CanTurnPlus(RoomPush *pushes)
{
    return RoomPushes_CanTurn(pushes, ROOM_PUSHES_QUARTER_TURN);
}
CLEAN_AS(func_ov004_0223c964, RoomPushes_CanTurnPlus)

/* func_ov004_0223c974: turns the object pushed a quarter turn down. */
void RoomPushes_TryTurnMinus(RoomPush *pushes)
{
    RoomPushes_TryTurn(pushes, -ROOM_PUSHES_QUARTER_TURN);
}
CLEAN_AS(func_ov004_0223c974, RoomPushes_TryTurnMinus)

/* func_ov004_0223c984: whether it may turn a quarter turn down. */
int RoomPushes_CanTurnMinus(RoomPush *pushes)
{
    return RoomPushes_CanTurn(pushes, -ROOM_PUSHES_QUARTER_TURN);
}
CLEAN_AS(func_ov004_0223c984, RoomPushes_CanTurnMinus)

/* func_ov004_0223c994: turns the object pushed by `turn` (RoomObject_TryTurn); whether it
 * turns, 0 without a push. */
int RoomPushes_TryTurn(RoomPush *pushes, int turn)
{
    RoomObject *object = RoomPushes_ObjectOf(pushes, ROOM_PUSHES_FLOOR);
    if (object != NULL) {
        return RoomObject_TryTurn(object, turn);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c994, RoomPushes_TryTurn)

/* func_ov004_0223c9b4: whether the object pushed may turn by `turn` (RoomObject_CanTurn); 0
 * without a push. */
int RoomPushes_CanTurn(RoomPush *pushes, int turn)
{
    RoomObject *object = RoomPushes_ObjectOf(pushes, ROOM_PUSHES_FLOOR);
    if (object != NULL) {
        return RoomObject_CanTurn(object, turn);
    }
    return 0;
}
CLEAN_AS(func_ov004_0223c9b4, RoomPushes_CanTurn)

/* Toggles the switch of the object of record `index` (RoomObject_ToggleSwitch), unless it is a
 * piece of furniture with FurnitureInfo_FlagBit4 pushed on another side than 0; whether it
 * toggled. */
static int toggle_pushed(RoomPush *pushes, int index)
{
    RoomObject *object = RoomPushes_ObjectOf(pushes, index);
    RoomPush *push = RoomPushes_Get(pushes, index);
    if (object == NULL || push == NULL) {
        return 0;
    }
    int allowed = 1;
    if (FurnitureInfo_FlagBit4(RoomObject_Number(object)) != 0 && RoomPushes_Side(push) != 0) {
        allowed = 0;
    }
    return allowed && RoomObject_ToggleSwitch(object) != 0;
}

/* func_ov004_0223c9d4: toggles the switch of the object pushed on top of others, else of the
 * one on the floor (toggle_pushed). */
void RoomPushes_ToggleSwitch(RoomPush *pushes)
{
    if (toggle_pushed(pushes, 1)) {
        return;
    }
    toggle_pushed(pushes, ROOM_PUSHES_FLOOR);
}
CLEAN_AS(func_ov004_0223c9d4, RoomPushes_ToggleSwitch)

/* ---- The records. */

/* The room's two records. */
extern RoomPush data_ov004_02259784[ROOM_PUSHES_COUNT];

/* func_ov004_0223ca6c: the object of record `index` (RoomPushes_Get), NULL without one. */
RoomObject *RoomPushes_ObjectOf(RoomPush *pushes, int index)
{
    RoomPush *push = RoomPushes_Get(pushes, index);
    if (push != NULL) {
        RoomObject **table = RoomObjects_Table();
        return RoomObjects_At(table, RoomPushes_Object(push));
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223ca6c, RoomPushes_ObjectOf)

/* func_ov004_0223ca9c: the record of `object` (by its index in the table of the room's
 * objects), NULL when it is in neither. Pushes need not be enabled. */
RoomPush *RoomPushes_FindObject(RoomPush *pushes, RoomObject *object)
{
    int index = RoomObjects_IndexOf(RoomObjects_Table(), object);
    if (index != -1) {
        for (u32 i = 0; i < ROOM_PUSHES_COUNT; i++) {
            if ((u32) index == RoomPushes_Object(&pushes[i])) {
                return &pushes[i];
            }
        }
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223ca9c, RoomPushes_FindObject)

/* func_ov004_0223cadc: while pushes are enabled (RoomPushes_Enabled), record `index` (its low
 * bit) when it holds an object; else NULL. */
RoomPush *RoomPushes_Get(RoomPush *pushes, int index)
{
    if (RoomPushes_Enabled() != 0) {
        RoomPush *push = &pushes[index & 1];
        if (RoomPushes_Object(push) != (u32) ROOM_PUSH_NO_OBJECT) {
            return push;
        }
    }
    return NULL;
}
CLEAN_AS(func_ov004_0223cadc, RoomPushes_Get)

/* func_ov004_0223cb10 */
RoomPush *RoomPushes_Records(void)
{
    return data_ov004_02259784;
}
CLEAN_AS(func_ov004_0223cb10, RoomPushes_Records)

/* func_ov004_0223cb18: the actor's facing, sign-extended. */
int RoomPushes_Facing(RoomPush *push)
{
    return push->facing;
}
CLEAN_AS(func_ov004_0223cb18, RoomPushes_Facing)

/* func_ov004_0223cb20 */
u32 RoomPushes_Side(RoomPush *push)
{
    return (u32) push->side;
}
CLEAN_AS(func_ov004_0223cb20, RoomPushes_Side)

/* func_ov004_0223cb24 */
Vec3 *RoomPushes_Destination(RoomPush *push)
{
    return &push->destination;
}
CLEAN_AS(func_ov004_0223cb24, RoomPushes_Destination)

/* func_ov004_0223cb28 */
Vec3 *RoomPushes_Centre(RoomPush *push)
{
    return &push->centre;
}
CLEAN_AS(func_ov004_0223cb28, RoomPushes_Centre)

/* func_ov004_0223cb2c */
u32 RoomPushes_Standoff(RoomPush *push)
{
    return (u32) push->standoff;
}
CLEAN_AS(func_ov004_0223cb2c, RoomPushes_Standoff)

/* func_ov004_0223cb30: how far apart, on the ground, the actor's position and its point at 0x68
 * are (Vec_DistanceXZ). */
fx32 RoomPushes_Moved(RoomPush *push)
{
    Vec3 *position = RoomPushes_Position(push);
    Vec3 *from = RoomPushes_From(push);
    return Vec_DistanceXZ(position, from);
}
CLEAN_AS(func_ov004_0223cb30, RoomPushes_Moved)

/* func_ov004_0223cb54 */
Vec3 *RoomPushes_Position(RoomPush *push)
{
    return &push->position;
}
CLEAN_AS(func_ov004_0223cb54, RoomPushes_Position)

/* func_ov004_0223cb58 */
Vec3 *RoomPushes_From(RoomPush *push)
{
    return &push->from;
}
CLEAN_AS(func_ov004_0223cb58, RoomPushes_From)

/* func_ov004_0223cb5c: the index of the object, ROOM_PUSH_NO_OBJECT for none. */
u32 RoomPushes_Object(RoomPush *push)
{
    return (u32) push->object;
}
CLEAN_AS(func_ov004_0223cb5c, RoomPushes_Object)

/* func_ov004_0223cb60: fills in `push`, unless `object` is ROOM_PUSH_NO_OBJECT (then it is left
 * as it was). The vectors are copied a field at a time, in this order. */
void RoomPushes_Set(RoomPush *push, s32 object, Vec3 *from, Vec3 *position, s32 standoff, Vec3 *centre, Vec3 *destination,
                    short facing, s32 side)
{
    if (object == ROOM_PUSH_NO_OBJECT) {
        return;
    }
    push->object = object;
    push->from.x = from->x;
    push->from.y = from->y;
    push->from.z = from->z;
    push->position.x = position->x;
    push->position.y = position->y;
    push->position.z = position->z;
    push->standoff = standoff;
    push->centre.x = centre->x;
    push->centre.y = centre->y;
    push->centre.z = centre->z;
    push->destination.x = destination->x;
    push->destination.y = destination->y;
    push->destination.z = destination->z;
    push->facing = facing;
    push->side = side;
}
CLEAN_AS(func_ov004_0223cb60, RoomPushes_Set)

/* func_ov004_0223cbb8: no object, everything zero, no side (the two bytes after the facing are
 * left as they are). */
RoomPush *RoomPushes_Clear(RoomPush *push)
{
    push->object = ROOM_PUSH_NO_OBJECT;
    push->from.x = 0;
    push->from.y = 0;
    push->from.z = 0;
    push->position.x = 0;
    push->position.y = 0;
    push->position.z = 0;
    push->standoff = 0;
    push->centre.x = 0;
    push->centre.y = 0;
    push->centre.z = 0;
    push->destination.x = 0;
    push->destination.y = 0;
    push->destination.z = 0;
    push->facing = 0;
    push->side = ROOM_PUSH_NO_SIDE;
    return push;
}
CLEAN_AS(func_ov004_0223cbb8, RoomPushes_Clear)

/* func_ov004_0223cbe0: the C++ destructor of a record; does nothing. */
void RoomPushes_DestructOne(void *push)
{
    (void) push;
}
CLEAN_AS(func_ov004_0223cbe0, RoomPushes_DestructOne)

/* func_ov004_0223cbe4: the C++ constructor of a record; does nothing (RoomPushes_Construct
 * resets them). */
void RoomPushes_ConstructOne(void *push)
{
    (void) push;
}
CLEAN_AS(func_ov004_0223cbe4, RoomPushes_ConstructOne)
