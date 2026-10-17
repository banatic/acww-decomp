/* The room objects that animate in bursts (room_object_periodic.h). */
#include "room_object_periodic.h"

#include "clean.h"
#include "furniture_model.h"
#include "main/frame_ctrl.h"
#include "room_object_anims.h"
#include "room_object_body.h"
#include "room_object_life.h"
#include "room_object_parts.h"

static_assert(offsetof(PeriodicRoomObject, repeats) == 0x844, "repeats");
static_assert(offsetof(PeriodicRoomObject, count) == 0x848, "count");
static_assert(offsetof(PeriodicRoomObject, frames) == 0x84c, "frames");
static_assert(sizeof(PeriodicRoomObject) == 0x850, "the size PeriodicRoomObject_Create allocates");

#define PERIODIC_ROOM_OBJECT_SIZE 0x850
#define ONE 0x1000       /* normal speed, 20.12 fixed point */
#define ANIM_MODE_ONCE 1 /* RoomObject_LoadAnims: stop at the end */
#define SOUND_SHORT_WAIT 0x3fc
#define SOUND_TICK 0x3ff /* played again at joint frame 20 */
#define TICK_FRAME 20
#define SHORT_WAIT 60
#define LONG_WAIT 200

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02252a7c[];
extern const u8 data_ov004_02252b28[];
/* The value the furniture's row has for no sound. */
extern u16 data_ov004_0224fd38;

extern u16 func_ov004_0223a760(int number);
extern void func_ov004_0223cf54(RoomSound *sound, int id, Vec3 *position);
extern unsigned int func_020644cc(int bound); /* a random number below `bound` */

/* Whether the object's sound is one of 0x3f9 to 0x3fc, the ones that make a single burst. */
static int single_burst(int sound)
{
    return sound >= 0x3f9 && sound <= 0x3fc;
}

/* Plays `sound` at the object's centre unless it is no sound. */
static void play(PeriodicRoomObject *object, int sound)
{
    if (sound != data_ov004_0224fd38) {
        func_ov004_0223cf54(&object->base.sound, sound, &object->base.sound.position);
    }
}

/* The whole frames of an animation's length (20.12 fixed point), cut to 16 bits. */
static u16 whole_frames(u32 length)
{
    return (u16) (length >> 12);
}

/* The length of the animation: the visibility animation's when the archive has one (variant
 * 0), else the joint animation's. */
static u16 anim_frames(PeriodicRoomObject *object)
{
    RoomObject *base = &object->base;
    u32 length;
    if (AnimSet_Anim10(FurnitureModel_Anims(&base->model_files), 0) != 0) {
        length = *(const u32 *) (const void *) base->anims[ROOM_ANIM_VISIBILITY].unk_04;
    } else {
        length = (u32) ((const FrameCtrl *) (const void *) base->joint_anim)->end;
    }
    return whole_frames(length);
}

/* Advances the animations; when they were at their end on the last frame and still are, runs
 * them again and counts the run. Whether the burst has had all its runs. */
static int advance(PeriodicRoomObject *object)
{
    int finished = 0;
    int ended = RoomObject_AdvanceAnims(&object->base);
    if (object->ended && ended) {
        RoomObject_PlayAnimsFrom(&object->base, 0, ANIM_MODE_ONCE, ONE, 0);
        object->count++;
        finished = object->count >= object->repeats;
    }
    object->ended = (u8) ended;
    return finished;
}

/* PERIODIC_WAIT: counts the wait down; at its end the first burst starts, with the sound. */
static void update_wait(PeriodicRoomObject *object, int sound, int single)
{
    if (object->wait != 0) {
        object->wait--;
    }
    if (object->wait == 0) {
        object->phase = PERIODIC_BURST_1;
        object->count = 0;
        object->ended = 0;
        if (single) {
            object->frames = 0;
        }
        play(object, sound);
    }
}

/* func_ov004_02211c80 (vtable slot 0x0c) */
int PeriodicRoomObject_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02211c80, PeriodicRoomObject_Vfunc0C)

/* func_ov004_02211c84 (vtable slot 0x80, each frame while neither appearing nor vanishing).
 * Phases 2 and 3 do nothing with sounds 0x3f9 to 0x3fc, and phases above 3 nothing at all. */
