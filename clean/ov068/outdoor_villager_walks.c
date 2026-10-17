/* Behaviours 0, 1 and 5 of a villager out walking in the town, the choice of what it does
 * next and its walker (outdoor_villager_walks.h). */
#include "outdoor_villager_walks.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/fx_math.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "itcm/vector.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/npc_lookup.h"
#include "main/obj_020d8c64.h"
#include "main/path_walker.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_value_3aa.h"
#include "main/session_players.h"
#include "main/sky.h"
#include "main/tile_requests.h"
#include "main/town_villager.h"
#include "main/villager_entry.h"
#include "main/villager_errand_catch.h"
#include "main/villager_home.h"
#include "main/villager_mode_record.h"
#include "main/villager_mood.h"
#include "main/villager_scene_held.h"
#include "main/villager_scene_object.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "ov003/field_actor.h"
#include "ov004/member_pointer.h"
#include "outdoor_villager.h"
#include "outdoor_villager_watch.h"

extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The word its motion requests carry, the range of its looks and the point they are given (the
 * origin). */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* How far either way of facing it a villager counts as in view (SceneLook_Within). */
extern s16 data_020c80f0;
/* The field camera (null without one) and the point it looks at (main's camera_view.c). */
extern void *data_021c67a4;
extern const Vec3 data_021c67d0;
/* The random numbers of the field. */
extern Random data_021cb5a0;
/* The town's map (acre_map.h), or null. */
extern AcreMap *data_021c80bc;
/* A null member pointer (the C++ runtime's). */
extern const MemberPointer __ptmf_null;

/* The count at 0xa06 at which behaviour 21 takes over (100). */
extern s16 data_ov068_02276724[];
/* The walker's kinds drawn when it has none to go to (0, 2 and 4). */
extern const s32 data_ov068_022767ac[3];
/* The frames before a villager may be paired again (1200). */
extern const u32 data_ov068_0227673c;
/* Behaviour 1's tables of catches (VillagerErrandCatch_Update). */
extern const u8 data_ov068_0227677c[];
extern const u8 data_ov068_02276734[];
/* Behaviour 0's draw hook (OutdoorVillagerObject_DrawWithItem: drawn with its held item link). */
extern const MemberPointer data_ov068_022770a8;

/* Behaviour 5's update's step table (filled once, bit 0 of its guard), and the member pointers
 * it is filled from. */
extern u32 data_ov068_0227829c;
extern MemberPointer data_ov068_0227831c[2];
extern const MemberPointer data_ov068_02276e98, data_ov068_02276f20;

/* The behaviour member's and the villager's functions used here (outdoor_villager.h has more). */
/* Whether behaviour 7 calls this console's player over. */
int OutdoorVillagerBehaviour_CallsPlayer(OutdoorVillagerBehaviour *self, u8 *villager);
/* Once a minute of the clock, in a contest, a catch drawn that may beat the event's winner's. */
void OutdoorVillagerRecords_EachMinute(u8 *villager);
/* The kind of the moment of its state entry redrawn (byte 0x1c). */
void OutdoorVillagerRecords_RedrawKind(u8 *villager);

/* The parts of the villager read here besides outdoor_villager.h's (main's scene_object.c). */
#define WALKS_ANGLE 0x8e      /* s16: where it faces */
#define WALKS_WALK_ANGLE 0x94 /* s16: where it walks */
#define WALKS_SPEED 0x98      /* fx32 */
#define WALKS_MOVER 0x350     /* SceneMover */
#define WALKS_VALUE_3AA 0x3aa /* SceneValue3aa */
#define WALKS_ENABLED 0x561   /* u8 */
#define WALKS_POSED 0x562     /* u8 */
#define WALKS_DRAW_HOOK 0x8b0 /* MemberPointer: called to draw in place of the plain joints */
#define WALKS_ITEM_SHOWN 0x9f0
#define WALKS_BYTE_A04 0xa04
#define WALKS_BYTE_A05 0xa05
#define WALKS_TOWN_RECORD 0x830 /* u8 *: its town record */
/* The parts of the behaviour member read here besides outdoor_villager.h's. */
#define WALKS_ITEM_CHECK 0x34  /* s16: frames to the next redraw of the kind of the moment */
#define WALKS_ITEM_HOLD 0x36   /* s16: while it and the check run, only the weather counts */
#define WALKS_WALKER 0x3c      /* PathWalker */
#define WALKS_WALK_TIME 0xd8   /* s16: frames left of the walker's walk, -1 before it starts */
#define WALKS_STEP_TIME 0xda   /* s16: frames to behaviour 1's next step */
#define WALKS_PAUSE 0xdc       /* s16: frames it stands watching */
#define WALKS_PAUSE_AGAIN 0xde /* s16: frames before it may stop to watch again */
#define WALKS_RAISE 0xf8       /* s32: frames to the next raise of the record's byte 0x1e */

#define WALKS_FLAG_1_PLAYER 1 /* the current player's flag that keeps villagers out late */
#define WALKS_PRIORITY 1
#define WALKS_MOTION_STAND 0
#define WALKS_MOTION_WALK 1
#define WALKS_MOTION_WALK_2 2
#define WALKS_MOTION_TURN_WALK 4
#define WALKS_NO_ITEM 0xfff1
#define WALKS_STATE_UNSET (-1)
#define WALKS_WALK_FRAMES 6000
#define WALKS_STEP_FRAMES 40
#define WALKS_RAISE_FRAMES 900
#define WALKS_PAUSE_AGAIN_FRAMES 1200
#define WALKS_PAUSE_BASE 160
#define WALKS_PAUSE_SPREAD 200
#define WALKS_SEEN_FRAMES 15
#define WALKS_STEP_WAIT 0x100
#define WALKS_TURN_WAIT 0x128
#define WALKS_GRADE_BLOCKED 2 /* SceneValue3aa_Grade's answer when it may not walk */
#define WALKS_EVENT_NEAR 0xc000
#define WALKS_EVENT_NEAR_WALKING 0x8000
#define WALKS_ITEM_FRAMES 12000
#define WALKS_ITEM_CHANGE_FRAMES 300
#define WALKS_ITEM_FIRST_FRAMES 6000
#define WALKS_UMBRELLA_FIRST 0x1380
#define WALKS_UMBRELLA_LAST 0x139f
#define WALKS_ITEM_1378 0x1378
#define WALKS_KIND_NONE 7 /* no kind of the moment (VillagerState_GetByte1C) */
#define WALKS_KIND_6 6
#define WALKS_ITEM_MARKED 0x1566
#define WALKS_MARKED_NEAR 0xb00
#define WALKS_HOME_NEAR 0x800
#define WALKS_PARTNER_NEAR 0x3000
#define WALKS_SHOWN_NEAR 0x6000
#define WALKS_SHOWN_STATUS_MAX 1
#define WALKS_PAIR_ONE_IN 5
#define WALKS_WALKER_HOME 3
#define WALKS_WALKER_KIND_6 6
#define WALKS_WALKER_KINDS 3
#define WALKS_WALKER_NONE 7
#define WALKS_TALK_STEP_DONE 1

