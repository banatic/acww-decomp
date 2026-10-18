/* The special character of "sp_npc_missing1" (missing_npc1.h). */
#include "missing_npc1.h"

#include "acre_map.h"
#include "acre_tile.h"
#include "activity.h"
#include "activity_talk.h"
#include "activity_vars.h"
#include "actor.h"
#include "actor_table.h"
#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h" /* MemberFn */
#include "block_021d27ac.h"
#include "camera_control.h"
#include "clean.h"
#include "event_queue.h"
#include "field_label.h"
#include "middle_spot.h"
#include "obj_020d9ff8.h"
#include "paired_town.h"
#include "player_record.h"
#include "player_records.h"
#include "pool_link.h"
#include "scene_action.h"
#include "scene_exit.h"
#include "scene_face.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object.h"
#include "scene_object_members.h"
#include "scene_probe.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "scene_value_3aa.h"
#include "session.h"
#include "sound_emitter.h"
#include "special_scene_object.h"
#include "talk_checks.h"
#include "town_tile.h"
#include "effect_system.h"
#include "main_random.h"
#include "missing_npc2.h"
#include "player_actor_ops.h"
#include "talk_answers.h"
#include "talk_object.h"

static_assert(sizeof(SceneBase) == 0x80, "the scene base");
static_assert(offsetof(MissingNpc1Talk, owner) == 0xb0 && sizeof(MissingNpc1Talk) == 0xb8, "MissingNpc1Talk");
static_assert(offsetof(MissingNpc1, position) == 0x5c && offsetof(MissingNpc1, angle) == 0x8e, "MissingNpc1");
static_assert(offsetof(MissingNpc1, walk_angle) == 0x94 && offsetof(MissingNpc1, flags) == 0x4e8, "MissingNpc1");
static_assert(offsetof(MissingNpc1, solid) == 0x510 && offsetof(MissingNpc1, local) == 0x563, "MissingNpc1");
static_assert(offsetof(MissingNpc1, state) == 0x654 && offsetof(MissingNpc1, talk) == 0x658, "MissingNpc1");
static_assert(offsetof(MissingNpc1, declined) == 0x711 && offsetof(MissingNpc1, last_position) == 0x718, "MissingNpc1");
static_assert(offsetof(MissingNpc1, effect) == 0x724 && offsetof(MissingNpc1, step) == 0x728, "MissingNpc1");
static_assert(sizeof(MissingNpc1) == 0x72c, "MissingNpc1");

/* The members of the scene object, by place (scene_object.h). */
#define MISSING_NPC1_PERSON 0x0ea /* u16: the person code */
#define MISSING_NPC1_MODEL 0x0ec
#define MISSING_NPC1_ANIM_FRAME 0x190 /* fx32: the body animation's frame */
#define MISSING_NPC1_STANDARD_ANIMS 0x2a0
#define MISSING_NPC1_FACE 0x2ac
#define MISSING_NPC1_ANIM 0x334
#define MISSING_NPC1_MOVER 0x350
#define MISSING_NPC1_PROBE 0x3a8
#define MISSING_NPC1_VALUE_3AA 0x3aa
#define MISSING_NPC1_LOOK 0x3b0
#define MISSING_NPC1_TALK_STATE 0x418
#define MISSING_NPC1_EFFECTS 0x420
#define MISSING_NPC1_JOINT_16_POINT 0x478 /* Vec3 */
#define MISSING_NPC1_COLLIDER 0x49c
#define MISSING_NPC1_CARRIER 0x4cc
#define MISSING_NPC1_EMITTER 0x514
#define MISSING_NPC1_FOOTSTEPS 0x558
#define MISSING_NPC1_MOTION 0x564
#define MISSING_NPC1_ACTION 0x618
#define MISSING_NPC1_HEAP 0x640

#define MISSING_NPC1_SIZE 0x72c
#define MISSING_NPC1_NO_PERSON 0xfff1
#define MISSING_NPC1_HELD 2 /* the scene object's flag at 0x4e8 (scene_object.c) */
#define MISSING_NPC1_NO_EFFECT (-1)

/* The scenes it acts in (SceneQuery_Current). */
#define MISSING_NPC1_SCENE_TOWN 0x00
#define MISSING_NPC1_SCENE_B 0x0b
#define MISSING_NPC1_SCENE_C 0x0c
#define MISSING_NPC1_SCENE_2F_ID 0x2f

/* The field actor that is the player. */
#define MISSING_NPC1_PLAYER_ACTOR 4

/* The kinds of motion it asks for (scene_motion_kinds.h) and its looks (scene_look.h). */
#define MISSING_NPC1_STAND 0
#define MISSING_NPC1_WALK 1
#define MISSING_NPC1_WALK_2 2
#define MISSING_NPC1_TURN 3
#define MISSING_NPC1_LOOK_AHEAD 0
#define MISSING_NPC1_LOOK_PLAYER 1
#define MISSING_NPC1_ANIM_MODE 1 /* the play mode of its animations */

/* Its animations and effects. */
#define MISSING_NPC1_ANIMATION_53 0x53
#define MISSING_NPC1_STANDARD_54 0x54
#define MISSING_NPC1_EFFECT_54 0x54
#define MISSING_NPC1_ANIMATION_AB 0xab
#define MISSING_NPC1_STANDARD_AC 0xac
#define MISSING_NPC1_ANIMATION_122 0x122
#define MISSING_NPC1_ANIMATION_123 0x123
#define MISSING_NPC1_EFFECT_39 0x39 /* at frame 7 of animation 0x122 */
#define MISSING_NPC1_EFFECT_38 0x38 /* at frame 9 */
#define MISSING_NPC1_LOST_SOUND 0x7db
#define MISSING_NPC1_LOST_VOLUME 0x7f

/* The flags of the player's record it reads and sets (player_record.h). */
#define MISSING_NPC1_FLAG_31 0x31
#define MISSING_NPC1_FLAG_33 0x33
#define MISSING_NPC1_FLAG_39 0x39
/* The daily bit of talk_checks.h it tests and sets. */
#define MISSING_NPC1_DAILY_BIT 0x29

/* Distances (fx32) and frames while following. */
#define MISSING_NPC1_LOSE_DISTANCE 0x6000 /* farther than this, it loses the player */
#define MISSING_NPC1_WALK_DISTANCE 0x2800 /* farther than this, it walks after the player */
#define MISSING_NPC1_STUCK_STEP 0x29      /* moving no more than this a frame counts as stuck */
#define MISSING_NPC1_STUCK_FRAMES 0x28
#define MISSING_NPC1_PAUSE_FRAMES 0x28
#define MISSING_NPC1_TILE 0x2000
#define MISSING_NPC1_GATE_HALF_WIDTH 0x4000
#define MISSING_NPC1_GATE_FRONT 0x1000

