/* The sounds of the sky's objects (sky_object_sounds.h). */
#include "sky_object_sounds.h"

#include "clean.h"

static_assert(sizeof(SoundSource) == 12, "a sound source");
static_assert(offsetof(SkyObjectSounds, points) == 0x60, "the points");
static_assert(offsetof(SkyObjectSounds, on) == 0xc0, "on");

extern const u8 data_0213efe8[];         /* the sound source class's vtable */
extern const u8 data_0213f03c[];         /* the derived class's (SoundSource's) */
extern void func_020012e8(void *object); /* a trivial object's constructor */
extern void func_020012dc(void *object); /* and destructor */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* func_020be568: while on, each source updated with its point.
 * QUIRK: the last source is updated without a point (NULL), not with its own. */
void SkyObjectSounds_Update(SkyObjectSounds *sounds)
{
    if (sounds->on == 0) {
        return;
    }
    for (int i = 0; i < SKY_OBJECT_SOUNDS; i++) {
        SoundSource_Update(&sounds->sources[i], i == SKY_OBJECT_SOUNDS - 1 ? NULL : &sounds->points[i]);
    }
}
CLEAN_AS(func_020be568, SkyObjectSounds_Update)

/* The point a source is heard from, a word at a time. */
static void sky_object_sounds_set_point(SkyObjectSounds *sounds, int index, const Vec3 *point)
{
    Vec3 *to = &sounds->points[index];
    to->x = point->x;
    to->y = point->y;
    to->z = point->z;
}

/* func_020be5a0: while on, sound `number` asked for from source `index`, heard from `point`.
 * REQUIRES: index is 0 to 7. */
void SkyObjectSounds_Play(SkyObjectSounds *sounds, int index, int number, const Vec3 *point)
{
    if (sounds->on == 0) {
        return;
    }
    SoundSource_Play(&sounds->sources[index], number);
    sky_object_sounds_set_point(sounds, index, point);
}
CLEAN_AS(func_020be5a0, SkyObjectSounds_Play)

/* func_020be5d0: the same, the sound kept playing while it is not asked for. */
void SkyObjectSounds_PlayHeld(SkyObjectSounds *sounds, int index, int number, const Vec3 *point)
{
    if (sounds->on == 0) {
        return;
    }
    SoundSource_PlayHeld(&sounds->sources[index], number);
    sky_object_sounds_set_point(sounds, index, point);
}
CLEAN_AS(func_020be5d0, SkyObjectSounds_PlayHeld)

/* func_020be600: off, and the sources released, from the last. */
void SkyObjectSounds_Release(SkyObjectSounds *sounds)
{
    sounds->on = 0;
    for (int i = SKY_OBJECT_SOUNDS - 1; i >= 0; i--) {
        SoundSource_Release(&sounds->sources[i]);
    }
}
CLEAN_AS(func_020be600, SkyObjectSounds_Release)

/* func_020be628: the sources set up, and on. */
void SkyObjectSounds_Init(SkyObjectSounds *sounds)
{
    for (int i = 0; i < SKY_OBJECT_SOUNDS; i++) {
        SoundSource_Init(&sounds->sources[i]);
    }
    sounds->on = 1;
}
CLEAN_AS(func_020be628, SkyObjectSounds_Init)

/* func_020be64c: the constructor: each source given the base class's vtable and then its own,
 * the points constructed (trivially) and cleared, off. */
SkyObjectSounds *SkyObjectSounds_Construct(SkyObjectSounds *sounds)
{
    for (SoundSource *source = sounds->sources; source != sounds->sources + SKY_OBJECT_SOUNDS; source++) {
        source->vtable = (const SoundSourceVtable *) (const void *) data_0213efe8;
        source->vtable = (const SoundSourceVtable *) (const void *) data_0213f03c;
    }
    __cxa_vec_ctor(sounds->points, SKY_OBJECT_SOUNDS, sizeof(Vec3), func_020012e8, func_020012dc);
    sounds->on = 0;
    for (int i = 0; i < SKY_OBJECT_SOUNDS; i++) {
        sounds->points[i].x = 0;
        sounds->points[i].y = 0;
        sounds->points[i].z = 0;
    }
    return sounds;
}
CLEAN_AS(func_020be64c, SkyObjectSounds_Construct)
