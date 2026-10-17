/* Where overlay 72's character places item 0x1568 in the town (gull_spots.h). */
#include "gull_spots.h"

#include <stdint.h>

#include "clean.h"
#include "main/acre_record.h"
#include "main/acre_tile.h"
#include "main/main_random.h"
#include "main/map_code.h"
#include "main/map_item.h"

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The inner acres, 1-4 each way, and the 16 x 16 tiles of an acre. */
#define GULL_SPOTS_ACRE_FIRST 1
#define GULL_SPOTS_ACRE_END 5
#define GULL_SPOTS_ACRES 16
#define GULL_SPOTS_SIDE 16

/* The item it places, what an empty tile holds, and how many it places at most. */
#define GULL_SPOTS_ITEM 0x1568
#define GULL_SPOTS_EMPTY 0xfff1
#define GULL_SPOTS_MAX 5

/* The buildings no tile to +z may hold. */
#define GULL_SPOTS_BUILDING_FIRST 0x5000
#define GULL_SPOTS_BUILDING_LAST 0x5021

/* The tiles to +z that must be clear (1 and 2 away). */
#define GULL_SPOTS_CLEAR_ROWS 2

/* The codes no tile to +z may hold unless they are at stage 0 (MapItem_IsStage0). */
static const u16 gull_spots_blocking[][2] = {
    {0x26, 0x2a}, {0x5d, 0x61}, {0x2f, 0x56}, {0x57, 0x5b}, {0x66, 0x68},
    {0x69, 0x69}, {0x6a, 0x6c}, {0x6d, 0x6d}, {0xc8, 0xcf},
};

static int gull_spots_is_blocking(u16 code)
{
    for (size_t i = 0; i < sizeof(gull_spots_blocking) / sizeof(gull_spots_blocking[0]); i++) {
        if (code >= gull_spots_blocking[i][0] && code <= gull_spots_blocking[i][1]) {
            return 1;
        }
    }
    return 0;
}

/* The record of acre (x, z) of the map, NULL outside it or without records. */
static AcreRecord *gull_spots_acre(AcreMap *map, int x, int z)
{
    if ((unsigned int) x < (unsigned int) map->acres_wide && (unsigned int) z < (unsigned int) map->acres_high &&
        map->acres != NULL) {
        return (AcreRecord *) (void *) (map->acres + ((unsigned int) z * (unsigned int) map->acres_wide + (unsigned int) x) *
                                                         ACRE_MAP_ACRE_SIZE);
    }
    return NULL;
}

/* Whether tile `tile` (x, z) of acre `acre` (x, z) takes the item: it is empty, its unit byte
 * 0x04 says yes and it fits (GullSpots_TileFits). Asked in this order, each only when the one
 * before holds. */
static int gull_spots_takes(AcreMap *map, int *acre, int *tile, const u16 *code)
{
    return *code == GULL_SPOTS_EMPTY && AcreTile_UnitByte04InAcre(map, acre[0], acre[1], tile[0], tile[1]) != 0 &&
           GullSpots_TileFits(acre, tile, map) != 0;
}

/* func_ov072_02279098 (after line 0xb of its talk): the fitting tiles of each inner acre
 * counted (counts[] in acre order), and one of item 0x1568 placed for each fitting tile, at most
 * five, while an acre with a fitting tile is left.
 * QUIRK: an acre's count is a byte: an acre of 256 fitting tiles counts 0. */
void GullSpots_PlaceItems(void)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    u8 counts[GULL_SPOTS_ACRES];
    u8 *count;
    int total = 0;
    int acres = 0;
    int acre[2] = {0, 0};
    int tile[2] = {0, 0};

    if (map == NULL) {
        return;
    }
    count = counts;
    MI_CpuFill8(count, 0, sizeof(counts));
    for (acre[1] = GULL_SPOTS_ACRE_FIRST; acre[1] < GULL_SPOTS_ACRE_END; acre[1]++) {
        for (acre[0] = GULL_SPOTS_ACRE_FIRST; acre[0] < GULL_SPOTS_ACRE_END; acre[0]++, count++) {
            AcreRecord *record = gull_spots_acre(map, acre[0], acre[1]);
            const u16 *code;
            if (record == NULL) {
                continue;
            }
            code = AcreRecord_Tile(record, 0, 0, 0);
            if (code == NULL) {
                continue;
            }
            for (tile[1] = 0; tile[1] < GULL_SPOTS_SIDE; tile[1]++) {
                for (tile[0] = 0; tile[0] < GULL_SPOTS_SIDE; tile[0]++, code++) {
                    if (gull_spots_takes(map, acre, tile, code)) {
                        (*count)++;
                    }
                }
            }
            if (*count != 0) {
                total += *count;
                acres++;
            }
        }
    }
    if (total >= GULL_SPOTS_MAX) {
        total = GULL_SPOTS_MAX;
    }
    for (int i = 0; i < total; i++) {
        GullSpots_PlaceOne(counts, &acres, map);
        if (acres <= 0) {
            return;
        }
    }
}
CLEAN_AS(func_ov072_02279098, GullSpots_PlaceItems)

