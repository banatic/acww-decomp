/* The room objects with three glowing materials (room_object_glowing.h). */
#include "room_object_glowing.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"

static_assert(offsetof(GlowingRoomObject, glows) == 0x844, "glows");
static_assert(offsetof(GlowingRoomObject, state) == 0x89c, "state");
static_assert(sizeof(GlowingRoomObject) == 0x8a0, "the size GlowingRoomObject_Create allocates");

#define GLOWING_ROOM_OBJECT_SIZE 0x8a0
#define ONE 0x1000       /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0 /* RoomObject_PlayAnimsFrom: start again at the end */
#define ANIM_MODE_ONCE 1
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257080;
extern MemberPointer data_ov004_02257244[GLOWING_STATE_COUNT];
extern const MemberPointer data_ov004_02250578, data_ov004_02250598;
extern u32 data_ov004_02257048;
extern MemberPointer data_ov004_02257224[GLOWING_STATE_COUNT];
extern const MemberPointer data_ov004_02250458, data_ov004_02250488;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_0224765c[GLOWING_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_022509ac[];
extern const u8 data_ov004_02250a58[];

/* Request a state for the object at the object's cell (only when data_020e54a8 is 1); the
 * second goes straight to func_020526b8, the first may go through the link instead. */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);
extern int func_02052738(unsigned int object, int state, int a2, int a3);
/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);

static unsigned int address_of(GlowingRoomObject *object)
{
    return (unsigned int) (uintptr_t) object;
}

/* func_ov004_0221206c (update of GLOWING_ON): the animations, the glows towards on, the sound
 * at 0; with a change of the switch pending, requests GLOWING_OFF and gives the answer, else
 * 0. */
int GlowingRoomObject_UpdateOn(GlowingRoomObject *object)
{
    RoomObject_AdvanceAnims(&object->base);
    GlowSet_Switch(&object->glows, 1, 1, 0);
    RoomObject_PlaySound0(&object->base);
    if (Switch_IsPending(&object->base.light_switch)) {
        return func_0205265c(address_of(object), GLOWING_OFF, SLOT_70_VALUE, 1);
    }
    return 0;
}
CLEAN_AS(func_ov004_0221206c, GlowingRoomObject_UpdateOn)

/* func_ov004_022120b0 (entry of GLOWING_ON): the sound at 2, the switch on (shown at once) and
 * the animations of variant 1 in a loop from the start. */
