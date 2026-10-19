/* The villager who visits the player's house at the time agreed (house_visitor.h). */
#include "house_visitor.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_record.h"
#include "main/block_020b220c.h"
#include "main/calendar.h"
#include "main/collision_map.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/footsteps.h"
#include "main/item_code.h"
#include "main/item_object.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/name_texts.h"
#include "main/npc_id.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/room_score.h"
#include "main/scene_action.h"
#include "main/scene_exit.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_place.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/session_players.h"
#include "main/sound.h"
#include "main/sound_emitter.h"
#include "main/talk_choices.h"
#include "main/talk_object.h"
#include "main/text_base.h"
#include "main/town_objects.h"
#include "main/town_villager.h"
#include "main/villager_memories.h"
#include "main/villager_memory_entry.h"
#include "main/villager_part_handover.h"
#include "main/villager_scene_slots.h"
#include "main/villager_state.h"
#include "main/villager_status.h"
#include "main/villager_talk.h"
#include "main/villager_talk_scene.h"
#include "ov004/birthday_guest.h"
#include "ov004/member_pointer.h"
#include "ov004/room_objects.h"

static_assert(sizeof(HouseVisitorTalk) == 0x1a8, "its talk scene");
static_assert(offsetof(HouseVisitor, state) == 0x898, "state");
static_assert(offsetof(HouseVisitor, talk) == 0x89c, "talk scene");
static_assert(offsetof(HouseVisitor, talk.base.scene.talk) == 0x8dc, "the talk scene's talk");
static_assert(offsetof(HouseVisitor, draw) == 0xa44, "draw");
static_assert(offsetof(HouseVisitor, rating) == 0xa4c, "rating");
static_assert(offsetof(HouseVisitor, enter_wait) == 0xa50, "enter wait");
static_assert(offsetof(HouseVisitor, walk_wait) == 0xa52, "walk wait");
static_assert(offsetof(HouseVisitor, advice) == 0xa54, "advice");
static_assert(offsetof(HouseVisitor, time_up) == 0xa58, "time up");
static_assert(offsetof(HouseVisitor, talk_kind) == 0xa5a, "talk kind");
static_assert(offsetof(HouseVisitor, talks_left) == 0xa5c, "talks left");
static_assert(offsetof(HouseVisitor, stay) == 0xa5e, "stay");
static_assert(offsetof(HouseVisitor, leave_wait) == 0xa60, "leave wait");
static_assert(offsetof(HouseVisitor, ring_wait) == 0xa61, "ring wait");
static_assert(offsetof(HouseVisitor, turn_yaw) == 0xa62, "turn yaw");
static_assert(offsetof(HouseVisitor, walk_point) == 0xa64, "walk point");
static_assert(offsetof(HouseVisitor, goal) == 0xa70, "goal");
static_assert(sizeof(HouseVisitor) == 0xa7c, "the size func_ov068_022766e8 allocates");
static_assert(sizeof(VillagerPartHandover) == 0x28, "the visit's record");

/* The parts of the town villager scene object used here, by place (main's scene_object.h). */
#define HOUSE_VISITOR_POSITION 0x5c     /* Vec3 */
#define HOUSE_VISITOR_YAW 0x8e          /* s16: the direction it faces */
#define HOUSE_VISITOR_WALK_ANGLE 0x94   /* s16 */
#define HOUSE_VISITOR_MOVER 0x350       /* SceneMover */
#define HOUSE_VISITOR_LOOK 0x3b0        /* SceneLook */
#define HOUSE_VISITOR_BYTE_508 0x508    /* u8: while set, a walk turns into a stand */
#define HOUSE_VISITOR_SOLID 0x510       /* u8: it collides and moves with its carrier */
#define HOUSE_VISITOR_EMITTER 0x514     /* SoundEmitter */
#define HOUSE_VISITOR_FOOTSTEPS 0x558   /* Footsteps */
#define HOUSE_VISITOR_PARTICIPANT 0x560 /* u8: the event's participant */
#define HOUSE_VISITOR_MOTION 0x564      /* SceneMotion */
#define HOUSE_VISITOR_ACTION 0x618      /* SceneAction */
#define HOUSE_VISITOR_RECORD 0x830      /* u8 *: its town record (town_villager.h) */
#define HOUSE_VISITOR_SOUND_PLAYED 0x897

/* Its vtable slot giving its town record (villager_scene_slots.h), called virtually. */
#define HOUSE_VISITOR_SLOT_RECORD 0x64

/* The field actor of this console's player, and where an actor's position is. */
#define HOUSE_VISITOR_PLAYER_ACTOR 4
#define HOUSE_VISITOR_ACTOR_POSITION 0x5c

/* The kinds of motion asked for here (scene_motion_request.h). */
#define HOUSE_VISITOR_MOTION_STAND 0
#define HOUSE_VISITOR_MOTION_WALK 1
#define HOUSE_VISITOR_MOTION_TURN 3

/* The look kind ahead (SceneLook_Request). */
#define HOUSE_VISITOR_LOOK_AHEAD 1

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* An acre's width and depth in world units, and half its width (the room is one acre). */
extern fx32 data_020ca0ec;
extern fx32 data_020ca0e8;
extern fx32 data_020ca0e4;
/* The town map: the room is its one acre (acre_map.h). */
extern AcreMap *data_021c80bc;
/* The message a talk closes on (main's villager_talk.h). */
extern u8 data_021f43e8;
/* Two tables of a town villager's three line members (VillagerTalkScene_SetLines). */
extern const MemberPointer data_021c1f04[3];
extern const MemberPointer data_021c1f34[3];
extern const MemberPointer __ptmf_null;

/* The vtables: the class's, and its talk scene's. */
extern const u8 data_ov068_02278140[];
extern const u8 data_ov068_022780b0[];
/* The room's visitor while there is one (set by its set-up, cleared once it may be deleted). */
extern HouseVisitor *data_ov068_022788ec;
/* The member pointers to HouseVisitor_Draw (two constants of the same value). */
extern const MemberPointer data_ov068_02277fdc;
extern const MemberPointer data_ov068_02278064;
/* The tables of its states' update and entry functions (filled once from the constants below,
 * bit 0 of the guards saying they were). */
extern u32 data_ov068_022788d4;
extern MemberPointer data_ov068_02278948[HOUSE_VISITOR_STATES];
extern u32 data_ov068_022788f4;
extern MemberPointer data_ov068_022789a0[HOUSE_VISITOR_STATES];
extern const MemberPointer data_ov068_0227806c, data_ov068_02278054, data_ov068_02277fbc, data_ov068_02277fc4,
    data_ov068_02277fe4, data_ov068_02277ff4, data_ov068_0227800c, data_ov068_02278044, data_ov068_02278074,
    data_ov068_0227805c, data_ov068_02277fec;
extern const MemberPointer data_ov068_0227804c, data_ov068_02277fd4, data_ov068_0227803c, data_ov068_02278034,
    data_ov068_0227802c, data_ov068_02277fcc, data_ov068_0227801c, data_ov068_02278014, data_ov068_02277ffc,
    data_ov068_02278004, data_ov068_02278024;
/* The texts its message file names are written in. */
#define HOUSE_VISITOR_FILE_NAME_SIZE 0x28
extern char data_ov068_02278920[HOUSE_VISITOR_FILE_NAME_SIZE];
extern char data_ov068_022788f8[HOUSE_VISITOR_FILE_NAME_SIZE];
/* The message files: "q_bye", "q10_call", "q10_back", "q10_wait", "q10_door", "q10_first",
 * "q10_furniture", "q10_layout". */
extern const char data_ov068_02278200[];
extern const char data_ov068_02278208[];
extern const char data_ov068_02278214[];
extern const char data_ov068_02278220[];
extern const char data_ov068_0227822c[];
extern const char data_ov068_02278238[];
extern const char data_ov068_02278244[];
extern const char data_ov068_02278254[];
/* The rating's text: ten of the rating mark (0x25). */
#define HOUSE_VISITOR_MARKS 10
extern const u16 data_ov068_0227807c[HOUSE_VISITOR_MARKS];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

static u8 *hv_part(HouseVisitor *visitor, u32 offset)
{
    return visitor->base + offset;
}

static Vec3 *hv_position(HouseVisitor *visitor)
{
    return (Vec3 *) (void *) hv_part(visitor, HOUSE_VISITOR_POSITION);
}

static s16 *hv_yaw(HouseVisitor *visitor)
{
    return (s16 *) (void *) hv_part(visitor, HOUSE_VISITOR_YAW);
}

static SceneMover *hv_mover(HouseVisitor *visitor)
{
    return (SceneMover *) (void *) hv_part(visitor, HOUSE_VISITOR_MOVER);
}

