/* Overlay 73's character (boar.h): its object's vtable slots, its life, its states and how it
 * moves. */
#include "boar.h"

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
#include "main/screen_panels.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/town_spot.h"
#include "main/town_tile.h"

static_assert(offsetof(Boar, position) == 0x5c && offsetof(Boar, angle) == 0x8e, "Boar");
static_assert(offsetof(Boar, walk_angle) == 0x94 && offsetof(Boar, speed) == 0x98 && offsetof(Boar, countdown) == 0x651,
              "Boar");
static_assert(offsetof(Boar, state) == 0x654 && offsetof(Boar, talk) == 0x658, "Boar");
static_assert(sizeof(Boar) == 0x724, "Boar");

/* The members of the scene object, by place (scene_object.h). */
#define BOAR_PERSON 0xea
#define BOAR_MODEL 0xec
#define BOAR_STANDARD_ANIMS 0x2a0
#define BOAR_FACE 0x2ac
#define BOAR_ANIM 0x334
#define BOAR_MOVER 0x350
#define BOAR_PROBE 0x3a8
#define BOAR_VALUE_3AA 0x3aa
#define BOAR_LOOK 0x3b0
#define BOAR_TALK_STATE 0x418
#define BOAR_EFFECTS 0x420
#define BOAR_COLLIDER 0x49c
#define BOAR_CARRIER 0x4cc
#define BOAR_EMITTER 0x514
#define BOAR_FOOTSTEPS 0x558
#define BOAR_MOTION 0x564
#define BOAR_ACTION 0x618
#define BOAR_HEAP 0x640
#define BOAR_NO_PERSON 0xfff1

/* The field actor that is the player. */
#define BOAR_PLAYER 4

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define BOAR_EVENT_0 0
#define BOAR_EVENT_ACT_STARTS 3
#define BOAR_EVENT_ACT_ENDED 8

/* The talk scene's vtable slot that resets it (BoarTalk_Reset). */
#define BOAR_TALK_SLOT_RESET 2

/* Its motions (scene_motion_request.h): standing, going to a point (kind 1, or 2 one time in
 * four) and turning to one (kind 4). */
#define BOAR_MOTION_STAND 0
#define BOAR_MOTION_GO 1
#define BOAR_MOTION_GO_2 2
#define BOAR_MOTION_TURN 4
#define BOAR_MOTION_PRIORITY 1
#define BOAR_GO_2_ODDS 4
#define BOAR_GO_FRAMES 100
#define BOAR_TURN_FRAMES 80

/* BOAR_WANDER picks a new point one frame in eight (Random_Next's low three bits 0), and stands
 * when its pair at 0x3aa grades 2 (scene_value_3aa.h). */
#define BOAR_PICK_MASK 7
#define BOAR_VALUE_3AA_STAND 2

/* The random points: 12.0 away, six tries. */
#define BOAR_POINT_DISTANCE 0xc000
#define BOAR_POINT_TRIES 6

/* The probe's bits (scene_probe.h): the point to +x blocked, to -x, both. */
#define BOAR_PROBE_RIGHT 1
#define BOAR_PROBE_LEFT 2
#define BOAR_PROBE_BOTH 3

/* What SceneProbe_IsBlocked answers for a blocked point. */
#define BOAR_BLOCKED 1

/* The box around the camera's point it is near in: 16.0 either way in x, 26.0 behind and 10.0
 * ahead in z. */
#define BOAR_NEAR_X 0x10000
#define BOAR_NEAR_Z_BEHIND 0x1a000
#define BOAR_NEAR_Z_AHEAD 0xa000

/* Its look's request (scene_look.h). */
#define BOAR_LOOK_AT 1

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
extern Vec3 data_ov073_02279bfc;
extern Vec3 data_ov073_02279c08;

/* The vtable of its class and its base classes' (scene_object.h, special_scene_object.h). */
extern const u8 data_ov073_02279b00[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];

/* Its model's and its texture's file names. */
extern const char data_ov073_02279a1c[];
extern const char data_ov073_02279a4c[];

static u8 *boar_at(Boar *self, int offset)
{
    return (u8 *) self + offset;
}

static SceneAction *boar_action(Boar *self)
{
    return (SceneAction *) (void *) boar_at(self, BOAR_ACTION);
}

