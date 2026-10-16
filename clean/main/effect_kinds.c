/* The effects started by kind, and their emitters (effect_kinds.h). */
#include "effect_kinds.h"

#include "autoload_2/fx_math.h"
#include "clean.h"
#include "field_collision.h"
#include "scene_query.h"
#include "sky.h"

static_assert(sizeof(EffectKindsPlace) == 0x1c, "EffectKindsPlace");
static_assert(offsetof(EffectKindsPlace, angle) == 0x0c, "EffectKindsPlace.angle");
static_assert(offsetof(EffectKindsPlace, frames) == 0x0e, "EffectKindsPlace.frames");
static_assert(offsetof(EffectKindsPlace, handle) == 0x14, "EffectKindsPlace.handle");
static_assert(offsetof(EffectKindsPlace, kind) == 0x18, "EffectKindsPlace.kind");
static_assert(offsetof(EffectKindsInstance, slot) == 0x04, "EffectKindsInstance.slot");
static_assert(offsetof(EffectKindsInstance, emitter) == 0x0c, "EffectKindsInstance.emitter");
static_assert(offsetof(EffectKindsModelTransform, position) == 0x04, "EffectKindsModelTransform.position");
static_assert(offsetof(EffectKindsModelTransform, scale) == 0x10, "EffectKindsModelTransform.scale");
static_assert(offsetof(EffectKindsModelTransform, rotation) == 0x1c, "EffectKindsModelTransform.rotation");
static_assert(offsetof(ParticleEmitter, state) == 0x1c, "ParticleEmitter.state");
static_assert(offsetof(ParticleEmitter, position) == 0x20, "ParticleEmitter.position");
static_assert(offsetof(ParticleEmitter, axis) == 0x3c, "ParticleEmitter.axis");
static_assert(offsetof(ParticleEmitter, speed) == 0x4c, "ParticleEmitter.speed");
static_assert(offsetof(ParticleEmitter, base_scale) == 0x54, "ParticleEmitter.base_scale");
static_assert(offsetof(ParticleEmitter, color) == 0x5a, "ParticleEmitter.color");
static_assert(offsetof(ParticleEmitter, misc) == 0x68, "ParticleEmitter.misc");
static_assert(offsetof(ParticleEmitter, callback) == 0x78, "ParticleEmitter.callback");
static_assert(offsetof(Particle, rotation) == 0x20, "Particle.rotation");
static_assert(offsetof(Particle, life) == 0x24, "Particle.life");

/* The places kept for the effects, and the one being started. */
extern EffectKindsPlace data_021d52d8[];
extern EffectKindsPlace data_021d5658;
/* Whether the scene is a room (1) or outdoors (0). */
extern u8 data_020e54a8;
extern const s16 FX_SinCosTable_[];

/* The emitters' offsets from their place and their axes (before the place's angle turns them). */
extern const Vec3 data_020d16b4; /* (-0.125, 0, -0.06) */
extern const Vec3 data_020d16c0; /* (0.18, 0, 0.5) */
extern const Vec3 data_020d16fc; /* (0.25, 1, 0) */
extern const Vec3 data_020d1714; /* (0.52, 0, 0) */
extern const Vec3 data_020d1720; /* (-0.45, 0, -0.55) */
extern const Vec3 data_020d1738; /* (-0.45, 0, 0.37) */
extern const Vec3 data_020d1750; /* (0, 0, 1) */
extern const Vec3 data_020d1768; /* (0, 1, -1) */
extern const Vec3 data_020d17c8; /* (0, 1, 1) */
extern const Vec3 data_020d17d4; /* (0, 0.85, 0.52) */
extern const Vec3 data_020d17e0; /* (-0.37, 0, -0.52) */
extern const Vec3 data_020d17ec; /* (0.3, 0, -0.075) */
extern const Vec3 data_020d17f8; /* (-0.25, 0, 0.3) */
extern const Vec3 data_020d1804; /* (0.22, 0, 0.6) */

/* The set-up words of the sets (one per emitter of a one-shot set, two of a kept one). */
extern void *data_020e2780[];
extern void *data_020e278c[];
extern void *data_020e2790[];
extern void *data_020e27a4[];
extern void *data_020e27ac[];
extern void *data_020e27b4[];
extern void *data_020e27b8[];
extern void *data_020e27c8[];
extern void *data_020e27cc[];
extern void *data_020e27e4[];
extern void *data_020e27ec[];
extern void *data_020e27fc[];
extern void *data_020e283c[];
extern void *data_020e2844[];
extern void *data_020e2854[];
extern void *data_020e28a4[];
extern void *data_020e28b4[];
extern void *data_020e28c4[];
extern void *data_020e28d4[];
extern void *data_020e2904[3];
extern void *data_020e2964[];
extern void *data_020e29dc[];
extern void *data_020e29fc[];
extern void *data_020e2a64[];

