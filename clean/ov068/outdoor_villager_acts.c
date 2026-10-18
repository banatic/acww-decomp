/* Behaviours 17 to 23 of a villager out walking in the town (outdoor_villager_acts.h). */
#include "outdoor_villager_acts.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/frame_ctrl.h"
#include "main/held_item_link.h"
#include "main/obj_020d8c64.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/session_players.h"
#include "main/sound_emitter.h"
#include "main/speaker_anim.h"
#include "main/villager_entry.h"
#include "main/villager_mood.h"
#include "main/villager_scene_held.h"
#include "main/villager_scene_object.h"
#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "outdoor_villager_watch.h"
#include "ov003/tile_event.h"
#include "outdoor_villager_bonds.h"
#include "outdoor_villager_walks.h"

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* An angle: within it either way of facing this console's player, behaviour 19 plays its
 * second animation. */
extern s16 data_020c80f0;

/* The updates' step tables (each filled once, bit 0 of its guard), and the member pointers
 * they are filled from. */
extern u32 data_ov068_02278288;
extern MemberPointer data_ov068_0227836c[2];
extern const MemberPointer data_ov068_02276f78, data_ov068_02277030;
extern u32 data_ov068_02278294;
extern MemberPointer data_ov068_0227830c[2];
extern const MemberPointer data_ov068_02277170, data_ov068_02276e40;
extern u32 data_ov068_022782a0;
extern MemberPointer data_ov068_022783c4[3];
extern const MemberPointer data_ov068_02276ff8, data_ov068_02277058, data_ov068_02277088;
extern u32 data_ov068_022782ac;
extern MemberPointer data_ov068_0227833c[2];
extern const MemberPointer data_ov068_02276ee0, data_ov068_02276f48;
extern u32 data_ov068_02278298;
extern MemberPointer data_ov068_02278394[3];
extern const MemberPointer data_ov068_02276e50, data_ov068_02276e68, data_ov068_02276e90;
extern u32 data_ov068_02278278;
extern MemberPointer data_ov068_022782c4[1];
extern const MemberPointer data_ov068_022770b8;
extern u32 data_ov068_0227826c;
extern MemberPointer data_ov068_02278424[5];
extern const MemberPointer data_ov068_02277020, data_ov068_02277050, data_ov068_02277070, data_ov068_02277080,
    data_ov068_02277098;

/* The motions' kinds and requests (main's scene_motion_kinds.h). */
#define ACTS_MOTION_TURN 3 /* turn in place to the angle, then stand */
#define ACTS_MOTION_ACT 8  /* an act of the table data_020c8290 */
#define ACTS_PRIORITY 1
/* Behaviour 23's act, and the frames before it may end. */
#define ACTS_ACT_23 0x1a
#define ACTS_WAIT_23 20
/* The frames behaviours 19 and 21 wait standing. */
#define ACTS_WAIT_STANDING 40
/* What a reaction's talk's end sets: the frames at 0xf4 and at `hold_3a`. */
#define ACTS_REACTION_FRAMES 1200
/* The mood asked for when a reaction's talk ends (VillagerMood_Ask's which and units). */
#define ACTS_MOOD_WHICH 4
#define ACTS_MOOD_UNITS 1
/* Behaviour 19's animations and the start that makes the third reaction 1. */
#define ACTS_ANIM_19 0xeb
#define ACTS_ANIM_19_FACING 0xec
#define ACTS_STRIKES 3
/* Behaviour 18's animations, effects, ground attribute and sound. */
#define ACTS_ANIM_18 0x12a
#define ACTS_ANIM_18_HOLDING 0x12b
#define ACTS_EFFECT_18 0x90
#define ACTS_EFFECT_18_GROUND 0x91
#define ACTS_GROUND_18 0x13
#define ACTS_SOUND_18 0x7e9
#define ACTS_SOUND_VOLUME 0x7f
/* The object's flag behaviour 18 sets (0x4e8). */
#define ACTS_FLAG_18 2
/* The effect handle when there is none (0xa00). */
#define ACTS_NO_EFFECT (-1)

static u8 *acts_at(u8 *villager, u32 offset)
{
    return villager + offset;
}

static SceneMotion *acts_motion(u8 *villager)
{
    return (SceneMotion *) (void *) acts_at(villager, OUTDOOR_VILLAGER_MOTION);
}

static SceneAction *acts_action(u8 *villager)
{
    return (SceneAction *) (void *) acts_at(villager, OUTDOOR_VILLAGER_ACTION);
}

static SpeakerAnim *acts_anim(u8 *villager)
{
    return (SpeakerAnim *) (void *) acts_at(villager, OUTDOOR_VILLAGER_ANIM);
}

static VillagerMood *acts_mood(u8 *villager)
{
    return (VillagerMood *) (void *) acts_at(villager, OUTDOOR_VILLAGER_MOOD);
}

static OutdoorVillagerWatch *acts_watch(u8 *villager)
{
    return (OutdoorVillagerWatch *) (void *) acts_at(villager, OUTDOOR_VILLAGER_WATCH);
}

static u32 *acts_reaction(u8 *villager)
{
    return (u32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_REACTION);
}

