/* The room objects drawn only while on (room_object_switch_shown.h). */
#include "room_object_switch_shown.h"

#include <stdint.h>

#include "clean.h"
#include "main/item_code.h"
#include "member_pointer.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(SwitchShownObject, state) == 0x844, "state");
static_assert(offsetof(SwitchShownObject, always_drawn) == 0x845, "always drawn");
static_assert(sizeof(SwitchShownObject) == 0x848, "the size SwitchShown_Create allocates");

#define SWITCH_SHOWN_SIZE 0x848
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */
#define ALWAYS_DRAWN_FIRST 0x4124
#define ALWAYS_DRAWN_LAST 0x4223

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257084;
extern MemberPointer data_ov004_022571f4[SWITCH_SHOWN_STATE_COUNT];
extern const MemberPointer data_ov004_022502e0, data_ov004_022500f8;
extern u32 data_ov004_0225704c;
extern MemberPointer data_ov004_022571e4[SWITCH_SHOWN_STATE_COUNT];
extern const MemberPointer data_ov004_02250298, data_ov004_02250310;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_02247670[SWITCH_SHOWN_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02250ad8[];
extern const u8 data_ov004_02250b84[];

/* Requests a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);

/* The state's frame: the switch and the node set's value both `value`. */
static void show(SwitchShownObject *object, u8 value)
{
    Switch_Set(&object->base.light_switch, value, 0);
    ByteSet_SetValue(&object->base.node_set, value);
}

/* func_ov004_022123c4 (update of SWITCH_SHOWN_ON) */
void SwitchShown_UpdateOn(SwitchShownObject *object)
{
    show(object, 1);
}
CLEAN_AS(func_ov004_022123c4, SwitchShown_UpdateOn)

/* func_ov004_022123ec (entry of SWITCH_SHOWN_ON): the switch on, shown at once. */
int SwitchShown_EnterOn(SwitchShownObject *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_022123ec, SwitchShown_EnterOn)

/* func_ov004_02212408 (update of SWITCH_SHOWN_OFF) */
void SwitchShown_UpdateOff(SwitchShownObject *object)
{
    show(object, 0);
}
CLEAN_AS(func_ov004_02212408, SwitchShown_UpdateOff)

/* func_ov004_02212430 (entry of SWITCH_SHOWN_OFF): the switch off, shown at once. */
int SwitchShown_EnterOff(SwitchShownObject *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_02212430, SwitchShown_EnterOff)

/* _ZN18Obj_ov004_02250ad819func_ov004_0221244cEv: the state's update, through its table. */
void SwitchShown_UpdateState(SwitchShownObject *object)
{
    static const MemberPointer *const updates[SWITCH_SHOWN_STATE_COUNT] = {
        &data_ov004_022502e0, /* SwitchShown_UpdateOff */
        &data_ov004_022500f8, /* SwitchShown_UpdateOn */
    };
    MemberTable_InitOnce(&data_ov004_02257084, data_ov004_022571f4, updates, SWITCH_SHOWN_STATE_COUNT);
    if (object->state < SWITCH_SHOWN_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022571f4[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02250ad819func_ov004_0221244cEv, SwitchShown_UpdateState)

/* func_ov004_022124b8 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int SwitchShown_EnterState(SwitchShownObject *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[SWITCH_SHOWN_STATE_COUNT] = {
        &data_ov004_02250298, /* SwitchShown_EnterOff */
        &data_ov004_02250310, /* SwitchShown_EnterOn */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_0225704c, data_ov004_022571e4, entries, SWITCH_SHOWN_STATE_COUNT);
    if (state < SWITCH_SHOWN_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022571e4[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022124b8, SwitchShown_EnterState)

/* func_ov004_0221253c (vtable slot 0x74): whether `state` shows the object on; 0 for a state
 * that does not exist. */
u8 SwitchShown_StateIsOn(SwitchShownObject *object, unsigned int state)
{
    (void) object;
    if (state < SWITCH_SHOWN_STATE_COUNT) {
        return data_ov004_02247670[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_0221253c, SwitchShown_StateIsOn)

/* func_ov004_02212550: requests SWITCH_SHOWN_ON for the object at its cell; the answer. */
int SwitchShown_RequestOn(SwitchShownObject *object)
{
    return func_0205265c((unsigned int) (uintptr_t) object, SWITCH_SHOWN_ON, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_02212550, SwitchShown_RequestOn)

/* func_ov004_02212564: requests SWITCH_SHOWN_OFF for the object at its cell; the answer. */
int SwitchShown_RequestOff(SwitchShownObject *object)
{
    return func_0205265c((unsigned int) (uintptr_t) object, SWITCH_SHOWN_OFF, SLOT_70_VALUE, 1);
}
CLEAN_AS(func_ov004_02212564, SwitchShown_RequestOff)

/* func_ov004_02212578 (vtable slot 0x88): drawn when always drawn or on. */
int SwitchShown_CanDraw(SwitchShownObject *object)
{
    return object->always_drawn != 0 || object->state == SWITCH_SHOWN_ON;
}
CLEAN_AS(func_ov004_02212578, SwitchShown_CanDraw)

/* func_ov004_0221259c (vtable slot 0x0c) */
int SwitchShown_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221259c, SwitchShown_Vfunc0C)

/* _ZN18Obj_ov004_02250ad819func_ov004_022125a0Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing) */
int SwitchShown_Update(SwitchShownObject *object)
{
    SwitchShown_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02250ad819func_ov004_022125a0Ev, SwitchShown_Update)

/* func_ov004_022125b0 (vtable slot 0x7c, once the model is bound): marks it always drawn by its
 * item code (the flag is only ever set here, never cleared), then enters the state its switch
 * says; done at once. */
int SwitchShown_Start(SwitchShownObject *object)
{
    RoomObject *base = &object->base;
    u16 code = ItemCode_MakeVariant(RoomObject_Number(base), 0);
    if (code >= ALWAYS_DRAWN_FIRST && code <= ALWAYS_DRAWN_LAST) {
        object->always_drawn = 1;
    }
    if (Switch_Value(&base->light_switch) != 0) {
        base->vtable->vfunc_70(base, SWITCH_SHOWN_ON, SLOT_70_VALUE);
    } else {
        base->vtable->vfunc_70(base, SWITCH_SHOWN_OFF, SLOT_70_VALUE);
    }
    return 1;
}
CLEAN_AS(func_ov004_022125b0, SwitchShown_Start)

static void set_vtables(SwitchShownObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02250ad8;
    object->base.receiver_vtable = data_ov004_02250b84;
}

/* func_ov004_02212620 (the deleting destructor, vtable slot 0x44) */
SwitchShownObject *SwitchShown_Delete(SwitchShownObject *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02212620, SwitchShown_Delete)

/* func_ov004_0221264c (the destructor, vtable slot 0x40) */
SwitchShownObject *SwitchShown_Destroy(SwitchShownObject *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221264c, SwitchShown_Destroy)

/* func_ov004_02212670 (the constructor). Its own fields are left as the allocation zeroed
 * them. */
SwitchShownObject *SwitchShown_Construct(SwitchShownObject *object)
{
    RoomObject_ConstructBase(&object->base);
    set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02212670, SwitchShown_Construct)

/* func_ov004_02212694: a new one from the room's heap; nothing when it has no room. */
void SwitchShown_Create(void)
{
    SwitchShownObject *object = RoomObject_Alloc(SWITCH_SHOWN_SIZE);
    if (object != NULL) {
        SwitchShown_Construct(object);
    }
}
CLEAN_AS(func_ov004_02212694, SwitchShown_Create)
