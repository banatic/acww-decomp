/* The special character with the model npc_sp/model/plc (npc_plc.h). */
#include "npc_plc.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "event_queue.h"
#include "scene_action.h"
#include "scene_motion_request.h"
#include "scene_object.h"
#include "special_scene_object.h"

static_assert(sizeof(SceneBase) == 0x80, "the scene base");
static_assert(offsetof(NpcPlcTalk, lines) == 0xb0 && offsetof(NpcPlcTalk, owner) == 0xb4, "NpcPlcTalk");
static_assert(sizeof(NpcPlcTalk) == 0xb8, "NpcPlcTalk");
static_assert(offsetof(NpcPlc, position) == 0x5c && offsetof(NpcPlc, angle) == 0x8e, "NpcPlc");
static_assert(offsetof(NpcPlc, state) == 0x654 && offsetof(NpcPlc, talk) == 0x658, "NpcPlc");
static_assert(offsetof(NpcPlc, home_angle) == 0x710 && sizeof(NpcPlc) == 0x714, "NpcPlc");

/* The members of the scene object, by place (scene_object.h). */
#define NPC_PLC_MOTION 0x564
#define NPC_PLC_ACTION 0x618

/* The kinds of motion it asks for (scene_motion_kinds.h). */
#define NPC_PLC_TURN 3

/* The field actor that is the player. */
#define NPC_PLC_PLAYER_ACTOR 4

/* How near another object must be to act on it (fx32). */
#define NPC_PLC_NEAR 0x2000

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define NPC_PLC_TALK_SLOT_RESET 2

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define NPC_PLC_EVENT_0 0
#define NPC_PLC_EVENT_ACT_ENDED 8

/* The talk's set of lines that is handled; NpcPlcTalk_SetOwner leaves none. */
#define NPC_PLC_LINES_0 0
#define NPC_PLC_LINES_NONE 1

/* The vtables of its class and of its talk's class. */
extern const u8 data_020e877c[];
extern const u8 data_020e86ec[];
/* "test", the archive of its line. */
extern const char data_020d315c[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;

static SceneMotion *npc_plc_motion(NpcPlc *self)
{
    return (SceneMotion *) (void *) ((u8 *) self + NPC_PLC_MOTION);
}

static SceneAction *npc_plc_action(NpcPlc *self)
{
    return (SceneAction *) (void *) ((u8 *) self + NPC_PLC_ACTION);
}

/* The talk scene's vtable slot `slot` called with no argument. */
static void npc_plc_talk_slot(NpcPlcTalk *talk, int slot)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(NpcPlcTalk *))(uintptr_t) vtable[slot])(talk);
}

/* ---- The object */

/* func_020c3a68 (slot 0x40): the destructor: its talk, then the base class's. */
NpcPlc *NpcPlc_Destruct(NpcPlc *self)
{
    *(const u8 **) (void *) self = data_020e877c;
    NpcPlcTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_020c3a68, NpcPlc_Destruct)

/* func_020c3a90 (slot 0x44): destructed, then freed to the auxiliary heap. */
NpcPlc *NpcPlc_DestructDelete(NpcPlc *self)
{
    *(const u8 **) (void *) self = data_020e877c;
    NpcPlcTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020c3a90, NpcPlc_DestructDelete)

/* func_020c3abc (slot 0x4c): told of an event. Code 0: its talk is reset and given the
 * player's object as its motion argument, and it talks (NPC_PLC_TALK). Code 8 (its act ended):
 * NPC_PLC_TURN_BACK. */
void NpcPlc_OnEvent(NpcPlc *self, int code)
{
    switch (code) {
        case NPC_PLC_EVENT_0:
            npc_plc_talk_slot(&self->talk, NPC_PLC_TALK_SLOT_RESET);
            SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, NPC_PLC_PLAYER_ACTOR));
            NpcPlc_SetState(self, NPC_PLC_TALK);
            break;
        case NPC_PLC_EVENT_ACT_ENDED:
            NpcPlc_SetState(self, NPC_PLC_TURN_BACK);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020c3abc, NpcPlc_OnEvent)

/* func_020c3b00 (slot 0x48): another object may act on it when within 0x2000 of it
 * (SceneObject_IsNear answering 1). */
