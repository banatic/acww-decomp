/* The camel of overlay 78 (camel.h): her object's vtable slots, her life, her states and how
 * she moves. */
#include "camel.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/block_021d27ac.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
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
#include "main/town_spot.h"
#include "main/town_tile.h"

static_assert(offsetof(Camel, position) == 0x5c && offsetof(Camel, angle) == 0x8e, "Camel");
static_assert(offsetof(Camel, walk_angle) == 0x94 && offsetof(Camel, speed) == 0x98 && offsetof(Camel, countdown) == 0x651,
              "Camel");
static_assert(offsetof(Camel, state) == 0x654 && offsetof(Camel, talk) == 0x658, "Camel");
static_assert(sizeof(Camel) == 0x714, "Camel");

/* The members of the scene object, by place (scene_object.h). */
#define CAMEL_PERSON 0xea
#define CAMEL_MODEL 0xec
#define CAMEL_STANDARD_ANIMS 0x2a0
#define CAMEL_FACE 0x2ac
#define CAMEL_ANIM 0x334
#define CAMEL_MOVER 0x350
#define CAMEL_PROBE 0x3a8
#define CAMEL_VALUE_3AA 0x3aa
#define CAMEL_LOOK 0x3b0
#define CAMEL_TALK_STATE 0x418
#define CAMEL_EFFECTS 0x420
#define CAMEL_COLLIDER 0x49c
#define CAMEL_CARRIER 0x4cc
#define CAMEL_EMITTER 0x514
#define CAMEL_FOOTSTEPS 0x558
#define CAMEL_MOTION 0x564
#define CAMEL_ACTION 0x618
#define CAMEL_HEAP 0x640
#define CAMEL_NO_PERSON 0xfff1

/* The field actor that is the player. */
#define CAMEL_PLAYER 4

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define CAMEL_EVENT_0 0
#define CAMEL_EVENT_1 1
#define CAMEL_EVENT_ACT_STARTS 3
#define CAMEL_EVENT_ACT_ENDED 8

/* The talk scene's vtable slot that resets it (CamelTalk_Reset). */
#define CAMEL_TALK_SLOT_RESET 2

/* Its motions (scene_motion_request.h): standing, going to a point (kind 1, or 2 one time in
 * four) and turning to one (kind 4). */
#define CAMEL_MOTION_STAND 0
#define CAMEL_MOTION_GO 1
#define CAMEL_MOTION_GO_2 2
#define CAMEL_MOTION_TURN 4
#define CAMEL_MOTION_PRIORITY 1
#define CAMEL_GO_2_ODDS 4
#define CAMEL_GO_FRAMES 100
#define CAMEL_TURN_FRAMES 80

/* CAMEL_WANDER picks a new point one frame in eight (Random_Next's low three bits 0), and stands
 * when its pair at 0x3aa grades 2 (scene_value_3aa.h). */
#define CAMEL_PICK_MASK 7
#define CAMEL_VALUE_3AA_STAND 2

/* The random points: 12.0 away, six tries. */
#define CAMEL_POINT_DISTANCE 0xc000
#define CAMEL_POINT_TRIES 6

/* The probe's bits (scene_probe.h): the point to +x blocked, to -x, both. */
#define CAMEL_PROBE_RIGHT 1
#define CAMEL_PROBE_LEFT 2
#define CAMEL_PROBE_BOTH 3

/* What SceneProbe_IsBlocked answers for a blocked point. */
#define CAMEL_BLOCKED 1

/* The box around the camera's point it is near in: 16.0 either way in x, 26.0 behind and 10.0
 * ahead in z. */
#define CAMEL_NEAR_X 0x10000
#define CAMEL_NEAR_Z_BEHIND 0x1a000
#define CAMEL_NEAR_Z_AHEAD 0xa000

/* Its look's request (scene_look.h). */
#define CAMEL_LOOK_AT 1

/* The word of a motion request, the range of a look request and its point (the origin). */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The first user's random numbers; the sines and cosines (NitroSDK's FX_SinCosTable_). */
extern Random data_021cb5a0;
extern const fx16 FX_SinCosTable_[4096 * 2];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The camera, while it exists, and its point. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
/* The speed scale of the villagers' animation players (special_scene_object.h). */
extern s32 data_020c8120;

/* The points beside it it steps aside to (0.5 to +x or -x, 1.0 ahead), filled by its static
 * initialiser. */
extern Vec3 data_ov078_02279c30;
extern Vec3 data_ov078_02279c3c;

/* The vtable of its class and its base classes' (scene_object.h, special_scene_object.h). */
extern const u8 data_ov078_02279b2c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];

