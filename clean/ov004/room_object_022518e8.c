/* The room objects of vtable 0x022518e8 (room_object_022518e8.h). */
#include "room_object_022518e8.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject, light_switch) == 0x740, "switch");
static_assert(offsetof(RoomObject, node_set) == 0x764, "node set");
static_assert(offsetof(RoomObject022518e8, state) == 0x845, "state");
static_assert(sizeof(RoomObject022518e8) == 0x848, "the size RoomObject022518e8_Create allocates");

#define ROOM_OBJECT_022518E8_SIZE 0x848
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1   /* the animations stop at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_0225707c;
extern MemberPointer data_ov004_0225742c[ROOM_OBJECT_022518E8_STATE_COUNT];
extern const MemberPointer data_ov004_02250468, data_ov004_02250338, data_ov004_02250270, data_ov004_022502d0;
extern u32 data_ov004_022570a4;
extern MemberPointer data_ov004_0225740c[ROOM_OBJECT_022518E8_STATE_COUNT];
extern const MemberPointer data_ov004_02250080, data_ov004_02250128, data_ov004_02250658, data_ov004_022504b8;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_02247698[ROOM_OBJECT_022518E8_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022518e8[];
extern const u8 data_ov004_02251994[];

/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);
/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);

/* Vtable slot 0x70: RoomObject022518e8_EnterState for this class. */
static void RoomObject022518e8_switch_to(RoomObject022518e8 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* Touched (a change of the switch pending), `state` is requested for the object at its cell;
 * else with unk_76C at 2 it is entered at once. */
static void RoomObject022518e8_on_touch(RoomObject022518e8 *object, int state)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        func_0205265c((unsigned int) (uintptr_t) object, state, SLOT_70_VALUE, 1);
    } else if (RoomObject_Unk76CIs2(&object->base)) {
        RoomObject022518e8_switch_to(object, state);
    }
}

/* func_ov004_02218f28 (update of SWITCHING_OFF): the node set's value 1, sound 0 and the switch
 * off (shown at once); OFF once the animations end. */
void RoomObject022518e8_UpdateSwitchingOff(RoomObject022518e8 *object)
{
    ByteSet_SetValue(&object->base.node_set, 1);
    RoomObject_PlaySound0(&object->base);
    Switch_Set(&object->base.light_switch, 0, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject022518e8_switch_to(object, ROOM_OBJECT_022518E8_OFF);
    }
}
CLEAN_AS(func_ov004_02218f28, RoomObject022518e8_UpdateSwitchingOff)

/* func_ov004_02218f6c (entry of SWITCHING_OFF): the switch off (shown at once), the node set's
 * value 1, the animations of variant 1 once from the start and sound 2 of its row. */
int RoomObject022518e8_EnterSwitchingOff(RoomObject022518e8 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    ByteSet_SetValue(&object->base.node_set, 1);
    RoomObject_PlayAnimsFrom(&object->base, 1, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound2(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02218f6c, RoomObject022518e8_EnterSwitchingOff)

/* func_ov004_02218fb4 (update of ON): sound 0; touched, it requests SWITCHING_OFF. */
void RoomObject022518e8_UpdateOn(RoomObject022518e8 *object)
{
    RoomObject_PlaySound0(&object->base);
    RoomObject022518e8_on_touch(object, ROOM_OBJECT_022518E8_SWITCHING_OFF);
}
CLEAN_AS(func_ov004_02218fb4, RoomObject022518e8_UpdateOn)

/* func_ov004_02218ff8 (entry of ON): the switch on (shown at once), the animations of variant 0
 * once from their end and the node set's value 1. */
int RoomObject022518e8_EnterOn(RoomObject022518e8 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 0, ANIM_MODE_ONCE, ONE);
    ByteSet_SetValue(&object->base.node_set, 1);
    return 1;
}
CLEAN_AS(func_ov004_02218ff8, RoomObject022518e8_EnterOn)

/* func_ov004_02219034 (update of SWITCHING_ON): the switch on (shown at once) and sound 0; ON
 * once the animations end. */
void RoomObject022518e8_UpdateSwitchingOn(RoomObject022518e8 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlaySound0(&object->base);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject022518e8_switch_to(object, ROOM_OBJECT_022518E8_ON);
    }
}
CLEAN_AS(func_ov004_02219034, RoomObject022518e8_UpdateSwitchingOn)

/* func_ov004_0221906c (entry of SWITCHING_ON): the switch on (shown at once), the node set's
 * value 1, the animations of variant 0 once from the start and sound 1 of its row. */
int RoomObject022518e8_EnterSwitchingOn(RoomObject022518e8 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    ByteSet_SetValue(&object->base.node_set, 1);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_0221906c, RoomObject022518e8_EnterSwitchingOn)

/* func_ov004_022190b4 (update of OFF): touched, it requests SWITCHING_ON. */
void RoomObject022518e8_UpdateOff(RoomObject022518e8 *object)
{
    RoomObject022518e8_on_touch(object, ROOM_OBJECT_022518E8_SWITCHING_ON);
}
CLEAN_AS(func_ov004_022190b4, RoomObject022518e8_UpdateOff)