/* A kept set started at a place filled from the arguments (`setups` NULL for the default
 * words): 0 when it started, else 3. */
extern int func_02094b58(int set, int kind, const Vec3 *position, const s16 *angle, const s16 *extra, void *const *setups);
/* A one-shot set started the same way: 1 when it started, else 3. */
extern int func_02094cf8(int set, int kind, const Vec3 *position, const s16 *angle, const s16 *extra, void *const *setups);
/* The place being started (data_021d5658) filled: cleared, then the handle, the kind, the point,
 * the angle and the half-word 0x10 when given, and the frames. */
extern void func_02091494(EffectKindsPlace *place, int handle, int kind, const Vec3 *position, const s16 *angle,
                          const s16 *extra, int frames);
/* The set's emitters started at `position`, each given its word of `setups`; 0 when `position`
 * is NULL, else 1. */
extern int func_02090c2c(int set, const Vec3 *position, const s16 *angle, void *const *setups);
/* The instance's emitter put at the place being started, `offset` and `axis` (each NULL for
 * none) turned by its angle; the place kept in the instance's entry of data_021d52d8. */
extern void func_02094c38(EffectKindsInstance *instance, const Vec3 *offset, const Vec3 *axis);
/* The instance's emitter moved with its kept place while it lasts (counting its frames down);
 * whether it did, the entry cleared when not. */
extern int func_02094bcc(EffectKindsInstance *instance, const Vec3 *offset, const Vec3 *axis);
/* The new emitter put at the place being started, `offset` and `axis` turned by its angle, and
 * tinted. */
extern void func_02094d48(ParticleEmitter *emitter, const Vec3 *offset, const Vec3 *axis);
/* The new emitter put at the place being started, and tinted. */
extern void func_02094ef4(ParticleEmitter *emitter);
/* The emitter's colour tinted as its resource asks. */
extern void func_02090db0(ParticleEmitter *emitter);
/* For each particle of the emitter that has come down to the ground (or to height 0 where the
 * ground has none), the given one-shot sets (-1 for none) started there and the particle ended;
 * whether the emitter has particles. */
extern int func_0209493c(ParticleEmitter *emitter, int ground_set, void *const *ground_setups, int ground_set2,
                         void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                         void *const *floor_setups2);
/* A place cleared (no handle, no kind). */
extern void func_020914dc(EffectKindsPlace *place);
/* Model `model` started at a place filled from the arguments, `setup` setting its transform up. */
extern int func_02094840(int model, int kind, const Vec3 *position, const s16 *angle, const s16 *extra,
                         void (*setup)(void *transform));
extern void func_02093678(void *transform);
extern void func_020933c0(ParticleEmitter *emitter, unsigned int after);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* The particle file's sets the kinds start. */
#define EFFECT_KINDS_SET_KIND_34 0x52
#define EFFECT_KINDS_SET_KIND_33 0x74
#define EFFECT_KINDS_SET_KIND_32 0x63
#define EFFECT_KINDS_SET_KIND_31 0x7a
#define EFFECT_KINDS_SET_KIND_30 0x79
#define EFFECT_KINDS_SET_KIND_2F 0x78
#define EFFECT_KINDS_SET_KIND_2E 0x77
#define EFFECT_KINDS_SET_KIND_2D 0x76
#define EFFECT_KINDS_SET_54 0x54 /* one emitter, started with kinds 0x2d-0x2f */
#define EFFECT_KINDS_SET_TWO_MARKS 0x57
#define EFFECT_KINDS_SET_MARK 0x58
#define EFFECT_KINDS_SET_KIND_28 0x56
#define EFFECT_KINDS_SET_KIND_27 0x55
#define EFFECT_KINDS_SET_KIND_26 0x70
#define EFFECT_KINDS_SET_KIND_26_LANDING 0x71
#define EFFECT_KINDS_SET_KIND_26_FLOOR 0x72
#define EFFECT_KINDS_SET_KIND_25 0x5a
#define EFFECT_KINDS_SET_KIND_24 0x59
#define EFFECT_KINDS_SET_KIND_23 0x6e
#define EFFECT_KINDS_SET_KIND_23_ON_13 0x6f
#define EFFECT_KINDS_SET_KIND_22 0x4b
#define EFFECT_KINDS_SET_KIND_22_ON_13 0x4c
#define EFFECT_KINDS_SET_KIND_22_WET 0x4d
#define EFFECT_KINDS_SET_KIND_22_SNOW 0x4e
#define EFFECT_KINDS_SET_SIZED 0x73 /* kinds 0x1a-0x21 */

