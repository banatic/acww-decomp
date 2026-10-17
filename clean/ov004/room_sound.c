/* What a room object does with its sound at a point (room_sound.h). */
#include "room_sound.h"

#include "clean.h"
#include "main/sound_emitter.h"
#include "room_manager.h"

static_assert(offsetof(RoomSound, playing) == 0x1c, "playing");
static_assert(offsetof(RoomSoundList, started) == 0x10, "list started");
static_assert(sizeof(RoomSoundList) == 0x14, "list");

/* func_ov004_0223cf18: PointSound_SetVariable while the sound plays. */
void RoomSound_SetVariable(RoomSound *sound, short value)
{
    if (sound->playing != 0) {
        PointSound_SetVariable(sound, value);
    }
}
CLEAN_AS(func_ov004_0223cf18, RoomSound_SetVariable)

/* func_ov004_0223cf2c: PointSound_UpdateVolumeAt while the sound plays. */
void RoomSound_UpdateVolumeAt(RoomSound *sound, const Vec3 *at)
{
    if (sound->playing != 0) {
        PointSound_UpdateVolumeAt(sound, at);
    }
}
CLEAN_AS(func_ov004_0223cf2c, RoomSound_UpdateVolumeAt)

/* func_ov004_0223cf40: PointSound_PlayAt while the sound plays. */
void RoomSound_PlayAt(RoomSound *sound, int number, const Vec3 *at)
{
    if (sound->playing != 0) {
        PointSound_PlayAt(sound, number, at);
    }
}
CLEAN_AS(func_ov004_0223cf40, RoomSound_PlayAt)

/* func_ov004_0223cf54: PointSound_PlayAtB while the sound plays. */
void RoomSound_PlayAtB(RoomSound *sound, int number, const Vec3 *at)
{
    if (sound->playing != 0) {
        PointSound_PlayAtB(sound, number, at);
    }
}
CLEAN_AS(func_ov004_0223cf54, RoomSound_PlayAtB)

/* func_ov004_0223cf68: a sound that plays is released and marked stopped. */
void RoomSound_Stop(RoomSound *sound)
{
    if (sound->playing != 0) {
        PointSound_Release((char *) (void *) sound);
        sound->playing = 0;
    }
}
CLEAN_AS(func_ov004_0223cf68, RoomSound_Stop)

/* func_ov004_0223cf80: a sound not yet playing joins the room's list (RoomManager_SoundList)
 * once that list is started, and is marked playing. */
void RoomSound_Start(RoomSound *sound)
{
    if (sound->playing != 0) {
        return;
    }
    RoomSoundList *list = RoomManager_SoundList();
    if (list != NULL && RoomSoundList_Started(list) != 0) {
        PointSound_Init(sound, (int) (intptr_t) RoomSoundList_Points(list));
        sound->playing = 1;
    }
}
CLEAN_AS(func_ov004_0223cf80, RoomSound_Start)

/* func_ov004_0223cfb8: the destructor; nothing to undo. */
void RoomSound_Destruct(RoomSound *sound)
{
    (void) sound;
}
CLEAN_AS(func_ov004_0223cfb8, RoomSound_Destruct)

/* func_ov004_0223cfbc: the constructor: not playing. */
void RoomSound_Construct(RoomSound *sound)
{
    sound->playing = 0;
}
CLEAN_AS(func_ov004_0223cfbc, RoomSound_Construct)

/* ---- The room's list of point sounds */

/* func_ov004_0223cfc4 */
unsigned char RoomSoundList_Started(RoomSoundList *list)
{
    return list->started;
}
CLEAN_AS(func_ov004_0223cfc4, RoomSoundList_Started)

/* func_ov004_0223cfc8: the list the sounds join. */
SoundPointList *RoomSoundList_Points(RoomSoundList *list)
{
    return &list->points;
}
CLEAN_AS(func_ov004_0223cfc8, RoomSoundList_Points)

/* func_ov004_0223cfcc: at the room's end; only asks whether the list was started and does
 * nothing with the answer. */
void RoomSoundList_Release(RoomSoundList *list)
{
    RoomSoundList_Started(list);
}
CLEAN_AS(func_ov004_0223cfcc, RoomSoundList_Release)

/* func_ov004_0223cfd4: each frame, the started list is flushed (PointSound_FlushList). */
void RoomSoundList_Flush(RoomSoundList *list)
{
    if (RoomSoundList_Started(list) != 0) {
        PointSound_FlushList(list);
    }
}
CLEAN_AS(func_ov004_0223cfd4, RoomSoundList_Flush)

/* func_ov004_0223cfec: each frame, until it is started: started as soon as the sound layer
 * allows it (PointSound_CanStartList). */
void RoomSoundList_Start(RoomSoundList *list)
{
    if (RoomSoundList_Started(list) == 0 && PointSound_CanStartList() != 0) {
        PointSound_StartList((char *) (void *) list);
        list->started = 1;
    }
}
CLEAN_AS(func_ov004_0223cfec, RoomSoundList_Start)

/* func_ov004_0223d010: the destructor (SoundPointList_Release). */
RoomSoundList *RoomSoundList_Destruct(RoomSoundList *list)
{
    SoundPointList_Release(&list->points);
    return list;
}
CLEAN_AS(func_ov004_0223d010, RoomSoundList_Destruct)

/* func_ov004_0223d020: the constructor: not started. */
void RoomSoundList_Construct(RoomSoundList *list)
{
    list->started = 0;
}
CLEAN_AS(func_ov004_0223d020, RoomSoundList_Construct)
