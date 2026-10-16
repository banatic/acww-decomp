/* The room objects of vtable 0x02252e00 (room_object_02252e00.h). */
#include "room_object_02252e00.h"

#include <stdint.h>

#include "clean.h"
#include "main/frame_ctrl.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"

static_assert(offsetof(RoomObject02252e00, state) == 0x844, "state");
static_assert(sizeof(RoomObject02252e00) == 0x848, "the size RoomObject02252e00_Create allocates");

#define ROOM_OBJECT_02252E00_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* the animations stop at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The furniture numbers (RoomObject_Number) with their own behaviour. */
#define FURNITURE_RESTARTS_1 0xb9
#define FURNITURE_RESTARTS_2 0xba
#define FURNITURE_0207 0x207
#define FURNITURE_0207_SOUND_FRAME 0x30

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257028;
extern MemberPointer data_ov004_022571a4[ROOM_OBJECT_02252E00_STATE_COUNT];
extern const MemberPointer data_ov004_02250380, data_ov004_02250240;
extern u32 data_ov004_02257060;
extern MemberPointer data_ov004_02257194[ROOM_OBJECT_02252E00_STATE_COUNT];
extern const MemberPointer data_ov004_02250340, data_ov004_022502a0;

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252e00[];
extern const u8 data_ov004_02252eac[];

/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);

static int RoomObject02252e00_request(RoomObject02252e00 *object, int state)
{
    return func_0205265c((unsigned int) (uintptr_t) object, state, SLOT_70_VALUE, 1);
}

/* func_ov004_02219e54 (update of PLAYING): furniture 0xb9 and 0xba with a change of the switch
 * pending request PLAYING again, and that is all. Otherwise the switch is turned over (shown at
 * once), STILL is requested once the animations end (else the sound at 0 played), and furniture
 * 0x207 plays the sound at 4 when its joint animation passes frame 0x30.
 * QUIRK: turning the switch over every frame makes it flicker between on and off while the
 * animations play, and leaves no change pending, so a touch then is lost (except for 0xb9 and
 * 0xba, which look before turning it). */
void RoomObject02252e00_UpdatePlaying(RoomObject02252e00 *object)
{
    RoomObject *base = &object->base;
    switch (RoomObject_Number(base)) {
        case FURNITURE_RESTARTS_1:
        case FURNITURE_RESTARTS_2:
            if (Switch_IsPending(&base->light_switch)) {
                RoomObject02252e00_request(object, ROOM_OBJECT_02252E00_PLAYING);
                return;
            }
            break;
    }
    Switch_Toggle(&base->light_switch, 0);
    if (RoomObject_AdvanceAnims(base)) {
        RoomObject02252e00_request(object, ROOM_OBJECT_02252E00_STILL);
    } else {
        RoomObject_PlaySound0(base);
    }
    if (RoomObject_Number(base) == FURNITURE_0207 &&
        FrameCtrl_Passed((const FrameCtrl *) (const void *) base->joint_anim, FURNITURE_0207_SOUND_FRAME)) {
        RoomObject_PlaySound2(base);
    }
}
CLEAN_AS(func_ov004_02219e54, RoomObject02252e00_UpdatePlaying)

/* func_ov004_02219ed8 (entry of PLAYING): the animations of variant 0 once from the start and
 * the sound at 2. */
int RoomObject02252e00_EnterPlaying(RoomObject02252e00 *object)
{
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02219ed8, RoomObject02252e00_EnterPlaying)

/* func_ov004_02219f00 (update of STILL): with a change of the switch pending, requests
 * PLAYING. */
void RoomObject02252e00_UpdateStill(RoomObject02252e00 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        RoomObject02252e00_request(object, ROOM_OBJECT_02252E00_PLAYING);
    }
}
CLEAN_AS(func_ov004_02219f00, RoomObject02252e00_UpdateStill)

/* func_ov004_02219f28 (entry of STILL): the animations of variant 0 once from their end, and
 * the sound at 4 except for furniture 0x207. */
int RoomObject02252e00_EnterStill(RoomObject02252e00 *object)
{
    RoomObject_PlayAnimsFromEnd(&object->base, 0, ANIM_MODE_ONCE, ONE);
    if (RoomObject_Number(&object->base) != FURNITURE_0207) {
        RoomObject_PlaySound2(&object->base);
    }
    return 1;
}
CLEAN_AS(func_ov004_02219f28, RoomObject02252e00_EnterStill)

