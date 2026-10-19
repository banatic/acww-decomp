/* Model holders that play one animation, blended in or not (animated_model.h). */
#include "animated_model.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "frame_ctrl.h"
#include "joint_blend.h"
#include "model_anim.h"
#include "model_object.h"

static_assert(sizeof(AnimatedModelAnim) == 0x14, "AnimatedModelAnim layout");
static_assert(sizeof(AnimatedModelRamp) == 0x3c, "AnimatedModelRamp layout");
static_assert(offsetof(AnimatedModel, frames) == 0x9c, "AnimatedModel frames");
static_assert(offsetof(AnimatedModel, anim) == 0xb4, "AnimatedModel anim");
static_assert(offsetof(AnimatedModel, ramp) == 0xb8, "AnimatedModel ramp");
static_assert(sizeof(AnimatedModel) == 0xf4, "AnimatedModel size");

/* The vtables: the animated model's and its frame control part's; the blended model's and its
 * frame control and Ramp parts'; the frame control's own. */
extern const u8 data_020dd05c[];
extern const u8 data_020dd06c[];
extern const u8 data_020dd0dc[];
extern const u8 data_020dd0ec[];
extern const u8 data_020dd0fc[];
extern const u8 data_020dd184[];

/* The joint animation header NitroSystem sizes an animation object by ("J\0AC"). */
extern const u8 data_020dd030[];

extern void NNS_G3dAnmObjInit(AnimatedModelAnim *anim, const u8 *file, u8 *model, void *texture);
extern void NNS_G3dRenderObjAddAnmObj(G3dRenderObject *render, AnimatedModelAnim *anim);
extern void NNS_G3dRenderObjRemoveAnmObj(G3dRenderObject *render, AnimatedModelAnim *anim);
extern void MTX_Identity33_(Mtx33 *mtx);

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* func_02054a9c: the joints play `anim` instead, when they play exactly one other animation. */
void AnimatedModel_UseJointAnim(AnimatedModel *model, AnimatedModelAnim *anim)
{
    AnimatedModelAnim *current = model->object.render.joint_anims;
    if (current != anim && current != NULL && current->next == NULL) {
        NNS_G3dRenderObjRemoveAnmObj(&model->object.render, current);
        NNS_G3dRenderObjAddAnmObj(&model->object.render, anim);
    }
}
CLEAN_AS(func_02054a9c, AnimatedModel_UseJointAnim)

/* func_02054cac: the blended model plays `file` (AnimatedModel_Start), blended in over `blend`
 * frames. */
void AnimatedModel_Play(AnimatedModel *model, const u8 *file, int blend, int flags, fx32 speed, u16 start, u16 frames)
{
    Ramp_Start((Ramp *) &model->ramp, blend);
    AnimatedModel_Start(model, file, flags, speed, start, frames);
}
CLEAN_AS(func_02054cac, AnimatedModel_Play)

/* func_02054cdc: one frame of the blended model: the blend, then the animation. */
void AnimatedModel_Update(AnimatedModel *model)
{
    Ramp_Step((Ramp *) &model->ramp);
    AnimatedModel_StepFrames(model);
}
CLEAN_AS(func_02054cdc, AnimatedModel_Update)

/* func_02054cf4: the node callback after a node (AnimatedModel_BlendNode). */
void AnimatedModel_AfterNode(AnimatedModel *model, G3dRenderState *state)
{
    if (!NodeHook_IsSkipped(model, state)) {
        AnimatedModel_BlendNode(model, state);
    }
}
CLEAN_AS(func_02054cf4, AnimatedModel_AfterNode)

/* func_02054d14: after a node: the parts of its transform flagged as not written are written
 * (a translation of 0, an identity rotation), then, while a blend runs, the node is blended
 * from the pose recorded before it. */
void AnimatedModel_BlendNode(AnimatedModel *model, G3dRenderState *state)
{
    G3dJointResult *joint = state->joint;
    if (joint->flags & G3D_JOINT_TRANSLATION_ZERO) {
        joint->translation.x = 0;
        joint->translation.y = 0;
        joint->translation.z = 0;
    }
    if (joint->flags & G3D_JOINT_ROTATION_IDENTITY) {
        MTX_Identity33_(&joint->rotation);
    }
    if (model->ramp.rate != 0) {
        JointBlend_Apply((JointBlend *) &model->ramp, state);
    }
}
CLEAN_AS(func_02054d14, AnimatedModel_BlendNode)

