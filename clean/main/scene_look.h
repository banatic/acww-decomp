/* Where a scene object looks (class 0x020d8c64, obj_020d8c64.h: its member at 0x3b0): the
 * head turns by a yaw (left and right, from the object's angle at 0x8e) and a pitch (up and
 * down, from the object's word at 0x8c), each moved a step a frame towards its aim
 * (Approach_S16Wrapped) and held within a limit.
 *
 * A request (SceneLook_Request) names what to look at, the kind, with a priority: it is taken
 * unless the look is locked, the priority waiting is 4 (final) or the new one is lower. Each
 * frame (SceneLook_Update) the kind's handler from the table at data_021c1794 aims the head:
 * - 0, none: back to straight ahead;
 * - 1, the player (field actor 4), at its head point (func_020954c0);
 * - 2, an object at `target`, at its own look's head point;
 * - 3, the point `point`;
 * - 4, the field actor numbered `actor`, as kind 1;
 * - 5, the rest angles `pitch_rest` and `yaw_rest` (SceneLook_RequestAngles).
 * The aim is straight ahead when the target is beyond `range` (0 for any distance) or, with
 * `in_view_only`, outside the yaw limit; `on_target` is 1 once both angles are on an aim that
 * reached the target.
 *
 * The head point is the translation of joint 15's matrix of the object's model, read each
 * frame (SceneLook_ReadHead). */
#ifndef CLEAN_MAIN_SCENE_LOOK_H
#define CLEAN_MAIN_SCENE_LOOK_H

#include "autoload_2/matrix.h"
#include "autoload_2/vector.h"
#include "types.h"

/* The kinds. */
#define SCENE_LOOK_NONE 0
#define SCENE_LOOK_PLAYER 1
#define SCENE_LOOK_OBJECT 2
#define SCENE_LOOK_POINT 3
#define SCENE_LOOK_ACTOR 4
#define SCENE_LOOK_ANGLES 5
#define SCENE_LOOK_KINDS 6

/* A priority no request replaces. */
#define SCENE_LOOK_PRIORITY_FINAL 4

typedef struct SceneLook {
    u8 kind; /* 0x00 */
    u8 unk_01[3];
    u32 target;      /* 0x04: the object of kind 2 (its address) */
    Vec3 point;      /* 0x08: the point of kind 3 */
    s32 priority;    /* 0x14 */
    u8 locked;       /* 0x18: no request is taken and nothing is aimed */
    u8 unk_19;       /* 0x19 */
    s16 pitch;       /* 0x1a */
    s16 pitch_step;  /* 0x1c */
    s16 pitch_rest;  /* 0x1e: kind 5's pitch */
    s16 pitch_limit; /* 0x20 */
    s16 yaw;         /* 0x22 */
    s16 yaw_step;    /* 0x24 */
    s16 yaw_rest;    /* 0x26: kind 5's yaw */
    s16 yaw_limit;   /* 0x28 */
    u8 on_target;    /* 0x2a */
    u8 unk_2b;       /* 0x2b */
    Mtx43 head;      /* 0x2c: joint 15 of the object's model; its translation is the head point */
    fx32 range;      /* 0x5c: 0 for any distance */
    u8 in_view_only; /* 0x60 */
    u8 unk_61[3];
    s32 actor; /* 0x64: the field actor of kinds 1 (when tested by SceneLook_CanSee) and 4 */
} SceneLook;

int SceneLook_IsOnTarget(SceneLook *self);
int SceneLook_InView(SceneLook *self, int yaw);
int SceneLook_Within(int value, int limit);
void SceneLook_Update(SceneLook *self, u8 *object);
void SceneLook_AimRest(SceneLook *self);
void SceneLook_AimPoint(SceneLook *self, u8 *object);
void SceneLook_AimObject(SceneLook *self, u8 *object);
void SceneLook_AimPlayer(SceneLook *self, u8 *object);
void SceneLook_AimActorNumber(SceneLook *self, u8 *object);
void SceneLook_AimActor(SceneLook *self, u8 *object, int actor, fx32 range, u8 in_view_only);
void SceneLook_AimAhead(SceneLook *self);
void SceneLook_AimAt(SceneLook *self, u8 *object, u8 *target, const Vec3 *target_head, fx32 range, u8 in_view_only);
int SceneLook_ClampPitch(SceneLook *self, int pitch);
int SceneLook_ClampedPitch(SceneLook *self, const Vec3 *target, const Vec3 *eye, int base);
int SceneLook_ClampYaw(SceneLook *self, int yaw);
int SceneLook_ClampedYaw(SceneLook *self, const Vec3 *target, const Vec3 *from, int base);
s16 SceneLook_Pitch(SceneLook *self, const Vec3 *target, const Vec3 *eye, int base);
int SceneLook_Yaw(SceneLook *self, const Vec3 *target, const Vec3 *from, int base);
int SceneLook_CanSee(SceneLook *self, u8 *object);
void SceneLook_RequestAngles(SceneLook *self, int priority, u16 pitch, u16 yaw, s16 pitch_step, s16 yaw_step);
void SceneLook_Request(SceneLook *self, u8 kind, int priority, int target, const Vec3 *point, int actor, fx32 range,
                       u8 in_view_only);
void SceneLook_SetPoint(SceneLook *self, const Vec3 *point);
void SceneLook_SetPitchLimit(SceneLook *self, int limit);
int SceneLook_HeadPoint(SceneLook *self, Vec3 *out);
void SceneLook_ReadHead(SceneLook *self, u8 *object);
void SceneLook_Lock(SceneLook *self);
void SceneLook_Destruct(SceneLook *self);
void SceneLook_Construct(SceneLook *self);

#endif