/* The talk's message numbers (MissingNpc1Talk_OnMessage, _OnAnswer, _Line). */
#define MISSING_NPC1_MESSAGE_CLEARS_MODE 0x14
#define MISSING_NPC1_MESSAGE_YES 0x1c /* to 0x1e, after answer 0 */
#define MISSING_NPC1_MESSAGE_NO 0x1f  /* to 0x21, after answer 1 */
#define MISSING_NPC1_LINE_HOME 0x14
#define MISSING_NPC1_LINE_SCENE_2F 10 /* the line it says in scene 0x2f */
#define MISSING_NPC1_TALK_SHOWN 5     /* the talk's state once a line is shown */
#define MISSING_NPC1_TALK_MODE 0x14   /* the talk's word cleared after message 0x14 */

/* The person (an actor of table D, actor_table.h) it talks with in scene 0x2f. */
#define MISSING_NPC1_SECOND_SPEAKER 0x23

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define MISSING_NPC1_TALK_SLOT_RESET 2

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define MISSING_NPC1_EVENT_0 0
#define MISSING_NPC1_EVENT_1 1
#define MISSING_NPC1_EVENT_ACT_ENDED 8

/* The vtables: its class, its talk's class, and its base classes'. */
extern const u8 data_020e7c60[];
extern const u8 data_020e7bd0[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* The file names its slots 0x70 and 0x6c give: "npc_sp/model/los.nsbmd" and
 * "npc_sp/model/los_tex.nsbtx". */
extern const char data_020e7b7c[];
extern const char data_020e7bac[];
/* The address of "sp_npc_missing1", the archive of its lines. */
extern const char *const data_020e7ad8;
/* The states' entries and updates (filled at start-up). */
typedef struct MissingNpc1StateFns {
    MemberFn enter;
    MemberFn update;
} MissingNpc1StateFns;
extern MissingNpc1StateFns data_021fbbfc[MISSING_NPC1_STATES];
/* The one that exists, or null. */
extern MissingNpc1 *data_021fbbe0;

/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The session, and the state of the screen (2: shown, activity_process.c). */
extern NetSession *data_020ccf94;
extern u8 data_021c75b8;
#define MISSING_NPC1_SCREEN_SHOWN 2
/* Where the player is put in scene 0x2f. */
extern const Vec3 data_020d3150;
#define MISSING_NPC1_PLAYER_ANGLE 0x35c

/* What is asked of the player's actor numbered `player` in scene 0x2f: whether it is ready
 * (with 1), whether it is still busy (DWCi_GsMalloc is the symbol's name), to be put at a point
 * and angle, and to turn. */
extern int DWCi_GsMalloc(int player);

static u8 *missing_npc1_at(MissingNpc1 *self, u32 offset)
{
    return (u8 *) self + offset;
}

static SceneMotion *missing_npc1_motion(MissingNpc1 *self)
{
    return (SceneMotion *) (void *) missing_npc1_at(self, MISSING_NPC1_MOTION);
}

static SceneLook *missing_npc1_look(MissingNpc1 *self)
{
    return (SceneLook *) (void *) missing_npc1_at(self, MISSING_NPC1_LOOK);
}

static SceneStandardAnims *missing_npc1_standard(MissingNpc1 *self)
{
    return (SceneStandardAnims *) (void *) missing_npc1_at(self, MISSING_NPC1_STANDARD_ANIMS);
}

static SceneAction *missing_npc1_action(MissingNpc1 *self)
{
    return (SceneAction *) (void *) missing_npc1_at(self, MISSING_NPC1_ACTION);
}

static SceneMover *missing_npc1_mover(MissingNpc1 *self)
{
    return (SceneMover *) (void *) missing_npc1_at(self, MISSING_NPC1_MOVER);
}

/* Whether its body plays animation `number`. */
static int missing_npc1_plays(MissingNpc1 *self, int number)
{
    return SpeakerAnim_IsBody((SpeakerAnim *) (void *) missing_npc1_at(self, MISSING_NPC1_ANIM), number,
                              missing_npc1_standard(self));
}

/* A motion of `kind` with the points and angle given (scene_motion_request.h). */
static void missing_npc1_move(MissingNpc1 *self, int kind, int priority, int x, int z, int angle)
{
    SceneMotion_Request(missing_npc1_motion(self), kind, priority, x, z, 0, (s16) angle, 0, 0, data_020c80f8, 0);
}

static void missing_npc1_stand(MissingNpc1 *self)
{
    missing_npc1_move(self, MISSING_NPC1_STAND, 1, 0, 0, 0);
}

static void missing_npc1_play(MissingNpc1 *self, int animation)
{
    SceneMotion_RequestAnimation(missing_npc1_motion(self), 1, animation, MISSING_NPC1_ANIM_MODE, data_020c80f8, 0);
}

static void missing_npc1_look_at(MissingNpc1 *self, u8 kind)
{
    SceneLook_Request(missing_npc1_look(self), kind, 0, 0, &data_021fbee8, MISSING_NPC1_PLAYER_ACTOR, data_020c814c, 1);
}

static void missing_npc1_set_standard(MissingNpc1 *self, int first, int second)
{
    SceneStandardAnims_SetFirst(missing_npc1_standard(self), first);
    SceneStandardAnims_SetSecond(missing_npc1_standard(self), second);
}

/* The middle spot of the town (part 0x0c of data_021d27ac). */
static MiddleSpot *missing_npc1_spot(void)
{
    return (MiddleSpot *) (void *) Block021d27ac_Part0C(Block021d27ac_Get());
}

/* The current player's paired town (paired_town.h). */
static u8 *missing_npc1_pairing(void)
{
    return PlayerRecord_Field242C(PlayerRecords_Current());
}

/* The point of the town's gate (building 0x500b) into `point`.
 * REQUIRES: the town has its gate. Without one the ROM leaves `point` as the stack held it;
 * here it is zero. */
static void missing_npc1_gate(Vec3 *point)
{
    AcreMap_HasBuilding500b((int) AcreMap_Town(), (int) (uintptr_t) point, 0, 0);
}

static int missing_npc1_add(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

/* The member function `fn` called on the object, as a C++ pointer to member function: the
 * object moved by half the adjustment and, for a virtual one, the entry `ptr` bytes into its
 * vtable. */
static int missing_npc1_call(const MemberFn *fn, MissingNpc1 *self)
{
    typedef int (*MissingNpc1Step)(void *self);
    uintptr_t object = (uintptr_t) self + (uintptr_t) (intptr_t) ((fn->adj - (fn->adj & 1)) / 2);
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) object;
        target = *(const u32 *) (vtable + fn->ptr);
    }
    return ((MissingNpc1Step) target)((void *) object);
}