static SceneLook *hv_look(HouseVisitor *visitor)
{
    return (SceneLook *) (void *) hv_part(visitor, HOUSE_VISITOR_LOOK);
}

static SceneMotion *hv_motion(HouseVisitor *visitor)
{
    return (SceneMotion *) (void *) hv_part(visitor, HOUSE_VISITOR_MOTION);
}

static SceneAction *hv_action(HouseVisitor *visitor)
{
    return (SceneAction *) (void *) hv_part(visitor, HOUSE_VISITOR_ACTION);
}

static u8 *hv_record_field(HouseVisitor *visitor)
{
    return *(u8 **) (void *) hv_part(visitor, HOUSE_VISITOR_RECORD);
}

/* Its town record through its vtable slot 0x64 (VillagerSceneObject_Record), or null. */
static u8 *hv_record(HouseVisitor *visitor)
{
    u32 vtable = *(const u32 *) (const void *) visitor;
    u32 code = *(const u32 *) (uintptr_t) (vtable + HOUSE_VISITOR_SLOT_RECORD);
    return (u8 *) (uintptr_t) ((u32 (*)(HouseVisitor *))(uintptr_t) code)(visitor);
}

/* The talk its talk scene has, or null. */
static TalkObject *hv_talk(HouseVisitor *visitor)
{
    return (TalkObject *) (void *) visitor->talk.base.scene.talk;
}

/* The visit's record in this console's player's record (villager_part_handover.h). */
static VillagerPartHandover *hv_visit(void)
{
    return (VillagerPartHandover *) (void *) (PlayerRecord_VillagerPart(PlayerRecords_Current()) + 0xa4);
}

/* The object of the visit's record whose low five bits say how far it went. */
static ItemObject *hv_progress(void)
{
    return (ItemObject *) (void *) hv_visit()->object;
}

static void hv_set_vtables(HouseVisitor *visitor)
{
    *(const u8 **) (void *) visitor->base = data_ov068_02278140;
    visitor->talk.base.scene.vtable = data_ov068_022780b0;
}

/* ---- Construction and the vtable slots of its own */

/* func_ov068_02275228 (the talk scene's vtable slot 0x04, its deleting destructor). */
HouseVisitorTalk *HouseVisitorTalk_Delete(HouseVisitorTalk *talk)
{
    talk->base.scene.vtable = data_ov068_022780b0;
    VillagerTalkScene_DestructBody(&talk->base);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov068_02275228, HouseVisitorTalk_Delete)

/* func_ov068_02275248 (vtable slot 0x40): the destructor, without freeing: its talk scene, then
 * the town villager scene object. */
HouseVisitor *HouseVisitor_Destroy(HouseVisitor *visitor)
{
    hv_set_vtables(visitor);
    VillagerTalkScene_DestructBody(&visitor->talk.base);
    VillagerSceneObject_DestructBody(visitor->base);
    return visitor;
}
CLEAN_AS(func_ov068_02275248, HouseVisitor_Destroy)

/* func_ov068_02275278 (vtable slot 0x44, the deleting destructor). */
HouseVisitor *HouseVisitor_Delete(HouseVisitor *visitor)
{
    hv_set_vtables(visitor);
    VillagerTalkScene_DestructBody(&visitor->talk.base);
    VillagerSceneObject_DestructBody(visitor->base);
    Heap_FreeAux(visitor);
    return visitor;
}
CLEAN_AS(func_ov068_02275278, HouseVisitor_Delete)

/* func_ov068_022752ac (the talk scene's vtable slot 0x00, its destructor). */
HouseVisitorTalk *HouseVisitorTalk_Destroy(HouseVisitorTalk *talk)
{
    talk->base.scene.vtable = data_ov068_022780b0;
    VillagerTalkScene_DestructBody(&talk->base);
    return talk;
}
CLEAN_AS(func_ov068_022752ac, HouseVisitorTalk_Destroy)

/* func_ov068_022752c4 (vtable slot 0x7c): its action sound is played only until it was once. */
int HouseVisitor_HasActionSound(HouseVisitor *visitor)
{
    return *hv_part(visitor, HOUSE_VISITOR_SOUND_PLAYED) == 0;
}
CLEAN_AS(func_ov068_022752c4, HouseVisitor_HasActionSound)

/* func_ov068_022752d8 (vtable slot 0x80): notes its action sound was played. */
void HouseVisitor_ActionSoundPlayed(HouseVisitor *visitor)
{
    *hv_part(visitor, HOUSE_VISITOR_SOUND_PLAYED) = 1;
}
CLEAN_AS(func_ov068_022752d8, HouseVisitor_ActionSoundPlayed)

/* ---- The states */

/* The exits of the scene it takes when it leaves (SceneExit_Take): the plain one, and the one
 * after the player's place is saved. */
#define HOUSE_VISITOR_EXIT 0
#define HOUSE_VISITOR_EXIT_SAVED 6

/* func_ov068_022752e4: state 10's update: once the talk has closed, the extra visitors of the
 * town objects are cleared, its state entry settles (its town record asked for twice), the
 * visit is over and the scene's exit is taken: exit 6 after the player's place is saved when its
 * stay ran out, else exit 0. */
void HouseVisitor_UpdateLeave(HouseVisitor *visitor)
{
    TalkObject *talk = hv_talk(visitor);
    if (talk == NULL || talk->state != TALK_OBJECT_CLOSED) {
        return;
    }
    TownObjects_ClearExtraVisitors();
    if (hv_record(visitor) != NULL) {
        VillagerState_SettleState(VillagerStatus_StateEntry(hv_record(visitor)));
    }
    HouseVisitor_MarkOver();
    if (visitor->time_up != 0) {
        ScenePlace_SavePlayer(SceneTables_EntryRecord(), 0);
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), HOUSE_VISITOR_EXIT_SAVED);
    } else {
        SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), HOUSE_VISITOR_EXIT);
    }
}
CLEAN_AS(func_ov068_022752e4, HouseVisitor_UpdateLeave)

/* func_ov068_02275354: entering state 10 always succeeds. */
int HouseVisitor_EnterLeave(void)
{
    return 1;
}
CLEAN_AS(func_ov068_02275354, HouseVisitor_EnterLeave)

/* func_ov068_02275358: state 9's update: once the talk has closed, the event ends. */
void HouseVisitor_UpdateTalk(HouseVisitor *visitor)
{
    TalkObject *talk = hv_talk(visitor);
    if (talk != NULL && talk->state == TALK_OBJECT_CLOSED) {
        EventQueue_FinishObjectEvent(visitor);
    }
}
CLEAN_AS(func_ov068_02275358, HouseVisitor_UpdateTalk)

/* func_ov068_02275378: entering state 9 always succeeds. */
int HouseVisitor_EnterTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov068_02275378, HouseVisitor_EnterTalk)

/* func_ov068_0227537c: state 8's update: on to state 9. */
int HouseVisitor_UpdateTurn(HouseVisitor *visitor)
{
    return HouseVisitor_SetState(visitor, HOUSE_VISITOR_TALK);
}
CLEAN_AS(func_ov068_0227537c, HouseVisitor_UpdateTurn)

/* func_ov068_02275388: entering state 8: it turns to this console's player's field actor and
 * talks, keeping the camera when its stay ran out or the player is leaving; fails when there is
 * no such actor. */
int HouseVisitor_EnterTurn(HouseVisitor *visitor)
{
    void *player = SessionPlayers_ActorOf(HOUSE_VISITOR_PLAYER_ACTOR);
    if (player == NULL) {
        return 0;
    }
    int yaw = SceneObject_YawTo(visitor->base, player);
    int keep_camera = visitor->time_up != 0 || visitor->player_leaving != 0;
    SceneAction_RequestTurnAndTalk(hv_action(visitor), 0, yaw, keep_camera);
    return 1;
}
CLEAN_AS(func_ov068_02275388, HouseVisitor_EnterTurn)

/* func_ov068_022753e4: state 7's update does nothing. */
void HouseVisitor_UpdateHeld(void) {}
CLEAN_AS(func_ov068_022753e4, HouseVisitor_UpdateHeld)

/* func_ov068_022753e8: entering state 7 always succeeds. */
int HouseVisitor_EnterHeld(void)
{
    return 1;
}
CLEAN_AS(func_ov068_022753e8, HouseVisitor_EnterHeld)

/* The countdowns of states 5 and 6, while its action is idle: once its stay or its talks have
 * run out, the wait to leave runs down, and at 0 it asks for an event (kind 6) and its stay is
 * up; the stay runs down while it is above 0. Whether it asked. */