int NpcPlc_MayAct(NpcPlc *self, u8 *other)
{
    return SceneObject_IsNear((u8 *) self, other, NPC_PLC_NEAR) == 1;
}
CLEAN_AS(func_020c3b00, NpcPlc_MayAct)

/* ---- Its talk scene */

/* func_020c3b1c (the talk's slot 0x14): a message handled by the set of lines (only set 0,
 * NpcPlcTalk_OnMessage0). */
void NpcPlcTalk_OnMessage(NpcPlcTalk *talk, void *message)
{
    if (talk->lines == NPC_PLC_LINES_0) {
        NpcPlcTalk_OnMessage0(talk, message);
    }
}
CLEAN_AS(func_020c3b1c, NpcPlcTalk_OnMessage)

/* func_020c3b8c: set 0 handles no message. */
void NpcPlcTalk_OnMessage0(NpcPlcTalk *talk, void *message)
{
    (void) talk;
    (void) message;
}
CLEAN_AS(func_020c3b8c, NpcPlcTalk_OnMessage0)

/* func_020c3b90 (the talk's slot 0x78): the line to say (NpcPlcTalk_LineBySet). */
void NpcPlcTalk_Line(NpcPlcTalk *talk, NpcPlcLine *line)
{
    NpcPlcTalk_LineBySet(talk, line);
}
CLEAN_AS(func_020c3b90, NpcPlcTalk_Line)

/* func_020c3b98: the line given by the set of lines (only set 0, NpcPlcTalk_Line0); any other
 * set leaves `line` as it was. */
void NpcPlcTalk_LineBySet(NpcPlcTalk *talk, NpcPlcLine *line)
{
    if (talk->lines == NPC_PLC_LINES_0) {
        NpcPlcTalk_Line0(talk, line);
    }
}
CLEAN_AS(func_020c3b98, NpcPlcTalk_LineBySet)

/* func_020c3c08: message 0 of the archive "test". */
void NpcPlcTalk_Line0(NpcPlcTalk *talk, NpcPlcLine *line)
{
    (void) talk;
    line->name = (u32) (uintptr_t) data_020d315c;
    line->message = 0;
}
CLEAN_AS(func_020c3c08, NpcPlcTalk_Line0)

/* func_020c3c18 */
void NpcPlcTalk_SetLines(NpcPlcTalk *talk, u32 lines)
{
    talk->lines = (s32) lines;
}
CLEAN_AS(func_020c3c18, NpcPlcTalk_SetLines)

/* func_020c3c20: the scene reset (its vtable slot 2), given its owner, and no set of lines. */
void NpcPlcTalk_SetOwner(NpcPlcTalk *talk, NpcPlc *owner)
{
    npc_plc_talk_slot(talk, NPC_PLC_TALK_SLOT_RESET);
    talk->owner = owner;
    talk->lines = NPC_PLC_LINES_NONE;
}
CLEAN_AS(func_020c3c20, NpcPlcTalk_SetOwner)

/* func_020c3c44 (the talk's slot 0x04): destructed, then freed (Heap_OperatorDeleteB). */
NpcPlcTalk *NpcPlcTalk_DestructDelete(NpcPlcTalk *talk)
{
    talk->scene.vtable = data_020e86ec;
    SceneBase_DestructBody(&talk->scene);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_020c3c44, NpcPlcTalk_DestructDelete)

/* func_020c3c64 (the talk's slot 0x00): the destructor. */
NpcPlcTalk *NpcPlcTalk_Destruct(NpcPlcTalk *talk)
{
    talk->scene.vtable = data_020e86ec;
    SceneBase_DestructBody(&talk->scene);
    return talk;
}
CLEAN_AS(func_020c3c64, NpcPlcTalk_Destruct)

/* func_020c3c7c: the constructor: a scene base given the class's vtable. */
NpcPlcTalk *NpcPlcTalk_Construct(NpcPlcTalk *talk)
{
    SceneBase_Construct(&talk->scene);
    talk->scene.vtable = data_020e86ec;
    return talk;
}
CLEAN_AS(func_020c3c7c, NpcPlcTalk_Construct)

/* ---- The states */

