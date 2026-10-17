/* The other villager of the rooms' "ev_nbirth" talks (birthday_guest.h). */
#include "birthday_guest.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/fx_math.h"  /* Math_Atan2 */
#include "autoload_2/heap.h"
#include "birthday_villager.h"
#include "clean.h"
#include "main/camera_modes.h"
#include "main/event_queue.h"
#include "main/main_random.h"
#include "main/npc_id.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_query.h"
#include "main/session_players.h"
#include "main/talk_object.h"
#include "main/town_villager.h"
#include "main/villager_memories.h"
#include "main/villager_memory_entry.h"
#include "main/villager_roster.h"
#include "main/villager_scene_slots.h"
#include "main/villager_talk_scene.h"
#include "main/villager_town.h"

static_assert(sizeof(BirthdayGuestTalk) == 0x1a8, "its talk scene");
static_assert(offsetof(BirthdayGuest, state) == 0x898, "state");
static_assert(offsetof(BirthdayGuest, talk) == 0x89c, "talk scene");
static_assert(offsetof(BirthdayGuest, talk.base.scene.talk) == 0x8dc, "the talk scene's talk");
static_assert(offsetof(BirthdayGuest, draw) == 0xa44, "draw");
static_assert(offsetof(BirthdayGuest, act_wait) == 0xa4c, "act wait");
static_assert(offsetof(BirthdayGuest, face_wait) == 0xa4e, "face wait");
static_assert(offsetof(BirthdayGuest, turn_yaw) == 0xa50, "turn yaw");
static_assert(offsetof(BirthdayGuest, wander_wait) == 0xa52, "wander wait");
static_assert(offsetof(BirthdayGuest, walk_point) == 0xa54, "walk point");
static_assert(offsetof(BirthdayGuest, goal) == 0xa60, "goal");
static_assert(sizeof(BirthdayGuest) == 0xa6c, "the size func_ov004_0221e2cc allocates");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define BIRTHDAY_GUEST_POSITION 0x5c /* Vec3 */
#define BIRTHDAY_GUEST_YAW 0x8e      /* s16 */
#define BIRTHDAY_GUEST_MOVER 0x350   /* SceneMover */
#define BIRTHDAY_GUEST_LOOK 0x3b0    /* SceneLook */
#define BIRTHDAY_GUEST_BYTE_508 0x508
#define BIRTHDAY_GUEST_PARTICIPANT 0x560 /* u8: the event's participant */
#define BIRTHDAY_GUEST_MOTION 0x564      /* SceneMotion */
#define BIRTHDAY_GUEST_ACTION 0x618      /* SceneAction */
#define BIRTHDAY_GUEST_RECORD 0x830      /* u8 *: its town record (town_villager.h) */
#define BIRTHDAY_GUEST_SOUND_PLAYED 0x897

/* The field actor of this console's player. */
#define BIRTHDAY_GUEST_PLAYER_ACTOR 4

/* The kinds of motion asked for here (scene_motion_request.h). */
#define BIRTHDAY_GUEST_MOTION_STAND 0
#define BIRTHDAY_GUEST_MOTION_WALK 1
#define BIRTHDAY_GUEST_MOTION_TURN 3

/* The acts of states 2 and 3 (SceneMotion_RequestAct). */
#define BIRTHDAY_GUEST_ACT_NONE 0
#define BIRTHDAY_GUEST_ACT_3 3
#define BIRTHDAY_GUEST_ACT_26 0x1a

