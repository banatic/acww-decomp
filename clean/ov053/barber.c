/* The barber (barber.h): its object's vtable slots, what it watches the player for, and its
 * states. */
#include "barber.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/block_021d27ac.h"
#include "main/camera_modes.h"
#include "main/collision_map.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/music_queue.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_exit.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_query.h"
#include "main/scene_standard_anims.h"
#include "main/scene_tables.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/screen_panels.h"
#include "main/session.h"
#include "main/sound_emitter.h"
#include "main/speaker_anim.h"
#include "main/special_scene_object.h"
#include "ov004/barber_machine.h"
#include "ov004/room_camera.h"
#include "ov004/room_player_actor.h"

static_assert(offsetof(Barber, state) == 0x654 && offsetof(Barber, talk) == 0x658, "Barber");
static_assert(offsetof(Barber, send_step) == 0x718 && offsetof(Barber, waypoint) == 0x719, "Barber");
static_assert(offsetof(Barber, cut_countdown) == 0x71a && offsetof(Barber, music_countdown) == 0x71b, "Barber");
static_assert(offsetof(Barber, home_angle) == 0x71c, "Barber");
static_assert(sizeof(Barber) == 0x720, "the size Barber_Create allocates");
static_assert(sizeof(BarberStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define BARBER_POSITION 0x5c        /* Vec3 */
#define BARBER_PERSON 0xea          /* u16: its person code */
#define BARBER_MODEL 0xec           /* LayeredModel */
#define BARBER_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define BARBER_FACE 0x2ac           /* SceneFace */
#define BARBER_ANIM 0x334           /* SpeakerAnim */
#define BARBER_MOVER 0x350          /* SceneMover */
#define BARBER_PROBE 0x3a8          /* the probe */
#define BARBER_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define BARBER_LOOK 0x3b0           /* SceneLook */
#define BARBER_TALK_STATE 0x418     /* SceneTalkState */
#define BARBER_EFFECTS 0x420        /* ActEffects */
#define BARBER_COLLIDER 0x49c       /* CollisionContacts */
#define BARBER_CARRIER 0x4cc        /* FieldOwnedBody */
#define BARBER_FLAGS 0x4e8          /* u32: the scene object's flags (2: held) */
#define BARBER_EMITTER 0x514        /* SoundEmitterObject */
#define BARBER_FOOTSTEPS 0x558      /* Footsteps */
#define BARBER_PARTICIPANT 0x560    /* u8: whose system the last event came from */
#define BARBER_MOTION 0x564         /* SceneMotion */
#define BARBER_ACTION 0x618         /* SceneAction */
#define BARBER_HEAP 0x640           /* PoolLink */

#define BARBER_NO_PERSON 0xfff1
#define BARBER_NO_ITEM 0xfff1
#define BARBER_HELD 2

/* The field actor of this console's player. */
#define BARBER_PLAYER_ACTOR 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h): the player talks to it, an event
 * of kind 6 or 7 it asked for runs, an event starts, the event ended. */
#define BARBER_EVENT_TALK 0
#define BARBER_EVENT_ASKED 1
#define BARBER_EVENT_STARTS 3
#define BARBER_EVENT_ENDED 8

/* The vtable slot of its talk scene that resets it (SceneBase_Reset). */
#define BARBER_TALK_SLOT_RESET 0x08

/* The flag of the block 0x021d27ac set while a cut is paid for and not given. */
#define BARBER_FLAG_PAID 7

/* The player's field states of a spot (ov004's field_actor_room_states.h): sitting down on it
 * and sitting at it. */
#define BARBER_PLAYER_SITS_DOWN 0x25
#define BARBER_PLAYER_SITS 0x28
/* The tiles of the chair: (4, 11) and (5, 11). */
#define BARBER_CHAIR_TILE_X0 4
#define BARBER_CHAIR_TILE_X1 5
#define BARBER_CHAIR_TILE_Z 0xb

/* The looks it asks for (SceneLook_Request): straight ahead and the player. */
#define BARBER_LOOK_AHEAD 0
#define BARBER_LOOK_PLAYER 1

/* Its motions (scene_motion_request.h): stand, a turn and a walk to a point. */
#define BARBER_MOTION_STAND 0
#define BARBER_MOTION_TURN 3
#define BARBER_MOTION_WALK 6
#define BARBER_WALK_RATE 0x800
#define BARBER_ANGLE_SIDE 0x4000
/* The animation of its cut, mode 1. */
#define BARBER_ANIM_CUT 0xf1
#define BARBER_ANIM_CUT_MODE 1

/* A route's points. */
#define BARBER_ROUTE_POINTS 2

/* The cut: 100 frames; at 85 left the hair changes, the machine runs and sound 0x41 plays. */
#define BARBER_CUT_FRAMES 100
#define BARBER_CUT_HAIR_AT 0x55
#define BARBER_CUT_SOUND 0x41
#define BARBER_CUT_SOUND_VOLUME 0x7f
/* The frames after the cut's talk starts before the music's priority 0xe is dropped. */
#define BARBER_MUSIC_FRAMES 0x1f
#define BARBER_MUSIC_PRIORITY 0xe
/* The camera's point when it talks after the cut: 2.0 above it. */
#define BARBER_CAMERA_RISE 0x2000

/* The player's walk back (state 9): the acceleration. */
#define BARBER_SEND_BACK_ACCEL 0x266

/* The scene SceneQuery_Previous names when the player comes in from outside, when she calls. */
#define BARBER_SCENE_CALL_FROM 29

/* The size of its collider (SceneObject_SetColliderSize), and its mover's pace index. */
#define BARBER_COLLIDER_SIZE 0x100
#define BARBER_PACE_INDEX 2

/* The vtables of its class and of the classes it derives from. */
extern const u8 data_ov053_02261b98[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Its model and texture file names: "npc_sp/model/poo.nsbmd", "npc_sp/model/poo_tex.nsbtx". */
extern const char data_ov053_02261a44[];
extern const char data_ov053_02261a74[];
/* The functions of its states (filled at start-up by __sinit_ov053_0226182c). */
extern BarberStep data_ov053_02261c64[BARBER_STATES];
/* The line past which the player walks to the door (its z, 29.0; the point is (11.0, 0, 29.0)). */
extern const Vec3 data_ov053_022617c8;
/* The point the player is walked back to: (16.0, 0, 27.0). */
extern const Vec3 data_ov053_022617d4;
/* Its mover's pace: speed 0x300, speeding up and slowing down by 0x199. */
typedef struct BarberPace {
    fx32 speed;
    fx32 speed_up;
    fx32 slow_down;
} BarberPace;
extern const BarberPace data_ov053_022617e0;
/* Its routes: A (14.0, 21.0) then (15.0, 23.0); B (14.5, 21.5) then (12.0, 21.0). Each is two
 * points; the bytes after them are read as a third (the start of route B after route A, and the
 * code of __sinit_ov053_0226182c after route B). */
extern const Vec3 data_ov053_022617fc[];
extern const Vec3 data_ov053_02261814[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The look's point and range when it names neither. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

static u8 *barber_part(Barber *barber, u32 offset)
{
    return barber->base + offset;
}

static SceneMotion *barber_motion(Barber *barber)
{
    return (SceneMotion *) (void *) barber_part(barber, BARBER_MOTION);
}

static SceneAction *barber_action(Barber *barber)
{
    return (SceneAction *) (void *) barber_part(barber, BARBER_ACTION);
}

/* Its look asked for: `kind`, priority 0, with the defaults for what it does not name. */
static void barber_look(Barber *barber, u8 kind)
{
    SceneLook_Request((SceneLook *) (void *) barber_part(barber, BARBER_LOOK), kind, 0, 0, &data_021fbee8, BARBER_PLAYER_ACTOR,
                      data_020c814c, 1);
}

/* A turn (priority 1) to `angle`. */
static void barber_turn(Barber *barber, s16 angle, u16 word)
{
    SceneMotion_Request(barber_motion(barber), BARBER_MOTION_TURN, 1, 0, 0, 0, angle, 0, 0, word, 0);
}

/* A walk (priority 1) to the route's point at the waypoint. */
static void barber_walk(Barber *barber, const Vec3 *route)
{
    const Vec3 *point = &route[barber->waypoint];
    SceneMotion_Request(barber_motion(barber), BARBER_MOTION_WALK, 1, point->x, point->z, BARBER_WALK_RATE, 0, 0, 0,
                        data_020c80f8, 0);
}

/* Its talk scene reset through its vtable slot 0x08, the talk's partner this console's player's
 * field actor. */
static void barber_reset_talk(Barber *barber)
{
    u32 vtable = *(const u32 *) (const void *) &barber->talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + BARBER_TALK_SLOT_RESET);
    ((void (*)(BarberTalk *))(uintptr_t) code)(&barber->talk);
    SceneBase_SetMotionArg(&barber->talk.base, SceneObject_ActorObject(barber->base, BARBER_PLAYER_ACTOR));
}

/* Whether the talk's topic is the player seated in the chair, with or without a hat. */
static int barber_seated_topic(Barber *barber)
{
    return barber->talk.topic == BARBER_TOPIC_SEATED || barber->talk.topic == BARBER_TOPIC_SEATED_HAT;
}

/* ---- The object */

/* func_ov053_02260420 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
Barber *Barber_Destruct(Barber *barber)
{
    *(const u8 **) (void *) barber = data_ov053_02261b98;
    BarberTalk_Destruct(&barber->talk);
    SpecialSceneObject_DestructBody(barber);
    return barber;
}
CLEAN_AS(func_ov053_02260420, Barber_Destruct)

/* func_ov053_02260448 (vtable slot 0x44): the same, then the object freed. */
void *Barber_DestructDelete(void *barber)
{
    *(const u8 **) barber = data_ov053_02261b98;
    BarberTalk_Destruct(&((Barber *) barber)->talk);
    SpecialSceneObject_DestructBody(barber);
    Heap_FreeAux(barber);
    return barber;
}
CLEAN_AS(func_ov053_02260448, Barber_DestructDelete)

/* func_ov053_02260474: whether a cut is paid for and not given yet (the flag 7 of the block
 * 0x021d27ac). */
int Barber_IsPaid(int unused)
{
    (void) unused;
    return Block021d27ac_TestFlag((u32 *) (void *) Block021d27ac_Get(), BARBER_FLAG_PAID);
}
CLEAN_AS(func_ov053_02260474, Barber_IsPaid)

/* func_ov053_02260488: whether the current player's record has an accessory (its item C) or a
 * hat. */
int Barber_WearsHat(void *unused)
{
    (void) unused;
    u8 *record = PlayerRecords_Current();
    if (*PlayerRecord_PartCItem(record) != BARBER_NO_ITEM) {
        return 1;
    }
    return *PlayerRecord_HeadItem(record) != BARBER_NO_ITEM;
}
CLEAN_AS(func_ov053_02260488, Barber_WearsHat)

/* func_ov053_022604bc: when this console's player stands on the map's claimed object (claimed
 * at its start), the topic claimed and an event of kind 6 asked for. Whether it was. */
int Barber_CheckClaimed(Barber *barber)
{
    Vec3 player = *PlayerActorOps_StartPosition(BARBER_PLAYER_ACTOR);
    if (!CollisionMap_IsClaimedAtPoint(&player)) {
        return 0;
    }
    BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_CLAIMED);
    EventQueue_RequestKind6(barber, 0);
    return 1;
}
CLEAN_AS(func_ov053_022604bc, Barber_CheckClaimed)

/* func_ov053_02260504: with the cut paid for, when this console's player walks past z 29.0 to
 * the door, the topic leaving and an event of kind 6 asked for. Whether it was. */
int Barber_CheckLeaving(Barber *barber)
{
    if (Barber_IsPaid((int) (uintptr_t) barber) == 0) {
        return 0;
    }
    Vec3 player = *PlayerActorOps_StartPosition(BARBER_PLAYER_ACTOR);
    if (player.z <= data_ov053_022617c8.z) {
        return 0;
    }
    BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_LEAVING);
    EventQueue_RequestKind6(barber, 0);
    return 1;
}
CLEAN_AS(func_ov053_02260504, Barber_CheckLeaving)

/* func_ov053_02260558: when no event about an object runs and the cut is paid for, and this
 * console's player sits down or sits on a spot, an event of kind 7 is asked for; given, the
 * topic is seated (seated with a hat when the player's record has one) on the chair's tiles
 * (4, 11) and (5, 11), else not seated. Whether it was given.
 * QUIRK: the current player's record is fetched and not used. */
int Barber_CheckSeated(Barber *barber)
{
    if (EventQueue_IsObjectEvent() != 0) {
        return 0;
    }
    if (Barber_IsPaid((int) (uintptr_t) barber) == 0) {
        return 0;
    }
    PlayerRecords_Current();
    Vec3 player = *PlayerActorOps_StartPosition(BARBER_PLAYER_ACTOR);
    int tile_x = 0;
    int tile_z = 0;
    Position_Tile(&tile_x, &tile_z, (const Position *) (const void *) &player);
    if (!PlayerActorOps_InState(BARBER_PLAYER_SITS_DOWN, BARBER_PLAYER_ACTOR) &&
        !PlayerActorOps_InState(BARBER_PLAYER_SITS, BARBER_PLAYER_ACTOR)) {
        return 0;
    }
    if (EventQueue_RequestKind7(barber, 0) == 0) {
        return 0;
    }
    if ((tile_x == BARBER_CHAIR_TILE_X0 || tile_x == BARBER_CHAIR_TILE_X1) && tile_z == BARBER_CHAIR_TILE_Z) {
        if (Barber_WearsHat(barber)) {
            BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_SEATED_HAT);
        } else {
            BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_SEATED);
        }
    } else {
        BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_NOT_SEATED);
    }
    return 1;
}
CLEAN_AS(func_ov053_02260558, Barber_CheckSeated)

