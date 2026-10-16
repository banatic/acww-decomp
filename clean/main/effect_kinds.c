/* The effects started by kind, and their emitters (effect_kinds.h). */
#include "effect_kinds.h"

#include "autoload_2/fx_math.h"
#include "clean.h"
#include "effect_places.h"
#include "effect_system.h"
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

/* The place being started (data_021d5658) filled: cleared, then the handle, the kind, the point,
 * the angle and the half-word 0x10 when given, and the frames. */
extern void func_02091494(EffectKindsPlace *place, int handle, int kind, const Vec3 *position, const s16 *angle,
                          const s16 *extra, int frames);
/* A place cleared (no handle, no kind). */
extern void func_020914dc(EffectKindsPlace *place);
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
    EffectPlaces_Place(instance, NULL, &data_020d1750);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_34, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02092ea4, EffectKinds_StartKind34)

/* func_02092ec8: kind 0x33, kept set 0x74, only while rain falls. */
int EffectKinds_StartKind33(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    if (Sky_Falling() == SKY_FALLING_RAIN) {
        return EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_33, kind, position, angle, extra, data_020e28d4);
    }
    return EFFECT_KINDS_NOT_STARTED;
}
CLEAN_AS(func_02092ec8, EffectKinds_StartKind33)

/* func_02092f00: kind 0x33's emitter moved with its place, its axis up and back. */
int EffectKinds_FollowKind33(EffectKindsInstance *instance)
{
    return EffectPlaces_Follow(instance, NULL, &data_020d1768);
}
CLEAN_AS(func_02092f00, EffectKinds_FollowKind33)

/* func_02092f10: kind 0x33's emitter placed, its axis up and back. */
void EffectKinds_PlaceKind33(EffectKindsInstance *instance)
{
    EffectPlaces_Place(instance, NULL, &data_020d1768);
}
CLEAN_AS(func_02092f10, EffectKinds_PlaceKind33)

/* func_02092f20: kind 0x32, one-shot set 0x63. */
void EffectKinds_StartKind32(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_32, kind, position, angle, extra, data_020e27a4);
}
CLEAN_AS(func_02092f20, EffectKinds_StartKind32)

/* func_02092f48: kind 0x32's first emitter set up at its place, its colour the sky's light
 * colour 3 instead of the tint. */
void EffectKinds_SetUpKind32(ParticleEmitter *emitter)
{
    EffectPlaces_SetUp(emitter);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_31, kind, position, angle, extra, data_020e27fc);
}
CLEAN_AS(func_02092ff8, EffectKinds_StartKind31)

/* func_02093020: kind 0x31's emitter moved with its place, its axis forward. */
void EffectKinds_FollowKind31(EffectKindsInstance *instance)
{
    Vec3 forward = {0, 0, EFFECT_KINDS_ONE};

    EffectPlaces_Follow(instance, NULL, &forward);
}
CLEAN_AS(func_02093020, EffectKinds_FollowKind31)

/* func_02093040: kind 0x31's emitter placed, its axis forward. */
void EffectKinds_PlaceKind31(EffectKindsInstance *instance)
{
    EffectPlaces_Place(instance, NULL, &data_020d1750);
}
CLEAN_AS(func_02093040, EffectKinds_PlaceKind31)

/* func_02093050: kind 0x30, kept set 0x79. */
void EffectKinds_StartKind30(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_30, kind, position, angle, extra, data_020e28a4);
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
    if (EffectSystem_StartSet(set, position, angle, data_020e27c8) == 0) {
        return EFFECT_KINDS_NOT_STARTED;
    }
    for (i = 0; i < 3; i++) {
        if (EffectSystem_StartSet(EFFECT_KINDS_SET_54, position, angle, &data_020e2904[i]) == 0) {
            return EFFECT_KINDS_NOT_STARTED;
        }
    }
    return 1;
}
CLEAN_AS(func_020930a0, EffectKinds_StartWithThree54)

/* func_0209310c: the third emitter of set 0x54 set up at its offset (data_020d1738). */
void EffectKinds_SetUp54C(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d1738, NULL);
}
CLEAN_AS(func_0209310c, EffectKinds_SetUp54C)

/* func_0209311c: the second emitter of set 0x54 set up at its offset (data_020d1720). */
void EffectKinds_SetUp54B(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d1720, NULL);
}
CLEAN_AS(func_0209311c, EffectKinds_SetUp54B)

/* func_0209312c: the first emitter of set 0x54 set up at its offset (data_020d1714). */
void EffectKinds_SetUp54A(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d1714, NULL);
}
CLEAN_AS(func_0209312c, EffectKinds_SetUp54A)

/* func_0209313c: kind 0x2d, one-shot set 0x76 then set 0x54 with the default word; 1 when
 * both started, else 3. */
int EffectKinds_StartKind2d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    int result = EFFECT_KINDS_NOT_STARTED;

    func_02091494(&data_021d5658, -1, kind, position, angle, extra, -1);
    if (EffectSystem_StartSet(EFFECT_KINDS_SET_KIND_2D, position, angle, data_020e27c8) != 0 &&
        EffectSystem_StartSet(EFFECT_KINDS_SET_54, position, angle, data_020e29fc) != 0) {
        result = 1;
    }
    return result;
}
CLEAN_AS(func_0209313c, EffectKinds_StartKind2d)

/* func_02093194: the emitter of sets 0x76-0x78 (kinds 0x2d-0x2f) set up, its axis mostly up. */
void EffectKinds_SetUpKind2d(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, NULL, &data_020d16fc);
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
        result = EffectPlaces_StartOneShot(set, kind, position, angle, extra, setups);
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
    EffectSystem_TintEmitter(emitter);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_26, kind, position, angle, extra, data_020e28c4);
}
CLEAN_AS(func_020934a4, EffectKinds_StartKind26)

/* Kind 0x26's particles that have come down: sets 0x71 on the ground, 0x71 and 0x72 at
 * height 0. */
static int effect_kinds_land_kind26(ParticleEmitter *emitter)
{
    return EffectKinds_LandParticles(emitter, EFFECT_KINDS_SET_KIND_26_LANDING, data_020e29dc, -1, NULL,
                                     EFFECT_KINDS_SET_KIND_26_LANDING, data_020e29dc, EFFECT_KINDS_SET_KIND_26_FLOOR,
                                     data_020e29dc);
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
    EffectPlaces_Place(instance, NULL, &data_020d1750);
}
CLEAN_AS(func_020935c4, EffectKinds_PlaceKind26)

/* func_020935d4: kind 0x25, kept set 0x5a (five emitters). */
void EffectKinds_StartKind25(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_25, kind, position, angle, extra, data_020e2a64);
}
CLEAN_AS(func_020935d4, EffectKinds_StartKind25)

