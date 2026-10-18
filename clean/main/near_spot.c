/* A spot near a position (near_spot.h). */
#include "near_spot.h"

#include "acre_tile.h"
#include "clean.h"
#include "town_spot.h"
#include "main_random.h"

/* The tiles NearSpot_Pick searches: rows from 5 tiles to +z of the position, starting 8 tiles
 * to the side, and columns from that side, from the position's row to 4 tiles to +z; each row
 * and column keeps at most NEAR_SPOT_ROWS x 16 candidates. */
#define NEAR_SPOT_SIDE_TILES 8
#define NEAR_SPOT_FIRST_ROW 5
#define NEAR_SPOT_FIRST_COLUMN_END 4
#define NEAR_SPOT_ROWS 4

extern AcreMap *data_021c80bc; /* the map of the scene */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The tests handed to NearSpot_PickInRange: the game's own functions. */
extern int func_02087dd0(int x, int z, AcreMap *map); /* NearSpot_ColumnTileSuits */
extern int func_02087dd8(int z, int x, AcreMap *map); /* NearSpot_RowTileSuits */

/* A tile a row or column search found. */
typedef struct NearSpotTile {
    int x;
    int z;
} NearSpotTile;

/* func_02087b8c: a tile near `from` that TownSpot_TileSuits accepts, searched on the scene's
 * map to +z and to one side (+x when `side` is 0, else -x). Step by step, while a row is left
 * on the map or the column is on it:
 *   a row (5 tiles to +z of `from` first, then one more each step) between `from`'s column and
 *   a column 8 tiles to the side (8 + `side` to -x), that column moving one more to the side
 *   each step while it is inside the map's border; and
 *   a column (starting at that same column, one more to the side each step) from `from`'s row
 *   to 4 tiles to +z, one more each step up to the map's last row;
 * each picking one of its tiles at random. When both found one, either at random
 * (func_020644cc(10)); else the one that found. The spot is set to that tile's centre with a
 * random quarter turn and marked found; without a map or a tile the found mark is cleared.
 * Whether a tile was found.
 * BUG: in the ROM, a search not made on the first step (the first row already past the map's
 * last row, or the first column off the map) leaves its result an uninitialised stack word,
 * and a nonzero one would pick tile (0, 0) at once. Here it counts as nothing found. */
int NearSpot_Pick(NearSpot *spot, const Position *from, int side)
{
    AcreMap *map = data_021c80bc;
    if (map == NULL) {
        NearSpot_ClearFound(spot);
        return 0;
    }
    const NearSpotTile *picked = NULL;
    int from_x = 0;
    int from_z = 0;
    int wide = map->tiles_wide;
    int high = map->tiles_high;
    NearSpotTile in_row = {0, 0};
    NearSpotTile in_column = {0, 0};
    int step = side != 0 ? -1 : 1;
    Position_Tile(&from_x, &from_z, from);

    int row_end_x = from_x + step * NEAR_SPOT_SIDE_TILES - side;
    int row_z = from_z + NEAR_SPOT_FIRST_ROW;
    int column_x = row_end_x;
    int column_end_z = from_z + NEAR_SPOT_FIRST_COLUMN_END;
    Vec3 centre = {0, 0, 0};
    u16 row_bits[NEAR_SPOT_ROWS];
    u16 column_bits[NEAR_SPOT_ROWS];
    int row_found = 0;
    int column_found = 0;

    while (row_z < high || (column_x >= 0 && column_x < wide)) {
        if (row_z < high) {
            in_row.z = row_z;
            row_found =
                NearSpot_PickInRange(&in_row.x, func_02087dd8, row_z, row_end_x, from_x, map, row_bits, NEAR_SPOT_ROWS);
            if (row_end_x > 0 && row_end_x < wide - 1) {
                row_end_x += step;
            }
            row_z++;
        }
        if (column_x >= 0 && column_x < wide) {
            in_column.x = column_x;
            column_found = NearSpot_PickInRange(&in_column.z, func_02087dd0, column_x, from_z, column_end_z, map, column_bits,
                                                NEAR_SPOT_ROWS);
            column_x += step;
            if (column_end_z < high - 1) {
                column_end_z++;
            }
        }
        if (row_found != 0) {
            if (column_found != 0 && (MainRandom_Below(10) & 1) != 0) {
                picked = &in_column;
            } else {
                picked = &in_row;
            }
            break;
        }
        if (column_found != 0) {
            picked = &in_column;
            break;
        }
    }

    if (picked == NULL) {
        NearSpot_ClearFound(spot);
        return 0;
    }
    AcreTile_TileCentre(&centre, (u32) picked->x, (u32) picked->z);
    NearSpot_SetFromPosition(spot, &centre);
    u32 facing = MainRandom_Below(4) & 3;
    spot->flags = (u8) ((spot->flags & ~NEAR_SPOT_FACING_MASK) | (facing << NEAR_SPOT_FACING_SHIFT));
    NearSpot_SetFound(spot);
    return 1;
}
CLEAN_AS(func_02087b8c, NearSpot_Pick)