/* The model kind 0x24 starts with its particles. */
#define EFFECT_KINDS_MODEL_KIND_24 3

/* Ground attributes (CollisionGround.attr) the kinds look at. */
#define EFFECT_KINDS_GROUND_13 0x13
#define EFFECT_KINDS_GROUND_3 3
#define EFFECT_KINDS_GROUND_9 9
#define EFFECT_KINDS_GROUND_16 0x16

#define EFFECT_KINDS_NOT_STARTED 3
#define EFFECT_KINDS_ONE 0x1000
#define EFFECT_KINDS_LIGHT_COLOR 3 /* the sky's light colour of kind 0x32's emitters */

/* The ARM's 32-bit sum. */
static fx32 effect_kinds_add(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

/* The emitter's point: `at` and its resource's base position. */
static void effect_kinds_put(ParticleEmitter *emitter, const Vec3 *at)
{
    emitter->position.x = effect_kinds_add(at->x, emitter->resource->header->base_pos.x);
    emitter->position.y = effect_kinds_add(at->y, emitter->resource->header->base_pos.y);
    emitter->position.z = effect_kinds_add(at->z, emitter->resource->header->base_pos.z);
}

/* func_02092e44: the fourth emitter of kind 0x35 placed, giving off particles every 5 frames
 * at speeds 0.055 and 0.15. */
void EffectKinds_PlaceKind35B(EffectKindsInstance *instance)
{
    EffectKinds_PlaceWithSpeeds(instance, 5, 0xe1, 0x266);
}
CLEAN_AS(func_02092e44, EffectKinds_PlaceKind35B)

/* func_02092e5c: the second and third emitters of kind 0x35 placed, giving off particles every
 * 5 frames at speeds 0.05 and 0.125. */
void EffectKinds_PlaceKind35A(EffectKindsInstance *instance)
{
    EffectKinds_PlaceWithSpeeds(instance, 5, 0xcd, 0x200);
}
CLEAN_AS(func_02092e5c, EffectKinds_PlaceKind35A)

/* func_02092e74: the instance's emitter placed with its axis forward (turned by the place's
 * angle), then its emission interval and its speeds away from its centre and along its axis
 * set. */
void EffectKinds_PlaceWithSpeeds(EffectKindsInstance *instance, char interval, fx32 speed, fx32 axis_speed)
{
    func_02094c38(instance, NULL, &data_020d1750);
    instance->emitter->misc = particle_with_bits(instance->emitter->misc, EMITTER_INTERVAL_SHIFT, 8, (u8) interval);
    instance->emitter->speed = speed;
    instance->emitter->axis_speed = axis_speed;
}
CLEAN_AS(func_02092e74, EffectKinds_PlaceWithSpeeds)

/* func_02092ea4: kind 0x34, kept set 0x52 with the default words. */
void EffectKinds_StartKind34(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_KIND_34, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02092ea4, EffectKinds_StartKind34)

/* func_02092ec8: kind 0x33, kept set 0x74, only while rain falls. */
int EffectKinds_StartKind33(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    if (Sky_Falling() == SKY_FALLING_RAIN) {
        return func_02094b58(EFFECT_KINDS_SET_KIND_33, kind, position, angle, extra, data_020e28d4);
    }
    return EFFECT_KINDS_NOT_STARTED;
}
CLEAN_AS(func_02092ec8, EffectKinds_StartKind33)

/* func_02092f00: kind 0x33's emitter moved with its place, its axis up and back. */
int EffectKinds_FollowKind33(EffectKindsInstance *instance)
{
    return func_02094bcc(instance, NULL, &data_020d1768);
}
CLEAN_AS(func_02092f00, EffectKinds_FollowKind33)

/* func_02092f10: kind 0x33's emitter placed, its axis up and back. */
void EffectKinds_PlaceKind33(EffectKindsInstance *instance)
{
    func_02094c38(instance, NULL, &data_020d1768);
}
CLEAN_AS(func_02092f10, EffectKinds_PlaceKind33)

/* func_02092f20: kind 0x32, one-shot set 0x63. */
void EffectKinds_StartKind32(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094cf8(EFFECT_KINDS_SET_KIND_32, kind, position, angle, extra, data_020e27a4);
}
CLEAN_AS(func_02092f20, EffectKinds_StartKind32)

/* func_02092f48: kind 0x32's first emitter set up at its place, its colour the sky's light
 * colour 3 instead of the tint. */
void EffectKinds_SetUpKind32(ParticleEmitter *emitter)
{
    func_02094ef4(emitter);
    /* QUIRK: each of the colour's components is scaled by white's (c * 31 / 31), which leaves
     * the light colour as it is, its top bit too. */
    emitter->color = (u16) Sky_LightColor(EFFECT_KINDS_LIGHT_COLOR);
}
CLEAN_AS(func_02092f48, EffectKinds_SetUpKind32)

/* func_02092ff8: kind 0x31, kept set 0x7a. */
void EffectKinds_StartKind31(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_KIND_31, kind, position, angle, extra, data_020e27fc);
}
CLEAN_AS(func_02092ff8, EffectKinds_StartKind31)

