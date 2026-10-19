/* The cafe's master (cafe_master.h). */
#include "cafe_master.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "cafe_props.h"
#include "clean.h"
#include "main/actor.h"
#include "main/camera_control.h"
#include "main/event_queue.h"
#include "main/frame_ctrl.h"
#include "main/game_variables.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/message_receiver.h"
#include "main/model_object.h"
#include "main/music_queue.h"
#include "main/player_actor_ops.h"
#include "main/player_field_2416.h"
#include "main/player_id.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_bells.h"
#include "main/scene_object.h"
#include "main/scene_object_members.h"
#include "main/scene_probe.h"
#include "main/scene_share.h"
#include "main/scene_value_3aa.h"
#include "main/screen_panels.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/sound_emitter.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/start_kind.h"
#include "main/talk_answers.h"
#include "main/talk_checks.h"
#include "main/talk_object.h"
#include "ov068/cafe_guest.h"
#include "ov004/room_player_actor.h"

/* Its parts read here. */
#define CAFE_MASTER_MODEL_FRAME 0x190 /* u32: its model's animation frame, 20.12 */
#define CAFE_MASTER_ANIM 0x334        /* SpeakerAnim */
#define CAFE_MASTER_TALK 0x658        /* its talk scene */
#define CAFE_MASTER_MATRIX_718 0x718  /* Mtx43 */
#define CAFE_MASTER_MATRIX_748 0x748  /* Mtx43 */

/* The vtable of its class. */
extern const u8 data_ov004_022546e0[];
/* The master while one is started. */
extern u8 *data_ov004_022580dc;

/* The address `offset` bytes into the master; with no master the offset itself, as the ROM
 * computes it. */
static uintptr_t cm_at(u32 offset)
{
    return (uintptr_t) data_ov004_022580dc + offset;
}

/* func_ov004_02223654 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
u8 *CafeMaster_Destroy(u8 *master)
{
    *(const u8 **) (void *) master = data_ov004_022546e0;
    CafeMasterTalk_Destroy((CafeMasterTalk *) (void *) (master + CAFE_MASTER_TALK));
    SpecialSceneObject_DestructBody(master);
    return master;
}
CLEAN_AS(func_ov004_02223654, CafeMaster_Destroy)

/* func_ov004_0222367c (vtable slot 0x44): the same, then the object freed. */
u8 *CafeMaster_Delete(u8 *master)
{
    *(const u8 **) (void *) master = data_ov004_022546e0;
    CafeMasterTalk_Destroy((CafeMasterTalk *) (void *) (master + CAFE_MASTER_TALK));
    SpecialSceneObject_DestructBody(master);
    Heap_FreeAux(master);
    return master;
}
CLEAN_AS(func_ov004_0222367c, CafeMaster_Delete)

/* func_ov004_022236a8: the number of the animation the master plays (SpeakerAnim_Number,
 * 0). */
int CafeMaster_AnimNumber(void)
{
    return SpeakerAnim_Number((SpeakerAnim *) cm_at(CAFE_MASTER_ANIM), 0);
}
CLEAN_AS(func_ov004_022236a8, CafeMaster_AnimNumber)

/* func_ov004_022236c4: the whole frame of the master's animation.
 * REQUIRES: a master is started (the ROM reads through the pointer unchecked). */
u16 CafeMaster_AnimFrame(void)
{
    u32 frame = *(const u32 *) cm_at(CAFE_MASTER_MODEL_FRAME);
    return (u16) (frame >> 12);
}
CLEAN_AS(func_ov004_022236c4, CafeMaster_AnimFrame)

/* func_ov004_022236dc: the master's matrix at 0x748. */
Mtx43 *CafeMaster_Matrix748(void)
{
    return (Mtx43 *) cm_at(CAFE_MASTER_MATRIX_748);
}
CLEAN_AS(func_ov004_022236dc, CafeMaster_Matrix748)

/* func_ov004_022236f0: the master's matrix at 0x718. */
Mtx43 *CafeMaster_Matrix718(void)
{
    return (Mtx43 *) cm_at(CAFE_MASTER_MATRIX_718);
}
CLEAN_AS(func_ov004_022236f0, CafeMaster_Matrix718)

/* ---- The rest of the class: its states, its talk scene and its coffee */

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(CafeMasterTalk, sequence) == 0xb0, "sequence");
static_assert(offsetof(CafeMasterTalk, master) == 0xb4, "master");
static_assert(offsetof(CafeMasterTalk, step) == 0xb8, "step");
static_assert(offsetof(CafeMasterTalk, saw_message_2d) == 0xb9, "message 0x2d seen");
static_assert(sizeof(CafeMasterTalk) == 0xbc, "its talk scene");
static_assert(sizeof(CafeMasterLine) == 8, "a line");
static_assert(sizeof(CafeMasterStep) == 0x10, "a state's functions");
static_assert(sizeof(CafeMasterTalkStep) == 0xc, "a sequence's function");
static_assert(offsetof(CafeMaster, state) == 0x654, "state");
static_assert(offsetof(CafeMaster, talk) == CAFE_MASTER_TALK, "talk scene");
static_assert(offsetof(CafeMaster, home_yaw) == 0x714, "home yaw");
static_assert(offsetof(CafeMaster, matrix_718) == CAFE_MASTER_MATRIX_718, "matrix 0x718");
static_assert(offsetof(CafeMaster, matrix_748) == CAFE_MASTER_MATRIX_748, "matrix 0x748");
static_assert(offsetof(CafeMaster, look_timer) == 0x778, "look timer");
static_assert(offsetof(CafeMaster, talk_frames) == 0x77c, "talk frames");
static_assert(offsetof(CafeMaster, on_beat) == 0x77e, "on beat");
static_assert(sizeof(CafeMaster) == 0x780, "the size func_ov004_02224c68 allocates");
static_assert(0xec + offsetof(LayeredModel, base_frames) + offsetof(FrameCtrl, frame) == CAFE_MASTER_MODEL_FRAME,
              "model frame");

/* The other parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define CAFE_MASTER_YAW 0x8e             /* s16: where he faces */
#define CAFE_MASTER_PERSON 0xea          /* u16: his person code */
#define CAFE_MASTER_MODEL 0xec           /* LayeredModel */
#define CAFE_MASTER_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define CAFE_MASTER_FACE 0x2ac           /* SceneFace */
#define CAFE_MASTER_MOVER 0x350          /* SceneMover */
#define CAFE_MASTER_PROBE 0x3a8
#define CAFE_MASTER_VALUE_3AA 0x3aa   /* SceneValue3aa */
#define CAFE_MASTER_LOOK 0x3b0        /* SceneLook */
#define CAFE_MASTER_TALK_STATE 0x418  /* SceneTalkState */
#define CAFE_MASTER_EFFECTS 0x420     /* ActEffects */
#define CAFE_MASTER_COLLIDER 0x49c    /* CollisionContacts */
#define CAFE_MASTER_CARRIER 0x4cc     /* FieldOwnedBody */
#define CAFE_MASTER_HELD_FLAGS 0x4e8  /* u32: the scene object's flags (2: held) */
#define CAFE_MASTER_EMITTER 0x514     /* SoundEmitterObject */
#define CAFE_MASTER_FOOTSTEPS 0x558   /* Footsteps */
#define CAFE_MASTER_PARTICIPANT 0x560 /* u8: whose system the last event came from */
#define CAFE_MASTER_MOTION 0x564      /* SceneMotion */
#define CAFE_MASTER_ACTION 0x618      /* SceneAction */
#define CAFE_MASTER_HEAP 0x640        /* PoolLink */

#define CAFE_MASTER_NO_PERSON 0xfff1
#define CAFE_MASTER_HELD 2

/* The field actor of this console's player, and the field states of it he waits for (main's
 * player_actor_ops.h): in the first an event about him is asked for, in the second he
 * talks. */
#define CAFE_MASTER_PLAYER_ACTOR 4
#define CAFE_MASTER_PLAYER_CALLS 0x27
#define CAFE_MASTER_PLAYER_SEATED 0x28