/* Behaviours started here. */
#define WALKS_DO_WALK 0
#define WALKS_DO_OFF_SCREEN 1
#define WALKS_DO_GO_IN 2
#define WALKS_DO_IN 3
#define WALKS_DO_PAIRED 9
#define WALKS_DO_EFFECT 11
#define WALKS_DO_ITEM_OUT 15
#define WALKS_DO_ITEM_AWAY 16
#define WALKS_DO_MARKED 17
#define WALKS_DO_BYTE_A05 19
#define WALKS_DO_COUNT_A06 21
#define WALKS_DO_SHOWN 23
#define WALKS_DO_CALL 7

static u8 *walks_at(void *object, u32 offset)
{
    return (u8 *) object + offset;
}

static s16 *walks_half(void *object, u32 offset)
{
    return (s16 *) (void *) walks_at(object, offset);
}

static s32 *walks_word(void *object, u32 offset)
{
    return (s32 *) (void *) walks_at(object, offset);
}

static SceneMotion *walks_motion(u8 *villager)
{
    return (SceneMotion *) (void *) walks_at(villager, OUTDOOR_VILLAGER_MOTION);
}

static SceneAction *walks_action(u8 *villager)
{
    return (SceneAction *) (void *) walks_at(villager, OUTDOOR_VILLAGER_ACTION);
}

static VillagerMood *walks_mood(u8 *villager)
{
    return (VillagerMood *) (void *) walks_at(villager, OUTDOOR_VILLAGER_MOOD);
}

static SceneLook *walks_look(u8 *villager)
{
    return (SceneLook *) (void *) walks_at(villager, OUTDOOR_VILLAGER_LOOK);
}

static OutdoorVillagerWatch *walks_watch(u8 *villager)
{
    return (OutdoorVillagerWatch *) (void *) walks_at(villager, OUTDOOR_VILLAGER_WATCH);
}

static Vec3 *walks_position(u8 *villager)
{
    return (Vec3 *) (void *) walks_at(villager, OUTDOOR_VILLAGER_POSITION);
}

static Footsteps *walks_footsteps(u8 *villager)
{
    return (Footsteps *) (void *) walks_at(villager, OUTDOOR_VILLAGER_FOOTSTEPS);
}

static PathWalker *walks_walker(OutdoorVillagerBehaviour *self)
{
    return (PathWalker *) (void *) walks_at(self, WALKS_WALKER);
}

/* The code at vtable slot `slot` of `object`. */
static uintptr_t walks_slot(u8 *object, u32 slot)
{
    u32 vtable = *(const u32 *) (const void *) object;
    return *(const u32 *) (uintptr_t) (vtable + slot);
}

/* Its town record (vtable slot 0x64), or null. */
static u8 *walks_record(u8 *villager)
{
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *)) walks_slot(villager, OUTDOOR_VILLAGER_SLOT_RECORD))(villager);
}

/* The motion asked to stand. */
static void walks_stand(u8 *villager)
{
    SceneMotion_RequestStand(walks_motion(villager), WALKS_PRIORITY, data_020c80f8);
}

/* The watch held on `kind` (1: this console's player, 0: nothing). */
static void walks_hold(u8 *villager, int kind)
{
    OutdoorVillagerWatch_Hold(walks_watch(villager), villager, kind, 0, 0, &data_021fbee8, OUTDOOR_VILLAGER_PLAYER_ACTOR,
                              data_020c814c, 1);
}

/* The walker started afresh (state `state`), its walk's time unset. */
static void walks_restart(OutdoorVillagerBehaviour *self, int state, u8 *villager)
{
    OutdoorVillagerWalks_StartWalker(self, state, villager);
    *walks_half(self, WALKS_WALK_TIME) = WALKS_STATE_UNSET;
    *walks_half(self, WALKS_STEP_TIME) = 0;
}

/* A walker's step from the villager's position; the walk's time starts on its first step. */
static void walks_step(OutdoorVillagerBehaviour *self, Vec3 *point)
{
    if (PathWalker_Step(walks_walker(self), point) != 0 && *walks_half(self, WALKS_WALK_TIME) == WALKS_STATE_UNSET) {
        *walks_half(self, WALKS_WALK_TIME) = WALKS_WALK_FRAMES;
    }
}

/* Whether the angle from the villager's facing to `point` is within a quarter turn. */
static int walks_facing(u8 *villager, const Vec3 *point)
{
    s16 yaw = Vec_YawTo(walks_position(villager), point);
    s16 angle = *walks_half(villager, WALKS_ANGLE);
    return SceneObject_IsWithinQuarterTurn((s16) (yaw - angle));
}

/* Its state entry's flag 1 (that sends it home).
 * REQUIRES: the record has a state entry. */
static int walks_flag_1(u8 *record)
{
    return (VillagerStatus_StateEntry(record)->flags & VILLAGER_STATE_FLAG_1) != 0;
}

/* The current player's flag 1 (0 without a current player). */
static int walks_player_flag_1(void)
{
    u8 *current = PlayerRecords_Current();
    return current != NULL ? PlayerRecord_TestFlag(current, WALKS_FLAG_1_PLAYER) : 0;
}

/* The kind of the moment of a record's state entry (byte 0x1c), 7 without a valid record. */
static int walks_kind(u8 *record, int kind)
{
    if (record != NULL && NpcId_IsValid(TownVillager_NpcId(record)) != 0 && VillagerStatus_StateEntry(record) != NULL) {
        kind = VillagerState_GetByte1C(VillagerStatus_StateEntry(record));
    }
    return kind;
}

/* Two item codes the same, by their variant item when the first has variants. */
static int walks_same_item(const u16 *a, const u16 *b)
{
    if (ItemCode_HasVariant(a)) {
        int variant = ItemCode_VariantItem(a);
        return variant == ItemCode_VariantItem(b);
    }
    return *a == *b;
}

static int walks_is_umbrella(u16 item)
{
    return item >= WALKS_UMBRELLA_FIRST && item <= WALKS_UMBRELLA_LAST;
}

/* Behaviour `index` started, the one to resume `resume`. */
static void walks_start_then(OutdoorVillagerBehaviour *self, u8 *villager, int index, int resume)
{
    OutdoorVillagerBehaviour_Start(self, villager, index);
    OutdoorVillagerBehaviour_SetResume(self, resume);
}

/* ---- Behaviour 5: its talk */