/* func_020935fc: kind 0x25's emitters moved with their place; once it is given up, each of the
 * emitter's particles is made as old as its life (so it ends) and the answer is 0; else 1. */
int EffectKinds_FollowKind25(EffectKindsInstance *instance)
{
    ParticleLink *link;

    if (EffectPlaces_Follow(instance, NULL, NULL) != 0) {
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

    if (EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_24, kind, position, angle, extra, data_020e2964) < 3) {
        EffectKinds_StartModel(EFFECT_KINDS_MODEL_KIND_24, kind, position, angle, extra, func_02093678);
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
    EffectPlaces_SetUpAt(emitter, NULL, &data_020d17d4);
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
    result = EffectPlaces_StartOneShot(set, kind, position, angle, extra, data_020e27cc);
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_020936bc, EffectKinds_StartKind23)

/* func_02093704: kind 0x23's emitter set up, its axis up and forward. */
void EffectKinds_SetUpKind23(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, NULL, &data_020d17c8);
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
            result = EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_22, (int) (intptr_t) kind, position, angle, extra, NULL);
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
        result = EffectPlaces_StartOneShot(set, (int) (intptr_t) kind, position, angle, extra, NULL);
    }
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_02093714, EffectKinds_StartKind22)

/* func_020937d4: kind 0x21, kept set 0x73 at its own size. */
int EffectKinds_StartKind21(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_020937d4, EffectKinds_StartKind21)

/* func_020937f8: kind 0x1f, kept set 0x73 at 0.8 of its size. */
void EffectKinds_StartKind1f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e27e4);
}
CLEAN_AS(func_020937f8, EffectKinds_StartKind1f)

/* The instance's emitter placed (no offset, its own axis), its particles' base scale `scale`. */
static void effect_kinds_place_scaled(EffectKindsInstance *instance, fx32 scale)
{
    EffectPlaces_Place(instance, NULL, NULL);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e27ec);
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
    return EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e2854);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e28b4);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e2844);
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
    EffectPlaces_StartKept(EFFECT_KINDS_SET_SIZED, kind, position, angle, extra, data_020e283c);
}
CLEAN_AS(func_0209394c, EffectKinds_StartKind1a)

/* func_02093974: set 0x73's emitter placed at 0.3 of its size (kind 0x1a). */
void EffectKinds_PlaceScaled03(EffectKindsInstance *instance)
{
    effect_kinds_place_scaled(instance, 0x4cd);
}
CLEAN_AS(func_02093974, EffectKinds_PlaceScaled03)

/* --- Kinds 0x00-0x19, the models some of them start, and the particles that come down --- */

/* The set-up words of the kinds 0x00-0x19's sets. */
extern void *data_020e277c[];
extern void *data_020e2784[];
extern void *data_020e2788[];
extern void *data_020e279c[];
extern void *data_020e27bc[];
extern void *data_020e27c4[];
extern void *data_020e27dc[];
extern void *data_020e27f4[];
extern void *data_020e2804[];
extern void *data_020e280c[];
extern void *data_020e2814[];
extern void *data_020e2824[];
extern void *data_020e282c[];
extern void *data_020e2834[];
extern void *data_020e287c[];
extern void *data_020e2884[];
extern void *data_020e288c[];
extern void *data_020e289c[];
extern void *data_020e28ac[];
extern void *data_020e28bc[];
extern void *data_020e28cc[];
extern void *data_020e28e4[];
extern void *data_020e28ec[];
extern void *data_020e28f4[];
extern void *data_020e28fc[];
extern void *data_020e2910[];
extern void *data_020e291c[];
extern void *data_020e2928[];
extern void *data_020e29ac[];

/* More emitters' offsets and axes. */
extern const Vec3 data_020d1708; /* (0.67, 0, 0) */
extern const Vec3 data_020d1780; /* (-1, 1, 0) */
extern const Vec3 data_020d17a4; /* (-0.2, 1, -0.4) */
extern const Vec3 data_020d181c; /* (-0.15, 1, -0.15) */

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* The models' transform set-up functions handed to func_02094840. */
extern void func_020939b8(void *transform);
extern void func_02093a18(void *transform);
extern void func_02093a78(void *transform);
extern void func_02094250(void *transform);
extern void func_02094884(void *transform);

/* The particle file's sets the kinds 0x00-0x19 start. */
#define EFFECT_KINDS_SET_WITH_MODEL 0x4a      /* kinds 0x0b, 0x16, 0x17 and 0x19 */
#define EFFECT_KINDS_SET_WITH_MODEL_KEPT 0x45 /* their kept set */
#define EFFECT_KINDS_SET_KIND_15 0x49
#define EFFECT_KINDS_SET_KIND_14 0x48
#define EFFECT_KINDS_SET_KIND_13 0x47
#define EFFECT_KINDS_SET_75 0x75 /* the kept set of kinds 0x13-0x15 */
#define EFFECT_KINDS_SET_KIND_12 0x46
#define EFFECT_KINDS_SET_5E 0x5e /* the kept set of kinds 0x0c, 0x0d, 0x10 and 0x12 */
#define EFFECT_KINDS_SET_5F 0x5f /* started where sets 0x75, 0x5e and 0x3c's particles land */
#define EFFECT_KINDS_SET_KIND_11 0x3c
#define EFFECT_KINDS_SET_KIND_10 0x3b
#define EFFECT_KINDS_SET_KIND_0F 0x3a
#define EFFECT_KINDS_SET_KIND_0E 0x39
#define EFFECT_KINDS_SET_KIND_0D 0x38
#define EFFECT_KINDS_SET_KIND_0C 0x37
#define EFFECT_KINDS_SET_KIND_0A_RAIN 0x36
#define EFFECT_KINDS_SET_KIND_0A_SNOW 0x35
#define EFFECT_KINDS_SET_KIND_0A_ON_13 0x34
#define EFFECT_KINDS_SET_KIND_0A 0x33
#define EFFECT_KINDS_SET_KIND_09_ON_13 0x32
#define EFFECT_KINDS_SET_KIND_09 0x31
#define EFFECT_KINDS_SET_KIND_08_ON_13 0x30
#define EFFECT_KINDS_SET_KIND_08 0x2f
#define EFFECT_KINDS_SET_KIND_07_ON_13 0x2e
#define EFFECT_KINDS_SET_KIND_07 0x2c
#define EFFECT_KINDS_SET_KIND_06_ON_13 0x2d
#define EFFECT_KINDS_SET_KIND_06 0x2b
#define EFFECT_KINDS_SET_KIND_03 0x2a
#define EFFECT_KINDS_SET_KIND_02 0x29
#define EFFECT_KINDS_SET_KIND_01_WET 0x1b
#define EFFECT_KINDS_SET_KIND_01_SNOW 0x1c
#define EFFECT_KINDS_SET_KIND_01_ON_13 0x1a
#define EFFECT_KINDS_SET_KIND_01 0x19
#define EFFECT_KINDS_SET_KIND_00_WET 0x21
#define EFFECT_KINDS_SET_KIND_00_RAIN 0x20
#define EFFECT_KINDS_SET_KIND_00_SNOW 0x18
#define EFFECT_KINDS_SET_KIND_00_ON_13 0x17
#define EFFECT_KINDS_SET_KIND_00 0x02
#define EFFECT_KINDS_SET_LANDED_1F 0x1f /* where the wet kinds' particles land on the ground */
#define EFFECT_KINDS_SET_LANDED_1E 0x1e
#define EFFECT_KINDS_SET_LANDED_1D 0x1d