/* The talk scene's vtable slot `slot` called with no argument. */
static void missing_npc1_talk_slot(MissingNpc1Talk *talk, int slot)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(MissingNpc1Talk *))(uintptr_t) vtable[slot])(talk);
}

/* ---- Overlay 48's questions */

/* func_020c1874: the one that exists (if any) set to follow the player, unless it does. */
void MissingNpc1_StartFollowing(void)
{
    if (data_021fbbe0 != NULL && data_021fbbe0->state != MISSING_NPC1_FOLLOW) {
        MissingNpc1_SetState(data_021fbbe0, MISSING_NPC1_FOLLOW);
    }
}
CLEAN_AS(func_020c1874, MissingNpc1_StartFollowing)

/* func_020c189c: the one that exists (if any) set to stand facing the player, unless it does. */
void MissingNpc1_StopToFacePlayer(void)
{
    MissingNpc1 *self = data_021fbbe0;
    if (self != NULL && self->state != MISSING_NPC1_FACE_PLAYER) {
        MissingNpc1_SetState(self, MISSING_NPC1_FACE_PLAYER);
    }
}
CLEAN_AS(func_020c189c, MissingNpc1_StopToFacePlayer)

/* func_020c18c4: with one in existence, whether its face plays animation 0xba
 * (SceneFace_AnimB) while it stands facing the player; 1 without one. */
int MissingNpc1_IsFacingPlayerAtBA(void)
{
    if (data_021fbbe0 == NULL) {
        return 1;
    }
    SceneFace *face = (SceneFace *) (void *) missing_npc1_at(data_021fbbe0, MISSING_NPC1_FACE);
    return SceneFace_AnimB(face) == 0xba && data_021fbbe0->state == MISSING_NPC1_FACE_PLAYER;
}
CLEAN_AS(func_020c18c4, MissingNpc1_IsFacingPlayerAtBA)

/* ---- Its talk scene */

/* func_020c1904 (the talk's slot 0x18): the player's answer to lines 0-9, 25-27 and 34-36.
 * Answer 0: the next message is 28, 29 or 30 at random and the middle spot is marked.
 * Answer 1: the next message is 31, 32 or 33 at random, the spot's mark is cleared in the
 * town, and the owner notes the answer (declined). Other answers and lines change nothing. */
void MissingNpc1Talk_OnAnswer(MissingNpc1Talk *talk)
{
    u8 line = talk->scene.receiver[0x1e - 4];
    int asked = line <= 9 || (line >= 25 && line <= 27) || (line >= 34 && line <= 36);
    if (!asked) {
        return;
    }
    u8 message;
    switch (TalkAnswers_Picked(TalkObject_Answers((TalkObject *) (void *) talk->scene.talk))) {
        case 0:
            message = (u8) (MainRandom_Below(3) + MISSING_NPC1_MESSAGE_YES);
            TalkObject_SetMessage((TalkObject *) (void *) talk->scene.talk, &message, data_020e7ad8);
            MiddleSpot_SetMark(missing_npc1_spot());
            break;
        case 1:
            message = (u8) (MainRandom_Below(3) + MISSING_NPC1_MESSAGE_NO);
            TalkObject_SetMessage((TalkObject *) (void *) talk->scene.talk, &message, data_020e7ad8);
            if (SceneQuery_Current() == MISSING_NPC1_SCENE_TOWN) {
                MiddleSpot_ClearMark(missing_npc1_spot());
            }
            talk->owner->declined = 1;
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020c1904, MissingNpc1Talk_OnAnswer)

/* func_020c19ec (the talk's slot 0x14): after message 0x14, the talk's word 0x14 cleared. */
void MissingNpc1Talk_OnMessage(MissingNpc1Talk *talk)
{
    if (talk->scene.receiver[0x1e - 4] == MISSING_NPC1_MESSAGE_CLEARS_MODE) {
        *(s32 *) (void *) (talk->scene.talk + MISSING_NPC1_TALK_MODE) = 0;
    }
}
CLEAN_AS(func_020c19ec, MissingNpc1Talk_OnMessage)

/* func_020c19fc (the talk's slot 0x10): the name of the current player's paired town put into
 * the talk's text slots 0 and 1; the second's answer. */
int MissingNpc1Talk_PutTownNames(MissingNpc1Talk *talk)
{
    u8 *pairing = missing_npc1_pairing();
    SceneBase_PutNameAt2(&talk->scene, (unsigned int) (uintptr_t) PairedTown_Town(pairing), 0);
    return (int) (uintptr_t) SceneBase_PutNameAt2(&talk->scene, (unsigned int) (uintptr_t) PairedTown_Town(pairing), 1);
}
CLEAN_AS(func_020c19fc, MissingNpc1Talk_PutTownNames)

/* func_020c1a34 (the talk's slot 0x78): the line to say for the topic, with the archive's
 * name, and the owner's note of answer 1 cleared. The first two topics set the player's flag
 * 0x33 first; the third sets the daily bit 0x29 after drawing its line. A topic of 7 or more
 * leaves the message as it was. */
void MissingNpc1Talk_Line(MissingNpc1Talk *talk, MissingNpc1Line *line)
{
    u8 *record = PlayerRecords_Current();
    line->name = (u32) (uintptr_t) data_020e7ad8;
    switch (MissingNpc1Talk_Topic(talk)) {
        case MISSING_NPC1_TOPIC_FIRST:
            PlayerRecord_SetFlag(record, MISSING_NPC1_FLAG_33);
            line->message = 0;
            break;
        case MISSING_NPC1_TOPIC_AGAIN:
            PlayerRecord_SetFlag(record, MISSING_NPC1_FLAG_33);
            line->message = (u8) (MainRandom_Below(3) + 1);
            break;
        case MISSING_NPC1_TOPIC_TODAY:
            line->message = (u8) (MainRandom_Below(3) + 4);
            TalkChecks_TestSetDailyBit(MISSING_NPC1_DAILY_BIT, 1);
            break;
        case MISSING_NPC1_TOPIC_FOLLOWING:
            line->message = (u8) (MainRandom_Below(3) + 7);
            break;
        case MISSING_NPC1_TOPIC_LOST:
            line->message = (u8) (MainRandom_Below(3) + 0x19);
            break;
        case MISSING_NPC1_TOPIC_MARKED:
            line->message = (u8) (MainRandom_Below(3) + 0x22);
            break;
        case MISSING_NPC1_TOPIC_HOME:
            line->message = MISSING_NPC1_LINE_HOME;
            break;
        default:
            break;
    }
    talk->owner->declined = 0;
}
CLEAN_AS(func_020c1a34, MissingNpc1Talk_Line)

/* func_020c1ae4 (the talk's slot 0x38): the owner's standard animations set to 0 and 1, then
 * the focus speaker's talking motion in `style` (SceneBase_FocusTalkStyle). */
void MissingNpc1Talk_SetTalkStyle(MissingNpc1Talk *talk, int style)
{
    missing_npc1_set_standard(talk->owner, 0, 1);
    SceneBase_FocusTalkStyle(&talk->scene, style);
}
CLEAN_AS(func_020c1ae4, MissingNpc1Talk_SetTalkStyle)

/* func_020c1b20 */
u32 MissingNpc1Talk_Topic(MissingNpc1Talk *talk)
{
    return talk->topic;
}
CLEAN_AS(func_020c1b20, MissingNpc1Talk_Topic)

/* func_020c1b28 */
void MissingNpc1Talk_SetTopic(MissingNpc1Talk *talk, u32 topic)
{
    talk->topic = topic;
}
CLEAN_AS(func_020c1b28, MissingNpc1Talk_SetTopic)

/* func_020c1b30: the scene reset (its vtable slot 2), then given its owner. */
void MissingNpc1Talk_SetOwner(MissingNpc1Talk *talk, MissingNpc1 *owner)
{
    missing_npc1_talk_slot(talk, MISSING_NPC1_TALK_SLOT_RESET);
    talk->owner = owner;
}
CLEAN_AS(func_020c1b30, MissingNpc1Talk_SetOwner)

/* func_020c1b4c (the talk's slot 0x04): destructed, then freed (Heap_OperatorDeleteB). */
MissingNpc1Talk *MissingNpc1Talk_DestructDelete(MissingNpc1Talk *talk)
{
    *(const u8 **) (void *) talk = data_020e7bd0;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_020c1b4c, MissingNpc1Talk_DestructDelete)

/* func_020c1b6c (the talk's slot 0x00): the destructor. */
MissingNpc1Talk *MissingNpc1Talk_Destruct(MissingNpc1Talk *talk)
{
    *(const u8 **) (void *) talk = data_020e7bd0;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_020c1b6c, MissingNpc1Talk_Destruct)

/* func_020c1b84: the constructor: a scene of class 0x020d9ff8 given the class's vtable. */
MissingNpc1Talk *MissingNpc1Talk_Construct(MissingNpc1Talk *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) (void *) talk = data_020e7bd0;
    return talk;
}
CLEAN_AS(func_020c1b84, MissingNpc1Talk_Construct)

