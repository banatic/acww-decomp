/* The copy of a texture's image and a palette from a texture resource in main memory over a
 * texture and a palette of a texture resource already in VRAM (a C++ class of main without a
 * vtable, 0x38 bytes): two queued transfer tasks (model_loader.h), one for the image, one for
 * the palette. Both resources are NitroSystem's NNSG3dResTex (g3d_resource.h); the textures and
 * palettes are given by index (-1 for none) or by name.
 *
 * The design textures (design_assets.h) and the texture slot animation (tex_slot_anim.h) use
 * it. */
#ifndef CLEAN_MAIN_TEX_UPLOAD_H
#define CLEAN_MAIN_TEX_UPLOAD_H

#include "main/g3d_resource.h"
#include "main/model_loader.h"
#include "types.h"

typedef struct TexUpload {
    ModelLoaderTask image;   /* 0x00: the copy of the texture's image */
    ModelLoaderTask palette; /* 0x1c: the copy of the palette */
} TexUpload;

int TexUpload_SendByName(TexUpload *upload, G3dResTex *target, const char *texture, const char *palette, G3dResTex *source,
                         int source_texture, int source_palette);
int TexUpload_Send(TexUpload *upload, G3dResTex *target, int texture, int palette, G3dResTex *source, int source_texture,
                   u32 source_palette);
TexUpload *TexUpload_Destruct(TexUpload *upload);
TexUpload *TexUpload_Construct(TexUpload *upload);

#endif
