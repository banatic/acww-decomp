/* The room objects of vtable 0x0225130c (room_object_0225130c.h). */
#include "room_object_0225130c.h"

#include <stdint.h>

#include "clean.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "room_object_parts.h"

static_assert(offsetof(RoomObject0225130c, ticks) == 0x845, "ticks");
static_assert(offsetof(RoomObject0225130c, settle_reset) == 0x846, "settle reset");
static_assert(offsetof(RoomObject0225130c, state) == 0x847, "state");
static_assert(sizeof(RoomObject0225130c) == 0x848, "the size RoomObject0225130c_Create allocates");

#define ROOM_OBJECT_0225130C_SIZE 0x848
#define ONE 0x1000       /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0 /* RoomObject_PlayAnimsFrom: start again at the end */
#define ANIM_MODE_ONCE 1
#define ANIM_MODE_3 3       /* the animations' mode 3 */
#define KEEP_FRAME 0xffff   /* RoomObject_PlayAnimsFrom: each animation keeps its frame */
#define SLOT_70_VALUE 0xff  /* the second argument given with a state (vtable slot 0x70) */
#define RUNNING_SOUND 0x42a /* the sound kept playing at its centre */
#define TICK_FRAME 0x14     /* the joint animation's frame where the sound's variable changes */

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_0225703c;
extern MemberPointer data_ov004_02257534[ROOM_OBJECT_0225130C_STATE_COUNT];
extern const MemberPointer data_ov004_022500b8, data_ov004_022501f8, data_ov004_02250200, data_ov004_02250630,
    data_ov004_02250220;
extern u32 data_ov004_0225700c;
extern MemberPointer data_ov004_0225750c[ROOM_OBJECT_0225130C_STATE_COUNT];
extern const MemberPointer data_ov004_02250120, data_ov004_022500d8, data_ov004_02250430, data_ov004_022500e8,
    data_ov004_02250308;

/* Whether each state shows the object on (for vtable slot 0x74). */
extern const u8 data_ov004_0224769c[ROOM_OBJECT_0225130C_STATE_COUNT];

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_0225130c[];
extern const u8 data_ov004_022513b8[];

/* Plays sound `id` at `position` while the sound plays; sets variable 0 of its player while it
 * plays. */
extern void func_ov004_0223cf40(RoomSound *sound, int id, Vec3 *position);
extern void func_ov004_0223cf18(RoomSound *sound, s16 value);
/* Whether the joint animation is at `frame`. */
extern int func_02056f28(void *anim, int frame);
/* Request a state for the object at the object's cell (only when data_020e54a8 is 1). */
extern int func_0205265c(unsigned int object, int state, int a2, int a3);
/* Whether func_020b6730 says so or the area (func_020b65c4) is 10 or 15. */
extern int func_ov004_0223c10c(void);

static unsigned int RoomObject0225130c_address(RoomObject0225130c *object)
{
    return (unsigned int) (uintptr_t) object;
}

/* Vtable slot 0x70: RoomObject0225130c_EnterState for this class. */
static void RoomObject0225130c_switch_to(RoomObject0225130c *object, int state)
{
    object->base.vtable->vfunc_70(&object->base, state, SLOT_70_VALUE);
}

/* Keeps the running sound playing at the object's centre (unless unk_76C is 2). */
static void RoomObject0225130c_keep_sound(RoomObject0225130c *object)
{
    if (!RoomObject_Unk76CIs2(&object->base)) {
        func_ov004_0223cf40(&object->base.sound, RUNNING_SOUND, &object->base.sound.position);
    }
}

/* At frame 0 of the joint animation the sound's variable is set to 1; at frame 0x14 to 1 and 2
 * in turn (unless unk_76C is 2). */
static void RoomObject0225130c_tick(RoomObject0225130c *object)
{
    if (RoomObject_Unk76CIs2(&object->base)) {
        return;
    }
    if (func_02056f28(object->base.joint_anim, 0)) {
        func_ov004_0223cf18(&object->base.sound, 1);
    } else if (func_02056f28(object->base.joint_anim, TICK_FRAME)) {
        func_ov004_0223cf18(&object->base.sound, (object->ticks & 1) != 0 ? 2 : 1);
        object->ticks++;
    }
}

/* func_ov004_02212a14 (update of SETTLING): the sound, its variable set to 1 once; the switch
 * off; off once the animations end. */
void RoomObject0225130c_UpdateSettling(RoomObject0225130c *object)
{
    if (!RoomObject_Unk76CIs2(&object->base)) {
        func_ov004_0223cf40(&object->base.sound, RUNNING_SOUND, &object->base.sound.position);
        if (object->settle_reset != 0) {
            func_ov004_0223cf18(&object->base.sound, 1);
            object->settle_reset = 0;
        }
    }
    Switch_Set(&object->base.light_switch, 0, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject0225130c_switch_to(object, ROOM_OBJECT_0225130C_OFF);
    }
}
CLEAN_AS(func_ov004_02212a14, RoomObject0225130c_UpdateSettling)