/* ---- The states */

/* func_020c1b9c: the walk of scene 0x2f, a step a frame on `step`:
 * 0: waits for the screen to be shown and the player to be ready;
 * 1: the player put at data_020d3150, and a walk to (0xe000, 0x10800);
 * 2: once the player and the walk are done: the topic "home", a look at the player, standing,
 *    and its talk;
 * 3: once the talk's line is shown: the talk held, a walk with priority 2 to (0xea00,
 *    0x12e00), "sp_npc_missing2" set to its state 4 and the camera to mode 19;
 * 4: once there: standing, looking at the player, actor 0x23 as the second speaker (when it
 *    exists), and the talk given line 10 to show and released;
 * 5: once its action ends: a turn towards (0xde00, 0x13a00);
 * 6: once turned: a walk there, the player turned, and "sp_npc_missing2" set to its state 6;
 * 7, 8: then a turn to angle 0 and a walk to (0xf000, 0x1d000);
 * 9: once there: unless the player is this system's, the message 10 of the field label until
 *    the activity's byte 0xd6 is set; then
 * 10: the scene exits: when the session's slot 0 is this system's, the current player's paired
 *    town reset when it has flag 4, flag 0x39 set, the player's paired town reset, the middle
 *    spot cleared and exit 1 taken; then this system's player resets its own paired town,
 *    clears the spot, sets flag 0x31 and takes exit 0, any other takes exit 1.
 * Always 1. */
int MissingNpc1_UpdateScene2F(MissingNpc1 *self)
{
    int player = ActivityVars_Slot3C1C();
    NetSession *session = data_020ccf94;
    int local = session->local_player;
    u8 *player_record = PlayerRecords_OfPlayer(player);
    ActivityTalk *talk = (ActivityTalk *) (void *) self->talk.scene.talk;

    switch (self->step) {
        case 0:
            if (data_021c75b8 == MISSING_NPC1_SCREEN_SHOWN && PlayerActorOps_SwitchFlag10(1, player) != 0) {
                self->step = 1;
            }
            break;
        case 1: {
            Vec3 point = data_020d3150;
            PlayerActorOps_MoveTo(&point, MISSING_NPC1_PLAYER_ANGLE, player);
            missing_npc1_move(self, MISSING_NPC1_WALK, 1, 0xe000, 0x10800, 0);
            self->step = 2;
            break;
        }
        case 2:
            if (DWCi_GsMalloc(player) != 0 || !SceneMotion_IsDone(missing_npc1_motion(self))) {
                break;
            }
            self->step = 3;
            MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_HOME);
            missing_npc1_look_at(self, MISSING_NPC1_LOOK_AHEAD);
            missing_npc1_stand(self);
            SceneAction_RequestTalk(missing_npc1_action(self), 0, 1);
            break;
        case 3:
            if (talk->state != MISSING_NPC1_TALK_SHOWN) {
                break;
            }
            TalkObject_Hold((TalkObject *) talk);
            missing_npc1_move(self, MISSING_NPC1_WALK_2, 2, 0xea00, 0x12e00, 0);
            MissingNpc2_StartScene2FWalk();
            CameraControl_SetMode19();
            self->step = 4;
            break;
        case 4: {
            if (!SceneMotion_IsDone(missing_npc1_motion(self))) {
                break;
            }
            missing_npc1_stand(self);
            missing_npc1_look_at(self, MISSING_NPC1_LOOK_PLAYER);
            u8 *second = (u8 *) Actors_GetDByIndex(MISSING_NPC1_SECOND_SPEAKER);
            if (second != NULL) {
                SceneBase_SetSecondSpeaker(&self->talk.scene, second);
            }
            u8 message = MISSING_NPC1_LINE_SCENE_2F;
            TalkObject_SetMessage((TalkObject *) talk, &message, data_020e7ad8);
            talk->request = 1;
            TalkObject_Release((TalkObject *) talk);
            self->step = 5;
            break;
        }
        case 5: {
            if (SceneAction_IsBusy(missing_npc1_action(self))) {
                break;
            }
            Vec3 point = {0xde00, 0, 0x13a00};
            missing_npc1_move(self, MISSING_NPC1_TURN, 1, 0, 0, Vec_YawTo(&self->position, &point));
            self->step = 6;
            break;
        }
        case 6:
            if (!SceneMotion_IsDone(missing_npc1_motion(self))) {
                break;
            }
            missing_npc1_move(self, MISSING_NPC1_WALK, 1, 0xde00, 0x13a00, 0);
            PlayerActorOps_Turn(0, player);
            MissingNpc2_StartScene2FExit();
            self->step = 7;
            break;
        case 7:
            if (!SceneMotion_IsDone(missing_npc1_motion(self))) {
                break;
            }
            missing_npc1_move(self, MISSING_NPC1_TURN, 1, 0, 0, 0);
            self->step = 8;
            break;
        case 8:
            if (!SceneMotion_IsDone(missing_npc1_motion(self))) {
                break;
            }
            missing_npc1_move(self, MISSING_NPC1_WALK, 1, 0xf000, 0x1d000, 0);
            self->step = 9;
            break;
        case 9:
            if (!SceneMotion_IsDone(missing_npc1_motion(self))) {
                break;
            }
            if (player != local && Activity_CurrentByteD6() == 0) {
                FieldLabel_ShowMessage10();
            } else {
                self->step = 10;
            }
            break;
        case 10:
            if (Session_IsLocalSlot(session, 0)) {
                u8 *pairing = missing_npc1_pairing();
                if (PairedTown_Flag4(pairing) == 1) {
                    PairedTown_Reset(pairing);
                }
                PlayerRecord_SetFlag(PlayerRecords_Current(), MISSING_NPC1_FLAG_39);
                PairedTown_Reset(PlayerRecord_Field242C(player_record));
                MiddleSpot_Clear(missing_npc1_spot());
                SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 1);
            }
            if (player == local) {
                PairedTown_Reset(missing_npc1_pairing());
                MiddleSpot_Clear(missing_npc1_spot());
                PlayerRecord_SetFlag(PlayerRecords_Current(), MISSING_NPC1_FLAG_31);
                SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 0);
            } else {
                SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), 1);
            }
            self->step = 11;
            break;
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_020c1b9c, MissingNpc1_UpdateScene2F)

