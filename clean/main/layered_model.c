/* A model object with layered joint animations (layered_model.h). */
#include "layered_model.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(sizeof(LayeredModelAnim) == 0x0c, "LayeredModelAnim layout");
static_assert(sizeof(LayeredModelRamp) == 0x3c && offsetof(LayeredModelRamp, rate) == 0x38, "LayeredModelRamp layout");
static_assert(offsetof(LayeredModel, model_resource) == 0x5c, "LayeredModel model_resource");
static_assert(offsetof(LayeredModel, base_frames) == 0x9c, "LayeredModel base_frames");
static_assert(offsetof(LayeredModel, base_anim) == 0xb4, "LayeredModel base_anim");
static_assert(offsetof(LayeredModel, anim_a) == 0xf4, "LayeredModel anim_a");
static_assert(offsetof(LayeredModel, ramp_a) == 0x110, "LayeredModel ramp_a");
static_assert(offsetof(LayeredModel, nodes_a) == 0x14c, "LayeredModel nodes_a");
static_assert(offsetof(LayeredModel, anim_b) == 0x154, "LayeredModel anim_b");
static_assert(offsetof(LayeredModel, ramp_b) == 0x170, "LayeredModel ramp_b");
static_assert(sizeof(LayeredModel) == 0x1b4, "LayeredModel size");
static_assert(offsetof(LayeredModelJoint, translation) == 0x4c, "LayeredModelJoint layout");
static_assert(offsetof(LayeredModelNodeState, joint) == 0xb4, "LayeredModelNodeState layout");

/* The vtables of the class with both layers: its own and those of its frame control and Ramp
 * parts (at 0x9c and 0xb8), and the frame control's. */
extern const u8 data_020dd07c[];
extern const u8 data_020dd08c[];
extern const u8 data_020dd09c[];
extern const u8 data_020dd184[];

/* The joint animation header NitroSystem sizes an animation object by ("J\0AC"). */
extern const u8 data_020dd030[];

/* The class with layer A: its constructor and destructor. */
extern LayeredModel *func_02054c2c(LayeredModel *model);
extern LayeredModel *func_02054ad0(LayeredModel *model);

/* The base model object's own functions. */
extern void func_02054cac(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames);
extern void func_02054cdc(LayeredModel *model);                                             /* update */
extern void func_0205510c(LayeredModel *model, const void *scale);                          /* draw */
extern int func_02055140(LayeredModel *model, int heap);                                    /* load the base animation */
extern void func_02054a9c(LayeredModel *model, LayeredModelAnim *anim);                     /* animation the joints use */
extern void func_02054d14(LayeredModel *model, LayeredModelNodeState *state);               /* blend a base node */
extern void func_02054d80(LayeredModel *model, LayeredModelNodeState *state);               /* record a base node */
extern const void *func_02054ecc(LayeredModel *model);                                      /* base_anim's animation */
extern void func_02054a94(LayeredModel *model, u32 node);                                   /* does nothing */
extern void func_02054a98(LayeredModel *model, u32 node);                                   /* does nothing */
extern void func_02054a64(LayeredModel *model, u32 node);                                   /* put a node in layer A */
extern u16 func_020550b8(int flags, const void *file);                                      /* the file's frame count */
extern LayeredModelAnim *func_02056548(void *model_resource, const void *header, int heap); /* a new animation */

/* Frame controls and Ramps (frame_ctrl.h). */
extern void func_02056fcc(FrameCtrl *ctrl, u32 frames, int flags, fx32 speed, u16 start); /* FrameCtrl_Init */
extern int func_02056f94(const FrameCtrl *ctrl);                                          /* FrameCtrl_IsDone */
extern void func_02056ffc(FrameCtrl *ctrl);                                               /* FrameCtrl_Step */
extern void func_02057078(FrameCtrl *ctrl);                                               /* its destructor */
extern void func_02056e60(LayeredModelRamp *ramp, int frames);                            /* start a blend */
extern int func_02056e84(LayeredModelRamp *ramp);                                         /* Ramp_Step */
extern void func_02056aa0(LayeredModelRamp *ramp, LayeredModelNodeState *state);          /* record the pose */
extern void func_02056b18(LayeredModelRamp *ramp, LayeredModelNodeState *state);          /* blend from it */
extern void func_02056ed4(LayeredModelRamp *ramp);                                        /* its destructor */
extern LayeredModelRamp *func_02056ee0(LayeredModelRamp *ramp);                           /* its constructor */

