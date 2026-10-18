/* A class of overlay 4's room objects (vtable 0x02252a7c, receiver part 0x02252b28, 0x850
 * bytes) that plays its model's animation (variant 0, once, at normal speed) in bursts: after a
 * wait it plays the sound at 0 of the furniture's row (FurnitureSounds_Sound0) and runs the
 * animation `repeats` times over, then waits again. What it does depends on that sound:
 *
 * - sounds 0x3f9 to 0x3fc: one burst between waits, the animation 4 times (2 for 0x3fc); the
 *   wait is 200 frames (60 for 0x3fc), the first one random below that;
 * - any other sound: three bursts in a row, the sound at the start of each, the animation once
 *   per burst; the wait is as long as the animation (its visibility animation's when it has
 *   one, else its joint animation's), the first one random below the animation's length.
 *   Sound 0x3ff is played again each time the joint animation passes frame 20.
 *
 * An animation counts as done on the second frame its end is seen (PeriodicRoomObject.ended).
 * In mode 1 (RoomObject.unk_76C) the first wait is 0. */
#ifndef CLEAN_OV004_ROOM_OBJECT_PERIODIC_H
#define CLEAN_OV004_ROOM_OBJECT_PERIODIC_H

#include "types.h"

#include "room_object.h"

typedef struct PeriodicRoomObject {
    RoomObject base;
    u16 repeats; /* runs of the animation in a burst */
    u16 wait;    /* frames left before the next burst */
    u8 count;    /* runs of the animation so far in this burst */
    u8 phase;    /* PeriodicPhase */
    u8 ended;    /* the animations were at their end on the last frame */
    u8 unk_84b;
    u16 frames; /* frames in the burst, counted for sounds 0x3f9 to 0x3fc only */
    u8 unk_84e[2];
} PeriodicRoomObject;

enum PeriodicPhase {
    PERIODIC_WAIT = 0,
    PERIODIC_BURST_1 = 1,
    PERIODIC_BURST_2 = 2, /* not with sounds 0x3f9 to 0x3fc */
    PERIODIC_BURST_3 = 3
};

int PeriodicRoomObject_Vfunc0C(void);
int PeriodicRoomObject_Update(PeriodicRoomObject *object);
int PeriodicRoomObject_Start(PeriodicRoomObject *object);
PeriodicRoomObject *PeriodicRoomObject_Delete(PeriodicRoomObject *object);
PeriodicRoomObject *PeriodicRoomObject_Destroy(PeriodicRoomObject *object);
PeriodicRoomObject *PeriodicRoomObject_Construct(PeriodicRoomObject *object);
void PeriodicRoomObject_Create(void);

PeriodicRoomObject *PeriodicRoomObjectReceiver_Delete(void *receiver);
PeriodicRoomObject *PeriodicRoomObjectReceiver_Destroy(void *receiver);

#endif