/* _ZN18Obj_ov068_022771c019func_ov068_0226af00Ei: behaviour 5's update: End5, Idle5. */
int OutdoorVillagerWalks_Update5(OutdoorVillagerBehaviour *self, u8 *villager)
{
    static const MemberPointer *const steps[2] = {
        &data_ov068_02276e98, /* OutdoorVillagerWalks_End5 */
        &data_ov068_02276f20, /* OutdoorVillagerWalks_Idle5 */
    };
    MemberTable_InitOnce(&data_ov068_0227829c, data_ov068_0227831c, steps, 2);
    if (self->step < 2) {
        const MemberPointer *member = &data_ov068_0227831c[self->step];
        void *object = MemberPointer_Object(member, self);
        ((void (*)(void *, u8 *))(uintptr_t) MemberPointer_Code(member, object))(object, villager);
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_022771c019func_ov068_0226af00Ei, OutdoorVillagerWalks_Update5)

/* func_ov068_0226af6c: nothing (after the talk). */
void OutdoorVillagerWalks_Idle5(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    (void) villager;
}
CLEAN_AS(func_ov068_0226af6c, OutdoorVillagerWalks_Idle5)

/* func_ov068_0226af70: once its action is no longer busy: its mood applied, the object event
 * finished, unpaired; step 1. */
void OutdoorVillagerWalks_End5(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (SceneAction_IsBusy(walks_action(villager)) != 0) {
        return;
    }
    VillagerMood_Apply(walks_mood(villager));
    EventQueue_FinishObjectEvent(villager);
    VillagerSceneObject_SetWord644((u32 *) (void *) villager, 0);
    VillagerSceneObject_SetByte648(villager, 0);
    self->step = WALKS_TALK_STEP_DONE;
}
CLEAN_AS(func_ov068_0226af70, OutdoorVillagerWalks_End5)

/* func_ov068_0226afb8: behaviour 5's start: a running act's effects reset and its last motion
 * number cleared. Paired: it talks (motion reset). With the byte at 0xa04: it talks where it
 * is, the watch held on this console's player. Else the watch held on the player and it turns
 * to the object its talk's motion names (angle 0 without one) and talks. Always 1. */
int OutdoorVillagerWalks_Start5(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    OutdoorVillagerObject_ResetActEffects(villager);
    Obj020d8c64_ClearLastMotionNumber(villager);
    if (VillagerSceneObject_HasWord644(villager) != 0) {
        SceneAction_RequestTalk(walks_action(villager), 1, 0);
        return 1;
    }
    if (*walks_at(villager, WALKS_BYTE_A04) != 0) {
        SceneAction_RequestTalk(walks_action(villager), 0, 0);
        walks_hold(villager, 1);
        return 1;
    }
    int object = SceneBase_MotionArg((SceneBase *) (void *) walks_at(villager, OUTDOOR_VILLAGER_TALK));
    int angle = 0;
    if (object != 0) {
        angle = SceneObject_YawTo(villager, (u8 *) (uintptr_t) (u32) object);
    }
    walks_hold(villager, 1);
    SceneAction_RequestTurnAndTalk(walks_action(villager), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov068_0226afb8, OutdoorVillagerWalks_Start5)

/* ---- Behaviour 1: off screen */

/* func_ov068_0226ba10: behaviour 1's update. Back on screen: behaviour 0. Else it may catch
 * (VillagerErrandCatch_Update), its talk lines' records kept (OutdoorVillagerRecords_EachMinute), and every
 * 900 frames its record's byte 0x1e rises. A walker that stopped or ran out of time starts
 * afresh (state 1). While it walks: at its door, behaviour 3; unless going home, it turns home
 * when it is time (TimeToGoHome); every 40 frames a step of the walker. Always 1. */
int OutdoorVillagerWalks_Update1(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (OutdoorVillagerWalks_OnScreen(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_WALK);
        return 1;
    }
    VillagerErrandCatch_Update(villager, (int) (uintptr_t) data_ov068_0227677c, (int) (uintptr_t) data_ov068_02276734, 1);
    OutdoorVillagerRecords_EachMinute(villager);
    if (*walks_word(self, WALKS_RAISE) == 0) {
        if (walks_record(villager) != NULL) {
            VillagerEntry_RaiseByte1E(walks_record(villager), NULL);
        }
        *walks_word(self, WALKS_RAISE) = WALKS_RAISE_FRAMES;
    }
    if (PathWalker_IsWalking(walks_walker(self)) == 0 || *walks_half(self, WALKS_WALK_TIME) == 0) {
        walks_restart(self, 1, villager);
    }
    if (PathWalker_IsWalking(walks_walker(self)) == 0) {
        return 1;
    }
    if (OutdoorVillagerWalks_AtHome(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_IN);
        return 1;
    }
    if (PathWalker_Status(walks_walker(self)) != WALKS_WALKER_HOME && OutdoorVillagerWalks_TimeToGoHome(self, villager) != 0) {
        PathWalker_Start(walks_walker(self), walks_position(villager), WALKS_WALKER_HOME, 1, villager);
        *walks_half(self, WALKS_STEP_TIME) = 0;
    }
    if (*walks_half(self, WALKS_STEP_TIME) != 0) {
        return 1;
    }
    walks_step(self, walks_position(villager));
    *walks_half(self, WALKS_STEP_TIME) = WALKS_STEP_FRAMES;
    return 1;
}
CLEAN_AS(func_ov068_0226ba10, OutdoorVillagerWalks_Update1)

/* func_ov068_0226bb3c: behaviour 1's start: a running act's effects reset, the watch held on
 * nothing, it stands; the wait 0, no draw hook, no footsteps, the step time 0 and the raise
 * timer 900; a walker that walks goes on in state 1, else it starts afresh (state 1); the
 * held item not shown, its mood's sounds off. */
int OutdoorVillagerWalks_Start1(OutdoorVillagerBehaviour *self, u8 *villager)
{
    OutdoorVillagerObject_ResetActEffects(villager);
    walks_hold(villager, 0);
    walks_stand(villager);
    self->wait = 0;
    *(MemberPointer *) (void *) walks_at(villager, WALKS_DRAW_HOOK) = __ptmf_null;
    Footsteps_Disable(walks_footsteps(villager));
    *walks_half(self, WALKS_STEP_TIME) = 0;
    *walks_word(self, WALKS_RAISE) = WALKS_RAISE_FRAMES;
    if (PathWalker_IsWalking(walks_walker(self)) != 0) {
        PathWalker_SetState(walks_walker(self), 1);
    } else {
        walks_restart(self, 1, villager);
    }
    *walks_at(villager, WALKS_ITEM_SHOWN) = 0;
    VillagerMood_SoundsOff(walks_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226bb3c, OutdoorVillagerWalks_Start1)

/* ---- Behaviour 0: walking about */

/* Once the motion is done: the pause to watch ends unless the watch still follows an insect
 * or a fish shadow it has seen for 15 frames or more and still sees; while it stands paused,
 * nothing more. Else it stands (when it may not walk, and seven frames in eight), or walks a
 * step of its walker: kind 1 (or 2 one time in four when byte 0x18 of its state entry is
 * clear) within a quarter turn of its facing, else kind 4 turning first, and the wait 0x100
 * or 0x128. It stands rather than cross the line between the player and an object event's
 * object near (0xc000). */
static void walks_after_motion(OutdoorVillagerBehaviour *self, u8 *villager)
{
    SceneMotion *motion = walks_motion(villager);
    s16 *pause = walks_half(self, WALKS_PAUSE);
    if (*pause > 0) {
        OutdoorVillagerWatch *watch = walks_watch(villager);
        int keep = 0;
        if (watch->held == 0 && (watch->mode == OUTDOOR_VILLAGER_WATCH_INSECT || watch->mode == OUTDOOR_VILLAGER_WATCH_FISH)) {
            keep = watch->seen >= WALKS_SEEN_FRAMES && SceneLook_CanSee(walks_look(villager), villager) != 0;
        }
        if (!keep) {
            *pause = 0;
            *walks_half(self, WALKS_PAUSE_AGAIN) = WALKS_PAUSE_AGAIN_FRAMES;
            OutdoorVillagerWatch_LookAtPlayer(watch, villager);
        }
    }
    if (SceneMotion_Kind(motion) == WALKS_MOTION_STAND && *pause != 0) {
        return;
    }
    *pause = 0;
    if (SceneValue3aa_Grade((SceneValue3aa *) (void *) walks_at(villager, WALKS_VALUE_3AA)) == WALKS_GRADE_BLOCKED) {
        walks_stand(villager);
        return;
    }
    if ((Random_Next(&data_021cb5a0) & 7) != 0) {
        walks_stand(villager);
        return;
    }
    Vec3 *position = walks_position(villager);
    Vec3 point = data_021fbee8;
    if (OutdoorVillagerWalks_StepWalker(self, &point, villager) == 0) {
        walks_stand(villager);
        return;
    }
    if (OutdoorVillagerWalks_NearEvent(self, position, WALKS_EVENT_NEAR) != 0 &&
        OutdoorVillagerWalks_CrossesEventTo(self, &point, position) != 0) {
        walks_stand(villager);
        return;
    }
    s16 yaw = Vec_YawTo(position, &point);
    if (SceneObject_IsWithinQuarterTurn((s16) (yaw - *walks_half(villager, WALKS_ANGLE))) != 0) {
        int kind = WALKS_MOTION_WALK;
        if (MainRandom_Below(4) == 0 && OutdoorVillagerRecords_Byte18(villager) == 0) {
            kind = WALKS_MOTION_WALK_2;
        }
        SceneMotion_Request(motion, kind, WALKS_PRIORITY, point.x, point.z, 0, 0, 0, 0, data_020c80f8, 0);
        self->wait = WALKS_STEP_WAIT;
        return;
    }
    SceneMotion_Request(motion, WALKS_MOTION_TURN_WALK, WALKS_PRIORITY, point.x, point.z, 0, yaw, 0, 0, data_020c80f8, 0);
    self->wait = WALKS_TURN_WAIT;
}

/* While a motion runs and the villager moves with a walk (kinds 1, 2, 4): it stands when its
 * wait is out; to watch, for 160 to 359 frames (then not again for 1200), when its watch
 * follows an insect or a fish shadow it has seen for more than 15 frames; when it walks into
 * the line between the player and an object event's object near (0x8000); when its mover's
 * end is more than a quarter turn from its facing. */
static void walks_while_walking(OutdoorVillagerBehaviour *self, u8 *villager)
{
    SceneMotion *motion = walks_motion(villager);
    if (*walks_word(villager, WALKS_SPEED) == 0) {
        return;
    }
    if (!(SceneMotion_Kind(motion) == WALKS_MOTION_WALK || SceneMotion_Kind(motion) == WALKS_MOTION_WALK_2 ||
          SceneMotion_Kind(motion) == WALKS_MOTION_TURN_WALK)) {
        return;
    }
    if (self->wait == 0) {
        walks_stand(villager);
        return;
    }
    OutdoorVillagerWatch *watch = walks_watch(villager);
    if (*walks_half(self, WALKS_PAUSE_AGAIN) == 0 && watch->held == 0 && watch->mode <= OUTDOOR_VILLAGER_WATCH_FISH &&
        watch->seen > WALKS_SEEN_FRAMES) {
        walks_stand(villager);
        *walks_half(self, WALKS_PAUSE) = (s16) (MainRandom_Below(WALKS_PAUSE_SPREAD) + WALKS_PAUSE_BASE);
        *walks_half(self, WALKS_PAUSE_AGAIN) = WALKS_PAUSE_AGAIN_FRAMES;
        return;
    }
    if (OutdoorVillagerWalks_NearEvent(self, walks_position(villager), WALKS_EVENT_NEAR_WALKING) != 0 &&
        OutdoorVillagerWalks_CrossesEventAhead(self, villager) != 0) {
        walks_stand(villager);
        return;
    }
    Vec3 end = *SceneMover_End((SceneMover *) (void *) walks_at(villager, WALKS_MOVER));
    if (walks_facing(villager, &end) == 0) {
        walks_stand(villager);
    }
}

/* func_ov068_0226bc1c: behaviour 0's update: off screen, behaviour 1; else unless the choice
 * starts another behaviour, its walk (walks_after_motion, walks_while_walking). Always 0. */
int OutdoorVillagerWalks_Update0(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (OutdoorVillagerWalks_OnScreen(self, villager) == 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_OFF_SCREEN);
        return 0;
    }
    if (OutdoorVillagerWalks_Choose(self, villager) != 0) {
        return 0;
    }
    if (SceneMotion_IsDone(walks_motion(villager)) != 0) {
        walks_after_motion(self, villager);
    } else {
        walks_while_walking(self, villager);
    }
    return 0;
}
CLEAN_AS(func_ov068_0226bc1c, OutdoorVillagerWalks_Update0)

/* func_ov068_0226befc: what the villager does next, the first that applies: at its door going
 * home, behaviour 2 (16 first, 2 to resume, with a held item); on a marked item 0x1566, 17; the
 * count at 0xa06 at its limit, 21; the byte at 0xa05, 19; behaviour 7's call, 7; a pairing
 * (TryPair starts 9); its effect's countdown, 11; a change of its held item (ChangeHeldItem
 * starts 15 or 16); the player showing an insect or a fish, 23; moving, a step aside
 * (StepAside). Whether one applied. */
int OutdoorVillagerWalks_Choose(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (OutdoorVillagerWalks_AtHome(self, villager) != 0) {
        u16 item;
        VillagerSceneHeld_Item(&item, villager);
        if (item != WALKS_NO_ITEM) {
            walks_start_then(self, villager, WALKS_DO_ITEM_AWAY, WALKS_DO_GO_IN);
        } else {
            OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_GO_IN);
        }
        return 1;
    }
    if (OutdoorVillagerWalks_OnMarkedTile(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_MARKED);
        return 1;
    }
    if (*(const u16 *) (const void *) walks_at(villager, OUTDOOR_VILLAGER_COUNT_A06) >= data_ov068_02276724[0]) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_COUNT_A06);
        return 1;
    }
    if (OutdoorVillagerWalks_HasByteA05(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_BYTE_A05);
        return 1;
    }
    if (OutdoorVillagerBehaviour_CallsPlayer(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_CALL);
        return 1;
    }
    if (OutdoorVillagerWalks_TryPair(self, villager) != 0) {
        return 1;
    }
    if (OutdoorVillagerEffect_Countdown((OutdoorVillagerEffect *) (void *) walks_at(villager, OUTDOOR_VILLAGER_EFFECT)) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_EFFECT);
        return 1;
    }
    if (OutdoorVillagerWalks_ChangeHeldItem(self, villager) != 0) {
        return 1;
    }
    if (OutdoorVillagerWalks_WatchShown(self, villager) != 0) {
        OutdoorVillagerBehaviour_Start(self, villager, WALKS_DO_SHOWN);
        return 1;
    }
    if (*walks_word(villager, WALKS_SPEED) != 0 && OutdoorVillagerWalks_StepAside(self, villager) != 0) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov068_0226befc, OutdoorVillagerWalks_Choose)

