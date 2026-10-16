/* Starting the particle file's sets at a place, and putting their emitters there (the helpers
 * the effect kinds of effect_kinds.h start and move their emitters with).
 *
 * A start function fills the place being started (data_021d5658, EffectKindsPlace) from its
 * arguments and starts a set of emitters there:
 * - a one-shot set (EffectPlaces_StartOneShot) gives each new emitter its set-up word, which
 *   puts it at the place (EffectPlaces_SetUp and its variants below) and tints it;
 * - a kept set (EffectPlaces_StartKept) gives the place the next handle; each emitter's first
 *   word puts it at the place and keeps the place in the instance's entry of data_021d52d8
 *   (EffectPlaces_Place), its second moves it with that entry each frame while the entry
 *   lasts (EffectPlaces_Follow), counting the entry's frames down. EffectPlaces_EndHandle ends
 *   the entries of a handle by setting their frames to 0. */
#ifndef CLEAN_MAIN_EFFECT_PLACES_H
#define CLEAN_MAIN_EFFECT_PLACES_H

#include "autoload_2/particle.h"
#include "autoload_2/vector.h"
#include "effect_kinds.h"
#include "types.h"

int EffectPlaces_StartKept(int set, int kind, const Vec3 *position, const s16 *angle, const s16 *extra, void *const *setups);
void EffectPlaces_FollowDefault(EffectKindsInstance *instance);
void EffectPlaces_PlaceDefault(EffectKindsInstance *instance);
int EffectPlaces_Follow(EffectKindsInstance *instance, const Vec3 *offset, const Vec3 *axis);
void EffectPlaces_Place(EffectKindsInstance *instance, const Vec3 *offset, const Vec3 *axis);
int EffectPlaces_CountDown(EffectKindsInstance *instance);
void EffectPlaces_EndHandle(int handle);
int EffectPlaces_StartOneShot(int set, int kind, const Vec3 *position, const s16 *angle, const s16 *extra,
                              void *const *setups);
void EffectPlaces_SetUpAt(ParticleEmitter *emitter, const Vec3 *offset, const Vec3 *axis);
void EffectPlaces_PutEmitter(ParticleEmitter *emitter, const EffectKindsPlace *place, const Vec3 *offset, const Vec3 *axis);
void EffectPlaces_SetUpScaled(ParticleEmitter *emitter, fx32 scale);
void EffectPlaces_SetUpFacingBack(ParticleEmitter *emitter);
void EffectPlaces_PutFacingBack(ParticleEmitter *emitter, const EffectKindsPlace *place);
void EffectPlaces_SetUpFacing(ParticleEmitter *emitter);
void EffectPlaces_PutFacing(ParticleEmitter *emitter, const EffectKindsPlace *place);
void EffectPlaces_SetUp(ParticleEmitter *emitter);
void EffectPlaces_SetUpTintOnly(ParticleEmitter *emitter);

#endif
