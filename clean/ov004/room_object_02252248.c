/* The room objects of vtable 0x02252248 (room_object_02252248.h). */
#include "room_object_02252248.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject, light_switch) == 0x740, "switch");
static_assert(offsetof(RoomObject02252248, state) == 0x844, "state");
static_assert(sizeof(RoomObject02252248) == 0x848, "the size RoomObject02252248_Create allocates");

#define ROOM_OBJECT_02252248_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* the animations stop at the end */
#define ANIM_MODE_3 3      /* the animations' mode 3 */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_022570ac;
extern MemberPointer data_ov004_022573ec[ROOM_OBJECT_02252248_STATE_COUNT];
extern const MemberPointer data_ov004_02250238, data_ov004_022503a0, data_ov004_02250228, data_ov004_02250218;
extern u32 data_ov004_0225709c;
extern MemberPointer data_ov004_022573ac[ROOM_OBJECT_02252248_STATE_COUNT];
extern const MemberPointer data_ov004_02250348, data_ov004_02250408, data_ov004_02250388, data_ov004_022502b8;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_0224768c[ROOM_OBJECT_02252248_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252248[];
extern const u8 data_ov004_022522f4[];

/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);

/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);

/* Vtable slot 0x70: RoomObject02252248_EnterState for this class. */
static void RoomObject02252248_switch_to(RoomObject02252248 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* Touched (a change of the switch pending), `state` is requested for the object at its cell;
 * else with unk_76C at 2 it is entered at once. */
static void RoomObject02252248_on_touch(RoomObject02252248 *object, int state)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        func_0205265c((unsigned int) (uintptr_t) object, state, SLOT_70_VALUE, 1);
    } else if (RoomObject_Unk76CIs2(&object->base)) {
        RoomObject02252248_switch_to(object, state);
    }
}

/* func_ov004_02219368 (update of SWITCHING_OFF): the switch off (shown at once); OFF once the
 * animations end. */
void RoomObject02252248_UpdateSwitchingOff(RoomObject02252248 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject02252248_switch_to(object, ROOM_OBJECT_02252248_OFF);
    }
}
CLEAN_AS(func_ov004_02219368, RoomObject02252248_UpdateSwitchingOff)

/* func_ov004_02219398 (entry of SWITCHING_OFF): the switch off (shown at once), the animations
 * of variant 0 from their end in mode 3 and sound 2 of its row. */
int RoomObject02252248_EnterSwitchingOff(RoomObject02252248 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 0, ANIM_MODE_3, ONE);
    RoomObject_PlaySound2(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02219398, RoomObject02252248_EnterSwitchingOff)

/* func_ov004_022193cc (update of ON): touched, it requests SWITCHING_OFF. */
void RoomObject02252248_UpdateOn(RoomObject02252248 *object)
{
    RoomObject02252248_on_touch(object, ROOM_OBJECT_02252248_SWITCHING_OFF);
}
CLEAN_AS(func_ov004_022193cc, RoomObject02252248_UpdateOn)

/* func_ov004_0221940c (entry of ON): the switch on (shown at once) and the animations of
 * variant 0 once from their end. */
int RoomObject02252248_EnterOn(RoomObject02252248 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 0, ANIM_MODE_ONCE, ONE);
    return 1;
}
CLEAN_AS(func_ov004_0221940c, RoomObject02252248_EnterOn)

/* func_ov004_02219438 (update of SWITCHING_ON): the switch on (shown at once); ON once the
 * animations end. */
void RoomObject02252248_UpdateSwitchingOn(RoomObject02252248 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject02252248_switch_to(object, ROOM_OBJECT_02252248_ON);
    }
}
CLEAN_AS(func_ov004_02219438, RoomObject02252248_UpdateSwitchingOn)

/* func_ov004_02219468 (entry of SWITCHING_ON): the switch on (shown at once), the animations of
 * variant 0 once from the start and sound 1 of its row. */
int RoomObject02252248_EnterSwitchingOn(RoomObject02252248 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02219468, RoomObject02252248_EnterSwitchingOn)

/* func_ov004_022194a0 (update of OFF): touched, it requests SWITCHING_ON. */
void RoomObject02252248_UpdateOff(RoomObject02252248 *object)
{
    RoomObject02252248_on_touch(object, ROOM_OBJECT_02252248_SWITCHING_ON);
}
CLEAN_AS(func_ov004_022194a0, RoomObject02252248_UpdateOff)