/* The look kinds (SceneLook_Request): ahead, and at an object. */
#define BIRTHDAY_GUEST_LOOK_AHEAD 1
#define BIRTHDAY_GUEST_LOOK_AT_OBJECT 2

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The distance it takes as "far" when there is no birthday villager (an acre's width). */
extern fx32 data_020ca0ec;
/* The town's villagers. */
extern VillagerTown data_021e5a2c;
/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov004_02253868[];
extern const u8 data_ov004_022537d8[];
/* The tables of its states' update and entry functions (filled once from the constants below,
 * bit 0 of the guards saying they were). */
extern u32 data_ov004_02257bd0;
extern MemberPointer data_ov004_02257c40[BIRTHDAY_GUEST_STATES];
extern u32 data_ov004_02257bdc;
extern MemberPointer data_ov004_02257c08[BIRTHDAY_GUEST_STATES];
extern const MemberPointer data_ov004_02253750, data_ov004_02253790, data_ov004_02253788, data_ov004_022537b0,
    data_ov004_02253740, data_ov004_02253748, data_ov004_02253770;
extern const MemberPointer data_ov004_02253768, data_ov004_02253778, data_ov004_02253780, data_ov004_022537a0,
    data_ov004_022537a8, data_ov004_02253760, data_ov004_02253758;
/* The name of its lines' message file ("ev_nbirth" for its villager), and the text it is
 * written in. */
extern const char data_ov004_02253928[];
extern char data_ov004_02257be0[0x28];

/* A point of the room to walk to (into `goal`) from `from`, and the direction to it. */
extern int func_ov004_0221e1e0(Vec3 *goal, Vec3 *from, int yaw);

static u8 *bg_part(BirthdayGuest *guest, u32 offset)
{
    return guest->base + offset;
}

static Vec3 *bg_position_of(u8 *object)
{
    return (Vec3 *) (void *) (object + BIRTHDAY_GUEST_POSITION);
}

static s16 bg_yaw_of(u8 *object)
{
    return *(s16 *) (void *) (object + BIRTHDAY_GUEST_YAW);
}

static SceneMover *bg_mover_of(BirthdayGuest *guest)
{
    return (SceneMover *) (void *) bg_part(guest, BIRTHDAY_GUEST_MOVER);
}

static SceneLook *bg_look_of(BirthdayGuest *guest)
{
    return (SceneLook *) (void *) bg_part(guest, BIRTHDAY_GUEST_LOOK);
}

static SceneMotion *bg_motion_of(BirthdayGuest *guest)
{
    return (SceneMotion *) (void *) bg_part(guest, BIRTHDAY_GUEST_MOTION);
}

static SceneAction *bg_action_of(BirthdayGuest *guest)
{
    return (SceneAction *) (void *) bg_part(guest, BIRTHDAY_GUEST_ACTION);
}

static u8 *bg_record_of(u8 *object)
{
    return *(u8 **) (void *) (object + BIRTHDAY_GUEST_RECORD);
}

static SceneBase *bg_scene_of(BirthdayGuestTalk *talk)
{
    return (SceneBase *) (void *) talk;
}

static void bg_set_vtables(BirthdayGuest *guest)
{
    *(const u8 **) (void *) guest->base = data_ov004_02253868;
    guest->talk.base.scene.vtable = data_ov004_022537d8;
}

/* func_ov004_0221d540 (the talk scene's vtable slot 0x04, its deleting destructor). */
BirthdayGuestTalk *BirthdayGuestTalk_Delete(BirthdayGuestTalk *talk)
{
    talk->base.scene.vtable = data_ov004_022537d8;
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_0221d540, BirthdayGuestTalk_Delete)

/* func_ov004_0221d560 (vtable slot 0x40): the destructor, without freeing: its talk scene, then
 * the town villager scene object. */
BirthdayGuest *BirthdayGuest_Destroy(BirthdayGuest *guest)
{
    bg_set_vtables(guest);
    VillagerTalkScene_DestructBody(&guest->talk.base);
    VillagerSceneObject_DestructBody(guest->base);
    return guest;
}
CLEAN_AS(func_ov004_0221d560, BirthdayGuest_Destroy)

/* func_ov004_0221d590 (vtable slot 0x44, the deleting destructor). */
BirthdayGuest *BirthdayGuest_Delete(BirthdayGuest *guest)
{
    bg_set_vtables(guest);
    VillagerTalkScene_DestructBody(&guest->talk.base);
    VillagerSceneObject_DestructBody(guest->base);
    Heap_FreeAux(guest);
    return guest;
}
CLEAN_AS(func_ov004_0221d590, BirthdayGuest_Delete)

/* func_ov004_0221d5c4 (the talk scene's vtable slot 0x00, its destructor). */
BirthdayGuestTalk *BirthdayGuestTalk_Destroy(BirthdayGuestTalk *talk)
{
    talk->base.scene.vtable = data_ov004_022537d8;
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov004_0221d5c4, BirthdayGuestTalk_Destroy)

/* func_ov004_0221d5dc (vtable slot 0x7c): its action sound is played only until it was once. */
int BirthdayGuest_HasActionSound(BirthdayGuest *guest)
{
    return *bg_part(guest, BIRTHDAY_GUEST_SOUND_PLAYED) == 0;
}
CLEAN_AS(func_ov004_0221d5dc, BirthdayGuest_HasActionSound)

/* func_ov004_0221d5f0 (vtable slot 0x80): notes its action sound was played. */
BirthdayGuest *BirthdayGuest_ActionSoundPlayed(BirthdayGuest *guest)
{
    *bg_part(guest, BIRTHDAY_GUEST_SOUND_PLAYED) = 1;
    return guest;
}
CLEAN_AS(func_ov004_0221d5f0, BirthdayGuest_ActionSoundPlayed)

/* func_ov004_0221d5fc: state 6's update: once the talk has closed, the event ends. */
void BirthdayGuest_UpdateTalk(BirthdayGuest *guest)
{
    TalkObject *talk = (TalkObject *) (void *) guest->talk.base.scene.talk;
    if (talk != NULL && talk->state == TALK_OBJECT_CLOSED) {
        EventQueue_FinishObjectEvent(guest);
    }
}
CLEAN_AS(func_ov004_0221d5fc, BirthdayGuest_UpdateTalk)

/* func_ov004_0221d61c: entering state 6 always succeeds. */
int BirthdayGuest_EnterTalk(BirthdayGuest *guest)
{
    (void) guest;
    return 1;
}
CLEAN_AS(func_ov004_0221d61c, BirthdayGuest_EnterTalk)

/* func_ov004_0221d620: state 5's update: on to state 6. */
void BirthdayGuest_UpdateTurn(BirthdayGuest *guest)
{
    BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_TALK);
}
CLEAN_AS(func_ov004_0221d620, BirthdayGuest_UpdateTurn)

