/* A class of overlay 4's room objects (vtable 0x022509ac, receiver part 0x02250a58, 0x8a0
 * bytes) that is on or off by its switch, with three glowing materials (a GlowSet,
 * room_object_parts.h) that fade in while it is on and out while it is off. Its state
 * (GlowingRoomObject.state) runs through tables of member pointers (member_pointer.h):
 *
 * - off: entered with the sound at 4 and the animation of variant 0 played once; while the
 *   switch has a change pending it requests the state "on" for the object at its cell
 *   (RoomSync_RequestState, which does so only when data_020e54a8 is 1);
 * - on: entered with the sound at 2 and the animation of variant 1 played in a loop; the sound
 *   at 0 is played each frame; while the switch has a change pending it requests "off".
 *
 * Once its model is bound it enters "on" when its switch is on, unless RoomObjects_InNookOrScene0AOr0F
 * says otherwise, and "off" if not; in mode 1 (RoomObject.unk_76C) it requests "off" through
 * RoomSync_SetState instead. */
#ifndef CLEAN_OV004_ROOM_OBJECT_GLOWING_H
#define CLEAN_OV004_ROOM_OBJECT_GLOWING_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct GlowingRoomObject {
    RoomObject base;
    GlowSet glows;
    u8 state; /* GlowingState */
    u8 unk_89d[3];
} GlowingRoomObject;

enum GlowingState { GLOWING_OFF = 0, GLOWING_ON = 1, GLOWING_STATE_COUNT = 2 };

int GlowingRoomObject_UpdateOn(GlowingRoomObject *object);
int GlowingRoomObject_EnterOn(GlowingRoomObject *object);
int GlowingRoomObject_UpdateOff(GlowingRoomObject *object);
int GlowingRoomObject_EnterOff(GlowingRoomObject *object);
void GlowingRoomObject_UpdateState(GlowingRoomObject *object);
int GlowingRoomObject_EnterState(GlowingRoomObject *object, unsigned int state, int value);
u8 GlowingRoomObject_StateIsOn(GlowingRoomObject *object, unsigned int state);
int GlowingRoomObject_Vfunc0C(void);
int GlowingRoomObject_Update(GlowingRoomObject *object);
int GlowingRoomObject_Start(GlowingRoomObject *object);
GlowingRoomObject *GlowingRoomObject_Delete(GlowingRoomObject *object);
GlowingRoomObject *GlowingRoomObject_Destroy(GlowingRoomObject *object);
GlowingRoomObject *GlowingRoomObject_Construct(GlowingRoomObject *object);
void GlowingRoomObject_Create(void);

GlowingRoomObject *GlowingRoomObjectReceiver_Delete(void *receiver);
GlowingRoomObject *GlowingRoomObjectReceiver_Destroy(void *receiver);

#endif
