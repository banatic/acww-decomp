/* A town villager walking about a room (room_villager.h). */
#include "room_villager.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/item_code.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_motion_request.h"
#include "main/scene_object.h"
#include "main/scene_share.h"
#include "main/session.h"
#include "main/spawner.h"
#include "main/speaker_anim.h"
#include "main/town_villager.h"
#include "main/villager_clothes.h"
#include "main/villager_errand_catch.h"
#include "main/villager_mood.h"
#include "main/villager_scene_object.h"
#include "main/villager_scene_slots.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "main/villager_talk.h"
#include "main/villager_talk_scene.h"

static_assert(sizeof(RoomVillagerStep) == 0x10, "a state's functions");
static_assert(sizeof(RoomVillagerMachine) == 0x14, "the machine");
static_assert(offsetof(RoomVillager, draw) == 0x898, "draw");
static_assert(offsetof(RoomVillager, machine) == 0x8a0, "machine");
static_assert(offsetof(RoomVillager, grid) == 0x8b4, "grid");
static_assert(offsetof(RoomVillager, sound_played) == 0x8d4, "sound played");
static_assert(offsetof(RoomVillager, talk_lines) == 0x8d8, "talk lines");
static_assert(sizeof(RoomVillager) == 0x8dc, "the size func_ov004_0221ee98 allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h and
 * villager_scene_slots.h). */
#define ROOM_VILLAGER_POSITION 0x5c      /* Vec3 */
#define ROOM_VILLAGER_YAW 0x8e           /* s16 */
#define ROOM_VILLAGER_SPEAKER_ANIM 0x334 /* SpeakerAnim */
#define ROOM_VILLAGER_FOOTSTEPS 0x558    /* Footsteps */
#define ROOM_VILLAGER_PARTICIPANT 0x560  /* u8: the event's participant */
#define ROOM_VILLAGER_MOTION 0x564       /* SceneMotion */
#define ROOM_VILLAGER_ACTION 0x618       /* SceneAction */
#define ROOM_VILLAGER_CLOTHES 0x64c      /* VillagerClothes */
#define ROOM_VILLAGER_TALK 0x680         /* VillagerTalk: its talk scene */
#define ROOM_VILLAGER_RECORD 0x830       /* u8 *: its town record */
#define ROOM_VILLAGER_MOOD 0x83c         /* VillagerMood */

/* Its vtable slot giving its town record (VillagerSceneObject_Record), and its talk scene's
 * vtable slot it calls at its set-up. */
#define ROOM_VILLAGER_SLOT_RECORD 0x64
#define ROOM_VILLAGER_TALK_SLOT_08 0x08

/* The field actor of this console's player, and a session slot naming no system. */
#define ROOM_VILLAGER_PLAYER_ACTOR 4
#define ROOM_VILLAGER_NO_SLOT 4

/* The kinds of motion asked for here (scene_motion_request.h). */
#define ROOM_VILLAGER_MOTION_STAND 0
#define ROOM_VILLAGER_MOTION_WALK 1
#define ROOM_VILLAGER_MOTION_TURN 3

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define ROOM_VILLAGER_EVENT_TALK 0
#define ROOM_VILLAGER_EVENT_STARTS 3
#define ROOM_VILLAGER_EVENT_REFUSED 4
#define ROOM_VILLAGER_EVENT_ENDED 8

/* The lines its talk scene is started with: by the villager's stay (VillagerStatus_Stay other
 * than 3), and by the town event going on (VillagerSceneObject_Event). */
#define ROOM_VILLAGER_STAY_SETTLED 3
#define ROOM_VILLAGER_LINES_PLAIN 0
#define ROOM_VILLAGER_LINES_EVENT_1 3
#define ROOM_VILLAGER_LINES_EVENT_0 5
#define ROOM_VILLAGER_LINES_EVENT_8_9 11
#define ROOM_VILLAGER_LINES_UNSETTLED 12

/* The clothes a villager may change into (TownVillager_Clothes). */
#define ROOM_VILLAGER_CLOTHES_FIRST 0x11a8
#define ROOM_VILLAGER_CLOTHES_LAST 0x12a7
/* The speaker animation number while it takes its clothes (SpeakerAnim_Number). */
#define ROOM_VILLAGER_ANIM_CHANGING 6