/* The codes of his vtable slot 0x4c (main's event_kinds.h). */
#define CAFE_MASTER_EVENT_TALK 0
#define CAFE_MASTER_EVENT_CALLED 1 /* the event asked for in state 0 */
#define CAFE_MASTER_EVENT_STARTS 3
#define CAFE_MASTER_EVENT_REFUSED 4
#define CAFE_MASTER_EVENT_ENDED 8

/* The vtable slot of his talk scene his talks call first (SceneBase_Reset). */
#define CAFE_MASTER_TALK_SLOT_08 0x08

/* The looks he asks for (SceneLook_Request): straight ahead and the player. */
#define CAFE_MASTER_LOOK_AHEAD 0
#define CAFE_MASTER_LOOK_PLAYER 1
/* How far he looks aside (the look's yaw) before he looks ahead again, and how late. */
#define CAFE_MASTER_LOOK_ASIDE 0x2000
#define CAFE_MASTER_LOOK_BACK_FRAMES 20

/* The motion kinds he asks for (scene_motion_request.h). */
#define CAFE_MASTER_MOTION_STAND 0
#define CAFE_MASTER_MOTION_TO_POINT 2
#define CAFE_MASTER_MOTION_TURN 3

/* The game variable (bank 0) that, when set, makes him act as when linked. */
#define CAFE_MASTER_VARIABLE 0x4a

/* His collider, reach, pace (SceneMover_SetPace, mode 2) and animations. */
#define CAFE_MASTER_COLLIDER_SIZE 0x100
#define CAFE_MASTER_REACH 0x5000
#define CAFE_MASTER_PACE_MODE 2
#define CAFE_MASTER_PACE_SPEED 0x166
#define CAFE_MASTER_PACE_SPEED_UP 0xcc
#define CAFE_MASTER_PACE_SLOW_DOWN 0x133
#define CAFE_MASTER_ANIM_F2 0xf2
#define CAFE_MASTER_ANIM_F3 0xf3
#define CAFE_MASTER_ANIM_F4 0xf4
#define CAFE_MASTER_ANIM_F5 0xf5
#define CAFE_MASTER_ANIM_F6 0xf6
#define CAFE_MASTER_ANIM_F7 0xf7
#define CAFE_MASTER_ANIM_F8 0xf8

/* The joints of his model kept at each draw (CafeMaster.matrix_718 and matrix_748). */
#define CAFE_MASTER_JOINT_718 0xe
#define CAFE_MASTER_JOINT_748 0xb

/* The cafe's guest (ov068's cafe_guest.h), made at his start: its actor profile and the
 * argument it is made with; its kind that plays music. */
#define CAFE_MASTER_GUEST_PROFILE 0x66
#define CAFE_MASTER_GUEST_ARG 0xd01d
#define CAFE_MASTER_GUEST_MUSICIAN 7

/* The musics whose beat his model follows, and the frames of the blend into it. */
#define CAFE_MASTER_BEAT_MUSIC_FIRST 0x63
#define CAFE_MASTER_BEAT_MUSIC_LAST 0xab
#define CAFE_MASTER_BEAT_BLEND_FRAMES 10
#define CAFE_MASTER_SOUND_STOPPED 1 /* byte 3 of the sound's entry while it does not play */

/* The current player's daily bits: the first talk of the day, a coffee drunk today. */
#define CAFE_MASTER_DAILY_FIRST_TALK 0x16
#define CAFE_MASTER_DAILY_COFFEE 0x17

/* The price of a coffee in bells. */
#define CAFE_MASTER_COFFEE_PRICE 200

/* His message files (data_ov004_02254594): "sp_npc_cafe" and "sp_etc_sequence4" (a game
 * being started anew). */
#define CAFE_MASTER_FILE_PLAIN 0
#define CAFE_MASTER_FILE_NEW_START 1
#define CAFE_MASTER_FILES 2

/* His messages, of "sp_npc_cafe" but the first; most are the first of a group picked from by
 * a quarter of the player's coffees (cm_level) or at random. */
#define CAFE_MASTER_LINE_NEW_START 0x1f /* of "sp_etc_sequence4" */
#define CAFE_MASTER_LINE_LINKED 0x55    /* 0x55 to 0x57 */
#define CAFE_MASTER_LINE_MUSICIAN 0x58  /* the guest that plays music is in */
#define CAFE_MASTER_LINE_STANDING 0x49  /* the player not seated, again on a day */
#define CAFE_MASTER_LINE_SEATED 0x14    /* the offer of a coffee: 0x14 to 0x17 */
#define CAFE_MASTER_LINE_DECLINED 0x18  /* the offer declined: 0x18 to 0x1b */
#define CAFE_MASTER_LINE_SERVED 0x1c    /* paid: 0x1c to 0x23, two by level */
#define CAFE_MASTER_LINE_SERVED_LAST 0x23
#define CAFE_MASTER_LINE_NO_BELLS 0x2f
#define CAFE_MASTER_LINE_ASK 0x24       /* the coffee made: 0x24 to 0x27 */
#define CAFE_MASTER_LINE_ANSWER_NO 0x28 /* to that line: 0x28 to 0x2b */
#define CAFE_MASTER_LINE_ASK_LAST 0x2b
#define CAFE_MASTER_LINE_REGULAR 0x2c /* now and then, from 5 coffees, once paid */
#define CAFE_MASTER_LINE_2D 0x2d
#define CAFE_MASTER_LINE_2E 0x2e
#define CAFE_MASTER_LINE_DRUNK_2D 0x30 /* drunk after message 0x2d; else 0x31 to 0x3b */
#define CAFE_MASTER_LINE_DRUNK 0x31
#define CAFE_MASTER_LINE_DRUNK_RANGE 11
#define CAFE_MASTER_LINE_DRUNK_LAST 0x3b
#define CAFE_MASTER_LINE_CLEARED 0x51 /* the clearing up done: 0x51 to 0x54 */
#define CAFE_MASTER_NO_LINE 0xff

#define CAFE_MASTER_REGULAR_COFFEES 5

/* The volume of his sequences' sounds (SoundEmitter_Play). */
#define CAFE_MASTER_SOUND_VOLUME 0x7f

/* The music asked for and dropped around the drink (music_queue.h). */
#define CAFE_MASTER_DRINK_PRIORITY 16
#define CAFE_MASTER_DRINK_MUSIC 0x3e

/* The functions of his states and of his talk scene's sequences (both filled at start-up by
 * __sinit_ov004_0224e734). */
extern CafeMasterStep data_ov004_022580e0[CAFE_MASTER_STATES];
extern CafeMasterTalkStep data_ov004_02254618[CAFE_MASTER_TALK_SEQUENCES];
/* The vtable of his talk scene, and of a class he derives from. */
extern const u8 data_ov004_02254650[];
extern const u8 data_020da088[];
/* His model and texture file names. */
extern const char data_ov004_022545cc[];
extern const char data_ov004_022545fc[];
/* His message files' names, by CAFE_MASTER_FILE_*. */
extern const u32 data_ov004_02254594[CAFE_MASTER_FILES];
/* The first of three messages of a talk after a coffee today, by level (8, 11, 14, 17). */
extern const u8 data_ov004_02254508[];
/* Where the cafe's guest is made, and its angles. */
extern const Vec3 data_ov004_02247760;
extern const s16 data_ov004_02247758[];
/* The word his motion requests carry. */
extern u16 data_020c80f8;
/* The look's point and range when it names neither. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

/* What RoomPlayerActor_RequestSpotMove is asked for when the player is seated. */
#define CAFE_MASTER_SEATED_KIND 2

static u8 *cm_part(CafeMaster *master, u32 offset)
{
    return master->base + offset;
}

static SceneMotion *cm_motion_of(CafeMaster *master)
{
    return (SceneMotion *) (void *) cm_part(master, CAFE_MASTER_MOTION);
}

