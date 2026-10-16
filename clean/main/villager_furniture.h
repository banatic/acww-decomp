/* The house of one of the town's villagers (VillagerTown, villager_town.h): the ten items it
 * keeps in its house, its wallpaper and carpet, and the filling of its acre's item template.
 *
 *   0x78c  ten item codes, the house's items (0xfff1: none); a mark for each at 0x7d0
 *          (villager_entry.h)
 *   0x7d4  the wallpaper: the index of an item 0x1100-0x1143
 *   0x7d5  the carpet: the index of an item 0x1144-0x1187
 *   0x7d8  a number drawn when the villager takes a new mode (VillagerFurniture_ResetForMode)
 *
 * An item template (acre_map.h) holds 16 x 16 codes; the codes 0xf000-0xf02f stand for one of
 * the villager's ten items (func_0207ff58 gives which), with its variant in the low two bits.
 * A list of spots names such codes by their tile within the acre. */
#ifndef CLEAN_MAIN_VILLAGER_FURNITURE_H
#define CLEAN_MAIN_VILLAGER_FURNITURE_H

#include "types.h"

#define VILLAGER_FURNITURE_ITEMS 10
#define VILLAGER_FURNITURE_NONE 0xfff1
#define VILLAGER_FURNITURE_NOT_FOUND (-1)
/* The codes of a template that stand for one of the villager's items. */
#define VILLAGER_FURNITURE_SLOT_FIRST 0xf000
#define VILLAGER_FURNITURE_SLOT_LAST 0xf02f
#define VILLAGER_FURNITURE_VARIANT_MASK 3
/* The codes of an item template. */
#define VILLAGER_FURNITURE_TEMPLATE_CODES 0x100
/* A spot's tile is within an acre: 0-15 each way. */
#define VILLAGER_FURNITURE_ACRE_TILES 16

/* A tile within the acre. */
typedef struct VillagerFurnitureTile {
    int x; /* 0x00 */
    int z; /* 0x04 */
} VillagerFurnitureTile;

/* A code of a template and the tile it stands on. */
typedef struct VillagerFurnitureSpot {
    u16 code; /* 0x00 */
    u8 x;     /* 0x02 */
    u8 z;     /* 0x03 */
} VillagerFurnitureSpot;

void VillagerFurniture_SetCarpet(u8 *villager, u8 index);
void VillagerFurniture_SetWallpaper(u8 *villager, u8 index);
u8 VillagerFurniture_Carpet(u8 *villager);
u8 VillagerFurniture_Wallpaper(u8 *villager);
int VillagerFurniture_IsMarkedAt(u8 *villager, const VillagerFurnitureTile *tile, const VillagerFurnitureSpot *spots,
                                 int count);
int VillagerFurniture_TakeAt(u8 *villager, const VillagerFurnitureTile *tile, const VillagerFurnitureSpot *spots, int count);
int VillagerFurniture_SlotAt(u8 *villager, const VillagerFurnitureTile *tile, const VillagerFurnitureSpot *spots, int count);
void VillagerFurniture_ResetForMode(u8 *villager, int mode, int from_2);
void VillagerFurniture_StoreItems(u8 *villager);
void VillagerFurniture_FillTemplate(u8 *villager, u16 *codes);

#endif
