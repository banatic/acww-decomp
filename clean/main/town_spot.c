/* A spot of the town (town_spot.h). */
#include "town_spot.h"

#include "acre_tile.h"
#include "clean.h"
#include "map_item.h"
#include "town_tile.h"
#include "main_random.h"
#include "map_code.h"

#define TOWN_SPOT_ACRE_TILES 16
/* The rows of inner acres TownSpot_PickRandom keeps a mask for. */
#define TOWN_SPOT_MASK_ROWS 4

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_02087854: the spot as a position on the ground (y 0). Returns 0. */
int TownSpot_ToPosition(const TownSpot *spot, Vec3 *position)
{
    position->x = spot->x;
    position->z = spot->z;
    position->y = 0;
    return 0;
}
CLEAN_AS(func_02087854, TownSpot_ToPosition)

/* func_02087864 */
void TownSpot_Set(TownSpot *spot, u32 x, u32 z)
{
    spot->x = (fx32) x;
    spot->z = (fx32) z;
}
CLEAN_AS(func_02087864, TownSpot_Set)

/* func_0208786c: with a town map, one of its inner acres (the border acres left out) that has
 * tiles func_02088024 accepts, at random, and one of those tiles at random
 * (TownSpot_PickTileInAcre): the spot is set to its centre. Whether one was found.
 * REQUIRES: the map has at most 4 rows of inner acres (the town has 4); with more, the ROM's
 * code writes past its mask. A column past the 8th is never picked (its bit is lost).
 * BUG: had TownSpot_PickTileInAcre found no tile, the spot would be set from a position never
 * written; it always finds one, since the acre was picked for having some. Here it is 0. */
int TownSpot_PickRandom(TownSpot *spot)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return 0;
    }
    int count = 0;
    TownSpotAcre acre = {0, 0};
    int wide = map->acres_wide;
    int high = map->acres_high;
    u8 mask[TOWN_SPOT_MASK_ROWS];
    MI_CpuFill8(mask, 0, sizeof(mask));
    for (acre.z = 1; acre.z < high - 1; acre.z++) {
        for (acre.x = 1; acre.x < wide - 1; acre.x++) {
            if (TownSpot_CountTilesInAcre(spot, &acre, map) != 0) {
                mask[acre.z - 1] = (u8) (mask[acre.z - 1] | (1u << (acre.x - 1)));
                count++;
            }
        }
    }
    if (count <= 0) {
        return 0;
    }
    int pick = (int) MainRandom_Below(count);
    for (acre.z = 1; acre.z < high - 1; acre.z++) {
        for (acre.x = 1; acre.x < wide - 1; acre.x++) {
            if (((mask[acre.z - 1] >> (acre.x - 1)) & 1) == 0) {
                continue;
            }
            if (pick == 0) {
                Vec3 position = {0, 0, 0};
                TownSpot_PickTileInAcre(spot, &position, &acre, map);
                TownSpot_Set(spot, (u32) position.x, (u32) position.z);
                return 1;
            }
            pick--;
        }
    }
    return 0;
}
CLEAN_AS(func_0208786c, TownSpot_PickRandom)

/* func_02087950: one of the acre's tiles that func_02088024 accepts, at random: its centre
 * into `position`. Whether there was one. `spot` is not read. */
int TownSpot_PickTileInAcre(TownSpot *spot, Vec3 *position, const TownSpotAcre *acre, AcreMap *map)
{
    (void) spot;
    int count = 0;
    int first_x = 0;
    int first_z = 0;
    u16 mask[TOWN_SPOT_ACRE_TILES];
    MI_CpuFill8(mask, 0, sizeof(mask));
    AcreTile_TileOfAcre(&first_x, &first_z, acre->x, acre->z, 0, 0);
    for (int z = 0; z < TOWN_SPOT_ACRE_TILES; z++) {
        for (int x = 0; x < TOWN_SPOT_ACRE_TILES; x++) {
            if (TownSpot_TileSuits(first_x + x, first_z + z, map) != 0) {
                mask[z] = (u16) (mask[z] | (1u << x));
                count++;
            }
        }
    }
    if (count <= 0) {
        return 0;
    }
    int pick = (int) MainRandom_Below(count);
    for (int z = 0; z < TOWN_SPOT_ACRE_TILES; z++) {
        for (int x = 0; x < TOWN_SPOT_ACRE_TILES; x++) {
            if (((mask[z] >> x) & 1) == 0) {
                continue;
            }
            if (pick == 0) {
                AcreTile_TileCentre(position, (u32) (first_x + x), (u32) (first_z + z));
                return 1;
            }
            pick--;
        }
    }
    return 0;
}
CLEAN_AS(func_02087950, TownSpot_PickTileInAcre)

