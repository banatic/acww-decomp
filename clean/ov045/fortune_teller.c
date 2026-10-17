/* The fortune teller of overlay 45: her object, her states and her creation (fortune_teller.h). */
#include "fortune_teller.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "fortune_teller_talk.h"
#include "main/act_effects.h"
#include "main/actor_table.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/model_object.h"
#include "main/player_actor_ops.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_exit.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_standard_anims.h"
#include "main/scene_tables.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "ov004/tarot_object.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(FortuneTellerTalk, sequence) == 0xb0, "sequence");
static_assert(offsetof(FortuneTellerTalk, owner) == 0xb4, "owner");
static_assert(sizeof(FortuneTellerTalk) == 0xb8, "its talk scene");
static_assert(sizeof(FortuneTellerStep) == 0x10, "a state's functions");
static_assert(sizeof(FortuneTellerCard) == 8, "a card");
static_assert(offsetof(FortuneTeller, effect) == 0x654, "effect");
static_assert(offsetof(FortuneTeller, state) == 0x658, "state");
static_assert(offsetof(FortuneTeller, joint14) == 0x65c, "joint 14");
static_assert(offsetof(FortuneTeller, talk) == 0x68c, "talk scene");
static_assert(offsetof(FortuneTeller, card_message) == 0x744, "card message");
static_assert(offsetof(FortuneTeller, result_message) == 0x745, "result message");
static_assert(offsetof(FortuneTeller, reading) == 0x748, "reading");
static_assert(offsetof(FortuneTeller, card) == 0x74c, "card");
static_assert(offsetof(FortuneTeller, reversed) == 0x750, "reversed");
static_assert(offsetof(FortuneTeller, villager_name) == 0x754, "villager name");
static_assert(offsetof(FortuneTeller, effect_frames) == 0x758, "effect frames");
static_assert(sizeof(FortuneTeller) == 0x75c, "the size FortuneTeller_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define FT_POSITION 0x5c        /* Vec3: where it stands */
#define FT_MODEL_FRAME 0x190    /* fx32: its model's animation frame, 20.12 */
#define FT_PERSON 0xea          /* u16: its person code */
#define FT_MODEL 0xec           /* LayeredModel */
#define FT_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define FT_FACE 0x2ac           /* SceneFace */
#define FT_ANIM 0x334           /* SpeakerAnim */
#define FT_MOVER 0x350          /* SceneMover */
#define FT_PROBE 0x3a8          /* the probe ahead */
#define FT_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define FT_LOOK 0x3b0           /* SceneLook */
#define FT_TALK_STATE 0x418     /* SceneTalkState */
#define FT_EFFECTS 0x420        /* ActEffects */
#define FT_JOINT16 0x478        /* Vec3: the point of its joint 16, at each draw */
#define FT_COLLIDER 0x49c       /* CollisionContacts */
#define FT_CARRIER 0x4cc        /* FieldOwnedBody */
#define FT_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define FT_EMITTER 0x514        /* SoundEmitterObject */
#define FT_FOOTSTEPS 0x558      /* Footsteps */
#define FT_MOTION 0x564         /* SceneMotion */
#define FT_ACTION 0x618         /* SceneAction */
#define FT_HEAP 0x640           /* PoolLink */

#define FT_NO_PERSON 0xfff1
#define FT_HELD 2
#define FT_NO_EFFECT (-1)

/* The field actor of this console's player. */
#define FT_PLAYER_ACTOR 4

/* The codes of her vtable slot 0x4c (main's event_kinds.h). */
#define FT_EVENT_TALK 0
#define FT_EVENT_1 1
#define FT_EVENT_ENDED 8

/* The scene's vtable slot her talks call first. */
#define FT_TALK_SLOT_08 0x08
/* The scene's vtable slot of the focus speaker's talking motion (FortuneTellerTalk_SetTalkStyle). */
#define FT_TALK_SLOT_STYLE 0x38

/* Her cards: 22, upright or reversed; the two lines of each card's picture; the cards that
 * tell good luck and bad luck. */
#define FT_CARDS 22
#define FT_GOOD_CARDS 17
#define FT_BAD_CARDS 21

/* The motion acts during which her effect may start or the cards follow her (scene_motion.h's
 * act number): the cards shown (0x1e, 0x20; when done, the talking motion of style 0) and
 * her effect's act (0x21, from frame 18). */
#define FT_ACT_CARDS_A 0x1e
#define FT_ACT_CARDS_B 0x20
#define FT_ACT_EFFECT 0x21
#define FT_EFFECT_FROM_FRAME 0x12
#define FT_EFFECT 0x3d
#define FT_EFFECT_FRAMES 0x16

/* Her joint whose matrix the tarot cards are drawn at. */
#define FT_CARD_JOINT 14

/* Before this hour she is closed. */
#define FT_OPENING_HOUR 6

/* Where the player must stand to talk to her: within 1.0 of her x, and 2.0 to 4.0 in front of
 * her (on z). */
#define FT_REACH_X 0x1000
#define FT_REACH_Z_NEAR 0x2000
#define FT_REACH_Z_FAR 0x4000

/* Her collider and reach. */
#define FT_COLLIDER_SIZE 0x100
#define FT_REACH 0x5000

/* The vtables: the class's, its talk scene's and those of the classes it derives from. */
extern const u8 data_ov045_022614f0[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* The one that exists, from her start to her leaving. */
extern FortuneTeller *data_ov045_022615a0;
/* Her states' functions (filled at start-up by __sinit_ov045_022612d8). */
extern FortuneTellerStep data_ov045_022615bc[FORTUNE_TELLER_STATES];
/* The cards that tell good luck and bad luck. */
extern const FortuneTellerCard data_ov045_022611a8[FT_GOOD_CARDS];
extern const FortuneTellerCard data_ov045_02261230[FT_BAD_CARDS];
/* Her model's and texture's file names: "npc_sp/model/bpt.nsbmd", "npc_sp/model/bpt_tex.nsbtx". */
extern const char data_ov045_022613dc[];
extern const char data_ov045_0226143c[];
/* The word her motion requests carry. */
extern u16 data_020c80f8;

static u8 *ft_part(FortuneTeller *teller, u32 offset)
{
    return teller->base + offset;
}

static SceneMotion *ft_motion_of(FortuneTeller *teller)
{
    return (SceneMotion *) (void *) ft_part(teller, FT_MOTION);
}

static SceneAction *ft_action_of(FortuneTeller *teller)
{
    return (SceneAction *) (void *) ft_part(teller, FT_ACTION);
}

/* The code of her talk scene's vtable slot `slot`. */
static u32 ft_talk_slot(FortuneTellerTalk *talk, u32 slot)
{
    u32 vtable = *(const u32 *) (const void *) talk;
    return *(const u32 *) (uintptr_t) (vtable + slot);
}

/* Her talk scene's vtable slot 0x08 called. */
static void ft_talk_slot_08(FortuneTellerTalk *talk)
{
    ((void (*)(FortuneTellerTalk *))(uintptr_t) ft_talk_slot(talk, FT_TALK_SLOT_08))(talk);
}

/* Her talk scene's vtable slot 0x38 called: the focus speaker's talking motion of `style`. */
static void ft_talk_style(FortuneTellerTalk *talk, int style)
{
    ((void (*)(FortuneTellerTalk *, int))(uintptr_t) ft_talk_slot(talk, FT_TALK_SLOT_STYLE))(talk, style);
}

/* func_ov045_02260420 (vtable slot 0x40): her talk scene's destructor, then the special
 * character's; the object. */
FortuneTeller *FortuneTeller_Destroy(FortuneTeller *teller)
{
    *(const u8 **) (void *) teller->base = data_ov045_022614f0;
    FortuneTellerTalk_Destroy(&teller->talk);
    SpecialSceneObject_DestructBody(teller);
    return teller;
}
CLEAN_AS(func_ov045_02260420, FortuneTeller_Destroy)

/* func_ov045_02260448 (vtable slot 0x44): the same, then the object freed. */
void *FortuneTeller_Delete(void *object)
{
    FortuneTeller *teller = object;
    *(const u8 **) (void *) teller->base = data_ov045_022614f0;
    FortuneTellerTalk_Destroy(&teller->talk);
    SpecialSceneObject_DestructBody(teller);
    Heap_FreeAux(teller);
    return teller;
}
CLEAN_AS(func_ov045_02260448, FortuneTeller_Delete)

static int ft_card_in(const FortuneTeller *teller, const FortuneTellerCard *cards, int count)
{
    for (int i = 0; i < count; i++) {
        if (teller->card == cards[i].card && teller->reversed == cards[i].reversed) {
            return 1;
        }
    }
    return 0;
}

/* func_ov045_02260524: what the card drawn tells: good luck when it is one of the 17 of
 * data_ov045_022611a8, bad luck when one of the 21 of data_ov045_02261230, else none. */
int FortuneTeller_CardLuck(FortuneTeller *teller)
{
    if (ft_card_in(teller, data_ov045_022611a8, FT_GOOD_CARDS)) {
        return FORTUNE_TELLER_LUCK_GOOD;
    }
    if (ft_card_in(teller, data_ov045_02261230, FT_BAD_CARDS)) {
        return FORTUNE_TELLER_LUCK_BAD;
    }
    return FORTUNE_TELLER_LUCK_NONE;
}
CLEAN_AS(func_ov045_02260524, FortuneTeller_CardLuck)

/* func_ov045_022605a4: a card drawn: one of 22, reversed or not (a coin), and the line that
 * shows it (one of two, by another coin) and the line of its meaning. */
void FortuneTeller_DrawCard(FortuneTeller *teller)
{
    teller->card = (u8) MainRandom_Below(FT_CARDS);
    teller->reversed = MainRandom_Below(2) != 0 ? 1 : 0;
    unsigned int variant = MainRandom_Below(2);
    teller->card_message =
        (u8) (teller->card * 2 + FORTUNE_TELLER_LINE_CARDS + variant + FORTUNE_TELLER_LINE_CARDS_REVERSED * teller->reversed);
    teller->result_message =
        (u8) (teller->card + FORTUNE_TELLER_LINE_MEANINGS + FORTUNE_TELLER_LINE_MEANINGS_REVERSED * teller->reversed);
}
CLEAN_AS(func_ov045_022605a4, FortuneTeller_DrawCard)

/* func_ov045_02260618: the whole frame of the current one's animation (her word at 0x190, cut
 * to 16 bits).
 * REQUIRES: one exists (the tarot object asks only while she does). */
unsigned int FortuneTeller_CurrentFrame(void)
{
    u32 frame = *(const u32 *) (const void *) ft_part(data_ov045_022615a0, FT_MODEL_FRAME);
    return (frame << 4) >> 16;
}
CLEAN_AS(func_ov045_02260618, FortuneTeller_CurrentFrame)

/* func_ov045_02260630: the address of the current one's matrix of joint 14 (0x65c past the
 * pointer, whatever it holds). */
int FortuneTeller_CurrentMatrix(void)
{
    return (int) ((u32) (uintptr_t) data_ov045_022615a0 + (u32) offsetof(FortuneTeller, joint14));
}
CLEAN_AS(func_ov045_02260630, FortuneTeller_CurrentMatrix)

/* func_ov045_02260644: whether the hour now is before 6 a.m. */
int FortuneTeller_BeforeSix(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return now.hour < FT_OPENING_HOUR;
}
CLEAN_AS(func_ov045_02260644, FortuneTeller_BeforeSix)

/* func_ov045_02260668 (vtable slot 0x4c, told of an event about her): codes 0 and 1, the
 * player talks to her: her talk scene told through its slot 0x08, the talk's partner this
 * console's player's object, and she talks (state 1); code 8, the event ended: she sits
 * (state 0). The base class is not told. */
void FortuneTeller_OnEvent(FortuneTeller *teller, int code)
{
    switch (code) {
        case FT_EVENT_TALK:
        case FT_EVENT_1:
            ft_talk_slot_08(&teller->talk);
            SceneBase_SetMotionArg(&teller->talk.base, SceneObject_ActorObject(teller->base, FT_PLAYER_ACTOR));
            FortuneTeller_SetState(teller, FORTUNE_TELLER_TALKING);
            break;
        case FT_EVENT_ENDED:
            FortuneTeller_SetState(teller, FORTUNE_TELLER_SIT);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov045_02260668, FortuneTeller_OnEvent)

/* func_ov045_022606b0 (vtable slot 0x48): whether the player may talk to her: she sits (state
 * 0) and this console's player stands (its start position, Position_Tile asked of it first)
 * strictly within 1.0 of her x and strictly between 2.0 and 4.0 past her z. */
int FortuneTeller_MayAct(FortuneTeller *teller)
{
    Vec3 player = *PlayerActorOps_StartPosition(FT_PLAYER_ACTOR);
    int tile_x = 0;
    int tile_z = 0;
    Position_Tile(&tile_x, &tile_z, (const Position *) (const void *) &player);

    const Vec3 *at = (const Vec3 *) (const void *) ft_part(teller, FT_POSITION);
    if (teller->state != FORTUNE_TELLER_SIT) {
        return 0;
    }
    return player.x > at->x - FT_REACH_X && player.x < at->x + FT_REACH_X && player.z > at->z + FT_REACH_Z_NEAR &&
           player.z < at->z + FT_REACH_Z_FAR;
}
CLEAN_AS(func_ov045_022606b0, FortuneTeller_MayAct)

/* func_ov045_02260d64 (state 2's update): nothing. 1. */
int FortuneTeller_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov045_02260d64, FortuneTeller_UpdateTalked)

/* func_ov045_02260d68 (state 2's entry): 1. */
int FortuneTeller_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov045_02260d68, FortuneTeller_EnterTalked)

/* func_ov045_02260d6c (state 3's update): once her action is idle, main's entry record takes
 * the scene's exit 0, and state 2 follows. 1. */
int FortuneTeller_UpdateClosing(FortuneTeller *teller)
{
    if (!SceneAction_IsBusy(ft_action_of(teller))) {
        SceneExit_Take((SceneExit *) (uintptr_t) (u32) SceneTables_EntryRecord(), 0);
        FortuneTeller_SetState(teller, FORTUNE_TELLER_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov045_02260d6c, FortuneTeller_UpdateClosing)

/* func_ov045_02260d9c (state 3's entry): 1. */
int FortuneTeller_EnterClosing(void)
{
    return 1;
}
CLEAN_AS(func_ov045_02260d9c, FortuneTeller_EnterClosing)

/* func_ov045_02260da0 (state 1's update): once her action is idle, the object's event ends
 * and state 2 follows. 1. */
int FortuneTeller_UpdateTalk(FortuneTeller *teller)
{
    if (!SceneAction_IsBusy(ft_action_of(teller))) {
        EventQueue_FinishObjectEvent(teller);
        FortuneTeller_SetState(teller, FORTUNE_TELLER_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov045_02260da0, FortuneTeller_UpdateTalk)

/* func_ov045_02260dcc (state 1's entry): with a talk's partner, the angle to it is asked (and
 * not used); she talks (resetting her motion). 1. */
int FortuneTeller_EnterTalk(FortuneTeller *teller)
{
    int partner = SceneBase_MotionArg(&teller->talk.base);
    if (partner != 0) {
        SceneObject_YawTo(teller->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTalk(ft_action_of(teller), 1, 0);
    return 1;
}
CLEAN_AS(func_ov045_02260dcc, FortuneTeller_EnterTalk)

/* func_ov045_02260e00 (state 0's update): before 6 a.m. an event of kind 6 is asked for her.
 * 1. */
int FortuneTeller_UpdateSit(int teller)
{
    if (FortuneTeller_BeforeSix()) {
        EventQueue_RequestKind6((void *) (uintptr_t) (u32) teller, 0);
    }
    return 1;
}
CLEAN_AS(func_ov045_02260e00, FortuneTeller_UpdateSit)

/* func_ov045_02260e1c (state 0's entry): her motion of kind 0 asked for (priority 1). 1. */
int FortuneTeller_EnterSit(FortuneTeller *teller)
{
    SceneMotion_Request(ft_motion_of(teller), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov045_02260e1c, FortuneTeller_EnterSit)

/* func_ov045_02260e50: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 3 (the table is not bounded). */
void FortuneTeller_SetState(FortuneTeller *teller, int state)
{
    const FortuneTellerStep *step = &data_ov045_022615bc[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, teller);
    }
    if (taken != 0) {
        teller->state = state;
    }
}
CLEAN_AS(func_ov045_02260e50, FortuneTeller_SetState)

/* func_ov045_02260e94 (vtable slot 0x68, each frame):
 * - in the motion acts 0x1e and 0x20, once the motion is done her talk scene takes the talking
 *   motion of style 0 (its slot 0x38);
 * - without her effect, in act 0x21 from frame 18 effect 0x3d starts at the point of her joint
 *   16 for 22 frames; with it, it ends when the frames run out (-1 again), else follows the
 *   point;
 * then her state's update when it has one, and its answer; else 0.
 * REQUIRES: her state is 0 to 3. */
int FortuneTeller_Update(FortuneTeller *teller)
{
    SceneMotion *motion = ft_motion_of(teller);
    const Vec3 *joint16 = (const Vec3 *) (const void *) ft_part(teller, FT_JOINT16);
    int act = SceneMotion_ActNumber(motion);

    if ((act == FT_ACT_CARDS_A || act == FT_ACT_CARDS_B) && SceneMotion_IsDone(motion)) {
        ft_talk_style(&teller->talk, 0);
    }
    if (teller->effect == FT_NO_EFFECT) {
        if (act == FT_ACT_EFFECT) {
            u32 frame = *(const u32 *) (const void *) ft_part(teller, FT_MODEL_FRAME);
            if (((frame >> 12) & 0xffff) >= FT_EFFECT_FROM_FRAME) {
                teller->effect = EffectSystem_StartKind(FT_EFFECT, joint16, NULL, NULL);
                teller->effect_frames = FT_EFFECT_FRAMES;
            }
        }
    } else if (Countdown_Tick8(&teller->effect_frames) == 0) {
        EffectSystem_EndHandle(teller->effect);
        teller->effect = FT_NO_EFFECT;
    } else {
        EffectSystem_MoveHandle(teller->effect, joint16, NULL, NULL);
    }

    const FortuneTellerStep *step = &data_ov045_022615bc[teller->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, teller);
}
CLEAN_AS(func_ov045_02260e94, FortuneTeller_Update)

/* func_ov045_02260f84 (vtable slot 0x70): her model's file name, "npc_sp/model/bpt.nsbmd". */
int FortuneTeller_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov045_022613dc;
}
CLEAN_AS(func_ov045_02260f84, FortuneTeller_ModelName)

/* func_ov045_02260f8c (vtable slot 0x6c): her texture's file name,
 * "npc_sp/model/bpt_tex.nsbtx". */
int FortuneTeller_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov045_0226143c;
}
CLEAN_AS(func_ov045_02260f8c, FortuneTeller_TextureName)

/* func_ov045_02260f94 (vtable slot 0x24, her drawing): unless the scene object draws nothing,
 * the matrix of her joint 14 is kept and the tarot cards are drawn at it. Whether she was
 * drawn. */
int FortuneTeller_Draw(FortuneTeller *teller)
{
    if (!SceneObject_Draw(teller->base)) {
        return 0;
    }
    ModelObject_JointMatrix((ModelObject *) (void *) ft_part(teller, FT_MODEL), &teller->joint14, FT_CARD_JOINT);
    TarotObject_DrawCurrent();
    return 1;
}
CLEAN_AS(func_ov045_02260f94, FortuneTeller_Draw)

/* func_ov045_02260fc4 (vtable slot 0x0c, her leaving): unless the special character refuses,
 * none is current any more. Whether she left. */
int FortuneTeller_Leave(FortuneTeller *teller)
{
    if (!SpecialSceneObject_Leave(teller)) {
        return 0;
    }
    data_ov045_022615a0 = NULL;
    return 1;
}
CLEAN_AS(func_ov045_02260fc4, FortuneTeller_Leave)

/* func_ov045_02260fe8 (vtable slot 0x00, her start): unless the special character refuses to
 * start, she becomes the current one, sits (state 0) and is held (flag 2 at 0x4e8), with no
 * card's lines. Whether she started. */
int FortuneTeller_Start(FortuneTeller *teller)
{
    if (SpecialSceneObject_Start(teller) == 0) {
        return 0;
    }
    data_ov045_022615a0 = teller;
    FortuneTeller_SetState(teller, FORTUNE_TELLER_SIT);
    *(u32 *) (void *) ft_part(teller, FT_HELD_FLAGS) |= FT_HELD;
    teller->card_message = FORTUNE_TELLER_NO_MESSAGE;
    teller->result_message = FORTUNE_TELLER_NO_MESSAGE;
    return 1;
}
CLEAN_AS(func_ov045_02260fe8, FortuneTeller_Start)

/* func_ov045_02261034 (vtable slot 0x04, her set-up): unless the special character refuses,
 * her talk scene becomes her scene and gets her as its owner; her collider (0x100) and reach
 * (5.0) set; no effect. Whether she was set up. */
int FortuneTeller_Init(FortuneTeller *teller)
{
    if (SpecialSceneObject_Init(teller) == 0) {
        return 0;
    }
    SceneObject_SetScene(teller->base, &teller->talk.base);
    FortuneTellerTalk_Begin(&teller->talk, teller);
    SceneObject_SetColliderSize(teller->base, FT_COLLIDER_SIZE);
    SceneObjectBase_SetReach((SceneObjectBase *) (void *) teller->base, FT_REACH);
    teller->effect = FT_NO_EFFECT;
    teller->effect_frames = 0;
    return 1;
}
CLEAN_AS(func_ov045_02261034, FortuneTeller_Init)

/* func_ov045_02261090 (the create function her record at 0x022613f4 names): a zeroed block of
 * 0x75c bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *FortuneTeller_Create(void)
{
    FortuneTeller *teller = (FortuneTeller *) Heap_AllocAuxZeroed(sizeof(FortuneTeller));
    if (teller == NULL) {
        return NULL;
    }
    u8 *object = teller->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) ft_part(teller, FT_PERSON) = FT_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) ft_part(teller, FT_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) ft_part(teller, FT_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) ft_part(teller, FT_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) ft_part(teller, FT_ANIM));
    SceneMover_Construct((SceneMover *) (void *) ft_part(teller, FT_MOVER));
    SceneProbe_Construct(ft_part(teller, FT_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) ft_part(teller, FT_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) ft_part(teller, FT_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) ft_part(teller, FT_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) ft_part(teller, FT_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) ft_part(teller, FT_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) ft_part(teller, FT_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) ft_part(teller, FT_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) ft_part(teller, FT_FOOTSTEPS));
    SceneMotion_Construct(ft_motion_of(teller));
    SceneAction_Construct(ft_action_of(teller));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) ft_part(teller, FT_HEAP));
    *(const u8 **) (void *) object = data_ov045_022614f0;
    FortuneTellerTalk_Construct(&teller->talk);
    return teller;
}
CLEAN_AS(func_ov045_02261090, FortuneTeller_Create)
