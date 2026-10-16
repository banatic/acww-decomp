/* A class of overlay 4's room objects (vtable 0x022524a0, receiver part 0x0225254c, 0x848 bytes)
 * whose state (RoomObject022524a0.state) runs through tables of member pointers
 * (member_pointer.h):
 *
 * - IDLE (0): entered with the value 0 of its node set and the animations of variant 0 played
 *   once; when its switch is asked to change it requests PLAYING for the object at its cell
 *   (func_02052738);
 * - PLAYING (1): entered with the value 1 of its node set, the animations of variant 0 played
 *   once and the sound at 2; once the model's joint animation has ended it requests IDLE. */
#ifndef CLEAN_OV004_ROOM_OBJECT_022524A0_H
#define CLEAN_OV004_ROOM_OBJECT_022524A0_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject022524a0 {
    RoomObject base;
    u8 state; /* RoomObject022524a0State */
    u8 unk_845[3];
} RoomObject022524a0;

enum RoomObject022524a0State {
    ROOM_OBJECT_022524A0_IDLE = 0,
    ROOM_OBJECT_022524A0_PLAYING = 1,
    ROOM_OBJECT_022524A0_STATE_COUNT = 2
};

int RoomObject022524a0_UpdatePlaying(RoomObject022524a0 *object);
int RoomObject022524a0_EnterPlaying(RoomObject022524a0 *object);
void RoomObject022524a0_UpdateIdle(RoomObject022524a0 *object);

#endif
