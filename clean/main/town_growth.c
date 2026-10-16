/* How the codes of the town's growth lines change as the days pass (town_growth.h). */
#include "town_growth.h"

#include "acre_tile.h"
#include "clean.h"
#include "map_item.h"

static_assert(sizeof(TownGrowthQuarter) == 0x288, "TownGrowthQuarter");

extern TownDay data_021c779c;

extern u32 func_020644cc(int range); /* a random number below `range` */
/* Item `code` put on tile (x, z) of the map, marked or not. */
extern void func_0204a25c(AcreMap *map, int x, int z, u16 code, int marked);
/* The code at `code` (tile (x, z)) moved on a stage. */
extern void func_0204a150(AcreMap *map, u16 *code, int x, int z);
/* A stage-0 code of the growth lines put back (its quarter's count goes down). */
extern void func_0204a198(AcreMap *map, u16 code, int x, int z);
/* Each of the eight tiles around `tile` (data_020ca5d4) inside `size` handed to `visit` until
 * it answers non-zero; its last answer. */
extern int func_02049944(AcreMap *map, TownGrowthTiles *size, TownGrowthTiles *tile,
                         int (*visit)(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size));
/* What func_02049944 is handed by TownGrowth_SpreadFamilyA. */
extern int func_02049bc4(AcreMap *map, TownGrowthTiles *near, TownGrowthTiles *tile, TownGrowthTiles *size);
/* What the day does to the map before the growth lines' codes move on. */
extern void func_020496f8(TownDay *town, AcreMap *map, TownGrowthTiles *size);
extern void func_02049638(TownDay *town, AcreMap *map, TownGrowthTiles *size);
extern void func_020493d4(TownDay *town, AcreMap *map, TownGrowthTiles *size);

#define TOWN_GROWTH_FAMILY_A_LAST 0x19
#define TOWN_GROWTH_SPREAD_PERCENT 20
#define TOWN_GROWTH_LAST_26 0x2a /* the last stage of line 0x26 */
#define TOWN_GROWTH_LAST_5D 0x61 /* the last stage of line 0x5d */
#define TOWN_GROWTH_AFTER_26 0x66
#define TOWN_GROWTH_AFTER_5D 0x6a
#define TOWN_GROWTH_ACRES_66 2 /* acres with 0x66 or 0x6a the day makes up to */
#define TOWN_GROWTH_MOST_LINES 6
#define TOWN_GROWTH_ACRE_TILES 256

/* The map's size in tiles. */
static TownGrowthTiles TownGrowth_MapTiles(const AcreMap *map)
{
    TownGrowthTiles size = {map->acres_wide * 16, map->acres_high * 16};
    return size;
}

/* func_020486d8: in each inner acre, one chance in five that one of its family A codes, drawn
 * at random, is handed to func_02049944 with its neighbours (func_02049bc4). */
void TownGrowth_SpreadFamilyA(TownDay *town, AcreMap *map, int wide, int high)
{
    (void) town;
    for (int acre_z = 0; acre_z < high; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            if (func_020644cc(100) >= TOWN_GROWTH_SPREAD_PERCENT) {
                continue;
            }
            TownGrowthTiles tiles[TOWN_GROWTH_ACRE_TILES];
            int count = 0;
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    const u16 *code = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), x, z, 0);
                    if (code == NULL || *code > TOWN_GROWTH_FAMILY_A_LAST) {
                        continue;
                    }
                    AcreTile_TileOfAcre(&tiles[count].x, &tiles[count].z, acre_x + 1, acre_z + 1, x, z);
                    count++;
                }
            }
            if (count > 0) {
                int pick = (int) func_020644cc(count);
                TownGrowthTiles size = TownGrowth_MapTiles(map);
                TownGrowthTiles tile = tiles[pick];
                func_02049944(map, &size, &tile, func_02049bc4);
            }
        }
    }
}
CLEAN_AS(func_020486d8, TownGrowth_SpreadFamilyA)

