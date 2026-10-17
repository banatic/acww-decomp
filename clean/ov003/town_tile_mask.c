/* Masks of the town's tiles that something may not be placed on (town_tile_mask.h). */
#include "town_tile_mask.h"

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_map.h"    /* AcreMap_Town */
#include "main/acre_tile.h"   /* AcreTile_ItemInAcre, AcreTile_TileCentreInAcre */
#include "main/actor_table.h" /* Position_Tile */
#include "main/main_random.h"
#include "main/map_code.h"
#include "main/unit_type_info.h"

#define TOWN_TILE_MASK_FIRST 0x10                                             /* the first tile of acre 1 */
#define TOWN_TILE_MASK_END 0x50                                               /* the tile after acre 4 */
#define TOWN_TILE_MASK_ACRE_ROW (TOWN_TILE_MASK_ACRES * TOWN_TILE_MASK_TILES) /* halfwords */

extern u16 data_ov003_02260794[TOWN_TILE_MASK_SIZE / 2];
extern u16 data_ov003_02260594[TOWN_TILE_MASK_SIZE / 2];

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* `value` shifted left as the ARM does by a register: by its low byte, 0 from 32 on. */
static u32 town_tile_mask_shl(u32 value, int amount)
{
    u32 by = (u32) amount & 0xff;
    return by >= 32 ? 0 : value << by;
}

/* The bits 0 to `last` (none for -1 and less; all for 31). */
static u32 town_tile_mask_bits_to(int last)
{
    return town_tile_mask_shl(2, last) - 1;
}

/* func_ov003_0222c4b8: in `mask` (a copy of one of the masks), the tiles around the tile of the
 * point (x, z) marked: `radius` tiles to either side, `up` rows before it and `down` rows after
 * it, clipped to the inner acres. The rectangle may run into the next acre across, down and
 * both; it is marked in at most those four acres.
 * QUIRK: when it starts within an acre (column 1 or more), the column it starts in is left out,
 * and the rectangle is one column narrower than it is from column 0.
 * REQUIRES: `mask` is halfword aligned. */
void TownTileMask_MarkAround(u16 *mask, int x, int z, int radius, u8 up, u8 down)
{
    int tile_x = 0;
    int tile_z = 0;
    Vec3 point = {x, 0, z};
    Position_Tile(&tile_x, &tile_z, (const Position *) &point);
    int left = tile_x - radius;
    int top = tile_z - up;
    int right = tile_x + radius;
    int bottom = tile_z + down;
    if (left < TOWN_TILE_MASK_FIRST) {
        left = TOWN_TILE_MASK_FIRST;
    }
    if (top < TOWN_TILE_MASK_FIRST) {
        top = TOWN_TILE_MASK_FIRST;
    }
    if (right > TOWN_TILE_MASK_END) {
        right = TOWN_TILE_MASK_END;
    }
    if (bottom > TOWN_TILE_MASK_END) {
        bottom = TOWN_TILE_MASK_END;
    }
    if (left >= right || top >= bottom) {
        return;
    }
    int acre_x = left >> 4;
    int acre_z = top >> 4;
    int first_column = left - (acre_x << 4);
    int first_row = top - (acre_z << 4);
    int width = first_column + radius * 2;
    int columns = width > TOWN_TILE_MASK_TILES ? TOWN_TILE_MASK_TILES : width;
    int height = down + (first_row + up);
    int rows = height > TOWN_TILE_MASK_TILES ? TOWN_TILE_MASK_TILES : height;
    if (acre_x == 1) {
        int past_edge = tile_x - TOWN_TILE_MASK_FIRST - radius;
        if (past_edge < 0) {
            columns += past_edge;
        }
    }
    if (acre_z == 1) {
        int past_edge = tile_z - TOWN_TILE_MASK_FIRST - up;
        if (past_edge < 0) {
            rows += past_edge;
        }
    }
    u32 skipped = first_column > 0 ? town_tile_mask_bits_to(first_column) : 0;
    u16 bits = (u16) (town_tile_mask_bits_to(columns) - skipped);
    u16 *acre = mask + ((acre_z - 1) * TOWN_TILE_MASK_ACRES + (acre_x - 1)) * TOWN_TILE_MASK_TILES;
    for (int row = first_row; row < rows; row++) {
        acre[row] |= bits;
    }
    if (height > TOWN_TILE_MASK_TILES && acre_z < TOWN_TILE_MASK_ACRES) {
        u16 *below = acre + TOWN_TILE_MASK_ACRE_ROW;
        for (int row = 0; row < height - TOWN_TILE_MASK_TILES; row++) {
            below[row] |= bits;
        }
    }
    if (width > TOWN_TILE_MASK_TILES && acre_x < TOWN_TILE_MASK_ACRES) {
        u16 next_bits = (u16) town_tile_mask_bits_to(width - TOWN_TILE_MASK_TILES);
        u16 *next = acre + TOWN_TILE_MASK_TILES;
        for (int row = first_row; row < rows; row++) {
            next[row] |= next_bits;
        }
    }
    if (height > TOWN_TILE_MASK_TILES && width > TOWN_TILE_MASK_TILES && acre_x < TOWN_TILE_MASK_ACRES &&
        acre_z < TOWN_TILE_MASK_ACRES) {
        u16 next_bits = (u16) town_tile_mask_bits_to(width - TOWN_TILE_MASK_TILES);
        u16 *next_below = acre + TOWN_TILE_MASK_ACRE_ROW + TOWN_TILE_MASK_TILES;
        for (int row = 0; row < height - TOWN_TILE_MASK_TILES; row++) {
            next_below[row] |= next_bits;
        }
    }
}
CLEAN_AS(func_ov003_0222c4b8, TownTileMask_MarkAround)

