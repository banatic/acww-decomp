/* The motions of kinds 0 to 13 of a scene object, and kind 14's start (scene_motion_kinds.h). */
#include "scene_motion_kinds.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "held_item_link.h"
#include "ov004/member_pointer.h"
#include "scene_motion_core.h"
#include "sound.h"
#include "sound_emitter.h"
#include "speaker_anim.h"
#include "act_effects.h"
#include "obj_020dd33c.h"
#include "ov004/room_player_actor.h"
#include "player_actor_ops.h"
#include "scene_face.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object.h"
#include "scene_value_3aa.h"

static_assert(sizeof(SceneMotionPlan) == sizeof(SceneMotionArgs), "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, gesture) == 0x14, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, angle) == 0x18, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, word) == 0x1c, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, mode) == 0x20, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, item) == 0x22, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, partner) == 0x28, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, unk_2c) == 0x2c, "SceneMotionPlan layout");
static_assert(offsetof(SceneMotionPlan, variant) == 0x30, "SceneMotionPlan layout");
static_assert(sizeof(SceneMotionAct) == 0x1c, "SceneMotionAct layout");
static_assert(offsetof(SceneMotionAct, mode) == 0x18, "SceneMotionAct layout");

/* The motion's words past its step that kinds 5 to 8 keep (at 0x9c). */
typedef struct SceneMotionWork {
    s32 walk_mode;             /* 0x9c: kinds 5 and 6: the mover's mode for walking */
    s16 half_3ac;              /* 0xa0: kinds 5 and 6: what func_0201b350 is given */
    u8 unk_a2[2];              /* 0xa2 */
    const SceneMotionAct *act; /* 0xa4: kind 8's record, or null */
    u8 act_mode;               /* 0xa8: 1 while the record's first part plays once */
    u8 act_number;             /* 0xa9 */
    u8 unk_aa[2];              /* 0xaa */
    s32 effect;                /* 0xac: kinds 14 and 19 (scene_motion.h) */
    s32 gesture;               /* 0xb0: kind 7's */
} SceneMotionWork;

#define MOTION_KINDS_WORK 0x9c
static_assert(offsetof(SceneMotionWork, act) == 0xa4 - MOTION_KINDS_WORK, "SceneMotionWork layout");
static_assert(offsetof(SceneMotionWork, act_number) == 0xa9 - MOTION_KINDS_WORK, "SceneMotionWork layout");
static_assert(offsetof(SceneMotionWork, gesture) == 0xb0 - MOTION_KINDS_WORK, "SceneMotionWork layout");

/* The scene object's parts used here. */
#define MOTION_KINDS_OBJECT_ANGLE 0x8e        /* s16 */
#define MOTION_KINDS_OBJECT_SPEED 0x98        /* u32 */
#define MOTION_KINDS_OBJECT_FRAME_COUNT 0x18c /* fx32: the body animation's frame count */
#define MOTION_KINDS_OBJECT_FRAME 0x190       /* fx32: its frame */
#define MOTION_KINDS_OBJECT_BODY_MODE 0x19c   /* u8: its play mode */
#define MOTION_KINDS_OBJECT_ACT 0x2ac         /* reset by func_0201a020 for act 0 */
#define MOTION_KINDS_OBJECT_ANIM 0x334        /* SpeakerAnim */
#define MOTION_KINDS_OBJECT_MOVER 0x350
#define MOTION_KINDS_OBJECT_3AA 0x3aa         /* graded by func_0201b354 */
#define MOTION_KINDS_OBJECT_EFFECTS 0x420     /* the effect group */
#define MOTION_KINDS_OBJECT_EFFECTS_ACT 0x445 /* u8: the group's record number */
#define MOTION_KINDS_OBJECT_EMITTER 0x514     /* SoundEmitter */
#define MOTION_KINDS_OBJECT_HELD 0x628        /* HeldItemLink *, or null */

/* The object's vtable slots giving kind 11's two animations and act 0's word. */
#define MOTION_KINDS_SLOT_KIND11_FIRST 0x94
#define MOTION_KINDS_SLOT_KIND11_SECOND 0x98
#define MOTION_KINDS_SLOT_ACT0_WORD 0x9c

/* The mover's modes (func_0201b1a4). */
#define MOTION_KINDS_MOVER_STAND 0
#define MOTION_KINDS_MOVER_WALK 1
#define MOTION_KINDS_MOVER_WALK_2 2
#define MOTION_KINDS_MOVER_TURN 3

/* What func_0201b350 is given by most starts, and by the walks. */
#define MOTION_KINDS_HALF_STILL (-2)
#define MOTION_KINDS_HALF_WALK 1

/* The animations' play modes (SpeakerAnim_Play) and speed. */
#define MOTION_KINDS_PLAY_LOOP 0
#define MOTION_KINDS_PLAY_ONCE 1
#define MOTION_KINDS_PLAY_2 2
#define MOTION_KINDS_PLAY_3 3
#define MOTION_KINDS_SPEED 0x1000
#define MOTION_KINDS_SLOT_BODY 0

#define MOTION_KINDS_VOLUME 0x7f

/* The priority a walk's return to its start point is asked for with. */
#define MOTION_KINDS_RETURN_PRIORITY 1
#define MOTION_KINDS_KIND_1 1

/* The acts (data_020c8290) and the animation of a part that has none. */
#define MOTION_KINDS_ACTS 60
#define MOTION_KINDS_ACT_NONE 0x137

#define MOTION_KINDS_GESTURES 5

/* The steps past the runs' tables. */
#define MOTION_KINDS_KIND13_END 5
#define MOTION_KINDS_KIND13_STEPS 5

/* The standard word, and the origin. */
extern u16 data_020c80f8;
extern Vec3 data_021fbee8;

/* Kind 13's animations by `variant`, kind 7's gestures (animations and sounds), the acts. */
extern const u32 data_020c8198[];
extern const u32 data_020c81c4[];
extern const u16 data_020c81a8[];
extern SceneMotionAct data_020c8290[];

/* The runs' tables of steps: a guard word, the table, and the constants it is filled from. */
extern u32 data_021c14ec;
extern MemberPointer data_021c176c[];
extern const MemberPointer data_020d891c, data_020d8914, data_020d890c, data_020d860c, data_020d85dc;
extern u32 data_021c1538;
extern MemberPointer data_021c1564[];
extern const MemberPointer data_020d892c;
extern u32 data_021c1504;
extern MemberPointer data_021c154c[];
extern const MemberPointer data_020d8944;
extern u32 data_021c14f0;
extern MemberPointer data_021c1554[];
extern const MemberPointer data_020d854c;
extern u32 data_021c1548;
extern MemberPointer data_021c15cc[];
extern const MemberPointer data_020d86b4, data_020d8a64;
extern u32 data_021c1514;
extern MemberPointer data_021c15ac[];
extern const MemberPointer data_020d8a8c, data_020d8a84;

static SceneMotionPlan *motion_kinds_plan(SceneMotion *self)
{
    return (SceneMotionPlan *) (void *) SceneMotion_Args(self);
}

static SceneMotionWork *motion_kinds_work(SceneMotion *self)
{
    return (SceneMotionWork *) (void *) ((u8 *) self + MOTION_KINDS_WORK);
}

static void *motion_kinds_mover(u8 *object)
{
    return object + MOTION_KINDS_OBJECT_MOVER;
}

static SpeakerAnim *motion_kinds_anim(u8 *object)
{
    return (SpeakerAnim *) (void *) (object + MOTION_KINDS_OBJECT_ANIM);
}

static s16 motion_kinds_angle(u8 *object)
{
    return *(const s16 *) (object + MOTION_KINDS_OBJECT_ANGLE);
}

static HeldItemLink *motion_kinds_held(u8 *object)
{
    return *(HeldItemLink **) (object + MOTION_KINDS_OBJECT_HELD);
}

/* The whole frames of an fx32 frame of the body animation (bits 12 to 27). */
static u32 motion_kinds_whole(u8 *object, u32 offset)
{
    return (*(const u32 *) (object + offset) << 4) >> 16;
}

static int motion_kinds_body_at_end(u8 *object)
{
    return SpeakerAnim_BodyAtEnd(motion_kinds_anim(object), object);
}

static void motion_kinds_play(u8 *object, int number, int word, int mode)
{
    SpeakerAnim_Play(motion_kinds_anim(object), object, number, word, mode, MOTION_KINDS_SPEED, 0, MOTION_KINDS_SLOT_BODY);
}

/* The body animation with `word`, and the held item takes action 0 with the same word. */
static void motion_kinds_play_with_item(u8 *object, int number, int word, int mode)
{
    motion_kinds_play(object, number, word, mode);
    HeldItemLink *held = motion_kinds_held(object);
    if (held != NULL) {
        HeldItemLink_Action0(held, word, 0);
    }
}

/* The held item takes action 1 with `word`. */
static void motion_kinds_item_action1(u8 *object, int word)
{
    HeldItemLink *held = motion_kinds_held(object);
    if (held != NULL) {
        HeldItemLink_Action1(held, word, 0);
    }
}

static void motion_kinds_sound(u8 *object, int number)
{
    SoundEmitter_Play((SoundEmitter *) (void *) (object + MOTION_KINDS_OBJECT_EMITTER), number, MOTION_KINDS_VOLUME, 0);
}

static void motion_kinds_set_half(u8 *object, int value)
{
    SceneValue3aa_SetSecond((SceneValue3aa *) (void *) (object + MOTION_KINDS_OBJECT_3AA), value);
}

/* Both the mover's points at the origin. */
static void motion_kinds_points_at_origin(u8 *object)
{
    SceneMover_SetStart(motion_kinds_mover(object), &data_021fbee8);
    SceneMover_SetEnd(motion_kinds_mover(object), &data_021fbee8);
}

/* The mover's mode, with the plan's rate and word. */
static void motion_kinds_set_mode(u8 *object, int mode, int rate, int word)
{
    SceneMover_SetMode(motion_kinds_mover(object), object, mode, rate, word);
}

static int motion_kinds_facing(u8 *object)
{
    return motion_kinds_angle(object) == SceneMover_Angle(motion_kinds_mover(object));
}

/* The note says the kind and priority running. */
static void motion_kinds_note(SceneMotion *self)
{
    self->note_kind = (u8) self->kind;
    self->note_priority = (u8) self->priority;
}

/* The object's vtable slot at `slot`, called with the object. */
static int motion_kinds_slot(u8 *object, u32 slot)
{
    const u8 *vtable = *(const u8 *const *) object;
    u32 code = *(const u32 *) (vtable + slot);
    return ((int (*)(u8 *))(uintptr_t) code)(object);
}

/* A call through a step's member pointer. */
static void motion_kinds_call(const MemberPointer *member, SceneMotion *self, u8 *object)
{
    void *target = MemberPointer_Object(member, self);
    ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, target))(target, object);
}

