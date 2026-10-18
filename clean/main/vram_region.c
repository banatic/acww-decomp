/* Regions of texture and palette VRAM, and loading textures into them (vram_region.h). */
#include "vram_region.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(offsetof(VramRegion, palette) == 0x0c, "VramRegion palette");
static_assert(offsetof(VramRegion, keys_given) == 0x11, "VramRegion keys_given");
static_assert(sizeof(VramRegion) == 0x14, "VramRegion size");

/* The region's vtable. */
extern const u8 data_020dd12c[];

/* NitroSystem's default VRAM allocators: a key for `size` bytes (`is_4x4` for the 4x4
 * compressed texture area), 0 when there is no room. */
extern VramKey (*NNS_GfdDefaultFuncAllocTexVram)(u32 size, int is_4x4, u32 options);
extern VramKey (*NNS_GfdDefaultFuncAllocPlttVram)(u32 size, int is_4x4, u32 options);

/* The bytes a texture resource needs in each area. */
extern u32 NNS_G3dTexGetRequiredSize(const void *texture);
extern u32 NNS_G3dTex4x4GetRequiredSize(const void *texture);
extern u32 NNS_G3dPlttGetRequiredSize(const void *texture);
/* The keys a texture resource is loaded to: its textures', its palettes' (func_02105178,
 * NitroSystem's NNS_G3dPlttSetPlttKey). */
extern void NNS_G3dTexSetTexKey(void *texture, VramKey key, VramKey key_4x4);
extern void func_02105178(void *texture, VramKey key);

extern void DC_FlushRange(const void *start, u32 size);
extern void NNS_G3dPlttLoad(void *texture, int exec_begin_end);

/* The texture resource's size, in its block header. */
static u32 texture_size(const void *texture)
{
    return ((const u32 *) texture)[1];
}

/* func_02055b34: the region takes the keys given. */
void VramRegion_SetKeys(VramRegion *region, VramKey texture, VramKey texture_4x4, VramKey palette)
{
    region->texture = texture;
    region->texture_4x4 = texture_4x4;
    region->palette = palette;
    region->keys_given = 1;
}
CLEAN_AS(func_02055b34, VramRegion_SetKeys)

/* func_02055b40: the region forgets its keys (they are not freed). */
void VramRegion_Clear(VramRegion *region)
{
    region->texture = 0;
    region->texture_4x4 = 0;
    region->palette = 0;
    region->in_use = 0;
    region->keys_given = 0;
}
CLEAN_AS(func_02055b40, VramRegion_Clear)

/* func_02055b50: the texture resource is given keys at the start of the region, each the size
 * it needs (nothing is sent to VRAM). */
void VramRegion_PlaceTexture(VramRegion *region, void *texture)
{
    u32 size = NNS_G3dTexGetRequiredSize(texture);
    u32 size_4x4 = NNS_G3dTex4x4GetRequiredSize(texture);
    u32 palette_size = NNS_G3dPlttGetRequiredSize(texture);
    VramKey key = VramRegion_TexKey(region, size);
    VramKey key_4x4 = VramRegion_Tex4x4Key(region, size_4x4);
    VramKey palette_key = VramRegion_PaletteKey(region, palette_size);
    NNS_G3dTexSetTexKey(texture, key, key_4x4);
    func_02105178(texture, palette_key);
    region->in_use = 1;
}
CLEAN_AS(func_02055b50, VramRegion_PlaceTexture)

/* func_02055bac: the palette key of `size` bytes that starts where `key`, a key at the start of
 * the region's palettes, ends. */
u32 VramRegion_PaletteKeyAfter(VramRegion *region, u32 key, u32 size)
{
    u32 address = ((region->palette & 0xffff) << 3) + ((key >> 16) << 3);
    return ((size >> 3) << 16) | ((address >> 3) & 0xffff);
}
CLEAN_AS(func_02055bac, VramRegion_PaletteKeyAfter)

/* func_02055bd8: the texture key of `size` bytes that starts where `key`, a key at the start of
 * `start`, ends; 4x4 when `key` is. */
VramKey VramRegion_TexKeyAt(void *unused, u32 size, VramKey start, VramKey key)
{
    (void) unused;
    u32 address = ((start & 0xffff) << 3) + (((key & 0x7fff0000) >> 16) << 4);
    return ((size >> 4) << 16) | ((address >> 3) & 0xffff) | (key & 0x80000000);
}
CLEAN_AS(func_02055bd8, VramRegion_TexKeyAt)

/* func_02055c18: the 4x4 texture key of `size` bytes after `key` in the region. */
VramKey VramRegion_Tex4x4KeyAfter(VramRegion *region, VramKey key, u32 size)
{
    return VramRegion_TexKeyAt(region, size, region->texture_4x4, key);
}
CLEAN_AS(func_02055c18, VramRegion_Tex4x4KeyAfter)

/* func_02055c2c: the plain texture key of `size` bytes after `key` in the region. */
VramKey VramRegion_TexKeyAfter(VramRegion *region, VramKey key, u32 size)
{
    return VramRegion_TexKeyAt(region, size, region->texture, key);
}
CLEAN_AS(func_02055c2c, VramRegion_TexKeyAfter)

/* func_02055c40: the palette key of `size` bytes at the start of the region's palettes. */
u32 VramRegion_PaletteKey(VramRegion *region, u32 size)
{
    return (region->palette & 0xffff) | ((size >> 3) << 16);
}
CLEAN_AS(func_02055c40, VramRegion_PaletteKey)

/* func_02055c54: `key` with its size made `size` bytes. */
u32 VramRegion_ResizeTexKey(u32 unused, u32 size, u32 key)
{
    (void) unused;
    return (key & 0x8000ffff) | ((size >> 4) << 16);
}
CLEAN_AS(func_02055c54, VramRegion_ResizeTexKey)

