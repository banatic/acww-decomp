/* A class of overlay 4's room objects (vtable 0x02251690, receiver part 0x0225173c, 0x850
 * bytes) that plays a sequence (main/sound.h's SoundSeq, at 0x844): each time vtable slot 0x70
 * is called it starts the sound at 2 of the furniture's row (func_ov004_0223a750), when there
 * is one. Touching it (a change of the switch pending) requests that again for the object at
 * its cell; every frame the sequence follows the object's centre, and vtable slot 0x0c stops
 * it. */
#ifndef CLEAN_OV004_ROOM_OBJECT_02251690_H
#define CLEAN_OV004_ROOM_OBJECT_02251690_H

#include "types.h"

#include "room_object.h"

typedef struct RoomObject02251690 {
    RoomObject base;
    u8 seq[0xc]; /* a SoundSeq (main/sound.h) */
} RoomObject02251690;

int RoomObject02251690_Play(RoomObject02251690 *object, int state, int value);
int RoomObject02251690_Stop(RoomObject02251690 *object);
int RoomObject02251690_Follow(RoomObject02251690 *object);
int RoomObject02251690_Update(RoomObject02251690 *object);
int RoomObject02251690_Start(RoomObject02251690 *object);
RoomObject02251690 *RoomObject02251690_Delete(RoomObject02251690 *object);
RoomObject02251690 *RoomObject02251690_Destroy(RoomObject02251690 *object);
RoomObject02251690 *RoomObject02251690_Construct(RoomObject02251690 *object);
void RoomObject02251690_Create(void);
RoomObject02251690 *RoomObject02251690Receiver_Delete(void *receiver);
RoomObject02251690 *RoomObject02251690Receiver_Destroy(void *receiver);

#endif