/* func_02093020: kind 0x31's emitter moved with its place, its axis forward. */
void EffectKinds_FollowKind31(EffectKindsInstance *instance)
{
    Vec3 forward = {0, 0, EFFECT_KINDS_ONE};

    func_02094bcc(instance, NULL, &forward);
}
CLEAN_AS(func_02093020, EffectKinds_FollowKind31)

/* func_02093040: kind 0x31's emitter placed, its axis forward. */
void EffectKinds_PlaceKind31(EffectKindsInstance *instance)
{
    func_02094c38(instance, NULL, &data_020d1750);
}
CLEAN_AS(func_02093040, EffectKinds_PlaceKind31)

/* func_02093050: kind 0x30, kept set 0x79. */
void EffectKinds_StartKind30(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_KIND_30, kind, position, angle, extra, data_020e28a4);
}
CLEAN_AS(func_02093050, EffectKinds_StartKind30)

/* func_02093078: kind 0x2f, set 0x78 and the three of set 0x54. */
void EffectKinds_StartKind2f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    EffectKinds_StartWithThree54(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_2F);
}
CLEAN_AS(func_02093078, EffectKinds_StartKind2f)

/* func_0209308c: kind 0x2e, set 0x77 and the three of set 0x54. */
void EffectKinds_StartKind2e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    EffectKinds_StartWithThree54(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_2E);
}
CLEAN_AS(func_0209308c, EffectKinds_StartKind2e)

/* func_020930a0: one-shot set `set`, then set 0x54 three times with the three set-up words of
 * data_020e2904 (an emitter at each of three offsets); 1, or 3 as soon as one fails. */
int EffectKinds_StartWithThree54(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set)
{
    int i;

    func_02091494(&data_021d5658, -1, kind, position, angle, extra, -1);
    if (func_02090c2c(set, position, angle, data_020e27c8) == 0) {
        return EFFECT_KINDS_NOT_STARTED;
    }
    for (i = 0; i < 3; i++) {
        if (func_02090c2c(EFFECT_KINDS_SET_54, position, angle, &data_020e2904[i]) == 0) {
            return EFFECT_KINDS_NOT_STARTED;
        }
    }
    return 1;
}
CLEAN_AS(func_020930a0, EffectKinds_StartWithThree54)

/* func_0209310c: the third emitter of set 0x54 set up at its offset (data_020d1738). */
void EffectKinds_SetUp54C(ParticleEmitter *emitter)
{
    func_02094d48(emitter, &data_020d1738, NULL);
}
CLEAN_AS(func_0209310c, EffectKinds_SetUp54C)

/* func_0209311c: the second emitter of set 0x54 set up at its offset (data_020d1720). */
void EffectKinds_SetUp54B(ParticleEmitter *emitter)
{
    func_02094d48(emitter, &data_020d1720, NULL);
}
CLEAN_AS(func_0209311c, EffectKinds_SetUp54B)

/* func_0209312c: the first emitter of set 0x54 set up at its offset (data_020d1714). */
void EffectKinds_SetUp54A(ParticleEmitter *emitter)
{
    func_02094d48(emitter, &data_020d1714, NULL);
}
CLEAN_AS(func_0209312c, EffectKinds_SetUp54A)

/* func_0209313c: kind 0x2d, one-shot set 0x76 then set 0x54 with the default word; 1 when
 * both started, else 3. */
int EffectKinds_StartKind2d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    int result = EFFECT_KINDS_NOT_STARTED;

    func_02091494(&data_021d5658, -1, kind, position, angle, extra, -1);
    if (func_02090c2c(EFFECT_KINDS_SET_KIND_2D, position, angle, data_020e27c8) != 0 &&
        func_02090c2c(EFFECT_KINDS_SET_54, position, angle, data_020e29fc) != 0) {
        result = 1;
    }
    return result;
}
CLEAN_AS(func_0209313c, EffectKinds_StartKind2d)

/* func_02093194: the emitter of sets 0x76-0x78 (kinds 0x2d-0x2f) set up, its axis mostly up. */
void EffectKinds_SetUpKind2d(ParticleEmitter *emitter)
{
    func_02094d48(emitter, NULL, &data_020d16fc);
}
CLEAN_AS(func_02093194, EffectKinds_SetUpKind2d)

