/* What a room object does with its sound at a point (RoomSound, room_object.h): the point
 * sound's calls (sound_emitter.h), made only while it plays. */
#ifndef CLEAN_OV004_ROOM_SOUND_H
#define CLEAN_OV004_ROOM_SOUND_H

#include "types.h"

#include "autoload_2/vector.h"
#include "room_object.h"

void RoomSound_SetVariable(RoomSound *sound, short value);
void RoomSound_UpdateVolumeAt(RoomSound *sound, const Vec3 *at);
void RoomSound_PlayAt(RoomSound *sound, int number, const Vec3 *at);

#endif
