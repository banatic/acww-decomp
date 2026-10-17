/* The turtle of overlay 086: his object, his states and his creation (turtle6.h). */
#include "turtle6.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/event_queue.h"
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
#include "turtle6_talk.h"

static_assert(sizeof(Turtle6Step) == 0x10, "a state's functions");
static_assert(offsetof(Turtle6, state) == 0x654, "state");
static_assert(offsetof(Turtle6, talk) == 0x658, "talk scene");
static_assert(sizeof(Turtle6Talk) == 0xb8, "talk scene size");
static_assert(sizeof(Turtle6) == 0x710, "the size Turtle6_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define T6_PERSON 0xea          /* u16: its person code */
#define T6_MODEL 0xec           /* LayeredModel */
#define T6_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define T6_FACE 0x2ac           /* SceneFace */
#define T6_ANIM 0x334           /* SpeakerAnim */
#define T6_MOVER 0x350          /* SceneMover */
#define T6_PROBE 0x3a8          /* the probe ahead */
#define T6_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define T6_LOOK 0x3b0           /* SceneLook */
#define T6_TALK_STATE 0x418     /* SceneTalkState */
#define T6_EFFECTS 0x420        /* ActEffects */
#define T6_COLLIDER 0x49c       /* CollisionContacts */
#define T6_CARRIER 0x4cc        /* FieldOwnedBody */
#define T6_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define T6_EMITTER 0x514        /* SoundEmitterObject */
#define T6_FOOTSTEPS 0x558      /* Footsteps */
#define T6_MOTION 0x564         /* SceneMotion */
#define T6_ACTION 0x618         /* SceneAction */
#define T6_HEAP 0x640           /* PoolLink */

#define T6_NO_PERSON 0xfff1
#define T6_HELD 2

/* The field actor of this console's player. */
#define T6_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player's act (the talk) and
 * the event's end. */
#define T6_EVENT_ACT 0
#define T6_EVENT_ENDED 8

/* The talk scene's vtable slot his talks call first (SceneBase_Reset). */
#define T6_TALK_SLOT_08 0x08

/* His animation on his start (speed 1.0, slot 1) and the nodes of his model moved to its part
 * A. */
#define T6_START_ANIM 0x140
#define T6_START_ANIM_SPEED 0x1000
#define T6_NODES_FIRST 0x0c
#define T6_NODES_LAST 0x0e

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov086_0227938c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His states' functions (filled at start-up by __sinit_ov086_022791f0). */
extern Turtle6Step data_ov086_02279480[TURTLE6_STATES];
/* His model's and texture's file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov086_022792a8[];
extern const char data_ov086_022792d8[];
/* The word his motion requests carry. */
extern u16 data_020c80f8;

static u8 *t6_part(Turtle6 *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneMotion *t6_motion(Turtle6 *turtle)
{
    return (SceneMotion *) (void *) t6_part(turtle, T6_MOTION);
}

static SceneAction *t6_action(Turtle6 *turtle)
{
    return (SceneAction *) (void *) t6_part(turtle, T6_ACTION);
}

/* func_ov086_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
Turtle6 *Turtle6_Destroy(Turtle6 *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov086_0227938c;
    Turtle6Talk_Destroy(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov086_02278a00, Turtle6_Destroy)

/* func_ov086_02278a28 (vtable slot 0x44): the same, then the object freed. */
void *Turtle6_Delete(void *object)
{
    Turtle6 *turtle = object;
    *(const u8 **) (void *) turtle->base = data_ov086_0227938c;
    Turtle6Talk_Destroy(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov086_02278a28, Turtle6_Delete)

/* func_ov086_02278a54 (vtable slot 0x4c, told of an event about him): code 0, the player's
 * act: his talk scene told through its slot 0x08, the talk's partner this console's player's
 * object, and he talks (state 1); code 8, the event ended: he stands (state 0). */
void Turtle6_OnEvent(Turtle6 *turtle, int code)
{
    switch (code) {
        case T6_EVENT_ACT: {
            u32 vtable = *(const u32 *) (const void *) &turtle->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + T6_TALK_SLOT_08);
            ((void (*)(Turtle6Talk *))(uintptr_t) slot)(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.base, SceneObject_ActorObject(turtle->base, T6_PLAYER_ACTOR));
            Turtle6_SetState(turtle, TURTLE6_TALKING);
            break;
        }
        case T6_EVENT_ENDED:
            Turtle6_SetState(turtle, TURTLE6_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov086_02278a54, Turtle6_OnEvent)

/* func_ov086_02278a98 (vtable slot 0x48): whether the player may talk to him: his action is
 * idle. */
int Turtle6_MayAct(Turtle6 *turtle)
{
    return !SceneAction_IsBusy(t6_action(turtle));
}
CLEAN_AS(func_ov086_02278a98, Turtle6_MayAct)

/* func_ov086_02278ee0 (state 2's update): nothing. 1. */
int Turtle6_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov086_02278ee0, Turtle6_UpdateTalked)

/* func_ov086_02278ee4 (state 1's update): once his action is idle, the object's event ends and
 * state 2 follows. 1. */
int Turtle6_UpdateTalk(Turtle6 *turtle)
{
    if (!SceneAction_IsBusy(t6_action(turtle))) {
        EventQueue_FinishObjectEvent(turtle);
        Turtle6_SetState(turtle, TURTLE6_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov086_02278ee4, Turtle6_UpdateTalk)

/* func_ov086_02278f10 (state 1's entry): he turns to the talk's partner (to angle 0 without
 * one) and talks. 1. */
int Turtle6_EnterTalk(Turtle6 *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.base);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(t6_action(turtle), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov086_02278f10, Turtle6_EnterTalk)

/* func_ov086_02278f48 (state 0's update): nothing. 1. */
int Turtle6_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov086_02278f48, Turtle6_UpdateStand)

/* func_ov086_02278f4c (state 0's entry): his motion of kind 0 asked for (priority 1). 1. */
int Turtle6_EnterStand(Turtle6 *turtle)
{
    SceneMotion_Request(t6_motion(turtle), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov086_02278f4c, Turtle6_EnterStand)

/* func_ov086_02278f80: state `state` taken unless its entry function, when it has one, answers
 * 0.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void Turtle6_SetState(Turtle6 *turtle, int state)
{
    const Turtle6Step *step = &data_ov086_02279480[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov086_02278f80, Turtle6_SetState)

/* func_ov086_02278fc4 (vtable slot 0x68, each frame): his state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: his state is 0 to 2. */
int Turtle6_Update(Turtle6 *turtle)
{
    const Turtle6Step *step = &data_ov086_02279480[turtle->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, turtle);
}
CLEAN_AS(func_ov086_02278fc4, Turtle6_Update)

/* func_ov086_02279010 (vtable slot 0x70): his model's file name, "npc_sp/model/ttl.nsbmd". */
int Turtle6_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov086_022792a8;
}
CLEAN_AS(func_ov086_02279010, Turtle6_ModelName)

/* func_ov086_02279018 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/ttl_tex.nsbtx". */
int Turtle6_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov086_022792d8;
}
CLEAN_AS(func_ov086_02279018, Turtle6_TextureName)

/* func_ov086_02279020 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 0), his animation player plays animation 0x140 (speed 1.0, slot 1),
 * his model's nodes 0x0c-0x0e go to its part A and he is held (flag 2 at 0x4e8). Whether he
 * started. */
int Turtle6_Start(Turtle6 *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    Turtle6_SetState(turtle, TURTLE6_STAND);
    SpeakerAnim_Play((SpeakerAnim *) (void *) t6_part(turtle, T6_ANIM), turtle->base, T6_START_ANIM, 0, 0, T6_START_ANIM_SPEED,
                     0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) t6_part(turtle, T6_MODEL), T6_NODES_FIRST, T6_NODES_LAST);
    *(u32 *) (void *) t6_part(turtle, T6_HELD_FLAGS) |= T6_HELD;
    return 1;
}
CLEAN_AS(func_ov086_02279020, Turtle6_Start)

/* func_ov086_02279088 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int Turtle6_Init(Turtle6 *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.base);
    Turtle6Talk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov086_02279088, Turtle6_Init)

/* func_ov086_022790b8 (the create function his record at 0x022792c0 names): a zeroed
 * block of 0x710 bytes from the auxiliary heap, constructed: the scene object base, the
 * class 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *Turtle6_Create(void)
{
    Turtle6 *turtle = (Turtle6 *) Heap_AllocAuxZeroed(sizeof(Turtle6));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) t6_part(turtle, T6_PERSON) = T6_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) t6_part(turtle, T6_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) t6_part(turtle, T6_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) t6_part(turtle, T6_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) t6_part(turtle, T6_ANIM));
    SceneMover_Construct((SceneMover *) (void *) t6_part(turtle, T6_MOVER));
    SceneProbe_Construct(t6_part(turtle, T6_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) t6_part(turtle, T6_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) t6_part(turtle, T6_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) t6_part(turtle, T6_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) t6_part(turtle, T6_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) t6_part(turtle, T6_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) t6_part(turtle, T6_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) t6_part(turtle, T6_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) t6_part(turtle, T6_FOOTSTEPS));
    SceneMotion_Construct(t6_motion(turtle));
    SceneAction_Construct(t6_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) t6_part(turtle, T6_HEAP));
    *(const u8 **) (void *) object = data_ov086_0227938c;
    Turtle6Talk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov086_022790b8, Turtle6_Create)