extern void NNS_G3dAnmObjInit(LayeredModelAnim *anim, const void *file, void *model_resource, void *texture);

/* 1 << shift as the ARM computes it: by the shift's low byte, 0 from 32 on. */
static u32 arm_bit(u32 shift)
{
    shift &= 0xff;
    return shift < 32 ? 1u << shift : 0;
}

/* Whether `node` is in a node mask. QUIRK: a node from 64 on reads bit (node - 32) & 0xff of
 * the high word when that is below 32, else nothing; the game's nodes are below 64. */
static int mask_has(const u32 mask[2], u32 node)
{
    if (node >= 32) {
        return (mask[1] & arm_bit(node - 32)) != 0;
    }
    return (mask[0] & arm_bit(node)) != 0;
}

static void mask_clear(u32 mask[2], u32 node)
{
    if (node >= 32) {
        mask[1] &= ~arm_bit(node - 32);
    } else {
        mask[0] &= ~arm_bit(node);
    }
}

static void mask_set(u32 mask[2], u32 node)
{
    if (node >= 32) {
        mask[1] |= arm_bit(node - 32);
    } else {
        mask[0] |= arm_bit(node);
    }
}

/* What the blend after a node does first: a joint result flagged as without translation gets
 * its translation written as 0. */
static void zero_translation(LayeredModelNodeState *state)
{
    LayeredModelJoint *joint = state->joint;
    if (joint->flags & LAYERED_MODEL_JOINT_TRANSLATION_ZERO) {
        joint->translation[0] = 0;
        joint->translation[1] = 0;
        joint->translation[2] = 0;
    }
}

/* The frame control's whole frame, as the start of a sequence. */
static u16 whole_frame(const FrameCtrl *ctrl)
{
    return (u16) ((u32) ctrl->frame >> 12);
}

/* func_02054170: no node in layer B. */
void LayeredModel_ClearNodesB(LayeredModel *model)
{
    model->nodes_b[1] = 0;
    model->nodes_b[0] = 0;
}
CLEAN_AS(func_02054170, LayeredModel_ClearNodesB)

/* func_02054188: nodes `first` to `last` from layer B to layer A.
 * QUIRK: a `last` of 0xffffffff never ends. */
void LayeredModel_MoveNodesToA(LayeredModel *model, u32 first, u32 last)
{
    for (u32 node = first; node <= last; node++) {
        func_02054a94(model, node);
        func_02054a64(model, node);
        LayeredModel_ClearNodeB(model, node);
    }
}
CLEAN_AS(func_02054188, LayeredModel_MoveNodesToA)

/* func_020541b8: nodes `first` to `last` from layer A to layer B.
 * QUIRK: a `last` of 0xffffffff never ends. */
void LayeredModel_MoveNodesToB(LayeredModel *model, u32 first, u32 last)
{
    for (u32 node = first; node <= last; node++) {
        func_02054a94(model, node);
        LayeredModel_ClearNodeA(model, node);
        LayeredModel_SetNodeB(model, node);
    }
}
CLEAN_AS(func_020541b8, LayeredModel_MoveNodesToB)

/* func_020541e8: with a `blend` of 0, no node in layer B; else layer B plays the base
 * animation's file from the base's whole frame on, with its flags and speed, for `frames`
 * frames (0: the file's), its nodes blended in over `blend` frames and freed once they are. */