static SceneMotion *boar_motion(Boar *self)
{
    return (SceneMotion *) (void *) boar_at(self, BOAR_MOTION);
}

static SceneMover *boar_mover(Boar *self)
{
    return (SceneMover *) (void *) boar_at(self, BOAR_MOVER);
}

static Footsteps *boar_footsteps(Boar *self)
{
    return (Footsteps *) (void *) boar_at(self, BOAR_FOOTSTEPS);
}

/* It stands. */
static void boar_stand(Boar *self)
{
    SceneMotion_Request(boar_motion(self), BOAR_MOTION_STAND, BOAR_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
}

/* Whether `point` is within a quarter turn of where it faces. */
static int boar_faces(Boar *self, const Vec3 *point)
{
    int yaw = Vec_YawTo(&self->position, point);
    return SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle));
}

/* ---- The object */

/* func_ov073_02278a00 (slot 0x40): the destructor: its talk, then the base class's. */
Boar *Boar_Destruct(Boar *self)
{
    *(const u8 **) (void *) self = data_ov073_02279b00;
    BoarTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov073_02278a00, Boar_Destruct)

/* func_ov073_02278a28 (slot 0x44): destructed, then freed to the auxiliary heap. */
Boar *Boar_DestructDelete(Boar *self)
{
    *(const u8 **) (void *) self = data_ov073_02279b00;
    BoarTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov073_02278a28, Boar_DestructDelete)

/* func_ov073_02278a54 (slot 0x4c): told of event 0, BOAR_FINISH; told the act starts (3), the
 * talk reset and given the player's object as its motion argument, then BOAR_TALK; told the
 * act ended (8), BOAR_WANDER. */
void Boar_OnEvent(Boar *self, int code)
{
    switch (code) {
        case BOAR_EVENT_0:
            Boar_SetState(self, BOAR_FINISH);
            break;
        case BOAR_EVENT_ACT_STARTS: {
            const u32 *vtable = (const u32 *) (const void *) self->talk.scene.vtable;
            ((void (*)(BoarTalk *))(uintptr_t) vtable[BOAR_TALK_SLOT_RESET])(&self->talk);
            SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, BOAR_PLAYER));
            Boar_SetState(self, BOAR_TALK);
            break;
        }
        case BOAR_EVENT_ACT_ENDED:
            Boar_SetState(self, BOAR_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov073_02278a54, Boar_OnEvent)

/* func_ov073_02278aa4 (slot 0x48): the player may act on it while no action of its runs. */
int Boar_MayAct(Boar *self)
{
    return SceneAction_IsBusy(boar_action(self)) == 0;
}
CLEAN_AS(func_ov073_02278aa4, Boar_MayAct)

/* func_ov073_02279698 (slot 0x70): its model's file name, "npc_sp/model/boa.nsbmd". */
int Boar_ModelName(void)
{
    return (int) (uintptr_t) data_ov073_02279a1c;
}
CLEAN_AS(func_ov073_02279698, Boar_ModelName)

/* func_ov073_022796a0 (slot 0x6c): its texture's file name, "npc_sp/model/boa_tex.nsbtx". */
int Boar_TextureName(void)
{
    return (int) (uintptr_t) data_ov073_02279a4c;
}
CLEAN_AS(func_ov073_022796a0, Boar_TextureName)

/* func_ov073_022796a8 (slot 0x00): unless the base class refuses to start, BOAR_STAND. Whether
 * it started. */
int Boar_Start(Boar *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    Boar_SetState(self, BOAR_STAND);
    return 1;
}
CLEAN_AS(func_ov073_022796a8, Boar_Start)

/* func_ov073_022796c8 (slot 0x0c): unless the base class refuses to leave, where it stands kept
 * as the spot of part 0x04 of the object at data_021d27ac (town_spot.h). Whether it left. */
int Boar_Leave(Boar *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    TownSpot_Set((TownSpot *) (void *) Block021d27ac_Part04(Block021d27ac_Get()), (u32) self->position.x,
                 (u32) self->position.z);
    return 1;
}
CLEAN_AS(func_ov073_022796c8, Boar_Leave)

/* func_ov073_022796f0 (slot 0x04): unless the base class refuses, its scene is its talk, which
 * starts over with it as its owner. Whether it was set up. */
int Boar_Init(Boar *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    BoarTalk_Begin(&self->talk, self);
    return 1;
}
CLEAN_AS(func_ov073_022796f0, Boar_Init)