/* func_ov053_02260620 (vtable slot 0x4c, told of an event about it by `participant`'s system):
 * the participant kept, then by the code:
 * - 3, an event starts: paused;
 * - 1, an event it asked for runs: its talk scene reset with this console's player as the
 *   partner; seated in the chair (with or without a hat), it walks route B first, else talks;
 * - 0, the player talks to it: the same reset, and it talks;
 * - 8, the event ended: after the topic hat back it walks route A, else, but after the topic
 *   claimed, it turns back; either way with no topic.
 * QUIRK: the current player's record is fetched and not used; with code 1 the participant is
 * stored a second time. */
void Barber_OnEvent(Barber *barber, unsigned int code, u8 participant)
{
    u8 *stored = barber_part(barber, BARBER_PARTICIPANT);

    PlayerRecords_Current();
    *stored = participant;
    switch (code) {
        case BARBER_EVENT_STARTS:
            Barber_SetState(barber, BARBER_STATE_PAUSED);
            break;
        case BARBER_EVENT_ASKED:
            *stored = participant;
            barber_reset_talk(barber);
            if (barber_seated_topic(barber)) {
                Barber_SetState(barber, BARBER_STATE_WALK_B);
            } else {
                Barber_SetState(barber, BARBER_STATE_TALK);
            }
            break;
        case BARBER_EVENT_TALK:
            barber_reset_talk(barber);
            Barber_SetState(barber, BARBER_STATE_TALK);
            break;
        case BARBER_EVENT_ENDED:
            if (barber->talk.topic == BARBER_TOPIC_HAT_BACK) {
                BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_NONE);
                Barber_SetState(barber, BARBER_STATE_WALK_A);
            } else if (barber->talk.topic != BARBER_TOPIC_CLAIMED) {
                BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_NONE);
                Barber_SetState(barber, BARBER_STATE_TURN_BACK);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov053_02260620, Barber_OnEvent)

