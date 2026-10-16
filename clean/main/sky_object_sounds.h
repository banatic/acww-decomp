/* The sounds of the sky's objects (data_021fbb14, at 0x2fcc of the objects data_021f8b48,
 * sky_objects.h): eight sound sources (main/sound_emitter.h), each with the point it is heard
 * from. A sound is asked for at a point (SkyObjectSounds_Play, SkyObjectSounds_PlayHeld) and
 * the sources are updated with their points each frame (SkyObjectSounds_Update) while they are
 * on (SkyObjectSounds_Init to SkyObjectSounds_Release). */
#ifndef CLEAN_MAIN_SKY_OBJECT_SOUNDS_H
#define CLEAN_MAIN_SKY_OBJECT_SOUNDS_H

#include "autoload_2/vector.h"
#include "sound_emitter.h"
#include "types.h"

#define SKY_OBJECT_SOUNDS 8

typedef struct SkyObjectSounds {
    SoundSource sources[SKY_OBJECT_SOUNDS]; /* 0x00 */
    Vec3 points[SKY_OBJECT_SOUNDS];         /* 0x60 */
    u8 on;                                  /* 0xc0 */
    u8 unk_c1[3];
} SkyObjectSounds;

void SkyObjectSounds_Update(SkyObjectSounds *sounds);
void SkyObjectSounds_Play(SkyObjectSounds *sounds, int index, int number, const Vec3 *point);
void SkyObjectSounds_PlayHeld(SkyObjectSounds *sounds, int index, int number, const Vec3 *point);
void SkyObjectSounds_Release(SkyObjectSounds *sounds);
void SkyObjectSounds_Init(SkyObjectSounds *sounds);
SkyObjectSounds *SkyObjectSounds_Construct(SkyObjectSounds *sounds);

#endif