static int hv_count_down_stay(HouseVisitor *visitor)
{
    if (SceneAction_IsBusy(hv_action(visitor)) != 0) {
        return 0;
    }
    if (visitor->stay == 0 || visitor->talks_left == 0) {
        u8 wait = visitor->leave_wait;
        if (wait == 0) {
            EventQueue_RequestKind6(visitor, 0);
            visitor->time_up = 1;
            return 1;
        }
        visitor->leave_wait = (u8) (wait - 1);
    }
    if (visitor->stay > 0) {
        visitor->stay--;
    }
    return 0;
}

/* Whether the unit under where this console's player's actor was at the start of the frame is
 * the claimed one (the door), the position copied first. */
static int hv_player_at_door(const Vec3 *player)
{
    Vec3 at = *player;
    return CollisionMap_IsClaimedAtPoint(&at);
}

/* Closer than this to the player it stops walking (outside states 6). */
#define HOUSE_VISITOR_NEAR_PLAYER 0x2334
/* Waits after a turn and after a walk: 20 frames plus up to 69 or 79 more. */
#define HOUSE_VISITOR_WAIT_BASE 20
#define HOUSE_VISITOR_TURN_WAIT_RANGE 70
#define HOUSE_VISITOR_WALK_WAIT_RANGE 80
/* How close to its goal it stops when nothing is left to step around. */
#define HOUSE_VISITOR_GOAL_DISTANCE 0x200

/* func_ov068_022753ec: state 6's update: its walk about the room.
 * - In state 6, while its action is idle, the countdowns of its stay (hv_count_down_stay); when
 *   it asked for an event, nothing more.
 * - In state 6, when the player is at the door it asks for an event (kind 6) to stop them, and
 *   nothing more.
 * - The distance to the player is measured (data_020ca0ec without one). While byte 0x508 is set,
 *   or outside state 6 within 0x2334 of the player, a walk (or anything in state 3) turns into
 *   a stand at priority 2; when that could be asked for, the pace is set back and nothing more.
 * - Standing: the wait runs down; at 0 it picks a goal (BirthdayGuest_PickGoal) and turns when
 *   the direction is not its own (then waits 20 to 89 frames), else walks there (then waits 20
 *   to 99 frames); a motion that cannot be asked for leaves the wait at 0, to try again. Before
 *   that, a finished motion turns into a stand.
 * - Turning: once done, it walks to the goal.
 * - Walking: when blocked, it stands (and the pace is set back); when it can step aside, the
 *   mover heads for that point; else the mover heads for the goal again when it was elsewhere,
 *   or it stands (and the pace is set back) once within 0x200 of the goal. */
void HouseVisitor_UpdateWander(HouseVisitor *visitor)
{
    SceneMotion *motion = hv_motion(visitor);
    Vec3 *position = hv_position(visitor);
    Vec3 *player = PlayerActorOps_StartPosition(HOUSE_VISITOR_PLAYER_ACTOR);

    if (visitor->state == HOUSE_VISITOR_WANDER && hv_count_down_stay(visitor)) {
        return;
    }
    if (visitor->state == HOUSE_VISITOR_WANDER && player != NULL && hv_player_at_door(player)) {
        EventQueue_RequestKind6(visitor, 0);
        visitor->player_leaving = 1;
        return;
    }

    fx32 distance = data_020ca0ec;
    if (player != NULL) {
        distance = Vec_DistanceXZ(player, position);
    }
    if (*hv_part(visitor, HOUSE_VISITOR_BYTE_508) != 0 ||
        (visitor->state != HOUSE_VISITOR_WANDER && distance < HOUSE_VISITOR_NEAR_PLAYER)) {
        if ((SceneMotion_Kind(motion) == HOUSE_VISITOR_MOTION_WALK || visitor->state == HOUSE_VISITOR_ENTER) &&
            SceneMotion_RequestStand(motion, 2, data_020c80f8) != 0) {
            HouseVisitor_SlowPace(visitor);
            return;
        }
    }

    if (SceneMotion_Kind(motion) == HOUSE_VISITOR_MOTION_STAND) {
        if (visitor->walk_wait != 0) {
            visitor->walk_wait--;
        }
        if (visitor->walk_wait != 0) {
            if (SceneMotion_IsDone(motion) != 0) {
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
            }
            return;
        }
        visitor->turn_yaw = (s16) BirthdayGuest_PickGoal(&visitor->goal, position, *hv_yaw(visitor));
        visitor->walk_point = visitor->goal;
        s16 yaw = visitor->turn_yaw;
        if (yaw != *hv_yaw(visitor)) {
            if (SceneMotion_Request(motion, HOUSE_VISITOR_MOTION_TURN, 1, 0, 0, 0, yaw, 0, 0, data_020c80f8, 0) != 0) {
                visitor->walk_wait = (u16) (MainRandom_Below(HOUSE_VISITOR_TURN_WAIT_RANGE) + HOUSE_VISITOR_WAIT_BASE);
            }
            return;
        }
        if (SceneMotion_Request(motion, HOUSE_VISITOR_MOTION_WALK, 1, visitor->goal.x, visitor->goal.z, 0, 0, 0, 0,
                                data_020c80f8, 0) != 0) {
            visitor->walk_wait = (u16) (MainRandom_Below(HOUSE_VISITOR_WALK_WAIT_RANGE) + HOUSE_VISITOR_WAIT_BASE);
        }
        return;
    }

    if (SceneMotion_Kind(motion) == HOUSE_VISITOR_MOTION_TURN) {
        if (SceneMotion_IsDone(motion) != 0) {
            SceneMotion_Request(motion, HOUSE_VISITOR_MOTION_WALK, 1, visitor->goal.x, visitor->goal.z, 0, 0, 0, 0,
                                data_020c80f8, 0);
        }
        return;
    }

    if (SceneMotion_Kind(motion) != HOUSE_VISITOR_MOTION_WALK) {
        return;
    }
    Vec3 side;
    switch (SceneObject_SideStep(visitor->base, &side)) {
        case SCENE_OBJECT_BLOCKED:
            if (SceneMotion_RequestStand(motion, 1, data_020c80f8) != 0) {
                HouseVisitor_SlowPace(visitor);
            }
            break;
        case SCENE_OBJECT_SIDE_POINT:
            visitor->walk_point = side;
            SceneMover_SetStart(hv_mover(visitor), &visitor->walk_point);
            break;
        default:
            if (Vec_Differ(&visitor->walk_point, &visitor->goal) != 0) {
                visitor->walk_point = visitor->goal;
                SceneMover_SetStart(hv_mover(visitor), &visitor->goal);
            } else if (Vec_DistanceXZ(&visitor->goal, position) < HOUSE_VISITOR_GOAL_DISTANCE) {
                SceneMotion_RequestStand(motion, 1, data_020c80f8);
                HouseVisitor_SlowPace(visitor);
            }
            break;
    }
}
CLEAN_AS(func_ov068_022753ec, HouseVisitor_UpdateWander)

/* func_ov068_0227570c: entering state 6: when it can stand, it looks ahead and claims the map's
 * object 0 (the door); fails when the stand cannot be asked for. */
int HouseVisitor_EnterWander(HouseVisitor *visitor)
{
    if (SceneMotion_RequestStand(hv_motion(visitor), 1, data_020c80f8) == 0) {
        return 0;
    }
    SceneLook_Request(hv_look(visitor), HOUSE_VISITOR_LOOK_AHEAD, 0, 0, &data_021fbee8, HOUSE_VISITOR_PLAYER_ACTOR,
                      data_020c814c, 1);
    CollisionMap_Claim(0);
    return 1;
}
CLEAN_AS(func_ov068_0227570c, HouseVisitor_EnterWander)

/* func_ov068_0227576c: state 5's update: the countdowns of its stay (hv_count_down_stay), then,
 * when it did not ask for an event, the player at the door asks for one (kind 6) to stop them. */
void HouseVisitor_UpdateArrived(HouseVisitor *visitor)
{
    if (hv_count_down_stay(visitor)) {
        return;
    }
    Vec3 *player = PlayerActorOps_StartPosition(HOUSE_VISITOR_PLAYER_ACTOR);
    if (player != NULL && hv_player_at_door(player)) {
        EventQueue_RequestKind6(visitor, 0);
        visitor->player_leaving = 1;
    }
}
CLEAN_AS(func_ov068_0227576c, HouseVisitor_UpdateArrived)

/* Its stay once it is in: 600 frames (until the player talks to it), and the wait before its
 * first walk. */
#define HOUSE_VISITOR_FIRST_STAY 600
#define HOUSE_VISITOR_FIRST_WALK_WAIT 5

