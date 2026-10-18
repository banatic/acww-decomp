/* The copy of a texture's image and a palette over those of a texture resource in VRAM
 * (tex_upload.h). */
#include "tex_upload.h"

#include "clean.h"
#include "vram_copy_task.h"

static_assert(sizeof(ModelLoaderTask) == 0x1c, "ModelLoaderTask size");
static_assert(offsetof(TexUpload, palette) == 0x1c && sizeof(TexUpload) == 0x38, "TexUpload layout");

/* The copy tasks' priorities (their byte 0x0c). */
#define IMAGE_PRIORITY 2
#define PALETTE_PRIORITY 3

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

/* func_02057778: TexUpload_Send with the target's texture and palette named (NULL for none). */
int TexUpload_SendByName(TexUpload *upload, G3dResTex *target, const char *texture, const char *palette, G3dResTex *source,
                         int source_texture, int source_palette)
{
    int texture_index = texture != NULL ? G3dRes_TextureIndex(target, texture) : -1;
    int palette_index = palette != NULL ? G3dRes_PaletteIndex(target, palette) : -1;
    return TexUpload_Send(upload, target, texture_index, palette_index, source, source_texture, (u32) source_palette);
}
CLEAN_AS(func_02057778, TexUpload_SendByName)

/* func_020577c8: the image of the source's texture `source_texture` copied over the target's
 * texture `texture` in VRAM, then the source's palette `source_palette` over the target's
 * palette `palette` (each unless the source's is -1). 0 when a copy could not be started (the
 * image's copy is ended when the palette's fails).
 * QUIRK: the size of the target's texture is worked out first and not used.
 * QUIRK: the target texture's address is taken with the plain textures' key also for a 4x4
 * compressed texture.
 * QUIRK: -1 for the target's texture or palette is not caught: the dictionary's bytes before
 * its first entry are read as its entry. */
int TexUpload_Send(TexUpload *upload, G3dResTex *target, int texture, int palette, G3dResTex *source, int source_texture,
                   u32 source_palette)
{
    const u8 *target_texture = dict_entry(target->texture_dict, (u32) texture);
    const u8 *target_palette = dict_entry((const u8 *) target + target->palette_dict, (u32) palette);

    G3dRes_TextureBytes(read_u32(target_texture));
    if (source_texture != -1) {
        u32 offset = (read_u32(target_texture) + (u16) target->tex_vram_key) & 0xffff;
        const u8 *source_entry = dict_entry(source->texture_dict, (u32) source_texture);
        void *image = G3dRes_TextureImage(source, source_texture);
        unsigned int size = G3dRes_TextureBytes(read_u32(source_entry));
        if (VramCopyTask_QueueImage((VramCopyTask *) &upload->image, image, offset << 3, (int) size, IMAGE_PRIORITY) == 0) {
            return 0;
        }
    }
    if (source_palette != (u32) -1) {
        u8 *data = G3dRes_Palette(source, (int) source_palette);
        int size = G3dRes_PaletteSize(source, (int) source_palette);
        unsigned int address = (unsigned int) (read_u16(target_palette) + (u16) target->palette_vram_key) << 3;
        if (VramCopyTask_QueuePalette((VramCopyTask *) &upload->palette, data, address, size, PALETTE_PRIORITY) == 0) {
            VramCopyTask_End((VramCopyTask *) &upload->image);
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_020577c8, TexUpload_Send)

/* func_020578d4: the destructor: both transfers ended. */
TexUpload *TexUpload_Destruct(TexUpload *upload)
{
    VramCopyTask_End((VramCopyTask *) &upload->image);
    VramCopyTask_End((VramCopyTask *) &upload->palette);
    return upload;
}
CLEAN_AS(func_020578d4, TexUpload_Destruct)

/* func_020578ec: the constructor: both transfers constructed. */
TexUpload *TexUpload_Construct(TexUpload *upload)
{
    VramCopyTask_Construct((VramCopyTask *) &upload->image);
    VramCopyTask_Construct((VramCopyTask *) &upload->palette);
    return upload;
}
CLEAN_AS(func_020578ec, TexUpload_Construct)