/* Its model's and its texture's file names. */
extern const char data_ov078_02279a48[];
extern const char data_ov078_02279a78[];

static u8 *camel_at(Camel *self, int offset)
{
    return (u8 *) self + offset;
}

static SceneAction *camel_action(Camel *self)
{
    return (SceneAction *) (void *) camel_at(self, CAMEL_ACTION);
}

static SceneMotion *camel_motion(Camel *self)
{
    return (SceneMotion *) (void *) camel_at(self, CAMEL_MOTION);
}

static SceneMover *camel_mover(Camel *self)
{
    return (SceneMover *) (void *) camel_at(self, CAMEL_MOVER);
}

static Footsteps *camel_footsteps(Camel *self)
{
    return (Footsteps *) (void *) camel_at(self, CAMEL_FOOTSTEPS);
}

/* It stands. */
static void camel_stand(Camel *self)
{
    SceneMotion_Request(camel_motion(self), CAMEL_MOTION_STAND, CAMEL_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
}

/* Whether `point` is within a quarter turn of where it faces. */
static int camel_faces(Camel *self, const Vec3 *point)
{
    int yaw = Vec_YawTo(&self->position, point);
    return SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle));
}

/* ---- The object */

/* func_ov078_02278a00 (slot 0x40): the destructor: its talk, then the base class's. */
Camel *Camel_Destruct(Camel *self)
{
    *(const u8 **) (void *) self = data_ov078_02279b2c;
    CamelTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov078_02278a00, Camel_Destruct)

/* func_ov078_02278a28 (slot 0x44): destructed, then freed to the auxiliary heap. */
Camel *Camel_DestructDelete(Camel *self)
{
    *(const u8 **) (void *) self = data_ov078_02279b2c;
    CamelTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov078_02278a28, Camel_DestructDelete)

/* Her talk reset (its vtable slot 0x08) and given the player's object as its motion argument. */
static void camel_set_up_talk(Camel *self)
{
    const u32 *vtable = (const u32 *) (const void *) self->talk.scene.vtable;
    ((void (*)(CamelTalk *))(uintptr_t) vtable[CAMEL_TALK_SLOT_RESET])(&self->talk);
    SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, CAMEL_PLAYER));
}

/* func_ov078_02278a54 (slot 0x4c): told of event 0, CAMEL_FINISH; told of event 1, her talk set
 * up, then CAMEL_FINISH; told the act starts (3), her talk set up, then CAMEL_TALK; told the act
 * ended (8), CAMEL_WANDER. */