/* func_020c1fb8: the walk of scene 0x2f begins at its first step. */
char MissingNpc1_EnterScene2F(MissingNpc1 *self)
{
    self->step = 0;
    return 1;
}
CLEAN_AS(func_020c1fb8, MissingNpc1_EnterScene2F)

/* func_020c1fc8: during animation 0x122, effect 0x39 at its frame 7 and effect 0x38 at frame
 * 9 (at its position and angle), and once its motion is done, animation 0x123; once that is
 * done, state MISSING_NPC1_ANIM_53. Always 1.
 * QUIRK: the frame is the animation frame's whole part, taken to 16 bits. */
int MissingNpc1_UpdateLost(MissingNpc1 *self)
{
    if (missing_npc1_plays(self, MISSING_NPC1_ANIMATION_122)) {
        s16 angle = self->angle;
        Vec3 point = self->position;
        u32 frame = *(const u32 *) (const void *) missing_npc1_at(self, MISSING_NPC1_ANIM_FRAME);
        u32 whole = (frame << 4) >> 16;
        if (whole == 7) {
            EffectSystem_StartKind(MISSING_NPC1_EFFECT_39, &point, &angle, 0);
        }
        if (whole == 9) {
            EffectSystem_StartKind(MISSING_NPC1_EFFECT_38, &point, &angle, 0);
        }
        if (SceneMotion_IsDone(missing_npc1_motion(self))) {
            missing_npc1_play(self, MISSING_NPC1_ANIMATION_123);
        }
    }
    if (missing_npc1_plays(self, MISSING_NPC1_ANIMATION_123) && SceneMotion_IsDone(missing_npc1_motion(self))) {
        MissingNpc1_SetState(self, MISSING_NPC1_ANIM_53);
    }
    return 1;
}
CLEAN_AS(func_020c1fc8, MissingNpc1_UpdateLost)

/* func_020c2098: the middle spot's mark cleared in the town, animation 0x122, the topic "lost"
 * and the sound 0x7db. Always 1. */
int MissingNpc1_EnterLost(MissingNpc1 *self)
{
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_TOWN) {
        MiddleSpot_ClearMark(missing_npc1_spot());
    }
    missing_npc1_play(self, MISSING_NPC1_ANIMATION_122);
    MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_LOST);
    SoundEmitter_PlayB((SoundEmitter *) (void *) missing_npc1_at(self, MISSING_NPC1_EMITTER), MISSING_NPC1_LOST_SOUND,
                       MISSING_NPC1_LOST_VOLUME, 0);
    return 1;
}
CLEAN_AS(func_020c2098, MissingNpc1_EnterLost)

/* func_020c2104: following the player. With a current player:
 * - it becomes solid once in front of the gate (in the town: its tile's centre further along
 *   z than the gate's point) or, in scene 0xb, once before the centre of tile (6, 15);
 * - with the player's actor present: in the town (or in scene 0xc while the paired town lacks
 *   flag 5), while walking (motion kind 2): farther than 0x6000 from the player it is lost
 *   (MISSING_NPC1_LOST); moving no more than 0x29 a frame or blocked ahead for 40 frames, it
 *   stops (MISSING_NPC1_ANIM_53); else the count starts again;
 * - farther than 0x2800 from the player it walks after it (kind 2, to the player's point),
 *   else it stands.
 * Always 1. */
int MissingNpc1_UpdateFollow(MissingNpc1 *self)
{
    u8 *record = PlayerRecords_Current();
    if (record == NULL) {
        return 1;
    }
    if (self->solid == 0 && SceneQuery_Current() == MISSING_NPC1_SCENE_TOWN) {
        Vec3 gate = {0, 0, 0};
        Vec3 here;
        missing_npc1_gate(&gate);
        AcreTile_SnapToTileCentre(&here, &self->position);
        if (here.z > gate.z) {
            self->solid = 1;
        }
    }
    if (self->solid == 0 && SceneQuery_Current() == MISSING_NPC1_SCENE_B) {
        Vec3 here;
        Vec3 tile;
        AcreTile_SnapToTileCentre(&here, &self->position);
        AcreTile_TileCentre(&tile, 6, 0xf);
        if (here.z < tile.z) {
            self->solid = 1;
        }
    }
    Vec3 *target = PlayerActorOps_StartPosition(MISSING_NPC1_PLAYER_ACTOR);
    if (target == NULL) {
        return 1;
    }
    int distance = SceneObject_DistanceToActor((u8 *) self, MISSING_NPC1_PLAYER_ACTOR);

    int checks = SceneQuery_Current() == MISSING_NPC1_SCENE_TOWN ||
                 (SceneQuery_Current() == MISSING_NPC1_SCENE_C && PairedTown_Flag5(PlayerRecord_Field242C(record)) == 0);
    if (checks && SceneMotion_Kind(missing_npc1_motion(self)) == MISSING_NPC1_WALK_2) {
        if (distance > MISSING_NPC1_LOSE_DISTANCE) {
            MissingNpc1_SetState(self, MISSING_NPC1_LOST);
            return 1;
        }
        int blocked = SceneProbe_Bits(missing_npc1_at(self, MISSING_NPC1_PROBE));
        int step = Vec_DistanceXZ(&self->last_position, &self->position);
        self->last_position = self->position;
        if (step <= MISSING_NPC1_STUCK_STEP || blocked != 0) {
            if (Countdown_Tick16(&self->stuck_count) == 0) {
                MissingNpc1_SetState(self, MISSING_NPC1_ANIM_53);
                return 1;
            }
        } else {
            self->stuck_count = MISSING_NPC1_STUCK_FRAMES;
        }
    }

    if (distance > MISSING_NPC1_WALK_DISTANCE) {
        if (SceneMotion_Kind(missing_npc1_motion(self)) != MISSING_NPC1_WALK_2) {
            missing_npc1_move(self, MISSING_NPC1_WALK_2, 1, 0, 0, 0);
        }
        SceneMover_SetStart(missing_npc1_mover(self), target);
    } else if (SceneMotion_Kind(missing_npc1_motion(self)) != MISSING_NPC1_STAND) {
        missing_npc1_stand(self);
    }
    return 1;
}
CLEAN_AS(func_020c2104, MissingNpc1_UpdateFollow)

