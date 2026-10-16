/* A texture and a palette bound to one material of a model (material_bind.h). */
#include "material_bind.h"

#include "clean.h"

static_assert(offsetof(MaterialBind, material) == 4, "MaterialBind material");

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

/* The model resource's offset of its materials (NNSG3dResMat). The materials start with the
 * offsets of their texture-to-material and palette-to-material dictionaries, then the
 * dictionary of materials (each entry the offset of its NNSG3dResMatData). */
#define MODEL_MATERIALS 0x08
#define MATERIALS_TEXTURE_DICT 0x00
#define MATERIALS_PALETTE_DICT 0x02
#define MATERIALS_DICT 0x04

/* An entry of the texture-to-material and palette-to-material dictionaries: the offset of its
 * list of material indices, their count, and flags. */
#define LIST_OFFSET 0
#define LIST_COUNT 2
#define LIST_FLAGS 3
#define LIST_BOUND 0x01 /* LIST_FLAGS: the texture or palette is bound */

/* A texture's entry: TEXIMAGE_PARAM, then the original width (bits 0-10) and height (bits
 * 11-21). A palette's entry: its offset / 8, then flags. */
#define TEXTURE_PARAM 0
#define TEXTURE_SIZE 4
#define PALETTE_OFFSET 0
#define PALETTE_FLAGS 2
#define PALETTE_4_COLORS 0x0001

/* The TEXIMAGE_PARAM bits a material keeps of its own when a texture is bound: the repeat and
 * flip bits (16-19) and the texture coordinate transform (30-31). */
#define MATERIAL_KEPT_BITS 0xc00f0000u

static u16 read_u16(const u8 *p)
{
    return *(const u16 *) (const void *) p;
}

static u32 read_u32(const u8 *p)
{
    return *(const u32 *) (const void *) p;
}

/* The data of entry `index` of a resource dictionary. */
static u8 *dict_entry(u8 *dict, u32 index)
{
    u8 *entries = dict + read_u16(dict + 6);
    return entries + 4 + read_u16(entries) * index;
}

static u8 *model_materials(const MaterialBind *bind)
{
    return bind->model + read_u32(bind->model + MODEL_MATERIALS);
}

/* The entry of the texture-to-material or palette-to-material dictionary at `dict_offset` of
 * the materials whose list holds the picked material, or NULL. */
static u8 *find_list(const MaterialBind *bind, u8 *materials, u16 dict_offset)
{
    u8 *dict = materials + dict_offset;
    for (u32 i = 0; i < dict[1]; i++) {
        u8 *list = dict_entry(dict, i);
        const u8 *indices = materials + read_u16(list + LIST_OFFSET);
        for (u32 k = 0; k < list[LIST_COUNT]; k++) {
            if (bind->material == indices[k]) {
                return list;
            }
        }
    }
    return NULL;
}

/* Material `k` of the list. */
static G3dResMaterial *list_material(u8 *materials, const u8 *list, u32 k)
{
    const u8 *indices = materials + read_u16(list + LIST_OFFSET);
    return (G3dResMaterial *) (void *) (materials + read_u32(dict_entry(materials + MATERIALS_DICT, indices[k])));
}

/* The scale of a material's texture: the texture's size over the size the material was made
 * for, 1.0 when they are the same. */
static fx32 texture_scale(u32 size, u16 original)
{
    if (size != original) {
        return FX_Div((fx32) (size << 12), (fx32) ((u32) original << 12));
    }
    return 0x1000;
}

/* func_02057084: the texture `texture` and palette `palette` of `tex` bound to the materials
 * that share the model's material named `material` (both are tried); 0 without such a
 * material. */
int MaterialBind_BindByIndex(u8 *model, const char *material, G3dResTex *tex, int texture, int palette)
{
    MaterialBind bind;
    MaterialBind_Construct(&bind);
    if (MaterialBind_PickByName(&bind, model, material)) {
        int result = MaterialBind_Set(&bind, tex, texture, palette);
        MaterialBind_Reset(&bind);
        MaterialBind_Destruct(&bind);
        return result;
    }
    MaterialBind_Destruct(&bind);
    return 0;
}
CLEAN_AS(func_02057084, MaterialBind_BindByIndex)