/* The model kinds 0x0b, 0x16, 0x17 and 0x19 start with their particles. */
#define EFFECT_KINDS_MODEL_WITH_SET 2

/* The kind func_0209493c and func_02094a4c start their sets with. */
#define EFFECT_KINDS_KIND_LANDED 0x64

/* What a start function answers when its kept set started: the kind's caller (func_02091358)
 * uses up a handle without handing it out. */
#define EFFECT_KINDS_KEPT_STARTED 2

/* The handle the next kept set gets: the half-word at 0x39c in data_021d52d8, after the place
 * being started. */
#define EFFECT_KINDS_NEXT_HANDLE 0x39c

static int effect_kinds_next_handle(void)
{
    return *(const u16 *) (const void *) ((const u8 *) data_021d52d8 + EFFECT_KINDS_NEXT_HANDLE);
}

/* One-shot set `set` started; when it started, the place filled again with the next handle and
 * kept set `kept_set` started there, 2 when that started; else 3. The place is cleared after. */
static int effect_kinds_start_with_kept(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set,
                                        void *const *setups, int kept_set, void *const *kept_setups)
{
    int result = EFFECT_KINDS_NOT_STARTED;

    if (EffectPlaces_StartOneShot(set, kind, position, angle, extra, setups) < EFFECT_KINDS_NOT_STARTED) {
        func_02091494(&data_021d5658, effect_kinds_next_handle(), kind, position, angle, extra, -1);
        if (EffectSystem_StartKeptSet(kept_set, position, angle, kept_setups) != 0) {
            result = EFFECT_KINDS_KEPT_STARTED;
        }
    }
    func_020914dc(&data_021d5658);
    return result;
}

/* One-shot set `set_on_13` where the ground's attribute is 0x13, else `set`. */
static int effect_kinds_start_by_ground(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set_on_13,
                                        int set, void *const *setups)
{
    CollisionGround ground;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    result = EffectPlaces_StartOneShot(ground.attr == EFFECT_KINDS_GROUND_13 ? set_on_13 : set, kind, position, angle, extra,
                                       setups);
    CollisionGround_Destroy(&ground);
    return result;
}

/* The emitter's axis: `v` cut to 16 bits. */
static void effect_kinds_set_axis(ParticleEmitter *emitter, const Vec3 *v)
{
    emitter->axis.x = (fx16) v->x;
    emitter->axis.y = (fx16) v->y;
    emitter->axis.z = (fx16) v->z;
}

/* The ground at `at` looked at; where it has unk_30, the emitter's axis is the ground's normal
 * (0x24) once normalized, when it is not zero. The ground is left to the caller to release. */
static void effect_kinds_axis_from_ground(ParticleEmitter *emitter, CollisionGround *ground, const Vec3 *at)
{
    CollisionGround_Init(ground, at, 0, 0);
    if (ground->unk_30 != 0) {
        Vec3 normal = ground->normal;

        if (Vec_NormalizeNonZero(&normal) != 0) {
            effect_kinds_set_axis(emitter, &normal);
        }
    }
}

/* func_02093990: kind 0x19, the set and model of kind 0x0b at their largest: set 0x4a's
 * emitter at 1.8 of its size, model 2 at 1.3, and kept set 0x45's emitter with a speed of 0.75
 * along its axis. */
int EffectKinds_StartKind19(int kind, Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectKinds_StartWithModel(kind, position, angle, extra, data_020e28fc, data_020e279c, func_020939b8);
}
CLEAN_AS(func_02093990, EffectKinds_StartKind19)

/* func_020939b8: kind 0x19's model at the place being started, at 1.3 of its size. */
void EffectKinds_SetModelTransformKind19(EffectKindsModelTransform *transform)
{
    EffectKinds_SetModelTransformScaled(transform, 0x14cd);
}
CLEAN_AS(func_020939b8, EffectKinds_SetModelTransformKind19)

/* func_020939c8: kind 0x19's set 0x4a emitter set up at 1.8 of its size. */
void EffectKinds_SetUpKind19(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x1ccd);
}
CLEAN_AS(func_020939c8, EffectKinds_SetUpKind19)

/* func_020939d8: kind 0x19's kept emitter placed, its speed along its axis 0.75. */
void EffectKinds_PlaceKind19(EffectKindsInstance *instance)
{
    EffectPlaces_PlaceDefault(instance);
    instance->emitter->axis_speed = 0xc00;
}
CLEAN_AS(func_020939d8, EffectKinds_PlaceKind19)

/* func_020939f0: kind 0x17, as kind 0x19 with set 0x4a's emitter at 1.3 of its size, the model
 * at 1.1 and the kept emitter's speed along its axis 0.6. */
int EffectKinds_StartKind17(int kind, Vec3 *position, const s16 *angle, const s16 *extra)
{
    return EffectKinds_StartWithModel(kind, position, angle, extra, data_020e282c, data_020e27c4, func_02093a18);
}
CLEAN_AS(func_020939f0, EffectKinds_StartKind17)

/* func_02093a18: kind 0x17's model at the place being started, at 1.1 of its size. */
void EffectKinds_SetModelTransformKind17(EffectKindsModelTransform *transform)
{
    EffectKinds_SetModelTransformScaled(transform, 0x119a);
}
CLEAN_AS(func_02093a18, EffectKinds_SetModelTransformKind17)

/* func_02093a28: kind 0x17's set 0x4a emitter set up at 1.3 of its size. */
void EffectKinds_SetUpKind17(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x14cd);
}
CLEAN_AS(func_02093a28, EffectKinds_SetUpKind17)

/* func_02093a38: kind 0x17's kept emitter placed, its speed along its axis 0.6. */
void EffectKinds_PlaceKind17(EffectKindsInstance *instance)
{
    EffectPlaces_PlaceDefault(instance);
    instance->emitter->axis_speed = 0x99a;
}
CLEAN_AS(func_02093a38, EffectKinds_PlaceKind17)

/* func_02093a50: kind 0x16, as kind 0x19 with set 0x4a's emitter at 1.1 of its size, the model
 * at 0.8 and the kept emitter's speed along its axis 0.5. */
