/* The turtle as the insect contest's host (turtle_insects.h): his object's vtable slots and his
 * states. */
#include "turtle_insects.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/event_winner.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/insect_draw.h"
#include "main/insect_tables.h"
#include "main/layered_model.h"
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
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/state_block.h"
#include "main/town_villager.h"
#include "main/villager_roster.h"
#include "turtle_insects_talk.h"

static_assert(offsetof(TurtleInsects, state) == 0x654 && offsetof(TurtleInsects, talk) == 0x658, "TurtleInsects");
static_assert(offsetof(TurtleInsects, size) == 0x724, "TurtleInsects");
static_assert(sizeof(TurtleInsects) == 0x728, "the size TurtleInsects_Create allocates");
static_assert(sizeof(TurtleInsectsStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define TURTLE_INSECTS_PERSON 0xea          /* u16: his person code */
#define TURTLE_INSECTS_MODEL 0xec           /* LayeredModel */
#define TURTLE_INSECTS_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TURTLE_INSECTS_FACE 0x2ac           /* SceneFace */
#define TURTLE_INSECTS_ANIM 0x334           /* SpeakerAnim */
#define TURTLE_INSECTS_MOVER 0x350          /* SceneMover */
#define TURTLE_INSECTS_PROBE 0x3a8          /* the probe */
#define TURTLE_INSECTS_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define TURTLE_INSECTS_LOOK 0x3b0           /* SceneLook */
#define TURTLE_INSECTS_TALK_STATE 0x418     /* SceneTalkState */
#define TURTLE_INSECTS_EFFECTS 0x420        /* ActEffects */
#define TURTLE_INSECTS_COLLIDER 0x49c       /* CollisionContacts */
#define TURTLE_INSECTS_CARRIER 0x4cc        /* FieldOwnedBody */
#define TURTLE_INSECTS_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define TURTLE_INSECTS_EMITTER 0x514        /* SoundEmitterObject */
#define TURTLE_INSECTS_FOOTSTEPS 0x558      /* Footsteps */
#define TURTLE_INSECTS_MOTION 0x564         /* SceneMotion */
#define TURTLE_INSECTS_ACTION 0x618         /* SceneAction */
#define TURTLE_INSECTS_HEAP 0x640           /* PoolLink */

#define TURTLE_INSECTS_NO_ITEM 0xfff1
#define TURTLE_INSECTS_HELD 2

/* The field actor of this console's player. */
#define TURTLE_INSECTS_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player talked to him, the
 * event ended. */
#define TURTLE_INSECTS_EVENT_TALK 0
#define TURTLE_INSECTS_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it (the scene base's reset). */
#define TURTLE_INSECTS_SLOT_RESET 0x08

/* His animation on start (speed 1.0, slot 1) and the nodes of his model moved to its part A. */
#define TURTLE_INSECTS_START_ANIM 0x140
#define TURTLE_INSECTS_NODES_FIRST 0x0c
#define TURTLE_INSECTS_NODES_LAST 0x0e

/* His stand (scene_motion_request.h). */
#define TURTLE_INSECTS_MOTION_STAND 0

/* The insects (items 0x12b0 to 0x12e7), the record's kind and the record's mode of
 * EventWinner_ResetIfNotToday for the contest, and the state block's flag of a winner to
 * announce. */
#define TURTLE_INSECTS_INSECT_FIRST 0x12b0
#define TURTLE_INSECTS_INSECT_LAST 0x12e7
#define TURTLE_INSECTS_RECORD_KIND EVENT_WINNER_KIND_INSECTS
#define TURTLE_INSECTS_RECORD_MODE 2
#define TURTLE_INSECTS_NOTICE_FLAG 0x0f

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov082_0227981c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov082_02279738[];
extern const char data_ov082_02279768[];
/* The functions of his states (filled at start-up by __sinit_ov082_02279684). */
extern TurtleInsectsStep data_ov082_02279914[TURTLE_INSECTS_STATES];
/* The town's record of the day's winner, its villagers, the state block, and the word his
 * motion requests carry. */
extern EventWinner data_021f3aa4;
extern VillagerTown data_021e5a2c;
extern u32 data_021dc7a8[];
extern u16 data_020c80f8;

static u8 *turtle_insects_part(TurtleInsects *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneAction *turtle_insects_action(TurtleInsects *turtle)
{
    return (SceneAction *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_ACTION);
}

static int turtle_insects_is_insect(u16 item)
{
    return item >= TURTLE_INSECTS_INSECT_FIRST && item <= TURTLE_INSECTS_INSECT_LAST;
}

/* ---- His object */

/* func_ov082_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
TurtleInsects *TurtleInsects_Destruct(TurtleInsects *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov082_0227981c;
    TurtleInsectsTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov082_02278a00, TurtleInsects_Destruct)

/* func_ov082_02278a28 (vtable slot 0x44): the same, then the object freed. */
TurtleInsects *TurtleInsects_DestructDelete(TurtleInsects *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov082_0227981c;
    TurtleInsectsTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov082_02278a28, TurtleInsects_DestructDelete)

/* func_ov082_02278a54 (vtable slot 0x4c, an event about him): when the player talked to him,
 * his talk scene is reset and given the player's field actor, and he talks (state 1); once the
 * event ended he stands (state 0). */
void TurtleInsects_OnEvent(TurtleInsects *turtle, int code)
{
    switch (code) {
        case TURTLE_INSECTS_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &turtle->talk;
            u32 reset = *(const u32 *) (uintptr_t) (vtable + TURTLE_INSECTS_SLOT_RESET);
            ((void (*)(TurtleInsectsTalk *))(uintptr_t) reset)(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.base, SceneObject_ActorObject(turtle->base, TURTLE_INSECTS_PLAYER_ACTOR));
            TurtleInsects_SetState(turtle, TURTLE_INSECTS_TALK);
            break;
        }
        case TURTLE_INSECTS_EVENT_ENDED:
            TurtleInsects_SetState(turtle, TURTLE_INSECTS_STAND);
            break;
    }
}
CLEAN_AS(func_ov082_02278a54, TurtleInsects_OnEvent)

/* func_ov082_02278a98 (vtable slot 0x48): the player may talk to him while his action is
 * idle. */
int TurtleInsects_AgreesToTalk(TurtleInsects *turtle)
{
    return SceneAction_IsBusy(turtle_insects_action(turtle)) == 0;
}
CLEAN_AS(func_ov082_02278a98, TurtleInsects_AgreesToTalk)

/* func_ov082_02279324: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded); him at a word-aligned address, as
 * every object of the game (the ROM's store drops the low two bits). */
void TurtleInsects_SetState(TurtleInsects *turtle, int state)
{
    const TurtleInsectsStep *step = &data_ov082_02279914[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov082_02279324, TurtleInsects_SetState)

/* func_ov082_02279368 (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: his state is 0 to 2. */
int TurtleInsects_Update(TurtleInsects *turtle)
{
    const TurtleInsectsStep *step = &data_ov082_02279914[turtle->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, turtle);
}
CLEAN_AS(func_ov082_02279368, TurtleInsects_Update)

/* func_ov082_022793b4 (vtable slot 0x70): his model's file name. */
int TurtleInsects_ModelName(void)
{
    return (int) (uintptr_t) data_ov082_02279738;
}
CLEAN_AS(func_ov082_022793b4, TurtleInsects_ModelName)

/* func_ov082_022793bc (vtable slot 0x6c): his texture's file name. */
int TurtleInsects_TextureName(void)
{
    return (int) (uintptr_t) data_ov082_02279768;
}
CLEAN_AS(func_ov082_022793bc, TurtleInsects_TextureName)

/* The record of the day made up when it holds no insect: an insect of this month's lists
 * drawn in band 0 or 1 at random, at any hour (0xfff1 when none is drawn); when the record then
 * holds an insect, a villager of the town picked at random as its catcher when there is one
 * (then the record is of the contest and a winner is to be announced); the insect's random
 * size (0 for none).
 * QUIRK: when the band has no insect the draw is tried again in the same band. */
static void turtle_insects_make_up_record(TurtleInsects *turtle, EventWinner *record)
{
    EventWinner_Player(record); /* the result is not used */
    int band = (int) MainRandom_Below(2);
    u16 insect = TURTLE_INSECTS_NO_ITEM;
    int place = 0;
    int time_slot = 0;
    DateTime now = {0};
    DateTime_Now(&now);
    const InsectDrawList *lists = InsectTables_MonthLists(now.month - 1);
    if (lists != NULL) {
        if (InsectDraw_OfBandAnyHour(&insect, &place, &time_slot, band, lists, NULL, 0) == 0) {
            InsectDraw_OfBandAnyHour(&insect, &place, &time_slot, band, lists, NULL, 0);
        }
    }
    EventWinner_SetItem(record, &insect);
    u16 recorded;
    EventWinner_GetItem(&recorded, record);
    if (turtle_insects_is_insect(recorded)) {
        u8 *villager = VillagerRoster_PickAny(&data_021e5a2c, NULL, 0);
        if (villager != NULL) {
            EventWinner_SetVillager(record, TownVillager_NpcId(villager));
            EventWinner_SetKind(record, TURTLE_INSECTS_RECORD_KIND);
            StateBlock_SetFlag(data_021dc7a8, TURTLE_INSECTS_NOTICE_FLAG);
        }
    }
    turtle->size = EventWinner_RandomSize(&insect);
    EventWinner_SetSize(record, turtle->size);
}

/* func_ov082_022793c4 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 0); the record of the day is started afresh unless it is of today,
 * and made up when it holds no insect (turtle_insects_make_up_record); his animation player
 * plays animation 0x140 (speed 1.0, slot 1), his model's nodes 0x0c-0x0e go to its part A and
 * he is held. Whether he started.
 * REQUIRES: him at a word-aligned address (his flags are a word). */
int TurtleInsects_Start(TurtleInsects *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    TurtleInsects_SetState(turtle, TURTLE_INSECTS_STAND);
    EventWinner *record = &data_021f3aa4;
    EventWinner_ResetIfNotToday(record, TURTLE_INSECTS_RECORD_MODE);
    u16 held;
    EventWinner_GetItem(&held, record);
    if (!turtle_insects_is_insect(held)) {
        turtle_insects_make_up_record(turtle, record);
    }
    SpeakerAnim_Play((SpeakerAnim *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_ANIM), turtle->base,
                     TURTLE_INSECTS_START_ANIM, 0, 0, 0x1000, 0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_MODEL),
                              TURTLE_INSECTS_NODES_FIRST, TURTLE_INSECTS_NODES_LAST);
    *(u32 *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_HELD_FLAGS) |= TURTLE_INSECTS_HELD;
    return 1;
}
CLEAN_AS(func_ov082_022793c4, TurtleInsects_Start)

/* func_ov082_0227953c (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int TurtleInsects_Init(TurtleInsects *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.base);
    TurtleInsectsTalk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov082_0227953c, TurtleInsects_Init)

/* func_ov082_0227956c (his record's create function): a zeroed block of 0x728 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then his
 * class's vtable and his talk scene. Null when there is no room. */
void *TurtleInsects_Create(void)
{
    TurtleInsects *turtle = (TurtleInsects *) Heap_AllocAuxZeroed(sizeof(TurtleInsects));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_PERSON) = TURTLE_INSECTS_NO_ITEM;
    LayeredModel_ConstructB((LayeredModel *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_ANIM));
    SceneMover_Construct((SceneMover *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_MOVER));
    SceneProbe_Construct(turtle_insects_part(turtle, TURTLE_INSECTS_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_MOTION));
    SceneAction_Construct(turtle_insects_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_HEAP));
    *(const u8 **) (void *) object = data_ov082_0227981c;
    TurtleInsectsTalk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov082_0227956c, TurtleInsects_Create)

