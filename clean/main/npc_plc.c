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

/* Its state set (the state's entry run first; its answer other than 1 refuses it). */
extern void func_020c3dac(NpcPlc *self, int state);

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
            func_020c3dac(self, NPC_PLC_TALK);
            break;
        case NPC_PLC_EVENT_ACT_ENDED:
            func_020c3dac(self, NPC_PLC_TURN_BACK);
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
        func_020c3dac(self, NPC_PLC_IDLE);
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
        func_020c3dac(self, NPC_PLC_TALKED);
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
