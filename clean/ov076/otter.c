/* The otter (otter.h): his object's vtable slots and his states. */
#include "otter.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/act_effects.h"
#include "main/effect_system.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_share.h"
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/sound_emitter.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/talk_checks.h"
#include "otter_talk.h"
#include "ov003/fish_shadow.h"

static_assert(offsetof(Otter, state) == 0x654 && offsetof(Otter, talk) == 0x658, "Otter");
static_assert(offsetof(Otter, gave) == 0x71c && offsetof(Otter, turn_angle) == 0x71e, "Otter");
static_assert(offsetof(Otter, dive_height) == 0x720 && offsetof(Otter, spin) == 0x724, "Otter");
static_assert(sizeof(Otter) == 0x728, "the size Otter_Create allocates");
static_assert(sizeof(OtterStep) == 0x10, "a state's functions");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define OTTER_POSITION 0x5c        /* Vec3: where he is */
#define OTTER_HEIGHT 0x64          /* fx32: the position's y */
#define OTTER_ANGLE 0x8e           /* s16: where he faces */
#define OTTER_WALK_ANGLE 0x94      /* s16: where he walks */
#define OTTER_PERSON 0xea          /* u16: his person code */
#define OTTER_MODEL 0xec           /* LayeredModel */
#define OTTER_MODEL_FRAME 0x190    /* fx32: his model's animation frame, 20.12 */
#define OTTER_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define OTTER_FACE 0x2ac           /* SceneFace */
#define OTTER_ANIM 0x334           /* SpeakerAnim */
#define OTTER_MOVER 0x350          /* SceneMover */
#define OTTER_PROBE 0x3a8          /* the probe */
#define OTTER_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define OTTER_LOOK 0x3b0           /* SceneLook */
#define OTTER_TALK_STATE 0x418     /* SceneTalkState */
#define OTTER_EFFECTS 0x420        /* ActEffects */
#define OTTER_COLLIDER 0x49c       /* CollisionContacts */
#define OTTER_CARRIER 0x4cc        /* FieldOwnedBody */
#define OTTER_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define OTTER_SOLID 0x510          /* u8: it collides and moves with its carrier */
#define OTTER_SHADOW 0x511         /* u8: its shadow is drawn */
#define OTTER_EMITTER 0x514        /* SoundEmitterObject */
#define OTTER_FOOTSTEPS 0x558      /* Footsteps */
#define OTTER_MOTION 0x564         /* SceneMotion */
#define OTTER_ACTION 0x618         /* SceneAction */
#define OTTER_HEAP 0x640           /* PoolLink */

#define OTTER_NO_PERSON 0xfff1
#define OTTER_HELD 2

/* The field actor of this console's player. */
#define OTTER_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player talked to him, the
 * event ended. */
#define OTTER_EVENT_TALK 0
#define OTTER_EVENT_ENDED 8

/* The vtable slot of his talk scene that resets it (OtterTalk_Reset). */
#define OTTER_SLOT_RESET 0x08

/* The current player's daily bit of a talk with him. */
#define OTTER_DAILY_BIT 0x18

/* His motions (scene_motion_request.h): a stand and a turn; animations 0xf9 (the dive, played
 * once: mode 1) and 0xfa (played on: mode 0). */
#define OTTER_MOTION_STAND 0
#define OTTER_MOTION_TURN 3
#define OTTER_ANIM_DIVE 0xf9
#define OTTER_ANIM_GONE 0xfa
#define OTTER_ANIM_ONCE 1
#define OTTER_ANIM_LOOP 0

/* Half a turn. */
#define OTTER_HALF_TURN 0x8000

/* The dive's sounds and their volume, its frames (whole) and the splash. */
#define OTTER_SOUND_DIVE 0x814
#define OTTER_SOUND_SPLASH 0x7ed
#define OTTER_SOUND_VOLUME 0x7f
#define OTTER_FRAME_SUBMERGE 0x0b
#define OTTER_FRAME_SPLASH 0x1b
#define OTTER_SPLASH_EFFECT 0x16
#define OTTER_SPLASH_AHEAD 0x3800 /* 3.5 along z */
#define OTTER_SPLASH_REACH 0x5000 /* 5.0: the fish scared */
#define OTTER_SPIN_DIVISOR 6

