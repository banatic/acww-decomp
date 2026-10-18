/* The texture files of carpets and of clothing (item_texture.h). */
#include "item_texture.h"

#include "clean.h"
#include "design_info.h"
#include "design_sets.h"
#include "player_record.h"
#include "c_library.h"
#include "rom_file.h"

static_assert(sizeof(DesignModel) == 0x2c4, "a clothing texture file");

#define CARPET_FIRST 0x1144
#define CARPET_LAST 0x1187
#define CLOTH_FIRST 0x11a8
#define CLOTH_LAST 0x12a7
#define CLOTH_PATH_SIZE 0x20

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
/* The block of textures of a texture file read whole. */
extern G3dResTex *func_021077e8(void *file);
/* An item code's destructor (nothing), registered for the static default codes. */
extern void func_020051b0(void *item);
extern void __register_global_object(void *object, void *destruct, void *record);

extern const char data_020da8c4[]; /* "/carpet/floor_%d.nsbtx" */
extern const char data_020da8dc[]; /* "/cloth/%d/cloth%03d.nsbtx" */
extern u8 data_021ed278[];         /* the shop's designs */

/* The first carpet, loaded in place of an item that is not one: a static item code built on
 * first use, its guard's bit 0 and its destructor's record. */
extern ItemCode data_021c6970;
extern int data_021c6974;
extern u8 data_021c6978[];

/* The first piece of clothing, the same way. */
extern ItemCode data_021c6984;
extern int data_021c6988;
extern u8 data_021c698c[];

/* The place of `code` in first..last, or -1. */
static int index_in(int code, int first, int last)
{
    if (code >= first && code <= last) {
        return code - first;
    }
    return -1;
}

static void *as_pointer(unsigned int address)
{
    return (void *) (uintptr_t) address;
}

/* func_0203cb30: the destructor: nothing. */
void CarpetTexture_Destruct(u8 *file)
{
    (void) file;
}
CLEAN_AS(func_0203cb30, CarpetTexture_Destruct)

/* func_0203cb34 */
G3dResTex *CarpetTexture_Textures(u8 *file)
{
    return func_021077e8(file);
}
CLEAN_AS(func_0203cb34, CarpetTexture_Textures)

/* func_0203cb3c: the texture file of carpet `*item` read into `file` (the first carpet's for an
 * item that is not a carpet); nonzero when read. */
int CarpetTexture_Load(u8 *file, const ItemCode *item)
{
    int carpet = index_in(*item, CARPET_FIRST, CARPET_LAST);
    if (carpet != -1) {
        return RomFile_ReadFormatted(file, -1, data_020da8c4, carpet) != 0;
    }
    if ((data_021c6974 & 1) == 0) {
        data_021c6970 = CARPET_FIRST;
        __register_global_object(&data_021c6970, (void *) func_020051b0, data_021c6978);
        data_021c6974 |= 1;
    }
    return CarpetTexture_Load(file, &data_021c6970);
}
CLEAN_AS(func_0203cb3c, CarpetTexture_Load)

/* func_0203cbcc: the constructor: nothing. */
u8 *CarpetTexture_Construct(u8 *file)
{
    return file;
}
CLEAN_AS(func_0203cbcc, CarpetTexture_Construct)

/* func_0203cfa8 */
G3dResTex *ClothTexture_GetTextures(DesignModel *file)
{
    return ClothTexture_Textures(file);
}
CLEAN_AS(func_0203cfa8, ClothTexture_GetTextures)

/* func_0203cfb0 */
int ClothTexture_PutDesign(DesignModel *file, Design *design)
{
    return ClothTexture_SetDesign(file, design);
}
CLEAN_AS(func_0203cfb0, ClothTexture_PutDesign)

/* func_0203cfb8 */
int ClothTexture_LoadItem(DesignModel *file, const ItemCode *item, u8 *player)
{
    return ClothTexture_Load(file, item, player);
}
CLEAN_AS(func_0203cfb8, ClothTexture_LoadItem)

/* func_0203cfc0: the size of the buffer a clothing texture file is read into. */
int ClothTexture_Size(void)
{
    return (int) sizeof(DesignModel);
}
CLEAN_AS(func_0203cfc0, ClothTexture_Size)