/* func_02048a80: the lines' last stages changed: 0x67 / 0x6b, 0x66 / 0x6a, then 0x68 / 0x6c. */
void TownGrowth_ChangeLastStages(TownDay *town, AcreMap *map, int wide, int high)
{
    TownGrowth_ChangeLastStagesTo67(town, map, wide, high);
    TownGrowth_ChangeLastStagesTo66(town, map, wide, high);
    TownGrowth_ChangeLastStagesTo68(town, map, wide, high);
}
CLEAN_AS(func_02048a80, TownGrowth_ChangeLastStages)

/* func_02048ab0: in each inner acre without code 0x68 or 0x6c, one last stage changed to it. */
void TownGrowth_ChangeLastStagesTo68(TownDay *town, AcreMap *map, int wide, int high)
{
    for (int acre_z = 0; acre_z < high; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            if ((TownAcreCount_Of(&data_021c779c, acre_x, acre_z)->flags & TOWN_ACRE_HAS_68) == 0) {
                TownGrowth_ChangeLastStage(town, map, acre_x + 1, acre_z + 1, 2);
            }
        }
    }
}
CLEAN_AS(func_02048ab0, TownGrowth_ChangeLastStagesTo68)

/* func_02048b0c: one last stage changed to 0x66 / 0x6a in an acre drawn at random for each
 * acre fewer than two that holds one.
 *
 * BUG: with more than two such acres the count is below 0 and the loop goes round until it
 * wraps to 0, about 2^32 times (BUGFIX: none). */
void TownGrowth_ChangeLastStagesTo66(TownDay *town, AcreMap *map, int wide, int high)
{
    u32 missing = (u32) (TOWN_GROWTH_ACRES_66 - TownAcreCount_Totals(&data_021c779c)->acres_66);
#ifdef BUGFIX
    if ((int) missing < 0) {
        missing = 0;
    }
#endif
    for (; missing != 0; missing--) {
        int acre_x = (int) func_020644cc(wide);
        int acre_z = (int) func_020644cc(high);
        TownGrowth_ChangeLastStage(town, map, acre_x + 1, acre_z + 1, 0);
    }
}
CLEAN_AS(func_02048b0c, TownGrowth_ChangeLastStagesTo66)

/* func_02048b54: in each column of inner acres without code 0x67 or 0x6b, one last stage
 * changed to it in an acre of the column drawn at random. */
void TownGrowth_ChangeLastStagesTo67(TownDay *town, AcreMap *map, int wide, int high)
{
    for (int acre_x = 0; acre_x < wide; acre_x++) {
        int found = 0;
        for (int acre_z = 0; acre_z < high; acre_z++) {
            if (TownAcreCount_Of(&data_021c779c, acre_x, acre_z)->flags & TOWN_ACRE_HAS_67) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int acre_z = (int) func_020644cc(high) + 1;
            TownGrowth_ChangeLastStage(town, map, acre_x + 1, acre_z, 1);
        }
    }
}
CLEAN_AS(func_02048b54, TownGrowth_ChangeLastStagesTo67)

/* func_02048bc0: one of the codes 0x2a and 0x61 of acre (acre_x, acre_z), drawn at random,
 * changed (unmarked) to 0x66 + stage or 0x6a + stage; whether there was one. */
