/* Overlay 79's walrus (walrus.h): his object's vtable slots, his life, his states and how he
 * moves. */
#include "walrus.h"

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
#include "main/event_announce.h"
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

static_assert(offsetof(Walrus, position) == 0x5c && offsetof(Walrus, angle) == 0x8e, "Walrus");
static_assert(offsetof(Walrus, walk_angle) == 0x94 && offsetof(Walrus, speed) == 0x98 && offsetof(Walrus, countdown) == 0x651,
              "Walrus");
static_assert(offsetof(Walrus, state) == 0x654 && offsetof(Walrus, talk) == 0x658, "Walrus");
static_assert(sizeof(Walrus) == 0x724, "Walrus");

/* The members of the scene object, by place (scene_object.h). */
#define WALRUS_PERSON 0xea
#define WALRUS_MODEL 0xec
#define WALRUS_STANDARD_ANIMS 0x2a0
#define WALRUS_FACE 0x2ac
#define WALRUS_ANIM 0x334
#define WALRUS_MOVER 0x350
#define WALRUS_PROBE 0x3a8
#define WALRUS_VALUE_3AA 0x3aa
#define WALRUS_LOOK 0x3b0
#define WALRUS_TALK_STATE 0x418
#define WALRUS_EFFECTS 0x420
#define WALRUS_COLLIDER 0x49c
#define WALRUS_CARRIER 0x4cc
#define WALRUS_EMITTER 0x514
#define WALRUS_FOOTSTEPS 0x558
#define WALRUS_MOTION 0x564
#define WALRUS_ACTION 0x618
#define WALRUS_HEAP 0x640
#define WALRUS_NO_PERSON 0xfff1

/* The field actor that is the player. */
#define WALRUS_PLAYER 4

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define WALRUS_EVENT_0 0
#define WALRUS_EVENT_ACT_STARTS 3
#define WALRUS_EVENT_ACT_ENDED 8

/* The talk scene's vtable slot that resets it (WalrusTalk_Reset). */
#define WALRUS_TALK_SLOT_RESET 2

/* Its motions (scene_motion_request.h): standing, going to a point (kind 1, or 2 one time in
 * four) and turning to one (kind 4). */
#define WALRUS_MOTION_STAND 0
#define WALRUS_MOTION_GO 1
#define WALRUS_MOTION_GO_2 2
#define WALRUS_MOTION_TURN 4
#define WALRUS_MOTION_PRIORITY 1
#define WALRUS_GO_2_ODDS 4
#define WALRUS_GO_FRAMES 100
#define WALRUS_TURN_FRAMES 80

/* WALRUS_WANDER picks a new point one frame in eight (Random_Next's low three bits 0), and stands
 * when its pair at 0x3aa grades 2 (scene_value_3aa.h). */
#define WALRUS_PICK_MASK 7
#define WALRUS_VALUE_3AA_STAND 2

/* The random points: 12.0 away, six tries. */
#define WALRUS_POINT_DISTANCE 0xc000
#define WALRUS_POINT_TRIES 6

/* The probe's bits (scene_probe.h): the point to +x blocked, to -x, both. */
#define WALRUS_PROBE_RIGHT 1
#define WALRUS_PROBE_LEFT 2
#define WALRUS_PROBE_BOTH 3

/* What SceneProbe_IsBlocked answers for a blocked point. */
#define WALRUS_BLOCKED 1

/* The box around the camera's point it is near in: 16.0 either way in x, 26.0 behind and 10.0
 * ahead in z. */
#define WALRUS_NEAR_X 0x10000
#define WALRUS_NEAR_Z_BEHIND 0x1a000
#define WALRUS_NEAR_Z_AHEAD 0xa000

/* Its look's request (scene_look.h). */
#define WALRUS_LOOK_AT 1

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
extern Vec3 data_ov079_0227a1f4;
extern Vec3 data_ov079_0227a200;

/* The vtable of its class and its base classes' (scene_object.h, special_scene_object.h). */
extern const u8 data_ov079_0227a104[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];

/* Its model's and its texture's file names. */
extern const char data_ov079_0227a020[];
extern const char data_ov079_0227a050[];

static u8 *walrus_at(Walrus *self, int offset)
{
    return (u8 *) self + offset;
}

static SceneAction *walrus_action(Walrus *self)
{
    return (SceneAction *) (void *) walrus_at(self, WALRUS_ACTION);
}

static SceneMotion *walrus_motion(Walrus *self)
{
    return (SceneMotion *) (void *) walrus_at(self, WALRUS_MOTION);
}

