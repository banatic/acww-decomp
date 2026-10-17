/* Overlay 72's character (gull.h): its object's vtable slots, its life and its states. */
#include "gull.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/item_1568_count.h"
#include "main/layered_model.h"
#include "main/main_random.h"
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
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"

static_assert(offsetof(Gull, angle) == 0x8e && offsetof(Gull, flags) == 0x4e8, "Gull");
static_assert(offsetof(Gull, state) == 0x654 && offsetof(Gull, talk) == 0x658, "Gull");
static_assert(offsetof(Gull, all_counted) == 0x718 && offsetof(Gull, act_frames) == 0x720, "Gull");
static_assert(sizeof(Gull) == 0x724, "Gull");

/* The members of the scene object, by place (scene_object.h). */
#define GULL_PERSON 0xea
#define GULL_MODEL 0xec
#define GULL_STANDARD_ANIMS 0x2a0
#define GULL_FACE 0x2ac
#define GULL_ANIM 0x334
#define GULL_MOVER 0x350
#define GULL_PROBE 0x3a8
#define GULL_VALUE_3AA 0x3aa
#define GULL_LOOK 0x3b0
#define GULL_TALK_STATE 0x418
#define GULL_EFFECTS 0x420
#define GULL_COLLIDER 0x49c
#define GULL_CARRIER 0x4cc
#define GULL_EMITTER 0x514
#define GULL_FOOTSTEPS 0x558
#define GULL_MOTION 0x564
#define GULL_ACTION 0x618
#define GULL_HEAP 0x640
#define GULL_NO_PERSON 0xfff1

/* The field actor that is the player. */
#define GULL_PLAYER 4

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define GULL_EVENT_0 0
#define GULL_EVENT_ACT_ENDED 8

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define GULL_TALK_SLOT_RESET 2

/* Its flag of the scene object: it is held (scene_action.h). */
#define GULL_HELD 2

/* Five of item 0x1568 counted. */
#define GULL_ALL_COUNTED 5

/* Its motions (scene_motion_request.h): standing, its acts, and GULL_UNMET's animation. */
#define GULL_MOTION_STAND 0
#define GULL_MOTION_PRIORITY 1
#define GULL_ACT_NONE 0
#define GULL_ACT_FIRST 0xc /* one of 0xc, 0xd and 0xe */
#define GULL_ACTS 3
#define GULL_UNMET_ANIMATION 0xef

/* GULL_IDLE's wait between acts (400 frames and up to 599 more) and an act's length. */
#define GULL_ACT_WAIT 400
#define GULL_ACT_WAIT_RANGE 600
#define GULL_ACT_FRAMES 0x7a

/* What Gull_CountDown answers when the act has two frames left: the act is stopped then. */
#define GULL_ACT_STOP_AT 2

/* Its look's requests (scene_look.h): kind 1 once it was met, 0 before. */
#define GULL_LOOK_AT 1
#define GULL_LOOK_AWAY 0

/* The count of item 0x1568 (item_1568_count.h). */
extern u8 data_021ebcd2[];
/* The word of a motion request, the range of a look request and its point (the origin). */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;

/* The vtable of its class and its base classes' (scene_object.h, special_scene_object.h). */
extern const u8 data_ov072_02279b08[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];

/* Its model's and its texture's file names. */
extern const char data_ov072_02279a0c[];
extern const char data_ov072_02279a54[];

static u8 *gull_at(Gull *self, int offset)
{
    return (u8 *) self + offset;
}

static SceneAction *gull_action(Gull *self)
{
    return (SceneAction *) (void *) gull_at(self, GULL_ACTION);
}

static SceneMotion *gull_motion(Gull *self)
{
    return (SceneMotion *) (void *) gull_at(self, GULL_MOTION);
}

static SceneLook *gull_look(Gull *self)
{
    return (SceneLook *) (void *) gull_at(self, GULL_LOOK);
}

/* Its look asked for, of `kind`. */
static void gull_look_request(Gull *self, u8 kind)
{
    SceneLook_Request(gull_look(self), kind, 0, 0, &data_021fbee8, GULL_PLAYER, data_020c814c, 1);
}

/* The turn to the one its talk names (by the yaw to it), or to where it faces without one,
 * and the talk. */
static void gull_turn_and_talk(Gull *self)
{
    int other = SceneBase_MotionArg(&self->talk.scene);
    int yaw = self->angle;

    if (other != 0) {
        yaw = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) other);
    }
    SceneAction_RequestTurnAndTalk(gull_action(self), 0, yaw, 0);
}

/* ---- The object */

/* func_ov072_02278a00 (slot 0x40): the destructor: its talk, then the base class's. */
Gull *Gull_Destruct(Gull *self)
{
    *(const u8 **) (void *) self = data_ov072_02279b08;
    GullTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov072_02278a00, Gull_Destruct)

/* func_ov072_02278a28 (slot 0x44): destructed, then freed to the auxiliary heap. */
Gull *Gull_DestructDelete(Gull *self)
{
    *(const u8 **) (void *) self = data_ov072_02279b08;
    GullTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov072_02278a28, Gull_DestructDelete)