/* func_020931a4: kind 0x2c, two marks of set 0x57 (data_020e2790, then data_020e27b8) where
 * the ground takes marks; the second's result, or 3 when the first failed. */
int EffectKinds_StartKind2c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    if (EffectKinds_StartOnMarkGround(kind, position, angle, extra, EFFECT_KINDS_SET_TWO_MARKS, data_020e2790) == 1) {
        return EffectKinds_StartOnMarkGround(kind, position, angle, extra, EFFECT_KINDS_SET_TWO_MARKS, data_020e27b8);
    }
    return EFFECT_KINDS_NOT_STARTED;
}
CLEAN_AS(func_020931a4, EffectKinds_StartKind2c)

/* func_020931e8: kind 0x2c's second mark set up at its offset (data_020d16c0). */
void EffectKinds_SetUpMark2cSecond(ParticleEmitter *emitter)
{
    EffectKinds_SetUpMark(emitter, &data_020d16c0, 0);
}
CLEAN_AS(func_020931e8, EffectKinds_SetUpMark2cSecond)

/* func_020931f8: kind 0x2c's first mark set up at its offset (data_020d16b4). */
void EffectKinds_SetUpMark2cFirst(ParticleEmitter *emitter)
{
    EffectKinds_SetUpMark(emitter, &data_020d16b4, 0);
}
CLEAN_AS(func_020931f8, EffectKinds_SetUpMark2cFirst)

/* func_02093208: kind 0x2b, two marks of set 0x57 (data_020e27ac, then data_020e2780) where
 * the ground takes marks; the second's result, or 3 when the first failed. */
int EffectKinds_StartKind2b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    if (EffectKinds_StartOnMarkGround(kind, position, angle, extra, EFFECT_KINDS_SET_TWO_MARKS, data_020e27ac) == 1) {
        return EffectKinds_StartOnMarkGround(kind, position, angle, extra, EFFECT_KINDS_SET_TWO_MARKS, data_020e2780);
    }
    return EFFECT_KINDS_NOT_STARTED;
}
CLEAN_AS(func_02093208, EffectKinds_StartKind2b)

/* func_0209324c: kind 0x2b's second mark set up at its offset (data_020d1804). */
void EffectKinds_SetUpMark2bSecond(ParticleEmitter *emitter)
{
    EffectKinds_SetUpMark(emitter, &data_020d1804, 0);
}
CLEAN_AS(func_0209324c, EffectKinds_SetUpMark2bSecond)

/* func_0209325c: kind 0x2b's first mark set up at its offset (data_020d17f8). */
void EffectKinds_SetUpMark2bFirst(ParticleEmitter *emitter)
{
    EffectKinds_SetUpMark(emitter, &data_020d17f8, 0);
}
CLEAN_AS(func_0209325c, EffectKinds_SetUpMark2bFirst)

/* func_0209326c: kind 0x2a, a mark of set 0x58 where the ground takes marks. */
int EffectKinds_StartKind2a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectKinds_StartOnMarkGround(kind, position, angle, extra, EFFECT_KINDS_SET_MARK, data_020e27b4);
}
CLEAN_AS(func_0209326c, EffectKinds_StartKind2a)

/* func_02093288: kind 0x2a's mark set up at its offset (data_020d17ec). */
void EffectKinds_SetUpMark2a(ParticleEmitter *emitter)
{
    EffectKinds_SetUpMark(emitter, &data_020d17ec, 0);
}
CLEAN_AS(func_02093288, EffectKinds_SetUpMark2a)

/* func_02093298: kind 0x29, a mark of set 0x58 where the ground takes marks. */
void EffectKinds_StartKind29(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the answer is still in r0 when it returns,
     * and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectKinds_StartOnMarkGround(kind, position, angle, extra, EFFECT_KINDS_SET_MARK, data_020e278c);
}
CLEAN_AS(func_02093298, EffectKinds_StartKind29)

/* One-shot set `set` started where the ground takes marks (and `set` is not -1); else 3.
 * The ground is released after the set has started. */
static int effect_kinds_start_on_mark_ground(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set,
                                             void *const *setups)
{
    CollisionGround ground;
    int attr;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    attr = ground.attr;
    if ((attr == EFFECT_KINDS_GROUND_13 || (SceneQuery_IsSnowSeason() && attr == EFFECT_KINDS_GROUND_3)) && set != -1) {
        result = func_02094cf8(set, kind, position, angle, extra, setups);
    } else {
        result = EFFECT_KINDS_NOT_STARTED;
    }
    CollisionGround_Destroy(&ground);
    return result;
}