/* ---- His states */

/* func_ov082_022792f0 (state 0's entry): he stands (priority 1, the plain word). 1. */
int TurtleInsects_EnterStand(TurtleInsects *turtle)
{
    SceneMotion_Request((SceneMotion *) (void *) turtle_insects_part(turtle, TURTLE_INSECTS_MOTION),
                        TURTLE_INSECTS_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov082_022792f0, TurtleInsects_EnterStand)

/* func_ov082_022792ec (state 0's update): 1. */
int TurtleInsects_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov082_022792ec, TurtleInsects_UpdateStand)

/* func_ov082_022792b4 (state 1's entry): he turns to his talk's partner (when it has one, else
 * to angle 0) and talks. 1. */
int TurtleInsects_EnterTalk(TurtleInsects *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(turtle_insects_action(turtle), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov082_022792b4, TurtleInsects_EnterTalk)

/* func_ov082_02279288 (state 1's update): once his action is idle, his event is finished and
 * he has talked (state 2). 1. */
int TurtleInsects_UpdateTalk(TurtleInsects *turtle)
{
    if (SceneAction_IsBusy(turtle_insects_action(turtle)) == 0) {
        EventQueue_FinishObjectEvent(turtle);
        TurtleInsects_SetState(turtle, TURTLE_INSECTS_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov082_02279288, TurtleInsects_UpdateTalk)

/* func_ov082_02279284 (state 2's update): 1. */
int TurtleInsects_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov082_02279284, TurtleInsects_UpdateTalked)