/* Its town record (vtable slot 0x64), or null. */
static u8 *acts_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(villager);
}

/* The step `step` of an update's table run (when it is in the table). */
static void acts_run_step(MemberPointer *table, int count, OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->step < count) {
        const MemberPointer *member = &table[self->step];
        void *object = MemberPointer_Object(member, self);
        ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager);
    }
}

/* The watch held on this console's player (OutdoorVillagerWatch_Hold, kind 1). */
static void acts_hold_on_player(u8 *villager)
{
    OutdoorVillagerWatch_Hold(acts_watch(villager), villager, 1, 0, 0, &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                              data_020c814c, 1);
}

/* A turn in place to this console's player. */
static void acts_turn_to_player(u8 *villager)
{
    void *yaw = SceneObject_YawToActor(villager, OUTDOOR_VILLAGER_PLAYER_ACTOR);
    SceneMotion_Request(acts_motion(villager), ACTS_MOTION_TURN, ACTS_PRIORITY, 0, 0, 0, (s16) (intptr_t) yaw, 0, 0,
                        data_020c80f8, 0);
}

/* What the starts of behaviours 18, 19, 21 and 23 do first: a running act's effects reset
 * (OutdoorVillagerObject_ResetActEffects), the body animation's speed following the villager's again, and the
 * watch held on `kind` (1, the player; 0, nothing). */
static void acts_begin(u8 *villager, int kind)
{
    OutdoorVillagerObject_ResetActEffects(villager);
    SpeakerAnim_SetKeepSpeed(acts_anim(villager), 0);
    OutdoorVillagerWatch_Hold(acts_watch(villager), villager, kind, 0, 0, &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                              data_020c814c, 1);
}

/* ---- Behaviour 23 */

/* _ZN18Obj_ov068_022771c019func_ov068_02267394Ei: behaviour 23's update: Turn23, Watch23. */
int OutdoorVillagerActs_Update23(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276f78, /* OutdoorVillagerActs_Turn23 */
        &data_ov068_02277030, /* OutdoorVillagerActs_Watch23 */
    };
    MemberTable_InitOnce(&data_ov068_02278288, data_ov068_0227836c, steps, 2);
    acts_run_step(data_ov068_0227836c, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02267394Ei, OutdoorVillagerActs_Update23)

/* func_ov068_02267400: once act 0x1a plays (kind 8), the wait is out, the player no longer
 * shows an insect or a fish and the body animation is at its first frame, it stands and
 * behaviour 0 starts.
 * QUIRK: the frame is taken as the whole frames' low 16 bits. */
void OutdoorVillagerActs_Watch23(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneMotion_Kind(acts_motion(villager)) != ACTS_MOTION_ACT) {
        return;
    }
    if (SceneMotion_ActNumber(acts_motion(villager)) != ACTS_ACT_23) {
        return;
    }
    if (self->wait != 0) {
        return;
    }
    if (OutdoorVillagerWalks_PlayerShowsCatch(self) != 0) {
        return;
    }
    u32 frame = *(const u32 *) (const void *) acts_at(villager, OUTDOOR_VILLAGER_ANIM_FRAME);
    if (((frame << 4) >> 16) != 0) {
        return;
    }
    SceneMotion_RequestStand(acts_motion(villager), ACTS_PRIORITY, data_020c80f8);
    OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
}
CLEAN_AS(func_ov068_02267400, OutdoorVillagerActs_Watch23)

/* func_ov068_02267468: once the turn (kind 3) is done, act 0x1a, a wait of 20 frames, step 1. */
void OutdoorVillagerActs_Turn23(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneMotion_Kind(acts_motion(villager)) != ACTS_MOTION_TURN) {
        return;
    }
    if (SceneMotion_IsDone(acts_motion(villager)) == 0) {
        return;
    }
    SceneMotion_RequestAct(acts_motion(villager), ACTS_PRIORITY, ACTS_ACT_23, data_020c80f8);
    self->wait = ACTS_WAIT_23;
    self->step = 1;
}
CLEAN_AS(func_ov068_02267468, OutdoorVillagerActs_Turn23)

/* func_ov068_022674b0: behaviour 23's start: held on the player (acts_begin), the byte at
 * 0x838 cleared, footsteps on, a turn to the player, its mood's sounds off;
 * step 0, and `shown` set. */
void OutdoorVillagerActs_Start23(OutdoorVillagerBehaviour *self, u8 *villager)
{
    acts_begin(villager, 1);
    VillagerSceneObject_ClearByte838(villager);
    Footsteps_Enable((Footsteps *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS));
    acts_turn_to_player(villager);
    VillagerMood_SoundsOff(acts_mood(villager));
    self->step = 0;
    self->shown = 1;
}
CLEAN_AS(func_ov068_022674b0, OutdoorVillagerActs_Start23)

/* ---- Behaviours 22 and 20: the talks after reactions 2 and 1 */

/* The turn to the object its talk names (its motion argument; angle 0 without one) and the
 * talk, held on the player meanwhile. */
