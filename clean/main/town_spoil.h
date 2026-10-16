/* The counted items 0x1531-0x153a going bad: each becomes the item of the same place in
 * 0x154a-0x1553. They go bad when the week changes or the clock goes back (town_day.c), as the
 * turnips the game sells do; the prices kept with them are turnip_prices.h's.
 *
 * TownSpoil_All looks everywhere they can be: the players' pockets, the town's map, the five
 * rooms' maps and the town's two item lists. */
#ifndef CLEAN_MAIN_TOWN_SPOIL_H
#define CLEAN_MAIN_TOWN_SPOIL_H

#include "acre_map.h"
#include "town_day.h"
#include "types.h"

#define TOWN_SPOIL_FIRST 0x1531
#define TOWN_SPOIL_LAST 0x153a
#define TOWN_SPOIL_SPOILED 0x154a
#define TOWN_SPOIL_KINDS 10
#define TOWN_SPOIL_LIST_PLACES 15
#define TOWN_SPOIL_ROOMS 5

void TownSpoil_All(TownDay *town);
void TownSpoil_ListB(void);
void TownSpoil_Rooms(int unused);
void TownSpoil_Town(int unused);
void TownSpoil_Pockets(void);
void TownSpoil_Map(int unused, AcreMap *map);

#endif