void EffectKinds_StartKind16(int kind, Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the start's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectKinds_StartWithModel(kind, position, angle, extra, data_020e287c, data_020e2784, func_02093a78);
}
CLEAN_AS(func_02093a50, EffectKinds_StartKind16)

/* func_02093a78: kind 0x16's model at the place being started, at 0.8 of its size. */
void EffectKinds_SetModelTransformKind16(EffectKindsModelTransform *transform)
{
    EffectKinds_SetModelTransformScaled(transform, 0xccd);
}
CLEAN_AS(func_02093a78, EffectKinds_SetModelTransformKind16)

/* func_02093a88: kind 0x16's set 0x4a emitter set up at 1.1 of its size. */
void EffectKinds_SetUpKind16(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x119a);
}
CLEAN_AS(func_02093a88, EffectKinds_SetUpKind16)

/* func_02093a98: kind 0x16's kept emitter placed, its speed along its axis 0.5. */
void EffectKinds_PlaceKind16(EffectKindsInstance *instance)
{
    EffectPlaces_PlaceDefault(instance);
    instance->emitter->axis_speed = 0x800;
}
CLEAN_AS(func_02093a98, EffectKinds_PlaceKind16)

/* func_02093ab0: kind 0x15, one-shot set 0x49 (its emitters at 2, 2 and 1.6 of their size),
 * then kept set 0x75. */
int EffectKinds_StartKind15(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_15, data_020e2928,
                                        EFFECT_KINDS_SET_75, data_020e2824);
}
CLEAN_AS(func_02093ab0, EffectKinds_StartKind15)

/* func_02093b28: kind 0x15's third emitter set up at 1.6 of its size. */
void EffectKinds_SetUpKind15Third(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x199a);
}
CLEAN_AS(func_02093b28, EffectKinds_SetUpKind15Third)

/* func_02093b38: kind 0x15's first two emitters set up at twice their size. */
void EffectKinds_SetUpKind15(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x2000);
}
CLEAN_AS(func_02093b38, EffectKinds_SetUpKind15)

/* func_02093b48: kinds 0x14 and 0x18, one-shot set 0x48 (its emitters at 1.5, 1.5 and 1.2 of
 * their size), then kept set 0x75. */
int EffectKinds_StartKind14(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_14, data_020e291c,
                                        EFFECT_KINDS_SET_75, data_020e28bc);
}
CLEAN_AS(func_02093b48, EffectKinds_StartKind14)

/* func_02093bc0: kept set 0x75's emitter placed (kinds 0x13-0x15), its particles at 1.2 of
 * their size. */
void EffectKinds_PlaceSet75(EffectKindsInstance *instance)
{
    EffectPlaces_PlaceDefault(instance);
    instance->emitter->base_scale = 0x1333;
}
CLEAN_AS(func_02093bc0, EffectKinds_PlaceSet75)

/* func_02093bd8: kind 0x14's third emitter set up at 1.2 of its size. */
void EffectKinds_SetUpKind14Third(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x1333);
}
CLEAN_AS(func_02093bd8, EffectKinds_SetUpKind14Third)

/* func_02093be8: kind 0x14's first two emitters set up at 1.5 of their size. */
void EffectKinds_SetUpKind14(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x1800);
}
CLEAN_AS(func_02093be8, EffectKinds_SetUpKind14)

/* func_02093bf8: kind 0x13, one-shot set 0x47 (its first emitter at 1.8 of its size), then kept
 * set 0x75. */
int EffectKinds_StartKind13(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_13, data_020e28ac,
                                        EFFECT_KINDS_SET_75, data_020e2884);
}
CLEAN_AS(func_02093bf8, EffectKinds_StartKind13)

/* func_02093c70: kept set 0x75's emitter each frame (EffectKinds_FollowParticles), set 0x5f
 * started where its particles land on the ground. */
void EffectKinds_FollowSet75(EffectKindsInstance *instance)
{
    /* QUIRK: declared without a result; in the ROM the follow's result is still in r0 when it
     * returns. */
    EffectKinds_FollowParticles(instance, EFFECT_KINDS_SET_5F, data_020e29dc, -1, NULL, -1, NULL, -1, NULL);
}
CLEAN_AS(func_02093c70, EffectKinds_FollowSet75)

/* func_02093c94: kind 0x13's second emitter set up (func_02094ef4). */
void EffectKinds_SetUpKind13Second(ParticleEmitter *emitter)
{
    EffectPlaces_SetUp(emitter);
}
CLEAN_AS(func_02093c94, EffectKinds_SetUpKind13Second)

/* func_02093c9c: kind 0x13's first emitter set up at 1.8 of its size. */
void EffectKinds_SetUpKind13(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpScaled(emitter, 0x1ccd);
}
CLEAN_AS(func_02093c9c, EffectKinds_SetUpKind13)

/* func_02093cac: kind 0x12, one-shot set 0x46 with the default words, then kept set 0x5e. */
int EffectKinds_StartKind12(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_12, NULL, EFFECT_KINDS_SET_5E,
                                        data_020e288c);
}
CLEAN_AS(func_02093cac, EffectKinds_StartKind12)

/* func_02093d20: kind 0x11, kept set 0x3c (three emitters, the third followed by
 * EffectKinds_FollowKind11Third). */
void EffectKinds_StartKind11(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_11, kind, position, angle, extra, data_020e29ac);
}
CLEAN_AS(func_02093d20, EffectKinds_StartKind11)

/* Set 0x5f started where the emitter's particles land (EffectKinds_LandParticlesAtLimit). */
static int effect_kinds_land_5f(ParticleEmitter *emitter)
{
    return EffectKinds_LandParticlesAtLimit(emitter, EFFECT_KINDS_SET_5F, data_020e29dc, -1, NULL, -1, NULL, -1, NULL);
}

/* func_02093d48: kind 0x11's third emitter each frame. While its place is kept and has frames
 * left the emitter is moved there and its landed particles start set 0x5f; once not, it stops
 * emitting and lasts while it has particles that land. Whether it lasts; the place's entry is
 * cleared when not. */
int EffectKinds_FollowKind11Third(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8[instance->slot];
    int lasts = 0;

    if (place->handle != -1 && place->frames != 0) {
        effect_kinds_put(instance->emitter, &place->position);
        effect_kinds_land_5f(instance->emitter);
        if (place->frames > 0) {
            place->frames = (s16) (place->frames - 1);
        }
        lasts = 1;
    }
    if (!lasts) {
        instance->emitter->state |= EMITTER_NO_EMISSION;
        if (instance->emitter->particles.count > 0) {
            lasts = effect_kinds_land_5f(instance->emitter);
        }
    }
    if (!lasts) {
        func_020914dc(place);
    }
    return lasts;
}
CLEAN_AS(func_02093d48, EffectKinds_FollowKind11Third)

