/* The room objects of vtable 0x02252f2c (room_object_02252f2c.h). */
#include "room_object_02252f2c.h"

#include <stdint.h>

#include "clean.h"
#include "main/frame_ctrl.h"
#include "member_pointer.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "main/main_random.h"
#include "main/room_sync.h"
#include "room_sound.h"

static_assert(offsetof(RoomObject02252f2c, state) == 0x844, "state");
static_assert(offsetof(RoomObject02252f2c, glows) == 0x848, "glows");
static_assert(sizeof(RoomObject02252f2c) == 0x8a0, "the size of the class");
static_assert(offsetof(RoomObject, sound) == 0x798, "sound");

#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* the animations start again at the end */
#define SLOT_70_VALUE 0xff /* the second argument given with a state (vtable slot 0x70) */

/* The furniture numbers (RoomObject_Number) with a sound of their own, and those sounds. */
#define FURNITURE_0123 0x123
#define FURNITURE_01FB 0x1fb
#define FURNITURE_01FC 0x1fc
#define SOUND_0123 0x429
#define SOUND_01FB 0x42b
#define SOUND_01FC 0x42c

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02257068;
extern MemberPointer data_ov004_02257174[ROOM_OBJECT_02252F2C_STATE_COUNT];
extern const MemberPointer data_ov004_02250460, data_ov004_022502c0;
extern u32 data_ov004_02256ffc;
extern MemberPointer data_ov004_02257164[ROOM_OBJECT_02252F2C_STATE_COUNT];
extern const MemberPointer data_ov004_02250628, data_ov004_02250580;

/* Whether each state shows the object on (for vtable slot 0x74): ON does. */
extern const u8 data_ov004_0224766c[ROOM_OBJECT_02252F2C_STATE_COUNT];

/* Whether the joint animation's last step reached `frame`. */
static int RoomObject02252f2c_joints_passed(RoomObject02252f2c *object, int frame)
{
    return FrameCtrl_Passed(&object->base.model.frames, frame);
}

/* Sound `id` at the object's point, unless RoomObject.unk_76C is 2; whether it was played. */
static int RoomObject02252f2c_play_sound(RoomObject02252f2c *object, int id)
{
    RoomObject *base = &object->base;
    if (RoomObject_Unk76CIs2(base)) {
        return 0;
    }
    RoomSound_PlayAt(&base->sound, id, &base->sound.position);
    return 1;
}

/* func_ov004_0221a150 (update of ON): the same as OFF's, requesting OFF. */
void RoomObject02252f2c_UpdateOn(RoomObject02252f2c *object)
{
    RoomObject02252f2c_UpdateOff(object);
}
CLEAN_AS(func_ov004_0221a150, RoomObject02252f2c_UpdateOn)