void LayeredModel_StartBFromBase(LayeredModel *model, int blend, int frames)
{
    if (blend == 0) {
        LayeredModel_ClearNodesB(model);
        return;
    }
    LayeredModel_PlayB(model, func_02054ecc(model), blend, model->base_frames.flags, model->base_frames.speed,
                       whole_frame(&model->base_frames), (u16) frames, 1);
}
CLEAN_AS(func_020541e8, LayeredModel_StartBFromBase)

/* func_02054230: whether layer B's sequence, played once, has reached its end. */
int LayeredModel_IsBDone(LayeredModel *model)
{
    return func_02056f94(&model->frames_b);
}
CLEAN_AS(func_02054230, LayeredModel_IsBDone)

/* func_02054240: layer B plays `file` from `start` for `frames` frames (0: the file's count
 * for the flags), stepped by `speed`, its nodes blended in over `blend` frames; with `release`
 * they are freed once the blend is done. */
void LayeredModel_PlayB(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames,
                        int release)
{
    func_02056e60(&model->ramp_b, blend);
    if (frames == 0) {
        frames = func_020550b8(flags, file);
    }
    func_02056fcc(&model->frames_b, frames, flags, speed, start);
    NNS_G3dAnmObjInit(model->anim_b, file, model->model_resource, NULL);
    if (release) {
        model->flags |= LAYERED_MODEL_RELEASE_B;
    } else {
        model->flags &= (u16) ~LAYERED_MODEL_RELEASE_B;
    }
}
CLEAN_AS(func_02054240, LayeredModel_PlayB)

/* func_020542c0: the base animation plays `file` (LayeredModel_PlayBaseA). */
void LayeredModel_PlayBaseB(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames)
{
    LayeredModel_PlayBaseA(model, file, blend, flags, speed, start, frames);
}
CLEAN_AS(func_020542c0, LayeredModel_PlayBaseB)

/* func_020542e0: one frame of the three animations. While layer B has nodes, its blend is
 * stepped (freeing its nodes when it is done and they are to be freed), then its frame, which
 * its animation object takes. */
void LayeredModel_UpdateB(LayeredModel *model)
{
    LayeredModel_UpdateA(model);
    if (model->nodes_b[0] == 0 && model->nodes_b[1] == 0) {
        return;
    }
    if (func_02056e84(&model->ramp_b) && (model->flags & LAYERED_MODEL_RELEASE_B)) {
        LayeredModel_ClearNodesB(model);
        model->flags &= (u16) ~LAYERED_MODEL_RELEASE_B;
    }
    func_02056ffc(&model->frames_b);
    model->anim_b->frame = model->frames_b.frame;
}
CLEAN_AS(func_020542e0, LayeredModel_UpdateB)

/* func_02054354: the animation objects of the base and layer A (LayeredModel_LoadA), then
 * layer B's, from `heap` (0: the current one). 1 when all were had. */
int LayeredModel_LoadB(LayeredModel *model, int heap)
{
    if (!LayeredModel_LoadA(model, heap)) {
        return 0;
    }
    model->anim_b = func_02056548(model->model_resource, data_020dd030, heap);
    return model->anim_b != NULL;
}
CLEAN_AS(func_02054354, LayeredModel_LoadB)

/* func_02054394: the node callback after a node (func_0201c49c): the node is blended by the
 * layer it is in, B before A, else as a base node.
 * QUIRK: it first tests bit (node & 31) of the four mask words together, a quick test that
 * only sends nodes to the base. */