/* func_02093e14: kind 0x0e, kept set 0x39 (placed by EffectKinds_PlaceKind0e, followed by
 * EffectKinds_FollowKind0e). */
void EffectKinds_StartKind0e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartKept(EFFECT_KINDS_SET_KIND_0E, kind, position, angle, extra, data_020e280c);
}
CLEAN_AS(func_02093e14, EffectKinds_StartKind0e)

/* func_02093e3c: kind 0x0e's emitter each frame. While its place is kept and has frames left
 * the emitter is moved there, its axis the ground's normal where the ground has unk_30, and
 * the frames counted down. Whether it lasts; the place's entry is cleared when not. */
int EffectKinds_FollowKind0e(EffectKindsInstance *instance)
{
    EffectKindsPlace *place = &data_021d52d8[instance->slot];
    int lasts = 0;

    if (place->handle != -1 && place->frames != 0) {
        CollisionGround ground;
        Vec3 at;

        effect_kinds_put(instance->emitter, &place->position);
        at = place->position;
        effect_kinds_axis_from_ground(instance->emitter, &ground, &at);
        if (place->frames > 0) {
            place->frames = (s16) (place->frames - 1);
        }
        lasts = 1;
        CollisionGround_Destroy(&ground);
    }
    if (!lasts) {
        func_020914dc(place);
    }
    return lasts;
}
CLEAN_AS(func_02093e3c, EffectKinds_FollowKind0e)

/* func_02093f0c: kind 0x0e's emitter placed at the place being started and tinted, its axis
 * the ground's normal where the ground has unk_30; the place kept in the instance's entry. */
void EffectKinds_PlaceKind0e(EffectKindsInstance *instance)
{
    const EffectKindsPlace *place = &data_021d5658;
    u8 slot = instance->slot;
    CollisionGround ground;
    Vec3 at;

    effect_kinds_put(instance->emitter, &place->position);
    EffectSystem_TintEmitter(instance->emitter);
    at = place->position;
    effect_kinds_axis_from_ground(instance->emitter, &ground, &at);
    MI_CpuCopy8(place, &data_021d52d8[slot], sizeof(EffectKindsPlace));
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_02093f0c, EffectKinds_PlaceKind0e)

/* func_02093fc4: kind 0x10, one-shot set 0x3b with the default words, then kept set 0x5e. */
int EffectKinds_StartKind10(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_10, NULL, EFFECT_KINDS_SET_5E,
                                        data_020e28e4);
}
CLEAN_AS(func_02093fc4, EffectKinds_StartKind10)

/* func_02094038: kind 0x0f, one-shot set 0x3a with the default words. */
void EffectKinds_StartKind0f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_0F, kind, position, angle, extra, NULL);
}
CLEAN_AS(func_02094038, EffectKinds_StartKind0f)

/* func_0209405c: kind 0x0d, one-shot set 0x38 with the default words, then kept set 0x5e. */
int EffectKinds_StartKind0d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_0D, NULL, EFFECT_KINDS_SET_5E,
                                        data_020e2804);
}
CLEAN_AS(func_0209405c, EffectKinds_StartKind0d)

/* func_020940d0: kind 0x0c, one-shot set 0x37 with the default words, then kept set 0x5e. */
int EffectKinds_StartKind0c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_with_kept(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_0C, NULL, EFFECT_KINDS_SET_5E,
                                        data_020e28f4);
}
CLEAN_AS(func_020940d0, EffectKinds_StartKind0c)

/* func_02094144: kept set 0x5e's emitter each frame (EffectKinds_FollowParticles), set 0x5f
 * started where its particles land on the ground. */
void EffectKinds_FollowSet5e(EffectKindsInstance *instance)
{
    /* QUIRK: declared without a result; in the ROM the follow's result is still in r0 when it
     * returns. */
    EffectKinds_FollowParticles(instance, EFFECT_KINDS_SET_5F, data_020e29dc, -1, NULL, -1, NULL, -1, NULL);
}
CLEAN_AS(func_02094144, EffectKinds_FollowSet5e)

/* func_02094168: kind 0x0b, set 0x4a with the default words, model 2 at its size and kept set
 * 0x45 (EffectKinds_StartWithModel). */
void EffectKinds_StartKind0b(unsigned int kind, Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the start's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectKinds_StartWithModel((int) kind, position, angle, extra, data_020e2834, NULL, func_02094250);
}
CLEAN_AS(func_02094168, EffectKinds_StartKind0b)

/* func_0209418c: where the ground at `position` has unk_30, the caller's point is moved to the
 * ground's limit (its Y written); then one-shot set 0x4a with `setups`, and when it started,
 * model 2 (`model_setup` setting its transform up) and kept set 0x45 with `kept_setups` at the
 * place filled again with the next handle: 2 when that started, else 3. The place being
 * started is cleared and the ground released after. */
int EffectKinds_StartWithModel(int kind, Vec3 *position, const s16 *angle, const s16 *extra, void *const *kept_setups,
                               void *const *setups, void (*model_setup)(void *transform))
{
    CollisionGround ground;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    result = EFFECT_KINDS_NOT_STARTED;
    if (ground.unk_30 != 0) {
        /* QUIRK: the point handed in by the kind's caller is changed. */
        position->y = ground.limit;
    }
    if (EffectPlaces_StartOneShot(EFFECT_KINDS_SET_WITH_MODEL, kind, position, angle, extra, setups) <
        EFFECT_KINDS_NOT_STARTED) {
        EffectKinds_StartModel(EFFECT_KINDS_MODEL_WITH_SET, kind, position, angle, extra, model_setup);
        func_02091494(&data_021d5658, effect_kinds_next_handle(), kind, position, angle, extra, -1);
        if (EffectSystem_StartKeptSet(EFFECT_KINDS_SET_WITH_MODEL_KEPT, position, angle, kept_setups) != 0) {
            result = EFFECT_KINDS_KEPT_STARTED;
        }
    }
    func_020914dc(&data_021d5658);
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_0209418c, EffectKinds_StartWithModel)

/* func_02094228: kept set 0x45's emitter each frame (EffectKinds_FollowParticles): where its
 * particles land, sets 0x1f and 0x1e on the ground, 0x1e at height 0. */
void EffectKinds_FollowSet45(EffectKindsInstance *instance)
{
    /* QUIRK: declared without a result; in the ROM the follow's result is still in r0 when it
     * returns. */
    EffectKinds_FollowParticles(instance, EFFECT_KINDS_SET_LANDED_1F, data_020e29dc, EFFECT_KINDS_SET_LANDED_1E, data_020e29dc,
                                EFFECT_KINDS_SET_LANDED_1E, data_020e29dc, -1, NULL);
}
CLEAN_AS(func_02094228, EffectKinds_FollowSet45)

