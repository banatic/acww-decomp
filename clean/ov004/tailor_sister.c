/* The character who sews at the tailor's machine, and its talk scene (tailor_sister.h). */
#include "tailor_sister.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/actor_table.h"
#include "main/calendar.h"
#include "main/day_events.h"
#include "main/event_queue.h"
#include "main/game_variables.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/obj_020d9ff8.h"
#include "main/player_field_2416.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_object.h"
#include "main/scene_object_members.h"
#include "main/scene_probe.h"
#include "main/scene_share.h"
#include "main/scene_value_3aa.h"
#include "main/session.h"
#include "main/special_scene_object.h"
#include "main/start_kind.h"
#include "main/talk_checks.h"
#include "tailor_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(TailorSisterTalk, owner) == 0xb0, "owner");
static_assert(sizeof(TailorSisterTalk) == 0xb4, "its talk scene");
static_assert(sizeof(TailorSisterLine) == 8, "a line");
static_assert(sizeof(TailorSisterStep) == 0x10, "a state's functions");
static_assert(offsetof(TailorSister, state) == 0x654, "state");
static_assert(offsetof(TailorSister, talk) == 0x658, "talk scene");
static_assert(offsetof(TailorSister, home_yaw) == 0x70c, "home yaw");
static_assert(offsetof(TailorSister, dated_event_told) == 0x70e, "dated event told");
static_assert(offsetof(TailorSister, sew_frame) == 0x710, "sew frame");
static_assert(offsetof(TailorSister, machine_turns) == 0x712, "machine turns");
static_assert(sizeof(TailorSister) == 0x714, "the size func_ov004_0222353c allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define TAILOR_SISTER_YAW 0x8e             /* s16: where it faces */
#define TAILOR_SISTER_MODEL_FRAME 0x190    /* fx32: its model's animation frame, 20.12 */
#define TAILOR_SISTER_PERSON 0xea          /* u16: its person code */
#define TAILOR_SISTER_MODEL 0xec           /* LayeredModel */
#define TAILOR_SISTER_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TAILOR_SISTER_FACE 0x2ac           /* SceneFace */
#define TAILOR_SISTER_ANIM 0x334           /* SpeakerAnim */
#define TAILOR_SISTER_MOVER 0x350          /* SceneMover */
#define TAILOR_SISTER_PROBE 0x3a8
#define TAILOR_SISTER_VALUE_3AA 0x3aa   /* SceneValue3aa */
#define TAILOR_SISTER_LOOK 0x3b0        /* SceneLook */
#define TAILOR_SISTER_TALK_STATE 0x418  /* SceneTalkState */
#define TAILOR_SISTER_EFFECTS 0x420     /* ActEffects */
#define TAILOR_SISTER_COLLIDER 0x49c    /* CollisionContacts */
#define TAILOR_SISTER_CARRIER 0x4cc     /* FieldOwnedBody */
#define TAILOR_SISTER_HELD_FLAGS 0x4e8  /* u32: the scene object's flags (2: held) */
#define TAILOR_SISTER_EMITTER 0x514     /* SoundEmitterObject */
#define TAILOR_SISTER_FOOTSTEPS 0x558   /* Footsteps */
#define TAILOR_SISTER_PARTICIPANT 0x560 /* u8: whose system the last event came from */
#define TAILOR_SISTER_MOTION 0x564      /* SceneMotion */
#define TAILOR_SISTER_ACTION 0x618      /* SceneAction */
#define TAILOR_SISTER_HEAP 0x640        /* PoolLink */

#define TAILOR_SISTER_NO_PERSON 0xfff1
#define TAILOR_SISTER_HELD 2

/* The field actor of this console's player. */
#define TAILOR_SISTER_PLAYER_ACTOR 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define TAILOR_SISTER_EVENT_TALK 0
#define TAILOR_SISTER_EVENT_STARTS 3
#define TAILOR_SISTER_EVENT_REFUSED 4
#define TAILOR_SISTER_EVENT_ENDED 8

/* Its talk scene's vtable slot its talks call first. */
#define TAILOR_SISTER_TALK_SLOT_08 0x08

/* Its sewing animation, the frames of one turn of the machine's part, and the motion kind of
 * a turn (scene_motion_request.h). */
#define TAILOR_SISTER_SEW_ANIM 0xe4
#define TAILOR_SISTER_MACHINE_TURN_FRAMES 0x38
#define TAILOR_SISTER_MOTION_TURN 3

/* The looks it asks for (SceneLook_Request): none (straight ahead) and the player. */
#define TAILOR_SISTER_LOOK_AHEAD 0
#define TAILOR_SISTER_LOOK_PLAYER 1

/* The days of talks from which it turns to the player and looks at them, and the most kept. */
#define TAILOR_SISTER_FAMILIAR_DAYS 6
#define TAILOR_SISTER_MOST_DAYS 15

/* The current player's daily bits: its first line of the day, and a day of talks counted. */
#define TAILOR_SISTER_DAILY_FIRST_LINE 0x10
#define TAILOR_SISTER_DAILY_COUNTED 0x11

/* The game variable (bank 0) that, when set, gives the plain line as when linked. */
#define TAILOR_SISTER_VARIABLE 0x4a

/* The kind of dated event it tells (day_events.h). */
#define TAILOR_SISTER_EVENT_KIND 2

/* Its body (SpecialSceneObject_SetBodySize), collider and reach. */
#define TAILOR_SISTER_BODY_RADIUS 0x119a
#define TAILOR_SISTER_BODY_HEIGHT 0x2000
#define TAILOR_SISTER_REACH 0x3000

/* Its message files (data_ov004_02254338): "sp_npc_osister", "sp_npc_drama3" (the dated
 * events) and "sp_etc_sequence4" (a game being started anew). */
#define TAILOR_SISTER_FILE_PLAIN 0
#define TAILOR_SISTER_FILE_DRAMA 1
#define TAILOR_SISTER_FILE_NEW_START 2
#define TAILOR_SISTER_FILES 3

/* Its line's messages. */
#define TAILOR_SISTER_LINE_LINKED 0x57
#define TAILOR_SISTER_LINE_NEW_START 5
#define TAILOR_SISTER_LINE_DAYS 12       /* the rows of data_ov004_022476f8 */
#define TAILOR_SISTER_LINE_LATE_FIRST 40 /* again on a day, past 12 days: 40 to 44 */
#define TAILOR_SISTER_LINE_LATE_RANGE 5
#define TAILOR_SISTER_DRAMA_PARTS 7 /* the columns of data_ov004_022476dc */

/* The special character the second speaker of some of its lines is (Actors_GetDByIndex). */
#define TAILOR_SISTER_SECOND_SPEAKER 4

/* A row of its lines by the days of talks. */
typedef struct TailorSisterDayLines {
    u8 first; /* the first talk of a day; again, one of the `count` after it */
    u8 unk_01[3];
    s32 count;
} TailorSisterDayLines;

static_assert(sizeof(TailorSisterDayLines) == 8, "a row of lines");

/* The vtables: the class's, its talk scene's and those of the classes it derives from. */
extern const u8 data_ov004_0225445c[];
extern const u8 data_ov004_022543cc[];
extern const u8 data_020da088[];
/* The functions of its states (filled at start-up by __sinit_ov004_0224e668). */
extern TailorSisterStep data_ov004_0225806c[TAILOR_SISTER_STATES];
/* Its model and texture file names. */
extern const char data_ov004_02254378[];
extern const char data_ov004_022543a8[];
/* Its message files' names, by TAILOR_SISTER_FILE_*. */
extern const u32 data_ov004_02254338[TAILOR_SISTER_FILES];
/* Its lines: by the days of talks, by the weekday (the first talk of a day past 11 days), and
 * the dated events' by event (rows of 7) and part. */
extern const TailorSisterDayLines data_ov004_022476f8[TAILOR_SISTER_LINE_DAYS];
extern const u8 data_ov004_022476d4[];
extern const u8 data_ov004_022476dc[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The look's point and range when it names neither. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

static u8 *ts_part(TailorSister *sister, u32 offset)
{
    return sister->base + offset;
}

static SceneMotion *ts_motion_of(TailorSister *sister)
{
    return (SceneMotion *) (void *) ts_part(sister, TAILOR_SISTER_MOTION);
}

static SceneAction *ts_action_of(TailorSister *sister)
{
    return (SceneAction *) (void *) ts_part(sister, TAILOR_SISTER_ACTION);
}

static SceneLook *ts_look_of(TailorSister *sister)
{
    return (SceneLook *) (void *) ts_part(sister, TAILOR_SISTER_LOOK);
}

static int ts_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* The player record's object at 0x2416 of the current player. */
static PlayerField2416 *ts_current_field(void)
{
    return (PlayerField2416 *) PlayerRecord_Field2416(PlayerRecords_Current());
}

/* Its look asked for: `kind`, priority 0, with the defaults for what it does not name. */
static void ts_look(TailorSister *sister, u8 kind)
{
    SceneLook_Request(ts_look_of(sister), kind, 0, 0, &data_021fbee8, TAILOR_SISTER_PLAYER_ACTOR, data_020c814c, 1);
}

/* The talk scene's vtable slot 0x08 called. */
static void ts_talk_slot_08(TailorSisterTalk *talk)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + TAILOR_SISTER_TALK_SLOT_08);
    ((void (*)(TailorSisterTalk *))(uintptr_t) code)(talk);
}