/* How he rises once gone: 4.0 at once, then 0xeb a frame, up to 20.0 above where he dove. */
#define OTTER_RISE_FIRST 0x4000
#define OTTER_RISE_STEP 0xeb
#define OTTER_RISE_LIMIT 0x14000

/* The vtables of his class and of the classes he derives from. */
extern const u8 data_ov076_022797d4[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His model and texture file names: "npc_sp/model/seo.nsbmd", "npc_sp/model/seo_tex.nsbtx". */
extern const char data_ov076_022796f0[];
extern const char data_ov076_02279720[];
/* The functions of his states (filled at start-up by __sinit_ov076_022795ac). */
extern OtterStep data_ov076_0227988c[OTTER_STATES];
/* The word his motion requests carry, the player's position (or where it would be), and the
 * range of a look. */
extern u16 data_020c80f8;
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;

static u8 *otter_part(Otter *otter, u32 offset)
{
    return otter->base + offset;
}

static SceneMotion *otter_motion(Otter *otter)
{
    return (SceneMotion *) (void *) otter_part(otter, OTTER_MOTION);
}

static SceneAction *otter_action(Otter *otter)
{
    return (SceneAction *) (void *) otter_part(otter, OTTER_ACTION);
}

static SceneMover *otter_mover(Otter *otter)
{
    return (SceneMover *) (void *) otter_part(otter, OTTER_MOVER);
}

static SpeakerAnim *otter_anim(Otter *otter)
{
    return (SpeakerAnim *) (void *) otter_part(otter, OTTER_ANIM);
}

static SoundEmitter *otter_emitter(Otter *otter)
{
    return (SoundEmitter *) (void *) otter_part(otter, OTTER_EMITTER);
}

static s16 *otter_angle(Otter *otter)
{
    return (s16 *) (void *) otter_part(otter, OTTER_ANGLE);
}

static s16 *otter_walk_angle(Otter *otter)
{
    return (s16 *) (void *) otter_part(otter, OTTER_WALK_ANGLE);
}

static s32 *otter_height(Otter *otter)
{
    return (s32 *) (void *) otter_part(otter, OTTER_HEIGHT);
}

/* The whole frame of his model's animation, cut to 16 bits. */
static u32 otter_whole_frame(Otter *otter)
{
    return (*(const u32 *) (const void *) otter_part(otter, OTTER_MODEL_FRAME) >> 12) & 0xffff;
}

/* ---- His object */

/* func_ov076_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
Otter *Otter_Destruct(Otter *otter)
{
    *(const u8 **) (void *) otter->base = data_ov076_022797d4;
    OtterTalk_Destruct(&otter->talk);
    SpecialSceneObject_DestructBody(otter);
    return otter;
}
CLEAN_AS(func_ov076_02278a00, Otter_Destruct)

/* func_ov076_02278a28 (vtable slot 0x44): the same, then the object freed. */
Otter *Otter_DestructDelete(Otter *otter)
{
    *(const u8 **) (void *) otter->base = data_ov076_022797d4;
    OtterTalk_Destruct(&otter->talk);
    SpecialSceneObject_DestructBody(otter);
    Heap_FreeAux(otter);
    return otter;
}
CLEAN_AS(func_ov076_02278a28, Otter_DestructDelete)

/* func_ov076_02278a54 (vtable slot 0x4c, an event about him): when the player talked to him,
 * his talk scene is reset and given the player's field actor, and he talks (state 1); once the
 * event ended he dives (state 4) when he gave something, else turns back (state 3). */
void Otter_OnEvent(Otter *otter, int code)
{
    switch (code) {
        case OTTER_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &otter->talk;
            u32 reset = *(const u32 *) (uintptr_t) (vtable + OTTER_SLOT_RESET);
            ((void (*)(OtterTalk *))(uintptr_t) reset)(&otter->talk);
            SceneBase_SetMotionArg(&otter->talk.base, SceneObject_ActorObject(otter->base, OTTER_PLAYER_ACTOR));
            Otter_SetState(otter, OTTER_TALK);
            break;
        }
        case OTTER_EVENT_ENDED:
            Otter_SetState(otter, otter->gave != 0 ? OTTER_DIVE : OTTER_TURN);
            break;
    }
}
CLEAN_AS(func_ov076_02278a54, Otter_OnEvent)

