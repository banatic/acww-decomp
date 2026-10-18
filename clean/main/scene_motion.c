/* The motions of kinds 14 to 21 of a scene object (scene_motion.h). */
#include "scene_motion.h"

#include "autoload_2/fx_math.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "held_item_link.h"
#include "ov004/member_pointer.h"
#include "sound_emitter.h"
#include "speaker_anim.h"
#include "effect_system.h"
#include "item_code.h"
#include "layered_model.h"
#include "obj_020dd33c.h"
#include "ov004/room_player_actor.h"
#include "player_actor_ops.h"
#include "player_actors.h"
#include "scene_motion_core.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object.h"
#include "scene_query.h"
#include "scene_share.h"

static_assert(sizeof(SceneMotionArgs) == 0x34, "SceneMotionArgs layout");
static_assert(offsetof(SceneMotionArgs, item) == 0x22, "SceneMotionArgs layout");
static_assert(offsetof(SceneMotionArgs, partner) == 0x28, "SceneMotionArgs layout");
static_assert(offsetof(SceneMotion, note) == 0x06, "SceneMotion layout");
static_assert(offsetof(SceneMotion, priority) == 0x14, "SceneMotion layout");
static_assert(offsetof(SceneMotion, hold) == 0x19, "SceneMotion layout");
static_assert(offsetof(SceneMotion, entry) == 0x20, "SceneMotion layout");
static_assert(offsetof(SceneMotion, next_priority) == 0x28, "SceneMotion layout");
static_assert(offsetof(SceneMotion, next_args) == 0x2c, "SceneMotion layout");
static_assert(offsetof(SceneMotion, args) == 0x60, "SceneMotion layout");
static_assert(offsetof(SceneMotion, done) == 0x94, "SceneMotion layout");
static_assert(offsetof(SceneMotion, step) == 0x98, "SceneMotion layout");
static_assert(offsetof(SceneMotion, effect) == 0xac, "SceneMotion layout");

/* The scene object's parts used here. */
#define SCENE_MOTION_OBJECT_POSITION 0x5c /* a Vec3 */
#define SCENE_MOTION_OBJECT_ANGLE 0x8e    /* s16 */
#define SCENE_MOTION_OBJECT_ANGLE_94 0x94 /* s16: given the object's angle as kind 21 turns */
#define SCENE_MOTION_OBJECT_MODEL 0xec
#define SCENE_MOTION_OBJECT_ITEM 0xea        /* u16: an item code */
#define SCENE_MOTION_OBJECT_BODY_FRAME 0x190 /* fx32: the frame of the body animation */
#define SCENE_MOTION_OBJECT_ANIM 0x334       /* SpeakerAnim */
#define SCENE_MOTION_OBJECT_MOVER 0x350
#define SCENE_MOTION_OBJECT_EFFECT_POINT 0x478 /* a Vec3 */
#define SCENE_MOTION_OBJECT_EFFECT_POINT_2 0x484
#define SCENE_MOTION_OBJECT_EFFECT_POINT_3 0x490
#define SCENE_MOTION_OBJECT_EMITTER 0x514 /* SoundEmitter */
#define SCENE_MOTION_OBJECT_HELD 0x628    /* HeldItemLink *, or null */

/* The object's vtable slot told of frame 8 of an animation SceneMotion_FinishAnimation waits
 * on, with the item and the flag. */
#define SCENE_MOTION_SLOT_FRAME_8 0x88

/* The mover's modes (func_0201b1a4, func_0201b1a0 gives the mode) as kind 21 uses them: stand,
 * walk (1, or 2 with `pace` 2), turn in place to the angle set (func_0201aff4), and turn
 * towards the angle set before walking. */
#define SCENE_MOTION_MOVER_STAND 0
#define SCENE_MOTION_MOVER_WALK 1
#define SCENE_MOTION_MOVER_WALK_2 2
#define SCENE_MOTION_MOVER_TURN 3
#define SCENE_MOTION_MOVER_TURN_FIRST 4
#define SCENE_MOTION_PACE_2 2

/* A spot is reached within a squared distance (fx32) of 0x28 in the ground plane. */
#define SCENE_MOTION_REACH 0x29

/* The steps of kind 21. */
#define SCENE_MOTION_SPOT_STAND 0
#define SCENE_MOTION_SPOT_WALK 1
#define SCENE_MOTION_SPOT_TURN_AT_SPOT 2
#define SCENE_MOTION_SPOT_TURN_FIRST 3
#define SCENE_MOTION_SPOT_STEPS 4

/* The last step of each run: past its table, nothing more runs. */
#define SCENE_MOTION_KIND19_END 1
#define SCENE_MOTION_KIND18_END 2
#define SCENE_MOTION_KIND17_END 3
#define SCENE_MOTION_KIND14_STEPS 20
#define SCENE_MOTION_KIND14_END 0x14

/* The animations' play modes (SpeakerAnim_Play) and their speed. */
#define SCENE_MOTION_PLAY_LOOP 0
#define SCENE_MOTION_PLAY_ONCE 1
#define SCENE_MOTION_PLAY_3 3
#define SCENE_MOTION_SPEED 0x1000

/* The animation slot of a held item's pose. */
#define SCENE_MOTION_SLOT_BODY 0
#define SCENE_MOTION_SLOT_ITEM 1
#define SCENE_MOTION_ITEM_POSE_ANIMATION 0x139

/* The sounds played on the object's emitter, at volume 0x7f. */
#define SCENE_MOTION_VOLUME 0x7f

#define SCENE_MOTION_NO_EFFECT (-1)

/* The last word every motion is set with, and the origin. */
extern u16 data_020c80f8;
extern Vec3 data_021fbee8;

/* The runs' tables of steps: a guard word, the table, and the constants it is filled from. */
extern u32 data_021c1530;
extern MemberPointer data_021c174c[];
extern const MemberPointer data_020d87e4;
extern const MemberPointer data_020d8a1c;
extern const MemberPointer data_020d8a6c;
extern const MemberPointer data_020d87b4;
extern u32 data_021c1528;
extern MemberPointer data_021c155c[];
extern const MemberPointer data_020d87ac;
extern u32 data_021c151c;
extern MemberPointer data_021c162c[];
extern const MemberPointer data_020d8814;
extern const MemberPointer data_020d8774;
extern u32 data_021c1508;
extern MemberPointer data_021c169c[];
extern const MemberPointer data_020d883c;
extern const MemberPointer data_020d8834;
extern const MemberPointer data_020d882c;
extern u32 data_021c1534;
extern MemberPointer data_021c1874[];
extern const MemberPointer data_020d88ec;
extern const MemberPointer data_020d88e4;
extern const MemberPointer data_020d88dc;
extern const MemberPointer data_020d88d4;
extern const MemberPointer data_020d8644;
extern const MemberPointer data_020d865c;
extern const MemberPointer data_020d88bc;
extern const MemberPointer data_020d86dc;
extern const MemberPointer data_020d88ac;
extern const MemberPointer data_020d88a4;
extern const MemberPointer data_020d889c;
extern const MemberPointer data_020d8894;
extern const MemberPointer data_020d888c;
extern const MemberPointer data_020d8884;
extern const MemberPointer data_020d887c;
extern const MemberPointer data_020d8874;
extern const MemberPointer data_020d886c;
extern const MemberPointer data_020d8864;
extern const MemberPointer data_020d885c;
extern const MemberPointer data_020d8854;