static SceneMover *walrus_mover(Walrus *self)
{
    return (SceneMover *) (void *) walrus_at(self, WALRUS_MOVER);
}

static Footsteps *walrus_footsteps(Walrus *self)
{
    return (Footsteps *) (void *) walrus_at(self, WALRUS_FOOTSTEPS);
}

/* It stands. */
static void walrus_stand(Walrus *self)
{
    SceneMotion_Request(walrus_motion(self), WALRUS_MOTION_STAND, WALRUS_MOTION_PRIORITY, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
}

/* Whether `point` is within a quarter turn of where it faces. */
static int walrus_faces(Walrus *self, const Vec3 *point)
{
    int yaw = Vec_YawTo(&self->position, point);
    return SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle));
}

/* ---- The object */

/* func_ov079_02278a00 (slot 0x40): the destructor: its talk, then the base class's. */
Walrus *Walrus_Destruct(Walrus *self)
{
    *(const u8 **) (void *) self = data_ov079_0227a104;
    WalrusTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_ov079_02278a00, Walrus_Destruct)

/* func_ov079_02278a28 (slot 0x44): destructed, then freed to the auxiliary heap. */
Walrus *Walrus_DestructDelete(Walrus *self)
{
    *(const u8 **) (void *) self = data_ov079_0227a104;
    WalrusTalk_Destruct(&self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov079_02278a28, Walrus_DestructDelete)

/* func_ov079_02278a54 (slot 0x4c): told of event 0, WALRUS_FINISH; told the act starts (3), the
 * talk reset and given the player's object as its motion argument, then WALRUS_TALK; told the
 * act ended (8), WALRUS_WANDER. */
void Walrus_OnEvent(Walrus *self, int code)
{
    switch (code) {
        case WALRUS_EVENT_0:
            Walrus_SetState(self, WALRUS_FINISH);
            break;
        case WALRUS_EVENT_ACT_STARTS: {
            const u32 *vtable = (const u32 *) (const void *) self->talk.scene.vtable;
            ((void (*)(WalrusTalk *))(uintptr_t) vtable[WALRUS_TALK_SLOT_RESET])(&self->talk);
            SceneBase_SetMotionArg(&self->talk.scene, SceneObject_ActorObject((u8 *) self, WALRUS_PLAYER));
            Walrus_SetState(self, WALRUS_TALK);
            break;
        }
        case WALRUS_EVENT_ACT_ENDED:
            Walrus_SetState(self, WALRUS_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov079_02278a54, Walrus_OnEvent)

/* func_ov079_02278aa4 (slot 0x48): the player may act on it while no action of its runs. */
int Walrus_MayAct(Walrus *self)
{
    return SceneAction_IsBusy(walrus_action(self)) == 0;
}
CLEAN_AS(func_ov079_02278aa4, Walrus_MayAct)

/* func_ov079_02279cc4 (slot 0x70): its model's file name, "npc_sp/model/wrl.nsbmd". */
int Walrus_ModelName(void)
{
    return (int) (uintptr_t) data_ov079_0227a020;
}
CLEAN_AS(func_ov079_02279cc4, Walrus_ModelName)

/* func_ov079_02279ccc (slot 0x6c): its texture's file name, "npc_sp/model/wrl_tex.nsbtx". */
int Walrus_TextureName(void)
{
    return (int) (uintptr_t) data_ov079_0227a050;
}
CLEAN_AS(func_ov079_02279ccc, Walrus_TextureName)

/* func_ov079_02279d00 (slot 0x00): unless the base class refuses to start, WALRUS_STAND. Whether
 * it started. */
int Walrus_Start(Walrus *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    Walrus_SetState(self, WALRUS_STAND);
    return 1;
}
CLEAN_AS(func_ov079_02279d00, Walrus_Start)

/* func_ov079_02279cd4 (slot 0x0c): unless the base class refuses to leave, a new random spot
 * picked for part 0x04 of the object at data_021d27ac (town_spot.h), except when the player was
 * sent to an announcement (EventAnnounce_Entered). Whether he left. */
int Walrus_Leave(Walrus *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    if (EventAnnounce_Entered() == 0) {
        TownSpot_PickRandom((TownSpot *) Block021d27ac_Part04(Block021d27ac_Get()));
    }
    return 1;
}
CLEAN_AS(func_ov079_02279cd4, Walrus_Leave)

/* func_ov079_02279d20 (slot 0x04): unless the base class refuses, its scene is its talk, which
 * starts over with it as its owner. Whether it was set up. */
int Walrus_Init(Walrus *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    SceneObject_SetScene((u8 *) self, &self->talk.scene);
    WalrusTalk_Begin(&self->talk, self);
    return 1;
}
CLEAN_AS(func_ov079_02279d20, Walrus_Init)

/* func_ov079_02279d50 (slot 0xa8): the speed scale of its animation player: the villagers'
 * (data_020c8120), not the special characters' slower one. */
int Walrus_AnimSpeed(void)
{
    return data_020c8120;
}
CLEAN_AS(func_ov079_02279d50, Walrus_AnimSpeed)

/* func_ov079_02279d5c (its record's create function, data_ov079_0227a038): a zeroed block of
 * 0x724 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then its class's vtable and its talk scene. Null when
 * there is no room. */
Walrus *Walrus_Create(void)
{
    Walrus *self = (Walrus *) Heap_AllocAuxZeroed(sizeof(Walrus));

    if (self == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) self);
    *(const u8 **) (void *) self = data_020d8c64;
    *(u16 *) (void *) walrus_at(self, WALRUS_PERSON) = WALRUS_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) walrus_at(self, WALRUS_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) walrus_at(self, WALRUS_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) walrus_at(self, WALRUS_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) walrus_at(self, WALRUS_ANIM));
    SceneMover_Construct(walrus_mover(self));
    SceneProbe_Construct(walrus_at(self, WALRUS_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) walrus_at(self, WALRUS_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) walrus_at(self, WALRUS_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) walrus_at(self, WALRUS_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) walrus_at(self, WALRUS_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) walrus_at(self, WALRUS_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) walrus_at(self, WALRUS_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) walrus_at(self, WALRUS_EMITTER));
    Footsteps_Construct(walrus_footsteps(self));
    SceneMotion_Construct(walrus_motion(self));
    SceneAction_Construct(walrus_action(self));
    *(const u8 **) (void *) self = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) walrus_at(self, WALRUS_HEAP));
    *(const u8 **) (void *) self = data_ov079_0227a104;
    WalrusTalk_Construct(&self->talk);
    return self;
}
CLEAN_AS(func_ov079_02279d5c, Walrus_Create)

