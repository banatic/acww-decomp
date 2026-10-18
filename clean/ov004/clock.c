/* The clocks (clock.h). */
#include "clock.h"

#include <stdint.h>

#include "clean.h"
#include "furniture_model.h"
#include "room_object_anims.h"
#include "room_object_life.h"
#include "room_object_methods.h"
#include "room_object_parts.h"
#include "main/animated_model.h"
#include "main/calendar.h"
#include "main/frame_ctrl.h"
#include "main/model_pool.h"
#include "room_manager.h"
#include "room_objects.h"
#include "room_sound.h"

static_assert(offsetof(Clock, strikes) == 0x844, "strikes");
static_assert(offsetof(Clock, time) == 0x846, "time");
static_assert(offsetof(Clock, last_time) == 0x848, "last time");
static_assert(offsetof(Clock, nearest) == 0x84a, "nearest");
static_assert(offsetof(Clock, nearest_striker) == 0x84b, "nearest striker");
static_assert(sizeof(Clock) == 0x84c, "the size Clock_Create allocates");
static_assert(offsetof(RoomObject, model_files) == 0x6cc, "the model files");

#define CLOCK_SIZE 0x84c
#define ONE 0x1000         /* normal speed, 20.12 fixed point */
#define ANIM_MODE_LOOP 0   /* start again at the end */
#define ANIM_MODE_ONCE 1   /* stop at the end */
#define KIND_STRIKING 0x10 /* RoomObject.unk_780 of the clocks that strike the hours */
#define KIND_SHARED 0x11   /* of those that show the shared frame counter */
#define KIND_ANIMATED 0x2b /* of those that advance their animations */
#define NO_STRIKES (-1)
#define STRIKE_SOUND 0x42d
#define TICK_SOUND 0x4d0
#define TICK_FRAME_1 9 /* the shared counter's frames a clock ticks at */
#define TICK_FRAME_2 0x1d

/* The class's vtables, and its receiver part's. */
extern const u8 data_ov004_02251d98[];
extern const u8 data_ov004_02251e44[];

/* The joint animation of the furniture's archive, variant 0. */
static const AnimFile *Clock_joint_file(Clock *clock)
{
    return (const AnimFile *) (uintptr_t) (u32) AnimSet_Anim00(FurnitureModel_Anims(&clock->base.model_files), 0);
}

/* One strike: the joint animation played once from the start. */
static void Clock_play_strike(Clock *clock)
{
    AnimatedModel_Start(&clock->base.model, (const u8 *) Clock_joint_file(clock), ANIM_MODE_ONCE, ONE, 0, 0);
}

/* func_ov004_022168d8: marks the clock as the nearest striking clock to the player, for this
 * frame. */
Clock *Clock_MarkNearestStriker(Clock *clock)
{
    clock->nearest_striker = 1;
    return clock;
}
CLEAN_AS(func_ov004_022168d8, Clock_MarkNearestStriker)

/* func_ov004_022168e4: marks the clock as the nearest clock to the player, for this frame. */
Clock *Clock_MarkNearest(Clock *clock)
{
    clock->nearest = 1;
    return clock;
}
CLEAN_AS(func_ov004_022168e4, Clock_MarkNearest)

/* func_ov004_022168f0 (vtable slot 0x6c, the model's hook after a node's description): turns
 * the hands. */
void Clock_NodeDescAfterHook(Clock *clock, int node, NodeHookState *state)
{
    RoomObject_ClockHandsHook(&clock->base, node, state);
}
CLEAN_AS(func_ov004_022168f0, Clock_NodeDescAfterHook)

/* func_ov004_022168f8 (vtable slot 0x0c) */
int Clock_Vfunc0C(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022168f8, Clock_Vfunc0C)

/* The striking of a clock of kind 0x10, each frame. The nearest striking clock sets variable 1
 * of its sound when its count changes (not in mode 2). With no strikes left, a new hour (not in
 * the areas RoomObjects_InNookOrScene0AOr0F names) starts the strikes of the hour, 12 for 0; in mode 2 one
 * strike at once. While strikes are left each frame plays the strike sound and advances the
 * animation; at its end the next strike starts, and the count goes down (not in mode 2). */
static void Clock_strike(Clock *clock)
{
    RoomObject *base = &clock->base;
    if (!RoomObject_Unk76CIs2(base) && clock->strikes >= 0 && clock->strikes != clock->last_strikes &&
        clock->nearest_striker) {
        RoomSound_SetVariable(&base->sound, 1);
    }
    clock->last_strikes = clock->strikes;
    if (clock->strikes == NO_STRIKES) {
        if (RoomObject_Unk76CIs2(base)) {
            clock->strikes = 1;
        } else if (!RoomObjects_InNookOrScene0AOr0F() && clock->last_time.hour != clock->time.hour) {
            clock->strikes = (s8) (clock->time.hour % 12);
            if (clock->strikes == 0) {
                clock->strikes = 12;
            }
            if (!RoomObject_Unk76CIs2(base)) {
                RoomSound_PlayAt(&base->sound, STRIKE_SOUND, &base->sound.position);
            }
            Clock_play_strike(clock);
        }
    } else if (clock->strikes > 0) {
        if (!RoomObject_Unk76CIs2(base)) {
            RoomSound_PlayAt(&base->sound, STRIKE_SOUND, &base->sound.position);
        }
        AnimatedModel_Update(&base->model);
        if (FrameCtrl_IsDone(&base->model.frames)) {
            Clock_play_strike(clock);
            if (!RoomObject_Unk76CIs2(base)) {
                clock->strikes--;
            }
            if (clock->strikes == 0) {
                clock->strikes = NO_STRIKES;
            }
        }
    }
}