/* func_02054d60: the node callback before a node (AnimatedModel_RecordNode). */
void AnimatedModel_BeforeNode(AnimatedModel *model, G3dRenderState *state)
{
    if (!NodeHook_IsSkipped(model, state)) {
        AnimatedModel_RecordNode(model, state);
    }
}
CLEAN_AS(func_02054d60, AnimatedModel_BeforeNode)

/* func_02054d80: while a blend runs, the node's pose before it is recorded. */
void AnimatedModel_RecordNode(AnimatedModel *model, G3dRenderState *state)
{
    if (model->ramp.rate != 0) {
        JointBlend_RecordPose((JointBlend *) &model->ramp, state);
    }
}
CLEAN_AS(func_02054d80, AnimatedModel_RecordNode)

/* The blended model's destructor's work: its vtables, its Ramp destructed, then the animated
 * model's destructor. */
static void destruct_blended(AnimatedModel *model)
{
    model->object.vtable = data_020dd0dc;
    model->frames.vtable = data_020dd0ec;
    model->ramp.vtable = data_020dd0fc;
    JointBlend_Destruct((JointBlend *) &model->ramp);
    AnimatedModel_Destruct(model);
}

/* func_02054d9c: the blended model's destructor (the layered models' destructors end with
 * it). */
AnimatedModel *AnimatedModel_DestructBlended(AnimatedModel *model)
{
    destruct_blended(model);
    return model;
}
CLEAN_AS(func_02054d9c, AnimatedModel_DestructBlended)

/* func_02054dd8: the blended model's deleting destructor. */
AnimatedModel *AnimatedModel_DeleteBlended(AnimatedModel *model)
{
    destruct_blended(model);
    Heap_OperatorDeleteB(model);
    return model;
}
CLEAN_AS(func_02054dd8, AnimatedModel_DeleteBlended)

/* func_02054e18: the blended model's complete destructor, the same. */
AnimatedModel *AnimatedModel_DestructBlendedComplete(AnimatedModel *model)
{
    destruct_blended(model);
    return model;
}
CLEAN_AS(func_02054e18, AnimatedModel_DestructBlendedComplete)

/* The blended model's constructor's work: the animated model, its Ramp, then its vtables. */
static void construct_blended(AnimatedModel *model)
{
    AnimatedModel_ConstructBase(model);
    JointBlend_ConstructBase((JointBlend *) &model->ramp);
    model->object.vtable = data_020dd0dc;
    model->frames.vtable = data_020dd0ec;
    model->ramp.vtable = data_020dd0fc;
}

/* func_02054e54: the blended model's constructor. */
AnimatedModel *AnimatedModel_ConstructBlended(AnimatedModel *model)
{
    construct_blended(model);
    return model;
}
CLEAN_AS(func_02054e54, AnimatedModel_ConstructBlended)

/* func_02054e8c: the same constructor, the one the layered models' constructors start with. */
AnimatedModel *AnimatedModel_ConstructBlendedBase(AnimatedModel *model)
{
    construct_blended(model);
    return model;
}
CLEAN_AS(func_02054e8c, AnimatedModel_ConstructBlendedBase)

/* func_02054ec4: the animation object. */
AnimatedModelAnim *AnimatedModel_Anim(AnimatedModel *model)
{
    return model->anim;
}
CLEAN_AS(func_02054ec4, AnimatedModel_Anim)

/* func_02054ecc: the animation the animation object plays. */
const u8 *AnimatedModel_AnimFile(AnimatedModel *model)
{
    return model->anim->resource;
}
CLEAN_AS(func_02054ecc, AnimatedModel_AnimFile)

/* func_02054ed4: the node's transform applied to the current matrix (model_matrix.h) as the
 * node command says: the matrix loaded from its saved place first, the transform (scaled by
 * `scale` when it is not NULL, else leaving out the parts flagged as not written), then the
 * matrix saved.
 * QUIRK: the first parameter is not used. */
