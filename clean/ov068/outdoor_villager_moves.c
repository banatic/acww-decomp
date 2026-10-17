/* Behaviours 6, 7, 8, 10, 11, 13, 14, 15 and 16 of a villager out walking in the town
 * (outdoor_villager_moves.h). */
#include "outdoor_villager_moves.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/camera_modes.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/frame_ctrl.h"
#include "main/held_item_link.h"
#include "main/main_random.h"
#include "main/music_queue.h"
#include "main/npc_id.h"
#include "main/player_actor_ops.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/session_players.h"
#include "main/sound_emitter.h"
#include "main/speaker_anim.h"
#include "main/town_villager.h"
#include "main/villager_entry.h"
#include "main/villager_memory_entry.h"
#include "main/villager_mood.h"
#include "main/villager_scene_held.h"
#include "main/villager_scene_object.h"
#include "main/villager_state.h"
#include "ov003/field_actor.h"
#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "outdoor_villager_watch.h"

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The town's map (acre_map.h), or null. */
extern AcreMap *data_021c80bc;
/* The count at 0xa06 at which behaviour 21 takes over (100). */
extern s16 data_ov068_02276724[];
/* A copy of data_020c80f0 made when the overlay starts: how far either way from facing the
 * player behaviour 7 counts as facing it. */
extern s16 data_ov068_02278264;

/* Behaviour 7's calls at frame 9 of animation 0xdf: an effect kind and a sound (less 0x84). */
typedef struct MovesCall {
    u16 effect;
    u8 sound;
    u8 unk_03;
} MovesCall;
extern const MovesCall data_ov068_022767a4[2];

/* Whether the byte at 0xa05 is set (behaviour 19 takes over). */
extern int func_ov068_0226c0e0(OutdoorVillagerBehaviour *self, u8 *villager);

/* The updates' step tables (each filled once, bit 0 of its guard), and the member pointers
 * they are filled from. */
extern u32 data_ov068_022782a4;
extern MemberPointer data_ov068_0227834c[2];
extern const MemberPointer data_ov068_02276fb8, data_ov068_02276fe0;
extern u32 data_ov068_022782b4;
extern MemberPointer data_ov068_0227832c[2];
extern const MemberPointer data_ov068_02276f18, data_ov068_02276f40;
extern u32 data_ov068_022782a8;
extern MemberPointer data_ov068_022783ac[3];
extern const MemberPointer data_ov068_02276ea0, data_ov068_02276f10, data_ov068_02276ec0;
extern u32 data_ov068_02278274;
extern MemberPointer data_ov068_022782fc[2];
extern const MemberPointer data_ov068_02276f60, data_ov068_02276e80;
extern u32 data_ov068_0227828c;
extern MemberPointer data_ov068_022782bc[1];
extern const MemberPointer data_ov068_02276e48;
extern u32 data_ov068_02278280;
extern MemberPointer data_ov068_022783fc[5];
extern const MemberPointer data_ov068_022770b0, data_ov068_022770c8, data_ov068_022770e8, data_ov068_02277128,
    data_ov068_02277168;
extern u32 data_ov068_02278268;
extern MemberPointer data_ov068_0227835c[2];
extern const MemberPointer data_ov068_02277090, data_ov068_022770a0;

/* The parts of the villager read here besides outdoor_villager.h's. */
#define MOVES_ANGLE 0x8e       /* s16: where it faces */
#define MOVES_WALK_ANGLE 0x94  /* s16: where it walks */
#define MOVES_MOVER 0x350      /* SceneMover */
#define MOVES_ITEM_SHOWN 0x9f0 /* u8: set while the held item is out */
#define MOVES_BYTE_A05 0xa05   /* u8: read through func_ov068_0226c0e0 */
/* The parts of the behaviour member read here besides outdoor_villager.h's (behaviour 7). */
#define MOVES_TARGET 0xe4 /* u8 *: this console's player's object */
#define MOVES_START 0xe8  /* Vec3: where the villager started */

/* The motions' kinds and priorities (main's scene_motion_kinds.h). */
#define MOVES_MOTION_STAND 0
#define MOVES_MOTION_WALK 2
#define MOVES_MOTION_TURN 3
#define MOVES_MOTION_GREET 11 /* the villager's two animations of its vtable slots 0x94 and 0x98 */
#define MOVES_PRIORITY 1
#define MOVES_PRIORITY_HIGH 2

#define MOVES_SOUND_VOLUME 0x7f
#define MOVES_NO_ITEM 0xfff1
#define MOVES_SCALE_ONE 0x1000
#define MOVES_SCALE_STEP 0x249
#define MOVES_FRAMES_200 200
#define MOVES_GIVE_UP_FRAMES 1200 /* the word at 0xf4 when behaviour 7 gives up */

/* Behaviours 15 and 16. */
#define MOVES_ITEM_FIRST 0x1380
#define MOVES_ITEM_LAST 0x139f
#define MOVES_ANIM_ITEM 0xcd
#define MOVES_ANIM_NO_ITEM 0xd6
#define MOVES_ITEM_ACTION 0x26
#define MOVES_SOUND_ITEM 0x4f
#define MOVES_SOUND_OPEN 0x857
#define MOVES_SOUND_CLOSE 0x858
#define MOVES_FRAME_OPEN 7
#define MOVES_FRAME_CLOSE 5
#define MOVES_POSE_ITEM 7
#define MOVES_POSE_ARG 3
/* An item's own animation (at 0x9c of the held item's record, a FrameCtrl): played backwards
 * from its last frame, to its first. */
#define MOVES_ITEM_FRAMES 0x9c
#define MOVES_FRAMES_BACKWARDS (FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE)

/* Behaviours 13 and 14: the place 0x2000 along x the other way and 0x8000 along z from a
 * point. */
#define MOVES_PLACE_DX (-0x2000)
#define MOVES_PLACE_DZ 0x8000
#define MOVES_ITEM_13_FIRST 0x5014
#define MOVES_ITEM_13_LAST 0x501a
#define MOVES_MUSIC_13 0x12
#define MOVES_MUSIC_13_VALUE 0xf
#define MOVES_PLAYER_FLAG_13 0x1d