/* func_ov004_0221d62c: entering state 5: it turns to this console's player's field actor and
 * talks; fails when there is no such actor. */
int BirthdayGuest_EnterTurn(BirthdayGuest *guest)
{
    void *player = SessionPlayers_ActorOf(BIRTHDAY_GUEST_PLAYER_ACTOR);
    if (player != NULL) {
        SceneAction_RequestTurnAndTalk(bg_action_of(guest), 0, SceneObject_YawTo(guest->base, player), 0);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221d62c, BirthdayGuest_EnterTurn)

/* func_ov004_0221d660: state 4's update does nothing. */
void BirthdayGuest_UpdateHalt(BirthdayGuest *guest)
{
    (void) guest;
}
CLEAN_AS(func_ov004_0221d660, BirthdayGuest_UpdateHalt)

/* func_ov004_0221d664: entering state 4 (always succeeds): from states 1 to 3 the act is ended
 * (act 0, priority 2). */
int BirthdayGuest_EnterHalt(BirthdayGuest *guest)
{
    if (guest->state == BIRTHDAY_GUEST_FACE || guest->state == BIRTHDAY_GUEST_ACT_SHORT ||
        guest->state == BIRTHDAY_GUEST_ACT_LONG) {
        SceneMotion_RequestAct(bg_motion_of(guest), 2, BIRTHDAY_GUEST_ACT_NONE, data_020c80f8);
    }
    return 1;
}
CLEAN_AS(func_ov004_0221d664, BirthdayGuest_EnterHalt)

/* The update of states 2 and 3: the countdown runs down (not below 0); at 1 frame left act 0,
 * at 0 back to state 0. */
static void bg_count_down_act(BirthdayGuest *guest)
{
    if (guest->act_wait != 0) {
        guest->act_wait--;
    }
    if (guest->act_wait == 0) {
        BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_WANDER);
    } else if (guest->act_wait == 1) {
        SceneMotion_RequestAct(bg_motion_of(guest), 1, BIRTHDAY_GUEST_ACT_NONE, data_020c80f8);
    }
}

/* func_ov004_0221d698: state 3's update (bg_count_down_act). */
void BirthdayGuest_UpdateActLong(BirthdayGuest *guest)
{
    bg_count_down_act(guest);
}
CLEAN_AS(func_ov004_0221d698, BirthdayGuest_UpdateActLong)

/* Whether the room's birthday villager (read from data_ov004_02257a18) wanders or faces (its
 * states 0 and 1) and enters `state`. */
static int bg_birthday_villager_enters(int state)
{
    BirthdayVillager *villager = data_ov004_02257a18;
    if (villager != NULL && (u32) villager->state <= BIRTHDAY_VILLAGER_FACE) {
        return BirthdayVillager_SetState(villager, state);
    }
    return 0;
}

/* func_ov004_0221d6e0: entering state 3: the birthday villager enters its state 3, then it
 * shows act 0x1a (priority 1) for 50 frames; fails when either cannot. */