/* func_020c3c94: once its turn is done, NPC_PLC_IDLE. Always 1. */
int NpcPlc_UpdateTurnBack(NpcPlc *self)
{
    if (SceneMotion_Kind(npc_plc_motion(self)) == NPC_PLC_TURN && SceneMotion_IsDone(npc_plc_motion(self)) == 1) {
        NpcPlc_SetState(self, NPC_PLC_IDLE);
    }
    return 1;
}
CLEAN_AS(func_020c3c94, NpcPlc_UpdateTurnBack)

/* func_020c3cc4: a turn to the angle it started at. Always 1. */
int NpcPlc_EnterTurnBack(NpcPlc *self)
{
    SceneMotion_Request(npc_plc_motion(self), NPC_PLC_TURN, 1, 0, 0, 0, self->home_angle, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_020c3cc4, NpcPlc_EnterTurnBack)

/* func_020c3d00: nothing. */
int NpcPlc_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_020c3d00, NpcPlc_UpdateTalked)

/* func_020c3d04: once its action ends, its event finished (EventQueue_FinishObjectEvent) and
 * NPC_PLC_TALKED. Always 1. */
int NpcPlc_UpdateTalk(NpcPlc *self)
{
    if (!SceneAction_IsBusy(npc_plc_action(self))) {
        EventQueue_FinishObjectEvent(self);
        NpcPlc_SetState(self, NPC_PLC_TALKED);
    }
    return 1;
}
CLEAN_AS(func_020c3d04, NpcPlc_UpdateTalk)

/* func_020c3d30: the action that turns it to the object its talk names (its motion argument;
 * angle 0 without one) and talks, and its talk's line set 0. Always 1. */
int NpcPlc_EnterTalk(NpcPlc *self)
{
    int target = SceneBase_MotionArg(&self->talk.scene);
    int angle = 0;
    if (target != 0) {
        angle = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) target);
    }
    SceneAction_RequestTurnAndTalk(npc_plc_action(self), 0, angle, 0);
    NpcPlcTalk_SetLines(&self->talk, NPC_PLC_LINES_0);
    return 1;
}
CLEAN_AS(func_020c3d30, NpcPlc_EnterTalk)

/* func_020c3d74: nothing. */
int NpcPlc_UpdateIdle(void)
{
    return 1;
}
CLEAN_AS(func_020c3d74, NpcPlc_UpdateIdle)

/* ---- The state machine and the object's life */

#include "ov004/member_pointer.h"
#include "pool_link.h"
#include "scene_object_base.h"
#include "scene_object_members.h"
#include "scene_probe.h"
#include "scene_value_3aa.h"

/* The members of the scene object built by NpcPlc_Create, by place (scene_object.h). */
#define NPC_PLC_PERSON 0x0ea /* u16: the person code */
#define NPC_PLC_MODEL 0x0ec
#define NPC_PLC_STANDARD_ANIMS 0x2a0
#define NPC_PLC_FACE 0x2ac
#define NPC_PLC_ANIM 0x334
#define NPC_PLC_MOVER 0x350
#define NPC_PLC_PROBE 0x3a8
#define NPC_PLC_VALUE_3AA 0x3aa
#define NPC_PLC_LOOK 0x3b0
#define NPC_PLC_TALK_STATE 0x418
#define NPC_PLC_EFFECTS 0x420
#define NPC_PLC_COLLIDER 0x49c
#define NPC_PLC_CARRIER 0x4cc
#define NPC_PLC_EMITTER 0x514
#define NPC_PLC_FOOTSTEPS 0x558
#define NPC_PLC_HEAP 0x640

/* No person yet, and its person. */
#define NPC_PLC_NO_PERSON 0xfff1
#define NPC_PLC_PERSON_CODE 0xd000

/* The kind of motion of standing (scene_motion_kinds.h). */
#define NPC_PLC_STAND 0

/* Each state's entry and update (C++ pointers to member functions of the object; null for
 * none), filled at start-up. */
typedef struct NpcPlcStateFns {
    MemberPointer enter;
    MemberPointer update;
} NpcPlcStateFns;
extern NpcPlcStateFns data_021fbd90[NPC_PLC_STATES];

/* Its files' names: "npc_sp/model/plc.nsbmd" and "npc_sp/model/plc_tex.nsbtx". */
extern const u32 data_020d3164[2];
/* The vtable of its base class (special_scene_object.h). */
extern const u8 data_020da088[];

