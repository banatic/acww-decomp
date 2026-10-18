/* The room objects of vtable 0x022510b4 (room_object_022510b4.h). */
#include "room_object_022510b4.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "main/room_sync.h"
#include "room_objects.h"

static_assert(offsetof(RoomObject, light_switch) == 0x740, "switch");
static_assert(offsetof(RoomObject022510b4, unk_844) == 0x844, "unk_844");
static_assert(offsetof(RoomObject022510b4, state) == 0x845, "state");
static_assert(sizeof(RoomObject022510b4) == 0x848, "the size RoomObject022510b4_Create allocates");

#define ROOM_OBJECT_022510B4_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* the animations start again at the end */
#define ANIM_MODE_ONCE 1   /* the animations stop at the end */
#define ANIM_MODE_3 3      /* the animations' mode 3 */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257030;
extern MemberPointer data_ov004_0225746c[ROOM_OBJECT_022510B4_STATE_COUNT];
extern const MemberPointer data_ov004_02250370, data_ov004_02250258, data_ov004_02250300, data_ov004_02250280;
extern u32 data_ov004_02257098;
extern MemberPointer data_ov004_0225744c[ROOM_OBJECT_022510B4_STATE_COUNT];
extern const MemberPointer data_ov004_02250600, data_ov004_02250318, data_ov004_02250290, data_ov004_02250278;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_02247688[ROOM_OBJECT_022510B4_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022510b4[];
extern const u8 data_ov004_02251160[];

/* Vtable slot 0x70: RoomObject022510b4_EnterState for this class. */
static void RoomObject022510b4_switch_to(RoomObject022510b4 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* Touched (a change of the switch pending), `state` is requested for the object at its cell;
 * else with unk_76C at 2 it is entered at once. */
static void RoomObject022510b4_on_touch(RoomObject022510b4 *object, int state)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        RoomSync_RequestState(&object->base, state, SLOT_70_VALUE, 1);
    } else if (RoomObject_Unk76CIs2(&object->base)) {
        RoomObject022510b4_switch_to(object, state);
    }
}

/* func_ov004_02218b2c (update of SWITCHING_OFF): the switch off (shown at once); OFF once the
 * animations end. */
void RoomObject022510b4_UpdateSwitchingOff(RoomObject022510b4 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject022510b4_switch_to(object, ROOM_OBJECT_022510B4_OFF);
    }
}
CLEAN_AS(func_ov004_02218b2c, RoomObject022510b4_UpdateSwitchingOff)

/* func_ov004_02218b5c (entry of SWITCHING_OFF): the switch off (shown at once), sound 2 of its
 * row and the animations of variant 0 from their end in mode 3. */
int RoomObject022510b4_EnterSwitchingOff(RoomObject022510b4 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlaySound2(&object->base);
    RoomObject_PlayAnimsFromEnd(&object->base, 0, ANIM_MODE_3, ONE);
    return 1;
}
CLEAN_AS(func_ov004_02218b5c, RoomObject022510b4_EnterSwitchingOff)

/* func_ov004_02218b90 (update of ON): the animations, FurnitureInfo_IndoorBit6 of its number and sound 0;
 * touched, it requests SWITCHING_OFF. */
void RoomObject022510b4_UpdateOn(RoomObject022510b4 *object)
{
    RoomObject_AdvanceAnims(&object->base);
    RoomObject_Lookup020537a8(&object->base);
    RoomObject_PlaySound0(&object->base);
    RoomObject022510b4_on_touch(object, ROOM_OBJECT_022510B4_SWITCHING_OFF);
}
CLEAN_AS(func_ov004_02218b90, RoomObject022510b4_UpdateOn)

/* func_ov004_02218be0 (entry of ON): the switch on (shown at once) and the animations of
 * variant 1 in a loop from their end. */
int RoomObject022510b4_EnterOn(RoomObject022510b4 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 1, ANIM_MODE_LOOP, ONE);
    return 1;
}
CLEAN_AS(func_ov004_02218be0, RoomObject022510b4_EnterOn)

/* func_ov004_02218c0c (update of SWITCHING_ON): the switch on (shown at once); ON once the
 * animations end. */
void RoomObject022510b4_UpdateSwitchingOn(RoomObject022510b4 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject022510b4_switch_to(object, ROOM_OBJECT_022510B4_ON);
    }
}
CLEAN_AS(func_ov004_02218c0c, RoomObject022510b4_UpdateSwitchingOn)

/* func_ov004_02218c3c (entry of SWITCHING_ON): the switch on (shown at once), sound 1 of its row
 * and the animations of variant 0 once from the start. */
int RoomObject022510b4_EnterSwitchingOn(RoomObject022510b4 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlaySound1(&object->base);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_02218c3c, RoomObject022510b4_EnterSwitchingOn)

/* func_ov004_02218c74 (update of OFF): touched, it requests SWITCHING_ON. */
void RoomObject022510b4_UpdateOff(RoomObject022510b4 *object)
{
    RoomObject022510b4_on_touch(object, ROOM_OBJECT_022510B4_SWITCHING_ON);
}
CLEAN_AS(func_ov004_02218c74, RoomObject022510b4_UpdateOff)

/* func_ov004_02218cb4 (entry of OFF): the switch off (shown at once) and the animations of
 * variant 0 in mode 3 from the start. */
