/* The special character of overlay 87: its object, its states and its creation (acorn_npc.h). */
#include "acorn_npc.h"

#include <stdint.h>

#include "acorn_npc_talk.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "main/act_effects.h"
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

static_assert(sizeof(AcornNpcStep) == 0x10, "a state's functions");
static_assert(offsetof(AcornNpcTalk, owner) == 0xb0, "owner");
static_assert(sizeof(AcornNpcTalk) == 0xb4, "talk scene");
static_assert(offsetof(AcornNpc, state) == 0x654, "state");
static_assert(offsetof(AcornNpc, talk) == 0x658, "talk scene");
static_assert(sizeof(AcornNpc) == 0x70c, "the size AcornNpc_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define ACN_PERSON 0xea          /* u16: its person code */
#define ACN_MODEL 0xec           /* LayeredModel */
#define ACN_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define ACN_FACE 0x2ac           /* SceneFace */
#define ACN_ANIM 0x334           /* SpeakerAnim */
#define ACN_MOVER 0x350          /* SceneMover */
#define ACN_PROBE 0x3a8          /* the probe ahead */
#define ACN_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define ACN_LOOK 0x3b0           /* SceneLook */
#define ACN_TALK_STATE 0x418     /* SceneTalkState */
#define ACN_EFFECTS 0x420        /* ActEffects */
#define ACN_COLLIDER 0x49c       /* CollisionContacts */
#define ACN_CARRIER 0x4cc        /* FieldOwnedBody */
#define ACN_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define ACN_EMITTER 0x514        /* SoundEmitterObject */
#define ACN_FOOTSTEPS 0x558      /* Footsteps */
#define ACN_MOTION 0x564         /* SceneMotion */
#define ACN_ACTION 0x618         /* SceneAction */
#define ACN_HEAP 0x640           /* PoolLink */

#define ACN_NO_PERSON 0xfff1
#define ACN_HELD 2

/* The field actor of this console's player. */
#define ACN_PLAYER_ACTOR 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h): the player's act (the talk) and
 * the event's end. */
#define ACN_EVENT_ACT 0
#define ACN_EVENT_ENDED 8

/* The talk scene's vtable slot its talks call first. */
#define ACN_TALK_SLOT_08 0x08

/* What it starts with: animation 0x140 of its animation player (speed 1.0, slot 1), its model's
 * nodes 0x0c-0x0e moved to the model's part A, and the record of the winner of event 2 started
 * afresh when its day is past. */
#define ACN_START_ANIMATION 0x140
#define ACN_START_NODE_FIRST 0x0c
#define ACN_START_NODE_LAST 0x0e
#define ACN_WINNER_EVENT 2

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov087_022794ec[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Its states' functions (filled at start-up by __sinit_ov087_02279354). */
extern AcornNpcStep data_ov087_022795c0[ACORN_NPC_STATES];
/* Its model's and texture's file names: "npc_sp/model/dnk.nsbmd", "npc_sp/model/dnk_tex.nsbtx". */
extern const char data_ov087_02279408[];
extern const char data_ov087_02279438[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The record of an event's winner the villagers talk about. */
extern EventWinner data_021f3aa4;

static u8 *acn_part(AcornNpc *npc, u32 offset)
{
    return npc->base + offset;
}

static SceneAction *acn_action(AcornNpc *npc)
{
    return (SceneAction *) (void *) acn_part(npc, ACN_ACTION);
}

static SceneMotion *acn_motion(AcornNpc *npc)
{
    return (SceneMotion *) (void *) acn_part(npc, ACN_MOTION);
}

/* func_ov087_02278a00 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
AcornNpc *AcornNpc_Destroy(AcornNpc *npc)
{
    *(const u8 **) (void *) npc->base = data_ov087_022794ec;
    AcornNpcTalk_Destroy(&npc->talk);
    SpecialSceneObject_DestructBody(npc);
    return npc;
}
CLEAN_AS(func_ov087_02278a00, AcornNpc_Destroy)

/* func_ov087_02278a28 (vtable slot 0x44): the same, then the object freed. */
AcornNpc *AcornNpc_Delete(AcornNpc *npc)
{
    *(const u8 **) (void *) npc->base = data_ov087_022794ec;
    AcornNpcTalk_Destroy(&npc->talk);
    SpecialSceneObject_DestructBody(npc);
    Heap_FreeAux(npc);
    return npc;
}
CLEAN_AS(func_ov087_02278a28, AcornNpc_Delete)

/* func_ov087_02278a54 (vtable slot 0x4c, told of an event about it): code 0, the player's act:
 * its talk scene told through its slot 0x08, the talk's partner this console's player's
 * object, and it talks (state 1); code 8, the event ended: it stands (state 0). The base class
 * is not told. */
void AcornNpc_OnEvent(AcornNpc *npc, int code)
{
    switch (code) {
        case ACN_EVENT_ACT: {
            u32 vtable = *(const u32 *) (const void *) &npc->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + ACN_TALK_SLOT_08);
            ((void (*)(AcornNpcTalk *))(uintptr_t) slot)(&npc->talk);
            SceneBase_SetMotionArg(&npc->talk.base, SceneObject_ActorObject(npc->base, ACN_PLAYER_ACTOR));
            AcornNpc_SetState(npc, ACORN_NPC_TALKING);
            break;
        }
        case ACN_EVENT_ENDED:
            AcornNpc_SetState(npc, ACORN_NPC_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov087_02278a54, AcornNpc_OnEvent)

/* func_ov087_02278a98 (vtable slot 0x48): whether the player may talk to it: its action is
 * idle. */
int AcornNpc_MayAct(AcornNpc *npc)
{
    return SceneAction_IsBusy(acn_action(npc)) == 0;
}
CLEAN_AS(func_ov087_02278a98, AcornNpc_MayAct)

/* func_ov087_0227900c (state 0's update): nothing. 1. */
int AcornNpc_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov087_0227900c, AcornNpc_UpdateStand)

/* func_ov087_02279010 (state 1's update): once its action is idle, the object's event ends and
 * state 2 follows. 1. */
int AcornNpc_UpdateTalk(AcornNpc *npc)
{
    if (SceneAction_IsBusy(acn_action(npc)) == 0) {
        EventQueue_FinishObjectEvent(npc);
        AcornNpc_SetState(npc, ACORN_NPC_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov087_02279010, AcornNpc_UpdateTalk)

/* func_ov087_0227903c (state 1's entry): it turns to the talk's partner (to angle 0 without
 * one) and talks. 1. */
int AcornNpc_EnterTalk(AcornNpc *npc)
{
    int partner = SceneBase_MotionArg(&npc->talk.base);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(npc->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(acn_action(npc), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov087_0227903c, AcornNpc_EnterTalk)

/* func_ov087_02279074 (state 2's update): nothing. 1. */
int AcornNpc_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov087_02279074, AcornNpc_UpdateTalked)

/* func_ov087_02279078 (state 0's entry): its motion of kind 0 asked for (priority 1). 1. */
int AcornNpc_EnterStand(AcornNpc *npc)
{
    SceneMotion_Request(acn_motion(npc), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov087_02279078, AcornNpc_EnterStand)

/* func_ov087_022790ac: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void AcornNpc_SetState(AcornNpc *npc, int state)
{
    const AcornNpcStep *step = &data_ov087_022795c0[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, npc);
    }
    if (taken != 0) {
        npc->state = state;
    }
}
CLEAN_AS(func_ov087_022790ac, AcornNpc_SetState)

/* func_ov087_022790f0 (vtable slot 0x68, each frame): its state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: its state is 0 to 2. */
int AcornNpc_Update(AcornNpc *npc)
{
    const AcornNpcStep *step = &data_ov087_022795c0[npc->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, npc);
}
CLEAN_AS(func_ov087_022790f0, AcornNpc_Update)

/* func_ov087_0227913c (vtable slot 0x70): its model's file name, "npc_sp/model/dnk.nsbmd". */
int AcornNpc_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov087_02279408;
}
CLEAN_AS(func_ov087_0227913c, AcornNpc_ModelName)

/* func_ov087_02279144 (vtable slot 0x6c): its texture's file name,
 * "npc_sp/model/dnk_tex.nsbtx". */
int AcornNpc_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov087_02279438;
}
CLEAN_AS(func_ov087_02279144, AcornNpc_TextureName)

/* func_ov087_0227914c (vtable slot 0x00, its start): unless the special character refuses to
 * start, it stands (state 0), its animation player plays animation 0x140 (speed 1.0, slot 1),
 * its model's nodes 0x0c-0x0e go to its part A, it is held (flag 2 at 0x4e8) and the record
 * data_021f3aa4 is started afresh for event 2 when its day is past. Whether it started. */
int AcornNpc_Start(AcornNpc *npc)
{
    if (SpecialSceneObject_Start(npc) == 0) {
        return 0;
    }
    AcornNpc_SetState(npc, ACORN_NPC_STAND);
    SpeakerAnim_Play((SpeakerAnim *) (void *) acn_part(npc, ACN_ANIM), npc->base, ACN_START_ANIMATION, 0, 0, 0x1000, 0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) acn_part(npc, ACN_MODEL), ACN_START_NODE_FIRST, ACN_START_NODE_LAST);
    *(u32 *) (void *) acn_part(npc, ACN_HELD_FLAGS) |= ACN_HELD;
    EventWinner_ExpireForEvent(&data_021f3aa4, ACN_WINNER_EVENT);
    return 1;
}
CLEAN_AS(func_ov087_0227914c, AcornNpc_Start)

/* func_ov087_022791bc (vtable slot 0x04, its set-up): unless the special character refuses,
 * its talk scene becomes its scene and gets it as its owner. Whether it was set up. */
int AcornNpc_Init(AcornNpc *npc)
{
    if (SpecialSceneObject_Init(npc) == 0) {
        return 0;
    }
    SceneObject_SetScene(npc->base, &npc->talk.base);
    AcornNpcTalk_Begin(&npc->talk, npc);
    return 1;
}
CLEAN_AS(func_ov087_022791bc, AcornNpc_Init)

/* func_ov087_022791ec (the create function its record at 0x02279420 names): a zeroed block of
 * 0x70c bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *AcornNpc_Create(void)
{
    AcornNpc *npc = (AcornNpc *) Heap_AllocAuxZeroed(sizeof(AcornNpc));
    if (npc == NULL) {
        return NULL;
    }
    u8 *object = npc->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) acn_part(npc, ACN_PERSON) = ACN_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) acn_part(npc, ACN_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) acn_part(npc, ACN_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) acn_part(npc, ACN_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) acn_part(npc, ACN_ANIM));
    SceneMover_Construct((SceneMover *) (void *) acn_part(npc, ACN_MOVER));
    SceneProbe_Construct(acn_part(npc, ACN_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) acn_part(npc, ACN_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) acn_part(npc, ACN_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) acn_part(npc, ACN_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) acn_part(npc, ACN_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) acn_part(npc, ACN_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) acn_part(npc, ACN_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) acn_part(npc, ACN_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) acn_part(npc, ACN_FOOTSTEPS));
    SceneMotion_Construct(acn_motion(npc));
    SceneAction_Construct(acn_action(npc));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) acn_part(npc, ACN_HEAP));
    *(const u8 **) (void *) object = data_ov087_022794ec;
    AcornNpcTalk_Construct(&npc->talk);
    return npc;
}
CLEAN_AS(func_ov087_022791ec, AcornNpc_Create)