/* func_ov068_0226c034: whether to watch what this console's player shows (behaviour 23): not
 * yet shown (`shown`), byte 0x18 of its state entry 0 or 1, the player showing an insect or a
 * fish, its look on the player, the player within 0x6000, seen and looked at. */
int OutdoorVillagerWalks_WatchShown(OutdoorVillagerBehaviour *self, u8 *villager)
{
    u8 status = OutdoorVillagerRecords_Byte18(villager);
    if (self->shown != 0 || status > WALKS_SHOWN_STATUS_MAX) {
        return 0;
    }
    if (OutdoorVillagerWalks_PlayerShowsCatch(self) == 0) {
        return 0;
    }
    if (walks_look(villager)->kind != SCENE_LOOK_PLAYER) {
        return 0;
    }
    if (SceneObject_DistanceToActor(villager, OUTDOOR_VILLAGER_PLAYER_ACTOR) > WALKS_SHOWN_NEAR) {
        return 0;
    }
    if (SceneLook_CanSee(walks_look(villager), villager) == 0) {
        return 0;
    }
    return SceneLook_IsOnTarget(walks_look(villager)) != 0;
}
CLEAN_AS(func_ov068_0226c034, OutdoorVillagerWalks_WatchShown)

/* func_ov068_0226c0a4: whether this console's player shows an insect (0x12b0 to 0x12e7) or a
 * fish (0x12e8 to 0x131f). */