/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The session of the multiplayer game (this system's slot at its 0x64). */
extern NetSession *data_020ccf94;
/* The vtable of the class. */
extern const u8 data_ov004_022539cc[];
/* The table of the machine's states (filled by the overlay's static initialiser from the
 * member pointers data_ov004_022539a4 to data_ov004_0225394c). */
extern RoomVillagerStep data_ov004_02257cb8[ROOM_VILLAGER_STATES];
/* The member pointers to RoomVillager_Draw (its start, and state 0's entry). */
extern const MemberPointer data_ov004_02253954, data_ov004_0225395c;
/* The steps of states 1 and 2: function-local tables filled once from the constants (bit 0 of
 * the guards saying they were). */
extern u32 data_ov004_02257c78;
extern MemberPointer data_ov004_02257c88[2];
extern const MemberPointer data_ov004_02253984, data_ov004_0225393c;
extern u32 data_ov004_02257c7c;
extern MemberPointer data_ov004_02257c80[1];
extern const MemberPointer data_ov004_0225399c;
/* A step from one tile to the next, in tiles. */
typedef struct RoomVillagerTileStep {
    s32 x;
    s32 z;
} RoomVillagerTileStep;

/* A tile's step ahead by the quarter faced: (0, 1), (1, 0), (0, -1), (-1, 0) (the overlay's
 * static initialiser fills them). */
extern RoomVillagerTileStep data_ov004_02257c98[4];
/* The tables VillagerErrandCatch_Update is given. */
extern u8 data_ov004_022476cc;
extern u8 data_ov004_022476c8;

static u8 *rv_part(RoomVillager *villager, u32 offset)
{
    return villager->base + offset;
}

static SceneMotion *rv_motion_of(RoomVillager *villager)
{
    return (SceneMotion *) (void *) rv_part(villager, ROOM_VILLAGER_MOTION);
}

static SceneAction *rv_action_of(RoomVillager *villager)
{
    return (SceneAction *) (void *) rv_part(villager, ROOM_VILLAGER_ACTION);
}

static VillagerTalk *rv_talk_of(RoomVillager *villager)
{
    return (VillagerTalk *) (void *) rv_part(villager, ROOM_VILLAGER_TALK);
}

static s16 rv_yaw_of(RoomVillager *villager)
{
    return *(s16 *) (void *) rv_part(villager, ROOM_VILLAGER_YAW);
}

static u8 *rv_record_field(RoomVillager *villager)
{
    return *(u8 **) (void *) rv_part(villager, ROOM_VILLAGER_RECORD);
}

/* Its town record, through its vtable slot 0x64. */
static u8 *rv_record(RoomVillager *villager)
{
    u32 vtable = *(const u32 *) (const void *) villager->base;
    u32 code = *(const u32 *) (uintptr_t) (vtable + ROOM_VILLAGER_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(u8 *))(uintptr_t) code)(villager->base);
}

/* This system's slot in the session. */
static int rv_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* Calls through a member pointer of the machine's tables, with the villager. */
static int rv_call_int(const MemberPointer *member, RoomVillagerMachine *machine, RoomVillager *villager)
{
    void *self = MemberPointer_Object(member, machine);
    return ((int (*)(void *, RoomVillager *))(uintptr_t) MemberPointer_Code(member, self))(self, villager);
}

/* func_ov004_0221e308 (vtable slot 0x40): the destructor, without freeing: its grid, its
 * machine, then the town villager scene object. */
RoomVillager *RoomVillager_Destroy(RoomVillager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_022539cc;
    Spawner_PartDestruct(&villager->grid);
    RoomVillagerMachine_Destroy(&villager->machine);
    VillagerSceneObject_DestructBody(villager->base);
    return villager;
}
CLEAN_AS(func_ov004_0221e308, RoomVillager_Destroy)

/* func_ov004_0221e33c (vtable slot 0x44, the deleting destructor). */
RoomVillager *RoomVillager_Delete(RoomVillager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_022539cc;
    Spawner_PartDestruct(&villager->grid);
    RoomVillagerMachine_Destroy(&villager->machine);
    VillagerSceneObject_DestructBody(villager->base);
    Heap_FreeAux(villager);
    return villager;
}
CLEAN_AS(func_ov004_0221e33c, RoomVillager_Delete)

/* The lines its talk scene starts with when this system talks to it: 12 while the villager has
 * a record whose stay is not 3, else by the town event (1: 3, 0: 5, 8 and 9: 11, others 0). */