void LayeredModel_ApplyNodeB(LayeredModel *model, LayeredModelNodeState *state)
{
    if (NodeHook_IsSkipped(model, &state->state)) {
        return;
    }
    u32 any = model->nodes_b[1] | model->nodes_b[0] | model->nodes_a[0] | model->nodes_a[1];
    if (any == 0) {
        func_02054d14(model, state);
        return;
    }
    u8 node = state->state.command[1];
    if ((any & 1u << (node & 0x1f)) == 0) {
        func_02054d14(model, state);
        return;
    }
    if (LayeredModel_HasNodeB(model, node)) {
        LayeredModel_BlendNodeB(model, state);
        return;
    }
    if (LayeredModel_HasNodeA(model, node)) {
        LayeredModel_BlendNodeA(model, state);
        return;
    }
    func_02054d14(model, state);
}
CLEAN_AS(func_02054394, LayeredModel_ApplyNodeB)

/* func_02054430: after a node of layer B: the translation written when it is flagged 0, then,
 * while B's blend runs, the node blended from the pose recorded before it. */
void LayeredModel_BlendNodeB(LayeredModel *model, LayeredModelNodeState *state)
{
    zero_translation(state);
    if (model->ramp_b.rate != 0) {
        func_02056b18(&model->ramp_b, state);
    }
}
CLEAN_AS(func_02054430, LayeredModel_BlendNodeB)

/* func_02054474: the node callback before a node (func_0201c6a8): the joints take the
 * animation of the node's layer, B before A, else the base one, and the node's pose is
 * recorded for that layer's blend. */
void LayeredModel_PrepareNodeB(LayeredModel *model, LayeredModelNodeState *state)
{
    if (NodeHook_IsSkipped(model, &state->state)) {
        return;
    }
    u8 node = state->state.command[1];
    if (mask_has(model->nodes_b, node)) {
        func_02054a9c(model, model->anim_b);
        LayeredModel_RecordNodeB(model, state);
        return;
    }
    if (mask_has(model->nodes_a, node)) {
        func_02054a9c(model, model->anim_a);
        LayeredModel_RecordNodeA(model, state);
        return;
    }
    func_02054a9c(model, model->base_anim);
    func_02054d80(model, state);
}
CLEAN_AS(func_02054474, LayeredModel_PrepareNodeB)

/* func_02054524: while layer B's blend runs, the node's pose before it is recorded. */
void LayeredModel_RecordNodeB(LayeredModel *model, LayeredModelNodeState *state)
{
    if (model->ramp_b.rate != 0) {
        func_02056aa0(&model->ramp_b, state);
    }
}
CLEAN_AS(func_02054524, LayeredModel_RecordNodeB)

/* func_02054548: whether `node` is in layer B (1 or 0). */
u32 LayeredModel_HasNodeB(LayeredModel *model, u32 node)
{
    return (u32) mask_has(model->nodes_b, node);
}
CLEAN_AS(func_02054548, LayeredModel_HasNodeB)

/* func_02054580: `node` out of layer B. */
void LayeredModel_ClearNodeB(LayeredModel *model, u32 node)
{
    mask_clear(model->nodes_b, node);
}
CLEAN_AS(func_02054580, LayeredModel_ClearNodeB)

/* func_020545b0: `node` into layer B. */
void LayeredModel_SetNodeB(LayeredModel *model, u32 node)
{
    mask_set(model->nodes_b, node);
}
CLEAN_AS(func_020545b0, LayeredModel_SetNodeB)

/* The destructor's work: the vtables of the class, then layer B's Ramp and frame control
 * destructed, then the class with layer A's destructor. */
static void destruct_b(LayeredModel *model)
{
    model->vtable = data_020dd07c;
    model->base_frames.vtable = data_020dd08c;
    model->base_ramp.vtable = data_020dd09c;
    func_02056ed4(&model->ramp_b);
    func_02057078(&model->frames_b);
    func_02054ad0(model);
}

/* func_020545e0: the deleting destructor (the vtable's second entry). */
LayeredModel *LayeredModel_DeleteB(LayeredModel *model)
{
    destruct_b(model);
    Heap_OperatorDeleteB(model);
    return model;
}
CLEAN_AS(func_020545e0, LayeredModel_DeleteB)

