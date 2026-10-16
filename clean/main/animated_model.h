/* Model holders (model_object.h) that play one animation. Two C++ classes of main:
 *
 * - the animated model (vtable data_020dd05c, 0xb4 bytes): a frame control steps the frame
 *   that its NitroSystem animation object (NNSG3dAnmObj) shows;
 * - the blended model (vtable data_020dd0dc, 0xf4 bytes), which adds a Ramp: a new animation
 *   is blended in over some frames from the pose each joint had, by node callbacks of
 *   NitroSystem's G3D run while the model is drawn.
 *
 * The models with layered animations extend the blended model (layered_model.h). */
#ifndef CLEAN_MAIN_ANIMATED_MODEL_H
#define CLEAN_MAIN_ANIMATED_MODEL_H

#include "autoload_2/vector.h"
#include "itcm/node_hook.h"
#include "main/frame_ctrl.h"
#include "main/model_matrix.h"
#include "main/model_object.h"
#include "types.h"

/* NitroSystem's NNSG3dAnmObj. */
typedef struct AnimatedModelAnim {
    fx32 frame;                     /* 0x00 */
    fx32 ratio;                     /* 0x04 */
    const u8 *resource;             /* 0x08: the animation */
    void *apply;                    /* 0x0c */
    struct AnimatedModelAnim *next; /* 0x10: the next of the render object's list */
} AnimatedModelAnim;

/* A blend from a node's pose to its animation's (the Ramp of frame_ctrl.h with its class's
 * vtable). */
typedef struct AnimatedModelRamp {
    const void *vtable;
    u8 pose[0x30]; /* 0x04: the pose blended from */
    fx32 weight;   /* 0x34 */
    fx32 rate;     /* 0x38: 0 when no blend runs */
} AnimatedModelRamp;

typedef struct AnimatedModel {
    ModelObject object;      /* 0x00 */
    FrameCtrl frames;        /* 0x9c */
    AnimatedModelAnim *anim; /* 0xb4 */
    AnimatedModelRamp ramp;  /* 0xb8: the blended model's */
} AnimatedModel;

/* NitroSystem's NNSG3dJntAnmResult, a node's transform. */
typedef struct AnimatedModelJoint {
    u32 flags;        /* 0x00: ANIMATED_MODEL_JOINT_* */
    u8 unk_04[0x24];  /* 0x04: the scale */
    Mtx33 rotation;   /* 0x28 */
    Vec3 translation; /* 0x4c */
} AnimatedModelJoint;

#define ANIMATED_MODEL_JOINT_ROTATION_IDENTITY 0x02 /* the rotation is the identity, not written */
#define ANIMATED_MODEL_JOINT_TRANSLATION_ZERO 0x04  /* the translation is 0, not written */

/* NitroSystem's NNSG3dRS, the parts read here. */
typedef struct AnimatedModelNodeState {
    G3dRenderState state;      /* 0x00: the command being run: NODEDESC, byte 1 the node */
    u8 unk_08[0xac];           /* 0x08 */
    AnimatedModelJoint *joint; /* 0xb4: the node's transform */
    u8 unk_b8[0x1c];           /* 0xb8 */
    const u8 *node_info;       /* 0xd4: the model's node information (NNSG3dResNodeInfo) */
} AnimatedModelNodeState;

/* The flags of the NODEDESC command, in the top 3 bits of its first byte. */
#define ANIMATED_MODEL_NODE_FLAGS 0xe0
#define ANIMATED_MODEL_NODE_STORE 0x20         /* the matrix is saved after, to index byte 4 */
#define ANIMATED_MODEL_NODE_RESTORE 0x40       /* the matrix is loaded before, from index byte 4 */
#define ANIMATED_MODEL_NODE_RESTORE_STORE 0x60 /* loaded from byte 5 and saved to byte 4 */

void AnimatedModel_UseJointAnim(AnimatedModel *model, AnimatedModelAnim *anim);
void AnimatedModel_Play(AnimatedModel *model, const u8 *file, int blend, int flags, fx32 speed, u16 start, u16 frames);
void AnimatedModel_Update(AnimatedModel *model);
void AnimatedModel_AfterNode(AnimatedModel *model, AnimatedModelNodeState *state);
void AnimatedModel_BlendNode(AnimatedModel *model, AnimatedModelNodeState *state);
void AnimatedModel_BeforeNode(AnimatedModel *model, AnimatedModelNodeState *state);
void AnimatedModel_RecordNode(AnimatedModel *model, AnimatedModelNodeState *state);
AnimatedModel *AnimatedModel_DestructBlended(AnimatedModel *model);
AnimatedModel *AnimatedModel_DeleteBlended(AnimatedModel *model);
AnimatedModel *AnimatedModel_DestructBlendedComplete(AnimatedModel *model);
AnimatedModel *AnimatedModel_ConstructBlended(AnimatedModel *model);
AnimatedModel *AnimatedModel_ConstructBlendedBase(AnimatedModel *model);
AnimatedModelAnim *AnimatedModel_Anim(AnimatedModel *model);
const u8 *AnimatedModel_AnimFile(AnimatedModel *model);
void AnimatedModel_ApplyNodeMatrix(void *unused, AnimatedModelNodeState *state, const Vec3 *scale);
void AnimatedModel_RestoreNodeTranslation(AnimatedModelNodeState *state, fx32 height);
void AnimatedModel_DetachAnim(AnimatedModel *model);
void AnimatedModel_DetachVisibility(AnimatedModel *model);
void AnimatedModel_DetachJoints(AnimatedModel *model);
void AnimatedModel_Attach(AnimatedModel *model);
void AnimatedModel_Start(AnimatedModel *model, const u8 *file, int flags, fx32 speed, u16 start, u16 frames);
u16 AnimatedModel_FrameCount(int flags, const u8 *file);
void AnimatedModel_SetFrame(AnimatedModel *model, int frame);
void AnimatedModel_Draw(AnimatedModel *model, const Vec3 *scale);
void AnimatedModel_StepFrames(AnimatedModel *model);
int AnimatedModel_LoadAnim(AnimatedModel *model, Heap *heap);
AnimatedModel *AnimatedModel_Destruct(AnimatedModel *model);
AnimatedModel *AnimatedModel_Delete(AnimatedModel *model);
AnimatedModel *AnimatedModel_DestructComplete(AnimatedModel *model);
AnimatedModel *AnimatedModel_Construct(AnimatedModel *model);
AnimatedModel *AnimatedModel_ConstructBase(AnimatedModel *model);
AnimatedModel *AnimatedModel_DeleteFromFrames(FrameCtrl *frames);
AnimatedModel *AnimatedModel_DestructCompleteFromFrames(FrameCtrl *frames);
AnimatedModel *AnimatedModel_DeleteBlendedFromFrames(FrameCtrl *frames);
AnimatedModel *AnimatedModel_DestructBlendedFromFrames(FrameCtrl *frames);
AnimatedModel *AnimatedModel_DeleteBlendedFromRamp(AnimatedModelRamp *ramp);
AnimatedModel *AnimatedModel_DestructBlendedFromRamp(AnimatedModelRamp *ramp);

#endif
