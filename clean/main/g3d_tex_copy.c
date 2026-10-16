/* Copies between texture resources (g3d_tex_copy.h). */
#include "g3d_tex_copy.h"

#include "clean.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* func_0206435c: the palette `from_name` of `from` copied over the palette `to_name` of `to`. */
void G3dTexCopy_Palette(G3dResTex *from, G3dResTex *to, const char *from_name, const char *to_name)
{
    const u8 *src = G3dRes_PaletteByName(from, from_name);
    int index = G3dRes_PaletteIndex(to, to_name);
    u8 *dst = G3dRes_Palette(to, index);
    int size = G3dRes_PaletteSize(to, index);
    MI_CpuCopy8(src, dst, (u32) size);
}
CLEAN_AS(func_0206435c, G3dTexCopy_Palette)

/* func_0206439c: the image of the texture `from_name` of `from` copied over the image of the
 * texture `to_name` of `to`. */
void G3dTexCopy_Image(G3dResTex *from, G3dResTex *to, const char *from_name, const char *to_name)
{
    const void *src = G3dRes_TextureImageByName(from, from_name);
    int index = G3dRes_TextureIndex(to, to_name);
    void *dst = G3dRes_TextureImage(to, index);
    int size = G3dRes_TextureSize(to, index);
    MI_CpuCopy8(src, dst, (u32) size);
}
CLEAN_AS(func_0206439c, G3dTexCopy_Image)