void AnimatedModel_ApplyNodeMatrix(void *unused, G3dRenderState *state, const Vec3 *scale)
{
    (void) unused;
    const u8 *command = state->command;
    u32 flags = command[0] & ANIMATED_MODEL_NODE_FLAGS;
    if (flags == ANIMATED_MODEL_NODE_RESTORE) {
        ModelMatrix_Load(command[4]);
    } else if (flags == ANIMATED_MODEL_NODE_RESTORE_STORE) {
        ModelMatrix_Load(command[5]);
    }

    G3dJointResult *joint = state->joint;
    if (scale != NULL) {
        ModelMatrix_ApplyScaledTransform(&joint->rotation, &joint->translation, scale);
    } else {
        u32 written = joint->flags;
        if (written & G3D_JOINT_ROTATION_IDENTITY) {
            if (!(written & G3D_JOINT_TRANSLATION_ZERO)) {
                ModelMatrix_ApplyTranslation(&joint->translation);
            }
        } else if (written & G3D_JOINT_TRANSLATION_ZERO) {
            ModelMatrix_ApplyRotation(&joint->rotation);
        } else {
            ModelMatrix_ApplyTransform(&joint->rotation, &joint->translation);
        }
    }

    if (flags == ANIMATED_MODEL_NODE_STORE || flags == ANIMATED_MODEL_NODE_RESTORE_STORE) {
        ModelMatrix_Save(state->command[4]);
    }
}
CLEAN_AS(func_02054ed4, AnimatedModel_ApplyNodeMatrix)

/* The translation node `node` has in the model itself: the node information's dictionary gives
 * each node's data (its offset in the information), which starts with the translation after a
 * flags word. */
static const u8 *rest_translation(const u8 *node_info, u32 node)
{
    const u8 *entries = node_info + read_u16(node_info + 6);
    return node_info + read_u32(entries + read_u16(entries) * node + 4) + 4;
}

/* func_02054f68: the animation's translation of the node replaced by the model's own, from
 * node 2 on; node 1 (with a `height`) is moved up by its own height less `height`. */
void AnimatedModel_RestoreNodeTranslation(G3dRenderState *state, fx32 height)
{
    u32 node = state->command[1];
    if (node >= 2) {
        const u8 *rest = rest_translation(state->node_info, node);
        G3dJointResult *joint = state->joint;
        joint->translation.x = (fx32) read_u32(rest);
        joint->translation.y = (fx32) read_u32(rest + 4);
        joint->translation.z = (fx32) read_u32(rest + 8);
    } else if (node == 1 && height != 0) {
        G3dJointResult *joint = state->joint;
        const u8 *rest = rest_translation(state->node_info, node);
        joint->translation.y = (fx32) ((u32) joint->translation.y + read_u32(rest + 4) - (u32) height);
    }
}
CLEAN_AS(func_02054f68, AnimatedModel_RestoreNodeTranslation)

/* func_02054fcc: the animation object taken off the render object, from the joints' or the
 * visibility animations, whichever list it starts; the model then has none. */
void AnimatedModel_DetachAnim(AnimatedModel *model)
{
    AnimatedModelAnim *anim = model->anim;
    if (anim == NULL) {
        return;
    }
    G3dRenderObject *render = &model->object.render;
    if (render->joint_anims == anim) {
        NNS_G3dRenderObjRemoveAnmObj(render, render->joint_anims);
        model->anim = NULL;
    } else if (render->visibility_anims == anim) {
        NNS_G3dRenderObjRemoveAnmObj(render, render->visibility_anims);
        model->anim = NULL;
    }
}
CLEAN_AS(func_02054fcc, AnimatedModel_DetachAnim)

/* func_02055008: with an animation object, the first visibility animation is taken off the
 * render object and the model has no animation object any more.
 * QUIRK: what is taken off is not checked to be the model's animation object. */
void AnimatedModel_DetachVisibility(AnimatedModel *model)
{
    if (model->anim != NULL) {
        NNS_G3dRenderObjRemoveAnmObj(&model->object.render, model->object.render.visibility_anims);
        model->anim = NULL;
    }
}
CLEAN_AS(func_02055008, AnimatedModel_DetachVisibility)

/* func_0205502c: AnimatedModel_DetachVisibility for the first joint animation.
 * QUIRK: the same. */
void AnimatedModel_DetachJoints(AnimatedModel *model)
{
    if (model->anim != NULL) {
        NNS_G3dRenderObjRemoveAnmObj(&model->object.render, model->object.render.joint_anims);
        model->anim = NULL;
    }
}
CLEAN_AS(func_0205502c, AnimatedModel_DetachJoints)

/* func_02055050: the animation object put on the render object. */
void AnimatedModel_Attach(AnimatedModel *model)
{
    NNS_G3dRenderObjAddAnmObj(&model->object.render, model->anim);
}
CLEAN_AS(func_02055050, AnimatedModel_Attach)

