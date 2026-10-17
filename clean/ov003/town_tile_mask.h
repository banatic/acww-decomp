/* Masks of the tiles of the town's 4 by 4 inner acres (acres 1-4 across and down) that
 * something may not be placed on, built when the town is set up (TownTileMask_Build) into two
 * global masks of 0x200 bytes: data_ov003_02260794 marks the tiles of a building (or covered by
 * one) and those of group 1 of the unit types; data_ov003_02260594 also those of group 2. A
 * mask is 16 rows of 16 bits (bit n for the tile n across) for each acre, the acres row by
 * row: the row r of acre (x, z), counted from acre 1, is the halfword (z * 4 + x) * 16 + r.
 *
 * A copy of one (func_ov003_0222d1bc picks the first for the kinds 0, 5 and 6) is marked around
 * what stands in the town (TownTileMask_MarkAround) before a free tile is picked at random from
 * an acre's rows (TownTileMask_PickFree). The tests of a tile's item code
 * (TownTileMask_IsCode*) are those func_ov003_0222c888 makes; what the codes stand for is not
 * read from this code. */
#ifndef CLEAN_OV003_TOWN_TILE_MASK_H
#define CLEAN_OV003_TOWN_TILE_MASK_H

#include "types.h"

#define TOWN_TILE_MASK_ACRES 4  /* across and down */
#define TOWN_TILE_MASK_TILES 16 /* of an acre, across and down */
#define TOWN_TILE_MASK_SIZE 0x200

void TownTileMask_MarkAround(u16 *mask, int x, int z, int radius, u8 up, u8 down);
void TownTileMask_PickFree(int bound, u16 *rows, int *acre_x, int *acre_z);
int TownTileMask_IsCodeCcToCf(u16 *code);
int TownTileMask_IsCode5bOr66To6d(u16 *code);
int TownTileMask_IsCodeOfList(u16 *code);
void TownTileMask_Build(void);

#endif