/* Whether it plays its sewing animation. */
static int ts_sewing(TailorSister *sister)
{
    return SpeakerAnim_IsBody((SpeakerAnim *) (void *) ts_part(sister, TAILOR_SISTER_ANIM), TAILOR_SISTER_SEW_ANIM,
                              ts_part(sister, TAILOR_SISTER_STANDARD_ANIMS)) != 0;
}

/* The frame of the machine's part that goes with its own: its whole turns, and the frame of
 * its animation. */
static u16 ts_machine_frame(TailorSister *sister)
{
    s32 frame = *(const s32 *) (const void *) ts_part(sister, TAILOR_SISTER_MODEL_FRAME);
    return (u16) (sister->machine_turns * TAILOR_SISTER_MACHINE_TURN_FRAMES + (u16) (frame >> 12));
}

/* The machine run in step with its sewing: when it stands or slows down, it runs from the
 * frame that goes with its own. */
static void ts_run_machine(TailorSister *sister)
{
    if (TailorObject_InState0Or3()) {
        TailorObject_RunCurrent();
        TailorObject_SetPartFrame(ts_machine_frame(sister));
    }
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void ts_set_slots(TailorSister *sister, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(sister->base, 1, owner, holder);
}

/* It talks to this console's player: its talk scene told through its vtable slot 0x08, the
 * talk's partner this console's player's field actor, state 1. */
static void ts_start_talk(TailorSister *sister)
{
    ts_talk_slot_08(&sister->talk);
    SceneBase_SetMotionArg(&sister->talk.base, SceneObject_ActorObject(sister->base, TAILOR_SISTER_PLAYER_ACTOR));
    TailorSister_SetState(sister, TAILOR_SISTER_TALK);
}

/* func_ov004_02222ad0 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
TailorSister *TailorSister_Destroy(TailorSister *sister)
{
    *(const u8 **) (void *) sister->base = data_ov004_0225445c;
    TailorSisterTalk_Destroy(&sister->talk);
    SpecialSceneObject_DestructBody(sister);
    return sister;
}
CLEAN_AS(func_ov004_02222ad0, TailorSister_Destroy)

/* func_ov004_02222af8 (vtable slot 0x44): the same, then the object freed. */
TailorSister *TailorSister_Delete(TailorSister *sister)
{
    *(const u8 **) (void *) sister->base = data_ov004_0225445c;
    TailorSisterTalk_Destroy(&sister->talk);
    SpecialSceneObject_DestructBody(sister);
    Heap_FreeAux(sister);
    return sister;
}
CLEAN_AS(func_ov004_02222af8, TailorSister_Delete)

/* func_ov004_02222b24: the days the current player has talked with it set to `days`. The
 * character is not used. */
void TailorSister_SetTalkDays(TailorSister *sister, int days)
{
    (void) sister;
    PlayerField2416_SetByte08(ts_current_field(), days);
}
CLEAN_AS(func_ov004_02222b24, TailorSister_SetTalkDays)

/* func_ov004_02222b3c: the days the current player has talked with it. The character is not
 * used. */
int TailorSister_TalkDays(TailorSister *sister)
{
    (void) sister;
    return PlayerField2416_Byte08(ts_current_field());
}
CLEAN_AS(func_ov004_02222b3c, TailorSister_TalkDays)

/* func_ov004_02222b54 (vtable slot 0x4c, told of an event about it by `participant`'s system, 4
 * for this one), then the base class's handling (SceneObject_Vfunc4c):
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused (state 6); this one's (with the object ours): owned and held by this system,
 *   paused;
 * - 0, the player talks to it: the participant kept; another system's (not this one's slot):
 *   owned and held by it (state 5); this one's (with the object ours): owned and held by this
 *   system, and it talks (state 1);
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none, it turns back (state 3); else owned by none and held by this
 *   system, it awaits the session (state 4);
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, it sews. */
void TailorSister_OnEvent(TailorSister *sister, int code, int participant)
{
    switch (code) {
        case TAILOR_SISTER_EVENT_STARTS:
            *ts_part(sister, TAILOR_SISTER_PARTICIPANT) = (u8) participant;
            if (participant != TAILOR_SISTER_PLAYER_ACTOR) {
                ts_set_slots(sister, ts_local_slot(), participant);
                TailorSister_SetState(sister, TAILOR_SISTER_PAUSED);
            } else if (SceneShare_IsOurs(sister->base)) {
                ts_set_slots(sister, ts_local_slot(), ts_local_slot());
                TailorSister_SetState(sister, TAILOR_SISTER_PAUSED);
            }
            break;
        case TAILOR_SISTER_EVENT_TALK:
            *ts_part(sister, TAILOR_SISTER_PARTICIPANT) = (u8) participant;
            if (participant != TAILOR_SISTER_PLAYER_ACTOR && participant != ts_local_slot()) {
                ts_set_slots(sister, participant, participant);
                TailorSister_SetState(sister, TAILOR_SISTER_OTHER);
            } else if (SceneShare_IsOurs(sister->base)) {
                ts_set_slots(sister, ts_local_slot(), ts_local_slot());
                ts_start_talk(sister);
            }
            break;
        case TAILOR_SISTER_EVENT_ENDED:
            if (participant == TAILOR_SISTER_PLAYER_ACTOR) {
                if (LinkGlobal_HoldsScene()) {
                    ts_set_slots(sister, ts_local_slot(), SCENE_SHARE_NO_SLOT);
                    TailorSister_SetState(sister, TAILOR_SISTER_TURN_BACK);
                } else {
                    ts_set_slots(sister, SCENE_SHARE_NO_SLOT, ts_local_slot());
                    TailorSister_SetState(sister, TAILOR_SISTER_AWAIT);
                }
            }
            break;
        case TAILOR_SISTER_EVENT_REFUSED:
            if (SceneShare_IsHeld(sister->base) && SceneShare_IsOurs(sister->base)) {
                int owner = SCENE_SHARE_NO_SLOT;
                int holder = SCENE_SHARE_NO_SLOT;
                if (SceneShare_ReadSlots(sister->base, &owner, &holder) &&
                    (participant == TAILOR_SISTER_PLAYER_ACTOR || participant == holder)) {
                    ts_set_slots(sister, ts_local_slot(), SCENE_SHARE_NO_SLOT);
                    TailorSister_SetState(sister, TAILOR_SISTER_SEW);
                }
            }
            break;
        default:
            break;
    }
    SceneObject_Vfunc4c(sister, code, participant);
}
CLEAN_AS(func_ov004_02222b54, TailorSister_OnEvent)

/* func_ov004_02222cd8 (vtable slot 0x48): whether the player may talk to it: its action idle
 * and no system holding it. */
int TailorSister_MayAct(TailorSister *sister)
{
    if (SceneAction_IsBusy(ts_action_of(sister))) {
        return 0;
    }
    return SceneShare_IsHeld(sister->base) == 0;
}
CLEAN_AS(func_ov004_02222cd8, TailorSister_MayAct)

/* func_ov004_02222d04 (the talk scene's vtable slot 0x18, the player's answer): nothing. */
void TailorSisterTalk_OnAnswer(void) {}
CLEAN_AS(func_ov004_02222d04, TailorSisterTalk_OnAnswer)

/* func_ov004_02222d08 (the talk scene's vtable slot 0x14, a message ended): nothing. */
void TailorSisterTalk_OnMessageEnded(void) {}
CLEAN_AS(func_ov004_02222d08, TailorSisterTalk_OnMessageEnded)

/* The message of a talk on a day it was already talked to, by the days of talks: past 12, 40
 * to 44; else one of the row's `count` messages after its first (the row of the day before,
 * from 0 to 11). */
static u8 ts_again_message(unsigned int days)
{
    if (days > TAILOR_SISTER_LINE_DAYS) {
        return (u8) (MainRandom_Below(TAILOR_SISTER_LINE_LATE_RANGE) + TAILOR_SISTER_LINE_LATE_FIRST);
    }
    int row = (int) days - 1;
    if (row < 0) {
        row = 0;
    } else if (row > TAILOR_SISTER_LINE_DAYS - 1) {
        row = TAILOR_SISTER_LINE_DAYS - 1;
    }
    int pick = (int) MainRandom_Below(data_ov004_022476f8[row].count) + 1;
    return (u8) (pick + data_ov004_022476f8[row].first);
}

/* Whether the other speaker joins in at `message` of "sp_npc_osister". */
static int ts_message_has_second_speaker(u8 message)
{
    switch (message) {
        case 2:
        case 5:
        case 8:
        case 9:
        case 12:
        case 15:
        case 17:
        case 18:
        case 19:
        case 21:
        case 23:
        case 24:
        case 27:
        case 28:
        case 30:
        case 40:
        case 43:
            return 1;
        default:
            return 0;
    }
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int ts_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, TAILOR_SISTER_VARIABLE) != 0;
}

