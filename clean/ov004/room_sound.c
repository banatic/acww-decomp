/* What a room object does with its sound at a point (room_sound.h). */
#include "room_sound.h"

#include "clean.h"
#include "main/sound_emitter.h"

static_assert(offsetof(RoomSound, playing) == 0x1c, "playing");

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
