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

/* Kinds 0x00-0x19. Several of them choose their set by the ground at the point (in a room, on
 * attributes 0x13, 3 in the snow season or 0x16, or while rain falls), some start a one-shot set
 * and then a kept one, answering 2 when the kept one started (the kind's caller then uses up a
 * handle without handing it out), and kinds 0x0b, 0x16, 0x17 and 0x19 start the same sets and
 * model 2 at different sizes. The kept emitters of several kinds start more sets where their
 * particles come down (EffectKinds_LandParticles). */
int EffectKinds_StartKind19(int kind, Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetModelTransformKind19(EffectKindsModelTransform *transform);
void EffectKinds_SetUpKind19(ParticleEmitter *emitter);
void EffectKinds_PlaceKind19(EffectKindsInstance *instance);
int EffectKinds_StartKind17(int kind, Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetModelTransformKind17(EffectKindsModelTransform *transform);
void EffectKinds_SetUpKind17(ParticleEmitter *emitter);
void EffectKinds_PlaceKind17(EffectKindsInstance *instance);
void EffectKinds_StartKind16(int kind, Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetModelTransformKind16(EffectKindsModelTransform *transform);
void EffectKinds_SetUpKind16(ParticleEmitter *emitter);
void EffectKinds_PlaceKind16(EffectKindsInstance *instance);
int EffectKinds_StartKind15(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetUpKind15Third(ParticleEmitter *emitter);
void EffectKinds_SetUpKind15(ParticleEmitter *emitter);
int EffectKinds_StartKind14(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_PlaceSet75(EffectKindsInstance *instance);
void EffectKinds_SetUpKind14Third(ParticleEmitter *emitter);
void EffectKinds_SetUpKind14(ParticleEmitter *emitter);
int EffectKinds_StartKind13(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowSet75(EffectKindsInstance *instance);
void EffectKinds_SetUpKind13Second(ParticleEmitter *emitter);
void EffectKinds_SetUpKind13(ParticleEmitter *emitter);
int EffectKinds_StartKind12(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind11(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind11Third(EffectKindsInstance *instance);
void EffectKinds_StartKind0e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind0e(EffectKindsInstance *instance);
void EffectKinds_PlaceKind0e(EffectKindsInstance *instance);
int EffectKinds_StartKind10(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind0f(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind0d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind0c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowSet5e(EffectKindsInstance *instance);
void EffectKinds_StartKind0b(unsigned int kind, Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartWithModel(int kind, Vec3 *position, const s16 *angle, const s16 *extra, void *const *kept_setups,
                               void *const *setups, void (*model_setup)(void *transform));
void EffectKinds_FollowSet45(EffectKindsInstance *instance);
void EffectKinds_SetModelTransformKind0b(EffectKindsModelTransform *transform);
void EffectKinds_SetModelTransformScaled(EffectKindsModelTransform *transform, u32 scale);
int EffectKinds_StartKind0a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind09(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetUpKind09(ParticleEmitter *emitter);
int EffectKinds_StartKind08(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind07(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetUpKind07Second(ParticleEmitter *emitter);
void EffectKinds_SetUpKind07First(ParticleEmitter *emitter);
int EffectKinds_StartKind06(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind03(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind02(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetUpKind02(ParticleEmitter *emitter);
int EffectKinds_StartKind01(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowWet(EffectKindsInstance *instance);
int EffectKinds_FollowSnow(EffectKindsInstance *instance);
void EffectKinds_PlaceKind01(EffectKindsInstance *instance);
int EffectKinds_StartKind00(int kind, const Vec3 *position, u16 *angle, const s16 *extra);
int EffectKinds_StartModel(int model, int kind, const Vec3 *position, const s16 *angle, const s16 *extra,
                           void (*setup)(void *transform));
void EffectKinds_SetModelTransform(EffectKindsModelTransform *transform);
int EffectKinds_FollowParticles(EffectKindsInstance *instance, int ground_set, void *const *ground_setups, int ground_set2,
                                void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                                void *const *floor_setups2);
int EffectKinds_LandParticles(ParticleEmitter *emitter, int ground_set, void *const *ground_setups, int ground_set2,
                              void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                              void *const *floor_setups2);
int EffectKinds_LandParticlesAtLimit(ParticleEmitter *emitter, int ground_set, void *const *ground_setups, int ground_set2,
                                     void *const *ground_setups2, int floor_set, void *const *floor_setups, int floor_set2,
                                     void *const *floor_setups2);

/* Kinds 0x35-0x4b. Kinds 0x35 and 0x36 follow their places from frames -181 counting up, their
 * emitters fading in and out over that time; kinds 0x37-0x39 choose their set by the ground at
 * the point; kinds 0x3e and 0x3f are sized by the half-word `extra`. */
void EffectKinds_StartKind4b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind4a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowKind4b(EffectKindsInstance *instance);
void EffectKinds_PlaceKind4b(EffectKindsInstance *instance);
void EffectKinds_StartKind49(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowKind49(EffectKindsInstance *instance);
void EffectKinds_PlaceKind49(EffectKindsInstance *instance);
void EffectKinds_StartKind48(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind47(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind46(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind45(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind44(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind43(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind42(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind41(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowKind41Third(EffectKindsInstance *instance);
void EffectKinds_FollowKind41Second(EffectKindsInstance *instance);
void EffectKinds_FollowKind41First(EffectKindsInstance *instance);
void EffectKinds_PlaceKind41Third(EffectKindsInstance *instance);
void EffectKinds_PlaceKind41Second(EffectKindsInstance *instance);
void EffectKinds_PlaceKind41First(EffectKindsInstance *instance);
void EffectKinds_StartKind40(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowKind40(EffectKindsInstance *instance);
void EffectKinds_PlaceKind40(EffectKindsInstance *instance);
int EffectKinds_StartKind3f(int kind, Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind3f(EffectKindsInstance *instance);
void EffectKinds_SetModelTransformKind3f(EffectKindsModelTransform *transform);
void EffectKinds_SetUpKind3f(ParticleEmitter *emitter);
void EffectKinds_PlaceKind3f(EffectKindsInstance *instance);
int EffectKinds_StartKind3e(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetUpKind3eLarge(ParticleEmitter *emitter);
void EffectKinds_SetUpKind3e(ParticleEmitter *emitter);
void EffectKinds_EndKind3d(int handle);
void EffectKinds_StartKind3d(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind3d(EffectKindsInstance *instance);
void EffectKinds_PlaceKind3d(EffectKindsInstance *instance);
void EffectKinds_StartKind3c(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_StartKind3b(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind3b(EffectKindsInstance *instance);
void EffectKinds_PlaceKind3b(EffectKindsInstance *instance);
void EffectKinds_StartKind3a(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind3a(EffectKindsInstance *instance);
void EffectKinds_PlaceKind3a(EffectKindsInstance *instance);
int EffectKinds_StartKind39(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_FollowKind39Snow(EffectKindsInstance *instance);
void EffectKinds_FollowKind39Wet(EffectKindsInstance *instance);
void EffectKinds_PlaceKind39(EffectKindsInstance *instance);
int EffectKinds_StartKind38(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_StartKind37(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
void EffectKinds_SetUpKind37(ParticleEmitter *emitter);
void EffectKinds_TurnFirstParticleKind37(ParticleEmitter *emitter, int after);
int EffectKinds_StartKind36(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind36(EffectKindsInstance *instance);
void EffectKinds_PlaceKind36(EffectKindsInstance *instance);
int EffectKinds_StartKind35(int kind, const Vec3 *position, const s16 *angle, const s16 *extra);
int EffectKinds_FollowKind35C(EffectKindsInstance *instance);
int EffectKinds_FollowKind35B(EffectKindsInstance *instance);
void EffectKinds_FollowKind35A(EffectKindsInstance *instance);
int EffectKinds_FollowKind35Ramp(EffectKindsInstance *instance, int interval, int in_rate, int out_rate, int speed,
                                 short speed_hold, short speed_in, short speed_out, int axis_speed, short axis_hold,
                                 short axis_in, short axis_out);
void EffectKinds_PlaceKind35C(EffectKindsInstance *instance);

#endif
