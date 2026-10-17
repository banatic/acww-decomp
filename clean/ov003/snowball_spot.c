/* Where the town's loose snowballs are put (snowball_spot.h). */
#include "snowball_spot.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor_table.h"
#include "main/collision_query.h"
#include "main/main_random.h"

static_assert(sizeof(SnowballSpotAcre) == 0x22, "an acre of the mask");
static_assert(sizeof(SnowballSpotMask) == 0x220, "the mask");

/* The empty tile of the map. */
#define SNOWBALL_SPOT_NO_ITEM 0xfff1

/* The scene's map (acre_map.h). */
extern AcreMap *data_021c80bc;
/* The mask, the guard of its one-time construction (bit 0) and its record for the list of
 * global destructors. */
extern SnowballSpotMask data_ov003_02262b58;
extern u32 data_ov003_02262b28;
extern u8 data_ov003_02262b2c[];

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __register_global_object(void *object, void *destruct, void *record);
/* The game's functions the construction of the mask hands on (SnowballSpot_ConstructAcre,
 * SnowballSpot_DestroyAcre, SnowballSpot_DestroyMask). */
extern void func_ov003_02235f30(void *acre);
extern void func_ov003_02235f2c(void *acre);
extern void *func_ov003_02235f10(void *mask);

/* func_ov003_02235d88: a spot for a loose ball: `spot` becomes the centre of a free tile of the
 * inner acres, and 1 is returned; 0 when there is none. A tile is taken when collision byte 8
 * says so of it (CollisionQuery_Byte08IfFree) or of either of the two tiles south of it
 * (CollisionQuery_Byte08IfNoPost); with `avoid_items` also when an item lies on it. With
 * `away_from`, the 15 by 15 tiles around its tile are taken too. Finding none while avoiding
 * items, it tries again without.
 * QUIRK: acres 1 to 5 are looked at across and down, and the mask keeps 4: the fifth row and
 * column of acres are marked onto the first ones. */
int SnowballSpot_Pick(void *unused, Vec3 *spot, const Vec3 *away_from, int avoid_items)
{
    AcreMap *map = data_021c80bc;
    SnowballSpotMask *mask = &data_ov003_02262b58;

    if ((data_ov003_02262b28 & 1) == 0) {
        __cxa_vec_ctor(mask, SNOWBALL_SPOT_ACRES * SNOWBALL_SPOT_ACRES, sizeof(SnowballSpotAcre), func_ov003_02235f30,
                       func_ov003_02235f2c);
        __register_global_object(mask, (void *) func_ov003_02235f10, data_ov003_02262b2c);
        data_ov003_02262b28 |= 1;
    }
    SnowballSpot_Clear(mask);

    for (u32 acre_z = 1; acre_z < 6; acre_z++) {
        for (u32 acre_x = 1; acre_x < 6; acre_x++) {
            for (u32 z = 0; z < SNOWBALL_SPOT_TILES; z++) {
                for (u32 x = 0; x < SNOWBALL_SPOT_TILES; x++) {
                    int tile_x;
                    int tile_z;
                    AcreTile_TileOfAcre(&tile_x, &tile_z, (int) acre_x, (int) acre_z, (int) x, (int) z);
                    if (CollisionQuery_Byte08IfFree(tile_x, tile_z) == 0 ||
                        CollisionQuery_Byte08IfNoPost(tile_x, tile_z + 1) == 0 ||
                        CollisionQuery_Byte08IfNoPost(tile_x, tile_z + 2) == 0) {
                        SnowballSpot_Take(mask, tile_x, tile_z);
                    } else if (avoid_items != 0) {
                        int in_x = tile_x >> 4;
                        int in_z = tile_z >> 4;
                        u16 *item =
                            AcreTile_ItemInAcre(map, (u32) in_x, (u32) in_z, tile_x - (in_x << 4), tile_z - (in_z << 4), 0);
                        if (item != NULL && *item != SNOWBALL_SPOT_NO_ITEM) {
                            SnowballSpot_Take(mask, tile_x, tile_z);
                        }
                    }
                }
            }
        }
    }

    if (away_from != NULL) {
        int centre_x;
        int centre_z;
        Position_Tile(&centre_x, &centre_z, (const Position *) (const void *) away_from);
        for (int z = centre_z - 7; z <= centre_z + 7; z++) {
            for (int x = centre_x - 7; x <= centre_x + 7; x++) {
                SnowballSpot_Take(mask, x, z);
            }
        }
    }

    int x;
    int z;
    if (SnowballSpot_PickTile(mask, &x, &z) != 0) {
        AcreTile_TileCentre(spot, (u32) x, (u32) z);
        return 1;
    }
    if (avoid_items != 0) {
        return SnowballSpot_Pick(unused, spot, away_from, 0);
    }
    return 0;
}
CLEAN_AS(func_ov003_02235d88, SnowballSpot_Pick)

/* func_ov003_02235f10: the global destructor of the mask: each acre destroyed; returns the
 * mask. */
SnowballSpotMask *SnowballSpot_DestroyMask(SnowballSpotMask *mask)
{
    __cxa_vec_cleanup(mask, SNOWBALL_SPOT_ACRES * SNOWBALL_SPOT_ACRES, sizeof(SnowballSpotAcre), func_ov003_02235f2c);
    return mask;
}
CLEAN_AS(func_ov003_02235f10, SnowballSpot_DestroyMask)

