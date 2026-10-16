/* The VBlank queue's copies into texture and palette VRAM (vram_copy_task.h). */
#include "vram_copy_task.h"

#include "clean.h"

static_assert(offsetof(VramCopyTask, copy) == 0x10, "VramCopyTask");
static_assert(sizeof(VramCopyTask) == 0x1c, "VramCopyTask");
static_assert(offsetof(VramCopyMaterial, palette) == 0x1c, "VramCopyMaterial");
static_assert(sizeof(VramCopyMaterial) == 0x28, "VramCopyMaterial");

extern const u32 data_020e591c[]; /* VramCopyMaterial's vtable */
extern const u32 data_020e5928[]; /* VramCopyTask's */

extern void DC_FlushRange(const void *start, u32 size);
extern void NNS_G3dTexLoad(void *texture, int exec_begin_end);
extern void NNS_G3dPlttLoad(void *texture, int exec_begin_end);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *src, u32 dest, u32 size);
extern void GX_EndLoadTex(void);
extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(const void *src, u32 dest, u32 size);
extern void GX_EndLoadTexPltt(void);

/* The bytes of a copy one scan line stands for (as a shift). */
#define VRAM_COPY_LINE_SHIFT 11

/* The model resource's offset of its materials (NNSG3dResMat); the materials' dictionary of
 * materials follows the offsets of two other dictionaries. */
#define VRAM_COPY_MODEL_MATERIALS 0x08
#define VRAM_COPY_MATERIALS_DICT 0x04

/* The priority VramCopyMaterial_Queue and VramCopyTask_QueueMaterialImage give their tasks. */
#define VRAM_COPY_MATERIAL_PRIORITY 0
#define VRAM_COPY_MATERIAL_IMAGE_PRIORITY 2

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* Material `index` of a model resource (its dictionary's entry `index` holds the material's
 * offset from the materials).
 * QUIRK: nothing checks the index: -1 (a name G3dRes_MaterialIndex did not find) reads the
 * word before the dictionary's first entry as the offset. */
static const G3dResMaterial *material_at(const u8 *model, int index)
{
    const u8 *materials = model + read_u32(model + VRAM_COPY_MODEL_MATERIALS);
    const u8 *dict = materials + VRAM_COPY_MATERIALS_DICT;
    const u8 *entries = dict + read_u16(dict + 6);
    const u8 *entry = entries + 4 + read_u16(entries) * index;
    return (const G3dResMaterial *) (const void *) (materials + read_u32(entry));
}

/* func_020b9d3c: queued to copy image `texture_index` and palette `palette_index` of `texture`
 * over the image and palette the model's material `material` uses (priority 0); 1 when queued.
 * The copies take the material's sizes for the image and the palette's own size. */
int VramCopyMaterial_Queue(VramCopyMaterial *task, const u8 *model, const char *material, G3dResTex *texture,
                           int texture_index, int palette_index)
{
    VramCopyMaterial_Prepare(task);
    const G3dResMaterial *target = material_at(model, G3dRes_MaterialIndex(model, material));
    void *image = G3dRes_TextureImage(texture, texture_index);
    u8 *palette = G3dRes_Palette(texture, palette_index);
    unsigned int image_size = G3dRes_MaterialTextureSize(target);
    int palette_size = G3dRes_PaletteSize(texture, palette_index);

    task->base.kind = TRANSFER_KIND_MATERIAL;
    VramCopy_Set(&task->image, (int) G3dRes_MaterialTextureAddress(target), image, (int) image_size);
    VramCopy_Set(&task->palette, (int) G3dRes_MaterialPaletteAddress(target), palette, palette_size);
    task->base.lines = (u8) (VramCopy_ImageLines(&task->image) + VramCopy_PaletteLines(&task->palette));
    task->base.priority = VRAM_COPY_MATERIAL_PRIORITY;
    if (TransferQueue_QueueVBlank(&task->base) != 0) {
        return 1;
    }
    VramCopyMaterial_Clear(task);
    return 0;
}
CLEAN_AS(func_020b9d3c, VramCopyMaterial_Queue)

/* func_020b9df4: off the queue and its copies cleared, then marked queued. */
void VramCopyMaterial_Prepare(VramCopyMaterial *task)
{
    VramCopyMaterial_End(task);
    task->base.state = TRANSFER_TASK_QUEUED;
}
CLEAN_AS(func_020b9df4, VramCopyMaterial_Prepare)