/* func_02055060: the animation object plays `file` from frame `start` for `frames` frames (0:
 * the file's count for the flags), stepped by `speed` with the FrameCtrlFlags `flags`. */
void AnimatedModel_Start(AnimatedModel *model, const u8 *file, int flags, fx32 speed, u16 start, u16 frames)
{
    if (frames == 0) {
        frames = AnimatedModel_FrameCount(flags, file);
    }
    FrameCtrl_Init(&model->frames, frames, flags, speed, start);
    NNS_G3dAnmObjInit(model->anim, file, model->object.model, NULL);
    model->anim->frame = model->frames.frame;
}
CLEAN_AS(func_02055060, AnimatedModel_Start)

/* func_020550b8: the frames a joint animation is played over: its frame count, one less when
 * it is played in a loop (flags 0 or 2) and its options have bit 0 (NitroSystem's
 * interpolation) without bit 1 (interpolation from the end to the start). */
u16 AnimatedModel_FrameCount(int flags, const u8 *file)
{
    u16 frames = read_u16(file + 4);
    if (flags == 0 || flags == 2) {
        u32 options = read_u32(file + 8);
        if (options & 2) {
            return frames;
        }
        if (options & 1) {
            frames = (u16) (frames - 1);
        }
    }
    return frames;
}
CLEAN_AS(func_020550b8, AnimatedModel_FrameCount)

/* func_020550e4: the animation set at whole frame `frame`; the joint results kept are computed
 * again on the next draw. */
void AnimatedModel_SetFrame(AnimatedModel *model, int frame)
{
    model->frames.frame = (fx32) ((u32) frame << 12);
    model->anim->frame = model->frames.frame;
    if (model->object.render.joint_results != NULL) {
        model->object.render.flags |= MODEL_RENDER_RECORD;
    }
}
CLEAN_AS(func_020550e4, AnimatedModel_SetFrame)

/* func_0205510c: the model drawn with `scale` (NULL: 1.0), its joint results kept computed
 * again. */
void AnimatedModel_Draw(AnimatedModel *model, const Vec3 *scale)
{
    if (model->object.render.joint_results != NULL) {
        model->object.render.flags |= MODEL_RENDER_RECORD;
    }
    ModelObject_Draw((ModelObject *) model, scale);
}
CLEAN_AS(func_0205510c, AnimatedModel_Draw)

/* func_02055124: one step of the frame control, whose frame the animation object takes. */
void AnimatedModel_StepFrames(AnimatedModel *model)
{
    FrameCtrl_Step(&model->frames);
    model->anim->frame = model->frames.frame;
}
CLEAN_AS(func_02055124, AnimatedModel_StepFrames)

/* func_02055140: a joint animation object from `heap` (0: the current one), when the model has
 * a model resource and no animation object yet. 1 when it was had. */
int AnimatedModel_LoadAnim(AnimatedModel *model, Heap *heap)
{
    if (model->anim != NULL || model->object.model == NULL) {
        return 0;
    }
    model->anim = ModelAnim_AllocAnmObj(model->object.model, data_020dd030, heap);
    return model->anim != NULL;
}
CLEAN_AS(func_02055140, AnimatedModel_LoadAnim)

/* The animated model's destructor's work: its vtables, its frame control destructed, then the
 * holder's destructor. */
static void destruct_animated(AnimatedModel *model)
{
    model->object.vtable = data_020dd05c;
    model->frames.vtable = data_020dd06c;
    FrameCtrl_Destruct(&model->frames);
    ModelObject_Destruct(&model->object);
}

/* func_0205517c: the animated model's destructor (the blended model's ends with it). */
AnimatedModel *AnimatedModel_Destruct(AnimatedModel *model)
{
    destruct_animated(model);
    return model;
}
CLEAN_AS(func_0205517c, AnimatedModel_Destruct)

/* func_020551ac: the animated model's deleting destructor. */
AnimatedModel *AnimatedModel_Delete(AnimatedModel *model)
{
    destruct_animated(model);
    Heap_OperatorDeleteB(model);
    return model;
}
CLEAN_AS(func_020551ac, AnimatedModel_Delete)

/* func_020551e0: the animated model's complete destructor, the same. */
AnimatedModel *AnimatedModel_DestructComplete(AnimatedModel *model)
{
    destruct_animated(model);
    return model;
}
CLEAN_AS(func_020551e0, AnimatedModel_DestructComplete)

