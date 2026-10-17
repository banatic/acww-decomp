/* Overlay 46's character (astro.h): its object's vtable slots, its life and its states. */
#include "astro.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/calendar.h"
#include "main/camera_control.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/game_variables.h"
#include "main/layered_model.h"
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
#include "main/session_players.h"
#include "main/speaker_anim.h"
#include "main/special_scene_object.h"
#include "main/touch_pick_shapes.h"

static_assert(offsetof(Astro, joint16) == 0x478 && offsetof(Astro, flags) == 0x4e8, "Astro");
static_assert(offsetof(Astro, state) == 0x654 && offsetof(Astro, talk) == 0x658, "Astro");
static_assert(offsetof(Astro, countdown) == 0x738 && offsetof(Astro, effect) == 0x740, "Astro");
static_assert(sizeof(Astro) == 0x744, "Astro");

/* The members of the scene object, by place (scene_object.h). */
#define ASTRO_PERSON 0xea
#define ASTRO_MODEL 0xec
#define ASTRO_STANDARD_ANIMS 0x2a0
#define ASTRO_FACE 0x2ac
#define ASTRO_ANIM 0x334
#define ASTRO_MOVER 0x350
#define ASTRO_PROBE 0x3a8
#define ASTRO_VALUE_3AA 0x3aa
#define ASTRO_LOOK 0x3b0
#define ASTRO_TALK_STATE 0x418
#define ASTRO_EFFECTS 0x420
#define ASTRO_COLLIDER 0x49c
#define ASTRO_CARRIER 0x4cc
#define ASTRO_EMITTER 0x514
#define ASTRO_FOOTSTEPS 0x558
#define ASTRO_MOTION 0x564
#define ASTRO_ACTION 0x618
#define ASTRO_HEAP 0x640
#define ASTRO_NO_PERSON 0xfff1

/* The field actor that is the player. */
#define ASTRO_PLAYER 4

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define ASTRO_EVENT_0 0
#define ASTRO_EVENT_1 1
#define ASTRO_EVENT_ACT_ENDED 8

/* The talk scene's vtable slot that resets it (AstroTalk_Reset). */
#define ASTRO_TALK_SLOT_RESET 2

/* Its flag of the scene object: it is held (scene_action.h). */
#define ASTRO_HELD 2

/* The game variable tested with the session's link (game_variables.h). */
#define ASTRO_VARIABLE 0x4a

/* Where the player calls it from: within 1.0 (in x and z) of (16.5, -, 23.0), facing between
 * the angles 0x6000 and 0xa000, pressing A or touching an object of kind 0x16. */
#define ASTRO_CALL_X 0x10800
#define ASTRO_CALL_Z 0x17000
#define ASTRO_CALL_RANGE 0x1000
#define ASTRO_CALL_ANGLE_MIN 0x6000
#define ASTRO_CALL_ANGLE_MAX 0xa000
#define ASTRO_CALL_PICK_KIND 0x16

/* Its motions: standing, turning (scene_motion_request.h), and the animation of ASTRO_ANIMATE. */
#define ASTRO_MOTION_STAND 0
#define ASTRO_MOTION_TURN 3
#define ASTRO_MOTION_PRIORITY 1
#define ASTRO_ANIMATION 0xf0
#define ASTRO_ANIM_WORD 0x18

/* ASTRO_IDLE's frames, and the effect of ASTRO_ANIMATE. */
#define ASTRO_IDLE_FRAMES 0x78
#define ASTRO_EFFECT 0x3c
#define ASTRO_NO_EFFECT (-1)

/* Its look's requests (scene_look.h): kind 1 while it stands or talks, 0 while it animates. */
#define ASTRO_LOOK_AT 1
#define ASTRO_LOOK_AWAY 0

/* The pad (input.h): button A. */
#define ASTRO_PAD_A 1

/* The session; the pad; both set when the pen came down this frame. */
extern NetSession *data_020ccf94;
extern PadState data_021fbe40;
extern u8 data_021f6c34;
extern u8 data_021f6c38;
/* The word of a motion request, the range of a look request and its point (the origin). */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;