/* func_020932b4: one-shot set `set` (-1 for none) started where the ground takes marks;
 * else 3. */
int EffectKinds_StartOnMarkGround(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set,
                                  void *const *setups)
{
    return effect_kinds_start_on_mark_ground(kind, position, angle, extra, set, setups);
}
CLEAN_AS(func_020932b4, EffectKinds_StartOnMarkGround)

/* func_02093318: kind 0x29's mark set up at its offset (data_020d17e0), its axis turned by -30000. */
void EffectKinds_SetUpMark29(ParticleEmitter *emitter)
{
    EffectKinds_SetUpMark(emitter, &data_020d17e0, -30000);
}
CLEAN_AS(func_02093318, EffectKinds_SetUpMark29)

/* func_0209332c: a mark's emitter set up at `offset` from the place being started (turned by
 * its angle), its axis the place's angle plus `turn` in the ground plane; its first particle
 * is turned to that axis after the emitter's first update (EffectKinds_TurnFirstParticle). */
void EffectKinds_SetUpMark(ParticleEmitter *emitter, const Vec3 *offset, int turn)
{
    const EffectKindsPlace *place = &data_021d5658;
    u16 axis_angle = (u16) ((u32) place->angle + (u32) turn);
    int index = (axis_angle >> 4) * 2;
    Vec3 at;

    at = *offset;
    Vec_RotateY(&at, place->angle);
    VEC_Add(&at, &place->position, &at);
    effect_kinds_put(emitter, &at);
    emitter->axis.x = FX_SinCosTable_[index];
    emitter->axis.y = 0;
    emitter->axis.z = FX_SinCosTable_[index + 1];
    func_02090db0(emitter);
    emitter->callback = func_020933c0;
}
CLEAN_AS(func_0209332c, EffectKinds_SetUpMark)

/* func_020933c0: a mark emitter's callback: after its update (`after` 1), once it has a
 * particle, the newest particle turned to face the emitter's axis and the callback removed. */
void EffectKinds_TurnFirstParticle(ParticleEmitter *emitter, int after)
{
    Particle *particle;

    if (after != 1) {
        return;
    }
    particle = (Particle *) emitter->particles.first;
    if (particle != NULL) {
        particle->rotation = (u16) Math_Atan2(emitter->axis.x, emitter->axis.z);
        emitter->callback = NULL;
    }
}
CLEAN_AS(func_020933c0, EffectKinds_TurnFirstParticle)

/* func_020933ec: kind 0x28 (a scene object's footstep, footsteps.h), one-shot set 0x56 where
 * the ground takes marks. */
int EffectKinds_StartKind28(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_on_mark_ground(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_28, data_020e29dc);
}
CLEAN_AS(func_020933ec, EffectKinds_StartKind28)

/* func_02093448: kind 0x27, one-shot set 0x55 where the ground takes marks. */
int EffectKinds_StartKind27(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_on_mark_ground(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_27, data_020e29dc);
}
CLEAN_AS(func_02093448, EffectKinds_StartKind27)

/* func_020934a4: kind 0x26, kept set 0x70. */
void EffectKinds_StartKind26(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_KIND_26, kind, position, angle, extra, data_020e28c4);
}
CLEAN_AS(func_020934a4, EffectKinds_StartKind26)

/* Kind 0x26's particles that have come down: sets 0x71 on the ground, 0x71 and 0x72 at
 * height 0. */
static int effect_kinds_land_kind26(ParticleEmitter *emitter)
{
    return func_0209493c(emitter, EFFECT_KINDS_SET_KIND_26_LANDING, data_020e29dc, -1, NULL, EFFECT_KINDS_SET_KIND_26_LANDING,
                         data_020e29dc, EFFECT_KINDS_SET_KIND_26_FLOOR, data_020e29dc);
}

/* func_020934cc: kind 0x26's emitter each frame. While its place is kept and has frames left
 * the emitter is moved there (its axis forward, turned by the place's angle) and its landed
 * particles start their sets; once not, it stops emitting and lasts while it has particles.
 * Whether it lasts; the place's entry is cleared when not. */
int EffectKinds_FollowKind26(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8[instance->slot];
    int lasts = 0;

    if (place->handle != -1 && place->frames != 0) {
        Vec3 axis = {0, 0, EFFECT_KINDS_ONE};

        effect_kinds_put(instance->emitter, &place->position);
        Vec_RotateY(&axis, place->angle);
        instance->emitter->axis.x = (fx16) axis.x;
        instance->emitter->axis.y = (fx16) axis.y;
        instance->emitter->axis.z = (fx16) axis.z;
        effect_kinds_land_kind26(instance->emitter);
        if (place->frames > 0) {
            place->frames = (s16) (place->frames - 1);
        }
        lasts = 1;
    }
    if (!lasts) {
        instance->emitter->state |= EMITTER_NO_EMISSION;
        if (instance->emitter->particles.count > 0) {
            lasts = effect_kinds_land_kind26(instance->emitter);
        }
    }
    if (!lasts) {
        func_020914dc(place);
    }
    return lasts;
}
CLEAN_AS(func_020934cc, EffectKinds_FollowKind26)

