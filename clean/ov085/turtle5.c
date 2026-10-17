/* The turtle of overlay 085: his object, his states and his creation (turtle5.h). */
#include "turtle5.h"

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
#include "main/talk_checks.h"
#include "main/speaker_anim.h"
#include "turtle5_talk.h"

static_assert(sizeof(Turtle5Step) == 0x10, "a state's functions");
static_assert(offsetof(Turtle5, state) == 0x654, "state");
static_assert(offsetof(Turtle5, talk) == 0x658, "talk scene");
static_assert(sizeof(Turtle5Talk) == 0xd0, "talk scene size");
static_assert(offsetof(Turtle5, festival_day) == 0x728, "festival day");
static_assert(sizeof(Turtle5) == 0x72c, "the size Turtle5_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define T5_PERSON 0xea          /* u16: its person code */
#define T5_MODEL 0xec           /* LayeredModel */
#define T5_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define T5_FACE 0x2ac           /* SceneFace */
#define T5_ANIM 0x334           /* SpeakerAnim */
#define T5_MOVER 0x350          /* SceneMover */
#define T5_PROBE 0x3a8          /* the probe ahead */
#define T5_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define T5_LOOK 0x3b0           /* SceneLook */
#define T5_TALK_STATE 0x418     /* SceneTalkState */
#define T5_EFFECTS 0x420        /* ActEffects */
#define T5_COLLIDER 0x49c       /* CollisionContacts */
#define T5_CARRIER 0x4cc        /* FieldOwnedBody */
#define T5_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define T5_EMITTER 0x514        /* SoundEmitterObject */
#define T5_FOOTSTEPS 0x558      /* Footsteps */
#define T5_MOTION 0x564         /* SceneMotion */
#define T5_ACTION 0x618         /* SceneAction */
#define T5_HEAP 0x640           /* PoolLink */

#define T5_NO_PERSON 0xfff1
#define T5_HELD 2

/* The field actor of this console's player. */
#define T5_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player's act (the talk) and
 * the event's end. */
#define T5_EVENT_ACT 0
#define T5_EVENT_ENDED 8

/* The talk scene's vtable slot his talks call first (SceneBase_Reset). */
#define T5_TALK_SLOT_08 0x08

/* His animation on his start (speed 1.0, slot 1) and the nodes of his model moved to its part
 * A. */
#define T5_START_ANIM 0x140
#define T5_START_ANIM_SPEED 0x1000
#define T5_NODES_FIRST 0x0c
#define T5_NODES_LAST 0x0e

/* The event whose days he counts (it starts with event 0x19), the winner record's kind of
 * event for it (EventWinner_ExpireForEvent), and the current player's daily bit of a talk
 * with him. */
#define T5_FESTIVAL_EVENT 0x11
#define T5_WINNER_EVENT 1
#define T5_DAILY_TALKED 0x1f

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov085_022794f0[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His states' functions (filled at start-up by __sinit_ov085_02279368). */
extern Turtle5Step data_ov085_022795e0[TURTLE5_STATES];
/* His model's and texture's file names: "npc_sp/model/ttl.nsbmd", "npc_sp/model/ttl_tex.nsbtx". */
extern const char data_ov085_02279408[];
extern const char data_ov085_02279438[];
/* The word his motion requests carry. */
extern u16 data_020c80f8;
/* The record of who won one of the town's events. */
extern EventWinner data_021f3aa4;

static u8 *t5_part(Turtle5 *turtle, u32 offset)
{
    return turtle->base + offset;
}

static SceneMotion *t5_motion(Turtle5 *turtle)
{
    return (SceneMotion *) (void *) t5_part(turtle, T5_MOTION);
}

static SceneAction *t5_action(Turtle5 *turtle)
{
    return (SceneAction *) (void *) t5_part(turtle, T5_ACTION);
}

/* func_ov085_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
Turtle5 *Turtle5_Destroy(Turtle5 *turtle)
{
    *(const u8 **) (void *) turtle->base = data_ov085_022794f0;
    Turtle5Talk_Destroy(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    return turtle;
}
CLEAN_AS(func_ov085_02278a00, Turtle5_Destroy)

/* func_ov085_02278a28 (vtable slot 0x44): the same, then the object freed. */
void *Turtle5_Delete(void *object)
{
    Turtle5 *turtle = object;
    *(const u8 **) (void *) turtle->base = data_ov085_022794f0;
    Turtle5Talk_Destroy(&turtle->talk);
    SpecialSceneObject_DestructBody(turtle);
    Heap_FreeAux(turtle);
    return turtle;
}
CLEAN_AS(func_ov085_02278a28, Turtle5_Delete)

/* func_ov085_02278a54 (vtable slot 0x4c, told of an event about him): code 0, the player's
 * act: his talk scene told through its slot 0x08, the talk's partner this console's player's
 * object, and he talks (state 1); code 8, the event ended: he stands (state 0). */
void Turtle5_OnEvent(Turtle5 *turtle, int code)
{
    switch (code) {
        case T5_EVENT_ACT: {
            u32 vtable = *(const u32 *) (const void *) &turtle->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + T5_TALK_SLOT_08);
            ((void (*)(Turtle5Talk *))(uintptr_t) slot)(&turtle->talk);
            SceneBase_SetMotionArg(&turtle->talk.base, SceneObject_ActorObject(turtle->base, T5_PLAYER_ACTOR));
            Turtle5_SetState(turtle, TURTLE5_TALKING);
            break;
        }
        case T5_EVENT_ENDED:
            Turtle5_SetState(turtle, TURTLE5_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov085_02278a54, Turtle5_OnEvent)

/* func_ov085_02278a98 (vtable slot 0x48): whether the player may talk to him: his action is
 * idle. */
int Turtle5_MayAct(Turtle5 *turtle)
{
    return !SceneAction_IsBusy(t5_action(turtle));
}
CLEAN_AS(func_ov085_02278a98, Turtle5_MayAct)

/* func_ov085_0227904c (state 2's update): nothing. 1. */
int Turtle5_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov085_0227904c, Turtle5_UpdateTalked)

/* func_ov085_02279050 (state 1's update): once his action is idle, the object's event ends and
 * state 2 follows. 1. */
int Turtle5_UpdateTalk(Turtle5 *turtle)
{
    if (!SceneAction_IsBusy(t5_action(turtle))) {
        EventQueue_FinishObjectEvent(turtle);
        Turtle5_SetState(turtle, TURTLE5_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov085_02279050, Turtle5_UpdateTalk)

/* func_ov085_0227907c (state 1's entry): he turns to the talk's partner (to angle 0 without
 * one) and talks. 1. */
int Turtle5_EnterTalk(Turtle5 *turtle)
{
    int partner = SceneBase_MotionArg(&turtle->talk.base);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(turtle->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(t5_action(turtle), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov085_0227907c, Turtle5_EnterTalk)

/* func_ov085_022790b4 (state 0's update): nothing. 1. */
int Turtle5_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov085_022790b4, Turtle5_UpdateStand)

/* func_ov085_022790b8 (state 0's entry): his motion of kind 0 asked for (priority 1). 1. */
int Turtle5_EnterStand(Turtle5 *turtle)
{
    SceneMotion_Request(t5_motion(turtle), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov085_022790b8, Turtle5_EnterStand)

/* func_ov085_022790ec: state `state` taken unless its entry function, when it has one, answers
 * 0.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void Turtle5_SetState(Turtle5 *turtle, int state)
{
    const Turtle5Step *step = &data_ov085_022795e0[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, turtle);
    }
    if (taken != 0) {
        turtle->state = state;
    }
}
CLEAN_AS(func_ov085_022790ec, Turtle5_SetState)

/* func_ov085_02279130 (vtable slot 0x68, each frame): his state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: his state is 0 to 2. */
int Turtle5_Update(Turtle5 *turtle)
{
    const Turtle5Step *step = &data_ov085_022795e0[turtle->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, turtle);
}
CLEAN_AS(func_ov085_02279130, Turtle5_Update)

/* func_ov085_0227917c (vtable slot 0x70): his model's file name, "npc_sp/model/ttl.nsbmd". */
int Turtle5_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov085_02279408;
}
CLEAN_AS(func_ov085_0227917c, Turtle5_ModelName)

/* func_ov085_02279184 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/ttl_tex.nsbtx". */
int Turtle5_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov085_02279438;
}
CLEAN_AS(func_ov085_02279184, Turtle5_TextureName)

/* func_ov085_0227918c (vtable slot 0x00, his start): unless the special character refuses to
 * start, he stands (state 0), his animation player plays animation 0x140 (speed 1.0, slot 1),
 * his model's nodes 0x0c-0x0e go to its part A and he is held (flag 2 at 0x4e8); the day of
 * event 0x11 is noted, the event winner record is started afresh unless it is still of that
 * event, and, before the current player's first talk with him today, the villager named today
 * (the record's NpcId at 0x2e) is cleared. Whether he started. */
int Turtle5_Start(Turtle5 *turtle)
{
    if (SpecialSceneObject_Start(turtle) == 0) {
        return 0;
    }
    Turtle5_SetState(turtle, TURTLE5_STAND);
    SpeakerAnim_Play((SpeakerAnim *) (void *) t5_part(turtle, T5_ANIM), turtle->base, T5_START_ANIM, 0, 0, T5_START_ANIM_SPEED,
                     0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) t5_part(turtle, T5_MODEL), T5_NODES_FIRST, T5_NODES_LAST);
    *(u32 *) (void *) t5_part(turtle, T5_HELD_FLAGS) |= T5_HELD;
    turtle->festival_day = (u8) EventCalendar_DaysSinceStart(T5_FESTIVAL_EVENT);
    EventWinner_ExpireForEvent(&data_021f3aa4, T5_WINNER_EVENT);
    if (TalkChecks_TestSetDailyBit(T5_DAILY_TALKED, 0) == 0) {
        EventWinner_ClearNpc2E(&data_021f3aa4);
    }
    return 1;
}
CLEAN_AS(func_ov085_0227918c, Turtle5_Start)

/* func_ov085_02279220 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int Turtle5_Init(Turtle5 *turtle)
{
    if (SpecialSceneObject_Init(turtle) == 0) {
        return 0;
    }
    SceneObject_SetScene(turtle->base, &turtle->talk.base);
    Turtle5Talk_Begin(&turtle->talk, turtle);
    return 1;
}
CLEAN_AS(func_ov085_02279220, Turtle5_Init)

/* func_ov085_02279250 (the create function his record at 0x02279420 names): a zeroed
 * block of 0x72c bytes from the auxiliary heap, constructed: the scene object base, the
 * class 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *Turtle5_Create(void)
{
    Turtle5 *turtle = (Turtle5 *) Heap_AllocAuxZeroed(sizeof(Turtle5));
    if (turtle == NULL) {
        return NULL;
    }
    u8 *object = turtle->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) t5_part(turtle, T5_PERSON) = T5_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) t5_part(turtle, T5_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) t5_part(turtle, T5_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) t5_part(turtle, T5_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) t5_part(turtle, T5_ANIM));
    SceneMover_Construct((SceneMover *) (void *) t5_part(turtle, T5_MOVER));
    SceneProbe_Construct(t5_part(turtle, T5_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) t5_part(turtle, T5_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) t5_part(turtle, T5_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) t5_part(turtle, T5_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) t5_part(turtle, T5_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) t5_part(turtle, T5_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) t5_part(turtle, T5_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) t5_part(turtle, T5_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) t5_part(turtle, T5_FOOTSTEPS));
    SceneMotion_Construct(t5_motion(turtle));
    SceneAction_Construct(t5_action(turtle));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) t5_part(turtle, T5_HEAP));
    *(const u8 **) (void *) object = data_ov085_022794f0;
    Turtle5Talk_Construct(&turtle->talk);
    return turtle;
}
CLEAN_AS(func_ov085_02279250, Turtle5_Create)