int TownGrowth_ChangeLastStage(TownDay *town, AcreMap *map, int acre_x, int acre_z, int stage)
{
    (void) town;
    TownGrowthTiles tiles[TOWN_GROWTH_ACRE_TILES];
    u16 after[TOWN_GROWTH_ACRE_TILES];
    int count = 0;
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            const u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x, z, 0);
            if (code == NULL) {
                continue;
            }
            int tile_x;
            int tile_z;
            AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
            if (*code == TOWN_GROWTH_LAST_26 || *code == TOWN_GROWTH_LAST_5D) {
                tiles[count].x = tile_x;
                tiles[count].z = tile_z;
                after[count] = *code == TOWN_GROWTH_LAST_26 ? TOWN_GROWTH_AFTER_26 : TOWN_GROWTH_AFTER_5D;
                count++;
            }
        }
    }
    if (count <= 0) {
        return 0;
    }
    int pick = (int) func_020644cc(count);
    func_0204a25c(map, tiles[pick].x, tiles[pick].z, (u16) (stage + after[pick]), 0);
    return 1;
}
CLEAN_AS(func_02048bc0, TownGrowth_ChangeLastStage)

/* func_02048fdc: a day of growth on the map: func_020496f8, func_02049638 and func_020493d4
 * (each with the map's size in tiles), the crowded quarters thinned, and the growth lines'
 * codes moved on. */
void TownGrowth_Day(TownDay *town, AcreMap *map, int wide, int high)
{
    TownGrowthTiles size = TownGrowth_MapTiles(map);
    TownGrowthTiles copy = size;
    func_020496f8(town, map, &copy);
    copy = size;
    func_02049638(town, map, &copy);
    copy = size;
    func_020493d4(town, map, &copy);
    TownGrowth_Thin(town, map, wide, high);
    copy = size;
    TownGrowth_Advance(town, map, &copy);
}
CLEAN_AS(func_02048fdc, TownGrowth_Day)

/* Whether a code is one of the growth lines' (map_item.h): 0x26-0x2a, 0x2f-0x5b, 0x5d-0x61,
 * 0x66-0x6d and 0xc8-0xcf. */
static int TownGrowth_IsLineCode(unsigned int code)
{
    return (code >= 0x26 && code <= 0x2a) || (code >= 0x5d && code <= 0x61) || (code >= 0x2f && code <= 0x56) ||
           (code >= 0x57 && code <= 0x5b) || (code >= 0x66 && code <= 0x68) || code == 0x69 ||
           (code >= 0x6a && code <= 0x6c) || code == 0x6d || (code >= 0xc8 && code <= 0xcf);
}

/* func_0204903c: every growth line code of the map (within `size` tiles, borders included)
 * moved on a stage (func_0204a150). */
void TownGrowth_Advance(TownDay *town, AcreMap *map, const TownGrowthTiles *size)
{
    (void) town;
    for (int z = 0; z < size->z; z++) {
        for (int x = 0; x < size->x; x++) {
            u16 *code = TownAcreCount_CodeAt(map, x, z);
            if (code != NULL && TownGrowth_IsLineCode(*code)) {
                func_0204a150(map, code, x, z);
            }
        }
    }
}
CLEAN_AS(func_0204903c, TownGrowth_Advance)

/* func_02049160: in each inner acre, row by row, the stage-0 codes (MapItem_IsStage0) of each
 * quarter listed and the crowded quarters thinned. */
void TownGrowth_Thin(TownDay *town, AcreMap *map, int wide, int high)
{
    (void) town;
    TownGrowthQuarter quarters[TOWN_GROWTH_QUARTERS];
    for (int acre_z = 0; acre_z < high; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            u16 *codes = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), 0, 0, 0);
            TownGrowth_InitQuarters(quarters, TownAcreCount_Of(&data_021c779c, acre_x, acre_z));
            if (codes != NULL) {
                for (int k = 0; k < TOWN_GROWTH_ACRE_TILES; k++) {
                    if (MapItem_IsStage0(&codes[k]) != 0) {
                        TownGrowth_ListInQuarter(quarters, codes[k], acre_x + 1, acre_z + 1, k & 15, (k >> 4) & 15);
                    }
                }
            }
            TownGrowth_ThinQuarters(quarters);
        }
    }
}
CLEAN_AS(func_02049160, TownGrowth_Thin)

