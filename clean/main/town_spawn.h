/* What the town's day puts on and takes off its tiles (TownDay_Pass and TownDay_Refresh,
 * town_day.h), besides growth (town_growth.h). Most items go on a free tile of an acre drawn at
 * random, through TownPlace_PutInAcre (town_place.h) and one of its tests:
 * - the marked items: up to three 0x1549 a day, from an acre drawn after the last (the last row
 *   and column of inner acres are never drawn), and one 0x1566 when there is no marked 0x1566;
 *   marked 0x1369 become 0x136a;
 * - the rocks 0xe3-0xe7: for each money rock kind (data_020ca59c: 0xe8, 0xed, 0xf2, 0xf7)
 *   the town lacks, one rock drawn by the acres' counts of rocks becomes a money rock of that
 *   kind (keeping its place in the five codes), then the day's money rock is set up;
 * - codes 0x1b, 0x1a, 0x1d, 0x1f / 0x20 and 0x21-0x24 drawn by the summary's state and chance;
 * - around each villager's house, family A codes (data_020cabc4) on the free tiles of a ring
 *   (data_020cab28), two for each day;
 * - after a wet day without rain now, three items drawn from 0x45dc on, marked;
 * - one day in ten, item 0x1548 on the beach unless there is one;
 * - codes 0xd4-0xe1 and 0xe2 moved on, and items 0x154a-0x1553 taken off. */
#ifndef CLEAN_MAIN_TOWN_SPAWN_H
#define CLEAN_MAIN_TOWN_SPAWN_H

#include "acre_map.h"
#include "actor_table.h"
#include "town_acre_count.h"
#include "town_day.h"
#include "town_place.h"
#include "types.h"

/* An inner acre (from 0), -1 for none. */
typedef struct TownSpawnAcre {
    int x;
    int z;
} TownSpawnAcre;

void TownSpawn_AdvanceMarked1369(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_AfterWetDay(TownDay *town, AcreMap *map, int wide, int high, u8 wet);
void TownSpawn_Put1548OnBeach(TownDay *town, AcreMap *map, int wide);
void TownSpawn_AdvanceCodesD4(TownDay *town, AcreMap *map, int days);
void TownSpawn_ClearTileAt(TownDay *town, const Position *position);
void TownSpawn_ClearCodesFc(TownDay *town);
void TownSpawn_MakeMoneyRocks(TownDay *town, AcreMap *map, int wide, int high);
int TownSpawn_MakeMoneyRock(TownDay *town, AcreMap *map, int wide, int high, int kind, int rocks);
int TownSpawn_MakeMoneyRockIn(TownDay *town, AcreMap *map, TownAcreCount *acre, int kind, int acre_x, int acre_z);
void TownSpawn_PutMarked1566(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_PutMarked1549(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_UpdateSpot(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_SpotTo89(TownDay *town, AcreMap *map);
int TownSpawn_PutSpot(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_Maybe1a(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_Put1a(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_PickAcreWithout1a(TownSpawnAcre *out, TownDay *town, int wide, int high);
void TownSpawn_Put1f(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_Put1d(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_PutFamilyA(TownDay *town, AcreMap *map, int wide, int high);
void TownSpawn_HousesForDays(TownDay *town, AcreMap *map, const DateTime *today, int days);
void TownSpawn_AroundHouses(TownDay *town, AcreMap *map, int all, int days);
void TownSpawn_AroundHouse(TownDay *town, AcreMap *map, const TownPlaceTile *house, int days);
void TownSpawn_Put21(TownDay *town, AcreMap *map);
int TownSpawn_IsListed(TownDay *town, const TownSpawnAcre *acre, const TownSpawnAcre *list, int count);

#endif
