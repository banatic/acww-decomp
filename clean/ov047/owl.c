/* The museum's owl (owl.h): its object's vtable slots and its states. */
#include "owl.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/calendar.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/game_variables.h"
#include "main/layered_model.h"
#include "main/link_global.h"
#include "main/main_random.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_share.h"
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/session.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/talk_checks.h"
#include "owl_talk.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(OwlTalk, drama) == 0xb0 && offsetof(OwlTalk, owner) == 0xb4, "OwlTalk");
static_assert(offsetof(OwlTalk, after) == 0xb8 && offsetof(OwlTalk, next) == 0xc0, "OwlTalk");
static_assert(offsetof(OwlTalk, slot) == 0xc8 && offsetof(OwlTalk, assessing) == 0xcc, "OwlTalk");
static_assert(offsetof(OwlTalk, item) == 0xce && offsetof(OwlTalk, next_line) == 0xd0, "OwlTalk");
static_assert(sizeof(OwlTalk) == 0xd4, "OwlTalk");
static_assert(offsetof(Owl, state) == 0x654 && offsetof(Owl, talk) == 0x658, "Owl");
static_assert(offsetof(Owl, drama_told) == 0x72c && offsetof(Owl, act_countdown) == 0x72e, "Owl");
static_assert(offsetof(Owl, stand_word) == 0x730 && offsetof(Owl, nap_countdown) == 0x732, "Owl");
static_assert(offsetof(Owl, home_angle) == 0x734 && offsetof(Owl, asleep) == 0x736, "Owl");
static_assert(offsetof(Owl, nap_word) == 0x738 && offsetof(Owl, effect) == 0x73c, "Owl");
static_assert(sizeof(Owl) == 0x740, "the size Owl_Create allocates");
static_assert(sizeof(OwlStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define OWL_X 0x5c               /* fx32: its position */
#define OWL_Z 0x64               /* fx32 */
#define OWL_ANGLE 0x8e           /* s16: where it faces */
#define OWL_WALK_ANGLE 0x94      /* s16: where it walks */
#define OWL_PERSON 0xea          /* u16: its person code */
#define OWL_MODEL 0xec           /* LayeredModel */
#define OWL_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define OWL_FACE 0x2ac           /* SceneFace */
#define OWL_ANIM 0x334           /* SpeakerAnim */
#define OWL_MOVER 0x350          /* SceneMover */
#define OWL_PROBE 0x3a8          /* the probe */
#define OWL_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define OWL_LOOK 0x3b0           /* SceneLook */
#define OWL_TALK_STATE 0x418     /* SceneTalkState */
#define OWL_EFFECTS 0x420        /* ActEffects */
#define OWL_JOINT_16_POINT 0x478 /* Vec3: its head, as last drawn */
#define OWL_COLLIDER 0x49c       /* CollisionContacts */
#define OWL_CARRIER 0x4cc        /* FieldOwnedBody */
#define OWL_FLAGS 0x4e8          /* u32: the scene object's flags (2: held) */
#define OWL_EMITTER 0x514        /* SoundEmitterObject */
#define OWL_FOOTSTEPS 0x558      /* Footsteps */
#define OWL_PARTICIPANT 0x560    /* u8: whose system the last event came from */
#define OWL_MOTION 0x564         /* SceneMotion */
#define OWL_ACTION 0x618         /* SceneAction */
#define OWL_HEAP 0x640           /* PoolLink */

#define OWL_NO_PERSON 0xfff1
#define OWL_HELD 2
#define OWL_NO_EFFECT (-1)

/* The field actor of this console's player, and whom an event is for when it is for it. */
#define OWL_PLAYER_ACTOR 4
#define OWL_THIS_PLAYER 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define OWL_EVENT_TALK 0
#define OWL_EVENT_STARTS 3
#define OWL_EVENT_REFUSED 4
#define OWL_EVENT_ENDED 8

/* The vtable slot of its talk scene that resets it (OwlTalk_Reset). */
#define OWL_TALK_SLOT_RESET 0x08

/* The game variable (bank 0) that, when set, makes it act as when linked. */
#define OWL_VARIABLE 0x4a

/* The looks it asks for (SceneLook_Request): straight ahead and the player. */
#define OWL_LOOK_AHEAD 0
#define OWL_LOOK_PLAYER 1

/* The motions it asks for (scene_motion_request.h): a turn, its act and its sleep. */
#define OWL_MOTION_TURN 3
#define OWL_MOTION_ACT 10
#define OWL_ANIM_ASLEEP 0xf0
/* The word of the stand after its act and of the animation it falls asleep with. */
#define OWL_WORD_BLEND 0x18

/* The dated events (day_events.h) it tells: kind 1. */
#define OWL_EVENT_KIND 1
/* The frames before it acts on such a day: 100 and 20 times 0 to 4 more. */
#define OWL_ACT_FRAMES 100
#define OWL_ACT_FRAMES_STEP 20
#define OWL_ACT_FRAMES_STEPS 5
#define OWL_NO_COUNTDOWN 0xff
/* The frames before it falls asleep. */
#define OWL_NAP_FRAMES 0x78

/* The effect shown while it sleeps (EffectSystem_StartKind). */
#define OWL_EFFECT_ASLEEP 0x3c

/* Where it stands when it starts in a linked game held by this system: (15.0, 21.0). */
#define OWL_LINKED_X 0xf000
#define OWL_LINKED_Z 0x15000

/* The vtables of its class and of the classes it derives from. */
extern const u8 data_ov047_02262ca4[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Its model and texture file names: "npc_sp/model/owl.nsbmd", "npc_sp/model/owl_tex.nsbtx". */
extern const char data_ov047_02262bc0[];
extern const char data_ov047_02262bf0[];
/* The functions of its states (filled at start-up by __sinit_ov047_02262838). */
extern OwlStep data_ov047_02263048[OWL_STATES];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The look's point and range when it names neither. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The session of the multiplayer game. */
extern NetSession *data_020ccf94;

static u8 *owl_part(Owl *owl, u32 offset)
{
    return owl->base + offset;
}

static SceneMotion *owl_motion(Owl *owl)
{
    return (SceneMotion *) (void *) owl_part(owl, OWL_MOTION);
}

static SceneAction *owl_action(Owl *owl)
{
    return (SceneAction *) (void *) owl_part(owl, OWL_ACTION);
}

static int owl_local_slot(void)
{
    return data_020ccf94->local_slot;
}

/* Its look asked for: `kind`, priority 0, with the defaults for what it does not name. */
static void owl_look(Owl *owl, u8 kind)
{
    SceneLook_Request((SceneLook *) (void *) owl_part(owl, OWL_LOOK), kind, 0, 0, &data_021fbee8, OWL_PLAYER_ACTOR,
                      data_020c814c, 1);
}

/* The object owned by `owner` and held by `holder`, when it is ours. */
static void owl_set_slots(Owl *owl, int owner, int holder)
{
    SceneShare_SetSlotsIfOurs(owl->base, 1, owner, holder);
}

/* Whether the session is linked or the game variable 0x4a is set. */
static int owl_linked_or_variable(NetSession *session)
{
    return Session_IsLinked(session) || *GameVariables_Slot(0, OWL_VARIABLE) != 0;
}

/* Whether it is the evening or the night, the hours it is awake. */
static int owl_awake_hours(void)
{
    return Calendar_PartOfDay() == PART_OF_DAY_EVENING || Calendar_PartOfDay() == PART_OF_DAY_NIGHT;
}

/* Its talk scene reset through its vtable slot 0x08, the talk's partner this console's player's
 * field actor. */
static void owl_reset_talk(Owl *owl)
{
    u32 vtable = *(const u32 *) (const void *) &owl->talk;
    u32 code = *(const u32 *) (uintptr_t) (vtable + OWL_TALK_SLOT_RESET);
    ((void (*)(OwlTalk *))(uintptr_t) code)(&owl->talk);
    SceneBase_SetMotionArg(&owl->talk.base, SceneObject_ActorObject(owl->base, OWL_PLAYER_ACTOR));
}

/* Its effect asleep ended, when it has one. */
static void owl_end_effect(Owl *owl)
{
    if (owl->effect != OWL_NO_EFFECT) {
        EffectSystem_EndHandle(owl->effect);
        owl->effect = OWL_NO_EFFECT;
    }
}

/* func_ov047_02260420 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
Owl *Owl_Destruct(Owl *owl)
{
    *(const u8 **) (void *) owl = data_ov047_02262ca4;
    OwlTalk_Destruct(&owl->talk);
    SpecialSceneObject_DestructBody(owl);
    return owl;
}
CLEAN_AS(func_ov047_02260420, Owl_Destruct)

/* func_ov047_02260448 (vtable slot 0x44): the same, then the object freed. */
void *Owl_DestructDelete(Owl *owl)
{
    *(const u8 **) (void *) owl = data_ov047_02262ca4;
    OwlTalk_Destruct(&owl->talk);
    SpecialSceneObject_DestructBody(owl);
    Heap_FreeAux(owl);
    return owl;
}
CLEAN_AS(func_ov047_02260448, Owl_DestructDelete)

/* func_ov047_02260474 (vtable slot 0x4c, told of an event about it by `participant`'s system, 4
 * for this one):
 * - 3, an event starts: the participant kept; another system's: owned by this system and held
 *   by it, paused; this one's (with the object ours): owned and held by this system, paused;
 * - 0, the player talks to it: the participant kept; another system's (not this one's slot):
 *   owned and held by it, state 7; this one's (with the object ours): owned and held by this
 *   system, its talk scene reset with this console's player as the partner, and it talks;
 * - 8, the event ended, for this console's player: when this system holds the scene, owned by
 *   this one and held by none, it stands when linked (or with the game variable 0x4a set),
 *   else turns back; else owned by none and held by this system, it awaits the session;
 * - 4, refused: with the object held and ours, and its holder the participant (or the
 *   participant this console's player), owned by this system and held by none, it stands. */
void Owl_OnEvent(Owl *owl, int code, int participant)
{
    switch (code) {
        case OWL_EVENT_STARTS:
            *owl_part(owl, OWL_PARTICIPANT) = (u8) participant;
            if (participant != OWL_THIS_PLAYER) {
                owl_set_slots(owl, owl_local_slot(), participant);
                Owl_SetState(owl, OWL_STATE_PAUSED);
            } else if (SceneShare_IsOurs(owl->base)) {
                int slot = owl_local_slot();
                owl_set_slots(owl, slot, slot);
                Owl_SetState(owl, OWL_STATE_PAUSED);
            }
            break;
        case OWL_EVENT_TALK:
            *owl_part(owl, OWL_PARTICIPANT) = (u8) participant;
            if (participant != OWL_THIS_PLAYER && participant != owl_local_slot()) {
                owl_set_slots(owl, participant, participant);
                Owl_SetState(owl, OWL_STATE_OTHER);
            } else if (SceneShare_IsOurs(owl->base)) {
                int slot = owl_local_slot();
                owl_set_slots(owl, slot, slot);
                owl_reset_talk(owl);
                Owl_SetState(owl, OWL_STATE_TALK);
            }
            break;
        case OWL_EVENT_ENDED:
            if (participant == OWL_THIS_PLAYER) {
                if (LinkGlobal_HoldsScene()) {
                    NetSession *session = data_020ccf94;
                    owl_set_slots(owl, session->local_slot, SCENE_SHARE_NO_SLOT);
                    if (owl_linked_or_variable(session)) {
                        Owl_SetState(owl, OWL_STATE_STAND);
                    } else {
                        Owl_SetState(owl, OWL_STATE_TURN_BACK);
                    }
                } else {
                    owl_set_slots(owl, SCENE_SHARE_NO_SLOT, owl_local_slot());
                    Owl_SetState(owl, OWL_STATE_AWAIT);
                }
            }
            break;
        case OWL_EVENT_REFUSED:
            if (SceneShare_IsHeld(owl->base) && SceneShare_IsOurs(owl->base)) {
                int owner = SCENE_SHARE_NO_SLOT;
                int holder = SCENE_SHARE_NO_SLOT;
                if (SceneShare_ReadSlots(owl->base, &owner, &holder) &&
                    (participant == OWL_THIS_PLAYER || participant == holder)) {
                    owl_set_slots(owl, owl_local_slot(), SCENE_SHARE_NO_SLOT);
                    Owl_SetState(owl, OWL_STATE_STAND);
                }
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov047_02260474, Owl_OnEvent)

/* func_ov047_02260610 (vtable slot 0x48): whether the player may talk to it: its action idle
 * and no system holding it. */
int Owl_MayAct(Owl *owl)
{
    if (SceneAction_IsBusy(owl_action(owl))) {
        return 0;
    }
    return SceneShare_IsHeld(owl->base) == 0;
}
CLEAN_AS(func_ov047_02260610, Owl_MayAct)

/* ---- Its states */

/* func_ov047_022619b4 (state 5's update): once its motion of kind 10 is done, its next stand
 * blends in (word 0x18) and it stands. 1. */
int Owl_UpdateAct(Owl *owl)
{
    if (SceneMotion_Kind(owl_motion(owl)) == OWL_MOTION_ACT && SceneMotion_IsDone(owl_motion(owl))) {
        owl->stand_word = OWL_WORD_BLEND;
        Owl_SetState(owl, OWL_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov047_022619b4, Owl_UpdateAct)

/* func_ov047_022619f0 (state 5's entry): its motion of kind 10 asked for (priority 1). 1. */
int Owl_EnterAct(Owl *owl)
{
    SceneMotion_Request(owl_motion(owl), OWL_MOTION_ACT, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov047_022619f0, Owl_EnterAct)

/* func_ov047_02262094 (state 8's update): nothing. 1. */
int Owl_UpdatePaused(void)
{
    return 1;
}
CLEAN_AS(func_ov047_02262094, Owl_UpdatePaused)

/* func_ov047_02262098 (state 8's entry): nothing. 1. */
int Owl_EnterPaused(void)
{
    return 1;
}
CLEAN_AS(func_ov047_02262098, Owl_EnterPaused)

/* func_ov047_0226209c (state 7's update, another system's player talked to it): once the object
 * is ours, the shared slots read show no owner and this system holds the scene, it is owned by
 * this system, held by none, and stands. 1. */
int Owl_UpdateOther(Owl *owl)
{
    if (SceneShare_IsOurs(owl->base)) {
        int owner = SCENE_SHARE_NO_SLOT;
        int holder = SCENE_SHARE_NO_SLOT;
        if (SceneShare_ReadSlots(owl->base, &owner, &holder) && owner == SCENE_SHARE_NO_SLOT && LinkGlobal_HoldsScene()) {
            owl_set_slots(owl, owl_local_slot(), SCENE_SHARE_NO_SLOT);
            Owl_SetState(owl, OWL_STATE_STAND);
        }
    }
    return 1;
}
CLEAN_AS(func_ov047_0226209c, Owl_UpdateOther)

/* func_ov047_022620f4 (state 7's entry): it looks ahead. 1. */
int Owl_EnterOther(Owl *owl)
{
    owl_look(owl, OWL_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov047_022620f4, Owl_EnterOther)

/* func_ov047_0226212c (state 6's update, awaiting the session): with the object ours, when the
 * shared slots read have this system as both owner and holder, they are set so, its talk scene
 * reset with this console's player as the partner, and it talks; else, when this system holds
 * the scene and no system holds it, it is owned by this system and stands. 1. */
int Owl_UpdateAwait(Owl *owl)
{
    if (!SceneShare_IsOurs(owl->base)) {
        return 1;
    }
    int owner = SCENE_SHARE_NO_SLOT;
    int holder = SCENE_SHARE_NO_SLOT;
    if (SceneShare_ReadSlots(owl->base, &owner, &holder) && owner == owl_local_slot() && owner == holder) {
        owl_set_slots(owl, owl_local_slot(), owl_local_slot());
        owl_reset_talk(owl);
        Owl_SetState(owl, OWL_STATE_TALK);
    } else if (LinkGlobal_HoldsScene() && holder == SCENE_SHARE_NO_SLOT) {
        owl_set_slots(owl, owl_local_slot(), SCENE_SHARE_NO_SLOT);
        Owl_SetState(owl, OWL_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov047_0226212c, Owl_UpdateAwait)

/* func_ov047_022621c8 (state 6's entry): it looks ahead. 1. */
int Owl_EnterAwait(Owl *owl)
{
    owl_look(owl, OWL_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov047_022621c8, Owl_EnterAwait)

/* func_ov047_02262200 (state 4's update): nothing. 1. */
int Owl_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov047_02262200, Owl_UpdateTalked)

/* func_ov047_02262204 (state 3's update): once its action is idle, it is no longer taken as
 * woken, its event ends (EventQueue_FinishObjectEvent) and state 4. 1. */
int Owl_UpdateTalk(Owl *owl)
{
    if (!SceneAction_IsBusy(owl_action(owl))) {
        owl->asleep = 0;
        EventQueue_FinishObjectEvent(owl);
        Owl_SetState(owl, OWL_STATE_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov047_02262204, Owl_UpdateTalk)

/* func_ov047_02262238 (state 3's entry): the yaw to its talk's partner (0 without one), its
 * effect asleep ended, it looks at the player and its action turns it by that yaw and talks. 1. */
int Owl_EnterTalk(Owl *owl)
{
    int partner = SceneBase_MotionArg(&owl->talk.base);
    int yaw = 0;

    if (partner != 0) {
        yaw = SceneObject_YawTo(owl->base, (u8 *) (uintptr_t) partner);
    }
    owl_end_effect(owl);
    owl_look(owl, OWL_LOOK_PLAYER);
    SceneAction_RequestTurnAndTalk(owl_action(owl), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov047_02262238, Owl_EnterTalk)

/* func_ov047_022622bc (state 2's update): its effect asleep (kind 0x3c) started at its head
 * with its angle when it has none, else moved there. 1. */
int Owl_UpdateAsleep(Owl *owl)
{
    const Vec3 *head = (const Vec3 *) (const void *) owl_part(owl, OWL_JOINT_16_POINT);
    const s16 *angle = (const s16 *) (const void *) owl_part(owl, OWL_ANGLE);

    if (owl->effect == OWL_NO_EFFECT) {
        owl->effect = EffectSystem_StartKind(OWL_EFFECT_ASLEEP, head, angle, NULL);
    } else {
        EffectSystem_MoveHandle(owl->effect, head, angle, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov047_022622bc, Owl_UpdateAsleep)

/* func_ov047_022622fc (state 2's entry): its animation asleep (0xf0, priority 1, mode 0, with
 * its word asleep), it is asleep and looks ahead. 1. */
int Owl_EnterAsleep(Owl *owl)
{
    SceneMotion_RequestAnimation(owl_motion(owl), 1, OWL_ANIM_ASLEEP, 0, owl->nap_word, 0);
    owl->asleep = 1;
    owl_look(owl, OWL_LOOK_AHEAD);
    return 1;
}
CLEAN_AS(func_ov047_022622fc, Owl_EnterAsleep)

/* func_ov047_02262360 (state 1's update): once its turn is done, it stands. 1. */
int Owl_UpdateTurnBack(Owl *owl)
{
    if (SceneMotion_Kind(owl_motion(owl)) == OWL_MOTION_TURN && SceneMotion_IsDone(owl_motion(owl))) {
        Owl_SetState(owl, OWL_STATE_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov047_02262360, Owl_UpdateTurnBack)

/* func_ov047_02262390 (state 1's entry): a turn (priority 1) to the angle it started with. 1. */
int Owl_EnterTurnBack(Owl *owl)
{
    SceneMotion_Request(owl_motion(owl), OWL_MOTION_TURN, 1, 0, 0, 0, owl->home_angle, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov047_02262390, Owl_EnterTurnBack)

/* func_ov047_022623cc (state 0's update): with a countdown to its act, it acts (state 5) once
 * the countdown ends. Else, unlinked (without the game variable 0x4a) in the morning or the
 * afternoon, once its countdown to sleep ends it falls asleep (state 2) with the word 0x18. 1. */
int Owl_UpdateStand(Owl *owl)
{
    if (owl->act_countdown != OWL_NO_COUNTDOWN) {
        if (Countdown_Tick16(&owl->act_countdown) == 0) {
            Owl_SetState(owl, OWL_STATE_ACT);
        }
        return 1;
    }
    if (owl_linked_or_variable(data_020ccf94) || owl_awake_hours()) {
        return 1;
    }
    if (Countdown_Tick16(&owl->nap_countdown) == 0) {
        owl->nap_word = OWL_WORD_BLEND;
        Owl_SetState(owl, OWL_STATE_ASLEEP);
    }
    return 1;
}
CLEAN_AS(func_ov047_022623cc, Owl_UpdateStand)

/* func_ov047_02262450 (state 0's entry): no countdown to its act; it stands (priority 1, with
 * its stand's word); when no dated event of kind 1 was told since it started and the player has
 * one today, it acts after 100 to 180 frames (in steps of 20, at random). It is no longer taken
 * as woken, its stand's word is the plain one again, it falls asleep after 120 frames, and it
 * looks at the player. 1. */
int Owl_EnterStand(Owl *owl)
{
    u8 event;

    owl->act_countdown = OWL_NO_COUNTDOWN;
    SceneMotion_RequestStand(owl_motion(owl), 1, owl->stand_word);
    if (owl->drama_told == 0 && TalkChecks_TodaysEventOfKind((int) (uintptr_t) owl, &event, OWL_EVENT_KIND)) {
        owl->act_countdown = (u16) (OWL_ACT_FRAMES + OWL_ACT_FRAMES_STEP * (int) MainRandom_Below(OWL_ACT_FRAMES_STEPS));
    }
    owl->asleep = 0;
    owl->stand_word = data_020c80f8;
    owl->nap_countdown = OWL_NAP_FRAMES;
    owl_look(owl, OWL_LOOK_PLAYER);
    return 1;
}
CLEAN_AS(func_ov047_02262450, Owl_EnterStand)

/* func_ov047_022624f4: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 8 (the table is not bounded); the owl at a word-aligned address,
 * as every object of the game (the ROM's store drops the low two bits). */
void Owl_SetState(Owl *owl, int state)
{
    const OwlStep *step = &data_ov047_02263048[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, owl);
    }
    if (taken != 0) {
        owl->state = state;
    }
}
CLEAN_AS(func_ov047_022624f4, Owl_SetState)

/* func_ov047_02262538 (vtable slot 0x68, each frame): its state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: its state is 0 to 8. */
int Owl_Update(Owl *owl)
{
    const OwlStep *step = &data_ov047_02263048[owl->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, owl);
}
CLEAN_AS(func_ov047_02262538, Owl_Update)

/* func_ov047_02262584 (vtable slot 0x70): its model's file name. */
int Owl_ModelName(void)
{
    return (int) (uintptr_t) data_ov047_02262bc0;
}
CLEAN_AS(func_ov047_02262584, Owl_ModelName)

/* func_ov047_0226258c (vtable slot 0x6c): its texture's file name. */
int Owl_TextureName(void)
{
    return (int) (uintptr_t) data_ov047_02262bf0;
}
CLEAN_AS(func_ov047_0226258c, Owl_TextureName)

/* func_ov047_02262594 (vtable slot 0x0c): when the special character may leave, its effect
 * asleep is ended. Whether it may. */
int Owl_Leave(Owl *owl)
{
    if (SpecialSceneObject_Leave(owl) == 0) {
        return 0;
    }
    owl_end_effect(owl);
    return 1;
}
CLEAN_AS(func_ov047_02262594, Owl_Leave)

/* func_ov047_022625c8 (vtable slot 0x00, its start): unless the special character refuses to
 * start, no dated event is told yet, it notes the angle it faces, has no countdown to its act,
 * is held (flag 2 at 0x4e8) and has the word 0 asleep. Linked (or with the game variable 0x4a
 * set): when this system holds the scene it is put at (15.0, 21.0) facing and walking angle 0
 * and stands, else it awaits the session. Unlinked it stands in the evening, at night or with a
 * dated event of kind 1 today, else it is asleep. Whether it started.
 * QUIRK: linked, the flag 2 is set a second time. */
int Owl_Start(Owl *owl)
{
    u8 event;

    if (SpecialSceneObject_Start(owl) == 0) {
        return 0;
    }
    u32 *flags = (u32 *) (void *) owl_part(owl, OWL_FLAGS);
    owl->drama_told = 0;
    owl->home_angle = *(const s16 *) (const void *) owl_part(owl, OWL_ANGLE);
    owl->act_countdown = OWL_NO_COUNTDOWN;
    *flags |= OWL_HELD;
    owl->nap_word = 0;
    if (owl_linked_or_variable(data_020ccf94)) {
        *flags |= OWL_HELD;
        if (LinkGlobal_HoldsScene()) {
            *(u32 *) (void *) owl_part(owl, OWL_X) = OWL_LINKED_X;
            *(u32 *) (void *) owl_part(owl, OWL_Z) = OWL_LINKED_Z;
            *(s16 *) (void *) owl_part(owl, OWL_ANGLE) = 0;
            *(s16 *) (void *) owl_part(owl, OWL_WALK_ANGLE) = 0;
            Owl_SetState(owl, OWL_STATE_STAND);
        } else {
            Owl_SetState(owl, OWL_STATE_AWAIT);
        }
        return 1;
    }
    if (owl_awake_hours() || TalkChecks_TodaysEventOfKind((int) (uintptr_t) owl, &event, OWL_EVENT_KIND)) {
        Owl_SetState(owl, OWL_STATE_STAND);
    } else {
        Owl_SetState(owl, OWL_STATE_ASLEEP);
    }
    return 1;
}
CLEAN_AS(func_ov047_022625c8, Owl_Start)

/* func_ov047_022626b4 (vtable slot 0x04, its set-up): unless the special character refuses, its
 * talk scene becomes its scene and gets it as its owner; its stand's word is the plain one and
 * it has no effect. Whether it was set up. */
int Owl_Init(Owl *owl)
{
    if (SpecialSceneObject_Init(owl) == 0) {
        return 0;
    }
    SceneObject_SetScene(owl->base, &owl->talk.base);
    OwlTalk_Begin(&owl->talk, owl);
    owl->stand_word = data_020c80f8;
    owl->effect = OWL_NO_EFFECT;
    return 1;
}
CLEAN_AS(func_ov047_022626b4, Owl_Init)

/* func_ov047_02262700 (its record's create function, data_ov047_02262bd8): a zeroed block of
 * 0x740 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
void *Owl_Create(void)
{
    Owl *owl = (Owl *) Heap_AllocAuxZeroed(sizeof(Owl));
    if (owl == NULL) {
        return NULL;
    }
    u8 *object = owl->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) owl_part(owl, OWL_PERSON) = OWL_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) owl_part(owl, OWL_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) owl_part(owl, OWL_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) owl_part(owl, OWL_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) owl_part(owl, OWL_ANIM));
    SceneMover_Construct((SceneMover *) (void *) owl_part(owl, OWL_MOVER));
    SceneProbe_Construct(owl_part(owl, OWL_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) owl_part(owl, OWL_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) owl_part(owl, OWL_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) owl_part(owl, OWL_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) owl_part(owl, OWL_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) owl_part(owl, OWL_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) owl_part(owl, OWL_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) owl_part(owl, OWL_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) owl_part(owl, OWL_FOOTSTEPS));
    SceneMotion_Construct(owl_motion(owl));
    SceneAction_Construct(owl_action(owl));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) owl_part(owl, OWL_HEAP));
    *(const u8 **) (void *) object = data_ov047_02262ca4;
    OwlTalk_Construct(&owl->talk);
    return owl;
}
CLEAN_AS(func_ov047_02262700, Owl_Create)