extern s32 FX_MulFunc(s32 a, s32 b);

static u8 *scene_motion_part(u8 *object, u32 offset)
{
    return object + offset;
}

static SpeakerAnim *scene_motion_anim(u8 *object)
{
    return (SpeakerAnim *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_ANIM);
}

static void *scene_motion_mover(u8 *object)
{
    return scene_motion_part(object, SCENE_MOTION_OBJECT_MOVER);
}

static s16 scene_motion_angle(u8 *object)
{
    return *(const s16 *) scene_motion_part(object, SCENE_MOTION_OBJECT_ANGLE);
}

static HeldItemLink *scene_motion_held(u8 *object)
{
    return *(HeldItemLink **) scene_motion_part(object, SCENE_MOTION_OBJECT_HELD);
}

/* The body animation `number` in `mode`, from its start, with `arg`. */
static void scene_motion_play(u8 *object, int number, int arg, int mode)
{
    SpeakerAnim_Play(scene_motion_anim(object), object, number, arg, mode, SCENE_MOTION_SPEED, 0, SCENE_MOTION_SLOT_BODY);
}

/* The same, then the held item takes action 0 with the same word. */
static void scene_motion_play_with_item(u8 *object, int number, int mode)
{
    u16 arg = data_020c80f8;
    scene_motion_play(object, number, arg, mode);
    HeldItemLink *held = scene_motion_held(object);
    if (held != NULL) {
        HeldItemLink_Action0(held, arg, 0);
    }
}

static int scene_motion_body_at_end(u8 *object)
{
    return SpeakerAnim_BodyAtEnd(scene_motion_anim(object), object);
}

static void scene_motion_sound(u8 *object, int number)
{
    SoundEmitter_Play((SoundEmitter *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EMITTER), number,
                      SCENE_MOTION_VOLUME, 0);
}

/* The model's item pose stops when slot 1 holds animation 0x139. */
static void scene_motion_drop_item_pose(u8 *object)
{
    if (SpeakerAnim_Number(scene_motion_anim(object), SCENE_MOTION_SLOT_ITEM) == SCENE_MOTION_ITEM_POSE_ANIMATION) {
        LayeredModel_StartAFromBase((LayeredModel *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_MODEL), 0, 0);
    }
}

/* The motion ends: done, and (for kind 14) its last step. */
static void scene_motion_end14(SceneMotion *self)
{
    SceneMotion_SetDone(self, 1);
    self->step = SCENE_MOTION_KIND14_END;
}

/* A call through a step's member pointer. */
static void scene_motion_call(const MemberPointer *member, SceneMotion *self, u8 *object)
{
    void *target = MemberPointer_Object(member, self);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, target))(target, object);
}

/* ---- Waiting for an animation's end */

/* func_02017f1c: while the body animation is `animation`: at its end, the first standard
 * animation loops (and the held item takes action 0), and the result is 1. Before then, at the
 * whole frames 8, 13 and 3 the object is told of frame 8 (its vtable slot 0x88, with `item` and
 * `flag`), effect 0x22 starts at its position, or effect 0x28 starts at its points 0x490 and
 * 0x484 with its angle. Else the result is 0.
 * QUIRK: a frame acts on every call made while the animation is on it, so an animation played
 * slower than one frame a call acts on it more than once. */
int SceneMotion_FinishAnimation(SceneMotion *self, u8 *object, u16 *item, int animation, u8 flag)
{
    (void) self;
    if (animation != SpeakerAnim_Number(scene_motion_anim(object), SCENE_MOTION_SLOT_BODY)) {
        return 0;
    }
    if (scene_motion_body_at_end(object)) {
        scene_motion_play_with_item(object, 0, SCENE_MOTION_PLAY_LOOP);
        return 1;
    }

    u32 frame = *(const u32 *) scene_motion_part(object, SCENE_MOTION_OBJECT_BODY_FRAME);
    switch ((frame << 4) >> 16) {
        case 8: {
            const u8 *vtable = *(const u8 *const *) object;
            u32 code = *(const u32 *) (vtable + SCENE_MOTION_SLOT_FRAME_8);
            ((void (*)(u8 *, u16 *, u8))(uintptr_t) code)(object, item, flag);
            break;
        }
        case 0xd:
            EffectSystem_StartKind(0x22, (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_POSITION), NULL,
                                   0);
            break;
        case 3: {
            s16 angle = scene_motion_angle(object);
            EffectSystem_StartKind(0x28, (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EFFECT_POINT_3),
                                   &angle, 0);
            EffectSystem_StartKind(0x28, (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EFFECT_POINT_2),
                                   &angle, 0);
            break;
        }
        default:
            break;
    }
    return 0;
}
CLEAN_AS(func_02017f1c, SceneMotion_FinishAnimation)

/* ---- Kind 21: walking to the spot */

static void scene_motion_set_mode(u8 *object, int mode)
{
    SceneMover_SetMode(scene_motion_mover(object), object, mode, 0, data_020c80f8);
}

static void scene_motion_set_angle(u8 *object, int angle)
{
    SceneMover_SetAngle(scene_motion_mover(object), angle);
}

static void scene_motion_set_target(u8 *object, const Vec3 *point)
{
    SceneMover_SetStart(scene_motion_mover(object), point);
    SceneMover_SetEnd(scene_motion_mover(object), point);
}

/* The walking mode: 2 with `pace` 2, else 1. */
static void scene_motion_set_walk(SceneMotion *self, u8 *object)
{
    scene_motion_set_mode(object, self->pace == SCENE_MOTION_PACE_2 ? SCENE_MOTION_MOVER_WALK_2 : SCENE_MOTION_MOVER_WALK);
}

/* The squared distance in the ground plane from the object to `spot`, as the game's
 * multiplications give it (wrapping like the ARM's), and the offsets. */
static s32 scene_motion_distance2(u8 *object, const Vec3 *spot, s32 *dx, s32 *dz)
{
    const Vec3 *position = (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_POSITION);
    *dx = (s32) ((u32) spot->x - (u32) position->x);
    *dz = (s32) ((u32) spot->z - (u32) position->z);
    s32 xx = FX_MulFunc(*dx, *dx);
    s32 zz = FX_MulFunc(*dz, *dz);
    return (s32) ((u32) xx + (u32) zz);
}

