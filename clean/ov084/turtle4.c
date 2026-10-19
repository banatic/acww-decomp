/* The turtle of overlay 84: his object, his states and his creation (turtle4.h). */
#include "turtle4.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/calendar.h"
#include "main/event_queue.h"
#include "main/event_winner.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
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
#include "turtle4_talk.h"

static_assert(sizeof(Turtle4Step) == 0x10, "a state's functions");
static_assert(offsetof(Turtle4, state) == 0x654, "state");
static_assert(offsetof(Turtle4, talk) == 0x658, "talk scene");
static_assert(sizeof(Turtle4Talk) == 0xbc, "talk scene size");
static_assert(offsetof(Turtle4, week) == 0x714, "week");
static_assert(sizeof(Turtle4) == 0x718, "the size Turtle4_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define T4_PERSON 0xea          /* u16: its person code */
#define T4_MODEL 0xec           /* LayeredModel */
#define T4_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define T4_FACE 0x2ac           /* SceneFace */
#define T4_ANIM 0x334           /* SpeakerAnim */
#define T4_MOVER 0x350          /* SceneMover */
#define T4_PROBE 0x3a8          /* the probe ahead */
#define T4_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define T4_LOOK 0x3b0           /* SceneLook */
#define T4_TALK_STATE 0x418     /* SceneTalkState */
#define T4_EFFECTS 0x420        /* ActEffects */
#define T4_COLLIDER 0x49c       /* CollisionContacts */
#define T4_CARRIER 0x4cc        /* FieldOwnedBody */
#define T4_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define T4_EMITTER 0x514        /* SoundEmitterObject */
#define T4_FOOTSTEPS 0x558      /* Footsteps */
#define T4_MOTION 0x564         /* SceneMotion */
#define T4_ACTION 0x618         /* SceneAction */
#define T4_HEAP 0x640           /* PoolLink */

#define T4_NO_PERSON 0xfff1
#define T4_HELD 2

/* The field actor of this console's player. */
#define T4_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player's act (the talk) and
 * the event's end. */
#define T4_EVENT_ACT 0
#define T4_EVENT_ENDED 8

/* The talk scene's vtable slot his talks call first (SceneBase_Reset). */
#define T4_TALK_SLOT_08 0x08

/* His animation on his start (speed 1.0, slot 1) and the nodes of his model moved to its part
 * A. */
#define T4_START_ANIM 0x140
#define T4_START_ANIM_SPEED 0x1000
#define T4_NODES_FIRST 0x0c
#define T4_NODES_LAST 0x0e

/* The days of a week of the month. */
#define T4_DAYS_IN_WEEK 7

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov084_022794ac[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His states' functions (filled at start-up by __sinit_ov084_0227931c). */
extern Turtle4Step data_ov084_022795a0[TURTLE4_STATES];
/* His model's and texture's file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov084_022793c8[];
extern const char data_ov084_022793f8[];
/* The word his motion requests carry. */
extern u16 data_020c80f8;
/* The record of who won one of the town's events. */
extern EventWinner data_021f3aa4;

static u8 *t4_part(Turtle4 *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneMotion *t4_motion(Turtle4 *turtle)
{
    return (SceneMotion *) (void *) t4_part(turtle, T4_MOTION);
}

static SceneAction *t4_action(Turtle4 *turtle)
{
    return (SceneAction *) (void *) t4_part(turtle, T4_ACTION);
}

/* func_ov084_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
Turtle4 *Turtle4_Destroy(Turtle4 *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov084_022794ac;
    Turtle4Talk_Destroy(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov084_02278a00, Turtle4_Destroy)

/* func_ov084_02278a28 (vtable slot 0x44): the same, then the object freed. */
void *Turtle4_Delete(void *object)
{
    Turtle4 *turtle = object;
    *(const u8 **) (void *) turtle->base = data_ov084_022794ac;
    Turtle4Talk_Destroy(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov084_02278a28, Turtle4_Delete)

/* func_ov084_02278a54 (vtable slot 0x4c, told of an event about him): code 0, the player's
 * act: his talk scene told through its slot 0x08, the talk's partner this console's player's
 * object, and he talks (state 1); code 8, the event ended: he stands (state 0). */
void Turtle4_OnEvent(Turtle4 *turtle, int code)
{
    switch (code) {
        case T4_EVENT_ACT: {
            u32 vtable = *(const u32 *) (const void *) &turtle->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + T4_TALK_SLOT_08);
            ((void (*)(Turtle4Talk *))(uintptr_t) slot)(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.base, SceneObject_ActorObject(turtle->base, T4_PLAYER_ACTOR));
            Turtle4_SetState(turtle, TURTLE4_TALKING);
            break;
        }
        case T4_EVENT_ENDED:
            Turtle4_SetState(turtle, TURTLE4_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov084_02278a54, Turtle4_OnEvent)

/* func_ov084_02278a98 (vtable slot 0x48): whether the player may talk to him: his action is
 * idle. */
int Turtle4_MayAct(Turtle4 *turtle)
{
    return !SceneAction_IsBusy(t4_action(turtle));
}
CLEAN_AS(func_ov084_02278a98, Turtle4_MayAct)

/* func_ov084_02278fe0 (state 2's update): nothing. 1. */
int Turtle4_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov084_02278fe0, Turtle4_UpdateTalked)

/* func_ov084_02278fe4 (state 1's update): once his action is idle, the object's event ends and
 * state 2 follows. 1. */
int Turtle4_UpdateTalk(Turtle4 *turtle)
{
    if (!SceneAction_IsBusy(t4_action(turtle))) {
        EventQueue_FinishObjectEvent(turtle);
        Turtle4_SetState(turtle, TURTLE4_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov084_02278fe4, Turtle4_UpdateTalk)

/* func_ov084_02279010 (state 1's entry): he turns to the talk's partner (to angle 0 without
 * one) and talks. 1. */
int Turtle4_EnterTalk(Turtle4 *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.base);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(t4_action(turtle), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov084_02279010, Turtle4_EnterTalk)

/* func_ov084_02279048 (state 0's update): nothing. 1. */
int Turtle4_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov084_02279048, Turtle4_UpdateStand)

/* func_ov084_0227904c (state 0's entry): his motion of kind 0 asked for (priority 1). 1. */
int Turtle4_EnterStand(Turtle4 *turtle)
{
    SceneMotion_Request(t4_motion(turtle), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov084_0227904c, Turtle4_EnterStand)

/* func_ov084_02279080: state `state` taken unless its entry function, when it has one, answers
 * 0.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void Turtle4_SetState(Turtle4 *turtle, int state)
{
    const Turtle4Step *step = &data_ov084_022795a0[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov084_02279080, Turtle4_SetState)

/* func_ov084_022790c4 (vtable slot 0x68, each frame): his state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: his state is 0 to 2. */
int Turtle4_Update(Turtle4 *turtle)
{
    const Turtle4Step *step = &data_ov084_022795a0[turtle->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, turtle);
}
CLEAN_AS(func_ov084_022790c4, Turtle4_Update)

/* func_ov084_02279110 (vtable slot 0x70): his model's file name, "npc_sp/model/ttl.nsbmd". */
int Turtle4_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov084_022793c8;
}
CLEAN_AS(func_ov084_02279110, Turtle4_ModelName)

/* func_ov084_02279118 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/ttl_tex.nsbtx". */
int Turtle4_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov084_022793f8;
}
CLEAN_AS(func_ov084_02279118, Turtle4_TextureName)

/* func_ov084_02279120 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 0), the event winner record is started afresh unless it is of today
 * (mode 0), his animation player plays animation 0x140 (speed 1.0, slot 1), his model's nodes
 * 0x0c-0x0e go to its part A, he is held (flag 2 at 0x4e8) and today's week of the month is
 * noted. Whether he started. */
int Turtle4_Start(Turtle4 *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    Turtle4_SetState(turtle, TURTLE4_STAND);
    EventWinner_ResetIfNotToday(&data_021f3aa4, 0);
    SpeakerAnim_Play((SpeakerAnim *) (void *) t4_part(turtle, T4_ANIM), turtle->base, T4_START_ANIM, 0, 0, T4_START_ANIM_SPEED,
                     0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) t4_part(turtle, T4_MODEL), T4_NODES_FIRST, T4_NODES_LAST);
    *(u32 *) (void *) t4_part(turtle, T4_HELD_FLAGS) |= T4_HELD;

    Date today;
    Calendar_Today(&today);
    turtle->week = (u8) ((today.day - 1) / T4_DAYS_IN_WEEK);
    turtle->week++;
    return 1;
}
CLEAN_AS(func_ov084_02279120, Turtle4_Start)

/* func_ov084_022791b4 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int Turtle4_Init(Turtle4 *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.base);
    Turtle4Talk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov084_022791b4, Turtle4_Init)

/* func_ov084_022791e4 (the create function his record at 0x022793e0 names): a zeroed
 * block of 0x718 bytes from the auxiliary heap, constructed: the scene object base, the
 * class 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *Turtle4_Create(void)
{
    Turtle4 *turtle = (Turtle4 *) Heap_AllocAuxZeroed(sizeof(Turtle4));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) t4_part(turtle, T4_PERSON) = T4_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) t4_part(turtle, T4_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) t4_part(turtle, T4_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) t4_part(turtle, T4_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) t4_part(turtle, T4_ANIM));
    SceneMover_Construct((SceneMover *) (void *) t4_part(turtle, T4_MOVER));
    SceneProbe_Construct(t4_part(turtle, T4_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) t4_part(turtle, T4_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) t4_part(turtle, T4_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) t4_part(turtle, T4_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) t4_part(turtle, T4_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) t4_part(turtle, T4_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) t4_part(turtle, T4_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) t4_part(turtle, T4_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) t4_part(turtle, T4_FOOTSTEPS));
    SceneMotion_Construct(t4_motion(turtle));
    SceneAction_Construct(t4_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) t4_part(turtle, T4_HEAP));
    *(const u8 **) (void *) object = data_ov084_022794ac;
    Turtle4Talk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov084_022791e4, Turtle4_Create)