void Camel_OnEvent(Camel *self, unsigned int code)
{
    switch (code) {
        case CAMEL_EVENT_0:
            Camel_SetState(self, CAMEL_FINISH);
            break;
        case CAMEL_EVENT_1:
            camel_set_up_talk(self);
            Camel_SetState(self, CAMEL_FINISH);
            break;
        case CAMEL_EVENT_ACT_STARTS:
            camel_set_up_talk(self);
            Camel_SetState(self, CAMEL_TALK);
            break;
        case CAMEL_EVENT_ACT_ENDED:
            Camel_SetState(self, CAMEL_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov078_02278a54, Camel_OnEvent)

/* func_ov078_02278ae0 (slot 0x48): the player may act on it while no action of its runs. */
int Camel_MayAct(Camel *self)
{
    return SceneAction_IsBusy(camel_action(self)) == 0;
}
CLEAN_AS(func_ov078_02278ae0, Camel_MayAct)

/* func_ov078_02279700 (slot 0x70): its model's file name, "npc_sp/model/cml.nsbmd". */
int Camel_ModelName(void)
{
    return (int) (uintptr_t) data_ov078_02279a48;
}
CLEAN_AS(func_ov078_02279700, Camel_ModelName)

/* func_ov078_02279708 (slot 0x6c): its texture's file name, "npc_sp/model/cml_tex.nsbtx". */
int Camel_TextureName(void)
{
    return (int) (uintptr_t) data_ov078_02279a78;
}
CLEAN_AS(func_ov078_02279708, Camel_TextureName)

/* func_ov078_02279738 (slot 0x00): unless the base class refuses to start, CAMEL_STAND. Whether
 * it started. */
int Camel_Start(Camel *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    Camel_SetState(self, CAMEL_STAND);
    return 1;
}
CLEAN_AS(func_ov078_02279738, Camel_Start)

/* func_ov078_02279710 (slot 0x0c): unless the base class refuses to leave, where it stands kept
 * as the spot of part 0x04 of the object at data_021d27ac (town_spot.h). Whether it left. */
int Camel_Leave(Camel *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    TownSpot_Set((TownSpot *) (void *) Block021d27ac_Part04(Block021d27ac_Get()), (u32) self->position.x,
                 (u32) self->position.z);
    return 1;
}
CLEAN_AS(func_ov078_02279710, Camel_Leave)

/* func_ov078_02279758 (slot 0x04): unless the base class refuses, its scene is its talk, which
 * starts over with it as its owner. Whether it was set up. */
int Camel_Init(Camel *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    CamelTalk_Begin(&self->talk, self);
    return 1;
}
CLEAN_AS(func_ov078_02279758, Camel_Init)

/* func_ov078_02279788 (slot 0xa8): the speed scale of its animation player: the villagers'
 * (data_020c8120), not the special characters' slower one. */
int Camel_AnimSpeed(void)
{
    return data_020c8120;
}
CLEAN_AS(func_ov078_02279788, Camel_AnimSpeed)

/* func_ov078_02279794 (its record's create function, data_ov078_02279a60): a zeroed block of
 * 0x714 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
Camel *Camel_Create(void)
{
    Camel *self = (Camel *) Heap_AllocAuxZeroed(sizeof(Camel));

    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) self);
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) camel_at(self, CAMEL_PERSON) = CAMEL_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) camel_at(self, CAMEL_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) camel_at(self, CAMEL_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) camel_at(self, CAMEL_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) camel_at(self, CAMEL_ANIM));
    SceneMover_Construct(camel_mover(self));
    SceneProbe_Construct(camel_at(self, CAMEL_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) camel_at(self, CAMEL_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) camel_at(self, CAMEL_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) camel_at(self, CAMEL_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) camel_at(self, CAMEL_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) camel_at(self, CAMEL_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) camel_at(self, CAMEL_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) camel_at(self, CAMEL_EMITTER));
    Footsteps_Construct(camel_footsteps(self));
    SceneMotion_Construct(camel_motion(self));
    SceneAction_Construct(camel_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) camel_at(self, CAMEL_HEAP));
    *(const u8 **) (void *) self = data_ov078_02279b2c;
    CamelTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_ov078_02279794, Camel_Create)

/* ---- Its states */

/* func_ov078_02279048 (CAMEL_TALK's run): nothing; agrees. */
int Camel_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov078_02279048, Camel_UpdateTalk)

/* func_ov078_0227904c (CAMEL_TALK's entry): it turns to the one its talk names (by the yaw to
 * it), or to where it faces without one, and talks. Agrees. */
int Camel_EnterTalk(Camel *self)
{
    int other = SceneBase_MotionArg(&self->talk.scene);
    int yaw = self->angle;

    if (other != 0) {
        yaw = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) other);
    }
    SceneAction_RequestTurnAndTalk(camel_action(self), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov078_0227904c, Camel_EnterTalk)

/* func_ov078_0227963c (CAMEL_DONE's run): nothing; agrees. */
int Camel_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov078_0227963c, Camel_UpdateDone)

/* func_ov078_02279640 (CAMEL_FINISH's run): once no action of hers runs, her event finished and
 * CAMEL_DONE. Agrees always. */