static SceneAction *cm_action_of(CafeMaster *master)
{
    return (SceneAction *) (void *) cm_part(master, CAFE_MASTER_ACTION);
}

static SceneLook *cm_look_of(CafeMaster *master)
{
    return (SceneLook *) (void *) cm_part(master, CAFE_MASTER_LOOK);
}

static LayeredModel *cm_model_of(CafeMaster *master)
{
    return (LayeredModel *) (void *) cm_part(master, CAFE_MASTER_MODEL);
}

static SceneStandardAnims *cm_anims_of(CafeMaster *master)
{
    return (SceneStandardAnims *) (void *) cm_part(master, CAFE_MASTER_STANDARD_ANIMS);
}

static int cm_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* His look asked for: `kind`, priority 0, with the defaults for what it does not name. */
static void cm_look(CafeMaster *master, u8 kind)
{
    SceneLook_Request(cm_look_of(master), kind, 0, 0, &data_021fbee8, CAFE_MASTER_PLAYER_ACTOR, data_020c814c, 1);
}

/* A turn (priority 1) to `angle`. */
static void cm_turn(CafeMaster *master, s16 angle)
{
    SceneMotion_Request(cm_motion_of(master), CAFE_MASTER_MOTION_TURN, 1, 0, 0, 0, angle, 0, 0, data_020c80f8, 0);
}

/* A move (priority 1) to the point (x, z). */
static void cm_move_to(CafeMaster *master, int x, int z)
{
    SceneMotion_Request(cm_motion_of(master), CAFE_MASTER_MOTION_TO_POINT, 1, x, z, 0, 0, 0, 0, data_020c80f8, 0);
}

/* An animation (priority 1) in play mode `mode` from its first frame. */
static void cm_animate(CafeMaster *master, int animation, char mode)
{
    SceneMotion_RequestAnimation(cm_motion_of(master), 1, animation, mode, data_020c80f8, 0);
}

static int cm_motion_done(CafeMaster *master)
{
    return SceneMotion_IsDone(cm_motion_of(master));
}

static void cm_play(CafeMaster *master, int sound)
{
    SoundEmitter_Play((SoundEmitter *) (void *) cm_part(master, CAFE_MASTER_EMITTER), sound, CAFE_MASTER_SOUND_VOLUME, 0);
}

/* His standard animations set to `first`, `second` and `second`. */
static void cm_standard_anims(CafeMaster *master, int first, int second)
{
    SceneStandardAnims_SetFirst(cm_anims_of(master), first);
    SceneStandardAnims_SetSecond(cm_anims_of(master), second);
    SceneStandardAnims_SetThird(cm_anims_of(master), second);
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void cm_set_slots(CafeMaster *master, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(master->base, 1, owner, holder);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int cm_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, CAFE_MASTER_VARIABLE) != 0;
}

/* The player record's object at 0x2416 of the current player. */
static PlayerField2416 *cm_current_field(void)
{
    return (PlayerField2416 *) PlayerRecord_Field2416(PlayerRecords_Current());
}

/* A quarter of the coffees the player of `field` has had (0 to 3). */
static int cm_level(PlayerField2416 *field)
{
    return PlayerField2416_Count09(field) >> 2;
}

/* The talk of the scene. */
static TalkObject *cm_talk_object(CafeMasterTalk *talk)
{
    return (TalkObject *) (void *) talk->base.talk;
}

/* The message the talk scene shows. */
static u8 cm_shown(CafeMasterTalk *talk)
{
    return ((const MessageReceiver *) (const void *) talk)->message;
}

/* The talk shows `message` of the file `text`. */
static void cm_say_in(TalkObject *object, u8 message, u32 text)
{
    TalkObject_SetMessage(object, &message, (const char *) (uintptr_t) text);
}

/* The talk shows `message` of "sp_npc_cafe" and opens again. */
static void cm_say_again(TalkObject *object, u8 message)
{
    cm_say_in(object, message, data_ov004_02254594[CAFE_MASTER_FILE_PLAIN]);
    object->next_state = TALK_OBJECT_OPENING;
}

/* The talk scene's vtable slot 0x08 called. */
static void cm_talk_slot_08(CafeMasterTalk *talk)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + CAFE_MASTER_TALK_SLOT_08);
    ((void (*)(CafeMasterTalk *))(uintptr_t) code)(talk);
}

/* His talk scene reset through its vtable slot 0x08, the talk's partner this console's
 * player's field actor. */
static void cm_reset_talk(CafeMaster *master)
{
    cm_talk_slot_08(&master->talk);
    SceneBase_SetMotionArg(&master->talk.base, SceneObject_ActorObject(master->base, CAFE_MASTER_PLAYER_ACTOR));
}

/* func_ov004_02223704 (vtable slot 0x4c, told of an event about him by `participant`'s system,
 * 4 for this one), then the base class's handling (SceneObject_Vfunc4c):
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused (state 7); this one's (with the object ours): owned and held by this system,
 *   paused;
 * - 0, the player talks to him, and 1, the event asked for in state 0: the participant kept;
 *   another system's (not this one's slot): owned and held by it (state 6); this one's (with
 *   the object ours): owned and held by this system, his talk scene reset with this console's
 *   player as the partner, and he talks (state 1); for code 1 he waits for the player to be
 *   seated (state 4) unless linked or with the game variable 0x4a set;
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none, he turns back (state 3); else owned by none and held by this
 *   system, he awaits the session (state 5);
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, he stands. */
void CafeMaster_OnEvent(CafeMaster *master, int code, int participant)
{
    switch (code) {
        case CAFE_MASTER_EVENT_STARTS:
            *cm_part(master, CAFE_MASTER_PARTICIPANT) = (u8) participant;
            if (participant != CAFE_MASTER_PLAYER_ACTOR) {
                cm_set_slots(master, cm_local_slot(), participant);
                CafeMaster_SetState(master, CAFE_MASTER_PAUSED);
            } else if (SceneShare_IsOurs(master->base)) {
                cm_set_slots(master, cm_local_slot(), cm_local_slot());
                CafeMaster_SetState(master, CAFE_MASTER_PAUSED);
            }
            break;
        case CAFE_MASTER_EVENT_CALLED:
            *cm_part(master, CAFE_MASTER_PARTICIPANT) = (u8) participant;
            if (participant != CAFE_MASTER_PLAYER_ACTOR && participant != cm_local_slot()) {
                cm_set_slots(master, participant, participant);
                CafeMaster_SetState(master, CAFE_MASTER_OTHER);
            } else if (SceneShare_IsOurs(master->base)) {
                NetSession *session = data_020ccf94;
                cm_set_slots(master, session->local_slot, session->local_slot);
                cm_reset_talk(master);
                if (cm_linked_or_variable(session)) {
                    CafeMaster_SetState(master, CAFE_MASTER_TALKING);
                } else {
                    CafeMaster_SetState(master, CAFE_MASTER_WAIT_SEAT);
                }
            }
            break;
        case CAFE_MASTER_EVENT_TALK:
            *cm_part(master, CAFE_MASTER_PARTICIPANT) = (u8) participant;
            if (participant != CAFE_MASTER_PLAYER_ACTOR && participant != cm_local_slot()) {
                cm_set_slots(master, participant, participant);
                CafeMaster_SetState(master, CAFE_MASTER_OTHER);
            } else if (SceneShare_IsOurs(master->base)) {
                cm_set_slots(master, cm_local_slot(), cm_local_slot());
                cm_reset_talk(master);
                CafeMaster_SetState(master, CAFE_MASTER_TALKING);
            }
            break;
        case CAFE_MASTER_EVENT_ENDED:
            if (participant == CAFE_MASTER_PLAYER_ACTOR) {
                if (LinkGlobal_HoldsScene()) {
                    cm_set_slots(master, cm_local_slot(), SCENE_SHARE_NO_SLOT);
                    CafeMaster_SetState(master, CAFE_MASTER_TURN_BACK);
                } else {
                    cm_set_slots(master, SCENE_SHARE_NO_SLOT, cm_local_slot());
                    CafeMaster_SetState(master, CAFE_MASTER_AWAIT);
                }
            }
            break;
        case CAFE_MASTER_EVENT_REFUSED:
            if (SceneShare_IsHeld(master->base) && SceneShare_IsOurs(master->base)) {
                int owner = SCENE_SHARE_NO_SLOT;
                int holder = SCENE_SHARE_NO_SLOT;
                if (SceneShare_ReadSlots(master->base, &owner, &holder) &&
                    (participant == CAFE_MASTER_PLAYER_ACTOR || participant == holder)) {
                    cm_set_slots(master, cm_local_slot(), SCENE_SHARE_NO_SLOT);
                    CafeMaster_SetState(master, CAFE_MASTER_STAND);
                }
            }
            break;
        default:
            break;
    }
    SceneObject_Vfunc4c(master, code, participant);
}
CLEAN_AS(func_ov004_02223704, CafeMaster_OnEvent)