/* func_ov068_0227580c: entering state 5 (always succeeds): its first walk waits 5 frames, the
 * mover's pace 1 is set (speed 0x148, 0x25 up and down) and its stay is 600 frames. */
int HouseVisitor_EnterArrived(HouseVisitor *visitor)
{
    visitor->walk_wait = HOUSE_VISITOR_FIRST_WALK_WAIT;
    SceneMover_SetPace(hv_mover(visitor), 1, 0x148, 0x25, 0x25);
    visitor->stay = HOUSE_VISITOR_FIRST_STAY;
    return 1;
}
CLEAN_AS(func_ov068_0227580c, HouseVisitor_EnterArrived)

/* func_ov068_0227584c: state 4's update: once it enters state 5, the event ends. */
void HouseVisitor_UpdateStop(HouseVisitor *visitor)
{
    if (HouseVisitor_SetState(visitor, HOUSE_VISITOR_ARRIVED) != 0) {
        EventQueue_FinishObjectEvent(visitor);
    }
}
CLEAN_AS(func_ov068_0227584c, HouseVisitor_UpdateStop)

/* func_ov068_02275868: entering state 4: it stands, at priority 2 while its action is busy,
 * else 1.
 * QUIRK: declared void, the original leaves the stand's answer as its result, which decides
 * whether the state is entered; the stand is asked for last for the same. */
void HouseVisitor_EnterStop(HouseVisitor *visitor)
{
    int priority = SceneAction_IsBusy(hv_action(visitor)) != 0 ? 2 : 1;
    SceneMotion_RequestStand(hv_motion(visitor), priority, data_020c80f8);
}
CLEAN_AS(func_ov068_02275868, HouseVisitor_EnterStop)

/* func_ov068_022758a8: state 3's update: with 1 frame of the wait left it is drawn and walks
 * (priority 2) to its goal; once the wait is over and the walk done, state 4. The wait runs
 * down to 0. */
void HouseVisitor_UpdateEnter(HouseVisitor *visitor)
{
    if (visitor->enter_wait == 1) {
        visitor->draw = data_ov068_02277fdc;
        SceneMotion_Request(hv_motion(visitor), HOUSE_VISITOR_MOTION_WALK, 2, visitor->goal.x, visitor->goal.z, 0, 0, 0, 0, 0,
                            0);
    } else if (visitor->enter_wait == 0) {
        if (SceneMotion_IsDone(hv_motion(visitor)) != 0) {
            HouseVisitor_SetState(visitor, HOUSE_VISITOR_STOP);
        }
    }
    if (visitor->enter_wait != 0) {
        visitor->enter_wait--;
    }
}
CLEAN_AS(func_ov068_022758a8, HouseVisitor_UpdateEnter)

/* How far in it walks (two tiles), and the frames before it comes in. */
#define HOUSE_VISITOR_ENTER_DEPTH 0x2000
#define HOUSE_VISITOR_ENTER_WAIT 40

/* func_ov068_02275934: entering state 3 (always succeeds): its goal is two tiles in from where
 * it stands, it is not drawn yet, it collides, and it comes in after 40 frames. */
int HouseVisitor_EnterEnter(HouseVisitor *visitor)
{
    visitor->goal = *hv_position(visitor);
    visitor->goal.z -= HOUSE_VISITOR_ENTER_DEPTH;
    visitor->draw = __ptmf_null;
    *hv_part(visitor, HOUSE_VISITOR_SOLID) = 1;
    visitor->enter_wait = HOUSE_VISITOR_ENTER_WAIT;
    return 1;
}
CLEAN_AS(func_ov068_02275934, HouseVisitor_EnterEnter)

/* The sounds of the doorbell and of the door opening (SoundEmitter_PlayB). */
#define HOUSE_VISITOR_SOUND_BELL 0x4ca
#define HOUSE_VISITOR_SOUND_DOOR 0x4cb
#define HOUSE_VISITOR_SOUND_VOLUME 0x7f

/* func_ov068_02275994: state 2's update: once the talk has closed, the door's sound at it and
 * the scene's sound, and state 3.
 * REQUIRES: its talk scene has a talk (the original reads it without a test). */
void HouseVisitor_UpdateCalled(HouseVisitor *visitor)
{
    if (hv_talk(visitor)->state != TALK_OBJECT_CLOSED) {
        return;
    }
    SoundEmitter_PlayB((SoundEmitter *) (void *) hv_part(visitor, HOUSE_VISITOR_EMITTER), HOUSE_VISITOR_SOUND_DOOR,
                       HOUSE_VISITOR_SOUND_VOLUME, 0);
    Block020b220c_PlaySceneSound();
    HouseVisitor_SetState(visitor, HOUSE_VISITOR_ENTER);
}
CLEAN_AS(func_ov068_02275994, HouseVisitor_UpdateCalled)

/* func_ov068_022759d0: entering state 2 (always succeeds): not drawn, and it collides. */
int HouseVisitor_EnterCalled(HouseVisitor *visitor)
{
    visitor->draw = __ptmf_null;
    *hv_part(visitor, HOUSE_VISITOR_SOLID) = 1;
    return 1;
}
CLEAN_AS(func_ov068_022759d0, HouseVisitor_EnterCalled)

/* func_ov068_022759f8: state 1's update: the wait from the doorbell runs down; at 0 its action
 * asks for its talk (keeping the camera), once (the wait then stays at -1). */
void HouseVisitor_UpdateRing(HouseVisitor *visitor)
{
    if (visitor->ring_wait > 0) {
        visitor->ring_wait--;
    }
    if (visitor->ring_wait == 0) {
        SceneAction_RequestTalk(hv_action(visitor), 0, 1);
        visitor->ring_wait = -1;
    }
}
CLEAN_AS(func_ov068_022759f8, HouseVisitor_UpdateRing)

/* The frames from the doorbell to its call, and the state its state entry is given while it
 * is in. */
#define HOUSE_VISITOR_RING_WAIT 30
#define HOUSE_VISITOR_VILLAGER_STATE_VISITING 2

/* func_ov068_02275a34: entering state 1 (always succeeds): not drawn, it does not collide, the
 * map's object 0 (the door) is claimed, the room is rated (its advice and rating kept), the
 * town objects get their extra visitors, its state entry is set to 2 (when it has a town
 * record), the doorbell rings at it after the wait of 30 frames is set, and the room let go. */
int HouseVisitor_EnterRing(HouseVisitor *visitor)
{
    RoomScoreRoom room;

    visitor->draw = __ptmf_null;
    *hv_part(visitor, HOUSE_VISITOR_SOLID) = 0;
    CollisionMap_Claim(0);
    RoomScore_InitRoom(&room);
    visitor->advice = RoomScore_Advice(&room, &visitor->rating);
    TownObjects_SetExtraVisitors();
    if (hv_record(visitor) != NULL) {
        VillagerState_SetState(VillagerStatus_StateEntry(hv_record(visitor)), HOUSE_VISITOR_VILLAGER_STATE_VISITING);
    }
    visitor->ring_wait = HOUSE_VISITOR_RING_WAIT;
    SoundEmitter_PlayB((SoundEmitter *) (void *) hv_part(visitor, HOUSE_VISITOR_EMITTER), HOUSE_VISITOR_SOUND_BELL,
                       HOUSE_VISITOR_SOUND_VOLUME, 0);
    RoomScore_DestructRoom(&room);
    return 1;
}
CLEAN_AS(func_ov068_02275a34, HouseVisitor_EnterRing)

/* Farther than this from the door's side the player hears the bell. */
#define HOUSE_VISITOR_RING_DISTANCE 0x4e66

/* func_ov068_02275ad0: state 0's update: while the visit is due, once this console's player's
 * field actor is farther than 0x4e66 from it (its position copied first), it asks for an event
 * (kind 6). */
void HouseVisitor_UpdateOutside(HouseVisitor *visitor)
{
    if (HouseVisitor_IsDue(visitor) == 0) {
        return;
    }
    u8 *player = SessionPlayers_ActorOf(HOUSE_VISITOR_PLAYER_ACTOR);
    if (player == NULL) {
        return;
    }
    Vec3 at = *(Vec3 *) (void *) (player + HOUSE_VISITOR_ACTOR_POSITION);
    if (Vec_DistanceXZ(&at, hv_position(visitor)) > HOUSE_VISITOR_RING_DISTANCE) {
        EventQueue_RequestKind6(visitor, 0);
    }
}
CLEAN_AS(func_ov068_02275ad0, HouseVisitor_UpdateOutside)

/* Facing into the room (half a turn). */
#define HOUSE_VISITOR_FACING_IN (-0x8000)
/* How far inside the room's front edge it waits. */
#define HOUSE_VISITOR_OUTSIDE_DEPTH 0x1000