static void rv_choose_lines(RoomVillager *villager)
{
    if (rv_record_field(villager) != NULL && VillagerStatus_Stay(rv_record_field(villager)) != ROOM_VILLAGER_STAY_SETTLED) {
        villager->talk_lines = ROOM_VILLAGER_LINES_UNSETTLED;
        return;
    }
    switch (VillagerSceneObject_Event(villager->base)) {
        case 1:
            villager->talk_lines = ROOM_VILLAGER_LINES_EVENT_1;
            break;
        case 0:
            villager->talk_lines = ROOM_VILLAGER_LINES_EVENT_0;
            break;
        case 8:
        case 9:
            villager->talk_lines = ROOM_VILLAGER_LINES_EVENT_8_9;
            break;
        default:
            villager->talk_lines = ROOM_VILLAGER_LINES_PLAIN;
            break;
    }
}

/* Its talk scene started with its lines and given this console's player's object as the
 * motion's argument. */
static void rv_start_talk(RoomVillager *villager)
{
    VillagerTalkScene_Start(rv_talk_of(villager), villager->base, (unsigned int) villager->talk_lines);
    SceneBase_SetMotionArg((SceneBase *) (void *) rv_talk_of(villager),
                           SceneObject_ActorObject(villager->base, ROOM_VILLAGER_PLAYER_ACTOR));
}

/* The object let go by this system (owned by it, held by no one): the state asked for next, or
 * wander. */
static void rv_let_go(RoomVillager *villager)
{
    SceneShare_SetSlotsIfOurs(villager->base, 1, rv_local_slot(), ROOM_VILLAGER_NO_SLOT);
    if (!RoomVillagerMachine_TakeNext(&villager->machine, villager)) {
        RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_WANDER);
    }
}