/* func_ov004_022190f4 (entry of OFF): the switch off (shown at once), the animations of variant
 * 1 once from their end and the node set's value 0. */
int RoomObject022518e8_EnterOff(RoomObject022518e8 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 1, ANIM_MODE_ONCE, ONE);
    ByteSet_SetValue(&object->base.node_set, 0);
    return 1;
}
CLEAN_AS(func_ov004_022190f4, RoomObject022518e8_EnterOff)

/* _ZN18Obj_ov004_022518e819func_ov004_02219130Ev: the state's update, through its table. */
void RoomObject022518e8_UpdateState(RoomObject022518e8 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_022518E8_STATE_COUNT] = {
        &data_ov004_02250468, /* RoomObject022518e8_UpdateOff */
        &data_ov004_02250338, /* RoomObject022518e8_UpdateSwitchingOn */
        &data_ov004_02250270, /* RoomObject022518e8_UpdateOn */
        &data_ov004_022502d0, /* RoomObject022518e8_UpdateSwitchingOff */
    };
    MemberTable_InitOnce(&data_ov004_0225707c, data_ov004_0225742c, updates, ROOM_OBJECT_022518E8_STATE_COUNT);
    if (object->state < ROOM_OBJECT_022518E8_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225742c[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022518e819func_ov004_02219130Ev, RoomObject022518e8_UpdateState)

/* func_ov004_022191bc (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 4 and above do not exist. */
int RoomObject022518e8_EnterState(RoomObject022518e8 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_022518E8_STATE_COUNT] = {
        &data_ov004_02250080, /* RoomObject022518e8_EnterOff */
        &data_ov004_02250128, /* RoomObject022518e8_EnterSwitchingOn */
        &data_ov004_02250658, /* RoomObject022518e8_EnterOn */
        &data_ov004_022504b8, /* RoomObject022518e8_EnterSwitchingOff */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_022570a4, data_ov004_0225740c, entries, ROOM_OBJECT_022518E8_STATE_COUNT);
    if (state < ROOM_OBJECT_022518E8_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225740c[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022191bc, RoomObject022518e8_EnterState)

/* func_ov004_0221925c (vtable slot 0x74): whether `state` shows the object on (SWITCHING_ON and
 * ON do); 0 for a state that does not exist. */
u8 RoomObject022518e8_StateIsOn(RoomObject022518e8 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_022518E8_STATE_COUNT) {
        return data_ov004_02247698[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_0221925c, RoomObject022518e8_StateIsOn)

/* func_ov004_02219270 (vtable slot 0x0c) */
int RoomObject022518e8_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02219270, RoomObject022518e8_Vfunc0C)

/* _ZN18Obj_ov004_022518e819func_ov004_02219274Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject022518e8_Update(RoomObject022518e8 *object)
{
    RoomObject022518e8_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022518e819func_ov004_02219274Ev, RoomObject022518e8_Update)

/* func_ov004_02219284 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (once, from the start); ON when the switch is on and func_ov004_0223c10c says no,
 * else OFF; done at once. */
int RoomObject022518e8_Start(RoomObject022518e8 *object)
{
    RoomObject_LoadAnims(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    if (Switch_Value(&object->base.light_switch) != 0 && !func_ov004_0223c10c()) {
        RoomObject022518e8_switch_to(object, ROOM_OBJECT_022518E8_ON);
    } else {
        RoomObject022518e8_switch_to(object, ROOM_OBJECT_022518E8_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02219284, RoomObject022518e8_Start)

static void RoomObject022518e8_set_vtables(RoomObject022518e8 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022518e8;
    object->base.receiver_vtable = data_ov004_02251994;
}

/* func_ov004_022192d8 (the deleting destructor, vtable slot 0x44) */
RoomObject022518e8 *RoomObject022518e8_Delete(RoomObject022518e8 *object)
{
    RoomObject022518e8_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_022192d8, RoomObject022518e8_Delete)

/* func_ov004_02219304 (the destructor, vtable slot 0x40) */
RoomObject022518e8 *RoomObject022518e8_Destroy(RoomObject022518e8 *object)
{
    RoomObject022518e8_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02219304, RoomObject022518e8_Destroy)

/* func_ov004_02219328 (the constructor). Its own fields are left as the allocation zeroed
 * them. */
RoomObject022518e8 *RoomObject022518e8_Construct(RoomObject022518e8 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject022518e8_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02219328, RoomObject022518e8_Construct)

/* func_ov004_0221934c: a new one from the room's heap; nothing when it has no room. */
void RoomObject022518e8_Create(void)
{
    RoomObject022518e8 *object = RoomObject_Alloc(ROOM_OBJECT_022518E8_SIZE);
    if (object != NULL) {
        RoomObject022518e8_Construct(object);
    }
}
CLEAN_AS(func_ov004_0221934c, RoomObject022518e8_Create)
