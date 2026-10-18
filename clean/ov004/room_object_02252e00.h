/* A class of overlay 4's room objects (vtable 0x02252e00, receiver part 0x02252eac, 0x848 bytes)
 * that plays its animations once when touched. Its state (RoomObject02252e00.state) runs
 * through tables of member pointers (member_pointer.h):
 *
 * - STILL (0): the animations of variant 0 at their end, entered with the sound at 4 (not for
 *   furniture 0x207); while the switch has a change pending it requests PLAYING for the object
 *   at its cell (RoomSync_RequestState);
 * - PLAYING (1): the animations of variant 0 once from the start, entered with the sound at 2;
 *   each frame the switch is turned over, and STILL requested once the animations end, the
 *   sound at 0 played until then. Furniture 0xb9 and 0xba touched again start over; furniture
 *   0x207 plays the sound at 4 at frame 0x30 of its joint animation.
 *
 * Its switch is set off when it starts, and by vtable slot 0x0c; whether a state shows it on is
 * the base class's answer (vtable slot 0x74). */
#ifndef CLEAN_OV004_ROOM_OBJECT_02252E00_H
#define CLEAN_OV004_ROOM_OBJECT_02252E00_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02252e00 {
    RoomObject base;
    u8 state; /* RoomObject02252e00State */
    u8 unk_845[3];
} RoomObject02252e00;

enum RoomObject02252e00State {
    ROOM_OBJECT_02252E00_STILL = 0,
    ROOM_OBJECT_02252E00_PLAYING = 1,
    ROOM_OBJECT_02252E00_STATE_COUNT = 2
};

void RoomObject02252e00_UpdatePlaying(RoomObject02252e00 *object);
int RoomObject02252e00_EnterPlaying(RoomObject02252e00 *object);
void RoomObject02252e00_UpdateStill(RoomObject02252e00 *object);
int RoomObject02252e00_EnterStill(RoomObject02252e00 *object);
void RoomObject02252e00_UpdateState(RoomObject02252e00 *object);
int RoomObject02252e00_EnterState(RoomObject02252e00 *object, unsigned int state, int value);
int RoomObject02252e00_SwitchOff(RoomObject02252e00 *object);
int RoomObject02252e00_Update(RoomObject02252e00 *object);
int RoomObject02252e00_Start(RoomObject02252e00 *object);
RoomObject02252e00 *RoomObject02252e00_Delete(RoomObject02252e00 *object);
RoomObject02252e00 *RoomObject02252e00_Destroy(RoomObject02252e00 *object);
RoomObject02252e00 *RoomObject02252e00_Construct(RoomObject02252e00 *object);
void RoomObject02252e00_Create(void);
RoomObject02252e00 *RoomObject02252e00Receiver_Delete(void *receiver);
RoomObject02252e00 *RoomObject02252e00Receiver_Destroy(void *receiver);

#endif