/* Behaviour 7. */
#define MOVES_ANIM_7 0xdf
#define MOVES_FRAME_CALL 9
#define MOVES_CALL_SOUND_BASE 0x84
#define MOVES_REACH 0x3000      /* within it and facing, the greeting */
#define MOVES_STAY_REACH 0x5000 /* beyond it (or not facing), it turns again */
#define MOVES_WANDER 0xc000     /* how far from where it started it follows */
#define MOVES_TURN_WAIT 10

static u8 *moves_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static SceneMotion *moves_motion(u8 *villager)
{
    return (SceneMotion *) (void *) moves_at(villager, OUTDOOR_VILLAGER_MOTION);
}

static SpeakerAnim *moves_anim(u8 *villager)
{
    return (SpeakerAnim *) (void *) moves_at(villager, OUTDOOR_VILLAGER_ANIM);
}

static SceneAction *moves_action(u8 *villager)
{
    return (SceneAction *) (void *) moves_at(villager, OUTDOOR_VILLAGER_ACTION);
}

static VillagerMood *moves_mood(u8 *villager)
{
    return (VillagerMood *) (void *) moves_at(villager, OUTDOOR_VILLAGER_MOOD);
}

static OutdoorVillagerWatch *moves_watch(u8 *villager)
{
    return (OutdoorVillagerWatch *) (void *) moves_at(villager, OUTDOOR_VILLAGER_WATCH);
}

static HeldItemLink *moves_link(u8 *villager)
{
    return (HeldItemLink *) (void *) moves_at(villager, OUTDOOR_VILLAGER_LINK);
}

static SoundEmitter *moves_emitter(u8 *villager)
{
    return (SoundEmitter *) (void *) moves_at(villager, OUTDOOR_VILLAGER_EMITTER);
}

static Vec3 *moves_position(u8 *villager)
{
    return (Vec3 *) (void *) moves_at(villager, OUTDOOR_VILLAGER_POSITION);
}

static OutdoorVillagerEffect *moves_effect(u8 *villager)
{
    return (OutdoorVillagerEffect *) (void *) moves_at(villager, OUTDOOR_VILLAGER_EFFECT);
}

/* The body animation's whole frame, as 16 bits. */
static u32 moves_frame(u8 *villager)
{
    u32 frame = *(const u32 *) (const void *) moves_at(villager, OUTDOOR_VILLAGER_ANIM_FRAME);
    return (frame << 4) >> 16;
}

/* Its town record (vtable slot 0x64), or null. */
static u8 *moves_record(u8 *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OUTDOOR_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(villager);
}

/* The step `step` of an update's table run (when it is in the table). */
static void moves_run_step(MemberPointer *table, int count, OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (self->step < count) {
        const MemberPointer *member = &table[self->step];
        void *object = MemberPointer_Object(member, self);
        ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager);
    }
}

/* The watch held on `kind` (1: this console's player, 0: nothing). */
static void moves_hold(u8 *villager, int kind)
{
    OutdoorVillagerWatch_Hold(moves_watch(villager), villager, kind, 0, 0, &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                              data_020c814c, 1);
}

/* A motion of `kind` with the angle and the end point given (the others 0). */
static void moves_request(u8 *villager, int kind, int priority, int x, int z, int angle)
{
    SceneMotion_Request(moves_motion(villager), kind, priority, x, z, 0, (s16) angle, 0, 0, data_020c80f8, 0);
}

/* Whether the motion is of `kind` and done. */
static int moves_done(u8 *villager, int kind)
{
    return SceneMotion_Kind(moves_motion(villager)) == kind && SceneMotion_IsDone(moves_motion(villager)) != 0;
}

/* The behaviour saved to resume started, else behaviour 0. */
static void moves_resume(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (OutdoorVillagerBehaviour_Resume(self, villager) == 0) {
        OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
    }
}

/* ---- Behaviour 16: the held item put away */

/* _ZN18Obj_ov068_022771c019func_ov068_022685d0Ei: behaviour 16's update: Shrink16, Close16. */
int OutdoorVillagerMoves_Update16(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276fb8, /* OutdoorVillagerMoves_Shrink16 */
        &data_ov068_02276fe0, /* OutdoorVillagerMoves_Close16 */
    };
    MemberTable_InitOnce(&data_ov068_022782a4, data_ov068_0227834c, steps, 2);
    moves_run_step(data_ov068_0227834c, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_022685d0Ei, OutdoorVillagerMoves_Update16)

/* func_ov068_0226863c: during animation 0xcd: once it is done, step 2 and the saved behaviour
 * resumed (else behaviour 0); until then, at frame 5 the link takes no item (pose 0) and the
 * byte at 0x9f0 is cleared. */
void OutdoorVillagerMoves_Close16(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(moves_anim(villager), 0) != MOVES_ANIM_ITEM) {
        return;
    }
    if (SceneMotion_IsDone(moves_motion(villager)) != 0) {
        self->step = 2;
        moves_resume(self, villager);
    } else if (moves_frame(villager) == MOVES_FRAME_CLOSE) {
        u16 none = MOVES_NO_ITEM;
        HeldItemLink_Take(moves_link(villager), villager, &none, NULL, MOVES_POSE_ARG);
        *moves_at(villager, MOVES_ITEM_SHOWN) = 0;
    }
}
CLEAN_AS(func_ov068_0226863c, OutdoorVillagerMoves_Close16)

/* func_ov068_022686c4: during animation 0xd6: once it is done, the link takes no item (pose
 * 0), step 2 and the saved behaviour resumed (else behaviour 0); until then the held item's
 * scale goes down by 0x249, to 0. */