/* func_ov073_02279720 (slot 0xa8): the speed scale of its animation player: the villagers'
 * (data_020c8120), not the special characters' slower one. */
int Boar_AnimSpeed(void)
{
    return data_020c8120;
}
CLEAN_AS(func_ov073_02279720, Boar_AnimSpeed)

/* func_ov073_0227972c (its record's create function, data_ov073_02279a34): a zeroed block of
 * 0x724 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
Boar *Boar_Create(void)
{
    Boar *self = (Boar *) Heap_AllocAuxZeroed(sizeof(Boar));

    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) self);
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) boar_at(self, BOAR_PERSON) = BOAR_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) boar_at(self, BOAR_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) boar_at(self, BOAR_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) boar_at(self, BOAR_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) boar_at(self, BOAR_ANIM));
    SceneMover_Construct(boar_mover(self));
    SceneProbe_Construct(boar_at(self, BOAR_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) boar_at(self, BOAR_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) boar_at(self, BOAR_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) boar_at(self, BOAR_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) boar_at(self, BOAR_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) boar_at(self, BOAR_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) boar_at(self, BOAR_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) boar_at(self, BOAR_EMITTER));
    Footsteps_Construct(boar_footsteps(self));
    SceneMotion_Construct(boar_motion(self));
    SceneAction_Construct(boar_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) boar_at(self, BOAR_HEAP));
    *(const u8 **) (void *) self = data_ov073_02279b00;
    BoarTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_ov073_0227972c, Boar_Create)

/* ---- Its states */

/* func_ov073_02278fdc (BOAR_TALK's run): nothing; agrees. */
int Boar_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov073_02278fdc, Boar_UpdateTalk)

/* func_ov073_02278fe0 (BOAR_TALK's entry): it turns to the one its talk names (by the yaw to
 * it), or to where it faces without one, and talks. Agrees. */
int Boar_EnterTalk(Boar *self)
{
    int other = SceneBase_MotionArg(&self->talk.scene);
    int yaw = self->angle;

    if (other != 0) {
        yaw = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) other);
    }
    SceneAction_RequestTurnAndTalk(boar_action(self), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov073_02278fe0, Boar_EnterTalk)

/* func_ov073_0227901c (BOAR_DONE's run): nothing; agrees. */
int Boar_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov073_0227901c, Boar_UpdateDone)

/* func_ov073_02279020 (BOAR_FINISH's run): once no action of its runs, its event finished, the
 * screen panels' request cleared and BOAR_DONE. Agrees always. */