/* func_020c22c4: no longer held, the stuck count at 40 and its position noted. Always 1. */
int MissingNpc1_EnterFollow(MissingNpc1 *self)
{
    self->flags &= ~(u32) MISSING_NPC1_HELD;
    self->stuck_count = MISSING_NPC1_STUCK_FRAMES;
    self->last_position = self->position;
    return 1;
}
CLEAN_AS(func_020c22c4, MissingNpc1_EnterFollow)

/* func_020c2300: when the pause has counted down, MISSING_NPC1_FOLLOW. Always 1. */
int MissingNpc1_UpdatePause(MissingNpc1 *self)
{
    if (Countdown_Tick16(&self->pause_count) == 0) {
        MissingNpc1_SetState(self, MISSING_NPC1_FOLLOW);
    }
    return 1;
}
CLEAN_AS(func_020c2300, MissingNpc1_UpdatePause)

/* func_020c2324: no longer held, and a pause of 40 frames. Always 1. */
int MissingNpc1_EnterPause(MissingNpc1 *self)
{
    self->flags &= ~(u32) MISSING_NPC1_HELD;
    self->pause_count = MISSING_NPC1_PAUSE_FRAMES;
    return 1;
}
CLEAN_AS(func_020c2324, MissingNpc1_EnterPause)

/* func_020c2344: nothing. */
int MissingNpc1_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_020c2344, MissingNpc1_UpdateTalked)

/* func_020c2348: nothing. */
int MissingNpc1_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_020c2348, MissingNpc1_EnterTalked)

/* func_020c234c: once its action ends, its event finished (EventQueue_FinishObjectEvent) and
 * MISSING_NPC1_TALKED. Always 1. */
int MissingNpc1_UpdateTalk(MissingNpc1 *self)
{
    if (!SceneAction_IsBusy(missing_npc1_action(self))) {
        EventQueue_FinishObjectEvent(self);
        MissingNpc1_SetState(self, MISSING_NPC1_TALKED);
    }
    return 1;
}
CLEAN_AS(func_020c234c, MissingNpc1_UpdateTalk)

/* func_020c2378: a look at the player, the standard animations 0xac, and the action that turns
 * it to the object its talk names (its motion argument; angle 0 without one) and talks.
 * Always 1. */
int MissingNpc1_EnterTalk(MissingNpc1 *self)
{
    missing_npc1_look_at(self, MISSING_NPC1_LOOK_PLAYER);
    int target = SceneBase_MotionArg(&self->talk.scene);
    int angle = 0;
    if (target != 0) {
        angle = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) target);
    }
    missing_npc1_set_standard(self, MISSING_NPC1_STANDARD_AC, MISSING_NPC1_STANDARD_AC);
    SceneAction_RequestTurnAndTalk(missing_npc1_action(self), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_020c2378, MissingNpc1_EnterTalk)

/* func_020c23f8: held; when animation 0xab's motion is done, standing with the standard
 * animations 0xac. Always 1. */
int MissingNpc1_UpdateAnimAB(MissingNpc1 *self)
{
    self->flags |= MISSING_NPC1_HELD;
    if (missing_npc1_plays(self, MISSING_NPC1_ANIMATION_AB) && SceneMotion_IsDone(missing_npc1_motion(self))) {
        missing_npc1_stand(self);
        missing_npc1_set_standard(self, MISSING_NPC1_STANDARD_AC, MISSING_NPC1_STANDARD_AC);
    }
    return 1;
}
CLEAN_AS(func_020c23f8, MissingNpc1_UpdateAnimAB)

/* func_020c247c: looking ahead, and animation 0xab. Always 1. */
int MissingNpc1_EnterAnimAB(MissingNpc1 *self)
{
    missing_npc1_look_at(self, MISSING_NPC1_LOOK_AHEAD);
    missing_npc1_play(self, MISSING_NPC1_ANIMATION_AB);
    return 1;
}
CLEAN_AS(func_020c247c, MissingNpc1_EnterAnimAB)

/* func_020c24d8: when animation 0x53's motion is done, standing with the standard animations
 * 0x54; effect 0x54 started (once) and kept at its joint 16's point and its angle. Always 1. */
int MissingNpc1_UpdateAnim53(MissingNpc1 *self)
{
    Vec3 *point = (Vec3 *) (void *) missing_npc1_at(self, MISSING_NPC1_JOINT_16_POINT);
    if (missing_npc1_plays(self, MISSING_NPC1_ANIMATION_53) && SceneMotion_IsDone(missing_npc1_motion(self))) {
        missing_npc1_stand(self);
        missing_npc1_set_standard(self, MISSING_NPC1_STANDARD_54, MISSING_NPC1_STANDARD_54);
    }
    if (self->effect == MISSING_NPC1_NO_EFFECT) {
        self->effect = EffectSystem_StartKind(MISSING_NPC1_EFFECT_54, point, &self->angle, 0);
    }
    if (self->effect != MISSING_NPC1_NO_EFFECT) {
        EffectSystem_MoveHandle(self->effect, point, &self->angle, 0);
    }
    return 1;
}
CLEAN_AS(func_020c24d8, MissingNpc1_UpdateAnim53)

/* func_020c2588: held, looking ahead, animation 0x53; when its tile's centre is behind the
 * gate's point and within 0x4000 of it along x, it is put 0x1000 in front of the gate. Then it
 * is solid. Always 1. */