/* func_0203cfc8 */
G3dResTex *ClothTexture_Textures(DesignModel *file)
{
    return func_021077e8(file);
}
CLEAN_AS(func_0203cfc8, ClothTexture_Textures)

/* func_0203cfd0: its first palette. */
u8 *ClothTexture_Palette(DesignModel *file)
{
    return G3dRes_Palette(ClothTexture_Textures(file), 0);
}
CLEAN_AS(func_0203cfd0, ClothTexture_Palette)

/* func_0203cfe4: its first texture's image. */
void *ClothTexture_Image(DesignModel *file)
{
    return G3dRes_TextureImage(ClothTexture_Textures(file), 0);
}
CLEAN_AS(func_0203cfe4, ClothTexture_Image)

/* func_0203cff8: the file of the first piece of clothing read into `file`, then (unless
 * `design` is NULL) the design's pixels and palette's colours copied over its image and
 * palette. 0 when the file could not be read. */
int ClothTexture_SetDesign(DesignModel *file, Design *design)
{
    ItemCode first = CLOTH_FIRST;
    if (ClothTexture_Load(file, &first, NULL) == 0) {
        return 0;
    }
    if (design == NULL) {
        return 1;
    }

    void *pixels = Design_Pixels(design);
    MI_CpuCopy8(pixels, ClothTexture_Image(file), DESIGN_PIXELS_SIZE);

    void *colours =
        as_pointer((unsigned int) DesignInfo_PaletteColours(as_pointer(Design_Info((unsigned int) (uintptr_t) design))));
    MI_CpuCopy8(colours, ClothTexture_Palette(file), DESIGN_PALETTE_SIZE);
    return 1;
}
CLEAN_AS(func_0203cff8, ClothTexture_SetDesign)

/* A design item's texture: design `index` of the shop (no `player`) or of `player`. */
static int load_design_item(DesignModel *file, int index, u8 *player)
{
    if (player == NULL) {
        return ClothTexture_SetDesign(file, as_pointer(ShopDesigns_At((unsigned int) (uintptr_t) data_021ed278, (u8) index)));
    }
    return ClothTexture_SetDesign(file, as_pointer((unsigned int) PlayerDesigns_At(PlayerRecord_Designs(player), (u8) index)));
}

/* func_0203d064: the texture file of clothing item `*item` read into `file`; nonzero when
 * read. A design item takes its design from the shop's designs when `player` is NULL, else
 * from that player's record. Any other item loads the first piece of clothing. */
int ClothTexture_Load(DesignModel *file, const ItemCode *item, u8 *player)
{
    static const struct {
        u16 first;
        u16 last;
    } design_items[] = {{0x12a8, 0x12af}, {0x1429, 0x1430}, {0x13a0, 0x13a7}};

    int code = *item;
    for (size_t i = 0; i < sizeof(design_items) / sizeof(design_items[0]); i++) {
        int index = index_in(code, design_items[i].first, design_items[i].last);
        if (index != -1) {
            return load_design_item(file, index, player);
        }
    }

    int cloth = index_in(code, CLOTH_FIRST, CLOTH_LAST);
    if (cloth != -1) {
        char path[CLOTH_PATH_SIZE];
        CLib_SPrintf(path, data_020da8dc, cloth >> 4, cloth);
        return RomFile_Read(path, file, -1) != 0;
    }

    if ((data_021c6988 & 1) == 0) {
        data_021c6984 = CLOTH_FIRST;
        __register_global_object(&data_021c6984, (void *) func_020051b0, data_021c698c);
        data_021c6988 |= 1;
    }
    return ClothTexture_Load(file, &data_021c6984, player);
}
CLEAN_AS(func_0203d064, ClothTexture_Load)

/* func_0203d224: the destructor: nothing. */
void ClothTexture_Destruct(DesignModel *file)
{
    (void) file;
}
CLEAN_AS(func_0203d224, ClothTexture_Destruct)

/* func_0203d228: the constructor: nothing. */
void ClothTexture_Construct(DesignModel *file)
{
    (void) file;
}
CLEAN_AS(func_0203d228, ClothTexture_Construct)