/* The vtable of its class and its base classes' (scene_object.h, special_scene_object.h). */
extern const u8 data_ov046_022620e0[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];

/* Its model's and its texture's file names. */
extern const char data_ov046_02261ff8[];
extern const char data_ov046_02262028[];

static u8 *astro_at(Astro *self, int offset)
{
    return (u8 *) self + offset;
}

static SceneAction *astro_action(Astro *self)
{
    return (SceneAction *) (void *) astro_at(self, ASTRO_ACTION);
}

static SceneMotion *astro_motion(Astro *self)
{
    return (SceneMotion *) (void *) astro_at(self, ASTRO_MOTION);
}

static SceneLook *astro_look(Astro *self)
{
    return (SceneLook *) (void *) astro_at(self, ASTRO_LOOK);
}

/* Its look asked for, of `kind`. */
static void astro_look_request(Astro *self, u8 kind)
{
    SceneLook_Request(astro_look(self), kind, 0, 0, &data_021fbee8, ASTRO_PLAYER, data_020c814c, 1);
}

/* ---- The object */

/* func_ov046_02260420 (slot 0x40): the destructor: its talk, then the base class's. */
Astro *Astro_Destruct(Astro *self)
{
    *(const u8 **) (void *) self = data_ov046_022620e0;
    AstroTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov046_02260420, Astro_Destruct)

/* func_ov046_02260448 (slot 0x44): destructed, then freed to the auxiliary heap. */
Astro *Astro_DestructDelete(Astro *self)
{
    *(const u8 **) (void *) self = data_ov046_022620e0;
    AstroTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov046_02260448, Astro_DestructDelete)

/* func_ov046_02260474: when the player calls it over (Astro_IsCalled), its talk's topic CALLED,
 * the camera's flag 0x1f5 set and an event of kind 6 asked for it. Whether it was called. */
int Astro_TakeCall(Astro *self)
{
    if (Astro_IsCalled(self) == 0) {
        return 0;
    }
    AstroTalk_SetTopic(&self->talk, ASTRO_TALK_TOPIC_CALLED);
    CameraControl_SetFlag1F5();
    EventQueue_RequestKind6(self, 0);
    return 1;
}
CLEAN_AS(func_ov046_02260474, Astro_TakeCall)

/* func_ov046_022604a8: whether the player calls it over: the player's actor exists, no action
 * of its runs, the player stands within 1.0 of (16.5, -, 23.0), faces between 0x6000 and 0xa000
 * and presses A (when the pen did not come down) or touches an object of kind 0x16 (when it
 * did). Without the actor, while an action runs or facing away, its talk's topic PENDING. */
int Astro_IsCalled(Astro *self)
{
    Actor *player = (Actor *) SessionPlayers_ActorOf(ASTRO_PLAYER);
    int pen = data_021f6c38 != 0 && data_021f6c34 != 0;
    Vec3 position;
    Vec3 point;
    u16 angle;

    if (player == NULL || SceneAction_IsBusy(astro_action(self))) {
        AstroTalk_SetTopic(&self->talk, ASTRO_TALK_TOPIC_PENDING);
        return 0;
    }
    position = player->position;
    point = player->position;
    point.x = ASTRO_CALL_X;
    point.z = ASTRO_CALL_Z;
    if (Vec_DistanceXZ(&position, &point) >= ASTRO_CALL_RANGE) {
        return 0;
    }
    angle = (u16) player->angle[1];
    if (angle < ASTRO_CALL_ANGLE_MIN || angle > ASTRO_CALL_ANGLE_MAX) {
        AstroTalk_SetTopic(&self->talk, ASTRO_TALK_TOPIC_PENDING);
        return 0;
    }
    if (!pen) {
        return (data_021fbe40.pressed & ASTRO_PAD_A) != 0;
    }
    {
        Vec3 touched;
        u32 kind;
        if (TouchPick_GetPick((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), &touched, &kind, NULL) != 0 &&
            kind == ASTRO_CALL_PICK_KIND) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov046_022604a8, Astro_IsCalled)

/* func_ov046_022605b0 (slot 0x4c): told of event 0 or 1, the talk reset and given the player's
 * object as its motion argument, then ASTRO_TALK; told the act ended (8), ASTRO_TURN_BACK. */
void Astro_OnEvent(Astro *self, int code)
{
    switch (code) {
        case ASTRO_EVENT_0:
        case ASTRO_EVENT_1: {
            const u32 *vtable = (const u32 *) (const void *) self->talk.scene.vtable;
            ((void (*)(AstroTalk *))(uintptr_t) vtable[ASTRO_TALK_SLOT_RESET])(&self->talk);
            SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, ASTRO_PLAYER));
            Astro_SetState(self, ASTRO_TALK);
            break;
        }
        case ASTRO_EVENT_ACT_ENDED:
            Astro_SetState(self, ASTRO_TURN_BACK);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov046_022605b0, Astro_OnEvent)