/* func_020570d4: MaterialBind_BindByIndex with the texture and the palette named. */
int MaterialBind_BindByName(u8 *model, const char *material, G3dResTex *tex, const char *texture, const char *palette)
{
    MaterialBind bind;
    MaterialBind_Construct(&bind);
    if (MaterialBind_PickByName(&bind, model, material) != 0) {
        int result = MaterialBind_SetByName(&bind, tex, texture, palette);
        MaterialBind_Reset(&bind);
        MaterialBind_Destruct(&bind);
        return result;
    }
    MaterialBind_Destruct(&bind);
    return 0;
}
CLEAN_AS(func_020570d4, MaterialBind_BindByName)

/* func_02057124: the picked material's index. */
s8 MaterialBind_Material(const MaterialBind *bind)
{
    return bind->material;
}
CLEAN_AS(func_02057124, MaterialBind_Material)

/* func_0205712c: palette `palette` of `tex` (in VRAM) bound to every material that uses the
 * picked material's palette; 0 when nothing is picked, for palette -1 or when no palette list
 * holds the material. A palette's base counts 16 bytes, 8 for a 4-color palette. */
int MaterialBind_SetPalette(MaterialBind *bind, G3dResTex *tex, int palette)
{
    if (MaterialBind_IsPicked(bind) == 0 || palette == -1) {
        return 0;
    }
    u8 *materials = model_materials(bind);
    u8 *list = find_list(bind, materials, read_u16(materials + MATERIALS_PALETTE_DICT));
    if (list == NULL) {
        return 0;
    }
    const u8 *entry = dict_entry((u8 *) tex + tex->palette_dict, (u32) palette);
    u16 offset = read_u16(entry + PALETTE_OFFSET);
    u16 vram = (u16) tex->palette_vram_key;
    if ((read_u16(entry + PALETTE_FLAGS) & PALETTE_4_COLORS) == 0) {
        offset >>= 1;
        vram >>= 1;
    }
    for (u32 k = 0; k < list[LIST_COUNT]; k++) {
        list_material(materials, list, k)->palette_base = (u16) (offset + vram);
    }
    list[LIST_FLAGS] |= LIST_BOUND;
    return 1;
}
CLEAN_AS(func_0205712c, MaterialBind_SetPalette)

/* func_0205720c: MaterialBind_SetPalette with the palette named; 1 for no name. */
int MaterialBind_SetPaletteByName(MaterialBind *bind, G3dResTex *tex, const char *palette)
{
    if (palette == NULL) {
        return 1;
    }
    return MaterialBind_SetPalette(bind, tex, G3dRes_PaletteIndex(tex, palette));
}
CLEAN_AS(func_0205720c, MaterialBind_SetPaletteByName)

/* func_02057238: texture `texture` of `tex` (in VRAM) bound to every material that uses the
 * picked material's texture: its address (the plain or the 4x4 textures' key added), format
 * and size go into each material's TEXIMAGE_PARAM, and its scale against the size each
 * material was made for. 0 when nothing is picked, for texture -1 or when no texture list
 * holds the material. */
int MaterialBind_SetTexture(MaterialBind *bind, G3dResTex *tex, int texture)
{
    if (MaterialBind_IsPicked(bind) == 0 || texture == -1) {
        return 0;
    }
    u8 *materials = model_materials(bind);
    u8 *list = find_list(bind, materials, read_u16(materials + MATERIALS_TEXTURE_DICT));
    if (list == NULL) {
        return 0;
    }
    const u8 *entry = dict_entry(tex->texture_dict, (u32) texture);
    u32 vram;
    if (((read_u32(entry + TEXTURE_PARAM) >> 26) & 7) != G3D_RES_TEXFMT_COMP4x4) {
        vram = tex->tex_vram_key & 0xffff;
    } else {
        vram = tex->tex4x4_vram_key & 0xffff;
    }
    for (u32 k = 0; k < list[LIST_COUNT]; k++) {
        G3dResMaterial *material = list_material(materials, list, k);
        material->tex_image_param =
            (material->tex_image_param & MATERIAL_KEPT_BITS) | (read_u32(entry + TEXTURE_PARAM) + vram);
        u32 size = read_u32(entry + TEXTURE_SIZE);
        u32 width = size & 0x7ff;
        u32 height = (size >> 11) & 0x7ff;
        material->width_scale = texture_scale(width, material->original_width);
        material->height_scale = texture_scale(height, material->original_height);
    }
    list[LIST_FLAGS] |= LIST_BOUND;
    return 1;
}
CLEAN_AS(func_02057238, MaterialBind_SetTexture)