int MissingNpc1_EnterAnim53(MissingNpc1 *self)
{
    self->flags |= MISSING_NPC1_HELD;
    missing_npc1_look_at(self, MISSING_NPC1_LOOK_AHEAD);
    missing_npc1_play(self, MISSING_NPC1_ANIMATION_53);
    Vec3 gate = {0, 0, 0};
    Vec3 here;
    missing_npc1_gate(&gate);
    AcreTile_SnapToTileCentre(&here, &self->position);
    if (here.z < gate.z && here.x >= missing_npc1_add(gate.x, -MISSING_NPC1_GATE_HALF_WIDTH) &&
        here.x <= missing_npc1_add(gate.x, MISSING_NPC1_GATE_HALF_WIDTH)) {
        self->position.z = missing_npc1_add(gate.z, MISSING_NPC1_GATE_FRONT);
    }
    self->solid = 1;
    return 1;
}
CLEAN_AS(func_020c2588, MissingNpc1_EnterAnim53)

/* func_020c263c: nothing. */
int MissingNpc1_UpdateFacePlayer(void)
{
    return 1;
}
CLEAN_AS(func_020c263c, MissingNpc1_UpdateFacePlayer)

/* func_020c2640: held, looking at the player, standing. Always 1. */
int MissingNpc1_EnterFacePlayer(MissingNpc1 *self)
{
    self->flags |= MISSING_NPC1_HELD;
    missing_npc1_look_at(self, MISSING_NPC1_LOOK_PLAYER);
    missing_npc1_stand(self);
    return 1;
}
CLEAN_AS(func_020c2640, MissingNpc1_EnterFacePlayer)

/* ---- The object */

/* func_020c26b4: the state's entry run (when it has one); unless it answers 0 the state is
 * taken, effect 0x54 stopped first unless the state is MISSING_NPC1_ANIM_53.
 * REQUIRES: `state` is one of the nine. */
void MissingNpc1_SetState(MissingNpc1 *self, int state)
{
    const MemberFn *enter = &data_021fbbfc[state].enter;
    int taken = 1;
    if (enter->ptr != 0) {
        taken = missing_npc1_call(enter, self);
    }
    if (!taken) {
        return;
    }
    if (state != MISSING_NPC1_ANIM_53 && self->effect != MISSING_NPC1_NO_EFFECT) {
        EffectSystem_EndHandle(self->effect);
        self->effect = MISSING_NPC1_NO_EFFECT;
    }
    self->state = state;
}
CLEAN_AS(func_020c26b4, MissingNpc1_SetState)

/* func_020c2718 (slot 0x4c): told of an event. Codes 0 and 1: its talk is reset, given the
 * player's object as its motion argument, and unless the topic is "home" it talks
 * (MISSING_NPC1_TALK). Code 8 (its act ended): the topic "following", then it follows when the
 * middle spot is marked, else MISSING_NPC1_ANIM_AB after answer 1, else
 * MISSING_NPC1_FACE_PLAYER. */
void MissingNpc1_OnEvent(MissingNpc1 *self, int code)
{
    switch (code) {
        case MISSING_NPC1_EVENT_0:
        case MISSING_NPC1_EVENT_1:
            missing_npc1_talk_slot(&self->talk, MISSING_NPC1_TALK_SLOT_RESET);
            SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, MISSING_NPC1_PLAYER_ACTOR));
            if (MissingNpc1Talk_Topic(&self->talk) != MISSING_NPC1_TOPIC_HOME) {
                MissingNpc1_SetState(self, MISSING_NPC1_TALK);
            }
            break;
        case MISSING_NPC1_EVENT_ACT_ENDED:
            MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_FOLLOWING);
            if (MiddleSpot_HasMark(missing_npc1_spot())) {
                MissingNpc1_SetState(self, MISSING_NPC1_FOLLOW);
            } else if (self->declined != 0) {
                MissingNpc1_SetState(self, MISSING_NPC1_ANIM_AB);
            } else {
                MissingNpc1_SetState(self, MISSING_NPC1_FACE_PLAYER);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020c2718, MissingNpc1_OnEvent)

/* func_020c27a8 (slot 0x48): the player may act on it while no action of its runs. */
int MissingNpc1_MayAct(MissingNpc1 *self)
{
    return !SceneAction_IsBusy(missing_npc1_action(self));
}
CLEAN_AS(func_020c27a8, MissingNpc1_MayAct)

/* func_020c27c8 (slot 0x68): the state's update run (when it has one; its answer is the
 * result, else 0); then its position kept in the middle spot in the town, and in scene 0xb
 * while the current player's paired town has flag 5. */
int MissingNpc1_Update(MissingNpc1 *self)
{
    const MemberFn *update = &data_021fbbfc[self->state].update;
    int result = 0;
    if (update->ptr != 0) {
        result = missing_npc1_call(update, self);
    }
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_TOWN) {
        MiddleSpot_SetFromPosition(missing_npc1_spot(), &self->position);
    }
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_B && PairedTown_Flag5(missing_npc1_pairing()) != 0) {
        MiddleSpot_SetFromPosition(missing_npc1_spot(), &self->position);
    }
    return result;
}
CLEAN_AS(func_020c27c8, MissingNpc1_Update)

/* func_020c2858 (slot 0x70): the model's file name. */
int MissingNpc1_ModelName(void)
{
    return (int) (uintptr_t) data_020e7b7c;
}
CLEAN_AS(func_020c2858, MissingNpc1_ModelName)

/* func_020c2860 (slot 0x6c): the texture's file name. */
int MissingNpc1_TextureName(void)
{
    return (int) (uintptr_t) data_020e7bac;
}
CLEAN_AS(func_020c2860, MissingNpc1_TextureName)

/* func_020c2868 (slot 0x0c): unless the base class refuses to leave, it is no longer the one
 * that exists, and in scene 0x2f the event queue's flag 1 is cleared. Whether it left. */
int MissingNpc1_Leave(MissingNpc1 *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    data_021fbbe0 = NULL;
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_2F_ID) {
        EventQueue_ClearFlag1();
    }
    return 1;
}
CLEAN_AS(func_020c2868, MissingNpc1_Leave)

/* func_020c2898 (slot 0x00): unless the base class refuses to start, it becomes the one that
 * exists, without an effect, and starts by the scene:
 * - the town: put at its tile's centre (moved a tile along x and z when there is a building
 *   0x5000 above it, after the tile is checked clear); with the middle spot marked, after scene
 *   0xb it stands a tile before the gate and follows ("following", not solid), else
 *   MISSING_NPC1_ANIM_53 with the topic "marked"; unmarked, MISSING_NPC1_ANIM_53 with the topic
 *   "first" or "again" (by the player's flag 0x31) until the player has flag 0x33, then
 *   "today" or "following" (by the daily bit 0x29);
 * - scene 0xb: following ("following", not solid);
 * - scene 0xc: at the middle spot, following ("following");
 * - scene 0x2f: not solid, the event queue's flag 1 set, and the walk of the scene.
 * Whether it started. (Without a gate, the step to the gate leaves the position as it was.) */
