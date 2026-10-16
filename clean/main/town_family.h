/* What the town's day does to the families' codes (map_item.h), and how two family A codes
 * side by side make a third.
 *
 * Each code of the families has a line (TownFamily_Line: 0-3, the same in each family; 4 for
 * 0x1a, 0x88 and 0xa4, 5 for 0x1d, 6 for 0x1e, 7 for the rest) and a stage in it
 * (TownFamily_Stage: 1-6 or 1-8, 0x1c is stage 9 of family A's fourth line and 0xa5 stage 7 of
 * family C's).
 *
 * The first day passed (TownFamily_FirstDay) takes family B's codes (and 0x88, 0x89) off, moves
 * family A's (and 0x1a) to family B (code + 0x6e) by the chance data_020cb4e8 gives each, 0x1d
 * to 0x1e three times in ten, and family C's back to family A (0xa5 to 0x1c). Each further
 * day (TownFamily_Day) does the same with the chances of data_020cb554, except that family C
 * stays, and that family B's codes and 0x1e (three times in ten) only go every seventh
 * day.
 *
 * A family A code drawn by the day (TownGrowth_SpreadFamilyA, town_growth.h) with a neighbour
 * of the same line (TownFamily_Cross) makes a code drawn from data_020db7c4 by their stages,
 * put on a free tile around the one or else the other (TownFamily_PutAround). */
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

/* A list of entries for a pair of stages. */
typedef struct TownFamilyCrosses {
    int count;
    const TownFamilyCross *entries; /* NULL for none */
} TownFamilyCrosses;

#define TOWN_FAMILY_LINES 4
#define TOWN_FAMILY_LINE_OTHER 7
#define TOWN_FAMILY_STAGES 10

void TownFamily_Day(TownDay *town, AcreMap *map, u32 day);
void TownFamily_FirstDay(TownDay *town, AcreMap *map);
int TownFamily_Cross(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);
int TownFamily_PutAround(AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile, int code);
int TownFamily_PutOnFree(AcreMap *map, const TownGrowthTiles *tile, const TownGrowthTiles *from, const TownGrowthTiles *size,
                         u16 code);
int TownFamily_DrawCross(const u16 *code, const u16 *mate);
int TownFamily_Stage(const u16 *code);
int TownFamily_Line(const u16 *code);

#endif
