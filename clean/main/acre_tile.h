/* The tiles and acres of a map of acres (acre_map.h): finding an acre or a tile, reading and
 * writing a tile's item code, the bit each tile has in its acre, what the map's slot says of a
 * unit, putting buildings down, and converting between tiles and positions.
 *
 * A tile is numbered (x, z) across the whole map: acre (x / 16, z / 16) and the tile (x % 16,
 * z % 16) within it, rounded down as the ARM's arithmetic shift does. A tile is 0x2000 units
 * of position wide, an acre 0x20000.
 *
 * Each acre record (ACRE_MAP_ACRE_SIZE bytes) holds its model number first, its item codes per
 * layer (layers 0 and 1, 16 x 16 codes each), and at 0x24 one bit per tile, a halfword per row
 * of 16 tiles.
 *
 * Buildings are the item codes 0x5000-0x5021. A building stands on its tile with its code;
 * the other tiles of its shape (func_020b3b50) hold ACRE_TILE_ITEM_OCCUPIED. */
#ifndef CLEAN_MAIN_ACRE_TILE_H
#define CLEAN_MAIN_ACRE_TILE_H

#include "acre_map.h"
#include "autoload_2/vector.h"
#include "types.h"

#define ACRE_TILE_BUILDING_FIRST 0x5000
#define ACRE_TILE_BUILDING_LAST 0x5021
/* The code of a tile a building's shape covers. */
#define ACRE_TILE_ITEM_OCCUPIED 0xf030

int AcreTile_StampBuildingNoting(AcreMap *map, u16 *building, int x, int z, u8 to_handler);
int AcreTile_RetypeUnit(AcreMap *map, int x, int z);
int AcreTile_PathDirectionsAt(AcreMap *map, const Vec3 *position);
int AcreTile_PathDirections(AcreMap *map, int x, int z);
int AcreTile_UnitWord06(AcreMap *map, int x, int z);
int AcreTile_UnitByte09(AcreMap *map, int x, int z);
int AcreTile_UnitHasByte17(AcreMap *map, int x, int z);
int AcreTile_UnitByte08(AcreMap *map, int x, int z);
int AcreTile_UnitByte05(AcreMap *map, int x, int z);
int AcreTile_UnitByte04InAcre(AcreMap *map, int acre_x, int acre_z, int x, int z);
int AcreTile_UnitByte04(AcreMap *map, int x, int z);
int AcreTile_ReplaceBuilding(AcreMap *map, int x, int z, u16 *code);
int AcreTile_StampBuilding(AcreMap *map, u16 *building, int x, int z);
int AcreTile_PutBuilding(AcreMap *map, u16 *code, u16 *building, u16 *fill, int x, int z);
int AcreTile_IsMarkedAt(AcreMap *map, const Vec3 *position);
int AcreTile_IsMarked(AcreMap *map, int x, int z);
int AcreTile_IsMarkedInAcre(AcreMap *map, u32 acre_x, u32 acre_z, u32 x, u32 z);
int AcreTile_Unmark(AcreMap *map, int x, int z);
int AcreTile_UnmarkInAcre(AcreMap *map, u32 acre_x, u32 acre_z, int x, int z);
void AcreTile_Mark(AcreMap *map, int x, int z);
int AcreTile_MarkInAcre(AcreMap *map, u32 acre_x, u32 acre_z, int x, int z);
int AcreTile_FindItemAnyFlag(AcreMap *map, int *acre_x, int *acre_z, int *x, int *z, u16 *first, u16 *last, int flags,
                             int layer);
int AcreTile_FindItemAllFlags(AcreMap *map, int *acre_x, int *acre_z, int *x, int *z, u16 *first, u16 *last, int flags,
                              int layer);
int AcreTile_SetItem(AcreMap *map, u16 *code, int x, int z, u8 layer);
int AcreTile_SetItemInAcre(AcreMap *map, u16 *code, u32 acre_x, u32 acre_z, int x, int z, u8 layer);
u16 *AcreTile_ItemAt(AcreMap *map, const Vec3 *position, int layer);
u16 *AcreTile_ItemInAcre(AcreMap *map, u32 acre_x, u32 acre_z, int x, int z, u8 layer);
void *AcreTile_AcreHasFlags(AcreMap *map, u32 acre_x, u32 acre_z, u32 flags);
void *AcreTile_AcreFlags(AcreMap *map, u32 acre_x, u32 acre_z);
void *AcreTile_FindAcreAnyFlag(AcreMap *map, void *flags);
void *AcreTile_FindAcreAllFlags(AcreMap *map, void *flags);
void AcreTile_PositionInAcre(Vec3 *position, u32 acre_x, u32 acre_z, u32 x, u32 z);
void AcreTile_TileCentre(Vec3 *position, u32 x, u32 z);
void AcreTile_TileCentreInAcre(Vec3 *position, int acre_x, int acre_z, int x, int z);
void AcreTile_SnapToTileCentre(Vec3 *position, const Vec3 *from);
void AcreTile_TileOfAcre(int *x, int *z, int acre_x, int acre_z, int offset_x, int offset_z);
void AcreTile_AcreAndTileOf(int *acre, int *tile, const Vec3 *position);
void AcreTile_SplitPosition(int *acre_x, int *acre_z, int *x, int *z, const Vec3 *position);

#endif
