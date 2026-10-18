/* The clocks: a class of overlay 4's room objects (vtable 0x02251d98, receiver part 0x02251e44,
 * 0x84c bytes) whose model's hands show the time (RoomObject_ClockHandsHook, vtable slot 0x6c).
 * Each frame it reads the time of day (Calendar_Now), keeping the last one, and by its kind
 * (RoomObject.unk_780):
 * - 0x10 strikes the hours: when the hour changes it strikes the hour on a 12-hour dial (12 for
 *   0), each strike one play of its joint animation with sound 0x42d; in mode 2 (unk_76C) it
 *   strikes once, then keeps swinging without sound;
 * - 0x11 shows the frame of the room's shared frame counter (RoomManager_FrameCounter) on its joint
 *   animation;
 * - 0x2b advances its animations.
 * The nearest clock to the player is marked each frame (Clock_MarkNearest, by
 * RoomManager_MarkNearestClock) and ticks at frames 9 and 0x1d of the shared counter; the nearest
 * striking clock (Clock_MarkNearestStriker, by RoomManager_MarkNearestStriker) sets its sound's variable
 * when its strike count changes. Both marks last one frame. */
#ifndef CLEAN_OV004_CLOCK_H
#define CLEAN_OV004_CLOCK_H

#include "types.h"

#include "main/calendar.h" /* Time */
#include "room_object.h"
#include "room_object_methods.h" /* NodeHookState */

typedef struct Clock {
    RoomObject base;
    s8 strikes;         /* strikes left of the hour (-1: none) */
    s8 last_strikes;    /* the count the frame before */
    Time time;          /* the time of day this frame */
    Time last_time;     /* the time of day the frame before */
    u8 nearest;         /* the nearest clock to the player this frame */
    u8 nearest_striker; /* the nearest striking clock to the player this frame */
} Clock;

Clock *Clock_MarkNearestStriker(Clock *clock);
Clock *Clock_MarkNearest(Clock *clock);
void Clock_NodeDescAfterHook(Clock *clock, int node, NodeHookState *state);
int Clock_Vfunc0C(void);
int Clock_Update(Clock *clock);
int Clock_Start(Clock *clock);
Clock *Clock_Delete(Clock *clock);
Clock *Clock_Destroy(Clock *clock);
Clock *Clock_Construct(Clock *clock);
void Clock_Create(void);
Clock *ClockReceiver_Delete(void *receiver);
Clock *ClockReceiver_Destroy(void *receiver);

#endif
