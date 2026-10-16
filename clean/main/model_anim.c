/* One animation of a model resource (model_anim.h). */
#include "model_anim.h"

#include "clean.h"

static_assert(offsetof(ModelAnim, anim) == 0x18, "ModelAnim anim");
static_assert(sizeof(ModelAnim) == 0x20, "ModelAnim size");

/* The class's vtable and the frame control's. */
extern const u8 data_020dd154[];
extern const u8 data_020dd184[];

/* The kinds of animation object, as NitroSystem names them in the animation files: joint
 * animations ("J\0AC") and the material animations of kind "M\0AT". */
extern const u8 data_020dd144[];
extern const u8 data_020dd148[];

/* NitroSystem's NNS_G3dAnmObjCalcSizeRequired: the bytes an animation object of the kind of
 * `kind` for `model` takes. */
extern u32 NNS_G3dAnmObjCalcSizeRequired__autoload_2_021055f8(const void *kind, const u8 *model);
extern void NNS_G3dAnmObjInit(AnimatedModelAnim *anim, const u8 *file, u8 *model, void *texture);
extern void NNS_G3dRenderObjAddAnmObj(ModelRenderObject *render, AnimatedModelAnim *anim);
extern void NNS_G3dRenderObjRemoveAnmObj(ModelRenderObject *render, AnimatedModelAnim *anim);

/* The current heap. */
extern Heap *data_021fbe94;

/* The frame count of an animation file (its u16 at 4). */
static u16 file_frames(const u8 *file)
{
    return *(const u16 *) (const void *) (file + 4);
}

/* The frame control's constructor, as the class's constructors have it inline: frame 0, a
 * speed of one frame a step. */
static void construct_frame_ctrl(FrameCtrl *ctrl)
{
    ctrl->vtable = data_020dd184;
    ctrl->frame = 0;
    ctrl->previous = 0;
    ctrl->speed = 0x1000;
}

/* func_020563cc: the animation taken off `render`. */
void ModelAnim_Detach(ModelAnim *anim, ModelRenderObject *render)
{
    NNS_G3dRenderObjRemoveAnmObj(render, anim->anim);
}
CLEAN_AS(func_020563cc, ModelAnim_Detach)

/* func_020563dc: the animation put on `render`. */
void ModelAnim_Attach(ModelAnim *anim, ModelRenderObject *render)
{
    NNS_G3dRenderObjAddAnmObj(render, anim->anim);
}
CLEAN_AS(func_020563dc, ModelAnim_Attach)

/* func_020563ec: the animation taken off `render`, started again from `file` with `texture`
 * (ModelAnim_Init) and put back on. */
void ModelAnim_RestartTextured(ModelAnim *anim, ModelRenderObject *render, const u8 *file, void *texture, u8 flags, fx32 speed,
                               u16 start)
{
    ModelAnim_Detach(anim, render);
    ModelAnim_Init(anim, file, texture, flags, speed, start);
    ModelAnim_Attach(anim, render);
}
CLEAN_AS(func_020563ec, ModelAnim_RestartTextured)

/* func_02056424: ModelAnim_Init. */
void ModelAnim_StartTextured(ModelAnim *anim, const u8 *file, void *texture, int flags, fx32 speed, u16 start)
{
    ModelAnim_Init(anim, file, texture, flags, speed, start);
}
CLEAN_AS(func_02056424, ModelAnim_StartTextured)

/* func_02056440: the animation taken off `render`, started again from `file` without a texture
 * and put back on. */
void ModelAnim_Restart(ModelAnim *anim, ModelRenderObject *render, const u8 *file, int flags, fx32 speed, u16 start)
{
    ModelAnim_Detach(anim, render);
    ModelAnim_Init(anim, file, NULL, flags, speed, start);
    ModelAnim_Attach(anim, render);
}
CLEAN_AS(func_02056440, ModelAnim_Restart)

/* func_02056478: ModelAnim_Init without a texture. */
void ModelAnim_Start(ModelAnim *anim, const u8 *file, int flags, fx32 speed, u16 start)
{
    ModelAnim_Init(anim, file, NULL, flags, speed, start);
}
CLEAN_AS(func_02056478, ModelAnim_Start)