static void acts_turn_and_talk(u8 *villager, int clear_motion_number)
{
    int target = SceneBase_MotionArg((SceneBase *) (void *) acts_at(villager, OUTDOOR_VILLAGER_TALK));
    int angle = 0;
    if (clear_motion_number) {
        Obj020d8c64_ClearLastMotionNumber(villager);
    }
    if (target != 0) {
        angle = SceneObject_YawTo(villager, (u8 *) (uintptr_t) (u32) target);
    }
    acts_hold_on_player(villager);
    SceneAction_RequestTurnAndTalk(acts_action(villager), 0, angle, 0);
}

/* What both do once the action of the talk ends, up to unpairing (the order of the last two
 * differs between them). */
static void acts_talk_ended(OutdoorVillagerBehaviour *self, u8 *villager)
{
    OutdoorVillagerBonds_AskMood(self, villager, ACTS_MOOD_WHICH, ACTS_MOOD_UNITS, 1);
    SceneObjectBase_DefaultApproach((SceneObjectBase *) (void *) villager);
    EventQueue_FinishObjectEvent(villager);
    VillagerSceneObject_SetWord644((u32 *) (void *) villager, 0);
}

/* _ZN18Obj_ov068_022771c019func_ov068_02267558Ei: behaviour 22's update: Talk22, Idle22. */
int OutdoorVillagerActs_Update22(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02277170, /* OutdoorVillagerActs_Talk22 */
        &data_ov068_02276e40, /* OutdoorVillagerActs_Idle22 */
    };
    MemberTable_InitOnce(&data_ov068_02278294, data_ov068_0227830c, steps, 2);
    acts_run_step(data_ov068_0227830c, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02267558Ei, OutdoorVillagerActs_Update22)

/* func_ov068_022675c4: nothing. */
void OutdoorVillagerActs_Idle22(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    (void) villager;
}
CLEAN_AS(func_ov068_022675c4, OutdoorVillagerActs_Idle22)

/* func_ov068_022675c8: once the action ends: its mood asked for, its approach set back, its
 * event finished, unpaired (the behaviour to resume set to 0 between the two halves), reaction
 * none, the word at 0xf4 1200, step 1. */
void OutdoorVillagerActs_Talk22(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneAction_IsBusy(acts_action(villager)) != 0) {
        return;
    }
    acts_talk_ended(self, villager);
    OutdoorVillagerBehaviour_SetResume(self, OUTDOOR_VILLAGER_DO_DEFAULT);
    VillagerSceneObject_SetByte648(villager, 0);
    *acts_reaction(villager) = OUTDOOR_VILLAGER_REACTION_NONE;
    self->unk_f4 = ACTS_REACTION_FRAMES;
    self->step = 1;
}
CLEAN_AS(func_ov068_022675c8, OutdoorVillagerActs_Talk22)

/* func_ov068_02267634: behaviour 22's start: the last motion number cleared, then the turn and
 * the talk. */
int OutdoorVillagerActs_Start22(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    acts_turn_and_talk(villager, 1);
    return 1;
}
CLEAN_AS(func_ov068_02267634, OutdoorVillagerActs_Start22)

/* _ZN18Obj_ov068_022771c019func_ov068_022676a8Ei: behaviour 20's update: Wait20, Talk20,
 * Idle20. */
int OutdoorVillagerActs_Update20(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[3] = {
        &data_ov068_02276ff8, /* OutdoorVillagerActs_Wait20 */
        &data_ov068_02277058, /* OutdoorVillagerActs_Talk20 */
        &data_ov068_02277088, /* OutdoorVillagerActs_Idle20 */
    };
    MemberTable_InitOnce(&data_ov068_022782a0, data_ov068_022783c4, steps, 3);
    acts_run_step(data_ov068_022783c4, 3, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_022676a8Ei, OutdoorVillagerActs_Update20)

/* func_ov068_02267724: nothing. */
void OutdoorVillagerActs_Idle20(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    (void) villager;
}
CLEAN_AS(func_ov068_02267724, OutdoorVillagerActs_Idle20)

/* func_ov068_02267728: once the action ends: as Talk22, with `count_38` and `hold_3a` cleared
 * too, step 2. */
void OutdoorVillagerActs_Talk20(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneAction_IsBusy(acts_action(villager)) != 0) {
        return;
    }
    acts_talk_ended(self, villager);
    VillagerSceneObject_SetByte648(villager, 0);
    OutdoorVillagerBehaviour_SetResume(self, OUTDOOR_VILLAGER_DO_DEFAULT);
    self->count_38 = 0;
    self->hold_3a = 0;
    *acts_reaction(villager) = OUTDOOR_VILLAGER_REACTION_NONE;
    self->unk_f4 = ACTS_REACTION_FRAMES;
    self->step = 2;
}
CLEAN_AS(func_ov068_02267728, OutdoorVillagerActs_Talk20)

/* Whether animation 0xec still plays (its motion not done). */
static int acts_anim_19_playing(u8 *villager)
{
    return SpeakerAnim_Number(acts_anim(villager), 0) == ACTS_ANIM_19_FACING && SceneMotion_IsDone(acts_motion(villager)) == 0;
}

/* func_ov068_022677a0: unless animation 0xec still plays, the turn and the talk, step 1. */
void OutdoorVillagerActs_Wait20(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (acts_anim_19_playing(villager)) {
        return;
    }
    acts_turn_and_talk(villager, 0);
    self->step = 1;
}
CLEAN_AS(func_ov068_022677a0, OutdoorVillagerActs_Wait20)