/* func_ov046_022605f8 (slot 0x58): agreed while no action of its runs. */
int Astro_MayTalk(Astro *self)
{
    return !SceneAction_IsBusy(astro_action(self));
}
CLEAN_AS(func_ov046_022605f8, Astro_MayTalk)

/* func_ov046_02260618 (slot 0x48): the player may act on it while no action of its runs and it
 * is not held. */
int Astro_MayAct(Astro *self)
{
    if (SceneAction_IsBusy(astro_action(self))) {
        return 0;
    }
    return !SceneShare_IsHeld((u8 *) self);
}
CLEAN_AS(func_ov046_02260618, Astro_MayAct)

/* func_ov046_02261a5c (slot 0x70): its model's file name, "npc_sp/model/ows.nsbmd". */
int Astro_ModelName(void)
{
    return (int) (uintptr_t) data_ov046_02261ff8;
}
CLEAN_AS(func_ov046_02261a5c, Astro_ModelName)

/* func_ov046_02261a64 (slot 0x6c): its texture's file name, "npc_sp/model/ows_tex.nsbtx". */
int Astro_TextureName(void)
{
    return (int) (uintptr_t) data_ov046_02262028;
}
CLEAN_AS(func_ov046_02261a64, Astro_TextureName)

/* Its effect ended, when it has one. */
static void astro_end_effect(Astro *self)
{
    if (self->effect != ASTRO_NO_EFFECT) {
        EffectSystem_EndHandle(self->effect);
        self->effect = ASTRO_NO_EFFECT;
    }
}

/* func_ov046_02261a6c (slot 0x0c): unless the base class refuses to leave, its effect ended.
 * Whether it left. */
int Astro_Leave(Astro *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    astro_end_effect(self);
    return 1;
}
CLEAN_AS(func_ov046_02261a6c, Astro_Leave)

/* func_ov046_02261aa0 (slot 0x00): unless the base class refuses to start, it keeps its angle
 * as the one it started with, its animation's word 0, is held, its talk's topic PENDING, and
 * it plays its animation (ASTRO_ANIMATE) in the morning or afternoon while the session is not
 * linked and game variable 0x4a is 0; else it stands (ASTRO_IDLE). Whether it started. */
int Astro_Start(Astro *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    self->home_angle = self->angle;
    self->anim_word = 0;
    self->flags |= ASTRO_HELD;
    AstroTalk_SetTopic(&self->talk, ASTRO_TALK_TOPIC_PENDING);
    if (Calendar_PartOfDay() == PART_OF_DAY_EVENING || Calendar_PartOfDay() == PART_OF_DAY_NIGHT ||
        Session_IsLinked(data_020ccf94) || *GameVariables_Slot(0, ASTRO_VARIABLE) != 0) {
        Astro_SetState(self, ASTRO_IDLE);
    } else {
        Astro_SetState(self, ASTRO_ANIMATE);
    }
    return 1;
}
CLEAN_AS(func_ov046_02261aa0, Astro_Start)