/* func_ov072_02278a54 (slot 0x4c): told of event 0, the talk reset and given the player's
 * object as its motion argument, then GULL_TALK; told the act ended (8), GULL_IDLE once the
 * count has its mark, else GULL_UNMET. */
void Gull_OnEvent(Gull *self, int code)
{
    switch (code) {
        case GULL_EVENT_0: {
            const u32 *vtable = (const u32 *) (const void *) self->talk.scene.vtable;
            ((void (*)(GullTalk *))(uintptr_t) vtable[GULL_TALK_SLOT_RESET])(&self->talk);
            SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, GULL_PLAYER));
            Gull_SetState(self, GULL_TALK);
            break;
        }
        case GULL_EVENT_ACT_ENDED:
            if (Item1568Count_HasMark(data_021ebcd2) != 0) {
                Gull_SetState(self, GULL_IDLE);
            } else {
                Gull_SetState(self, GULL_UNMET);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov072_02278a54, Gull_OnEvent)

/* func_ov072_02278ab4 (slot 0x48): the player may act on it while no action of its runs. */
int Gull_MayAct(Gull *self)
{
    return SceneAction_IsBusy(gull_action(self)) == 0;
}
CLEAN_AS(func_ov072_02278ab4, Gull_MayAct)

/* func_ov072_022796b8 (slot 0x70): its model's file name, "npc_sp/model/seg.nsbmd". */
int Gull_ModelName(void)
{
    return (int) (uintptr_t) data_ov072_02279a0c;
}
CLEAN_AS(func_ov072_022796b8, Gull_ModelName)

/* func_ov072_022796c0 (slot 0x6c): its texture's file name, "npc_sp/model/seg_tex.nsbtx". */
int Gull_TextureName(void)
{
    return (int) (uintptr_t) data_ov072_02279a54;
}
CLEAN_AS(func_ov072_022796c0, Gull_TextureName)

/* func_ov072_022796c8 (slot 0x00): unless the base class refuses to start, GULL_IDLE when the
 * count has its mark (noting whether five were counted), else GULL_UNMET; and it is held.
 * Whether it started. */
int Gull_Start(Gull *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    if (Item1568Count_HasMark(data_021ebcd2) != 0) {
        if (Item1568Count_Get(data_021ebcd2) >= GULL_ALL_COUNTED) {
            self->all_counted = 1;
        }
        Gull_SetState(self, GULL_IDLE);
    } else {
        Gull_SetState(self, GULL_UNMET);
    }
    self->flags |= GULL_HELD;
    return 1;
}
CLEAN_AS(func_ov072_022796c8, Gull_Start)

/* func_ov072_0227972c (slot 0x04): unless the base class refuses, its scene is its talk, which
 * starts over with it as its owner. Whether it was set up. */
int Gull_Init(Gull *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    GullTalk_Begin(&self->talk, self);
    return 1;
}
CLEAN_AS(func_ov072_0227972c, Gull_Init)

/* func_ov072_0227975c (its record's create function, data_ov072_02279a3c): a zeroed block of
 * 0x724 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
Gull *Gull_Create(void)
{
    Gull *self = (Gull *) Heap_AllocAuxZeroed(sizeof(Gull));

    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) self);
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) gull_at(self, GULL_PERSON) = GULL_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) gull_at(self, GULL_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) gull_at(self, GULL_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) gull_at(self, GULL_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) gull_at(self, GULL_ANIM));
    SceneMover_Construct((SceneMover *) (void *) gull_at(self, GULL_MOVER));
    SceneProbe_Construct(gull_at(self, GULL_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) gull_at(self, GULL_VALUE_3AA));
    SceneLook_Construct(gull_look(self));
    SceneTalkState_Construct((SceneTalkState *) (void *) gull_at(self, GULL_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) gull_at(self, GULL_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) gull_at(self, GULL_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) gull_at(self, GULL_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) gull_at(self, GULL_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) gull_at(self, GULL_FOOTSTEPS));
    SceneMotion_Construct(gull_motion(self));
    SceneAction_Construct(gull_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) gull_at(self, GULL_HEAP));
    *(const u8 **) (void *) self = data_ov072_02279b08;
    GullTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_ov072_0227975c, Gull_Create)

/* ---- Its states */

/* func_ov072_02278fa4 (GULL_TALKED's run): nothing; agrees. */
int Gull_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov072_02278fa4, Gull_UpdateTalked)

/* func_ov072_02278fa8 (GULL_TALK's run): when an act was stopped first, the turn and the talk
 * now; once no action of its runs, its event finished and GULL_TALKED. Agrees always. */