/* func_ov068_02267830: behaviour 20's start: the last motion number cleared; while animation
 * 0xec still plays, step 0; else the turn and the talk, step 1. */
int OutdoorVillagerActs_Start20(OutdoorVillagerBehaviour *self, u8 *villager)
{
    Obj020d8c64_ClearLastMotionNumber(villager);
    if (acts_anim_19_playing(villager)) {
        self->step = 0;
        return 1;
    }
    acts_turn_and_talk(villager, 0);
    self->step = 1;
    return 1;
}
CLEAN_AS(func_ov068_02267830, OutdoorVillagerActs_Start20)

/* ---- Behaviour 21 */

/* _ZN18Obj_ov068_022771c019func_ov068_022678d0Ei: behaviour 21's update: Turn21, Wait21. */
int OutdoorVillagerActs_Update21(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276ee0, /* OutdoorVillagerActs_Turn21 */
        &data_ov068_02276f48, /* OutdoorVillagerActs_Wait21 */
    };
    MemberTable_InitOnce(&data_ov068_022782ac, data_ov068_0227833c, steps, 2);
    acts_run_step(data_ov068_0227833c, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_022678d0Ei, OutdoorVillagerActs_Update21)

/* func_ov068_0226793c: once the wait is out, behaviour 0 and its approach set back; until
 * then event kind 6 asked for. */
void OutdoorVillagerActs_Wait21(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->wait == 0) {
        OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
        SceneObjectBase_DefaultApproach((SceneObjectBase *) (void *) villager);
    } else {
        EventQueue_RequestKind6(villager, 0);
    }
}
CLEAN_AS(func_ov068_0226793c, OutdoorVillagerActs_Wait21)

/* Event kind 6 asked for; once the turn (kind 3) is done, it stands and waits 40 frames, then
 * step `next`. */
static void acts_turn_then_wait(OutdoorVillagerBehaviour *self, u8 *villager, u8 next)
{
    EventQueue_RequestKind6(villager, 0);
    if (SceneMotion_Kind(acts_motion(villager)) == ACTS_MOTION_TURN && SceneMotion_IsDone(acts_motion(villager)) != 0) {
        SceneMotion_RequestStand(acts_motion(villager), ACTS_PRIORITY, data_020c80f8);
        self->wait = ACTS_WAIT_STANDING;
        self->step = next;
    }
}

/* func_ov068_02267964: the turn, then a wait (step 1). */
void OutdoorVillagerActs_Turn21(OutdoorVillagerBehaviour *self, u8 *villager)
{
    acts_turn_then_wait(self, villager, 1);
}
CLEAN_AS(func_ov068_02267964, OutdoorVillagerActs_Turn21)

/* func_ov068_022679b4: behaviour 21's start: held on the player (acts_begin), the byte at
 * 0x838 cleared, footsteps on, a turn to the player, the count at 0xa06 cleared, event kind 6
 * asked for, reaction 2, its approach cleared, step 0, its mood's sounds off, and its record's
 * byte 0x1e halved. */
int OutdoorVillagerActs_Start21(OutdoorVillagerBehaviour *self, u8 *villager)
{
    acts_begin(villager, 1);
    VillagerSceneObject_ClearByte838(villager);
    Footsteps_Enable((Footsteps *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS));
    acts_turn_to_player(villager);
    *(u16 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_COUNT_A06) = 0;
    EventQueue_RequestKind6(villager, 0);
    *acts_reaction(villager) = OUTDOOR_VILLAGER_REACTION_2;
    SceneObjectBase_ClearApproach((SceneObjectBase *) (void *) villager);
    self->step = 0;
    VillagerMood_SoundsOff(acts_mood(villager));
    if (acts_record(villager) != NULL) {
        VillagerEntry_HalveByte1E(acts_record(villager));
    }
    return 1;
}
CLEAN_AS(func_ov068_022679b4, OutdoorVillagerActs_Start21)

/* ---- Behaviour 19 */

/* _ZN18Obj_ov068_022771c019func_ov068_02267a90Ei: behaviour 19's update: React19, Turn19,
 * Wait19. */
int OutdoorVillagerActs_Update19(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[3] = {
        &data_ov068_02276e50, /* OutdoorVillagerActs_React19 */
        &data_ov068_02276e68, /* OutdoorVillagerActs_Turn19 */
        &data_ov068_02276e90, /* OutdoorVillagerActs_Wait19 */
    };
    MemberTable_InitOnce(&data_ov068_02278298, data_ov068_02278394, steps, 3);
    acts_run_step(data_ov068_02278394, 3, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02267a90Ei, OutdoorVillagerActs_Update19)

/* func_ov068_02267b0c: once the wait is out, `hold_3a` 1200, behaviour 0 and its approach set
 * back; until then event kind 6 asked for. */
void OutdoorVillagerActs_Wait19(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->wait == 0) {
        self->hold_3a = ACTS_REACTION_FRAMES;
        OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
        SceneObjectBase_DefaultApproach((SceneObjectBase *) (void *) villager);
    } else {
        EventQueue_RequestKind6(villager, 0);
    }
}
CLEAN_AS(func_ov068_02267b0c, OutdoorVillagerActs_Wait19)