/* ---- Kind 14's start */

/* func_02018568: kind 14's start: the object stands (the plan's word), the mover's points at
 * the origin; with `variant` 1 func_ov004_0222bf74 (overlay 4) is given the plan's item,
 * words 0x24, 0x2c and 0x30 and the object, and the run begins at step 13; else
 * func_02095a4c is given the same and the run begins at step 0. Returns 1. */
int SceneMotion_StartKind14(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, plan->word);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    if (plan->variant == 1) {
        RoomPlayerActor_RequestItemOut(&plan->item, (const int *) &plan->unk_24, &plan->unk_2c, (const int *) &plan->variant,
                                       (int) (uintptr_t) object);
        self->step = 13;
    } else {
        PlayerActorOps_RequestState30(&plan->item, (int *) &plan->unk_24, &plan->unk_2c, (int *) &plan->variant,
                                      (int) (uintptr_t) object);
        self->step = 0;
    }
    SceneMotion_SetDone(self, 0);
    return 1;
}
CLEAN_AS(func_02018568, SceneMotion_StartKind14)

/* ---- Kind 13: the exchange */

/* func_0201860c: kind 13's after-step: nothing. */
void SceneMotion_Kind13After(void) {}
CLEAN_AS(func_0201860c, SceneMotion_Kind13After)