int BirthdayGuest_EnterActLong(BirthdayGuest *guest)
{
    if (bg_birthday_villager_enters(BIRTHDAY_VILLAGER_ACT_LONG) &&
        SceneMotion_RequestAct(bg_motion_of(guest), 1, BIRTHDAY_GUEST_ACT_26, data_020c80f8) != 0) {
        guest->act_wait = 50;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221d6e0, BirthdayGuest_EnterActLong)

/* func_ov004_0221d73c: state 2's update (bg_count_down_act). */
void BirthdayGuest_UpdateActShort(BirthdayGuest *guest)
{
    bg_count_down_act(guest);
}
CLEAN_AS(func_ov004_0221d73c, BirthdayGuest_UpdateActShort)

/* func_ov004_0221d784: entering state 2: the birthday villager enters its state 2, then it
 * shows act 3 (priority 1) for 30 frames; fails when either cannot. */
int BirthdayGuest_EnterActShort(BirthdayGuest *guest)
{
    if (bg_birthday_villager_enters(BIRTHDAY_VILLAGER_ACT_SHORT) &&
        SceneMotion_RequestAct(bg_motion_of(guest), 1, BIRTHDAY_GUEST_ACT_3, data_020c80f8) != 0) {
        guest->act_wait = 30;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221d784, BirthdayGuest_EnterActShort)

/* How far off facing each other the two may be, and the frames before it faces the birthday
 * villager again after an act. */
#define BIRTHDAY_GUEST_FACING_ANGLE 0x500
#define BIRTHDAY_GUEST_FACE_WAIT 300
/* Half a turn. */
#define BIRTHDAY_GUEST_HALF_TURN 0x8000

/* func_ov004_0221d7e0: state 1's update: once it faces its direction and the birthday villager
 * faces the opposite one (each within 0x500), state 3 or 2 (at random); when that is entered,
 * it waits 300 frames before facing it again. */
void BirthdayGuest_UpdateFace(BirthdayGuest *guest)
{
    s16 yaw = guest->turn_yaw;
    s16 opposite = (s16) (yaw + BIRTHDAY_GUEST_HALF_TURN);
    BirthdayVillager *villager = BirthdayVillager_Current();
    if (villager == NULL) {
        return;
    }
    int off = Math_AbsDiff16(yaw, bg_yaw_of(guest->base));
    int other_off = Math_AbsDiff16(opposite, bg_yaw_of(villager->base));
    if (off > BIRTHDAY_GUEST_FACING_ANGLE || other_off > BIRTHDAY_GUEST_FACING_ANGLE) {
        return;
    }
    if (MainRandom_Below(2) != 0) {
        if (BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_ACT_LONG) != 0) {
            guest->face_wait = BIRTHDAY_GUEST_FACE_WAIT;
        }
    } else if (BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_ACT_SHORT) != 0) {
        guest->face_wait = BIRTHDAY_GUEST_FACE_WAIT;
    }
}
CLEAN_AS(func_ov004_0221d7e0, BirthdayGuest_UpdateFace)

/* func_ov004_0221d868: entering state 1, once the wait to face again is over and there is a
 * birthday villager: its direction to the birthday villager is kept; when the birthday
 * villager enters its state 1 (it wanders or faces), it turns to that direction and looks at
 * the birthday villager. Fails otherwise. */
