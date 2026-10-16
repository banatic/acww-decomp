/* Lookups in NitroSystem's 3D resources: the index of a name in a resource dictionary
 * (NNSG3dResDict), a model resource's (NNSG3dResMdl) nodes and materials by name, a texture
 * resource's (NNSG3dResTex) textures and palettes by name or index (their data and sizes), and
 * a material's (NNSG3dResMatData) texture and palette addresses in VRAM.
 *
 * A dictionary's entries follow its header at its halfword 6: the entry size at 0, then the
 * entries from 4 on. A texture's entry holds its TEXIMAGE_PARAM word (the image's offset / 8
 * in bits 0-15, the width and height as 8 << n in bits 20-22 and 23-25, the format in bits
 * 26-28) and its original width and height; a palette's entry its offset / 8 and a flag (bit 0
 * set for a 4-color palette). */
#ifndef CLEAN_MAIN_G3D_RESOURCE_H
#define CLEAN_MAIN_G3D_RESOURCE_H

#include "types.h"

/* The texture formats of TEXIMAGE_PARAM bits 26-28 (NitroSDK's GXTexFmt). */
enum G3dResTexFormat {
    G3D_RES_TEXFMT_PLTT4 = 2,   /* 2 bits a texel */
    G3D_RES_TEXFMT_PLTT16 = 3,  /* 4 bits a texel */
    G3D_RES_TEXFMT_COMP4x4 = 5, /* 2 bits a texel, and a palette index block elsewhere */
    G3D_RES_TEXFMT_DIRECT = 7,  /* 16 bits a texel */
};

/* NNSG3dResTex: the texture resource's header, up to its dictionary of textures. */
typedef struct G3dResTex {
    u32 kind;             /* 0x00 */
    u32 size;             /* 0x04 */
    u32 tex_vram_key;     /* 0x08: plain textures' key (the address / 8 in bits 0-15) */
    u16 tex_size;         /* 0x0c */
    u16 tex_dict;         /* 0x0e */
    u16 tex_flag;         /* 0x10 */
    u16 pad_12;           /* 0x12 */
    u32 tex_images;       /* 0x14: the offset of the plain textures' images */
    u32 tex4x4_vram_key;  /* 0x18: 4x4 compressed textures' key */
    u16 tex4x4_size;      /* 0x1c */
    u16 tex4x4_dict;      /* 0x1e */
    u16 tex4x4_flag;      /* 0x20 */
    u16 pad_22;           /* 0x22 */
    u32 tex4x4_images;    /* 0x24 */
    u32 tex4x4_index;     /* 0x28 */
    u32 palette_vram_key; /* 0x2c: the palettes' key (the address / 8 in bits 0-15) */
    u16 palette_size;     /* 0x30: the size of all palettes / 8 */
    u16 palette_flag;     /* 0x32 */
    u16 palette_dict;     /* 0x34: the offset of the dictionary of palettes */
    u16 pad_36;           /* 0x36 */
    u32 palette_data;     /* 0x38: the offset of the palettes */
    u8 texture_dict[];    /* 0x3c: the dictionary of textures */
} G3dResTex;

/* NNSG3dResMatData: the part of a material that holds its texture and palette. */
typedef struct G3dResMaterial {
    u16 item_tag;        /* 0x00 */
    u16 size;            /* 0x02 */
    u32 diff_amb;        /* 0x04 */
    u32 spec_emi;        /* 0x08 */
    u32 poly_attr;       /* 0x0c */
    u32 poly_attr_mask;  /* 0x10 */
    u32 tex_image_param; /* 0x14: TEXIMAGE_PARAM */
    u32 tex_image_mask;  /* 0x18 */
    u16 palette_base;    /* 0x1c: the palette's address / 8 (4-color) or / 16 (others) */
    u16 flag;            /* 0x1e */
    u16 original_width;  /* 0x20 */
    u16 original_height; /* 0x22 */
    fx32 width_scale;    /* 0x24: the texture's width over the original width */
    fx32 height_scale;   /* 0x28 */
} G3dResMaterial;

int G3dRes_NodeIndex(const u8 *model, const char *name);
int G3dRes_PaletteSize(const G3dResTex *tex, int index);
u8 *G3dRes_PaletteByName(G3dResTex *tex, const char *name);
u8 *G3dRes_Palette(G3dResTex *tex, int index);
int G3dRes_PaletteIndex(const G3dResTex *tex, const char *name);
int G3dRes_TextureSize(const G3dResTex *tex, int index);
void *G3dRes_TextureImage(G3dResTex *tex, int index);
void *G3dRes_TextureImageByName(G3dResTex *tex, const char *name);
int G3dRes_TextureIndex(const G3dResTex *tex, const char *name);
int G3dRes_TextureHeaderSize(const G3dResTex *tex);
int G3dRes_MaterialIndex(const u8 *model, const char *name);
unsigned int G3dRes_MaterialPaletteAddress(const G3dResMaterial *material);
unsigned int G3dRes_MaterialTextureAddress(const G3dResMaterial *material);
unsigned int G3dRes_MaterialTextureSize(const G3dResMaterial *material);
int G3dRes_DictIndex(const u8 *dict, const char *name);
unsigned int G3dRes_TextureBytes(u32 image_param);
int G3dRes_TexelCount(u32 image_param);

#endif
