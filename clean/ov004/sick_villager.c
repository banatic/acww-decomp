/* The villager who talks with the lines of "q12_sick1_2" and "q12_sick3_5" (sick_villager.h). */
#include "sick_villager.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "birthday_guest.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/collision_map.h"
#include "main/current_pockets.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/group_params.h"
#include "main/item_code.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pockets.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_command.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_standard_anims.h"
#include "main/session_players.h"
#include "main/sound.h"
#include "main/spawner.h"
#include "main/talk_answers.h"
#include "main/talk_object.h"
#include "main/town_villager.h"
#include "main/villager_memories.h"
#include "main/villager_memory_entry.h"
#include "main/villager_mood.h"
#include "main/villager_move.h"
#include "main/villager_move_record.h"
#include "main/villager_scene_slots.h"
#include "main/villager_talk_scene.h"
#include "main/villager_town.h"

static_assert(sizeof(VillagerTalk) == 0x1a4, "the town villager's talk scene");
static_assert(sizeof(SickVillagerTalk) == 0x1ac, "its talk scene");
static_assert(offsetof(SickVillager, stage_named) == 0x898, "stage named");
static_assert(offsetof(SickVillager, answered) == 0x899, "answered");
static_assert(offsetof(SickVillager, sound_played) == 0x89a, "sound played");
static_assert(offsetof(SickVillager, state) == 0x89c, "state");
static_assert(offsetof(SickVillager, talk) == 0x8a0, "talk scene");
static_assert(offsetof(SickVillager, talk.base.scene.talk) == 0x8e0, "the talk scene's talk");
static_assert(offsetof(SickVillager, talk.stage) == 0xa44, "the talk scene's stage");
static_assert(offsetof(SickVillager, draw) == 0xa4c, "draw");
static_assert(offsetof(SickVillager, spawner) == 0xa54, "spawner part");
static_assert(offsetof(SickVillager, turn_yaw) == 0xa74, "turn yaw");
static_assert(offsetof(SickVillager, wander_wait) == 0xa76, "wander wait");
static_assert(offsetof(SickVillager, walk_point) == 0xa78, "walk point");
static_assert(offsetof(SickVillager, goal) == 0xa84, "goal");
static_assert(offsetof(SickVillager, act_wait) == 0xa90, "act wait");
static_assert(sizeof(SickVillager) == 0xa94, "the size func_ov004_02222a88 allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define SICK_VILLAGER_POSITION 0x5c /* Vec3 */
#define SICK_VILLAGER_YAW 0x8e      /* s16 */
#define SICK_VILLAGER_MOVER 0x350   /* SceneMover */
#define SICK_VILLAGER_BYTE_508 0x508
#define SICK_VILLAGER_MOTION 0x564 /* SceneMotion */
#define SICK_VILLAGER_ACTION 0x618 /* SceneAction */
#define SICK_VILLAGER_RECORD 0x830 /* u8 *: its town record (town_villager.h) */
#define SICK_VILLAGER_MOOD 0x83c   /* VillagerMood */
#define SICK_VILLAGER_BADLY 0x897  /* u8: the record's stage is above 1 */

/* The field actor of this console's player. */
#define SICK_VILLAGER_PLAYER_ACTOR 4

/* The kinds of motion asked for here (scene_motion_request.h). */
#define SICK_VILLAGER_MOTION_STAND 0
#define SICK_VILLAGER_MOTION_WALK 1
#define SICK_VILLAGER_MOTION_TURN 3

/* State 1: its frames, the frame its act 7 starts at, and the act ending it. */
#define SICK_VILLAGER_ACT_FRAMES 0x46
#define SICK_VILLAGER_ACT_START_FRAME 0x45
#define SICK_VILLAGER_ACT_SHOWN 7
#define SICK_VILLAGER_ACT_NONE 0
/* The wait after state 1: 20 frames and up to 19 more. */
#define SICK_VILLAGER_ACT_WAIT_BASE 0x14
#define SICK_VILLAGER_ACT_WAIT_RANGE 0x14
/* While walking above stage 1, the frames between its mood effects. */
#define SICK_VILLAGER_EFFECT_PERIOD 14
/* Waits after a turn and after a walk: 20 frames plus up to 69 or 79 more; above stage 1, 50
 * frames plus up to 69 more after both. */
#define SICK_VILLAGER_WAIT_BASE 20
#define SICK_VILLAGER_BADLY_WAIT_BASE 50
#define SICK_VILLAGER_TURN_WAIT_RANGE 70
#define SICK_VILLAGER_WALK_WAIT_RANGE 80
/* How close to its goal it acts when nothing is left to step around. */
#define SICK_VILLAGER_GOAL_DISTANCE 0x200

/* The mode its talk is kept in while state 5 waits (TalkObject.mode). */
#define SICK_VILLAGER_KEEP_TALK 1
/* The argument the player's pockets are opened with (GroupParams_OpenWithMask). */
#define SICK_VILLAGER_POCKETS_ARG 0xd

/* The size of the text the message file's name is written in. */
#define SICK_VILLAGER_FILE_NAME_SIZE 40

/* Its line's messages, by the player's answer (TalkAnswers_Picked) to the choices offered at
 * messages 0 to 5. */
#define SICK_VILLAGER_HAS_ITEM_FIRST 7 /* answer 0 with the item in the pockets: 7 to 9 */
#define SICK_VILLAGER_NO_ITEM_FIRST 10 /* answer 0 without it: 10 to 12 */
#define SICK_VILLAGER_OTHER_FIRST 4    /* another answer: 4 to 6 */
#define SICK_VILLAGER_NAMED_FIRST 19   /* answer 0 when the stage names a player: 19 to 21 */
/* The choices offered: at messages 0 to 2, three (21, 22 and 10 to 19, 2 the cancel); at 3 to
 * 5, two (23 and 120 to 129, 1 the cancel). */
#define SICK_VILLAGER_CHOICE_A 21
#define SICK_VILLAGER_CHOICE_B 22
#define SICK_VILLAGER_CHOICE_C_FIRST 10
#define SICK_VILLAGER_CHOICE_D 23
#define SICK_VILLAGER_CHOICE_E_FIRST 120
#define SICK_VILLAGER_CHOICE_RANGE 10
/* After the answer: at messages 7 to 9 it asks for the item (state 5); at 16 to 18 the sound
 * effect 95 is played. */
#define SICK_VILLAGER_SOUND 95

/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov004_022541d8[];
extern const u8 data_ov004_02254148[];
/* The tables of its states' update and entry functions (filled once from the constants below,
 * bit 0 of the guards saying they were). */
extern u32 data_ov004_02257f8c;
extern MemberPointer data_ov004_0225802c[SICK_VILLAGER_STATES];
extern u32 data_ov004_02257f90;
extern MemberPointer data_ov004_02257fec[SICK_VILLAGER_STATES];
extern const MemberPointer data_ov004_022540b0, data_ov004_02254100, data_ov004_022540d8, data_ov004_02254108,
    data_ov004_02254120, data_ov004_022540a0, data_ov004_022540b8, data_ov004_022540c8;
extern const MemberPointer data_ov004_022540f8, data_ov004_022540f0, data_ov004_022540d0, data_ov004_022540e0,
    data_ov004_022540e8, data_ov004_02254110, data_ov004_02254118, data_ov004_022540c0;
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The frames since the game started. */
extern u32 data_021fbdd0;
/* The value an answer's 0x70 is given here. */
extern u8 data_021f43f8;
/* The town's villagers. */
extern VillagerTown data_021e5a2c;
/* The message files "q12_sick1_2" and "q12_sick3_5", and the text its answer's file is written
 * in. */
extern const char data_ov004_02254298[], data_ov004_022542a4[];
extern char data_ov004_02257fc4[SICK_VILLAGER_FILE_NAME_SIZE];

/* Whether a pocket's item is the one it asks for (the item 0x155e, any variant), the state 0. */
extern int func_ov004_02222a30(u16 *item, int state);

static u8 *sk_part(SickVillager *villager, u32 offset)
{
    return villager->base + offset;
}

static Vec3 *sk_position_of(SickVillager *villager)
{
    return (Vec3 *) (void *) sk_part(villager, SICK_VILLAGER_POSITION);
}

static s16 sk_yaw_of(SickVillager *villager)
{
    return *(s16 *) (void *) sk_part(villager, SICK_VILLAGER_YAW);
}

static int sk_badly(SickVillager *villager)
{
    return *sk_part(villager, SICK_VILLAGER_BADLY) != 0;
}

static SceneMover *sk_mover_of(SickVillager *villager)
{
    return (SceneMover *) (void *) sk_part(villager, SICK_VILLAGER_MOVER);
}

static SceneMotion *sk_motion_of(SickVillager *villager)
{
    return (SceneMotion *) (void *) sk_part(villager, SICK_VILLAGER_MOTION);
}

static SceneAction *sk_action_of(SickVillager *villager)
{
    return (SceneAction *) (void *) sk_part(villager, SICK_VILLAGER_ACTION);
}

/* The talk its talk scene runs in (read through the villager). */
static TalkObject *sk_talk_object(SickVillager *villager)
{
    return (TalkObject *) (void *) villager->talk.base.scene.talk;
}

static void sk_set_talk_vtable(SickVillagerTalk *talk)
{
    talk->base.scene.vtable = data_ov004_02254148;
}

/* func_ov004_02221b9c (the talk scene's vtable slot 0x04, its deleting destructor). */
SickVillagerTalk *SickVillagerTalk_Delete(SickVillagerTalk *talk)
{
    sk_set_talk_vtable(talk);
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_02221b9c, SickVillagerTalk_Delete)

/* The destructor's body: the spawner part, its talk scene, then the town villager scene
 * object. */
static void sk_destruct(SickVillager *villager)
{
    *(const u8 **) (void *) villager->base = data_ov004_022541d8;
    Spawner_PartDestruct(villager->spawner);
    sk_set_talk_vtable(&villager->talk);
    VillagerTalkScene_DestructBody(&villager->talk.base);
    VillagerSceneObject_DestructBody(villager->base);
}

/* func_ov004_02221bbc (vtable slot 0x40): the destructor, without freeing. */
SickVillager *SickVillager_Destroy(SickVillager *villager)
{
    sk_destruct(villager);
    return villager;
}
CLEAN_AS(func_ov004_02221bbc, SickVillager_Destroy)

/* func_ov004_02221bf8 (vtable slot 0x44, the deleting destructor). */
SickVillager *SickVillager_Delete(SickVillager *villager)
{
    sk_destruct(villager);
    Heap_FreeAux(villager);
    return villager;
}
CLEAN_AS(func_ov004_02221bf8, SickVillager_Delete)

/* func_ov004_02221c38 (the talk scene's vtable slot 0x00, its destructor). */
SickVillagerTalk *SickVillagerTalk_Destroy(SickVillagerTalk *talk)
{
    sk_set_talk_vtable(talk);
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov004_02221c38, SickVillagerTalk_Destroy)

/* func_ov004_02221c50 (vtable slot 0x7c): its action sound is played only until it was once. */
int SickVillager_HasActionSound(SickVillager *villager)
{
    return villager->sound_played == 0;
}
CLEAN_AS(func_ov004_02221c50, SickVillager_HasActionSound)

/* func_ov004_02221c64 (vtable slot 0x80): notes its action sound was played. */
SickVillager *SickVillager_ActionSoundPlayed(SickVillager *villager)
{
    villager->sound_played = 1;
    return villager;
}
CLEAN_AS(func_ov004_02221c64, SickVillager_ActionSoundPlayed)

/* func_ov004_02221c70 (state 7's update): on to its talk (state 4). */
void SickVillager_UpdateBack(SickVillager *villager)
{
    SickVillager_SetState(villager, SICK_VILLAGER_TALK);
}
CLEAN_AS(func_ov004_02221c70, SickVillager_UpdateBack)

/* func_ov004_02221c7c (state 7's entry): 1. */
int SickVillager_EnterBack(SickVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_02221c7c, SickVillager_EnterBack)

/* func_ov004_02221c80 (state 6's update): nothing. */
void SickVillager_UpdatePockets(SickVillager *villager)
{
    (void) villager;
}
CLEAN_AS(func_ov004_02221c80, SickVillager_UpdatePockets)

/* func_ov004_02221c84 (state 6's entry): 1. */
int SickVillager_EnterPockets(SickVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_02221c84, SickVillager_EnterPockets)

/* func_ov004_02221c88 (state 5's update): once its talk is gone, the player's pockets are opened
 * for the items SickVillager_IsAskedItem takes; when they open, state 6.
 * REQUIRES: it has a talk (the ROM reads it without a check). */
void SickVillager_UpdateAsk(SickVillager *villager)
{
    if (sk_talk_object(villager)->state == TALK_OBJECT_GONE &&
        GroupParams_OpenWithMask(Pockets_Select(func_ov004_02222a30), SICK_VILLAGER_POCKETS_ARG) != 0) {
        SickVillager_SetState(villager, SICK_VILLAGER_POCKETS);
    }
}
CLEAN_AS(func_ov004_02221c88, SickVillager_UpdateAsk)

/* func_ov004_02221cbc (state 5's entry): its talk is kept for more (mode 1). 1.
 * REQUIRES: it has a talk (the ROM writes it without a check). */
int SickVillager_EnterAsk(SickVillager *villager)
{
    sk_talk_object(villager)->mode = SICK_VILLAGER_KEEP_TALK;
    return 1;
}
CLEAN_AS(func_ov004_02221cbc, SickVillager_EnterAsk)

/* func_ov004_02221ccc (state 4's update): once the talk has closed, the event ends. */
void SickVillager_UpdateTalk(SickVillager *villager)
{
    TalkObject *talk = sk_talk_object(villager);
    if (talk != NULL && talk->state == TALK_OBJECT_CLOSED) {
        EventQueue_FinishObjectEvent(villager);
    }
}
CLEAN_AS(func_ov004_02221ccc, SickVillager_UpdateTalk)

/* func_ov004_02221cec (state 4's entry): 1. */
int SickVillager_EnterTalk(SickVillager *villager)
{
    (void) villager;
    return 1;
}
CLEAN_AS(func_ov004_02221cec, SickVillager_EnterTalk)

/* func_ov004_02221cf0 (state 3's update): on to its talk (state 4). */
void SickVillager_UpdateTurn(SickVillager *villager)
{
    SickVillager_SetState(villager, SICK_VILLAGER_TALK);
}
CLEAN_AS(func_ov004_02221cf0, SickVillager_UpdateTurn)

/* func_ov004_02221cfc (state 3's entry): it turns to this console's player's field actor and
 * talks; fails when there is no such actor. */
int SickVillager_EnterTurn(SickVillager *villager)
{
    void *player = SessionPlayers_ActorOf(SICK_VILLAGER_PLAYER_ACTOR);
    if (player != NULL) {
        SceneAction_RequestTurnAndTalk(sk_action_of(villager), 0, SceneObject_YawTo(villager->base, player), 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02221cfc, SickVillager_EnterTurn)

/* func_ov004_02221d30 (state 2's update): nothing. */
void SickVillager_UpdateHalt(SickVillager *villager)
{
    (void) villager;
}
CLEAN_AS(func_ov004_02221d30, SickVillager_UpdateHalt)

/* func_ov004_02221d34 (state 2's entry): from state 1 its act ends (act 0, priority 2). 1. */
int SickVillager_EnterHalt(SickVillager *villager)
{
    if (villager->state == SICK_VILLAGER_ACT) {
        SceneMotion_RequestAct(sk_motion_of(villager), 2, SICK_VILLAGER_ACT_NONE, data_020c80f8);
    }
    return 1;
}
CLEAN_AS(func_ov004_02221d34, SickVillager_EnterHalt)

/* func_ov004_02221d64 (state 1's update): its frames count down; on the second it shows act 7,
 * at 1 frame left act 0 and its walk waits 20 to 39 frames; at 0 it wanders (state 0) when it
 * can, else it stays at 0 and tries again. */
void SickVillager_UpdateAct(SickVillager *villager)
{
    switch (villager->act_wait) {
        case SICK_VILLAGER_ACT_START_FRAME:
            SceneMotion_RequestAct(sk_motion_of(villager), 1, SICK_VILLAGER_ACT_SHOWN, data_020c80f8);
            break;
        case 1:
            SceneMotion_RequestAct(sk_motion_of(villager), 1, SICK_VILLAGER_ACT_NONE, data_020c80f8);
            villager->wander_wait = (u16) (MainRandom_Below(SICK_VILLAGER_ACT_WAIT_RANGE) + SICK_VILLAGER_ACT_WAIT_BASE);
            break;
        case 0:
            if (SickVillager_SetState(villager, SICK_VILLAGER_WANDER) != 0) {
                return;
            }
            break;
        default:
            break;
    }
    if (villager->act_wait != 0) {
        villager->act_wait--;
    }
}
CLEAN_AS(func_ov004_02221d64, SickVillager_UpdateAct)

/* func_ov004_02221dd8 (state 1's entry): it stands (priority 1) and its 70 frames begin; fails
 * when the stand cannot be asked for. */
int SickVillager_EnterAct(SickVillager *villager)
{
    if (SceneMotion_RequestStand(sk_motion_of(villager), 1, data_020c80f8) != 0) {
        villager->act_wait = SICK_VILLAGER_ACT_FRAMES;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02221dd8, SickVillager_EnterAct)

/* The wait after a turn (`walk` 0) or a walk (`walk` 1). */
static u16 sk_wait_after(SickVillager *villager, int walk)
{
    if (sk_badly(villager)) {
        return (u16) (MainRandom_Below(SICK_VILLAGER_TURN_WAIT_RANGE) + SICK_VILLAGER_BADLY_WAIT_BASE);
    }
    int range = walk ? SICK_VILLAGER_WALK_WAIT_RANGE : SICK_VILLAGER_TURN_WAIT_RANGE;
    return (u16) (MainRandom_Below(range) + SICK_VILLAGER_WAIT_BASE);
}

/* func_ov004_02221e0c (state 0's update): its walk about the room. Its motion's kind is asked
 * afresh at each test.
 * - Above stage 1, while it walks, the mood effect 3 is shown every 14 frames.
 * - While the base's byte 0x508 is set and it walks, it acts (state 1) when it can, and does
 *   nothing more this frame.
 * - Standing: the wait runs down; at 0 it picks a goal (BirthdayGuest_PickGoal, which also gives
 *   its direction) and the mover's point is the goal. When the direction is not its own it
 *   turns, else walks to the goal; when that can be asked for, it waits (sk_wait_after) before
 *   the next. Before that, a finished motion turns into a stand.
 * - Turning: once done, it walks to the goal.
 * - Walking: when blocked, it stands; when it can step aside, the mover heads for that point;
 *   else the mover heads for the goal again when it was elsewhere, or it acts (state 1) once
 *   within 0x200 of the goal. */
void SickVillager_UpdateWander(SickVillager *villager)
{
    SceneMotion *motion = sk_motion_of(villager);
    Vec3 *position = sk_position_of(villager);

    if (sk_badly(villager) && SceneMotion_Kind(motion) == SICK_VILLAGER_MOTION_WALK &&
        data_021fbdd0 % SICK_VILLAGER_EFFECT_PERIOD == 0) {
        VillagerMood_PlayEffect3((VillagerMood *) (void *) sk_part(villager, SICK_VILLAGER_MOOD), villager->base);
    }
    if (*sk_part(villager, SICK_VILLAGER_BYTE_508) != 0 && SceneMotion_Kind(motion) == SICK_VILLAGER_MOTION_WALK &&
        SickVillager_SetState(villager, SICK_VILLAGER_ACT) != 0) {
        return;
    }

    if (SceneMotion_Kind(motion) == SICK_VILLAGER_MOTION_STAND) {
        if (villager->wander_wait != 0) {
            villager->wander_wait--;
        }
        if (villager->wander_wait != 0) {
            if (SceneMotion_IsDone(motion)) {
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
            }
            return;
        }
        villager->turn_yaw = (s16) BirthdayGuest_PickGoal(&villager->goal, position, sk_yaw_of(villager));
        villager->walk_point = villager->goal;
        if (villager->turn_yaw != sk_yaw_of(villager)) {
            if (SceneMotion_Request(motion, SICK_VILLAGER_MOTION_TURN, 1, 0, 0, 0, villager->turn_yaw, 0, 0, data_020c80f8,
                                    0)) {
                villager->wander_wait = sk_wait_after(villager, 0);
            }
        } else if (SceneMotion_Request(motion, SICK_VILLAGER_MOTION_WALK, 1, villager->goal.x, villager->goal.z, 0, 0, 0, 0,
                                       data_020c80f8, 0)) {
            villager->wander_wait = sk_wait_after(villager, 1);
        }
    } else if (SceneMotion_Kind(motion) == SICK_VILLAGER_MOTION_TURN) {
        if (SceneMotion_IsDone(motion)) {
            SceneMotion_Request(motion, SICK_VILLAGER_MOTION_WALK, 1, villager->goal.x, villager->goal.z, 0, 0, 0, 0,
                                data_020c80f8, 0);
        }
    } else if (SceneMotion_Kind(motion) == SICK_VILLAGER_MOTION_WALK) {
        Vec3 side;
        switch (SceneObject_SideStep(villager->base, &side)) {
            case SCENE_OBJECT_BLOCKED:
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
                break;
            case SCENE_OBJECT_SIDE_POINT:
                villager->walk_point = side;
                SceneMover_SetStart(sk_mover_of(villager), &villager->walk_point);
                break;
            default:
                if (Vec_Differ(&villager->walk_point, &villager->goal)) {
                    villager->walk_point = villager->goal;
                    SceneMover_SetStart(sk_mover_of(villager), &villager->goal);
                } else if (Vec_DistanceXZ(&villager->goal, position) < SICK_VILLAGER_GOAL_DISTANCE) {
                    SickVillager_SetState(villager, SICK_VILLAGER_ACT);
                }
                break;
        }
    }
}
CLEAN_AS(func_ov004_02221e0c, SickVillager_UpdateWander)

/* func_ov004_02222098 (state 0's entry): it stands (priority 1); whether that could be asked
 * for. */
int SickVillager_EnterWander(SickVillager *villager)
{
    return SceneMotion_RequestStand(sk_motion_of(villager), 1, data_020c80f8);
}
CLEAN_AS(func_ov004_02222098, SickVillager_EnterWander)

/* _ZN18Obj_ov004_022541d819func_ov004_022220b4Ev: the update of the current state, through its
 * table (filled once). */
void SickVillager_Update(SickVillager *villager)
{
    static const MemberPointer *const updates[SICK_VILLAGER_STATES] = {
        &data_ov004_022540b0, /* SickVillager_UpdateWander */
        &data_ov004_02254100, /* SickVillager_UpdateAct */
        &data_ov004_022540d8, /* SickVillager_UpdateHalt */
        &data_ov004_02254108, /* SickVillager_UpdateTurn */
        &data_ov004_02254120, /* SickVillager_UpdateTalk */
        &data_ov004_022540a0, /* SickVillager_UpdateAsk */
        &data_ov004_022540b8, /* SickVillager_UpdatePockets */
        &data_ov004_022540c8, /* SickVillager_UpdateBack */
    };
    MemberTable_InitOnce(&data_ov004_02257f8c, data_ov004_0225802c, updates, SICK_VILLAGER_STATES);
    /* REQUIRES: state >= 0; the ROM's signed test lets a negative one index before the table */
    if (villager->state >= 0 && villager->state < SICK_VILLAGER_STATES) {
        MemberPointer_CallVoid(&data_ov004_0225802c[villager->state], villager);
    }
}
CLEAN_AS(_ZN18Obj_ov004_022541d819func_ov004_022220b4Ev, SickVillager_Update)

/* func_ov004_02222178: enters `state` if its entry function (through a table, filled once)
 * agrees; whether it did. States 8 and above do not exist. */
int SickVillager_SetState(SickVillager *villager, int state)
{
    static const MemberPointer *const entries[SICK_VILLAGER_STATES] = {
        &data_ov004_022540f8, /* SickVillager_EnterWander */
        &data_ov004_022540f0, /* SickVillager_EnterAct */
        &data_ov004_022540d0, /* SickVillager_EnterHalt */
        &data_ov004_022540e0, /* SickVillager_EnterTurn */
        &data_ov004_022540e8, /* SickVillager_EnterTalk */
        &data_ov004_02254110, /* SickVillager_EnterAsk */
        &data_ov004_02254118, /* SickVillager_EnterPockets */
        &data_ov004_022540c0, /* SickVillager_EnterBack */
    };
    MemberTable_InitOnce(&data_ov004_02257f90, data_ov004_02257fec, entries, SICK_VILLAGER_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 7); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < SICK_VILLAGER_STATES && MemberPointer_CallInt(&data_ov004_02257fec[state], villager) != 0) {
        villager->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02222178, SickVillager_SetState)

/* The message `message` of the file in data_ov004_02257fc4 for the villager's talk. */
static void sk_say(SickVillager *villager, u8 message)
{
    TalkObject_SetMessage(sk_talk_object(villager), &message, data_ov004_02257fc4);
}

/* func_ov004_0222224c (the talk scene's receiver slot 0x18, the player's answer): the answer
 * picked is read, the file ("q12_sick1_2", above stage 1 "q12_sick3_5") written into
 * data_ov004_02257fc4 and the answer noted. Then, when the record's stage named no player at its
 * line: answer 0 gives 7 to 9 with the item in the pockets (SickVillager_IsAskedItem), else 10 to 12;
 * answer 1 gives 0 to 3, another 4 to 6. When it named one: answer 0 gives 19 to 21, another 4
 * to 6. */
void SickVillagerTalk_OnAnswer(SickVillagerTalk *talk)
{
    SickVillager *villager = talk->villager;
    unsigned int answer = TalkAnswers_Picked(TalkObject_Answers(sk_talk_object(villager)));
    const char *file = sk_badly(villager) ? data_ov004_022542a4 : data_ov004_02254298;
    u8 *record = *(u8 **) (void *) sk_part(villager, SICK_VILLAGER_RECORD);
    NpcId_FormatResourceName(TownVillager_NpcId(record), data_ov004_02257fc4, SICK_VILLAGER_FILE_NAME_SIZE, file);
    villager->answered = 1;

    if (villager->stage_named == 0) {
        switch (answer) {
            case 0:
                if (Pockets_Select(func_ov004_02222a30) != 0) {
                    sk_say(villager, (u8) (MainRandom_Below(3) + SICK_VILLAGER_HAS_ITEM_FIRST));
                } else {
                    sk_say(villager, (u8) (MainRandom_Below(3) + SICK_VILLAGER_NO_ITEM_FIRST));
                }
                break;
            case 1:
                sk_say(villager, (u8) MainRandom_Below(4));
                break;
            default:
                sk_say(villager, (u8) (MainRandom_Below(3) + SICK_VILLAGER_OTHER_FIRST));
                break;
        }
    } else if (answer == 0) {
        sk_say(villager, (u8) (MainRandom_Below(3) + SICK_VILLAGER_NAMED_FIRST));
    } else {
        sk_say(villager, (u8) (MainRandom_Below(3) + SICK_VILLAGER_OTHER_FIRST));
    }
}
CLEAN_AS(func_ov004_0222224c, SickVillagerTalk_OnAnswer)

/* The answer `index` of `answers` set to the message `message` (file 0). */
static void sk_offer(TalkAnswers *answers, int index, u8 message)
{
    TalkAnswers_Set(answers, index, &message, 0, &data_021f43f8, NULL, 0);
}

/* func_ov004_022223b8 (the talk scene's receiver slot 0x14, a message ended). Before an answer:
 * at messages 0 to 2 the talk's answers become three (21, 22 and 10 to 19 at random; 2 the
 * cancel), at 3 to 5 two (23 and 120 to 129; 1 the cancel), their texts loaded and the choices
 * opened when the message's walk stops; with no answers nothing. After one: at messages 7 to 9
 * it asks for the item (state 5); at 16 to 18 the sound effect 95 is played. */
void SickVillagerTalk_OnMessageEnded(SickVillagerTalk *talk)
{
    SickVillager *villager = talk->villager;
    u8 message = ((const MessageReceiver *) (const void *) talk)->message;
    TalkObject *object = (TalkObject *) (void *) talk->base.scene.talk;

    if (villager->answered == 0) {
        TalkAnswers *answers;
        switch (message) {
            case 0:
            case 1:
            case 2:
                answers = TalkObject_Answers(object);
                if (answers != NULL) {
                    TalkAnswers_Reset(answers, 3, 2);
                    sk_offer(answers, 0, SICK_VILLAGER_CHOICE_A);
                    sk_offer(answers, 1, SICK_VILLAGER_CHOICE_B);
                    sk_offer(answers, 2, (u8) (MainRandom_Below(SICK_VILLAGER_CHOICE_RANGE) + SICK_VILLAGER_CHOICE_C_FIRST));
                    TalkAnswers_LoadTexts(answers);
                    TalkObject_OpenChoices(object, 1);
                }
                break;
            case 3:
            case 4:
            case 5:
                answers = TalkObject_Answers(object);
                if (answers != NULL) {
                    TalkAnswers_Reset(answers, 2, 1);
                    sk_offer(answers, 0, SICK_VILLAGER_CHOICE_D);
                    sk_offer(answers, 1, (u8) (MainRandom_Below(SICK_VILLAGER_CHOICE_RANGE) + SICK_VILLAGER_CHOICE_E_FIRST));
                    TalkAnswers_LoadTexts(answers);
                    TalkObject_OpenChoices(object, 1);
                }
                break;
            default:
                break;
        }
    } else {
        switch (message) {
            case 7:
            case 8:
            case 9:
                SickVillager_SetState(villager, SICK_VILLAGER_ASK);
                break;
            case 16:
            case 17:
            case 18:
                SoundSys_PlaySe(SICK_VILLAGER_SOUND);
                break;
            default:
                break;
        }
    }
}
CLEAN_AS(func_ov004_022223b8, SickVillagerTalk_OnMessageEnded)

/* func_ov004_0222251c (the talk scene's receiver slot 0x10, a message begins): the player the
 * current stage of the town's villager move record names (asked twice), when there is one, is
 * the talk's name 0. */
void SickVillagerTalk_OnMessageBegun(SickVillagerTalk *talk)
{
    VillagerMove *move = VillagerMove_Record(&data_021e5a2c);
    if (move != NULL && VillagerMoveRecord_StagePlayer(move) != NULL) {
        SceneBase_PutNameAt10((SceneBase *) (void *) talk, VillagerMoveRecord_StagePlayer(move), 0);
    }
}
CLEAN_AS(func_ov004_0222251c, SickVillagerTalk_OnMessageBegun)

/* The town villager scene object's parts used by its set-up, start and events. */
#define SICK_VILLAGER_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define SICK_VILLAGER_LOOK 0x3b0           /* SceneLook */
#define SICK_VILLAGER_FOOTSTEPS 0x558      /* Footsteps */
#define SICK_VILLAGER_PARTICIPANT 0x560    /* u8: whose system the last event came from */

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define SICK_VILLAGER_EVENT_TALK 0
#define SICK_VILLAGER_EVENT_STARTS 3
#define SICK_VILLAGER_EVENT_REFUSED 4
#define SICK_VILLAGER_EVENT_ENDED 8

/* The lines table VillagerTalkScene_Start is given: 17 and above leave the line members as they
 * are (the talk scene's own vtable slot 0x78 says the line). */
#define SICK_VILLAGER_TALK_OWN_LINES 0x11

/* The first line's messages: 0 to 2, or 3 to 5 when the record's current stage names a
 * player. */
#define SICK_VILLAGER_FIRST_LINES 3
#define SICK_VILLAGER_NAMED_LINES_FIRST 3
/* After the pockets: nothing picked gives 13 to 15, the item handed 16 to 18. */
#define SICK_VILLAGER_NOTHING_PICKED_FIRST 0xd
#define SICK_VILLAGER_HANDED_FIRST 0x10
/* The value the scene's command 4 hands the item over with. */
#define SICK_VILLAGER_HAND_MOTION_ARG 6
/* The item it asks for. */
#define SICK_VILLAGER_ASKED_ITEM 0x155e

/* Above stage 1: its first and second standard animations and its walking pace (index 1:
 * speed, speed-up, slow-down); else the pace of a well villager. */
#define SICK_VILLAGER_BADLY_ANIM_FIRST 0xe9
#define SICK_VILLAGER_BADLY_ANIM_SECOND 0xea
#define SICK_VILLAGER_PACE 1
#define SICK_VILLAGER_BADLY_SPEED 0xa4
#define SICK_VILLAGER_BADLY_SPEED_CHANGE 0x10
#define SICK_VILLAGER_SPEED 0xcd
#define SICK_VILLAGER_SPEED_CHANGE 0x14
/* The look asked for above stage 1: none (straight ahead), priority 0. */
#define SICK_VILLAGER_LOOK_AHEAD 0

/* The side of an acre in tiles. */
#define SICK_VILLAGER_ACRE_TILES 0x10

/* The villager of this class that is set up, cleared when it may be deleted. */
extern SickVillager *data_ov004_02257f7c;
/* The text its first line's message file name is written in, and those files ("q12_ask1_2",
 * above stage 1 "q12_ask3_5"). */
extern char data_ov004_02257f9c[SICK_VILLAGER_FILE_NAME_SIZE];
extern const char data_ov004_022542b0[], data_ov004_022542bc[];
/* Its draw member (SickVillager_DrawModel), copied in at its start. */
extern const MemberPointer data_ov004_022540a8;
/* The map of the scene. */
extern AcreMap *data_021c80bc;
/* The look's point and range when it names neither. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;

/* func_ov004_02222554 (the talk scene's vtable slot 0x78, the line to say): the file
 * "q12_ask1_2" (above stage 1 "q12_ask3_5") for the villager, written into
 * data_ov004_02257f9c, the player's answer forgotten, and a message 0 to 2, or 3 to 5 when the
 * current stage of the town's villager move record names a player (which is noted).
 * QUIRK: the talk's stage is asked for first and not used. */
void SickVillagerTalk_Line(SickVillagerTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) data_ov004_02257f9c;
    (void) SickVillagerTalk_Stage(talk);
    SickVillager *villager = talk->villager;
    u8 *record = *(u8 **) (void *) sk_part(villager, SICK_VILLAGER_RECORD);
    const char *file = sk_badly(villager) ? data_ov004_022542bc : data_ov004_022542b0;
    NpcId_FormatResourceName(TownVillager_NpcId(record), data_ov004_02257f9c, SICK_VILLAGER_FILE_NAME_SIZE, file);
    villager->answered = 0;
    if (SickVillagerTalk_StageNamesPlayer(talk)) {
        out->message = (u8) (MainRandom_Below(SICK_VILLAGER_FIRST_LINES) + SICK_VILLAGER_NAMED_LINES_FIRST);
        villager->stage_named = 1;
    } else {
        out->message = (u8) MainRandom_Below(SICK_VILLAGER_FIRST_LINES);
        villager->stage_named = 0;
    }
}
CLEAN_AS(func_ov004_02222554, SickVillagerTalk_Line)

/* func_ov004_022225fc (the talk scene's vtable slot 0x80, each step): in state 6, once the
 * pockets screen has closed: when nothing was picked the talk window opens again on message 13
 * to 15 and the villager talks (state 4); else the picked pocket is emptied, the message is 16
 * to 18, the scene's command 4 hands over the item 0x155e and the villager goes back (state
 * 7). */
void SickVillagerTalk_TakeItem(SickVillagerTalk *talk)
{
    u8 message;

    if (talk->villager->state != SICK_VILLAGER_POCKETS || !GroupParams_CanOpen()) {
        return;
    }
    TalkObject *window = (TalkObject *) (void *) talk->base.scene.talk;
    if (!GroupParams_C4CIs1()) {
        window->next_state = TALK_OBJECT_OPENING;
        message = (u8) (MainRandom_Below(3) + SICK_VILLAGER_NOTHING_PICKED_FIRST);
        TalkObject_SetMessage(window, &message, NULL);
        SickVillager_SetState(talk->villager, SICK_VILLAGER_TALK);
    } else {
        CurrentPockets_Empty(GroupParams_Arg());
        message = (u8) (MainRandom_Below(3) + SICK_VILLAGER_HANDED_FIRST);
        TalkObject_SetMessage(window, &message, NULL);
        u16 item = SICK_VILLAGER_ASKED_ITEM;
        SceneCommand_RequestMotion14(&talk->base.scene, &item, 0, SICK_VILLAGER_HAND_MOTION_ARG, 0);
        SickVillager_SetState(talk->villager, SICK_VILLAGER_BACK);
    }
}
CLEAN_AS(func_ov004_022225fc, SickVillagerTalk_TakeItem)

/* func_ov004_0222269c (the talk scene's vtable slot 0x84, told which command ended): after
 * command 4 (the item handed) the current stage of the town's villager move record names the
 * current player and the talk window opens again. */
void SickVillagerTalk_OnCommandEnd(SickVillagerTalk *talk, int command)
{
    if (command == SCENE_COMMAND_MOTION_14) {
        SickVillagerTalk_NameStagePlayer();
        ((TalkObject *) (void *) talk->base.scene.talk)->next_state = TALK_OBJECT_OPENING;
    }
}
CLEAN_AS(func_ov004_0222269c, SickVillagerTalk_OnCommandEnd)

/* func_ov004_022226b4: its talk scene started for `villager` (with its own lines) and kept
 * pointing back at it. */
void SickVillagerTalk_Start(SickVillagerTalk *talk, SickVillager *villager)
{
    VillagerTalkScene_Start(&talk->base, villager->base, SICK_VILLAGER_TALK_OWN_LINES);
    talk->villager = villager;
}
CLEAN_AS(func_ov004_022226b4, SickVillagerTalk_Start)

/* func_ov004_022226d4: the current stage of the town's villager move record names the current
 * player. */
void SickVillagerTalk_NameStagePlayer(void)
{
    VillagerMove *move = VillagerMove_Record(&data_021e5a2c);
    VillagerMoveRecord_SetStagePlayer(move, PlayerRecord_Player(PlayerRecords_Current()));
}
CLEAN_AS(func_ov004_022226d4, SickVillagerTalk_NameStagePlayer)

/* func_ov004_022226f8: whether the current stage of the town's villager move record names a
 * player. The talk is not used. */
int SickVillagerTalk_StageNamesPlayer(SickVillagerTalk *talk)
{
    (void) talk;
    return VillagerMoveRecord_HasStagePlayer(VillagerMove_Record(&data_021e5a2c)) != 0;
}
CLEAN_AS(func_ov004_022226f8, SickVillagerTalk_StageNamesPlayer)

/* func_ov004_0222271c: the stage of the town's villager move record at its set-up. */
int SickVillagerTalk_Stage(SickVillagerTalk *talk)
{
    return talk->stage;
}
CLEAN_AS(func_ov004_0222271c, SickVillagerTalk_Stage)

/* func_ov004_02222728 (vtable slot 0x4c, told of an event by `participant`'s system, 4 for this
 * one): 3, an event starts: the participant kept, its act ends (state 2); 0, the player talks
 * to it: the participant kept, the talk's partner this console's player's field actor, it turns
 * to talk (state 3); 8, the event ended: it has met the current player
 * (SickVillager_MeetPlayer) and wanders (state 0); 4, refused: it wanders. */
void SickVillager_OnEvent(SickVillager *villager, unsigned int code, int participant)
{
    switch (code) {
        case SICK_VILLAGER_EVENT_STARTS:
            *sk_part(villager, SICK_VILLAGER_PARTICIPANT) = (u8) participant;
            SickVillager_SetState(villager, SICK_VILLAGER_HALT);
            break;
        case SICK_VILLAGER_EVENT_TALK:
            *sk_part(villager, SICK_VILLAGER_PARTICIPANT) = (u8) participant;
            SceneBase_SetMotionArg((SceneBase *) (void *) &villager->talk,
                                   SceneObject_ActorObject(villager->base, SICK_VILLAGER_PLAYER_ACTOR));
            SickVillager_SetState(villager, SICK_VILLAGER_TURN);
            break;
        case SICK_VILLAGER_EVENT_ENDED:
            SickVillager_MeetPlayer(villager);
            SickVillager_SetState(villager, SICK_VILLAGER_WANDER);
            break;
        case SICK_VILLAGER_EVENT_REFUSED:
            SickVillager_SetState(villager, SICK_VILLAGER_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02222728, SickVillager_OnEvent)

/* func_ov004_022227b8 (vtable slot 0x48): whether the player may talk to it: its action idle,
 * and wandering or acting (states 0 and 1). */
int SickVillager_MayAct(SickVillager *villager)
{
    if (SceneAction_IsBusy(sk_action_of(villager))) {
        return 0;
    }
    return (u32) villager->state <= (u32) SICK_VILLAGER_ACT;
}
CLEAN_AS(func_ov004_022227b8, SickVillager_MayAct)

/* func_ov004_022227e8: with a current player and a town record, the villager's memory of the
 * player is found or taken (VillagerMemory_Meet) and updated for a meeting now.
 * QUIRK: the memory is updated without a check that one was found. */
void SickVillager_MeetPlayer(SickVillager *villager)
{
    u8 *player_record = PlayerRecords_Current();
    if (player_record == NULL) {
        return;
    }
    u8 *record = *(u8 **) (void *) sk_part(villager, SICK_VILLAGER_RECORD);
    if (record == NULL) {
        return;
    }
    VillagerMemory *memory = VillagerMemory_Meet(record, PlayerRecord_Player(player_record));
    VillagerMemoryEntry_Update(memory, NULL, NULL, NULL);
}
CLEAN_AS(func_ov004_022227e8, SickVillager_MeetPlayer)

/* func_ov004_02222820: in the first acre of the scene's map (none when the map is empty), every
 * tile whose item code is 0xf031 or of a kind with variants (ItemCode_IsF031OrVariant) has its
 * path unit unlinked, row by row. The villager is not used. */
void SickVillager_UnlinkItemTiles(SickVillager *villager)
{
    (void) villager;
    AcreMap *map = data_021c80bc;
    AcreRecord *acre = NULL;
    if (map->acres_wide != 0 && map->acres_high != 0 && map->acres != NULL) {
        acre = (AcreRecord *) (void *) map->acres;
    }
    for (int z = 0; z < SICK_VILLAGER_ACRE_TILES; z++) {
        for (int x = 0; x < SICK_VILLAGER_ACRE_TILES; x++) {
            u16 *tile = AcreRecord_Tile(acre, (unsigned int) x, (unsigned int) z, 0);
            if (tile != NULL && ItemCode_IsF031OrVariant(tile)) {
                CollisionMap_UnlinkPathUnit(x, z);
            }
        }
    }
}
CLEAN_AS(func_ov004_02222820, SickVillager_UnlinkItemTiles)

/* _ZN18Obj_ov004_022541d819func_ov004_0222287cEv (vtable slot 0x68, each frame): its state's
 * update, then its mood follows it. 1. */
int SickVillager_Frame(SickVillager *villager)
{
    SickVillager_Update(villager);
    VillagerMood_FollowVillager((VillagerMood *) (void *) sk_part(villager, SICK_VILLAGER_MOOD), villager->base);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_022541d819func_ov004_0222287cEv, SickVillager_Frame)

/* func_ov004_0222289c (vtable slot 0x10): whether it may be deleted (the town villager's
 * answer); when it may, it is no longer the villager set up. */
int SickVillager_CanDelete(SickVillager *villager)
{
    if (VillagerSceneObject_CanDelete(villager->base) == 0) {
        return 0;
    }
    data_ov004_02257f7c = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0222289c, SickVillager_CanDelete)

/* func_ov004_022228c0 (vtable slot 0x24, its draw): its draw member when it has one, and its
 * answer; else 1. */
int SickVillager_Draw(SickVillager *villager)
{
    if (villager->draw.function != 0) {
        return MemberPointer_CallInt(&villager->draw, villager);
    }
    return 1;
}
CLEAN_AS(func_ov004_022228c0, SickVillager_Draw)

/* func_ov004_022228f4 (its draw member): the scene object drawn; whether it was. */
int SickVillager_DrawModel(SickVillager *villager)
{
    return SceneObject_Draw(villager->base) != 0;
}
CLEAN_AS(func_ov004_022228f4, SickVillager_DrawModel)

/* func_ov004_0222290c (vtable slot 0x00, its start): the town villager's start; then its draw
 * member is SickVillager_DrawModel, the room's item tiles are unlinked from the paths
 * (SickVillager_UnlinkItemTiles) and its footsteps are on. Whether the start was done. */
int SickVillager_Start(SickVillager *villager)
{
    if (VillagerSceneObject_Start(villager->base) == 0) {
        return 0;
    }
    villager->draw = data_ov004_022540a8;
    SickVillager_UnlinkItemTiles(villager);
    Footsteps_Enable((Footsteps *) (void *) sk_part(villager, SICK_VILLAGER_FOOTSTEPS));
    return 1;
}
CLEAN_AS(func_ov004_0222290c, SickVillager_Start)

/* func_ov004_02222950 (vtable slot 0x04, its set-up): the town villager's set-up; then it is the
 * villager set up (data_ov004_02257f7c), its talk scene becomes its scene and is started, and
 * the talk keeps the stage of the town's villager move record. Above stage 1 its standard
 * animations are 0xe9 and 0xea, it walks slower, looks straight ahead and 0x897 is set; else it
 * walks at a well villager's pace. Then it wanders (state 0). Whether the set-up was done. */
int SickVillager_Init(SickVillager *villager)
{
    if (VillagerSceneObject_Init(villager->base) == 0) {
        return 0;
    }
    data_ov004_02257f7c = villager;
    SceneObject_SetScene(villager->base, (SceneBase *) (void *) &villager->talk);
    SickVillagerTalk_Start(&villager->talk, villager);
    villager->talk.stage = VillagerMove_Record(&data_021e5a2c)->stage;
    if ((unsigned int) SickVillagerTalk_Stage(&villager->talk) > 1) {
        SceneStandardAnims *anims = (SceneStandardAnims *) (void *) sk_part(villager, SICK_VILLAGER_STANDARD_ANIMS);
        SceneStandardAnims_SetSecond(anims, SICK_VILLAGER_BADLY_ANIM_SECOND);
        SceneStandardAnims_SetFirst(anims, SICK_VILLAGER_BADLY_ANIM_FIRST);
        SceneMover_SetPace(sk_mover_of(villager), SICK_VILLAGER_PACE, SICK_VILLAGER_BADLY_SPEED,
                           SICK_VILLAGER_BADLY_SPEED_CHANGE, SICK_VILLAGER_BADLY_SPEED_CHANGE);
        SceneLook_Request((SceneLook *) (void *) sk_part(villager, SICK_VILLAGER_LOOK), SICK_VILLAGER_LOOK_AHEAD, 0, 0,
                          &data_021fbee8, SICK_VILLAGER_PLAYER_ACTOR, data_020c814c, 1);
        *sk_part(villager, SICK_VILLAGER_BADLY) = 1;
    } else {
        SceneMover_SetPace(sk_mover_of(villager), SICK_VILLAGER_PACE, SICK_VILLAGER_SPEED, SICK_VILLAGER_SPEED_CHANGE,
                           SICK_VILLAGER_SPEED_CHANGE);
        *sk_part(villager, SICK_VILLAGER_BADLY) = 0;
    }
    SickVillager_SetState(villager, SICK_VILLAGER_WANDER);
    return 1;
}
CLEAN_AS(func_ov004_02222950, SickVillager_Init)

/* func_ov004_02222a30 (the pockets' predicate, handed to Pockets_Select by its symbol): whether a
 * slot in the state 0 holds the item 0x155e, of any variant when the code has variants. */
int SickVillager_IsAskedItem(u16 *item, int state)
{
    if (state != 0) {
        return 0;
    }
    if (ItemCode_HasVariant(item)) {
        u16 asked = SICK_VILLAGER_ASKED_ITEM;
        int variant = ItemCode_VariantItem(item);
        return variant == ItemCode_VariantItem(&asked);
    }
    return *item == SICK_VILLAGER_ASKED_ITEM;
}
CLEAN_AS(func_ov004_02222a30, SickVillager_IsAskedItem)

/* func_ov004_02222a88 (its create function): allocates (zeroed) and builds a villager: the town
 * villager scene object, its talk scene and its spawner part. */
SickVillager *SickVillager_New(void)
{
    SickVillager *villager = Heap_AllocAuxZeroed(sizeof(SickVillager));
    if (villager != NULL) {
        VillagerSceneObject_Construct(villager->base);
        *(const u8 **) (void *) villager->base = data_ov004_022541d8;
        VillagerTalkScene_ConstructAlt(&villager->talk.base);
        sk_set_talk_vtable(&villager->talk);
        Spawner_PartConstruct(villager->spawner);
    }
    return villager;
}
CLEAN_AS(func_ov004_02222a88, SickVillager_New)