int OutdoorVillagerWalks_PlayerShowsCatch(OutdoorVillagerBehaviour *self)
{
    (void) self;
    u32 item = FieldActor_PlayerShownItem();
    return item >= 0x12b0 && item <= 0x131f;
}
CLEAN_AS(func_ov068_0226c0a4, OutdoorVillagerWalks_PlayerShowsCatch)

/* func_ov068_0226c0e0: whether the byte at 0xa05 is set (behaviour 19). */
int OutdoorVillagerWalks_HasByteA05(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    return villager[WALKS_BYTE_A05] != 0;
}
CLEAN_AS(func_ov068_0226c0e0, OutdoorVillagerWalks_HasByteA05)

/* func_ov068_0226c0f4: whether the villager stands on a marked item 0x1566 (TileMarked),
 * within 0xb00 of its tile's centre, and a request of the tile (TileRequests_AskMarked1566,
 * with its person index) answers 1 at once (the request then released). */
int OutdoorVillagerWalks_OnMarkedTile(OutdoorVillagerBehaviour *self, u8 *villager)
{
    Vec3 *position = walks_position(villager);
    int result = 0;
    TileRequestTile tile = {0, 0};
    Position_Tile(&tile.x, &tile.z, (const Position *) (const void *) position);
    if (OutdoorVillagerWalks_TileMarked(self, &tile) == 0) {
        return 0;
    }
    Vec3 centre;
    AcreTile_SnapToTileCentre(&centre, position);
    if (Vec_DistanceXZ(&centre, position) > WALKS_MARKED_NEAR) {
        return 0;
    }
    TileRequestTile asked = tile;
    int request = TileRequests_AskMarked1566((s8) (u8) SceneObject_PersonIndex(villager), &asked);
    if (request >= 0) {
        if (TileRequests_Answer((u32) request) == 1) {
            result = 1;
        }
        TileRequests_Release(request);
    }
    return result;
}
CLEAN_AS(func_ov068_0226c0f4, OutdoorVillagerWalks_OnMarkedTile)

/* func_ov068_0226c170: whether the town's tile holds item 0x1566, marked (AcreTile_IsMarked);
 * 0 without the town's map or the tile. */
int OutdoorVillagerWalks_TileMarked(OutdoorVillagerBehaviour *self, TileRequestTile *tile)
{
    (void) self;
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        return 0;
    }
    int x = tile->x;
    int z = tile->z;
    u16 *item = AcreTile_ItemInAcre(map, (u32) (x >> 4), (u32) (z >> 4), x & 15, z & 15, 0);
    if (item == NULL) {
        return 0;
    }
    return *item == WALKS_ITEM_MARKED && AcreTile_IsMarked(map, tile->x, tile->z) != 0;
}
CLEAN_AS(func_ov068_0226c170, OutdoorVillagerWalks_TileMarked)

/* func_ov068_0226c1dc: a change of the held item, while the villager stands after a motion.
 * Unless both the check (0x34) and the hold (0x36) run: when the check is out the kind of the
 * moment is redrawn (and the check set to 12000); with no item it takes the kind's item, or
 * its umbrella when rain falls and the kind gives none or item 0x1378 (behaviour 15, then 0);
 * with an umbrella and no rain, or an item not the kind's, it puts it away (behaviour 16, then
 * 0, the hold 300). While both run only the weather counts: no item in rain, its umbrella
 * out; an umbrella (or item 0x1378) without (or with) rain, or an item not the kind's, away.
 * Whether it started a behaviour. */
