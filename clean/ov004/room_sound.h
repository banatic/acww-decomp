/* What a room object does with its sound at a point (RoomSound, room_object.h): the point
 * sound's calls (sound_emitter.h), made only while it plays.
 *
 * The room's own list of those sounds (RoomSoundList, the member at 0x50 of the room's object,
 * room_manager.h): started once the sound layer allows it and flushed every frame by the
 * room's update; a room object's sound joins it when it starts (RoomSound_Start). */
#ifndef CLEAN_OV004_ROOM_SOUND_H
#define CLEAN_OV004_ROOM_SOUND_H

#include "types.h"

#include "autoload_2/sound_point.h"
#include "autoload_2/vector.h"
#include "room_object.h"

typedef struct RoomSoundList {
    SoundPointList points; /* 0x00 */
    u8 started;            /* 0x10: PointSound_StartList was run on it */
    u8 pad_11[3];
} RoomSoundList;

void RoomSound_SetVariable(RoomSound *sound, short value);
void RoomSound_UpdateVolumeAt(RoomSound *sound, const Vec3 *at);
void RoomSound_PlayAt(RoomSound *sound, int number, const Vec3 *at);
void RoomSound_PlayAtB(RoomSound *sound, int number, const Vec3 *at);
void RoomSound_Stop(RoomSound *sound);
void RoomSound_Start(RoomSound *sound);
void RoomSound_Destruct(RoomSound *sound);
void RoomSound_Construct(RoomSound *sound);

unsigned char RoomSoundList_Started(RoomSoundList *list);
SoundPointList *RoomSoundList_Points(RoomSoundList *list);
void RoomSoundList_Release(RoomSoundList *list);
void RoomSoundList_Flush(RoomSoundList *list);
void RoomSoundList_Start(RoomSoundList *list);
RoomSoundList *RoomSoundList_Destruct(RoomSoundList *list);
void RoomSoundList_Construct(RoomSoundList *list);

#endif
