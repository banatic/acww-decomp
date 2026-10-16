/* Putting an item on a free tile of one of the town's acres, as the day's changes do
 * (town_spawn.h, town_beach.h): the acre's free tiles (code 0xfff1) that a test accepts are
 * listed, one is drawn at random and gets the item, marked or not. While linked the item goes
 * to the session's record of map items (LinkedMapItems_Set) instead of the map.
 *
 * The tests (TownPlaceTest) look at what the map's slot says of the tile's unit
 * (AcreTile_UnitWord06, AcreTile_UnitByte08, AcreTile_UnitByte09, AcreTile_UnitHasByte17) and
 * some at the two tiles below it (z + 1 and z + 2), which must hold codes and none that
 * func_0204a034 picks out. */
#ifndef CLEAN_MAIN_TOWN_PLACE_H
#define CLEAN_MAIN_TOWN_PLACE_H

#include "acre_map.h"
#include "town_day.h"
#include "types.h"

#define TOWN_PLACE_ACRE_TILES 256

/* A tile of the map. */
typedef struct TownPlaceTile {
    int x;
    int z;
} TownPlaceTile;

/* Whether tile (x, z) of the map may get the item. The game's own tests are handed as
 * func_02048e34, func_02048e4c, func_02048e54, func_02048ec8, func_02048ee4, func_02048f54 and
 * func_02048f6c. */
typedef int (*TownPlaceTest)(AcreMap *map, int x, int z);

int TownPlace_PutInAcre(TownDay *town, AcreMap *map, int acre_x, int acre_z, u16 item, TownPlaceTest test, int marked);
int TownPlace_PutOneOf(TownDay *town, AcreMap *map, int count, const TownPlaceTile *tiles, u16 item, int marked);
int TownPlace_ListFree(TownDay *town, TownPlaceTile *tiles, AcreMap *map, int acre_x, int acre_z, TownPlaceTest test);
int TownPlace_TestByte17(AcreMap *map, int x, int z);
int TownPlace_TestByte17Raw(AcreMap *map, int x, int z);
int TownPlace_TestByte09Low(AcreMap *map, int x, int z);
int TownPlace_TestWord06Low(AcreMap *map, int x, int z);
int TownPlace_TestWord06Is1Clear(AcreMap *map, int x, int z);
int TownPlace_TestWord06Is1(AcreMap *map, int x, int z);
int TownPlace_TestByte08Clear(AcreMap *map, int x, int z);

/* The game's tests, to hand to the game. */
extern int func_02048e34(AcreMap *map, int x, int z);
extern int func_02048e4c(AcreMap *map, int x, int z);
extern int func_02048e54(AcreMap *map, int x, int z);
extern int func_02048ec8(AcreMap *map, int x, int z);
extern int func_02048ee4(AcreMap *map, int x, int z);
extern int func_02048f54(AcreMap *map, int x, int z);
extern int func_02048f6c(AcreMap *map, int x, int z);

#endif
