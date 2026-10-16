/* A region of texture and palette VRAM kept for one set of textures (a C++ class of main,
 * vtable data_020dd12c, 0x14 bytes), and the loading of a texture resource (NitroSystem's
 * NNSG3dResTex) into such a region or anywhere in VRAM.
 *
 * A region is three keys of NitroSystem's VRAM managers: one for plain textures, one for 4x4
 * compressed textures (NNSGfdTexKey: the address / 8 in bits 0-15, the size / 16 in bits
 * 16-30, bit 31 set for 4x4) and one for palettes (NNSGfdPlttKey: the address / 8 in bits 0-15,
 * the size / 8 in bits 16-31). Its keys are allocated by the default allocators
 * (VramRegion_Alloc) or given (VramRegion_SetKeys); a texture placed in it starts at the start
 * of each, and a second one can be placed right after a first (VramRegion_TexKeyAfter and the
 * like). The pools of model files (model_pool.h) keep one per entry. */
#ifndef CLEAN_MAIN_VRAM_REGION_H
#define CLEAN_MAIN_VRAM_REGION_H

#include "types.h"

/* A key of NitroSystem's texture or palette VRAM manager (NNSGfdTexKey, NNSGfdPlttKey). */
typedef u32 VramKey;

typedef struct VramRegion {
    const void *vtable;  /* 0x00 */
    VramKey texture;     /* 0x04: for plain textures */
    VramKey texture_4x4; /* 0x08: for 4x4 compressed textures */
    VramKey palette;     /* 0x0c */
    u8 in_use;           /* 0x10: set once its keys are allocated or a texture is placed in it */
    u8 keys_given;       /* 0x11: set when its keys were given (VramRegion_SetKeys) */
    u8 pad_12[2];
} VramRegion;

void VramRegion_SetKeys(VramRegion *region, VramKey texture, VramKey texture_4x4, VramKey palette);
void VramRegion_Clear(VramRegion *region);
void VramRegion_PlaceTexture(VramRegion *region, void *texture);
u32 VramRegion_PaletteKeyAfter(VramRegion *region, u32 key, u32 size);
VramKey VramRegion_TexKeyAt(void *unused, u32 size, VramKey start, VramKey key);
VramKey VramRegion_Tex4x4KeyAfter(VramRegion *region, VramKey key, u32 size);
VramKey VramRegion_TexKeyAfter(VramRegion *region, VramKey key, u32 size);
u32 VramRegion_PaletteKey(VramRegion *region, u32 size);
u32 VramRegion_ResizeTexKey(u32 unused, u32 size, u32 key);
VramKey VramRegion_Tex4x4Key(VramRegion *region, u32 size);
VramKey VramRegion_TexKey(VramRegion *region, u32 size);
int VramRegion_Alloc(VramRegion *region, u32 texture_size, u32 texture_4x4_size, u32 palette_size);
VramRegion *VramRegion_Delete(VramRegion *region);
void VramRegion_Destruct(VramRegion *region);
VramRegion *VramRegion_Construct(VramRegion *region);
int VramRegion_LoadTexture(void *texture, VramRegion *region);
int VramRegion_LoadPalettes(void *texture, VramRegion *region);
int VramRegion_LoadPalettesAt(void *texture, VramKey key);
int VramRegion_LoadImages(void *texture, VramRegion *region);
int VramRegion_LoadImagesAt(void *texture, VramKey key, VramKey key_4x4);

#endif
