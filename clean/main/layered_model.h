/* A model object of main whose joints play up to three joint animations at once: the base
 * one, layer A and layer B. Each layer plays on the nodes of its 64-bit node mask, and B wins
 * over A, A over the base. Switching a node to a layer blends it in over some frames from the
 * pose it had (a Ramp per animation). The game's node callbacks of NitroSystem's G3D (run for
 * each node descriptor command while the model is drawn) pick the animation of the node's
 * layer before the node and blend it after.
 *
 * Three classes of main share the layout: the base model object (constructor func_02054e8c,
 * up to 0xf4), the class with layer A (constructor func_02054c2c, up to 0x154) and the class
 * with both (constructor func_0205467c, 0x1b4 bytes). The functions of the two upper classes
 * are here, named for the layer they work on. */
#ifndef CLEAN_MAIN_LAYERED_MODEL_H
#define CLEAN_MAIN_LAYERED_MODEL_H

#include "main/g3d_render.h"
#include "itcm/node_hook.h"
#include "main/frame_ctrl.h"
#include "types.h"

/* LayeredModel.flags */
#define LAYERED_MODEL_RELEASE_A 0x4000 /* free layer A's nodes once its blend is done */
#define LAYERED_MODEL_RELEASE_B 0x8000 /* the same for layer B */

/* NitroSystem's NNSG3dAnmObj, the parts read here. */
typedef struct LayeredModelAnim {
    fx32 frame;           /* 0x00 */
    fx32 ratio;           /* 0x04 */
    const void *resource; /* 0x08: the animation */
} LayeredModelAnim;

/* A blend from a node's pose to its animation's, the weight stepped by func_02056e84 (the Ramp
 * of frame_ctrl.h, with its class's vtable). */
typedef struct LayeredModelRamp {
    const void *vtable;
    u8 pose[0x30]; /* 0x04: the pose blended from */
    fx32 weight;   /* 0x34 */
    fx32 rate;     /* 0x38: 0 when no blend runs */
} LayeredModelRamp;

typedef struct LayeredModel {
    const void *vtable;          /* 0x00 */
    u16 flags;                   /* 0x04: LAYERED_MODEL_RELEASE_* */
    u8 unk_06[2];                /* 0x06 */
    G3dRenderObject render;      /* 0x08 */
    void *model_resource;        /* 0x5c: the model (NNSG3dResMdl) */
    u8 unk_60[0x3c];             /* 0x60 */
    FrameCtrl base_frames;       /* 0x9c */
    LayeredModelAnim *base_anim; /* 0xb4 */
    LayeredModelRamp base_ramp;  /* 0xb8 */
    LayeredModelAnim *anim_a;    /* 0xf4 */
    FrameCtrl frames_a;          /* 0xf8 */
    LayeredModelRamp ramp_a;     /* 0x110 */
    u32 nodes_a[2];              /* 0x14c: nodes 0-31, then 32-63 */
    LayeredModelAnim *anim_b;    /* 0x154 */
    FrameCtrl frames_b;          /* 0x158 */
    LayeredModelRamp ramp_b;     /* 0x170 */
    u32 nodes_b[2];              /* 0x1ac */
} LayeredModel;

void LayeredModel_ClearNodesB(LayeredModel *model);
void LayeredModel_MoveNodesToA(LayeredModel *model, u32 first, u32 last);
void LayeredModel_MoveNodesToB(LayeredModel *model, u32 first, u32 last);
void LayeredModel_StartBFromBase(LayeredModel *model, int blend, int frames);
int LayeredModel_IsBDone(LayeredModel *model);
void LayeredModel_PlayB(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames,
                        int release);
void LayeredModel_PlayBaseB(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames);
void LayeredModel_UpdateB(LayeredModel *model);
int LayeredModel_LoadB(LayeredModel *model, int heap);
void LayeredModel_ApplyNodeB(LayeredModel *model, G3dRenderState *state);
void LayeredModel_BlendNodeB(LayeredModel *model, G3dRenderState *state);
void LayeredModel_PrepareNodeB(LayeredModel *model, G3dRenderState *state);
void LayeredModel_RecordNodeB(LayeredModel *model, G3dRenderState *state);
u32 LayeredModel_HasNodeB(LayeredModel *model, u32 node);
void LayeredModel_ClearNodeB(LayeredModel *model, u32 node);
void LayeredModel_SetNodeB(LayeredModel *model, u32 node);
LayeredModel *LayeredModel_DeleteB(LayeredModel *model);
LayeredModel *LayeredModel_DestructB(LayeredModel *model);
LayeredModel *LayeredModel_ConstructB(LayeredModel *model);
void LayeredModel_ClearNodesA(LayeredModel *model);
void LayeredModel_RemoveNodesA(LayeredModel *model, u32 first, u32 last);
void LayeredModel_AddNodesA(LayeredModel *model, u32 first, u32 last);
void LayeredModel_StartAFromBase(LayeredModel *model, int blend, int frames);
void LayeredModel_PlayA(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames,
                        int release);
void LayeredModel_PlayBaseA(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames);
void LayeredModel_DrawA(LayeredModel *model, const void *scale);
void LayeredModel_UpdateA(LayeredModel *model);
int LayeredModel_LoadA(LayeredModel *model, int heap);
void LayeredModel_ApplyNodeA(LayeredModel *model, G3dRenderState *state);
void LayeredModel_BlendNodeA(LayeredModel *model, G3dRenderState *state);
void LayeredModel_PrepareNodeA(LayeredModel *model, G3dRenderState *state);
void LayeredModel_RecordNodeA(LayeredModel *model, G3dRenderState *state);
int LayeredModel_HasNodeA(LayeredModel *model, u32 node);
void LayeredModel_ClearNodeA(LayeredModel *model, u32 node);

void LayeredModel_SetNodeA(LayeredModel *model, u32 node);
void LayeredModel_BeforeAddNode(LayeredModel *model, u32 node);
void LayeredModel_BeforeRemoveNode(LayeredModel *model, u32 node);
LayeredModel *LayeredModel_DestructA(LayeredModel *model);
LayeredModel *LayeredModel_DeleteA(LayeredModel *model);
LayeredModel *LayeredModel_DestructAComplete(LayeredModel *model);
LayeredModel *LayeredModel_ConstructA(LayeredModel *model);
LayeredModel *LayeredModel_ConstructABase(LayeredModel *model);
LayeredModel *LayeredModel_DeleteAFromFrames(FrameCtrl *frames);
LayeredModel *LayeredModel_DestructAFromFrames(FrameCtrl *frames);
LayeredModel *LayeredModel_DeleteAFromRamp(LayeredModelRamp *ramp);
LayeredModel *LayeredModel_DestructAFromRamp(LayeredModelRamp *ramp);
LayeredModel *LayeredModel_DeleteBFromFrames(FrameCtrl *frames);
LayeredModel *LayeredModel_DestructBFromFrames(FrameCtrl *frames);
LayeredModel *LayeredModel_DeleteBFromRamp(LayeredModelRamp *ramp);
LayeredModel *LayeredModel_DestructBFromRamp(LayeredModelRamp *ramp);

#endif
