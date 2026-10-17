/* Overlay 80's turtle (turtle.h): his object, his states and his creation. */
#include "turtle.h"

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
#include "main/player_record.h"
#include "main/player_records.h"
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
#include "turtle_talk.h"

static_assert(sizeof(TurtleStateRow) == 0x10, "a state's functions");
static_assert(offsetof(Turtle, state) == 0x654, "state");
static_assert(offsetof(Turtle, talk) == 0x658, "talk scene");
static_assert(sizeof(Turtle) == 0x710, "the size Turtle_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define TURTLE_PERSON 0xea          /* u16: its person code */
#define TURTLE_MODEL 0xec           /* LayeredModel */
#define TURTLE_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TURTLE_FACE 0x2ac           /* SceneFace */
#define TURTLE_ANIM 0x334           /* SpeakerAnim */
#define TURTLE_MOVER 0x350          /* SceneMover */
#define TURTLE_PROBE 0x3a8          /* the probe ahead */
#define TURTLE_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define TURTLE_LOOK 0x3b0           /* SceneLook */
#define TURTLE_TALK_STATE 0x418     /* SceneTalkState */
#define TURTLE_EFFECTS 0x420        /* ActEffects */
#define TURTLE_COLLIDER 0x49c       /* CollisionContacts */
#define TURTLE_CARRIER 0x4cc        /* FieldOwnedBody */
#define TURTLE_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define TURTLE_EMITTER 0x514        /* SoundEmitterObject */
#define TURTLE_FOOTSTEPS 0x558      /* Footsteps */
#define TURTLE_MOTION 0x564         /* SceneMotion */
#define TURTLE_ACTION 0x618         /* SceneAction */
#define TURTLE_HEAP 0x640           /* PoolLink */

#define TURTLE_NO_PERSON 0xfff1
#define TURTLE_HELD 2

/* The field actor of this console's player. */
#define TURTLE_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player's act (the talk) and
 * the event's end. */
#define TURTLE_EVENT_ACT 0
#define TURTLE_EVENT_ENDED 8

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define TURTLE_TALK_SLOT_RESET 2

/* His start: animation 0x140 at speed 1.0 in slot 1; his model's nodes 0xc-0xe moved; the
 * flag of the player's record that keeps the event queue's flag 0x20 clear. */
#define TURTLE_START_ANIMATION 0x140
#define TURTLE_START_SPEED 0x1000
#define TURTLE_START_SLOT 1
#define TURTLE_NODES_FIRST 0xc
#define TURTLE_NODES_LAST 0xe
#define TURTLE_PLAYER_FLAG_1 1

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov080_022792ec[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model's and texture's file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov080_02279208[];
extern const char data_ov080_02279238[];
/* The word his motion requests carry. */
extern u16 data_020c80f8;

static u8 *turtle_part(Turtle *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneMotion *turtle_motion(Turtle *turtle)
{
    return (SceneMotion *) (void *) turtle_part(turtle, TURTLE_MOTION);
}

static SceneAction *turtle_action(Turtle *turtle)
{
    return (SceneAction *) (void *) turtle_part(turtle, TURTLE_ACTION);
}

/* func_ov080_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
Turtle *Turtle_Destruct(Turtle *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov080_022792ec;
    TurtleTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov080_02278a00, Turtle_Destruct)

/* func_ov080_02278a28 (vtable slot 0x44): the same, then the object freed. */
Turtle *Turtle_DestructDelete(Turtle *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov080_022792ec;
    TurtleTalk_Destruct(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov080_02278a28, Turtle_DestructDelete)

/* func_ov080_02278a54 (vtable slot 0x4c, told of an event about him): code 0, the player's
 * act: his talk reset (its slot 2), the talk's partner this console's player's object, and he
 * talks (TURTLE_TALK); code 8, the event ended: he stands (TURTLE_STAND). The base class is
 * not told. */
void Turtle_OnEvent(Turtle *turtle, int code)
{
    switch (code) {
        case TURTLE_EVENT_ACT: {
            const u32 *vtable = (const u32 *) (const void *) turtle->talk.scene.vtable;
            ((void (*)(TurtleTalk *))(uintptr_t) vtable[TURTLE_TALK_SLOT_RESET])(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.scene, SceneObject_ActorObject(turtle->base, TURTLE_PLAYER_ACTOR));
            Turtle_SetState(turtle, TURTLE_TALK);
            break;
        }
        case TURTLE_EVENT_ENDED:
            Turtle_SetState(turtle, TURTLE_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov080_02278a54, Turtle_OnEvent)

/* func_ov080_02278a98 (vtable slot 0x48): whether the player may talk to him: his action is
 * idle. */
int Turtle_MayAct(Turtle *turtle)
{
    return !SceneAction_IsBusy(turtle_action(turtle));
}
CLEAN_AS(func_ov080_02278a98, Turtle_MayAct)

/* func_ov080_02278e60 (TURTLE_TALKED's run): nothing. 1. */
int Turtle_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov080_02278e60, Turtle_UpdateTalked)

/* func_ov080_02278e64 (TURTLE_TALK's run): once his action is idle, the object's event ends
 * and TURTLE_TALKED follows. 1. */
int Turtle_UpdateTalk(Turtle *turtle)
{
    if (!SceneAction_IsBusy(turtle_action(turtle))) {
        EventQueue_FinishObjectEvent(turtle);
        Turtle_SetState(turtle, TURTLE_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov080_02278e64, Turtle_UpdateTalk)

/* func_ov080_02278e90 (TURTLE_TALK's entry): he turns to the talk's partner (to angle 0
 * without one) and talks. 1. */
int Turtle_EnterTalk(Turtle *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.scene);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(turtle_action(turtle), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov080_02278e90, Turtle_EnterTalk)

/* func_ov080_02278ec8 (TURTLE_STAND's run): nothing. 1. */
int Turtle_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov080_02278ec8, Turtle_UpdateStand)

/* func_ov080_02278ecc (TURTLE_STAND's entry): his motion of kind 0 asked for (priority 1). 1. */
int Turtle_EnterStand(Turtle *turtle)
{
    SceneMotion_Request(turtle_motion(turtle), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov080_02278ecc, Turtle_EnterStand)

/* func_ov080_02278f00: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void Turtle_SetState(Turtle *turtle, int state)
{
    const TurtleStateRow *row = &data_ov080_022793e0[state];
    int taken = 1;
    if (row->enter.function != 0) {
        taken = MemberPointer_CallInt(&row->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov080_02278f00, Turtle_SetState)

/* func_ov080_02278f44 (vtable slot 0x68, each frame): his state's run when it has one, and its
 * answer; else 0.
 * REQUIRES: his state is 0 to 2. */
int Turtle_Update(Turtle *turtle)
{
    const TurtleStateRow *row = &data_ov080_022793e0[turtle->state];
    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, turtle);
}
CLEAN_AS(func_ov080_02278f44, Turtle_Update)

/* func_ov080_02278f90 (vtable slot 0x70): his model's file name, "npc_sp/model/ttl.nsbmd". */
int Turtle_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov080_02279208;
}
CLEAN_AS(func_ov080_02278f90, Turtle_ModelName)

/* func_ov080_02278f98 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/ttl_tex.nsbtx". */
int Turtle_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov080_02279238;
}
CLEAN_AS(func_ov080_02278f98, Turtle_TextureName)

/* func_ov080_02278fa0 (vtable slot 0x0c): whether the special character leaves, as 0 or 1. */
int Turtle_Leave(Turtle *turtle)
{
    return SpecialSceneObject_Leave(turtle) != 0;
}
CLEAN_AS(func_ov080_02278fa0, Turtle_Leave)

/* func_ov080_02278fb8 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (TURTLE_STAND), plays animation 0x140 (speed 1.0, slot 1), the nodes 0xc-0xe
 * of his model are moved to its first set, he is held (flag 2 at 0x4e8), and unless the
 * current player's record has flag 1 the event queue's flag 0x20 is set. Whether he started. */
int Turtle_Start(Turtle *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    Turtle_SetState(turtle, TURTLE_STAND);
    SpeakerAnim_Play((SpeakerAnim *) (void *) turtle_part(turtle, TURTLE_ANIM), turtle->base, TURTLE_START_ANIMATION, 0, 0,
                     TURTLE_START_SPEED, 0, TURTLE_START_SLOT);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) turtle_part(turtle, TURTLE_MODEL), TURTLE_NODES_FIRST,
                              TURTLE_NODES_LAST);
    *(u32 *) (void *) turtle_part(turtle, TURTLE_HELD_FLAGS) |= TURTLE_HELD;
    if (PlayerRecord_TestFlag(PlayerRecords_Current(), TURTLE_PLAYER_FLAG_1) == 0) {
        EventQueue_SetFlag20();
    }
    return 1;
}
CLEAN_AS(func_ov080_02278fb8, Turtle_Start)

/* func_ov080_02279030 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int Turtle_Init(Turtle *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.scene);
    TurtleTalk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov080_02279030, Turtle_Init)

/* func_ov080_02279060 (the create function his record at 0x02279220 names): a zeroed block of
 * 0x710 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
Turtle *Turtle_Create(void)
{
    Turtle *turtle = (Turtle *) Heap_AllocAuxZeroed(sizeof(Turtle));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) turtle_part(turtle, TURTLE_PERSON) = TURTLE_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) turtle_part(turtle, TURTLE_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) turtle_part(turtle, TURTLE_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) turtle_part(turtle, TURTLE_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) turtle_part(turtle, TURTLE_ANIM));
    SceneMover_Construct((SceneMover *) (void *) turtle_part(turtle, TURTLE_MOVER));
    SceneProbe_Construct(turtle_part(turtle, TURTLE_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) turtle_part(turtle, TURTLE_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) turtle_part(turtle, TURTLE_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) turtle_part(turtle, TURTLE_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) turtle_part(turtle, TURTLE_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) turtle_part(turtle, TURTLE_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) turtle_part(turtle, TURTLE_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) turtle_part(turtle, TURTLE_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) turtle_part(turtle, TURTLE_FOOTSTEPS));
    SceneMotion_Construct(turtle_motion(turtle));
    SceneAction_Construct(turtle_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) turtle_part(turtle, TURTLE_HEAP));
    *(const u8 **) (void *) object = data_ov080_022792ec;
    TurtleTalk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov080_02279060, Turtle_Create)
