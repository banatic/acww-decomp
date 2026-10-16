/* A texture pattern animation played by copying texture images in VRAM (a C++ class of main,
 * vtable data_020dd164, 0x2c bytes, extending the frame control of frame_ctrl.h). Scene
 * objects' faces use it (scene_face.h).
 *
 * The animation (NitroSystem's NNSG3dResTexPatAnm) gives, for each material it animates, a
 * list of keys: from which whole frame on which of its named textures is shown. Instead of
 * binding textures to the model, each material keeps its texture's place in VRAM and, when its
 * key changes, the image of the new texture (from the texture resource given) is copied over it
 * by a queued transfer (the task of model_loader.h). A material can also be held on a texture
 * picked by name (TexPatternAnim_Hold, TexPatternAnim_Show) until it is let go again. */
#ifndef CLEAN_MAIN_TEX_PATTERN_ANIM_H
#define CLEAN_MAIN_TEX_PATTERN_ANIM_H

#include "autoload_2/heap.h"
#include "main/frame_ctrl.h"
#include "main/model_loader.h"
#include "types.h"

/* TexPatternAnimEntry.flags */
#define TEX_PATTERN_ANIM_HELD 0x01 /* the material is not animated (TexPatternAnim_Hold) */

/* The value of a byte or of the frame that nothing was shown for yet, and the material index
 * of a material the model does not have. */
#define TEX_PATTERN_ANIM_NONE 0xff
#define TEX_PATTERN_ANIM_NO_FRAME 0xffff

/* One material the animation plays on (0x28 bytes). */
typedef struct TexPatternAnimEntry {
    const u8 *keys;           /* 0x00: the animation's data for the material (key count at 0,
                                 offset of the keys from the animation at 6) */
    ModelLoaderTask transfer; /* 0x04: the copy of the current texture's image to VRAM */
    u8 texture;               /* 0x20: the index of the texture shown in the texture resource */
    u8 key;                   /* 0x21: the key shown */
    u8 material;              /* 0x22: the material's index in the model */
    u8 flags;                 /* 0x23: TEX_PATTERN_ANIM_HELD */
    u16 frame;                /* 0x24: the whole frame it was last updated for */
    u8 pad_26[2];
} TexPatternAnimEntry;

typedef struct TexPatternAnim {
    FrameCtrl ctrl;               /* 0x00: its vtable is the class's */
    u8 *model;                    /* 0x18: the model resource (NNSG3dResMdl) */
    void *texture;                /* 0x1c: the texture resource the images are taken from */
    const u8 *anim;               /* 0x20: the animation (NNSG3dResTexPatAnm) */
    u16 frames;                   /* 0x24: its frame count */
    u8 count;                     /* 0x26: the entries */
    TexPatternAnimEntry *entries; /* 0x28 */
} TexPatternAnim;

void TexPatternAnim_Release(TexPatternAnim *self, const char *material);
void TexPatternAnim_Hold(TexPatternAnim *self, const char *material);
int TexPatternAnim_Show(TexPatternAnim *self, const char *material, const char *texture);
void TexPatternAnim_Update(TexPatternAnim *self);
void TexPatternAnim_Step(TexPatternAnim *self);
void TexPatternAnim_Start(TexPatternAnim *self, void *anim_file, int start, int frames, u8 flags, fx32 speed);
void TexPatternAnim_Unload(TexPatternAnim *self);
int TexPatternAnim_Load(TexPatternAnim *self, u8 *model, u8 *texture_file, u8 count, Heap *heap);
void TexPatternAnim_Clear(TexPatternAnim *self);
TexPatternAnim *TexPatternAnim_Delete(TexPatternAnim *self);
TexPatternAnim *TexPatternAnim_Destruct(TexPatternAnim *self);
TexPatternAnim *TexPatternAnim_Construct(TexPatternAnim *self);
int TexPatternAnim_IsHeld(const TexPatternAnimEntry *entry);
void TexPatternAnim_CopyTexture(TexPatternAnimEntry *entry, u8 *model, u8 *texture);
void TexPatternAnim_UpdateEntry(TexPatternAnimEntry *entry, u32 frame, const u8 *anim, u8 *texture, u8 *model);
void TexPatternAnim_ReleaseEntry(TexPatternAnimEntry *entry);
int TexPatternAnim_InitEntry(TexPatternAnimEntry *entry);
void TexPatternAnim_ResetEntry(TexPatternAnimEntry *entry);
TexPatternAnimEntry *TexPatternAnim_ConstructEntry(TexPatternAnimEntry *entry);

#endif