/* ---- Its states */

/* func_ov079_02279640 (WALRUS_TALK's run): nothing; agrees. */
int Walrus_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov079_02279640, Walrus_UpdateTalk)

/* func_ov079_02279644 (WALRUS_TALK's entry): it turns to the one its talk names (by the yaw to
 * it), or to where it faces without one, and talks. Agrees. */
int Walrus_EnterTalk(Walrus *self)
{
    int other = SceneBase_MotionArg(&self->talk.scene);
    int yaw = self->angle;

    if (other != 0) {
        yaw = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) other);
    }
    SceneAction_RequestTurnAndTalk(walrus_action(self), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov079_02279644, Walrus_EnterTalk)

/* func_ov079_0227960c (WALRUS_DONE's run): nothing; agrees. */
int Walrus_UpdateDone(void)
{
    return 1;
}
CLEAN_AS(func_ov079_0227960c, Walrus_UpdateDone)

/* func_ov079_02279610 (WALRUS_FINISH's run): once no action of his runs, his event finished and
 * WALRUS_DONE. Agrees always. */
int Walrus_UpdateFinish(Walrus *self)
{
    if (SceneAction_IsBusy(walrus_action(self)) == 0) {
        EventQueue_FinishObjectEvent(self);
        Walrus_SetState(self, WALRUS_DONE);
    }
    return 1;
}
CLEAN_AS(func_ov079_02279610, Walrus_UpdateFinish)

/* func_ov079_0227963c (WALRUS_FINISH's entry): nothing; agrees. */
int Walrus_EnterFinish(void)
{
    return 1;
}
CLEAN_AS(func_ov079_0227963c, Walrus_EnterFinish)

/* func_ov079_02279680 (WALRUS_STAND's run): once the camera's point is near, WALRUS_WANDER. Agrees
 * always. */
int Walrus_UpdateStand(Walrus *self)
{
    if (Walrus_NearCamera(self) != 0) {
        Walrus_SetState(self, WALRUS_WANDER);
    }
    return 1;
}
CLEAN_AS(func_ov079_02279680, Walrus_UpdateStand)

/* func_ov079_0227969c (WALRUS_STAND's entry): it stands, no frames counted and its footsteps
 * off. Agrees. */
int Walrus_EnterStand(Walrus *self)
{
    walrus_stand(self);
    self->countdown = 0;
    Footsteps_Disable(walrus_footsteps(self));
    return 1;
}
CLEAN_AS(func_ov079_0227969c, Walrus_EnterStand)

