/* The room objects of vtable 0x02251a14 (room_object_02251a14.h). */
#include "room_object_02251a14.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"

static_assert(offsetof(RoomObject02251a14, state) == 0x844, "state");
static_assert(offsetof(RoomObject02251a14, glows) == 0x848, "glows");
static_assert(sizeof(RoomObject02251a14) == 0x8a0, "the size RoomObject02251a14_Create allocates");

#define ROOM_OBJECT_02251A14_SIZE 0x8a0
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* the animations start again at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_022570b4;
extern MemberPointer data_ov004_022571d4[ROOM_OBJECT_02251A14_STATE_COUNT];
extern const MemberPointer data_ov004_02250178, data_ov004_02250070;
extern u32 data_ov004_0225708c;
extern MemberPointer data_ov004_022571c4[ROOM_OBJECT_02251A14_STATE_COUNT];
extern const MemberPointer data_ov004_022503e8, data_ov004_02250160;

/* Whether each state shows the object on (for vtable slot 0x74): ON does. */
extern const u8 data_ov004_02247668[ROOM_OBJECT_02251A14_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251a14[];
extern const u8 data_ov004_02251ac0[];

/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);

static int RoomObject02251a14_request(RoomObject02251a14 *object, int state)
{
    return func_0205265c((unsigned int) (uintptr_t) object, state, SLOT_70_VALUE, 1);
}