int Gull_UpdateTalk(Gull *self)
{
    if (self->act_frames != 0) {
        gull_turn_and_talk(self);
        self->act_frames = 0;
    }
    if (SceneAction_IsBusy(gull_action(self)) == 0) {
        EventQueue_FinishObjectEvent(self);
        Gull_SetState(self, GULL_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov072_02278fa8, Gull_UpdateTalk)

/* func_ov072_02279010 (GULL_TALK's entry): no longer noted as all counted. Once the count has
 * its mark it turns to the one its talk names and talks, or while an act plays only stops the
 * act (act 0; GULL_TALK's run talks then); before the mark it talks where it lies. Agrees. */
int Gull_EnterTalk(Gull *self)
{
    self->all_counted = 0;
    if (Item1568Count_HasMark(data_021ebcd2) != 0) {
        if (self->act_frames == 0) {
            gull_turn_and_talk(self);
        } else {
            SceneMotion_RequestAct(gull_motion(self), GULL_MOTION_PRIORITY, GULL_ACT_NONE, data_020c80f8);
        }
    } else {
        SceneAction_RequestTalk(gull_action(self), 0, 0);
    }
    return 1;
}
CLEAN_AS(func_ov072_02279010, Gull_EnterTalk)

/* func_ov072_02279424 (GULL_IDLE's run): once five were counted, its act counted down: two
 * frames before its end the act is stopped, and on its last frame it stands; with no act
 * playing, its wait counted down, and at 0 one of the acts 0xc-0xe for 122 frames and a new
 * wait of 400-999 frames. Agrees always. */
int Gull_UpdateIdle(Gull *self)
{
    if (self->all_counted == 0) {
        return 1;
    }
    if (Gull_CountDown(self, &self->act_frames) == GULL_ACT_STOP_AT) {
        SceneMotion_RequestAct(gull_motion(self), GULL_MOTION_PRIORITY, GULL_ACT_NONE, data_020c80f8);
        return 1;
    }
    if (self->act_frames == 1) {
        SceneMotion_Request(gull_motion(self), GULL_MOTION_STAND, GULL_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        return 1;
    }
    if (Gull_CountDown(self, &self->act_wait) == 0) {
        unsigned int act = MainRandom_Below(GULL_ACTS);
        if (act < GULL_ACTS) {
            SceneMotion_RequestAct(gull_motion(self), GULL_MOTION_PRIORITY, GULL_ACT_FIRST + (int) act, data_020c80f8);
        }
        self->act_wait = GULL_ACT_WAIT;
        self->act_wait += (s32) MainRandom_Below(GULL_ACT_WAIT_RANGE);
        self->act_frames = GULL_ACT_FRAMES;
    }
    return 1;
}
CLEAN_AS(func_ov072_02279424, Gull_UpdateIdle)

/* func_ov072_02279518 (GULL_IDLE's entry): it stands and its look is asked for; once five were
 * counted, a wait of 400-999 frames to its first act. Agrees. */
int Gull_EnterIdle(Gull *self)
{
    SceneMotion_Request(gull_motion(self), GULL_MOTION_STAND, GULL_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    gull_look_request(self, GULL_LOOK_AT);
    if (self->all_counted != 0) {
        self->act_wait = GULL_ACT_WAIT;
        self->act_wait += (s32) MainRandom_Below(GULL_ACT_WAIT_RANGE);
    }
    return 1;
}
CLEAN_AS(func_ov072_02279518, Gull_EnterIdle)

/* func_ov072_022795a8 (GULL_UNMET's run): nothing; agrees. */
int Gull_UpdateUnmet(void)
{
    return 1;
}
CLEAN_AS(func_ov072_022795a8, Gull_UpdateUnmet)

/* func_ov072_022795ac (GULL_UNMET's entry): its look asked away, animation 0xef, and the same
 * animation as its first standard one. Agrees. */
int Gull_EnterUnmet(Gull *self)
{
    gull_look_request(self, GULL_LOOK_AWAY);
    SceneMotion_RequestAnimation(gull_motion(self), GULL_MOTION_PRIORITY, GULL_UNMET_ANIMATION, 1, data_020c80f8, 0);
    SceneStandardAnims_SetFirst((SceneStandardAnims *) (void *) gull_at(self, GULL_STANDARD_ANIMS), GULL_UNMET_ANIMATION);
    return 1;
}
CLEAN_AS(func_ov072_022795ac, Gull_EnterUnmet)

/* func_ov072_02279618: `counter` one less unless it is 0; what it is now. */
int Gull_CountDown(Gull *self, s32 *counter)
{
    (void) self;
    if (*counter != 0) {
        (*counter)--;
    }
    return *counter;
}
CLEAN_AS(func_ov072_02279618, Gull_CountDown)

/* func_ov072_02279628: state `state` entered when its entry agrees (or it has none).
 * REQUIRES: `state` is below 4 (the game's are). */
void Gull_SetState(Gull *self, int state)
{
    const GullStateRow *row = &data_ov072_02279bd8[state];
    int agreed = 1;

    if (row->enter.function != 0) {
        agreed = MemberPointer_CallInt(&row->enter, self);
    }
    if (agreed) {
        self->state = state;
    }
}
CLEAN_AS(func_ov072_02279628, Gull_SetState)

/* func_ov072_0227966c (slot 0x68, each frame): its state's run, when it has one, and what that
 * answers; else 0.
 * REQUIRES: its state is below 4. */
int Gull_Update(Gull *self)
{
    const GullStateRow *row = &data_ov072_02279bd8[self->state];

    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, self);
}
CLEAN_AS(func_ov072_0227966c, Gull_Update)