/* func_ov079_022796ec (WALRUS_WANDER's run): its frames counted down; then
 * - with the camera's point away: WALRUS_STAND, once it moves;
 * - else unless it is stepping aside (Walrus_AvoidObstacle), when its motion is done: it stands
 *   when its pair at 0x3aa grades 2; else one frame in eight it picks a random clear point
 *   (Walrus_RandomPointNear) and goes there (kind 1, or 2 one time in four, for 100 frames, unless
 *   it is already in that kind) when the point is within a quarter turn of where it faces, else
 *   turns to it (kind 4, 80 frames, unless already turning); without a point, and on the other
 *   seven frames, it stands;
 * - while its motion of kind 1, 2 or 4 is not done and it moves, it stands once its frames are
 *   up or its mover's end point is no longer within a quarter turn of where it faces.
 * QUIRK: it answers 0, so its update does too. */
int Walrus_UpdateWander(Walrus *self)
{
    SceneMotion *motion = walrus_motion(self);
    int near = Walrus_NearCamera(self);

    Countdown_Tick8(&self->countdown);
    if (near == 0) {
        if (self->speed != 0) {
            Walrus_SetState(self, WALRUS_STAND);
        }
        return 0;
    }
    if (Walrus_AvoidObstacle(self) != 0) {
        return 0;
    }
    if (SceneMotion_IsDone(motion) != 0) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) walrus_at(self, WALRUS_VALUE_3AA)) == WALRUS_VALUE_3AA_STAND) {
            walrus_stand(self);
        } else if ((Random_Next(&data_021cb5a0) & WALRUS_PICK_MASK) == 0) {
            Vec3 point = data_021fbee8;
            if (Walrus_RandomPointNear(self, &point.x, &point.z) != 0) {
                int yaw = Vec_YawTo(&self->position, &point);
                if (SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle)) != 0) {
                    int kind = WALRUS_MOTION_GO;
                    if (MainRandom_Below(WALRUS_GO_2_ODDS) == 0) {
                        kind = WALRUS_MOTION_GO_2;
                    }
                    if (kind != SceneMotion_Kind(motion)) {
                        SceneMotion_Request(motion, kind, WALRUS_MOTION_PRIORITY, point.x, point.z, 0, 0, 0, 0, data_020c80f8,
                                            0);
                        self->countdown = WALRUS_GO_FRAMES;
                    }
                } else if (SceneMotion_Kind(motion) != WALRUS_MOTION_TURN) {
                    SceneMotion_Request(motion, WALRUS_MOTION_TURN, WALRUS_MOTION_PRIORITY, point.x, point.z, 0, (s16) yaw, 0,
                                        0, data_020c80f8, 0);
                    self->countdown = WALRUS_TURN_FRAMES;
                }
            } else {
                walrus_stand(self);
            }
        } else {
            walrus_stand(self);
        }
    } else if (self->speed != 0) {
        if (SceneMotion_Kind(motion) == WALRUS_MOTION_GO || SceneMotion_Kind(motion) == WALRUS_MOTION_GO_2 ||
            SceneMotion_Kind(motion) == WALRUS_MOTION_TURN) {
            if (self->countdown == 0) {
                walrus_stand(self);
            } else {
                Vec3 end = *SceneMover_End(walrus_mover(self));
                if (walrus_faces(self, &end) == 0) {
                    walrus_stand(self);
                }
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov079_022796ec, Walrus_UpdateWander)

/* func_ov079_02279bb4 (WALRUS_WANDER's entry): no frames counted, it stands, its footsteps on and
 * its look asked for. Agrees.
 * QUIRK: the footsteps are switched on twice. */
int Walrus_EnterWander(Walrus *self)
{
    self->countdown = 0;
    walrus_stand(self);
    Footsteps_Enable(walrus_footsteps(self));
    Footsteps_Enable(walrus_footsteps(self));
    SceneLook_Request((SceneLook *) (void *) walrus_at(self, WALRUS_LOOK), WALRUS_LOOK_AT, 0, 0, &data_021fbee8, WALRUS_PLAYER,
                      data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov079_02279bb4, Walrus_EnterWander)

/* func_ov079_02279c34: state `state` entered when its entry agrees (or it has none).
 * REQUIRES: `state` is below 5 (the game's are). */
void Walrus_SetState(Walrus *self, int state)
{
    const WalrusStateRow *row = &data_ov079_0227a224[state];
    int agreed = 1;

    if (row->enter.function != 0) {
        agreed = MemberPointer_CallInt(&row->enter, self);
    }
    if (agreed) {
        self->state = state;
    }
}
CLEAN_AS(func_ov079_02279c34, Walrus_SetState)

/* func_ov079_02279c78 (slot 0x68, each frame): its state's run, when it has one, and what that
 * answers; else 0.
 * REQUIRES: its state is below 5. */
int Walrus_Update(Walrus *self)
{
    const WalrusStateRow *row = &data_ov079_0227a224[self->state];

    if (row->run.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&row->run, self);
}
CLEAN_AS(func_ov079_02279c78, Walrus_Update)

/* ---- How it moves */

/* func_ov079_02279934: while it moves, whether it is stepping aside (Walrus_StepAside). */
int Walrus_AvoidObstacle(Walrus *self)
{
    return self->speed != 0 && Walrus_StepAside(self) != 0;
}
CLEAN_AS(func_ov079_02279934, Walrus_AvoidObstacle)

/* func_ov079_02279958: until it reaches its mover's start point, by its probe's bits: the way
 * to +x blocked, its mover's end point set 0.5 to -x and 1.0 ahead when that is clear; to -x
 * blocked, 0.5 to +x and 1.0 ahead; both blocked, or no clear point, it stands. Whether it
 * stepped aside (or stood). Once it reached the start point, the end point is put back to the
 * start point when they differ; it answers 0. */
int Walrus_StepAside(Walrus *self)
{
    SceneMover *mover = walrus_mover(self);
    int bits = SceneProbe_Bits(walrus_at(self, WALRUS_PROBE));
    const Vec3 *offset;
    Vec3 point;

    if (SceneMover_Reached(mover, (u8 *) self, 1) != 0) {
        if (SceneMover_PointsDiffer(mover) != 0) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }
    switch (bits) {
        case WALRUS_PROBE_RIGHT:
            offset = &data_ov079_0227a200;
            break;
        case WALRUS_PROBE_LEFT:
            offset = &data_ov079_0227a1f4;
            break;
        case WALRUS_PROBE_BOTH:
            walrus_stand(self);
            return 1;
        default:
            return 0;
    }
    if (Walrus_PointAside(self, &point, offset) != 0) {
        SceneMover_SetEnd(mover, &point);
    } else {
        walrus_stand(self);
    }
    return 1;
}
CLEAN_AS(func_ov079_02279958, Walrus_StepAside)

/* func_ov079_02279a58: the point at `offset` from it, turned by where it walks, given in `out`
 * when it is not blocked. Whether it was given. */
int Walrus_PointAside(Walrus *self, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;

    SceneProbe_PointAt(&point, &self->position, offset, self->walk_angle);
    if (SceneProbe_IsBlocked(&point) != WALRUS_BLOCKED) {
        *out = point;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov079_02279a58, Walrus_PointAside)

/* func_ov079_02279a94: up to six tries at a point 12.0 from it in a random direction, put on
 * its tile's centre (AcreTile_SnapToTileCentre); the first that is clear (TownTile_IsClearAt)
 * given in `x` and `z`. Whether one was. Each try starts from what the last left in the
 * point. */
int Walrus_RandomPointNear(Walrus *self, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};

    for (int i = 0; i < WALRUS_POINT_TRIES; i++) {
        unsigned int index = (unsigned int) ((u16) Random_Next(&data_021cb5a0) >> 4) * 2;
        point.x = FX_MulFunc(WALRUS_POINT_DISTANCE, FX_SinCosTable_[index]) + self->position.x;
        point.z = FX_MulFunc(WALRUS_POINT_DISTANCE, FX_SinCosTable_[index + 1]) + self->position.z;
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL) != 0) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov079_02279a94, Walrus_RandomPointNear)

/* func_ov079_02279b24: whether the camera exists and its point is in the box around it
 * (Walrus_InBox, with a copy of the camera's point). */
int Walrus_NearCamera(Walrus *self)
{
    if (data_021c67a4 != 0) {
        Vec3 camera = data_021c67d0;
        return Walrus_InBox((int) (uintptr_t) self, &camera, &self->position);
    }
    return 0;
}
CLEAN_AS(func_ov079_02279b24, Walrus_NearCamera)

/* func_ov079_02279b5c: whether `point` is less than 16.0 from `centre` either way in x, less
 * than 26.0 from it to -z and less than 10.0 to +z. */
int Walrus_InBox(int unused, const Vec3 *centre, const Vec3 *point)
{
    (void) unused;
    return point->x > centre->x - WALRUS_NEAR_X && point->x < centre->x + WALRUS_NEAR_X &&
           point->z > centre->z - WALRUS_NEAR_Z_BEHIND && point->z < centre->z + WALRUS_NEAR_Z_AHEAD;
}
CLEAN_AS(func_ov079_02279b5c, Walrus_InBox)
