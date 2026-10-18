/* A class of overlay 4's room objects (vtable 0x02251a14, receiver part 0x02251ac0, 0x8a0 bytes)
 * that is on or off by its switch, with three glowing materials (a GlowSet,
 * room_object_parts.h) that fade in while it is on and out while it is off. Its state
 * (RoomObject02251a14.state) runs through tables of member pointers (member_pointer.h):
 *
 * - OFF (0): entered with the switch off and the sound at 4; its animations stand still; while
 *   the switch has a change pending it requests ON for the object at its cell (RoomSync_RequestState);
 * - ON (1): entered with the switch on and the sound at 2; its animations run (in a loop) and
 *   the sound at 0 is played each frame; while the switch has a change pending it requests OFF.
 *
 * ON shows it on (vtable slot 0x74). Once its model is bound it enters ON when its switch is on
 * and RoomObjects_InNookOrScene0AOr0F says no, else OFF. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02251A14_H
#define CLEAN_OV004_ROOM_OBJECT_02251A14_H

#include "types.h"

#include "room_object.h"
#include "room_object_parts.h"

typedef struct RoomObject02251a14 {
    RoomObject base;
    u8 state; /* RoomObject02251a14State */
    u8 unk_845[3];
    GlowSet glows;
} RoomObject02251a14;

enum RoomObject02251a14State {
    ROOM_OBJECT_02251A14_OFF = 0,
    ROOM_OBJECT_02251A14_ON = 1,
    ROOM_OBJECT_02251A14_STATE_COUNT = 2
};

int RoomObject02251a14_UpdateOn(RoomObject02251a14 *object);
int RoomObject02251a14_EnterOn(RoomObject02251a14 *object);
void RoomObject02251a14_UpdateOff(RoomObject02251a14 *object);
int RoomObject02251a14_EnterOff(RoomObject02251a14 *object);
void RoomObject02251a14_UpdateState(RoomObject02251a14 *object);
int RoomObject02251a14_EnterState(RoomObject02251a14 *object, unsigned int state, int value);
u8 RoomObject02251a14_StateIsOn(RoomObject02251a14 *object, unsigned int state);
int RoomObject02251a14_Vfunc0C(void);
int RoomObject02251a14_Update(RoomObject02251a14 *object);
int RoomObject02251a14_Start(RoomObject02251a14 *object);
RoomObject02251a14 *RoomObject02251a14_Delete(RoomObject02251a14 *object);
RoomObject02251a14 *RoomObject02251a14_Destroy(RoomObject02251a14 *object);
RoomObject02251a14 *RoomObject02251a14_Construct(RoomObject02251a14 *object);
void RoomObject02251a14_Create(void);
RoomObject02251a14 *RoomObject02251a14Receiver_Delete(void *receiver);
RoomObject02251a14 *RoomObject02251a14Receiver_Destroy(void *receiver);

#endif
