/* The turtle as the judge of the town's gardens (turtle_gardens.h): his object's vtable slots
 * and his states. */
#include "turtle_gardens.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/event_calendar.h"
#include "main/event_queue.h"
#include "main/event_winner.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
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
#include "turtle_gardens_talk.h"

static_assert(offsetof(TurtleGardens, countdown) == 0x654 && offsetof(TurtleGardens, state) == 0x658, "TurtleGardens");
static_assert(offsetof(TurtleGardens, talk) == 0x65c && offsetof(TurtleGardens, event_day) == 0x718, "TurtleGardens");
static_assert(sizeof(TurtleGardens) == 0x71c, "the size TurtleGardens_Create allocates");
static_assert(sizeof(TurtleGardensStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define TURTLE_GARDENS_PERSON 0xea          /* u16: his person code */
#define TURTLE_GARDENS_MODEL 0xec           /* LayeredModel */
#define TURTLE_GARDENS_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TURTLE_GARDENS_FACE 0x2ac           /* SceneFace */
#define TURTLE_GARDENS_ANIM 0x334           /* SpeakerAnim */
#define TURTLE_GARDENS_MOVER 0x350          /* SceneMover */
#define TURTLE_GARDENS_PROBE 0x3a8          /* the probe */
#define TURTLE_GARDENS_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define TURTLE_GARDENS_LOOK 0x3b0           /* SceneLook */
#define TURTLE_GARDENS_TALK_STATE 0x418     /* SceneTalkState */
#define TURTLE_GARDENS_EFFECTS 0x420        /* ActEffects */
#define TURTLE_GARDENS_COLLIDER 0x49c       /* CollisionContacts */
#define TURTLE_GARDENS_CARRIER 0x4cc        /* FieldOwnedBody */
#define TURTLE_GARDENS_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define TURTLE_GARDENS_EMITTER 0x514        /* SoundEmitterObject */
#define TURTLE_GARDENS_FOOTSTEPS 0x558      /* Footsteps */
#define TURTLE_GARDENS_MOTION 0x564         /* SceneMotion */
#define TURTLE_GARDENS_ACTION 0x618         /* SceneAction */
#define TURTLE_GARDENS_HEAP 0x640           /* PoolLink */

#define TURTLE_GARDENS_NO_ITEM 0xfff1
#define TURTLE_GARDENS_HELD 2

/* The field actor of this console's player. */
#define TURTLE_GARDENS_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player talked to him, the
 * event ended. */
#define TURTLE_GARDENS_EVENT_TALK 0
#define TURTLE_GARDENS_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it (the scene base's reset). */
#define TURTLE_GARDENS_SLOT_RESET 0x08

/* His animation on start (speed 1.0, slot 1) and the nodes of his model moved to its part A. */
#define TURTLE_GARDENS_START_ANIM 0x140
#define TURTLE_GARDENS_NODES_FIRST 0x0c
#define TURTLE_GARDENS_NODES_LAST 0x0e

/* His stand (scene_motion_request.h). */
#define TURTLE_GARDENS_MOTION_STAND 0

/* The record's kind for the gardens, the event of EventWinner_ExpireForEvent the record is
 * kept for (0: the calendar's event 0x0e), and the state block's flag of a winner to announce. */
#define TURTLE_GARDENS_RECORD_KIND EVENT_WINNER_KIND_GARDENS
#define TURTLE_GARDENS_RECORD_EVENT 0
#define TURTLE_GARDENS_NOTICE_FLAG 0x0f

/* The calendar's event whose days he counts, and the frames between two judgings (10
 * seconds). */
#define TURTLE_GARDENS_EVENT 0x0e
#define TURTLE_GARDENS_JUDGE_FRAMES 600

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov083_0227928c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov083_022791a8[];
extern const char data_ov083_022791d8[];
/* The functions of his states (filled at start-up by __sinit_ov083_02279100). */
extern TurtleGardensStep data_ov083_02279360[TURTLE_GARDENS_STATES];
/* The town's record of the day's winner, the state block, and the word his motion requests
 * carry. */
extern EventWinner data_021f3aa4;
extern u32 data_021dc7a8[];
extern u16 data_020c80f8;

static u8 *turtle_gardens_part(TurtleGardens *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneAction *turtle_gardens_action(TurtleGardens *turtle)
{
    return (SceneAction *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_ACTION);
}

/* ---- His object */

/* func_ov083_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
TurtleGardens *TurtleGardens_Destruct(TurtleGardens *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov083_0227928c;
    TurtleGardensTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov083_02278a00, TurtleGardens_Destruct)

/* func_ov083_02278a28 (vtable slot 0x44): the same, then the object freed. */
TurtleGardens *TurtleGardens_DestructDelete(TurtleGardens *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov083_0227928c;
    TurtleGardensTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov083_02278a28, TurtleGardens_DestructDelete)

/* func_ov083_02278a54 (vtable slot 0x4c, an event about him): when the player talked to him,
 * his talk scene is reset and given the player's field actor, and he talks (state 1); once the
 * event ended he stands (state 0). */
void TurtleGardens_OnEvent(TurtleGardens *turtle, int code)
{
    switch (code) {
        case TURTLE_GARDENS_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &turtle->talk;
            u32 reset = *(const u32 *) (uintptr_t) (vtable + TURTLE_GARDENS_SLOT_RESET);
            ((void (*)(TurtleGardensTalk *))(uintptr_t) reset)(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.base, SceneObject_ActorObject(turtle->base, TURTLE_GARDENS_PLAYER_ACTOR));
            TurtleGardens_SetState(turtle, TURTLE_GARDENS_TALK);
            break;
        }
        case TURTLE_GARDENS_EVENT_ENDED:
            TurtleGardens_SetState(turtle, TURTLE_GARDENS_STAND);
            break;
    }
}
CLEAN_AS(func_ov083_02278a54, TurtleGardens_OnEvent)

/* func_ov083_02278a98 (vtable slot 0x48): the player may talk to him while his action is
 * idle. */
int TurtleGardens_AgreesToTalk(TurtleGardens *turtle)
{
    return SceneAction_IsBusy(turtle_gardens_action(turtle)) == 0;
}
CLEAN_AS(func_ov083_02278a98, TurtleGardens_AgreesToTalk)

/* func_ov083_02278e98: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded); him at a word-aligned address, as
 * every object of the game (the ROM's store drops the low two bits). */
void TurtleGardens_SetState(TurtleGardens *turtle, int state)
{
    const TurtleGardensStep *step = &data_ov083_02279360[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov083_02278e98, TurtleGardens_SetState)

/* func_ov083_02278edc (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: his state is 0 to 2. */
int TurtleGardens_Update(TurtleGardens *turtle)
{
    const TurtleGardensStep *step = &data_ov083_02279360[turtle->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, turtle);
}
CLEAN_AS(func_ov083_02278edc, TurtleGardens_Update)

/* func_ov083_02278f28 (vtable slot 0x70): his model's file name. */
int TurtleGardens_ModelName(void)
{
    return (int) (uintptr_t) data_ov083_022791a8;
}
CLEAN_AS(func_ov083_02278f28, TurtleGardens_ModelName)

/* func_ov083_02278f30 (vtable slot 0x6c): his texture's file name. */
int TurtleGardens_TextureName(void)
{
    return (int) (uintptr_t) data_ov083_022791d8;
}
CLEAN_AS(func_ov083_02278f30, TurtleGardens_TextureName)

/* func_ov083_02278f38 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 0); his animation player plays animation 0x140 (speed 1.0, slot 1),
 * his model's nodes 0x0c-0x0e go to its part A and he is held; the days since the start of
 * event 0x0e are noted, and the record of the day dropped unless it is still of that event.
 * Whether he started.
 * REQUIRES: him at a word-aligned address (his flags are a word). */
int TurtleGardens_Start(TurtleGardens *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    TurtleGardens_SetState(turtle, TURTLE_GARDENS_STAND);
    SpeakerAnim_Play((SpeakerAnim *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_ANIM), turtle->base,
                     TURTLE_GARDENS_START_ANIM, 0, 0, 0x1000, 0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_MODEL),
                              TURTLE_GARDENS_NODES_FIRST, TURTLE_GARDENS_NODES_LAST);
    *(u32 *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_HELD_FLAGS) |= TURTLE_GARDENS_HELD;
    turtle->event_day = (u8) EventCalendar_DaysSinceStart(TURTLE_GARDENS_EVENT);
    EventWinner_ExpireForEvent(&data_021f3aa4, TURTLE_GARDENS_RECORD_EVENT);
    return 1;
}
CLEAN_AS(func_ov083_02278f38, TurtleGardens_Start)

/* func_ov083_02278fb8 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int TurtleGardens_Init(TurtleGardens *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.base);
    TurtleGardensTalk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov083_02278fb8, TurtleGardens_Init)

/* func_ov083_02278fe8 (his record's create function): a zeroed block of 0x71c bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then his
 * class's vtable and his talk scene. Null when there is no room. */
void *TurtleGardens_Create(void)
{
    TurtleGardens *turtle = (TurtleGardens *) Heap_AllocAuxZeroed(sizeof(TurtleGardens));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_PERSON) = TURTLE_GARDENS_NO_ITEM;
    LayeredModel_ConstructB((LayeredModel *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_ANIM));
    SceneMover_Construct((SceneMover *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_MOVER));
    SceneProbe_Construct(turtle_gardens_part(turtle, TURTLE_GARDENS_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_MOTION));
    SceneAction_Construct(turtle_gardens_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_HEAP));
    *(const u8 **) (void *) object = data_ov083_0227928c;
    TurtleGardensTalk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov083_02278fe8, TurtleGardens_Create)