/* Whether a turn of `turn` (an angle) is less than a quarter turn either way (func_0201c3dc). */
static int scene_motion_ahead(int heading, s16 angle)
{
    return SceneObject_IsWithinQuarterTurn((s16) (u16) ((u32) heading - (u32) angle));
}

/* Standing: the stand mode, the angle and the origin as the target, and step 0. */
static void scene_motion_stand(SceneMotion *self, u8 *object, s16 angle)
{
    scene_motion_set_mode(object, SCENE_MOTION_MOVER_STAND);
    scene_motion_set_angle(object, angle);
    scene_motion_set_target(object, &data_021fbee8);
    self->step = SCENE_MOTION_SPOT_STAND;
}

/* Turning in place to the spot's angle: step 2. */
static void scene_motion_turn(SceneMotion *self, u8 *object, s16 angle)
{
    scene_motion_set_mode(object, SCENE_MOTION_MOVER_TURN);
    scene_motion_set_angle(object, angle);
    self->step = SCENE_MOTION_SPOT_TURN_AT_SPOT;
}

/* _ZN12Obj_020d8bd413func_020169b8EPv: kind 21's run: its step through its table. */
void SceneMotion_RunGoToSpot(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d87e4, /* SceneMotion_GoToSpotStand */
        &data_020d8a1c, /* SceneMotion_GoToSpotWalk */
        &data_020d8a6c, /* SceneMotion_GoToSpotTurnFirst */
        &data_020d87b4, /* SceneMotion_GoToSpotTurnAtSpot */
    };
    MemberTable_InitOnce(&data_021c1530, data_021c174c, steps, SCENE_MOTION_SPOT_STEPS);
    if (self->step < SCENE_MOTION_SPOT_STEPS) {
        scene_motion_call(&data_021c174c[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020169b8EPv, SceneMotion_RunGoToSpot)

/* func_02016a48: step 2, turning at the spot. The mover's angle is brought up to date
 * (func_0201b188). Without a spot, the object stands. On the spot exactly, the object's angle
 * goes to its word at 0x94 and it turns on to the spot's angle, or stands once there. Out of
 * reach, it walks when the spot is ahead (its word at 0x94 is set as above; step 1), else it
 * keeps turning, to face the spot; either way the spot is the target.
 * QUIRK: within reach but not exactly on the spot, nothing happens. */
void SceneMotion_GoToSpotTurnAtSpot(SceneMotion *self, u8 *object)
{
    s16 *angle_94 = (s16 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_ANGLE_94);
    Vec3 spot = {0, 0, 0};
    s16 angle = scene_motion_angle(object);
    s32 dx;
    s32 dz;

    SceneMover_AimAtEnd(scene_motion_mover(object), object);
    if (SceneShare_ReadPlace(object, &spot, &angle) == 0) {
        scene_motion_stand(self, object, angle);
        return;
    }
    s32 distance2 = scene_motion_distance2(object, &spot, &dx, &dz);
    if (distance2 == 0) {
        *angle_94 = scene_motion_angle(object);
        if (angle != scene_motion_angle(object)) {
            scene_motion_turn(self, object, angle);
        } else {
            scene_motion_stand(self, object, angle);
        }
        return;
    }
    if (distance2 < SCENE_MOTION_REACH) {
        return;
    }
    int heading = Math_Atan2(dx, dz);
    if (scene_motion_ahead(heading, angle)) {
        scene_motion_set_walk(self, object);
        *angle_94 = scene_motion_angle(object);
        scene_motion_set_angle(object, angle);
        self->step = SCENE_MOTION_SPOT_WALK;
    } else {
        scene_motion_set_angle(object, heading);
    }
    scene_motion_set_target(object, &spot);
}
CLEAN_AS(func_02016a48, SceneMotion_GoToSpotTurnAtSpot)

/* func_02016bfc: step 3, turning before walking. Without a spot, the object stands. Within
 * reach, the mover turns to the spot's angle, and once it has it and the object faces that
 * way, step 0. Out of reach, it walks when the spot is ahead (step 1), else turns to face it
 * (step 3); the spot is the target. */
void SceneMotion_GoToSpotTurnFirst(SceneMotion *self, u8 *object)
{
    Vec3 spot = {0, 0, 0};
    s16 angle = scene_motion_angle(object);
    s32 dx;
    s32 dz;

    if (SceneShare_ReadPlace(object, &spot, &angle) == 0) {
        scene_motion_stand(self, object, angle);
        return;
    }
    if (scene_motion_distance2(object, &spot, &dx, &dz) < SCENE_MOTION_REACH) {
        void *mover = scene_motion_mover(object);
        if (angle != SceneMover_Angle(mover)) {
            scene_motion_set_angle(object, angle);
        } else if (SceneMover_Angle(mover) == scene_motion_angle(object)) {
            self->step = SCENE_MOTION_SPOT_STAND;
        }
        return;
    }
    int heading = Math_Atan2(dx, dz);
    if (scene_motion_ahead(heading, angle)) {
        scene_motion_set_walk(self, object);
        scene_motion_set_angle(object, angle);
        self->step = SCENE_MOTION_SPOT_WALK;
    } else {
        scene_motion_set_mode(object, SCENE_MOTION_MOVER_TURN_FIRST);
        scene_motion_set_angle(object, heading);
        self->step = SCENE_MOTION_SPOT_TURN_FIRST;
    }
    scene_motion_set_target(object, &spot);
}
CLEAN_AS(func_02016bfc, SceneMotion_GoToSpotTurnFirst)

/* func_02016d6c: step 1, walking. The mover's angle is brought up to date (func_0201b188).
 * Without a spot, the object stands. Within reach, it turns to the spot's angle (step 2) or
 * stands. Out of reach with the spot behind, it turns in place to the spot's angle (step 2,
 * the target unchanged); with the spot ahead, the walking mode follows `pace` (1 becomes 2
 * with pace 2, 2 becomes 1 with pace 1) and the spot is the target. */
void SceneMotion_GoToSpotWalk(SceneMotion *self, u8 *object)
{
    void *mover = scene_motion_mover(object);
    Vec3 spot = {0, 0, 0};
    s16 angle = scene_motion_angle(object);
    s32 dx;
    s32 dz;

    SceneMover_AimAtEnd(mover, object);
    if (SceneShare_ReadPlace(object, &spot, &angle) == 0) {
        scene_motion_stand(self, object, angle);
        return;
    }
    if (scene_motion_distance2(object, &spot, &dx, &dz) < SCENE_MOTION_REACH) {
        if (angle != scene_motion_angle(object)) {
            scene_motion_turn(self, object, angle);
        } else {
            scene_motion_stand(self, object, angle);
        }
        return;
    }
    if (!scene_motion_ahead(Math_Atan2(dx, dz), angle)) {
        scene_motion_turn(self, object, angle);
        return;
    }
    if (SceneMover_Mode(mover) == SCENE_MOTION_MOVER_WALK) {
        if (self->pace == SCENE_MOTION_PACE_2) {
            scene_motion_set_mode(object, SCENE_MOTION_MOVER_WALK_2);
        }
    } else if (SceneMover_Mode(mover) == SCENE_MOTION_MOVER_WALK_2) {
        if (self->pace == 1) {
            scene_motion_set_mode(object, SCENE_MOTION_MOVER_WALK);
        }
    }
    scene_motion_set_target(object, &spot);
}
CLEAN_AS(func_02016d6c, SceneMotion_GoToSpotWalk)

/* func_02016f30: step 0, standing. Without a spot, nothing. Within reach, the object turns to
 * the spot's angle (step 2) when it does not face it, else a moving mover is stopped with the
 * origin as its target. Out of reach, it walks when the spot is ahead (step 1), else turns to
 * face it (step 3); the spot is the target. */
void SceneMotion_GoToSpotStand(SceneMotion *self, u8 *object)
{
    Vec3 spot = {0, 0, 0};
    s16 angle = scene_motion_angle(object);
    s32 dx;
    s32 dz;

    if (SceneShare_ReadPlace(object, &spot, &angle) == 0) {
        return;
    }
    if (scene_motion_distance2(object, &spot, &dx, &dz) < SCENE_MOTION_REACH) {
        if (angle != scene_motion_angle(object)) {
            scene_motion_turn(self, object, angle);
            return;
        }
        if (SceneMover_Mode(scene_motion_mover(object)) == SCENE_MOTION_MOVER_STAND) {
            return;
        }
        scene_motion_set_mode(object, SCENE_MOTION_MOVER_STAND);
        scene_motion_set_target(object, &data_021fbee8);
        return;
    }
    int heading = Math_Atan2(dx, dz);
    if (scene_motion_ahead(heading, angle)) {
        scene_motion_set_walk(self, object);
        scene_motion_set_angle(object, angle);
        self->step = SCENE_MOTION_SPOT_WALK;
    } else {
        scene_motion_set_mode(object, SCENE_MOTION_MOVER_TURN_FIRST);
        scene_motion_set_angle(object, heading);
        self->step = SCENE_MOTION_SPOT_TURN_FIRST;
    }
    scene_motion_set_target(object, &spot);
}
CLEAN_AS(func_02016f30, SceneMotion_GoToSpotStand)

/* func_0201709c: kind 21's start. Without a spot, the object stands (mover's stand mode, the
 * origin as the target; step 0). Within reach, it turns to the spot's angle (step 2) or
 * stands, with the origin as the target. Out of reach, it walks when the spot is ahead (step
 * 1), else turns to face it first (step 3); the spot is the target. Returns 1. */
int SceneMotion_StartGoToSpot(SceneMotion *self, u8 *object)
{
    Vec3 spot = {0, 0, 0};
    s16 angle = scene_motion_angle(object);
    s32 dx;
    s32 dz;

    if (SceneShare_ReadPlace(object, &spot, &angle) == 0) {
        scene_motion_set_mode(object, SCENE_MOTION_MOVER_STAND);
        scene_motion_set_target(object, &data_021fbee8);
        self->step = SCENE_MOTION_SPOT_STAND;
        return 1;
    }
    if (scene_motion_distance2(object, &spot, &dx, &dz) < SCENE_MOTION_REACH) {
        if (angle != scene_motion_angle(object)) {
            scene_motion_turn(self, object, angle);
        } else {
            scene_motion_set_mode(object, SCENE_MOTION_MOVER_STAND);
            self->step = SCENE_MOTION_SPOT_STAND;
        }
        scene_motion_set_target(object, &data_021fbee8);
        return 1;
    }
    int heading = Math_Atan2(dx, dz);
    if (scene_motion_ahead(heading, angle)) {
        scene_motion_set_walk(self, object);
        self->step = SCENE_MOTION_SPOT_WALK;
    } else {
        scene_motion_set_mode(object, SCENE_MOTION_MOVER_TURN_FIRST);
        scene_motion_set_angle(object, heading);
        self->step = SCENE_MOTION_SPOT_TURN_FIRST;
    }
    scene_motion_set_target(object, &spot);
    return 1;
}
CLEAN_AS(func_0201709c, SceneMotion_StartGoToSpot)

/* ---- Kind 20: animation 6 with an item */

/* func_02017224: kind 20's after-step: done once animation 6 ends (SceneMotion_FinishAnimation
 * with the motion's item and flag 0). */
void SceneMotion_Kind20After(SceneMotion *self, u8 *object)
{
    SceneMotionArgs *args = SceneMotion_Args(self);
    if (SceneMotion_FinishAnimation(self, object, &args->item, 6, 0)) {
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02017224, SceneMotion_Kind20After)

/* func_02017258: kind 20's start: animation 6 once (the held item takes action 0), effect 0x61
 * at the object's position and sound 0x76. Returns 1. */
int SceneMotion_StartKind20(SceneMotion *self, u8 *object)
{
    SceneMotion_Args(self);
    scene_motion_play_with_item(object, 6, SCENE_MOTION_PLAY_ONCE);
    EffectSystem_StartOneShotSetNumber(0x61, (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_POSITION),
                                       0, 0);
    scene_motion_sound(object, 0x76);
    SceneMotion_SetDone(self, 0);
    return 1;
}
CLEAN_AS(func_02017258, SceneMotion_StartKind20)

/* func_020172d8: asks for kind 20 with `priority` and the item `*item`, when `priority` is at
 * least that of the motion asked for, or that one's is 3. Returns whether it was asked for. */
int SceneMotion_RequestKind20(SceneMotion *self, int priority, u16 *item)
{
    if (priority < self->next_priority && self->next_priority != 3) {
        return 0;
    }
    SceneMotion_SetNext(self, SCENE_MOTION_KIND_20, priority);
    SceneMotionArgs_Clear(&self->next_args);
    self->next_args.item = *item;
    return 1;
}
CLEAN_AS(func_020172d8, SceneMotion_RequestKind20)

/* ---- Kind 19: animations 0x29 and 0x2a with effect 0x40 */

/* func_02017310: kind 19's after-step: once animation 0x2a ends, func_02057cb8, the first
 * standard animation loops and the motion is done. */
void SceneMotion_Kind19After(SceneMotion *self, u8 *object)
{
    if (SpeakerAnim_Number(scene_motion_anim(object), SCENE_MOTION_SLOT_BODY) != 0x2a) {
        return;
    }
    if (!scene_motion_body_at_end(object)) {
        return;
    }
    Obj020dd33c_Finish(object);
    scene_motion_play(object, 0, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
    SceneMotion_SetDone(self, 1);
}
CLEAN_AS(func_02017310, SceneMotion_Kind19After)

/* _ZN12Obj_020d8bd413func_02017370EPv: kind 19's run: its step through its table. */
void SceneMotion_RunKind19(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d87ac, /* SceneMotion_Kind19Step0 */
    };
    MemberTable_InitOnce(&data_021c1528, data_021c155c, steps, 1);
    if (self->step < 1) {
        scene_motion_call(&data_021c155c[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02017370EPv, SceneMotion_RunKind19)

/* func_020173d8: kind 19's step 0: when the body animation ends, animation 0x2a once and the
 * effect stops (step 1); until then the effect follows the object's effect point and angle. */
void SceneMotion_Kind19Step0(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object)) {
        scene_motion_play(object, 0x2a, 0, SCENE_MOTION_PLAY_ONCE);
        if (self->effect != SCENE_MOTION_NO_EFFECT) {
            EffectSystem_EndHandle(self->effect);
        }
        self->step = SCENE_MOTION_KIND19_END;
    } else if (self->effect != SCENE_MOTION_NO_EFFECT) {
        EffectSystem_MoveHandle(self->effect,
                                (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EFFECT_POINT),
                                (const s16 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_ANGLE), 0);
    }
}
CLEAN_AS(func_020173d8, SceneMotion_Kind19Step0)

/* func_0201744c: kind 19's start: the object is handed over with 0xb (func_02057d0c),
 * animation 0x29 once, effect 0x40 at the object's effect point and angle (kept as `effect`)
 * and sound 0x6f. Returns 1. */
int SceneMotion_StartKind19(SceneMotion *self, u8 *object)
{
    Vec3 point = *(const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EFFECT_POINT);
    s16 angle = scene_motion_angle(object);

    Obj020dd33c_SetActorMode(0xb, object);
    scene_motion_play(object, 0x29, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
    self->effect = EffectSystem_StartKind(0x40, &point, &angle, 0);
    scene_motion_sound(object, 0x6f);
    SceneMotion_SetDone(self, 0);
    return 1;
}
CLEAN_AS(func_0201744c, SceneMotion_StartKind19)

/* ---- Kind 18: waiting on the object at data_021c9350 (number 8) */

/* _ZN12Obj_020d8bd413func_020174e0Ei: kind 18's run: its step through its table. */
void SceneMotion_RunKind18(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d8814, /* SceneMotion_Kind18Step0 */
        &data_020d8774, /* SceneMotion_Kind18Step1 */
    };
    MemberTable_InitOnce(&data_021c151c, data_021c162c, steps, 2);
    if (self->step < 2) {
        scene_motion_call(&data_021c162c[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020174e0Ei, SceneMotion_RunKind18)

/* func_02017550: kind 18's step 1: once func_02057bf0 (8) says no, the motion is done. */
void SceneMotion_Kind18Step1(SceneMotion *self, u8 *object)
{
    (void) object;
    if (Obj020dd33c_InMode(8) == 0) {
        self->step = SCENE_MOTION_KIND18_END;
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02017550, SceneMotion_Kind18Step1)

/* func_02017574: kind 18's step 0: once func_02057bf0 (8) says yes, step 1. */
void SceneMotion_Kind18Step0(SceneMotion *self, u8 *object)
{
    (void) object;
    if (Obj020dd33c_InMode(8)) {
        self->step = 1;
    }
}
CLEAN_AS(func_02017574, SceneMotion_Kind18Step0)

/* func_02017590: kind 18's start: with the object at data_021c9350 there and taking the object
 * with 8 (func_02057d0c), func_02057b90 (8), step 0, not done, and func_02095380 (0x72).
 * Returns 1. */
int SceneMotion_StartKind18(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsBusy() && Obj020dd33c_SetActorMode(8, object)) {
        Obj020dd33c_SetStage(8, object);
        self->step = 0;
        SceneMotion_SetDone(self, 0);
        PlayerActors_OwnPlaySound(0x72);
    }
    return 1;
}
CLEAN_AS(func_02017590, SceneMotion_StartKind18)

/* ---- Kind 17: animations 0x26 and 0x23 */

/* _ZN12Obj_020d8bd413func_020175d4EPv: kind 17's run: its step through its table. */
void SceneMotion_RunKind17(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d883c, /* SceneMotion_Kind17Step0 */
        &data_020d8834, /* SceneMotion_Kind17Step1 */
        &data_020d882c, /* SceneMotion_Kind17Step2 */
    };
    MemberTable_InitOnce(&data_021c1508, data_021c169c, steps, 3);
    if (self->step < 3) {
        scene_motion_call(&data_021c169c[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020175d4EPv, SceneMotion_RunKind17)

/* func_02017654: kind 17's step 2: once the object at data_021c9350 is gone or idle
 * (func_02057bd4 gives 0), the motion is done. */
void SceneMotion_Kind17Step2(SceneMotion *self, u8 *object)
{
    (void) object;
    if (Obj020dd33c_IsBusy() == 0) {
        SceneMotion_SetDone(self, 1);
        self->step = SCENE_MOTION_KIND17_END;
    }
}
CLEAN_AS(func_02017654, SceneMotion_Kind17Step2)

/* func_02017674: kind 17's step 1: unless func_02057d34 says so of the object, the first
 * standard animation loops (step 2). */
void SceneMotion_Kind17Step1(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsLead(object) != 0) {
        return;
    }
    scene_motion_play(object, 0, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
    self->step = 2;
}
CLEAN_AS(func_02017674, SceneMotion_Kind17Step1)

/* func_020176bc: kind 17's step 0: when the body animation ends and func_02095a28 says so,
 * animation 0x23 loops (step 1). */
void SceneMotion_Kind17Step0(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object) && PlayerActorOps_RequestState32() != 0) {
        scene_motion_play(object, 0x23, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
        self->step = 1;
    }
}
CLEAN_AS(func_020176bc, SceneMotion_Kind17Step0)

/* func_02017710: kind 17's start: with the object at data_021c9350 there and taking the object
 * with 7, animation 0x26 in mode 3, the item pose stops when it is animation 0x139,
 * func_02057b90 (5) and not done. Returns 1. */
int SceneMotion_StartKind17(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsBusy() && Obj020dd33c_SetActorMode(7, object)) {
        scene_motion_play(object, 0x26, data_020c80f8, SCENE_MOTION_PLAY_3);
        scene_motion_drop_item_pose(object);
        Obj020dd33c_SetStage(5, object);
        SceneMotion_SetDone(self, 0);
    }
    return 1;
}
CLEAN_AS(func_02017710, SceneMotion_StartKind17)

/* ---- Kind 16: animation 0x27 */

/* func_02017790: kind 16's after-step: when the body animation ends, func_02057cb8, the first
 * standard animation loops and the motion is done. */
void SceneMotion_Kind16After(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object)) {
        Obj020dd33c_Finish(object);
        scene_motion_play(object, 0, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02017790, SceneMotion_Kind16After)

/* func_020177e0: kind 16's start: with the object at data_021c9350 there and taking the object
 * with 5, animation 0x27 once, sound 0x4f, the item pose stops when it is animation 0x139, and
 * not done. Returns 1. */
int SceneMotion_StartKind16(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsBusy() && Obj020dd33c_SetActorMode(5, object)) {
        scene_motion_play(object, 0x27, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
        scene_motion_sound(object, 0x4f);
        scene_motion_drop_item_pose(object);
        SceneMotion_SetDone(self, 0);
    }
    return 1;
}
CLEAN_AS(func_020177e0, SceneMotion_StartKind16)

/* ---- Kind 15: animation 0x28 with the item of the object at data_021c9350 */

/* func_0201786c: kind 15's after-step: done once animation 0x28 ends (SceneMotion_FinishAnimation
 * with the motion's item and flag 1). */
void SceneMotion_Kind15After(SceneMotion *self, u8 *object)
{
    SceneMotionArgs *args = SceneMotion_Args(self);
    if (SceneMotion_FinishAnimation(self, object, &args->item, 0x28, 1) != 0) {
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_0201786c, SceneMotion_Kind15After)

/* func_020178a0: kind 15's start: the motion's item is the one func_02057bb8 gives (0xfff1
 * without the object at data_021c9350); func_02057cb8 when that object is there; animation 0x28
 * once, effect 0x61 at the object's position, sound 0x76, not done. Then the note says kind 20
 * with the motion's priority and the item (func_020199ec). Returns 1. */
int SceneMotion_StartKind15(SceneMotion *self, u8 *object)
{
    SceneMotionArgs *args = SceneMotion_Args(self);
    u16 item;

    Obj020dd33c_Item(&item);
    args->item = item;
    if (Obj020dd33c_IsBusy() != 0) {
        Obj020dd33c_Finish(object);
    }
    scene_motion_play(object, 0x28, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
    EffectSystem_StartOneShotSetNumber(0x61, (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_POSITION),
                                       0, 0);
    scene_motion_sound(object, 0x76);
    SceneMotion_SetDone(self, 0);
    self->note_kind = SCENE_MOTION_KIND_20;
    self->note_priority = (u8) self->priority;
    SceneMotionNote_PackItem(self, self->note, &args->item);
    return 1;
}
CLEAN_AS(func_020178a0, SceneMotion_StartKind15)

/* ---- Kind 14: a sequence of animations led by the object at data_021c9350 */

/* func_02017938: kind 14's after-step: nothing. */
void SceneMotion_Kind14After(void) {}
CLEAN_AS(func_02017938, SceneMotion_Kind14After)

/* _ZN12Obj_020d8bd413func_0201793cEi: kind 14's run: its step through its table. */
void SceneMotion_RunKind14(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d88ec, /* SceneMotion_Kind14Step0 */
        &data_020d88e4, /* SceneMotion_Kind14Step1 */
        &data_020d88dc, /* SceneMotion_Kind14Step2 */
        &data_020d88d4, /* SceneMotion_Kind14Step3 */
        &data_020d8644, /* SceneMotion_Kind14Step4 */
        &data_020d865c, /* SceneMotion_Kind14Step5 */
        &data_020d88bc, /* SceneMotion_Kind14Step6 */
        &data_020d86dc, /* SceneMotion_Kind14Step7 */
        &data_020d88ac, /* SceneMotion_Kind14Step8 */
        &data_020d88a4, /* SceneMotion_Kind14Step9 */
        &data_020d889c, /* SceneMotion_Kind14Step10 */
        &data_020d8894, /* SceneMotion_Kind14Step11 */
        &data_020d888c, /* SceneMotion_Kind14Step12 */
        &data_020d8884, /* SceneMotion_Kind14Step13 */
        &data_020d887c, /* SceneMotion_Kind14Step14 */
        &data_020d8874, /* SceneMotion_Kind14Step15 */
        &data_020d886c, /* SceneMotion_Kind14Step16 */
        &data_020d8864, /* SceneMotion_Kind14Step17 */
        &data_020d885c, /* SceneMotion_Kind14Step18 */
        &data_020d8854, /* SceneMotion_Kind14Step19 */
    };
    MemberTable_InitOnce(&data_021c1534, data_021c1874, steps, SCENE_MOTION_KIND14_STEPS);
    if (self->step < SCENE_MOTION_KIND14_STEPS) {
        scene_motion_call(&data_021c1874[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_0201793cEi, SceneMotion_RunKind14)

/* Whether the item code at `item` is `code`; through func_0204bc64 on both when func_0204bcdc
 * says so of it. */
static int scene_motion_item_is(u16 *item, u16 code)
{
    if (ItemCode_HasVariant(item) == 0) {
        return *item == code;
    }
    u16 other = code;
    int value = ItemCode_VariantItem(item);
    return value == ItemCode_VariantItem(&other);
}

/* Step 2 of kind 14: animation 0x25 once (the held item takes action 0). */
static void scene_motion_kind14_to_step2(SceneMotion *self, u8 *object)
{
    scene_motion_play_with_item(object, 0x25, SCENE_MOTION_PLAY_ONCE);
    self->step = 2;
}

/* func_020183cc: kind 14's step 0, while func_02057bf0 (2) says so: with the object's item
 * 0xd00c, or near the object at data_021c9350 (func_02057c68), step 2. Else, with the motion's
 * item 0x1565, its word at 0x24 zero and func_020b65c4 9 or 0x10, step 2 when func_02057c20
 * says so of the object (else nothing). Else the object walks (mover mode 1) to the point
 * func_02057c44 gives, at height 0 (step 1). */
void SceneMotion_Kind14Step0(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_InMode(2) == 0) {
        return;
    }
    SceneMotionArgs *args = SceneMotion_Args(self);

    if (scene_motion_item_is((u16 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_ITEM), 0xd00c) ||
        Obj020dd33c_IsNear((const Actor *) (void *) object)) {
        scene_motion_kind14_to_step2(self, object);
        return;
    }
    if (scene_motion_item_is(&args->item, 0x1565) && args->unk_24 == 0 &&
        (SceneQuery_Current() == 9 || SceneQuery_Current() == 0x10)) {
        if (Obj020dd33c_Lead(object) != 0) {
            scene_motion_kind14_to_step2(self, object);
        }
        return;
    }
    Vec3 point;
    if (Obj020dd33c_Point(&point) != 0) {
        point.y = 0;
        scene_motion_set_target(object, &point);
        scene_motion_set_mode(object, SCENE_MOTION_MOVER_WALK);
        self->step = 1;
    }
}
CLEAN_AS(func_020183cc, SceneMotion_Kind14Step0)

/* func_02018340: kind 14's step 1: once near the object at data_021c9350, the object stands
 * (mover mode 0, the origin as the target) and step 2 begins. */
void SceneMotion_Kind14Step1(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsNear((const Actor *) (void *) object) == 0) {
        return;
    }
    u16 arg = data_020c80f8;
    SceneMover_SetMode(scene_motion_mover(object), object, SCENE_MOTION_MOVER_STAND, 0, arg);
    scene_motion_set_target(object, &data_021fbee8);
    scene_motion_play(object, 0x25, arg, SCENE_MOTION_PLAY_ONCE);
    HeldItemLink *held = scene_motion_held(object);
    if (held != NULL) {
        HeldItemLink_Action0(held, arg, 0);
    }
    self->step = 2;
}
CLEAN_AS(func_02018340, SceneMotion_Kind14Step1)

/* func_02018304: kind 14's step 2: when the body animation ends, func_02057c20 says so of the
 * object and the object takes it with 3, step 3. */
void SceneMotion_Kind14Step2(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object) && Obj020dd33c_Lead(object) && Obj020dd33c_SetActorMode(3, object)) {
        self->step = 3;
    }
}
CLEAN_AS(func_02018304, SceneMotion_Kind14Step2)

/* func_02018298: kind 14's step 3: unless func_02057bf0 (3), when the object at data_021c9350
 * takes the object with 4, animation 0x26 once (step 4). */
void SceneMotion_Kind14Step3(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_InMode(3) != 0) {
        return;
    }
    if (Obj020dd33c_SetActorMode(4, object) == 0) {
        return;
    }
    scene_motion_play_with_item(object, 0x26, SCENE_MOTION_PLAY_ONCE);
    self->step = 4;
}
CLEAN_AS(func_02018298, SceneMotion_Kind14Step3)

/* func_02018090: kind 14's step 4: when the body animation ends, by what func_02057cf4 gives
 * (where the object needs to take the object with that number, nothing happens until it does):
 * - 6: func_02057cb8, animation 0x28 once, effect 0x61 at the position, sound 0x76 (step 6);
 * - 7: animation 0x26 in mode 3 (step 7);
 * - 5: animation 0x27 once and sound 0x4f (step 5);
 * - 10: the first standard animation loops, animation 0x139 in the item slot on joints 9 to
 *   0x0e, and the motion is done;
 * - 11: animation 0x29 once with effect 0x40 at the effect point (step 11);
 * - else: animation 0x24 loops and the motion is done. */
void SceneMotion_Kind14Step4(SceneMotion *self, u8 *object)
{
    if (!scene_motion_body_at_end(object)) {
        return;
    }
    switch (Obj020dd33c_Stage()) {
        case 6:
            Obj020dd33c_Finish(object);
            scene_motion_play(object, 0x28, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
            EffectSystem_StartOneShotSetNumber(
                0x61, (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_POSITION), 0, 0);
            scene_motion_sound(object, 0x76);
            self->step = 6;
            break;
        case 7:
            if (Obj020dd33c_SetActorMode(7, object) == 0) {
                return;
            }
            scene_motion_play(object, 0x26, data_020c80f8, SCENE_MOTION_PLAY_3);
            self->step = 7;
            break;
        case 5:
            if (Obj020dd33c_SetActorMode(5, object) == 0) {
                return;
            }
            scene_motion_play(object, 0x27, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
            scene_motion_sound(object, 0x4f);
            self->step = 5;
            break;
        case 10:
            if (Obj020dd33c_SetActorMode(10, object) == 0) {
                return;
            }
            scene_motion_play(object, 0, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
            SpeakerAnim_Play(scene_motion_anim(object), object, SCENE_MOTION_ITEM_POSE_ANIMATION, 0, 0, SCENE_MOTION_SPEED, 0,
                             SCENE_MOTION_SLOT_ITEM);
            LayeredModel_MoveNodesToA((LayeredModel *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_MODEL), 9, 0xe);
            SceneMotion_SetDone(self, 1);
            self->step = SCENE_MOTION_KIND14_END;
            break;
        case 11: {
            if (Obj020dd33c_SetActorMode(0xb, object) == 0) {
                return;
            }
            Vec3 point = *(const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EFFECT_POINT);
            s16 angle = scene_motion_angle(object);
            scene_motion_play(object, 0x29, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
            self->effect = EffectSystem_StartKind(0x40, &point, &angle, 0);
            self->step = 0xb;
            break;
        }
        default:
            scene_motion_play(object, 0x24, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
            SceneMotion_SetDone(self, 1);
            self->step = SCENE_MOTION_KIND14_END;
            break;
    }
}
CLEAN_AS(func_02018090, SceneMotion_Kind14Step4)

/* func_02017ff4: kind 14's step 5: when the body animation ends, the first standard animation
 * loops (the held item takes action 0), func_02057cb8, the effect stops and the motion is
 * done; until then the effect follows the object's effect point and angle. */
void SceneMotion_Kind14Step5(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object)) {
        scene_motion_play_with_item(object, 0, SCENE_MOTION_PLAY_LOOP);
        Obj020dd33c_Finish(object);
        if (self->effect != SCENE_MOTION_NO_EFFECT) {
            EffectSystem_EndHandle(self->effect);
        }
        scene_motion_end14(self);
    } else if (self->effect != SCENE_MOTION_NO_EFFECT) {
        EffectSystem_MoveHandle(self->effect,
                                (const Vec3 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_EFFECT_POINT),
                                (const s16 *) (void *) scene_motion_part(object, SCENE_MOTION_OBJECT_ANGLE), 0);
    }
}
CLEAN_AS(func_02017ff4, SceneMotion_Kind14Step5)

/* func_02017ee4: kind 14's step 6: done once animation 0x28 ends (SceneMotion_FinishAnimation
 * with the motion's item and flag 1). */
void SceneMotion_Kind14Step6(SceneMotion *self, u8 *object)
{
    SceneMotionArgs *args = SceneMotion_Args(self);
    if (SceneMotion_FinishAnimation(self, object, &args->item, 0x28, 1) != 0) {
        scene_motion_end14(self);
    }
}
CLEAN_AS(func_02017ee4, SceneMotion_Kind14Step6)

/* func_02017e7c: kind 14's step 7: when the body animation ends and func_02095a28 says so,
 * animation 0x23 loops (step 8). */
void SceneMotion_Kind14Step7(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object) && PlayerActorOps_RequestState32()) {
        scene_motion_play_with_item(object, 0x23, SCENE_MOTION_PLAY_LOOP);
        self->step = 8;
    }
}
CLEAN_AS(func_02017e7c, SceneMotion_Kind14Step7)

/* func_02017e20: kind 14's step 8: unless func_02057d34 says so of the object, the first
 * standard animation loops (step 9). */
void SceneMotion_Kind14Step8(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsLead(object) != 0) {
        return;
    }
    scene_motion_play_with_item(object, 0, SCENE_MOTION_PLAY_LOOP);
    self->step = 9;
}
CLEAN_AS(func_02017e20, SceneMotion_Kind14Step8)

/* func_02017e00: kind 14's step 9: once func_02057bd4 gives 0, the motion is done. */
void SceneMotion_Kind14Step9(SceneMotion *self, u8 *object)
{
    (void) object;
    if (Obj020dd33c_IsBusy() == 0) {
        scene_motion_end14(self);
    }
}
CLEAN_AS(func_02017e00, SceneMotion_Kind14Step9)

/* func_02017dd8: kind 14's step 10: the motion is done when the body animation is on its frame
 * 0 (whole part). */
void SceneMotion_Kind14Step10(SceneMotion *self, u8 *object)
{
    u32 frame = *(const u32 *) scene_motion_part(object, SCENE_MOTION_OBJECT_BODY_FRAME);
    if (((frame << 4) >> 16) == 0) {
        scene_motion_end14(self);
    }
}
CLEAN_AS(func_02017dd8, SceneMotion_Kind14Step10)

/* func_02017d80: kind 14's step 11: when the body animation ends, animation 0x2a once and the
 * effect stops (step 12). */
void SceneMotion_Kind14Step11(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object)) {
        scene_motion_play(object, 0x2a, 0, SCENE_MOTION_PLAY_ONCE);
        if (self->effect != SCENE_MOTION_NO_EFFECT) {
            EffectSystem_EndHandle(self->effect);
        }
        self->step = 0xc;
    }
}
CLEAN_AS(func_02017d80, SceneMotion_Kind14Step11)

/* func_02017d14: kind 14's step 12: when the body animation ends, the first standard animation
 * loops (the held item takes action 0), func_02057cb8, and the motion is done. */
void SceneMotion_Kind14Step12(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object)) {
        scene_motion_play_with_item(object, 0, SCENE_MOTION_PLAY_LOOP);
        Obj020dd33c_Finish(object);
        scene_motion_end14(self);
    }
}
CLEAN_AS(func_02017d14, SceneMotion_Kind14Step12)

/* func_02017cf8: kind 14's step 13: once func_02057bf0 (1) says so, step 14. */
void SceneMotion_Kind14Step13(SceneMotion *self, u8 *object)
{
    (void) object;
    if (Obj020dd33c_InMode(1)) {
        self->step = 14;
    }
}
CLEAN_AS(func_02017cf8, SceneMotion_Kind14Step13)

/* func_02017cac: kind 14's step 14: once func_02057bf0 (1) says no, animation 0x2c once
 * (step 15). */
void SceneMotion_Kind14Step14(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_InMode(1) != 0) {
        return;
    }
    scene_motion_play(object, 0x2c, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
    self->step = 0xf;
}
CLEAN_AS(func_02017cac, SceneMotion_Kind14Step14)

/* func_02017c70: kind 14's step 15: when the body animation ends, func_02057c20 says so of the
 * object and the object takes it with 3, step 16. */
void SceneMotion_Kind14Step15(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object) && Obj020dd33c_Lead(object) && Obj020dd33c_SetActorMode(3, object)) {
        self->step = 0x10;
    }
}
CLEAN_AS(func_02017c70, SceneMotion_Kind14Step15)