/* func_ov072_022791b0: one of item 0x1568 placed on layer 0 of a random fitting tile of a
 * random inner acre with a fitting tile (`counts` the fitting tiles of each, `acres` how many
 * have one); that acre's count one less, and `acres` one less when it reaches 0. Whether one
 * was placed. Each pick is drawn below the count it picks from; the tiles are looked at again
 * as GullSpots_PlaceItems did. */
int GullSpots_PlaceOne(u8 *counts, int *acres, AcreMap *map)
{
    int skip_acres = (int) MainRandom_Below(*acres);
    u8 *count = counts;
    int acre[2] = {0, 0};
    int tile[2] = {0, 0};

    for (acre[1] = GULL_SPOTS_ACRE_FIRST; acre[1] < GULL_SPOTS_ACRE_END; acre[1]++) {
        for (acre[0] = GULL_SPOTS_ACRE_FIRST; acre[0] < GULL_SPOTS_ACRE_END; acre[0]++, count++) {
            if (*count == 0) {
                continue;
            }
            if (skip_acres == 0) {
                AcreRecord *record = gull_spots_acre(map, acre[0], acre[1]);
                const u16 *code = record != NULL ? AcreRecord_Tile(record, 0, 0, 0) : NULL;
                if (code != NULL) {
                    int skip_tiles = (int) MainRandom_Below(*count);
                    for (tile[1] = 0; tile[1] < GULL_SPOTS_SIDE; tile[1]++) {
                        for (tile[0] = 0; tile[0] < GULL_SPOTS_SIDE; tile[0]++, code++) {
                            if (!gull_spots_takes(map, acre, tile, code)) {
                                continue;
                            }
                            if (skip_tiles == 0) {
                                u16 item = GULL_SPOTS_ITEM;
                                AcreRecord_SetTile(record, &item, tile[0], tile[1], 0);
                                (*count)--;
                                if (*count == 0) {
                                    (*acres)--;
                                }
                                return 1;
                            }
                            skip_tiles--;
                        }
                    }
                }
            }
            skip_acres--;
        }
    }
    return 0;
}
CLEAN_AS(func_ov072_022791b0, GullSpots_PlaceOne)

/* func_ov072_022792e4: whether the two tiles to +z of tile `tile` of acre `acre` (each found
 * in the whole map, layer 0) are there and neither holds a building 0x5000-0x5021, a special
 * code (MapCode_IsSpecial), or, unless it is at stage 0, one of the blocking codes. */
int GullSpots_TileFits(int *acre, int *tile, AcreMap *map)
{
    int x = 0;
    int z = 0;

    for (int row = 1; row <= GULL_SPOTS_CLEAR_ROWS; row++) {
        const u16 *code;
        int acre_x;
        int acre_z;
        AcreTile_TileOfAcre(&x, &z, acre[0], acre[1], tile[0], tile[1] + row);
        acre_x = x >> 4;
        acre_z = z >> 4;
        code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x & (GULL_SPOTS_SIDE - 1), z & (GULL_SPOTS_SIDE - 1), 0);
        if (code == NULL) {
            return 0;
        }
        if (*code >= GULL_SPOTS_BUILDING_FIRST && *code <= GULL_SPOTS_BUILDING_LAST) {
            return 0;
        }
        if (MapCode_IsSpecial(code) != 0) {
            return 0;
        }
        if (MapItem_IsStage0(code) != 0) {
            continue;
        }
        if (gull_spots_is_blocking(*code)) {
            return 0;
        }
    }
    return 1;
}
CLEAN_AS(func_ov072_022792e4, GullSpots_TileFits)