/* func_ov004_0221e374 (vtable slot 0x4c, told of an event about it by `participant`'s system,
 * 4 for this one):
 * - 3, an event starts: the participant kept; another system's: the object is owned by this
 *   one and held by it; this one's (with the object ours): owned and held by this one, its lines
 *   chosen (rv_choose_lines). Either way it turns to the participant (state 2);
 * - 0, the player talks to it: the participant kept; another system's (not this one's slot):
 *   owned and held by it, state 4; this one's (with the object ours): owned and held by this
 *   one, its talk started with its lines, state 1, and the lines back to 0;
 * - 8, the event ended: for this console's player, when this system holds the scene it lets the
 *   object go (rv_let_go); without, the object is owned by no one and held by this system,
 *   state 3;
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), it lets the object go. */
void RoomVillager_OnEvent(RoomVillager *villager, int code, int participant)
{
    switch (code) {
        case ROOM_VILLAGER_EVENT_STARTS:
            *rv_part(villager, ROOM_VILLAGER_PARTICIPANT) = (u8) participant;
            if (participant != ROOM_VILLAGER_PLAYER_ACTOR) {
                SceneShare_SetSlotsIfOurs(villager->base, 1, rv_local_slot(), participant);
                RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_TURN);
            } else if (SceneShare_IsOurs(villager->base)) {
                SceneShare_SetSlotsIfOurs(villager->base, 1, rv_local_slot(), rv_local_slot());
                rv_choose_lines(villager);
                RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_TURN);
            }
            break;
        case ROOM_VILLAGER_EVENT_TALK:
            *rv_part(villager, ROOM_VILLAGER_PARTICIPANT) = (u8) participant;
            if (participant != ROOM_VILLAGER_PLAYER_ACTOR && participant != rv_local_slot()) {
                SceneShare_SetSlotsIfOurs(villager->base, 1, participant, participant);
                RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_RELEASE);
            } else if (SceneShare_IsOurs(villager->base)) {
                SceneShare_SetSlotsIfOurs(villager->base, 1, rv_local_slot(), rv_local_slot());
                rv_start_talk(villager);
                RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_TALK);
                villager->talk_lines = ROOM_VILLAGER_LINES_PLAIN;
            }
            break;
        case ROOM_VILLAGER_EVENT_ENDED:
            if (participant == ROOM_VILLAGER_PLAYER_ACTOR) {
                if (LinkGlobal_HoldsScene()) {
                    rv_let_go(villager);
                } else {
                    SceneShare_SetSlotsIfOurs(villager->base, 1, ROOM_VILLAGER_NO_SLOT, rv_local_slot());
                    RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_AWAIT);
                }
            }
            break;
        case ROOM_VILLAGER_EVENT_REFUSED:
            if (SceneShare_IsHeld(villager->base) && SceneShare_IsOurs(villager->base)) {
                int owner = ROOM_VILLAGER_NO_SLOT;
                int holder = ROOM_VILLAGER_NO_SLOT;
                if (SceneShare_ReadSlots(villager->base, &owner, &holder) &&
                    (participant == ROOM_VILLAGER_PLAYER_ACTOR || participant == holder)) {
                    rv_let_go(villager);
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221e374, RoomVillager_OnEvent)

/* func_ov004_0221e594 (vtable slot 0x48): whether the player may talk to it: its action idle
 * and the object not held. */
int RoomVillager_MayAct(RoomVillager *villager)
{
    if (SceneAction_IsBusy(rv_action_of(villager))) {
        return 0;
    }
    return SceneShare_IsHeld(villager->base) == 0;
}
CLEAN_AS(func_ov004_0221e594, RoomVillager_MayAct)

/* func_ov004_0221e5c0: state 4's update: with the object ours and owned by no one, when this
 * system holds the scene it lets the object go (rv_let_go). 0. */
int RoomVillager_UpdateRelease(RoomVillagerMachine *machine, RoomVillager *villager)
{
    (void) machine;
    if (SceneShare_IsOurs(villager->base)) {
        int owner = ROOM_VILLAGER_NO_SLOT;
        int holder = ROOM_VILLAGER_NO_SLOT;
        if (SceneShare_ReadSlots(villager->base, &owner, &holder) && owner == ROOM_VILLAGER_NO_SLOT &&
            LinkGlobal_HoldsScene()) {
            rv_let_go(villager);
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0221e5c0, RoomVillager_UpdateRelease)

/* func_ov004_0221e630: entering state 4 always succeeds. */
int RoomVillager_EnterRelease(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221e630, RoomVillager_EnterRelease)

/* func_ov004_0221e634: state 3's update, with the object ours: when this system owns and holds
 * it, it is owned and held by this system, its lines are 12 (a record whose stay is not 3) or
 * 0, and its talk starts (state 1); else when this system holds the scene and no one holds the
 * object, it lets the object go (rv_let_go). 0. */
int RoomVillager_UpdateAwait(RoomVillagerMachine *machine, RoomVillager *villager)
{
    (void) machine;
    if (!SceneShare_IsOurs(villager->base)) {
        return 0;
    }
    int owner = ROOM_VILLAGER_NO_SLOT;
    int holder = ROOM_VILLAGER_NO_SLOT;
    u8 *record = rv_record_field(villager);
    if (SceneShare_ReadSlots(villager->base, &owner, &holder) && owner == rv_local_slot() && owner == holder) {
        SceneShare_SetSlotsIfOurs(villager->base, 1, rv_local_slot(), rv_local_slot());
        if (record != NULL && VillagerStatus_Stay(record) != ROOM_VILLAGER_STAY_SETTLED) {
            villager->talk_lines = ROOM_VILLAGER_LINES_UNSETTLED;
        } else {
            villager->talk_lines = ROOM_VILLAGER_LINES_PLAIN;
        }
        rv_start_talk(villager);
        RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_TALK);
    } else if (LinkGlobal_HoldsScene() && holder == ROOM_VILLAGER_NO_SLOT) {
        rv_let_go(villager);
    }
    return 0;
}
CLEAN_AS(func_ov004_0221e634, RoomVillager_UpdateAwait)

/* func_ov004_0221e718: entering state 3 always succeeds. */
int RoomVillager_EnterAwait(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0221e718, RoomVillager_EnterAwait)

/* func_ov004_0221e71c: state 2's update: its step (one, RoomVillager_TurnStep0; the table filled
 * once). 0. */
int RoomVillager_UpdateTurn(RoomVillagerMachine *machine, RoomVillager *villager)
{
    static const MemberPointer *const steps[1] = {&data_ov004_0225399c};
    MemberTable_InitOnce(&data_ov004_02257c7c, data_ov004_02257c80, steps, 1);
    if (machine->phase < 1) {
        rv_call_int(&data_ov004_02257c80[machine->phase], machine, villager);
    }
    return 0;
}
CLEAN_AS(func_ov004_0221e71c, RoomVillager_UpdateTurn)

/* func_ov004_0221e780: state 2's step 0: once its turn is done it stands (priority 2), step 1. */
void RoomVillager_TurnStep0(RoomVillagerMachine *machine, RoomVillager *villager)
{
    SceneMotion *motion = rv_motion_of(villager);
    if (SceneMotion_Kind(motion) == ROOM_VILLAGER_MOTION_TURN && SceneMotion_IsDone(motion)) {
        SceneMotion_RequestStand(motion, 2, data_020c80f8);
        machine->phase = 1;
    }
}
CLEAN_AS(func_ov004_0221e780, RoomVillager_TurnStep0)

/* func_ov004_0221e7c4: entering state 2 (always succeeds): it turns (priority 2) to the event's
 * participant's field actor; step 0. */
int RoomVillager_EnterTurn(RoomVillagerMachine *machine, RoomVillager *villager)
{
    int yaw = (int) (intptr_t) SceneObject_YawToActor(villager->base, *rv_part(villager, ROOM_VILLAGER_PARTICIPANT));
    SceneMotion_Request(rv_motion_of(villager), ROOM_VILLAGER_MOTION_TURN, 2, 0, 0, 0, (s16) yaw, 0, 0, data_020c80f8, 0);
    machine->phase = 0;
    return 1;
}
CLEAN_AS(func_ov004_0221e7c4, RoomVillager_EnterTurn)

/* func_ov004_0221e810: state 1's update: its step (RoomVillager_TalkStep0, then
 * RoomVillager_TalkStep1; the table filled once). 0. */
int RoomVillager_UpdateTalk(RoomVillagerMachine *machine, RoomVillager *villager)
{
    static const MemberPointer *const steps[2] = {&data_ov004_02253984, &data_ov004_0225393c};
    MemberTable_InitOnce(&data_ov004_02257c78, data_ov004_02257c88, steps, 2);
    if (machine->phase < 2) {
        rv_call_int(&data_ov004_02257c88[machine->phase], machine, villager);
    }
    return 0;
}
CLEAN_AS(func_ov004_0221e810, RoomVillager_UpdateTalk)

/* func_ov004_0221e87c: state 1's step 1 does nothing. */
void RoomVillager_TalkStep1(void) {}
CLEAN_AS(func_ov004_0221e87c, RoomVillager_TalkStep1)

/* func_ov004_0221e880: state 1's step 0: once its action is idle, its mood is applied, the
 * object's event ends and step 1 follows; 1 then, else 0. */
int RoomVillager_TalkStep0(RoomVillagerMachine *machine, RoomVillager *villager)
{
    int busy = SceneAction_IsBusy(rv_action_of(villager));
    if (busy != 0) {
        return busy;
    }
    VillagerMood_Apply((VillagerMood *) (void *) rv_part(villager, ROOM_VILLAGER_MOOD));
    EventQueue_FinishObjectEvent(villager);
    machine->phase = 1;
    return 1;
}
CLEAN_AS(func_ov004_0221e880, RoomVillager_TalkStep0)

/* func_ov004_0221e8b8: entering state 1 (always succeeds): it turns to the talk scene's motion
 * argument (an object; angle 0 without one) and talks. */
int RoomVillager_EnterTalk(RoomVillagerMachine *machine, RoomVillager *villager)
{
    (void) machine;
    int partner = SceneBase_MotionArg((SceneBase *) (void *) rv_talk_of(villager));
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(villager->base, (u8 *) (uintptr_t) partner);
    }
    SceneAction_RequestTurnAndTalk(rv_action_of(villager), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221e8b8, RoomVillager_EnterTalk)

/* How long a walk lasts before its end turns it into a stand. */
#define ROOM_VILLAGER_WALK_FRAMES 60
/* A quarter turn, and the bits of a yaw below one. */
#define ROOM_VILLAGER_QUARTER 0x4000
#define ROOM_VILLAGER_QUARTER_SHIFT 14
#define ROOM_VILLAGER_OFF_QUARTER 0x3fff

/* It turns (priority 1) to a quarter drawn at random, the next one when that is the one it
 * faces. */
static void rv_turn_at_random(RoomVillager *villager)
{
    s16 yaw = (s16) (MainRandom_Below(4) << ROOM_VILLAGER_QUARTER_SHIFT);
    if (yaw == rv_yaw_of(villager)) {
        yaw = (s16) (yaw + ROOM_VILLAGER_QUARTER);
    }
    SceneMotion_Request(rv_motion_of(villager), ROOM_VILLAGER_MOTION_TURN, 1, 0, 0, 0, yaw, 0, 0, data_020c80f8, 0);
}

/* func_ov004_0221e8f0: state 0's update. When its motion is done: six times in seven it stands;
 * else when it does not face a quarter it turns to one (rv_turn_at_random); facing one, two
 * times in three it walks (priority 1) to the free tile ahead (RoomVillager_FindStepAhead) and
 * the timer is 60, and otherwise it turns. While its motion goes on, a walk becomes a stand once
 * the timer is 0. 0. */
int RoomVillager_UpdateWander(RoomVillagerMachine *machine, RoomVillager *villager)
{
    SceneMotion *motion = rv_motion_of(villager);
    if (SceneMotion_IsDone(motion)) {
        int x = 0;
        int z = 0;
        if (MainRandom_Below(7) != 0) {
            SceneMotion_Request(motion, ROOM_VILLAGER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        } else if ((rv_yaw_of(villager) & ROOM_VILLAGER_OFF_QUARTER) != 0) {
            rv_turn_at_random(villager);
        } else if (MainRandom_Below(3) != 0 && RoomVillager_FindStepAhead(machine, &x, &z, villager)) {
            SceneMotion_Request(motion, ROOM_VILLAGER_MOTION_WALK, 1, x, z, 0, 0, 0, 0, data_020c80f8, 0);
            machine->timer = ROOM_VILLAGER_WALK_FRAMES;
        } else {
            rv_turn_at_random(villager);
        }
    } else if (machine->timer == 0 && SceneMotion_Kind(motion) == ROOM_VILLAGER_MOTION_WALK) {
        SceneMotion_Request(motion, ROOM_VILLAGER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    return 0;
}
CLEAN_AS(func_ov004_0221e8f0, RoomVillager_UpdateWander)

/* func_ov004_0221ea40: entering state 0 (always succeeds): its drawing member is
 * RoomVillager_Draw again, it stands (priority 1) and the timer is 0. */
int RoomVillager_EnterWander(RoomVillagerMachine *machine, RoomVillager *villager)
{
    villager->draw = data_ov004_0225395c;
    SceneMotion_Request(rv_motion_of(villager), ROOM_VILLAGER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    machine->timer = 0;
    return 1;
}
CLEAN_AS(func_ov004_0221ea40, RoomVillager_EnterWander)

/* func_ov004_0221ea98: the tile one step ahead of it (by the quarter its yaw is in), when the
 * grid marks it (only rows 0-13 count while it stands in them): the tile's centre's x and z into
 * `x` and `z`; whether there was one. */
int RoomVillager_FindStepAhead(RoomVillagerMachine *machine, int *x, int *z, RoomVillager *villager)
{
    (void) machine;
    int quarter = (u8) ((rv_yaw_of(villager) >> ROOM_VILLAGER_QUARTER_SHIFT) & 3);
    int at_x = 0;
    int at_z = 0;
    Position_Tile(&at_x, &at_z, (const Position *) (const void *) rv_part(villager, ROOM_VILLAGER_POSITION));
    int to_x = at_x + data_ov004_02257c98[quarter].x;
    int to_z = at_z + data_ov004_02257c98[quarter].z;
    int marked;
    if ((u32) at_z < TILE_GRID_SEARCH_ROWS) {
        marked = TileGrid_IsMarkedInSearchRows(&villager->grid, (u32) to_x, (u32) to_z);
    } else {
        marked = TileGrid_IsMarked(&villager->grid, (u32) to_x, (u32) to_z);
    }
    if (!marked) {
        return 0;
    }
    Vec3 centre = {0, 0, 0};
    AcreTile_TileCentre(&centre, (u32) to_x, (u32) to_z);
    *x = centre.x;
    *z = centre.z;
    return 1;
}
CLEAN_AS(func_ov004_0221ea98, RoomVillager_FindStepAhead)

/* func_ov004_0221eb44: the state asked for next taken (when below 5), and none asked for after;
 * whether one was.
 * QUIRK: a negative one counts as taken though RoomVillagerMachine_SetState ignores it. */
int RoomVillagerMachine_TakeNext(RoomVillagerMachine *machine, RoomVillager *villager)
{
    int next = machine->next;
    if (next < ROOM_VILLAGER_STATES) {
        RoomVillagerMachine_SetState(machine, villager, next);
        RoomVillagerMachine_ClearNext(machine);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221eb44, RoomVillagerMachine_TakeNext)

/* func_ov004_0221eb64: no state asked for next. */
void RoomVillagerMachine_ClearNext(RoomVillagerMachine *machine)
{
    machine->next = ROOM_VILLAGER_STATES;
}
CLEAN_AS(func_ov004_0221eb64, RoomVillagerMachine_ClearNext)

/* func_ov004_0221eb6c: state `state` (0 to 4, others ignored) entered: its entry of the table,
 * step 0, then its entry function run with the villager when it has one (its answer is not
 * used). */
void RoomVillagerMachine_SetState(RoomVillagerMachine *machine, RoomVillager *villager, int state)
{
    if (state < 0 || state >= ROOM_VILLAGER_STATES) {
        return;
    }
    machine->state = state;
    machine->step = &data_ov004_02257cb8[state];
    machine->phase = 0;
    if (machine->step->enter.function != 0) {
        rv_call_int(&machine->step->enter, machine, villager);
    }
}
CLEAN_AS(func_ov004_0221eb6c, RoomVillagerMachine_SetState)

/* func_ov004_0221ebb8: the state's update run with the villager (when a state was entered), then
 * the timer runs down to 0. */
void RoomVillagerMachine_Update(RoomVillagerMachine *machine, RoomVillager *villager)
{
    if (machine->step != NULL) {
        rv_call_int(&machine->step->update, machine, villager);
    }
    if (machine->timer > 0) {
        machine->timer--;
    }
}
CLEAN_AS(func_ov004_0221ebb8, RoomVillagerMachine_Update)

/* func_ov004_0221ebf4: the machine's destructor does nothing. */
void RoomVillagerMachine_Destroy(RoomVillagerMachine *machine)
{
    (void) machine;
}
CLEAN_AS(func_ov004_0221ebf4, RoomVillagerMachine_Destroy)

/* func_ov004_0221ebf8: the machine's constructor: no next state, the timer 0. */
void RoomVillagerMachine_Construct(RoomVillagerMachine *machine)
{
    machine->next = ROOM_VILLAGER_STATES;
    machine->timer = 0;
}
CLEAN_AS(func_ov004_0221ebf8, RoomVillagerMachine_Construct)

/* func_ov004_0221ec04 (vtable slot 0x68, its update): the machine updated. In a linked session,
 * unless its speaker animation is number 6, a villager with a record wearing other clothes
 * than the record's (compared by the variant's item for clothes with a variant) changes into the
 * record's when those are clothes (0x11a8-0x12a7). Then its mood is updated; 1. */
int RoomVillager_RunState(RoomVillager *villager)
{
    RoomVillagerMachine_Update(&villager->machine, villager);
    if (Session_IsLinked(data_020ccf94) &&
        SpeakerAnim_Number((SpeakerAnim *) (void *) rv_part(villager, ROOM_VILLAGER_SPEAKER_ANIM), 0) !=
            ROOM_VILLAGER_ANIM_CHANGING &&
        rv_record(villager) != NULL) {
        u16 *wanted = TownVillager_Clothes(rv_record(villager));
        u16 *worn = (u16 *) (uintptr_t) VillagerClothes_ItemOf((int) (uintptr_t) rv_part(villager, ROOM_VILLAGER_CLOTHES));
        int same;
        if (ItemCode_HasVariant(worn)) {
            int item = ItemCode_VariantItem(worn);
            same = item == ItemCode_VariantItem(wanted);
        } else {
            same = *worn == *wanted;
        }
        if (!same) {
            u16 *clothes = TownVillager_Clothes(rv_record(villager));
            if (*clothes >= ROOM_VILLAGER_CLOTHES_FIRST && *clothes <= ROOM_VILLAGER_CLOTHES_LAST) {
                VillagerClothes_Change((VillagerClothes *) (void *) rv_part(villager, ROOM_VILLAGER_CLOTHES), villager->base,
                                       TownVillager_Clothes(rv_record(villager)));
            }
        }
    }
    VillagerMood_Update((VillagerMood *) (void *) rv_part(villager, ROOM_VILLAGER_MOOD), villager->base);
    return 1;
}
CLEAN_AS(func_ov004_0221ec04, RoomVillager_RunState)

/* func_ov004_0221ecec (vtable slot 0x80): notes its action sound was played. */
RoomVillager *RoomVillager_ActionSoundPlayed(RoomVillager *villager)
{
    villager->sound_played = 1;
    return villager;
}
CLEAN_AS(func_ov004_0221ecec, RoomVillager_ActionSoundPlayed)

/* func_ov004_0221ecf8 (vtable slot 0x7c): its action sound is played only until it was once. */
int RoomVillager_HasActionSound(RoomVillager *villager)
{
    return villager->sound_played == 0;
}
CLEAN_AS(func_ov004_0221ecf8, RoomVillager_HasActionSound)

/* func_ov004_0221ed0c (vtable slot 0x24, the drawing): its drawing member run
 * (RoomVillager_Draw once started); 1 while its function is not set. */
int RoomVillager_RunDraw(RoomVillager *villager)
{
    if (villager->draw.function != 0) {
        return MemberPointer_CallInt(&villager->draw, villager);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221ed0c, RoomVillager_RunDraw)

/* func_ov004_0221ed44 (the member data_ov004_02253954 and data_ov004_0225395c name): the scene
 * object drawn; whether it was. */
int RoomVillager_Draw(RoomVillager *villager)
{
    return SceneObject_Draw(villager->base) != 0;
}
CLEAN_AS(func_ov004_0221ed44, RoomVillager_Draw)

/* The record state a villager is fetched from while this system has no slot (VillagerState). */
#define ROOM_VILLAGER_LINKED_STATE_FETCH 1

/* func_ov004_0221ed5c (vtable slot 0x00, its start): the town villager's start; then its drawing
 * member is RoomVillager_Draw and its footsteps are on. With the object ours it wanders (state
 * 0) and its errands' catches are drawn (VillagerErrandCatch_Update); else it awaits (state 3).
 * While this system's slot in the session is free, a villager with a record whose state entry
 * is linked in state 1 has it set to 0. */
int RoomVillager_Start(RoomVillager *villager)
{
    if (VillagerSceneObject_Start(villager->base) == 0) {
        return 0;
    }
    villager->draw = data_ov004_02253954;
    Footsteps_Enable((Footsteps *) (void *) rv_part(villager, ROOM_VILLAGER_FOOTSTEPS));
    if (SceneShare_IsOurs(villager->base)) {
        RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_WANDER);
        VillagerErrandCatch_Update(villager, (int) (uintptr_t) &data_ov004_022476cc, (int) (uintptr_t) &data_ov004_022476c8,
                                   0);
    } else {
        RoomVillagerMachine_SetState(&villager->machine, villager, ROOM_VILLAGER_AWAIT);
    }
    NetSession *session = data_020ccf94;
    if (Session_IsSlotTaken(session, session->local_slot) == 0 && rv_record(villager) != NULL &&
        VillagerState_LinkedState(VillagerStatus_StateEntry(rv_record(villager))) == ROOM_VILLAGER_LINKED_STATE_FETCH) {
        VillagerState_SetState(VillagerStatus_StateEntry(rv_record(villager)), 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221ed5c, RoomVillager_Start)

/* func_ov004_0221ee1c (vtable slot 0x04, its set-up): the town villager's set-up; its talk scene
 * becomes its scene and is told through its vtable slot 0x08, the grid of the room's free tiles
 * is built, its lines and its action sound cleared. A villager with a record of a valid
 * villager and a state entry has the entry's tally cleared. */
int RoomVillager_Init(RoomVillager *villager)
{
    if (VillagerSceneObject_Init(villager->base) == 0) {
        return 0;
    }
    VillagerTalk *talk = rv_talk_of(villager);
    SceneObject_SetScene(villager->base, (struct SceneBase *) (void *) talk);
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + ROOM_VILLAGER_TALK_SLOT_08);
    ((void (*)(VillagerTalk *))(uintptr_t) code)(talk);
    TileGrid_Build(&villager->grid);
    villager->talk_lines = ROOM_VILLAGER_LINES_PLAIN;
    villager->sound_played = 0;
    u8 *record = rv_record(villager);
    if (record != NULL && NpcId_IsValid(TownVillager_NpcId(record))) {
        VillagerState *entry = VillagerStatus_StateEntry(record);
        if (entry != NULL) {
            VillagerTally_Clear(VillagerState_Tally(entry));
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0221ee1c, RoomVillager_Init)

/* func_ov004_0221ee98 (its entry in the overlay's table of profiles): allocates (zeroed) and
 * builds a villager: the town villager scene object, its machine and its grid. */
RoomVillager *RoomVillager_New(void)
{
    RoomVillager *villager = Heap_AllocAuxZeroed(sizeof(RoomVillager));
    if (villager != NULL) {
        VillagerSceneObject_Construct(villager->base);
        *(const u8 **) (void *) villager->base = data_ov004_022539cc;
        RoomVillagerMachine_Construct(&villager->machine);
        Spawner_PartConstruct(&villager->grid);
    }
    return villager;
}
CLEAN_AS(func_ov004_0221ee98, RoomVillager_New)