/* func_ov068_02275b1c: entering state 0 (always succeeds): it stands at the middle of the room's
 * front edge (x and z only), its walking direction, its direction and its mover facing into
 * the room; not drawn, and it does not collide. */
int HouseVisitor_EnterOutside(HouseVisitor *visitor)
{
    Vec3 *position = hv_position(visitor);
    position->x = data_020ca0e4;
    position->z = data_020ca0e8 - HOUSE_VISITOR_OUTSIDE_DEPTH;
    *(s16 *) (void *) hv_part(visitor, HOUSE_VISITOR_WALK_ANGLE) = HOUSE_VISITOR_FACING_IN;
    *hv_yaw(visitor) = HOUSE_VISITOR_FACING_IN;
    SceneMover_SetAngle(hv_mover(visitor), HOUSE_VISITOR_FACING_IN);
    visitor->draw = __ptmf_null;
    *hv_part(visitor, HOUSE_VISITOR_SOLID) = 0;
    return 1;
}
CLEAN_AS(func_ov068_02275b1c, HouseVisitor_EnterOutside)

/* func_ov068_02275b8c: the update of the current state, through its table (filled once). */
void HouseVisitor_Update(HouseVisitor *visitor)
{
    static const MemberPointer *const updates[HOUSE_VISITOR_STATES] = {
        &data_ov068_0227806c, /* HouseVisitor_UpdateOutside */
        &data_ov068_02278054, /* HouseVisitor_UpdateRing */
        &data_ov068_02277fbc, /* HouseVisitor_UpdateCalled */
        &data_ov068_02277fc4, /* HouseVisitor_UpdateEnter */
        &data_ov068_02277fe4, /* HouseVisitor_UpdateStop */
        &data_ov068_02277ff4, /* HouseVisitor_UpdateArrived */
        &data_ov068_0227800c, /* HouseVisitor_UpdateWander */
        &data_ov068_02278044, /* HouseVisitor_UpdateHeld */
        &data_ov068_02278074, /* HouseVisitor_UpdateTurn */
        &data_ov068_0227805c, /* HouseVisitor_UpdateTalk */
        &data_ov068_02277fec, /* HouseVisitor_UpdateLeave */
    };
    MemberTable_InitOnce(&data_ov068_022788d4, data_ov068_02278948, updates, HOUSE_VISITOR_STATES);
    /* REQUIRES: state >= 0; the ROM's signed test lets a negative one index before the table */
    if (visitor->state >= 0 && visitor->state < HOUSE_VISITOR_STATES) {
        MemberPointer_CallVoid(&data_ov068_02278948[visitor->state], visitor);
    }
}
CLEAN_AS(func_ov068_02275b8c, HouseVisitor_Update)

/* func_ov068_02275c78: enters `state` if its entry function (through a table, filled once)
 * agrees; whether it did. States 11 and above do not exist. */
int HouseVisitor_SetState(HouseVisitor *visitor, int state)
{
    static const MemberPointer *const entries[HOUSE_VISITOR_STATES] = {
        &data_ov068_0227804c, /* HouseVisitor_EnterOutside */
        &data_ov068_02277fd4, /* HouseVisitor_EnterRing */
        &data_ov068_0227803c, /* HouseVisitor_EnterCalled */
        &data_ov068_02278034, /* HouseVisitor_EnterEnter */
        &data_ov068_0227802c, /* HouseVisitor_EnterStop */
        &data_ov068_02277fcc, /* HouseVisitor_EnterArrived */
        &data_ov068_0227801c, /* HouseVisitor_EnterWander */
        &data_ov068_02278014, /* HouseVisitor_EnterHeld */
        &data_ov068_02277ffc, /* HouseVisitor_EnterTurn */
        &data_ov068_02278004, /* HouseVisitor_EnterTalk */
        &data_ov068_02278024, /* HouseVisitor_EnterLeave */
    };
    MemberTable_InitOnce(&data_ov068_022788f4, data_ov068_022789a0, entries, HOUSE_VISITOR_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 10); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < HOUSE_VISITOR_STATES && MemberPointer_CallInt(&data_ov068_022789a0[state], visitor) != 0) {
        visitor->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov068_02275c78, HouseVisitor_SetState)

/* ---- Its talk */

/* func_ov068_02275d74 (the talk scene's slot 0x18, the player's answer): a town villager's
 * (TalkChoices_Reply) while it chats. */
void HouseVisitorTalk_OnAnswer(HouseVisitorTalk *talk, int arg)
{
    if (talk->visitor->talk_kind == HOUSE_VISITOR_SAYS_CHAT) {
        TalkChoices_Reply((TalkChoicesScene *) (void *) talk, (void *) (intptr_t) arg);
    }
}
CLEAN_AS(func_ov068_02275d74, HouseVisitorTalk_OnAnswer)

/* The messages its leaving lines are drawn from ("q_bye"). */
#define HOUSE_VISITOR_BYE_MESSAGES 3
/* The system sound once it says goodbye. */
#define HOUSE_VISITOR_SOUND_BYE 0x5f

/* func_ov068_02275d98 (the talk scene's slot 0x14, a message ended), by what it says:
 * - chatting: a town villager's (VillagerTalk_OnEvent14);
 * - its call from outside: state 2;
 * - "q10_back" or "q10_wait": it says goodbye: one of three messages of its "q_bye" file
 *   (written into data_ov068_022788f8) unless the talk has one already;
 * - goodbye: the talk's closing message, state 10 and the system sound 0x5f;
 * nothing for the others.
 * QUIRK: the villager is tested for null only after its byte 0xa5a was read. */
void HouseVisitorTalk_OnMessageEnded(HouseVisitorTalk *talk, int event)
{
    HouseVisitor *visitor = talk->visitor;
    u8 says = visitor->talk_kind;
    if (says == HOUSE_VISITOR_SAYS_CHAT) {
        VillagerTalk_OnEvent14(&talk->base, event);
        return;
    }
    if (visitor == NULL) {
        return;
    }
    if (says == HOUSE_VISITOR_SAYS_CALL) {
        HouseVisitor_SetState(visitor, HOUSE_VISITOR_CALLED);
    } else if (says == HOUSE_VISITOR_SAYS_BACK || says == HOUSE_VISITOR_SAYS_WAIT) {
        visitor->talk_kind = HOUSE_VISITOR_SAYS_BYE;
        NpcId_FormatResourceName(TownVillager_NpcId(hv_record_field(talk->visitor)), data_ov068_022788f8,
                                 HOUSE_VISITOR_FILE_NAME_SIZE, data_ov068_02278200);
        u8 message = (u8) MainRandom_Below(HOUSE_VISITOR_BYE_MESSAGES);
        TalkObject_SetMessageIfNone(hv_talk(talk->visitor), &message, data_ov068_022788f8);
    } else if (says == HOUSE_VISITOR_SAYS_BYE) {
        u8 message = data_021f43e8;
        TalkObject_SetMessage(hv_talk(talk->visitor), &message, NULL);
        HouseVisitor_SetState(talk->visitor, HOUSE_VISITOR_LEAVE);
        SoundSys_PlaySe(HOUSE_VISITOR_SOUND_BYE);
    }
}
CLEAN_AS(func_ov068_02275d98, HouseVisitorTalk_OnMessageEnded)

/* func_ov068_02275e54 (the talk scene's slot 0x10, a message begins): a town villager's
 * (VillagerTalk_OnEvent10) while it chats. */
void HouseVisitorTalk_OnMessageBegun(HouseVisitorTalk *talk, int arg)
{
    if (talk->visitor->talk_kind == HOUSE_VISITOR_SAYS_CHAT) {
        VillagerTalk_OnEvent10(&talk->base, (void *) (intptr_t) arg);
    }
}
CLEAN_AS(func_ov068_02275e54, HouseVisitorTalk_OnMessageBegun)

/* The highest rating shown, the part of the talk the rating's marks go in, and the chances (of
 * 100) of its lines about the furniture, the layout and the two town villager's tables. */
#define HOUSE_VISITOR_MAX_RATING 5
#define HOUSE_VISITOR_RATING_PART 3
#define HOUSE_VISITOR_CHANCES 100
#define HOUSE_VISITOR_FURNITURE_BELOW 30
#define HOUSE_VISITOR_LAYOUT_BELOW 50
#define HOUSE_VISITOR_CHAT_A_BELOW 70
#define HOUSE_VISITOR_NO_MESSAGE (-1)
/* The bits of the room's advice (RoomScore_Advice). */
#define HOUSE_VISITOR_ADVICE_LOOSE 0x01
#define HOUSE_VISITOR_ADVICE_FACING 0x02
#define HOUSE_VISITOR_ADVICE_ALL_KINDS 0x04
#define HOUSE_VISITOR_ADVICE_GROUP_0 0x10
#define HOUSE_VISITOR_ADVICE_FIVE_OF_GROUP 0x20
/* The low three bits of the visit record's byte 0x24: the rating given. */
#define HOUSE_VISITOR_RATING_MASK 7

