/* The gatekeeper of overlay 48 (gatekeeper.h): its object's vtable slots and questions. */
#include "gatekeeper.h"

#include <stdint.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "gatekeeper_talk_lines.h"
#include "main/act_effects.h"
#include "main/block_021d27ac.h"
#include "main/block_021d27ac_parts.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/link_global.h"
#include "main/missing_npc1.h"
#include "main/paired_town.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_query.h"
#include "main/scene_share.h"
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/session.h"
#include "main/speaker_anim.h"
#include "main/special_scene_object.h"
#include "main/talk_object.h"
#include "main/town_name.h"

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
 * point's (16.0). */
extern const Vec3 data_ov048_02263968;

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
 * stands at z 16.0 or less, its talk gets the topic 9 (linked by now) or 10 and an event of kind
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
                Gatekeeper_SetState(self, GATEKEEPER_STATE_10);
            } else if (SceneShare_IsOurs(object)) {
                int slot = data_020ccf94->local_slot;
                SceneShare_SetSlotsIfOurs(object, 1, slot, slot);
                Gatekeeper_SetState(self, GATEKEEPER_STATE_10);
            }
            break;
        case GATEKEEPER_EVENT_1:
            gatekeeper_reset_talk(self);
            Gatekeeper_SetState(self, GATEKEEPER_STATE_2);
            break;
        case GATEKEEPER_EVENT_0:
            self->participant = (u8) participant;
            if (participant != GATEKEEPER_THIS_PLAYER && participant != data_020ccf94->local_slot) {
                SceneShare_SetSlotsIfOurs(object, 1, participant, participant);
                Gatekeeper_SetState(self, GATEKEEPER_STATE_11);
            } else if (SceneShare_IsOurs(object)) {
                int slot = data_020ccf94->local_slot;
                SceneShare_SetSlotsIfOurs(object, 1, slot, slot);
                gatekeeper_reset_talk(self);
                Gatekeeper_SetState(self, GATEKEEPER_STATE_2);
            }
            break;
        case GATEKEEPER_EVENT_ACT_ENDED:
            if (participant == GATEKEEPER_THIS_PLAYER) {
                if (LinkGlobal_HoldsScene()) {
                    SceneShare_SetSlotsIfOurs(object, 1, data_020ccf94->local_slot, SCENE_SHARE_NO_SLOT);
                    Gatekeeper_SetState(self, GATEKEEPER_STATE_4);
                } else {
                    SceneShare_SetSlotsIfOurs(object, 1, SCENE_SHARE_NO_SLOT, data_020ccf94->local_slot);
                    Gatekeeper_SetState(self, GATEKEEPER_STATE_F);
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
                Gatekeeper_SetState(self, GATEKEEPER_STATE_1);
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

/* ---- Its paired town, its files, its life */

/* This town (number and name, town_name.h). */
extern const u16 data_021dc7aa[];
/* The current player's flag set when its paired town has the pairing's flag 5. */
#define GATEKEEPER_FLAG_PAIRED_VISIT 0x36

/* func_ov048_02262ee8 (asked by main's activity_link_jobs.c before the scene's exit is taken):
 * when PairedTown_CurrentUnflaggedInLastWeek agrees, the current player's pairing
 * (paired_town.h) loses its flag 5 unless its town is set and is this town; then, when the
 * pairing has the flag 5, the current player's flag 0x36 is set. Whether it was. */
int Gatekeeper_CheckPairedTown(void)
{
    u8 *record = PlayerRecords_Current();
    u8 *pairing;

    if (!PairedTown_CurrentUnflaggedInLastWeek()) {
        return 0;
    }
    pairing = PlayerRecord_Field242C(record);
    int here = 0;
    if (TownName_IsSet((const u16 *) (const void *) PairedTown_Town(pairing))) {
        const u16 *town = (const u16 *) (const void *) PairedTown_Town(pairing);
        here = town[0] == data_021dc7aa[0] && memcmp(town + 1, data_021dc7aa + 1, 2 * TOWN_NAME_LENGTH) == 0;
    }
    if (!here) {
        PairedTown_ClearFlag5(PlayerRecord_Field242C(PlayerRecords_Current()));
    }
    if (!PairedTown_Flag5(pairing)) {
        return 0;
    }
    PlayerRecord_SetFlag(record, GATEKEEPER_FLAG_PAIRED_VISIT);
    return 1;
}
CLEAN_AS(func_ov048_02262ee8, Gatekeeper_CheckPairedTown)

/* Its model's and its texture's file names: "npc_sp/model/plc.nsbmd" and
 * "npc_sp/model/plc_tex.nsbtx" (the words at data_ov048_02263d28 and data_ov048_02263d24). */
extern const char *const data_ov048_02263d28;
extern const char *const data_ov048_02263d24;

/* func_ov048_02263684 (slot 0x70): its model's file name. */
unsigned int Gatekeeper_ModelName(void)
{
    return (unsigned int) (uintptr_t) data_ov048_02263d28;
}
CLEAN_AS(func_ov048_02263684, Gatekeeper_ModelName)

/* func_ov048_02263690 (slot 0x6c): its texture's file name. */
int Gatekeeper_TextureName(void)
{
    return (int) (uintptr_t) data_ov048_02263d24;
}
CLEAN_AS(func_ov048_02263690, Gatekeeper_TextureName)

/* The scenes it acts differently in (SceneQuery_Current). */
#define GATEKEEPER_SCENE_SHARED 0xb
#define GATEKEEPER_SCENE_C 0xc
#define GATEKEEPER_SCENE_ARRIVE 0xd
#define GATEKEEPER_SCENE_SERVED 0xe

/* The kinds of the block's part 0x20 (block_021d27ac_parts.h) set when the player left through
 * states 0xc and 0xd, and the topics of its talk after each. */
#define GATEKEEPER_PART20_KIND_C 1
#define GATEKEEPER_PART20_KIND_D 2
#define GATEKEEPER_TOPIC_BACK_C 6
#define GATEKEEPER_TOPIC_BACK_D 7

/* Its flag of the scene object: it is held (scene_action.h). */
#define GATEKEEPER_HELD 2

/* func_ov048_0226369c (slot 0x0c): unless the base class refuses to leave, in scenes 0xd and
 * 0xe the event queue's flag 1 is cleared. Whether it left. */
int Gatekeeper_Leave(Gatekeeper *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    if (SceneQuery_Current() == GATEKEEPER_SCENE_ARRIVE || SceneQuery_Current() == GATEKEEPER_SCENE_SERVED) {
        EventQueue_ClearFlag1();
    }
    return 1;
}
CLEAN_AS(func_ov048_0226369c, Gatekeeper_Leave)

/* func_ov048_022636c8 (slot 0x00): unless the base class refuses to start, it keeps its angle
 * as the one it started with, is held, and takes its first state:
 * - linked to a session in scene 0xb: 1 when the object is ours, else 0xf;
 * - back from a trip (the block's part 0x20 of kind 1 or 2): its talk's topic 6 or 7, state 0,
 *   facing and walking the part's angle, and the part's kind cleared;
 * - scene 0xd: the event queue's flag 1 set and state 9; scene 0xe: the same and state 0xb;
 * - else state 1.
 * Whether it started. */
int Gatekeeper_Start(Gatekeeper *self)
{
    Block021d27acPart20 *part;

    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    self->home_angle = self->angle;
    self->flags |= GATEKEEPER_HELD;
    if (Session_IsLinked(data_020ccf94) && SceneQuery_Current() == GATEKEEPER_SCENE_SHARED) {
        if (SceneShare_IsOurs((u8 *) self)) {
            Gatekeeper_SetState(self, GATEKEEPER_STATE_1);
        } else {
            Gatekeeper_SetState(self, GATEKEEPER_STATE_F);
        }
        return 1;
    }
    part = (Block021d27acPart20 *) Block021d27ac_Part20(Block021d27ac_Get());
    if (Block021d27acPart20_Kind(part) == GATEKEEPER_PART20_KIND_C ||
        Block021d27acPart20_Kind(part) == GATEKEEPER_PART20_KIND_D) {
        if (Block021d27acPart20_Kind(part) == GATEKEEPER_PART20_KIND_C) {
            GatekeeperTalk_SetTopic(&self->talk, GATEKEEPER_TOPIC_BACK_C);
        } else {
            GatekeeperTalk_SetTopic(&self->talk, GATEKEEPER_TOPIC_BACK_D);
        }
        Gatekeeper_SetState(self, GATEKEEPER_STATE_0);
        self->angle = (s16) Block021d27acPart20_Value(part);
        self->walk_angle = (s16) Block021d27acPart20_Value(part);
        Block021d27acPart20_ClearKind(part);
    } else if (SceneQuery_Current() == GATEKEEPER_SCENE_ARRIVE) {
        EventQueue_SetFlag1();
        Gatekeeper_SetState(self, GATEKEEPER_STATE_9);
    } else if (SceneQuery_Current() == GATEKEEPER_SCENE_SERVED) {
        EventQueue_SetFlag1();
        Gatekeeper_SetState(self, GATEKEEPER_STATE_B);
    } else {
        Gatekeeper_SetState(self, GATEKEEPER_STATE_1);
    }
    return 1;
}
CLEAN_AS(func_ov048_022636c8, Gatekeeper_Start)

/* The members of the scene object, by place (scene_object.h). */
#define GATEKEEPER_MODEL 0xec
#define GATEKEEPER_STANDARD_ANIMS 0x2a0
#define GATEKEEPER_ANIM 0x334
#define GATEKEEPER_MOVER 0x350
#define GATEKEEPER_PROBE 0x3a8
#define GATEKEEPER_VALUE_3AA 0x3aa
#define GATEKEEPER_LOOK 0x3b0
#define GATEKEEPER_TALK_STATE 0x418
#define GATEKEEPER_EFFECTS 0x420
#define GATEKEEPER_COLLIDER 0x49c
#define GATEKEEPER_CARRIER 0x4cc
#define GATEKEEPER_EMITTER 0x514
#define GATEKEEPER_FOOTSTEPS 0x558
#define GATEKEEPER_MOTION 0x564
#define GATEKEEPER_HEAP 0x640
#define GATEKEEPER_PERSON 0xea
#define GATEKEEPER_NO_PERSON 0xfff1

/* Its collider's size and its standard animations (scene_standard_anims.h). */
#define GATEKEEPER_COLLIDER_SIZE 0x100
#define GATEKEEPER_STANDARD_FIRST 0xd8
#define GATEKEEPER_STANDARD_SECOND 0xd9

static u8 *gatekeeper_at(Gatekeeper *self, int offset)
{
    return (u8 *) self + offset;
}

static SceneStandardAnims *gatekeeper_standard_anims(Gatekeeper *self)
{
    return (SceneStandardAnims *) (void *) gatekeeper_at(self, GATEKEEPER_STANDARD_ANIMS);
}

/* func_ov048_022637d4 (slot 0x04): unless the base class refuses, its scene is its talk (which
 * gets it as its owner), its collider's size 0x100 and its standard animations 0xd8 and 0xd9;
 * outside scene 0xb it is not shared, and in scene 0xc not solid. Whether it was set up. */
int Gatekeeper_Init(Gatekeeper *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    GatekeeperTalk_Start(&self->talk, self);
    SceneObject_SetColliderSize((u8 *) self, GATEKEEPER_COLLIDER_SIZE);
    SceneStandardAnims_SetSecond(gatekeeper_standard_anims(self), GATEKEEPER_STANDARD_SECOND);
    SceneStandardAnims_SetFirst(gatekeeper_standard_anims(self), GATEKEEPER_STANDARD_FIRST);
    if (SceneQuery_Current() != GATEKEEPER_SCENE_SHARED) {
        self->local = 1;
    }
    if (SceneQuery_Current() == GATEKEEPER_SCENE_C) {
        self->solid = 0;
    }
    return 1;
}
CLEAN_AS(func_ov048_022637d4, Gatekeeper_Init)

/* The vtables of its base classes (scene_object.h, special_scene_object.h). */
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];

/* func_ov048_0226384c (its record's create function, data_ov048_02264174): a zeroed block of
 * 0xe74 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
Gatekeeper *Gatekeeper_Create(void)
{
    Gatekeeper *self = (Gatekeeper *) Heap_AllocAuxZeroed(sizeof(Gatekeeper));

    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) self);
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) gatekeeper_at(self, GATEKEEPER_PERSON) = GATEKEEPER_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) gatekeeper_at(self, GATEKEEPER_MODEL));
    SceneStandardAnims_Init(gatekeeper_standard_anims(self));
    SceneFace_Construct((SceneFace *) (void *) gatekeeper_at(self, GATEKEEPER_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) gatekeeper_at(self, GATEKEEPER_ANIM));
    SceneMover_Construct((SceneMover *) (void *) gatekeeper_at(self, GATEKEEPER_MOVER));
    SceneProbe_Construct(gatekeeper_at(self, GATEKEEPER_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) gatekeeper_at(self, GATEKEEPER_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) gatekeeper_at(self, GATEKEEPER_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) gatekeeper_at(self, GATEKEEPER_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) gatekeeper_at(self, GATEKEEPER_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) gatekeeper_at(self, GATEKEEPER_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) gatekeeper_at(self, GATEKEEPER_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) gatekeeper_at(self, GATEKEEPER_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) gatekeeper_at(self, GATEKEEPER_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) gatekeeper_at(self, GATEKEEPER_MOTION));
    SceneAction_Construct(gatekeeper_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) gatekeeper_at(self, GATEKEEPER_HEAP));
    *(const u8 **) (void *) self = data_ov048_02264298;
    GatekeeperTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_ov048_0226384c, Gatekeeper_Create)