/* func_ov004_02212a84 (entry of SETTLING): the switch off (shown at once) and the animations
 * of variant 0 from their end in mode 3. */
int RoomObject0225130c_EnterSettling(RoomObject0225130c *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 0, ANIM_MODE_3, ONE);
    object->settle_reset = 1;
    return 1;
}
CLEAN_AS(func_ov004_02212a84, RoomObject0225130c_EnterSettling)

/* func_ov004_02212ab8 (update of STOPPING): the sound; the switch off; the sound's variable as
 * the joint animation goes; settling once the animations end. */
void RoomObject0225130c_UpdateStopping(RoomObject0225130c *object)
{
    RoomObject0225130c_keep_sound(object);
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject0225130c_tick(object);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject0225130c_switch_to(object, ROOM_OBJECT_0225130C_SETTLING);
    }
}
CLEAN_AS(func_ov004_02212ab8, RoomObject0225130c_UpdateStopping)

/* func_ov004_02212b70 (entry of STOPPING): the switch off (shown at once), the sound at 4 and
 * the animations of variant 1 once, each from the frame it is at. */
int RoomObject0225130c_EnterStopping(RoomObject0225130c *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlaySound2(&object->base);
    RoomObject_PlayAnimsFrom(&object->base, 1, ANIM_MODE_ONCE, ONE, KEEP_FRAME);
    return 1;
}
CLEAN_AS(func_ov004_02212b70, RoomObject0225130c_EnterStopping)

/* func_ov004_02212bb0 (update of RUNNING): the sound; the animations; the sound's variable as
 * the joint animation goes; touched, it requests STOPPING. */