/* func_ov004_02223910 (vtable slot 0x48): whether the player may talk to him: his action idle
 * and no system holding him. */
int CafeMaster_MayAct(CafeMaster *master)
{
    if (SceneAction_IsBusy(cm_action_of(master))) {
        return 0;
    }
    return SceneShare_IsHeld(master->base) == 0;
}
CLEAN_AS(func_ov004_02223910, CafeMaster_MayAct)

/* func_ov004_0222393c (sequence 3, the clearing up, each step of the scene), by the step:
 * - 0: once the talk is gone, the player's field actor plays its animation of it
 *   (RoomPlayerActor_PlayAnimation98) and the props enter their state 9;
 * - 1: sounds 0x4e6 and 0x4e7 at frames 15 and 20; once part 1's animation 12 of the props has
 *   run out the camera's sounds come back, he looks ahead, plays his animation 0xf8 (mode 3,
 *   priority 4) and the props enter state 6;
 * - 2: sounds 0x4e8 and 0x4e9 at frames 18 and 45; once that is done the props enter state 1
 *   and he turns to angle 0;
 * - 3: once turned, his animation 0xf6 (mode 3), the props' state 7 and his standard
 *   animations 0xf2, 0xf4 and 0xf4;
 * - 4: sound 0x4ea at frame 10; once that is done the props enter state 0, he looks at the
 *   player and turns to angle -0x4000;
 * - 5: once turned, the talk shows his message 0x51 to 0x54 by level and opens again, the
 *   sequence ends and message 0x2d is forgotten.
 * The current player's level is read at each step. */
void CafeMasterTalk_ClearUp(CafeMasterTalk *talk)
{
    TalkObject *object = cm_talk_object(talk);
    u8 message = (u8) (cm_level(cm_current_field()) + CAFE_MASTER_LINE_CLEARED);
    CafeMaster *master = talk->master;

    switch (talk->step) {
        case 0:
            if (object->state != TALK_OBJECT_GONE) {
                break;
            }
            RoomPlayerActor_PlayAnimation98();
            CafeProps_EnterState9();
            talk->step = 1;
            master->talk_frames = 0;
            break;
        case 1:
            master->talk_frames++;
            if (master->talk_frames == 15) {
                cm_play(master, 0x4e6);
            }
            if (master->talk_frames == 20) {
                cm_play(master, 0x4e7);
            }
            if (!CafeProps_Part1Anim12Done()) {
                break;
            }
            CameraControl_UnmuteSounds();
            cm_look(master, CAFE_MASTER_LOOK_AHEAD);
            SceneMotion_RequestAnimation(cm_motion_of(master), 4, CAFE_MASTER_ANIM_F8, 3, data_020c80f8, 0);
            CafeProps_EnterState6();
            talk->step = 2;
            master->talk_frames = 0;
            break;
        case 2:
            master->talk_frames++;
            if (master->talk_frames == 18) {
                cm_play(master, 0x4e8);
            }
            if (master->talk_frames == 45) {
                cm_play(master, 0x4e9);
            }
            if (!cm_motion_done(master)) {
                break;
            }
            CafeProps_EnterState1();
            cm_turn(master, 0);
            talk->step = 3;
            break;
        case 3:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_animate(master, CAFE_MASTER_ANIM_F6, 3);
            CafeProps_EnterState7();
            cm_standard_anims(master, CAFE_MASTER_ANIM_F2, CAFE_MASTER_ANIM_F4);
            talk->step = 4;
            master->talk_frames = 0;
            break;
        case 4:
            master->talk_frames++;
            if (master->talk_frames == 10) {
                cm_play(master, 0x4ea);
            }
            if (!cm_motion_done(master)) {
                break;
            }
            CafeProps_EnterState0();
            cm_look(master, CAFE_MASTER_LOOK_PLAYER);
            cm_turn(master, -0x4000);
            talk->step = 5;
            break;
        case 5:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_say_again(object, message);
            CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_NONE);
            talk->saw_message_2d = 0;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0222393c, CafeMasterTalk_ClearUp)

/* func_ov004_02223c1c (the talk scene's slot 0x70, the talk closes): after one of the lines of
 * the drink (0x30 to 0x3b), the music 0x3e is dropped and the value (6, 0x1a) added at
 * priority 12. */
void CafeMasterTalk_OnClose(CafeMasterTalk *talk)
{
    u8 message = cm_shown(talk);
    if (message >= CAFE_MASTER_LINE_DRUNK_2D && message <= CAFE_MASTER_LINE_DRUNK_LAST) {
        Music_DropMusic(CAFE_MASTER_DRINK_MUSIC);
        Music_AddValue(12, 6, 0x1a);
    }
}
CLEAN_AS(func_ov004_02223c1c, CafeMasterTalk_OnClose)

/* func_ov004_02223c40 (sequence 2, the drink, each step of the scene), while the talk is gone:
 * the first time the props are in their state 5 they enter state 8, the player's field actor
 * plays its animation of it (RoomPlayerActor_RequestSequence8A) and the frames start again. Each frame:
 * sounds 0x4e1, 0x4e2 (with the value (20, 0) added to the music at priority 16) and 0x4e3 at
 * frames 7, 20 and 40, and at frame 70 0x4e4 or 0x4e5 by the current player id's byte 0x1c
 * (0 or not). Once part 1's animation 11 of the props is at frame 9: his line is picked (0x30
 * after message 0x2d, else one of 0x31 to 0x3b), the music of priority 16 is dropped, the
 * value (0, 10) added at 12 and the music 0x3e at 13; the talk shows the line and opens again;
 * a coffee is noted for today (daily bit 0x17); half the time the player's coffees grow by
 * one; the sequence ends. */
void CafeMasterTalk_Drink(CafeMasterTalk *talk)
{
    TalkObject *object = cm_talk_object(talk);

    if (object->state != TALK_OBJECT_GONE) {
        return;
    }
    if (CafeProps_State() == 5) {
        CafeProps_EnterState8();
        RoomPlayerActor_RequestSequence8A();
        talk->master->talk_frames = 0;
    }
    CafeMaster *master = talk->master;
    master->talk_frames++;
    if (master->talk_frames == 7) {
        cm_play(master, 0x4e1);
    }
    if (master->talk_frames == 20) {
        cm_play(master, 0x4e2);
        Music_AddValue(CAFE_MASTER_DRINK_PRIORITY, 20, 0);
    }
    if (master->talk_frames == 40) {
        cm_play(master, 0x4e3);
    }
    if (master->talk_frames == 70) {
        u8 *record = PlayerRecords_Current();
        if (PlayerId_Byte1c((const s8 *) PlayerRecord_Player(record)) == 0) {
            cm_play(master, 0x4e4);
        } else {
            cm_play(master, 0x4e5);
        }
    }
    if (!CafeProps_Part1Anim11AtFrame9()) {
        return;
    }
    u8 line;
    if (talk->saw_message_2d) {
        line = CAFE_MASTER_LINE_DRUNK_2D;
    } else {
        line = (u8) (MainRandom_Below(CAFE_MASTER_LINE_DRUNK_RANGE) + CAFE_MASTER_LINE_DRUNK);
    }
    Music_DropPriority(CAFE_MASTER_DRINK_PRIORITY);
    Music_AddValue(12, 0, 10);
    Music_Add(13, CAFE_MASTER_DRINK_MUSIC, 0x7f, 1);
    cm_say_again(object, line);
    TalkChecks_TestSetDailyBit(CAFE_MASTER_DAILY_COFFEE, 1);
    PlayerField2416 *field = cm_current_field();
    if (MainRandom_Below(10) < 5) {
        PlayerField2416_SetCount09(field, (u8) (PlayerField2416_Count09(field) + 1));
    }
    CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_NONE);
}
CLEAN_AS(func_ov004_02223c40, CafeMasterTalk_Drink)