/* func_ov004_02222d0c (the talk scene's vtable slot 0x78, the line to say):
 * - linked (or with the game variable 0x4a set): message 0x57 of "sp_npc_osister";
 * - when a game is being started anew (StartKind_IsSet): message 5 of "sp_etc_sequence4";
 * - with the player's dated event of kind 2 today: its message by event and part (the table
 *   data_ov004_022476dc) of "sp_npc_drama3", the event noted as told and its part marked;
 * - else from "sp_npc_osister", by the days the player has talked with it: at the first talk of
 *   the day the row's first message (past 11 days, the weekday's, 33 to 39), else
 *   ts_again_message.
 * Unlinked, without the variable, a message of "sp_npc_osister" in the list
 * ts_message_has_second_speaker gets the special character 4 as the second speaker when there
 * is one.
 * QUIRK: the table of the dated events' messages has four rows; an event 4 reads its messages
 * from the start of the next table (data_ov004_022476f8). */
void TailorSisterTalk_Line(TailorSisterTalk *talk, TailorSisterLine *out)
{
    u8 event;
    unsigned int days = (unsigned int) TailorSister_TalkDays(talk->owner);
    unsigned int file;
    NetSession *session = data_020ccf94;

    if (ts_linked_or_variable(session)) {
        file = TAILOR_SISTER_FILE_PLAIN;
        out->message = TAILOR_SISTER_LINE_LINKED;
    } else if (StartKind_IsSet()) {
        file = TAILOR_SISTER_FILE_NEW_START;
        out->message = TAILOR_SISTER_LINE_NEW_START;
    } else if (TalkChecks_TodaysEventOfKind((int) (uintptr_t) talk->owner, &event, TAILOR_SISTER_EVENT_KIND)) {
        file = TAILOR_SISTER_FILE_DRAMA;
        talk->owner->dated_event_told = 1;
        out->message = data_ov004_022476dc[DAY_EVENT_INDEX(event) * TAILOR_SISTER_DRAMA_PARTS + DAY_EVENT_PART(event)];
        TalkChecks_MarkDayEvent((int) (uintptr_t) talk->owner, &event);
    } else if (!TalkChecks_TestSetDailyBit(TAILOR_SISTER_DAILY_FIRST_LINE, 1)) {
        if (days >= TAILOR_SISTER_LINE_DAYS) {
            out->message = data_ov004_022476d4[Calendar_TodayWeekday()];
        } else {
            out->message = data_ov004_022476f8[days].first;
        }
        file = TAILOR_SISTER_FILE_PLAIN;
    } else {
        out->message = ts_again_message(days);
        file = TAILOR_SISTER_FILE_PLAIN;
    }
    out->text = data_ov004_02254338[file];

    if (!Session_IsLinked(session) && *GameVariables_Slot(0, TAILOR_SISTER_VARIABLE) == 0 &&
        file == TAILOR_SISTER_FILE_PLAIN && ts_message_has_second_speaker(out->message)) {
        u8 *speaker = Actors_GetDByIndex(TAILOR_SISTER_SECOND_SPEAKER);
        if (speaker != NULL) {
            SceneBase_SetSecondSpeaker(&talk->base, speaker);
        }
    }
}
CLEAN_AS(func_ov004_02222d0c, TailorSisterTalk_Line)

