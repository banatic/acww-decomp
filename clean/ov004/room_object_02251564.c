/* The room objects of vtable 0x02251564 (room_object_02251564.h). */
#include "room_object_02251564.h"

#include <stdint.h>

#include "clean.h"
#include "main/session.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "main/player_pockets.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/room_sync.h"

static_assert(offsetof(RoomObject02251564, state) == 0x844, "state");
static_assert(sizeof(RoomObject02251564) == 0x848, "the size RoomObject02251564_Create allocates");

#define ROOM_OBJECT_02251564_SIZE 0x848
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_0225701c;
extern MemberPointer data_ov004_02257134[ROOM_OBJECT_02251564_STATE_COUNT];
extern const MemberPointer data_ov004_02250150, data_ov004_02250148;
extern u32 data_ov004_02257078;
extern MemberPointer data_ov004_02257124[ROOM_OBJECT_02251564_STATE_COUNT];
extern const MemberPointer data_ov004_02250170, data_ov004_02250168;

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251564[];
extern const u8 data_ov004_02251610[];

extern NetSession *data_020ccf94; /* the session */

static PlayerPockets *RoomObject02251564_pockets(u8 *player)
{
    return PlayerRecord_Pockets(player);
}

/* func_ov004_02213008 (update of USED): the same as idle's. */
void RoomObject02251564_UpdateUsed(RoomObject02251564 *object)
{
    RoomObject02251564_UpdateIdle(object);
}
CLEAN_AS(func_ov004_02213008, RoomObject02251564_UpdateUsed)

/* func_ov004_02213010 (entry of USED): the sound at 2; when the player who used it
 * (RoomObject.unk_77C) is this system's and there is a player record, one bell less in the
 * wallet if it holds any. */
int RoomObject02251564_EnterUsed(RoomObject02251564 *object)
{
    RoomObject_PlaySound1(&object->base);
    if (object->base.unk_77C == data_020ccf94->local_player) {
        u8 *player = PlayerRecords_Current();
        if (player != NULL && PlayerPockets_Bells(RoomObject02251564_pockets(player), 0) > 0) {
            PlayerPockets *pockets = RoomObject02251564_pockets(player);
            int bells = PlayerPockets_Bells(RoomObject02251564_pockets(player), 0);
            PlayerPockets_SetBells(pockets, bells - 1, 0);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02213010, RoomObject02251564_EnterUsed)

/* func_ov004_02213074 (update of IDLE): touched, it requests USED with this system's player
 * number; else, with unk_76C at 2, it enters USED with no player. */
void RoomObject02251564_UpdateIdle(RoomObject02251564 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        RoomSync_RequestState(&object->base, ROOM_OBJECT_02251564_USED, (u8) data_020ccf94->local_player, 1);
        return;
    }
    if (RoomObject_Unk76CIs2(&object->base)) {
        object->base.vtable->vfunc_70(&object->base, ROOM_OBJECT_02251564_USED, SLOT_70_VALUE);
    }
}
CLEAN_AS(func_ov004_02213074, RoomObject02251564_UpdateIdle)

/* func_ov004_022130c0 (entry of IDLE) */
int RoomObject02251564_EnterIdle(RoomObject02251564 *object)
{
    (void) object;
    return 1;
}
CLEAN_AS(func_ov004_022130c0, RoomObject02251564_EnterIdle)

/* _ZN18Obj_ov004_0225156419func_ov004_022130c4Ev: the state's update, through its table. */
void RoomObject02251564_UpdateState(RoomObject02251564 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02251564_STATE_COUNT] = {
        &data_ov004_02250150, /* RoomObject02251564_UpdateIdle */
        &data_ov004_02250148, /* RoomObject02251564_UpdateUsed */
    };
    MemberTable_InitOnce(&data_ov004_0225701c, data_ov004_02257134, updates, ROOM_OBJECT_02251564_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02251564_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257134[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225156419func_ov004_022130c4Ev, RoomObject02251564_UpdateState)

/* func_ov004_02213130 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int RoomObject02251564_EnterState(RoomObject02251564 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02251564_STATE_COUNT] = {
        &data_ov004_02250170, /* RoomObject02251564_EnterIdle */
        &data_ov004_02250168, /* RoomObject02251564_EnterUsed */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257078, data_ov004_02257124, entries, ROOM_OBJECT_02251564_STATE_COUNT);
    if (state < ROOM_OBJECT_02251564_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257124[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02213130, RoomObject02251564_EnterState)

/* func_ov004_022131b4 (vtable slot 0x0c) */
int RoomObject02251564_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022131b4, RoomObject02251564_Vfunc0C)

/* _ZN18Obj_ov004_0225156419func_ov004_022131b8Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject02251564_Update(RoomObject02251564 *object)
{
    RoomObject02251564_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225156419func_ov004_022131b8Ev, RoomObject02251564_Update)

/* func_ov004_022131c8 (vtable slot 0x7c, once the model is bound): idle; done at once. */
int RoomObject02251564_Start(RoomObject02251564 *object)
{
    object->base.vtable->vfunc_70(&object->base, ROOM_OBJECT_02251564_IDLE, SLOT_70_VALUE);
    return 1;
}
CLEAN_AS(func_ov004_022131c8, RoomObject02251564_Start)

static void RoomObject02251564_set_vtables(RoomObject02251564 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02251564;
    object->base.receiver_vtable = data_ov004_02251610;
}

/* func_ov004_022131e0 (the deleting destructor, vtable slot 0x44) */
RoomObject02251564 *RoomObject02251564_Delete(RoomObject02251564 *object)
{
    RoomObject02251564_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022131e0, RoomObject02251564_Delete)

/* func_ov004_0221320c (the destructor, vtable slot 0x40) */
RoomObject02251564 *RoomObject02251564_Destroy(RoomObject02251564 *object)
{
    RoomObject02251564_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221320c, RoomObject02251564_Destroy)

/* func_ov004_02213230 (the constructor). Its own fields are left as the allocation zeroed
 * them. */
RoomObject02251564 *RoomObject02251564_Construct(RoomObject02251564 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02251564_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02213230, RoomObject02251564_Construct)

/* func_ov004_02213254: a new one from the room's heap; nothing when it has no room. */
void RoomObject02251564_Create(void)
{
    RoomObject02251564 *object = RoomObject_Alloc(ROOM_OBJECT_02251564_SIZE);
    if (object != NULL) {
        RoomObject02251564_Construct(object);
    }
}
CLEAN_AS(func_ov004_02213254, RoomObject02251564_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02251564's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02251564 *RoomObject02251564_from_receiver(void *receiver)
{
    return (RoomObject02251564 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221aadc: the deleting destructor, entered from the receiver part. */
RoomObject02251564 *RoomObject02251564Receiver_Delete(void *receiver)
{
    return RoomObject02251564_Delete(RoomObject02251564_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251564D0Ev, RoomObject02251564Receiver_Delete)

/* func_ov004_0221aaf8: the destructor, entered from the receiver part. */
RoomObject02251564 *RoomObject02251564Receiver_Destroy(void *receiver)
{
    return RoomObject02251564_Destroy(RoomObject02251564_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251564D1Ev, RoomObject02251564Receiver_Destroy)
