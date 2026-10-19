/* A model object of main whose joints play up to three joint animations at once: the base
 * one, layer A and layer B. Each layer plays on the nodes of its 64-bit node mask, and B wins
 * over A, A over the base. Switching a node to a layer blends it in over some frames from the
 * pose it had (a Ramp per animation). The game's node callbacks of NitroSystem's G3D (run for
 * each node descriptor command while the model is drawn) pick the animation of the node's
 * layer before the node and blend it after.
 *
 * Three classes of main share the layout: the blended model of animated_model.h (0xf4 bytes,
 * whose animation is the base one), the class with layer A that extends it (constructor
 * func_02054c2c, up to 0x154) and the class with both (constructor func_0205467c, 0x1b4 bytes).
 * The functions of the two upper classes are here, named for the layer they work on. */
#ifndef CLEAN_MAIN_LAYERED_MODEL_H
#define CLEAN_MAIN_LAYERED_MODEL_H

#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/g3d_render.h"
#include "types.h"

/* The model object's flags (ModelObject.flags) in a LayeredModel. */
#define LAYERED_MODEL_RELEASE_A 0x4000 /* free layer A's nodes once its blend is done */
#define LAYERED_MODEL_RELEASE_B 0x8000 /* the same for layer B */

typedef struct LayeredModel {
    AnimatedModel base;        /* 0x00: the blended model; its animation is the base one */
    AnimatedModelAnim *anim_a; /* 0xf4 */
    FrameCtrl frames_a;        /* 0xf8 */
    AnimatedModelRamp ramp_a;  /* 0x110 */
    u32 nodes_a[2];            /* 0x14c: nodes 0-31, then 32-63 */
    AnimatedModelAnim *anim_b; /* 0x154 */
    FrameCtrl frames_b;        /* 0x158 */
    AnimatedModelRamp ramp_b;  /* 0x170 */
    u32 nodes_b[2];            /* 0x1ac */
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
LayeredModel *LayeredModel_DeleteAFromRamp(AnimatedModelRamp *ramp);
LayeredModel *LayeredModel_DestructAFromRamp(AnimatedModelRamp *ramp);
LayeredModel *LayeredModel_DeleteBFromFrames(FrameCtrl *frames);
LayeredModel *LayeredModel_DestructBFromFrames(FrameCtrl *frames);
LayeredModel *LayeredModel_DeleteBFromRamp(AnimatedModelRamp *ramp);
LayeredModel *LayeredModel_DestructBFromRamp(AnimatedModelRamp *ramp);

#endif
