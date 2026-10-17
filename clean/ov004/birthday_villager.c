/* The rooms' town villager of the "ev_nbirth" talks (birthday_villager.h). */
#include "birthday_villager.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/fx_math.h"  /* Math_Atan2 */
#include "autoload_2/heap.h"
#include "clean.h"
#include "main/actor.h" /* Vec_YawTo */
#include "main/actor_table.h"
#include "main/current_pockets.h"
#include "main/event_queue.h"
#include "main/group_params.h"
#include "main/item_lists.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/player_actor_ops.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/session_players.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/town_villager.h"
#include "main/villager_scene_slots.h"
#include "main/villager_talk_scene.h"

static_assert(sizeof(VillagerTalk) == 0x1a4, "the town villager's talk scene");
static_assert(sizeof(BirthdayVillagerTalk) == 0x1a8, "its talk scene");
static_assert(offsetof(BirthdayVillager, state) == 0x898, "state");
static_assert(offsetof(BirthdayVillager, sound_played) == 0x89c, "sound played");
static_assert(offsetof(BirthdayVillager, talk) == 0x8a0, "talk scene");
static_assert(offsetof(BirthdayVillager, talk.base.scene.talk) == 0x8e0, "the talk scene's talk");
static_assert(offsetof(BirthdayVillager, gift) == 0xa50, "gift");
static_assert(offsetof(BirthdayVillager, approach_wait) == 0xa52, "approach wait");
static_assert(offsetof(BirthdayVillager, act_wait) == 0xa53, "act wait");
static_assert(offsetof(BirthdayVillager, turn_yaw) == 0xa54, "turn yaw");
static_assert(offsetof(BirthdayVillager, wander_wait) == 0xa56, "wander wait");
static_assert(offsetof(BirthdayVillager, walk_point) == 0xa58, "walk point");
static_assert(offsetof(BirthdayVillager, goal) == 0xa64, "goal");
static_assert(sizeof(BirthdayVillager) == 0xa70, "the size func_ov004_0221d4f4 allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define BIRTHDAY_VILLAGER_POSITION 0x5c /* Vec3 */
#define BIRTHDAY_VILLAGER_YAW 0x8e      /* s16 */
#define BIRTHDAY_VILLAGER_MOVER 0x350   /* SceneMover */
#define BIRTHDAY_VILLAGER_LOOK 0x3b0    /* SceneLook */
#define BIRTHDAY_VILLAGER_BYTE_508 0x508
#define BIRTHDAY_VILLAGER_MOTION 0x564 /* SceneMotion */
#define BIRTHDAY_VILLAGER_ACTION 0x618 /* SceneAction */
#define BIRTHDAY_VILLAGER_RECORD 0x830 /* u8 *: its town record (town_villager.h) */

/* The field actor of this console's player. */
#define BIRTHDAY_VILLAGER_PLAYER_ACTOR 4

/* The kinds of motion asked for here (scene_motion_request.h). */
#define BIRTHDAY_VILLAGER_MOTION_STAND 0
#define BIRTHDAY_VILLAGER_MOTION_WALK 1
#define BIRTHDAY_VILLAGER_MOTION_RUN 2
#define BIRTHDAY_VILLAGER_MOTION_TURN 3
#define BIRTHDAY_VILLAGER_MOTION_TURN_WALK 4

/* The acts of states 2 and 3 (SceneMotion_RequestAct). */
#define BIRTHDAY_VILLAGER_ACT_NONE 0
#define BIRTHDAY_VILLAGER_ACT_3 3
#define BIRTHDAY_VILLAGER_ACT_10 10
#define BIRTHDAY_VILLAGER_ACT_23 0x17

/* The look kinds (SceneLook_Request): ahead, and at an object. */
#define BIRTHDAY_VILLAGER_LOOK_AHEAD 1
#define BIRTHDAY_VILLAGER_LOOK_AT_OBJECT 2

/* The pockets screen's mode (GroupParams_OpenWithMask), and the value kind of an item's name
 * (SceneBase_PutItemName). */
#define BIRTHDAY_VILLAGER_POCKETS_MODE 0xd
#define BIRTHDAY_VILLAGER_ITEM_NAME_KIND 7
/* The item named in the lines' values 0 and 1. */
#define BIRTHDAY_VILLAGER_LINE_ITEM 0x1100
/* The item code of "no item". */
#define BIRTHDAY_VILLAGER_NO_ITEM 0xfff1

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The message number that ends the talk. */
extern u8 data_021f43e8;
/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov004_02253674[];
extern const u8 data_ov004_022535e4[];
/* The tables of its states' update and entry functions (filled once from the constants below,
 * bit 0 of the guards saying they were). */
extern u32 data_ov004_02257a20;
extern MemberPointer data_ov004_02257b4c[BIRTHDAY_VILLAGER_STATES];
extern u32 data_ov004_02257a14;
extern MemberPointer data_ov004_02257adc[BIRTHDAY_VILLAGER_STATES];
extern const MemberPointer data_ov004_022535a4, data_ov004_02253584, data_ov004_022535b4, data_ov004_022534f4,
    data_ov004_022534ec, data_ov004_022534e4, data_ov004_02253504, data_ov004_02253534, data_ov004_0225352c,
    data_ov004_0225357c, data_ov004_02253594, data_ov004_022534dc, data_ov004_0225350c, data_ov004_02253524;
extern const MemberPointer data_ov004_0225358c, data_ov004_0225359c, data_ov004_022535ac, data_ov004_02253574,
    data_ov004_0225356c, data_ov004_02253564, data_ov004_0225355c, data_ov004_02253554, data_ov004_0225354c,
    data_ov004_02253544, data_ov004_022534fc, data_ov004_022535bc, data_ov004_02253514, data_ov004_0225351c;
/* The name of its lines' message file ("ev_nbirth" for its villager), and the text it is
 * written in. */
extern const char data_ov004_02253734[];
extern char data_ov004_02257a6c[0x28];

/* The class's functions kept as the game's. */
/* Whether a pocket's item is one to offer (the predicate of the pockets screen). */
extern int func_ov004_0221d468(u16 *item, int state);
/* The object state 1 faces, or null. */
extern u8 *func_ov004_0221e2c0(void);
/* A point of the room to walk to (into `goal`) from `from`, and the direction to it. */
extern int func_ov004_0221e1e0(Vec3 *goal, Vec3 *from, int yaw);
/* The villager's fondness of this console's player (VillagerMemoryEntry_Fondness of its memory;
 * 0 without one). */
extern int func_ov004_0221cec8(BirthdayVillagerTalk *talk);
/* Its memory of the player: bit 7 set; whether bit 6 is clear, whether bit 7 is set; bit 6
 * set (VillagerMemoryEntry_*; nothing, or 0, without a memory). */
extern void func_ov004_0221cfe0(BirthdayVillagerTalk *talk);
extern int func_ov004_0221d02c(BirthdayVillagerTalk *talk);
extern int func_ov004_0221cff8(BirthdayVillagerTalk *talk);
extern void func_ov004_0221d014(BirthdayVillagerTalk *talk);

static u8 *part(BirthdayVillager *villager, u32 offset)
{
    return villager->base + offset;
}

static Vec3 *position_of(BirthdayVillager *villager)
{
    return (Vec3 *) (void *) part(villager, BIRTHDAY_VILLAGER_POSITION);
}

static s16 yaw_of(BirthdayVillager *villager)
{
    return *(s16 *) (void *) part(villager, BIRTHDAY_VILLAGER_YAW);
}

static SceneMover *mover_of(BirthdayVillager *villager)
{
    return (SceneMover *) (void *) part(villager, BIRTHDAY_VILLAGER_MOVER);
}

static SceneLook *look_of(BirthdayVillager *villager)
{
    return (SceneLook *) (void *) part(villager, BIRTHDAY_VILLAGER_LOOK);
}

static SceneMotion *motion_of(BirthdayVillager *villager)
{
    return (SceneMotion *) (void *) part(villager, BIRTHDAY_VILLAGER_MOTION);
}

static SceneAction *action_of(BirthdayVillager *villager)
{
    return (SceneAction *) (void *) part(villager, BIRTHDAY_VILLAGER_ACTION);
}

static u8 *record_of(u8 *object)
{
    return *(u8 **) (void *) (object + BIRTHDAY_VILLAGER_RECORD);
}

/* The talk of its talk scene. */
static TalkObject *talk_of(BirthdayVillager *villager)
{
    return (TalkObject *) (void *) villager->talk.base.scene.talk;
}

/* The talk scene as the scene base and as a scene of commands. */
static SceneBase *scene_of(BirthdayVillagerTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

/* The message of the talk scene's receiver. */
static u8 message_of(BirthdayVillagerTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

static void set_vtables(BirthdayVillager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_02253674;
    villager->talk.base.scene.vtable = data_ov004_022535e4;
}

/* func_ov004_0221bf84 (the talk scene's vtable slot 0x04, its deleting destructor): the town
 * villager's talk scene destroyed, then the memory freed. */
BirthdayVillagerTalk *BirthdayVillagerTalk_Delete(BirthdayVillagerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_022535e4;
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_0221bf84, BirthdayVillagerTalk_Delete)

/* func_ov004_0221bfa4 (vtable slot 0x40): the destructor, without freeing: its talk scene, then
 * the town villager scene object. */
BirthdayVillager *BirthdayVillager_Destroy(BirthdayVillager *villager)
{
    set_vtables(villager);
    VillagerTalkScene_DestructBody(&villager->talk.base);
    VillagerSceneObject_DestructBody(villager->base);
    return villager;
}
CLEAN_AS(func_ov004_0221bfa4, BirthdayVillager_Destroy)

/* func_ov004_0221bfd4 (vtable slot 0x44, the deleting destructor). */
BirthdayVillager *BirthdayVillager_Delete(BirthdayVillager *villager)
{
    set_vtables(villager);
    VillagerTalkScene_DestructBody(&villager->talk.base);
    VillagerSceneObject_DestructBody(villager->base);
    Heap_FreeAux(villager);
    return villager;
}
CLEAN_AS(func_ov004_0221bfd4, BirthdayVillager_Delete)

/* func_ov004_0221c008 (the talk scene's vtable slot 0x00, its destructor). */
BirthdayVillagerTalk *BirthdayVillagerTalk_Destroy(BirthdayVillagerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_022535e4;
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov004_0221c008, BirthdayVillagerTalk_Destroy)

/* func_ov004_0221c020 (vtable slot 0x7c): its action sound is played only until it was once. */
int BirthdayVillager_HasActionSound(BirthdayVillager *villager)
{
    return villager->sound_played == 0;
}
CLEAN_AS(func_ov004_0221c020, BirthdayVillager_HasActionSound)

/* func_ov004_0221c034 (vtable slot 0x80): notes its action sound was played. */
BirthdayVillager *BirthdayVillager_ActionSoundPlayed(BirthdayVillager *villager)
{
    villager->sound_played = 1;
    return villager;
}
CLEAN_AS(func_ov004_0221c034, BirthdayVillager_ActionSoundPlayed)

/* Its talk's next message. */
static void say(BirthdayVillager *villager, u8 message)
{
    TalkObject_SetMessage(talk_of(villager), &message, NULL);
}

/* func_ov004_0221c040: state 13's update: message 0x11 or 0x12 at random, then state 6. */
void BirthdayVillager_UpdateThanks(BirthdayVillager *villager)
{
    say(villager, (u8) (MainRandom_Below(2) + 0x11));
    BirthdayVillager_SetState(villager, BIRTHDAY_VILLAGER_TALK);
}
CLEAN_AS(func_ov004_0221c040, BirthdayVillager_UpdateThanks)

/* func_ov004_0221c074: entering state 13 always succeeds. */
int BirthdayVillager_EnterThanks(BirthdayVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_0221c074, BirthdayVillager_EnterThanks)

/* func_ov004_0221c078: state 12's update does nothing. */
void BirthdayVillager_UpdateState12(BirthdayVillager *villager)
{
    (void) villager;
}
CLEAN_AS(func_ov004_0221c078, BirthdayVillager_UpdateState12)

/* func_ov004_0221c07c: entering state 12 always succeeds. */
int BirthdayVillager_EnterState12(BirthdayVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_0221c07c, BirthdayVillager_EnterState12)

/* func_ov004_0221c080: state 11's update does nothing. */
void BirthdayVillager_UpdateChoosing(BirthdayVillager *villager)
{
    (void) villager;
}
CLEAN_AS(func_ov004_0221c080, BirthdayVillager_UpdateChoosing)

/* func_ov004_0221c084: entering state 11 always succeeds. */
int BirthdayVillager_EnterChoosing(BirthdayVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_0221c084, BirthdayVillager_EnterChoosing)

/* func_ov004_0221c088: state 10's update: once the talk's state is 5 (its line out), the pockets
 * screen is opened (mode 0xd) on the pockets func_ov004_0221d468 picks; when it opens, state 11.
 * REQUIRES: its talk scene has a talk. */
void BirthdayVillager_UpdateAsk(BirthdayVillager *villager)
{
    if (talk_of(villager)->state == TALK_OBJECT_GONE &&
        GroupParams_OpenWithMask(Pockets_Select(func_ov004_0221d468), BIRTHDAY_VILLAGER_POCKETS_MODE) != 0) {
        BirthdayVillager_SetState(villager, BIRTHDAY_VILLAGER_CHOOSING);
    }
}
CLEAN_AS(func_ov004_0221c088, BirthdayVillager_UpdateAsk)

/* func_ov004_0221c0bc: entering state 10 (always succeeds): the talk's mode becomes 1.
 * REQUIRES: its talk scene has a talk. */
int BirthdayVillager_EnterAsk(BirthdayVillager *villager)
{
    talk_of(villager)->mode = 1;
    return 1;
}
CLEAN_AS(func_ov004_0221c0bc, BirthdayVillager_EnterAsk)

/* The update of states 6 and 9: once the talk has closed, the event ends. */
static void finish_when_closed(BirthdayVillager *villager)
{
    if (talk_of(villager) != NULL && talk_of(villager)->state == TALK_OBJECT_CLOSED) {
        EventQueue_FinishObjectEvent(villager);
    }
}

/* func_ov004_0221c0cc: state 9's update: the event ends once the talk has closed. */
void BirthdayVillager_UpdateGreet(BirthdayVillager *villager)
{
    finish_when_closed(villager);
}
CLEAN_AS(func_ov004_0221c0cc, BirthdayVillager_UpdateGreet)

/* func_ov004_0221c0ec: entering state 9 always succeeds. */
int BirthdayVillager_EnterGreet(BirthdayVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_0221c0ec, BirthdayVillager_EnterGreet)

/* How far from the player it runs, and how close it comes. */
#define BIRTHDAY_VILLAGER_RUN_DISTANCE 0x4000
#define BIRTHDAY_VILLAGER_NEAR_DISTANCE 0x3000
/* The rate of its run, and how far off its direction may be before it turns while walking. */
#define BIRTHDAY_VILLAGER_RUN_RATE 0x800
#define BIRTHDAY_VILLAGER_TURN_ANGLE 0x2000

/* func_ov004_0221c0f0: state 8's update. It heads for the player's start position: running
 * beyond 0x4000 from the player, walking within it (switching between the two motions when it
 * moves at all). The approach's countdown runs down; once within 0x3000 of the player or out
 * of time, it turns to the start position and talks (state 9); else, when its direction is more
 * than 0x2000 off, it turns to it as it goes on. */
void BirthdayVillager_UpdateApproach(BirthdayVillager *villager)
{
    Vec3 target = *PlayerActorOps_StartPosition(BIRTHDAY_VILLAGER_PLAYER_ACTOR);
    int distance = SceneObject_DistanceToActor(villager->base, BIRTHDAY_VILLAGER_PLAYER_ACTOR);
    if (distance > BIRTHDAY_VILLAGER_RUN_DISTANCE) {
        if (SceneMotion_Kind(motion_of(villager)) == BIRTHDAY_VILLAGER_MOTION_WALK) {
            SceneMotion_Request(motion_of(villager), BIRTHDAY_VILLAGER_MOTION_RUN, 1, 0, 0, BIRTHDAY_VILLAGER_RUN_RATE, 0, 0,
                                0, data_020c80f8, 0);
        }
    } else if (SceneMotion_Kind(motion_of(villager)) == BIRTHDAY_VILLAGER_MOTION_RUN) {
        SceneMotion_Request(motion_of(villager), BIRTHDAY_VILLAGER_MOTION_WALK, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    SceneMover_SetStart(mover_of(villager), &target);
    if (villager->approach_wait != 0) {
        villager->approach_wait--;
    }
    s16 yaw = Vec_YawTo(position_of(villager), &target);
    int off = Math_AbsDiff16(yaw_of(villager), yaw);
    if (distance <= BIRTHDAY_VILLAGER_NEAR_DISTANCE || villager->approach_wait == 0) {
        SceneAction_RequestTurnAndTalk(action_of(villager), 0, yaw, 0);
        BirthdayVillager_SetState(villager, BIRTHDAY_VILLAGER_GREET);
    } else if (off > BIRTHDAY_VILLAGER_TURN_ANGLE) {
        SceneMotion_Request(motion_of(villager), BIRTHDAY_VILLAGER_MOTION_TURN_WALK, 2, target.x, target.z, 0, yaw, 0, 0,
                            data_020c80f8, 0);
    }
}
CLEAN_AS(func_ov004_0221c0f0, BirthdayVillager_UpdateApproach)

/* func_ov004_0221c224: entering state 8 (always succeeds): 50 frames to approach, walking. */
int BirthdayVillager_EnterApproach(BirthdayVillager *villager)
{
    villager->approach_wait = 50;
    SceneMotion_Request(motion_of(villager), BIRTHDAY_VILLAGER_MOTION_WALK, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_0221c224, BirthdayVillager_EnterApproach)

/* func_ov004_0221c264: state 7's update: asks for an event about itself (its answer is not
 * used by the update's caller). */
int BirthdayVillager_UpdateCall(BirthdayVillager *villager)
{
    return EventQueue_RequestKind6(villager, 0);
}
CLEAN_AS(func_ov004_0221c264, BirthdayVillager_UpdateCall)

/* func_ov004_0221c270: entering state 7 always succeeds. */
int BirthdayVillager_EnterCall(BirthdayVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_0221c270, BirthdayVillager_EnterCall)

/* func_ov004_0221c274: state 6's update: the event ends once the talk has closed. */
void BirthdayVillager_UpdateTalk(BirthdayVillager *villager)
{
    finish_when_closed(villager);
}
CLEAN_AS(func_ov004_0221c274, BirthdayVillager_UpdateTalk)

/* func_ov004_0221c294: entering state 6 always succeeds. */
int BirthdayVillager_EnterTalk(BirthdayVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_0221c294, BirthdayVillager_EnterTalk)

/* func_ov004_0221c298: state 5's update: on to state 6. */
void BirthdayVillager_UpdateTurn(BirthdayVillager *villager)
{
    BirthdayVillager_SetState(villager, BIRTHDAY_VILLAGER_TALK);
}
CLEAN_AS(func_ov004_0221c298, BirthdayVillager_UpdateTurn)

/* func_ov004_0221c2a4: entering state 5: it turns to this console's player's field actor and
 * talks; fails when there is no such actor. */
int BirthdayVillager_EnterTurn(BirthdayVillager *villager)
{
    void *player = SessionPlayers_ActorOf(BIRTHDAY_VILLAGER_PLAYER_ACTOR);
    if (player != NULL) {
        SceneAction_RequestTurnAndTalk(action_of(villager), 0, SceneObject_YawTo(villager->base, player), 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221c2a4, BirthdayVillager_EnterTurn)

/* func_ov004_0221c2d8: state 4's update does nothing. */
void BirthdayVillager_UpdateHalt(BirthdayVillager *villager)
{
    (void) villager;
}
CLEAN_AS(func_ov004_0221c2d8, BirthdayVillager_UpdateHalt)

/* func_ov004_0221c2dc: entering state 4 (always succeeds): from states 1 to 3 the act is ended
 * (act 0, priority 2). */
int BirthdayVillager_EnterHalt(BirthdayVillager *villager)
{
    if (villager->state == BIRTHDAY_VILLAGER_FACE || villager->state == BIRTHDAY_VILLAGER_ACT_SHORT ||
        villager->state == BIRTHDAY_VILLAGER_ACT_LONG) {
        SceneMotion_RequestAct(motion_of(villager), 2, BIRTHDAY_VILLAGER_ACT_NONE, data_020c80f8);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221c2dc, BirthdayVillager_EnterHalt)

/* The countdown of states 2 and 3, one frame down (not below 0). */
static u8 count_down_act(BirthdayVillager *villager)
{
    if (villager->act_wait != 0) {
        villager->act_wait--;
    }
    return villager->act_wait;
}

/* func_ov004_0221c310: state 3's update: at 40 frames left act 10 or 23 (at random), at 1 act
 * 0, at 0 back to state 0. */
void BirthdayVillager_UpdateActLong(BirthdayVillager *villager)
{
    switch (count_down_act(villager)) {
        case 40:
            if (MainRandom_Below(2) == 0) {
                SceneMotion_RequestAct(motion_of(villager), 1, BIRTHDAY_VILLAGER_ACT_10, data_020c80f8);
            } else {
                SceneMotion_RequestAct(motion_of(villager), 1, BIRTHDAY_VILLAGER_ACT_23, data_020c80f8);
            }
            break;
        case 1:
            SceneMotion_RequestAct(motion_of(villager), 1, BIRTHDAY_VILLAGER_ACT_NONE, data_020c80f8);
            break;
        case 0:
            BirthdayVillager_SetState(villager, BIRTHDAY_VILLAGER_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221c310, BirthdayVillager_UpdateActLong)

/* func_ov004_0221c38c: entering state 3 (always succeeds): 50 frames. */
int BirthdayVillager_EnterActLong(BirthdayVillager *villager)
{
    villager->act_wait = 50;
    return 1;
}
CLEAN_AS(func_ov004_0221c38c, BirthdayVillager_EnterActLong)

/* func_ov004_0221c39c: state 2's update: at 20 frames left act 3, at 1 act 0, at 0 back to
 * state 0. */
void BirthdayVillager_UpdateActShort(BirthdayVillager *villager)
{
    switch (count_down_act(villager)) {
        case 20:
            SceneMotion_RequestAct(motion_of(villager), 1, BIRTHDAY_VILLAGER_ACT_3, data_020c80f8);
            break;
        case 1:
            SceneMotion_RequestAct(motion_of(villager), 1, BIRTHDAY_VILLAGER_ACT_NONE, data_020c80f8);
            break;
        case 0:
            BirthdayVillager_SetState(villager, BIRTHDAY_VILLAGER_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221c39c, BirthdayVillager_UpdateActShort)

/* func_ov004_0221c3fc: entering state 2 (always succeeds): 30 frames. */
int BirthdayVillager_EnterActShort(BirthdayVillager *villager)
{
    villager->act_wait = 30;
    return 1;
}
CLEAN_AS(func_ov004_0221c3fc, BirthdayVillager_EnterActShort)

/* func_ov004_0221c40c: state 1's update does nothing. */
void BirthdayVillager_UpdateFace(BirthdayVillager *villager)
{
    (void) villager;
}
CLEAN_AS(func_ov004_0221c40c, BirthdayVillager_UpdateFace)

/* func_ov004_0221c410: entering state 1: it turns to the object func_ov004_0221e2c0 gives and
 * looks at it; fails when there is none. */
int BirthdayVillager_EnterFace(BirthdayVillager *villager)
{
    u8 *object = func_ov004_0221e2c0();
    if (object == NULL) {
        return 0;
    }
    const Vec3 *at = (const Vec3 *) (const void *) (object + BIRTHDAY_VILLAGER_POSITION);
    s16 angle = Math_Atan2(at->x - position_of(villager)->x, at->z - position_of(villager)->z);
    SceneMotion_Request(motion_of(villager), BIRTHDAY_VILLAGER_MOTION_TURN, 1, 0, 0, 0, angle, 0, 0, data_020c80f8, 0);
    SceneLook_Request(look_of(villager), BIRTHDAY_VILLAGER_LOOK_AT_OBJECT, 0, (int) (uintptr_t) object, &data_021fbee8,
                      BIRTHDAY_VILLAGER_PLAYER_ACTOR, data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov004_0221c410, BirthdayVillager_EnterFace)

/* Waits after a turn and after a walk: 20 frames plus up to 69 or 79 more. */
#define BIRTHDAY_VILLAGER_WAIT_BASE 20
#define BIRTHDAY_VILLAGER_TURN_WAIT_RANGE 70
#define BIRTHDAY_VILLAGER_WALK_WAIT_RANGE 80
/* How close to its goal it stops when nothing is left to step around. */
#define BIRTHDAY_VILLAGER_GOAL_DISTANCE 0x200

/* func_ov004_0221c494: state 0's update: its walk about the room.
 * - While byte 0x508 of the object is set, a walk is turned into a stand.
 * - Standing: the wait runs down; at 0 it picks a goal (func_ov004_0221e1e0) and, when the
 *   goal's direction is not its own, turns to it (then waits 20 to 89 frames), else walks to it
 *   (then waits 20 to 99 frames); a motion that cannot be asked for leaves the wait at 0, to try
 *   again. Before that, a finished motion turns into a stand.
 * - Turning: once done, it walks to the goal.
 * - Walking: when blocked, it stands; when it can step aside, the mover heads for that point;
 *   else the mover heads for the goal again when it was elsewhere, or it stands once within
 *   0x200 of the goal. */
void BirthdayVillager_UpdateWander(BirthdayVillager *villager)
{
    SceneMotion *motion = motion_of(villager);

    if (*part(villager, BIRTHDAY_VILLAGER_BYTE_508) != 0 && SceneMotion_Kind(motion) == BIRTHDAY_VILLAGER_MOTION_WALK) {
        SceneMotion_Request(motion, BIRTHDAY_VILLAGER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        return;
    }
    if (SceneMotion_Kind(motion) == BIRTHDAY_VILLAGER_MOTION_STAND) {
        if (villager->wander_wait != 0) {
            villager->wander_wait--;
        }
        if (villager->wander_wait == 0) {
            villager->turn_yaw = (s16) func_ov004_0221e1e0(&villager->goal, position_of(villager), yaw_of(villager));
            villager->walk_point = villager->goal;
            if (villager->turn_yaw != yaw_of(villager)) {
                if (SceneMotion_Request(motion, BIRTHDAY_VILLAGER_MOTION_TURN, 1, 0, 0, 0, villager->turn_yaw, 0, 0,
                                        data_020c80f8, 0)) {
                    villager->wander_wait =
                        (u16) (MainRandom_Below(BIRTHDAY_VILLAGER_TURN_WAIT_RANGE) + BIRTHDAY_VILLAGER_WAIT_BASE);
                }
            } else if (SceneMotion_Request(motion, BIRTHDAY_VILLAGER_MOTION_WALK, 1, villager->goal.x, villager->goal.z, 0, 0,
                                           0, 0, data_020c80f8, 0)) {
                villager->wander_wait =
                    (u16) (MainRandom_Below(BIRTHDAY_VILLAGER_WALK_WAIT_RANGE) + BIRTHDAY_VILLAGER_WAIT_BASE);
            }
        } else if (SceneMotion_IsDone(motion)) {
            SceneMotion_RequestStand(motion, 1, data_020c80f8);
        }
    } else if (SceneMotion_Kind(motion) == BIRTHDAY_VILLAGER_MOTION_TURN) {
        if (SceneMotion_IsDone(motion)) {
            SceneMotion_Request(motion, BIRTHDAY_VILLAGER_MOTION_WALK, 1, villager->goal.x, villager->goal.z, 0, 0, 0, 0,
                                data_020c80f8, 0);
        }
    } else if (SceneMotion_Kind(motion) == BIRTHDAY_VILLAGER_MOTION_WALK) {
        Vec3 side;
        switch (SceneObject_SideStep(villager->base, &side)) {
            case SCENE_OBJECT_BLOCKED:
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
                break;
            case SCENE_OBJECT_SIDE_POINT:
                villager->walk_point = side;
                SceneMover_SetStart(mover_of(villager), &villager->walk_point);
                break;
            default:
                if (Vec_Differ(&villager->walk_point, &villager->goal)) {
                    villager->walk_point = villager->goal;
                    SceneMover_SetStart(mover_of(villager), &villager->goal);
                } else if (Vec_DistanceXZ(&villager->goal, position_of(villager)) < BIRTHDAY_VILLAGER_GOAL_DISTANCE) {
                    SceneMotion_RequestStand(motion, 1, data_020c80f8);
                }
                break;
        }
    }
}
CLEAN_AS(func_ov004_0221c494, BirthdayVillager_UpdateWander)

/* func_ov004_0221c6d4: entering state 0: it stands and looks ahead; fails when the stand cannot
 * be asked for. */
int BirthdayVillager_EnterWander(BirthdayVillager *villager)
{
    if (SceneMotion_RequestStand(motion_of(villager), 1, data_020c80f8)) {
        SceneLook_Request(look_of(villager), BIRTHDAY_VILLAGER_LOOK_AHEAD, 0, 0, &data_021fbee8,
                          BIRTHDAY_VILLAGER_PLAYER_ACTOR, data_020c814c, 1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221c6d4, BirthdayVillager_EnterWander)

/* _ZN18Obj_ov004_0225367419func_ov004_0221c72cEv: the update of the current state, through its
 * table (filled once). */
void BirthdayVillager_Update(BirthdayVillager *villager)
{
    static const MemberPointer *const updates[BIRTHDAY_VILLAGER_STATES] = {
        &data_ov004_022535a4, /* BirthdayVillager_UpdateWander */
        &data_ov004_02253584, /* BirthdayVillager_UpdateFace */
        &data_ov004_022535b4, /* BirthdayVillager_UpdateActShort */
        &data_ov004_022534f4, /* BirthdayVillager_UpdateActLong */
        &data_ov004_022534ec, /* BirthdayVillager_UpdateHalt */
        &data_ov004_022534e4, /* BirthdayVillager_UpdateTurn */
        &data_ov004_02253504, /* BirthdayVillager_UpdateTalk */
        &data_ov004_02253534, /* BirthdayVillager_UpdateCall */
        &data_ov004_0225352c, /* BirthdayVillager_UpdateApproach */
        &data_ov004_0225357c, /* BirthdayVillager_UpdateGreet */
        &data_ov004_02253594, /* BirthdayVillager_UpdateAsk */
        &data_ov004_022534dc, /* BirthdayVillager_UpdateChoosing */
        &data_ov004_0225350c, /* BirthdayVillager_UpdateState12 */
        &data_ov004_02253524, /* BirthdayVillager_UpdateThanks */
    };
    MemberTable_InitOnce(&data_ov004_02257a20, data_ov004_02257b4c, updates, BIRTHDAY_VILLAGER_STATES);
    /* REQUIRES: state >= 0; the ROM's signed test lets a negative one index before the table */
    if (villager->state >= 0 && villager->state < BIRTHDAY_VILLAGER_STATES) {
        MemberPointer_CallVoid(&data_ov004_02257b4c[villager->state], villager);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225367419func_ov004_0221c72cEv, BirthdayVillager_Update)

/* func_ov004_0221c844: enters `state` if its entry function (through a table, filled once)
 * agrees; whether it did. States 14 and above do not exist. */
int BirthdayVillager_SetState(BirthdayVillager *villager, int state)
{
    static const MemberPointer *const entries[BIRTHDAY_VILLAGER_STATES] = {
        &data_ov004_0225358c, /* BirthdayVillager_EnterWander */
        &data_ov004_0225359c, /* BirthdayVillager_EnterFace */
        &data_ov004_022535ac, /* BirthdayVillager_EnterActShort */
        &data_ov004_02253574, /* BirthdayVillager_EnterActLong */
        &data_ov004_0225356c, /* BirthdayVillager_EnterHalt */
        &data_ov004_02253564, /* BirthdayVillager_EnterTurn */
        &data_ov004_0225355c, /* BirthdayVillager_EnterTalk */
        &data_ov004_02253554, /* BirthdayVillager_EnterCall */
        &data_ov004_0225354c, /* BirthdayVillager_EnterApproach */
        &data_ov004_02253544, /* BirthdayVillager_EnterGreet */
        &data_ov004_022534fc, /* BirthdayVillager_EnterAsk */
        &data_ov004_022535bc, /* BirthdayVillager_EnterChoosing */
        &data_ov004_02253514, /* BirthdayVillager_EnterState12 */
        &data_ov004_0225351c, /* BirthdayVillager_EnterThanks */
    };
    MemberTable_InitOnce(&data_ov004_02257a14, data_ov004_02257adc, entries, BIRTHDAY_VILLAGER_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 13); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < BIRTHDAY_VILLAGER_STATES && MemberPointer_CallInt(&data_ov004_02257adc[state], villager) != 0) {
        villager->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221c844, BirthdayVillager_SetState)

/* The talk of the villager a talk scene belongs to (read through its pointer each time). */
static TalkObject *villager_talk_of(BirthdayVillagerTalk *talk)
{
    return talk_of(talk->villager);
}

/* func_ov004_0221c96c (the talk scene's receiver slot 0x18, the player's answer). After messages
 * 4 and 5: on the first answer, messages 9 or 10 (at random) when the pockets screen's
 * predicate picks any pocket, else message 6; on the other answer, messages 7 or 8 (at random).
 * The answer is read whatever the message. */
void BirthdayVillagerTalk_OnAnswer(BirthdayVillagerTalk *talk)
{
    u8 message;
    unsigned int answer = TalkAnswers_Picked(TalkObject_Answers(villager_talk_of(talk)));

    switch (message_of(talk)) {
        case 4:
        case 5:
            if (answer == 0) {
                if (Pockets_Select(func_ov004_0221d468) != 0) {
                    message = (u8) (MainRandom_Below(2) + 9);
                    TalkObject_SetMessage(villager_talk_of(talk), &message, NULL);
                } else {
                    message = 6;
                    TalkObject_SetMessage(villager_talk_of(talk), &message, NULL);
                }
            } else {
                message = (u8) (MainRandom_Below(2) + 7);
                TalkObject_SetMessage(villager_talk_of(talk), &message, NULL);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221c96c, BirthdayVillagerTalk_OnAnswer)

/* The talk scene's talk ends after its message, unless a message is set already. */
static void end_talk(BirthdayVillagerTalk *talk)
{
    u8 message = data_021f43e8;
    TalkObject_SetMessageIfNone((TalkObject *) (void *) talk->base.scene.talk, &message, NULL);
}

/* func_ov004_0221ca04 (the talk scene's receiver slot 0x14, a message ended):
 * - 7, 8 and 19 to 22: the talk ends;
 * - 9, 10: the villager goes to state 10 (asks for an item);
 * - 11 to 14: message 15 or 16 at random;
 * - 15, 16: the scene's command 3 hands the villager's item over (priority 5), the item goes
 *   into the player's pockets and the villager goes to state 13;
 * - 17, 18: bit 7 of its memory of the player is set (func_ov004_0221cfe0);
 * - others (4 to 6 among them): nothing. */
void BirthdayVillagerTalk_OnMessageEnded(BirthdayVillagerTalk *talk)
{
    u8 message;

    switch (message_of(talk)) {
        case 7:
        case 8:
        case 19:
        case 20:
        case 21:
        case 22:
            end_talk(talk);
            break;
        case 9:
        case 10:
            BirthdayVillager_SetState(talk->villager, BIRTHDAY_VILLAGER_ASK);
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            message = (u8) (MainRandom_Below(2) + 0xf);
            TalkObject_SetMessage(villager_talk_of(talk), &message, NULL);
            break;
        case 15:
        case 16:
            SceneCommand_RequestMotion13(&talk->base.scene, &talk->villager->gift, 0, 5, 0);
            CurrentPockets_Give(&talk->villager->gift, 0);
            BirthdayVillager_SetState(talk->villager, BIRTHDAY_VILLAGER_THANKS);
            break;
        case 17:
        case 18:
            func_ov004_0221cfe0(talk);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221ca04, BirthdayVillagerTalk_OnMessageEnded)

/* func_ov004_0221cae4 (the talk scene's receiver slot 0x10, a message begins): at messages 15
 * and 16 the villager picks the item it gives by its fondness of the player, keeps it and its
 * name becomes the talk's value 1. */
void BirthdayVillagerTalk_OnMessageBegun(BirthdayVillagerTalk *talk)
{
    switch (message_of(talk)) {
        case 15:
        case 16: {
            u16 gift = BirthdayVillager_PickGift(func_ov004_0221cec8(talk));
            talk->villager->gift = gift;
            SceneBase_PutItemName(scene_of(talk), (int) (uintptr_t) &gift, 1, BIRTHDAY_VILLAGER_ITEM_NAME_KIND);
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221cae4, BirthdayVillagerTalk_OnMessageBegun)

/* The fondness from which the gift comes from the player's record's group. */
#define BIRTHDAY_VILLAGER_FOND 0x40

/* An item drawn from the list of `kind` (group 0). */
static u16 draw_from_list(int kind)
{
    ItemList list;
    u16 item;

    ItemList_Construct(&list, kind, 0);
    ItemLists_Draw(&item, &list, 0, 0, 1, 1, 0);
    u16 drawn = item;
    ItemList_Destruct(&list);
    return drawn;
}

/* func_ov004_0221cb28: the item the villager gives for `fondness`: from list 1 at 0 or less,
 * from list 0 or 2 (at random) below 0x40, else one drawn by the group of the current player's
 * record (from list 0 when that gives no item). */
u16 BirthdayVillager_PickGift(int fondness)
{
    if (fondness <= 0) {
        return draw_from_list(1);
    }
    if (fondness < BIRTHDAY_VILLAGER_FOND) {
        if (MainRandom_Below(2) == 0) {
            return draw_from_list(0);
        }
        return draw_from_list(2);
    }
    u16 item;
    ItemLists_DrawByGroup(&item, (int) (uintptr_t) PlayerRecords_Current(), NULL);
    if (item == BIRTHDAY_VILLAGER_NO_ITEM) {
        return draw_from_list(0);
    }
    return item;
}
CLEAN_AS(func_ov004_0221cb28, BirthdayVillager_PickGift)

/* The size of the text the lines' message file name is written in. */
#define BIRTHDAY_VILLAGER_FILE_NAME_SIZE 0x28

/* func_ov004_0221cc14 (the talk scene's vtable slot 0x78, the line to say): the message file is
 * the villager's "ev_nbirth" one (written into data_ov004_02257a6c). In state 9 the message is
 * 0 or 1 at random. Else it is, by the villager's memory of the player, 2 or 3 when bit 6 is
 * clear (the first time), 0x13 to 0x16 when bit 7 is set, 4 or 5 otherwise; bit 6 is then set.
 * When the villager's talk scene has a talk, the villager's name becomes its part 1, the name
 * of the first other villager of the actor slots part 0, and item 0x1100 its values 0 and 1. */
void BirthdayVillagerTalk_Line(BirthdayVillagerTalk *talk, VillagerTalkLine *out)
{
    NpcId_FormatResourceName(TownVillager_NpcId(record_of(talk->villager->base)), data_ov004_02257a6c,
                             BIRTHDAY_VILLAGER_FILE_NAME_SIZE, data_ov004_02253734);
    out->text = (u32) (uintptr_t) data_ov004_02257a6c;
    if (talk->villager->state == BIRTHDAY_VILLAGER_GREET) {
        out->message = (u8) MainRandom_Below(2);
        return;
    }

    int first_time = func_ov004_0221d02c(talk);
    int marked = !first_time && func_ov004_0221cff8(talk);
    func_ov004_0221d014(talk);
    if (first_time) {
        out->message = (u8) (MainRandom_Below(2) + 2);
    } else if (marked) {
        out->message = (u8) (MainRandom_Below(4) + 0x13);
    } else {
        out->message = (u8) (MainRandom_Below(2) + 4);
    }

    if (talk->villager->talk.base.scene.talk == NULL) {
        return;
    }
    if (talk->villager != NULL && record_of(talk->villager->base) != NULL) {
        SceneBase_PutNpcName(scene_of(&talk->villager->talk), TownVillager_NpcId(record_of(talk->villager->base)), 1);
    }
    for (int i = 0; i < Actors_SlotCount(); i++) {
        u8 *other = Actors_SlotE(i);
        if (other != NULL && other != talk->villager->base) {
            SceneBase_PutNpcName(scene_of(&talk->villager->talk), TownVillager_NpcId(record_of(other)), 0);
            break;
        }
    }
    u16 item = BIRTHDAY_VILLAGER_LINE_ITEM;
    SceneBase_PutItemName(scene_of(talk), (int) (uintptr_t) &item, 0, BIRTHDAY_VILLAGER_ITEM_NAME_KIND);
    SceneBase_PutItemName(scene_of(talk), (int) (uintptr_t) &item, 1, BIRTHDAY_VILLAGER_ITEM_NAME_KIND);
}
CLEAN_AS(func_ov004_0221cc14, BirthdayVillagerTalk_Line)
