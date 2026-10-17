/* The turtle as the fishing tourney's host (turtle_fishing.h): his object's vtable slots and his
 * states. */
#include "turtle_fishing.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/calendar.h"
#include "main/creature_draw.h"
#include "main/creature_table.h"
#include "main/date_time.h"
#include "main/event_queue.h"
#include "main/event_winner.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
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
#include "turtle_fishing_talk.h"

static_assert(offsetof(TurtleFishing, state) == 0x654 && offsetof(TurtleFishing, talk) == 0x658, "TurtleFishing");
static_assert(offsetof(TurtleFishing, size) == 0x724, "TurtleFishing");
static_assert(sizeof(TurtleFishing) == 0x728, "the size TurtleFishing_Create allocates");
static_assert(sizeof(TurtleFishingStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define TURTLE_FISHING_PERSON 0xea          /* u16: his person code */
#define TURTLE_FISHING_MODEL 0xec           /* LayeredModel */
#define TURTLE_FISHING_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TURTLE_FISHING_FACE 0x2ac           /* SceneFace */
#define TURTLE_FISHING_ANIM 0x334           /* SpeakerAnim */
#define TURTLE_FISHING_MOVER 0x350          /* SceneMover */
#define TURTLE_FISHING_PROBE 0x3a8          /* the probe */
#define TURTLE_FISHING_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define TURTLE_FISHING_LOOK 0x3b0           /* SceneLook */
#define TURTLE_FISHING_TALK_STATE 0x418     /* SceneTalkState */
#define TURTLE_FISHING_EFFECTS 0x420        /* ActEffects */
#define TURTLE_FISHING_COLLIDER 0x49c       /* CollisionContacts */
#define TURTLE_FISHING_CARRIER 0x4cc        /* FieldOwnedBody */
#define TURTLE_FISHING_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define TURTLE_FISHING_EMITTER 0x514        /* SoundEmitterObject */
#define TURTLE_FISHING_FOOTSTEPS 0x558      /* Footsteps */
#define TURTLE_FISHING_MOTION 0x564         /* SceneMotion */
#define TURTLE_FISHING_ACTION 0x618         /* SceneAction */
#define TURTLE_FISHING_HEAP 0x640           /* PoolLink */

#define TURTLE_FISHING_NO_ITEM 0xfff1
#define TURTLE_FISHING_HELD 2

/* The field actor of this console's player. */
#define TURTLE_FISHING_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player talked to him, the
 * event ended. */
#define TURTLE_FISHING_EVENT_TALK 0
#define TURTLE_FISHING_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it (the scene base's reset). */
#define TURTLE_FISHING_SLOT_RESET 0x08

/* His animation on start (speed 1.0, slot 1) and the nodes of his model moved to its part A. */
#define TURTLE_FISHING_START_ANIM 0x140
#define TURTLE_FISHING_NODES_FIRST 0x0c
#define TURTLE_FISHING_NODES_LAST 0x0e

/* His stand (scene_motion_request.h). */
#define TURTLE_FISHING_MOTION_STAND 0

/* The fish (items 0x12e8 to 0x131f), the record's kind and the record's mode of
 * EventWinner_ResetIfNotToday for the tourney, and the state block's flag of a winner to
 * announce. */
#define TURTLE_FISHING_FISH_FIRST 0x12e8
#define TURTLE_FISHING_FISH_LAST 0x131f
#define TURTLE_FISHING_RECORD_KIND EVENT_WINNER_KIND_FISHING
#define TURTLE_FISHING_RECORD_MODE 1
#define TURTLE_FISHING_NOTICE_FLAG 0x0f

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov081_022797bc[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov081_022796d8[];
extern const char data_ov081_02279708[];
/* The functions of his states (filled at start-up by __sinit_ov081_02279620). */
extern TurtleFishingStep data_ov081_022798b4[TURTLE_FISHING_STATES];
/* The town's record of the day's winner, its villagers, the state block, and the word his
 * motion requests carry. */
extern EventWinner data_021f3aa4;
extern VillagerTown data_021e5a2c;
extern u32 data_021dc7a8[];
extern u16 data_020c80f8;

static u8 *turtle_fishing_part(TurtleFishing *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneAction *turtle_fishing_action(TurtleFishing *turtle)
{
    return (SceneAction *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_ACTION);
}

static int turtle_fishing_is_fish(u16 item)
{
    return item >= TURTLE_FISHING_FISH_FIRST && item <= TURTLE_FISHING_FISH_LAST;
}

/* ---- His object */

/* func_ov081_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
TurtleFishing *TurtleFishing_Destruct(TurtleFishing *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov081_022797bc;
    TurtleFishingTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov081_02278a00, TurtleFishing_Destruct)

/* func_ov081_02278a28 (vtable slot 0x44): the same, then the object freed. */
TurtleFishing *TurtleFishing_DestructDelete(TurtleFishing *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov081_022797bc;
    TurtleFishingTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov081_02278a28, TurtleFishing_DestructDelete)

/* func_ov081_02278a54 (vtable slot 0x4c, an event about him): when the player talked to him,
 * his talk scene is reset and given the player's field actor, and he talks (state 1); once the
 * event ended he stands (state 0). */
void TurtleFishing_OnEvent(TurtleFishing *turtle, int code)
{
    switch (code) {
        case TURTLE_FISHING_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &turtle->talk;
            u32 reset = *(const u32 *) (uintptr_t) (vtable + TURTLE_FISHING_SLOT_RESET);
            ((void (*)(TurtleFishingTalk *))(uintptr_t) reset)(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.base, SceneObject_ActorObject(turtle->base, TURTLE_FISHING_PLAYER_ACTOR));
            TurtleFishing_SetState(turtle, TURTLE_FISHING_TALK);
            break;
        }
        case TURTLE_FISHING_EVENT_ENDED:
            TurtleFishing_SetState(turtle, TURTLE_FISHING_STAND);
            break;
    }
}
CLEAN_AS(func_ov081_02278a54, TurtleFishing_OnEvent)

/* func_ov081_02278a98 (vtable slot 0x48): the player may talk to him while his action is
 * idle. */
int TurtleFishing_AgreesToTalk(TurtleFishing *turtle)
{
    return SceneAction_IsBusy(turtle_fishing_action(turtle)) == 0;
}
CLEAN_AS(func_ov081_02278a98, TurtleFishing_AgreesToTalk)

/* func_ov081_022792e0: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded); him at a word-aligned address, as
 * every object of the game (the ROM's store drops the low two bits). */
void TurtleFishing_SetState(TurtleFishing *turtle, int state)
{
    const TurtleFishingStep *step = &data_ov081_022798b4[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov081_022792e0, TurtleFishing_SetState)

/* func_ov081_02279324 (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: his state is 0 to 2. */
int TurtleFishing_Update(TurtleFishing *turtle)
{
    const TurtleFishingStep *step = &data_ov081_022798b4[turtle->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, turtle);
}
CLEAN_AS(func_ov081_02279324, TurtleFishing_Update)

/* func_ov081_02279370 (vtable slot 0x70): his model's file name. */
int TurtleFishing_ModelName(void)
{
    return (int) (uintptr_t) data_ov081_022796d8;
}
CLEAN_AS(func_ov081_02279370, TurtleFishing_ModelName)

/* func_ov081_02279378 (vtable slot 0x6c): his texture's file name. */
int TurtleFishing_TextureName(void)
{
    return (int) (uintptr_t) data_ov081_02279708;
}
CLEAN_AS(func_ov081_02279378, TurtleFishing_TextureName)

/* The record of the day made up when it holds no fish: a fish drawn for today in band 0 or 1
 * at random (the other band when that has none), with its random size, and a villager of the
 * town picked at random as its catcher when there is one (then the record is of the tourney
 * and a winner is to be announced). Without the day's lists the fish stays 0xfff1 (size 0). */
static void turtle_fishing_make_up_record(TurtleFishing *turtle, EventWinner *record)
{
    EventWinner_Player(record); /* the result is not used */
    int band = (int) MainRandom_Below(2);
    u16 fish = TURTLE_FISHING_NO_ITEM;
    int second = 0;
    int time_slot = 0;
    DateTime now = {0};
    DateTime_Now(&now);
    void *lists = CreatureTable_Lists(now.month, (unsigned int) CreatureTable_IsSecondHalf(now.day));
    if (lists != NULL) {
        if (CreatureDraw_FishOfBand(&fish, &second, &time_slot, band, lists) == 0) {
            CreatureDraw_FishOfBand(&fish, &second, &time_slot, (band + 1) & 1, lists);
        }
    }
    EventWinner_SetItem(record, &fish);
    turtle->size = EventWinner_RandomSize(&fish);
    EventWinner_SetSize(record, turtle->size);
    u8 *villager = VillagerRoster_PickAny(&data_021e5a2c, NULL, 0);
    if (villager != NULL) {
        EventWinner_SetVillager(record, TownVillager_NpcId(villager));
        EventWinner_SetKind(record, TURTLE_FISHING_RECORD_KIND);
        StateBlock_SetFlag(data_021dc7a8, TURTLE_FISHING_NOTICE_FLAG);
    }
}

/* func_ov081_02279380 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 0); the record of the day is started afresh unless it is of today,
 * and made up when it holds no fish (turtle_fishing_make_up_record); his animation player
 * plays animation 0x140 (speed 1.0, slot 1), his model's nodes 0x0c-0x0e go to its part A and
 * he is held. Whether he started.
 * REQUIRES: him at a word-aligned address (his flags are a word). */
int TurtleFishing_Start(TurtleFishing *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    TurtleFishing_SetState(turtle, TURTLE_FISHING_STAND);
    EventWinner *record = &data_021f3aa4;
    EventWinner_ResetIfNotToday(record, TURTLE_FISHING_RECORD_MODE);
    u16 held;
    EventWinner_GetItem(&held, record);
    if (!turtle_fishing_is_fish(held)) {
        turtle_fishing_make_up_record(turtle, record);
    }
    SpeakerAnim_Play((SpeakerAnim *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_ANIM), turtle->base,
                     TURTLE_FISHING_START_ANIM, 0, 0, 0x1000, 0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_MODEL),
                              TURTLE_FISHING_NODES_FIRST, TURTLE_FISHING_NODES_LAST);
    *(u32 *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_HELD_FLAGS) |= TURTLE_FISHING_HELD;
    return 1;
}
CLEAN_AS(func_ov081_02279380, TurtleFishing_Start)

/* func_ov081_022794d8 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int TurtleFishing_Init(TurtleFishing *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.base);
    TurtleFishingTalk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov081_022794d8, TurtleFishing_Init)

/* func_ov081_02279508 (his record's create function): a zeroed block of 0x728 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then his
 * class's vtable and his talk scene. Null when there is no room. */
void *TurtleFishing_Create(void)
{
    TurtleFishing *turtle = (TurtleFishing *) Heap_AllocAuxZeroed(sizeof(TurtleFishing));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_PERSON) = TURTLE_FISHING_NO_ITEM;
    LayeredModel_ConstructB((LayeredModel *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_ANIM));
    SceneMover_Construct((SceneMover *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_MOVER));
    SceneProbe_Construct(turtle_fishing_part(turtle, TURTLE_FISHING_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_MOTION));
    SceneAction_Construct(turtle_fishing_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_HEAP));
    *(const u8 **) (void *) object = data_ov081_022797bc;
    TurtleFishingTalk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov081_02279508, TurtleFishing_Create)

/* ---- His states */

/* func_ov081_022792ac (state 0's entry): he stands (priority 1, the plain word). 1. */
int TurtleFishing_EnterStand(TurtleFishing *turtle)
{
    SceneMotion_Request((SceneMotion *) (void *) turtle_fishing_part(turtle, TURTLE_FISHING_MOTION),
                        TURTLE_FISHING_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov081_022792ac, TurtleFishing_EnterStand)

/* func_ov081_022792a8 (state 0's update): 1. */
int TurtleFishing_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov081_022792a8, TurtleFishing_UpdateStand)

/* func_ov081_02279270 (state 1's entry): he turns to his talk's partner (when it has one, else
 * to angle 0) and talks. 1. */
int TurtleFishing_EnterTalk(TurtleFishing *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(turtle_fishing_action(turtle), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov081_02279270, TurtleFishing_EnterTalk)

/* func_ov081_02279244 (state 1's update): once his action is idle, his event is finished and
 * he has talked (state 2). 1. */
int TurtleFishing_UpdateTalk(TurtleFishing *turtle)
{
    if (SceneAction_IsBusy(turtle_fishing_action(turtle)) == 0) {
        EventQueue_FinishObjectEvent(turtle);
        TurtleFishing_SetState(turtle, TURTLE_FISHING_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov081_02279244, TurtleFishing_UpdateTalk)

/* func_ov081_02279240 (state 2's update): 1. */
int TurtleFishing_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov081_02279240, TurtleFishing_UpdateTalked)
