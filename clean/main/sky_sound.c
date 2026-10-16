/* The sound of the sky's process (sky_sound.h). */
#include "sky_sound.h"

#include "autoload_2/approach.h"
#include "clean.h"
#include "scene_kinds.h"
#include "sky.h"
#include "sound_emitter.h"

static_assert(offsetof(SkySound, level) == 0x0c, "the rain's loudness");

#define SKY_SOUND_RAIN_LEVEL 0x099a00
#define SKY_SOUND_HEAVY_RAIN_LEVEL 0x100000
#define SKY_SOUND_STEP_UP 0xdf
#define SKY_SOUND_STEP_DOWN 0x1eb
#define SKY_SOUND_STEP_DRY 0x5200

extern const s32 data_020d2334[];                /* the rain's sound per sound kind of the scene, -1: none */
extern void *func_02137550(void *dst, u32 size); /* clears size bytes */

/* The loudness of rain at `weather` while it rains, else 0. */
static s32 rain_level(s32 weather, s32 precipitation)
{
    if (precipitation != SKY_FALLING_RAIN) {
        return 0;
    }
    if (weather == SKY_WEATHER_RAIN) {
        return SKY_SOUND_RAIN_LEVEL;
    }
    if (weather == SKY_WEATHER_HEAVY_RAIN) {
        return SKY_SOUND_HEAVY_RAIN_LEVEL;
    }
    return 0;
}

/* func_020bbdc8: the loudness a step towards the next level's: while it rains by 0xdf a frame
 * up and 0x1eb down, else by 0x5200 down to 0. */
void SkySound_ApproachLevel(SkySound *sound)
{
    int raining = data_021f75b0.precipitation == SKY_FALLING_RAIN;
    s32 target = rain_level(data_021f75b0.next_weather, data_021f75b0.precipitation);
    int step;
    if (!raining) {
        step = SKY_SOUND_STEP_DRY;
    } else if (target < sound->level) {
        step = SKY_SOUND_STEP_DOWN;
    } else {
        step = SKY_SOUND_STEP_UP;
    }
    Approach_S32(&sound->level, target, step);
}
CLEAN_AS(func_020bbdc8, SkySound_ApproachLevel)

/* func_020bbe38: the loudness set to the level's at once. */
void SkySound_SetLevel(SkySound *sound)
{
    sound->level = rain_level(data_021f75b0.weather, data_021f75b0.precipitation);
}
CLEAN_AS(func_020bbe38, SkySound_SetLevel)

/* func_020bbe8c */
void SkySound_Release(SkySound *sound)
{
    SoundSource_Release((SoundSource *) (void *) &sound->source);
}
CLEAN_AS(func_020bbe8c, SkySound_Release)

/* func_020bbe94: a frame: while the rain is heard its sound asked for (the scene's, when it has
 * one), the sound updated at the loudness's distance, then the loudness moved. */
void SkySound_Update(SkySound *sound)
{
    if (sound->level != 0) {
        s32 number = data_020d2334[SceneKinds_SoundKind(0)];
        if (number >= 0) {
            SoundSource_Play((SoundSource *) (void *) &sound->source, number);
        }
    }
    Vec3 position;
    func_02137550(&position, sizeof(position));
    position.z = sound->level >> 8;
    SoundSource_Update((SoundSource *) (void *) &sound->source, &position);
    SkySound_ApproachLevel(sound);
}
CLEAN_AS(func_020bbe94, SkySound_Update)

/* func_020bbee0: the loudness set to the level's and the sound started; its answer. */
int SkySound_Start(SkySound *sound)
{
    SkySound_SetLevel(sound);
    return SoundSource_Init((SoundSource *) (void *) &sound->source);
}
CLEAN_AS(func_020bbee0, SkySound_Start)