void OutdoorVillagerMoves_Shrink16(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(moves_anim(villager), 0) != MOVES_ANIM_NO_ITEM) {
        return;
    }
    if (SceneMotion_IsDone(moves_motion(villager)) != 0) {
        u16 none = MOVES_NO_ITEM;
        HeldItemLink_Take(moves_link(villager), villager, &none, NULL, MOVES_POSE_ARG);
        self->step = 2;
        moves_resume(self, villager);
        return;
    }
    fx32 scale = HeldItemLink_Scale(moves_link(villager));
    if (scale != 0) {
        scale -= MOVES_SCALE_STEP;
        if (scale < 0) {
            scale = 0;
        }
    }
    HeldItemLink_SetScale(moves_link(villager), scale);
}
CLEAN_AS(func_ov068_022686c4, OutdoorVillagerMoves_Shrink16)

/* func_ov068_02268758: behaviour 16's start: the villager's held item read, a running act's
 * effects reset (OutdoorVillagerObject_ResetActEffects), the watch held on nothing. With an item of 0x1380 to
 * 0x139f: animation 0xcd (mode 3), the link takes the item, its action 0x26, the item's own
 * animation played backwards from its last frame (when the link has a record), scale 1.0,
 * sound 0x858, step 1. Else animation 0xd6, the link takes the item, scale 1.0, the byte at
 * 0x9f0 set, step 0. Then the byte at 0x838 set, sound 0x4f, the villager's held item none
 * and its mood's sounds off. */
int OutdoorVillagerMoves_Start16(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    OutdoorVillagerObject_ResetActEffects(villager);
    moves_hold(villager, 0);
    if (item >= MOVES_ITEM_FIRST && item <= MOVES_ITEM_LAST) {
        u16 word = data_020c80f8;
        SceneMotion_RequestAnimation(moves_motion(villager), MOVES_PRIORITY, MOVES_ANIM_ITEM, 3, word, 0);
        HeldItemLink_Take(moves_link(villager), villager, &item, (void *) (uintptr_t) MOVES_ANIM_ITEM, word);
        HeldItemLink_Act(moves_link(villager), MOVES_ITEM_ACTION, 1, 3);
        int record = HeldItemLink_Record(moves_link(villager));
        if (record != 0) {
            u8 *frames = (u8 *) (uintptr_t) (u32) record + MOVES_ITEM_FRAMES;
            u32 end = (u32) ((FrameCtrl *) (void *) frames)->end;
            u32 whole = (end << 4) >> 16;
            FrameCtrl_Init((FrameCtrl *) (void *) frames, whole, MOVES_FRAMES_BACKWARDS, MOVES_SCALE_ONE, (u16) (whole - 1));
        }
        HeldItemLink_SetScale(moves_link(villager), MOVES_SCALE_ONE);
        SoundEmitter_Play(moves_emitter(villager), MOVES_SOUND_CLOSE, MOVES_SOUND_VOLUME, 0);
        self->step = 1;
    } else {
        u16 word = data_020c80f8;
        SceneMotion_RequestAnimation(moves_motion(villager), MOVES_PRIORITY, MOVES_ANIM_NO_ITEM, 1, word, 0);
        HeldItemLink_Take(moves_link(villager), villager, &item, (void *) (uintptr_t) MOVES_ANIM_NO_ITEM, word);
        HeldItemLink_SetScale(moves_link(villager), MOVES_SCALE_ONE);
        *moves_at(villager, MOVES_ITEM_SHOWN) = 1;
        self->step = 0;
    }
    VillagerSceneObject_SetByte838(villager);
    SoundEmitter_Play(moves_emitter(villager), MOVES_SOUND_ITEM, MOVES_SOUND_VOLUME, 0);
    u16 none = MOVES_NO_ITEM;
    VillagerSceneHeld_SetItem(villager, &none);
    VillagerMood_SoundsOff(moves_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_02268758, OutdoorVillagerMoves_Start16)

/* ---- Behaviour 15: the held item brought out */

/* _ZN18Obj_ov068_022771c019func_ov068_022688d0Ei: behaviour 15's update: Grow15, Open15. */
int OutdoorVillagerMoves_Update15(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276f18, /* OutdoorVillagerMoves_Grow15 */
        &data_ov068_02276f40, /* OutdoorVillagerMoves_Open15 */
    };
    MemberTable_InitOnce(&data_ov068_022782b4, data_ov068_0227832c, steps, 2);
    moves_run_step(data_ov068_0227832c, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_022688d0Ei, OutdoorVillagerMoves_Update15)

/* func_ov068_0226893c: during animation 0xcd: once it is done, the held item's pose 0 (with
 * 7), step 2 and the saved behaviour resumed (else behaviour 0); until then, at frame 7 the
 * byte at 0x9f0 is set and sound 0x857 plays. */
void OutdoorVillagerMoves_Open15(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(moves_anim(villager), 0) != MOVES_ANIM_ITEM) {
        return;
    }
    if (SceneMotion_IsDone(moves_motion(villager)) != 0) {
        SpeakerAnim_PlayItemPose(moves_anim(villager), villager, &moves_link(villager)->item, 0, MOVES_POSE_ITEM);
        self->step = 2;
        moves_resume(self, villager);
    } else if (moves_frame(villager) == MOVES_FRAME_OPEN) {
        *moves_at(villager, MOVES_ITEM_SHOWN) = 1;
        SoundEmitter_Play(moves_emitter(villager), MOVES_SOUND_OPEN, MOVES_SOUND_VOLUME, 0);
    }
}
CLEAN_AS(func_ov068_0226893c, OutdoorVillagerMoves_Open15)

/* func_ov068_022689d4: during animation 0xd6: once it is done, step 2 and the saved behaviour
 * resumed (else behaviour 0); until frame 8 the held item's scale goes up by 0x249, to 1.0,
 * with the held item's pose 0 (with 7) at frame 7. */