/* func_ov068_02267b3c: the turn, then a wait (step 2). */
void OutdoorVillagerActs_Turn19(OutdoorVillagerBehaviour *self, u8 *villager)
{
    acts_turn_then_wait(self, villager, 2);
}
CLEAN_AS(func_ov068_02267b3c, OutdoorVillagerActs_Turn19)

/* func_ov068_02267b8c: while animation 0xeb or 0xec plays: the third time, event kind 6 asked
 * for; once the motion is done, the third time a turn to the player (step 1), else its
 * approach set back, behaviour 0 and `hold_3a` 1200.
 * QUIRK: the animation's number is asked for again when it is not 0xeb. */
void OutdoorVillagerActs_React19(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_19 &&
        SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_19_FACING) {
        return;
    }
    if (self->count_38 >= ACTS_STRIKES) {
        EventQueue_RequestKind6(villager, 0);
    }
    if (SceneMotion_IsDone(acts_motion(villager)) == 0) {
        return;
    }
    if (self->count_38 >= ACTS_STRIKES) {
        acts_turn_to_player(villager);
        self->step = 1;
    } else {
        SceneObjectBase_DefaultApproach((SceneObjectBase *) (void *) villager);
        OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
        self->hold_3a = ACTS_REACTION_FRAMES;
    }
}
CLEAN_AS(func_ov068_02267b8c, OutdoorVillagerActs_React19)

/* func_ov068_02267c34: behaviour 19's start: held on the player (acts_begin), the byte at
 * 0x838 cleared, footsteps on, its held item link's action 0; one more start (counted from 0 once
 * `hold_3a` ran out). The third: animation 0xec, event kind 6 asked for, reaction 1, its
 * approach cleared, the count held at 3. Else animation 0xec when this console's player's
 * object is within data_020c80f0 either way of where it faces, 0xeb otherwise. Then its
 * mood's sounds off.
 * QUIRK: the angle's size is taken as a 16-bit value: -0x8000 stays negative and counts as
 * facing. */
int OutdoorVillagerActs_Start19(OutdoorVillagerBehaviour *self, u8 *villager)
{
    acts_begin(villager, 1);
    VillagerSceneObject_ClearByte838(villager);
    Footsteps_Enable((Footsteps *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS));
    u16 word = data_020c80f8;
    HeldItemLink_Action0((HeldItemLink *) (void *) acts_at(villager, OUTDOOR_VILLAGER_LINK), word, 0);

    if (self->hold_3a == 0) {
        self->count_38 = 0;
    }
    self->count_38++;

    int animation = ACTS_ANIM_19;
    if (self->count_38 >= ACTS_STRIKES) {
        animation = ACTS_ANIM_19_FACING;
        EventQueue_RequestKind6(villager, 0);
        *acts_reaction(villager) = OUTDOOR_VILLAGER_REACTION_1;
        SceneObjectBase_ClearApproach((SceneObjectBase *) (void *) villager);
        self->count_38 = ACTS_STRIKES;
    } else {
        int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
        if (player != 0) {
            int angle = SceneObject_AngleTo(villager, (u8 *) (uintptr_t) (u32) player);
            if (angle < 0) {
                angle = (s16) -angle;
            }
            if (angle < data_020c80f0) {
                animation = ACTS_ANIM_19_FACING;
            }
        }
    }
    SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, animation, 1, word, 0);
    VillagerMood_SoundsOff(acts_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_02267c34, OutdoorVillagerActs_Start19)

/* ---- Behaviours 18 and 17 */

/* _ZN18Obj_ov068_022771c019func_ov068_02267d5cEi: behaviour 18's update: its one step
 * (func_ov068_02268020, behaviour 17's last). */