/* func_ov004_02222ec0: its talk scene told through its vtable slot 0x08 and given its owner. */
void TailorSisterTalk_Begin(TailorSisterTalk *talk, TailorSister *owner)
{
    ts_talk_slot_08(talk);
    talk->owner = owner;
}
CLEAN_AS(func_ov004_02222ec0, TailorSisterTalk_Begin)

/* func_ov004_02222edc (the talk scene's vtable slot 0x04): its destructor, then the scene
 * freed. */
TailorSisterTalk *TailorSisterTalk_Delete(TailorSisterTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov004_022543cc;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_ov004_02222edc, TailorSisterTalk_Delete)

/* func_ov004_02222efc (the talk scene's vtable slot 0x00): the destructor of main's class
 * 0x020d9ff8. */
TailorSisterTalk *TailorSisterTalk_Destroy(TailorSisterTalk *talk)
{
    *(const u8 **) (void *) talk = data_ov004_022543cc;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_ov004_02222efc, TailorSisterTalk_Destroy)

/* func_ov004_02222f14: the constructor: a scene of main's class 0x020d9ff8 given this class's
 * vtable. */
TailorSisterTalk *TailorSisterTalk_Construct(TailorSisterTalk *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) (void *) talk = data_ov004_022543cc;
    return talk;
}
CLEAN_AS(func_ov004_02222f14, TailorSisterTalk_Construct)