/* func_020935c4: kind 0x26's emitter placed, its axis forward. */
void EffectKinds_PlaceKind26(EffectKindsInstance *instance)
{
    func_02094c38(instance, NULL, &data_020d1750);
}
CLEAN_AS(func_020935c4, EffectKinds_PlaceKind26)

/* func_020935d4: kind 0x25, kept set 0x5a (five emitters). */
void EffectKinds_StartKind25(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_KIND_25, kind, position, angle, extra, data_020e2a64);
}
CLEAN_AS(func_020935d4, EffectKinds_StartKind25)

/* func_020935fc: kind 0x25's emitters moved with their place; once it is given up, each of the
 * emitter's particles is made as old as its life (so it ends) and the answer is 0; else 1. */
int EffectKinds_FollowKind25(EffectKindsInstance *instance)
{
    ParticleLink *link;

    if (func_02094bcc(instance, NULL, NULL) != 0) {
        return 1;
    }
    for (link = instance->emitter->particles.first; link != NULL; link = link->next) {
        Particle *particle = (Particle *) link;

        particle->age = particle->life;
    }
    return 0;
}
CLEAN_AS(func_020935fc, EffectKinds_FollowKind25)

/* func_02093628: kind 0x24, one-shot set 0x59 (four emitters); when it started (a result
 * below 3), model 3 too, turned by the place's angle (func_02093678); 1 then, else 3. */
int EffectKinds_StartKind24(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    int result = EFFECT_KINDS_NOT_STARTED;

    if (func_02094cf8(EFFECT_KINDS_SET_KIND_24, kind, position, angle, extra, data_020e2964) < 3) {
        func_02094840(EFFECT_KINDS_MODEL_KIND_24, kind, position, angle, extra, func_02093678);
        result = 1;
    }
    return result;
}
CLEAN_AS(func_02093628, EffectKinds_StartKind24)

/* func_02093678: kind 0x24's model at the place being started, at its size, turned about Y by
 * the place's angle. */
void EffectKinds_SetModelTransformTurned(EffectKindsModelTransform *transform)
{
    const EffectKindsPlace *place = &data_021d5658;

    transform->position.x = place->position.x;
    transform->position.y = place->position.y;
    transform->position.z = place->position.z;
    transform->scale.x = EFFECT_KINDS_ONE;
    transform->scale.y = EFFECT_KINDS_ONE;
    transform->scale.z = EFFECT_KINDS_ONE;
    transform->rotation[0] = 0;
    transform->rotation[1] = place->angle;
    transform->rotation[2] = 0;
}
CLEAN_AS(func_02093678, EffectKinds_SetModelTransformTurned)

/* func_020936ac: an emitter of kind 0x24 set up, its axis up and forward. */
void EffectKinds_SetUpKind24(ParticleEmitter *emitter)
{
    func_02094d48(emitter, NULL, &data_020d17d4);
}
CLEAN_AS(func_020936ac, EffectKinds_SetUpKind24)

/* func_020936bc: kind 0x23, one-shot set 0x6f on ground attribute 0x13, else 0x6e. */
int EffectKinds_StartKind23(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    CollisionGround ground;
    int set;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    set = ground.attr == EFFECT_KINDS_GROUND_13 ? EFFECT_KINDS_SET_KIND_23_ON_13 : EFFECT_KINDS_SET_KIND_23;
    result = func_02094cf8(set, kind, position, angle, extra, data_020e27cc);
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_020936bc, EffectKinds_StartKind23)

/* func_02093704: kind 0x23's emitter set up, its axis up and forward. */
void EffectKinds_SetUpKind23(ParticleEmitter *emitter)
{
    func_02094d48(emitter, NULL, &data_020d17c8);
}
CLEAN_AS(func_02093704, EffectKinds_SetUpKind23)

/* func_02093714: kind 0x22, a one-shot set with the default word chosen by the ground at the
 * point. In a room: set 0x4b on attributes 9 and 3, nothing elsewhere. Outdoors: 0x4d on
 * attribute 0x16 or while rain falls, 0x4e on attribute 3 in the snow season, else 0x4c on
 * attribute 0x13 and 0x4b elsewhere. */