void OutdoorVillagerMoves_Grow15(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SpeakerAnim_Number(moves_anim(villager), 0) != MOVES_ANIM_NO_ITEM) {
        return;
    }
    if (SceneMotion_IsDone(moves_motion(villager)) != 0) {
        self->step = 2;
        moves_resume(self, villager);
        return;
    }
    if (moves_frame(villager) >= MOVES_FRAME_OPEN + 1) {
        return;
    }
    fx32 scale = HeldItemLink_Scale(moves_link(villager));
    if (moves_frame(villager) == MOVES_FRAME_OPEN) {
        SpeakerAnim_PlayItemPose(moves_anim(villager), villager, &moves_link(villager)->item, 0, MOVES_POSE_ITEM);
    }
    if (scale != MOVES_SCALE_ONE) {
        scale += MOVES_SCALE_STEP;
        if (scale > MOVES_SCALE_ONE) {
            scale = MOVES_SCALE_ONE;
        }
    }
    HeldItemLink_SetScale(moves_link(villager), scale);
}
CLEAN_AS(func_ov068_022689d4, OutdoorVillagerMoves_Grow15)

/* func_ov068_02268a84: behaviour 15's start: the villager's held item read, a running act's
 * effects reset (OutdoorVillagerObject_ResetActEffects), the watch held on nothing. With an item of 0x1380 to
 * 0x139f: animation 0xcd, the link takes the item, its action 0x26 (with the motions' word and
 * 1), scale 1.0, the byte at 0x9f0 cleared, step 1. Else animation 0xd6 (mode 3), the link
 * takes the item, scale 0, the byte at 0x9f0 set, step 0. Then the byte at 0x838 set, sound
 * 0x4f and its mood's sounds off. */
int OutdoorVillagerMoves_Start15(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u16 item;
    VillagerSceneHeld_Item(&item, villager);
    OutdoorVillagerObject_ResetActEffects(villager);
    moves_hold(villager, 0);
    if (item >= MOVES_ITEM_FIRST && item <= MOVES_ITEM_LAST) {
        u16 word = data_020c80f8;
        SceneMotion_RequestAnimation(moves_motion(villager), MOVES_PRIORITY, MOVES_ANIM_ITEM, 1, word, 0);
        HeldItemLink_Take(moves_link(villager), villager, &item, (void *) (uintptr_t) MOVES_ANIM_ITEM, word);
        HeldItemLink_Act(moves_link(villager), MOVES_ITEM_ACTION, word, 1);
        HeldItemLink_SetScale(moves_link(villager), MOVES_SCALE_ONE);
        *moves_at(villager, MOVES_ITEM_SHOWN) = 0;
        self->step = 1;
    } else {
        u16 word = data_020c80f8;
        SceneMotion_RequestAnimation(moves_motion(villager), MOVES_PRIORITY, MOVES_ANIM_NO_ITEM, 3, word, 0);
        HeldItemLink_Take(moves_link(villager), villager, &item, (void *) (uintptr_t) MOVES_ANIM_NO_ITEM, word);
        HeldItemLink_SetScale(moves_link(villager), 0);
        *moves_at(villager, MOVES_ITEM_SHOWN) = 1;
        self->step = 0;
    }
    VillagerSceneObject_SetByte838(villager);
    SoundEmitter_Play(moves_emitter(villager), MOVES_SOUND_ITEM, MOVES_SOUND_VOLUME, 0);
    VillagerMood_SoundsOff(moves_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_02268a84, OutdoorVillagerMoves_Start15)

/* ---- Behaviour 14: the talk after reaction 0, then off */

/* _ZN18Obj_ov068_022771c019func_ov068_02268bb4Ei: behaviour 14's update: Talk14, Walk14,
 * Arrive14. */
int OutdoorVillagerMoves_Update14(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[3] = {
        &data_ov068_02276ea0, /* OutdoorVillagerMoves_Talk14 */
        &data_ov068_02276f10, /* OutdoorVillagerMoves_Walk14 */
        &data_ov068_02276ec0, /* OutdoorVillagerMoves_Arrive14 */
    };
    MemberTable_InitOnce(&data_ov068_022782a8, data_ov068_022783ac, steps, 3);
    moves_run_step(data_ov068_022783ac, 3, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02268bb4Ei, OutdoorVillagerMoves_Update14)

/* func_ov068_02268c30: once the walk (kind 2) is done or the wait is out: its event finished,
 * it stands, the event queue's flag 0x20 cleared; step 3. */
void OutdoorVillagerMoves_Arrive14(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_done(villager, MOVES_MOTION_WALK) || self->wait == 0) {
        EventQueue_FinishObjectEvent(villager);
        SceneMotion_RequestStand(moves_motion(villager), MOVES_PRIORITY, data_020c80f8);
        EventQueue_ClearFlag20();
        self->step = 3;
    }
}
CLEAN_AS(func_ov068_02268c30, OutdoorVillagerMoves_Arrive14)

/* func_ov068_02268c84: once the turn (kind 3) is done, a walk (kind 2) to its place moved by
 * (-0x2000, +0x8000), a wait of 200 frames; step 2. */
void OutdoorVillagerMoves_Walk14(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (!moves_done(villager, MOVES_MOTION_TURN)) {
        return;
    }
    Vec3 to = *moves_position(villager);
    to.x += MOVES_PLACE_DX;
    to.z += MOVES_PLACE_DZ;
    moves_request(villager, MOVES_MOTION_WALK, MOVES_PRIORITY, to.x, to.z, 0);
    self->wait = MOVES_FRAMES_200;
    self->step = 2;
}
CLEAN_AS(func_ov068_02268c84, OutdoorVillagerMoves_Walk14)

/* func_ov068_02268d04: once the action (the talk) ends, the camera's mode reset and a turn to
 * angle 0; step 1. */
void OutdoorVillagerMoves_Talk14(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneAction_IsBusy(moves_action(villager)) != 0) {
        return;
    }
    CameraControl_ResetMode();
    moves_request(villager, MOVES_MOTION_TURN, MOVES_PRIORITY, 0, 0, 0);
    self->step = 1;
}
CLEAN_AS(func_ov068_02268d04, OutdoorVillagerMoves_Talk14)

/* func_ov068_02268d54: behaviour 14's start: a turn to the object of its talk (its motion
 * argument; angle 0 without one) and the talk, keeping the camera; footsteps on and the watch
 * held on the player before the request; its mood's sounds off; step 0. */
