/* A spot of the town (town_spot.h). */
#include "town_spot.h"

#include "acre_tile.h"
#include "clean.h"

#define TOWN_SPOT_ACRE_TILES 16
/* The rows of inner acres TownSpot_PickRandom keeps a mask for. */
#define TOWN_SPOT_MASK_ROWS 4

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern u32 func_020644cc(int bound); /* a random number below `bound` */
/* How many tiles of the acre func_02088024 accepts. `spot` is not read. */
extern int func_02087a08(TownSpot *spot, const TownSpotAcre *acre, AcreMap *map);
/* Whether the tile (x, z) of the map suits. */
extern int func_02088024(int x, int z, AcreMap *map);

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
            if (func_02087a08(spot, &acre, map) != 0) {
                mask[acre.z - 1] = (u8) (mask[acre.z - 1] | (1u << (acre.x - 1)));
                count++;
            }
        }
    }
    if (count <= 0) {
        return 0;
    }
    int pick = (int) func_020644cc(count);
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
            if (func_02088024(first_x + x, first_z + z, map) != 0) {
                mask[z] = (u16) (mask[z] | (1u << x));
                count++;
            }
        }
    }
    if (count <= 0) {
        return 0;
    }
    int pick = (int) func_020644cc(count);
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