/* func_02087d00: of the tiles `first` to `last` (either way round) of a row or column, the
 * ones `test` accepts noted in `bits` (`rows` halfwords of 16 bits, cleared first; the search
 * stops when they are full), and one of them picked at random into `*out`. Whether one was. */
int NearSpot_PickInRange(int *out, NearSpotTest *test, int fixed, int first, int last, AcreMap *map, u16 *bits, int rows)
{
    int count = 0;
    int row = 0;
    int bit = 0;
    if (first > last) {
        int swap = first;
        first = last;
        last = swap;
    }
    MI_CpuFill8(bits, 0, (u32) (rows * 2));
    for (int i = first; i <= last; i++) {
        if (test(fixed, i, map) != 0) {
            bits[row] = (u16) (bits[row] | (1u << bit));
            count++;
        }
        if (++bit >= 16) {
            bit = 0;
            row++;
        }
        if (row >= rows) {
            break;
        }
    }
    if (count <= 0) {
        return 0;
    }
    int pick = (int) MainRandom_Below(count);
    row = 0;
    bit = 0;
    for (int i = first; i <= last; i++) {
        if (((bits[row] >> bit) & 1) != 0) {
            if (pick == 0) {
                *out = i;
                return 1;
            }
            pick--;
        }
        if (++bit >= 16) {
            bit = 0;
            row++;
        }
        if (row >= rows) {
            break;
        }
    }
    return 0;
}
CLEAN_AS(func_02087d00, NearSpot_PickInRange)

/* func_02087dd0: the test of a column, x fixed. */
int NearSpot_ColumnTileSuits(int x, int z, AcreMap *map)
{
    return TownSpot_TileSuits(x, z, map);
}
CLEAN_AS(func_02087dd0, NearSpot_ColumnTileSuits)

/* func_02087dd8: the test of a row, z fixed. */
int NearSpot_RowTileSuits(int z, int x, AcreMap *map)
{
    return TownSpot_TileSuits(x, z, map);
}
CLEAN_AS(func_02087dd8, NearSpot_RowTileSuits)

/* func_02087de8: the quarter turn as an angle.
 * QUIRK: sign-extended from 16 bits: 0, 0x4000, -0x8000 or -0x4000. */
int NearSpot_Facing(const NearSpot *spot)
{
    int angle = ((spot->flags & NEAR_SPOT_FACING_MASK) >> NEAR_SPOT_FACING_SHIFT) * 0x4000;
    return angle >= 0x8000 ? angle - 0x10000 : angle;
}
CLEAN_AS(func_02087de8, NearSpot_Facing)

/* func_02087df4 */
void NearSpot_SetServed(NearSpot *spot)
{
    spot->flags |= NEAR_SPOT_SERVED;
}
CLEAN_AS(func_02087df4, NearSpot_SetServed)

/* func_02087e00 */
void NearSpot_ClearServed(NearSpot *spot)
{
    spot->flags = (u8) (spot->flags & ~NEAR_SPOT_SERVED);
}
CLEAN_AS(func_02087e00, NearSpot_ClearServed)

/* func_02087e0c */
int NearSpot_WasServed(const NearSpot *spot)
{
    return (spot->flags & NEAR_SPOT_SERVED) != 0;
}
CLEAN_AS(func_02087e0c, NearSpot_WasServed)

/* func_02087e20 */
void NearSpot_ClearFound(NearSpot *spot)
{
    spot->flags = (u8) (spot->flags & ~NEAR_SPOT_FOUND);
}
CLEAN_AS(func_02087e20, NearSpot_ClearFound)

/* func_02087e2c */
void NearSpot_SetFound(NearSpot *spot)
{
    spot->flags |= NEAR_SPOT_FOUND;
}
CLEAN_AS(func_02087e2c, NearSpot_SetFound)

/* func_02087e38 */
int NearSpot_Found(const NearSpot *spot)
{
    return (spot->flags & NEAR_SPOT_FOUND) != 0;
}
CLEAN_AS(func_02087e38, NearSpot_Found)

/* func_02087e4c: x and z into the position; its y is left alone. */
void NearSpot_ToPosition(const NearSpot *spot, Vec3 *position)
{
    position->x = spot->x;
    position->z = spot->z;
}
CLEAN_AS(func_02087e4c, NearSpot_ToPosition)

/* func_02087e58: x and z from the position. */
void NearSpot_SetFromPosition(NearSpot *spot, const Vec3 *position)
{
    spot->x = position->x;
    spot->z = position->z;
}
CLEAN_AS(func_02087e58, NearSpot_SetFromPosition)

/* func_02087e64 */
void NearSpot_Clear(NearSpot *spot)
{
    MI_CpuFill8(spot, 0, sizeof(*spot));
}
CLEAN_AS(func_02087e64, NearSpot_Clear)

/* func_02087e70: the destructor does nothing. */
void NearSpot_Destruct(NearSpot *spot)
{
    (void) spot;
}
CLEAN_AS(func_02087e70, NearSpot_Destruct)

/* func_02087e74: the constructor does nothing. */
void NearSpot_Construct(NearSpot *spot)
{
    (void) spot;
}
CLEAN_AS(func_02087e74, NearSpot_Construct)
