/* Lookups in NitroSystem's 3D resources (g3d_resource.h). */
#include "g3d_resource.h"

#include <string.h>

#include "clean.h"

static_assert(offsetof(G3dResTex, tex_images) == 0x14, "G3dResTex tex_images");
static_assert(offsetof(G3dResTex, tex4x4_vram_key) == 0x18, "G3dResTex tex4x4_vram_key");
static_assert(offsetof(G3dResTex, palette_vram_key) == 0x2c, "G3dResTex palette_vram_key");
static_assert(offsetof(G3dResTex, palette_dict) == 0x34, "G3dResTex palette_dict");
static_assert(offsetof(G3dResTex, texture_dict) == 0x3c, "G3dResTex texture_dict");
static_assert(offsetof(G3dResMaterial, tex_image_param) == 0x14, "G3dResMaterial tex_image_param");
static_assert(offsetof(G3dResMaterial, palette_base) == 0x1c, "G3dResMaterial palette_base");
static_assert(offsetof(G3dResMaterial, width_scale) == 0x24, "G3dResMaterial width_scale");

/* The width and height of a texture by their TEXIMAGE_PARAM code (8 << code). */
extern const u16 data_020dd19c[];

/* NitroSystem: the index of a 16-byte name in a resource dictionary, -1 when it is not there. */
extern int NNS_G3dGetResDictIdxByName(const u8 *dict, const void *name);

/* The model resource's offset of its materials (NNSG3dResMat), and of its dictionary of nodes. */
#define MODEL_MATERIALS 0x08
#define MODEL_NODE_DICT 0x40
/* The materials' dictionary of materials, after the offsets of two other dictionaries. */
#define MATERIALS_DICT 0x04

/* A texture's entry: TEXIMAGE_PARAM at 0, the original size at 4. A palette's entry: its offset
 * / 8 at 0 (a halfword). */
#define TEXTURE_ENTRY_PARAM 0
#define PALETTE_ENTRY_OFFSET 0

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* The data of entry `index` of a resource dictionary. */
static const u8 *dict_entry(const u8 *dict, u32 index)
{
    const u8 *entries = dict + read_u16(dict + 6);
    return entries + 4 + read_u16(entries) * index;
}

/* The number of entries of a resource dictionary. */
static u8 dict_count(const u8 *dict)
{
    return dict[1];
}

static const u8 *palette_dict(const G3dResTex *tex)
{
    return (const u8 *) tex + tex->palette_dict;
}

/* The palette's offset / 8 among the texture resource's palettes. */
static u16 palette_offset(const G3dResTex *tex, int index)
{
    return read_u16(dict_entry(palette_dict(tex), (u32) index) + PALETTE_ENTRY_OFFSET);
}

static u32 texture_param(const G3dResTex *tex, int index)
{
    return read_u32(dict_entry(tex->texture_dict, (u32) index) + TEXTURE_ENTRY_PARAM);
}

/* func_0205790c: the index of the model's node named `name`, or -1. */
int G3dRes_NodeIndex(const u8 *model, const char *name)
{
    return G3dRes_DictIndex(model + MODEL_NODE_DICT, name);
}
CLEAN_AS(func_0205790c, G3dRes_NodeIndex)

/* func_02057918: the size in bytes of palette `index` (0 for -1): up to the next palette that
 * starts after it, or for the last one to the end of the palettes.
 * QUIRK: the result is a 16-bit difference times 8 and is negative when a palette's offset is
 * past the palettes' size. */
int G3dRes_PaletteSize(const G3dResTex *tex, int index)
{
    if (index == -1) {
        return 0;
    }
    u16 start = palette_offset(tex, index);
    int count = dict_count(palette_dict(tex));
    for (int next = index + 1; next < count; next++) {
        u16 end = palette_offset(tex, next);
        if (end > start) {
            return (int) ((u32) (end - start) << 3);
        }
    }
    return (int) ((u32) (tex->palette_size - start) << 3);
}
CLEAN_AS(func_02057918, G3dRes_PaletteSize)

/* func_02057970: the data of the palette named `name`, NULL when there is none. */
u8 *G3dRes_PaletteByName(G3dResTex *tex, const char *name)
{
    return G3dRes_Palette(tex, G3dRes_PaletteIndex(tex, name));
}
CLEAN_AS(func_02057970, G3dRes_PaletteByName)

/* func_02057988: the data of palette `index`, NULL for -1. */
u8 *G3dRes_Palette(G3dResTex *tex, int index)
{
    if (index == -1) {
        return NULL;
    }
    return (u8 *) tex + tex->palette_data + ((u32) palette_offset(tex, index) << 3);
}
CLEAN_AS(func_02057988, G3dRes_Palette)

/* func_020579b8: the index of the palette named `name`, or -1. */
int G3dRes_PaletteIndex(const G3dResTex *tex, const char *name)
{
    return G3dRes_DictIndex(palette_dict(tex), name);
}
CLEAN_AS(func_020579b8, G3dRes_PaletteIndex)

