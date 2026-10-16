/* A bit per tile of an acre. Coordinates are unsigned so that the neighbours of an edge tile
 * (x - 1 at x = 0) fall outside the grid and read as unmarked, as the callers rely on. */
#include "tile_grid.h"
#include "clean.h"

#include <assert.h>

/* func_02084e00: a tile in the rows the callers search; tiles in the last two rows read as
 * unmarked. */
BOOL TileGrid_IsMarkedInSearchRows(const TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SEARCH_ROWS) {
        return FALSE;
    }
    return (grid->rows[z] >> x) & 1;
}
CLEAN_AS(func_02084e00, TileGrid_IsMarkedInSearchRows)

/* func_02084e20 */
BOOL TileGrid_IsMarked(const TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SIZE) {
        return FALSE;
    }
    return (grid->rows[z] >> x) & 1;
}
CLEAN_AS(func_02084e20, TileGrid_IsMarked)

/* func_02084e40: TRUE when the tile is in the grid. */
BOOL TileGrid_Unmark(TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SIZE) {
        return FALSE;
    }
    grid->rows[z] &= (u16) ~(1u << x);
    return TRUE;
}
CLEAN_AS(func_02084e40, TileGrid_Unmark)

/* func_02084e68: TRUE when the tile is in the grid. */
BOOL TileGrid_Mark(TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SIZE) {
        return FALSE;
    }
    grid->rows[z] |= (u16) (1u << x);
    return TRUE;
}
CLEAN_AS(func_02084e68, TileGrid_Mark)

static_assert(sizeof(TileGrid) == 0x20, "TileGrid layout");

/* ---- Building a grid */

#include "acre_map.h"
#include "acre_tile.h"
#include "field_collision.h"

extern AcreMap *data_021c80bc; /* the map of the scene */
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_02084e90: the grid of the first acre of the scene's map: every tile whose item is
 * ACRE_MAP_ITEM_NONE and whose ground is at height 0 is marked, then each marked tile of the
 * rows 0-13 without a marked neighbour is unmarked. 0, with the grid cleared, when there is no
 * map or no acre. */
int TileGrid_Build(TileGrid *grid)
{
    AcreMap *map = data_021c80bc;
    MI_CpuFill8(grid, 0, sizeof *grid);
    if (map == NULL) {
        return 0;
    }
    const u16 *item = AcreTile_ItemInAcre(map, 0, 0, 0, 0, 0);
    if (item == NULL) {
        return 0;
    }
    for (u32 z = 0; z < TILE_GRID_SIZE; z++) {
        for (u32 x = 0; x < TILE_GRID_SIZE; x++) {
            Vec3 position;
            CollisionGround ground;
            AcreTile_TileCentre(&position, x, z);
            CollisionGround_Init(&ground, &position, 0, 0);
            if (*item == ACRE_MAP_ITEM_NONE && CollisionGround_GetHeight(&ground, 1) == 0) {
                TileGrid_Mark(grid, x, z);
            }
            item++;
            CollisionGround_Destroy(&ground);
        }
    }
    for (u32 z = 0; z < TILE_GRID_SEARCH_ROWS; z++) {
        for (u32 x = 0; x < TILE_GRID_SIZE; x++) {
            if (TileGrid_IsMarked(grid, x, z) && !TileGrid_IsMarked(grid, x + 1, z) && !TileGrid_IsMarked(grid, x - 1, z) &&
                !TileGrid_IsMarked(grid, x, z + 1) && !TileGrid_IsMarked(grid, x, z - 1)) {
                TileGrid_Unmark(grid, x, z);
            }
        }
    }
    return 1;
}
CLEAN_AS(func_02084e90, TileGrid_Build)