/* func_02094250: kind 0x0b's model at the place being started, at its size. */
void EffectKinds_SetModelTransformKind0b(EffectKindsModelTransform *transform)
{
    EffectKinds_SetModelTransformScaled(transform, EFFECT_KINDS_ONE);
}
CLEAN_AS(func_02094250, EffectKinds_SetModelTransformKind0b)

/* The model at the place being started, scaled by `scale` on each axis and not turned. */
static void effect_kinds_set_model_transform(EffectKindsModelTransform *transform, fx32 scale)
{
    const EffectKindsPlace *place = &data_021d5658;

    transform->position.x = place->position.x;
    transform->position.y = place->position.y;
    transform->position.z = place->position.z;
    transform->scale.x = scale;
    transform->scale.y = scale;
    transform->scale.z = scale;
    transform->rotation[0] = 0;
    transform->rotation[1] = 0;
    transform->rotation[2] = 0;
}

/* func_02094260: a model at the place being started, scaled by `scale` on each axis and not
 * turned. */
void EffectKinds_SetModelTransformScaled(EffectKindsModelTransform *transform, u32 scale)
{
    effect_kinds_set_model_transform(transform, (fx32) scale);
}
CLEAN_AS(func_02094260, EffectKinds_SetModelTransformScaled)

/* func_02094294: kind 0x0a. While rain falls, kept set 0x36; on ground attribute 3 in the snow
 * season, kept set 0x35; else one-shot set 0x34 on attribute 0x13 and 0x33 elsewhere. A kept
 * set answers 2 when it started, else 3. */
int EffectKinds_StartKind0a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    CollisionGround ground;
    int attr;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    attr = ground.attr;
    result = EFFECT_KINDS_NOT_STARTED;
    /* QUIRK: neither kept start clears the place being started afterwards, as the others do;
     * the one in the snow leaves out the half-word 0x10 (`extra`). */
    if (Sky_Falling() == SKY_FALLING_RAIN) {
        func_02091494(&data_021d5658, effect_kinds_next_handle(), kind, position, angle, extra, -1);
        if (EffectSystem_StartKeptSet(EFFECT_KINDS_SET_KIND_0A_RAIN, position, angle, data_020e289c) != 0) {
            result = EFFECT_KINDS_KEPT_STARTED;
        }
    } else if (SceneQuery_IsSnowSeason() != 0 && attr == EFFECT_KINDS_GROUND_3) {
        func_02091494(&data_021d5658, effect_kinds_next_handle(), kind, position, angle, NULL, -1);
        if (EffectSystem_StartKeptSet(EFFECT_KINDS_SET_KIND_0A_SNOW, position, angle, data_020e28ec) != 0) {
            result = EFFECT_KINDS_KEPT_STARTED;
        }
    } else {
        result = EffectPlaces_StartOneShot(attr == EFFECT_KINDS_GROUND_13 ? EFFECT_KINDS_SET_KIND_0A_ON_13
                                                                          : EFFECT_KINDS_SET_KIND_0A,
                                           kind, position, angle, extra, NULL);
    }
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_02094294, EffectKinds_StartKind0a)

/* func_02094364: kind 0x09, one-shot set 0x32 on ground attribute 0x13, else 0x31. */
int EffectKinds_StartKind09(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_by_ground(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_09_ON_13, EFFECT_KINDS_SET_KIND_09,
                                        data_020e2910);
}
CLEAN_AS(func_02094364, EffectKinds_StartKind09)

/* func_020943ac: kind 0x09's emitters set up at their offset (data_020d1708), their axis up and
 * to the side (data_020d1780). */
void EffectKinds_SetUpKind09(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, &data_020d1708, &data_020d1780);
}
CLEAN_AS(func_020943ac, EffectKinds_SetUpKind09)

/* func_020943c0: kind 0x08, one-shot set 0x30 on ground attribute 0x13, else 0x2f, with the
 * default words. */
int EffectKinds_StartKind08(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_by_ground(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_08_ON_13, EFFECT_KINDS_SET_KIND_08,
                                        NULL);
}
CLEAN_AS(func_020943c0, EffectKinds_StartKind08)

/* func_02094404: kind 0x07, one-shot set 0x2e on ground attribute 0x13, else 0x2c. */
int EffectKinds_StartKind07(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_by_ground(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_07_ON_13, EFFECT_KINDS_SET_KIND_07,
                                        data_020e28cc);
}
CLEAN_AS(func_02094404, EffectKinds_StartKind07)

/* func_0209444c: kind 0x07's second emitter set up, its axis mostly up (data_020d17a4). */
void EffectKinds_SetUpKind07Second(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, NULL, &data_020d17a4);
}
CLEAN_AS(func_0209444c, EffectKinds_SetUpKind07Second)

/* func_0209445c: kind 0x07's first emitter set up, its axis mostly up (data_020d181c). */
void EffectKinds_SetUpKind07First(ParticleEmitter *emitter)
{
    EffectPlaces_SetUpAt(emitter, NULL, &data_020d181c);
}
CLEAN_AS(func_0209445c, EffectKinds_SetUpKind07First)

/* func_0209446c: kind 0x06, one-shot set 0x2d on ground attribute 0x13, else 0x2b, with the
 * default words. */
int EffectKinds_StartKind06(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    return effect_kinds_start_by_ground(kind, position, angle, extra, EFFECT_KINDS_SET_KIND_06_ON_13, EFFECT_KINDS_SET_KIND_06,
                                        NULL);
}
CLEAN_AS(func_0209446c, EffectKinds_StartKind06)

/* func_020944b0: kinds 0x03-0x05, one-shot set 0x2a. */
void EffectKinds_StartKind03(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_03, kind, position, angle, extra, data_020e2814);
}
CLEAN_AS(func_020944b0, EffectKinds_StartKind03)

/* func_020944d8: kind 0x02, one-shot set 0x29 (set up by EffectKinds_SetUpKind02). */
void EffectKinds_StartKind02(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    /* QUIRK: declared without a result; in the ROM the set's result is still in r0 when it
     * returns, and the kind table's caller (func_02091358) reads it as the kind's. */
    EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_02, kind, position, angle, extra, data_020e277c);
}
CLEAN_AS(func_020944d8, EffectKinds_StartKind02)

/* func_02094500: kind 0x02's emitter set up at the place being started, its particles stopped
 * 0.2 above it, its axis forward tilted up by an eighth of a turn and turned to face behind the
 * place's angle, and tinted. */
