/* The special character drawn with the model tti (tti_npc.h). */
#include "tti_npc.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "main/activity_job.h"
#include "main/pool_link.h"
#include "main/scene_object_members.h"
#include "main/scene_probe.h"
#include "main/scene_value_3aa.h"
#include "main/special_scene_object.h"

static_assert(sizeof(TtiNpcStep) == 0x10, "a state's functions");
static_assert(offsetof(TtiNpc, state) == 0x654, "state");
static_assert(offsetof(TtiNpc, countdown) == 0x658, "countdown");
static_assert(sizeof(TtiNpc) == 0x65c, "the size func_ov004_02225cd4 allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h and scene_object_members.h). */
#define TTI_NPC_MODEL_END 0x18c      /* u32: its model's animation's frame count, 20.12 */
#define TTI_NPC_MODEL_FRAME 0x190    /* u32: its model's animation's frame, 20.12 */
#define TTI_NPC_PERSON 0xea          /* u16: its person code */
#define TTI_NPC_MODEL 0xec           /* LayeredModel */
#define TTI_NPC_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TTI_NPC_FACE 0x2ac           /* SceneFace */
#define TTI_NPC_ANIM 0x334           /* SpeakerAnim */
#define TTI_NPC_MOVER 0x350          /* SceneMover */
#define TTI_NPC_PROBE 0x3a8
#define TTI_NPC_VALUE_3AA 0x3aa  /* SceneValue3aa */
#define TTI_NPC_LOOK 0x3b0       /* SceneLook */
#define TTI_NPC_TALK_STATE 0x418 /* SceneTalkState */
#define TTI_NPC_EFFECTS 0x420    /* ActEffects */
#define TTI_NPC_COLLIDER 0x49c   /* CollisionContacts */
#define TTI_NPC_CARRIER 0x4cc    /* FieldOwnedBody */
#define TTI_NPC_HELD_FLAGS 0x4e8 /* u32: the scene object's flags (2: held) */
#define TTI_NPC_SOLID 0x510      /* u8: it collides and moves with its carrier */
#define TTI_NPC_EMITTER 0x514    /* SoundEmitterObject */
#define TTI_NPC_FOOTSTEPS 0x558  /* Footsteps */
#define TTI_NPC_MOTION 0x564     /* SceneMotion */
#define TTI_NPC_ACTION 0x618     /* SceneAction */
#define TTI_NPC_HEAP 0x640       /* PoolLink */

static_assert(0xec + offsetof(LayeredModel, base.frames) + offsetof(FrameCtrl, end) == TTI_NPC_MODEL_END, "frame count");
static_assert(0xec + offsetof(LayeredModel, base.frames) + offsetof(FrameCtrl, frame) == TTI_NPC_MODEL_FRAME, "frame");

#define TTI_NPC_NO_PERSON 0xfff1
#define TTI_NPC_HELD 2

/* The animation player's number of the standard animation (SpeakerAnim_IsBody). */
#define TTI_NPC_STANDARD 0xff
/* Its gesture's two animations, played once (mode 1, priority 1). */
#define TTI_NPC_GESTURE_FIRST 0x100
#define TTI_NPC_GESTURE_SECOND 0x101
#define TTI_NPC_GESTURE_MODE 1
/* Its motion's stand (main's scene_motion_request.h). */
#define TTI_NPC_MOTION_STAND 0
/* How many times its animation reaches its last frame before a gesture. */
#define TTI_NPC_COUNTDOWN 10

/* The started one, or null. */
extern TtiNpc *data_ov004_02258200;
/* The functions of its states (filled at start-up by __sinit_ov004_0224e968). */
extern TtiNpcStep data_ov004_02258204[TTI_NPC_STATES];
/* The vtables of the class and of a class it derives from. */
extern const u8 data_ov004_02254a38[];
extern const u8 data_020da088[];
/* Its model's and texture's file names. */
extern const char data_ov004_022549e4[];
extern const char data_ov004_02254a14[];
/* The word its motion requests carry. */
extern u16 data_020c80f8;

static u8 *tti_part(TtiNpc *npc, u32 offset)
{
    return npc->base + offset;
}

static SceneMotion *tti_motion_of(TtiNpc *npc)
{
    return (SceneMotion *) (void *) tti_part(npc, TTI_NPC_MOTION);
}

/* Whether its animation player plays the animation `number`. */
static int tti_plays(TtiNpc *npc, int number)
{
    return SpeakerAnim_IsBody((SpeakerAnim *) (void *) tti_part(npc, TTI_NPC_ANIM), number,
                              tti_part(npc, TTI_NPC_STANDARD_ANIMS));
}

/* The whole frame of a 20.12 frame word of its model, cut to 16 bits. */
static u32 tti_whole_frame(TtiNpc *npc, u32 offset)
{
    return (*(const u32 *) (const void *) tti_part(npc, offset) << 4) >> 16;
}

/* func_ov004_022259dc (vtable slot 0x40): the special character's destructor; the object. */
TtiNpc *TtiNpc_Destroy(TtiNpc *npc)
{
    *(const u8 **) (void *) npc->base = data_ov004_02254a38;
    SpecialSceneObject_DestructBody(npc);
    return npc;
}
CLEAN_AS(func_ov004_022259dc, TtiNpc_Destroy)

/* func_ov004_022259f4 (vtable slot 0x44): the same, then the object freed. */
TtiNpc *TtiNpc_Delete(TtiNpc *npc)
{
    *(const u8 **) (void *) npc->base = data_ov004_02254a38;
    SpecialSceneObject_DestructBody(npc);
    Heap_FreeAux(npc);
    return npc;
}
CLEAN_AS(func_ov004_022259f4, TtiNpc_Delete)

/* func_ov004_02225a14: whether the started one, if any, stands (state 0) playing its standard
 * animation; 1 when none is started. */
int TtiNpc_IsIdle(void)
{
    TtiNpc *npc = data_ov004_02258200;
    if (npc == NULL) {
        return 1;
    }
    if (tti_plays(npc, TTI_NPC_STANDARD) && data_ov004_02258200->state == TTI_NPC_STAND) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_02225a14, TtiNpc_IsIdle)

/* func_ov004_02225a60 (state 1's update): once the gesture's first animation is done its
 * second is played; once that is done it stands (state 0). 1. */
int TtiNpc_UpdateGesture(TtiNpc *npc)
{
    if (tti_plays(npc, TTI_NPC_GESTURE_FIRST) && SceneMotion_IsDone(tti_motion_of(npc))) {
        SceneMotion_RequestAnimation(tti_motion_of(npc), 1, TTI_NPC_GESTURE_SECOND, TTI_NPC_GESTURE_MODE, data_020c80f8, 0);
    }
    if (tti_plays(npc, TTI_NPC_GESTURE_SECOND) && SceneMotion_IsDone(tti_motion_of(npc))) {
        TtiNpc_SetState(npc, TTI_NPC_STAND);
    }
    return 1;
}
CLEAN_AS(func_ov004_02225a60, TtiNpc_UpdateGesture)

/* func_ov004_02225ae4 (state 1's entry): the gesture's first animation is played. 1. */
int TtiNpc_EnterGesture(TtiNpc *npc)
{
    SceneMotion_RequestAnimation(tti_motion_of(npc), 1, TTI_NPC_GESTURE_FIRST, TTI_NPC_GESTURE_MODE, data_020c80f8, 0);
    return 1;
}
CLEAN_AS(func_ov004_02225ae4, TtiNpc_EnterGesture)

/* func_ov004_02225b14 (state 0's update): at the last whole frame of its model's animation the
 * countdown runs down; once it is out and no job of the activities runs, the gesture (state
 * 1). 1.
 * QUIRK: the frames are compared as their whole parts cut to 16 bits, the count less one in
 * 32 bits (so a count of 0 never matches). */
int TtiNpc_UpdateStand(TtiNpc *npc)
{
    u32 frame = tti_whole_frame(npc, TTI_NPC_MODEL_FRAME);
    u32 end = tti_whole_frame(npc, TTI_NPC_MODEL_END);
    if (frame == end - 1 && Countdown_Tick8(&npc->countdown) == 0 && ActivityJob_IsIdle()) {
        TtiNpc_SetState(npc, TTI_NPC_GESTURE);
    }
    return 1;
}
CLEAN_AS(func_ov004_02225b14, TtiNpc_UpdateStand)

/* func_ov004_02225b60 (state 0's entry): it stands (priority 1) and the countdown starts at
 * 10. 1. */
int TtiNpc_EnterStand(TtiNpc *npc)
{
    SceneMotion_Request(tti_motion_of(npc), TTI_NPC_MOTION_STAND, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    npc->countdown = TTI_NPC_COUNTDOWN;
    return 1;
}
CLEAN_AS(func_ov004_02225b60, TtiNpc_EnterStand)

/* func_ov004_02225ba4: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 or 1 (the table is not bounded). */
void TtiNpc_SetState(TtiNpc *npc, int state)
{
    const TtiNpcStep *step = &data_ov004_02258204[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, npc);
    }
    if (taken != 0) {
        npc->state = state;
    }
}
CLEAN_AS(func_ov004_02225ba4, TtiNpc_SetState)

/* func_ov004_02225be8 (vtable slot 0x68, each frame): its state's update when it has one (its
 * answer), else 0.
 * REQUIRES: its state is 0 or 1. */
int TtiNpc_Update(TtiNpc *npc)
{
    const TtiNpcStep *step = &data_ov004_02258204[(u32) npc->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, npc);
}
CLEAN_AS(func_ov004_02225be8, TtiNpc_Update)

/* func_ov004_02225c34 (vtable slot 0x70): its model's file name, "npc_sp/model/tti.nsbmd". */
const char *TtiNpc_ModelName(void)
{
    return data_ov004_022549e4;
}
CLEAN_AS(func_ov004_02225c34, TtiNpc_ModelName)

/* func_ov004_02225c3c (vtable slot 0x6c): its texture's file name,
 * "npc_sp/model/tti_tex.nsbtx". */
const char *TtiNpc_TextureName(void)
{
    return data_ov004_02254a14;
}
CLEAN_AS(func_ov004_02225c3c, TtiNpc_TextureName)

/* func_ov004_02225c44 (vtable slot 0x0c): when the special character may leave, it is no
 * longer the one started. Whether it may. */
int TtiNpc_Leave(TtiNpc *npc)
{
    if (SpecialSceneObject_Leave(npc) == 0) {
        return 0;
    }
    data_ov004_02258200 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_02225c44, TtiNpc_Leave)

/* func_ov004_02225c68 (vtable slot 0x00, its start): unless the special character refuses to
 * start, it is the one started, stands, is held (flag 2 at 0x4e8) and is not solid. Whether it
 * started. */
int TtiNpc_Start(TtiNpc *npc)
{
    if (SpecialSceneObject_Start(npc) == 0) {
        return 0;
    }
    data_ov004_02258200 = npc;
    TtiNpc_SetState(npc, TTI_NPC_STAND);
    *(u32 *) (void *) tti_part(npc, TTI_NPC_HELD_FLAGS) |= TTI_NPC_HELD;
    *tti_part(npc, TTI_NPC_SOLID) = 0;
    return 1;
}
CLEAN_AS(func_ov004_02225c68, TtiNpc_Start)

/* func_ov004_02225cac (vtable slot 0x04, its set-up): unless the special character refuses,
 * its first standard animation is 0xff. Whether it was set up. */
int TtiNpc_Init(TtiNpc *npc)
{
    if (SpecialSceneObject_Init(npc) == 0) {
        return 0;
    }
    SceneStandardAnims_SetFirst((SceneStandardAnims *) (void *) tti_part(npc, TTI_NPC_STANDARD_ANIMS), TTI_NPC_STANDARD);
    return 1;
}
CLEAN_AS(func_ov004_02225cac, TtiNpc_Init)

/* func_ov004_02225cd4: a zeroed block of 0x65c bytes from the auxiliary heap, constructed: the
 * scene object base, the class 0x020d8c64's vtable and members in place order (no person yet,
 * 0xfff1), the class 0x020da088's vtable and heap link, then the class's vtable. Null when
 * there is no room. */
TtiNpc *TtiNpc_Create(void)
{
    TtiNpc *npc = (TtiNpc *) Heap_AllocAuxZeroed(sizeof(TtiNpc));
    if (npc == NULL) {
        return NULL;
    }
    u8 *object = npc->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) tti_part(npc, TTI_NPC_PERSON) = TTI_NPC_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) tti_part(npc, TTI_NPC_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) tti_part(npc, TTI_NPC_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) tti_part(npc, TTI_NPC_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) tti_part(npc, TTI_NPC_ANIM));
    SceneMover_Construct((SceneMover *) (void *) tti_part(npc, TTI_NPC_MOVER));
    SceneProbe_Construct(tti_part(npc, TTI_NPC_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) tti_part(npc, TTI_NPC_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) tti_part(npc, TTI_NPC_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) tti_part(npc, TTI_NPC_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) tti_part(npc, TTI_NPC_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) tti_part(npc, TTI_NPC_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) tti_part(npc, TTI_NPC_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) tti_part(npc, TTI_NPC_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) tti_part(npc, TTI_NPC_FOOTSTEPS));
    SceneMotion_Construct(tti_motion_of(npc));
    SceneAction_Construct((SceneAction *) (void *) tti_part(npc, TTI_NPC_ACTION));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) tti_part(npc, TTI_NPC_HEAP));
    *(const u8 **) (void *) object = data_ov004_02254a38;
    return npc;
}
CLEAN_AS(func_ov004_02225cd4, TtiNpc_Create)
