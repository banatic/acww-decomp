/* The animations and sounds of overlay 4's room objects (room_object.h): the five animations of
 * the furniture's archive (AnimSet, room_object_parts.h) in one of their two variants, played by
 * the model's joint animation and the four animations in RoomObject.anims; the sounds of the
 * furniture's row of func_ov004_0223a770, played at the object's centre; and the sound of a
 * move. */
#ifndef CLEAN_OV004_ROOM_OBJECT_ANIMS_H
#define CLEAN_OV004_ROOM_OBJECT_ANIMS_H

#include "types.h"

#include "room_object.h"

/* An animation file of NitroSDK's G3D (NNSG3dResAnmHeader and its frame count). */
typedef struct AnimFile {
    u32 tag;
    u16 frames;
} AnimFile;

int RoomObject_MoveSound(RoomObject *object);
int RoomObject_PoolEntry(RoomObject *object);
int RoomObject_AdvanceAnims(RoomObject *object);
void RoomObject_PlayAnimsFromEnd(RoomObject *object, int variant, int mode, int speed);
void RoomObject_PlayAnimsFrom(RoomObject *object, int variant, u8 mode, int speed, u16 frame);
void RoomObject_LoadAnims(RoomObject *object, int variant, u8 mode, int speed, u16 frame);
u16 RoomObject_AnimFrames(RoomObject *object, int variant);
int RoomObject_PlaySound3(RoomObject *object);
int RoomObject_PlaySound2(RoomObject *object);
int RoomObject_PlaySound1(RoomObject *object);
int RoomObject_PlaySound0(RoomObject *object);

#endif