/* Vtable slot 0x70: RoomObject02251a14_EnterState for this class. */
static void RoomObject02251a14_switch_to(RoomObject02251a14 *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* func_ov004_02219b38 (update of ON): the animations, func_020537a8 of its number, the sound at
 * 0; with a change of the switch pending, requests OFF and gives the answer, else 0. */
int RoomObject02251a14_UpdateOn(RoomObject02251a14 *object)
{
    RoomObject_AdvanceAnims(&object->base);
    RoomObject_Lookup020537a8(&object->base);
    RoomObject_PlaySound0(&object->base);
    if (Switch_IsPending(&object->base.light_switch)) {
        return RoomObject02251a14_request(object, ROOM_OBJECT_02251A14_OFF);
    }
    return 0;
}
CLEAN_AS(func_ov004_02219b38, RoomObject02251a14_UpdateOn)

/* func_ov004_02219b70 (entry of ON): the switch on (shown at once), the sound at 2 and the
 * glows towards on (fading). */
int RoomObject02251a14_EnterOn(RoomObject02251a14 *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlaySound1(&object->base);
    GlowSet_Switch(&object->glows, 1, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_02219b70, RoomObject02251a14_EnterOn)

/* func_ov004_02219ba4 (update of OFF): with a change of the switch pending, requests ON. */
void RoomObject02251a14_UpdateOff(RoomObject02251a14 *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        RoomObject02251a14_request(object, ROOM_OBJECT_02251A14_ON);
    }
}
CLEAN_AS(func_ov004_02219ba4, RoomObject02251a14_UpdateOff)

/* func_ov004_02219bcc (entry of OFF): the switch off (shown at once), the sound at 4 and the
 * glows towards off (fading). */
int RoomObject02251a14_EnterOff(RoomObject02251a14 *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlaySound2(&object->base);
    GlowSet_Switch(&object->glows, 0, 1, 0);
    return 1;
}
CLEAN_AS(func_ov004_02219bcc, RoomObject02251a14_EnterOff)

/* _ZN18Obj_ov004_02251a1419func_ov004_02219c00Ev: the state's update, through its table. */
void RoomObject02251a14_UpdateState(RoomObject02251a14 *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02251A14_STATE_COUNT] = {
        &data_ov004_02250178, /* RoomObject02251a14_UpdateOff */
        &data_ov004_02250070, /* RoomObject02251a14_UpdateOn */
    };
    MemberTable_InitOnce(&data_ov004_022570b4, data_ov004_022571d4, updates, ROOM_OBJECT_02251A14_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02251A14_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022571d4[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02251a1419func_ov004_02219c00Ev, RoomObject02251a14_UpdateState)

/* func_ov004_02219c6c (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int RoomObject02251a14_EnterState(RoomObject02251a14 *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02251A14_STATE_COUNT] = {
        &data_ov004_022503e8, /* RoomObject02251a14_EnterOff */
        &data_ov004_02250160, /* RoomObject02251a14_EnterOn */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_0225708c, data_ov004_022571c4, entries, ROOM_OBJECT_02251A14_STATE_COUNT);
    if (state < ROOM_OBJECT_02251A14_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022571c4[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02219c6c, RoomObject02251a14_EnterState)

/* func_ov004_02219cf0 (vtable slot 0x74): whether `state` shows the object on (ON does); 0 for a
 * state that does not exist. */
u8 RoomObject02251a14_StateIsOn(RoomObject02251a14 *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_02251A14_STATE_COUNT) {
        return data_ov004_02247668[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02219cf0, RoomObject02251a14_StateIsOn)

/* func_ov004_02219d04 (vtable slot 0x0c) */
int RoomObject02251a14_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02219d04, RoomObject02251a14_Vfunc0C)

/* _ZN18Obj_ov004_02251a1419func_ov004_02219d08Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): each glow's frame, then the state's update. */
int RoomObject02251a14_Update(RoomObject02251a14 *object)
{
    GlowSet_Update(&object->glows);
    RoomObject02251a14_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02251a1419func_ov004_02219d08Ev, RoomObject02251a14_Update)

/* func_ov004_02219d28 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (in a loop, from the start) and the glows, lit as the switch is; then enters ON
 * when the switch is on and func_ov004_0223c10c says no, OFF otherwise; done at once. */
int RoomObject02251a14_Start(RoomObject02251a14 *object)
{
    RoomObject *base = &object->base;
    RoomObject_LoadAnims(base, 0, ANIM_MODE_LOOP, ONE, 0);
    GlowSet_Bind(&object->glows, base->model_resource, Switch_Value(&base->light_switch));
    if (Switch_Value(&base->light_switch) != 0 && func_ov004_0223c10c() == 0) {
        RoomObject02251a14_switch_to(object, ROOM_OBJECT_02251A14_ON);
    } else {
        RoomObject02251a14_switch_to(object, ROOM_OBJECT_02251A14_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02219d28, RoomObject02251a14_Start)

static void RoomObject02251a14_set_vtables(RoomObject02251a14 *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02251a14;
    object->base.receiver_vtable = data_ov004_02251ac0;
}

/* func_ov004_02219d9c (the deleting destructor, vtable slot 0x44) */
RoomObject02251a14 *RoomObject02251a14_Delete(RoomObject02251a14 *object)
{
    RoomObject02251a14_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02219d9c, RoomObject02251a14_Delete)

/* func_ov004_02219dd4 (the destructor, vtable slot 0x40) */
RoomObject02251a14 *RoomObject02251a14_Destroy(RoomObject02251a14 *object)
{
    RoomObject02251a14_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02219dd4, RoomObject02251a14_Destroy)

/* func_ov004_02219e08 (the constructor): the base, the vtables, the glows (not bound). The state
 * is left as the allocation zeroed it. */
RoomObject02251a14 *RoomObject02251a14_Construct(RoomObject02251a14 *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02251a14_set_vtables(object);
    GlowSet_Construct(&object->glows);
    return object;
}
CLEAN_AS(func_ov004_02219e08, RoomObject02251a14_Construct)

/* func_ov004_02219e38: a new one from the room's heap; nothing when it has no room. */
void RoomObject02251a14_Create(void)
{
    RoomObject02251a14 *object = RoomObject_Alloc(ROOM_OBJECT_02251A14_SIZE);
    if (object != NULL) {
        RoomObject02251a14_Construct(object);
    }
}
CLEAN_AS(func_ov004_02219e38, RoomObject02251a14_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02251a14's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02251a14 *RoomObject02251a14_from_receiver(void *receiver)
{
    return (RoomObject02251a14 *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a5d4: the deleting destructor, entered from the receiver part. */
RoomObject02251a14 *RoomObject02251a14Receiver_Delete(void *receiver)
{
    return RoomObject02251a14_Delete(RoomObject02251a14_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251a14D0Ev, RoomObject02251a14Receiver_Delete)

/* func_ov004_0221a5f0: the destructor, entered from the receiver part. */
RoomObject02251a14 *RoomObject02251a14Receiver_Destroy(void *receiver)
{
    return RoomObject02251a14_Destroy(RoomObject02251a14_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251a14D1Ev, RoomObject02251a14Receiver_Destroy)
