/* The room objects of vtable 0x022525cc (room_object_022525cc.h). */
#include "room_object_022525cc.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "clean.h"
#include "furniture_model.h"
#include "main/frame_ctrl.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "main/room_sync.h"
#include "room_objects.h"

static_assert(offsetof(RoomObject022525cc, state) == 0x844, "state");
static_assert(offsetof(RoomObject022525cc, speed) == 0x848, "speed");
static_assert(offsetof(RoomObject022525cc, glows) == 0x84c, "glows");
static_assert(sizeof(RoomObject022525cc) == 0x8a4, "the size RoomObject022525cc_Create allocates");
static_assert(offsetof(RoomObject, model.frames) == 0x5d4, "joint animation");
static_assert(offsetof(RoomObject, anims) == 0x7c4, "animations");
static_assert(offsetof(FurnitureAnim, base.ctrl.speed) == 0x10, "animation speed");

#define ROOM_OBJECT_022525CC_SIZE 0x8a4
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define STOP_STEP 0xcc     /* what the speed falls by each frame of STOPPING */
#define ANIM_MODE_LOOP 0   /* the animations start again at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257050;
extern MemberPointer data_ov004_0225727c[ROOM_OBJECT_022525CC_STATE_COUNT];
extern const MemberPointer data_ov004_022500c0, data_ov004_022503a8, data_ov004_022500f0;
extern u32 data_ov004_02257004;
extern MemberPointer data_ov004_02257264[ROOM_OBJECT_022525CC_STATE_COUNT];
extern const MemberPointer data_ov004_02250188, data_ov004_02250050, data_ov004_02250400;

