/* The items held in the hand and their entries in the held items' pool (held_item.h). */
#include "held_item.h"

#include <string.h>

#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "cloth_slots.h"
#include "frame_ctrl.h"
#include "g3d_resource.h"
#include "model_loader.h"
#include "vram_copy_task.h"
#include "fishing_float.h"
#include "g3d_tex_copy.h"
#include "globe.h"
#include "held_item_pool.h"
#include "item_info.h"

/* The ModelLoaderTask.state of a task that is queued. */
#define HELD_ITEM_TASK_QUEUED 1
/* The pool's code of an entry without an item. */
#define HELD_ITEM_NO_ITEM 0xfff1
/* The model kinds (func_0205f64c): no model; a model that also plays a texture SRT animation. */
#define HELD_ITEM_NO_MODEL 0x2b
#define HELD_ITEM_TEXTURE_ANIMATED 0x27
/* The items made from a design. */
#define HELD_ITEM_DESIGN_FIRST 0x13a0
#define HELD_ITEM_DESIGN_LAST 0x13a7
/* The fishing rods (their line takes kind 0 or 1) and the items whose line takes kind 2; other
 * items' lines take kind 3. */
#define HELD_ITEM_ROD_A 0x1374
#define HELD_ITEM_ROD_B 0x1375
#define HELD_ITEM_LINE_2_A 0x137a
#define HELD_ITEM_LINE_2_B 0x137b
/* The joint of the rods' model the line hangs from; other items use joint 0. */
#define HELD_ITEM_ROD_JOINT 2
/* The texture SRT animation's buffer and the room kept after it. */
#define HELD_ITEM_TEXTURE_ANIM_SIZE 0x210
#define HELD_ITEM_TEXTURE_ANIM_EXTRA 0x1c
#define HELD_ITEM_ALIGN 4
/* The texture SRT animation's start: looping, at speed 1.0 from frame 0. */
#define HELD_ITEM_TEXTURE_ANIM_FLAGS 1
#define HELD_ITEM_SPEED_ONE 0x1000
/* The animation action that starts texture SRT animation 1, and the line states the action
 * gives (HeldItem_Act). */
#define HELD_ITEM_ACTION_TEXTURE_ANIM 0x28
/* The line states in which its position is set again after the item is drawn. */
#define HELD_ITEM_LINE_STATE_7 7
#define HELD_ITEM_LINE_STATE_8 8

static_assert(offsetof(HeldItemObject, anim) == 0x08, "HeldItemObject.anim");
static_assert(offsetof(HeldItemObject, line) == 0x28, "HeldItemObject.line");
static_assert(offsetof(AnimatedModel, frames) == 0x9c, "AnimatedModel.frames");

extern u8 data_021ca16c[];       /* the held items' pool */
extern const u8 data_020dd754[]; /* HeldItemAnim's vtable */
/* The names of the texture a design is copied from ("cloth", in the clothes' file) and to
 * ("myD", in the item's model). */
extern const char data_020dd75c[];
extern const char data_020dd764[];

extern G3dResTex *func_021077e8(int file); /* the file's texture resource */
extern void *NNS_G3dGetTexSRTAnmSet(u8 *file);
extern u8 *func_02107bbc(void *set, u32 index);

/* The node callbacks, handed to the game. */
extern void func_0205ef28(void *state);
extern void func_0205ef5c(void *state);

static int held_item_is(ItemCode *item, ItemCode code)
{
    return *item == code;
}

/* func_0205e8d8: whether the line's state is 4 or 5. */
int HeldItem_LineState4Or5(HeldItemObject *held)
{
    return FishingFloat_IsInWater((FishingFloat *) &held->line);
}
CLEAN_AS(func_0205e8d8, HeldItem_LineState4Or5)

/* func_0205e8e4: the model of the item's entry, as an address. */
int HeldItem_Model(const unsigned char *held)
{
    return (int) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, *held);
}
CLEAN_AS(func_0205e8e4, HeldItem_Model)

/* func_0205e8f8: the world matrix of joint `joint` of the item's model as last drawn, all 0
 * without an item.
 * QUIRK: when the model keeps no result for the joint, `out` gets an unwritten matrix. */
void HeldItem_JointMatrix(Mtx43 *out, const u8 *held, u32 joint)
{
    Mtx43 matrix;
    int index = *held;
    if (*HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index) != HELD_ITEM_NO_ITEM) {
        ModelObject_JointMatrix(
            &((AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, index))->object,
            &matrix, (int) joint);
    } else {
        memset(&matrix, 0, sizeof(matrix));
    }
    *out = matrix;
}
CLEAN_AS(func_0205e8f8, HeldItem_JointMatrix)