/* func_ov046_02261b30 (slot 0x04): unless the base class refuses, its scene is its talk (which
 * gets it as its owner), and it has no effect. Whether it was set up. */
int Astro_Init(Astro *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    AstroTalk_SetOwner(&self->talk, self);
    self->effect = ASTRO_NO_EFFECT;
    return 1;
}
CLEAN_AS(func_ov046_02261b30, Astro_Init)

/* func_ov046_02261b6c (its record's create function, data_ov046_02262010): a zeroed block of
 * 0x744 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
Astro *Astro_Create(void)
{
    Astro *self = (Astro *) Heap_AllocAuxZeroed(sizeof(Astro));

    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) self);
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) astro_at(self, ASTRO_PERSON) = ASTRO_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) astro_at(self, ASTRO_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) astro_at(self, ASTRO_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) astro_at(self, ASTRO_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) astro_at(self, ASTRO_ANIM));
    SceneMover_Construct((SceneMover *) (void *) astro_at(self, ASTRO_MOVER));
    SceneProbe_Construct(astro_at(self, ASTRO_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) astro_at(self, ASTRO_VALUE_3AA));
    SceneLook_Construct(astro_look(self));
    SceneTalkState_Construct((SceneTalkState *) (void *) astro_at(self, ASTRO_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) astro_at(self, ASTRO_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) astro_at(self, ASTRO_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) astro_at(self, ASTRO_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) astro_at(self, ASTRO_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) astro_at(self, ASTRO_FOOTSTEPS));
    SceneMotion_Construct(astro_motion(self));
    SceneAction_Construct(astro_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) astro_at(self, ASTRO_HEAP));
    *(const u8 **) (void *) self = data_ov046_022620e0;
    AstroTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_ov046_02261b6c, Astro_Create)

/* ---- Its states */

/* func_ov046_02261708 (ASTRO_TALKED's run): nothing; agrees. */
int Astro_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov046_02261708, Astro_UpdateTalked)

/* func_ov046_0226170c (ASTRO_TALK's run): once no action of its runs, its animation is
 * forgotten, its talk's topic PENDING, its event finished, and ASTRO_TALKED. Agrees always. */
int Astro_UpdateTalk(Astro *self)
{
    if (SceneAction_IsBusy(astro_action(self)) == 0) {
        self->was_animating = 0;
        AstroTalk_SetTopic(&self->talk, ASTRO_TALK_TOPIC_PENDING);
        EventQueue_FinishObjectEvent(self);
        Astro_SetState(self, ASTRO_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov046_0226170c, Astro_UpdateTalk)

/* func_ov046_02261750 (ASTRO_TALK's entry): it turns to the object its talk names (by the yaw
 * to it, 0 without one) and talks, its effect ended first; its look asked for. Agrees. */
int Astro_EnterTalk(Astro *self)
{
    int other = SceneBase_MotionArg(&self->talk.scene);
    int yaw = 0;

    if (other != 0) {
        yaw = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) other);
    }
    astro_end_effect(self);
    SceneAction_RequestTurnAndTalk(astro_action(self), 0, yaw, 0);
    astro_look_request(self, ASTRO_LOOK_AT);
    return 1;
}
CLEAN_AS(func_ov046_02261750, Astro_EnterTalk)

/* func_ov046_022617d4 (ASTRO_ANIMATE's run): unless the player calls it over, effect 0x3c at its
 * joint 16 with its angle: started when it has none, else moved there. Agrees always. */
int Astro_UpdateAnimate(Astro *self)
{
    if (Astro_TakeCall(self)) {
        return 1;
    }
    if (self->effect == ASTRO_NO_EFFECT) {
        self->effect = EffectSystem_StartKind(ASTRO_EFFECT, &self->joint16, &self->angle, NULL);
    } else {
        EffectSystem_MoveHandle(self->effect, &self->joint16, &self->angle, NULL);
    }
    return 1;
}
CLEAN_AS(func_ov046_022617d4, Astro_UpdateAnimate)