/* func_020b9e08 (vtable slot 0): both copies, when the task is a material's; always 1. */
int VramCopyMaterial_Run(VramCopyMaterial *task)
{
    if (task->base.kind == TRANSFER_KIND_MATERIAL) {
        VramCopy_LoadImage(&task->image);
        VramCopy_LoadPalette(&task->palette);
    }
    return 1;
}
CLEAN_AS(func_020b9e08, VramCopyMaterial_Run)

/* func_020b9e2c: off the VBlank queue, its copies cleared.
 * QUIRK: unlike VramCopyTask_End, the kind, state and lines stay. */
void VramCopyMaterial_End(VramCopyMaterial *task)
{
    TransferQueue_UnqueueVBlank(&task->base);
    VramCopyMaterial_Clear(task);
}
CLEAN_AS(func_020b9e2c, VramCopyMaterial_End)

/* func_020b9e40 */
void VramCopyMaterial_Clear(VramCopyMaterial *task)
{
    VramCopy_Clear(&task->image);
    VramCopy_Clear(&task->palette);
}
CLEAN_AS(func_020b9e40, VramCopyMaterial_Clear)

/* func_020b9e58: the constructor. */
VramCopyMaterial *VramCopyMaterial_Construct(VramCopyMaterial *task)
{
    TransferTask_Construct(&task->base);
    task->base.vtable = data_020e591c;
    VramCopy_Clear(&task->image);
    VramCopy_Clear(&task->palette);
    return task;
}
CLEAN_AS(func_020b9e58, VramCopyMaterial_Construct)

/* func_020b9e80: queued to copy `image` over the texture image the model's material number
 * `material` uses (its size, priority 2); 1 when queued. */
int VramCopyTask_QueueMaterialImage(VramCopyTask *task, const u8 *model, int material, void *image)
{
    const G3dResMaterial *target = material_at(model, material);
    unsigned int size = G3dRes_MaterialTextureSize(target);
    unsigned int address = G3dRes_MaterialTextureAddress(target);
    return VramCopyTask_QueueImage(task, image, (int) address, (int) size, VRAM_COPY_MATERIAL_IMAGE_PRIORITY);
}
CLEAN_AS(func_020b9e80, VramCopyTask_QueueMaterialImage)

/* func_020b9ec4: off the VBlank queue and reset. */
void VramCopyTask_End(VramCopyTask *task)
{
    TransferQueue_UnqueueVBlank(&task->base);
    VramCopyTask_Reset(task);
}
CLEAN_AS(func_020b9ec4, VramCopyTask_End)

/* func_020b9ed8: off the queue and reset, then marked queued. */
void VramCopyTask_Prepare(VramCopyTask *task)
{
    VramCopyTask_End(task);
    task->base.state = TRANSFER_TASK_QUEUED;
}
CLEAN_AS(func_020b9ed8, VramCopyTask_Prepare)

/* func_020b9eec: queued to take the whole texture resource (its images and palettes) to the
 * VRAM keys it was given; 1 when queued. */
int VramCopyTask_QueueTexture(VramCopyTask *task, G3dResTex *texture, int priority)
{
    VramCopyTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_TEXTURE;
    VramCopy_Set(&task->copy, 0, texture, (int) texture->size);
    task->base.lines = VramCopy_TextureLines(&task->copy);
    task->base.priority = (u8) priority;
    if (TransferQueue_QueueVBlank(&task->base) != 0) {
        return 1;
    }
    VramCopyTask_Reset(task);
    return 0;
}
CLEAN_AS(func_020b9eec, VramCopyTask_QueueTexture)

/* func_020b9f30: queued to copy `size` bytes from `src` to texture palette VRAM at `dst`; 1
 * when queued. */
int VramCopyTask_QueuePalette(VramCopyTask *task, void *src, int dst, int size, u8 priority)
{
    VramCopyTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_TEXTURE_PALETTE;
    VramCopy_Set(&task->copy, dst, src, size);
    task->base.lines = (u8) VramCopy_PaletteLines(&task->copy);
    task->base.priority = priority;
    if (TransferQueue_QueueVBlank(&task->base) != 0) {
        return 1;
    }
    VramCopyTask_Reset(task);
    return 0;
}
CLEAN_AS(func_020b9f30, VramCopyTask_QueuePalette)

/* func_020b9f80: queued to copy `size` bytes from `src` to texture VRAM at `dst`; 1 when
 * queued. */
