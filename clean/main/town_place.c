/* Putting an item on a free tile of one of the town's acres (town_place.h). */
#include "town_place.h"

#include "acre_tile.h"
#include "clean.h"
#include "linked_map_items.h"
#include "scene_query.h"
#include "session.h"
#include "town_acre_count.h"

extern NetSession *data_020ccf94;

extern u32 func_020644cc(int range); /* a random number below `range` */
/* A code that is not taken out of the tile but stands for something else to take there. */
extern int func_0204a034(const u16 *code);

/* func_02048cb8: the item put on a free tile of acre (acre_x, acre_z) that `test` accepts,
 * marked or not; whether there was one. */
int TownPlace_PutInAcre(TownDay *town, AcreMap *map, int acre_x, int acre_z, u16 item, TownPlaceTest test, int marked)
{
    TownPlaceTile tiles[TOWN_PLACE_ACRE_TILES];
    int count = TownPlace_ListFree(town, tiles, map, acre_x, acre_z, test);
    return TownPlace_PutOneOf(town, map, count, tiles, item, marked) >= 0;
}
CLEAN_AS(func_02048cb8, TownPlace_PutInAcre)

/* func_02048d2c: the item put on one of `count` tiles drawn at random, marked or not (while
 * linked, handed to the session's map items for the current scene); the tile's place in the
 * list, or -1 for no tile. */
int TownPlace_PutOneOf(TownDay *town, AcreMap *map, int count, const TownPlaceTile *tiles, u16 item, int marked)
{
    (void) town;
    if (count <= 0) {
        return -1;
    }
    int index = (int) func_020644cc(count);
    const TownPlaceTile *tile = &tiles[index];
    if (Session_IsLinked(data_020ccf94)) {
        int scene = SceneQuery_Current();
        LinkedMapItems_Set((u8) tile->x, (u8) tile->z, scene, item, marked);
        return index;
    }
    u16 code = item;
    AcreTile_SetItem(map, &code, tile->x, tile->z, 0);
    if (marked != 0) {
        AcreTile_Mark(map, tile->x, tile->z);
    } else {
        AcreTile_Unmark(map, tile->x, tile->z);
    }
    return index;
}
CLEAN_AS(func_02048d2c, TownPlace_PutOneOf)

/* func_02048db8: the free tiles (code 0xfff1) of acre (acre_x, acre_z) that `test` accepts,
 * written to `tiles` row by row; their number. */
int TownPlace_ListFree(TownDay *town, TownPlaceTile *tiles, AcreMap *map, int acre_x, int acre_z, TownPlaceTest test)
{
    (void) town;
    int count = 0;
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            const u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x, z, 0);
            if (code == NULL || *code != ACRE_MAP_ITEM_NONE) {
                continue;
            }
            int tile_x;
            int tile_z;
            AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
            if (test(map, tile_x, tile_z) != 0) {
                tiles[count].x = tile_x;
                tiles[count].z = tile_z;
                count++;
            }
        }
    }
    return count;
}
CLEAN_AS(func_02048db8, TownPlace_ListFree)

/* Whether the two tiles below (x, z) hold codes, none of them one func_0204a034 picks out. */
static int TownPlace_ClearBelow(AcreMap *map, int x, int z)
{
    for (int below = 1; below <= 2; below++) {
        const u16 *code = TownAcreCount_CodeAt(map, x, z + below);
        if (code == NULL || func_0204a034(code) != 0) {
            return 0;
        }
    }
    return 1;
}

/* func_02048e34: whether the tile's unit has byte 0x17 (as 1). */
int TownPlace_TestByte17(AcreMap *map, int x, int z)
{
    return AcreTile_UnitHasByte17(map, x, z) != 0;
}
CLEAN_AS(func_02048e34, TownPlace_TestByte17)

/* func_02048e4c: AcreTile_UnitHasByte17's answer as it is. */
int TownPlace_TestByte17Raw(AcreMap *map, int x, int z)
{
    return AcreTile_UnitHasByte17(map, x, z);
}
CLEAN_AS(func_02048e4c, TownPlace_TestByte17Raw)

/* func_02048e54: whether the tile's unit has byte 9 of 0 or 1 and the two tiles below are
 * clear. */
int TownPlace_TestByte09Low(AcreMap *map, int x, int z)
{
    int value = AcreTile_UnitByte09(map, x, z);
    if (value != 0 && value != 1) {
        return 0;
    }
    return TownPlace_ClearBelow(map, x, z);
}
CLEAN_AS(func_02048e54, TownPlace_TestByte09Low)

/* func_02048ec8: whether the tile's unit has word 6 of 0 or 1. */
int TownPlace_TestWord06Low(AcreMap *map, int x, int z)
{
    int value = AcreTile_UnitWord06(map, x, z);
    return value == 0 || value == 1;
}
CLEAN_AS(func_02048ec8, TownPlace_TestWord06Low)

/* func_02048ee4: whether the tile's unit has word 6 of 1 and the two tiles below are clear. */
int TownPlace_TestWord06Is1Clear(AcreMap *map, int x, int z)
{
    if (TownPlace_TestWord06Is1(map, x, z) == 0) {
        return 0;
    }
    return TownPlace_ClearBelow(map, x, z);
}
CLEAN_AS(func_02048ee4, TownPlace_TestWord06Is1Clear)

/* func_02048f54: whether the tile's unit has word 6 of 1. */
int TownPlace_TestWord06Is1(AcreMap *map, int x, int z)
{
    return AcreTile_UnitWord06(map, x, z) == 1;
}
CLEAN_AS(func_02048f54, TownPlace_TestWord06Is1)

/* func_02048f6c: whether the tile's unit has a byte 8 and the two tiles below are clear. */
int TownPlace_TestByte08Clear(AcreMap *map, int x, int z)
{
    if (AcreTile_UnitByte08(map, x, z) == 0) {
        return 0;
    }
    return TownPlace_ClearBelow(map, x, z);
}
CLEAN_AS(func_02048f6c, TownPlace_TestByte08Clear)
