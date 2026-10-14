/* A bit per tile of an acre. Coordinates are unsigned so that the neighbours of an edge tile
 * (x - 1 at x = 0) fall outside the grid and read as unmarked, as the callers rely on. */
#include "tile_grid.h"

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

/* func_02084e20 */
BOOL TileGrid_IsMarked(const TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SIZE) {
        return FALSE;
    }
    return (grid->rows[z] >> x) & 1;
}

/* func_02084e40: TRUE when the tile is in the grid. */
BOOL TileGrid_Unmark(TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SIZE) {
        return FALSE;
    }
    grid->rows[z] &= (u16) ~(1u << x);
    return TRUE;
}

/* func_02084e68: TRUE when the tile is in the grid. */
BOOL TileGrid_Mark(TileGrid *grid, u32 x, u32 z)
{
    if (x >= TILE_GRID_SIZE || z >= TILE_GRID_SIZE) {
        return FALSE;
    }
    grid->rows[z] |= (u16) (1u << x);
    return TRUE;
}

static_assert(sizeof(TileGrid) == 0x20, "TileGrid layout");