/* func_02049240: each quarter thinned, the z halves outside (quarters 0, 2, 1, 3). */
void TownGrowth_ThinQuarters(TownGrowthQuarter *quarters)
{
    for (int z_half = 0; z_half < 2; z_half++) {
        for (int x_half = 0; x_half < 2; x_half++) {
            TownGrowth_ThinQuarter(&quarters[x_half * 2 + z_half]);
        }
    }
}
CLEAN_AS(func_02049240, TownGrowth_ThinQuarters)

/* func_0204927c: tile (x, z) of acre (acre_x, acre_z) and its code listed in its quarter. */
void TownGrowth_ListInQuarter(TownGrowthQuarter *quarters, u16 code, int acre_x, int acre_z, int x, int z)
{
    int tile_x;
    int tile_z;
    AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x, acre_z, x, z);
    TownGrowth_AddToQuarter(&quarters[((x >> 3) & 1) * 2 + ((z >> 3) & 1)], code, tile_x, tile_z);
}
CLEAN_AS(func_0204927c, TownGrowth_ListInQuarter)

/* func_020492c8: the four quarters started from the acre's counts, the z halves outside. */
void TownGrowth_InitQuarters(TownGrowthQuarter *quarters, const TownAcreCount *acre)
{
    for (int z_half = 0; z_half < 2; z_half++) {
        for (int x_half = 0; x_half < 2; x_half++) {
            TownGrowth_InitQuarter(&quarters[x_half * 2 + z_half], acre, x_half, z_half);
        }
    }
}
CLEAN_AS(func_020492c8, TownGrowth_InitQuarters)

/* func_0204930c: in a quarter with 7 or more of the lines' codes, as many listed codes as
 * there are above 6 (at most all listed) put back, each drawn at random among those left.
 *
 * REQUIRES: the count listed is not negative (the ROM's loop counts down to exactly 0). */
void TownGrowth_ThinQuarter(TownGrowthQuarter *quarter)
{
    if (quarter->lines <= TOWN_GROWTH_MOST_LINES) {
        return;
    }
    int remove = quarter->lines - TOWN_GROWTH_MOST_LINES;
    if (remove > quarter->count) {
        remove = quarter->count;
    }
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    int listed = quarter->count;
    for (; remove > 0; remove--) {
        int left = (int) func_020644cc(quarter->count);
        for (int i = 0; i < listed; i++) {
            TownGrowthTiles *tile = &quarter->tiles[i];
            if (tile->x < 0) {
                continue;
            }
            left--;
            if (left >= 0) {
                continue;
            }
            func_0204a198(map, quarter->codes[i], tile->x, tile->z);
            tile->x = -1;
            tile->z = -1;
            quarter->count--;
            break;
        }
    }
}
CLEAN_AS(func_0204930c, TownGrowth_ThinQuarter)

/* func_02049384: a tile and its code added to the quarter's list.
 *
 * REQUIRES: the list has room (a quarter has 64 tiles). */
void TownGrowth_AddToQuarter(TownGrowthQuarter *quarter, u16 code, int x, int z)
{
    int index = quarter->count;
    quarter->codes[index] = code;
    quarter->tiles[index].x = x;
    quarter->tiles[index].z = z;
    quarter->count = index + 1;
}
CLEAN_AS(func_02049384, TownGrowth_AddToQuarter)

/* func_020493b4: a quarter started: its count of the lines' codes from the acre's record, no
 * tile listed. */
void TownGrowth_InitQuarter(TownGrowthQuarter *quarter, const TownAcreCount *acre, int x_half, int z_half)
{
    quarter->lines = acre->lines[x_half][z_half];
    quarter->count = 0;
    for (int i = 0; i < TOWN_GROWTH_QUARTER_TILES; i++) {
        quarter->tiles[i].x = -1;
        quarter->tiles[i].z = -1;
    }
}
CLEAN_AS(func_020493b4, TownGrowth_InitQuarter)