void RoomObject0225130c_UpdateRunning(RoomObject0225130c *object)
{
    RoomObject0225130c_keep_sound(object);
    RoomObject_AdvanceAnims(&object->base);
    RoomObject0225130c_tick(object);
    if (Switch_IsPending(&object->base.light_switch)) {
        func_0205265c(RoomObject0225130c_address(object), ROOM_OBJECT_0225130C_STOPPING, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_02212bb0, RoomObject0225130c_UpdateRunning)

/* func_ov004_02212c64 (entry of RUNNING): the switch on (shown at once) and the animations of
 * variant 1 in a loop from their end. */
int RoomObject0225130c_EnterRunning(RoomObject0225130c *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFromEnd(&object->base, 1, ANIM_MODE_LOOP, ONE);
    return 1;
}
CLEAN_AS(func_ov004_02212c64, RoomObject0225130c_EnterRunning)

/* func_ov004_02212c90 (update of STARTING): the sound; the switch on; running once the
 * animations end. */
void RoomObject0225130c_UpdateStarting(RoomObject0225130c *object)
{
    RoomObject0225130c_keep_sound(object);
    Switch_Set(&object->base.light_switch, 1, 0);
    if (RoomObject_AdvanceAnims(&object->base)) {
        RoomObject0225130c_switch_to(object, ROOM_OBJECT_0225130C_RUNNING);
    }
}
CLEAN_AS(func_ov004_02212c90, RoomObject0225130c_UpdateStarting)

/* func_ov004_02212ce4 (entry of STARTING): the switch on (shown at once), the animations of
 * variant 0 once from the start and the sound at 2. */
int RoomObject0225130c_EnterStarting(RoomObject0225130c *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_02212ce4, RoomObject0225130c_EnterStarting)

/* func_ov004_02212d1c (update of OFF): touched, it requests STARTING. */
void RoomObject0225130c_UpdateOff(RoomObject0225130c *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        func_0205265c(RoomObject0225130c_address(object), ROOM_OBJECT_0225130C_STARTING, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_02212d1c, RoomObject0225130c_UpdateOff)

/* func_ov004_02212d44 (entry of OFF): the switch off (shown at once) and the animations of
 * variant 0 in mode 3 from the start. */
int RoomObject0225130c_EnterOff(RoomObject0225130c *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_3, ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_02212d44, RoomObject0225130c_EnterOff)

/* _ZN18Obj_ov004_0225130c19func_ov004_02212d78Ev: the state's update, through its table. */
void RoomObject0225130c_UpdateState(RoomObject0225130c *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_0225130C_STATE_COUNT] = {
        &data_ov004_022500b8, /* RoomObject0225130c_UpdateOff */
        &data_ov004_022501f8, /* RoomObject0225130c_UpdateStarting */
        &data_ov004_02250200, /* RoomObject0225130c_UpdateRunning */
        &data_ov004_02250630, /* RoomObject0225130c_UpdateStopping */
        &data_ov004_02250220, /* RoomObject0225130c_UpdateSettling */
    };
    MemberTable_InitOnce(&data_ov004_0225703c, data_ov004_02257534, updates, ROOM_OBJECT_0225130C_STATE_COUNT);
    if (object->state < ROOM_OBJECT_0225130C_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257534[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225130c19func_ov004_02212d78Ev, RoomObject0225130c_UpdateState)

/* func_ov004_02212e10 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 5 and above do not exist. */
int RoomObject0225130c_EnterState(RoomObject0225130c *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_0225130C_STATE_COUNT] = {
        &data_ov004_02250120, /* RoomObject0225130c_EnterOff */
        &data_ov004_022500d8, /* RoomObject0225130c_EnterStarting */
        &data_ov004_02250430, /* RoomObject0225130c_EnterRunning */
        &data_ov004_022500e8, /* RoomObject0225130c_EnterStopping */
        &data_ov004_02250308, /* RoomObject0225130c_EnterSettling */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_0225700c, data_ov004_0225750c, entries, ROOM_OBJECT_0225130C_STATE_COUNT);
    if (state < ROOM_OBJECT_0225130C_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225750c[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02212e10, RoomObject0225130c_EnterState)

/* func_ov004_02212ebc (vtable slot 0x74): whether `state` shows the object on (starting and
 * running do); 0 for a state that does not exist. */
u8 RoomObject0225130c_StateIsOn(RoomObject0225130c *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_0225130C_STATE_COUNT) {
        return data_ov004_0224769c[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_02212ebc, RoomObject0225130c_StateIsOn)

/* func_ov004_02212ed0 (vtable slot 0x0c) */
int RoomObject0225130c_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02212ed0, RoomObject0225130c_Vfunc0C)

/* func_ov004_02212ed4 (vtable slot 0x84, each frame while appearing or vanishing): the sound,
 * but not while vanishing. */
int RoomObject0225130c_UpdateUnsettled(RoomObject0225130c *object)
{
    if (!RoomObject_Unk76CIs2(&object->base) && !RoomObject_IsVanishing(&object->base)) {
        func_ov004_0223cf40(&object->base.sound, RUNNING_SOUND, &object->base.sound.position);
    }
    return 1;
}
CLEAN_AS(func_ov004_02212ed4, RoomObject0225130c_UpdateUnsettled)

/* _ZN18Obj_ov004_0225130c19func_ov004_02212f0cEv (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the state's update. */
int RoomObject0225130c_Update(RoomObject0225130c *object)
{
    RoomObject0225130c_UpdateState(object);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_0225130c19func_ov004_02212f0cEv, RoomObject0225130c_Update)

/* func_ov004_02212f1c (vtable slot 0x7c, once the model is bound): binds the animations of
 * variant 0 (once, from the start); running when the switch is on and func_ov004_0223c10c says
 * no, else off; done at once. */
int RoomObject0225130c_Start(RoomObject0225130c *object)
{
    object->unk_844 = 0;
    RoomObject_LoadAnims(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
    if (Switch_Value(&object->base.light_switch) != 0 && !func_ov004_0223c10c()) {
        RoomObject0225130c_switch_to(object, ROOM_OBJECT_0225130C_RUNNING);
    } else {
        RoomObject0225130c_switch_to(object, ROOM_OBJECT_0225130C_OFF);
    }
    return 1;
}
CLEAN_AS(func_ov004_02212f1c, RoomObject0225130c_Start)

static void RoomObject0225130c_set_vtables(RoomObject0225130c *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_0225130c;
    object->base.receiver_vtable = data_ov004_022513b8;
}

/* func_ov004_02212f78 (the deleting destructor, vtable slot 0x44) */
RoomObject0225130c *RoomObject0225130c_Delete(RoomObject0225130c *object)
{
    RoomObject0225130c_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02212f78, RoomObject0225130c_Delete)

/* func_ov004_02212fa4 (the destructor, vtable slot 0x40) */
RoomObject0225130c *RoomObject0225130c_Destroy(RoomObject0225130c *object)
{
    RoomObject0225130c_set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02212fa4, RoomObject0225130c_Destroy)

/* func_ov004_02212fc8 (the constructor). Its own fields are left as the allocation zeroed
 * them. */
RoomObject0225130c *RoomObject0225130c_Construct(RoomObject0225130c *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject0225130c_set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_02212fc8, RoomObject0225130c_Construct)

/* func_ov004_02212fec: a new one from the room's heap; nothing when it has no room. */
void RoomObject0225130c_Create(void)
{
    RoomObject0225130c *object = RoomObject_Alloc(ROOM_OBJECT_0225130C_SIZE);
    if (object != NULL) {
        RoomObject0225130c_Construct(object);
    }
}
CLEAN_AS(func_ov004_02212fec, RoomObject0225130c_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject0225130c's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject0225130c *RoomObject0225130c_from_receiver(void *receiver)
{
    return (RoomObject0225130c *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ab14: the deleting destructor, entered from the receiver part. */
RoomObject0225130c *RoomObject0225130cReceiver_Delete(void *receiver)
{
    return RoomObject0225130c_Delete(RoomObject0225130c_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225130cD0Ev, RoomObject0225130cReceiver_Delete)

/* func_ov004_0221ab30: the destructor, entered from the receiver part. */
RoomObject0225130c *RoomObject0225130cReceiver_Destroy(void *receiver)
{
    return RoomObject0225130c_Destroy(RoomObject0225130c_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_0225130cD1Ev, RoomObject0225130cReceiver_Destroy)