/* Writes its message file of `name` (the villager's) into data_ov068_02278920 and notes what it
 * says. */
static void hv_say(HouseVisitorTalk *talk, u8 says, const char *name)
{
    talk->visitor->talk_kind = says;
    NpcId_FormatResourceName(TownVillager_NpcId(hv_record_field(talk->visitor)), data_ov068_02278920,
                             HOUSE_VISITOR_FILE_NAME_SIZE, name);
}

/* The message of its "q10_layout" line for the room's advice. */
static u8 hv_layout_message(int advice)
{
    if (advice & HOUSE_VISITOR_ADVICE_LOOSE) {
        return (u8) MainRandom_Below(2);
    }
    if (advice & HOUSE_VISITOR_ADVICE_FACING) {
        return (u8) (MainRandom_Below(2) + 2);
    }
    if ((advice & HOUSE_VISITOR_ADVICE_ALL_KINDS) == 0) {
        return (u8) (MainRandom_Below(2) + 4);
    }
    if (advice & HOUSE_VISITOR_ADVICE_GROUP_0) {
        return 0xa;
    }
    if (advice & HOUSE_VISITOR_ADVICE_FIVE_OF_GROUP) {
        return (u8) (MainRandom_Below(2) + 8);
    }
    return (u8) (MainRandom_Below(2) + 6);
}

/* func_ov068_02275e78 (the talk scene's vtable slot 0x78, the line it starts with). The text is
 * its message file, written into data_ov068_02278920:
 * - from outside (state 1): "q10_call", one of three messages; the visit has rung;
 * - when its stay ran out and the player is leaving too, the stay is forgotten;
 * - its stay ran out: "q10_back" (one of three); the player is leaving: "q10_wait" (one of two);
 * - the visit not yet let in: "q10_door" (one of three), and it is let in;
 * - just let in: "q10_first" (one of three), and the player greeted;
 * - else one talk fewer is left, a number below 100 is drawn, a message for the villager's
 *   personality (func_ov004_0223c144), and the room's rating (up to 5) put into the talk's part 3
 *   as that many marks; then below 30, with a message, "q10_furniture" with it; below 50
 *   "q10_layout" with a message by the room's advice, the rating kept in the visit's record;
 *   below 70 and above, a town villager's lines (the tables data_021c1f04 and data_021c1f34). */
void HouseVisitorTalk_Line(HouseVisitorTalk *talk, VillagerTalkLine *out)
{
    out->text = (u32) (uintptr_t) data_ov068_02278920;
    HouseVisitor *visitor = talk->visitor;
    if (visitor->state == HOUSE_VISITOR_RING) {
        hv_say(talk, HOUSE_VISITOR_SAYS_CALL, data_ov068_02278208);
        out->message = (u8) MainRandom_Below(3);
        HouseVisitor_MarkRang(talk);
        return;
    }
    if (visitor->time_up != 0 && visitor->player_leaving != 0) {
        visitor->time_up = 0;
    }
    visitor = talk->visitor;
    if (visitor->time_up != 0) {
        hv_say(talk, HOUSE_VISITOR_SAYS_BACK, data_ov068_02278214);
        out->text = (u32) (uintptr_t) data_ov068_02278920;
        out->message = (u8) MainRandom_Below(3);
        return;
    }
    if (visitor->player_leaving != 0) {
        hv_say(talk, HOUSE_VISITOR_SAYS_WAIT, data_ov068_02278220);
        out->text = (u32) (uintptr_t) data_ov068_02278920;
        out->message = (u8) MainRandom_Below(2);
        return;
    }
    if (HouseVisitor_IsPastRing(talk) == 0) {
        hv_say(talk, HOUSE_VISITOR_SAYS_DOOR, data_ov068_0227822c);
        out->message = (u8) MainRandom_Below(3);
        HouseVisitor_MarkLetIn(talk);
        return;
    }
    if (HouseVisitor_IsLetIn(talk) != 0) {
        hv_say(talk, HOUSE_VISITOR_SAYS_FIRST, data_ov068_02278238);
        out->text = (u32) (uintptr_t) data_ov068_02278920;
        out->message = (u8) MainRandom_Below(3);
        HouseVisitor_MarkGreeted(talk);
        return;
    }

    visitor = talk->visitor;
    if (visitor->talks_left != 0) {
        visitor->talks_left--;
    }
    unsigned int chance = MainRandom_Below(HOUSE_VISITOR_CHANCES);
    int message = RoomObjects_PickUnk778(NpcId_Personality(TownVillager_NpcId(hv_record_field(talk->visitor))));
    u32 rating = (u32) talk->visitor->rating;
    if (rating >= HOUSE_VISITOR_MAX_RATING) {
        rating = HOUSE_VISITOR_MAX_RATING;
    }
    u16 marks[HOUSE_VISITOR_MARKS];
    for (int i = 0; i < HOUSE_VISITOR_MARKS; i++) {
        marks[i] = data_ov068_0227807c[i];
    }
    for (u32 i = rating; i < HOUSE_VISITOR_MARKS; i++) {
        marks[i] = 0;
    }
    NameWideText wide;
    MessagePart part;
    NameWideText_ConstructFrom(&wide, marks);
    MessagePart_Construct(&part);
    TextBase_WideToBytes((TextBase *) (void *) &part, (WideTextBase *) (void *) &wide, 0, 0);
    TalkObject_SetPart((TalkObject *) (void *) talk->base.scene.talk, HOUSE_VISITOR_RATING_PART, (TextBase *) (void *) &part);

    if (chance < HOUSE_VISITOR_FURNITURE_BELOW && message != HOUSE_VISITOR_NO_MESSAGE) {
        hv_say(talk, HOUSE_VISITOR_SAYS_FURNITURE, data_ov068_02278244);
        out->text = (u32) (uintptr_t) data_ov068_02278920;
        out->message = (u8) message;
        MessagePart_Destruct(&part);
        NameWideText_Destruct(&wide);
        return;
    }
    if (chance < HOUSE_VISITOR_LAYOUT_BELOW) {
        hv_say(talk, HOUSE_VISITOR_SAYS_LAYOUT, data_ov068_02278254);
        out->text = (u32) (uintptr_t) data_ov068_02278920;
        out->message = hv_layout_message(talk->visitor->advice);
        VillagerPartHandover *visit = hv_visit();
        visit->byte_24 = (u8) ((visit->byte_24 & ~HOUSE_VISITOR_RATING_MASK) | (rating & HOUSE_VISITOR_RATING_MASK));
    } else if (chance < HOUSE_VISITOR_CHAT_A_BELOW) {
        talk->visitor->talk_kind = HOUSE_VISITOR_SAYS_CHAT;
        VillagerTalkScene_SetLines(&talk->base, data_021c1f04);
        VillagerTalkScene_RunLine(&talk->base, out);
    } else {
        talk->visitor->talk_kind = HOUSE_VISITOR_SAYS_CHAT;
        VillagerTalkScene_SetLines(&talk->base, data_021c1f34);
        VillagerTalkScene_RunLine(&talk->base, out);
    }
    MessagePart_Destruct(&part);
    NameWideText_Destruct(&wide);
}
CLEAN_AS(func_ov068_02275e78, HouseVisitorTalk_Line)

/* The lines table VillagerTalkScene_Start is given: 17 and above leave the line members as they
 * are (the talk scene's own vtable slot 0x78 says the line). */
#define HOUSE_VISITOR_TALK_OWN_LINES 0x11

/* func_ov068_022761d0: its talk scene started for `visitor`, and kept pointing back at it. */
void HouseVisitorTalk_Start(HouseVisitorTalk *talk, HouseVisitor *visitor)
{
    VillagerTalkScene_Start(&talk->base, visitor->base, HOUSE_VISITOR_TALK_OWN_LINES);
    talk->visitor = visitor;
}
CLEAN_AS(func_ov068_022761d0, HouseVisitorTalk_Start)

/* ---- The visit's progress (the argument is not used) */

/* func_ov068_022761f0: the player was greeted. */
void HouseVisitor_MarkGreeted(void *unused)
{
    (void) unused;
    ItemObject_SetLow5(hv_progress(), HOUSE_VISITOR_VISIT_GREETED);
}
CLEAN_AS(func_ov068_022761f0, HouseVisitor_MarkGreeted)