/* func_0205e954: with an item, its model drawn at `matrix` with the item's scale on all three
 * axes; the line then follows the model's joint (HELD_ITEM_ROD_JOINT for the rods, else 0),
 * and in states 7 and 8 is put at that joint's position on the curved ground. */
void HeldItem_Draw(HeldItemObject *held, const Mtx43 *matrix)
{
    int index = held->index;
    if (*HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index) == HELD_ITEM_NO_ITEM) {
        return;
    }
    AnimatedModel *model = (AnimatedModel *) (uintptr_t) (HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, index));
    memcpy(model->object.unk_64, matrix, sizeof(Mtx43));
    Vec3 scale = {held->scale, held->scale, held->scale};
    AnimatedModel_Draw(model, &scale);

    Mtx43 joint;
    if (held_item_is(HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index), HELD_ITEM_ROD_A) ||
        held_item_is(HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index), HELD_ITEM_ROD_B)) {
        HeldItem_JointMatrix(&joint, &held->index, HELD_ITEM_ROD_JOINT);
    } else {
        HeldItem_JointMatrix(&joint, &held->index, 0);
    }
    FishingFloat_Draw((FishingFloat *) &held->line, &joint, &scale);
    Vec3 position = {joint.m[3][0], joint.m[3][1], joint.m[3][2]};
    Vec3 on_ground;
    Globe_Unbend(&on_ground, &position);
    if (held->line.state == HELD_ITEM_LINE_STATE_7 || held->line.state == HELD_ITEM_LINE_STATE_8) {
        Vec3 at = on_ground;
        FishingFloat_SetTarget((FishingFloat *) &held->line, &at);
    }
}
CLEAN_AS(func_0205e954, HeldItem_Draw)

/* func_0205ea60: with an item, its upload polled; with a model, the model's animation updated
 * and, for a texture-animated item, its material animation stepped and the frame given to the
 * animation object. The line is updated in any case. */
void HeldItem_Update(HeldItemObject *held)
{
    int index = held->index;
    if (*HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index) != HELD_ITEM_NO_ITEM) {
        HeldItem_PollUpload(data_021ca16c, index);
        int kind = HeldItemPool_ModelKind(HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index));
        if (kind != HELD_ITEM_NO_MODEL) {
            AnimatedModel_Update(
                (AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, index));
            if (kind == HELD_ITEM_TEXTURE_ANIMATED) {
                FrameCtrl_Step(&held->anim.ctrl);
                held->anim.anim->frame = held->anim.ctrl.frame;
            }
        }
    }
    FishingFloat_Update((FishingFloat *) &held->line);
}
CLEAN_AS(func_0205ea60, HeldItem_Update)

/* func_0205eac4: the speed of the item's model's animation. */
void HeldItem_SetAnimSpeed(unsigned char *held, int speed)
{
    ((AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, *held))->frames.speed = speed;
}
CLEAN_AS(func_0205eac4, HeldItem_SetAnimSpeed)

/* func_0205eae0: the item's model plays joint animation `action` (blended over `blend` frames,
 * with `flags`); some actions also set the line's state (0x13: 1, 0x15: 3, 0x16: 2, 0x18: 6,
 * 0x19 and 0x1b: 7, 0x1a: 8), and HELD_ITEM_ACTION_TEXTURE_ANIM starts texture animation 1. */
void HeldItem_Act(u8 *held, int action, int blend, int flags)
{
    HeldItemLine *line = (HeldItemLine *) (void *) (held + offsetof(HeldItemObject, line));
    HeldItemPool_PlayJointAnim((HeldItemPool *) (void *) data_021ca16c, held[0], action, blend, flags);
    switch (action) {
        case 0x13:
            FishingFloat_SetState((FishingFloat *) line, 1);
            break;
        case 0x15:
            FishingFloat_SetState((FishingFloat *) line, 3);
            break;
        case 0x16:
            FishingFloat_SetState((FishingFloat *) line, 2);
            break;
        case 0x18:
            FishingFloat_SetState((FishingFloat *) line, 6);
            break;
        case 0x19:
        case 0x1b:
            FishingFloat_SetState((FishingFloat *) line, 7);
            break;
        case 0x1a:
            FishingFloat_SetState((FishingFloat *) line, 8);
            break;
        case HELD_ITEM_ACTION_TEXTURE_ANIM:
            HeldItemPool_StartTextureAnim((HeldItemPool *) (void *) data_021ca16c, held[0], 1, flags);
            break;
    }
}
CLEAN_AS(func_0205eae0, HeldItem_Act)

