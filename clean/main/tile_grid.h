/* One bit for each of the 16 x 16 tiles of an acre. func_02084e90 builds one: a bit for each
 * tile whose item is 0xfff1 (nothing there) and that passes a further test, then clears the
 * bits that have no marked neighbour in the rows 0-13. */
#ifndef CLEAN_MAIN_TILE_GRID_H
#define CLEAN_MAIN_TILE_GRID_H

#include "types.h"

#define TILE_GRID_SIZE 16
/* The rows the callers search; the last two are cleared before a search (func_02085d6c). */
#define TILE_GRID_SEARCH_ROWS 14

typedef struct TileGrid {
    u16 rows[TILE_GRID_SIZE]; /* bit x of row z is tile (x, z) */
} TileGrid;

BOOL TileGrid_IsMarkedInSearchRows(const TileGrid *grid, u32 x, u32 z);
BOOL TileGrid_IsMarked(const TileGrid *grid, u32 x, u32 z);
BOOL TileGrid_Unmark(TileGrid *grid, u32 x, u32 z);
BOOL TileGrid_Mark(TileGrid *grid, u32 x, u32 z);
int TileGrid_Build(TileGrid *grid);

#endif