/* func_ov004_02222f2c: it looks straight ahead. */
void TailorSister_LookAhead(TailorSister *sister)
{
    ts_look(sister, TAILOR_SISTER_LOOK_AHEAD);
}
CLEAN_AS(func_ov004_02222f2c, TailorSister_LookAhead)

/* func_ov004_02222f64 (state 6's update): nothing. 1. */
int TailorSister_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02222f64, TailorSister_UpdatePaused)

/* func_ov004_02222f68 (state 6's entry): the machine stops and the frame its animation is at
 * is kept. 1. */
int TailorSister_EnterPaused(TailorSister *sister)
{
    TailorObject_StopCurrent();
    s32 frame = *(const s32 *) (const void *) ts_part(sister, TAILOR_SISTER_MODEL_FRAME);
    sister->sew_frame = (u16) (frame >> 12);
    return 1;
}
CLEAN_AS(func_ov004_02222f68, TailorSister_EnterPaused)

/* func_ov004_02222f8c (state 5's update): once the object, ours, is owned by no system and
 * this one holds the scene, it is owned by this system and held by none, and it sews. 1. */
int TailorSister_UpdateOther(TailorSister *sister)
{
    if (SceneShare_IsOurs(sister->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(sister->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            ts_set_slots(sister, ts_local_slot(), SCENE_SHARE_NO_SLOT);
            TailorSister_SetState(sister, TAILOR_SISTER_SEW);
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02222f8c, TailorSister_UpdateOther)

/* func_ov004_02222fe4 (state 5's entry): it looks straight ahead. 1. */
int TailorSister_EnterOther(TailorSister *sister)
{
    ts_look(sister, TAILOR_SISTER_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov004_02222fe4, TailorSister_EnterOther)

/* func_ov004_0222301c (state 4's update):
 * - with the object ours: once this system owns and holds it, it is set so again and it talks
 *   to this console's player (state 1); else, once this system holds the scene and no system
 *   holds the object, it is owned by this system and held by none, and it sews;
 * - run by another system, while this one does not hold the scene: the machine runs in step
 *   with its sewing animation, and stops when it plays another while the machine runs. 1. */
int TailorSister_UpdateAwait(TailorSister *sister)
{
    if (SceneShare_IsOurs(sister->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(sister->base, &owner, &holder) && owner == ts_local_slot() && owner == holder) {
            ts_set_slots(sister, ts_local_slot(), ts_local_slot());
            ts_start_talk(sister);
        } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
            ts_set_slots(sister, ts_local_slot(), SCENE_SHARE_NO_SLOT);
            TailorSister_SetState(sister, TAILOR_SISTER_SEW);
        }
    } else if (!LinkGlobal_HoldsScene()) {
        if (ts_sewing(sister)) {
            ts_run_machine(sister);
        } else if (!TailorObject_InState0Or3()) {
            TailorObject_StopCurrent();
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_0222301c, TailorSister_UpdateAwait)

/* func_ov004_02223118 (state 4's entry): it looks straight ahead. 1. */
int TailorSister_EnterAwait(TailorSister *sister)
{
    ts_look(sister, TAILOR_SISTER_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov004_02223118, TailorSister_EnterAwait)

/* func_ov004_02223150 (state 3's update): once its turn is done, it sews. 1. */
int TailorSister_UpdateTurnBack(TailorSister *sister)
{
    if (SceneMotion_Kind(ts_motion_of(sister)) == TAILOR_SISTER_MOTION_TURN && SceneMotion_IsDone(ts_motion_of(sister))) {
        TailorSister_SetState(sister, TAILOR_SISTER_SEW);
    }
    return 1;
}
CLEAN_AS(func_ov004_02223150, TailorSister_UpdateTurnBack)

/* func_ov004_02223180 (state 3's entry): it turns (priority 1) to the angle it faced at its
 * start. 1. */
int TailorSister_EnterTurnBack(TailorSister *sister)
{
    SceneMotion_Request(ts_motion_of(sister), TAILOR_SISTER_MOTION_TURN, 1, 0, 0, 0, sister->home_yaw, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_02223180, TailorSister_EnterTurnBack)

/* func_ov004_022231bc (state 2's update): nothing. 1. */
int TailorSister_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022231bc, TailorSister_UpdateTalked)

/* func_ov004_022231c0 (state 2's entry): 1. */
int TailorSister_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov004_022231c0, TailorSister_EnterTalked)

/* func_ov004_022231c4 (state 1's update): once its action is idle: unlinked, at the first such
 * end of a talk of the day the days of talks grow by one (at most 15); the object's event ends
 * and state 2 follows. 1. */
int TailorSister_UpdateTalk(TailorSister *sister)
{
    if (SceneAction_IsBusy(ts_action_of(sister))) {
        return 1;
    }
    if (!Session_IsLinked(data_020ccf94) && !TalkChecks_TestSetDailyBit(TAILOR_SISTER_DAILY_COUNTED, 1)) {
        unsigned int days = (u8) (TailorSister_TalkDays(sister) + 1);
        if (days > TAILOR_SISTER_MOST_DAYS) {
            days = TAILOR_SISTER_MOST_DAYS;
        }
        TailorSister_SetTalkDays(sister, (int) days);
    }
    EventQueue_FinishObjectEvent(sister);
    TailorSister_SetState(sister, TAILOR_SISTER_TALKED);
    return 1;
}
CLEAN_AS(func_ov004_022231c4, TailorSister_UpdateTalk)

/* func_ov004_02223228 (state 1's entry): from 6 days of talks it looks at the player; the
 * machine stops; below 6 days it talks where it is, else it turns to the talk's partner (none:
 * angle 0) and talks. 1. */
int TailorSister_EnterTalk(TailorSister *sister)
{
    if ((unsigned int) TailorSister_TalkDays(sister) >= TAILOR_SISTER_FAMILIAR_DAYS) {
        ts_look(sister, TAILOR_SISTER_LOOK_PLAYER);
    }
    TailorObject_StopCurrent();
    if ((unsigned int) TailorSister_TalkDays(sister) < TAILOR_SISTER_FAMILIAR_DAYS) {
        SceneAction_RequestTalk(ts_action_of(sister), 1, 0);
    } else {
        int partner = SceneBase_MotionArg(&sister->talk.base);
        int angle = 0;
        if (partner != 0) {
            angle = SceneObject_YawTo(sister->base, (u8 *) (uintptr_t) (u32) partner);
        }
        SceneAction_RequestTurnAndTalk(ts_action_of(sister), 0, angle, 0);
    }
    return 1;
}
CLEAN_AS(func_ov004_02223228, TailorSister_EnterTalk)

/* func_ov004_022232b4 (state 0's update): when it no longer faces where it did at its start, it
 * turns back (state 3); else while it plays its sewing animation the machine runs in step. 1. */
int TailorSister_UpdateSew(TailorSister *sister)
{
    if (sister->home_yaw != *(const s16 *) (const void *) ts_part(sister, TAILOR_SISTER_YAW)) {
        TailorSister_SetState(sister, TAILOR_SISTER_TURN_BACK);
        return 1;
    }
    if (ts_sewing(sister)) {
        ts_run_machine(sister);
    }
    return 1;
}
CLEAN_AS(func_ov004_022232b4, TailorSister_UpdateSew)

/* func_ov004_02223324 (state 0's entry): it looks straight ahead and plays its sewing
 * animation (priority 1) from the frame where it stopped. 1. */
int TailorSister_EnterSew(TailorSister *sister)
{
    ts_look(sister, TAILOR_SISTER_LOOK_AHEAD);
    SceneMotion_RequestAnimation(ts_motion_of(sister), 1, TAILOR_SISTER_SEW_ANIM, 0, data_020c80f8, sister->sew_frame);
    return 1;
}
CLEAN_AS(func_ov004_02223324, TailorSister_EnterSew)

/* func_ov004_02223388: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 6 (the table is not bounded). */
void TailorSister_SetState(TailorSister *sister, int state)
{
    const TailorSisterStep *step = &data_ov004_0225806c[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, sister);
    }
    if (taken != 0) {
        sister->state = state;
    }
}
CLEAN_AS(func_ov004_02223388, TailorSister_SetState)

/* func_ov004_022233cc (vtable slot 0x68, each frame): the machine's part's whole turns kept and
 * shared with the session; then its state's update when it has one, and its answer; else 0.
 * REQUIRES: its state is 0 to 6. */
int TailorSister_Update(TailorSister *sister)
{
    sister->machine_turns = (u8) (TailorObject_PartFrame() / TAILOR_SISTER_MACHINE_TURN_FRAMES);
    SceneShare_SetExtra(sister->base, &sister->machine_turns, 1);
    const TailorSisterStep *step = &data_ov004_0225806c[sister->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, sister);
}
CLEAN_AS(func_ov004_022233cc, TailorSister_Update)

/* func_ov004_02223430 (vtable slot 0x70): its model's file name, "npc_sp/model/hgs.nsbmd". */
const char *TailorSister_ModelName(void)
{
    return data_ov004_02254378;
}
CLEAN_AS(func_ov004_02223430, TailorSister_ModelName)

/* func_ov004_02223438 (vtable slot 0x6c): its texture's file name,
 * "npc_sp/model/hgs_tex.nsbtx". */
const char *TailorSister_TextureName(void)
{
    return data_ov004_022543a8;
}
CLEAN_AS(func_ov004_02223438, TailorSister_TextureName)

/* func_ov004_02223440 (vtable slot 0x00, its start): unless the special character refuses to
 * start, it notes the angle it faces and is held (flag 2 at 0x4e8). Linked (or with the game
 * variable 0x4a set) it sews when this system holds the scene, else it reads the machine's
 * turns from the session and awaits it (state 4). Unlinked it sews, and notes whether the
 * player's dated event of kind 2 is today. Whether it started. */
int TailorSister_Start(TailorSister *sister)
{
    u8 event;

    if (SpecialSceneObject_Start(sister) == 0) {
        return 0;
    }
    sister->home_yaw = *(const s16 *) (const void *) ts_part(sister, TAILOR_SISTER_YAW);
    *(u32 *) (void *) ts_part(sister, TAILOR_SISTER_HELD_FLAGS) |= TAILOR_SISTER_HELD;
    if (ts_linked_or_variable(data_020ccf94)) {
        if (LinkGlobal_HoldsScene()) {
            TailorSister_SetState(sister, TAILOR_SISTER_SEW);
        } else {
            SceneShare_ReadExtra(sister->base, &sister->machine_turns, 1);
            TailorSister_SetState(sister, TAILOR_SISTER_AWAIT);
        }
    } else {
        TailorSister_SetState(sister, TAILOR_SISTER_SEW);
        if (TalkChecks_TodaysEventOfKind((int) (uintptr_t) sister, &event, TAILOR_SISTER_EVENT_KIND)) {
            sister->dated_event_told = 1;
        }
    }
    return 1;
}
CLEAN_AS(func_ov004_02223440, TailorSister_Start)

/* func_ov004_022234e4 (vtable slot 0x04, its set-up): unless the special character refuses, its
 * talk scene becomes its scene and gets it as its owner, and its body (radius 1.1, height 2.0),
 * collider and reach (3.0) are set. Whether it was set up. */
int TailorSister_Init(TailorSister *sister)
{
    if (SpecialSceneObject_Init(sister) == 0) {
        return 0;
    }
    SceneObject_SetScene(sister->base, &sister->talk.base);
    TailorSisterTalk_Begin(&sister->talk, sister);
    SpecialSceneObject_SetBodySize(sister->base, TAILOR_SISTER_BODY_RADIUS, TAILOR_SISTER_BODY_HEIGHT);
    SceneObject_SetColliderSize(sister->base, 0);
    SceneObjectBase_SetReach((SceneObjectBase *) (void *) sister->base, TAILOR_SISTER_REACH);
    return 1;
}
CLEAN_AS(func_ov004_022234e4, TailorSister_Init)

/* func_ov004_0222353c (the create function its record at 0x02254378 names): a zeroed block of 0x714 bytes from the auxiliary heap, constructed: the scene object base, the
 * class 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
TailorSister *TailorSister_Create(void)
{
    TailorSister *sister = (TailorSister *) Heap_AllocAuxZeroed(sizeof(TailorSister));
    if (sister == NULL) {
        return NULL;
    }
    u8 *object = sister->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) ts_part(sister, TAILOR_SISTER_PERSON) = TAILOR_SISTER_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) ts_part(sister, TAILOR_SISTER_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) ts_part(sister, TAILOR_SISTER_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) ts_part(sister, TAILOR_SISTER_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) ts_part(sister, TAILOR_SISTER_ANIM));
    SceneMover_Construct((SceneMover *) (void *) ts_part(sister, TAILOR_SISTER_MOVER));
    SceneProbe_Construct(ts_part(sister, TAILOR_SISTER_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) ts_part(sister, TAILOR_SISTER_VALUE_3AA));
    SceneLook_Construct(ts_look_of(sister));
    SceneTalkState_Construct((SceneTalkState *) (void *) ts_part(sister, TAILOR_SISTER_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) ts_part(sister, TAILOR_SISTER_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) ts_part(sister, TAILOR_SISTER_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) ts_part(sister, TAILOR_SISTER_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) ts_part(sister, TAILOR_SISTER_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) ts_part(sister, TAILOR_SISTER_FOOTSTEPS));
    SceneMotion_Construct(ts_motion_of(sister));
    SceneAction_Construct(ts_action_of(sister));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) ts_part(sister, TAILOR_SISTER_HEAP));
    *(const u8 **) (void *) object = data_ov004_0225445c;
    TailorSisterTalk_Construct(&sister->talk);
    return sister;
}
CLEAN_AS(func_ov004_0222353c, TailorSister_Create)