/* ---- His states */

/* func_ov083_02278e64 (state 0's entry): he stands (priority 1, the plain word). 1. */
int TurtleGardens_EnterStand(TurtleGardens *turtle)
{
    SceneMotion_Request((SceneMotion *) (void *) turtle_gardens_part(turtle, TURTLE_GARDENS_MOTION),
                        TURTLE_GARDENS_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov083_02278e64, TurtleGardens_EnterStand)

/* func_ov083_02278e08: a count down by one unless it is 0; the count. The object is not
 * used. */
int TurtleGardens_CountDown(TurtleGardens *turtle, s32 *counter)
{
    (void) turtle;
    if (*counter != 0) {
        (*counter)--;
    }
    return *counter;
}
CLEAN_AS(func_ov083_02278e08, TurtleGardens_CountDown)

/* func_ov083_02278e18 (state 0's update): when his count down reaches 0 it starts again at 600
 * frames, the gardens are judged into the record of the day, which is then of the gardens, and
 * a winner is to be announced. 1. */
int TurtleGardens_UpdateStand(TurtleGardens *turtle)
{
    if (TurtleGardens_CountDown(turtle, &turtle->countdown) != 0) {
        return 1;
    }
    turtle->countdown = TURTLE_GARDENS_JUDGE_FRAMES;
    EventWinner *record = &data_021f3aa4;
    EventWinner_JudgeGardens(record);
    EventWinner_SetKind(record, TURTLE_GARDENS_RECORD_KIND);
    StateBlock_SetFlag(data_021dc7a8, TURTLE_GARDENS_NOTICE_FLAG);
    return 1;
}
CLEAN_AS(func_ov083_02278e18, TurtleGardens_UpdateStand)

/* func_ov083_02278dd0 (state 1's entry): he turns to his talk's partner (when it has one, else
 * to angle 0) and talks. 1. */
int TurtleGardens_EnterTalk(TurtleGardens *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(turtle_gardens_action(turtle), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov083_02278dd0, TurtleGardens_EnterTalk)

/* func_ov083_02278da4 (state 1's update): once his action is idle, his event is finished and
 * he has talked (state 2). 1. */
int TurtleGardens_UpdateTalk(TurtleGardens *turtle)
{
    if (SceneAction_IsBusy(turtle_gardens_action(turtle)) == 0) {
        EventQueue_FinishObjectEvent(turtle);
        TurtleGardens_SetState(turtle, TURTLE_GARDENS_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov083_02278da4, TurtleGardens_UpdateTalk)

/* func_ov083_02278da0 (state 2's update): 1. */
int TurtleGardens_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov083_02278da0, TurtleGardens_UpdateTalked)