void EffectKinds_SetUpKind02(ParticleEmitter *emitter)
{
    const EffectKindsPlace *place = &data_021d5658;
    int behind = (s16) (u16) ((u32) (u16) place->angle + 0x8000);
    Vec3 axis = {0, 0, EFFECT_KINDS_ONE};

    effect_kinds_put(emitter, &place->position);
    emitter->collision_y = effect_kinds_add(place->position.y, 0x333);
    Vec_RotateX(&axis, -0x2000);
    Vec_RotateY(&axis, behind);
    effect_kinds_set_axis(emitter, &axis);
    EffectSystem_TintEmitter(emitter);
}
CLEAN_AS(func_02094500, EffectKinds_SetUpKind02)

/* func_0209458c: kind 0x01, chosen by the ground at the point. In a room: one-shot set 0x19 on
 * attributes 9 and 3, nothing elsewhere. Outdoors: kept set 0x1b on attribute 0x16 or while
 * rain falls, kept set 0x1c on attribute 3 in the snow season, else one-shot set 0x1a on
 * attribute 0x13 and 0x19 elsewhere. A kept set answers 2 when it started, else 3. */
int EffectKinds_StartKind01(int kind, const Vec3 *position, const s16 *angle, const s16 *extra)
{
    CollisionGround ground;
    int attr;
    int result;

    CollisionGround_Init(&ground, position, 0, 0);
    attr = ground.attr;
    result = EFFECT_KINDS_NOT_STARTED;
    if (data_020e54a8 == 1) {
        if (attr == EFFECT_KINDS_GROUND_9 || attr == EFFECT_KINDS_GROUND_3) {
            result = EffectPlaces_StartOneShot(EFFECT_KINDS_SET_KIND_01, kind, position, angle, extra, data_020e27bc);
        }
    } else if (attr == EFFECT_KINDS_GROUND_16 || Sky_Falling() == SKY_FALLING_RAIN) {
        /* QUIRK: the kept starts leave out the half-word 0x10 (`extra`) and do not clear the
         * place being started afterwards. */
        func_02091494(&data_021d5658, effect_kinds_next_handle(), kind, position, angle, NULL, -1);
        if (EffectSystem_StartKeptSet(EFFECT_KINDS_SET_KIND_01_WET, position, angle, data_020e27dc) != 0) {
            result = EFFECT_KINDS_KEPT_STARTED;
        }
    } else if (attr == EFFECT_KINDS_GROUND_3 && SceneQuery_IsSnowSeason() != 0) {
        func_02091494(&data_021d5658, effect_kinds_next_handle(), kind, position, angle, NULL, -1);
        if (EffectSystem_StartKeptSet(EFFECT_KINDS_SET_KIND_01_SNOW, position, angle, data_020e27f4) != 0) {
            result = EFFECT_KINDS_KEPT_STARTED;
        }
    } else {
        result = EffectPlaces_StartOneShot(attr == EFFECT_KINDS_GROUND_13 ? EFFECT_KINDS_SET_KIND_01_ON_13
                                                                          : EFFECT_KINDS_SET_KIND_01,
                                           kind, position, angle, extra, data_020e27bc);
    }
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_0209458c, EffectKinds_StartKind01)

/* func_0209469c: the kept emitter of kind 0x01 when wet and of kind 0x0a in the rain each frame
 * (EffectKinds_FollowParticles): where its particles land, sets 0x1f and 0x1e on the ground,
 * 0x1e at height 0. */
void EffectKinds_FollowWet(EffectKindsInstance *instance)
{
    /* QUIRK: declared without a result; in the ROM the follow's result is still in r0 when it
     * returns. */
    EffectKinds_FollowParticles(instance, EFFECT_KINDS_SET_LANDED_1F, data_020e29dc, EFFECT_KINDS_SET_LANDED_1E, data_020e29dc,
                                EFFECT_KINDS_SET_LANDED_1E, data_020e29dc, -1, NULL);
}
CLEAN_AS(func_0209469c, EffectKinds_FollowWet)

/* func_020946c4: the kept emitter of kinds 0x01 and 0x0a in the snow each frame
 * (EffectKinds_FollowParticles): where its particles land, sets 0x1f and 0x1d on the ground,
 * 0x1d at height 0. */
int EffectKinds_FollowSnow(EffectKindsInstance *instance)
{
    return EffectKinds_FollowParticles(instance, EFFECT_KINDS_SET_LANDED_1F, data_020e29dc, EFFECT_KINDS_SET_LANDED_1D,
                                       data_020e29dc, EFFECT_KINDS_SET_LANDED_1D, data_020e29dc, -1, NULL);
}
CLEAN_AS(func_020946c4, EffectKinds_FollowSnow)

/* func_020946ec: kind 0x01's kept emitter placed at the place being started and tinted, its
 * axis up and forward at an eighth of a turn, turned by the place's angle; the place kept in
 * the instance's entry. */
void EffectKinds_PlaceKind01(EffectKindsInstance *instance)
{
    const EffectKindsPlace *place = &data_021d5658;
    u8 slot = instance->slot;
    Vec3 axis = {0, 0xb50, 0xb50};

    effect_kinds_put(instance->emitter, &place->position);
    EffectSystem_TintEmitter(instance->emitter);
    Vec_RotateY(&axis, place->angle);
    effect_kinds_set_axis(instance->emitter, &axis);
    MI_CpuCopy8(place, &data_021d52d8[slot], sizeof(EffectKindsPlace));
}
CLEAN_AS(func_020946ec, EffectKinds_PlaceKind01)

/* func_02094780: kind 0x00, a one-shot set chosen by the ground at the point. In a room: set 2
 * on attributes 9 and 3, nothing elsewhere. Outdoors: 0x21 on attribute 0x16 and 0x20 while
 * rain falls (both with the default words of data_020e29dc, the caller's angle set to 0), 0x18
 * with the default words on attribute 3 in the snow season, 0x17 on attribute 0x13, else 2. */
int EffectKinds_StartKind00(int kind, const Vec3 *position, u16 *angle, const s16 *extra)
{
    CollisionGround ground;
    int attr;
    int result;
    int set;
    void *const *setups;

    CollisionGround_Init(&ground, position, 0, 0);
    attr = ground.attr;
    setups = data_020e2788;
    result = EFFECT_KINDS_NOT_STARTED;
    set = EFFECT_KINDS_SET_KIND_00;
    if (data_020e54a8 == 1) {
        if (attr == EFFECT_KINDS_GROUND_9 || attr == EFFECT_KINDS_GROUND_3) {
            result = EffectPlaces_StartOneShot(set, kind, position, (const s16 *) angle, extra, setups);
        }
    } else {
        if (attr == EFFECT_KINDS_GROUND_16 || Sky_Falling() == SKY_FALLING_RAIN) {
            set = attr == EFFECT_KINDS_GROUND_16 ? EFFECT_KINDS_SET_KIND_00_WET : EFFECT_KINDS_SET_KIND_00_RAIN;
            /* QUIRK: the angle handed in by the kind's caller is changed. */
            if (angle != NULL) {
                *angle = 0;
            }
            setups = data_020e29dc;
        } else if (attr == EFFECT_KINDS_GROUND_3) {
            if (SceneQuery_IsSnowSeason() != 0) {
                set = EFFECT_KINDS_SET_KIND_00_SNOW;
                setups = NULL;
            }
        } else if (attr == EFFECT_KINDS_GROUND_13) {
            set = EFFECT_KINDS_SET_KIND_00_ON_13;
        }
        result = EffectPlaces_StartOneShot(set, kind, position, (const s16 *) angle, extra, setups);
    }
    CollisionGround_Destroy(&ground);
    return result;
}
CLEAN_AS(func_02094780, EffectKinds_StartKind00)