int GlowingRoomObject_EnterOn(GlowingRoomObject *object)
{
    RoomObject_PlaySound1(&object->base);
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFrom(&object->base, 1, ANIM_MODE_LOOP, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022120b0, GlowingRoomObject_EnterOn)

/* func_ov004_022120e8 (update of GLOWING_OFF): the animations and the glows towards off; with a
 * change of the switch pending, requests GLOWING_ON and gives the answer, else 0. */
int GlowingRoomObject_UpdateOff(GlowingRoomObject *object)
{
    RoomObject_AdvanceAnims(&object->base);
    GlowSet_Switch(&object->glows, 0, 1, 0);
    if (Switch_IsPending(&object->base.light_switch)) {
        return func_0205265c(address_of(object), GLOWING_ON, SLOT_70_VALUE, 1);
    }
    return 0;
}
CLEAN_AS(func_ov004_022120e8, GlowingRoomObject_UpdateOff)

/* func_ov004_02212124 (entry of GLOWING_OFF): the sound at 4, the switch off (shown at once)
 * and the animations of variant 0 once from the start. */
int GlowingRoomObject_EnterOff(GlowingRoomObject *object)
{
    RoomObject_PlaySound2(&object->base);
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_02212124, GlowingRoomObject_EnterOff)

/* _ZN18Obj_ov004_022509ac19func_ov004_0221215cEv: the state's update, through its table. */
void GlowingRoomObject_UpdateState(GlowingRoomObject *object)
{
    static const MemberPointer *const updates[GLOWING_STATE_COUNT] = {
        &data_ov004_02250578, /* GlowingRoomObject_UpdateOff */
        &data_ov004_02250598, /* GlowingRoomObject_UpdateOn */
    };
    MemberTable_InitOnce(&data_ov004_02257080, data_ov004_02257244, updates, GLOWING_STATE_COUNT);
    if (object->state < GLOWING_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257244[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022509ac19func_ov004_0221215cEv, GlowingRoomObject_UpdateState)

/* func_ov004_022121c8 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int GlowingRoomObject_EnterState(GlowingRoomObject *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[GLOWING_STATE_COUNT] = {
        &data_ov004_02250458, /* GlowingRoomObject_EnterOff */
        &data_ov004_02250488, /* GlowingRoomObject_EnterOn */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02257048, data_ov004_02257224, entries, GLOWING_STATE_COUNT);
    if (state < GLOWING_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257224[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_022121c8, GlowingRoomObject_EnterState)

/* func_ov004_0221224c (vtable slot 0x74): whether `state` shows the object on; 0 for a state
 * that does not exist. */
u8 GlowingRoomObject_StateIsOn(GlowingRoomObject *object, unsigned int state)
{
    (void) object;
    if (state < GLOWING_STATE_COUNT) {
        return data_ov004_0224765c[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_0221224c, GlowingRoomObject_StateIsOn)

/* func_ov004_02212260 (vtable slot 0x0c) */
int GlowingRoomObject_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02212260, GlowingRoomObject_Vfunc0C)

/* _ZN18Obj_ov004_022509ac19func_ov004_02212264Ev (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state, then each glow's frame. */
int GlowingRoomObject_Update(GlowingRoomObject *object)
{
    GlowingRoomObject_UpdateState(object);
    GlowSet_Update(&object->glows);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022509ac19func_ov004_02212264Ev, GlowingRoomObject_Update)

/* func_ov004_02212280 (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (once) and the glows, lit as the switch is; then in mode 1 requests GLOWING_OFF
 * (func_02052738), else enters GLOWING_ON when the switch is on and func_ov004_0223c10c says
 * no, GLOWING_OFF otherwise; done at once. */
int GlowingRoomObject_Start(GlowingRoomObject *object)
{
    RoomObject *base = &object->base;
    RoomObject_LoadAnims(base, 0, ANIM_MODE_ONCE, ONE, 0);
    GlowSet_Bind(&object->glows, base->model_resource, Switch_Value(&base->light_switch));
    if (base->unk_76C == 1) {
        func_02052738(address_of(object), GLOWING_OFF, SLOT_70_VALUE, 1);
    } else if (Switch_Value(&base->light_switch) != 0 && func_ov004_0223c10c() == 0) {
        base->vtable->vfunc_70(base, GLOWING_ON, SLOT_70_VALUE);
    } else {
        base->vtable->vfunc_70(base, GLOWING_OFF, SLOT_70_VALUE);
    }
    return 1;
}
CLEAN_AS(func_ov004_02212280, GlowingRoomObject_Start)

static void set_vtables(GlowingRoomObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_022509ac;
    object->base.receiver_vtable = data_ov004_02250a58;
}

/* func_ov004_0221230c (the deleting destructor, vtable slot 0x44) */
GlowingRoomObject *GlowingRoomObject_Delete(GlowingRoomObject *object)
{
    set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_0221230c, GlowingRoomObject_Delete)

/* func_ov004_02212344 (the destructor, vtable slot 0x40) */
GlowingRoomObject *GlowingRoomObject_Destroy(GlowingRoomObject *object)
{
    set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02212344, GlowingRoomObject_Destroy)

/* func_ov004_02212378 (the constructor): the base, the vtables, the glows (not bound). The state
 * is left as the allocation zeroed it. */
GlowingRoomObject *GlowingRoomObject_Construct(GlowingRoomObject *object)
{
    RoomObject_ConstructBase(&object->base);
    set_vtables(object);
    GlowSet_Construct(&object->glows);
    return object;
}
CLEAN_AS(func_ov004_02212378, GlowingRoomObject_Construct)

/* func_ov004_022123a8: a new one from the room's heap; nothing when it has no room. */
void GlowingRoomObject_Create(void)
{
    GlowingRoomObject *object = RoomObject_Alloc(GLOWING_ROOM_OBJECT_SIZE);
    if (object != NULL) {
        GlowingRoomObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_022123a8, GlowingRoomObject_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters GlowingRoomObject's destructors through
 * its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static GlowingRoomObject *GlowingRoomObject_from_receiver(void *receiver)
{
    return (GlowingRoomObject *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ac2c: the deleting destructor, entered from the receiver part. */
GlowingRoomObject *GlowingRoomObjectReceiver_Delete(void *receiver)
{
    return GlowingRoomObject_Delete(GlowingRoomObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022509acD0Ev, GlowingRoomObjectReceiver_Delete)

/* func_ov004_0221ac48: the destructor, entered from the receiver part. */
GlowingRoomObject *GlowingRoomObjectReceiver_Destroy(void *receiver)
{
    return GlowingRoomObject_Destroy(GlowingRoomObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_022509acD1Ev, GlowingRoomObjectReceiver_Destroy)
