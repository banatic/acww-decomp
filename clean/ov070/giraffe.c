/* The giraffe of overlay 70: her object, her states and her creation (giraffe.h). */
#include "giraffe.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "clean.h"
#include "giraffe_talk.h"
#include "main/act_effects.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
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

static_assert(sizeof(GiraffeStep) == 0x10, "a state's functions");
static_assert(offsetof(Giraffe, state) == 0x654, "state");
static_assert(offsetof(Giraffe, talk) == 0x658, "talk scene");
static_assert(offsetof(Giraffe, advice_said) == 0x724, "advice said");
static_assert(offsetof(Giraffe, advice_count) == 0x738, "advice count");
static_assert(sizeof(Giraffe) == 0x73c, "the size Giraffe_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define GR_PERSON 0xea          /* u16: its person code */
#define GR_MODEL 0xec           /* LayeredModel */
#define GR_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define GR_FACE 0x2ac           /* SceneFace */
#define GR_ANIM 0x334           /* SpeakerAnim */
#define GR_MOVER 0x350          /* SceneMover */
#define GR_PROBE 0x3a8          /* the probe ahead */
#define GR_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define GR_LOOK 0x3b0           /* SceneLook */
#define GR_TALK_STATE 0x418     /* SceneTalkState */
#define GR_EFFECTS 0x420        /* ActEffects */
#define GR_COLLIDER 0x49c       /* CollisionContacts */
#define GR_CARRIER 0x4cc        /* FieldOwnedBody */
#define GR_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define GR_EMITTER 0x514        /* SoundEmitterObject */
#define GR_FOOTSTEPS 0x558      /* Footsteps */
#define GR_MOTION 0x564         /* SceneMotion */
#define GR_ACTION 0x618         /* SceneAction */
#define GR_HEAP 0x640           /* PoolLink */

#define GR_NO_PERSON 0xfff1
#define GR_HELD 2

/* The field actor of this console's player. */
#define GR_PLAYER_ACTOR 4

/* The codes of her vtable slot 0x4c (main's event_kinds.h): the player's act (the talk) and
 * the event's end. */
#define GR_EVENT_ACT 0
#define GR_EVENT_ENDED 8

/* The talk scene's vtable slot her talks call first. */
#define GR_TALK_SLOT_08 0x08

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov070_02279e4c[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Her states' functions (filled at start-up by __sinit_ov070_02279c50). */
extern GiraffeStep data_ov070_02279f24[GIRAFFE_STATES];
/* Her model's and texture's file names: "npc_sp/model/grf.nsbmd", "npc_sp/model/grf_tex.nsbtx". */
extern const char data_ov070_02279d68[];
extern const char data_ov070_02279d98[];
/* The word her motion requests carry. */
extern u16 data_020c80f8;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static u8 *gr_part(Giraffe *giraffe, u32 offset)
{
    return giraffe->base + offset;
}

static SceneMotion *gr_motion(Giraffe *giraffe)
{
    return (SceneMotion *) (void *) gr_part(giraffe, GR_MOTION);
}

static SceneAction *gr_action(Giraffe *giraffe)
{
    return (SceneAction *) (void *) gr_part(giraffe, GR_ACTION);
}

/* func_ov070_02278a00 (vtable slot 0x40): her talk scene's destructor, then the special
 * character's; the object. */
Giraffe *Giraffe_Destroy(Giraffe *giraffe)
{
    *(const u8 **) (void *) giraffe->base = data_ov070_02279e4c;
    GiraffeTalk_Destroy(&giraffe->talk);
    SpecialSceneObject_DestructBody(giraffe);
    return giraffe;
}
CLEAN_AS(func_ov070_02278a00, Giraffe_Destroy)

/* func_ov070_02278a28 (vtable slot 0x44): the same, then the object freed. */
void *Giraffe_Delete(void *object)
{
    Giraffe *giraffe = object;
    *(const u8 **) (void *) giraffe->base = data_ov070_02279e4c;
    GiraffeTalk_Destroy(&giraffe->talk);
    SpecialSceneObject_DestructBody(giraffe);
    Heap_FreeAux(giraffe);
    return giraffe;
}
CLEAN_AS(func_ov070_02278a28, Giraffe_Delete)

/* func_ov070_02278a54 (vtable slot 0x4c, told of an event about her): code 0, the player's
 * act: her talk scene told through its slot 0x08, the talk's partner this console's player's
 * object, and she talks (state 1); code 8, the event ended: she stands (state 0). The base
 * class is not told. */
void Giraffe_OnEvent(Giraffe *giraffe, int code)
{
    switch (code) {
        case GR_EVENT_ACT: {
            u32 vtable = *(const u32 *) (const void *) &giraffe->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + GR_TALK_SLOT_08);
            ((void (*)(GiraffeTalk *))(uintptr_t) slot)(&giraffe->talk);
            SceneBase_SetMotionArg(&giraffe->talk.base, SceneObject_ActorObject(giraffe->base, GR_PLAYER_ACTOR));
            Giraffe_SetState(giraffe, GIRAFFE_TALKING);
            break;
        }
        case GR_EVENT_ENDED:
            Giraffe_SetState(giraffe, GIRAFFE_STAND);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov070_02278a54, Giraffe_OnEvent)

/* func_ov070_02278a98 (vtable slot 0x48): whether the player may talk to her: her action is
 * idle. */
int Giraffe_MayAct(Giraffe *giraffe)
{
    return !SceneAction_IsBusy(gr_action(giraffe));
}
CLEAN_AS(func_ov070_02278a98, Giraffe_MayAct)

/* func_ov070_02279904 (state 1's entry): she turns to the talk's partner (to angle 0 without
 * one) and talks. 1. */
int Giraffe_EnterTalk(Giraffe *giraffe)
{
    int partner = SceneBase_MotionArg(&giraffe->talk.base);
    int angle = 0;
    if (partner != 0) {
        angle = SceneObject_YawTo(giraffe->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(gr_action(giraffe), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov070_02279904, Giraffe_EnterTalk)

/* func_ov070_0227993c (state 0's update): nothing. 1. */
int Giraffe_UpdateStand(void)
{
    return 1;
}
CLEAN_AS(func_ov070_0227993c, Giraffe_UpdateStand)

/* func_ov070_02279940 (state 0's entry): her motion of kind 0 asked for (priority 1). 1. */
int Giraffe_EnterStand(Giraffe *giraffe)
{
    SceneMotion_Request(gr_motion(giraffe), 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov070_02279940, Giraffe_EnterStand)

/* func_ov070_022798d4 (state 2's update): nothing. 1. */
int Giraffe_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov070_022798d4, Giraffe_UpdateTalked)

/* func_ov070_022798d8 (state 1's update): once her action is idle, the object's event ends and
 * state 2 follows. 1. */
int Giraffe_UpdateTalk(Giraffe *giraffe)
{
    if (!SceneAction_IsBusy(gr_action(giraffe))) {
        EventQueue_FinishObjectEvent(giraffe);
        Giraffe_SetState(giraffe, GIRAFFE_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov070_022798d8, Giraffe_UpdateTalk)

/* func_ov070_02279974: state `state` taken when its entry function, if it has one, answers 1
 * (not merely nonzero).
 * REQUIRES: `state` is 0 to 2 (the table is not bounded). */
void Giraffe_SetState(Giraffe *giraffe, int state)
{
    const GiraffeStep *step = &data_ov070_02279f24[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, giraffe);
    }
    if (taken == 1) {
        giraffe->state = state;
    }
}
CLEAN_AS(func_ov070_02279974, Giraffe_SetState)

/* func_ov070_022799b8 (vtable slot 0x68, each frame): her state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: her state is 0 to 2. */
int Giraffe_Update(Giraffe *giraffe)
{
    const GiraffeStep *step = &data_ov070_02279f24[giraffe->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, giraffe);
}
CLEAN_AS(func_ov070_022799b8, Giraffe_Update)

/* func_ov070_02279a04 (vtable slot 0x70): her model's file name, "npc_sp/model/grf.nsbmd". */
int Giraffe_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov070_02279d68;
}
CLEAN_AS(func_ov070_02279a04, Giraffe_ModelName)

/* func_ov070_02279a0c (vtable slot 0x6c): her texture's file name,
 * "npc_sp/model/grf_tex.nsbtx". */
int Giraffe_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov070_02279d98;
}
CLEAN_AS(func_ov070_02279a0c, Giraffe_TextureName)

/* func_ov070_02279a14 (vtable slot 0x00, her start): unless the special character refuses to
 * start, she stands (state 0) and is held (flag 2 at 0x4e8), with no advice said in a row.
 * Whether she started. */
int Giraffe_Start(Giraffe *giraffe)
{
    if (SpecialSceneObject_Start(giraffe) == 0) {
        return 0;
    }
    Giraffe_SetState(giraffe, GIRAFFE_STAND);
    *(u32 *) (void *) gr_part(giraffe, GR_HELD_FLAGS) |= GR_HELD;
    giraffe->advice_count = 0;
    return 1;
}
CLEAN_AS(func_ov070_02279a14, Giraffe_Start)

/* func_ov070_02279a50 (vtable slot 0x04, her set-up): unless the special character refuses,
 * her talk scene becomes her scene and gets her as its owner, and no advice is marked said.
 * Whether she was set up. */
int Giraffe_Init(Giraffe *giraffe)
{
    if (SpecialSceneObject_Init(giraffe) == 0) {
        return 0;
    }
    SceneObject_SetScene(giraffe->base, &giraffe->talk.base);
    GiraffeTalk_Begin(&giraffe->talk, giraffe);
    MI_CpuFill8(giraffe->advice_said, 0, GIRAFFE_ADVICE_LINES);
    return 1;
}
CLEAN_AS(func_ov070_02279a50, Giraffe_Init)

/* func_ov070_02279a90 (the create function her record at 0x02279d80 names): a zeroed block of
 * 0x73c bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *Giraffe_Create(void)
{
    Giraffe *giraffe = (Giraffe *) Heap_AllocAuxZeroed(sizeof(Giraffe));
    if (giraffe == NULL) {
        return NULL;
    }
    u8 *object = giraffe->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) gr_part(giraffe, GR_PERSON) = GR_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) gr_part(giraffe, GR_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) gr_part(giraffe, GR_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) gr_part(giraffe, GR_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) gr_part(giraffe, GR_ANIM));
    SceneMover_Construct((SceneMover *) (void *) gr_part(giraffe, GR_MOVER));
    SceneProbe_Construct(gr_part(giraffe, GR_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) gr_part(giraffe, GR_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) gr_part(giraffe, GR_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) gr_part(giraffe, GR_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) gr_part(giraffe, GR_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) gr_part(giraffe, GR_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) gr_part(giraffe, GR_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) gr_part(giraffe, GR_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) gr_part(giraffe, GR_FOOTSTEPS));
    SceneMotion_Construct(gr_motion(giraffe));
    SceneAction_Construct(gr_action(giraffe));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) gr_part(giraffe, GR_HEAP));
    *(const u8 **) (void *) object = data_ov070_02279e4c;
    GiraffeTalk_Construct(&giraffe->talk);
    return giraffe;
}
CLEAN_AS(func_ov070_02279a90, Giraffe_Create)
