/* The items that wash up on the town's beach, the last row of inner acres (acre row 4).
 *
 * The items 0x1554-0x155c are drawn by the weights of data_020cac9c (TownBeach_DrawItem) and
 * put on a free tile of a beach acre by func_02048cb8. When the town is loaded every beach
 * acre gets up to two (TownBeach_Fill); then once every ten minutes of the clock (the minutes
 * ending in 3), a beach acre drawn at random gets one more while it holds fewer than four,
 * unless a player stands on that acre (alone) or any player is on the beach (linked, checked
 * by the host). The bottle with a letter (bottle_mail.h) is put on the beach the same way
 * (TownBeach_PutBottle). */
#ifndef CLEAN_MAIN_TOWN_BEACH_H
#define CLEAN_MAIN_TOWN_BEACH_H

#include "acre_map.h"
#include "town_day.h"
#include "types.h"

#define TOWN_BEACH_FIRST_ITEM 0x1554
#define TOWN_BEACH_ITEM_KINDS 9
#define TOWN_BEACH_ACRE_ROW 4     /* the beach's acres in the map */
#define TOWN_BEACH_FILL 2         /* items in each beach acre when the town is loaded */
#define TOWN_BEACH_MOST 4         /* no item washes up in an acre with this many */
#define TOWN_BEACH_MINUTE_DIGIT 3 /* the last digit of the minutes an item washes up at */

int TownBeach_PutBottle(int town);
void TownBeach_Fill(TownDay *town, AcreMap *map);
void TownBeach_Update(int town);
void TownBeach_UpdateLinked(int town);
void TownBeach_UpdateAlone(int town);
void TownBeach_WashUp(int town, AcreMap *map, int acre_x);
int TownBeach_DrawItem(TownDay *town);

#endif