int MissingNpc1_Start(MissingNpc1 *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    data_021fbbe0 = self;
    self->effect = MISSING_NPC1_NO_EFFECT;
    u8 *record = PlayerRecords_Current();

    if (SceneQuery_Current() == MISSING_NPC1_SCENE_TOWN) {
        AcreTile_SnapToTileCentre(&self->position, &self->position);
        if (TownTile_FindItem5000AboveAt(&self->position, 1, NULL, NULL)) {
            TownTile_IsClearAt(&self->position, NULL);
            self->position.x = missing_npc1_add(self->position.x, MISSING_NPC1_TILE);
            self->position.z = missing_npc1_add(self->position.z, MISSING_NPC1_TILE);
        }
        if (MiddleSpot_HasMark(missing_npc1_spot())) {
            if (SceneQuery_Previous() == MISSING_NPC1_SCENE_B) {
                missing_npc1_gate(&self->position);
                self->position.z = missing_npc1_add(self->position.z, -MISSING_NPC1_TILE);
                MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_FOLLOWING);
                MissingNpc1_SetState(self, MISSING_NPC1_FOLLOW);
                self->solid = 0;
            } else {
                MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_MARKED);
                MissingNpc1_SetState(self, MISSING_NPC1_ANIM_53);
            }
        } else if (!PlayerRecord_TestFlag(record, MISSING_NPC1_FLAG_33)) {
            if (!PlayerRecord_TestFlag(record, MISSING_NPC1_FLAG_31)) {
                MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_FIRST);
            } else {
                MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_AGAIN);
            }
            MissingNpc1_SetState(self, MISSING_NPC1_ANIM_53);
        } else {
            if (!TalkChecks_TestSetDailyBit(MISSING_NPC1_DAILY_BIT, 0)) {
                MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_TODAY);
            } else {
                MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_FOLLOWING);
            }
            MissingNpc1_SetState(self, MISSING_NPC1_ANIM_53);
        }
    } else if (SceneQuery_Current() == MISSING_NPC1_SCENE_B) {
        MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_FOLLOWING);
        MissingNpc1_SetState(self, MISSING_NPC1_FOLLOW);
        self->solid = 0;
    } else if (SceneQuery_Current() == MISSING_NPC1_SCENE_C) {
        MiddleSpot_ToPosition(missing_npc1_spot(), &self->position);
        MissingNpc1Talk_SetTopic(&self->talk, MISSING_NPC1_TOPIC_FOLLOWING);
        MissingNpc1_SetState(self, MISSING_NPC1_FOLLOW);
    } else if (SceneQuery_Current() == MISSING_NPC1_SCENE_2F_ID) {
        self->solid = 0;
        EventQueue_SetFlag1();
        MissingNpc1_SetState(self, MISSING_NPC1_SCENE_2F);
    }
    return 1;
}
CLEAN_AS(func_020c2898, MissingNpc1_Start)

/* func_020c2a40 (slot 0x04): unless the base class refuses, its scene is its talk (which gets
 * it as its owner), its walking paces 2 and 1 set, and by the scene: in scenes 0xb and 0xc it
 * faces and walks along -z (angle 0x8000); in scene 0x2f it faces angle 0 at (0xe000, 0x4000)
 * with a faster pace 1. It is not shared. Whether it was set up. */
int MissingNpc1_Init(MissingNpc1 *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    MissingNpc1Talk_SetOwner(&self->talk, self);
    SceneMover_SetPace(missing_npc1_mover(self), 2, 0x333, 0xcc, 0x133);
    SceneMover_SetPace(missing_npc1_mover(self), 1, 0x1b3, 0xcc, 0x133);
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_B) {
        self->angle = (s16) -0x8000;
        self->walk_angle = (s16) -0x8000;
    }
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_C) {
        self->angle = (s16) -0x8000;
        self->walk_angle = (s16) -0x8000;
    }
    if (SceneQuery_Current() == MISSING_NPC1_SCENE_2F_ID) {
        self->angle = 0;
        self->walk_angle = 0;
        self->position.x = 0xe000;
        self->position.z = 0x4000;
        SceneMover_SetPace(missing_npc1_mover(self), 1, 0x280, 0xcc, 0x133);
    }
    self->local = 1;
    return 1;
}
CLEAN_AS(func_020c2a40, MissingNpc1_Init)

/* func_020c1820 (slot 0x40): the destructor: its talk, then the base class's. */
MissingNpc1 *MissingNpc1_Destruct(MissingNpc1 *self)
{
    *(const u8 **) (void *) self = data_020e7c60;
    MissingNpc1Talk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_020c1820, MissingNpc1_Destruct)

/* func_020c1848 (slot 0x44): destructed, then freed to the auxiliary heap. */
MissingNpc1 *MissingNpc1_DestructDelete(MissingNpc1 *self)
{
    *(const u8 **) (void *) self = data_020e7c60;
    MissingNpc1Talk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020c1848, MissingNpc1_DestructDelete)

/* func_020c2b1c (data_020e7b94's create function): a zeroed block of 0x72c bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and
 * members in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link,
 * then the class's vtable and its talk. Null when there is no room. */
MissingNpc1 *MissingNpc1_Create(void)
{
    u8 *object = (u8 *) Heap_AllocAuxZeroed(MISSING_NPC1_SIZE);
    if (object == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) (object + MISSING_NPC1_PERSON) = MISSING_NPC1_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) (object + MISSING_NPC1_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) (object + MISSING_NPC1_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) (object + MISSING_NPC1_FACE));
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) (object + MISSING_NPC1_ANIM));
    SceneMover_Construct((SceneMover *) (void *) (object + MISSING_NPC1_MOVER));
    SceneProbe_Construct(object + MISSING_NPC1_PROBE);
    SceneValue3aa_Clear((SceneValue3aa *) (void *) (object + MISSING_NPC1_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) (object + MISSING_NPC1_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) (object + MISSING_NPC1_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) (object + MISSING_NPC1_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) (object + MISSING_NPC1_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) (object + MISSING_NPC1_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) (object + MISSING_NPC1_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) (object + MISSING_NPC1_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) (object + MISSING_NPC1_MOTION));
    SceneAction_Construct((SceneAction *) (void *) (object + MISSING_NPC1_ACTION));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) (object + MISSING_NPC1_HEAP));
    *(const u8 **) (void *) object = data_020e7c60;
    MissingNpc1 *self = (MissingNpc1 *) (void *) object;
    MissingNpc1Talk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_020c2b1c, MissingNpc1_Create)