/* func_ov068_0227620c: whether the visit was let in and the player not yet greeted. */
int HouseVisitor_IsLetIn(void *unused)
{
    (void) unused;
    return ItemObject_Low5(hv_progress()) == HOUSE_VISITOR_VISIT_IN;
}
CLEAN_AS(func_ov068_0227620c, HouseVisitor_IsLetIn)

/* func_ov068_02276230: the visit let in, unless it went further already. */
void HouseVisitor_MarkLetIn(void *unused)
{
    if (HouseVisitor_IsPastRing(unused) != 0) {
        return;
    }
    ItemObject_SetLow5(hv_progress(), HOUSE_VISITOR_VISIT_IN);
}
CLEAN_AS(func_ov068_02276230, HouseVisitor_MarkLetIn)

/* func_ov068_02276254: whether the visit went past its ring (let in or further). */
int HouseVisitor_IsPastRing(void *unused)
{
    (void) unused;
    return ItemObject_Low5(hv_progress()) > HOUSE_VISITOR_VISIT_RANG;
}
CLEAN_AS(func_ov068_02276254, HouseVisitor_IsPastRing)

/* func_ov068_02276278: the visit has rung, when it had not started. */
void HouseVisitor_MarkRang(void *unused)
{
    if (HouseVisitor_HasStarted(unused) == 0) {
        ItemObject_SetLow5(hv_progress(), HOUSE_VISITOR_VISIT_RANG);
    }
}
CLEAN_AS(func_ov068_02276278, HouseVisitor_MarkRang)

/* func_ov068_0227629c: whether the visit has started (rung or further). */
int HouseVisitor_HasStarted(void *unused)
{
    (void) unused;
    return ItemObject_Low5(hv_progress()) != HOUSE_VISITOR_VISIT_AGREED;
}
CLEAN_AS(func_ov068_0227629c, HouseVisitor_HasStarted)

/* ---- Events and its other vtable slots */

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define HOUSE_VISITOR_EVENT_TALK 0
#define HOUSE_VISITOR_EVENT_ASKED 1
#define HOUSE_VISITOR_EVENT_STARTS 3
#define HOUSE_VISITOR_EVENT_REFUSED 4
#define HOUSE_VISITOR_EVENT_ENDED 8

/* Its stay once an event of another started while it waited near the door: 60 to 99 seconds. */
#define HOUSE_VISITOR_SECOND 60
#define HOUSE_VISITOR_HELD_STAY_BASE 60
#define HOUSE_VISITOR_HELD_STAY_RANGE 40
/* The frames it waits to leave after an event. */
#define HOUSE_VISITOR_LEAVE_WAIT 20

/* func_ov068_022762c0 (vtable slot 0x4c, told of an event):
 * - 3, an event starts: the participant kept; outside state 0 it is held (state 7), its stay
 *   set to 60 to 99 seconds first when it waited near the door (state 5);
 * - 0, the player talks to it: the participant kept, its talk scene started, state 8;
 * - 1, the event it asked for: the participant kept, its talk scene started, state 1 from
 *   state 0 (it rings), else 8;
 * - 8, the event ended: it waits 20 frames to leave, its memory of the player is updated, and
 *   unless it leaves or waits near the door (states 10 and 5) it wanders (state 6);
 * - 4, refused: state 6. */