int Camel_UpdateFinish(Camel *self)
{
    if (SceneAction_IsBusy(camel_action(self)) == 0) {
        EventQueue_FinishObjectEvent(self);
        Camel_SetState(self, CAMEL_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov078_02279640, Camel_UpdateFinish)

/* func_ov078_0227966c (CAMEL_FINISH's entry): nothing; agrees. */
int Camel_EnterFinish(void)
{
    return 1;
}
CLEAN_AS(func_ov078_0227966c, Camel_EnterFinish)

/* func_ov078_02279088 (CAMEL_STAND's run): once the camera's point is near, CAMEL_WANDER. Agrees
 * always. */
int Camel_UpdateStand(Camel *self)
{
    if (Camel_NearCamera(self) != 0) {
        Camel_SetState(self, CAMEL_WANDER);
    }
    return 1;
}
CLEAN_AS(func_ov078_02279088, Camel_UpdateStand)

/* func_ov078_022790a4 (CAMEL_STAND's entry): it stands, no frames counted and its footsteps
 * off. Agrees. */
int Camel_EnterStand(Camel *self)
{
    camel_stand(self);
    self->countdown = 0;
    Footsteps_Disable(camel_footsteps(self));
    return 1;
}
CLEAN_AS(func_ov078_022790a4, Camel_EnterStand)

/* func_ov078_022790f4 (CAMEL_WANDER's run): its frames counted down; then
 * - with the camera's point away: CAMEL_STAND, once it moves;
 * - else unless it is stepping aside (Camel_AvoidObstacle), when its motion is done: it stands
 *   when its pair at 0x3aa grades 2; else one frame in eight it picks a random clear point
 *   (Camel_RandomPointNear) and goes there (kind 1, or 2 one time in four, for 100 frames, unless
 *   it is already in that kind) when the point is within a quarter turn of where it faces, else
 *   turns to it (kind 4, 80 frames, unless already turning); without a point, and on the other
 *   seven frames, it stands;
 * - while its motion of kind 1, 2 or 4 is not done and it moves, it stands once its frames are
 *   up or its mover's end point is no longer within a quarter turn of where it faces.
 * QUIRK: it answers 0, so its update does too. */
int Camel_UpdateWander(Camel *self)
{
    SceneMotion *motion = camel_motion(self);
    int near = Camel_NearCamera(self);

    Countdown_Tick8(&self->countdown);
    if (near == 0) {
        if (self->speed != 0) {
            Camel_SetState(self, CAMEL_STAND);
        }
        return 0;
    }
    if (Camel_AvoidObstacle(self) != 0) {
        return 0;
    }
    if (SceneMotion_IsDone(motion) != 0) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) camel_at(self, CAMEL_VALUE_3AA)) == CAMEL_VALUE_3AA_STAND) {
            camel_stand(self);
        } else if ((Random_Next(&data_021cb5a0) & CAMEL_PICK_MASK) == 0) {
            Vec3 point = data_021fbee8;
            if (Camel_RandomPointNear(self, &point.x, &point.z) != 0) {
                int yaw = Vec_YawTo(&self->position, &point);
                if (SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle)) != 0) {
                    int kind = CAMEL_MOTION_GO;
                    if (MainRandom_Below(CAMEL_GO_2_ODDS) == 0) {
                        kind = CAMEL_MOTION_GO_2;
                    }
                    if (kind != SceneMotion_Kind(motion)) {
                        SceneMotion_Request(motion, kind, CAMEL_MOTION_PRIORITY, point.x, point.z, 0, 0, 0, 0, data_020c80f8,
                                            0);
                        self->countdown = CAMEL_GO_FRAMES;
                    }
                } else if (SceneMotion_Kind(motion) != CAMEL_MOTION_TURN) {
                    SceneMotion_Request(motion, CAMEL_MOTION_TURN, CAMEL_MOTION_PRIORITY, point.x, point.z, 0, (s16) yaw, 0, 0,
                                        data_020c80f8, 0);
                    self->countdown = CAMEL_TURN_FRAMES;
                }
            } else {
                camel_stand(self);
            }
        } else {
            camel_stand(self);
        }
    } else if (self->speed != 0) {
        if (SceneMotion_Kind(motion) == CAMEL_MOTION_GO || SceneMotion_Kind(motion) == CAMEL_MOTION_GO_2 ||
            SceneMotion_Kind(motion) == CAMEL_MOTION_TURN) {
            if (self->countdown == 0) {
                camel_stand(self);
            } else {
                Vec3 end = *SceneMover_End(camel_mover(self));
                if (camel_faces(self, &end) == 0) {
                    camel_stand(self);
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov078_022790f4, Camel_UpdateWander)

/* func_ov078_022795bc (CAMEL_WANDER's entry): no frames counted, it stands, its footsteps on and
 * its look asked for. Agrees.
 * QUIRK: the footsteps are switched on twice. */
int Camel_EnterWander(Camel *self)
{
    self->countdown = 0;
    camel_stand(self);
    Footsteps_Enable(camel_footsteps(self));
    Footsteps_Enable(camel_footsteps(self));
    SceneLook_Request((SceneLook *) (void *) camel_at(self, CAMEL_LOOK), CAMEL_LOOK_AT, 0, 0, &data_021fbee8, CAMEL_PLAYER,
                      data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov078_022795bc, Camel_EnterWander)

/* func_ov078_02279670: state `state` entered when its entry agrees (or it has none).
 * REQUIRES: `state` is below 5 (the game's are). */
void Camel_SetState(Camel *self, int state)
{
    const CamelStateRow *row = &data_ov078_02279c48[state];
    int agreed = 1;

    if (row->enter.function != 0) {
        agreed = MemberPointer_CallInt(&row->enter, self);
    }
    if (agreed) {
        self->state = state;
    }
}
CLEAN_AS(func_ov078_02279670, Camel_SetState)

/* func_ov078_022796b4 (slot 0x68, each frame): its state's run, when it has one, and what that
 * answers; else 0.
 * REQUIRES: its state is below 5. */
int Camel_Update(Camel *self)
{
    const CamelStateRow *row = &data_ov078_02279c48[self->state];

    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, self);
}
CLEAN_AS(func_ov078_022796b4, Camel_Update)

/* ---- How it moves */

/* func_ov078_0227933c: while it moves, whether it is stepping aside (Camel_StepAside). */
int Camel_AvoidObstacle(Camel *self)
{
    return self->speed != 0 && Camel_StepAside(self) != 0;
}
CLEAN_AS(func_ov078_0227933c, Camel_AvoidObstacle)

/* func_ov078_02279360: until it reaches its mover's start point, by its probe's bits: the way
 * to +x blocked, its mover's end point set 0.5 to -x and 1.0 ahead when that is clear; to -x
 * blocked, 0.5 to +x and 1.0 ahead; both blocked, or no clear point, it stands. Whether it
 * stepped aside (or stood). Once it reached the start point, the end point is put back to the
 * start point when they differ; it answers 0. */
int Camel_StepAside(Camel *self)
{
    SceneMover *mover = camel_mover(self);
    int bits = SceneProbe_Bits(camel_at(self, CAMEL_PROBE));
    const Vec3 *offset;
    Vec3 point;

    if (SceneMover_Reached(mover, (u8 *) self, 1) != 0) {
        if (SceneMover_PointsDiffer(mover) != 0) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }
    switch (bits) {
        case CAMEL_PROBE_RIGHT:
            offset = &data_ov078_02279c3c;
            break;
        case CAMEL_PROBE_LEFT:
            offset = &data_ov078_02279c30;
            break;
        case CAMEL_PROBE_BOTH:
            camel_stand(self);
            return 1;
        default:
            return 0;
    }
    if (Camel_PointAside(self, &point, offset) != 0) {
        SceneMover_SetEnd(mover, &point);
    } else {
        camel_stand(self);
    }
    return 1;
}
CLEAN_AS(func_ov078_02279360, Camel_StepAside)

/* func_ov078_02279460: the point at `offset` from it, turned by where it walks, given in `out`
 * when it is not blocked. Whether it was given. */
int Camel_PointAside(Camel *self, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;

    SceneProbe_PointAt(&point, &self->position, offset, self->walk_angle);
    if (SceneProbe_IsBlocked(&point) != CAMEL_BLOCKED) {
        *out = point;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov078_02279460, Camel_PointAside)

/* func_ov078_0227949c: up to six tries at a point 12.0 from it in a random direction, put on
 * its tile's centre (AcreTile_SnapToTileCentre); the first that is clear (TownTile_IsClearAt)
 * given in `x` and `z`. Whether one was. Each try starts from what the last left in the
 * point. */
int Camel_RandomPointNear(Camel *self, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};

    for (int i = 0; i < CAMEL_POINT_TRIES; i++) {
        unsigned int index = (unsigned int) ((u16) Random_Next(&data_021cb5a0) >> 4) * 2;
        point.x = FX_MulFunc(CAMEL_POINT_DISTANCE, FX_SinCosTable_[index]) + self->position.x;
        point.z = FX_MulFunc(CAMEL_POINT_DISTANCE, FX_SinCosTable_[index + 1]) + self->position.z;
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL) != 0) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov078_0227949c, Camel_RandomPointNear)

/* func_ov078_0227952c: whether the camera exists and its point is in the box around it
 * (Camel_InBox, with a copy of the camera's point). */
int Camel_NearCamera(Camel *self)
{
    if (data_021c67a4 != 0) {
        Vec3 camera = data_021c67d0;
        return Camel_InBox((int) (uintptr_t) self, &camera, &self->position);
    }
    return 0;
}
CLEAN_AS(func_ov078_0227952c, Camel_NearCamera)

/* func_ov078_02279564: whether `point` is less than 16.0 from `centre` either way in x, less
 * than 26.0 from it to -z and less than 10.0 to +z. */
int Camel_InBox(int unused, const Vec3 *centre, const Vec3 *point)
{
    (void) unused;
    return point->x > centre->x - CAMEL_NEAR_X && point->x < centre->x + CAMEL_NEAR_X &&
           point->z > centre->z - CAMEL_NEAR_Z_BEHIND && point->z < centre->z + CAMEL_NEAR_Z_AHEAD;
}
CLEAN_AS(func_ov078_02279564, Camel_InBox)