/* func_02094840: model `model` started at the place being started, filled from the arguments
 * (no handle, for ever), `setup` setting its transform up (func_02094884 when NULL); 1. The
 * place is left filled for the setup to read. */
int EffectKinds_StartModel(int model, int kind, const Vec3 *position, const s16 *angle, const s16 *extra,
                           void (*setup)(void *transform))
{
    if (setup == NULL) {
        setup = func_02094884;
    }
    func_02091494(&data_021d5658, -1, kind, position, angle, extra, -1);
    EffectSystem_StartModel(model, setup);
    return 1;
}
CLEAN_AS(func_02094840, EffectKinds_StartModel)

/* func_02094884: a model at the place being started, at its size and not turned. */
void EffectKinds_SetModelTransform(EffectKindsModelTransform *transform)
{
    effect_kinds_set_model_transform(transform, EFFECT_KINDS_ONE);
}
CLEAN_AS(func_02094884, EffectKinds_SetModelTransform)

/* func_020948b8: a kept emitter each frame without moving it, while its place is kept. While
 * the place's frames are -1 it lasts, and once the emitter has particles they are set to 0;
 * at 0 it lasts while it has particles, those that land starting the given sets
 * (EffectKinds_LandParticlesAtLimit). Whether it lasts; the place's entry is cleared when
 * not. */
int EffectKinds_FollowParticles(EffectKindsInstance *instance, int ground_set, void *const *ground_setups, int ground_set2,
                                void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                                void *const *floor_setups2)
{
    EffectKindsPlace *place = &data_021d52d8[instance->slot];
    int lasts = 0;

    if (place->handle != -1) {
        if (place->frames == -1) {
            if (instance->emitter->particles.count > 0) {
                place->frames = 0;
            }
            lasts = 1;
        }
        /* QUIRK: any other count of frames than -1 and 0 gives the place up at once. */
        if (place->frames == 0) {
            lasts = EffectKinds_LandParticlesAtLimit(instance->emitter, ground_set, ground_setups, ground_set2, ground_setups2,
                                                     floor_set, floor_setups, floor_set2, floor_setups2);
        }
    }
    if (!lasts) {
        func_020914dc(place);
    }
    return lasts;
}
CLEAN_AS(func_020948b8, EffectKinds_FollowParticles)

/* For each of the emitter's particles at its point in the world (its position plus its
 * emitter's): where the ground there has unk_30 and the particle is not above its limit (as
 * CollisionGround_GetLimit gives it when `scaled`, else as it is kept), the ground sets start at
 * that height; elsewhere, where it is not above height 0, the floor
 * sets start at height 0. Each set (-1 for none) is a one-shot set of kind 0x64 with no angle,
 * and a particle that starts them is made as old as its life (so it ends). Whether the emitter
 * has particles. */
static int effect_kinds_land_particles(ParticleEmitter *emitter, int scaled, int ground_set, void *const *ground_setups,
                                       int ground_set2, void *const *ground_setups2, int floor_set, void *const *floor_setups,
                                       int floor_set2, void *const *floor_setups2)
{
    ParticleLink *link = emitter->particles.first;
    int any = 0;

    while (link != NULL) {
        Particle *particle = (Particle *) link;
        CollisionGround ground;
        Vec3 at;

        any = 1;
        at.x = effect_kinds_add(particle->position.x, particle->emitter_pos.x);
        at.y = effect_kinds_add(particle->position.y, particle->emitter_pos.y);
        at.z = effect_kinds_add(particle->position.z, particle->emitter_pos.z);
        CollisionGround_Init(&ground, &at, 0, 0);
        if (ground.unk_30 != 0) {
            fx32 top = scaled ? CollisionGround_GetLimit(&ground) : ground.limit;

            if (at.y <= top) {
                at.y = top;
                if (ground_set != -1) {
                    EffectPlaces_StartOneShot(ground_set, EFFECT_KINDS_KIND_LANDED, &at, NULL, NULL, ground_setups);
                }
                if (ground_set2 != -1) {
                    EffectPlaces_StartOneShot(ground_set2, EFFECT_KINDS_KIND_LANDED, &at, NULL, NULL, ground_setups2);
                }
                particle->age = particle->life;
            }
        } else if (at.y <= 0) {
            if (floor_set != -1) {
                at.y = 0;
                EffectPlaces_StartOneShot(floor_set, EFFECT_KINDS_KIND_LANDED, &at, NULL, NULL, floor_setups);
            }
            if (floor_set2 != -1) {
                at.y = 0;
                EffectPlaces_StartOneShot(floor_set2, EFFECT_KINDS_KIND_LANDED, &at, NULL, NULL, floor_setups2);
            }
            particle->age = particle->life;
        }
        link = link->next;
        CollisionGround_Destroy(&ground);
    }
    return any;
}

/* func_0209493c: the emitter's particles that have come down (effect_kinds_land_particles),
 * to the ground's limit as CollisionGround_GetLimit gives it where the ground has unk_30, else
 * to height 0. */
int EffectKinds_LandParticles(ParticleEmitter *emitter, int ground_set, void *const *ground_setups, int ground_set2,
                              void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                              void *const *floor_setups2)
{
    return effect_kinds_land_particles(emitter, 1, ground_set, ground_setups, ground_set2, ground_setups2, floor_set,
                                       floor_setups, floor_set2, floor_setups2);
}
CLEAN_AS(func_0209493c, EffectKinds_LandParticles)

/* func_02094a4c: as EffectKinds_LandParticles, with the ground's limit as it is kept (without
 * CollisionGround_GetLimit's scaling on attribute 0x16). */
int EffectKinds_LandParticlesAtLimit(ParticleEmitter *emitter, int ground_set, void *const *ground_setups, int ground_set2,
                                     void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                                     void *const *floor_setups2)
{
    return effect_kinds_land_particles(emitter, 0, ground_set, ground_setups, ground_set2, ground_setups2, floor_set,
                                       floor_setups, floor_set2, floor_setups2);
}
CLEAN_AS(func_02094a4c, EffectKinds_LandParticlesAtLimit)
