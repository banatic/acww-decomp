/* What the town's day does to the growth lines' codes (map_item.h) besides moving them on: a
 * code at its first stage (stage 0) goes back to the code before the line's first
 * (TownLines_PutBack: 0x25 for line 0x26 and the others, 0x5c for line 0x5d, 0xc7 for line
 * 0xc8), counted off its acre's quarter. Before the codes move on (TownGrowth_Advance,
 * town_growth.h), on the whole map:
 * - TownLines_CheckGround: each stage-0 code goes back unless its tile's unit has word 6 of 1
 *   and none of its eight neighbours holds a grown line code, an occupied tile, a short line's
 *   code or a rock (TownLines_HasRoom); line 0x5d's only in the first 48 rows, line 0xc8's only
 *   from row 64 on;
 * - TownLines_ThinNeighbours: on three spaced patterns of tiles (one tile in four of each row),
 *   each stage-0 code makes its stage-0 neighbours go back;
 * - TownLines_ThinCrowded: each stage-0 code with eight or more line codes within three tiles
 *   goes back.
 * A neighbour is one of the eight tiles around (data_020ca5d4) inside the map
 * (TownLines_VisitAround). */
#ifndef CLEAN_MAIN_TOWN_LINES_H
#define CLEAN_MAIN_TOWN_LINES_H

#include "acre_map.h"
#include "town_day.h"
#include "town_growth.h"
#include "types.h"

#define TOWN_LINES_BEFORE_26 0x25
#define TOWN_LINES_BEFORE_5D 0x5c
#define TOWN_LINES_BEFORE_C8 0xc7

/* What TownLines_VisitAround hands each neighbour `near` of `tile` (with the map's `size`);
 * non-zero stops the visit. The game's are func_02049f74, func_02049fbc and func_02049bc4. */
typedef int (*TownLinesVisit)(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);

void TownLines_ThinCrowded(TownDay *town, AcreMap *map, const TownGrowthTiles *size);
void TownLines_ThinNeighbours(TownDay *town, AcreMap *map, const TownGrowthTiles *size);
int TownLines_PutBackAround(TownDay *town, AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile);
void TownLines_CheckGround(TownDay *town, AcreMap *map, const TownGrowthTiles *size);
void TownLines_CheckC8(TownDay *town, AcreMap *map, u16 *code, const TownGrowthTiles *size, int x, int z);
void TownLines_Check5d(TownDay *town, AcreMap *map, u16 *code, const TownGrowthTiles *size, int x, int z);
void TownLines_CheckTile(TownDay *town, AcreMap *map, u16 *code, const TownGrowthTiles *size, int x, int z);
int TownLines_HasRoom(TownDay *town, AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile);
int TownLines_VisitAround(AcreMap *map, const TownGrowthTiles *size, const TownGrowthTiles *tile, TownLinesVisit visit);
int TownLines_PutBackStage0(AcreMap *map, const TownGrowthTiles *near);
int TownLines_BlocksAt(AcreMap *map, const TownGrowthTiles *near);
int TownLines_IsGrownOrRock(const u16 *code);
int TownLines_IsGrownOrOccupied(const u16 *code);
void TownLines_Advance(AcreMap *map, const u16 *code, int x, int z);
void TownLines_PutBack(AcreMap *map, u16 code, int x, int z);

/* The game's visits, to hand to the game. */
extern int func_02049f74(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);
extern int func_02049fbc(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);
extern int func_02049bc4(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);

#endif