int OutdoorVillagerWalks_ChangeHeldItem(OutdoorVillagerBehaviour *self, u8 *villager)
{
    SceneMotion *motion = walks_motion(villager);
    if (SceneMotion_Kind(motion) != WALKS_MOTION_STAND || SceneMotion_IsDone(motion) == 0) {
        return 0;
    }
    u8 *record = walks_record(villager);
    int falling = Sky_Falling();
    int kind = walks_kind(record, WALKS_KIND_NONE);
    DateTime now = {0};
    DateTime_Now(&now);
    s16 *check = walks_half(self, WALKS_ITEM_CHECK);
    s16 *hold = walks_half(self, WALKS_ITEM_HOLD);
    int raining = falling == SKY_FALLING_RAIN;

    if (*check == 0 || *hold == 0) {
        if (*check == 0) {
            OutdoorVillagerRecords_RedrawKind(villager);
            kind = walks_kind(record, kind);
            *check = WALKS_ITEM_FRAMES;
        }
        u16 held;
        VillagerSceneHeld_Item(&held, villager);
        if (held == WALKS_NO_ITEM) {
            u16 want = WALKS_NO_ITEM;
            if (VillagerModeRecord_IsKindMode((unsigned int) kind) != 0) {
                u16 kind_item;
                VillagerModeRecord_KindItem(&kind_item, kind);
                want = kind_item;
            }
            if ((want == WALKS_NO_ITEM || want == WALKS_ITEM_1378) && raining) {
                u16 umbrella;
                TownVillager_Item1380(&umbrella, record);
                want = umbrella;
            }
            *hold = -1;
            if (want == WALKS_NO_ITEM) {
                return 0;
            }
            VillagerSceneHeld_SetItem(villager, &want);
            walks_start_then(self, villager, WALKS_DO_ITEM_OUT, WALKS_DO_WALK);
            return 1;
        }
        VillagerSceneHeld_Item(&held, villager);
        if (walks_is_umbrella(held)) {
            if (raining) {
                return 0;
            }
            *hold = WALKS_ITEM_CHANGE_FRAMES;
            walks_start_then(self, villager, WALKS_DO_ITEM_AWAY, WALKS_DO_WALK);
            return 1;
        }
        u16 kind_item;
        VillagerModeRecord_KindItem(&kind_item, kind);
        VillagerSceneHeld_Item(&held, villager);
        if (!walks_same_item(&kind_item, &held)) {
            walks_start_then(self, villager, WALKS_DO_ITEM_AWAY, WALKS_DO_WALK);
            *hold = WALKS_ITEM_CHANGE_FRAMES;
            return 1;
        }
        *hold = -1;
        return 0;
    }

    u16 held;
    VillagerSceneHeld_Item(&held, villager);
    if (held == WALKS_NO_ITEM) {
        if (!raining) {
            return 0;
        }
        u16 umbrella;
        TownVillager_Item1380(&umbrella, record);
        VillagerSceneHeld_SetItem(villager, &umbrella);
        walks_start_then(self, villager, WALKS_DO_ITEM_OUT, WALKS_DO_WALK);
        *hold = -1;
        return 1;
    }
    VillagerSceneHeld_Item(&held, villager);
    if (walks_is_umbrella(held)) {
        if (raining) {
            return 0;
        }
        *hold = WALKS_ITEM_CHANGE_FRAMES;
        walks_start_then(self, villager, WALKS_DO_ITEM_AWAY, WALKS_DO_WALK);
        return 1;
    }
    VillagerSceneHeld_Item(&held, villager);
    if (held == WALKS_ITEM_1378 && raining) {
        walks_start_then(self, villager, WALKS_DO_ITEM_AWAY, WALKS_DO_WALK);
        *hold = WALKS_ITEM_CHANGE_FRAMES;
        return 1;
    }
    u16 kind_item;
    VillagerSceneHeld_Item(&held, villager);
    VillagerModeRecord_KindItem(&kind_item, kind);
    if (walks_same_item(&held, &kind_item)) {
        return 0;
    }
    walks_start_then(self, villager, WALKS_DO_ITEM_AWAY, WALKS_DO_WALK);
    *hold = WALKS_ITEM_CHANGE_FRAMES;
    return 1;
}
CLEAN_AS(func_ov068_0226c1dc, OutdoorVillagerWalks_ChangeHeldItem)

/* func_ov068_0226c520: one time in five, when the villager may pair (its vtable slot 0xb4) and
 * a villager near and in view (FindPartner) pairs with it (that one's slot 0xb8): it is
 * paired with that one (the byte at 0x648 cleared), its behaviour saved to resume and
 * behaviour 9 started. Whether it paired. */
int OutdoorVillagerWalks_TryPair(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (MainRandom_Below(WALKS_PAIR_ONE_IN) != 0) {
        return 0;
    }
    if (((int (*)(u8 *)) walks_slot(villager, OUTDOOR_VILLAGER_SLOT_CAN_PAIR))(villager) == 0) {
        return 0;
    }
    u8 *partner = OutdoorVillagerWalks_FindPartner(self, villager);
    if (partner == NULL) {
        return 0;
    }
    if (((int (*)(u8 *, u8 *)) walks_slot(partner, OUTDOOR_VILLAGER_SLOT_CAN_PAIR + 4))(partner, villager) == 0) {
        return 0;
    }
    VillagerSceneObject_SetWord644((u32 *) (void *) villager, (u32) (uintptr_t) partner);
    VillagerSceneObject_SetByte648(villager, 0);
    OutdoorVillagerBehaviour_SaveResume(self);
    OutdoorVillagerBehaviour_Start((OutdoorVillagerBehaviour *) (void *) walks_at(villager, OUTDOOR_VILLAGER_BEHAVIOUR),
                                   villager, WALKS_DO_PAIRED);
    return 1;
}
CLEAN_AS(func_ov068_0226c520, OutdoorVillagerWalks_TryPair)

/* func_ov068_0226c58c: the first of the eight villager objects (Actors_SlotE) with a town
 * record that is not the same villager (head and number), within 0x3000 and within
 * data_020c80f0 either way of its facing (SceneLook_Within); null when none. */
u8 *OutdoorVillagerWalks_FindPartner(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    Vec3 *position = walks_position(villager);
    s16 within = data_020c80f0;
    for (int i = 0; i < 8; i++) {
        u8 *other = (u8 *) Actors_SlotE(i);
        if (other == NULL) {
            continue;
        }
        u8 *other_record = *(u8 **) (void *) walks_at(other, WALKS_TOWN_RECORD);
        if (other_record == NULL) {
            continue;
        }
        const NpcId *mine = TownVillager_NpcId(*(u8 **) (void *) walks_at(villager, WALKS_TOWN_RECORD));
        const NpcId *theirs = TownVillager_NpcId(other_record);
        if (theirs->head.id == mine->head.id && memcmp(theirs->head.data, mine->head.data, sizeof(mine->head.data)) == 0 &&
            theirs->number == mine->number) {
            continue;
        }
        Vec3 *other_position = walks_position(other);
        if (Vec_DistanceXZ(position, other_position) >= WALKS_PARTNER_NEAR) {
            continue;
        }
        s16 yaw = Vec_YawTo(position, other_position);
        if (SceneLook_Within((s16) (yaw - *walks_half(villager, WALKS_ANGLE)), within) == 0) {
            continue;
        }
        return other;
    }
    return NULL;
}
CLEAN_AS(func_ov068_0226c58c, OutdoorVillagerWalks_FindPartner)

/* func_ov068_0226c63c: while its mover has not reached its end: blocked ahead with no free point
 * aside, it stands (1); a free point aside becomes the mover's end. Once it has reached it,
 * the end put back at the start when they differ. Whether it stood. */