/* func_02018610: kind 13's run, by step. */
void SceneMotion_RunKind13(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d891c, /* SceneMotion_Kind13Step0 */
        &data_020d8914, /* SceneMotion_Kind13Step1 */
        &data_020d890c, /* SceneMotion_Kind13Step2 */
        &data_020d860c, /* SceneMotion_Kind13Step3 */
        &data_020d85dc, /* SceneMotion_Kind13Step4 */
    };
    MemberTable_InitOnce(&data_021c14ec, data_021c176c, steps, MOTION_KINDS_KIND13_STEPS);
    if (self->step < MOTION_KINDS_KIND13_STEPS) {
        motion_kinds_call(&data_021c176c[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02018610Ei, SceneMotion_RunKind13)

/* func_020186b0: kind 13's step 4: unless func_02057bf0 (1), func_02057b90 (9), and step 2 when
 * func_02057c20 says so of the plan's `partner` and func_ov004_0222bf50 (overlay 4) says so
 * too. While func_02057bf0 (1) says yes, sound 0x63 on the body animation's whole frame 8. */
void SceneMotion_Kind13Step4(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_InMode(1) == 0) {
        SceneMotionPlan *plan = motion_kinds_plan(self);
        Obj020dd33c_SetStage(9, object);
        if (Obj020dd33c_Lead((void *) (uintptr_t) plan->partner) != 0 && RoomPlayerActor_RequestItemBack() != 0) {
            self->step = 2;
        }
    } else if (motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME) == 8) {
        motion_kinds_sound(object, 0x63);
    }
}
CLEAN_AS(func_020186b0, SceneMotion_Kind13Step4)

/* func_02018714: kind 13's step 3: on the body animation's whole frame 0x17, the object at
 * data_021c9350 takes the object with 2 (func_02057d0c), and step 4. */
void SceneMotion_Kind13Step3(SceneMotion *self, u32 *object)
{
    u8 *bytes = (u8 *) object;
    if (motion_kinds_whole(bytes, MOTION_KINDS_OBJECT_FRAME) == 0x17) {
        Obj020dd33c_SetActorMode(2, bytes);
        self->step = 4;
    }
}
CLEAN_AS(func_02018714, SceneMotion_Kind13Step3)

/* func_0201873c: kind 13's step 2: once func_02057bd4 says no, the motion is done (step 5). */
void SceneMotion_Kind13Step2(SceneMotion *self, u8 *object)
{
    (void) object;
    if (Obj020dd33c_IsBusy() != 0) {
        return;
    }
    SceneMotion_SetDone(self, 1);
    self->step = MOTION_KINDS_KIND13_END;
}
CLEAN_AS(func_0201873c, SceneMotion_Kind13Step2)

/* func_0201875c: kind 13's step 1: once func_02057d34 says no of the object, the first standard
 * animation loops (and the held item takes action 0), and step 2. */
void SceneMotion_Kind13Step1(SceneMotion *self, u8 *object)
{
    if (Obj020dd33c_IsLead(object) != 0) {
        return;
    }
    motion_kinds_play_with_item(object, 0, data_020c80f8, MOTION_KINDS_PLAY_LOOP);
    self->step = 2;
}
CLEAN_AS(func_0201875c, SceneMotion_Kind13Step1)

/* func_020187b8: kind 13's step 0: when the body animation ends and func_02095a28 says yes,
 * animation 0x23 loops (and the held item takes action 0), and step 1. Until the end, sound
 * 0x63 on the body animation's whole frame 8. */
void SceneMotion_Kind13Step0(SceneMotion *self, u8 *object)
{
    if (motion_kinds_body_at_end(object)) {
        if (PlayerActorOps_RequestState32() != 0) {
            motion_kinds_play_with_item(object, 0x23, data_020c80f8, MOTION_KINDS_PLAY_LOOP);
            self->step = 1;
        }
    } else if (motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME) == 8) {
        motion_kinds_sound(object, 0x63);
    }
}
CLEAN_AS(func_020187b8, SceneMotion_Kind13Step0)

