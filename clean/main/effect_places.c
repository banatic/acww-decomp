/* Starting sets at a place and putting their emitters there (effect_places.h). */
#include "effect_places.h"

#include "clean.h"

/* The place being started, followed by the handle the next kept set takes (at 0x39c of
 * data_021d52d8). */
typedef struct EffectPlacesStarting {
    EffectKindsPlace place; /* 0x00 */
    u16 next_handle;        /* 0x1c */
} EffectPlacesStarting;

static_assert(offsetof(EffectPlacesStarting, next_handle) == 0x1c, "EffectPlacesStarting.next_handle");

#define EFFECT_PLACES_COUNT 32

/* The places kept for the effects, and the one being started. */
extern EffectKindsPlace data_021d52d8[EFFECT_PLACES_COUNT];
extern EffectPlacesStarting data_021d5658;
extern const s16 FX_SinCosTable_[];

/* The default set-up words of a one-shot set (EffectPlaces_SetUp for each emitter) and of a
 * kept set (EffectPlaces_PlaceDefault and EffectPlaces_FollowDefault for each emitter). */
extern void *data_020e29fc[];
extern void *data_020e2ac4[];

/* The place being started filled: cleared, then the handle, the kind, the point, the angle and
 * the half-word 0x10 when given, and the frames. */
extern void func_02091494(EffectKindsPlace *place, int handle, int kind, const Vec3 *position, const s16 *angle,
                          const s16 *extra, int frames);
/* A kept set's emitters started at `position`, each given its two words of `setups`; nonzero
 * when it started. */
extern int func_02090ac4(int set, const Vec3 *position, const s16 *angle, void *const *setups);
/* A one-shot set's emitters started the same way, one word each. */
extern int func_02090c2c(int set, const Vec3 *position, const s16 *angle, void *const *setups);
/* A place cleared (no handle, no kind). */
extern void func_020914dc(EffectKindsPlace *place);
/* The emitter's colour tinted as its resource asks. */
extern void func_02090db0(ParticleEmitter *emitter);
/* The frames of each of the 32 places with handle `handle` set to `frames` (none for -1). */
extern void func_020913c8(EffectKindsPlace *places, int handle, s16 frames);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define EFFECT_PLACES_NOT_STARTED 3
#define EFFECT_PLACES_KEPT_STARTED 0
#define EFFECT_PLACES_ONE_SHOT_STARTED 1
#define EFFECT_PLACES_NO_HANDLE (-1)
#define EFFECT_PLACES_FOR_EVER (-1)
#define EFFECT_PLACES_HALF_TURN 0x8000