/* func_ov076_02278aac (vtable slot 0x48): the player may talk to him unless he gave something
 * or the current player talked to him today, while his action is idle. */
int Otter_AgreesToTalk(Otter *otter)
{
    if (otter->gave != 0) {
        return 0;
    }
    if (TalkChecks_TestSetDailyBit(OTTER_DAILY_BIT, 0) == 1) {
        return 0;
    }
    return SceneAction_IsBusy(otter_action(otter)) == 0;
}
CLEAN_AS(func_ov076_02278aac, Otter_AgreesToTalk)

/* func_ov076_02279370: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 5 (the table is not bounded); him at a word-aligned address, as
 * every object of the game (the ROM's store drops the low two bits). */
void Otter_SetState(Otter *otter, int state)
{
    const OtterStep *step = &data_ov076_0227988c[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, otter);
    }
    if (taken != 0) {
        otter->state = state;
    }
}
CLEAN_AS(func_ov076_02279370, Otter_SetState)

/* func_ov076_022793b4 (vtable slot 0x68, each frame): his state's update when it has one (its
 * answer is the result, else 0).
 * REQUIRES: his state is 0 to 5. */
int Otter_Update(Otter *otter)
{
    const OtterStep *step = &data_ov076_0227988c[otter->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, otter);
}
CLEAN_AS(func_ov076_022793b4, Otter_Update)

/* func_ov076_02279400 (vtable slot 0x70): his model's file name. */
int Otter_ModelName(void)
{
    return (int) (uintptr_t) data_ov076_022796f0;
}
CLEAN_AS(func_ov076_02279400, Otter_ModelName)

/* func_ov076_02279408 (vtable slot 0x6c): his texture's file name. */
int Otter_TextureName(void)
{
    return (int) (uintptr_t) data_ov076_02279720;
}
CLEAN_AS(func_ov076_02279408, Otter_TextureName)

/* func_ov076_02279410 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he is held, notes the angle he faces and stands (state 0). Whether he started.
 * REQUIRES: him at a word-aligned address (his flags are a word). */
int Otter_Start(Otter *otter)
{
    if (SpecialSceneObject_Start(otter) == 0) {
        return 0;
    }
    *(u32 *) (void *) otter_part(otter, OTTER_HELD_FLAGS) |= OTTER_HELD;
    otter->turn_angle = *otter_angle(otter);
    Otter_SetState(otter, OTTER_STAND);
    return 1;
}
CLEAN_AS(func_ov076_02279410, Otter_Start)

/* func_ov076_0227944c (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int Otter_Init(Otter *otter)
{
    if (SpecialSceneObject_Init(otter) == 0) {
        return 0;
    }
    SceneObject_SetScene(otter->base, &otter->talk.base);
    OtterTalk_Begin(&otter->talk, otter);
    return 1;
}
CLEAN_AS(func_ov076_0227944c, Otter_Init)

/* func_ov076_0227947c (his record's create function): a zeroed block of 0x728 bytes from the
 * auxiliary heap, constructed: the scene object base, the class 0x020d8c64's vtable and members
 * in place order (no person yet, 0xfff1), the class 0x020da088's vtable and heap link, then his
 * class's vtable and his talk scene. Null when there is no room. */
