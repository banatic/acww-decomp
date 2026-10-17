/* The gatekeeper of overlay 48 (gatekeeper.h): its object's vtable slots and questions. */
#include "gatekeeper.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "gatekeeper_talk_lines.h"
#include "main/event_queue.h"
#include "main/link_global.h"
#include "main/missing_npc1.h"
#include "main/player_actor_ops.h"
#include "main/player_records.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_face.h"
#include "main/scene_object.h"
#include "main/scene_query.h"
#include "main/scene_share.h"
#include "main/session.h"
#include "main/special_scene_object.h"
#include "main/talk_object.h"

static_assert(offsetof(Gatekeeper, participant) == 0x560 && offsetof(Gatekeeper, local) == 0x563, "Gatekeeper");
static_assert(offsetof(Gatekeeper, talk) == 0x658, "Gatekeeper");
static_assert(offsetof(Gatekeeper, countdown) == 0xe6e && sizeof(Gatekeeper) == 0xe74, "Gatekeeper");

/* The members of the scene object, by place (scene_object.h). */
#define GATEKEEPER_FACE 0x2ac
#define GATEKEEPER_ACTION 0x618

/* The field actor that is the player. */
#define GATEKEEPER_PLAYER_ACTOR 4
/* Whom an event is for when it is for this console's player (event_kinds.h). */
#define GATEKEEPER_THIS_PLAYER 4

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define GATEKEEPER_EVENT_0 0
#define GATEKEEPER_EVENT_1 1
#define GATEKEEPER_EVENT_ACT_STARTS 3
#define GATEKEEPER_EVENT_REFUSED 4
#define GATEKEEPER_EVENT_ACT_ENDED 8

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define GATEKEEPER_TALK_SLOT_RESET 2

/* The scenes it acts differently in (SceneQuery_Current). */
#define GATEKEEPER_SCENE_NO_SOUND 12
#define GATEKEEPER_SCENE_NO_CALL 0x2f

/* The second animation of its face, and of the missing character's, while both wait. */
#define GATEKEEPER_POSE_BA 0xba

/* The talk's topics GatekeeperTalk_SetTopic sets when it calls the player. */
#define GATEKEEPER_TOPIC_LINKED 9
#define GATEKEEPER_TOPIC_ALONE 0xa

/* The session. */
extern NetSession *data_020ccf94;

/* The vtable of its class. */
extern const u8 data_ov048_02264298[];
/* How far north the player is called from: the player is called once its z is at most this
 * point's (1.0). */
extern const Vec3 data_ov048_02263968;

/* The gatekeeper's state. */
extern void func_ov048_022635f4(Gatekeeper *self, int state);

static SceneAction *gatekeeper_action(Gatekeeper *self)
{
    return (SceneAction *) (void *) ((u8 *) self + GATEKEEPER_ACTION);
}

/* The talk scene's vtable slot `slot` called with no argument. */
static void gatekeeper_talk_slot(GatekeeperTalk *talk, int slot)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(GatekeeperTalk *))(uintptr_t) vtable[slot])(talk);
}

/* Whether the player may act on it: no action of its runs and it is not held. */
static int gatekeeper_may_act(Gatekeeper *self)
{
    if (SceneAction_IsBusy(gatekeeper_action(self))) {
        return 0;
    }
    return !SceneShare_IsHeld((u8 *) self);
}

/* The talk reset and given the player's object as its motion argument. */
static void gatekeeper_reset_talk(Gatekeeper *self)
{
    gatekeeper_talk_slot(&self->talk, GATEKEEPER_TALK_SLOT_RESET);
    SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, GATEKEEPER_PLAYER_ACTOR));
}

/* func_ov048_02260420 (slot 0x40): the destructor: its talk, then the base class's. */
Gatekeeper *Gatekeeper_Destruct(Gatekeeper *self)
{
    *(const u8 **) (void *) self = data_ov048_02264298;
    GatekeeperTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov048_02260420, Gatekeeper_Destruct)

/* func_ov048_02260448 (slot 0x44): destructed, then freed to the auxiliary heap. */
Gatekeeper *Gatekeeper_DestructDelete(Gatekeeper *self)
{
    *(const u8 **) (void *) self = data_ov048_02264298;
    GatekeeperTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov048_02260448, Gatekeeper_DestructDelete)

/* func_ov048_02260474: whether it waits with the missing character: its face's second animation
 * is 0xba, the missing character faces the player in the same pose, and its talk waits for the
 * player. */
int Gatekeeper_IsWaitingInPoseBA(Gatekeeper *self)
{
    if (SceneFace_AnimB((SceneFace *) (void *) ((u8 *) self + GATEKEEPER_FACE)) != GATEKEEPER_POSE_BA) {
        return 0;
    }
    if (!MissingNpc1_IsFacingPlayerAtBA()) {
        return 0;
    }
    return ((const TalkObject *) (const void *) self->talk.scene.talk)->state == TALK_OBJECT_WAITING;
}
CLEAN_AS(func_ov048_02260474, Gatekeeper_IsWaitingInPoseBA)

/* func_ov048_022604ac (slot 0x7c): the sound of an action's start as the base class has it,
 * except in scene 12, where it has none. */
int Gatekeeper_HasActionSound(Gatekeeper *self)
{
    if (SceneQuery_Current() == GATEKEEPER_SCENE_NO_SOUND) {
        return 0;
    }
    return SpecialSceneObject_HasActionSound((u8 *) self);
}
CLEAN_AS(func_ov048_022604ac, Gatekeeper_HasActionSound)

