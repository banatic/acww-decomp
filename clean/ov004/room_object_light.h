/* The lights among overlay 4's room objects (room_object.h): an object whose furniture has a
 * light (RoomObject_Check0221134c: FurnitureInfo_LightKind of its number, kept in light_kind) glows by its
 * switch (room_object_parts.h), and in areas 1 to 5 (SceneQuery_Current) the room's lighting follows
 * the lamps that are on: the first one switched on sets it by its kind (RoomLight_TurnOn),
 * the last one switched off sets it back (SceneLights_RequestOff with 8). The count of lamps on is
 * RoomObjects_CountOn's. */
#ifndef CLEAN_OV004_ROOM_OBJECT_LIGHT_H
#define CLEAN_OV004_ROOM_OBJECT_LIGHT_H

#include "types.h"

#include "room_object.h"

void RoomObject_ExitLight(RoomObject *object);
void RoomObject_UpdateLight(RoomObject *object);
void RoomObject_StartLight(RoomObject *object);
int Area_CurrentIs1To5(void);
int Area_Is1To5(unsigned int area);
void RoomLight_TurnOn(int light_kind);
int LightKind_Flashes(int light_kind);

#endif