void *Otter_Create(void)
{
    Otter *otter = (Otter *) Heap_AllocAuxZeroed(sizeof(Otter));
    if (otter == NULL) {
        return NULL;
    }
    u8 *object = otter->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) otter_part(otter, OTTER_PERSON) = OTTER_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) otter_part(otter, OTTER_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) otter_part(otter, OTTER_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) otter_part(otter, OTTER_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct(otter_anim(otter));
    SceneMover_Construct(otter_mover(otter));
    SceneProbe_Construct(otter_part(otter, OTTER_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) otter_part(otter, OTTER_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) otter_part(otter, OTTER_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) otter_part(otter, OTTER_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) otter_part(otter, OTTER_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) otter_part(otter, OTTER_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) otter_part(otter, OTTER_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) otter_part(otter, OTTER_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) otter_part(otter, OTTER_FOOTSTEPS));
    SceneMotion_Construct(otter_motion(otter));
    SceneAction_Construct(otter_action(otter));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) otter_part(otter, OTTER_HEAP));
    *(const u8 **) (void *) object = data_ov076_022797d4;
    OtterTalk_Construct(&otter->talk);
    return otter;
}
CLEAN_AS(func_ov076_0227947c, Otter_Create)

/* ---- His states */

/* func_ov076_0227933c (state 0's entry): he stands (priority 1, the plain word). 1. */
int Otter_EnterStand(Otter *otter)
{
    SceneMotion_Request(otter_motion(otter), OTTER_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov076_0227933c, Otter_EnterStand)

/* func_ov076_02279338 (state 0's update): 1. */
int Otter_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov076_02279338, Otter_UpdateStand)

/* func_ov076_02279300 (state 1's entry): he turns to his talk's partner (when it has one, else
 * to angle 0) and talks. 1. */