/* func_ov004_022168fc (vtable slot 0x80, each frame while neither appearing nor vanishing): the
 * time read (the last one kept); the striking of kind 0x10, the animations of kind 0x2b, the
 * shared frame on kind 0x11; the tick of the nearest clock at frames 9 and 0x1d (sound 0x4d0
 * for kind 0x10, else sound 3); then both marks cleared. */
int Clock_Update(Clock *clock)
{
    RoomObject *base = &clock->base;
    clock->last_time = clock->time;
    Calendar_Now(&clock->time);
    if (base->unk_780 == KIND_STRIKING) {
        Clock_strike(clock);
    } else if (base->unk_780 == KIND_ANIMATED) {
        RoomObject_AdvanceAnims(base);
    }
    int frame = RoomManager_FrameCounter();
    if (base->unk_780 == KIND_SHARED) {
        AnimatedModel_SetFrame(&base->model, frame);
    }
    if (clock->nearest && (frame == TICK_FRAME_1 || frame == TICK_FRAME_2)) {
        if (base->unk_780 == KIND_STRIKING) {
            RoomSound_PlayAtB(&base->sound, TICK_SOUND, &base->sound.position);
        } else {
            RoomObject_PlaySound3(base);
        }
    }
    clock->nearest = 0;
    clock->nearest_striker = 0;
    return 1;
}
CLEAN_AS(func_ov004_022168fc, Clock_Update)

/* Binds the joint animation to the model and plays it by `mode` from the start. */
static void Clock_bind_joints(Clock *clock, int entry, int mode)
{
    AnimatedModel *model = &clock->base.model;
    if (AnimatedModel_LoadAnim(model, (Heap *) (uintptr_t) ModelPoolEntry_Heap((void *) (uintptr_t) (u32) entry)) != 0) {
        AnimatedModel_Start(model, (const u8 *) Clock_joint_file(clock), mode, ONE, 0, 0);
        AnimatedModel_Attach(model);
    }
}

/* func_ov004_02216aec (vtable slot 0x7c, once the model is bound): the time read, with no
 * strikes; kind 0x10 binds its joint animation to play once, kind 0x11 to loop; kind 0x2b loads
 * its animations of variant 0, looping. Done at once. */
int Clock_Start(Clock *clock)
{
    RoomObject *base = &clock->base;
    int entry = RoomObject_PoolEntry(base);
    Calendar_Now(&clock->last_time);
    clock->time = clock->last_time;
    clock->strikes = NO_STRIKES;
    if (base->unk_780 == KIND_STRIKING) {
        Clock_bind_joints(clock, entry, ANIM_MODE_ONCE);
    } else if (base->unk_780 == KIND_SHARED) {
        Clock_bind_joints(clock, entry, ANIM_MODE_LOOP);
    } else if (base->unk_780 == KIND_ANIMATED) {
        RoomObject_LoadAnims(base, 0, ANIM_MODE_LOOP, ONE, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_02216aec, Clock_Start)

static void Clock_set_vtables(Clock *clock)
{
    clock->base.vtable = (const RoomObjectVtable *) data_ov004_02251d98;
    clock->base.receiver_vtable = data_ov004_02251e44;
}

/* func_ov004_02216bd0 (the deleting destructor, vtable slot 0x44) */
Clock *Clock_Delete(Clock *clock)
{
    Clock_set_vtables(clock);
    RoomObject_DestructBase(&clock->base);
    RoomObject_Free(clock);
    return clock;
}
CLEAN_AS(func_ov004_02216bd0, Clock_Delete)

/* func_ov004_02216bfc (the destructor, vtable slot 0x40) */
Clock *Clock_Destroy(Clock *clock)
{
    Clock_set_vtables(clock);
    RoomObject_DestructBase(&clock->base);
    return clock;
}
CLEAN_AS(func_ov004_02216bfc, Clock_Destroy)

/* func_ov004_02216c20 (the constructor). Its own fields are left as the allocation zeroed them
 * until Clock_Start. */
Clock *Clock_Construct(Clock *clock)
{
    RoomObject_ConstructBase(&clock->base);
    Clock_set_vtables(clock);
    return clock;
}
CLEAN_AS(func_ov004_02216c20, Clock_Construct)

/* func_ov004_02216c44: a new clock from the room's heap; nothing when it has no room. */
void Clock_Create(void)
{
    Clock *clock = RoomObject_Alloc(CLOCK_SIZE);
    if (clock != NULL) {
        Clock_Construct(clock);
    }
}
CLEAN_AS(func_ov004_02216c44, Clock_Create)

/* The receiver part (at 0xec, RoomObject.receiver_vtable) enters Clock's functions
 * through its vtable with these: each moves the pointer back to the object and goes on with the
 * object's function. */
static Clock *Clock_from_receiver(void *receiver)
{
    return (Clock *) (void *) ((u8 *) receiver - offsetof(RoomObject, receiver_vtable));
}

/* func_ov004_0221a7cc: the deleting destructor, entered from the receiver part. */
Clock *ClockReceiver_Delete(void *receiver)
{
    return Clock_Delete(Clock_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251d98D0Ev, ClockReceiver_Delete)

/* func_ov004_0221a7e8: the destructor, entered from the receiver part. */
Clock *ClockReceiver_Destroy(void *receiver)
{
    return Clock_Destroy(Clock_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov004_02251d98D1Ev, ClockReceiver_Destroy)