/* _ZN18Obj_ov004_02252e0019func_ov004_02219f58Ev: the state's update, through its table. */
void RoomObject02252e00_UpdateState(RoomObject02252e00 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02252E00_STATE_COUNT] = {
        &data_ov004_02250380, /* RoomObject02252e00_UpdateStill */
        &data_ov004_02250240, /* RoomObject02252e00_UpdatePlaying */
    };
    MemberTable_InitOnce(&data_ov004_02257028, data_ov004_022571a4, updates, ROOM_OBJECT_02252E00_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02252E00_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022571a4[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02252e0019func_ov004_02219f58Ev, RoomObject02252e00_UpdateState)

/* func_ov004_02219fc4 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int RoomObject02252e00_EnterState(RoomObject02252e00 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02252E00_STATE_COUNT] = {
        &data_ov004_02250340, /* RoomObject02252e00_EnterStill */
        &data_ov004_022502a0, /* RoomObject02252e00_EnterPlaying */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257060, data_ov004_02257194, entries, ROOM_OBJECT_02252E00_STATE_COUNT);
    if (state < ROOM_OBJECT_02252E00_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257194[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02219fc4, RoomObject02252e00_EnterState)

/* func_ov004_0221a048 (vtable slot 0x0c): the switch off, shown at once. */
int RoomObject02252e00_SwitchOff(RoomObject02252e00 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221a048, RoomObject02252e00_SwitchOff)

/* _ZN18Obj_ov004_02252e0019func_ov004_0221a064Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject02252e00_Update(RoomObject02252e00 *object)
{
    RoomObject02252e00_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02252e0019func_ov004_0221a064Ev, RoomObject02252e00_Update)

/* func_ov004_0221a074 (vtable slot 0x7c, once the model is bound): the switch off (shown at
 * once), the animations of variant 0 bound (once, from the start) and put at their end, then
 * STILL; done at once. */
int RoomObject02252e00_Start(RoomObject02252e00 *object)
{
    RoomObject *base = &object->base;
    Switch_Set(&base->light_switch, 0, 0);
    RoomObject_LoadAnims(base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlayAnimsFromEnd(base, 0, ANIM_MODE_ONCE, ONE);
    base->vtable->vfunc_70(base, ROOM_OBJECT_02252E00_STILL, SLOT_70_VALUE);
    return 1;
}
CLEAN_AS(func_ov004_0221a074, RoomObject02252e00_Start)

static void RoomObject02252e00_set_vtables(RoomObject02252e00 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252e00;
    object->base.receiver_vtable = data_ov004_02252eac;
}

/* func_ov004_0221a0c0 (the deleting destructor, vtable slot 0x44) */
RoomObject02252e00 *RoomObject02252e00_Delete(RoomObject02252e00 *object)
{
    RoomObject02252e00_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_0221a0c0, RoomObject02252e00_Delete)

/* func_ov004_0221a0ec (the destructor, vtable slot 0x40) */
RoomObject02252e00 *RoomObject02252e00_Destroy(RoomObject02252e00 *object)
{
    RoomObject02252e00_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221a0ec, RoomObject02252e00_Destroy)

/* func_ov004_0221a110 (the constructor): the base and the vtables. The state is left as the
 * allocation zeroed it. */
RoomObject02252e00 *RoomObject02252e00_Construct(RoomObject02252e00 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252e00_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_0221a110, RoomObject02252e00_Construct)

/* func_ov004_0221a134: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252e00_Create(void)
{
    RoomObject02252e00 *object = RoomObject_Alloc(ROOM_OBJECT_02252E00_SIZE);
    if (object != NULL) {
        RoomObject02252e00_Construct(object);
    }
}
CLEAN_AS(func_ov004_0221a134, RoomObject02252e00_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02252e00's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02252e00 *RoomObject02252e00_from_receiver(void *receiver)
{
    return (RoomObject02252e00 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a59c: the deleting destructor, entered from the receiver part. */
RoomObject02252e00 *RoomObject02252e00Receiver_Delete(void *receiver)
{
    return RoomObject02252e00_Delete(RoomObject02252e00_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252e00D0Ev, RoomObject02252e00Receiver_Delete)

/* func_ov004_0221a5b8: the destructor, entered from the receiver part. */
RoomObject02252e00 *RoomObject02252e00Receiver_Destroy(void *receiver)
{
    return RoomObject02252e00_Destroy(RoomObject02252e00_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252e00D1Ev, RoomObject02252e00Receiver_Destroy)