int BirthdayGuest_EnterFace(BirthdayGuest *guest)
{
    if (guest->face_wait != 0) {
        return 0;
    }
    BirthdayVillager *villager = BirthdayVillager_Current();
    if (villager == NULL) {
        return 0;
    }
    const Vec3 *at = bg_position_of(villager->base);
    const Vec3 *from = bg_position_of(guest->base);
    guest->turn_yaw = Math_Atan2(at->x - from->x, at->z - from->z);
    if (!bg_birthday_villager_enters(BIRTHDAY_VILLAGER_FACE)) {
        return 0;
    }
    SceneMotion_Request(bg_motion_of(guest), BIRTHDAY_GUEST_MOTION_TURN, 1, 0, 0, 0, guest->turn_yaw, 0, 0, data_020c80f8, 0);
    SceneLook_Request(bg_look_of(guest), BIRTHDAY_GUEST_LOOK_AT_OBJECT, 0, (int) (uintptr_t) villager, &data_021fbee8,
                      BIRTHDAY_GUEST_PLAYER_ACTOR, data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov004_0221d868, BirthdayGuest_EnterFace)

/* Within this distance of the birthday villager it faces it; from this one on it may walk to
 * it. */
#define BIRTHDAY_GUEST_NEAR_DISTANCE 0x3334
#define BIRTHDAY_GUEST_FAR_DISTANCE 0x6000
/* How far off its direction the birthday villager must be before it turns to it first. */
#define BIRTHDAY_GUEST_TURN_ANGLE 0x2000
/* Waits after a turn and after a walk: 20 frames plus up to 69 or 79 more. */
#define BIRTHDAY_GUEST_WAIT_BASE 20
#define BIRTHDAY_GUEST_TURN_WAIT_RANGE 70
#define BIRTHDAY_GUEST_WALK_WAIT_RANGE 80
/* How close to its goal it stops when nothing is left to step around. */
#define BIRTHDAY_GUEST_GOAL_DISTANCE 0x200

/* func_ov004_0221d92c: state 0's update: its walk about the room.
 * - The distance to the birthday villager is measured (data_020ca0ec without one) and the wait
 *   to face it again runs down.
 * - While byte 0x508 of the object is set, a walk is turned into a stand (when that can be
 *   asked for, nothing more this frame).
 * - Within 0x3334 of the birthday villager it faces it (state 1) when it can.
 * - Standing: the wait runs down; at 0 it picks a goal (func_ov004_0221e1e0); from 0x6000 away
 *   from the birthday villager, one time in two the goal is the birthday villager's position
 *   instead, and its direction becomes the direction to it when that is 0x2000 or more off its
 *   own. When the direction is not its own it turns (then waits 20 to 89 frames), else walks to
 *   the goal (then waits 20 to 99 frames); a motion that cannot be asked for leaves the wait at
 *   0, to try again. Before that, a finished motion turns into a stand.
 * - Turning: once done, it walks to the goal.
 * - Walking: when blocked, it stands; when it can step aside, the mover heads for that point;
 *   else the mover heads for the goal again when it was elsewhere, or it stands once within
 *   0x200 of the goal. */
void BirthdayGuest_UpdateWander(BirthdayGuest *guest)
{
    SceneMotion *motion = bg_motion_of(guest);
    Vec3 *position = bg_position_of(guest->base);
    BirthdayVillager *villager = BirthdayVillager_Current();
    fx32 distance;

    if (villager != NULL) {
        distance = Vec_DistanceXZ(bg_position_of(villager->base), position);
    } else {
        distance = data_020ca0ec;
    }
    if (guest->face_wait != 0) {
        guest->face_wait--;
    }
    if (*bg_part(guest, BIRTHDAY_GUEST_BYTE_508) != 0 && SceneMotion_Kind(motion) == BIRTHDAY_GUEST_MOTION_WALK &&
        SceneMotion_RequestStand(motion, 1, data_020c80f8) != 0) {
        return;
    }
    if (distance < BIRTHDAY_GUEST_NEAR_DISTANCE && BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_FACE) != 0) {
        return;
    }

    if (SceneMotion_Kind(motion) == BIRTHDAY_GUEST_MOTION_STAND) {
        if (guest->wander_wait != 0) {
            guest->wander_wait--;
        }
        if (guest->wander_wait != 0) {
            if (SceneMotion_IsDone(motion)) {
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
            }
            return;
        }
        guest->turn_yaw = (s16) func_ov004_0221e1e0(&guest->goal, position, bg_yaw_of(guest->base));
        guest->walk_point = guest->goal;
        if (villager != NULL && distance >= BIRTHDAY_GUEST_FAR_DISTANCE && MainRandom_Below(2) == 0) {
            const Vec3 *at = bg_position_of(villager->base);
            s16 yaw = Math_Atan2(at->x - position->x, at->z - position->z);
            int off = Math_AbsDiff16(bg_yaw_of(guest->base), yaw);
            guest->goal.x = at->x;
            guest->goal.y = at->y;
            guest->goal.z = at->z;
            guest->walk_point = guest->goal;
            if (off >= BIRTHDAY_GUEST_TURN_ANGLE) {
                guest->turn_yaw = yaw;
            }
        }
        if (guest->turn_yaw != bg_yaw_of(guest->base)) {
            if (SceneMotion_Request(motion, BIRTHDAY_GUEST_MOTION_TURN, 1, 0, 0, 0, guest->turn_yaw, 0, 0, data_020c80f8, 0)) {
                guest->wander_wait = (u16) (MainRandom_Below(BIRTHDAY_GUEST_TURN_WAIT_RANGE) + BIRTHDAY_GUEST_WAIT_BASE);
            }
        } else if (SceneMotion_Request(motion, BIRTHDAY_GUEST_MOTION_WALK, 1, guest->goal.x, guest->goal.z, 0, 0, 0, 0,
                                       data_020c80f8, 0)) {
            guest->wander_wait = (u16) (MainRandom_Below(BIRTHDAY_GUEST_WALK_WAIT_RANGE) + BIRTHDAY_GUEST_WAIT_BASE);
        }
    } else if (SceneMotion_Kind(motion) == BIRTHDAY_GUEST_MOTION_TURN) {
        if (SceneMotion_IsDone(motion)) {
            SceneMotion_Request(motion, BIRTHDAY_GUEST_MOTION_WALK, 1, guest->goal.x, guest->goal.z, 0, 0, 0, 0, data_020c80f8,
                                0);
        }
    } else if (SceneMotion_Kind(motion) == BIRTHDAY_GUEST_MOTION_WALK) {
        Vec3 side;
        switch (SceneObject_SideStep(guest->base, &side)) {
            case SCENE_OBJECT_BLOCKED:
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
                break;
            case SCENE_OBJECT_SIDE_POINT:
                guest->walk_point = side;
                SceneMover_SetStart(bg_mover_of(guest), &guest->walk_point);
                break;
            default:
                if (Vec_Differ(&guest->walk_point, &guest->goal)) {
                    guest->walk_point = guest->goal;
                    SceneMover_SetStart(bg_mover_of(guest), &guest->goal);
                } else if (Vec_DistanceXZ(&guest->goal, position) < BIRTHDAY_GUEST_GOAL_DISTANCE) {
                    SceneMotion_RequestStand(motion, 1, data_020c80f8);
                }
                break;
        }
    }
}
CLEAN_AS(func_ov004_0221d92c, BirthdayGuest_UpdateWander)

