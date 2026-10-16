/* Questions about one tile of the town's map (data_021c80bc): what its object is and who stands
 * on it. A tile is numbered (x, z) across the whole map; func_0204f5e0 finds its object from the
 * acre (x / 16, z / 16) and the tile within it (x % 16, z % 16), and func_0204f818 gives the tile
 * a position is on. */
#ifndef CLEAN_MAIN_TOWN_TILE_H
#define CLEAN_MAIN_TOWN_TILE_H

#include "autoload_2/vector.h"
#include "types.h"

/* The object codes TownTile_FindItem5000Above looks for. */
#define TOWN_TILE_ITEM_5000_FIRST 0x5000
#define TOWN_TILE_ITEM_5000_LAST 0x5021

int TownTile_FindItem5000AboveAt(const Vec3 *position, int rows, int *out_x, int *out_z);
int TownTile_FindItem5000Above(int x, int z, int rows, int *out_x, int *out_z);
int TownTile_IsClearAt(const Vec3 *position, void *map);
int TownTile_IsClear(int x, int z, void *map);
int TownTile_Occupant(int x, int z);
int TownTile_PlayerOccupant(int x, int z);

#endif
