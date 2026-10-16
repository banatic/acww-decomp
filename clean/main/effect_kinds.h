/* The effects started by kind (func_020912d4 hands a kind below 0x66 to its entry in the table
 * at data_020e2c1c): each kind's start function, and the functions that set up and move the
 * particle emitters of the kinds 0x1a-0x34.
 *
 * A start function fills the place being started (data_021d5658, EffectKindsPlace: the point,
 * the angle and the kind) and starts a set of the particle file's emitters (a set number of the
 * table at data_020d0f88), giving each emitter its own entry of a list of set-up words:
 * - a one-shot set (func_02094cf8, result 1 when started) takes one word per emitter, the
 *   function that sets the new emitter up (by default func_02094ef4: at the place, tinted);
 * - a kept set (func_02094b58, result 0 when started, which makes the kind's caller hand out a
 *   handle) takes two words per emitter: the function that places the effect's emitter when it
 *   starts and the one that moves it with its place each frame (by default func_02094bc0 and
 *   func_02094bb4). The place is kept in the entry of data_021d52d8 the instance names; a
 *   follow function answers 0 once the place is given up or its frames have run out.
 * Any start function answers 3 when nothing started.
 *
 * Kinds 0x1a-0x21 are the same kept set 0x73 at different sizes; kinds 0x27-0x2c leave marks on
 * the ground (kind 0x28 is a scene object's footstep, footsteps.h) where its attribute is 0x13,
 * or 3 in the snow season. */
#ifndef CLEAN_MAIN_EFFECT_KINDS_H
#define CLEAN_MAIN_EFFECT_KINDS_H

#include "autoload_2/particle.h"
#include "autoload_2/vector.h"
#include "types.h"

/* A place an effect starts at or follows (0x1c bytes): data_021d52d8 holds 32 of them, the one
 * being started (data_021d5658) and, at 0x39c, the next handle. */
typedef struct EffectKindsPlace {
    Vec3 position; /* 0x00 */
    s16 angle;     /* 0x0c: about Y */
    s16 frames;    /* 0x0e: frames left to follow it, -1 for ever */
    s16 unk_10;    /* 0x10: 0x1000 unless the start function is given one */
    u8 unk_12[2];
    s32 handle; /* 0x14: -1 for a free entry */
    s16 kind;   /* 0x18: 0x66 for none */
    u8 unk_1a[2];
} EffectKindsPlace;

/* An effect's instance of one emitter of a kept set (made by func_02090ac4). */
typedef struct EffectKindsInstance {
    u8 unk_00[4];
    u8 slot; /* 0x04: its place's entry in data_021d52d8 */
    u8 unk_05[7];
    ParticleEmitter *emitter; /* 0x0c */
} EffectKindsInstance;

/* Where a model started by func_02094840 is drawn: its point, scale and angles. */
typedef struct EffectKindsModelTransform {
    u32 unk_00;
    Vec3 position;   /* 0x04 */
    Vec3 scale;      /* 0x10 */
    s16 rotation[3]; /* 0x1c: about X, Y and Z */
} EffectKindsModelTransform;

/* The kinds' start functions */
int EffectKinds_StartKind33(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind34(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind32(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind31(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind30(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind2f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind2e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartWithThree54(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set);
int EffectKinds_StartKind2d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind2c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind2b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind2a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind29(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartOnMarkGround(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int set,
                                  void *const *setups);
int EffectKinds_StartKind28(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind27(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind26(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind25(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind24(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind23(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind22(void *kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind21(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind1f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind1e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind1d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra, int unused);
void EffectKinds_StartKind1c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind1b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind1a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);

/* The emitters' set-up, place and follow functions */
void EffectKinds_PlaceKind35B(EffectKindsInstance *instance);
void EffectKinds_PlaceKind35A(EffectKindsInstance *instance);
void EffectKinds_PlaceWithSpeeds(EffectKindsInstance *instance, char interval, fx32 speed, fx32 axis_speed);
int EffectKinds_FollowKind33(EffectKindsInstance *instance);
void EffectKinds_PlaceKind33(EffectKindsInstance *instance);
void EffectKinds_SetUpKind32(ParticleEmitter *emitter);
void EffectKinds_FollowKind31(EffectKindsInstance *instance);
void EffectKinds_PlaceKind31(EffectKindsInstance *instance);
void EffectKinds_SetUp54C(ParticleEmitter *emitter);
void EffectKinds_SetUp54B(ParticleEmitter *emitter);
void EffectKinds_SetUp54A(ParticleEmitter *emitter);
void EffectKinds_SetUpKind2d(ParticleEmitter *emitter);
void EffectKinds_SetUpMark2cSecond(ParticleEmitter *emitter);
void EffectKinds_SetUpMark2cFirst(ParticleEmitter *emitter);
void EffectKinds_SetUpMark2bSecond(ParticleEmitter *emitter);
void EffectKinds_SetUpMark2bFirst(ParticleEmitter *emitter);
void EffectKinds_SetUpMark2a(ParticleEmitter *emitter);
void EffectKinds_SetUpMark29(ParticleEmitter *emitter);
void EffectKinds_SetUpMark(ParticleEmitter *emitter, const Vec3 *offset, int turn);
void EffectKinds_TurnFirstParticle(ParticleEmitter *emitter, int after);
void EffectKinds_PlaceKind26(EffectKindsInstance *instance);
int EffectKinds_FollowKind26(EffectKindsInstance *instance);
int EffectKinds_FollowKind25(EffectKindsInstance *instance);
void EffectKinds_SetModelTransformTurned(EffectKindsModelTransform *transform);
void EffectKinds_SetUpKind24(ParticleEmitter *emitter);
void EffectKinds_SetUpKind23(ParticleEmitter *emitter);
void EffectKinds_PlaceScaled08(EffectKindsInstance *instance);
void EffectKinds_PlaceScaled07(EffectKindsInstance *instance);
void EffectKinds_PlaceScaled06(EffectKindsInstance *instance);
void EffectKinds_PlaceScaled05(EffectKindsInstance *instance);
void EffectKinds_PlaceScaled04(EffectKindsInstance *instance);
void EffectKinds_PlaceScaled03(EffectKindsInstance *instance);

#endif
