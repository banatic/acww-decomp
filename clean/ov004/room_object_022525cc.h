/* A class of overlay 4's room objects (vtable 0x022525cc, receiver part 0x02252678, 0x8a4 bytes)
 * whose animations run in a loop at a speed it sets each frame, with three glowing materials (a
 * GlowSet, room_object_parts.h). Its state (RoomObject022525cc.state) runs through tables of
 * member pointers (member_pointer.h):
 *
 * - OFF (0): the switch off, the glows fading out, the speed 0; while the switch has a change
 *   pending it requests ON for the object at its cell (RoomSync_RequestState);
 * - ON (1): the switch on, the glows fading in, the speed normal and the sound at 0 each frame;
 *   while the switch has a change pending it requests STOPPING;
 * - STOPPING (2): the switch off, the glows still fading in, the speed falling by 0xcc a frame;
 *   at 0 it enters OFF.
 *
 * ON alone shows it on (vtable slot 0x74). Once its model is bound it enters ON when its switch
 * is on and RoomObjects_InNookOrScene0AOr0F says no, else OFF. */
#ifndef CLEAN_OV004_ROOM_OBJECT_022525CC_H
#define CLEAN_OV004_ROOM_OBJECT_022525CC_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct RoomObject022525cc {
    RoomObject base;
    u8 state; /* RoomObject022525ccState */
    u8 unk_845[3];
    int speed; /* of the joint animation and the bound animations, 20.12 fixed point */
    GlowSet glows;
} RoomObject022525cc;

enum RoomObject022525ccState {
    ROOM_OBJECT_022525CC_OFF = 0,
    ROOM_OBJECT_022525CC_ON = 1,
    ROOM_OBJECT_022525CC_STOPPING = 2,
    ROOM_OBJECT_022525CC_STATE_COUNT = 3
};

int RoomObject022525cc_UpdateStopping(RoomObject022525cc *object);
int RoomObject022525cc_EnterStopping(RoomObject022525cc *object);
int RoomObject022525cc_UpdateOn(RoomObject022525cc *object);
int RoomObject022525cc_EnterOn(RoomObject022525cc *object);
void RoomObject022525cc_UpdateOff(RoomObject022525cc *object);
int RoomObject022525cc_EnterOff(RoomObject022525cc *object);
void RoomObject022525cc_UpdateState(RoomObject022525cc *object);
int RoomObject022525cc_EnterState(RoomObject022525cc *object, unsigned int state, int value);
u8 RoomObject022525cc_StateIsOn(RoomObject022525cc *object, unsigned int state);
int RoomObject022525cc_Vfunc0C(void);
int RoomObject022525cc_Update(RoomObject022525cc *object);
int RoomObject022525cc_Start(RoomObject022525cc *object);
RoomObject022525cc *RoomObject022525cc_Delete(RoomObject022525cc *object);
RoomObject022525cc *RoomObject022525cc_Destroy(RoomObject022525cc *object);
RoomObject022525cc *RoomObject022525cc_Construct(RoomObject022525cc *object);
void RoomObject022525cc_Create(void);
RoomObject022525cc *RoomObject022525ccReceiver_Delete(void *receiver);
RoomObject022525cc *RoomObject022525ccReceiver_Destroy(void *receiver);

#endif
