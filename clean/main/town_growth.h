/* How the codes of the town's growth lines (map_item.h) change as the days pass (TownDay_Pass,
 * town_day.h), and the codes the lines' last stages turn into.
 *
 * Each day (up to five): every code of the growth lines moves on a stage (func_0204a150);
 * before that func_020496f8, func_02049638 and func_020493d4 run on the whole map, and in each
 * quarter (8 x 8 tiles) of each inner acre that holds 7 or more of the lines' codes, as many of
 * its stage-0 codes as are above 6 (at most all of them), drawn at random, go back
 * (func_0204a198).
 *
 * After the last stage of lines 0x26 (0x2a) and 0x5d (0x61) come codes 0x66-0x68 and 0x6a-0x6c:
 * TownGrowth_ChangeLastStage turns one of an acre's 0x2a into 0x66 + n or one of its 0x61 into
 * 0x6a + n. The day makes n = 1 in a random acre of each column without one, n = 0 in random
 * acres while fewer than two acres hold 0x66 or 0x6a, and n = 2 in each acre without one.
 *
 * Over up to 60 days, each inner acre has one chance in five a day of a family A code (0x00-
 * 0x19) drawn at random being handed to func_02049944 with func_02049bc4 (its neighbours). */
#ifndef CLEAN_MAIN_TOWN_GROWTH_H
#define CLEAN_MAIN_TOWN_GROWTH_H

#include "acre_map.h"
#include "town_acre_count.h"
#include "town_day.h"
#include "types.h"

/* A size or a tile in tiles. */
typedef struct TownGrowthTiles {
    int x;
    int z;
} TownGrowthTiles;

#define TOWN_GROWTH_QUARTER_TILES 64
#define TOWN_GROWTH_QUARTERS 4

/* The stage-0 codes of a quarter of an acre (0x288 bytes); quarter x_half * 2 + z_half. */
typedef struct TownGrowthQuarter {
    int lines;                                        /* 0x000: the growth lines' codes in it */
    int count;                                        /* 0x004: the tiles listed */
    TownGrowthTiles tiles[TOWN_GROWTH_QUARTER_TILES]; /* 0x008: -1, -1 once gone back */
    u16 codes[TOWN_GROWTH_QUARTER_TILES];             /* 0x208 */
} TownGrowthQuarter;

void TownGrowth_SpreadFamilyA(TownDay *town, AcreMap *map, int wide, int high);
void TownGrowth_ChangeLastStages(TownDay *town, AcreMap *map, int wide, int high);
void TownGrowth_ChangeLastStagesTo68(TownDay *town, AcreMap *map, int wide, int high);
void TownGrowth_ChangeLastStagesTo66(TownDay *town, AcreMap *map, int wide, int high);
void TownGrowth_ChangeLastStagesTo67(TownDay *town, AcreMap *map, int wide, int high);
int TownGrowth_ChangeLastStage(TownDay *town, AcreMap *map, int acre_x, int acre_z, int stage);
void TownGrowth_Day(TownDay *town, AcreMap *map, int wide, int high);
void TownGrowth_Advance(TownDay *town, AcreMap *map, const TownGrowthTiles *size);
void TownGrowth_Thin(TownDay *town, AcreMap *map, int wide, int high);
void TownGrowth_ThinQuarters(TownGrowthQuarter *quarters);
void TownGrowth_ListInQuarter(TownGrowthQuarter *quarters, u16 code, int acre_x, int acre_z, int x, int z);
void TownGrowth_InitQuarters(TownGrowthQuarter *quarters, const TownAcreCount *acre);
void TownGrowth_ThinQuarter(TownGrowthQuarter *quarter);
void TownGrowth_AddToQuarter(TownGrowthQuarter *quarter, u16 code, int x, int z);
void TownGrowth_InitQuarter(TownGrowthQuarter *quarter, const TownAcreCount *acre, int x_half, int z_half);

#endif