int OutdoorVillagerWalks_StepAside(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    SceneMover *mover = (SceneMover *) (void *) walks_at(villager, WALKS_MOVER);
    int stood = 0;
    if (SceneMover_Reached(mover, villager, 1) == 0) {
        Vec3 side;
        switch (SceneObject_SideStep(villager, &side)) {
            case SCENE_OBJECT_BLOCKED:
                walks_stand(villager);
                stood = 1;
                break;
            case SCENE_OBJECT_SIDE_POINT:
                SceneMover_SetEnd(mover, &side);
                break;
            default:
                break;
        }
    } else if (SceneMover_PointsDiffer(mover) != 0) {
        SceneMover_EndAtStart(mover);
    }
    return stood;
}
CLEAN_AS(func_ov068_0226c63c, OutdoorVillagerWalks_StepAside)

/* func_ov068_0226c6ac: the next point of the villager's walk into `point`: a walker going other
 * than home runs out of time when its state entry's flag 1 is set; a walker that stopped or ran
 * out of time starts afresh (state 0); `point` is the villager's position stepped by the
 * walker (the walk's time 6000 from its first step). Always 1.
 * REQUIRES: a villager with a record has a state entry. */
int OutdoorVillagerWalks_StepWalker(OutdoorVillagerBehaviour *self, Vec3 *point, u8 *villager)
{
    if (walks_record(villager) != NULL && walks_flag_1(walks_record(villager)) &&
        PathWalker_Status(walks_walker(self)) != WALKS_WALKER_HOME) {
        *walks_half(self, WALKS_WALK_TIME) = 0;
    }
    if (PathWalker_IsWalking(walks_walker(self)) == 0 || *walks_half(self, WALKS_WALK_TIME) == 0) {
        walks_restart(self, 0, villager);
    }
    Vec3 *position = walks_position(villager);
    point->x = position->x;
    point->y = position->y;
    point->z = position->z;
    walks_step(self, point);
    return 1;
}
CLEAN_AS(func_ov068_0226c6ac, OutdoorVillagerWalks_StepWalker)

/* func_ov068_0226c754: during an object event (EventQueue_IsObjectEvent) with both this
 * console's player and the event's object, whether `point` is within `range` (along x and z)
 * of the point half their distance beyond the player (the player's position plus half of the
 * player's position less the object's).
 * QUIRK: that point is beyond the player, not between the two. */
int OutdoorVillagerWalks_NearEvent(OutdoorVillagerBehaviour *self, const Vec3 *point, fx32 range)
{
    (void) self;
    if (EventQueue_IsObjectEvent() == 0) {
        return 0;
    }
    u8 *player = (u8 *) (uintptr_t) (u32) SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    u8 *object = (u8 *) (uintptr_t) (u32) EventQueue_TargetObjectAddress();
    if (player == NULL || object == NULL) {
        return 0;
    }
    Vec3 half;
    Vec3 beyond;
    Vec_Subtract(&half, walks_position(player), walks_position(object));
    Vec_ShiftRight(&half, 1);
    Vec_Add(&beyond, walks_position(player), &half);
    fx32 distance = Vec_DistanceXZ(point, &beyond);
    if (distance < 0) {
        distance = (fx32) (0u - (u32) distance);
    }
    return distance <= range;
}
CLEAN_AS(func_ov068_0226c754, OutdoorVillagerWalks_NearEvent)

/* func_ov068_0226c7bc: whether the way from `from` to `to` crosses the line between the player
 * and the event's object (CrossesEvent). */
int OutdoorVillagerWalks_CrossesEventTo(OutdoorVillagerBehaviour *self, const Vec3 *to, const Vec3 *from)
{
    Vec3 direction;
    Vec_Subtract(&direction, to, from);
    return OutdoorVillagerWalks_CrossesEvent(self, from, &direction);
}
CLEAN_AS(func_ov068_0226c7bc, OutdoorVillagerWalks_CrossesEventTo)

/* func_ov068_0226c7dc: while the villager moves (its speed not 0), whether the way ahead of
 * it (its walking angle) crosses the line between the player and the event's object. */
int OutdoorVillagerWalks_CrossesEventAhead(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (*walks_word(villager, WALKS_SPEED) == 0) {
        return 0;
    }
    Vec3 ahead = {0, 0, 0x1000};
    Vec_RotateY(&ahead, *walks_half(villager, WALKS_WALK_ANGLE));
    return OutdoorVillagerWalks_CrossesEvent(self, walks_position(villager), &ahead);
}
CLEAN_AS(func_ov068_0226c7dc, OutdoorVillagerWalks_CrossesEventAhead)

/* The z of the cross product of `a` and `b` in the x-z plane, in fixed point. */
static fx32 walks_cross(const Vec3 *a, const Vec3 *b)
{
    fx32 first = FX_MulFunc(a->x, b->z);
    fx32 second = FX_MulFunc(a->z, b->x);
    return (fx32) ((u32) first - (u32) second);
}

/* func_ov068_0226c820: during an object event with both the player and the event's object,
 * and a `direction` that is not 0, whether the player and the object are not on the same side
 * of the line from `from` along `direction` (the products of the crosses not above 0). */
int OutdoorVillagerWalks_CrossesEvent(OutdoorVillagerBehaviour *self, const Vec3 *from, const Vec3 *direction)
{
    (void) self;
    if (EventQueue_IsObjectEvent() == 0) {
        return 0;
    }
    if (Vec_Differ(direction, &data_021fbee8) == 0) {
        return 0;
    }
    u8 *player = (u8 *) (uintptr_t) (u32) SessionPlayers_ActorHandle(OUTDOOR_VILLAGER_PLAYER_ACTOR);
    u8 *object = (u8 *) (uintptr_t) (u32) EventQueue_TargetObjectAddress();
    if (player == NULL || object == NULL) {
        return 0;
    }
    Vec3 to_player;
    Vec3 to_object;
    Vec_Subtract(&to_player, walks_position(player), from);
    Vec_Subtract(&to_object, walks_position(object), from);
    fx32 side_player = walks_cross(direction, &to_player);
    fx32 side_object = walks_cross(direction, &to_object);
    return FX_MulFunc(side_player, side_object) <= 0;
}
CLEAN_AS(func_ov068_0226c820, OutdoorVillagerWalks_CrossesEvent)

/* func_ov068_0226c8b0: whether the walker walks home (kind 3) and the villager is within 0x800
 * of the centre of the tile in front of its house. */
int OutdoorVillagerWalks_AtHome(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (PathWalker_IsWalking(walks_walker(self)) == 0 || PathWalker_Status(walks_walker(self)) != WALKS_WALKER_HOME) {
        return 0;
    }
    VillagerPlot *home = VillagerHome_Tile(walks_record(villager));
    Vec3 door;
    AcreTile_TileCentre(&door, home->x, (u32) home->z + 1);
    return Vec_DistanceXZ(&door, walks_position(villager)) < WALKS_HOME_NEAR;
}
CLEAN_AS(func_ov068_0226c8b0, OutdoorVillagerWalks_AtHome)

/* func_ov068_0226c910: whether it is time to go home: its state entry's flag 1, or its sleep
 * time (VillagerEntry_IsSleepTime) unless the current player has flag 1.
 * REQUIRES: its record has a state entry. */