/* func_ov004_0221a158 (entry of ON): the switch on (shown at once) and the sound at 2. */
int RoomObject02252f2c_EnterOn(RoomObject02252f2c *object)
{
    Switch_Set(&object->base.light_switch, 1, 0);
    RoomObject_PlaySound1(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_0221a158, RoomObject02252f2c_EnterOn)

/* func_ov004_0221a17c (update of OFF, and of ON through RoomObject02252f2c_UpdateOn): with a
 * change of the switch pending, requests the other state (the state plus one, its low bit). */
void RoomObject02252f2c_UpdateOff(RoomObject02252f2c *object)
{
    if (Switch_IsPending(&object->base.light_switch)) {
        int other = (object->state + 1) & 1;
        RoomSync_RequestState(&object->base, other, SLOT_70_VALUE, 1);
    }
}
CLEAN_AS(func_ov004_0221a17c, RoomObject02252f2c_UpdateOff)

/* func_ov004_0221a1b0 (entry of OFF): the switch off (shown at once) and the sound at 4. */
int RoomObject02252f2c_EnterOff(RoomObject02252f2c *object)
{
    Switch_Set(&object->base.light_switch, 0, 0);
    RoomObject_PlaySound2(&object->base);
    return 1;
}
CLEAN_AS(func_ov004_0221a1b0, RoomObject02252f2c_EnterOff)

/* _ZN18Obj_ov004_02252f2c19func_ov004_0221a1d4Ev: the state's update, through its table. */
void RoomObject02252f2c_UpdateState(RoomObject02252f2c *object)
{
    static const MemberPointer *const updates[ROOM_OBJECT_02252F2C_STATE_COUNT] = {
        &data_ov004_02250460, /* RoomObject02252f2c_UpdateOff */
        &data_ov004_022502c0, /* RoomObject02252f2c_UpdateOn */
    };
    MemberTable_InitOnce(&data_ov004_02257068, data_ov004_02257174, updates, ROOM_OBJECT_02252F2C_STATE_COUNT);
    if (object->state < ROOM_OBJECT_02252F2C_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_02257174[object->state], object);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02252f2c19func_ov004_0221a1d4Ev, RoomObject02252f2c_UpdateState)

/* func_ov004_0221a240 (vtable slot 0x70): the base class's (RoomObject_SetUnk77C, given `state`
 * and `value`), then enters `state` if its entry (through a table) agrees; whether it did.
 * States 2 and above do not exist. */
int RoomObject02252f2c_EnterState(RoomObject02252f2c *object, unsigned int state, int value)
{
    static const MemberPointer *const entries[ROOM_OBJECT_02252F2C_STATE_COUNT] = {
        &data_ov004_02250628, /* RoomObject02252f2c_EnterOff */
        &data_ov004_02250580, /* RoomObject02252f2c_EnterOn */
    };
    RoomObject_SetUnk77C(&object->base, (int) state, value);
    MemberTable_InitOnce(&data_ov004_02256ffc, data_ov004_02257164, entries, ROOM_OBJECT_02252F2C_STATE_COUNT);
    if (state < ROOM_OBJECT_02252F2C_STATE_COUNT && MemberPointer_CallInt(&data_ov004_02257164[state], object) != 0) {
        object->state = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221a240, RoomObject02252f2c_EnterState)

/* func_ov004_0221a2c4 (vtable slot 0x74): whether `state` shows the object on (ON does); 0 for a
 * state that does not exist. */
u8 RoomObject02252f2c_StateIsOn(RoomObject02252f2c *object, unsigned int state)
{
    (void) object;
    if (state < ROOM_OBJECT_02252F2C_STATE_COUNT) {
        return data_ov004_0224766c[state];
    }
    return 0;
}
CLEAN_AS(func_ov004_0221a2c4, RoomObject02252f2c_StateIsOn)

/* func_ov004_0221a2d8 (vtable slot 0x0c) */
int RoomObject02252f2c_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221a2d8, RoomObject02252f2c_Vfunc0C)

/* _ZN18Obj_ov004_02252f2c19func_ov004_0221a2dcEv (vtable slot 0x80, each frame while neither
 * appearing nor vanishing): the animations (with unk_780 at 1), each glow's frame and the glows
 * on (at once), FurnitureInfo_IndoorBit6 of its number and the state's update. Then, unless unk_76C is 2,
 * furniture 0x123 plays sound 0x429 at its point, setting the sound's variable to 1 at frame
 * 0x43 of the joint animation; 0x1fb plays 0x42b, 1 at frame 4 and 2 at frame 0x16; 0x1fc plays
 * 0x42c, 1 at frames 5 and 0x12. Other furniture plays the sound at 0. */
int RoomObject02252f2c_Update(RoomObject02252f2c *object)
{
    RoomObject *base = &object->base;
    if (base->unk_780 == 1) {
        RoomObject_AdvanceAnims(base);
    }
    GlowSet_Update(&object->glows);
    GlowSet_Switch(&object->glows, 1, 0, 0);
    RoomObject_Lookup020537a8(base);
    RoomObject02252f2c_UpdateState(object);
    switch (RoomObject_Number(base)) {
        case FURNITURE_0123:
            if (RoomObject02252f2c_play_sound(object, SOUND_0123)) {
                if (RoomObject02252f2c_joints_passed(object, 0x43)) {
                    RoomSound_SetVariable(&base->sound, 1);
                }
            }
            break;
        case FURNITURE_01FB:
            if (RoomObject02252f2c_play_sound(object, SOUND_01FB)) {
                if (RoomObject02252f2c_joints_passed(object, 4)) {
                    RoomSound_SetVariable(&base->sound, 1);
                } else if (RoomObject02252f2c_joints_passed(object, 0x16)) {
                    RoomSound_SetVariable(&base->sound, 2);
                }
            }
            break;
        case FURNITURE_01FC:
            if (RoomObject02252f2c_play_sound(object, SOUND_01FC)) {
                if (RoomObject02252f2c_joints_passed(object, 5) || RoomObject02252f2c_joints_passed(object, 0x12)) {
                    RoomSound_SetVariable(&base->sound, 1);
                }
            }
            break;
        default:
            RoomObject_PlaySound0(base);
            break;
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02252f2c19func_ov004_0221a2dcEv, RoomObject02252f2c_Update)

/* func_ov004_0221a420 (vtable slot 0x7c, once the model is bound): with unk_780 at 1, binds the
 * animations of variant 0 in a loop from a random frame below their frame count (from the start
 * when unk_76C is 1; the count is read either way) and the glows lit. Then enters ON when the
 * switch is on, OFF otherwise; done at once. */
int RoomObject02252f2c_Start(RoomObject02252f2c *object)
{
    RoomObject *base = &object->base;
    if (base->unk_780 == 1) {
        int frames = RoomObject_AnimFrames(base, 0);
        int start;
        if (base->unk_76C == 1) {
            start = 0;
        } else {
            start = MainRandom_Below(frames);
        }
        RoomObject_LoadAnims(base, 0, ANIM_MODE_LOOP, ONE, (u16) start);
        GlowSet_Bind(&object->glows, base->model_resource, 1);
    }
    if (Switch_Value(&base->light_switch) != 0) {
        base->vtable->vfunc_70(base, ROOM_OBJECT_02252F2C_ON, SLOT_70_VALUE);
    } else {
        base->vtable->vfunc_70(base, ROOM_OBJECT_02252F2C_OFF, SLOT_70_VALUE);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221a420, RoomObject02252f2c_Start)

#define ROOM_OBJECT_02252F2C_SIZE 0x8a0

/* The class's vtable and its receiver part's (at 0xec). */
extern const u8 data_ov004_02252f2c[];
extern const u8 data_ov004_02252fd8[];

static void RoomObject02252f2c_set_vtables(RoomObject02252f2c *object)
{
    object->base.vtable = (const RoomObjectVtable *) (const void *) data_ov004_02252f2c;
    object->base.receiver_vtable = data_ov004_02252fd8;
}

/* func_ov004_0221a4ac (the deleting destructor, vtable slot 0x44): the vtables back to the
 * class's, the glows taken down, the base taken down and the block freed. */
RoomObject02252f2c *RoomObject02252f2c_Delete(RoomObject02252f2c *object)
{
    RoomObject02252f2c_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_0221a4ac, RoomObject02252f2c_Delete)

/* func_ov004_0221a4e4 (the destructor, vtable slot 0x40): as RoomObject02252f2c_Delete, without
 * freeing the block. */
RoomObject02252f2c *RoomObject02252f2c_Destroy(RoomObject02252f2c *object)
{
    RoomObject02252f2c_set_vtables(object);
    GlowSet_Destruct(&object->glows);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_0221a4e4, RoomObject02252f2c_Destroy)

/* func_ov004_0221a518 (the constructor): the base, the vtables, the glows (not bound). The state
 * is left as the allocation zeroed it. */
RoomObject02252f2c *RoomObject02252f2c_Construct(RoomObject02252f2c *object)
{
    RoomObject_ConstructBase(&object->base);
    RoomObject02252f2c_set_vtables(object);
    GlowSet_Construct(&object->glows);
    return object;
}
CLEAN_AS(func_ov004_0221a518, RoomObject02252f2c_Construct)

/* func_ov004_0221a548: a new one from the room's heap; nothing when it has no room. */
void RoomObject02252f2c_Create(void)
{
    RoomObject02252f2c *object = RoomObject_Alloc(ROOM_OBJECT_02252F2C_SIZE);
    if (object != NULL) {
        RoomObject02252f2c_Construct(object);
    }
}
CLEAN_AS(func_ov004_0221a548, RoomObject02252f2c_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters RoomObject02252f2c's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static RoomObject02252f2c *RoomObject02252f2c_from_receiver(void *receiver)
{
    return (RoomObject02252f2c *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a564: the deleting destructor, entered from the receiver part. */
RoomObject02252f2c *RoomObject02252f2cReceiver_Delete(void *receiver)
{
    return RoomObject02252f2c_Delete(RoomObject02252f2c_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252f2cD0Ev, RoomObject02252f2cReceiver_Delete)

/* func_ov004_0221a580: the destructor, entered from the receiver part. */
RoomObject02252f2c *RoomObject02252f2cReceiver_Destroy(void *receiver)
{
    return RoomObject02252f2c_Destroy(RoomObject02252f2c_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252f2cD1Ev, RoomObject02252f2cReceiver_Destroy)