int PeriodicRoomObject_Update(PeriodicRoomObject *object)
{
    int sound = func_ov004_0223a760(RoomObject_Number(&object->base));
    if (single_burst(sound)) {
        if (object->phase == PERIODIC_WAIT) {
            update_wait(object, sound, 1);
        } else if (object->phase == PERIODIC_BURST_1) {
            object->frames++;
            if (advance(object)) {
                object->phase = PERIODIC_WAIT;
                object->wait = sound == SOUND_SHORT_WAIT ? SHORT_WAIT : LONG_WAIT;
            }
        }
    } else if (object->phase == PERIODIC_WAIT) {
        update_wait(object, sound, 0);
    } else if (object->phase <= PERIODIC_BURST_3) {
        /* the joint animation's last step, before this frame's */
        const FrameCtrl *joints = (const FrameCtrl *) (const void *) object->base.joint_anim;
        if (sound == SOUND_TICK && FrameCtrl_Passed(joints, TICK_FRAME)) {
            play(object, sound);
        }
        if (advance(object)) {
            object->phase = (u8) ((object->phase + 1) & 3);
            object->count = 0;
            if (object->phase != PERIODIC_WAIT) {
                play(object, sound);
            } else {
                object->wait = (u16) (object->repeats * anim_frames(object));
            }
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02211c84, PeriodicRoomObject_Update)

/* func_ov004_02211ed4 (vtable slot 0x7c, once the model is bound): binds the animation of
 * variant 0, sets the runs of a burst by the sound and the first wait at random (none in mode
 * 1); done at once. */
int PeriodicRoomObject_Start(PeriodicRoomObject *object)
{
    RoomObject *base = &object->base;
    RoomObject_LoadAnims(base, 0, ANIM_MODE_ONCE, ONE, 0);
    int sound = func_ov004_0223a760(RoomObject_Number(base));
    switch (sound) {
        case 0x3f9:
        case 0x3fa:
        case 0x3fb:
            object->count = 4;
            break;
        case SOUND_SHORT_WAIT:
            object->count = 2;
            break;
        default:
            object->count = 1;
            break;
    }
    object->repeats = object->count;
    object->phase = PERIODIC_WAIT;
    object->wait = 0;
    if (base->unk_76C != 1) {
        if (sound == SOUND_SHORT_WAIT) {
            object->wait = (u16) func_020644cc(SHORT_WAIT);
        } else if (single_burst(sound)) {
            object->wait = (u16) func_020644cc(LONG_WAIT);
        } else {
            object->wait = (u16) func_020644cc(RoomObject_AnimFrames(base, 0) * object->repeats);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02211ed4, PeriodicRoomObject_Start)

static void set_vtables(PeriodicRoomObject *object)
{
    object->base.vtable = (const RoomObjectVtable *) data_ov004_02252a7c;
    object->base.receiver_vtable = data_ov004_02252b28;
}

/* func_ov004_02211fdc (the deleting destructor, vtable slot 0x44) */
PeriodicRoomObject *PeriodicRoomObject_Delete(PeriodicRoomObject *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    RoomObject_Free(object);
    return object;
}
CLEAN_AS(func_ov004_02211fdc, PeriodicRoomObject_Delete)

/* func_ov004_02212008 (the destructor, vtable slot 0x40) */
PeriodicRoomObject *PeriodicRoomObject_Destroy(PeriodicRoomObject *object)
{
    set_vtables(object);
    RoomObject_DestructBase(&object->base);
    return object;
}
CLEAN_AS(func_ov004_02212008, PeriodicRoomObject_Destroy)

/* func_ov004_0221202c (the constructor). Its own fields are left as the allocation zeroed
 * them. */
PeriodicRoomObject *PeriodicRoomObject_Construct(PeriodicRoomObject *object)
{
    RoomObject_ConstructBase(&object->base);
    set_vtables(object);
    return object;
}
CLEAN_AS(func_ov004_0221202c, PeriodicRoomObject_Construct)

/* func_ov004_02212050: a new one from the room's heap; nothing when it has no room. */
void PeriodicRoomObject_Create(void)
{
    PeriodicRoomObject *object = RoomObject_Alloc(PERIODIC_ROOM_OBJECT_SIZE);
    if (object != NULL) {
        PeriodicRoomObject_Construct(object);
    }
}
CLEAN_AS(func_ov004_02212050, PeriodicRoomObject_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters PeriodicRoomObject's destructors through
 * its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static PeriodicRoomObject *PeriodicRoomObject_from_receiver(void *receiver)
{
    return (PeriodicRoomObject *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221ac64: the deleting destructor, entered from the receiver part. */
PeriodicRoomObject *PeriodicRoomObjectReceiver_Delete(void *receiver)
{
    return PeriodicRoomObject_Delete(PeriodicRoomObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252a7cD0Ev, PeriodicRoomObjectReceiver_Delete)

/* func_ov004_0221ac80: the destructor, entered from the receiver part. */
PeriodicRoomObject *PeriodicRoomObjectReceiver_Destroy(void *receiver)
{
    return PeriodicRoomObject_Destroy(PeriodicRoomObject_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02252a7cD1Ev, PeriodicRoomObjectReceiver_Destroy)