/* func_ov003_02235f2c: the destructor of an acre: nothing to do. */
void SnowballSpot_DestroyAcre(SnowballSpotAcre *acre)
{
    (void) acre;
}
CLEAN_AS(func_ov003_02235f2c, SnowballSpot_DestroyAcre)

/* func_ov003_02235f30: the constructor of an acre: nothing to do. */
void SnowballSpot_ConstructAcre(SnowballSpotAcre *acre)
{
    (void) acre;
}
CLEAN_AS(func_ov003_02235f30, SnowballSpot_ConstructAcre)

/* func_ov003_02235f34: a free tile of a random acre among those with free tiles, as world tile
 * (*x, *z); whether there was one. */
int SnowballSpot_PickTile(SnowballSpotMask *mask, int *x, int *z)
{
    int count = SnowballSpot_OpenAcres(mask);
    if (count == 0) {
        return 0;
    }
    int chosen = (int) MainRandom_Below(count);
    int n = 0;
    for (u32 acre_z = 0; acre_z < SNOWBALL_SPOT_ACRES; acre_z++) {
        for (u32 acre_x = 0; acre_x < SNOWBALL_SPOT_ACRES; acre_x++) {
            SnowballSpotAcre *acre = &mask->acres[acre_z][acre_x];
            if (acre->free == 0) {
                continue;
            }
            if (chosen == n) {
                int in_x;
                int in_z;
                if (SnowballSpot_PickInAcre(acre, &in_x, &in_z) != 0) {
                    *x = (int) ((acre_x + 1) << 4) + in_x;
                    *z = (int) ((acre_z + 1) << 4) + in_z;
                    return 1;
                }
                return 0;
            }
            n++;
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_02235f34, SnowballSpot_PickTile)

/* func_ov003_02235fb8: world tile (x, z) marked taken, in the acre of the mask its inner acre
 * falls on (wrapping every four acres). */
void SnowballSpot_Take(SnowballSpotMask *mask, int x, int z)
{
    SnowballSpotAcre *acre = &mask->acres[((z - 0x10) >> 4) & 3][((x - 0x10) >> 4) & 3];
    SnowballSpot_TakeInAcre(acre, x & 0xf, z & 0xf);
}
CLEAN_AS(func_ov003_02235fb8, SnowballSpot_Take)

/* func_ov003_02235fec: how many acres of the mask have a free tile. */
int SnowballSpot_OpenAcres(SnowballSpotMask *mask)
{
    int count = 0;
    for (u32 acre_z = 0; acre_z < SNOWBALL_SPOT_ACRES; acre_z++) {
        for (u32 acre_x = 0; acre_x < SNOWBALL_SPOT_ACRES; acre_x++) {
            if (mask->acres[acre_z][acre_x].free != 0) {
                count++;
            }
        }
    }
    return count;
}
CLEAN_AS(func_ov003_02235fec, SnowballSpot_OpenAcres)

/* func_ov003_02236028: every acre of the mask cleared. */
void SnowballSpot_Clear(SnowballSpotMask *mask)
{
    for (u32 acre_z = 0; acre_z < SNOWBALL_SPOT_ACRES; acre_z++) {
        for (u32 acre_x = 0; acre_x < SNOWBALL_SPOT_ACRES; acre_x++) {
            SnowballSpot_ClearAcre(&mask->acres[acre_z][acre_x]);
        }
    }
}
CLEAN_AS(func_ov003_02236028, SnowballSpot_Clear)

/* func_ov003_0223605c: a random free tile of the acre, counted row by row, as (*x, *z) in it;
 * whether there was one. */
int SnowballSpot_PickInAcre(SnowballSpotAcre *acre, int *x, int *z)
{
    if (acre->free == 0) {
        return 0;
    }
    int chosen = (int) MainRandom_Below(acre->free);
    int n = 0;
    for (u32 row = 0; row < SNOWBALL_SPOT_TILES; row++) {
        for (u32 column = 0; column < SNOWBALL_SPOT_TILES; column++) {
            if (SnowballSpot_IsTaken(acre, (int) column, (int) row) == 0) {
                if (chosen == n) {
                    *x = (int) column;
                    *z = (int) row;
                    return 1;
                }
                n++;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov003_0223605c, SnowballSpot_PickInAcre)

/* func_ov003_022360b8: whether tile (x, z) of the acre is taken (their low four bits). */
int SnowballSpot_IsTaken(SnowballSpotAcre *acre, int x, int z)
{
    return (acre->rows[z & 0xf] >> (x & 0xf)) & 1;
}
CLEAN_AS(func_ov003_022360b8, SnowballSpot_IsTaken)

/* func_ov003_022360d8: tile (x, z) of the acre marked taken, and the free count lowered, when it
 * was not taken yet. */
void SnowballSpot_TakeInAcre(SnowballSpotAcre *acre, int x, int z)
{
    if (SnowballSpot_IsTaken(acre, x, z) != 0) {
        return;
    }
    acre->rows[z & 0xf] = (u16) (acre->rows[z & 0xf] | 1u << (x & 0xf));
    acre->free--;
}
CLEAN_AS(func_ov003_022360d8, SnowballSpot_TakeInAcre)

/* func_ov003_02236110: every tile of the acre free. */
void SnowballSpot_ClearAcre(SnowballSpotAcre *acre)
{
    for (u32 row = 0; row < SNOWBALL_SPOT_TILES; row++) {
        acre->rows[row] = 0;
    }
    acre->free = SNOWBALL_SPOT_TILES * SNOWBALL_SPOT_TILES;
}
CLEAN_AS(func_ov003_02236110, SnowballSpot_ClearAcre)