int OutdoorVillagerMoves_Start14(OutdoorVillagerBehaviour *self, u8 *villager)
{
    int target = SceneBase_MotionArg((SceneBase *) (void *) moves_at(villager, OUTDOOR_VILLAGER_TALK));
    int angle = 0;
    if (target != 0) {
        angle = SceneObject_YawTo(villager, (u8 *) (uintptr_t) (u32) target);
    }
    Footsteps_Enable((Footsteps *) (void *) moves_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS));
    moves_hold(villager, 1);
    SceneAction_RequestTurnAndTalk(moves_action(villager), 0, angle, 1);
    VillagerMood_SoundsOff(moves_mood(villager));
    self->step = 0;
    return 1;
}
CLEAN_AS(func_ov068_02268d54, OutdoorVillagerMoves_Start14)

/* ---- Behaviour 13 */

/* func_ov068_02268ddc: behaviour 13's update: event kind 6 asked for and flag 0x1d of the
 * player actor 4 set, each frame. */
int OutdoorVillagerMoves_Update13(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    EventQueue_RequestKind6(villager, 0);
    PlayerActorOps_SetFlag(MOVES_PLAYER_FLAG_13, OUTDOOR_VILLAGER_PLAYER_ACTOR);
    return 0;
}
CLEAN_AS(func_ov068_02268ddc, OutdoorVillagerMoves_Update13)

/* func_ov068_02268df8: behaviour 13's start: with the town's map and an item of 0x5014 to
 * 0x501a on it (AcreTile_FindItemAllFlags, flags 1), the villager is put at the item's place
 * moved by (-0x2000, +0x8000) at height 0 (its last place too), facing the item, its mover
 * turned the same way. Then reaction 0, it stands, the watch held on the player, music value
 * 0x12, the state table's index at 0x16c set to -1, its mood's sounds off and the event
 * queue's flag 0x20 set. */
int OutdoorVillagerMoves_Start13(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    int acre_x = 0;
    int acre_z = 0;
    int x = 0;
    int z = 0;
    if (map != NULL) {
        u16 items[2] = {MOVES_ITEM_13_FIRST, MOVES_ITEM_13_LAST};
        if (AcreTile_FindItemAllFlags(map, &acre_x, &acre_z, &x, &z, &items[0], &items[1], 1, 0) != 0) {
            Vec3 item = {0, 0, 0};
            AcreTile_PositionInAcre(&item, (u32) acre_x, (u32) acre_z, (u32) x, (u32) z);
            Vec3 place = {item.x + MOVES_PLACE_DX, 0, item.z + MOVES_PLACE_DZ};
            *moves_position(villager) = place;
            *(Vec3 *) (void *) moves_at(villager, OUTDOOR_VILLAGER_LAST_POSITION) = *moves_position(villager);
            s16 *angle = (s16 *) (void *) moves_at(villager, MOVES_ANGLE);
            *angle = Vec_YawTo(&place, &item);
            *(s16 *) (void *) moves_at(villager, MOVES_WALK_ANGLE) = *angle;
            SceneMover_SetAngle((SceneMover *) (void *) moves_at(villager, MOVES_MOVER), *angle);
        }
    }
    *(u32 *) (void *) moves_at(villager, OUTDOOR_VILLAGER_REACTION) = OUTDOOR_VILLAGER_REACTION_0;
    SceneMotion_RequestStand(moves_motion(villager), MOVES_PRIORITY, data_020c80f8);
    moves_hold(villager, 1);
    Music_AddValue(MOVES_MUSIC_13, MOVES_MUSIC_13_VALUE, 0);
    VillagerState_SetIndex16C(-1);
    VillagerMood_SoundsOff(moves_mood(villager));
    EventQueue_SetFlag20();
    return 1;
}
CLEAN_AS(func_ov068_02268df8, OutdoorVillagerMoves_Start13)

/* ---- Behaviour 11 */

/* _ZN18Obj_ov068_022771c019func_ov068_02268f40Ei: behaviour 11's update: Turn11, Watch11. */
int OutdoorVillagerMoves_Update11(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276f60, /* OutdoorVillagerMoves_Turn11 */
        &data_ov068_02276e80, /* OutdoorVillagerMoves_Watch11 */
    };
    MemberTable_InitOnce(&data_ov068_02278274, data_ov068_022782fc, steps, 2);
    moves_run_step(data_ov068_022782fc, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02268f40Ei, OutdoorVillagerMoves_Update11)

/* func_ov068_02268fac: once the effect's countdown is out, step 2 and behaviour 0; else with
 * the count at 0xa06 at its limit, behaviour 21, or with the byte at 0xa05 set, behaviour 19,
 * the countdown cleared first. */
void OutdoorVillagerMoves_Watch11(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (OutdoorVillagerEffect_Countdown(moves_effect(villager)) == 0) {
        self->step = 2;
        OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
    } else if (*(const u16 *) (const void *) moves_at(villager, OUTDOOR_VILLAGER_COUNT_A06) >= data_ov068_02276724[0]) {
        OutdoorVillagerEffect_SetCountdown(moves_effect(villager), 0);
        OutdoorVillagerBehaviour_Start(self, villager, 21);
    } else if (func_ov068_0226c0e0(self, villager) != 0) {
        OutdoorVillagerEffect_SetCountdown(moves_effect(villager), 0);
        OutdoorVillagerBehaviour_Start(self, villager, 19);
    }
}
CLEAN_AS(func_ov068_02268fac, OutdoorVillagerMoves_Watch11)

/* func_ov068_02269028: once the turn (kind 3) is done, it stands; step 1. */
void OutdoorVillagerMoves_Turn11(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_done(villager, MOVES_MOTION_TURN)) {
        SceneMotion_RequestStand(moves_motion(villager), MOVES_PRIORITY, data_020c80f8);
        self->step = 1;
    }
}
CLEAN_AS(func_ov068_02269028, OutdoorVillagerMoves_Turn11)

