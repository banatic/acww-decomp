/* The life of overlay 4's room objects (room_object.h): making one (from the room's heap,
 * data_ov004_022595c4, zeroed), its constructors and destructors with those of its members,
 * setting it up when it enters the scene (its slot in the pool, its model files, loaded at once
 * or a step each frame), and what it does each frame: its update and its drawing.
 *
 * The base class (vtable 0x0224fe6c) and its receiver part (vtable 0x0224ff18, at 0xec) are
 * shared by the derived classes, which build on RoomObject_ConstructBase and
 * RoomObject_DestructBase. */
#ifndef CLEAN_OV004_ROOM_OBJECT_LIFE_H
#define CLEAN_OV004_ROOM_OBJECT_LIFE_H

#include "types.h"

#include "room_object.h"

int RoomObject_Draw(RoomObject *object);
int RoomObject_Vfunc84(void);
int RoomObject_Vfunc80(void);
int RoomObject_Update(RoomObject *object);
void RoomObject_Vfunc08(RoomObject *object, int mode);
int RoomObject_Init(RoomObject *object);
RoomObject *RoomObject_DestructBase(RoomObject *object);
RoomObject *RoomObject_Delete(RoomObject *object);
RoomObject *RoomObject_Destroy(RoomObject *object);
RoomObject *RoomObject_Construct(RoomObject *object);
RoomObject *RoomObject_ConstructBase(RoomObject *object);
int RoomObject_Vfunc7C(void);
void RoomObject_Free(void *block);
void *RoomObject_Alloc(u32 size);
void RoomObject_Create(void);
RoomObject *RoomObjectReceiver_Delete(void *receiver);
RoomObject *RoomObjectReceiver_Destroy(void *receiver);

#endif