/* func_02055c68: the 4x4 texture key of `size` bytes at the start of the region. */
VramKey VramRegion_Tex4x4Key(VramRegion *region, u32 size)
{
    return VramRegion_ResizeTexKey((u32) (uintptr_t) region, size, region->texture_4x4);
}
CLEAN_AS(func_02055c68, VramRegion_Tex4x4Key)

/* func_02055c74: the plain texture key of `size` bytes at the start of the region. */
VramKey VramRegion_TexKey(VramRegion *region, u32 size)
{
    return VramRegion_ResizeTexKey((u32) (uintptr_t) region, size, region->texture);
}
CLEAN_AS(func_02055c74, VramRegion_TexKey)

/* func_02055c80: keys of the sizes given from the default VRAM allocators, each only when its
 * size is not 0 (a key stays as it was otherwise). 1.
 * QUIRK: a failed allocation is not noticed: its key is 0. */
int VramRegion_Alloc(VramRegion *region, u32 texture_size, u32 texture_4x4_size, u32 palette_size)
{
    if (texture_size != 0) {
        region->texture = NNS_GfdDefaultFuncAllocTexVram(texture_size, 0, 0);
    }
    if (texture_4x4_size != 0) {
        region->texture_4x4 = NNS_GfdDefaultFuncAllocTexVram(texture_4x4_size, 1, 0);
    }
    if (palette_size != 0) {
        region->palette = NNS_GfdDefaultFuncAllocPlttVram(palette_size, 0, 0);
    }
    region->in_use = 1;
    return 1;
}
CLEAN_AS(func_02055c80, VramRegion_Alloc)

/* func_02055cd0: the deleting destructor (the keys are not freed). */
VramRegion *VramRegion_Delete(VramRegion *region)
{
    region->vtable = data_020dd12c;
    Heap_OperatorDeleteB(region);
    return region;
}
CLEAN_AS(func_02055cd0, VramRegion_Delete)

/* func_02055ce8: the destructor (the keys are not freed). */
void VramRegion_Destruct(VramRegion *region)
{
    region->vtable = data_020dd12c;
}
CLEAN_AS(func_02055ce8, VramRegion_Destruct)

/* func_02055cf4: the constructor: no keys. */
VramRegion *VramRegion_Construct(VramRegion *region)
{
    region->vtable = data_020dd12c;
    VramRegion_Clear(region);
    return region;
}
CLEAN_AS(func_02055cf4, VramRegion_Construct)

/* func_02056064: the texture resource's textures, then its palettes, sent to VRAM at the start of
 * `region`, or anywhere (from the default allocators) when it is NULL. 1. */
int VramRegion_LoadTexture(void *texture, VramRegion *region)
{
    int images = VramRegion_LoadImages(texture, region);
    return images | VramRegion_LoadPalettes(texture, region);
}
CLEAN_AS(func_02056064, VramRegion_LoadTexture)

/* func_02056084: the texture resource's palettes sent to VRAM at the start of `region`, or
 * anywhere when it is NULL. 1. */
int VramRegion_LoadPalettes(void *texture, VramRegion *region)
{
    u32 size = NNS_G3dPlttGetRequiredSize(texture);
    VramKey key;
    if (region != NULL) {
        key = VramRegion_PaletteKey(region, size);
    } else {
        key = NNS_GfdDefaultFuncAllocPlttVram(size, 0, 0);
    }
    return VramRegion_LoadPalettesAt(texture, key);
}
CLEAN_AS(func_02056084, VramRegion_LoadPalettes)

/* func_020560c0: the texture resource's palettes given `key` and sent to VRAM (the whole
 * resource is flushed from the data cache first). 1. */
int VramRegion_LoadPalettesAt(void *texture, VramKey key)
{
    func_02105178(texture, key);
    DC_FlushRange(texture, texture_size(texture));
    NNS_G3dPlttLoad(texture, 1);
    return 1;
}
CLEAN_AS(func_020560c0, VramRegion_LoadPalettesAt)

/* func_020560e0: the texture resource's plain and 4x4 textures sent to VRAM at the start of
 * `region`, or anywhere when it is NULL. 1. */
int VramRegion_LoadImages(void *texture, VramRegion *region)
{
    u32 size = NNS_G3dTexGetRequiredSize(texture);
    u32 size_4x4 = NNS_G3dTex4x4GetRequiredSize(texture);
    VramKey key;
    VramKey key_4x4;
    if (region != NULL) {
        key = VramRegion_TexKey(region, size);
        key_4x4 = VramRegion_Tex4x4Key(region, size_4x4);
    } else {
        key = NNS_GfdDefaultFuncAllocTexVram(size, 0, 0);
        key_4x4 = NNS_GfdDefaultFuncAllocTexVram(size_4x4, 1, 0);
    }
    return VramRegion_LoadImagesAt(texture, key, key_4x4);
}
CLEAN_AS(func_020560e0, VramRegion_LoadImages)

/* NitroSystem: the texture resource's textures sent to VRAM at their keys (`exec_begin_end`
 * set: the VRAM banks are opened and closed around the copy). */
extern void NNS_G3dTexLoad(void *texture, int exec_begin_end);

/* func_02056140: the texture resource's plain and 4x4 textures given `key` and `key_4x4`, the
 * resource written back from the data cache, and its textures sent to VRAM. 1. */
int VramRegion_LoadImagesAt(void *texture, VramKey key, VramKey key_4x4)
{
    NNS_G3dTexSetTexKey(texture, key, key_4x4);
    DC_FlushRange(texture, texture_size(texture));
    NNS_G3dTexLoad(texture, 1);
    return 1;
}
CLEAN_AS(func_02056140, VramRegion_LoadImagesAt)