/* func_ov004_02223dcc (sequence 1, the making, each step of the scene), by the step:
 * - 0: once the talk is gone he looks ahead and turns to angle 0;
 * - 1: once turned, his animation 0xf6 (mode 1), the props' state 3 and his standard
 *   animations 0xf3, 0xf5 and 0xf5;
 * - 2: sound 0x4db at frame 5; once done he turns the other way (turn way 2) to angle -0x8000
 *   and the props enter state 1;
 * - 3: once turned, he moves to the point (0x19700, 0x14000);
 * - 4: once there, he turns the usual way (0) to angle -0x4000;
 * - 5: once turned, his animation 0xf7 (mode 1) and the props' state 4;
 * - 6: sounds 0x4dc, 0x4dd and 0x4de at frames 13, 30 and 70; once done the props enter
 *   state 2 and he turns to angle 0;
 * - 7: once turned, he moves to the point (0x19700, 0x15000);
 * - 8: once there, he turns to angle -0x4000;
 * - 9: once turned, he looks at the player, plays his animation 0xf8 (mode 1) and the props
 *   enter state 5;
 * - 10: sounds 0x4df and 0x4e0 at frames 15 and 30; once done the talk shows his message 0x24
 *   to 0x27 by level and opens again, and the sequence ends.
 * The current player's level is read at each step. */
void CafeMasterTalk_Brew(CafeMasterTalk *talk)
{
    TalkObject *object = cm_talk_object(talk);
    u8 message = (u8) (cm_level(cm_current_field()) + CAFE_MASTER_LINE_ASK);
    CafeMaster *master = talk->master;
    SceneMover *mover = (SceneMover *) (void *) cm_part(master, CAFE_MASTER_MOVER);

    switch (talk->step) {
        case 0:
            if (object->state != TALK_OBJECT_GONE) {
                break;
            }
            cm_look(master, CAFE_MASTER_LOOK_AHEAD);
            cm_turn(master, 0);
            talk->step = 1;
            break;
        case 1:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_animate(master, CAFE_MASTER_ANIM_F6, 1);
            CafeProps_EnterState3();
            cm_standard_anims(master, CAFE_MASTER_ANIM_F3, CAFE_MASTER_ANIM_F5);
            talk->step = 2;
            master->talk_frames = 0;
            break;
        case 2:
            master->talk_frames++;
            if (master->talk_frames == 5) {
                cm_play(master, 0x4db);
            }
            if (!cm_motion_done(master)) {
                break;
            }
            SceneMover_SetTurnWay(mover, 2);
            cm_turn(master, -0x8000);
            CafeProps_EnterState1();
            talk->step = 3;
            break;
        case 3:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_move_to(master, 0x19700, 0x14000);
            talk->step = 4;
            break;
        case 4:
            if (!cm_motion_done(master)) {
                break;
            }
            SceneMover_SetTurnWay(mover, 0);
            cm_turn(master, -0x4000);
            talk->step = 5;
            break;
        case 5:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_animate(master, CAFE_MASTER_ANIM_F7, 1);
            CafeProps_EnterState4();
            talk->step = 6;
            master->talk_frames = 0;
            break;
        case 6:
            master->talk_frames++;
            if (master->talk_frames == 13) {
                cm_play(master, 0x4dc);
            }
            if (master->talk_frames == 30) {
                cm_play(master, 0x4dd);
            }
            if (master->talk_frames == 70) {
                cm_play(master, 0x4de);
            }
            if (!cm_motion_done(master)) {
                break;
            }
            CafeProps_EnterState2();
            cm_turn(master, 0);
            talk->step = 7;
            break;
        case 7:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_move_to(master, 0x19700, 0x15000);
            talk->step = 8;
            break;
        case 8:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_turn(master, -0x4000);
            talk->step = 9;
            break;
        case 9:
            if (!cm_motion_done(master)) {
                break;
            }
            cm_look(master, CAFE_MASTER_LOOK_PLAYER);
            cm_animate(master, CAFE_MASTER_ANIM_F8, 1);
            CafeProps_EnterState5();
            talk->step = 10;
            master->talk_frames = 0;
            break;
        case 10:
            master->talk_frames++;
            if (master->talk_frames == 15) {
                cm_play(master, 0x4df);
            }
            if (master->talk_frames == 30) {
                cm_play(master, 0x4e0);
            }
            if (!cm_motion_done(master)) {
                break;
            }
            cm_say_again(object, message);
            CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_NONE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_02223dcc, CafeMasterTalk_Brew)

/* func_ov004_0222421c: sequence `sequence`, from its first step. */
void CafeMasterTalk_SetSequence(CafeMasterTalk *talk, int sequence)
{
    talk->sequence = sequence;
    talk->step = 0;
}
CLEAN_AS(func_ov004_0222421c, CafeMasterTalk_SetSequence)

/* func_ov004_0222422c (the talk scene's slot 0x84, a command of the scene ended): the
 * sequence's function, when it is not one run at each step and it has one; then no sequence.
 * The game's three sequences are all run at each step.
 * REQUIRES: the sequence is 0 to 3 (the table is not bounded). */
void CafeMasterTalk_RunCommandSequence(CafeMasterTalk *talk)
{
    const CafeMasterTalkStep *entry = &data_ov004_02254618[talk->sequence];
    if (entry->each_step != 0 || entry->run.function == 0) {
        return;
    }
    MemberPointer_CallVoid(&entry->run, talk);
    CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_NONE);
}
CLEAN_AS(func_ov004_0222422c, CafeMasterTalk_RunCommandSequence)

/* func_ov004_0222427c (the talk scene's slot 0x80, each step): the sequence's function, when it
 * is one run at each step and it has one.
 * REQUIRES: the sequence is 0 to 3. */
void CafeMasterTalk_RunStepSequence(CafeMasterTalk *talk)
{
    const CafeMasterTalkStep *entry = &data_ov004_02254618[talk->sequence];
    if (entry->each_step != 0 && entry->run.function != 0) {
        MemberPointer_CallVoid(&entry->run, talk);
    }
}
CLEAN_AS(func_ov004_0222427c, CafeMasterTalk_RunStepSequence)

/* func_ov004_022242c0 (the talk scene's slot 0x18, the player's answer), by the message shown:
 * - 0x24 to 0x2b (the coffee made): the first answer ends the talk (its mode 0) and starts the
 *   drink (sequence 2); another gives message 0x28 to 0x2b by level;
 * - 0x14 to 0x17 (the offer): the first answer, with 200 bells, takes them and gives one of
 *   two of 0x1c to 0x23 by level, at random; without them 0x2f; another answer gives 0x18 to
 *   0x1b by level. */