/* Whether each state shows the object on (for vtable slot 0x74): ON does. */
extern const u8 data_ov004_0224767c[ROOM_OBJECT_022525CC_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022525cc[];
extern const u8 data_ov004_02252678[];

static int RoomObject022525cc_request(RoomObject022525cc *object, int state)
{
    return RoomSync_RequestState(&object->base, state, SLOT_70_VALUE, 1);
}

/* Vtable slot 0x70: RoomObject022525cc_EnterState for this class. */
static int RoomObject022525cc_switch_to(RoomObject022525cc *object, int state)
{
    return object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* func_ov004_0221974c (update of STOPPING): the speed 0xcc closer to 0; at 0 enters OFF and
 * gives the answer, else the speed. */
int RoomObject022525cc_UpdateStopping(RoomObject022525cc *object)
{
    Approach_S32Again(&object->speed, 0, STOP_STEP);
    if (object->speed == 0) {
        return RoomObject022525cc_switch_to(object, ROOM_OBJECT_022525CC_OFF);
    }
    return object->speed;
}
CLEAN_AS(func_ov004_0221974c, RoomObject022525cc_UpdateStopping)

/* func_ov004_0221977c (entry of STOPPING): the switch off (shown at once), the sound at 4 and
 * the glows towards on (fading). */
int RoomObject022525cc_EnterStopping(RoomObject022525cc *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlaySound2(&object->base);
    GlowSet_Switch(&object->glows, 1, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221977c, RoomObject022525cc_EnterStopping)

/* func_ov004_022197b0 (update of ON): FurnitureInfo_IndoorBit6 of its number, the sound at 0; with a change
 * of the switch pending, requests STOPPING and gives the answer, else 0. */
int RoomObject022525cc_UpdateOn(RoomObject022525cc *object)
{
    RoomObject_Lookup020537a8(&object->base);
    RoomObject_PlaySound0(&object->base);
    if (Switch_IsPending(&object->base.light_switch)) {
        return RoomObject022525cc_request(object, ROOM_OBJECT_022525CC_STOPPING);
    }
    return 0;
}
CLEAN_AS(func_ov004_022197b0, RoomObject022525cc_UpdateOn)

/* func_ov004_022197e0 (entry of ON): the speed normal, the switch on (shown at once), the sound
 * at 2 and the glows towards on (fading). */
int RoomObject022525cc_EnterOn(RoomObject022525cc *object)
{
    object->speed = ONE;
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlaySound1(&object->base);
    GlowSet_Switch(&object->glows, 1, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_022197e0, RoomObject022525cc_EnterOn)

/* func_ov004_02219824 (update of OFF): with a change of the switch pending, requests ON. */
void RoomObject022525cc_UpdateOff(RoomObject022525cc *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        RoomObject022525cc_request(object, ROOM_OBJECT_022525CC_ON);
    }
}
CLEAN_AS(func_ov004_02219824, RoomObject022525cc_UpdateOff)

/* func_ov004_0221984c (entry of OFF): the speed 0, the switch off (shown at once) and the glows
 * towards off (fading). */
int RoomObject022525cc_EnterOff(RoomObject022525cc *object)
{
    object->speed = 0;
    Switch_Set(&object->base.light_switch, 0, 0);
    GlowSet_Switch(&object->glows, 0, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221984c, RoomObject022525cc_EnterOff)

/* _ZN18Obj_ov004_022525cc19func_ov004_02219884Ev: the state's update, through its table. */
void RoomObject022525cc_UpdateState(RoomObject022525cc *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_022525CC_STATE_COUNT] = {
        &data_ov004_022500c0, /* RoomObject022525cc_UpdateOff */
        &data_ov004_022503a8, /* RoomObject022525cc_UpdateOn */
        &data_ov004_022500f0, /* RoomObject022525cc_UpdateStopping */
    };
    MemberTable_InitOnce(&data_ov004_02257050, data_ov004_0225727c, updates, ROOM_OBJECT_022525CC_STATE_COUNT);
    if (object->state < ROOM_OBJECT_022525CC_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225727c[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022525cc19func_ov004_02219884Ev, RoomObject022525cc_UpdateState)

/* func_ov004_02219900 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 3 and above do not exist. */
int RoomObject022525cc_EnterState(RoomObject022525cc *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_022525CC_STATE_COUNT] = {
        &data_ov004_02250188, /* RoomObject022525cc_EnterOff */
        &data_ov004_02250050, /* RoomObject022525cc_EnterOn */
        &data_ov004_02250400, /* RoomObject022525cc_EnterStopping */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257004, data_ov004_02257264, entries, ROOM_OBJECT_022525CC_STATE_COUNT);
    if (state < ROOM_OBJECT_022525CC_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257264[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02219900, RoomObject022525cc_EnterState)

/* func_ov004_02219990 (vtable slot 0x74): whether `state` shows the object on (ON does); 0 for a
 * state that does not exist. */
u8 RoomObject022525cc_StateIsOn(RoomObject022525cc *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_022525CC_STATE_COUNT) {
        return data_ov004_0224767c[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02219990, RoomObject022525cc_StateIsOn)

/* func_ov004_022199a4 (vtable slot 0x0c) */
int RoomObject022525cc_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022199a4, RoomObject022525cc_Vfunc0C)

/* _ZN18Obj_ov004_022525cc19func_ov004_022199a8Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): each glow's frame, the state; then the speed given to the joint
 * animation and to each bound animation, and every animation advanced. */
int RoomObject022525cc_Update(RoomObject022525cc *object)
{
    RoomObject *base = &object->base;
    GlowSet_Update(&object->glows);
    RoomObject022525cc_UpdateState(object);
    base->model.frames.speed = object->speed;
    for (int i = 0; i < 4; i++) {
        if (FurnitureAnim_Target(&base->anims[i]) != NULL) {
            base->anims[i].base.ctrl.speed = object->speed;
        }
    }
    RoomObject_AdvanceAnims(base);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022525cc19func_ov004_022199a8Ev, RoomObject022525cc_Update)

/* func_ov004_02219a0c (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (in a loop, from the start) and the glows, lit as the switch is; then enters ON
 * when the switch is on and RoomObjects_InNookOrScene0AOr0F says no, OFF otherwise; done at once. */
int RoomObject022525cc_Start(RoomObject022525cc *object)
{
    RoomObject *base = &object->base;
    RoomObject_LoadAnims(base, 0, ANIM_MODE_LOOP, ONE, 0);
    GlowSet_Bind(&object->glows, base->model_resource, Switch_Value(&base->light_switch));
    if (Switch_Value(&base->light_switch) != 0 && RoomObjects_InNookOrScene0AOr0F() == 0) {
        RoomObject022525cc_switch_to(object, ROOM_OBJECT_022525CC_ON);
    } else {
        RoomObject022525cc_switch_to(object, ROOM_OBJECT_022525CC_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02219a0c, RoomObject022525cc_Start)

static void RoomObject022525cc_set_vtables(RoomObject022525cc *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022525cc;
    object->base.receiver_vtable = data_ov004_02252678;
}

/* func_ov004_02219a80 (the deleting destructor, vtable slot 0x44) */
RoomObject022525cc *RoomObject022525cc_Delete(RoomObject022525cc *object)
{
    RoomObject022525cc_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02219a80, RoomObject022525cc_Delete)

/* func_ov004_02219ab8 (the destructor, vtable slot 0x40) */
RoomObject022525cc *RoomObject022525cc_Destroy(RoomObject022525cc *object)
{
    RoomObject022525cc_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02219ab8, RoomObject022525cc_Destroy)

/* func_ov004_02219aec (the constructor): the base, the vtables, the glows (not bound). The
 * state and the speed are left as the allocation zeroed them. */
RoomObject022525cc *RoomObject022525cc_Construct(RoomObject022525cc *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject022525cc_set_vtables(object);
    GlowSet_Construct(&object->glows);
    return object;
}
CLEAN_AS(func_ov004_02219aec, RoomObject022525cc_Construct)

/* func_ov004_02219b1c: a new one from the room's heap; nothing when it has no room. */
void RoomObject022525cc_Create(void)
{
    RoomObject022525cc *object = RoomObject_Alloc(ROOM_OBJECT_022525CC_SIZE);
    if (object != NULL) {
        RoomObject022525cc_Construct(object);
    }
}
CLEAN_AS(func_ov004_02219b1c, RoomObject022525cc_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject022525cc's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject022525cc *RoomObject022525cc_from_receiver(void *receiver)
{
    return (RoomObject022525cc *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a60c: the deleting destructor, entered from the receiver part. */
RoomObject022525cc *RoomObject022525ccReceiver_Delete(void *receiver)
{
    return RoomObject022525cc_Delete(RoomObject022525cc_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022525ccD0Ev, RoomObject022525ccReceiver_Delete)

/* func_ov004_0221a628: the destructor, entered from the receiver part. */
RoomObject022525cc *RoomObject022525ccReceiver_Destroy(void *receiver)
{
    return RoomObject022525cc_Destroy(RoomObject022525cc_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022525ccD1Ev, RoomObject022525ccReceiver_Destroy)
