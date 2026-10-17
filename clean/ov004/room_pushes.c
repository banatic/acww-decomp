/* The room's two pushes (room_pushes.h). */
#include "room_pushes.h"

#include "clean.h"
#include "main/scene_kinds.h"
#include "main/scene_query.h"
#include "room_object.h"
#include "room_object_body.h"

static_assert(sizeof(RoomPush) == 0x40, "push");
static_assert(offsetof(RoomPush, standoff) == 0x1c, "standoff");
static_assert(offsetof(RoomPush, facing) == 0x38, "facing");
static_assert(offsetof(RoomPush, side) == 0x3c, "side");

/* Whether a villager of the flea market is in the room, or the scene is one where the
 * room's objects stay off (set by the room's start). */
extern unsigned char func_ov004_0223d348(void);

/* The table of the room's objects. */
extern void *func_ov004_0223ce84(void);
extern RoomObject *func_ov004_0223cd58(void *objects, unsigned int index);

/* One push: set, reset, and the C++ constructor and destructor of the array's elements (which
 * do nothing). */
extern void func_ov004_0223cb60(RoomPush *push, s32 object, Vec3 *from, Vec3 *position, s32 standoff, Vec3 *centre,
                                Vec3 *destination, short facing, s32 side);
extern void *func_ov004_0223cbb8(RoomPush *push);
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

/* func_ov004_0223c72c: unless func_ov004_0223d348 says no, whether the scene is a house's room
 * (SceneKinds_CurrentIsHouseRoom) or of kind 11 (SceneQuery_CurrentIn11). */
int RoomPushes_Enabled(void)
{
    if (func_ov004_0223d348() != 0) {
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
    RoomObject *pushed = func_ov004_0223cd58(func_ov004_0223ce84(), (unsigned int) object);
    if (pushed == NULL) {
        return 0;
    }
    func_ov004_0223cb60(&pushes[RoomObject_Layer(pushed) & 1], object, from, position, standoff, centre, destination, facing,
                        side);
    return 1;
}
CLEAN_AS(func_ov004_0223c758, RoomPushes_Record)

/* func_ov004_0223c7b8: resets both records (no object, no side). */
void RoomPushes_Reset(RoomPush *pushes)
{
    for (u32 i = 0; i < ROOM_PUSHES_COUNT; i++) {
        func_ov004_0223cbb8(&pushes[i]);
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