/* func_02054630: the destructor. */
LayeredModel *LayeredModel_DestructB(LayeredModel *model)
{
    destruct_b(model);
    return model;
}
CLEAN_AS(func_02054630, LayeredModel_DestructB)

/* func_0205467c: the constructor: the class with layer A, then this class's vtables, layer B's
 * frame control at frame 0 with speed 1.0, its Ramp, no animation object and no node. */
LayeredModel *LayeredModel_ConstructB(LayeredModel *model)
{
    func_02054c2c(model);
    model->vtable = data_020dd07c;
    model->base_frames.vtable = data_020dd08c;
    model->base_ramp.vtable = data_020dd09c;
    model->frames_b.vtable = data_020dd184;
    model->frames_b.frame = 0;
    model->frames_b.previous = 0;
    model->frames_b.speed = 0x1000;
    func_02056ee0(&model->ramp_b);
    model->anim_b = NULL;
    model->nodes_b[0] = 0;
    model->nodes_b[1] = 0;
    return model;
}
CLEAN_AS(func_0205467c, LayeredModel_ConstructB)

/* func_02054700: no node in layer A. */
void LayeredModel_ClearNodesA(LayeredModel *model)
{
    model->nodes_a[1] = 0;
    model->nodes_a[0] = 0;
}
CLEAN_AS(func_02054700, LayeredModel_ClearNodesA)

/* func_02054718: nodes `first` to `last` out of layer A.
 * QUIRK: a `last` of 0xffffffff never ends. */
void LayeredModel_RemoveNodesA(LayeredModel *model, u32 first, u32 last)
{
    for (u32 node = first; node <= last; node++) {
        func_02054a98(model, node);
        LayeredModel_ClearNodeA(model, node);
    }
}
CLEAN_AS(func_02054718, LayeredModel_RemoveNodesA)

/* func_02054740: nodes `first` to `last` into layer A.
 * QUIRK: a `last` of 0xffffffff never ends. */
void LayeredModel_AddNodesA(LayeredModel *model, u32 first, u32 last)
{
    for (u32 node = first; node <= last; node++) {
        func_02054a94(model, node);
        func_02054a64(model, node);
    }
}
CLEAN_AS(func_02054740, LayeredModel_AddNodesA)

/* func_02054768: LayeredModel_StartBFromBase for layer A. */
void LayeredModel_StartAFromBase(LayeredModel *model, int blend, int frames)
{
    if (blend == 0) {
        LayeredModel_ClearNodesA(model);
        return;
    }
    LayeredModel_PlayA(model, func_02054ecc(model), blend, model->base_frames.flags, model->base_frames.speed,
                       whole_frame(&model->base_frames), (u16) frames, 1);
}
CLEAN_AS(func_02054768, LayeredModel_StartAFromBase)

/* func_020547b0: LayeredModel_PlayB for layer A. */
void LayeredModel_PlayA(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames,
                        int release)
{
    func_02056e60(&model->ramp_a, blend);
    if (frames == 0) {
        frames = func_020550b8(flags, file);
    }
    func_02056fcc(&model->frames_a, frames, flags, speed, start);
    NNS_G3dAnmObjInit(model->anim_a, file, model->model_resource, NULL);
    if (release) {
        model->flags |= LAYERED_MODEL_RELEASE_A;
    } else {
        model->flags &= (u16) ~LAYERED_MODEL_RELEASE_A;
    }
}
CLEAN_AS(func_020547b0, LayeredModel_PlayA)

/* func_02054828: the base animation plays `file`, blended over `blend` frames (the base model
 * object's func_02054cac). */
void LayeredModel_PlayBaseA(LayeredModel *model, const void *file, int blend, int flags, fx32 speed, u16 start, u16 frames)
{
    func_02054cac(model, file, blend, flags, speed, start, frames);
}
CLEAN_AS(func_02054828, LayeredModel_PlayBaseA)

