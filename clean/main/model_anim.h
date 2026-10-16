/* One animation of a model resource (a C++ class of main, vtable data_020dd154, 0x20 bytes): a
 * frame control (frame_ctrl.h, the class it extends) and NitroSystem's animation object
 * (NNSG3dAnmObj) for the model. The object is allocated for a kind of animation (joints or
 * materials), started from an animation file at a frame, and attached to a render object
 * (NNSG3dRenderObj) to play on it. Its owners copy the frame control's frame into the object.
 *
 * Overlay 3's countdown, mailbox and villager houses and overlay 4's room objects use it. */
#ifndef CLEAN_MAIN_MODEL_ANIM_H
#define CLEAN_MAIN_MODEL_ANIM_H

#include "autoload_2/heap.h"
#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/model_object.h"
#include "types.h"

typedef struct ModelAnim {
    FrameCtrl ctrl;          /* 0x00: its vtable is the class's */
    AnimatedModelAnim *anim; /* 0x18: NULL until allocated */
    u8 *model;               /* 0x1c: the model resource it was allocated for */
} ModelAnim;

void ModelAnim_Detach(ModelAnim *anim, ModelRenderObject *render);
void ModelAnim_Attach(ModelAnim *anim, ModelRenderObject *render);
void ModelAnim_RestartTextured(ModelAnim *anim, ModelRenderObject *render, const u8 *file, void *texture, u8 flags, fx32 speed,
                               u16 start);
void ModelAnim_StartTextured(ModelAnim *anim, const u8 *file, void *texture, int flags, fx32 speed, u16 start);
void ModelAnim_Restart(ModelAnim *anim, ModelRenderObject *render, const u8 *file, int flags, fx32 speed, u16 start);
void ModelAnim_Start(ModelAnim *anim, const u8 *file, int flags, fx32 speed, u16 start);
void ModelAnim_Init(ModelAnim *anim, const u8 *file, void *texture, int flags, fx32 speed, u16 start);
int ModelAnim_AllocJointAnim(ModelAnim *anim, u8 *model, Heap *heap);
int ModelAnim_AllocMaterialAnim(ModelAnim *anim, u8 *model, Heap *heap);
AnimatedModelAnim *ModelAnim_AllocAnmObj(u8 *model, const void *kind, Heap *heap);
ModelAnim *ModelAnim_Destruct(ModelAnim *anim);
ModelAnim *ModelAnim_Delete(ModelAnim *anim);
ModelAnim *ModelAnim_DestructComplete(ModelAnim *anim);
void ModelAnim_Construct(ModelAnim *anim);
void ModelAnim_ConstructBase(ModelAnim *anim);

#endif