/* func_02018844: kind 13's start: the object stands (the plan's word), the mover's points at
 * the origin; the animation of `variant` (data_020c8198) once (and the held item takes action
 * 0), sound 0x4f, the exchange (func_02057d58 with the plan's item, words 0x24, 0x2c, 0x30, the
 * object and `partner`), the object at data_021c9350 takes the object with 1, and the run
 * begins at step 4 with `variant` 1, else at step 0. Returns 1.
 * REQUIRES: `variant` is below 4 (data_020c8198's entries). */
int SceneMotion_StartKind13(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, plan->word);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    motion_kinds_play_with_item(object, (int) data_020c8198[(u32) plan->variant], data_020c80f8, MOTION_KINDS_PLAY_ONCE);
    motion_kinds_sound(object, 0x4f);
    Obj020dd33c_Start(&plan->item, plan->unk_24, plan->unk_2c, plan->variant, (Actor *) (void *) object,
                      (Actor *) (uintptr_t) plan->partner);
    Obj020dd33c_SetActorMode(1, object);
    SceneMotion_SetDone(self, 0);
    self->step = plan->variant == 1 ? 4 : 0;
    return 1;
}
CLEAN_AS(func_02018844, SceneMotion_StartKind13)

/* ---- Kind 12: an animation */

/* func_02018934: kind 12's after-step: the motion is done when the body animation is back on
 * its whole frame 0 (play modes 0 and 2) or at its end (modes 1 and 3). */
void SceneMotion_Kind12After(SceneMotion *self, u8 *object)
{
    int finished = 0;
    switch (object[MOTION_KINDS_OBJECT_BODY_MODE]) {
        case MOTION_KINDS_PLAY_LOOP:
        case MOTION_KINDS_PLAY_2:
            if (motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME) == 0) {
                finished = 1;
            }
            break;
        case MOTION_KINDS_PLAY_ONCE:
        case MOTION_KINDS_PLAY_3:
            finished = motion_kinds_body_at_end(object);
            break;
        default:
            break;
    }
    if (finished) {
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02018934, SceneMotion_Kind12After)

/* func_02018990: kind 12's start: the object stands, the mover's points at the origin, and the
 * plan's animation plays in its mode from its frame, with its word; the note says so. Returns
 * 1. */
int SceneMotion_StartKind12(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, data_020c80f8);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    SpeakerAnim_Play(motion_kinds_anim(object), object, (int) plan->animation, plan->word, plan->mode, MOTION_KINDS_SPEED,
                     plan->frame, MOTION_KINDS_SLOT_BODY);
    motion_kinds_note(self);
    SceneMotionNote_PackAnimation(self->note, (u8) plan->animation, plan->mode, (u8) plan->word, plan->frame);
    SceneMotion_SetDone(self, 0);
    return 1;
}
CLEAN_AS(func_02018990, SceneMotion_StartKind12)

/* ---- Kind 11: the object's two animations */

/* func_02018a3c: kind 11's after-step: from step 1, unless done, the motion is done when the
 * body animation's whole frame is at least its whole frame count less 0x1000.
 * BUG: whole frames are compared with a whole count less 0x1000 (a frame in fx32), so for any
 * animation shorter than 0x1000 frames the motion is done on the first check; one frame from
 * the end was likely meant. */
void SceneMotion_Kind11After(SceneMotion *self, u8 *object)
{
    if (self->step < 1 || SceneMotion_IsDone(self) != 0) {
        return;
    }
    s32 frame = (s32) motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME);
    s32 count = (s32) motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME_COUNT);
#ifdef BUGFIX
    if (frame < count - 1) {
        return;
    }
#else
    if (frame < count - 0x1000) {
        return;
    }
#endif
    SceneMotion_SetDone(self, 1);
}
CLEAN_AS(func_02018a3c, SceneMotion_Kind11After)

