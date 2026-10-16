/* The texture files of two kinds of item, each read whole into a buffer its owner keeps:
 *
 * - a carpet's (items 0x1144-0x1187): "/carpet/floor_<n>.nsbtx", n = item - 0x1144;
 * - a piece of clothing's (DesignModel, 0x2c4 bytes, design_assets.h): for the items
 *   0x11a8-0x12a7 "/cloth/<n / 16>/cloth<n>.nsbtx", n = item - 0x11a8; for the items made from
 *   a design (0x12a8-0x12af, 0x13a0-0x13a7 and 0x1429-0x1430, design n = the item's place in
 *   its range) the file of item 0x11a8 with its image and palette replaced by the design's.
 *
 * An item outside the ranges loads the first of its kind (0x1144, 0x11a8). */
#ifndef CLEAN_MAIN_ITEM_TEXTURE_H
#define CLEAN_MAIN_ITEM_TEXTURE_H

#include "design.h"
#include "design_assets.h" /* DesignModel */
#include "g3d_resource.h"  /* G3dResTex */
#include "lookups.h"       /* ItemCode */
#include "types.h"

void CarpetTexture_Destruct(u8 *file);
G3dResTex *CarpetTexture_Textures(u8 *file);
int CarpetTexture_Load(u8 *file, const ItemCode *item);
u8 *CarpetTexture_Construct(u8 *file);

G3dResTex *ClothTexture_GetTextures(DesignModel *file);
int ClothTexture_PutDesign(DesignModel *file, Design *design);
int ClothTexture_LoadItem(DesignModel *file, const ItemCode *item, u8 *player);
int ClothTexture_Size(void);
G3dResTex *ClothTexture_Textures(DesignModel *file);
u8 *ClothTexture_Palette(DesignModel *file);
void *ClothTexture_Image(DesignModel *file);
int ClothTexture_SetDesign(DesignModel *file, Design *design);
int ClothTexture_Load(DesignModel *file, const ItemCode *item, u8 *player);
void ClothTexture_Destruct(DesignModel *file);
void ClothTexture_Construct(DesignModel *file);

#endif