/* func_02087a08: how many of the acre's 16 x 16 tiles TownSpot_TileSuits accepts, row by row.
 * `spot` is not read. */
int TownSpot_CountTilesInAcre(TownSpot *spot, const TownSpotAcre *acre, AcreMap *map)
{
    (void) spot;
    int first_x = 0;
    int first_z = 0;
    int count = 0;
    AcreTile_TileOfAcre(&first_x, &first_z, acre->x, acre->z, 0, 0);
    for (int z = first_z; z < first_z + TOWN_SPOT_ACRE_TILES; z++) {
        for (int x = first_x; x < first_x + TOWN_SPOT_ACRE_TILES; x++) {
            if (TownSpot_TileSuits(x, z, map) != 0) {
                count++;
            }
        }
    }
    return count;
}
CLEAN_AS(func_02087a08, TownSpot_CountTilesInAcre)

/* func_02087a64 */
void TownSpot_Clear(TownSpot *spot)
{
    MI_CpuFill8(spot, 0, sizeof(*spot));
}
CLEAN_AS(func_02087a64, TownSpot_Clear)

/* func_02087a70: the destructor does nothing. */
void TownSpot_Destruct(TownSpot *spot)
{
    (void) spot;
}
CLEAN_AS(func_02087a70, TownSpot_Destruct)

/* func_02087a74: the constructor does nothing. */
void TownSpot_Construct(TownSpot *spot)
{
    (void) spot;
}
CLEAN_AS(func_02087a74, TownSpot_Construct)

/* The objects that keep a tile from suiting: the event buildings, and (beside the tile) the
 * codes of the growth lines and 0x66-0x6d (map_item.h) past their first stage. */
#define TOWN_SPOT_EVENT_BUILDING_FIRST 0x5000
#define TOWN_SPOT_EVENT_BUILDING_LAST 0x5021

/* The acre of a tile, with the ROM's arithmetic shift for tiles left of or above the map. */
static int town_spot_acre_of(int tile)
{
    return tile >= 0 ? tile / TOWN_SPOT_ACRE_TILES : ~(~tile / TOWN_SPOT_ACRE_TILES);
}

static int town_spot_is_event_building(u16 code)
{
    return code >= TOWN_SPOT_EVENT_BUILDING_FIRST && code <= TOWN_SPOT_EVENT_BUILDING_LAST;
}

/* The growth lines 0x26-0x2a, 0x2f-0x56, 0x57-0x5b, 0x5d-0x61 and 0xc8-0xcf, and the codes
 * 0x66-0x6d, tested range by range as the ROM does. */
static int town_spot_grows(u16 code)
{
    static const u16 ranges[][2] = {
        {0x26, 0x2a}, {0x5d, 0x61}, {0x2f, 0x56}, {0x57, 0x5b}, {0x66, 0x68},
        {0x69, 0x69}, {0x6a, 0x6c}, {0x6d, 0x6d}, {0xc8, 0xcf},
    };
    for (size_t i = 0; i < sizeof(ranges) / sizeof(ranges[0]); i++) {
        if (code >= ranges[i][0] && code <= ranges[i][1]) {
            return 1;
        }
    }
    return 0;
}

/* The object of tile (x, z) of the map in layer 0, or NULL off the map. */
static const u16 *town_spot_item(AcreMap *map, int x, int z)
{
    int acre_x = town_spot_acre_of(x);
    int acre_z = town_spot_acre_of(z);
    return AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * TOWN_SPOT_ACRE_TILES,
                               z - acre_z * TOWN_SPOT_ACRE_TILES, 0);
}

/* func_02088024: whether an actor may be put on tile (x, z) of the map: the tile is clear
 * (TownTile_IsClear), and for the tiles 1 and then 2 away in +z and in -z (asked in the order
 * +1, -1, +2, -2) each is on the map and holds no event building (0x5000-0x5021); the ones in
 * +z must also not hold an object func_0204c71c accepts, nor a growing object past its first
 * stage (MapItem_IsStage0 is asked first). 0 without a map. */
int TownSpot_TileSuits(int x, int z, AcreMap *map)
{
    if (map == NULL) {
        return 0;
    }
    if (TownTile_IsClear(x, z, map) == 0) {
        return 0;
    }
    for (int i = 1; i <= 2; i++) {
        const u16 *item = town_spot_item(map, x, z + i);
        if (item == NULL || town_spot_is_event_building(*item)) {
            return 0;
        }
        if (MapCode_IsSpecial(item) != 0) {
            return 0;
        }
        if (MapItem_IsStage0(item) == 0 && town_spot_grows(*item)) {
            return 0;
        }
        item = town_spot_item(map, x, z - i);
        if (item == NULL || town_spot_is_event_building(*item)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_02088024, TownSpot_TileSuits)