/* func_020c3d78: standing (priority 1). Always 1. */
int NpcPlc_EnterIdle(NpcPlc *self)
{
    SceneMotion_Request(npc_plc_motion(self), NPC_PLC_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_020c3d78, NpcPlc_EnterIdle)

/* func_020c3dac: the state's entry run (when it has one); when it answers 1 (or there is
 * none) the state is taken.
 * REQUIRES: `state` is one of the NPC_PLC_STATES. */
void NpcPlc_SetState(NpcPlc *self, int state)
{
    const MemberPointer *enter = &data_021fbd90[state].enter;
    int answer = 1;
    if (enter->function != 0) {
        answer = MemberPointer_CallInt(enter, self);
    }
    if (answer == 1) {
        self->state = state;
    }
}
CLEAN_AS(func_020c3dac, NpcPlc_SetState)

/* func_020c3df0 (slot 0x68): the state's update run (when it has one); its answer, else 0. */
int NpcPlc_Update(NpcPlc *self)
{
    const MemberPointer *update = &data_021fbd90[self->state].update;
    if (update->function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(update, self);
}
CLEAN_AS(func_020c3df0, NpcPlc_Update)

/* func_020c3e3c (slot 0x70): the model's file name. */
u32 NpcPlc_ModelName(void)
{
    return data_020d3164[0];
}
CLEAN_AS(func_020c3e3c, NpcPlc_ModelName)

/* func_020c3e48 (slot 0x6c): the texture's file name. */
u32 NpcPlc_TextureName(void)
{
    return data_020d3164[1];
}
CLEAN_AS(func_020c3e48, NpcPlc_TextureName)

/* func_020c3e54 (slot 0x0c): whether the base class let it leave. */
int NpcPlc_Leave(NpcPlc *self)
{
    return SpecialSceneObject_Leave(self) != 0;
}
CLEAN_AS(func_020c3e54, NpcPlc_Leave)

/* func_020c3e6c (slot 0x00): unless the base class refuses to start, NPC_PLC_IDLE, and the
 * angle it faces kept as the one to turn back to. Whether it started. */
int NpcPlc_Start(NpcPlc *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    NpcPlc_SetState(self, NPC_PLC_IDLE);
    self->home_angle = self->angle;
    return 1;
}
CLEAN_AS(func_020c3e6c, NpcPlc_Start)

/* func_020c3e98 (slot 0x04): unless the base class refuses, its person is 0xd000 and its
 * scene is its talk, which gets it as its owner. Whether it was set up. */
int NpcPlc_Init(NpcPlc *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    u16 person = NPC_PLC_PERSON_CODE;
    SceneObject_SetPerson((u8 *) self, &person);
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    NpcPlcTalk_SetOwner(&self->talk, self);
    return 1;
}
CLEAN_AS(func_020c3e98, NpcPlc_Init)

/* func_020c3ee8 (the create function of its record): a zeroed block of 0x714 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and
 * members in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link,
 * then the class's vtable and its talk. Null when there is no room. */
NpcPlc *NpcPlc_Create(void)
{
    u8 *object = (u8 *) Heap_AllocAuxZeroed(sizeof(NpcPlc));
    if (object == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) (object + NPC_PLC_PERSON) = NPC_PLC_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) (object + NPC_PLC_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) (object + NPC_PLC_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) (object + NPC_PLC_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) (object + NPC_PLC_ANIM));
    SceneMover_Construct((SceneMover *) (void *) (object + NPC_PLC_MOVER));
    SceneProbe_Construct(object + NPC_PLC_PROBE);
    SceneValue3aa_Clear((SceneValue3aa *) (void *) (object + NPC_PLC_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) (object + NPC_PLC_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) (object + NPC_PLC_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) (object + NPC_PLC_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) (object + NPC_PLC_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) (object + NPC_PLC_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) (object + NPC_PLC_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) (object + NPC_PLC_FOOTSTEPS));
    SceneMotion_Construct(npc_plc_motion((NpcPlc *) (void *) object));
    SceneAction_Construct(npc_plc_action((NpcPlc *) (void *) object));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) (object + NPC_PLC_HEAP));
    *(const u8 **) (void *) object = data_020e877c;
    NpcPlc *self = (NpcPlc *) (void *) object;
    NpcPlcTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_020c3ee8, NpcPlc_Create)