/* func_02054848: draw the model (the base model object's func_0205510c; `scale` NULL for
 * 1.0), then give its joints back the base animation, which the node callbacks may have
 * left another layer's. */
void LayeredModel_DrawA(LayeredModel *model, const void *scale)
{
    func_0205510c(model, scale);
    func_02054a9c(model, model->base_anim);
}
CLEAN_AS(func_02054848, LayeredModel_DrawA)

/* func_02054860: LayeredModel_UpdateB for the base animation and layer A. */
void LayeredModel_UpdateA(LayeredModel *model)
{
    func_02054cdc(model);
    if (model->nodes_a[0] == 0 && model->nodes_a[1] == 0) {
        return;
    }
    if (func_02056e84(&model->ramp_a) && (model->flags & LAYERED_MODEL_RELEASE_A)) {
        LayeredModel_ClearNodesA(model);
        model->flags &= (u16) ~LAYERED_MODEL_RELEASE_A;
    }
    func_02056ffc(&model->frames_a);
    model->anim_a->frame = model->frames_a.frame;
}
CLEAN_AS(func_02054860, LayeredModel_UpdateA)

/* func_020548cc: LayeredModel_LoadB for the base animation and layer A. */
int LayeredModel_LoadA(LayeredModel *model, int heap)
{
    if (func_02055140(model, heap) == 0) {
        return 0;
    }
    model->anim_a = func_02056548(model->model_resource, data_020dd030, heap);
    return model->anim_a != NULL;
}
CLEAN_AS(func_020548cc, LayeredModel_LoadA)

/* func_0205490c: LayeredModel_ApplyNodeB for layer A (func_02005740). */
void LayeredModel_ApplyNodeA(LayeredModel *model, LayeredModelNodeState *state)
{
    if (NodeHook_IsSkipped(model, &state->state)) {
        return;
    }
    if (LayeredModel_HasNodeA(model, state->state.command[1])) {
        LayeredModel_BlendNodeA(model, state);
    } else {
        func_02054d14(model, state);
    }
}
CLEAN_AS(func_0205490c, LayeredModel_ApplyNodeA)

/* func_02054944: LayeredModel_BlendNodeB for layer A. */
void LayeredModel_BlendNodeA(LayeredModel *model, LayeredModelNodeState *state)
{
    zero_translation(state);
    if (model->ramp_a.rate != 0) {
        func_02056b18(&model->ramp_a, state);
    }
}
CLEAN_AS(func_02054944, LayeredModel_BlendNodeA)

/* func_02054988: LayeredModel_PrepareNodeB for layer A (func_020058b4). */
void LayeredModel_PrepareNodeA(LayeredModel *model, LayeredModelNodeState *state)
{
    if (NodeHook_IsSkipped(model, &state->state)) {
        return;
    }
    if (LayeredModel_HasNodeA(model, state->state.command[1])) {
        func_02054a9c(model, model->anim_a);
        LayeredModel_RecordNodeA(model, state);
    } else {
        func_02054a9c(model, model->base_anim);
        func_02054d80(model, state);
    }
}
CLEAN_AS(func_02054988, LayeredModel_PrepareNodeA)

/* func_020549d8: LayeredModel_RecordNodeB for layer A. */
void LayeredModel_RecordNodeA(LayeredModel *model, LayeredModelNodeState *state)
{
    if (model->ramp_a.rate != 0) {
        func_02056aa0(&model->ramp_a, state);
    }
}
CLEAN_AS(func_020549d8, LayeredModel_RecordNodeA)

/* func_020549fc: whether `node` is in layer A (1 or 0). */
int LayeredModel_HasNodeA(LayeredModel *model, u32 node)
{
    return mask_has(model->nodes_a, node);
}
CLEAN_AS(func_020549fc, LayeredModel_HasNodeA)

/* func_02054a34: `node` out of layer A. */
void LayeredModel_ClearNodeA(LayeredModel *model, u32 node)
{
    mask_clear(model->nodes_a, node);
}
CLEAN_AS(func_02054a34, LayeredModel_ClearNodeA)