int OutdoorVillagerActs_Update18(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[1] = {
        &data_ov068_022770b8, /* func_ov068_02268020 */
    };
    MemberTable_InitOnce(&data_ov068_02278278, data_ov068_022782c4, steps, 1);
    acts_run_step(data_ov068_022782c4, 1, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02267d5cEi, OutdoorVillagerActs_Update18)

/* Whether behaviour 18 plays its animation for a held item: 0x1374 to 0x1377 or 0x1380 to
 * 0x139f (main's held_item.c: the rods are 0x1374 and 0x1375). */
static int acts_holds_18_item(u16 item)
{
    return (item >= 0x1374 && item <= 0x1377) || (item >= 0x1380 && item <= 0x139f);
}

/* func_ov068_02267dc0: behaviour 18's start: its watch held on nothing (acts_begin, kind 0),
 * flag 2 at 0x4e8 set, footsteps off, the byte at 0x838 set, the byte at
 * 0xa04 cleared, the effect at 0xa00 ended; animation 0x12b with an item held for which
 * acts_holds_18_item answers (its link's action 18 then), else 0x12a; at its place effect 0x91
 * on ground of attribute 0x13, else 0x90, with func_ov003_02220b44 run on the place between
 * the ground's reading and the effect; sound 0x7e9 and its mood's sounds off. */
int OutdoorVillagerActs_Start18(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    acts_begin(villager, 0);
    *(u32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FLAGS) |= ACTS_FLAG_18;
    Footsteps_Disable((Footsteps *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS));
    VillagerSceneObject_SetByte838(villager);
    *acts_at(villager, OUTDOOR_VILLAGER_BYTE_A04) = 0;
    s32 *handle = (s32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_EFFECT_HANDLE);
    if (*handle != ACTS_NO_EFFECT) {
        EffectSystem_EndHandle(*handle);
        *handle = ACTS_NO_EFFECT;
    }

    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    if (acts_holds_18_item(item)) {
        u16 word = data_020c80f8;
        SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_18_HOLDING, 1, word, 0);
        HeldItemLink_Action18((HeldItemLink *) (void *) acts_at(villager, OUTDOOR_VILLAGER_LINK), word, 0);
    } else {
        SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_18, 1, data_020c80f8, 0);
    }

    Vec3 at = *(const Vec3 *) (const void *) acts_at(villager, OUTDOOR_VILLAGER_POSITION);
    CollisionGround ground;
    CollisionGround_Init(&ground, &at, 0, 0);
    int attribute = ground.attr;
    Vec3 place = at;
    TileEvent_StartKindE(0, &place);
    EffectSystem_StartOneShotSetNumberCopy(attribute == ACTS_GROUND_18 ? ACTS_EFFECT_18_GROUND : ACTS_EFFECT_18, &at, NULL,
                                           NULL);
    SoundEmitter_Play((SoundEmitter *) (void *) acts_at(villager, OUTDOOR_VILLAGER_EMITTER), ACTS_SOUND_18, ACTS_SOUND_VOLUME,
                      0);
    VillagerMood_SoundsOff(acts_mood(villager));
    CollisionGround_Destroy(&ground);
    return 1;
}
CLEAN_AS(func_ov068_02267dc0, OutdoorVillagerActs_Start18)

/* _ZN18Obj_ov068_022771c019func_ov068_02267f84Ei: behaviour 17's update: func_ov068_0226840c,
 * func_ov068_0226831c, func_ov068_02268254, func_ov068_022680a4, func_ov068_02268020. */
int OutdoorVillagerActs_Update17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[5] = {
        &data_ov068_02277020, &data_ov068_02277050, &data_ov068_02277070, &data_ov068_02277080, &data_ov068_02277098,
    };
    MemberTable_InitOnce(&data_ov068_0227826c, data_ov068_02278424, steps, 5);
    acts_run_step(data_ov068_02278424, 5, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02267f84Ei, OutdoorVillagerActs_Update17)

/* ---- Behaviour 17: its start and its update's steps
 *
 * What the player's field actor does in states 0x73 to 0x75 (clean/ov003/field_actor.c), with
 * the villager's animations: 0x127 while it steps onto the middle of its tile, 0x128 with
 * effect 0x8e (0x8f on ground of attribute 0x13) and sound 0x7e8 once there, then 0x129 at a
 * set speed with effect 0x4c following it for 100 frames (the countdown at 0x2c, which the
 * behaviour member counts down), then behaviour 18's leaving (0x12a or 0x12b). */

extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The villager's body animation's frames (a FrameCtrl: its speed at 0x198, its flags at
 * 0x19c). */
#define ACTS_ANIM_CTRL 0x188
#define ACTS_ANIM_SPEED 0x198
/* Behaviour 17's animations, effects, sounds, speed and frames. */
#define ACTS_ANIM_17_STEP 0x127
#define ACTS_ANIM_17_ENTER 0x128
#define ACTS_ANIM_17_STAY 0x129
#define ACTS_EFFECT_17 0x8e
#define ACTS_EFFECT_17_GROUND 0x8f
#define ACTS_EFFECT_17_STAY 0x4c
#define ACTS_SOUND_17_START 0x7ee
#define ACTS_SOUND_17 0x7e8
#define ACTS_SPEED_17 0x1400
#define ACTS_STAY_17 100
/* How it steps onto the middle of its tile (OutdoorVillagerActs_Approach): the part of the
 * way it goes each frame, the most and the least. */
#define ACTS_APPROACH_RATE 0xe66
#define ACTS_APPROACH_MOST 0x1ec
#define ACTS_APPROACH_LEAST 0x31
/* The held item's pose behaviour 17 leaves with, and the argument of its poses. */
#define ACTS_POSE_NONE 0
#define ACTS_POSE_ARG 3

/* Behaviour 17's countdown (s16) and the animation speed it keeps (fx32). */
static s16 *acts_count_17(OutdoorVillagerBehaviour *self)
{
    return (s16 *) (void *) ((u8 *) self + 0x2c);
}

static fx32 *acts_speed_17(OutdoorVillagerBehaviour *self)
{
    return (fx32 *) (void *) ((u8 *) self + 0x30);
}

static HeldItemLink *acts_link(u8 *villager)
{
    return (HeldItemLink *) (void *) acts_at(villager, OUTDOOR_VILLAGER_LINK);
}

static Vec3 *acts_position(u8 *villager)
{
    return (Vec3 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_POSITION);
}