/* func_ov003_0222c68c: a free tile of an acre's 16 `rows` picked at random (the n-th clear bit,
 * row by row, n below `bound`): the centre of that tile of acre (*acre_x + 1, *acre_z + 1) is
 * written back to *acre_x and *acre_z (its x and z). Nothing changes when there are no more than
 * n free tiles.
 * REQUIRES: `rows` is halfword aligned. */
void TownTileMask_PickFree(int bound, u16 *rows, int *acre_x, int *acre_z)
{
    int left = (int) MainRandom_Below(bound);
    for (int row = 0; row < TOWN_TILE_MASK_TILES; row++) {
        for (int column = 0; column < TOWN_TILE_MASK_TILES; column++) {
            if (((rows[row] >> column) & 1) == 0 && left-- == 0) {
                Vec3 centre;
                AcreTile_TileCentreInAcre(&centre, *acre_x + 1, *acre_z + 1, column, row);
                *acre_x = centre.x;
                *acre_z = centre.z;
                return;
            }
        }
    }
}
CLEAN_AS(func_ov003_0222c68c, TownTileMask_PickFree)

/* func_ov003_0222c6f0: whether the item code is 0xcc-0xcf. */
int TownTileMask_IsCodeCcToCf(u16 *code)
{
    return *code >= 0xcc && *code <= 0xcf;
}
CLEAN_AS(func_ov003_0222c6f0, TownTileMask_IsCodeCcToCf)

/* func_ov003_0222c704: whether the item code is 0x5b or 0x66-0x6d. */
int TownTileMask_IsCode5bOr66To6d(u16 *code)
{
    return *code == 0x5b || (*code >= 0x66 && *code <= 0x6d);
}
CLEAN_AS(func_ov003_0222c704, TownTileMask_IsCode5bOr66To6d)

/* func_ov003_0222c71c: whether the item code is 0x2a, 0x61, or in 0x33-0x36, 0x3b-0x3e,
 * 0x43-0x46, 0x4b-0x4e or 0x53-0x56. */
int TownTileMask_IsCodeOfList(u16 *code)
{
    u16 value = *code;
    return value == 0x2a || value == 0x61 || (value >= 0x33 && value <= 0x36) || (value >= 0x3b && value <= 0x3e) ||
           (value >= 0x43 && value <= 0x46) || (value >= 0x4b && value <= 0x4e) || (value >= 0x53 && value <= 0x56);
}
CLEAN_AS(func_ov003_0222c71c, TownTileMask_IsCodeOfList)

/* func_ov003_0222c758: both masks built from the town's map (none: nothing): cleared, then for
 * each inner acre (across, then down within it), row by row, each tile with an item code is
 * marked in both masks when it is a building's or covered by one, or of group 1; in the second
 * only when of group 2. */
void TownTileMask_Build(void)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return;
    }
    MI_CpuFill8(data_ov003_02260794, 0, TOWN_TILE_MASK_SIZE);
    MI_CpuFill8(data_ov003_02260594, 0, TOWN_TILE_MASK_SIZE);
    for (int across = 0; across < TOWN_TILE_MASK_ACRES; across++) {
        int first_x = (across + 1) << 4;
        for (int down = 0; down < TOWN_TILE_MASK_ACRES; down++) {
            int first_z = (down + 1) << 4;
            int acre = (down * TOWN_TILE_MASK_ACRES + across) * TOWN_TILE_MASK_TILES;
            for (int row = 0; row < TOWN_TILE_MASK_TILES; row++) {
                int z = first_z + row;
                for (int column = 0; column < TOWN_TILE_MASK_TILES; column++) {
                    int x = first_x + column;
                    u16 *code = AcreTile_ItemInAcre(map, (u32) (x >> 4), (u32) (z >> 4), x & 15, z & 15, 0);
                    if (code == NULL) {
                        continue;
                    }
                    u16 bit = (u16) (1 << column);
                    if (MapCode_IsBuildingOrCovered(code) != 0 || UnitTypeInfo_GroupAt(x, z) == 1) {
                        data_ov003_02260794[acre + row] |= bit;
                        data_ov003_02260594[acre + row] |= bit;
                    } else if (UnitTypeInfo_GroupAt(x, z) == 2) {
                        data_ov003_02260594[acre + row] |= bit;
                    }
                }
            }
        }
    }
}
CLEAN_AS(func_ov003_0222c758, TownTileMask_Build)