/* func_ov053_0226071c (vtable slot 0x58): agreed while no action of its runs. */
int Barber_MayTalk(Barber *barber)
{
    return !SceneAction_IsBusy(barber_action(barber));
}
CLEAN_AS(func_ov053_0226071c, Barber_MayTalk)

/* func_ov053_0226073c (vtable slot 0x48): whether the player may talk to it: no action of its
 * runs. */
int Barber_MayAct(Barber *barber)
{
    return !SceneAction_IsBusy(barber_action(barber));
}
CLEAN_AS(func_ov053_0226073c, Barber_MayAct)

/* ---- Its states */

/* func_ov053_02260c2c (state 10's update): nothing. 1. */
int Barber_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov053_02260c2c, Barber_UpdatePaused)

/* func_ov053_02260c30 (state 10's entry): nothing. 1. */
int Barber_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov053_02260c30, Barber_EnterPaused)

/* func_ov053_02260c34 (state 9's update), by its step: 0, once its action is idle the camera's
 * mode is reset; 1, this console's player walks to (16.0, 27.0) (acceleration 0x266); 2, once the
 * player is no longer busy the event ends and it turns back. 1.
 * QUIRK: the current player's record is fetched, and the tiles of the player's position and of
 * that point computed, and none is used. */
int Barber_UpdateSendBack(Barber *barber)
{
    int tiles[4];

    PlayerRecords_Current();
    Vec3 player = *PlayerActorOps_StartPosition(BARBER_PLAYER_ACTOR);
    tiles[0] = 0;
    tiles[1] = 0;
    tiles[2] = 0;
    tiles[3] = 0;
    Vec3 point = data_ov053_022617d4;
    Position_Tile(&tiles[2], &tiles[3], (const Position *) (const void *) &point);
    Position_Tile(&tiles[0], &tiles[1], (const Position *) (const void *) &player);

    switch (barber->send_step) {
        case 0:
            if (!SceneAction_IsBusy(barber_action(barber))) {
                CameraControl_ResetMode();
                barber->send_step = 1;
            }
            break;
        case 1: {
            Vec3 to = point;
            PlayerActorOps_MoveTo(&to, BARBER_SEND_BACK_ACCEL, BARBER_PLAYER_ACTOR);
            barber->send_step = 2;
            break;
        }
        case 2:
            if (PlayerActorOps_IsBusy(BARBER_PLAYER_ACTOR) == 0) {
                EventQueue_FinishObjectEvent(barber);
                Barber_SetState(barber, BARBER_STATE_TURN_BACK);
            }
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov053_02260c34, Barber_UpdateSendBack)

/* func_ov053_02260cf0 (state 9's entry): its first step. 1. */
int Barber_EnterSendBack(Barber *barber)
{
    barber->send_step = 0;
    return 1;
}
CLEAN_AS(func_ov053_02260cf0, Barber_EnterSendBack)

/* func_ov053_02260d00 (state 8's update): once the cut's frames have run out, the topic cut and
 * it talks. With 85 frames left this console's player's field actor takes the style and colour
 * picked, overlay 4's machine runs (BarberMachine_Run) and its sound 0x41 plays. Once its
 * animation is the cut's and its motion is done, it stands (priority 1). 1. */
int Barber_UpdateCut(Barber *barber)
{
    if (Countdown_Tick8(&barber->cut_countdown) == 0) {
        BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_CUT);
        Barber_SetState(barber, BARBER_STATE_TALK);
    }
    if (barber->cut_countdown == BARBER_CUT_HAIR_AT) {
        u8 colour = barber->talk.colour;
        u8 style = barber->talk.style;
        RoomPlayerActor_RequestHairOff(&style, &colour);
        BarberMachine_Run();
        SoundEmitter_Play((SoundEmitter *) (void *) barber_part(barber, BARBER_EMITTER), BARBER_CUT_SOUND,
                          BARBER_CUT_SOUND_VOLUME, 0);
    }
    if (SpeakerAnim_IsBody((SpeakerAnim *) (void *) barber_part(barber, BARBER_ANIM), BARBER_ANIM_CUT,
                           barber_part(barber, BARBER_STANDARD_ANIMS)) &&
        SceneMotion_IsDone(barber_motion(barber))) {
        SceneMotion_Request(barber_motion(barber), BARBER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }
    return 1;
}
CLEAN_AS(func_ov053_02260d00, Barber_UpdateCut)

/* func_ov053_02260dc4 (state 8's entry): 100 frames of cut, and its animation of the cut (0xf1,
 * priority 1, mode 1). 1. */
int Barber_EnterCut(Barber *barber)
{
    barber->cut_countdown = BARBER_CUT_FRAMES;
    SceneMotion_RequestAnimation(barber_motion(barber), 1, BARBER_ANIM_CUT, BARBER_ANIM_CUT_MODE, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov053_02260dc4, Barber_EnterCut)

/* func_ov053_02260dfc (state 7's update): while it walks, its mover starts from the point it
 * walks to; once there, the next point of route A, and past the last a turn to -0x4000. Once a
 * turn is done: past the last point it cuts, else it walks to the point. 1.
 * QUIRK: past the last point a walk to a third point (route B's first) is asked for too. */
int Barber_UpdateToCut(Barber *barber)
{
    SceneMover *mover = (SceneMover *) (void *) barber_part(barber, BARBER_MOVER);

    if (SceneMotion_Kind(barber_motion(barber)) == BARBER_MOTION_WALK) {
        Vec3 start = data_ov053_022617fc[barber->waypoint];
        SceneMover_SetStart(mover, &start);
        if (SceneMotion_IsDone(barber_motion(barber))) {
            barber->waypoint++;
            u16 word = data_020c80f8;
            barber_walk(barber, data_ov053_022617fc);
            if (barber->waypoint >= BARBER_ROUTE_POINTS) {
                barber_turn(barber, -BARBER_ANGLE_SIDE, word);
            }
        }
    }
    if (SceneMotion_Kind(barber_motion(barber)) == BARBER_MOTION_TURN && SceneMotion_IsDone(barber_motion(barber))) {
        if (barber->waypoint >= BARBER_ROUTE_POINTS) {
            Barber_SetState(barber, BARBER_STATE_CUT);
        } else {
            barber_walk(barber, data_ov053_022617fc);
        }
    }
    return 1;
}
CLEAN_AS(func_ov053_02260dfc, Barber_UpdateToCut)

/* func_ov053_02260f20 (state 7's entry): it looks ahead, starts at route A's first point and
 * turns to 0x4000. 1. */
int Barber_EnterToCut(Barber *barber)
{
    barber_look(barber, BARBER_LOOK_AHEAD);
    barber->waypoint = 0;
    barber_turn(barber, BARBER_ANGLE_SIDE, data_020c80f8);
    return 1;
}
CLEAN_AS(func_ov053_02260f20, Barber_EnterToCut)

/* The update of a walk along `route` (states 5 and 6): while it walks, its mover starts from the
 * point it walks to; once there, the next point, and past the last the state `then`. Once a
 * turn is done it walks to the point.
 * QUIRK: past the last point a walk to a third point (the bytes after the route) is asked for
 * before the state changes. */
static void barber_update_walk(Barber *barber, const Vec3 *route, int then)
{
    SceneMover *mover = (SceneMover *) (void *) barber_part(barber, BARBER_MOVER);

    if (SceneMotion_Kind(barber_motion(barber)) == BARBER_MOTION_WALK) {
        Vec3 start = route[barber->waypoint];
        SceneMover_SetStart(mover, &start);
        if (SceneMotion_IsDone(barber_motion(barber))) {
            barber->waypoint++;
            barber_walk(barber, route);
            if (barber->waypoint >= BARBER_ROUTE_POINTS) {
                Barber_SetState(barber, then);
            }
        }
    }
    if (SceneMotion_Kind(barber_motion(barber)) == BARBER_MOTION_TURN && SceneMotion_IsDone(barber_motion(barber))) {
        barber_walk(barber, route);
    }
}

/* func_ov053_02260f94 (state 6's update): the walk of route B, then it talks. 1. */
int Barber_UpdateWalkB(Barber *barber)
{
    barber_update_walk(barber, data_ov053_02261814, BARBER_STATE_TALK);
    return 1;
}
CLEAN_AS(func_ov053_02260f94, Barber_UpdateWalkB)

/* func_ov053_02261090 (state 6's entry): it starts at route B's first point and turns (priority
 * 1) to the yaw from its position to it. 1. */
int Barber_EnterWalkB(Barber *barber)
{
    barber->waypoint = 0;
    Vec3 first = data_ov053_02261814[0];
    s16 angle = Vec_YawTo((const Vec3 *) (const void *) barber_part(barber, BARBER_POSITION), &first);
    barber_turn(barber, angle, data_020c80f8);
    return 1;
}
CLEAN_AS(func_ov053_02261090, Barber_EnterWalkB)

/* func_ov053_022610f0 (state 5's update): the walk of route A, then it turns back. 1. */
int Barber_UpdateWalkA(Barber *barber)
{
    barber_update_walk(barber, data_ov053_022617fc, BARBER_STATE_TURN_BACK);
    return 1;
}
CLEAN_AS(func_ov053_022610f0, Barber_UpdateWalkA)

/* func_ov053_022611ec (state 5's entry): it starts at route A's first point and turns to
 * 0x4000. 1. */
int Barber_EnterWalkA(Barber *barber)
{
    barber->waypoint = 0;
    barber_turn(barber, BARBER_ANGLE_SIDE, data_020c80f8);
    return 1;
}
CLEAN_AS(func_ov053_022611ec, Barber_EnterWalkA)

/* func_ov053_02261230 (state 4's update): once its turn is done, it stands. 1. */
int Barber_UpdateTurnBack(Barber *barber)
{
    if (SceneMotion_Kind(barber_motion(barber)) == BARBER_MOTION_TURN && SceneMotion_IsDone(barber_motion(barber))) {
        Barber_SetState(barber, BARBER_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov053_02261230, Barber_UpdateTurnBack)

/* func_ov053_02261260 (state 4's entry): a turn (priority 1) to its home angle. 1. */
int Barber_EnterTurnBack(Barber *barber)
{
    barber_turn(barber, barber->home_angle, data_020c80f8);
    return 1;
}
CLEAN_AS(func_ov053_02261260, Barber_EnterTurnBack)

/* func_ov053_0226129c (state 3's update): nothing. 1. */
int Barber_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov053_0226129c, Barber_UpdateTalked)

/* func_ov053_022612a0 (state 3's entry): nothing. 1. */
int Barber_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov053_022612a0, Barber_EnterTalked)

/* func_ov053_022612a4 (state 2's update): when the music's countdown comes to 1, the music's
 * priority 0xe is dropped. Once its action is idle, the screen's panels' request cleared, then
 * by the topic:
 * - seated (with or without a hat): it walks to the chair (state 7);
 * - cut, with a hat in the player's record: the topic hat back, and it walks route B (state 6);
 *   nothing more;
 * - else while this console's player sits on a spot: the player asked to step off it, and when
 *   that answers nonzero the event ends and state 3;
 * - claimed: main's entry record takes the scene's exit 0 (the player is put out), state 3;
 * - else the event ends, state 3.
 * When its state changed with the topic cut, the camera's mode is reset. 1.
 * QUIRK: the request clear gets 0x654 (an offset left in the register); the step off answers 0
 * always, so a player on a spot keeps it talked. */
int Barber_UpdateTalk(Barber *barber)
{
    if (Countdown_Tick8(&barber->music_countdown) == 1) {
        Music_DropPriority(BARBER_MUSIC_PRIORITY);
    }
    if (SceneAction_IsBusy(barber_action(barber))) {
        return 1;
    }
    int old = barber->state;
    ScreenPanels_ClearRequest(offsetof(Barber, state));
    if (barber_seated_topic(barber)) {
        Barber_SetState(barber, BARBER_STATE_TO_CUT);
    } else if (barber->talk.topic == BARBER_TOPIC_CUT && Barber_WearsHat(barber)) {
        BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_HAT_BACK);
        Barber_SetState(barber, BARBER_STATE_WALK_B);
        return 1;
    } else if (PlayerActorOps_InState(BARBER_PLAYER_SITS, BARBER_PLAYER_ACTOR)) {
        if (RoomPlayerActor_RequestSpotMove(0) != 0) {
            EventQueue_FinishObjectEvent(barber);
            Barber_SetState(barber, BARBER_STATE_TALKED);
        }
    } else if (barber->talk.topic == BARBER_TOPIC_CLAIMED) {
        if (!SceneAction_IsBusy(barber_action(barber))) {
            SceneExit_Take((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), 0);
            Barber_SetState(barber, BARBER_STATE_TALKED);
        }
    } else {
        EventQueue_FinishObjectEvent(barber);
        Barber_SetState(barber, BARBER_STATE_TALKED);
    }
    if (old != barber->state && barber->talk.topic == BARBER_TOPIC_CUT) {
        CameraControl_ResetMode();
    }
    return 1;
}
CLEAN_AS(func_ov053_022612a4, Barber_UpdateTalk)

/* func_ov053_022613b0 (state 2's entry): it looks at the player; the yaw to its talk's partner
 * (0 without one). With the topic cut the room's camera goes between the player and a point 2.0
 * above it, and the music's countdown starts at 31 frames. Its action turns it by that yaw and
 * talks, keeping the camera with the topics cut, leaving and claimed. 1. */
int Barber_EnterTalk(Barber *barber)
{
    barber_look(barber, BARBER_LOOK_PLAYER);
    int partner = SceneBase_MotionArg(&barber->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(barber->base, (u8 *) (uintptr_t) partner);
    }
    if (barber->talk.topic == BARBER_TOPIC_CUT) {
        Vec3 point = *(const Vec3 *) (const void *) barber_part(barber, BARBER_POSITION);
        point.y += BARBER_CAMERA_RISE;
        RoomCamera_SetModeBetween(&point);
        barber->music_countdown = BARBER_MUSIC_FRAMES;
    }
    u32 topic = barber->talk.topic;
    int keep_camera = topic == BARBER_TOPIC_CUT || topic == BARBER_TOPIC_LEAVING || topic == BARBER_TOPIC_CLAIMED;
    SceneAction_RequestTurnAndTalk(barber_action(barber), 0, yaw, keep_camera);
    return 1;
}
CLEAN_AS(func_ov053_022613b0, Barber_EnterTalk)

/* func_ov053_02261484 (state 1's update): it watches the player: seated (Barber_CheckSeated),
 * else leaving (Barber_CheckLeaving), else on the claimed object (Barber_CheckClaimed). 1. */
int Barber_UpdateStand(Barber *barber)
{
    if (Barber_CheckSeated(barber)) {
        return 1;
    }
    if (Barber_CheckLeaving(barber)) {
        return 1;
    }
    Barber_CheckClaimed(barber);
    return 1;
}
CLEAN_AS(func_ov053_02261484, Barber_UpdateStand)

/* func_ov053_022614b0 (state 1's entry): it stands (priority 1). 1. */
int Barber_EnterStand(Barber *barber)
{
    SceneMotion_Request(barber_motion(barber), BARBER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov053_022614b0, Barber_EnterStand)

/* func_ov053_022614e4 (state 0's update): an event of kind 6 asked for it. 1. */
int Barber_UpdateCall(Barber *barber)
{
    EventQueue_RequestKind6(barber, 0);
    return 1;
}
CLEAN_AS(func_ov053_022614e4, Barber_UpdateCall)

/* func_ov053_022614f8 (state 0's entry): the topic call. 1. */
int Barber_EnterCall(Barber *barber)
{
    BarberTalk_SetTopic(&barber->talk, BARBER_TOPIC_CALL);
    return 1;
}
CLEAN_AS(func_ov053_022614f8, Barber_EnterCall)

/* func_ov053_02261524: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 10 (the table is not bounded); the barber at a word-aligned address,
 * as every object of the game. */
void Barber_SetState(Barber *barber, int state)
{
    const BarberStep *step = &data_ov053_02261c64[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, barber);
    }
    if (taken != 0) {
        barber->state = state;
    }
}
CLEAN_AS(func_ov053_02261524, Barber_SetState)

/* func_ov053_02261568 (vtable slot 0x68, each frame): its state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: its state is 0 to 10. */
int Barber_Update(Barber *barber)
{
    const BarberStep *step = &data_ov053_02261c64[barber->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, barber);
}
CLEAN_AS(func_ov053_02261568, Barber_Update)

/* func_ov053_022615b4 (vtable slot 0x70): its model's file name. */
int Barber_ModelName(void)
{
    return (int) (uintptr_t) data_ov053_02261a44;
}
CLEAN_AS(func_ov053_022615b4, Barber_ModelName)

/* func_ov053_022615bc (vtable slot 0x6c): its texture's file name. */
int Barber_TextureName(void)
{
    return (int) (uintptr_t) data_ov053_02261a74;
}
CLEAN_AS(func_ov053_022615bc, Barber_TextureName)

/* func_ov053_022615c4 (vtable slot 0x00, its start): unless the special character refuses to
 * start: unlinked, the current map's object 0 is claimed (Barber_CheckClaimed watches it); its
 * home angle is 0, it is held (flag 2 at 0x4e8) and at route's first point. Linked it stands;
 * unlinked it calls the player when the previous scene was 29, else stands. Whether it
 * started. */
int Barber_Start(Barber *barber)
{
    if (SpecialSceneObject_Start(barber) == 0) {
        return 0;
    }
    NetSession *session = data_020ccf94;
    if (Session_IsLinked(session) == 0) {
        CollisionMap_Claim(0);
    }
    barber->home_angle = 0;
    *(u32 *) (void *) barber_part(barber, BARBER_FLAGS) |= BARBER_HELD;
    barber->waypoint = 0;
    if (Session_IsLinked(session) != 0) {
        Barber_SetState(barber, BARBER_STATE_STAND);
    } else if (SceneQuery_Previous() == BARBER_SCENE_CALL_FROM) {
        Barber_SetState(barber, BARBER_STATE_CALL);
    } else {
        Barber_SetState(barber, BARBER_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov053_022615c4, Barber_Start)

/* func_ov053_0226164c (vtable slot 0x04, its set-up): unless the special character refuses, its
 * talk scene becomes its scene and gets it as its owner; its collider is 0x100 wide and its
 * mover's pace 2 is set. Whether it was set up. */
int Barber_Init(Barber *barber)
{
    if (SpecialSceneObject_Init(barber) == 0) {
        return 0;
    }
    SceneObject_SetScene(barber->base, &barber->talk.base);
    BarberTalk_Begin(&barber->talk, barber);
    SceneObject_SetColliderSize(barber->base, BARBER_COLLIDER_SIZE);
    SceneMover_SetPace((SceneMover *) (void *) barber_part(barber, BARBER_MOVER), BARBER_PACE_INDEX, data_ov053_022617e0.speed,
                       data_ov053_022617e0.speed_up, data_ov053_022617e0.slow_down);
    return 1;
}
CLEAN_AS(func_ov053_0226164c, Barber_Init)

/* func_ov053_022616a8 (its record's create function, data_ov053_02261a5c): a zeroed block of
 * 0x720 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
void *Barber_Create(void)
{
    Barber *barber = (Barber *) Heap_AllocAuxZeroed(sizeof(Barber));
    if (barber == NULL) {
        return NULL;
    }
    u8 *object = barber->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) barber_part(barber, BARBER_PERSON) = BARBER_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) barber_part(barber, BARBER_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) barber_part(barber, BARBER_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) barber_part(barber, BARBER_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) barber_part(barber, BARBER_ANIM));
    SceneMover_Construct((SceneMover *) (void *) barber_part(barber, BARBER_MOVER));
    SceneProbe_Construct(barber_part(barber, BARBER_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) barber_part(barber, BARBER_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) barber_part(barber, BARBER_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) barber_part(barber, BARBER_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) barber_part(barber, BARBER_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) barber_part(barber, BARBER_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) barber_part(barber, BARBER_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) barber_part(barber, BARBER_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) barber_part(barber, BARBER_FOOTSTEPS));
    SceneMotion_Construct(barber_motion(barber));
    SceneAction_Construct(barber_action(barber));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) barber_part(barber, BARBER_HEAP));
    *(const u8 **) (void *) object = data_ov053_02261b98;
    BarberTalk_Construct(&barber->talk);
    return barber;
}
CLEAN_AS(func_ov053_022616a8, Barber_Create)