static SoundEmitter *acts_emitter(u8 *villager)
{
    return (SoundEmitter *) (void *) acts_at(villager, OUTDOOR_VILLAGER_EMITTER);
}

static FrameCtrl *acts_anim_ctrl(u8 *villager)
{
    return (FrameCtrl *) (void *) acts_at(villager, ACTS_ANIM_CTRL);
}

/* func_ov068_02268020: behaviour 17's last step and behaviour 18's only one: once animation
 * 0x12b or 0x12a is done, flag 2 at 0x4e8 cleared, step 5, the held item's pose 0 and
 * behaviour 0.
 * QUIRK: the animation's number is asked for again when it is not 0x12b. */
void OutdoorVillagerActs_Leave17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_18_HOLDING &&
        SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_18) {
        return;
    }
    if (SceneMotion_IsDone(acts_motion(villager)) == 0) {
        return;
    }
    *(u32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FLAGS) &= ~(u32) ACTS_FLAG_18;
    self->step = 5;
    SpeakerAnim_PlayItemPose(acts_anim(villager), villager, &acts_link(villager)->item, ACTS_POSE_NONE, ACTS_POSE_ARG);
    OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
}
CLEAN_AS(func_ov068_02268020, OutdoorVillagerActs_Leave17)

/* func_ov068_022680a4: during animation 0x129: while the countdown runs the body animation
 * keeps the speed kept and the effect at 0xa00 (when there is one) follows the villager;
 * once it is out, what behaviour 18's start does after its first steps: the animation's speed
 * its own again, the byte at 0x838 set, the byte at 0xa04 cleared, the effect ended, animation
 * 0x12b (its link's action 18) or 0x12a, effect 0x90 or 0x91 with func_ov003_02220b44 on its
 * place, sound 0x7e9; step 4. */
void OutdoorVillagerActs_Stay17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_17_STAY) {
        return;
    }
    s32 *handle = (s32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_EFFECT_HANDLE);
    if (*acts_count_17(self) != 0) {
        *(fx32 *) (void *) acts_at(villager, ACTS_ANIM_SPEED) = *acts_speed_17(self);
        if (*handle != ACTS_NO_EFFECT) {
            EffectSystem_MoveHandle(*handle, acts_position(villager), NULL, NULL);
        }
        return;
    }

    SpeakerAnim_SetKeepSpeed(acts_anim(villager), 0);
    VillagerSceneObject_SetByte838(villager);
    *acts_at(villager, OUTDOOR_VILLAGER_BYTE_A04) = 0;
    if (*handle != ACTS_NO_EFFECT) {
        EffectSystem_EndHandle(*handle);
        *handle = ACTS_NO_EFFECT;
    }

    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    if (acts_holds_18_item(item)) {
        u16 word = data_020c80f8;
        SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_18_HOLDING, 1, word, 0);
        HeldItemLink_Action18(acts_link(villager), word, 0);
    } else {
        SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_18, 1, data_020c80f8, 0);
    }

    Vec3 at = *acts_position(villager);
    CollisionGround ground;
    CollisionGround_Init(&ground, &at, 0, 0);
    int attribute = ground.attr;
    Vec3 place = at;
    TileEvent_StartKindE(0, &place);
    EffectSystem_StartOneShotSetNumberCopy(attribute == ACTS_GROUND_18 ? ACTS_EFFECT_18_GROUND : ACTS_EFFECT_18, &at, NULL,
                                           NULL);
    SoundEmitter_Play(acts_emitter(villager), ACTS_SOUND_18, ACTS_SOUND_VOLUME, 0);
    self->step = 4;
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov068_022680a4, OutdoorVillagerActs_Stay17)

/* func_ov068_02268254: once animation 0x128 is done: animation 0x129 at speed 0x1400, kept
 * as the animation's own (its link's action 17 and the link's record value the same speed),
 * the countdown 100, effect 0x4c started at its place (its handle at 0xa00), the byte at
 * 0xa04 set and the byte at 0x838 cleared; step 3. The speed is read back from where it is
 * kept each time. */
void OutdoorVillagerActs_Begin17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_17_ENTER) {
        return;
    }
    if (SceneMotion_IsDone(acts_motion(villager)) == 0) {
        return;
    }
    *acts_speed_17(self) = ACTS_SPEED_17;
    u16 word = data_020c80f8;
    SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_17_STAY, 0, word, 0);
    *(fx32 *) (void *) acts_at(villager, ACTS_ANIM_SPEED) = *acts_speed_17(self);
    SpeakerAnim_SetKeepSpeed(acts_anim(villager), 1);
    HeldItemLink_Action17(acts_link(villager), word, 0);
    HeldItemLink_SetRecordValue(acts_link(villager), *acts_speed_17(self));
    *acts_count_17(self) = ACTS_STAY_17;
    Vec3 at = *acts_position(villager);
    int handle = EffectSystem_StartKind(ACTS_EFFECT_17_STAY, &at, NULL, NULL);
    *(s32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_EFFECT_HANDLE) = handle;
    *acts_at(villager, OUTDOOR_VILLAGER_BYTE_A04) = 1;
    VillagerSceneObject_ClearByte838(villager);
    self->step = 3;
}
CLEAN_AS(func_ov068_02268254, OutdoorVillagerActs_Begin17)