int VramCopyTask_QueueImage(VramCopyTask *task, void *src, int dst, int size, u8 priority)
{
    VramCopyTask_Prepare(task);
    task->base.kind = TRANSFER_KIND_TEXTURE_IMAGE;
    VramCopy_Set(&task->copy, dst, src, size);
    task->base.lines = VramCopy_ImageLines(&task->copy);
    task->base.priority = priority;
    if (TransferQueue_QueueVBlank(&task->base) != 0) {
        return 1;
    }
    VramCopyTask_Reset(task);
    return 0;
}
CLEAN_AS(func_020b9f80, VramCopyTask_QueueImage)

/* func_020b9fd0 (vtable slot 0): the copy its kind says; always 1. */
int VramCopyTask_Run(VramCopyTask *task)
{
    switch (task->base.kind) {
        case TRANSFER_KIND_TEXTURE:
            VramCopy_LoadTexture(&task->copy);
            break;
        case TRANSFER_KIND_TEXTURE_IMAGE:
            VramCopy_LoadImage(&task->copy);
            break;
        case TRANSFER_KIND_TEXTURE_PALETTE:
            VramCopy_LoadPalette(&task->copy);
            break;
    }
    return 1;
}
CLEAN_AS(func_020b9fd0, VramCopyTask_Run)

/* func_020ba004 */
void VramCopyTask_Reset(VramCopyTask *task)
{
    TransferTask_Reset(&task->base);
    VramCopy_Clear(&task->copy);
}
CLEAN_AS(func_020ba004, VramCopyTask_Reset)

/* func_020ba01c: the constructor. */
VramCopyTask *VramCopyTask_Construct(VramCopyTask *task)
{
    TransferTask_Construct(&task->base);
    task->base.vtable = data_020e5928;
    VramCopy_Clear(&task->copy);
    return task;
}
CLEAN_AS(func_020ba01c, VramCopyTask_Construct)

/* func_020ba118: the lines a whole texture resource needs: one for every 2 KB and one more
 * (the count kept to a byte). */
u8 VramCopy_TextureLines(const VramCopy *copy)
{
    return (u8) ((copy->size >> VRAM_COPY_LINE_SHIFT) + 1);
}
CLEAN_AS(func_020ba118, VramCopy_TextureLines)

/* func_020ba128: a palette needs one line. */
int VramCopy_PaletteLines(const VramCopy *copy)
{
    (void) copy;
    return 1;
}
CLEAN_AS(func_020ba128, VramCopy_PaletteLines)

/* func_020ba12c: the lines an image needs, as VramCopy_TextureLines. */
u8 VramCopy_ImageLines(const VramCopy *copy)
{
    return (u8) ((copy->size >> VRAM_COPY_LINE_SHIFT) + 1);
}
CLEAN_AS(func_020ba12c, VramCopy_ImageLines)

/* func_020ba13c: the texture resource's images and palettes to their VRAM keys.
 * HW: the data cache is flushed over the resource first, so the copies read it from memory. */
void VramCopy_LoadTexture(VramCopy *copy)
{
    G3dResTex *texture = copy->src;
    DC_FlushRange(texture, texture->size);
    NNS_G3dTexLoad(texture, 1);
    NNS_G3dPlttLoad(texture, 1);
}
CLEAN_AS(func_020ba13c, VramCopy_LoadTexture)

/* func_020ba160: the copy into texture palette VRAM.
 * HW: the cache flushed over the source, then the copy between the Begin and End that map the
 * palette banks to the CPU and back. */
void VramCopy_LoadPalette(VramCopy *copy)
{
    DC_FlushRange(copy->src, copy->size);
    GX_BeginLoadTexPltt();
    GX_LoadTexPltt(copy->src, copy->dst, copy->size);
    GX_EndLoadTexPltt();
}
CLEAN_AS(func_020ba160, VramCopy_LoadPalette)

/* func_020ba184: the copy into texture VRAM.
 * HW: as VramCopy_LoadPalette, with the texture banks. */
void VramCopy_LoadImage(VramCopy *copy)
{
    DC_FlushRange(copy->src, copy->size);
    GX_BeginLoadTex();
    GX_LoadTex(copy->src, copy->dst, copy->size);
    GX_EndLoadTex();
}
CLEAN_AS(func_020ba184, VramCopy_LoadImage)

/* func_020ba1a8 */
void VramCopy_Set(VramCopy *copy, int dst, void *src, int size)
{
    copy->dst = (u32) dst;
    copy->src = src;
    copy->size = (u32) size;
}
CLEAN_AS(func_020ba1a8, VramCopy_Set)

/* func_020ba1b0 */
void VramCopy_Clear(VramCopy *copy)
{
    copy->dst = 0;
    copy->src = NULL;
    copy->size = 0;
}
CLEAN_AS(func_020ba1b0, VramCopy_Clear)
