/* The sounds of the room object on the floor at a point (RoomObjects_GridObjectAtPoint of the room's
 * grid, RoomObjects_Grid), played when the object is of kind 0x36 or 0x37
 * (RoomObject.unk_00C, RoomObject_Unk00CIs36Or37): the sounds at 4, 0 and 2 of the furniture's
 * row (RoomObject_PlaySound2, RoomObject_PlaySound0, RoomObject_PlaySound1). Room actors of
 * overlay 4 (FieldActorRoomStates_EnterSpotStepOff, FieldActorRoomStates_UpdateSpotClaim, FieldActorRoomStates_UpdateSpotStay and
 * FieldActorRoomStates_StepSpotEnter) ask for them at the point they act on. */
#ifndef CLEAN_OV004_ROOM_POINT_SOUND_H
#define CLEAN_OV004_ROOM_POINT_SOUND_H

#include "autoload_2/vector.h"
#include "types.h"

void RoomPointSound_Play2(Vec3 *point);
void RoomPointSound_Play0(Vec3 *point);
void RoomPointSound_Play1(Vec3 *point);

#endif