int Otter_EnterTalk(Otter *otter)
{
    int partner = SceneBase_MotionArg(&otter->talk.base);
    int yaw = 0;
    if (partner != 0) {
        yaw = SceneObject_YawTo(otter->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(otter_action(otter), 0, yaw, 0);
    return 1;
}
CLEAN_AS(func_ov076_02279300, Otter_EnterTalk)

/* func_ov076_022792d4 (state 1's update): once his action is idle, his event is finished and
 * he has talked (state 2). 1. */
int Otter_UpdateTalk(Otter *otter)
{
    if (SceneAction_IsBusy(otter_action(otter)) == 0) {
        EventQueue_FinishObjectEvent(otter);
        Otter_SetState(otter, OTTER_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov076_022792d4, Otter_UpdateTalk)

/* func_ov076_022792d0 (state 2's update): 1. */
int Otter_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov076_022792d0, Otter_UpdateTalked)

/* func_ov076_02279278 (state 3's entry): he turns (priority 1) to the angle he started with,
 * half a turn further first when he gave something. 1. */
int Otter_EnterTurn(Otter *otter)
{
    if (otter->gave == 1) {
        otter->turn_angle = (s16) (otter->turn_angle + OTTER_HALF_TURN);
    }
    SceneMotion_Request(otter_motion(otter), OTTER_MOTION_TURN, 1, 0, 0, 0, otter->turn_angle, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov076_02279278, Otter_EnterTurn)

/* func_ov076_02279230 (state 3's update): once his turn is done he stands (state 0), or dives
 * (state 4) when he gave something. 1. */
int Otter_UpdateTurn(Otter *otter)
{
    if (SceneMotion_Kind(otter_motion(otter)) == OTTER_MOTION_TURN && SceneMotion_IsDone(otter_motion(otter)) != 0) {
        Otter_SetState(otter, otter->gave == 0 ? OTTER_STAND : OTTER_DIVE);
    }
    return 1;
}
CLEAN_AS(func_ov076_02279230, Otter_UpdateTurn)

/* func_ov076_02279178 (state 4's entry): animation 0xf9 once (priority 1) and sound 0x814; he
 * faces and walks half a turn about; his spin back to angle 0 is a sixth of that angle a frame;
 * his head looks ahead (kind 0, with the player's position and actor 4 given); his height is
 * noted. 1. */
int Otter_EnterDive(Otter *otter)
{
    SceneMotion_RequestAnimation(otter_motion(otter), 1, OTTER_ANIM_DIVE, OTTER_ANIM_ONCE, 0, 0);
    SoundEmitter_Play(otter_emitter(otter), OTTER_SOUND_DIVE, OTTER_SOUND_VOLUME, 0);
    s16 *angle = otter_angle(otter);
    *angle = (s16) (*angle + OTTER_HALF_TURN);
    *otter_walk_angle(otter) = *angle;
    SceneMover_SetAngle(otter_mover(otter), *angle);
    int spin = -(*angle / OTTER_SPIN_DIVISOR);
    if (spin < 0) {
        spin = -spin;
    }
    otter->spin = (u16) spin;
    SceneLook_Request((SceneLook *) (void *) otter_part(otter, OTTER_LOOK), SCENE_LOOK_NONE, 0, 0, &data_021fbee8,
                      OTTER_PLAYER_ACTOR, data_020c814c, 1);
    otter->dive_height = *otter_height(otter);
    return 1;
}
CLEAN_AS(func_ov076_02279178, Otter_EnterDive)

/* func_ov076_0227908c (state 4's update): see otter.h. At the end of animation 0xf9 he is gone
 * (state 5); else at its frame 0xb he stops being solid and loses his shadow; he spins towards
 * angle 0; at frame 0x1b the splash. Each frame he walks the way he faces. 1. */
int Otter_UpdateDive(Otter *otter)
{
    s16 *angle = otter_angle(otter);

    if (SpeakerAnim_Number(otter_anim(otter), 0) == OTTER_ANIM_DIVE &&
        SpeakerAnim_BodyAtEnd(otter_anim(otter), otter->base) != 0) {
        Otter_SetState(otter, OTTER_GONE);
    } else {
        if (SpeakerAnim_Number(otter_anim(otter), 0) == OTTER_ANIM_DIVE && otter_whole_frame(otter) == OTTER_FRAME_SUBMERGE) {
            *otter_part(otter, OTTER_SHADOW) = 0;
            *otter_part(otter, OTTER_SOLID) = 0;
        }
        Approach_S16Wrapped(angle, 0, (s16) otter->spin);
        if (otter_whole_frame(otter) == OTTER_FRAME_SPLASH) {
            Vec3 splash = *(const Vec3 *) (const void *) otter_part(otter, OTTER_POSITION);
            splash.y = 0;
            splash.z += OTTER_SPLASH_AHEAD;
            FishShadow_ScareNear(&splash, OTTER_SPLASH_REACH);
            EffectSystem_StartKind(OTTER_SPLASH_EFFECT, &splash, NULL, NULL);
            SoundEmitter_Play(otter_emitter(otter), OTTER_SOUND_SPLASH, OTTER_SOUND_VOLUME, 0);
        }
    }
    *otter_walk_angle(otter) = *angle;
    SceneMover_SetAngle(otter_mover(otter), *angle);
    return 1;
}
CLEAN_AS(func_ov076_0227908c, Otter_UpdateDive)

/* func_ov076_02279034 (state 5's entry): animation 0xfa (priority 1, played on), his head
 * locked, angle 0 faced and walked, and he rises 4.0. 1. */
int Otter_EnterGone(Otter *otter)
{
    SceneMotion_RequestAnimation(otter_motion(otter), 1, OTTER_ANIM_GONE, OTTER_ANIM_LOOP, 0, 0);
    SceneLook_Lock((SceneLook *) (void *) otter_part(otter, OTTER_LOOK));
    *otter_angle(otter) = 0;
    *otter_walk_angle(otter) = 0;
    SceneMover_SetAngle(otter_mover(otter), 0);
    *otter_height(otter) += OTTER_RISE_FIRST;
    return 1;
}
CLEAN_AS(func_ov076_02279034, Otter_EnterGone)

/* func_ov076_02278fec (state 5's update): angle 0 kept; he rises 0xeb, and once he is more
 * than 20.0 above where he dove he is deleted. 1. */
int Otter_UpdateGone(Otter *otter)
{
    *otter_walk_angle(otter) = 0;
    *otter_angle(otter) = 0;
    SceneMover_SetAngle(otter_mover(otter), 0);
    *otter_height(otter) += OTTER_RISE_STEP;
    if (*otter_height(otter) > otter->dive_height + OTTER_RISE_LIMIT) {
        Process_RequestDelete((Process *) (void *) otter);
    }
    return 1;
}
CLEAN_AS(func_ov076_02278fec, Otter_UpdateGone)