/* func_ov068_0226831c: once animation 0x127 has played to its end: animation 0x128, effect
 * 0x8e at its place (0x8f on ground of attribute 0x13) with func_ov003_02221228 on the place
 * between the ground's reading and the effect, sound 0x7e8, its link's action 16 and the
 * held item's pose 0x128; step 2. */
void OutdoorVillagerActs_Enter17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_17_STEP) {
        return;
    }
    if (FrameCtrl_IsDone(acts_anim_ctrl(villager)) == 0) {
        return;
    }
    u16 word = data_020c80f8;
    SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_17_ENTER, 1, word, 0);

    Vec3 at = *acts_position(villager);
    CollisionGround ground;
    CollisionGround_Init(&ground, &at, 0, 0);
    int attribute = ground.attr;
    Vec3 place = at;
    TileEvent_StartUnitKind2(0, &place);
    EffectSystem_StartOneShotSetNumberCopy(attribute == ACTS_GROUND_18 ? ACTS_EFFECT_17_GROUND : ACTS_EFFECT_17, &at, NULL,
                                           NULL);
    SoundEmitter_Play(acts_emitter(villager), ACTS_SOUND_17, ACTS_SOUND_VOLUME, 0);
    HeldItemLink_Action16(acts_link(villager), word, 1);
    SpeakerAnim_PlayItemPose(acts_anim(villager), villager, &acts_link(villager)->item, ACTS_ANIM_17_ENTER, ACTS_POSE_ARG);
    self->step = 2;
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov068_0226831c, OutdoorVillagerActs_Enter17)

/* func_ov068_0226840c: during animation 0x127 the villager steps towards the middle of its
 * tile (OutdoorVillagerActs_Approach on x, then z) and the animation is made to stop at its
 * end; once it is there, OutdoorVillagerActs_Enter17 at once when the animation has ended,
 * else step 1 (which waits for it). */
void OutdoorVillagerActs_StepOnto17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(acts_anim(villager), 0) != ACTS_ANIM_17_STEP) {
        return;
    }
    Vec3 *position = acts_position(villager);
    Vec3 centre;
    AcreTile_SnapToTileCentre(&centre, position);
    OutdoorVillagerActs_Approach(&position->x, centre.x, ACTS_APPROACH_RATE, ACTS_APPROACH_MOST, ACTS_APPROACH_LEAST);
    OutdoorVillagerActs_Approach(&position->z, centre.z, ACTS_APPROACH_RATE, ACTS_APPROACH_MOST, ACTS_APPROACH_LEAST);
    acts_anim_ctrl(villager)->flags = FRAME_CTRL_ONCE;
    if (position->x != centre.x || position->z != centre.z) {
        return;
    }
    if (FrameCtrl_IsDone(acts_anim_ctrl(villager)) != 0) {
        OutdoorVillagerActs_Enter17(self, villager);
    } else {
        self->step = 1;
    }
}
CLEAN_AS(func_ov068_0226840c, OutdoorVillagerActs_StepOnto17)

/* func_ov068_022684a4: `*value` moved towards `target` by the part `rate` of the way left
 * (FX_MulFunc), at most `most` and at least `least`; when less than `least` is left it
 * arrives. */
void OutdoorVillagerActs_Approach(fx32 *value, fx32 target, fx32 rate, fx32 most, fx32 least)
{
    if (*value == target) {
        return;
    }
    fx32 left = target - *value;
    fx32 left_size = left < 0 ? -left : left;
    if (left_size < least) {
        *value = target;
        return;
    }
    fx32 step = FX_MulFunc(left, rate);
    fx32 step_size = step < 0 ? -step : step;
    if (step_size > most) {
        step = step >= 0 ? most : -most;
    } else if (step_size < least) {
        step = step >= 0 ? least : -least;
    }
    *value += step;
}
CLEAN_AS(func_ov068_022684a4, OutdoorVillagerActs_Approach)

/* func_ov068_02268514: behaviour 17's start: a running act's effects reset
 * (OutdoorVillagerObject_ResetActEffects), animation 0x127, the watch held on nothing, its link's action 15,
 * flag 2 at 0x4e8 set, the byte at 0x838 set, footsteps off, sound 0x7ee and its mood's
 * sounds off. */
int OutdoorVillagerActs_Start17(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    OutdoorVillagerObject_ResetActEffects(villager);
    u16 word = data_020c80f8;
    SceneMotion_RequestAnimation(acts_motion(villager), ACTS_PRIORITY, ACTS_ANIM_17_STEP, 0, word, 0);
    OutdoorVillagerWatch_Hold(acts_watch(villager), villager, 0, 0, 0, &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                              data_020c814c, 1);
    HeldItemLink_Action15(acts_link(villager), word, 0);
    *(u32 *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FLAGS) |= ACTS_FLAG_18;
    VillagerSceneObject_SetByte838(villager);
    Footsteps_Disable((Footsteps *) (void *) acts_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS));
    SoundEmitter_Play(acts_emitter(villager), ACTS_SOUND_17_START, ACTS_SOUND_VOLUME, 0);
    VillagerMood_SoundsOff(acts_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_02268514, OutdoorVillagerActs_Start17)