int EffectKinds_StartKind22(void *kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    CollisionGround ground;
    int attr;
    int result;
    int set;

    CollisionGround_Init(&ground, position, 0, 0);
    attr = ground.attr;
    result = EFFECT_KINDS_NOT_STARTED;
    if (data_020e54a8 == 1) {
        if (attr == EFFECT_KINDS_GROUND_9 || attr == EFFECT_KINDS_GROUND_3) {
            result = func_02094cf8(EFFECT_KINDS_SET_KIND_22, (int) (intptr_t) kind, position, angle, extra, NULL);
        }
    } else {
        if (attr == EFFECT_KINDS_GROUND_16 || Sky_Falling() == SKY_FALLING_RAIN) {
            set = EFFECT_KINDS_SET_KIND_22_WET;
        } else if (attr == EFFECT_KINDS_GROUND_3 && SceneQuery_IsSnowSeason() != 0) {
            set = EFFECT_KINDS_SET_KIND_22_SNOW;
        } else if (attr == EFFECT_KINDS_GROUND_13) {
            set = EFFECT_KINDS_SET_KIND_22_ON_13;
        } else {
            set = EFFECT_KINDS_SET_KIND_22;
        }
        result = func_02094cf8(set, (int) (intptr_t) kind, position, angle, extra, NULL);
    }
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_02093714, EffectKinds_StartKind22)

/* func_020937d4: kind 0x21, kept set 0x73 at its own size. */
int EffectKinds_StartKind21(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_020937d4, EffectKinds_StartKind21)

/* func_020937f8: kind 0x1f, kept set 0x73 at 0.8 of its size. */
void EffectKinds_StartKind1f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e27e4);
}
CLEAN_AS(func_020937f8, EffectKinds_StartKind1f)

/* The instance's emitter placed (no offset, its own axis), its particles' base scale `scale`. */
static void effect_kinds_place_scaled(EffectKindsInstance *instance, fx32 scale)
{
    func_02094c38(instance, NULL, NULL);
    instance->emitter->base_scale = scale;
}

/* func_02093820: set 0x73's emitter placed at 0.8 of its size (kind 0x1f). */
void EffectKinds_PlaceScaled08(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0xccd);
}
CLEAN_AS(func_02093820, EffectKinds_PlaceScaled08)

/* func_0209383c: kind 0x1e, kept set 0x73 at 0.7 of its size. */
void EffectKinds_StartKind1e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e27ec);
}
CLEAN_AS(func_0209383c, EffectKinds_StartKind1e)

/* func_02093864: set 0x73's emitter placed at 0.7 of its size (kind 0x1e). */
void EffectKinds_PlaceScaled07(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0xb33);
}
CLEAN_AS(func_02093864, EffectKinds_PlaceScaled07)

/* func_02093880: kind 0x1d, kept set 0x73 at 0.6 of its size. The kind table's caller passes
 * a fifth argument (-1), which goes unused. */
int EffectKinds_StartKind1d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int unused)
{
    (void) unused;
    return func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e2854);
}
CLEAN_AS(func_02093880, EffectKinds_StartKind1d)

/* func_020938a8: set 0x73's emitter placed at 0.6 of its size (kind 0x1d). */
void EffectKinds_PlaceScaled06(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0x99a);
}
CLEAN_AS(func_020938a8, EffectKinds_PlaceScaled06)

/* func_020938c4: kind 0x1c, kept set 0x73 at half its size. */
void EffectKinds_StartKind1c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e28b4);
}
CLEAN_AS(func_020938c4, EffectKinds_StartKind1c)

/* func_020938ec: set 0x73's emitter placed at half its size (kind 0x1c). */
void EffectKinds_PlaceScaled05(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0x800);
}
CLEAN_AS(func_020938ec, EffectKinds_PlaceScaled05)

/* func_02093908: kinds 0x1b and 0x20, kept set 0x73 at 0.4 of its size. */
void EffectKinds_StartKind1b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e2844);
}
CLEAN_AS(func_02093908, EffectKinds_StartKind1b)

/* func_02093930: set 0x73's emitter placed at 0.4 of its size (kinds 0x1b and 0x20). */
void EffectKinds_PlaceScaled04(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0x666);
}
CLEAN_AS(func_02093930, EffectKinds_PlaceScaled04)

/* func_0209394c: kind 0x1a, kept set 0x73 at 0.3 of its size. */
void EffectKinds_StartKind1a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    func_02094b58(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e283c);
}
CLEAN_AS(func_0209394c, EffectKinds_StartKind1a)

/* func_02093974: set 0x73's emitter placed at 0.3 of its size (kind 0x1a). */
void EffectKinds_PlaceScaled03(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0x4cd);
}
CLEAN_AS(func_02093974, EffectKinds_PlaceScaled03)
