/* The sound of the sky's process (SkyProcess.sound, block_020ba298.h): the rain heard while it
 * rains (Sky.precipitation SKY_FALLING_RAIN), louder at the heavy level. Its loudness
 * (`level`, 0 to 0x100000) moves towards the level's each frame and is handed to the sound
 * as the distance of a point straight ahead (level / 256). */
#ifndef CLEAN_MAIN_SKY_SOUND_H
#define CLEAN_MAIN_SKY_SOUND_H

#include "autoload_2/sound_source.h"
#include "types.h"

/* The sound source of the sky's process and the word after it (SkyProcess 0x50). */
typedef struct SkySound {
    SoundSourceObject source; /* 0x00 */
    int level;                /* 0x0c: the rain's loudness */
} SkySound;

void SkySound_ApproachLevel(SkySound *sound);
void SkySound_SetLevel(SkySound *sound);
void SkySound_Release(SkySound *sound);
void SkySound_Update(SkySound *sound);
int SkySound_Start(SkySound *sound);

#endif
