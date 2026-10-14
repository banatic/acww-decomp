#include "../../../clean/main/tile_grid.h"
#include "diffcheck.h"

#define GRID DIFF_SCRATCH

/* A grid with some tiles marked, and a tile in it or one step outside it, as the neighbour
 * tests ask for (-1 arrives as 0xffffffff). */
static void grid_and_tile(DiffRng *rng, uint32_t args[4])
{
    TileGrid *grid = (TileGrid *) (uintptr_t) GRID;
    for (int z = 0; z < TILE_GRID_SIZE; z++) {
        grid->rows[z] = diff_range(rng, 0, 3) == 0 ? 0 : (u16) diff_rand(rng);
    }
    args[0] = GRID;
    args[1] = (uint32_t) diff_range(rng, -1, TILE_GRID_SIZE);
    args[2] = (uint32_t) diff_range(rng, -1, TILE_GRID_SIZE);
}

static uint32_t is_marked_in_search_rows(const uint32_t args[4])
{
    return (uint32_t) TileGrid_IsMarkedInSearchRows((const TileGrid *) (uintptr_t) args[0], args[1], args[2]);
}

static uint32_t is_marked(const uint32_t args[4])
{
    return (uint32_t) TileGrid_IsMarked((const TileGrid *) (uintptr_t) args[0], args[1], args[2]);
}

static uint32_t unmark(const uint32_t args[4])
{
    return (uint32_t) TileGrid_Unmark((TileGrid *) (uintptr_t) args[0], args[1], args[2]);
}

static uint32_t mark(const uint32_t args[4])
{
    return (uint32_t) TileGrid_Mark((TileGrid *) (uintptr_t) args[0], args[1], args[2]);
}

DIFF_CHECK(func_02084e00, "main", 0x02084e00 | 1, 32, 0, grid_and_tile, is_marked_in_search_rows)
DIFF_CHECK(func_02084e20, "main", 0x02084e20 | 1, 32, 0, grid_and_tile, is_marked)
DIFF_CHECK(func_02084e40, "main", 0x02084e40 | 1, 32, 0, grid_and_tile, unmark)
DIFF_CHECK(func_02084e68, "main", 0x02084e68 | 1, 32, 0, grid_and_tile, mark)
