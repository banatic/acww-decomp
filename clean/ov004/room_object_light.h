/* The lights among overlay 4's room objects (room_object.h): an object whose furniture has a
 * light (RoomObject_Check0221134c: func_02053818 of its number, kept in light_kind) glows by its
 * switch (room_object_parts.h), and in areas 1 to 5 (func_020b65c4) the room's lighting follows
 * the lamps that are on: the first one switched on sets it by its kind (func_ov004_02211414),
 * the last one switched off sets it back (func_02064da0 with 8). The count of lamps on is
 * func_ov004_0223c264's. */
#ifndef CLEAN_OV004_ROOM_OBJECT_LIGHT_H
#define CLEAN_OV004_ROOM_OBJECT_LIGHT_H

#include "types.h"

#include "room_object.h"

void RoomObject_ExitLight(RoomObject *object);
void RoomObject_UpdateLight(RoomObject *object);
void RoomObject_StartLight(RoomObject *object);
int Area_CurrentIs1To5(void);
int Area_Is1To5(unsigned int area);

#endif
