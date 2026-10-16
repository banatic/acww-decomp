/* A texture pattern animation played by copying textures into one texture slot (a C++ class of
 * main, vtable data_020dd194, 0x90 bytes, extending the frame control of frame_ctrl.h). The
 * slot is a texture and a palette, named, of a texture resource in VRAM (the target); for the
 * whole frame the frame control is at, the animation (NitroSystem's NNSG3dResTexPatAnm, its
 * first material) names a texture and a palette of a source texture resource in main memory,
 * and when they change, their image and data are copied over the slot's (tex_upload.h).
 *
 * Overlay 3's and overlay 4's objects make one. */
#ifndef CLEAN_MAIN_TEX_SLOT_ANIM_H
#define CLEAN_MAIN_TEX_SLOT_ANIM_H

#include "main/frame_ctrl.h"
#include "main/g3d_resource.h"
#include "main/tex_upload.h"
#include "types.h"

/* TexSlotAnim's indices before anything was copied, and a texture or palette not to copy. */
#define TEX_SLOT_ANIM_NONE (-1)

/* The length of a slot's names, their end included. */
#define TEX_SLOT_NAME_SIZE 17

/* A name of the slot (a C++ class of main without a vtable). */
typedef struct TexSlotName {
    char text[TEX_SLOT_NAME_SIZE];
} TexSlotName;

typedef struct TexSlotAnim {
    FrameCtrl ctrl;           /* 0x00: its vtable is the class's */
    TexUpload upload;         /* 0x18 */
    G3dResTex *target;        /* 0x50: the texture resource in VRAM holding the slot */
    TexSlotName texture_name; /* 0x54: the slot's texture */
    TexSlotName palette_name; /* 0x65: the slot's palette */
    u8 pad_76[2];
    G3dResTex *source;    /* 0x78: the texture resource the animation's textures are in */
    const u8 *anim;       /* 0x7c: the animation (NNSG3dResTexPatAnm) */
    int palette;          /* 0x80: the source's palette copied last */
    int texture;          /* 0x84: the source's texture copied last */
    int previous_texture; /* 0x88: `texture` before the last update */
    u8 palette_only;      /* 0x8c: the slot's texture is left as it is */
    u8 pad_8d[3];
} TexSlotAnim;

void TexSlotAnim_CurrentIndices(TexSlotAnim *self, int *texture, int *palette);
int TexSlotAnim_Update(TexSlotAnim *self);
int TexSlotAnim_Start(TexSlotAnim *self, G3dResTex *target, const char *texture_name, const char *palette_name,
                      G3dResTex *source, const u8 *anim, u8 palette_only);
void TexSlotAnim_Clear(TexSlotAnim *self);
TexSlotAnim *TexSlotAnim_Delete(TexSlotAnim *self);
TexSlotAnim *TexSlotAnim_Destruct(TexSlotAnim *self);
TexSlotAnim *TexSlotAnim_Construct(TexSlotAnim *self);
const char *TexSlotName_Text(const TexSlotName *name);
void TexSlotName_Set(TexSlotName *name, const char *text);
void TexSlotName_Destruct(TexSlotName *name);
void TexSlotName_Construct(TexSlotName *name);

#endif