/* func_ov068_0226906c: behaviour 11's start: a running act's effects reset
 * (OutdoorVillagerObject_ResetActEffects) after the angle to this console's player is taken, a turn to it, the
 * watch held on the player, the byte at 0x838 cleared and its mood's sounds on. */
int OutdoorVillagerMoves_Start11(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    int angle = (int) (intptr_t) SceneObject_YawToActor(villager, OUTDOOR_VILLAGER_PLAYER_ACTOR);
    OutdoorVillagerObject_ResetActEffects(villager);
    moves_request(villager, MOVES_MOTION_TURN, MOVES_PRIORITY, 0, 0, angle);
    moves_hold(villager, 1);
    VillagerSceneObject_ClearByte838(villager);
    VillagerMood_SetSoundsOn(moves_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226906c, OutdoorVillagerMoves_Start11)

/* ---- Behaviour 10 */

/* func_ov068_022690f4: behaviour 10's update: nothing. */
int OutdoorVillagerMoves_Update10(void)
{
    return 0;
}
CLEAN_AS(func_ov068_022690f4, OutdoorVillagerMoves_Update10)

/* func_ov068_022690f8: behaviour 10's start: a running act's effects reset
 * (OutdoorVillagerObject_ResetActEffects), it stands (priority 2) and the byte at 0x838 is set. */
int OutdoorVillagerMoves_Start10(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    OutdoorVillagerObject_ResetActEffects(villager);
    SceneMotion_RequestStand(moves_motion(villager), MOVES_PRIORITY_HIGH, data_020c80f8);
    VillagerSceneObject_SetByte838(villager);
    return 1;
}
CLEAN_AS(func_ov068_022690f8, OutdoorVillagerMoves_Start10)

/* ---- Behaviour 8 */

/* _ZN18Obj_ov068_022771c019func_ov068_02269128Ei: behaviour 8's update: Turn8. */
int OutdoorVillagerMoves_Update8(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[1] = {
        &data_ov068_02276e48, /* OutdoorVillagerMoves_Turn8 */
    };
    MemberTable_InitOnce(&data_ov068_0227828c, data_ov068_022782bc, steps, 1);
    moves_run_step(data_ov068_022782bc, 1, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02269128Ei, OutdoorVillagerMoves_Update8)

/* func_ov068_0226918c: once the turn (kind 3) is done, it stands (priority 2); step 1. */
void OutdoorVillagerMoves_Turn8(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_done(villager, MOVES_MOTION_TURN)) {
        SceneMotion_RequestStand(moves_motion(villager), MOVES_PRIORITY_HIGH, data_020c80f8);
        self->step = 1;
    }
}
CLEAN_AS(func_ov068_0226918c, OutdoorVillagerMoves_Turn8)

/* func_ov068_022691d0: behaviour 8's start: a running act's effects reset
 * (OutdoorVillagerObject_ResetActEffects); paired, with a reaction other than none or with the byte at 0xa04
 * set, step 1 (nothing more); else a turn (priority 2) to the event's participant (the byte at
 * 0x560) with the watch held on the player, step 0. */
int OutdoorVillagerMoves_Start8(OutdoorVillagerBehaviour *self, u8 *villager)
{
    OutdoorVillagerObject_ResetActEffects(villager);
    if (VillagerSceneObject_HasWord644(villager) != 0 ||
        *(const u32 *) (const void *) moves_at(villager, OUTDOOR_VILLAGER_REACTION) != OUTDOOR_VILLAGER_REACTION_NONE ||
        *moves_at(villager, OUTDOOR_VILLAGER_BYTE_A04) != 0) {
        self->step = 1;
        return 1;
    }
    u8 participant = *moves_at(villager, OUTDOOR_VILLAGER_PARTICIPANT);
    int angle = (int) (intptr_t) SceneObject_YawToActor(villager, participant);
    moves_request(villager, MOVES_MOTION_TURN, MOVES_PRIORITY_HIGH, 0, 0, angle);
    moves_hold(villager, 1);
    self->step = 0;
    return 1;
}
CLEAN_AS(func_ov068_022691d0, OutdoorVillagerMoves_Start8)

/* ---- Behaviour 7: coming up to this console's player */

static u8 *moves_target(OutdoorVillagerBehaviour *self)
{
    return *(u8 **) (void *) moves_at(self, MOVES_TARGET);
}

/* Gives up: behaviour 0, the word at 0xf4 1200, and its record's byte 0x1e lowered by 1
 * (`halve` 0) or halved. Its record is asked for twice. */
static void moves_give_up(OutdoorVillagerBehaviour *self, u8 *villager, int halve)
{
    OutdoorVillagerBehaviour_Start(self, villager, OUTDOOR_VILLAGER_DO_DEFAULT);
    self->unk_f4 = MOVES_GIVE_UP_FRAMES;
    if (moves_record(villager) != NULL) {
        if (halve) {
            VillagerEntry_HalveByte1E(moves_record(villager));
        } else {
            VillagerEntry_AddByte1E(moves_record(villager), -1);
        }
    }
}

/* Behaviour 21 when the count at 0xa06 is at its limit, else 19 when the byte at 0xa05 is set;
 * whether either started. */
static int moves_taken_over(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (*(const u16 *) (const void *) moves_at(villager, OUTDOOR_VILLAGER_COUNT_A06) >= data_ov068_02276724[0]) {
        OutdoorVillagerBehaviour_Start(self, villager, 21);
        return 1;
    }
    if (func_ov068_0226c0e0(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, 19);
        return 1;
    }
    return 0;
}

/* The greeting (motion kind 11), step 2, a wait of 200 frames. */
static void moves_greet(OutdoorVillagerBehaviour *self, u8 *villager)
{
    moves_request(villager, MOVES_MOTION_GREET, MOVES_PRIORITY, 0, 0, 0);
    self->step = 2;
    self->wait = MOVES_FRAMES_200;
}

/* A walk (kind 2) to the player's place, step 1, a wait of 200 frames. */
static void moves_walk_to_player(OutdoorVillagerBehaviour *self, u8 *villager)
{
    const Vec3 *at = (const Vec3 *) (const void *) moves_at(moves_target(self), OUTDOOR_VILLAGER_POSITION);
    moves_request(villager, MOVES_MOTION_WALK, MOVES_PRIORITY, at->x, at->z, 0);
    self->step = 1;
    self->wait = MOVES_FRAMES_200;
}

/* _ZN18Obj_ov068_022771c019func_ov068_02269278Ei: behaviour 7's update: Call7, Walk7, Near7,
 * Turn7, Wait7. */
int OutdoorVillagerMoves_Update7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[5] = {
        &data_ov068_022770b0, /* OutdoorVillagerMoves_Call7 */
        &data_ov068_022770c8, /* OutdoorVillagerMoves_Walk7 */
        &data_ov068_022770e8, /* OutdoorVillagerMoves_Near7 */
        &data_ov068_02277128, /* OutdoorVillagerMoves_Turn7 */
        &data_ov068_02277168, /* OutdoorVillagerMoves_Wait7 */
    };
    MemberTable_InitOnce(&data_ov068_02278280, data_ov068_022783fc, steps, 5);
    moves_run_step(data_ov068_022783fc, 5, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_02269278Ei, OutdoorVillagerMoves_Update7)

/* func_ov068_02269314: standing after a turn: unless behaviours 21 or 19 take over or the wait
 * runs: the greeting when the player is in reach (0x3000), else, once standing (kind 0) and
 * done, a walk to the player. */
void OutdoorVillagerMoves_Wait7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_taken_over(self, villager)) {
        return;
    }
    if (self->wait != 0) {
        return;
    }
    if (OutdoorVillagerMoves_PlayerInReach(self, villager, MOVES_REACH) != 0) {
        moves_greet(self, villager);
        return;
    }
    if (SceneMotion_Kind(moves_motion(villager)) != MOVES_MOTION_STAND) {
        return;
    }
    if (SceneMotion_IsDone(moves_motion(villager)) == 0) {
        return;
    }
    moves_walk_to_player(self, villager);
}
CLEAN_AS(func_ov068_02269314, OutdoorVillagerMoves_Wait7)