void HouseVisitor_OnEvent(HouseVisitor *visitor, int code, unsigned char participant)
{
    switch (code) {
        case HOUSE_VISITOR_EVENT_STARTS:
            *hv_part(visitor, HOUSE_VISITOR_PARTICIPANT) = participant;
            if (visitor->state == HOUSE_VISITOR_OUTSIDE) {
                break;
            }
            if (visitor->state == HOUSE_VISITOR_ARRIVED) {
                visitor->stay = (s16) (u16) ((MainRandom_Below(HOUSE_VISITOR_HELD_STAY_RANGE) + HOUSE_VISITOR_HELD_STAY_BASE) *
                                             HOUSE_VISITOR_SECOND);
            }
            HouseVisitor_SetState(visitor, HOUSE_VISITOR_HELD);
            break;
        case HOUSE_VISITOR_EVENT_TALK:
            *hv_part(visitor, HOUSE_VISITOR_PARTICIPANT) = participant;
            HouseVisitorTalk_Start(&visitor->talk, visitor);
            HouseVisitor_SetState(visitor, HOUSE_VISITOR_TURN);
            break;
        case HOUSE_VISITOR_EVENT_ASKED:
            *hv_part(visitor, HOUSE_VISITOR_PARTICIPANT) = participant;
            HouseVisitorTalk_Start(&visitor->talk, visitor);
            if (visitor->state == HOUSE_VISITOR_OUTSIDE) {
                HouseVisitor_SetState(visitor, HOUSE_VISITOR_RING);
            } else {
                HouseVisitor_SetState(visitor, HOUSE_VISITOR_TURN);
            }
            break;
        case HOUSE_VISITOR_EVENT_ENDED:
            visitor->leave_wait = HOUSE_VISITOR_LEAVE_WAIT;
            HouseVisitor_UpdatePlayerMemory(visitor);
            if (visitor->state == HOUSE_VISITOR_LEAVE || visitor->state == HOUSE_VISITOR_ARRIVED) {
                break;
            }
            HouseVisitor_SetState(visitor, HOUSE_VISITOR_WANDER);
            break;
        case HOUSE_VISITOR_EVENT_REFUSED:
            HouseVisitor_SetState(visitor, HOUSE_VISITOR_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov068_022762c0, HouseVisitor_OnEvent)

/* func_ov068_02276394 (vtable slot 0x48): whether the player may talk to it: its action idle and
 * it is in (states 5 and 6). */
int HouseVisitor_MayAct(HouseVisitor *visitor)
{
    if (SceneAction_IsBusy(hv_action(visitor)) != 0) {
        return 0;
    }
    return (u32) visitor->state - HOUSE_VISITOR_ARRIVED <= HOUSE_VISITOR_WANDER - HOUSE_VISITOR_ARRIVED;
}
CLEAN_AS(func_ov068_02276394, HouseVisitor_MayAct)

/* func_ov068_022763c8: the visit is over. */
void HouseVisitor_MarkOver(void)
{
    ItemObject_SetLow5(hv_progress(), HOUSE_VISITOR_VISIT_OVER);
}
CLEAN_AS(func_ov068_022763c8, HouseVisitor_MarkOver)

/* How long after the time agreed the visit may start, in minutes, and the fields compared (the
 * minute to the year). */
#define HOUSE_VISITOR_DUE_MINUTES 30
#define HOUSE_VISITOR_DUE_FIELDS (DATE_TIME_MINUTE | DATE_TIME_HOUR | DATE_TIME_DAY | DATE_TIME_MONTH | DATE_TIME_YEAR)

/* func_ov068_022763e4: whether the visit is due: now is from the time agreed (copied out of the
 * visit's record) to before 30 minutes after it. The argument is not used.
 * QUIRK: the time agreed is compared with now a second time when it is not earlier. */
int HouseVisitor_IsDue(void *unused)
{
    (void) unused;
    DateTime agreed;
    DateTime until;
    MI_CpuCopy8(&hv_visit()->date, &agreed, sizeof(agreed));
    MI_CpuCopy8(&agreed, &until, sizeof(until));
    DateTime_AddMinutes(&until, HOUSE_VISITOR_DUE_MINUTES);
    DateTime now = {0};
    DateTime_Now(&now);
    if (DateTime_Compare(&agreed, &now, HOUSE_VISITOR_DUE_FIELDS) != -1 &&
        DateTime_Compare(&agreed, &now, HOUSE_VISITOR_DUE_FIELDS) != 0) {
        return 0;
    }
    if (DateTime_Compare(&now, &until, HOUSE_VISITOR_DUE_FIELDS) != -1) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov068_022763e4, HouseVisitor_IsDue)

/* func_ov068_02276458: the mover's pace 1 set back (speed 0x100, 0x19 up, 0x33 down). */
void HouseVisitor_SlowPace(HouseVisitor *visitor)
{
    SceneMover_SetPace(hv_mover(visitor), 1, 0x100, 0x19, 0x33);
}
CLEAN_AS(func_ov068_02276458, HouseVisitor_SlowPace)

/* func_ov068_0227647c: its memory of the current player updated (VillagerMemoryEntry_Update with
 * no player, town or date); nothing without a current player or a record. */
void HouseVisitor_UpdatePlayerMemory(HouseVisitor *visitor)
{
    u8 *player = PlayerRecords_Current();
    if (player == NULL || hv_record_field(visitor) == NULL) {
        return;
    }
    VillagerMemoryEntry_Update(VillagerMemory_Meet(hv_record_field(visitor), PlayerRecord_Player(player)), NULL, NULL, NULL);
}
CLEAN_AS(func_ov068_0227647c, HouseVisitor_UpdatePlayerMemory)

/* The room's tiles each way. */
#define HOUSE_VISITOR_ROOM_TILES 16

/* func_ov068_022764b4: every tile of the room whose code (layer 0) is furniture or a cell a piece
 * of furniture covers (ItemCode_IsF031OrVariant) loses its path directions, and its neighbours
 * their way to it. With no acre in the map (no width, no height or no records) the tiles are
 * asked of a null acre. The argument is not used. */
void HouseVisitor_UnlinkFurnitureTiles(void *unused)
{
    (void) unused;
    AcreMap *map = data_021c80bc;
    AcreRecord *acre = NULL;
    if (map->acres_wide != 0 && map->acres_high != 0 && map->acres != NULL) {
        acre = (AcreRecord *) (void *) map->acres;
    }
    for (int z = 0; z < HOUSE_VISITOR_ROOM_TILES; z++) {
        for (int x = 0; x < HOUSE_VISITOR_ROOM_TILES; x++) {
            u16 *code = AcreRecord_Tile(acre, (unsigned int) x, (unsigned int) z, 0);
            if (code != NULL && ItemCode_IsF031OrVariant(code)) {
                CollisionMap_UnlinkPathUnit(x, z);
            }
        }
    }
}
CLEAN_AS(func_ov068_022764b4, HouseVisitor_UnlinkFurnitureTiles)

/* func_ov068_02276510 (vtable slot 0x68, its frame): the current state's update; always 1. */
int HouseVisitor_Frame(HouseVisitor *visitor)
{
    HouseVisitor_Update(visitor);
    return 1;
}
CLEAN_AS(func_ov068_02276510, HouseVisitor_Frame)

/* func_ov068_02276520 (vtable slot 0x10, the deletion check): the town villager's; once it may
 * be deleted, a visit that only rang counts as let in, and the room's visitor is forgotten. */
int HouseVisitor_CanDelete(HouseVisitor *visitor)
{
    if (VillagerSceneObject_CanDelete(visitor->base) == 0) {
        return 0;
    }
    ItemObject *progress = hv_progress();
    if (ItemObject_Low5(progress) == HOUSE_VISITOR_VISIT_RANG) {
        ItemObject_SetLow5(progress, HOUSE_VISITOR_VISIT_IN);
    }
    data_ov068_022788ec = NULL;
    return 1;
}
CLEAN_AS(func_ov068_02276520, HouseVisitor_CanDelete)

/* func_ov068_02276564 (vtable slot 0x24, the drawing): its drawing member run (HouseVisitor_Draw
 * while it is shown); 1 while its function is not set. */
int HouseVisitor_RunDraw(HouseVisitor *visitor)
{
    if (visitor->draw.function != 0) {
        return MemberPointer_CallInt(&visitor->draw, visitor);
    }
    return 1;
}
CLEAN_AS(func_ov068_02276564, HouseVisitor_RunDraw)

/* func_ov068_02276598 (the member data_ov068_02277fdc and data_ov068_02278064 name): the scene
 * object drawn; whether it was. */
int HouseVisitor_Draw(HouseVisitor *visitor)
{
    return SceneObject_Draw(visitor->base) != 0;
}
CLEAN_AS(func_ov068_02276598, HouseVisitor_Draw)

/* Its stay and talks, and the frames it waits to leave, when it starts: no limit, 3 talks and
 * 176 frames; then outside, 60 to 99 seconds and 7 to 10 talks; when the visit had started
 * already (it is in), 40 to 59 seconds and 2 to 5 talks. */
#define HOUSE_VISITOR_NO_LIMIT (-1)
#define HOUSE_VISITOR_START_TALKS 3
#define HOUSE_VISITOR_START_LEAVE_WAIT 0xb0
#define HOUSE_VISITOR_OUT_STAY_BASE 60
#define HOUSE_VISITOR_OUT_STAY_RANGE 40
#define HOUSE_VISITOR_OUT_TALKS_BASE 7
#define HOUSE_VISITOR_IN_STAY_BASE 40
#define HOUSE_VISITOR_IN_STAY_RANGE 20
#define HOUSE_VISITOR_IN_TALKS_BASE 2
#define HOUSE_VISITOR_TALKS_RANGE 4

/* func_ov068_022765b0 (vtable slot 0x00, its start): the town villager's start; then it is drawn,
 * the furnished tiles leave the room's paths, its footsteps are on, and its countdowns set.
 * Coming from scene 0 it starts outside (state 0). Else, when the visit had started, it is in
 * already: the town objects get their extra visitors, its stay and talks are set, the room is
 * rated and it wanders (state 6); otherwise its stay and talks are set and it starts outside. */
int HouseVisitor_Start(HouseVisitor *visitor)
{
    if (VillagerSceneObject_Start(visitor->base) == 0) {
        return 0;
    }
    visitor->draw = data_ov068_02278064;
    HouseVisitor_UnlinkFurnitureTiles(visitor);
    Footsteps_Enable((Footsteps *) (void *) hv_part(visitor, HOUSE_VISITOR_FOOTSTEPS));
    visitor->stay = HOUSE_VISITOR_NO_LIMIT;
    visitor->talks_left = HOUSE_VISITOR_START_TALKS;
    visitor->leave_wait = HOUSE_VISITOR_START_LEAVE_WAIT;

    if (SceneQuery_Is0(SceneQuery_Previous()) != 0) {
        HouseVisitor_SetState(visitor, HOUSE_VISITOR_OUTSIDE);
    } else if (HouseVisitor_HasStarted(&visitor->talk) != 0) {
        RoomScoreRoom room;
        TownObjects_SetExtraVisitors();
        visitor->stay =
            (s16) ((MainRandom_Below(HOUSE_VISITOR_IN_STAY_RANGE) + HOUSE_VISITOR_IN_STAY_BASE) * HOUSE_VISITOR_SECOND);
        visitor->talks_left = (u8) (MainRandom_Below(HOUSE_VISITOR_TALKS_RANGE) + HOUSE_VISITOR_IN_TALKS_BASE);
        RoomScore_InitRoom(&room);
        visitor->advice = RoomScore_Advice(&room, &visitor->rating);
        HouseVisitor_SetState(visitor, HOUSE_VISITOR_WANDER);
        RoomScore_DestructRoom(&room);
    } else {
        visitor->stay =
            (s16) ((MainRandom_Below(HOUSE_VISITOR_OUT_STAY_RANGE) + HOUSE_VISITOR_OUT_STAY_BASE) * HOUSE_VISITOR_SECOND);
        visitor->talks_left = (u8) (MainRandom_Below(HOUSE_VISITOR_TALKS_RANGE) + HOUSE_VISITOR_OUT_TALKS_BASE);
        HouseVisitor_SetState(visitor, HOUSE_VISITOR_OUTSIDE);
    }
    return 1;
}
CLEAN_AS(func_ov068_022765b0, HouseVisitor_Start)

/* func_ov068_022766b0 (vtable slot 0x04, its set-up): the town villager's set-up; it becomes the
 * room's visitor, and its talk scene becomes its scene and is started. */
int HouseVisitor_Init(HouseVisitor *visitor)
{
    if (VillagerSceneObject_Init(visitor->base) == 0) {
        return 0;
    }
    data_ov068_022788ec = visitor;
    SceneObject_SetScene(visitor->base, (struct SceneBase *) (void *) &visitor->talk);
    HouseVisitorTalk_Start(&visitor->talk, visitor);
    return 1;
}
CLEAN_AS(func_ov068_022766b0, HouseVisitor_Init)

/* func_ov068_022766e8: a new house visitor, zeroed from the auxiliary heap: a town villager
 * scene object with this class's vtable, and its talk scene constructed with the talk scene's
 * vtable. Null when the heap has no room. */
HouseVisitor *HouseVisitor_New(void)
{
    HouseVisitor *visitor = Heap_AllocAuxZeroed(sizeof(HouseVisitor));
    if (visitor != NULL) {
        VillagerSceneObject_Construct(visitor->base);
        *(const u8 **) (void *) visitor->base = data_ov068_02278140;
        VillagerTalkScene_ConstructAlt(&visitor->talk.base);
        visitor->talk.base.scene.vtable = data_ov068_022780b0;
    }
    return visitor;
}
CLEAN_AS(func_ov068_022766e8, HouseVisitor_New)