/* func_ov004_022194e0 (entry of OFF): the switch off (shown at once) and the animations of
 * variant 0 in mode 3 from the start. */
int RoomObject02252248_EnterOff(RoomObject02252248 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_3, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022194e0, RoomObject02252248_EnterOff)

/* _ZN18Obj_ov004_0225224819func_ov004_02219514Ev: the state's update, through its table. */
void RoomObject02252248_UpdateState(RoomObject02252248 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02252248_STATE_COUNT] = {
        &data_ov004_02250238, /* RoomObject02252248_UpdateOff */
        &data_ov004_022503a0, /* RoomObject02252248_UpdateSwitchingOn */
        &data_ov004_02250228, /* RoomObject02252248_UpdateOn */
        &data_ov004_02250218, /* RoomObject02252248_UpdateSwitchingOff */
    };
    MemberTable_InitOnce(&data_ov004_022570ac, data_ov004_022573ec, updates, ROOM_OBJECT_02252248_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02252248_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022573ec[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225224819func_ov004_02219514Ev, RoomObject02252248_UpdateState)

/* func_ov004_022195a0 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 4 and above do not exist. */
int RoomObject02252248_EnterState(RoomObject02252248 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02252248_STATE_COUNT] = {
        &data_ov004_02250348, /* RoomObject02252248_EnterOff */
        &data_ov004_02250408, /* RoomObject02252248_EnterSwitchingOn */
        &data_ov004_02250388, /* RoomObject02252248_EnterOn */
        &data_ov004_022502b8, /* RoomObject02252248_EnterSwitchingOff */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_0225709c, data_ov004_022573ac, entries, ROOM_OBJECT_02252248_STATE_COUNT);
    if (state < ROOM_OBJECT_02252248_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022573ac[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022195a0, RoomObject02252248_EnterState)

/* func_ov004_02219640 (vtable slot 0x74): whether `state` shows the object on (SWITCHING_ON and
 * ON do); 0 for a state that does not exist. */
u8 RoomObject02252248_StateIsOn(RoomObject02252248 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_02252248_STATE_COUNT) {
        return data_ov004_0224768c[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02219640, RoomObject02252248_StateIsOn)

/* func_ov004_02219654 (vtable slot 0x0c) */
int RoomObject02252248_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02219654, RoomObject02252248_Vfunc0C)

/* _ZN18Obj_ov004_0225224819func_ov004_02219658Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject02252248_Update(RoomObject02252248 *object)
{
    RoomObject02252248_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225224819func_ov004_02219658Ev, RoomObject02252248_Update)

/* func_ov004_02219668 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (once, from the start), then enters ON when the switch is on and
 * func_ov004_0223c10c says no, OFF otherwise; done at once. */
int RoomObject02252248_Start(RoomObject02252248 *object)
{
    RoomObject_LoadAnims(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    if (Switch_Value(&object->base.light_switch) != 0 && func_ov004_0223c10c() == 0) {
        RoomObject02252248_switch_to(object, ROOM_OBJECT_02252248_ON);
    } else {
        RoomObject02252248_switch_to(object, ROOM_OBJECT_02252248_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02219668, RoomObject02252248_Start)

static void RoomObject02252248_set_vtables(RoomObject02252248 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252248;
    object->base.receiver_vtable = data_ov004_022522f4;
}

/* func_ov004_022196bc (the deleting destructor, vtable slot 0x44) */
RoomObject02252248 *RoomObject02252248_Delete(RoomObject02252248 *object)
{
    RoomObject02252248_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022196bc, RoomObject02252248_Delete)

/* func_ov004_022196e8 (the destructor, vtable slot 0x40) */
RoomObject02252248 *RoomObject02252248_Destroy(RoomObject02252248 *object)
{
    RoomObject02252248_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_022196e8, RoomObject02252248_Destroy)

/* func_ov004_0221970c (the constructor): the base and the vtables. The state is left as the
 * allocation zeroed it. */
RoomObject02252248 *RoomObject02252248_Construct(RoomObject02252248 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252248_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_0221970c, RoomObject02252248_Construct)

/* func_ov004_02219730: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252248_Create(void)
{
    RoomObject02252248 *object = RoomObject_Alloc(ROOM_OBJECT_02252248_SIZE);
    if (object != NULL) {
        RoomObject02252248_Construct(object);
    }
}
CLEAN_AS(func_ov004_02219730, RoomObject02252248_Create)