/* func_02056498: the frame control set to the file's frame count with `flags` (FrameCtrlFlags,
 * the low byte kept), `speed` and `start` (FrameCtrl_Init), the animation object made to play
 * `file` on the model with `texture`, and its frame set to `start`.
 * QUIRK: a `start` of 0xffff makes the frame control start at the last frame, but the object's
 * frame is still set to frame 0xffff, until its owner copies the frame control's into it. */
void ModelAnim_Init(ModelAnim *anim, const u8 *file, void *texture, int flags, fx32 speed, u16 start)
{
    FrameCtrl_Init(&anim->ctrl, file_frames(file), (u8) flags, (u32) speed, start);
    NNS_G3dAnmObjInit(anim->anim, file, anim->model, texture);
    anim->anim->frame = (fx32) start << 12;
}
CLEAN_AS(func_02056498, ModelAnim_Init)

/* func_020564d0: a joint animation object for `model` allocated from `heap` (NULL: the current
 * heap). 0 when the animation already has an object or a model, or the heap is full. */
int ModelAnim_AllocJointAnim(ModelAnim *anim, u8 *model, Heap *heap)
{
    if (anim->anim != NULL || anim->model != NULL) {
        return 0;
    }
    anim->anim = ModelAnim_AllocAnmObj(model, data_020dd144, heap);
    anim->model = model;
    return anim->anim != NULL;
}
CLEAN_AS(func_020564d0, ModelAnim_AllocJointAnim)

/* func_0205650c: ModelAnim_AllocJointAnim for a material animation of kind "M\0AT". */
int ModelAnim_AllocMaterialAnim(ModelAnim *anim, u8 *model, Heap *heap)
{
    if (anim->anim != NULL || anim->model != NULL) {
        return 0;
    }
    anim->anim = ModelAnim_AllocAnmObj(model, data_020dd148, heap);
    anim->model = model;
    return anim->anim != NULL;
}
CLEAN_AS(func_0205650c, ModelAnim_AllocMaterialAnim)

/* func_02056548: room for an animation object of the kind of `kind` for `model` from `heap`
 * (NULL: the current heap), not yet set up; NULL without a model or when the heap is full. */
AnimatedModelAnim *ModelAnim_AllocAnmObj(u8 *model, const void *kind, Heap *heap)
{
    if (model == NULL) {
        return NULL;
    }
    u32 size = NNS_G3dAnmObjCalcSizeRequired__autoload_2_021055f8(kind, model);
    if (heap == NULL) {
        heap = data_021fbe94;
    }
    return Heap_Alloc(heap, (int) size);
}
CLEAN_AS(func_02056548, ModelAnim_AllocAnmObj)

/* func_02056578: the destructor. The animation object is not freed. */
ModelAnim *ModelAnim_Destruct(ModelAnim *anim)
{
    anim->ctrl.vtable = data_020dd154;
    FrameCtrl_Destruct(&anim->ctrl);
    return anim;
}
CLEAN_AS(func_02056578, ModelAnim_Destruct)

/* func_02056590: the deleting destructor (the vtable's second entry). */
ModelAnim *ModelAnim_Delete(ModelAnim *anim)
{
    anim->ctrl.vtable = data_020dd154;
    FrameCtrl_Destruct(&anim->ctrl);
    Heap_OperatorDeleteB(anim);
    return anim;
}
CLEAN_AS(func_02056590, ModelAnim_Delete)

/* func_020565b0: the complete destructor (the vtable's first entry), the same as
 * ModelAnim_Destruct. */
ModelAnim *ModelAnim_DestructComplete(ModelAnim *anim)
{
    anim->ctrl.vtable = data_020dd154;
    FrameCtrl_Destruct(&anim->ctrl);
    return anim;
}
CLEAN_AS(func_020565b0, ModelAnim_DestructComplete)

/* func_020565c8: the constructor: the frame control's, then no object and no model. */
void ModelAnim_Construct(ModelAnim *anim)
{
    construct_frame_ctrl(&anim->ctrl);
    anim->ctrl.vtable = data_020dd154;
    anim->model = NULL;
    anim->anim = NULL;
}
CLEAN_AS(func_020565c8, ModelAnim_Construct)

/* func_020565ec: the base constructor, the same as ModelAnim_Construct. */
void ModelAnim_ConstructBase(ModelAnim *anim)
{
    construct_frame_ctrl(&anim->ctrl);
    anim->ctrl.vtable = data_020dd154;
    anim->model = NULL;
    anim->anim = NULL;
}
CLEAN_AS(func_020565ec, ModelAnim_ConstructBase)