int OutdoorVillagerWalks_TimeToGoHome(OutdoorVillagerBehaviour *self, u8 *villager)
{
    (void) self;
    int flag_1 = walks_player_flag_1();
    u8 *record = walks_record(villager);
    if (walks_flag_1(record)) {
        return 1;
    }
    if (flag_1 != 0 || VillagerEntry_IsSleepTime(record, NULL) == 0) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov068_0226c910, OutdoorVillagerWalks_TimeToGoHome)

/* func_ov068_0226c964: the walker started from the villager's position in `state`, of the kind
 * the villager wants: home (3) with its state entry's flag 1 or at night for its personality
 * (NpcLookup_IsInNightWindow) unless the current player has flag 1; 6 for the kind of the
 * moment 6; else drawn (DrawWalkKind).
 * REQUIRES: a villager with a record has a state entry. */
void OutdoorVillagerWalks_StartWalker(OutdoorVillagerBehaviour *self, int state, u8 *villager)
{
    u8 *record = walks_record(villager);
    int kind = WALKS_WALKER_NONE;
    if (record != NULL) {
        if (walks_flag_1(record)) {
            kind = WALKS_WALKER_HOME;
        } else {
            int flag_1 = walks_player_flag_1();
            DateTime now = {0};
            DateTime_Now(&now);
            if (flag_1 == 0 && NpcLookup_IsInNightWindow(NpcId_Personality(TownVillager_NpcId(record)), &now) != 0) {
                kind = WALKS_WALKER_HOME;
            } else if (walks_kind(record, WALKS_KIND_NONE) == WALKS_KIND_6) {
                kind = WALKS_WALKER_KIND_6;
            }
        }
    }
    if (kind == WALKS_WALKER_NONE) {
        kind = OutdoorVillagerWalks_DrawWalkKind(self);
    }
    PathWalker_Start(walks_walker(self), walks_position(villager), (u32) kind, state, villager);
}
CLEAN_AS(func_ov068_0226c964, OutdoorVillagerWalks_StartWalker)

/* func_ov068_0226ca2c: a walk kind drawn of data_ov068_022767ac (of the first two while the
 * walker walks, else of the three); when it is the walker's own, the next one (round to the
 * first). */
int OutdoorVillagerWalks_DrawWalkKind(OutdoorVillagerBehaviour *self)
{
    PathWalker *walker = walks_walker(self);
    int index = (int) MainRandom_Below(PathWalker_IsWalking(walker) != 0 ? 2 : 3);
    int kind = data_ov068_022767ac[index];
    if (kind == PathWalker_Status(walker)) {
        kind = data_ov068_022767ac[index + 1 < WALKS_WALKER_KINDS ? index + 1 : 0];
    }
    return kind;
}
CLEAN_AS(func_ov068_0226ca2c, OutdoorVillagerWalks_DrawWalkKind)

/* func_ov068_0226ca74: whether the villager is within the box (the behaviour member's first
 * four words) around the camera's target; 0 without a camera. */
int OutdoorVillagerWalks_OnScreen(OutdoorVillagerBehaviour *self, u8 *villager)
{
    if (data_021c67a4 == NULL) {
        return 0;
    }
    Vec3 target = data_021c67d0;
    return OutdoorVillagerWalks_InBox((const OutdoorVillagerWalksBox *) (const void *) self, &target,
                                      walks_position(villager));
}
CLEAN_AS(func_ov068_0226ca74, OutdoorVillagerWalks_OnScreen)

static fx32 walks_add(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

static fx32 walks_sub(fx32 a, fx32 b)
{
    return (fx32) ((u32) a - (u32) b);
}

/* func_ov068_0226caac: whether `point` is strictly inside the box around `centre`: x between
 * centre - left and centre + right, z between centre - back and centre + front. */
int OutdoorVillagerWalks_InBox(const OutdoorVillagerWalksBox *box, const Vec3 *centre, const Vec3 *point)
{
    if (!(point->x > walks_sub(centre->x, box->left) && point->x < walks_add(centre->x, box->right))) {
        return 0;
    }
    if (!(point->z > walks_sub(centre->z, box->back))) {
        return 0;
    }
    return point->z < walks_add(centre->z, box->front);
}
CLEAN_AS(func_ov068_0226caac, OutdoorVillagerWalks_InBox)

/* func_ov068_0226cb00: behaviour 0's start: a running act's effects reset, the draw hook
 * data_ov068_022770a8, it stands, its footsteps on, the watch on this console's player; a
 * walker that walks goes on in state 0, else it starts afresh (state 0); the byte at 0x838
 * cleared, enabled and posed, the raise timer off (-1), the held item shown and its mood's
 * sounds on. */
int OutdoorVillagerWalks_Start0(OutdoorVillagerBehaviour *self, u8 *villager)
{
    OutdoorVillagerObject_ResetActEffects(villager);
    *(MemberPointer *) (void *) walks_at(villager, WALKS_DRAW_HOOK) = data_ov068_022770a8;
    walks_stand(villager);
    Footsteps_Enable(walks_footsteps(villager));
    OutdoorVillagerWatch_LookAtPlayer(walks_watch(villager), villager);
    if (PathWalker_IsWalking(walks_walker(self)) != 0) {
        PathWalker_SetState(walks_walker(self), 0);
    } else {
        walks_restart(self, 0, villager);
    }
    VillagerSceneObject_ClearByte838(villager);
    *walks_at(villager, WALKS_ENABLED) = 1;
    *walks_at(villager, WALKS_POSED) = 1;
    *walks_word(self, WALKS_RAISE) = -1;
    *walks_at(villager, WALKS_ITEM_SHOWN) = 1;
    VillagerMood_SetSoundsOn(walks_mood(villager));
    return 1;
}
CLEAN_AS(func_ov068_0226cb00, OutdoorVillagerWalks_Start0)

/* func_ov068_0226cbc8: the held item's first check in 0 to 5999 frames, no hold (-1). */
void OutdoorVillagerWalks_InitItemCheck(OutdoorVillagerBehaviour *self)
{
    *walks_half(self, WALKS_ITEM_CHECK) = (s16) MainRandom_Below(WALKS_ITEM_FIRST_FRAMES);
    *walks_half(self, WALKS_ITEM_HOLD) = -1;
}
CLEAN_AS(func_ov068_0226cbc8, OutdoorVillagerWalks_InitItemCheck)

/* func_ov068_0226cbe4: whether behaviour `index` runs. */
int OutdoorVillagerWalks_IsDoing(OutdoorVillagerBehaviour *self, int index)
{
    return self->current == index;
}
CLEAN_AS(func_ov068_0226cbe4, OutdoorVillagerWalks_IsDoing)

/* func_ov068_0226cbf4: the pairing's cooldown started (data_ov068_0227673c, 1200 frames). */
void OutdoorVillagerWalks_StartCooldown(OutdoorVillagerBehaviour *self)
{
    self->cooldown = (s32) data_ov068_0227673c;
}
CLEAN_AS(func_ov068_0226cbf4, OutdoorVillagerWalks_StartCooldown)