int RoomObject022510b4_EnterOff(RoomObject022510b4 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_3, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_02218cb4, RoomObject022510b4_EnterOff)

/* _ZN18Obj_ov004_022510b419func_ov004_02218ce8Ev: the state's update, through its table. */
void RoomObject022510b4_UpdateState(RoomObject022510b4 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_022510B4_STATE_COUNT] = {
        &data_ov004_02250370, /* RoomObject022510b4_UpdateOff */
        &data_ov004_02250258, /* RoomObject022510b4_UpdateSwitchingOn */
        &data_ov004_02250300, /* RoomObject022510b4_UpdateOn */
        &data_ov004_02250280, /* RoomObject022510b4_UpdateSwitchingOff */
    };
    MemberTable_InitOnce(&data_ov004_02257030, data_ov004_0225746c, updates, ROOM_OBJECT_022510B4_STATE_COUNT);
    if (object->state < ROOM_OBJECT_022510B4_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225746c[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022510b419func_ov004_02218ce8Ev, RoomObject022510b4_UpdateState)

/* func_ov004_02218d74 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 4 and above do not exist. */
int RoomObject022510b4_EnterState(RoomObject022510b4 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_022510B4_STATE_COUNT] = {
        &data_ov004_02250600, /* RoomObject022510b4_EnterOff */
        &data_ov004_02250318, /* RoomObject022510b4_EnterSwitchingOn */
        &data_ov004_02250290, /* RoomObject022510b4_EnterOn */
        &data_ov004_02250278, /* RoomObject022510b4_EnterSwitchingOff */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257098, data_ov004_0225744c, entries, ROOM_OBJECT_022510B4_STATE_COUNT);
    if (state < ROOM_OBJECT_022510B4_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225744c[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02218d74, RoomObject022510b4_EnterState)

/* func_ov004_02218e14 (vtable slot 0x74): whether `state` shows the object on (SWITCHING_ON and
 * ON do); 0 for a state that does not exist. */
u8 RoomObject022510b4_StateIsOn(RoomObject022510b4 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_022510B4_STATE_COUNT) {
        return data_ov004_02247688[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02218e14, RoomObject022510b4_StateIsOn)

/* func_ov004_02218e28 (vtable slot 0x0c) */
int RoomObject022510b4_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02218e28, RoomObject022510b4_Vfunc0C)

/* _ZN18Obj_ov004_022510b419func_ov004_02218e2cEv (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject022510b4_Update(RoomObject022510b4 *object)
{
    RoomObject022510b4_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022510b419func_ov004_02218e2cEv, RoomObject022510b4_Update)

/* func_ov004_02218e3c (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (once, from the start); ON when the switch is on and RoomObjects_InNookOrScene0AOr0F says no,
 * else OFF; done at once. */
int RoomObject022510b4_Start(RoomObject022510b4 *object)
{
    object->unk_844 = 0;
    RoomObject_LoadAnims(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    if (Switch_Value(&object->base.light_switch) != 0 && !RoomObjects_InNookOrScene0AOr0F()) {
        RoomObject022510b4_switch_to(object, ROOM_OBJECT_022510B4_ON);
    } else {
        RoomObject022510b4_switch_to(object, ROOM_OBJECT_022510B4_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02218e3c, RoomObject022510b4_Start)

static void RoomObject022510b4_set_vtables(RoomObject022510b4 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022510b4;
    object->base.receiver_vtable = data_ov004_02251160;
}

/* func_ov004_02218e98 (the deleting destructor, vtable slot 0x44) */
RoomObject022510b4 *RoomObject022510b4_Delete(RoomObject022510b4 *object)
{
    RoomObject022510b4_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02218e98, RoomObject022510b4_Delete)

/* func_ov004_02218ec4 (the destructor, vtable slot 0x40) */
RoomObject022510b4 *RoomObject022510b4_Destroy(RoomObject022510b4 *object)
{
    RoomObject022510b4_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02218ec4, RoomObject022510b4_Destroy)

/* func_ov004_02218ee8 (the constructor). Its own fields are left as the allocation zeroed
 * them. */
RoomObject022510b4 *RoomObject022510b4_Construct(RoomObject022510b4 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject022510b4_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02218ee8, RoomObject022510b4_Construct)

/* func_ov004_02218f0c: a new one from the room's heap; nothing when it has no room. */
void RoomObject022510b4_Create(void)
{
    RoomObject022510b4 *object = RoomObject_Alloc(ROOM_OBJECT_022510B4_SIZE);
    if (object != NULL) {
        RoomObject022510b4_Construct(object);
    }
}
CLEAN_AS(func_ov004_02218f0c, RoomObject022510b4_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject022510b4's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject022510b4 *RoomObject022510b4_from_receiver(void *receiver)
{
    return (RoomObject022510b4 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a6b4: the deleting destructor, entered from the receiver part. */
RoomObject022510b4 *RoomObject022510b4Receiver_Delete(void *receiver)
{
    return RoomObject022510b4_Delete(RoomObject022510b4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022510b4D0Ev, RoomObject022510b4Receiver_Delete)

/* func_ov004_0221a6d0: the destructor, entered from the receiver part. */
RoomObject022510b4 *RoomObject022510b4Receiver_Destroy(void *receiver)
{
    return RoomObject022510b4_Destroy(RoomObject022510b4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022510b4D1Ev, RoomObject022510b4Receiver_Destroy)