/* func_0205738c: MaterialBind_SetTexture with the texture named; 1 for no name. */
int MaterialBind_SetTextureByName(MaterialBind *bind, G3dResTex *tex, const char *texture)
{
    if (texture == NULL) {
        return 1;
    }
    return MaterialBind_SetTexture(bind, tex, G3dRes_TextureIndex(tex, texture));
}
CLEAN_AS(func_0205738c, MaterialBind_SetTextureByName)

/* func_020573b8: the texture and the palette bound (both are tried); whether both were. */
int MaterialBind_Set(MaterialBind *bind, G3dResTex *tex, int texture, int palette)
{
    int texture_bound = (MaterialBind_SetTexture(bind, tex, texture) & 1) != 0;
    int palette_bound = MaterialBind_SetPalette(bind, tex, palette);
    return (texture_bound & palette_bound) != 0;
}
CLEAN_AS(func_020573b8, MaterialBind_Set)

/* func_020573f0: MaterialBind_Set with the texture and the palette named. */
int MaterialBind_SetByName(MaterialBind *bind, G3dResTex *tex, const char *texture, const char *palette)
{
    int texture_bound = (MaterialBind_SetTextureByName(bind, tex, texture) & 1) != 0;
    int palette_bound = MaterialBind_SetPaletteByName(bind, tex, palette);
    return (texture_bound & palette_bound) != 0;
}
CLEAN_AS(func_020573f0, MaterialBind_SetByName)

/* func_02057428: no material picked. */
void MaterialBind_Reset(MaterialBind *bind)
{
    bind->material = MATERIAL_BIND_NONE;
}
CLEAN_AS(func_02057428, MaterialBind_Reset)

/* func_02057430: material `material` of the model picked, unless one is picked already or the
 * model has no such material (-1 included); whether it was.
 * QUIRK: the index is a signed comparison with the material count, so a negative index other
 * than -1 is picked (and kept in a byte). */
int MaterialBind_Pick(MaterialBind *bind, u8 *model, int material)
{
    if (MaterialBind_IsPicked(bind) != 0) {
        return 0;
    }
    if (material == -1) {
        return 0;
    }
    const u8 *materials = model + read_u32(model + MODEL_MATERIALS);
    if (material < materials[MATERIALS_DICT + 1]) {
        bind->material = (s8) material;
        bind->model = model;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02057430, MaterialBind_Pick)

/* func_02057468: the model's material named `material` picked, unless one is picked already
 * or the model has none of that name; whether it was. The index is kept in a byte. */
int MaterialBind_PickByName(MaterialBind *bind, u8 *model, const char *material)
{
    if (MaterialBind_IsPicked(bind) != 0) {
        return 0;
    }
    int index = (s8) G3dRes_MaterialIndex(model, material);
    if (index == -1) {
        return 0;
    }
    return MaterialBind_Pick(bind, model, index);
}
CLEAN_AS(func_02057468, MaterialBind_PickByName)

/* func_020574a0: whether a material is picked. */
int MaterialBind_IsPicked(const MaterialBind *bind)
{
    return bind->material != MATERIAL_BIND_NONE;
}
CLEAN_AS(func_020574a0, MaterialBind_IsPicked)

/* func_020574b0: the destructor: nothing to do. */
void MaterialBind_Destruct(MaterialBind *bind)
{
    (void) bind;
}
CLEAN_AS(func_020574b0, MaterialBind_Destruct)

/* func_020574b4: the constructor: no material picked. */
MaterialBind *MaterialBind_Construct(MaterialBind *bind)
{
    MaterialBind_Reset(bind);
    return bind;
}
CLEAN_AS(func_020574b4, MaterialBind_Construct)