/* func_02054a64: `node` into layer A. */
void LayeredModel_SetNodeA(LayeredModel *model, u32 node)
{
    mask_set(model->nodes_a, node);
}
CLEAN_AS(func_02054a64, LayeredModel_SetNodeA)

/* func_02054a94: called before a node is put in a layer; does nothing. */
void LayeredModel_BeforeAddNode(LayeredModel *model, u32 node)
{
    (void) model;
    (void) node;
}
CLEAN_AS(func_02054a94, LayeredModel_BeforeAddNode)

/* func_02054a98: called before a node is taken out of layer A; does nothing. */
void LayeredModel_BeforeRemoveNode(LayeredModel *model, u32 node)
{
    (void) model;
    (void) node;
}
CLEAN_AS(func_02054a98, LayeredModel_BeforeRemoveNode)

/* The vtables of the class with layer A: its own and those of its frame control and Ramp
 * parts (at 0x9c and 0xb8). */
extern const u8 data_020dd0ac[];
extern const u8 data_020dd0bc[];
extern const u8 data_020dd0cc[];

/* The base model object's destructor and constructor (animated_model.h). */
extern LayeredModel *func_02054d9c(LayeredModel *model);
extern LayeredModel *func_02054e8c(LayeredModel *model);

/* The destructor's work: the vtables of the class, then layer A's Ramp and frame control
 * destructed, then the base model object's destructor. */
static void destruct_a(LayeredModel *model)
{
    model->vtable = data_020dd0ac;
    model->base_frames.vtable = data_020dd0bc;
    model->base_ramp.vtable = data_020dd0cc;
    func_02056ed4(&model->ramp_a);
    func_02057078(&model->frames_a);
    func_02054d9c(model);
}

/* func_02054ad0: the destructor of the class with layer A (the class with both layers' ends
 * with it). */
LayeredModel *LayeredModel_DestructA(LayeredModel *model)
{
    destruct_a(model);
    return model;
}
CLEAN_AS(func_02054ad0, LayeredModel_DestructA)

/* func_02054b18: its deleting destructor. */
LayeredModel *LayeredModel_DeleteA(LayeredModel *model)
{
    destruct_a(model);
    Heap_OperatorDeleteB(model);
    return model;
}
CLEAN_AS(func_02054b18, LayeredModel_DeleteA)

/* func_02054b64: its complete destructor, the same. */
LayeredModel *LayeredModel_DestructAComplete(LayeredModel *model)
{
    destruct_a(model);
    return model;
}
CLEAN_AS(func_02054b64, LayeredModel_DestructAComplete)

/* The constructor's work: the base model object, then this class's vtables, layer A's frame
 * control at frame 0 with speed 1.0, its Ramp, no animation object and no node. */
static void construct_a(LayeredModel *model)
{
    func_02054e8c(model);
    model->vtable = data_020dd0ac;
    model->base_frames.vtable = data_020dd0bc;
    model->base_ramp.vtable = data_020dd0cc;
    model->frames_a.vtable = data_020dd184;
    model->frames_a.frame = 0;
    model->frames_a.previous = 0;
    model->frames_a.speed = 0x1000;
    func_02056ee0(&model->ramp_a);
    model->anim_a = NULL;
    model->nodes_a[0] = 0;
    model->nodes_a[1] = 0;
}

/* func_02054bac: the constructor of the class with layer A. */
LayeredModel *LayeredModel_ConstructA(LayeredModel *model)
{
    construct_a(model);
    return model;
}
CLEAN_AS(func_02054bac, LayeredModel_ConstructA)

/* func_02054c2c: the same constructor, the one the class with both layers' starts with. */
LayeredModel *LayeredModel_ConstructABase(LayeredModel *model)
{
    construct_a(model);
    return model;
}
CLEAN_AS(func_02054c2c, LayeredModel_ConstructABase)