/* func_0205eb8c: the item cleared, then set up again in its entry as `*item` with `record`,
 * without an owner. */
void HeldItem_Take(HeldItemObject *held, ItemCode *item, u8 *record)
{
    int index = held->index;
    HeldItem_Clear(held);
    HeldItem_Setup(held, index, NULL, item, record, 0);
}
CLEAN_AS(func_0205eb8c, HeldItem_Take)

/* func_0205ebb4: the line released; with a model, its joint animation taken off and the
 * material animation without object or model; the entry's animation link dropped, its model
 * released, its upload stopped, its heap emptied, its animation buffers forgotten and it holds
 * no item; the item then names no entry. */
void HeldItem_Clear(HeldItemObject *held)
{
    FishingFloat_Release((FishingFloat *) &held->line);
    int index = held->index;
    if (HeldItemPool_ModelKind(HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index)) != HELD_ITEM_NO_MODEL) {
        AnimatedModel_DetachJoints(
            (AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, index));
        held->anim.anim = NULL;
        held->anim.model = NULL;
    }
    HeldItemPool_SetMaterialAnim((HeldItemPool *) (void *) data_021ca16c, index, NULL);
    ModelObject_Release(
        &((AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, index))->object);
    HeldItemPool_StopUpload((HeldItemPool *) (void *) data_021ca16c, index);
    Heap_FreeAll((Heap *) (uintptr_t) HeldItemPool_Heap((HeldItemPool *) (void *) data_021ca16c, index));
    HeldItemPool_SetJointAnim((HeldItemPool *) (void *) data_021ca16c, index, (int) (uintptr_t) NULL, 0);
    HeldItemPool_SetTextureAnim((HeldItemPool *) (void *) data_021ca16c, index, (int) (uintptr_t) NULL, 0);
    HeldItemPool_SetTextureAnimHeap((HeldItemPool *) (void *) data_021ca16c, index, (unsigned long) (uintptr_t) NULL);
    *HeldItemPool_Code((HeldItemPool *) (void *) data_021ca16c, index) = HELD_ITEM_NO_ITEM;
    held->index = HELD_ITEM_NONE;
}
CLEAN_AS(func_0205ebb4, HeldItem_Clear)

/* func_0205ec50: the item takes entry `index` (its material animation linked to the entry) and
 * becomes `*item`. An item without a model number holds nothing. Otherwise its model file is
 * read; for a design item, unless `plain`, the design (from `record`) is loaded into the
 * clothes' scratch slot and its texture "cloth" (image, then palette) copied over the model's
 * "myD". The texture is placed and the model takes the file; with a model kind other than
 * HELD_ITEM_NO_MODEL its joint animation and results are allocated from the entry's heap, a
 * texture-animated item gets its texture animation (buffer, heap, file 0, attached to the
 * model, looping at speed 1.0), the rest of the heap becomes the joint animation's buffer, the
 * model plays joint animation `kind`, is attached, and unless `plain` gets the node callbacks
 * (func_0205ef5c, given the item). Last the line is set up with `owner` (kind 0 or 1 for the
 * rods, 2 for items 0x137a and 0x137b, else 3) and set to state 1 for the rods.
 * QUIRK: a texture-animated item takes 0x1c more bytes from its heap and never uses them. */