/* func_ov048_022604c8: the gatekeeper calls the player: when the session is not linked, the
 * scene is not 0x2f, no event runs, this system's slot of the session is taken and the player
 * stands at z 1.0 or less, its talk gets the topic 9 (linked by now) or 10 and an event of kind
 * 6 is asked for it. Whether it was.
 * QUIRK: the current player's record is fetched and not used.
 * REQUIRES: the player's field actor exists (PlayerActorOps_StartPosition is not NULL). */
int Gatekeeper_CallPlayer(Gatekeeper *self)
{
    NetSession *session = data_020ccf94;
    const Vec3 *position;

    if (Session_IsLinked(session)) {
        return 0;
    }
    if (SceneQuery_Current() == GATEKEEPER_SCENE_NO_CALL) {
        return 0;
    }
    if (EventQueue_HasCurrent()) {
        return 0;
    }
    if (!Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
        return 0;
    }
    position = PlayerActorOps_StartPosition(GATEKEEPER_PLAYER_ACTOR);
    if (position->z > data_ov048_02263968.z) {
        return 0;
    }
    PlayerRecords_Current();
    if (Session_IsLinked(session)) {
        GatekeeperTalk_SetTopic(&self->talk, GATEKEEPER_TOPIC_LINKED);
    } else {
        GatekeeperTalk_SetTopic(&self->talk, GATEKEEPER_TOPIC_ALONE);
    }
    EventQueue_RequestKind6(self, 0);
    return 1;
}
CLEAN_AS(func_ov048_022604c8, Gatekeeper_CallPlayer)

/* func_ov048_0226056c (slot 0x4c): told of an event, for `participant` (a session slot, or 4
 * for this console's player):
 * - 3 (the act starts): the participant kept; for another system, the shared slots (when the
 *   object is ours) become this system's as owner and the participant as holder, and state
 *   0x10; for this player, the same with this system as both, when the object is ours;
 * - 1: the talk reset, then state 2;
 * - 0: the participant kept; for another system than this one, both shared slots become the
 *   participant's and state 0x11; else, when the object is ours, both become this system's, the
 *   talk is reset and state 2;
 * - 8 (the act ended): for this player, while the link holds the scene this system as owner and
 *   no holder, state 4, else no owner and this system as holder, state 0xf; then the talk's
 *   topic 0xb;
 * - 4 (refused): when the object is held and ours and the shared slots read, for this player
 *   or for the system holding it, this system as owner and no holder, and state 1. */
void Gatekeeper_OnEvent(Gatekeeper *self, int code, int participant)
{
    u8 *object = (u8 *) self;

    switch (code) {
        case GATEKEEPER_EVENT_ACT_STARTS:
            self->participant = (u8) participant;
            if (participant != GATEKEEPER_THIS_PLAYER) {
                SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, participant);
                func_ov048_022635f4(self, GATEKEEPER_STATE_10);
            } else if (SceneShare_IsOurs(object)) {
                int slot = data_020ccf94->local_slot;
                SceneShare_SetSlotsIfOurs(object, 1, slot, slot);
                func_ov048_022635f4(self, GATEKEEPER_STATE_10);
            }
            break;
        case GATEKEEPER_EVENT_1:
            gatekeeper_reset_talk(self);
            func_ov048_022635f4(self, GATEKEEPER_STATE_2);
            break;
        case GATEKEEPER_EVENT_0:
            self->participant = (u8) participant;
            if (participant != GATEKEEPER_THIS_PLAYER && participant != data_020ccf94->local_slot) {
                SceneShare_SetSlotsIfOurs(object, 1, participant, participant);
                func_ov048_022635f4(self, GATEKEEPER_STATE_11);
            } else if (SceneShare_IsOurs(object)) {
                int slot = data_020ccf94->local_slot;
                SceneShare_SetSlotsIfOurs(object, 1, slot, slot);
                gatekeeper_reset_talk(self);
                func_ov048_022635f4(self, GATEKEEPER_STATE_2);
            }
            break;
        case GATEKEEPER_EVENT_ACT_ENDED:
            if (participant == GATEKEEPER_THIS_PLAYER) {
                if (LinkGlobal_HoldsScene()) {
                    SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
                    func_ov048_022635f4(self, GATEKEEPER_STATE_4);
                } else {
                    SceneShare_SetSlotsIfOurs(object, 1, SCENE_SHARE_NO_SLOT, data_020ccf94->local_slot);
                    func_ov048_022635f4(self, GATEKEEPER_STATE_F);
                }
            }
            GatekeeperTalk_SetTopic(&self->talk, 0xb);
            break;
        case GATEKEEPER_EVENT_REFUSED: {
            int owner = SCENE_SHARE_NO_SLOT;
            int holder = SCENE_SHARE_NO_SLOT;
            if (!SceneShare_IsHeld(object) || !SceneShare_IsOurs(object)) {
                break;
            }
            if (!SceneShare_ReadSlots(object, &owner, &holder)) {
                break;
            }
            if (participant == GATEKEEPER_THIS_PLAYER || participant == holder) {
                SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
                func_ov048_022635f4(self, GATEKEEPER_STATE_1);
            }
            break;
        }
        default:
            break;
    }
}
CLEAN_AS(func_ov048_0226056c, Gatekeeper_OnEvent)

/* func_ov048_02260714 (slot 0x58): agreed when it is not shared with a session, else as
 * Gatekeeper_MayAct. */
int Gatekeeper_Ask58(Gatekeeper *self)
{
    if (self->local) {
        return 1;
    }
    return gatekeeper_may_act(self);
}
CLEAN_AS(func_ov048_02260714, Gatekeeper_Ask58)

/* func_ov048_02260750 (slot 0x48): the player may act on it while no action of its runs and it
 * is not held. */
int Gatekeeper_MayAct(Gatekeeper *self)
{
    return gatekeeper_may_act(self);
}
CLEAN_AS(func_ov048_02260750, Gatekeeper_MayAct)
