/* The post office's clerks (post_clerk.h): her object's vtable slots, the counter places and
 * her states. */
#include "post_clerk.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/acre_map.h"
#include "main/actor.h"
#include "main/actor_table.h"
#include "main/block_020b220c.h"
#include "main/calendar.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/item_code.h"
#include "main/layered_model.h"
#include "main/link_global.h"
#include "main/main_random.h"
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
#include "main/scene_share.h"
#include "main/scene_standard_anims.h"
#include "main/scene_tables.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/session.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/start_kind.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "ov004/tti_npc.h"
#include "post_clerk_talk.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(PostClerkTalk, owner) == 0xb0 && offsetof(PostClerkTalk, menu) == 0xb4, "PostClerkTalk");
static_assert(offsetof(PostClerkTalk, step) == 0xb8 && offsetof(PostClerkTalk, letters_shown) == 0xbc, "PostClerkTalk");
static_assert(offsetof(PostClerkTalk, balance) == 0xc0 && offsetof(PostClerkTalk, town_amount) == 0xc4, "PostClerkTalk");
static_assert(offsetof(PostClerkTalk, search_frames) == 0xc8, "PostClerkTalk");
static_assert(offsetof(PostClerk, state) == 0x654 && offsetof(PostClerk, talk) == 0x658, "PostClerk");
static_assert(offsetof(PostClerk, home_angle) == 0x804 && offsetof(PostClerk, clerk) == 0x808, "PostClerk");
static_assert(offsetof(PostClerk, spot) == 0x80c && offsetof(PostClerk, act_countdown) == 0x810, "PostClerk");
static_assert(offsetof(PostClerk, stand_word) == 0x812 && offsetof(PostClerk, event_told) == 0x814, "PostClerk");
static_assert(sizeof(PostClerk) == 0x818, "the size PostClerk_Create allocates");
static_assert(sizeof(PostClerkStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define POST_CLERK_POSITION 0x5c        /* Vec3: her position */
#define POST_CLERK_ANGLE 0x8e           /* s16: where she faces */
#define POST_CLERK_PERSON 0xea          /* u16: her person code */
#define POST_CLERK_MODEL 0xec           /* LayeredModel */
#define POST_CLERK_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define POST_CLERK_FACE 0x2ac           /* SceneFace */
#define POST_CLERK_ANIM 0x334           /* SpeakerAnim */
#define POST_CLERK_MOVER 0x350          /* SceneMover */
#define POST_CLERK_PROBE 0x3a8          /* the probe */
#define POST_CLERK_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define POST_CLERK_LOOK 0x3b0           /* SceneLook */
#define POST_CLERK_TALK_STATE 0x418     /* SceneTalkState */
#define POST_CLERK_EFFECTS 0x420        /* ActEffects */
#define POST_CLERK_COLLIDER 0x49c       /* CollisionContacts */
#define POST_CLERK_CARRIER 0x4cc        /* FieldOwnedBody */
#define POST_CLERK_FLAGS 0x4e8          /* u32: the scene object's flags (2: held) */
#define POST_CLERK_EMITTER 0x514        /* SoundEmitterObject */
#define POST_CLERK_FOOTSTEPS 0x558      /* Footsteps */
#define POST_CLERK_PARTICIPANT 0x560    /* u8: whose system the last event came from */
#define POST_CLERK_MOTION 0x564         /* SceneMotion */
#define POST_CLERK_ACTION 0x618         /* SceneAction */
#define POST_CLERK_HEAP 0x640           /* PoolLink */

/* The part of an actor read: its position. */
#define POST_CLERK_ACTOR_POSITION 0x5c

#define POST_CLERK_NO_PERSON 0xfff1
#define POST_CLERK_HELD 2

/* The field actor of this console's player, and whom an event is for when it is for it. */
#define POST_CLERK_PLAYER_ACTOR 4
#define POST_CLERK_THIS_PLAYER 4

/* The codes of her vtable slot 0x4c (main's event_kinds.h). */
#define POST_CLERK_EVENT_TALK 0
#define POST_CLERK_EVENT_KIND6 1
#define POST_CLERK_EVENT_STARTS 3
#define POST_CLERK_EVENT_REFUSED 4
#define POST_CLERK_EVENT_ENDED 8

/* The vtable slot of her talk scene that resets it. */
#define POST_CLERK_TALK_SLOT_RESET 0x08

/* The motion kinds she asks for (scene_motion_request.h): a turn, a walk behind the counter
 * (at the rate 0x800) and her act; the word of the stand after her act. */
#define POST_CLERK_MOTION_TURN 3
#define POST_CLERK_MOTION_WALK 6
#define POST_CLERK_MOTION_ACT 10
#define POST_CLERK_WALK_RATE 0x800
#define POST_CLERK_WORD_BLEND 24

/* The frames before she acts on a day with a dated event: 100 and 20 times 0 to 4 more. The
 * dated events looked at are of kind 0 (talk_checks.h). */
#define POST_CLERK_ACT_FRAMES 100
#define POST_CLERK_ACT_FRAMES_STEP 20
#define POST_CLERK_ACT_FRAMES_STEPS 5
#define POST_CLERK_NO_COUNTDOWN 0xff
#define POST_CLERK_EVENT_KIND 0

/* The counter places. */
#define POST_CLERK_SPOTS 2

/* The player's walk to the counter: its acceleration. */
#define POST_CLERK_CALL_OVER_ACCEL 0x400

/* The current player's flag (player_record.h) of the sequence's first talk. */
#define POST_CLERK_FLAG_SEQUENCE_TALKED 9

/* The hours the clerk of the night serves: from 22 to 7. */
#define POST_CLERK_NIGHT_FROM 22
#define POST_CLERK_NIGHT_UNTIL 7

/* Her mover's pace (mode 2), her reach and the music of each clerk (Music_Add's priority and
 * values). */
#define POST_CLERK_PACE_MODE 2
#define POST_CLERK_PACE_SPEED 0x399
#define POST_CLERK_PACE_SPEED_UP 0xcc
#define POST_CLERK_PACE_SLOW_DOWN 0x133
#define POST_CLERK_REACH 0x5000
#define POST_CLERK_MUSIC_PRIORITY 0x11
#define POST_CLERK_MUSIC_DAY 0x55
#define POST_CLERK_MUSIC_NIGHT 0x56
#define POST_CLERK_MUSIC_VOLUME 0x7f

/* Her profile (main's profile table) and her face's animation while she takes the job's
 * talk. */
#define POST_CLERK_PROFILE 0x7a
#define POST_CLERK_FACE_JOB_ANIM 0xba

/* The leave: the exit to the town (scene 0) before building 0x5000, one tile on, with the
 * player's parameter 0x0ec00000, angle 0 and the change's bytes 2 and 2. */
#define POST_CLERK_LEAVE_SCENE 0
#define POST_CLERK_LEAVE_AHEAD 0x1000
#define POST_CLERK_LEAVE_PLAYER_PARAM 0x0ec00000
#define POST_CLERK_LEAVE_CHANGE_ARG 2
#define POST_CLERK_LEAVE_NEXT_ARG 2

/* The vtables of her class and of the classes it derives from. */
extern const u8 data_ov054_02263094[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Her model and texture file names, by clerk ("npc_sp/model/pga.nsbmd" and the like). */
extern const char *const data_ov054_02262df8[POST_CLERK_SPOTS];
extern const char *const data_ov054_02262d28[POST_CLERK_SPOTS];
/* The functions of her states (filled at start-up by __sinit_ov054_02262a70). */
extern PostClerkStep data_ov054_022632dc[POST_CLERK_STATES];
/* The persons of the two clerks (0xd006 and 0xd007), the turn way of her mover to each place
 * behind the counter, the player's places before the counter and hers behind them. */
extern const u16 data_ov054_02262990[2];
extern const u8 data_ov054_0226297c[POST_CLERK_SPOTS];
extern const Vec3 data_ov054_022629c8[POST_CLERK_SPOTS];
extern const Vec3 data_ov054_022629e0[POST_CLERK_SPOTS];
/* The word her motion requests carry. */
extern u16 data_020c80f8;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

static u8 *clerk_part(PostClerk *clerk, u32 offset)
{
    return clerk->base + offset;
}

static SceneMotion *clerk_motion(PostClerk *clerk)
{
    return (SceneMotion *) (void *) clerk_part(clerk, POST_CLERK_MOTION);
}

static SceneAction *clerk_action(PostClerk *clerk)
{
    return (SceneAction *) (void *) clerk_part(clerk, POST_CLERK_ACTION);
}

static SceneMover *clerk_mover(PostClerk *clerk)
{
    return (SceneMover *) (void *) clerk_part(clerk, POST_CLERK_MOVER);
}

static int clerk_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void clerk_set_slots(PostClerk *clerk, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(clerk->base, 1, owner, holder);
}

/* Her talk scene reset through its vtable slot 0x08, the talk's partner this console's
 * player's field actor. */
static void clerk_reset_talk(PostClerk *clerk)
{
    u32 vtable = *(const u32 *) (const void *) &clerk->talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + POST_CLERK_TALK_SLOT_RESET);
    ((void (*)(PostClerkTalk *))(uintptr_t) code)(&clerk->talk);
    SceneBase_SetMotionArg(&clerk->talk.base, SceneObject_ActorObject(clerk->base, POST_CLERK_PLAYER_ACTOR));
}

/* A motion of `kind` asked for (priority 1) toward (x, z) at `rate` and `angle`, with the
 * plain word. */
static void clerk_request(PostClerk *clerk, int kind, int x, int z, s16 rate, s16 angle)
{
    SceneMotion_Request(clerk_motion(clerk), kind, 1, x, z, rate, angle, 0, 0, data_020c80f8, 0);
}

/* Whether her motion is of `kind` and done. */
static int clerk_motion_done(PostClerk *clerk, int kind)
{
    return SceneMotion_Kind(clerk_motion(clerk)) == kind && SceneMotion_IsDone(clerk_motion(clerk));
}

/* The tile of `point`. */
static void clerk_tile(const Vec3 *point, int *x, int *z)
{
    *x = 0;
    *z = 0;
    Position_Tile(x, z, (const Position *) (const void *) point);
}

/* After the player moved to the other counter place: she walks there (state 3) and her mover
 * turns the way of that place. */
static void clerk_walk_to_spot(PostClerk *clerk)
{
    PostClerk_SetState(clerk, POST_CLERK_WALK);
    SceneMover_SetTurnWay(clerk_mover(clerk), data_ov054_0226297c[clerk->spot]);
}

/* func_ov054_02260420 (vtable slot 0x40): her talk scene's and the special character's
 * destructors; the object. */
PostClerk *PostClerk_Destruct(PostClerk *clerk)
{
    *(const u8 **) (void *) clerk->base = data_ov054_02263094;
    PostClerkTalk_Destruct(&clerk->talk);
    SpecialSceneObject_DestructBody(clerk);
    return clerk;
}
CLEAN_AS(func_ov054_02260420, PostClerk_Destruct)

/* func_ov054_02260448 (vtable slot 0x44): the same, then the object freed. */
PostClerk *PostClerk_DestructDelete(PostClerk *clerk)
{
    *(const u8 **) (void *) clerk->base = data_ov054_02263094;
    PostClerkTalk_Destruct(&clerk->talk);
    SpecialSceneObject_DestructBody(clerk);
    Heap_FreeAux(clerk);
    return clerk;
}
CLEAN_AS(func_ov054_02260448, PostClerk_DestructDelete)

/* func_ov054_02260474: whether the session is linked (the clerk is not looked at). */
int PostClerk_IsLinked(PostClerk *clerk)
{
    (void) clerk;
    return Session_IsLinked(data_020ccf94);
}
CLEAN_AS(func_ov054_02260474, PostClerk_IsLinked)

/* func_ov054_02260484: whether this system has a slot in the session (the clerk is not looked
 * at). */
u8 PostClerk_HasSessionSlot(PostClerk *clerk)
{
    (void) clerk;
    NetSession *session = data_020ccf94;
    return Session_IsSlotTaken(session, session->local_slot);
}
CLEAN_AS(func_ov054_02260484, PostClerk_HasSessionSlot)

/* func_ov054_02260498: whether an activity job may start: her face plays its animation 0xba,
 * overlay 4's character at the counter is idle (TtiNpc_IsIdle) and her talk waits for the
 * player (TALK_OBJECT_WAITING). */
int PostClerk_ReadyForJob(PostClerk *clerk)
{
    if (SceneFace_AnimB((SceneFace *) (void *) clerk_part(clerk, POST_CLERK_FACE)) != POST_CLERK_FACE_JOB_ANIM) {
        return 0;
    }
    if (TtiNpc_IsIdle() == 0) {
        return 0;
    }
    const TalkObject *talk = (const TalkObject *) (const void *) clerk->talk.base.talk;
    return talk->state == TALK_OBJECT_WAITING;
}
CLEAN_AS(func_ov054_02260498, PostClerk_ReadyForJob)

/* func_ov054_022604d0 (vtable slot 0x4c, told of an event about her by `participant`'s
 * system):
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused; this one's (with the object ours): owned and held by this system, paused;
 * - 1, the event of kind 6 she asked for: her talk reset with this console's player as the
 *   partner, and the player is called over (state 1);
 * - 0, the player talks to her: the participant kept; another system's (not this one's slot):
 *   owned and held by it, state 10; this one's (with the object ours): owned and held by this
 *   system, her talk reset with the partner, and she talks (state 4);
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none, she stands; else owned by none and held by this system, she
 *   awaits the session;
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, she stands. */
void PostClerk_OnEvent(PostClerk *clerk, int code, int participant)
{
    switch (code) {
        case POST_CLERK_EVENT_STARTS:
            *clerk_part(clerk, POST_CLERK_PARTICIPANT) = (u8) participant;
            if (participant != POST_CLERK_THIS_PLAYER) {
                clerk_set_slots(clerk, clerk_local_slot(), participant);
                PostClerk_SetState(clerk, POST_CLERK_PAUSED);
            } else if (SceneShare_IsOurs(clerk->base)) {
                int slot = clerk_local_slot();
                clerk_set_slots(clerk, slot, slot);
                PostClerk_SetState(clerk, POST_CLERK_PAUSED);
            }
            break;
        case POST_CLERK_EVENT_KIND6:
            clerk_reset_talk(clerk);
            PostClerk_SetState(clerk, POST_CLERK_CALL_OVER);
            break;
        case POST_CLERK_EVENT_TALK:
            *clerk_part(clerk, POST_CLERK_PARTICIPANT) = (u8) participant;
            if (participant != POST_CLERK_THIS_PLAYER && participant != clerk_local_slot()) {
                clerk_set_slots(clerk, participant, participant);
                PostClerk_SetState(clerk, POST_CLERK_OTHER);
            } else if (SceneShare_IsOurs(clerk->base)) {
                int slot = clerk_local_slot();
                clerk_set_slots(clerk, slot, slot);
                clerk_reset_talk(clerk);
                PostClerk_SetState(clerk, POST_CLERK_TALK);
            }
            break;
        case POST_CLERK_EVENT_ENDED:
            if (participant != POST_CLERK_THIS_PLAYER) {
                break;
            }
            if (LinkGlobal_HoldsScene()) {
                clerk_set_slots(clerk, clerk_local_slot(), SCENE_SHARE_NO_SLOT);
                PostClerk_SetState(clerk, POST_CLERK_STAND);
            } else {
                clerk_set_slots(clerk, SCENE_SHARE_NO_SLOT, clerk_local_slot());
                PostClerk_SetState(clerk, POST_CLERK_AWAIT);
            }
            break;
        case POST_CLERK_EVENT_REFUSED: {
            if (SceneShare_IsHeld(clerk->base) == 0 || SceneShare_IsOurs(clerk->base) == 0) {
                break;
            }
            int owner = SCENE_SHARE_NO_SLOT;
            int holder = SCENE_SHARE_NO_SLOT;
            if (SceneShare_ReadSlots(clerk->base, &owner, &holder) == 0) {
                break;
            }
            if (participant == POST_CLERK_THIS_PLAYER || participant == holder) {
                clerk_set_slots(clerk, clerk_local_slot(), SCENE_SHARE_NO_SLOT);
                PostClerk_SetState(clerk, POST_CLERK_STAND);
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov054_022604d0, PostClerk_OnEvent)

/* func_ov054_0226066c (vtable slot 0x48): whether `actor` may talk to her: her action idle, no
 * system holding her, she greets, stands or awaits the session (states 0, 2, 9), and the actor
 * stands on the tile of the counter place she serves. */
int PostClerk_MayTalk(PostClerk *clerk, u8 *actor)
{
    int actor_x;
    int actor_z;
    int spot_x;
    int spot_z;
    Vec3 at = *(const Vec3 *) (const void *) (actor + POST_CLERK_ACTOR_POSITION);
    clerk_tile(&at, &actor_x, &actor_z);
    Vec3 spot = data_ov054_022629c8[clerk->spot];
    clerk_tile(&spot, &spot_x, &spot_z);

    if (SceneAction_IsBusy(clerk_action(clerk)) || SceneShare_IsHeld(clerk->base)) {
        return 0;
    }
    if (clerk->state != POST_CLERK_STAND && clerk->state != POST_CLERK_GREET && clerk->state != POST_CLERK_AWAIT) {
        return 0;
    }
    return actor_x == spot_x && actor_z == spot_z;
}
CLEAN_AS(func_ov054_0226066c, PostClerk_MayTalk)

/* ---- Her states */

/* func_ov054_02261fc8 (state 11's update): nothing. 1. */
int PostClerk_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov054_02261fc8, PostClerk_UpdatePaused)

/* func_ov054_02261fcc (state 11's entry): nothing. 1. */
int PostClerk_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov054_02261fcc, PostClerk_EnterPaused)

/* func_ov054_02261fd0 (state 10's update, another system's player talked to her): once the
 * object is ours, the shared slots read show no owner and this system holds the scene, she is
 * owned by this system, held by none, and stands. 1. */
int PostClerk_UpdateOther(PostClerk *clerk)
{
    if (SceneShare_IsOurs(clerk->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(clerk->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            clerk_set_slots(clerk, clerk_local_slot(), SCENE_SHARE_NO_SLOT);
            PostClerk_SetState(clerk, POST_CLERK_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov054_02261fd0, PostClerk_UpdateOther)

/* func_ov054_02262028 (state 10's entry): nothing. 1. */
int PostClerk_EnterOther(void)
{
    return 1;
}
CLEAN_AS(func_ov054_02262028, PostClerk_EnterOther)

/* func_ov054_0226202c (state 9's update, awaiting the session): with the object ours, when the
 * shared slots read have this system as both owner and holder, they are set so, her talk is
 * reset with this console's player as the partner and she talks; else, when this system holds
 * the scene and no system holds her, she is owned by this system and stands. 1. */
int PostClerk_UpdateAwait(PostClerk *clerk)
{
    if (!SceneShare_IsOurs(clerk->base)) {
        return 1;
    }
    int owner = SCENE_SHARE_NO_SLOT;
    int holder = SCENE_SHARE_NO_SLOT;
    if (SceneShare_ReadSlots(clerk->base, &owner, &holder) && owner == clerk_local_slot() && owner == holder) {
        int slot = clerk_local_slot();
        clerk_set_slots(clerk, slot, slot);
        clerk_reset_talk(clerk);
        PostClerk_SetState(clerk, POST_CLERK_TALK);
        return 1;
    }
    if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
        clerk_set_slots(clerk, clerk_local_slot(), SCENE_SHARE_NO_SLOT);
        PostClerk_SetState(clerk, POST_CLERK_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov054_0226202c, PostClerk_UpdateAwait)

/* func_ov054_022620c8 (state 9's entry): nothing. 1. */
int PostClerk_EnterAwait(void)
{
    return 1;
}
CLEAN_AS(func_ov054_022620c8, PostClerk_EnterAwait)

/* func_ov054_022620cc (state 8's update): once talk 0 is gone (TALK_OBJECT_GONE), the flag
 * 0x021f4b1c is set and, with the town's map and its building 0x5000 found, main's entry record
 * is set to the town at the point before the building one tile on; then she has talked
 * (state 5). 1. */
int PostClerk_UpdateLeave(PostClerk *clerk)
{
    if (TalkObject_Get(0)->state != TALK_OBJECT_GONE) {
        return 1;
    }
    Block020b220c_SetFlag4b1c();
    unsigned int town = AcreMap_Town();
    if (town != 0) {
        Vec3 point;
        int tile_x;
        int tile_z;
        if (AcreMap_HasBuilding5000((int) town, (int) (uintptr_t) &point, (int) (uintptr_t) &tile_x,
                                    (int) (uintptr_t) &tile_z) != 0) {
            point.z += POST_CLERK_LEAVE_AHEAD;
            SceneExit_SetTo((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), POST_CLERK_LEAVE_SCENE, &point,
                            POST_CLERK_LEAVE_PLAYER_PARAM, 0, POST_CLERK_LEAVE_CHANGE_ARG, POST_CLERK_LEAVE_NEXT_ARG);
        }
    }
    PostClerk_SetState(clerk, POST_CLERK_TALKED);
    return 1;
}
CLEAN_AS(func_ov054_022620cc, PostClerk_UpdateLeave)

/* func_ov054_02262130 (state 8's entry): nothing. 1. */
int PostClerk_EnterLeave(void)
{
    return 1;
}
CLEAN_AS(func_ov054_02262130, PostClerk_EnterLeave)

/* func_ov054_02262134 (state 7's update): once her act is done her next stand blends in (word
 * 24) and she stands. 1.
 * QUIRK: whether the session is linked and this console's player's start position are asked
 * for and not used. */
int PostClerk_UpdateAct(PostClerk *clerk)
{
    PostClerk_IsLinked(clerk);
    (void) PlayerActorOps_StartPosition(POST_CLERK_PLAYER_ACTOR);
    if (clerk_motion_done(clerk, POST_CLERK_MOTION_ACT)) {
        clerk->stand_word = POST_CLERK_WORD_BLEND;
        PostClerk_SetState(clerk, POST_CLERK_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov054_02262134, PostClerk_UpdateAct)

/* func_ov054_02262188 (state 7's entry): her act (motion kind 10, priority 1). 1. */
int PostClerk_EnterAct(PostClerk *clerk)
{
    clerk_request(clerk, POST_CLERK_MOTION_ACT, 0, 0, 0, 0);
    return 1;
}
CLEAN_AS(func_ov054_02262188, PostClerk_EnterAct)

/* func_ov054_022621bc (state 6's update): when the player moved to the other counter place she
 * walks there (state 3); else once her turn is done she stands. 1.
 * QUIRK: whether the session is linked is asked for and not used. */
int PostClerk_UpdateTurn(PostClerk *clerk)
{
    PostClerk_IsLinked(clerk);
    if (PostClerk_FindSpot(clerk)) {
        PostClerk_SetState(clerk, POST_CLERK_WALK);
        return 1;
    }
    if (clerk_motion_done(clerk, POST_CLERK_MOTION_TURN)) {
        PostClerk_SetState(clerk, POST_CLERK_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov054_022621bc, PostClerk_UpdateTurn)

/* func_ov054_02262208 (state 6's entry): her mover's turn way 0 and a turn (priority 1) to her
 * home angle. 1. */
int PostClerk_EnterTurn(PostClerk *clerk)
{
    SceneMover_SetTurnWay(clerk_mover(clerk), 0);
    clerk_request(clerk, POST_CLERK_MOTION_TURN, 0, 0, 0, clerk->home_angle);
    return 1;
}
CLEAN_AS(func_ov054_02262208, PostClerk_EnterTurn)

/* func_ov054_02262258 (state 5's update): nothing. 1. */
int PostClerk_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov054_02262258, PostClerk_UpdateTalked)

/* func_ov054_0226225c (state 5's entry): nothing. 1. */
int PostClerk_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov054_0226225c, PostClerk_EnterTalked)

/* func_ov054_02262260 (state 4's update): once her action is idle her event ends and she has
 * talked. 1. */
int PostClerk_UpdateTalk(PostClerk *clerk)
{
    if (!SceneAction_IsBusy(clerk_action(clerk))) {
        EventQueue_FinishObjectEvent(clerk);
        PostClerk_SetState(clerk, POST_CLERK_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov054_02262260, PostClerk_UpdateTalk)

/* func_ov054_0226228c (state 4's entry): her action talks (its motion reset). 1. */
int PostClerk_EnterTalk(PostClerk *clerk)
{
    SceneAction_RequestTalk(clerk_action(clerk), 1, 0);
    return 1;
}
CLEAN_AS(func_ov054_0226228c, PostClerk_EnterTalk)

/* func_ov054_022622a8 (state 3's update): when the player moved to the other counter place
 * again she walks there anew; else once her walk is done she turns (state 6). 1.
 * QUIRK: whether the session is linked is asked for and not used. */
int PostClerk_UpdateWalk(PostClerk *clerk)
{
    PostClerk_IsLinked(clerk);
    if (PostClerk_FindSpot(clerk)) {
        clerk_walk_to_spot(clerk);
        return 1;
    }
    if (clerk_motion_done(clerk, POST_CLERK_MOTION_WALK)) {
        PostClerk_SetState(clerk, POST_CLERK_TURN);
    }
    return 1;
}
CLEAN_AS(func_ov054_022622a8, PostClerk_UpdateWalk)

/* func_ov054_02262310 (state 3's entry): her walk (motion kind 6, priority 1, rate 0x800) to
 * her place behind the counter place she serves. 1. */
int PostClerk_EnterWalk(PostClerk *clerk)
{
    const Vec3 *place = &data_ov054_022629e0[clerk->spot];
    clerk_request(clerk, POST_CLERK_MOTION_WALK, place->x, place->z, POST_CLERK_WALK_RATE, 0);
    return 1;
}
CLEAN_AS(func_ov054_02262310, PostClerk_EnterWalk)

/* func_ov054_02262368 (state 2's update): unlinked, when the player moved to the other counter
 * place she walks there; and once her countdown to act (when there is one) runs out, she acts
 * (state 7). Linked, nothing. 1. */
int PostClerk_UpdateStand(PostClerk *clerk)
{
    if (PostClerk_IsLinked(clerk)) {
        return 1;
    }
    if (PostClerk_FindSpot(clerk)) {
        clerk_walk_to_spot(clerk);
    }
    if (clerk->act_countdown != POST_CLERK_NO_COUNTDOWN && Countdown_Tick16(&clerk->act_countdown) == 0) {
        PostClerk_SetState(clerk, POST_CLERK_ACT);
    }
    return 1;
}
CLEAN_AS(func_ov054_02262368, PostClerk_UpdateStand)

/* func_ov054_022623c8 (state 2's entry): she stands (priority 1, with her stand's word); with
 * today's dated event of kind 0 not told yet in this visit she acts after 100 to 180 frames
 * (MainRandom_Below), else not; her next stand's word is the plain one. 1. */
int PostClerk_EnterStand(PostClerk *clerk)
{
    u8 event;
    SceneMotion_RequestStand(clerk_motion(clerk), 1, clerk->stand_word);
    clerk->act_countdown = POST_CLERK_NO_COUNTDOWN;
    if (clerk->event_told == 0 && TalkChecks_TodaysEventOfKind((int) (uintptr_t) clerk, &event, POST_CLERK_EVENT_KIND)) {
        clerk->act_countdown =
            (u16) (MainRandom_Below(POST_CLERK_ACT_FRAMES_STEPS) * POST_CLERK_ACT_FRAMES_STEP + POST_CLERK_ACT_FRAMES);
    }
    clerk->stand_word = data_020c80f8;
    return 1;
}
CLEAN_AS(func_ov054_022623c8, PostClerk_EnterStand)

/* func_ov054_02262430 (state 1's update): once this console's player has stopped walking, she
 * talks (state 4). 1. */
int PostClerk_UpdateCallOver(PostClerk *clerk)
{
    if (PlayerActorOps_IsBusy(POST_CLERK_PLAYER_ACTOR) == 0) {
        PostClerk_SetState(clerk, POST_CLERK_TALK);
    }
    return 1;
}
CLEAN_AS(func_ov054_02262430, PostClerk_UpdateCallOver)

/* func_ov054_02262450 (state 1's entry): this console's player walks to the first counter
 * place (a copy of it is handed on). 1. */
int PostClerk_EnterCallOver(void)
{
    Vec3 spot = data_ov054_022629c8[0];
    PlayerActorOps_MoveTo(&spot, POST_CLERK_CALL_OVER_ACCEL, POST_CLERK_PLAYER_ACTOR);
    return 1;
}
CLEAN_AS(func_ov054_02262450, PostClerk_EnterCallOver)

/* func_ov054_0226247c (state 0's update): an event of kind 6 asked for her. 1. */
int PostClerk_UpdateGreet(PostClerk *clerk)
{
    EventQueue_RequestKind6(clerk, 0);
    return 1;
}
CLEAN_AS(func_ov054_0226247c, PostClerk_UpdateGreet)

/* func_ov054_02262490 (state 0's entry): nothing. 1. */
int PostClerk_EnterGreet(void)
{
    return 1;
}
CLEAN_AS(func_ov054_02262490, PostClerk_EnterGreet)

/* func_ov054_02262494: the counter place whose tile this console's player's start position is
 * on becomes the one she serves (the first that matches; unchanged when none does). Whether it
 * changed. */
int PostClerk_FindSpot(PostClerk *clerk)
{
    Vec3 player = *PlayerActorOps_StartPosition(POST_CLERK_PLAYER_ACTOR);
    int player_x;
    int player_z;
    clerk_tile(&player, &player_x, &player_z);

    u32 before = clerk->spot;
    for (int i = 0; i < POST_CLERK_SPOTS; i++) {
        int spot_x;
        int spot_z;
        Vec3 spot = data_ov054_022629c8[i];
        clerk_tile(&spot, &spot_x, &spot_z);
        if (player_x == spot_x && player_z == spot_z) {
            clerk->spot = (u32) i;
            break;
        }
    }
    return before != clerk->spot;
}
CLEAN_AS(func_ov054_02262494, PostClerk_FindSpot)

/* func_ov054_02262528: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 11 (the table is not bounded). */
void PostClerk_SetState(PostClerk *clerk, int state)
{
    const PostClerkStep *step = &data_ov054_022632dc[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, clerk);
    }
    if (taken != 0) {
        clerk->state = state;
    }
}
CLEAN_AS(func_ov054_02262528, PostClerk_SetState)

/* func_ov054_0226256c (vtable slot 0x68, each frame): her state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: her state is 0 to 11. */
int PostClerk_Update(PostClerk *clerk)
{
    const PostClerkStep *step = &data_ov054_022632dc[clerk->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, clerk);
}
CLEAN_AS(func_ov054_0226256c, PostClerk_Update)

/* func_ov054_022625b8 (vtable slot 0x70): her model's file name, by clerk.
 * REQUIRES: PostClerk.clerk is 0 or 1. */
unsigned int PostClerk_ModelName(PostClerk *clerk)
{
    return (unsigned int) (uintptr_t) data_ov054_02262df8[clerk->clerk];
}
CLEAN_AS(func_ov054_022625b8, PostClerk_ModelName)

/* func_ov054_022625cc (vtable slot 0x6c): her texture's file name, by clerk.
 * REQUIRES: PostClerk.clerk is 0 or 1. */
int PostClerk_TextureName(PostClerk *clerk)
{
    return (int) (uintptr_t) data_ov054_02262d28[clerk->clerk];
}
CLEAN_AS(func_ov054_022625cc, PostClerk_TextureName)

/* func_ov054_022625e0 (vtable slot 0x0c, her leaving): unless the special character refuses to
 * leave, her music goes (0x55 for the clerk of the day; 0x56 for the clerk of the night, when
 * unlinked). Whether she left. */
int PostClerk_Leave(PostClerk *clerk)
{
    if (SpecialSceneObject_Leave(clerk) == 0) {
        return 0;
    }
    if (clerk->clerk == POST_CLERK_DAY) {
        Music_DropMusic(POST_CLERK_MUSIC_DAY);
    } else if (clerk->clerk == POST_CLERK_NIGHT && !PostClerk_IsLinked(clerk)) {
        Music_DropMusic(POST_CLERK_MUSIC_NIGHT);
    }
    return 1;
}
CLEAN_AS(func_ov054_022625e0, PostClerk_Leave)

/* func_ov054_02262620 (vtable slot 0x00, her start): unless the special character refuses to
 * start: linked she stands when this system holds the scene, else awaits the session; unlinked
 * she greets while a game is being started anew and the current player has not had its first
 * talk (flag 9), else stands. Her home angle is the angle she faces, she is held (flag 2 at
 * 0x4e8) and her music starts (0x55 for the clerk of the day; 0x56 for the clerk of the night,
 * when unlinked). Whether she started. */
int PostClerk_Start(PostClerk *clerk)
{
    if (SpecialSceneObject_Start(clerk) == 0) {
        return 0;
    }
    u8 *record = PlayerRecords_Current();
    if (PostClerk_IsLinked(clerk)) {
        if (LinkGlobal_HoldsScene()) {
            PostClerk_SetState(clerk, POST_CLERK_STAND);
        } else {
            PostClerk_SetState(clerk, POST_CLERK_AWAIT);
        }
    } else if (StartKind_IsSet() != 0 && PlayerRecord_TestFlag(record, POST_CLERK_FLAG_SEQUENCE_TALKED) == 0) {
        PostClerk_SetState(clerk, POST_CLERK_GREET);
    } else {
        PostClerk_SetState(clerk, POST_CLERK_STAND);
    }

    clerk->home_angle = *(const s16 *) (const void *) clerk_part(clerk, POST_CLERK_ANGLE);
    *(u32 *) (void *) clerk_part(clerk, POST_CLERK_FLAGS) |= POST_CLERK_HELD;

    if (clerk->clerk == POST_CLERK_DAY) {
        Music_Add(POST_CLERK_MUSIC_PRIORITY, POST_CLERK_MUSIC_DAY, POST_CLERK_MUSIC_VOLUME, 0);
    } else if (clerk->clerk == POST_CLERK_NIGHT && !PostClerk_IsLinked(clerk)) {
        Music_Add(POST_CLERK_MUSIC_PRIORITY, POST_CLERK_MUSIC_NIGHT, POST_CLERK_MUSIC_VOLUME, 0);
    }
    return 1;
}
CLEAN_AS(func_ov054_02262620, PostClerk_Start)

/* Whether her person is the clerk of the day's (0xd006): for a code with a variant, whether
 * its item is that code's item. */
static int clerk_is_day_person(PostClerk *clerk)
{
    u16 *person = (u16 *) (void *) clerk_part(clerk, POST_CLERK_PERSON);
    if (ItemCode_HasVariant(person)) {
        u16 day = data_ov054_02262990[POST_CLERK_DAY];
        int own = ItemCode_VariantItem(person);
        return own == ItemCode_VariantItem(&day);
    }
    return *person == data_ov054_02262990[POST_CLERK_DAY];
}

/* func_ov054_022626e0 (vtable slot 0x04, her set-up): unless the special character refuses,
 * her talk scene becomes her scene and gets her as its owner.
 * - Linked: made with the person 0xd006 she is the clerk of the day, serves the second counter
 *   place from the place behind it, and makes the other clerk (profile 0x7a, person 0xd007) at
 *   the place behind the first, angle 0, with her as the parent; else she is the clerk of the
 *   night at the first place.
 * - Unlinked: the clerk of the night from 22 to 7 o'clock (Calendar_Now) unless a game is being
 *   started anew, else the clerk of the day; her mover's pace (mode 2) is set, and her person
 *   is that clerk's.
 * Her reach is 5.0 and her stand's word the plain one. Whether she was set up. */
int PostClerk_Init(PostClerk *clerk)
{
    if (SpecialSceneObject_Init(clerk) == 0) {
        return 0;
    }
    SceneObject_SetScene(clerk->base, &clerk->talk.base);
    PostClerkTalk_Begin(&clerk->talk, clerk);

    Vec3 *position = (Vec3 *) (void *) clerk_part(clerk, POST_CLERK_POSITION);
    if (PostClerk_IsLinked(clerk)) {
        if (clerk_is_day_person(clerk)) {
            clerk->clerk = POST_CLERK_DAY;
            clerk->spot = 1;
            *position = data_ov054_022629e0[1];
            s16 angle[3] = {0, 0, 0};
            Vec3 other = data_ov054_022629e0[0];
            Actor_Spawn(POST_CLERK_PROFILE, data_ov054_02262990[POST_CLERK_NIGHT], &other, angle, clerk);
        } else {
            clerk->clerk = POST_CLERK_NIGHT;
            clerk->spot = 0;
            *position = data_ov054_022629e0[0];
        }
    } else {
        Time now;
        Calendar_Now(&now);
        u8 hour = now.hour;
        clerk->clerk = POST_CLERK_DAY;
        if (StartKind_IsSet() == 0 && (hour >= POST_CLERK_NIGHT_FROM || hour < POST_CLERK_NIGHT_UNTIL)) {
            clerk->clerk = POST_CLERK_NIGHT;
        }
        SceneMover_SetPace(clerk_mover(clerk), POST_CLERK_PACE_MODE, POST_CLERK_PACE_SPEED, POST_CLERK_PACE_SPEED_UP,
                           POST_CLERK_PACE_SLOW_DOWN);
        u16 person = data_ov054_02262990[clerk->clerk];
        SceneObject_SetPerson(clerk->base, &person);
        *(u16 *) (void *) clerk_part(clerk, POST_CLERK_PERSON) = data_ov054_02262990[clerk->clerk];
    }
    SceneObjectBase_SetReach((SceneObjectBase *) (void *) clerk->base, POST_CLERK_REACH);
    clerk->stand_word = data_020c80f8;
    return 1;
}
CLEAN_AS(func_ov054_022626e0, PostClerk_Init)

/* func_ov054_0226285c (her record's create function, data_ov054_02262f94): a zeroed block of
 * 0x818 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then her class's vtable and her talk scene. Null when there
 * is no room. */
PostClerk *PostClerk_Create(void)
{
    PostClerk *clerk = (PostClerk *) Heap_AllocAuxZeroed(sizeof(PostClerk));
    if (clerk == NULL) {
        return NULL;
    }
    u8 *object = clerk->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) clerk_part(clerk, POST_CLERK_PERSON) = POST_CLERK_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) clerk_part(clerk, POST_CLERK_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) clerk_part(clerk, POST_CLERK_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) clerk_part(clerk, POST_CLERK_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) clerk_part(clerk, POST_CLERK_ANIM));
    SceneMover_Construct(clerk_mover(clerk));
    SceneProbe_Construct(clerk_part(clerk, POST_CLERK_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) clerk_part(clerk, POST_CLERK_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) clerk_part(clerk, POST_CLERK_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) clerk_part(clerk, POST_CLERK_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) clerk_part(clerk, POST_CLERK_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) clerk_part(clerk, POST_CLERK_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) clerk_part(clerk, POST_CLERK_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) clerk_part(clerk, POST_CLERK_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) clerk_part(clerk, POST_CLERK_FOOTSTEPS));
    SceneMotion_Construct(clerk_motion(clerk));
    SceneAction_Construct(clerk_action(clerk));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) clerk_part(clerk, POST_CLERK_HEAP));
    *(const u8 **) (void *) object = data_ov054_02263094;
    PostClerkTalk_Construct(&clerk->talk);
    return clerk;
}
CLEAN_AS(func_ov054_0226285c, PostClerk_Create)