/* func_ov068_022693f0: once the turn (kind 3) is done, it stands and waits 10 frames (step
 * 4); until then behaviour 19 when the byte at 0xa05 is set. */
void OutdoorVillagerMoves_Turn7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_done(villager, MOVES_MOTION_TURN)) {
        SceneMotion_RequestStand(moves_motion(villager), MOVES_PRIORITY, data_020c80f8);
        self->step = 4;
        self->wait = MOVES_TURN_WAIT;
    } else if (func_ov068_0226c0e0(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, 19);
    }
}
CLEAN_AS(func_ov068_022693f0, OutdoorVillagerMoves_Turn7)

/* func_ov068_02269450: by the player: the player gone, it gives up (byte 0x1e lowered); the
 * player out of reach (0x5000) or not faced, a turn to it (step 3); else behaviours 21 or 19
 * may take over, and once the wait is out it gives up (byte 0x1e halved). */
void OutdoorVillagerMoves_Near7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_target(self) == NULL) {
        moves_give_up(self, villager, 0);
        return;
    }
    if (OutdoorVillagerMoves_PlayerInReach(self, villager, MOVES_STAY_REACH) == 0) {
        int angle = SceneObject_YawTo(villager, moves_target(self));
        moves_request(villager, MOVES_MOTION_TURN, MOVES_PRIORITY, 0, 0, angle);
        self->step = 3;
        return;
    }
    if (moves_taken_over(self, villager)) {
        return;
    }
    if (self->wait != 0) {
        return;
    }
    moves_give_up(self, villager, 1);
}
CLEAN_AS(func_ov068_02269450, OutdoorVillagerMoves_Near7)

/* func_ov068_02269548: walking to the player: the player gone, it gives up (byte 0x1e
 * lowered); in reach (0x3000), the greeting; else behaviours 21 or 19 may take over; once
 * the wait is out, or when it has gone 0xc000 from where it started, it gives up (byte 0x1e
 * halved); else its mover's start point is set to the player's place. */
void OutdoorVillagerMoves_Walk7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    SceneMover *mover = (SceneMover *) (void *) moves_at(villager, MOVES_MOVER);
    if (moves_target(self) == NULL) {
        moves_give_up(self, villager, 0);
        return;
    }
    if (OutdoorVillagerMoves_PlayerInReach(self, villager, MOVES_REACH) != 0) {
        moves_greet(self, villager);
        return;
    }
    if (moves_taken_over(self, villager)) {
        return;
    }
    if (self->wait == 0 || OutdoorVillagerMoves_NearStart(self, villager) == 0) {
        moves_give_up(self, villager, 1);
        return;
    }
    SceneMover_SetStart(mover, (const Vec3 *) (const void *) moves_at(moves_target(self), OUTDOOR_VILLAGER_POSITION));
}
CLEAN_AS(func_ov068_02269548, OutdoorVillagerMoves_Walk7)

/* func_ov068_02269684: the first step: the player gone, it gives up (byte 0x1e lowered).
 * Once animation 0xdf is done, the greeting when the player is in reach (0x3000), else a walk
 * to the player. Until then, at its frame 9, one of the two calls at random: its effect at
 * joint 16 (with the villager's angle) and its sound. */