void CafeMasterTalk_OnAnswer(CafeMasterTalk *talk)
{
    PlayerField2416 *field = cm_current_field();
    int answer = (int) TalkAnswers_Picked((TalkAnswers *) (uintptr_t) (u32) SceneBase_TalkChoices(&talk->base));
    u32 text = data_ov004_02254594[CAFE_MASTER_FILE_PLAIN];
    u8 message = CAFE_MASTER_NO_LINE;
    u8 shown = cm_shown(talk);

    if (shown >= CAFE_MASTER_LINE_ASK && shown <= CAFE_MASTER_LINE_ASK_LAST) {
        if (answer != 0) {
            message = (u8) (cm_level(field) + CAFE_MASTER_LINE_ANSWER_NO);
        } else {
            cm_talk_object(talk)->mode = 0;
            CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_DRINK);
        }
    }
    if (shown >= CAFE_MASTER_LINE_SEATED && shown <= CAFE_MASTER_LINE_SEATED + 3) {
        if (answer != 0) {
            message = (u8) (cm_level(field) + CAFE_MASTER_LINE_DECLINED);
        } else if (SceneBells_CanPay((int) (uintptr_t) talk->master, CAFE_MASTER_COFFEE_PRICE) == 0) {
            message = CAFE_MASTER_LINE_NO_BELLS;
        } else {
            SceneBells_Take((int) (uintptr_t) talk->master, CAFE_MASTER_COFFEE_PRICE);
            int pick = (int) MainRandom_Below(2);
            message = (u8) (pick + cm_level(field) * 2 + CAFE_MASTER_LINE_SERVED);
        }
    }
    if (message != CAFE_MASTER_NO_LINE) {
        cm_say_in(cm_talk_object(talk), message, text);
    }
}
CLEAN_AS(func_ov004_022242c0, CafeMasterTalk_OnAnswer)

/* func_ov004_0222439c (the talk scene's slot 0x14, a message ended): nothing when a game is
 * being started anew. After his line of the payment (0x1c to 0x23), from 5 coffees one time in
 * three message 0x2c; else, and after messages 0x2d (noted) and 0x2e, the talk ends (its mode
 * 0) and the making starts (sequence 1). After the lines of the drink (0x30 to 0x3b), the
 * clearing up (sequence 3). */
void CafeMasterTalk_OnMessageEnded(CafeMasterTalk *talk)
{
    PlayerField2416 *field = cm_current_field();
    TalkObject *object = cm_talk_object(talk);
    u32 text = data_ov004_02254594[CAFE_MASTER_FILE_PLAIN];
    u8 message = CAFE_MASTER_NO_LINE;

    if (StartKind_IsSet()) {
        return;
    }
    u8 shown = cm_shown(talk);
    if (shown >= CAFE_MASTER_LINE_SERVED && shown <= CAFE_MASTER_LINE_SERVED_LAST) {
        if ((unsigned int) PlayerField2416_Count09(field) >= CAFE_MASTER_REGULAR_COFFEES && MainRandom_Below(3) == 0) {
            message = CAFE_MASTER_LINE_REGULAR;
        } else {
            object->mode = 0;
            CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_BREW);
        }
    }
    if (shown == CAFE_MASTER_LINE_2D || shown == CAFE_MASTER_LINE_2E) {
        if (shown == CAFE_MASTER_LINE_2D) {
            talk->saw_message_2d = 1;
        }
        object->mode = 0;
        CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_BREW);
    }
    if (shown >= CAFE_MASTER_LINE_DRUNK_2D && shown <= CAFE_MASTER_LINE_DRUNK_LAST) {
        object->mode = 0;
        CafeMasterTalk_SetSequence(talk, CAFE_MASTER_TALK_CLEAR);
    }
    if (message != CAFE_MASTER_NO_LINE) {
        cm_say_in(cm_talk_object(talk), message, text);
    }
}
CLEAN_AS(func_ov004_0222439c, CafeMasterTalk_OnMessageEnded)

/* Whether the cafe's guest `guest` is there and the one that plays music. */
static int cm_musician_in(void *guest)
{
    return guest != NULL && CafeGuest_Kind((CafeGuest *) guest) == CAFE_MASTER_GUEST_MUSICIAN;
}

/* func_ov004_02224440 (the talk scene's slot 0x78, the line to say):
 * - when a game is being started anew: message 0x1f of "sp_etc_sequence4";
 * - else of "sp_npc_cafe": linked (or with the game variable 0x4a set) 0x55 to 0x57; after a
 *   coffee today 0x58 when the musician is in, else one of three from data_ov004_02254508's
 *   by level; with the player not seated, at the first talk of the day (noted) half the
 *   player's coffees (0 to 7), else 0x58 when the musician is in, else 0x49 to 0x4c by level;
 *   seated, the offer 0x14 to 0x17 by level, the panels asked for first (ScreenPanels_Request)
 *   when there was no coffee today. The talk scene is not used. */
void CafeMasterTalk_Line(CafeMasterTalk *talk, CafeMasterLine *out)
{
    (void) talk;
    PlayerField2416 *field = cm_current_field();

    if (StartKind_IsSet()) {
        out->text = data_ov004_02254594[CAFE_MASTER_FILE_NEW_START];
        out->message = CAFE_MASTER_LINE_NEW_START;
        return;
    }
    out->text = data_ov004_02254594[CAFE_MASTER_FILE_PLAIN];
    void *guest = Actor_FindNextOfProfile(CAFE_MASTER_GUEST_PROFILE, NULL);
    if (cm_linked_or_variable(data_020ccf94)) {
        out->message = (u8) (MainRandom_Below(3) + CAFE_MASTER_LINE_LINKED);
        return;
    }
    if (TalkChecks_TestSetDailyBit(CAFE_MASTER_DAILY_COFFEE, 0)) {
        if (cm_musician_in(guest)) {
            out->message = CAFE_MASTER_LINE_MUSICIAN;
            return;
        }
        int level = cm_level(field);
        out->message = (u8) (data_ov004_02254508[level] + MainRandom_Below(3));
        return;
    }
    if (!PlayerActorOps_InState(CAFE_MASTER_PLAYER_SEATED, CAFE_MASTER_PLAYER_ACTOR)) {
        if (!TalkChecks_TestSetDailyBit(CAFE_MASTER_DAILY_FIRST_TALK, 1)) {
            out->message = (u8) (PlayerField2416_Count09(field) >> 1);
            return;
        }
        if (cm_musician_in(guest)) {
            out->message = CAFE_MASTER_LINE_MUSICIAN;
            return;
        }
        out->message = (u8) (cm_level(field) + CAFE_MASTER_LINE_STANDING);
        return;
    }
    if (!TalkChecks_TestSetDailyBit(CAFE_MASTER_DAILY_COFFEE, 0)) {
        ScreenPanels_Request();
    }
    out->message = (u8) (cm_level(field) + CAFE_MASTER_LINE_SEATED);
}
CLEAN_AS(func_ov004_02224440, CafeMasterTalk_Line)

/* func_ov004_02224544: his talk scene reset through its vtable slot 0x08 and given its
 * master. */
void CafeMasterTalk_Begin(CafeMasterTalk *talk, CafeMaster *master)
{
    cm_talk_slot_08(talk);
    talk->master = master;
}
CLEAN_AS(func_ov004_02224544, CafeMasterTalk_Begin)

/* func_ov004_02224560 (the talk scene's vtable slot 0x04): its destructor, then the scene
 * freed. */
CafeMasterTalk *CafeMasterTalk_Delete(CafeMasterTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov004_02254650;
    SceneBase_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_02224560, CafeMasterTalk_Delete)

/* func_ov004_02224580 (the talk scene's vtable slot 0x00): the scene base's destructor. */
CafeMasterTalk *CafeMasterTalk_Destroy(CafeMasterTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov004_02254650;
    SceneBase_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov004_02224580, CafeMasterTalk_Destroy)

/* func_ov004_02224598: the constructor: a scene base given this class's vtable. */
CafeMasterTalk *CafeMasterTalk_Construct(CafeMasterTalk *talk)
{
    SceneBase_Construct(&talk->base);
    *(const u8 **) (void *) talk = data_ov004_02254650;
    return talk;
}
CLEAN_AS(func_ov004_02224598, CafeMasterTalk_Construct)

/* func_ov004_022245b0 (state 7's update): nothing. 1. */
int CafeMaster_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022245b0, CafeMaster_UpdatePaused)