/* The animated model's constructor's work: the holder, the frame control at frame 0 with
 * speed 1.0, the vtables, and no animation object. */
static void construct_animated(AnimatedModel *model)
{
    ModelObject_ConstructBase(&model->object);
    model->frames.vtable = data_020dd184;
    model->frames.frame = 0;
    model->frames.previous = 0;
    model->frames.speed = 0x1000;
    model->object.vtable = data_020dd05c;
    model->frames.vtable = data_020dd06c;
    model->anim = NULL;
}

/* func_02055210: the animated model's constructor. */
AnimatedModel *AnimatedModel_Construct(AnimatedModel *model)
{
    construct_animated(model);
    return model;
}
CLEAN_AS(func_02055210, AnimatedModel_Construct)

/* func_02055260: the same constructor, the one the blended model's constructors start with. */
AnimatedModel *AnimatedModel_ConstructBase(AnimatedModel *model)
{
    construct_animated(model);
    return model;
}
CLEAN_AS(func_02055260, AnimatedModel_ConstructBase)

/* _ZThn156_N12Obj_020dd05cD0Ev (func_020557c4): the deleting destructor reached through the
 * frame control part's vtable, with the part's address. */
AnimatedModel *AnimatedModel_DeleteFromFrames(FrameCtrl *frames)
{
    return AnimatedModel_Delete((AnimatedModel *) ((uintptr_t) frames - offsetof(AnimatedModel, frames)));
}
CLEAN_AS(_ZThn156_N12Obj_020dd05cD0Ev, AnimatedModel_DeleteFromFrames)

/* The destructors reached through the vtables of the frame control part (at 0x9c) and the Ramp
 * part (at 0xb8), with the part's address. */
static AnimatedModel *from_frames(FrameCtrl *frames)
{
    return (AnimatedModel *) ((uintptr_t) frames - offsetof(AnimatedModel, frames));
}

static AnimatedModel *from_ramp(AnimatedModelRamp *ramp)
{
    return (AnimatedModel *) ((uintptr_t) ramp - offsetof(AnimatedModel, ramp));
}

/* _ZThn156_N12Obj_020dd05cD1Ev (func_020557e0): the animated model's complete destructor. */
AnimatedModel *AnimatedModel_DestructCompleteFromFrames(FrameCtrl *frames)
{
    return AnimatedModel_DestructComplete(from_frames(frames));
}
CLEAN_AS(_ZThn156_N12Obj_020dd05cD1Ev, AnimatedModel_DestructCompleteFromFrames)

/* _ZThn156_N12Obj_020dd0dcD0Ev (func_020557fc): the blended model's deleting destructor. */
AnimatedModel *AnimatedModel_DeleteBlendedFromFrames(FrameCtrl *frames)
{
    return AnimatedModel_DeleteBlended(from_frames(frames));
}
CLEAN_AS(_ZThn156_N12Obj_020dd0dcD0Ev, AnimatedModel_DeleteBlendedFromFrames)

/* _ZThn156_N12Obj_020dd0dcD1Ev (func_02055818): the blended model's complete destructor. */
AnimatedModel *AnimatedModel_DestructBlendedFromFrames(FrameCtrl *frames)
{
    return AnimatedModel_DestructBlendedComplete(from_frames(frames));
}
CLEAN_AS(_ZThn156_N12Obj_020dd0dcD1Ev, AnimatedModel_DestructBlendedFromFrames)

/* _ZThn184_N12Obj_020dd0dcD0Ev (func_02055834): the blended model's deleting destructor. */
AnimatedModel *AnimatedModel_DeleteBlendedFromRamp(AnimatedModelRamp *ramp)
{
    return AnimatedModel_DeleteBlended(from_ramp(ramp));
}
CLEAN_AS(_ZThn184_N12Obj_020dd0dcD0Ev, AnimatedModel_DeleteBlendedFromRamp)

/* _ZThn184_N12Obj_020dd0dcD1Ev (func_02055850): the blended model's complete destructor. */
AnimatedModel *AnimatedModel_DestructBlendedFromRamp(AnimatedModelRamp *ramp)
{
    return AnimatedModel_DestructBlendedComplete(from_ramp(ramp));
}
CLEAN_AS(_ZThn184_N12Obj_020dd0dcD1Ev, AnimatedModel_DestructBlendedFromRamp)
