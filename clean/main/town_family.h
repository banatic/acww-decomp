/* What the town's day does to the flowers (the families of map_item.h: A the flowers, B the
 * wilted flowers, C the watered flowers), and how two flowers side by side make a third.
 *
 * Each flower code has a kind (TownFamily_Kind: 0-3 the tulips, pansies, cosmos and roses, the
 * same in each family; 4 for the lily of the valley 0x1a, 0x88 and 0xa4, 5 for the dandelion
 * 0x1d, 6 for the dandelion puff 0x1e, 7 for the rest) and a color in it (TownFamily_Color: 1-6 or 1-8, in the
 * order of the flower items; the gold rose 0x1c is color 9 of the roses and the watered gold
 * rose 0xa5 color 7, the black rose's).
 *
 * The first day passed (TownFamily_FirstDay) takes the wilted flowers (and 0x88, 0x89) off,
 * wilts the flowers (and 0x1a: code + 0x6e) by the chance data_020cb4e8 gives each, turns the
 * dandelion 0x1d into the puff 0x1e three times in ten, and makes the watered flowers flowers again
 * (0xa5 the gold rose 0x1c). Each further day (TownFamily_Day) does the same with the chances
 * of data_020cb554, except that the watered flowers stay, and that the wilted flowers and 0x1e
 * (three times in ten) only go every seventh day.
 *
 * A flower drawn by the day (TownGrowth_BreedFlowers, town_growth.h) with a neighbor of the
 * same kind (TownFamily_Cross) makes a code drawn from data_020db7c4 by their colors, put on a
 * free tile around the one or else the other (TownFamily_PutAround). */
#ifndef CLEAN_MAIN_TOWN_FAMILY_H
#define CLEAN_MAIN_TOWN_FAMILY_H

#include "acre_map.h"
#include "town_day.h"
#include "town_growth.h"
#include "types.h"

/* An entry of the lists TownFamily_DrawCross draws from: its chance in 100 and its code. */
typedef struct TownFamilyCross {
    int chance;
    u16 code;
} TownFamilyCross;

/* A list of entries for a pair of colors. */
typedef struct TownFamilyCrosses {
    int count;
    const TownFamilyCross *entries; /* NULL for none */
} TownFamilyCrosses;

#define TOWN_FAMILY_KINDS 4
#define TOWN_FAMILY_KIND_OTHER 7
#define TOWN_FAMILY_COLORS 10

void TownFamily_Day(TownDay *town, AcreMap *map, u32 day);
void TownFamily_FirstDay(TownDay *town, AcreMap *map);
int TownFamily_Cross(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);
int TownFamily_PutAround(AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile, int code);
int TownFamily_PutOnFree(AcreMap *map, const TownGrowthTiles *tile, const TownGrowthTiles *from, const TownGrowthTiles *size,
                         u16 code);
int TownFamily_DrawCross(const u16 *code, const u16 *mate);
int TownFamily_Color(const u16 *code);
int TownFamily_Kind(const u16 *code);

#endif