void HeldItem_Setup(HeldItemObject *held, int index, void *owner, ItemCode *item, u8 *record, int plain)
{
    u8 *pool = data_021ca16c;
    held->index = (u8) index;
    HeldItemPool_SetMaterialAnim((HeldItemPool *) (void *) pool, index, &held->anim);
    if (*item == HELD_ITEM_NO_ITEM) {
        *HeldItemPool_Code((HeldItemPool *) (void *) pool, index) = HELD_ITEM_NO_ITEM;
    } else {
        unsigned int number = ItemInfo_HeldModelNumber(item);
        if ((int) number >= 0 && number < ItemInfo_HeldModelCount()) {
            *HeldItemPool_Code((HeldItemPool *) (void *) pool, index) = *item;
            HeldItemPool_LoadModel((HeldItemPool *) (void *) pool, index, HeldItemPool_ModelNumber(item));
            int file = HeldItemPool_ModelFile((HeldItemPool *) (void *) pool, index);
            if (plain == 0 && *item >= HELD_ITEM_DESIGN_FIRST && *item <= HELD_ITEM_DESIGN_LAST) {
                u8 *scratch = (u8 *) (uintptr_t) ClothSlots_ScratchSlot();
                ClothSlots_Load(scratch, item, record, 0, 0);
                G3dResTex *design = func_021077e8(ClothSlots_SlotFile(scratch));
                G3dResTex *texture = func_021077e8(file);
                G3dTexCopy_Image(design, texture, data_020dd75c, data_020dd764);
                G3dTexCopy_Palette(design, texture, data_020dd75c, data_020dd764);
            }
            HeldItemPool_PlaceTexture((HeldItemPool *) (void *) pool, index);
            AnimatedModel *model = (AnimatedModel *) (uintptr_t) (HeldItemPool_Model((HeldItemPool *) (void *) pool, index));
            ModelObject_UseFileModel(&model->object, (u8 *) (uintptr_t) file);
            int kind = HeldItemPool_ModelKind(item);
            if (kind != HELD_ITEM_NO_MODEL) {
                AnimatedModel_LoadAnim(model, (Heap *) (uintptr_t) HeldItemPool_Heap((HeldItemPool *) (void *) pool, index));
                ModelObject_AllocJointResults(&model->object,
                                              (Heap *) (uintptr_t) HeldItemPool_Heap((HeldItemPool *) (void *) pool, index));
                if (kind == HELD_ITEM_TEXTURE_ANIMATED) {
                    Heap *heap = (Heap *) (uintptr_t) (HeldItemPool_Heap((HeldItemPool *) (void *) pool, index));
                    HeldItemPool_SetTextureAnim(
                        (HeldItemPool *) (void *) pool, index,
                        (int) (uintptr_t) Heap_AllocAligned(heap, HELD_ITEM_TEXTURE_ANIM_SIZE, HELD_ITEM_ALIGN),
                        HELD_ITEM_TEXTURE_ANIM_SIZE);
                    HeldItemPool_SetTextureAnimHeap((HeldItemPool *) (void *) pool, index, (unsigned long) (uintptr_t) heap);
                    Heap_AllocAligned(heap, HELD_ITEM_TEXTURE_ANIM_EXTRA, HELD_ITEM_ALIGN);
                    ModelAnim *anim =
                        (ModelAnim *) (uintptr_t) (HeldItemPool_MaterialAnim((HeldItemPool *) (void *) pool, index));
                    anim->anim = NULL;
                    anim->model = NULL;
                    HeldItemPool_LoadTextureAnim((HeldItemPool *) (void *) pool, index, 0);
                    u8 *texture_anim = func_02107bbc(NNS_G3dGetTexSRTAnmSet((u8 *) (uintptr_t) HeldItemPool_TextureAnim(
                                                         (HeldItemPool *) (void *) pool, index)),
                                                     0);
                    u8 *resource = model->object.model;
                    ModelAnim_AllocMaterialAnim(
                        anim, resource,
                        (Heap *) (uintptr_t) HeldItemPool_TextureAnimHeap((HeldItemPool *) (void *) pool, index));
                    ModelAnim_Start(anim, texture_anim, HELD_ITEM_TEXTURE_ANIM_FLAGS, HELD_ITEM_SPEED_ONE, 0);
                    ModelAnim_Attach(anim, ModelObject_RenderObject(&model->object));
                }
                Heap *heap = (Heap *) (uintptr_t) (HeldItemPool_Heap((HeldItemPool *) (void *) pool, index));
                int size = Heap_GetFreeSize(heap);
                HeldItemPool_SetJointAnim((HeldItemPool *) (void *) pool, index,
                                          (int) (uintptr_t) Heap_AllocAligned(heap, size, HELD_ITEM_ALIGN), size);
                HeldItemPool_PlayJointAnim((HeldItemPool *) (void *) pool, index, kind, 0, 0);
                AnimatedModel_Attach(model);
                if (plain == 0) {
                    ModelObject_SetNodeCallback(&model->object, (void *) (uintptr_t) func_0205ef5c, G3D_COMMAND_NODE_DESC,
                                                G3D_TIMING_A, held, NULL);
                }
            }
        } else {
            *HeldItemPool_Code((HeldItemPool *) (void *) pool, index) = HELD_ITEM_NO_ITEM;
        }
    }

    unsigned int line_kind;
    if (held_item_is(item, HELD_ITEM_ROD_B)) {
        line_kind = 1;
    } else if (held_item_is(item, HELD_ITEM_ROD_A)) {
        line_kind = 0;
    } else if (held_item_is(item, HELD_ITEM_LINE_2_A) || held_item_is(item, HELD_ITEM_LINE_2_B)) {
        line_kind = 2;
    } else {
        line_kind = 3;
    }
    FishingFloat_Setup((FishingFloat *) &held->line, index, owner, line_kind);
    if (held_item_is(item, HELD_ITEM_ROD_A) || held_item_is(item, HELD_ITEM_ROD_B)) {
        FishingFloat_SetState((FishingFloat *) &held->line, 1);
    }
}
CLEAN_AS(func_0205ec50, HeldItem_Setup)