/* func_02017c18: kind 14's step 16: unless func_02057bf0 (3), when the object at data_021c9350
 * takes the object with 4, animation 0x2d once (step 17). */
void SceneMotion_Kind14Step16(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_InMode(3) == 0 && Obj020dd33c_SetActorMode(4, object) != 0) {
        scene_motion_play(object, 0x2d, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
        self->step = 0x11;
    }
}
CLEAN_AS(func_02017c18, SceneMotion_Kind14Step16)

/* func_02017b44: kind 14's step 17: when the body animation ends, by what func_02057cf4 gives
 * (where the object needs to take the object with that number, nothing happens until it does):
 * 5: animation 0x2e once and sound 0x4f (step 5); 7: animation 0x2d in mode 3 (step 18); else
 * animation 0x24 loops and the motion is done. */
void SceneMotion_Kind14Step17(SceneMotion *self, u8 *object)
{
    if (!scene_motion_body_at_end(object)) {
        return;
    }
    int state = Obj020dd33c_Stage();
    if (state == 5) {
        if (Obj020dd33c_SetActorMode(5, object) == 0) {
            return;
        }
        scene_motion_play(object, 0x2e, data_020c80f8, SCENE_MOTION_PLAY_ONCE);
        scene_motion_sound(object, 0x4f);
        self->step = 5;
    } else if (state == 7) {
        if (Obj020dd33c_SetActorMode(7, object) == 0) {
            return;
        }
        scene_motion_play(object, 0x2d, data_020c80f8, SCENE_MOTION_PLAY_3);
        self->step = 0x12;
    } else {
        scene_motion_play(object, 0x24, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
        SceneMotion_SetDone(self, 1);
        self->step = SCENE_MOTION_KIND14_END;
    }
}
CLEAN_AS(func_02017b44, SceneMotion_Kind14Step17)

/* func_02017af0: kind 14's step 18: when the body animation ends and the object at
 * data_021c9350 takes the object with 2, the first standard animation loops (step 19). */
void SceneMotion_Kind14Step18(SceneMotion *self, u8 *object)
{
    if (scene_motion_body_at_end(object) && Obj020dd33c_SetActorMode(2, object) != 0) {
        scene_motion_play(object, 0, data_020c80f8, SCENE_MOTION_PLAY_LOOP);
        self->step = 0x13;
    }
}
CLEAN_AS(func_02017af0, SceneMotion_Kind14Step18)

/* func_02017ab4: kind 14's step 19: unless func_02057bf0 (2), func_02057b90 (9), and step 9
 * when func_02057c20 says so of the motion's `partner` and func_ov004_0222bf50 (overlay 4)
 * says so too. */
void SceneMotion_Kind14Step19(SceneMotion *self, u8 *object)
{
    SceneMotionArgs *args = SceneMotion_Args(self);
    if (Obj020dd33c_InMode(2) != 0) {
        return;
    }
    Obj020dd33c_SetStage(9, object);
    if (Obj020dd33c_Lead((void *) (uintptr_t) args->partner) != 0 && RoomPlayerActor_RequestItemBack() != 0) {
        self->step = 9;
    }
}
CLEAN_AS(func_02017ab4, SceneMotion_Kind14Step19)
