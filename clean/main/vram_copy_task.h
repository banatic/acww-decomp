/* The VBlank queue's tasks (transfer_task.h, kinds 0 to 3): copies into the 3D engine's texture
 * and palette VRAM, run in the VBlank interrupt when there are lines enough left for them.
 *
 * A VramCopyTask (vtable data_020e5928, 0x1c bytes) copies one block: a whole texture resource
 * (its images and palettes, through NitroSystem), an image into texture VRAM or a palette into
 * texture palette VRAM. A VramCopyMaterial (vtable data_020e591c, 0x28 bytes) copies a texture's
 * image and one of its palettes over those a model's material uses, so the material shows the
 * new texture. Neither class has a reset in its vtable's second slot.
 *
 * Each queue function first takes the task off the queue and resets it, then sets it up, marks
 * it queued and queues it; it answers 1 when it is queued (always, the queue takes any task),
 * else resets it again and answers 0. A copy needs one scan line for every 2 KB and one more; a
 * palette one line. */
#ifndef CLEAN_MAIN_VRAM_COPY_TASK_H
#define CLEAN_MAIN_VRAM_COPY_TASK_H

#include "g3d_resource.h"
#include "transfer_task.h"
#include "types.h"

/* One copy: `size` bytes from `src` to the VRAM offset `dst` (for a whole texture resource,
 * `dst` is 0 and `src` the resource). */
typedef struct VramCopy {
    u32 dst;   /* 0x00 */
    void *src; /* 0x04 */
    u32 size;  /* 0x08 */
} VramCopy;

typedef struct VramCopyTask {
    TransferTask base;
    VramCopy copy; /* 0x10 */
} VramCopyTask;

typedef struct VramCopyMaterial {
    TransferTask base;
    VramCopy image;   /* 0x10: into texture VRAM */
    VramCopy palette; /* 0x1c: into texture palette VRAM */
} VramCopyMaterial;

int VramCopyMaterial_Queue(VramCopyMaterial *task, const u8 *model, const char *material, G3dResTex *texture,
                           int texture_index, int palette_index);
void VramCopyMaterial_Prepare(VramCopyMaterial *task);
int VramCopyMaterial_Run(VramCopyMaterial *task);
void VramCopyMaterial_End(VramCopyMaterial *task);
void VramCopyMaterial_Clear(VramCopyMaterial *task);
VramCopyMaterial *VramCopyMaterial_Construct(VramCopyMaterial *task);
int VramCopyTask_QueueMaterialImage(VramCopyTask *task, const u8 *model, int material, void *image);
void VramCopyTask_End(VramCopyTask *task);
void VramCopyTask_Prepare(VramCopyTask *task);
int VramCopyTask_QueueTexture(VramCopyTask *task, G3dResTex *texture, int priority);
int VramCopyTask_QueuePalette(VramCopyTask *task, void *src, int dst, int size, u8 priority);
int VramCopyTask_QueueImage(VramCopyTask *task, void *src, int dst, int size, u8 priority);
int VramCopyTask_Run(VramCopyTask *task);
void VramCopyTask_Reset(VramCopyTask *task);
VramCopyTask *VramCopyTask_Construct(VramCopyTask *task);
u8 VramCopy_TextureLines(const VramCopy *copy);
int VramCopy_PaletteLines(const VramCopy *copy);
u8 VramCopy_ImageLines(const VramCopy *copy);
void VramCopy_LoadTexture(VramCopy *copy);
void VramCopy_LoadPalette(VramCopy *copy);
void VramCopy_LoadImage(VramCopy *copy);
void VramCopy_Set(VramCopy *copy, int dst, void *src, int size);
void VramCopy_Clear(VramCopy *copy);

#endif