/* func_02018a8c: kind 11's run, by step. */
void SceneMotion_RunKind11(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d892c, /* SceneMotion_Kind11Step0 */
    };
    MemberTable_InitOnce(&data_021c1538, data_021c1564, steps, 1);
    if (self->step < 1) {
        motion_kinds_call(&data_021c1564[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02018a8cEPv, SceneMotion_RunKind11)

/* func_02018af4: kind 11's step 0: when the body animation ends, the object's second animation
 * (its vtable slot 0x98) loops (and the held item takes action 0), and step 1. */
void SceneMotion_Kind11Step0(SceneMotion *self, u8 *object)
{
    if (!motion_kinds_body_at_end(object)) {
        return;
    }
    int animation = motion_kinds_slot(object, MOTION_KINDS_SLOT_KIND11_SECOND);
    motion_kinds_play_with_item(object, animation, data_020c80f8, MOTION_KINDS_PLAY_LOOP);
    self->step = 1;
}
CLEAN_AS(func_02018af4, SceneMotion_Kind11Step0)

/* func_02018b60: kind 11's start: the object's first animation (its vtable slot 0x94); the
 * object stands (the plan's word), the mover's points at the origin, and the animation plays
 * once (and the held item takes action 0). Step 0. Returns 0. */
int SceneMotion_StartKind11(SceneMotion *self, u8 *object)
{
    int animation = motion_kinds_slot(object, MOTION_KINDS_SLOT_KIND11_FIRST);
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, plan->word);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    motion_kinds_play_with_item(object, animation, data_020c80f8, MOTION_KINDS_PLAY_ONCE);
    self->step = 0;
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_02018b60, SceneMotion_StartKind11)

/* ---- Kind 10: animations 0x77 and 0x78 */

/* func_02018c10: kind 10's after-step: from step 1, the motion is done at the body animation's
 * end. */
void SceneMotion_Kind10After(SceneMotion *self, u8 *object)
{
    if (self->step >= 1 && motion_kinds_body_at_end(object)) {
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02018c10, SceneMotion_Kind10After)

/* func_02018c3c: kind 10's run, by step. */
void SceneMotion_RunKind10(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d8944, /* SceneMotion_Kind10Step0 */
    };
    MemberTable_InitOnce(&data_021c1504, data_021c154c, steps, 1);
    if (self->step < 1) {
        motion_kinds_call(&data_021c154c[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02018c3cEPv, SceneMotion_RunKind10)

/* func_02018ca4: kind 10's step 0: when the body animation ends, animation 0x78 once, and
 * step 1. */
void SceneMotion_Kind10Step0(SceneMotion *self, u8 *object)
{
    if (motion_kinds_body_at_end(object)) {
        motion_kinds_play(object, 0x78, data_020c80f8, MOTION_KINDS_PLAY_ONCE);
        self->step = 1;
    }
}
CLEAN_AS(func_02018ca4, SceneMotion_Kind10Step0)

/* func_02018cf0: kind 10's start: the object stands, the mover's points at the origin,
 * animation 0x77 once (both with the plan's word), and SoundSys_StartOnHandle40B (0xa0). Step
 * 0. Unlike the other starts, it returns nothing. */
void SceneMotion_StartKind10(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, plan->word);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    motion_kinds_play(object, 0x77, plan->word, MOTION_KINDS_PLAY_ONCE);
    SceneMotion_SetDone(self, 0);
    SoundSys_StartOnHandle40B(0xa0);
    self->step = 0;
}
CLEAN_AS(func_02018cf0, SceneMotion_StartKind10)

/* ---- Kind 9: animation 0xd8 */

/* func_02018d7c: kind 9's run: the motion is done when the body animation is on its whole
 * frame 0 and func_0201b354 grades the object's member at 0x3aa 0 (below 100). */
void SceneMotion_RunKind9(SceneMotion *self, u8 *object)
{
    if (motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME) != 0) {
        return;
    }
    if (SceneValue3aa_Grade((SceneValue3aa *) (void *) (object + MOTION_KINDS_OBJECT_3AA)) != 0) {
        return;
    }
    SceneMotion_SetDone(self, 1);
}
CLEAN_AS(func_02018d7c, SceneMotion_RunKind9)

/* func_02018db0: kind 9's start: the object stands and animation 0xd8 loops (both with the
 * plan's word), the mover's points at the origin. Returns 0. */
int SceneMotion_StartKind9(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, plan->word);
    motion_kinds_play(object, 0xd8, plan->word, MOTION_KINDS_PLAY_LOOP);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_02018db0, SceneMotion_StartKind9)

/* ---- Kind 8: an act */

/* func_02018e30: kind 8's run. While the act's first part plays once, at its end: the second
 * part's animation loops (and the held item takes action 0) and its effects start (the effect
 * group's record number set again), or, when the second part has none (0x137), the motion is
 * done. Otherwise the motion is done when the first part's animation is the first standard one
 * and the body animation is on its whole frame 0. */
void SceneMotion_RunKind8(SceneMotion *self, u8 *object)
{
    SceneMotionWork *work = motion_kinds_work(self);
    const SceneMotionAct *act = work->act;
    if (act == NULL) {
        return;
    }
    if (work->act_mode == MOTION_KINDS_PLAY_ONCE) {
        if (!motion_kinds_body_at_end(object)) {
            return;
        }
        s32 second = (s32) work->act->part[1].animation;
        if (second < MOTION_KINDS_ACT_NONE) {
            motion_kinds_play_with_item(object, second, data_020c80f8, MOTION_KINDS_PLAY_LOOP);
            object[MOTION_KINDS_OBJECT_EFFECTS_ACT] = work->act_number;
            ActEffects_StartPart((ActEffects *) (void *) (object + MOTION_KINDS_OBJECT_EFFECTS),
                                 (SceneMotionActPart *) work->act, 1);
            work->act_mode = MOTION_KINDS_PLAY_LOOP;
        } else if (second == MOTION_KINDS_ACT_NONE) {
            SceneMotion_SetDone(self, 1);
        }
    } else if (act->part[0].animation == 0 && motion_kinds_whole(object, MOTION_KINDS_OBJECT_FRAME) == 0) {
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02018e30, SceneMotion_RunKind8)

/* func_02018f08: kind 8's start: the plan's act (0 past the 60 acts); the first part's
 * animation plays in the act's mode (and the held item takes action 0) and its effects start
 * in the object's effect group, whose record number is set. For act 0 the object's member at
 * 0x2ac is reset first (func_0201a020) and the word comes from the object's vtable slot 0x9c,
 * else it is the standard word. Returns 1. */
int SceneMotion_StartKind8(SceneMotion *self, u8 *object)
{
    SceneMotionWork *work = motion_kinds_work(self);
    u8 number = motion_kinds_plan(self)->act;
    int word = data_020c80f8;
    if (number >= MOTION_KINDS_ACTS) {
        number = 0;
    }
    work->act_number = number;
    if (number == 0) {
        SceneFace_ResetTimer((SceneFace *) (void *) (object + MOTION_KINDS_OBJECT_ACT));
        word = motion_kinds_slot(object, MOTION_KINDS_SLOT_ACT0_WORD);
    }
    work->act = &data_020c8290[number];
    work->act_mode = work->act->mode;
    motion_kinds_play_with_item(object, (int) work->act->part[0].animation, word, work->act_mode);
    object[MOTION_KINDS_OBJECT_EFFECTS_ACT] = number;
    ActEffects_StartPart((ActEffects *) (void *) (object + MOTION_KINDS_OBJECT_EFFECTS), (SceneMotionActPart *) work->act, 0);
    SceneMotion_SetDone(self, 0);
    return 1;
}
CLEAN_AS(func_02018f08, SceneMotion_StartKind8)

/* func_02018fdc: act `number`'s record, or null past the 60 acts (field actors' state 0x14
 * plays them too). */
SceneMotionAct *SceneMotion_Act(u32 number)
{
    if (number < MOTION_KINDS_ACTS) {
        return &data_020c8290[number];
    }
    return NULL;
}
CLEAN_AS(func_02018fdc, SceneMotion_Act)

/* ---- Kind 7: a gesture */

/* func_02018ff4: kind 7's after-step: from step 1, unless done, the motion is done at the body
 * animation's end. */
void SceneMotion_Kind7After(SceneMotion *self, u8 *object)
{
    if (self->step < 1 || SceneMotion_IsDone(self) != 0) {
        return;
    }
    if (motion_kinds_body_at_end(object)) {
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02018ff4, SceneMotion_Kind7After)

/* func_02019030: kind 7's run, by step. */
void SceneMotion_RunKind7(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d854c, /* SceneMotion_Kind7Step0 */
    };
    MemberTable_InitOnce(&data_021c14f0, data_021c1554, steps, 1);
    if (self->step < 1) {
        motion_kinds_call(&data_021c1554[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02019030EPv, SceneMotion_RunKind7)

/* func_02019098: kind 7's step 0: once the object faces the mover's angle, the gesture (0 from
 * 5 on): its animation once (and the held item takes action 0) and its sound, and step 1.
 * REQUIRES: the gesture is not negative (it is not checked, and the tables would be read
 * before their start). */
void SceneMotion_Kind7Step0(SceneMotion *self, u8 *object)
{
    SceneMotionWork *work = motion_kinds_work(self);
    if (!motion_kinds_facing(object)) {
        return;
    }
    if (work->gesture >= MOTION_KINDS_GESTURES) {
        work->gesture = 0;
    }
    motion_kinds_play_with_item(object, (int) data_020c81c4[work->gesture], data_020c80f8, MOTION_KINDS_PLAY_ONCE);
    motion_kinds_sound(object, data_020c81a8[work->gesture]);
    self->step = 1;
}
CLEAN_AS(func_02019098, SceneMotion_Kind7Step0)

/* func_02019144: kind 7's start: the object turns in place to the plan's angle (with its rate
 * and word), the held item takes action 1 with the plan's word, and the gesture is the plan's.
 * Returns 0. */
int SceneMotion_StartKind7(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_TURN, plan->rate, plan->word);
    SceneMover_SetAngle(motion_kinds_mover(object), plan->angle);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    motion_kinds_item_action1(object, plan->word);
    motion_kinds_work(self)->gesture = plan->gesture;
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_02019144, SceneMotion_StartKind7)

/* ---- Kinds 5 and 6: walking to a point */

/* func_020191b4: kind 6's start: SceneMotion_StartWalkTo with mode 2 and 2. */
int SceneMotion_StartKind6(SceneMotion *self, u8 *object)
{
    return SceneMotion_StartWalkTo(self, object, MOTION_KINDS_MOVER_WALK_2, 2);
}
CLEAN_AS(func_020191b4, SceneMotion_StartKind6)

/* func_020191c8: kind 5's start: SceneMotion_StartWalkTo with mode 1 and 1. */
int SceneMotion_StartKind5(SceneMotion *self, u8 *object)
{
    return SceneMotion_StartWalkTo(self, object, MOTION_KINDS_MOVER_WALK, 1);
}
CLEAN_AS(func_020191c8, SceneMotion_StartKind5)

/* func_020191dc: the run of kinds 5 and 6, by step. */
void SceneMotion_RunKind5(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d86b4, /* SceneMotion_Kind5Step0 */
        &data_020d8a64, /* SceneMotion_Kind5Step1 */
    };
    MemberTable_InitOnce(&data_021c1548, data_021c15cc, steps, 2);
    if (self->step < 2) {
        motion_kinds_call(&data_021c15cc[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_020191dcEi, SceneMotion_RunKind5)

/* func_0201924c: step 1 of kinds 5 and 6, walking (the mover's angle brought up to date,
 * func_0201b188). At the end point, the motion is done when the mover's two points are the
 * same; else, when the end point is more than a quarter turn away, the object turns to it again
 * (step 0, the held item takes action 1).
 * QUIRK: at the end point with the two points different, the end point is set to itself. */
void SceneMotion_Kind5Step1(SceneMotion *self, u8 *object)
{
    void *mover = motion_kinds_mover(object);
    Vec3 *end = SceneMover_EndPoint(mover);
    SceneMover_AimAtEnd(mover, object);
    if (SceneMover_Reached(mover, object, 0) != 0) {
        if (SceneMover_PointsDiffer(mover) != 0) {
            SceneMover_SetEnd(mover, end);
        } else {
            SceneMotion_SetDone(self, 1);
        }
        return;
    }
    s16 angle;
    if (SceneObject_FacesPoint(object, &angle, end) == 0) {
        int word = data_020c80f8;
        int rate = SceneMover_TurnRate(mover);
        SceneMover_SetMode(mover, object, MOTION_KINDS_MOVER_TURN, rate, word);
        SceneMover_SetAngle(mover, angle);
        self->step = 0;
        *(u32 *) (object + MOTION_KINDS_OBJECT_SPEED) = 0;
        motion_kinds_item_action1(object, word);
    }
}
CLEAN_AS(func_0201924c, SceneMotion_Kind5Step1)

/* func_02019304: step 0 of kinds 5 and 6, turning: within a quarter turn of the mover's angle,
 * the object walks (the kind's mode, at the mover's rate) and step 1. */
void SceneMotion_Kind5Step0(SceneMotion *self, u8 *object)
{
    void *mover = motion_kinds_mover(object);
    if (SceneObject_IsWithinQuarterTurn((s16) (u16) ((u32) SceneMover_Angle(mover) - (u32) motion_kinds_angle(object))) == 0) {
        return;
    }
    int mode = motion_kinds_work(self)->walk_mode;
    SceneMover_SetMode(mover, object, mode, SceneMover_TurnRate(mover), data_020c80f8);
    self->step = 1;
}
CLEAN_AS(func_02019304, SceneMotion_Kind5Step0)

/* func_0201935c: the start of kinds 5 and 6: the mover's points are the plan's (on the ground
 * plane), and `mode` and `half_3ac` are kept. When the end point is within a quarter turn
 * (func_0201c3b0), the object walks in `mode` (step 1); else it turns to it first (step 0).
 * Either with the plan's rate and word; the held item takes action 1 and func_0201b350 is
 * given `half_3ac`. Returns 0. */
int SceneMotion_StartWalkTo(SceneMotion *self, u8 *object, int mode, int half_3ac)
{
    SceneMotionWork *work = motion_kinds_work(self);
    SceneMotionPlan *plan = motion_kinds_plan(self);
    Vec3 from = {plan->from_x, 0, plan->from_z};
    Vec3 to = {plan->to_x, 0, plan->to_z};
    void *mover = motion_kinds_mover(object);

    work->walk_mode = mode;
    work->half_3ac = (s16) half_3ac;
    SceneMover_SetStart(mover, &from);
    SceneMover_SetEnd(mover, &to);
    s16 angle;
    if (SceneObject_FacesPoint(object, &angle, SceneMover_EndPoint(mover)) != 0) {
        motion_kinds_set_mode(object, work->walk_mode, plan->rate, plan->word);
        self->step = 1;
    } else {
        motion_kinds_set_mode(object, MOTION_KINDS_MOVER_TURN, plan->rate, plan->word);
        SceneMover_SetAngle(mover, angle);
        *(u32 *) (object + MOTION_KINDS_OBJECT_SPEED) = 0;
        self->step = 0;
    }
    motion_kinds_item_action1(object, data_020c80f8);
    motion_kinds_set_half(object, work->half_3ac);
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_0201935c, SceneMotion_StartWalkTo)

/* ---- Kind 4: turning, then walking */

/* func_02019450: kind 4's run, by step. */
void SceneMotion_RunKind4(SceneMotion *self, u8 *object)
{
    static const MemberPointer *const steps[] = {
        &data_020d8a8c, /* SceneMotion_Kind4Step0 */
        &data_020d8a84, /* SceneMotion_Kind4Step1 */
    };
    MemberTable_InitOnce(&data_021c1514, data_021c15ac, steps, 2);
    if (self->step < 2) {
        motion_kinds_call(&data_021c15ac[self->step], self, object);
    }
}
CLEAN_AS(_ZN12Obj_020d8bd413func_02019450Ei, SceneMotion_RunKind4)

/* func_020194c0: kind 4's step 1: kind 1's run. */
void SceneMotion_Kind4Step1(SceneMotion *self, u8 *object)
{
    SceneMotion_RunKind1(self, object);
}
CLEAN_AS(func_020194c0, SceneMotion_Kind4Step1)

/* func_020194c8: kind 4's step 0: once the object faces the mover's angle, kind 1's start, and
 * step 1. */
void SceneMotion_Kind4Step0(SceneMotion *self, u8 *object)
{
    if (motion_kinds_facing(object)) {
        SceneMotion_StartKind1(self, object);
        self->step = 1;
    }
}
CLEAN_AS(func_020194c8, SceneMotion_Kind4Step0)

/* func_020194fc: kind 4's start: the object turns in place to the plan's angle (with its rate
 * and word) and the mover's points are the plan's (on the ground plane); the held item takes
 * action 1. Returns 0. */
int SceneMotion_StartKind4(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    Vec3 from = {plan->from_x, 0, plan->from_z};
    Vec3 to = {plan->to_x, 0, plan->to_z};
    void *mover = motion_kinds_mover(object);

    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_TURN, plan->rate, plan->word);
    SceneMover_SetStart(mover, &from);
    SceneMover_SetEnd(mover, &to);
    SceneMover_SetAngle(mover, plan->angle);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    motion_kinds_item_action1(object, data_020c80f8);
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_020194fc, SceneMotion_StartKind4)

/* ---- Kind 3: turning */

/* func_02019594: kind 3's run: once the object faces the mover's angle, it stands (the plan's
 * word) and the motion is done. */
void SceneMotion_RunKind3(SceneMotion *self, u8 *object)
{
    if (motion_kinds_facing(object)) {
        motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, motion_kinds_plan(self)->word);
        SceneMotion_SetDone(self, 1);
    }
}
CLEAN_AS(func_02019594, SceneMotion_RunKind3)

/* func_020195d8: kind 3's start: the object turns in place to the plan's angle (with its rate
 * and word), the mover's points at the origin, the held item takes action 1; the note says so.
 * Returns 0. */
int SceneMotion_StartKind3(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_TURN, plan->rate, plan->word);
    SceneMover_SetAngle(motion_kinds_mover(object), plan->angle);
    motion_kinds_points_at_origin(object);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    motion_kinds_item_action1(object, data_020c80f8);
    motion_kinds_note(self);
    SceneMotionNote_PackTurn(self->note, (u16) plan->rate, (u16) plan->angle, (char) plan->word);
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_020195d8, SceneMotion_StartKind3)

/* ---- Kinds 1 and 2: walking a path */

/* The run of kinds 1 and 2 (the mover's angle brought up to date, func_0201b188): at the end
 * point, when the mover's two points differ, kind 1 is asked for at priority 1 with the plan's
 * start point as both its points; else the motion is done. */
static void motion_kinds_run_path(SceneMotion *self, u8 *object)
{
    void *mover = motion_kinds_mover(object);
    SceneMover_AimAtEnd(mover, object);
    if (SceneMover_Reached(mover, object, 0) == 0) {
        return;
    }
    if (SceneMover_PointsDiffer(mover) != 0) {
        SceneMotionPlan *plan = motion_kinds_plan(self);
        SceneMotion_Request(self, MOTION_KINDS_KIND_1, MOTION_KINDS_RETURN_PRIORITY, plan->from_x, plan->from_z, 0, 0, 0, 0,
                            data_020c80f8, 0);
    } else {
        SceneMotion_SetDone(self, 1);
    }
}

/* The start of kinds 1 and 2: the mover's points are the plan's (on the ground plane), the
 * object walks in `mode` (with the plan's rate and word), the held item takes action 1; the
 * note says so. Returns 0. */
static int motion_kinds_start_path(SceneMotion *self, u8 *object, int mode)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    Vec3 from = {plan->from_x, 0, plan->from_z};
    Vec3 to = {plan->to_x, 0, plan->to_z};

    SceneMover_SetStart(motion_kinds_mover(object), &from);
    SceneMover_SetEnd(motion_kinds_mover(object), &to);
    motion_kinds_set_mode(object, mode, plan->rate, plan->word);
    motion_kinds_set_half(object, MOTION_KINDS_HALF_WALK);
    motion_kinds_item_action1(object, data_020c80f8);
    motion_kinds_note(self);
    SceneMotionNote_PackPath(self->note, plan->from_x, plan->from_z, plan->to_x, plan->to_z, plan->rate, plan->word);
    SceneMotion_SetDone(self, 0);
    return 0;
}

/* func_02019678: kind 2's run (as kind 1's).
 * QUIRK: the walk back to the start point is kind 1, in mode 1. */
void SceneMotion_RunKind2(SceneMotion *self, u8 *object)
{
    motion_kinds_run_path(self, object);
}
CLEAN_AS(func_02019678, SceneMotion_RunKind2)

/* func_020196e8: kind 2's start: the path in mode 2. */
int SceneMotion_StartKind2(SceneMotion *self, u8 *object)
{
    return motion_kinds_start_path(self, object, MOTION_KINDS_MOVER_WALK_2);
}
CLEAN_AS(func_020196e8, SceneMotion_StartKind2)

/* func_02019794: kind 1's run. */
void SceneMotion_RunKind1(SceneMotion *self, u8 *object)
{
    motion_kinds_run_path(self, object);
}
CLEAN_AS(func_02019794, SceneMotion_RunKind1)

/* func_02019804: kind 1's start: the path in mode 1. */
int SceneMotion_StartKind1(SceneMotion *self, u8 *object)
{
    return motion_kinds_start_path(self, object, MOTION_KINDS_MOVER_WALK);
}
CLEAN_AS(func_02019804, SceneMotion_StartKind1)

/* ---- Kind 0: standing */

/* func_020198b0: kind 0's run: the motion is done. */
void SceneMotion_RunKind0(SceneMotion *self, u8 *object)
{
    (void) object;
    SceneMotion_SetDone(self, 1);
}
CLEAN_AS(func_020198b0, SceneMotion_RunKind0)

/* func_020198bc: kind 0's start: the object stands (the plan's word) facing its own angle, the
 * mover's points at the origin, the held item takes action 0; the note says so. Returns 0. */
int SceneMotion_StartKind0(SceneMotion *self, u8 *object)
{
    SceneMotionPlan *plan = motion_kinds_plan(self);
    void *mover = motion_kinds_mover(object);
    motion_kinds_set_mode(object, MOTION_KINDS_MOVER_STAND, 0, plan->word);
    motion_kinds_points_at_origin(object);
    SceneMover_SetAngle(mover, motion_kinds_angle(object));
    motion_kinds_set_half(object, MOTION_KINDS_HALF_STILL);
    HeldItemLink *held = motion_kinds_held(object);
    if (held != NULL) {
        HeldItemLink_Action0(held, data_020c80f8, 0);
    }
    motion_kinds_note(self);
    SceneMotion_SetDone(self, 0);
    return 0;
}
CLEAN_AS(func_020198bc, SceneMotion_StartKind0)