/* func_0205ef28: the node callback after a node: the item's model's (AnimatedModel_AfterNode),
 * then HeldItem_BeforeNode for the next node. */
void HeldItem_AfterNode(void *state)
{
    G3dRenderState *node = state;
    HeldItemObject *held = node->object->user;
    if (held != NULL) {
        AnimatedModel_AfterNode(
            (AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, held->index), state);
    }
    node->hooks[G3D_COMMAND_NODE_DESC] = (u32) (uintptr_t) func_0205ef5c;
    node->hook_timings[G3D_COMMAND_NODE_DESC] = G3D_TIMING_A;
}
CLEAN_AS(func_0205ef28, HeldItem_AfterNode)

/* func_0205ef5c: the node callback before a node: the item's model's
 * (AnimatedModel_BeforeNode), then HeldItem_AfterNode after it. */
void HeldItem_BeforeNode(void *state)
{
    G3dRenderState *node = state;
    HeldItemObject *held = node->object->user;
    if (held != NULL) {
        AnimatedModel_BeforeNode(
            (AnimatedModel *) (uintptr_t) HeldItemPool_Model((HeldItemPool *) (void *) data_021ca16c, held->index), state);
    }
    node->hooks[G3D_COMMAND_NODE_DESC] = (u32) (uintptr_t) func_0205ef28;
    node->hook_timings[G3D_COMMAND_NODE_DESC] = G3D_TIMING_B;
}
CLEAN_AS(func_0205ef5c, HeldItem_BeforeNode)

/* func_0205ef90: the item's destructor: the line's, then the material animation's. Returns the
 * item. */
HeldItemObject *HeldItem_Destruct(HeldItemObject *held)
{
    FishingFloat_Destruct(&held->line);
    HeldItemAnim_Destruct(&held->anim);
    return held;
}
CLEAN_AS(func_0205ef90, HeldItem_Destruct)

/* func_0205efac: the item's constructor: the material animation, the line, no entry and scale
 * 1.0. Returns the item. */
HeldItemObject *HeldItem_Construct(HeldItemObject *held)
{
    HeldItemAnim_Construct(&held->anim);
    FishingFloat_Construct((FishingFloat *) &held->line);
    held->index = HELD_ITEM_NONE;
    held->scale = HELD_ITEM_SPEED_ONE;
    return held;
}
CLEAN_AS(func_0205efac, HeldItem_Construct)

/* func_0205efd4: the material animation's deleting destructor. */
ModelAnim *HeldItemAnim_Delete(ModelAnim *anim)
{
    anim->ctrl.vtable = data_020dd754;
    ModelAnim_Destruct(anim);
    Heap_OperatorDeleteB(anim);
    return anim;
}
CLEAN_AS(func_0205efd4, HeldItemAnim_Delete)

/* func_0205eff4: the material animation's destructor (a ModelAnim's, with its own vtable). */
ModelAnim *HeldItemAnim_Destruct(ModelAnim *anim)
{
    anim->ctrl.vtable = data_020dd754;
    ModelAnim_Destruct(anim);
    return anim;
}
CLEAN_AS(func_0205eff4, HeldItemAnim_Destruct)

/* func_0205f00c: the material animation's constructor: a ModelAnim's, then its own vtable. */
ModelAnim *HeldItemAnim_Construct(ModelAnim *anim)
{
    ModelAnim_ConstructBase(anim);
    anim->ctrl.vtable = data_020dd754;
    return anim;
}
CLEAN_AS(func_0205f00c, HeldItemAnim_Construct)

/* func_0205f024: whether the texture of entry `index`'s model is in VRAM (its task done); when
 * the task is neither done nor queued, the model file's texture is queued. */
int HeldItem_PollUpload(u8 *pool, int index)
{
    ModelLoaderTask *task = HeldItemPool_Task((HeldItemPool *) (void *) pool, index);
    if (task->state == MODEL_LOADER_TASK_DONE) {
        return 1;
    }
    if (task->state != HELD_ITEM_TASK_QUEUED) {
        VramCopyTask_QueueTexture((VramCopyTask *) task,
                                  func_021077e8(HeldItemPool_ModelFile((HeldItemPool *) (void *) pool, index)), 1);
    }
    return 0;
}
CLEAN_AS(func_0205f024, HeldItem_PollUpload)