void OutdoorVillagerMoves_Call7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (moves_target(self) == NULL) {
        moves_give_up(self, villager, 0);
        return;
    }
    if (SceneMotion_IsDone(moves_motion(villager)) != 0) {
        if (OutdoorVillagerMoves_PlayerInReach(self, villager, MOVES_REACH) != 0) {
            moves_greet(self, villager);
        } else {
            moves_walk_to_player(self, villager);
        }
        return;
    }
    if (SpeakerAnim_Number(moves_anim(villager), 0) != MOVES_ANIM_7) {
        return;
    }
    if (moves_frame(villager) != MOVES_FRAME_CALL) {
        return;
    }
    Vec3 at = *(const Vec3 *) (const void *) moves_at(villager, OUTDOOR_VILLAGER_JOINT_16_POINT);
    s16 angle = *(const s16 *) (const void *) moves_at(villager, MOVES_ANGLE);
    const MovesCall *call = &data_ov068_022767a4[MainRandom_Below(2)];
    EffectSystem_StartKind(call->effect, &at, &angle, NULL);
    SoundEmitter_Play(moves_emitter(villager), call->sound + MOVES_CALL_SOUND_BASE, MOVES_SOUND_VOLUME, 0);
}
CLEAN_AS(func_ov068_02269684, OutdoorVillagerMoves_Call7)

/* func_ov068_022697cc: whether the player's object is within `range` of the villager and
 * within data_ov068_02278264 either way of where the villager faces. */
int OutdoorVillagerMoves_PlayerInReach(OutdoorVillagerBehaviour *self, u8 *villager, int range)
{
    if (SceneObject_DistanceTo(villager, moves_target(self)) > range) {
        return 0;
    }
    int angle = SceneObject_AngleTo(villager, moves_target(self));
    return angle >= -data_ov068_02278264 && angle <= data_ov068_02278264;
}
CLEAN_AS(func_ov068_022697cc, OutdoorVillagerMoves_PlayerInReach)

/* func_ov068_02269814: whether the villager is within 0xc000 of where it started. */
int OutdoorVillagerMoves_NearStart(OutdoorVillagerBehaviour *self, u8 *villager)
{
    return Vec_Distance(moves_position(villager), (const Vec3 *) (const void *) moves_at(self, MOVES_START)) <= MOVES_WANDER;
}
CLEAN_AS(func_ov068_02269814, OutdoorVillagerMoves_NearStart)

/* func_ov068_0226983c: behaviour 7's start: a running act's effects reset
 * (OutdoorVillagerObject_ResetActEffects), the player's object (field actor 4) and its own place kept,
 * animation 0xdf, the watch held on the player, step 0 and the byte at 0x838 cleared. */
int OutdoorVillagerMoves_Start7(OutdoorVillagerBehaviour *self, u8 *villager)
{
    OutdoorVillagerObject_ResetActEffects(villager);
    *(int *) (void *) moves_at(self, MOVES_TARGET) = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    *(Vec3 *) (void *) moves_at(self, MOVES_START) = *moves_position(villager);
    SceneMotion_RequestAnimation(moves_motion(villager), MOVES_PRIORITY, MOVES_ANIM_7, 1, data_020c80f8, 0);
    moves_hold(villager, 1);
    self->step = 0;
    VillagerSceneObject_ClearByte838(villager);
    return 1;
}
CLEAN_AS(func_ov068_0226983c, OutdoorVillagerMoves_Start7)

/* ---- Behaviour 6: a gesture */

/* _ZN18Obj_ov068_022771c019func_ov068_022698d4Ei: behaviour 6's update: Wait6, Idle6. */
int OutdoorVillagerMoves_Update6(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02277090, /* OutdoorVillagerMoves_Wait6 */
        &data_ov068_022770a0, /* OutdoorVillagerMoves_Idle6 */
    };
    MemberTable_InitOnce(&data_ov068_02278268, data_ov068_0227835c, steps, 2);
    moves_run_step(data_ov068_0227835c, 2, self, villager);
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_022698d4Ei, OutdoorVillagerMoves_Update6)

/* func_ov068_02269940: nothing. */
void OutdoorVillagerMoves_Idle6(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    (void) villager;
}
CLEAN_AS(func_ov068_02269940, OutdoorVillagerMoves_Idle6)

/* func_ov068_02269944: once the action ends, its event finished and behaviour 0 the one to
 * resume; step 1. */
void OutdoorVillagerMoves_Wait6(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneAction_IsBusy(moves_action(villager)) != 0) {
        return;
    }
    EventQueue_FinishObjectEvent(villager);
    OutdoorVillagerBehaviour_SetResume(self, OUTDOOR_VILLAGER_DO_DEFAULT);
    self->step = 1;
}
CLEAN_AS(func_ov068_02269944, OutdoorVillagerMoves_Wait6)

/* func_ov068_02269978: behaviour 6's start: the gesture (its action's motion 7) by its fondness
 * for this console's player (its memory of the player, 0 without one) and its personality
 * (of its town record's NpcId): with a fondness of 0 or more, 1 for personalities 0 and 3,
 * else 0; below 0, 2 for 0 and 3, 3 for 1 and 4, else 4. It turns to the player's object (angle 0
 * without one). A running act's effects are reset (OutdoorVillagerObject_ResetActEffects) and the player's field
 * actor asked for state 0x11 before the request; then the watch held on the player. */
int OutdoorVillagerMoves_Start6(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    int player = SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    u8 *record = *(u8 **) (void *) moves_at(villager, OUTDOOR_VILLAGER_RECORD);
    VillagerMemory *memory = OutdoorVillagerRecords_MemoryOfPlayer(villager);
    int fondness = 0;
    if (memory != NULL) {
        fondness = VillagerMemoryEntry_Fondness(memory);
    }

    int gesture;
    int personality = NpcId_Personality(TownVillager_NpcId(record));
    if (fondness >= 0) {
        gesture = personality == 0 || personality == 3 ? 1 : 0;
    } else if (personality == 0 || personality == 3) {
        gesture = 2;
    } else if (personality == 1 || personality == 4) {
        gesture = 3;
    } else {
        gesture = 4;
    }

    int angle = 0;
    if (player != 0) {
        angle = SceneObject_YawTo(villager, (u8 *) (uintptr_t) (u32) player);
    }
    OutdoorVillagerObject_ResetActEffects(villager);
    FieldActor_PlayerRequestState11();
    SceneAction_RequestMotion7(moves_action(villager), gesture, 0, angle, 0);
    moves_hold(villager, 1);
    return 1;
}
CLEAN_AS(func_ov068_02269978, OutdoorVillagerMoves_Start6)