/* func_ov004_022245b4 (state 7's entry): 1. */
int CafeMaster_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022245b4, CafeMaster_EnterPaused)

/* func_ov004_022245b8 (state 6's update): once the object, ours, is owned by no system and
 * this one holds the scene, it is owned by this system and held by none, and he stands. 1. */
int CafeMaster_UpdateOther(CafeMaster *master)
{
    if (SceneShare_IsOurs(master->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(master->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            cm_set_slots(master, cm_local_slot(), SCENE_SHARE_NO_SLOT);
            CafeMaster_SetState(master, CAFE_MASTER_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_022245b8, CafeMaster_UpdateOther)

/* func_ov004_02224610 (state 6's entry): he looks straight ahead. 1. */
int CafeMaster_EnterOther(CafeMaster *master)
{
    cm_look(master, CAFE_MASTER_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov004_02224610, CafeMaster_EnterOther)

/* func_ov004_02224648 (state 5's update), with the object ours: once this system owns and
 * holds it, it is set so again and he talks to this console's player (state 1); else, once
 * this system holds the scene and no system holds the object, it is owned by this system and
 * held by none, and he stands. 1. */
int CafeMaster_UpdateAwait(CafeMaster *master)
{
    if (SceneShare_IsOurs(master->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(master->base, &owner, &holder) && owner == cm_local_slot() && owner == holder) {
            cm_set_slots(master, cm_local_slot(), cm_local_slot());
            cm_reset_talk(master);
            CafeMaster_SetState(master, CAFE_MASTER_TALKING);
        } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
            cm_set_slots(master, cm_local_slot(), SCENE_SHARE_NO_SLOT);
            CafeMaster_SetState(master, CAFE_MASTER_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02224648, CafeMaster_UpdateAwait)

/* func_ov004_022246e4 (state 5's entry): he looks straight ahead. 1. */
int CafeMaster_EnterAwait(CafeMaster *master)
{
    cm_look(master, CAFE_MASTER_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov004_022246e4, CafeMaster_EnterAwait)

/* func_ov004_0222471c (state 4's update): once this console's player is seated, he talks. 1. */
int CafeMaster_UpdateWaitSeat(CafeMaster *master)
{
    if (PlayerActorOps_InState(CAFE_MASTER_PLAYER_SEATED, CAFE_MASTER_PLAYER_ACTOR)) {
        CafeMaster_SetState(master, CAFE_MASTER_TALKING);
    }
    return 1;
}
CLEAN_AS(func_ov004_0222471c, CafeMaster_UpdateWaitSeat)

/* func_ov004_0222473c (state 4's entry): 1. */
int CafeMaster_EnterWaitSeat(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0222473c, CafeMaster_EnterWaitSeat)

/* func_ov004_02224740 (state 3's update): once his turn is done, he stands. 1. */
int CafeMaster_UpdateTurnBack(CafeMaster *master)
{
    if (SceneMotion_Kind(cm_motion_of(master)) == CAFE_MASTER_MOTION_TURN && cm_motion_done(master)) {
        CafeMaster_SetState(master, CAFE_MASTER_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov004_02224740, CafeMaster_UpdateTurnBack)

/* func_ov004_02224770 (state 3's entry): he turns (priority 2) to the angle he faced at his
 * start. 1. */
int CafeMaster_EnterTurnBack(CafeMaster *master)
{
    SceneMotion_Request(cm_motion_of(master), CAFE_MASTER_MOTION_TURN, 2, 0, 0, 0, master->home_yaw, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_02224770, CafeMaster_EnterTurnBack)

/* func_ov004_022247ac (state 2's update): nothing. 1. */
int CafeMaster_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022247ac, CafeMaster_UpdateTalked)

/* func_ov004_022247b0 (state 2's entry): 1. */
int CafeMaster_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022247b0, CafeMaster_EnterTalked)

/* func_ov004_022247b4 (state 1's update): once his action is idle: unlinked and without the
 * game variable 0x4a, the panels' request is cleared (ScreenPanels_ClearRequest, given
 * RoomPlayerActor_RequestSpotMove's answer when the player is seated, else 0); he looks ahead, the
 * object's event ends and state 2 follows. 1. */
int CafeMaster_UpdateTalk(CafeMaster *master)
{
    if (SceneAction_IsBusy(cm_action_of(master))) {
        return 1;
    }
    if (!cm_linked_or_variable(data_020ccf94)) {
        int value = PlayerActorOps_InState(CAFE_MASTER_PLAYER_SEATED, CAFE_MASTER_PLAYER_ACTOR);
        if (value != 0) {
            value = RoomPlayerActor_RequestSpotMove(CAFE_MASTER_SEATED_KIND);
        }
        ScreenPanels_ClearRequest((unsigned int) value);
    }
    cm_look(master, CAFE_MASTER_LOOK_AHEAD);
    EventQueue_FinishObjectEvent(master);
    CafeMaster_SetState(master, CAFE_MASTER_TALKED);
    return 1;
}
CLEAN_AS(func_ov004_022247b4, CafeMaster_UpdateTalk)

/* func_ov004_02224844 (state 1's entry): he looks at the player and talks, turned to the
 * talk's partner (none: angle 0). 1. */
int CafeMaster_EnterTalk(CafeMaster *master)
{
    int partner = SceneBase_MotionArg(&master->talk.base);
    int angle = 0;
    cm_look(master, CAFE_MASTER_LOOK_PLAYER);
    if (partner != 0) {
        angle = SceneObject_YawTo(master->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(cm_action_of(master), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov004_02224844, CafeMaster_EnterTalk)

/* func_ov004_022248b0 (state 0's update): 20 frames after he has looked aside he looks ahead,
 * once; unlinked and without the game variable 0x4a, while this console's player is in its
 * field state 0x27 an event of kind 7 is asked for him; when he no longer faces where he did
 * at his start, he turns back (state 3). 1.
 * QUIRK: only a look to one side (a yaw above 0x2000, not one below -0x2000) starts the
 * count. */
int CafeMaster_UpdateStand(CafeMaster *master)
{
    if (master->look_timer > 0) {
        master->look_timer++;
        if (master->look_timer > CAFE_MASTER_LOOK_BACK_FRAMES) {
            cm_look(master, CAFE_MASTER_LOOK_AHEAD);
            master->look_timer = -1;
        }
    } else if (master->look_timer == 0) {
        if (cm_look_of(master)->yaw > CAFE_MASTER_LOOK_ASIDE) {
            master->look_timer = 1;
        }
    }
    if (!cm_linked_or_variable(data_020ccf94) && PlayerActorOps_InState(CAFE_MASTER_PLAYER_CALLS, CAFE_MASTER_PLAYER_ACTOR)) {
        EventQueue_RequestKind7(master, 0);
    }
    if (master->home_yaw != *(const s16 *) (const void *) cm_part(master, CAFE_MASTER_YAW)) {
        CafeMaster_SetState(master, CAFE_MASTER_TURN_BACK);
    }
    return 1;
}
CLEAN_AS(func_ov004_022248b0, CafeMaster_UpdateStand)

/* func_ov004_02224978 (state 0's entry): the look's count starts again and he stands (priority
 * 1). 1. */
int CafeMaster_EnterStand(CafeMaster *master)
{
    master->look_timer = 0;
    SceneMotion_Request(cm_motion_of(master), CAFE_MASTER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_02224978, CafeMaster_EnterStand)

/* func_ov004_022249b4: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 7 (the table is not bounded). */
void CafeMaster_SetState(CafeMaster *master, int state)
{
    const CafeMasterStep *step = &data_ov004_022580e0[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, master);
    }
    if (taken != 0) {
        master->state = state;
    }
}
CLEAN_AS(func_ov004_022249b4, CafeMaster_SetState)

/* func_ov004_022249f8 (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0). Then while one of the musics 0x63 to 0xab plays: at its first
 * frame his model blends into the beat over 10 frames when its animation is past its first
 * whole frame; while the music's sound entry plays, his model's base animation is stepped from
 * frame 0 by the entry's word at 0x10. Otherwise the music is noted as not playing.
 * QUIRK: the blend tests only the low 16 bits of the animation's whole frame.
 * REQUIRES: his state is 0 to 7. */
int CafeMaster_Update(CafeMaster *master)
{
    const CafeMasterStep *step = &data_ov004_022580e0[master->state];
    int result = 0;
    if (step->update.function != 0) {
        result = MemberPointer_CallInt(&step->update, master);
    }
    LayeredModel *model = cm_model_of(master);
    if (Math_IsBetween(Music_CurrentMusic(), CAFE_MASTER_BEAT_MUSIC_FIRST, CAFE_MASTER_BEAT_MUSIC_LAST)) {
        if (master->on_beat == 0) {
            if ((u16) (model->base_frames.frame >> 12) != 0) {
                Ramp_Start((Ramp *) (void *) &model->base_ramp, CAFE_MASTER_BEAT_BLEND_FRAMES);
            }
            master->on_beat = 1;
        }
        const int *entry = SoundSys_FirstEntryData();
        if (entry != NULL && ((const s8 *) entry)[3] != CAFE_MASTER_SOUND_STOPPED) {
            model->base_frames.frame = 0;
            model->base_frames.speed = entry[4];
            LayeredModel_UpdateB(model);
            model->base_frames.speed = 0;
        }
    } else {
        master->on_beat = 0;
    }
    return result;
}
CLEAN_AS(func_ov004_022249f8, CafeMaster_Update)

/* func_ov004_02224abc (vtable slot 0x70): his model's file name, "npc_sp/model/pge.nsbmd". */
const char *CafeMaster_ModelName(void)
{
    return data_ov004_022545cc;
}
CLEAN_AS(func_ov004_02224abc, CafeMaster_ModelName)

/* func_ov004_02224ac4 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/pge_tex.nsbtx". */
const char *CafeMaster_TextureName(void)
{
    return data_ov004_022545fc;
}
CLEAN_AS(func_ov004_02224ac4, CafeMaster_TextureName)

/* func_ov004_02224acc (vtable slot 0x24, drawn): unless the scene object is not drawn, the
 * matrices of his model's joints 14 and 11 are kept and the cafe's props are drawn
 * (CafeProps_DrawCurrent). Whether he was drawn. */
int CafeMaster_Draw(CafeMaster *master)
{
    if (!SceneObject_Draw(master->base)) {
        return 0;
    }
    ModelObject *model = (ModelObject *) (void *) cm_model_of(master);
    ModelObject_JointMatrix(model, &master->matrix_718, CAFE_MASTER_JOINT_718);
    ModelObject_JointMatrix(model, &master->matrix_748, CAFE_MASTER_JOINT_748);
    CafeProps_DrawCurrent();
    return 1;
}
CLEAN_AS(func_ov004_02224acc, CafeMaster_Draw)

/* func_ov004_02224b0c (vtable slot 0x0c): when the special character may leave, he is no
 * longer the master started. Whether he may. */
int CafeMaster_Leave(CafeMaster *master)
{
    if (SpecialSceneObject_Leave(master) == 0) {
        return 0;
    }
    data_ov004_022580dc = NULL;
    return 1;
}
CLEAN_AS(func_ov004_02224b0c, CafeMaster_Leave)

/* func_ov004_02224b30 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he is the master started, notes the angle he faces and is held (flag 2 at 0x4e8).
 * Linked (or with the game variable 0x4a set) he stands when this system holds the scene,
 * else awaits the session (state 5); unlinked he stands. When this console's slot is not
 * taken in the session, the cafe's guest is made (profile 0x66). Whether he started. */
int CafeMaster_Start(CafeMaster *master)
{
    if (SpecialSceneObject_Start(master) == 0) {
        return 0;
    }
    data_ov004_022580dc = master->base;
    master->home_yaw = *(const s16 *) (const void *) cm_part(master, CAFE_MASTER_YAW);
    *(u32 *) (void *) cm_part(master, CAFE_MASTER_HELD_FLAGS) |= CAFE_MASTER_HELD;
    if (cm_linked_or_variable(data_020ccf94)) {
        if (LinkGlobal_HoldsScene()) {
            CafeMaster_SetState(master, CAFE_MASTER_STAND);
        } else {
            CafeMaster_SetState(master, CAFE_MASTER_AWAIT);
        }
    } else {
        CafeMaster_SetState(master, CAFE_MASTER_STAND);
    }
    if (!Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        Actor_Spawn(CAFE_MASTER_GUEST_PROFILE, CAFE_MASTER_GUEST_ARG, &data_ov004_02247760, data_ov004_02247758, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov004_02224b30, CafeMaster_Start)

/* func_ov004_02224bdc (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its master; his collider, reach, pace
 * (mode 2) and standard animations (0xf2, 0xf4, 0xf4) are set. Whether he was set up. */
int CafeMaster_Init(CafeMaster *master)
{
    if (SpecialSceneObject_Init(master) == 0) {
        return 0;
    }
    SceneObject_SetScene(master->base, &master->talk.base);
    CafeMasterTalk_Begin(&master->talk, master);
    SceneObject_SetColliderSize(master->base, CAFE_MASTER_COLLIDER_SIZE);
    SceneObjectBase_SetReach((SceneObjectBase *) (void *) master->base, CAFE_MASTER_REACH);
    SceneMover_SetPace((SceneMover *) (void *) cm_part(master, CAFE_MASTER_MOVER), CAFE_MASTER_PACE_MODE,
                       CAFE_MASTER_PACE_SPEED, CAFE_MASTER_PACE_SPEED_UP, CAFE_MASTER_PACE_SLOW_DOWN);
    cm_standard_anims(master, CAFE_MASTER_ANIM_F2, CAFE_MASTER_ANIM_F4);
    return 1;
}
CLEAN_AS(func_ov004_02224bdc, CafeMaster_Init)

/* func_ov004_02224c68: a zeroed block of 0x780 bytes from the auxiliary heap, constructed: the
 * scene object base, the class 0x020d8c64's vtable and members in place order (no person yet,
 * 0xfff1), the class 0x020da088's vtable and heap link, then the class's vtable and its talk
 * scene. Null when there is no room. */
CafeMaster *CafeMaster_Create(void)
{
    CafeMaster *master = (CafeMaster *) Heap_AllocAuxZeroed(sizeof(CafeMaster));
    if (master == NULL) {
        return NULL;
    }
    u8 *object = master->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) cm_part(master, CAFE_MASTER_PERSON) = CAFE_MASTER_NO_PERSON;
    LayeredModel_ConstructB(cm_model_of(master));
    SceneStandardAnims_Init(cm_anims_of(master));
    SceneFace_Construct((SceneFace *) (void *) cm_part(master, CAFE_MASTER_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) cm_part(master, CAFE_MASTER_ANIM));
    SceneMover_Construct((SceneMover *) (void *) cm_part(master, CAFE_MASTER_MOVER));
    SceneProbe_Construct(cm_part(master, CAFE_MASTER_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) cm_part(master, CAFE_MASTER_VALUE_3AA));
    SceneLook_Construct(cm_look_of(master));
    SceneTalkState_Construct((SceneTalkState *) (void *) cm_part(master, CAFE_MASTER_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) cm_part(master, CAFE_MASTER_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) cm_part(master, CAFE_MASTER_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) cm_part(master, CAFE_MASTER_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) cm_part(master, CAFE_MASTER_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) cm_part(master, CAFE_MASTER_FOOTSTEPS));
    SceneMotion_Construct(cm_motion_of(master));
    SceneAction_Construct(cm_action_of(master));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) cm_part(master, CAFE_MASTER_HEAP));
    *(const u8 **) (void *) object = data_ov004_022546e0;
    CafeMasterTalk_Construct(&master->talk);
    return master;
}
CLEAN_AS(func_ov004_02224c68, CafeMaster_Create)