/* func_ov046_02261820 (ASTRO_ANIMATE's entry): animation 0xf0 asked for with its word, its look
 * asked away, and the animation noted. Agrees. */
int Astro_EnterAnimate(Astro *self)
{
    SceneMotion_RequestAnimation(astro_motion(self), ASTRO_MOTION_PRIORITY, ASTRO_ANIMATION, 0, self->anim_word, 0);
    astro_look_request(self, ASTRO_LOOK_AWAY);
    self->was_animating = 1;
    return 1;
}
CLEAN_AS(func_ov046_02261820, Astro_EnterAnimate)

/* func_ov046_02261884 (ASTRO_TURN_BACK's run): once its turn is done, ASTRO_IDLE. Agrees
 * always. */
int Astro_UpdateTurnBack(Astro *self)
{
    if (SceneMotion_Kind(astro_motion(self)) == ASTRO_MOTION_TURN && SceneMotion_IsDone(astro_motion(self)) != 0) {
        Astro_SetState(self, ASTRO_IDLE);
    }
    return 1;
}
CLEAN_AS(func_ov046_02261884, Astro_UpdateTurnBack)

/* func_ov046_022618b4 (ASTRO_TURN_BACK's entry): a turn to the angle it started with. Agrees. */
int Astro_EnterTurnBack(Astro *self)
{
    SceneMotion_Request(astro_motion(self), ASTRO_MOTION_TURN, ASTRO_MOTION_PRIORITY, 0, 0, 0, self->home_angle, 0, 0,
                        data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov046_022618b4, Astro_EnterTurnBack)

/* func_ov046_022618f0 (ASTRO_IDLE's run): unless the player calls it over, the session is
 * linked, game variable 0x4a is set or it is evening or night, its frames count down; at 0 its
 * animation's word 0x18 and ASTRO_ANIMATE. Agrees always. */
int Astro_UpdateIdle(Astro *self)
{
    if (Astro_TakeCall(self)) {
        return 1;
    }
    if (Session_IsLinked(data_020ccf94) || *GameVariables_Slot(0, ASTRO_VARIABLE) != 0 ||
        Calendar_PartOfDay() == PART_OF_DAY_EVENING || Calendar_PartOfDay() == PART_OF_DAY_NIGHT) {
        return 1;
    }
    if (Countdown_Tick16(&self->countdown) == 0) {
        self->anim_word = ASTRO_ANIM_WORD;
        Astro_SetState(self, ASTRO_ANIMATE);
    }
    return 1;
}
CLEAN_AS(func_ov046_022618f0, Astro_UpdateIdle)

/* func_ov046_02261960 (ASTRO_IDLE's entry): it stands, 120 frames to wait, and its look asked
 * for. Agrees. */
int Astro_EnterIdle(Astro *self)
{
    SceneMotion_Request(astro_motion(self), ASTRO_MOTION_STAND, ASTRO_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    self->countdown = ASTRO_IDLE_FRAMES;
    astro_look_request(self, ASTRO_LOOK_AT);
    return 1;
}
CLEAN_AS(func_ov046_02261960, Astro_EnterIdle)

/* func_ov046_022619cc: state `state` entered when its entry agrees (or it has none).
 * REQUIRES: `state` is below 5 (the game's are). */
void Astro_SetState(Astro *self, unsigned int state)
{
    const AstroStateRow *row = &data_ov046_0226248c[state];
    int agreed = 1;

    if (row->enter.function != 0) {
        agreed = MemberPointer_CallInt(&row->enter, self);
    }
    if (agreed) {
        self->state = (s32) state;
    }
}
CLEAN_AS(func_ov046_022619cc, Astro_SetState)

/* func_ov046_02261a10 (slot 0x68, each frame): its state's run, when it has one, and what that
 * answers; else 0.
 * REQUIRES: its state is below 5. */
int Astro_Update(Astro *self)
{
    const AstroStateRow *row = &data_ov046_0226248c[self->state];

    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, self);
}
CLEAN_AS(func_ov046_02261a10, Astro_Update)