/* The ARM's 32-bit sum. */
static fx32 effect_places_add(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

/* The emitter's point: `at` and its resource's base position. */
static void effect_places_put_at(ParticleEmitter *emitter, const Vec3 *at)
{
    emitter->position.x = effect_places_add(at->x, emitter->resource->header->base_pos.x);
    emitter->position.y = effect_places_add(at->y, emitter->resource->header->base_pos.y);
    emitter->position.z = effect_places_add(at->z, emitter->resource->header->base_pos.z);
}

/* The emitter's axis level and pointing at `angle` about Y; then its tint. */
static void effect_places_face(ParticleEmitter *emitter, u16 angle)
{
    int index = (angle >> 4) * 2;
    emitter->axis.x = FX_SinCosTable_[index];
    emitter->axis.y = 0;
    emitter->axis.z = FX_SinCosTable_[index + 1];
    func_02090db0(emitter);
}

/* func_02094b58: a kept set started at a place filled from the arguments with the next handle
 * and no end (`setups` NULL for the default words); 0 when it started, else 3. The place being
 * started is cleared afterwards. */
int EffectPlaces_StartKept(int set, int kind, const Vec3 *position, const s16 *angle, const s16 *extra, void *const *setups)
{
    int result = EFFECT_PLACES_NOT_STARTED;

    if (setups == NULL) {
        setups = data_020e2ac4;
    }
    func_02091494(&data_021d5658.place, data_021d5658.next_handle, kind, position, angle, extra, EFFECT_PLACES_FOR_EVER);
    if (func_02090ac4(set, position, angle, setups) != 0) {
        result = EFFECT_PLACES_KEPT_STARTED;
    }
    func_020914dc(&data_021d5658.place);
    return result;
}
CLEAN_AS(func_02094b58, EffectPlaces_StartKept)

/* func_02094bb4: the default follow word: the emitter moved with its place, with no offset and
 * its axis left as it is. */
void EffectPlaces_FollowDefault(EffectKindsInstance *instance)
{
    EffectPlaces_Follow(instance, NULL, NULL);
}
CLEAN_AS(func_02094bb4, EffectPlaces_FollowDefault)

/* func_02094bc0: the default place word: the emitter put at the place being started, with no
 * offset and its axis left as it is. */
void EffectPlaces_PlaceDefault(EffectKindsInstance *instance)
{
    EffectPlaces_Place(instance, NULL, NULL);
}
CLEAN_AS(func_02094bc0, EffectPlaces_PlaceDefault)

/* func_02094bcc: while the instance's kept place has a handle and frames left, its emitter is
 * put there (`offset` and `axis`, each NULL for none, turned by the place's angle) and a
 * counted frame used up; else the place is cleared. Whether it was put. */
int EffectPlaces_Follow(EffectKindsInstance *instance, const Vec3 *offset, const Vec3 *axis)
{
    EffectKindsPlace *place = &data_021d52d8[instance->slot];
    int lasts = 0;

    if (place->handle != EFFECT_PLACES_NO_HANDLE && place->frames != 0) {
        EffectPlaces_PutEmitter(instance->emitter, place, offset, axis);
        if (place->frames > 0) {
            place->frames--;
        }
        lasts = 1;
    }
    if (!lasts) {
        func_020914dc(place);
    }
    return lasts;
}
CLEAN_AS(func_02094bcc, EffectPlaces_Follow)

/* func_02094c38: the instance's emitter put at the place being started (`offset` and `axis`
 * turned by its angle) and tinted, and the place kept in the instance's entry. */
void EffectPlaces_Place(EffectKindsInstance *instance, const Vec3 *offset, const Vec3 *axis)
{
    u8 slot = instance->slot;

    EffectPlaces_PutEmitter(instance->emitter, &data_021d5658.place, offset, axis);
    func_02090db0(instance->emitter);
    MI_CpuCopy8(&data_021d5658.place, &data_021d52d8[slot], sizeof(EffectKindsPlace));
}
CLEAN_AS(func_02094c38, EffectPlaces_Place)

/* func_02094c8c: as EffectPlaces_Follow without moving the emitter: while the instance's kept
 * place has a handle and frames left a counted frame is used up, else the place is cleared.
 * Whether it lasted. */
int EffectPlaces_CountDown(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8[instance->slot];
    int lasts = 0;

    if (place->handle != EFFECT_PLACES_NO_HANDLE && place->frames != 0) {
        if (place->frames > 0) {
            place->frames--;
        }
        lasts = 1;
    }
    if (!lasts) {
        func_020914dc(place);
    }
    return lasts;
}
CLEAN_AS(func_02094c8c, EffectPlaces_CountDown)

/* func_02094ce4: the kept places of handle `handle` given no frames left, which ends their
 * emitters' following at their next frame. */
void EffectPlaces_EndHandle(int handle)
{
    func_020913c8(data_021d52d8, handle, 0);
}
CLEAN_AS(func_02094ce4, EffectPlaces_EndHandle)

/* func_02094cf8: a one-shot set started at a place filled from the arguments with no handle and
 * no end (`setups` NULL for the default words); 1 when it started, else 3. */
int EffectPlaces_StartOneShot(int set, int kind, const Vec3 *position, const s16 *angle, const s16 *extra, void *const *setups)
{
    int result = EFFECT_PLACES_NOT_STARTED;

    if (setups == NULL) {
        setups = data_020e29fc;
    }
    func_02091494(&data_021d5658.place, EFFECT_PLACES_NO_HANDLE, kind, position, angle, extra, EFFECT_PLACES_FOR_EVER);
    if (func_02090c2c(set, position, angle, setups) != 0) {
        result = EFFECT_PLACES_ONE_SHOT_STARTED;
    }
    return result;
}
CLEAN_AS(func_02094cf8, EffectPlaces_StartOneShot)

/* func_02094d48: the new emitter put at the place being started (`offset` and `axis` turned by
 * its angle) and tinted. */
void EffectPlaces_SetUpAt(ParticleEmitter *emitter, const Vec3 *offset, const Vec3 *axis)
{
    EffectPlaces_PutEmitter(emitter, &data_021d5658.place, offset, axis);
    func_02090db0(emitter);
}
CLEAN_AS(func_02094d48, EffectPlaces_SetUpAt)

/* func_02094d6c: the emitter put at `place` plus `offset` turned by the place's angle about Y,
 * and its resource's base position; its axis set to `axis` turned the same way and made of
 * length one, unless that is zero. Either may be NULL for none (the axis is then left). */
void EffectPlaces_PutEmitter(ParticleEmitter *emitter, const EffectKindsPlace *place, const Vec3 *offset, const Vec3 *axis)
{
    Vec3 at = place->position;

    if (offset != NULL) {
        Vec3 turned = *offset;
        Vec_RotateY(&turned, place->angle);
        VEC_Add(&at, &turned, &at);
    }
    effect_places_put_at(emitter, &at);
    if (axis != NULL) {
        Vec3 turned = *axis;
        Vec_RotateY(&turned, place->angle);
        if (Vec_NormalizeNonZero(&turned) != 0) {
            emitter->axis.x = (fx16) turned.x;
            emitter->axis.y = (fx16) turned.y;
            emitter->axis.z = (fx16) turned.z;
        }
    }
}
CLEAN_AS(func_02094d6c, EffectPlaces_PutEmitter)

/* func_02094e04: the new emitter set up at the place being started (EffectPlaces_SetUp), its
 * particles' base scale `scale`. */
void EffectPlaces_SetUpScaled(ParticleEmitter *emitter, fx32 scale)
{
    EffectPlaces_SetUp(emitter);
    emitter->base_scale = scale;
}
CLEAN_AS(func_02094e04, EffectPlaces_SetUpScaled)

/* func_02094e1c: the new emitter put at the place being started, its axis level and pointing
 * away from the place's angle, and tinted. */
void EffectPlaces_SetUpFacingBack(ParticleEmitter *emitter)
{
    EffectPlaces_PutFacingBack(emitter, &data_021d5658.place);
}
CLEAN_AS(func_02094e1c, EffectPlaces_SetUpFacingBack)

/* func_02094e2c: the emitter put at `place`, its axis level and pointing half a turn from the
 * place's angle, and tinted. */
void EffectPlaces_PutFacingBack(ParticleEmitter *emitter, const EffectKindsPlace *place)
{
    effect_places_put_at(emitter, &place->position);
    effect_places_face(emitter, (u16) ((u16) place->angle + EFFECT_PLACES_HALF_TURN));
}
CLEAN_AS(func_02094e2c, EffectPlaces_PutFacingBack)

/* func_02094e90: the new emitter put at the place being started, its axis level and pointing at
 * the place's angle, and tinted. */
void EffectPlaces_SetUpFacing(ParticleEmitter *emitter)
{
    EffectPlaces_PutFacing(emitter, &data_021d5658.place);
}
CLEAN_AS(func_02094e90, EffectPlaces_SetUpFacing)

/* func_02094ea0: the emitter put at `place`, its axis level and pointing at the place's angle,
 * and tinted. */
void EffectPlaces_PutFacing(ParticleEmitter *emitter, const EffectKindsPlace *place)
{
    effect_places_put_at(emitter, &place->position);
    effect_places_face(emitter, (u16) place->angle);
}
CLEAN_AS(func_02094ea0, EffectPlaces_PutFacing)

/* func_02094ef4: the default set-up word: the new emitter put at the place being started, and
 * tinted. */
void EffectPlaces_SetUp(ParticleEmitter *emitter)
{
    effect_places_put_at(emitter, &data_021d5658.place.position);
    func_02090db0(emitter);
}
CLEAN_AS(func_02094ef4, EffectPlaces_SetUp)

/* func_02094f28: a set-up word that only tints the new emitter (left where it started). */
void EffectPlaces_SetUpTintOnly(ParticleEmitter *emitter)
{
    func_02090db0(emitter);
}
CLEAN_AS(func_02094f28, EffectPlaces_SetUpTintOnly)