/* func_ov004_0221dc18: entering state 0: it stands and looks ahead; fails when the stand cannot
 * be asked for. */
int BirthdayGuest_EnterWander(BirthdayGuest *guest)
{
    if (SceneMotion_RequestStand(bg_motion_of(guest), 1, data_020c80f8)) {
        SceneLook_Request(bg_look_of(guest), BIRTHDAY_GUEST_LOOK_AHEAD, 0, 0, &data_021fbee8, BIRTHDAY_GUEST_PLAYER_ACTOR,
                          data_020c814c, 1);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221dc18, BirthdayGuest_EnterWander)

/* _ZN18Obj_ov004_0225386819func_ov004_0221dc70Ev: the update of the current state, through its
 * table (filled once). */
void BirthdayGuest_Update(BirthdayGuest *guest)
{
    static const MemberPointer *const updates[BIRTHDAY_GUEST_STATES] = {
        &data_ov004_02253750, /* BirthdayGuest_UpdateWander */
        &data_ov004_02253790, /* BirthdayGuest_UpdateFace */
        &data_ov004_02253788, /* BirthdayGuest_UpdateActShort */
        &data_ov004_022537b0, /* BirthdayGuest_UpdateActLong */
        &data_ov004_02253740, /* BirthdayGuest_UpdateHalt */
        &data_ov004_02253748, /* BirthdayGuest_UpdateTurn */
        &data_ov004_02253770, /* BirthdayGuest_UpdateTalk */
    };
    MemberTable_InitOnce(&data_ov004_02257bd0, data_ov004_02257c40, updates, BIRTHDAY_GUEST_STATES);
    /* REQUIRES: state >= 0; the ROM's signed test lets a negative one index before the table */
    if (guest->state >= 0 && guest->state < BIRTHDAY_GUEST_STATES) {
        MemberPointer_CallVoid(&data_ov004_02257c40[guest->state], guest);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225386819func_ov004_0221dc70Ev, BirthdayGuest_Update)

/* func_ov004_0221dd24: enters `state` if its entry function (through a table, filled once)
 * agrees; whether it did. States 7 and above do not exist. */
int BirthdayGuest_SetState(BirthdayGuest *guest, int state)
{
    static const MemberPointer *const entries[BIRTHDAY_GUEST_STATES] = {
        &data_ov004_02253768, /* BirthdayGuest_EnterWander */
        &data_ov004_02253778, /* BirthdayGuest_EnterFace */
        &data_ov004_02253780, /* BirthdayGuest_EnterActShort */
        &data_ov004_022537a0, /* BirthdayGuest_EnterActLong */
        &data_ov004_022537a8, /* BirthdayGuest_EnterHalt */
        &data_ov004_02253760, /* BirthdayGuest_EnterTurn */
        &data_ov004_02253758, /* BirthdayGuest_EnterTalk */
    };
    MemberTable_InitOnce(&data_ov004_02257bdc, data_ov004_02257c08, entries, BIRTHDAY_GUEST_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 6); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < BIRTHDAY_GUEST_STATES && MemberPointer_CallInt(&data_ov004_02257c08[state], guest) != 0) {
        guest->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221dd24, BirthdayGuest_SetState)

/* func_ov004_0221dde8 (the talk scene's receiver slot 0x18, the player's answer): nothing. */
void BirthdayGuestTalk_OnAnswer(void) {}
CLEAN_AS(func_ov004_0221dde8, BirthdayGuestTalk_OnAnswer)

/* func_ov004_0221ddec (the talk scene's receiver slot 0x14, a message ended): nothing. */
void BirthdayGuestTalk_OnMessageEnded(void) {}
CLEAN_AS(func_ov004_0221ddec, BirthdayGuestTalk_OnMessageEnded)

/* func_ov004_0221ddf0 (the talk scene's receiver slot 0x10, a message begins): nothing. */
void BirthdayGuestTalk_OnMessageBegun(void) {}
CLEAN_AS(func_ov004_0221ddf0, BirthdayGuestTalk_OnMessageBegun)

/* The size of the text the lines' message file name is written in. */
#define BIRTHDAY_GUEST_FILE_NAME_SIZE 0x28

/* func_ov004_0221ddf4 (the talk scene's vtable slot 0x78, the line to say): the message file is
 * the villager's "ev_nbirth" one (written into data_ov004_02257be0). The message is, by its
 * memory of the player, 0x1a or 0x1b when bit 6 is clear (the first time), else 0x1e to 0x21
 * when bit 7 of the birthday villager's memory of the player is set, else 0x1c or 0x1d; bit 6
 * is then set. When its talk scene has a talk, the name of the villager of the current scene's
 * house (its index among the scenes of group 11, when the town has a villager there) becomes
 * its part 1 and its own name its part 0.
 * QUIRK: a player id text is built and destroyed around the house villager's name, unused. */
void BirthdayGuestTalk_Line(BirthdayGuestTalk *talk, VillagerTalkLine *out)
{
    NpcId_FormatResourceName(TownVillager_NpcId(bg_record_of(talk->guest->base)), data_ov004_02257be0,
                             BIRTHDAY_GUEST_FILE_NAME_SIZE, data_ov004_02253928);
    out->text = (u32) (uintptr_t) data_ov004_02257be0;

    int first_time = BirthdayGuestTalk_MemoryBit6Clear(talk);
    int marked = !first_time && BirthdayVillager_CurrentMemoryBit7();
    BirthdayGuestTalk_SetMemoryBit6(talk);
    if (first_time) {
        out->message = (u8) (MainRandom_Below(2) + 0x1a);
    } else if (marked) {
        out->message = (u8) (MainRandom_Below(4) + 0x1e);
    } else {
        out->message = (u8) (MainRandom_Below(2) + 0x1c);
    }

    if (talk->guest->talk.base.scene.talk == NULL) {
        return;
    }
    int house = SceneQuery_CurrentIndexIn11();
    if (VillagerRoster_IsFilled(&data_021e5a2c, house) != 0) {
        PlayerIdText unused;
        PlayerIdText_Construct(&unused);
        SceneBase_PutNpcName(bg_scene_of(&talk->guest->talk), TownVillager_NpcId(VillagerRoster_At(&data_021e5a2c, house)), 1);
        PlayerIdText_Destruct(&unused);
    }
    if (talk->guest != NULL && bg_record_of(talk->guest->base) != NULL) {
        SceneBase_PutNpcName(bg_scene_of(&talk->guest->talk), TownVillager_NpcId(bg_record_of(talk->guest->base)), 0);
    }
}
CLEAN_AS(func_ov004_0221ddf4, BirthdayGuestTalk_Line)

/* The lines table VillagerTalkScene_Start is given: 17 and above leave the line members as they
 * are (the talk scene's own vtable slot 0x78 says the line). */
#define BIRTHDAY_GUEST_TALK_OWN_LINES 0x11

/* func_ov004_0221defc: its talk scene started for `guest`, and kept pointing back at it. */
void BirthdayGuestTalk_Start(BirthdayGuestTalk *talk, BirthdayGuest *guest)
{
    VillagerTalkScene_Start(&talk->base, guest->base, BIRTHDAY_GUEST_TALK_OWN_LINES);
    talk->guest = guest;
}
CLEAN_AS(func_ov004_0221defc, BirthdayGuestTalk_Start)

/* func_ov004_0221df1c: bit 6 of its memory of the player set (none without one). */
void BirthdayGuestTalk_SetMemoryBit6(BirthdayGuestTalk *talk)
{
    VillagerMemory *memory = BirthdayGuestTalk_PlayerMemory(talk);
    if (memory != NULL) {
        VillagerMemoryEntry_SetBit6(memory);
    }
}
CLEAN_AS(func_ov004_0221df1c, BirthdayGuestTalk_SetMemoryBit6)

/* func_ov004_0221df34: whether bit 6 of its memory of the player is clear; 0 without a
 * memory. */
int BirthdayGuestTalk_MemoryBit6Clear(BirthdayGuestTalk *talk)
{
    VillagerMemory *memory = BirthdayGuestTalk_PlayerMemory(talk);
    if (memory != NULL) {
        return VillagerMemoryEntry_Bit6(memory) == 0;
    }
    return 0;
}
CLEAN_AS(func_ov004_0221df34, BirthdayGuestTalk_MemoryBit6Clear)

/* func_ov004_0221df58: its memory of the current player (VillagerMemory_Meet); NULL for a talk
 * scene without a villager or a villager without a record. */
VillagerMemory *BirthdayGuestTalk_PlayerMemory(BirthdayGuestTalk *talk)
{
    if (talk->guest != NULL && bg_record_of(talk->guest->base) != NULL) {
        return VillagerMemory_Meet(bg_record_of(talk->guest->base), PlayerRecord_Player(PlayerRecords_Current()));
    }
    return NULL;
}
CLEAN_AS(func_ov004_0221df58, BirthdayGuestTalk_PlayerMemory)

/* How far above its position the camera looks at it in a talk. */
#define BIRTHDAY_GUEST_FOCUS_HEIGHT 0x2000

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define BIRTHDAY_GUEST_EVENT_TALK 0
#define BIRTHDAY_GUEST_EVENT_STARTS 3
#define BIRTHDAY_GUEST_EVENT_REFUSED 4
#define BIRTHDAY_GUEST_EVENT_ENDED 8

/* func_ov004_0221df94 (vtable slot 0x4c, told of an event):
 * - 3, an event starts: the participant kept, state 4;
 * - 0, the player talks to it: the participant kept, the camera looks at a point 0x2000 above
 *   it, state 5;
 * - 8, the event ended: its memory of the player updated, the camera's mode reset, state 0;
 * - 4, refused: state 0. */
void BirthdayGuest_OnEvent(BirthdayGuest *guest, unsigned int code, int participant)
{
    Vec3 focus = *bg_position_of(guest->base);
    focus.y += BIRTHDAY_GUEST_FOCUS_HEIGHT;

    switch (code) {
        case BIRTHDAY_GUEST_EVENT_STARTS:
            *bg_part(guest, BIRTHDAY_GUEST_PARTICIPANT) = (u8) participant;
            BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_HALT);
            break;
        case BIRTHDAY_GUEST_EVENT_TALK:
            *bg_part(guest, BIRTHDAY_GUEST_PARTICIPANT) = (u8) participant;
            CameraControl_FocusOn(&focus);
            BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_TURN);
            break;
        case BIRTHDAY_GUEST_EVENT_ENDED:
            BirthdayGuest_UpdatePlayerMemory(guest);
            CameraControl_ResetMode();
            BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_WANDER);
            break;
        case BIRTHDAY_GUEST_EVENT_REFUSED:
            BirthdayGuest_SetState(guest, BIRTHDAY_GUEST_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0221df94, BirthdayGuest_OnEvent)

/* func_ov004_0221e018 (vtable slot 0x48): whether the player may talk to it: its action idle and
 * it wanders, faces or acts (states 0 to 3). */
int BirthdayGuest_MayAct(BirthdayGuest *guest)
{
    if (SceneAction_IsBusy(bg_action_of(guest))) {
        return 0;
    }
    return guest->state <= BIRTHDAY_GUEST_ACT_LONG;
}
CLEAN_AS(func_ov004_0221e018, BirthdayGuest_MayAct)

/* func_ov004_0221e048: its memory of the current player updated (VillagerMemoryEntry_Update with
 * no player, town or date); nothing without a current player or a record. */
void BirthdayGuest_UpdatePlayerMemory(BirthdayGuest *guest)
{
    u8 *player = PlayerRecords_Current();
    if (player == NULL || bg_record_of(guest->base) == NULL) {
        return;
    }
    VillagerMemoryEntry_Update(VillagerMemory_Meet(bg_record_of(guest->base), PlayerRecord_Player(player)), NULL, NULL, NULL);
}
CLEAN_AS(func_ov004_0221e048, BirthdayGuest_UpdatePlayerMemory)