int Boar_UpdateFinish(Boar *self)
{
    if (SceneAction_IsBusy(boar_action(self)) == 0) {
        ScreenPanels_ClearRequest((unsigned int) EventQueue_FinishObjectEvent(self));
        Boar_SetState(self, BOAR_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov073_02279020, Boar_UpdateFinish)

/* func_ov073_02279050 (BOAR_FINISH's entry): nothing; agrees. */
int Boar_EnterFinish(void)
{
    return 1;
}
CLEAN_AS(func_ov073_02279050, Boar_EnterFinish)

/* func_ov073_02279054 (BOAR_STAND's run): once the camera's point is near, BOAR_WANDER. Agrees
 * always. */
int Boar_UpdateStand(Boar *self)
{
    if (Boar_NearCamera(self) != 0) {
        Boar_SetState(self, BOAR_WANDER);
    }
    return 1;
}
CLEAN_AS(func_ov073_02279054, Boar_UpdateStand)

/* func_ov073_02279070 (BOAR_STAND's entry): it stands, no frames counted and its footsteps
 * off. Agrees. */
int Boar_EnterStand(Boar *self)
{
    boar_stand(self);
    self->countdown = 0;
    Footsteps_Disable(boar_footsteps(self));
    return 1;
}
CLEAN_AS(func_ov073_02279070, Boar_EnterStand)

/* func_ov073_022790c0 (BOAR_WANDER's run): its frames counted down; then
 * - with the camera's point away: BOAR_STAND, once it moves;
 * - else unless it is stepping aside (Boar_AvoidObstacle), when its motion is done: it stands
 *   when its pair at 0x3aa grades 2; else one frame in eight it picks a random clear point
 *   (Boar_RandomPointNear) and goes there (kind 1, or 2 one time in four, for 100 frames, unless
 *   it is already in that kind) when the point is within a quarter turn of where it faces, else
 *   turns to it (kind 4, 80 frames, unless already turning); without a point, and on the other
 *   seven frames, it stands;
 * - while its motion of kind 1, 2 or 4 is not done and it moves, it stands once its frames are
 *   up or its mover's end point is no longer within a quarter turn of where it faces.
 * QUIRK: it answers 0, so its update does too. */
int Boar_UpdateWander(Boar *self)
{
    SceneMotion *motion = boar_motion(self);
    int near = Boar_NearCamera(self);

    Countdown_Tick8(&self->countdown);
    if (near == 0) {
        if (self->speed != 0) {
            Boar_SetState(self, BOAR_STAND);
        }
        return 0;
    }
    if (Boar_AvoidObstacle(self) != 0) {
        return 0;
    }
    if (SceneMotion_IsDone(motion) != 0) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) boar_at(self, BOAR_VALUE_3AA)) == BOAR_VALUE_3AA_STAND) {
            boar_stand(self);
        } else if ((Random_Next(&data_021cb5a0) & BOAR_PICK_MASK) == 0) {
            Vec3 point = data_021fbee8;
            if (Boar_RandomPointNear(self, &point.x, &point.z) != 0) {
                int yaw = Vec_YawTo(&self->position, &point);
                if (SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle)) != 0) {
                    int kind = BOAR_MOTION_GO;
                    if (MainRandom_Below(BOAR_GO_2_ODDS) == 0) {
                        kind = BOAR_MOTION_GO_2;
                    }
                    if (kind != SceneMotion_Kind(motion)) {
                        SceneMotion_Request(motion, kind, BOAR_MOTION_PRIORITY, point.x, point.z, 0, 0, 0, 0, data_020c80f8,
                                            0);
                        self->countdown = BOAR_GO_FRAMES;
                    }
                } else if (SceneMotion_Kind(motion) != BOAR_MOTION_TURN) {
                    SceneMotion_Request(motion, BOAR_MOTION_TURN, BOAR_MOTION_PRIORITY, point.x, point.z, 0, (s16) yaw, 0, 0,
                                        data_020c80f8, 0);
                    self->countdown = BOAR_TURN_FRAMES;
                }
            } else {
                boar_stand(self);
            }
        } else {
            boar_stand(self);
        }
    } else if (self->speed != 0) {
        if (SceneMotion_Kind(motion) == BOAR_MOTION_GO || SceneMotion_Kind(motion) == BOAR_MOTION_GO_2 ||
            SceneMotion_Kind(motion) == BOAR_MOTION_TURN) {
            if (self->countdown == 0) {
                boar_stand(self);
            } else {
                Vec3 end = *SceneMover_End(boar_mover(self));
                if (boar_faces(self, &end) == 0) {
                    boar_stand(self);
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov073_022790c0, Boar_UpdateWander)

/* func_ov073_02279588 (BOAR_WANDER's entry): no frames counted, it stands, its footsteps on and
 * its look asked for. Agrees.
 * QUIRK: the footsteps are switched on twice. */
int Boar_EnterWander(Boar *self)
{
    self->countdown = 0;
    boar_stand(self);
    Footsteps_Enable(boar_footsteps(self));
    Footsteps_Enable(boar_footsteps(self));
    SceneLook_Request((SceneLook *) (void *) boar_at(self, BOAR_LOOK), BOAR_LOOK_AT, 0, 0, &data_021fbee8, BOAR_PLAYER,
                      data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov073_02279588, Boar_EnterWander)

/* func_ov073_02279608: state `state` entered when its entry agrees (or it has none).
 * REQUIRES: `state` is below 5 (the game's are). */
void Boar_SetState(Boar *self, int state)
{
    const BoarStateRow *row = &data_ov073_02279c14[state];
    int agreed = 1;

    if (row->enter.function != 0) {
        agreed = MemberPointer_CallInt(&row->enter, self);
    }
    if (agreed) {
        self->state = state;
    }
}
CLEAN_AS(func_ov073_02279608, Boar_SetState)

/* func_ov073_0227964c (slot 0x68, each frame): its state's run, when it has one, and what that
 * answers; else 0.
 * REQUIRES: its state is below 5. */
int Boar_Update(Boar *self)
{
    const BoarStateRow *row = &data_ov073_02279c14[self->state];

    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, self);
}
CLEAN_AS(func_ov073_0227964c, Boar_Update)

/* ---- How it moves */

/* func_ov073_02279308: while it moves, whether it is stepping aside (Boar_StepAside). */
int Boar_AvoidObstacle(Boar *self)
{
    return self->speed != 0 && Boar_StepAside(self) != 0;
}
CLEAN_AS(func_ov073_02279308, Boar_AvoidObstacle)

/* func_ov073_0227932c: until it reaches its mover's start point, by its probe's bits: the way
 * to +x blocked, its mover's end point set 0.5 to -x and 1.0 ahead when that is clear; to -x
 * blocked, 0.5 to +x and 1.0 ahead; both blocked, or no clear point, it stands. Whether it
 * stepped aside (or stood). Once it reached the start point, the end point is put back to the
 * start point when they differ; it answers 0. */
int Boar_StepAside(Boar *self)
{
    SceneMover *mover = boar_mover(self);
    int bits = SceneProbe_Bits(boar_at(self, BOAR_PROBE));
    const Vec3 *offset;
    Vec3 point;

    if (SceneMover_Reached(mover, (u8 *) self, 1) != 0) {
        if (SceneMover_PointsDiffer(mover) != 0) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }
    switch (bits) {
        case BOAR_PROBE_RIGHT:
            offset = &data_ov073_02279c08;
            break;
        case BOAR_PROBE_LEFT:
            offset = &data_ov073_02279bfc;
            break;
        case BOAR_PROBE_BOTH:
            boar_stand(self);
            return 1;
        default:
            return 0;
    }
    if (Boar_PointAside(self, &point, offset) != 0) {
        SceneMover_SetEnd(mover, &point);
    } else {
        boar_stand(self);
    }
    return 1;
}
CLEAN_AS(func_ov073_0227932c, Boar_StepAside)

/* func_ov073_0227942c: the point at `offset` from it, turned by where it walks, given in `out`
 * when it is not blocked. Whether it was given. */
int Boar_PointAside(Boar *self, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;

    SceneProbe_PointAt(&point, &self->position, offset, self->walk_angle);
    if (SceneProbe_IsBlocked(&point) != BOAR_BLOCKED) {
        *out = point;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov073_0227942c, Boar_PointAside)

/* func_ov073_02279468: up to six tries at a point 12.0 from it in a random direction, put on
 * its tile's centre (AcreTile_SnapToTileCentre); the first that is clear (TownTile_IsClearAt)
 * given in `x` and `z`. Whether one was. Each try starts from what the last left in the
 * point. */
int Boar_RandomPointNear(Boar *self, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};

    for (int i = 0; i < BOAR_POINT_TRIES; i++) {
        unsigned int index = (unsigned int) ((u16) Random_Next(&data_021cb5a0) >> 4) * 2;
        point.x = FX_MulFunc(BOAR_POINT_DISTANCE, FX_SinCosTable_[index]) + self->position.x;
        point.z = FX_MulFunc(BOAR_POINT_DISTANCE, FX_SinCosTable_[index + 1]) + self->position.z;
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL) != 0) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov073_02279468, Boar_RandomPointNear)

/* func_ov073_022794f8: whether the camera exists and its point is in the box around it
 * (Boar_InBox, with a copy of the camera's point). */
int Boar_NearCamera(Boar *self)
{
    if (data_021c67a4 != 0) {
        Vec3 camera = data_021c67d0;
        return Boar_InBox((int) (uintptr_t) self, &camera, &self->position);
    }
    return 0;
}
CLEAN_AS(func_ov073_022794f8, Boar_NearCamera)

/* func_ov073_02279530: whether `point` is less than 16.0 from `centre` either way in x, less
 * than 26.0 from it to -z and less than 10.0 to +z. */
int Boar_InBox(int unused, const Vec3 *centre, const Vec3 *point)
{
    (void) unused;
    return point->x > centre->x - BOAR_NEAR_X && point->x < centre->x + BOAR_NEAR_X &&
           point->z > centre->z - BOAR_NEAR_Z_BEHIND && point->z < centre->z + BOAR_NEAR_Z_AHEAD;
}
CLEAN_AS(func_ov073_02279530, Boar_InBox)