/* func_020579c4: the size in bytes of texture `index`'s image (0 for -1). */
int G3dRes_TextureSize(const G3dResTex *tex, int index)
{
    if (index == -1) {
        return 0;
    }
    return (int) G3dRes_TextureBytes(texture_param(tex, index));
}
CLEAN_AS(func_020579c4, G3dRes_TextureSize)

/* func_020579f0: the image of texture `index` among the plain textures' images.
 * REQUIRES: `index` is a texture of the resource (-1 is not caught). */
void *G3dRes_TextureImage(G3dResTex *tex, int index)
{
    return (u8 *) tex + tex->tex_images + ((texture_param(tex, index) & 0xffff) << 3);
}
CLEAN_AS(func_020579f0, G3dRes_TextureImage)

/* func_02057a20: the image of the texture named `name`, NULL when there is none. */
void *G3dRes_TextureImageByName(G3dResTex *tex, const char *name)
{
    int index = G3dRes_TextureIndex(tex, name);
    if (index == -1) {
        return NULL;
    }
    return G3dRes_TextureImage(tex, index);
}
CLEAN_AS(func_02057a20, G3dRes_TextureImageByName)

/* func_02057a40: the index of the texture named `name`, or -1. */
int G3dRes_TextureIndex(const G3dResTex *tex, const char *name)
{
    return G3dRes_DictIndex(tex->texture_dict, name);
}
CLEAN_AS(func_02057a40, G3dRes_TextureIndex)

/* func_02057a4c: the bytes of the texture resource that precede the plain textures' images. */
int G3dRes_TextureHeaderSize(const G3dResTex *tex)
{
    return (int) tex->tex_images;
}
CLEAN_AS(func_02057a4c, G3dRes_TextureHeaderSize)

/* func_02057a50: the index of the model's material named `name`, or -1. */
int G3dRes_MaterialIndex(const u8 *model, const char *name)
{
    const u8 *materials = model + read_u32(model + MODEL_MATERIALS);
    return G3dRes_DictIndex(materials + MATERIALS_DICT, name);
}
CLEAN_AS(func_02057a50, G3dRes_MaterialIndex)

/* func_02057a60: the address in palette VRAM (in bytes) of the material's palette: its base
 * counts 8 bytes for a 4-color texture, 16 for the others. */
unsigned int G3dRes_MaterialPaletteAddress(const G3dResMaterial *material)
{
    unsigned int format = (material->tex_image_param >> 26) & 7;
    if (format == G3D_RES_TEXFMT_PLTT4) {
        return (unsigned int) material->palette_base << 3;
    }
    return (unsigned int) material->palette_base << 4;
}
CLEAN_AS(func_02057a60, G3dRes_MaterialPaletteAddress)

/* func_02057a7c: the address in texture VRAM (in bytes) of the material's texture image. */
unsigned int G3dRes_MaterialTextureAddress(const G3dResMaterial *material)
{
    return (material->tex_image_param & 0xffff) << 3;
}
CLEAN_AS(func_02057a7c, G3dRes_MaterialTextureAddress)

/* func_02057a8c: the size in bytes of the material's texture image. */
unsigned int G3dRes_MaterialTextureSize(const G3dResMaterial *material)
{
    return G3dRes_TextureBytes(material->tex_image_param);
}
CLEAN_AS(func_02057a8c, G3dRes_MaterialTextureSize)

/* func_02057a98: the index of `name` in the dictionary, or -1: the name is copied into the
 * 16 zeroed bytes the dictionary compares.
 * REQUIRES: `name` has at most 15 characters (the original copies a longer one past its
 * buffer). */
int G3dRes_DictIndex(const u8 *dict, const char *name)
{
    char buffer[16] = {0};
    strcpy(buffer, name);
    return NNS_G3dGetResDictIdxByName(dict, buffer);
}
CLEAN_AS(func_02057a98, G3dRes_DictIndex)

/* func_02057ac0: the size in bytes of a texture image by its TEXIMAGE_PARAM: the texels count
 * one byte each in the formats not listed (A3I5, 256 colors, A5I3). */
unsigned int G3dRes_TextureBytes(u32 image_param)
{
    unsigned int bytes = (unsigned int) G3dRes_TexelCount(image_param);
    switch ((image_param >> 26) & 7) {
        case G3D_RES_TEXFMT_PLTT4:
        case G3D_RES_TEXFMT_COMP4x4:
            return bytes >> 2;
        case G3D_RES_TEXFMT_PLTT16:
            return bytes >> 1;
        case G3D_RES_TEXFMT_DIRECT:
            return bytes << 1;
        default:
            return bytes;
    }
}
CLEAN_AS(func_02057ac0, G3dRes_TextureBytes)

/* func_02057b08: the number of texels of a texture by its TEXIMAGE_PARAM (width times height,
 * each read from the game's table). */
int G3dRes_TexelCount(u32 image_param)
{
    return data_020dd19c[(image_param >> 20) & 7] * data_020dd19c[(image_param >> 23) & 7];
}
CLEAN_AS(func_02057b08, G3dRes_TexelCount)
