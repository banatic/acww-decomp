/* What the town's summary counts in each inner acre and over all of them (town_acre_count.h). */
#include "town_acre_count.h"

#include "acre_tile.h"
#include "clean.h"
#include "map_item.h"
#include "town_tile_put.h"

static_assert(offsetof(TownDayAcres, acres) == 0x44, "TownDayAcres.acres");
static_assert(sizeof(TownDayAcres) == 0x44 + 16 * 0x24, "TownDayAcres");

extern TownDay data_021c779c;

#define TOWN_ACRE_START_SCORE 100
#define TOWN_ACRE_FEWEST_LINES 12
#define TOWN_ACRE_MOST_LINES 15
#define TOWN_ACRE_FREE_COUNT 2 /* codes 0x21-0x24, other items and family codes: two pass free */
#define TOWN_ACRE_1320_COST 10
#define TOWN_ACRE_SPOT_COST 50
#define TOWN_ACRE_NO_LOW_SCORE 10000

static TownAcreTotals *totals_of(TownDayAcres *acres)
{
    return (TownAcreTotals *) (void *) ((u8 *) acres + TOWN_ACRE_TOTALS_OFFSET);
}

static TownAcreWorst *worst_of(TownDayAcres *acres)
{
    return (TownAcreWorst *) (void *) ((u8 *) acres + TOWN_ACRE_WORST_OFFSET);
}

/* The acre counts of the town's object: the summary's bands, which the summaries write there
 * whatever summary they are handed. */
static int *town_bands(void)
{
    return (int *) (void *) ((u8 *) &data_021c779c.acres + TOWN_ACRE_BANDS_OFFSET);
}

/* The record of inner acre (acre_x, acre_z); for the acre -1, -1 (no acre) only its address, the
 * record 0xb4 bytes before the first, which is never read. */
static const TownAcreCount *acre_record(TownDayAcres *acres, int acre_x, int acre_z)
{
    uintptr_t first = (uintptr_t) (void *) &acres->acres[0][0];
    intptr_t offset =
        (intptr_t) acre_x * (intptr_t) sizeof(acres->acres[0]) + (intptr_t) acre_z * (intptr_t) sizeof(TownDayAcre);
    return (const TownAcreCount *) (first + (uintptr_t) offset);
}

/* What both counts start from: nothing counted, no tile of code 0x1b. */
static void clear_count(TownAcreCount *acre)
{
    for (int x = 0; x < 2; x++) {
        for (int z = 0; z < 2; z++) {
            acre->lines[x][z] = 0;
        }
    }
    acre->codes_21 = 0;
    acre->others = 0;
    acre->items_1320 = 0;
    acre->family_codes = 0;
    acre->flags = 0;
    acre->spot_x = -1;
    acre->spot_z = -1;
    acre->rocks = 0;
    acre->code_6d = 0;
    acre->beach_items = 0;
    acre->marked_1549 = 0;
}

/* A growth line's code at tile `index` (row by row) of the acre: counted in its quarter, with the
 * flags of codes 0x66-0x6c, of line 0x26 and of line 0x5d at its last stage (`grown_5d`, which
 * each count asks its own way), or as a code 0x6d. */
static void count_line_code(TownAcreCount *acre, u16 *code, int index, int day)
{
    acre->lines[(index & 15) >> 3][index >> 7]++;
    switch (*code) {
        case 0x66:
        case 0x6a:
            acre->flags |= TOWN_ACRE_HAS_66;
            break;
        case 0x67:
        case 0x6b:
            acre->flags |= TOWN_ACRE_HAS_67;
            break;
        case 0x68:
        case 0x6c:
            acre->flags |= TOWN_ACRE_HAS_68;
            break;
    }
    if ((*code >= 0x26 && *code <= 0x2a) || (*code >= 0x66 && *code <= 0x68)) {
        acre->flags |= TOWN_ACRE_HAS_LINE_26;
        return;
    }
    if (*code >= 0x5d && *code <= 0x61) {
        /* The day's count also takes stage 3 as grown. */
        if ((day && MapItem_IsStage3(code)) || MapItem_IsGrown(code)) {
            acre->flags |= TOWN_ACRE_LINE_5D_GROWN;
            return;
        }
    }
    if (*code == 0x6d) {
        acre->code_6d++;
    }
}

/* Codes 0x00-0x1d: the tile of code 0x1b, and the families' codes. */
static void count_low_code(TownAcreCount *acre, u16 code, int index)
{
    switch (code) {
        case 0x1b:
            acre->spot_x = index % 16;
            acre->spot_z = index / 16;
            acre->flags |= TOWN_ACRE_HAS_SPOT;
            break;
        case 0x1a:
            acre->flags |= TOWN_ACRE_HAS_1A;
            acre->family_codes++;
            break;
        case 0x1c:
        case 0x1d:
            acre->family_codes++;
            break;
        default:
            acre->flags |= TOWN_ACRE_HAS_FAMILY;
            acre->family_codes++;
            break;
    }
}

/* A kind 1 item lying on the tile, marked or not. */
static void count_item(TownAcreCount *acre, AcreMap *map, int acre_x, int acre_z, u16 code, int index)
{
    if (AcreTile_IsMarkedInAcre(map, (u32) acre_x, (u32) acre_z, (u32) (index % 16), (u32) (index / 16)) == 0) {
        if (code >= 0x1554 && code <= 0x155c) {
            acre->beach_items++;
        } else if (code >= 0x154a && code <= 0x1553) {
            acre->flags |= TOWN_ACRE_HAS_154A;
        } else if ((code >= 0x1518 && code <= 0x151c) || (code >= 0x1542 && code <= 0x1546)) {
            /* not counted */
        } else {
            acre->others++;
        }
    } else if (code == 0x1549) {
        acre->marked_1549++;
    } else if (code == 0x1566) {
        acre->flags |= TOWN_ACRE_HAS_MARKED_1566;
    }
}

/* Kinds 2 to 4: other items (kind 2 only unmarked). */
static void count_other(TownAcreCount *acre, AcreMap *map, int acre_x, int acre_z, int kind, int index)
{
    if (kind == 2) {
        if (AcreTile_IsMarkedInAcre(map, (u32) acre_x, (u32) acre_z, (u32) (index % 16), (u32) (index / 16)) == 0) {
            acre->others++;
        }
    } else if (kind == 3 || kind == 4) {
        acre->others++;
    }
}

/* func_0204a848: acre (acre_x, acre_z) of the map counted into its record (as the town is
 * loaded), then scored. */
void TownAcreCount_Count(TownAcreCount *acre, AcreMap *map, int acre_x, int acre_z)
{
    clear_count(acre);
    u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, 0, 0, 0);
    for (int index = 0; index < TOWN_DAY_ACRE_TILES; code++, index++) {
        int kind = (*code & 0xf000) >> 12;
        if (kind == 0) {
            if (TownAcreCount_IsLineCode(*code)) {
                count_line_code(acre, code, index, 0);
            } else if (*code >= 0x21 && *code <= 0x24) {
                acre->codes_21++;
            } else if (*code <= 0x1d) {
                count_low_code(acre, *code, index);
            } else if (TownAcreCount_IsFamilyCCode(*code) || TownAcreCount_IsFamilyBCode(*code)) {
                acre->flags |= TOWN_ACRE_HAS_FAMILY;
                acre->family_codes++;
            }
        } else if (kind == 1) {
            if (*code >= 0x1320 && *code <= 0x1322) {
                acre->items_1320++;
            } else {
                count_item(acre, map, acre_x, acre_z, *code, index);
            }
        } else {
            count_other(acre, map, acre_x, acre_z, kind, index);
        }
    }
    TownAcreCount_Score(acre);
}
CLEAN_AS(func_0204a848, TownAcreCount_Count)

/* func_0204abc8: acre (acre_x, acre_z) of the map counted into its record by the day's change,
 * then scored. Unlike TownAcreCount_Count it takes off the map codes 0x25, 0x5c, 0xc7 (the
 * lines' codes before their first stage), family B's codes, 0x89 and item 0x1568
 * (TownAcreCount_ClearTile), counts the rocks 0xe3-0xe7 and the kinds of money rock
 * (0xe8-0xfb, five codes a kind), notes item 0x1548, and takes stage 3 of line 0x5d as grown. */
void TownAcreCount_CountDay(TownAcreCount *acre, AcreMap *map, int acre_x, int acre_z)
{
    clear_count(acre);
    u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, 0, 0, 0);
    for (int index = 0; index < TOWN_DAY_ACRE_TILES; code++, index++) {
        int kind = (*code & 0xf000) >> 12;
        if (kind == 0) {
            u16 now = *code;
            if (TownAcreCount_IsLineCode(now)) {
                count_line_code(acre, code, index, 1);
            } else if (now == 0x25 || now == 0x5c || now == 0xc7 || TownAcreCount_IsFamilyBCode(now) || now == 0x89) {
                TownAcreCount_ClearTile(acre, map, acre_x, acre_z, index);
            } else if (now >= 0x21 && now <= 0x24) {
                acre->codes_21++;
            } else if (now <= 0x1d) {
                count_low_code(acre, now, index);
            } else if (TownAcreCount_IsFamilyCCode(now)) {
                acre->flags |= TOWN_ACRE_HAS_FAMILY;
                acre->family_codes++;
            } else if (now >= 0xe3 && now <= 0xe7) {
                acre->rocks++;
            } else if (now >= 0xe8 && now <= 0xfb) {
                acre->flags |= (u32) 1 << (TOWN_ACRE_MONEY_ROCKS_SHIFT + (now - 0xe8) / 5);
            }
        } else if (kind == 1) {
            u16 now = *code;
            if (now == 0x1548) {
                acre->flags |= TOWN_ACRE_HAS_1548;
            } else if (now >= 0x1320 && now <= 0x1322) {
                acre->items_1320++;
            } else if (now == 0x1568) {
                TownAcreCount_ClearTile(acre, map, acre_x, acre_z, index);
            } else {
                count_item(acre, map, acre_x, acre_z, now, index);
            }
        } else {
            count_other(acre, map, acre_x, acre_z, kind, index);
        }
    }
    TownAcreCount_Score(acre);
}
CLEAN_AS(func_0204abc8, TownAcreCount_CountDay)

/* func_0204a370: inner acre (acre_x, acre_z) of the summary counted (TownAcreCount_Count, the
 * map's acre one further right and down). */
void TownAcreCount_CountInner(TownDayAcres *acres, AcreMap *map, int acre_x, int acre_z)
{
    TownAcreCount_Count((TownAcreCount *) (void *) &acres->acres[acre_x][acre_z], map, acre_x + 1, acre_z + 1);
}
CLEAN_AS(func_0204a370, TownAcreCount_CountInner)

/* func_0204aff0: tile `index` (row by row) of acre (acre_x, acre_z) emptied, unmarked. */
void TownAcreCount_ClearTile(TownAcreCount *acre, AcreMap *map, int acre_x, int acre_z, int index)
{
    (void) acre;
    int x;
    int z;
    AcreTile_TileOfAcre(&x, &z, acre_x, acre_z, index % 16, index / 16);
    TownTilePut_At(map, (u32) x, (u32) z, ACRE_MAP_ITEM_NONE, 0);
}
CLEAN_AS(func_0204aff0, TownAcreCount_ClearTile)

/* func_0204b038: the acre's score: 100, less two for each growth line's code above 15 or below
 * 12, less one for each code 0x21-0x24 and each other item past two, less ten for each item
 * 0x1320-0x1322, and one more for each family code past two.
 *
 * QUIRK: the 50 meant to be taken off for a code 0x1b never is: the flag is read as a one-bit
 * signed field (0 or -1) and compared with 1. TownAcreCount_FindWorst does count it. */
void TownAcreCount_Score(TownAcreCount *acre)
{
    int lines = acre->lines[0][0] + acre->lines[0][1] + acre->lines[1][0] + acre->lines[1][1];
    int score = TOWN_ACRE_START_SCORE;
    if (lines > TOWN_ACRE_MOST_LINES) {
        score -= 2 * (lines - TOWN_ACRE_MOST_LINES);
    } else if (lines < TOWN_ACRE_FEWEST_LINES) {
        score -= 2 * (TOWN_ACRE_FEWEST_LINES - lines);
    }
    if (acre->codes_21 > TOWN_ACRE_FREE_COUNT) {
        score -= acre->codes_21 - TOWN_ACRE_FREE_COUNT;
    }
    if (acre->others > TOWN_ACRE_FREE_COUNT) {
        score -= acre->others - TOWN_ACRE_FREE_COUNT;
    }
    score -= TOWN_ACRE_1320_COST * acre->items_1320;
#ifdef BUGFIX
    if (acre->flags & TOWN_ACRE_HAS_SPOT) {
        score -= TOWN_ACRE_SPOT_COST;
    }
#endif
    if (acre->family_codes > TOWN_ACRE_FREE_COUNT) {
        score += acre->family_codes - TOWN_ACRE_FREE_COUNT;
    }
    acre->score = score;
}
CLEAN_AS(func_0204b038, TownAcreCount_Score)

/* func_0204b0c0: `worst` set to the acre `acre_of` and, unless that is none (x below 0), the
 * reason its record `acre` gives for the largest deduction from its score. */
void TownAcreCount_FindWorst(TownAcreWorst *worst, const TownDayTile *acre_of, const TownAcreCount *acre)
{
    worst->acre_x = acre_of->x;
    worst->acre_z = acre_of->z;
    if (worst->acre_x < 0) {
        worst->reason = -1;
        return;
    }
    int cost[TOWN_ACRE_WORST_REASONS] = {0};
    int lines = acre->lines[0][0] + acre->lines[0][1] + acre->lines[1][0] + acre->lines[1][1];
    if (lines > TOWN_ACRE_MOST_LINES) {
        cost[TOWN_ACRE_WORST_MANY_LINES] = 2 * (lines - TOWN_ACRE_MOST_LINES);
    } else if (lines < TOWN_ACRE_FEWEST_LINES) {
        cost[TOWN_ACRE_WORST_FEW_LINES] = 2 * (TOWN_ACRE_FEWEST_LINES - lines);
    }
    if (acre->codes_21 > TOWN_ACRE_FREE_COUNT) {
        cost[TOWN_ACRE_WORST_CODES_21] = acre->codes_21 - TOWN_ACRE_FREE_COUNT;
    }
    if (acre->others > TOWN_ACRE_FREE_COUNT) {
        cost[TOWN_ACRE_WORST_OTHERS] = acre->others - TOWN_ACRE_FREE_COUNT;
    }
    cost[TOWN_ACRE_WORST_1320] = acre->items_1320 * TOWN_ACRE_1320_COST;
    if (acre->flags & TOWN_ACRE_HAS_SPOT) {
        cost[TOWN_ACRE_WORST_SPOT] = TOWN_ACRE_SPOT_COST;
    }
    int most = -1;
    int reason = -1;
    for (int i = 0; i < TOWN_ACRE_WORST_REASONS; i++) {
        if (cost[i] > most) {
            most = cost[i];
            reason = i;
        }
    }
    worst->reason = reason;
}
CLEAN_AS(func_0204b0c0, TownAcreCount_FindWorst)

/* func_0204a824: the band of a score: 0 below 75, 1 below 80, 2 below 95, 3 below 101, else 4. */
int TownAcreCount_ScoreBand(const TownDayAcres *acres, int score)
{
    (void) acres;
    if (score < 75) {
        return 0;
    }
    if (score < 80) {
        return 1;
    }
    if (score < 95) {
        return 2;
    }
    if (score < 101) {
        return 3;
    }
    return 4;
}
CLEAN_AS(func_0204a824, TownAcreCount_ScoreBand)

/* func_0204a398: the town's grade from the acres in each band: 0 when all `wide` x `high` are
 * in band 0, 1 with any in bands 0 or 1, 2 with any in band 2, 3 with fewer than eight in band
 * 4, else 4. */
int TownAcreCount_Grade(const TownDayAcres *acres, const int *bands, int wide, int high)
{
    (void) acres;
    if (bands[0] == wide * high) {
        return 0;
    }
    if (bands[0] > 0 || bands[1] > 0) {
        return 1;
    }
    if (bands[2] > 0) {
        return 2;
    }
    if (bands[4] < 8) {
        return 3;
    }
    return 4;
}
CLEAN_AS(func_0204a398, TownAcreCount_Grade)

/* What both summaries start from. */
static void clear_totals(TownDayAcres *acres)
{
    TownAcreTotals *totals = totals_of(acres);
    totals->acres_1a = 0;
    totals->unk_26 = 0;
    totals->unk_25 = 0;
    totals->unk_28 = 0;
    totals->unk_2a = 0;
    totals->acres_66 = 0;
    totals->marked_1549 = 0;
    acres->spot_acre_x = -1;
    acres->spot_acre_z = -1;
    acres->spot_x = -1;
    acres->spot_z = -1;
    totals->rocks = 0;
    totals->flags = 0;
    int *bands = town_bands();
    for (int i = 0; i < TOWN_ACRE_BANDS; i++) {
        bands[i] = 0;
    }
}

/* One inner acre's record added to the totals (the rocks and the flags of the day's count only
 * by the day's summary); its score's band counted. */
static void add_acre(TownDayAcres *acres, const TownAcreCount *acre, int acre_x, int acre_z, int day)
{
    TownAcreTotals *totals = totals_of(acres);
    if (acre->flags & TOWN_ACRE_HAS_1A) {
        totals->acres_1a++;
    }
    if (acre->flags & TOWN_ACRE_HAS_FAMILY) {
        totals->unk_25++;
    }
    if (acre->flags & TOWN_ACRE_HAS_66) {
        totals->acres_66++;
    }
    if (acre->marked_1549 != 0) {
        totals->marked_1549 += acre->marked_1549;
    }
    if (day) {
        totals->rocks += (u8) acre->rocks;
        totals->flags |= (u8) ((acre->flags >> TOWN_ACRE_MONEY_ROCKS_SHIFT) & TOWN_TOTALS_MONEY_ROCKS);
        if (acre->flags & TOWN_ACRE_HAS_1548) {
            totals->flags |= TOWN_TOTALS_HAS_1548;
        }
    }
    if (acre->flags & TOWN_ACRE_HAS_MARKED_1566) {
        totals->flags |= TOWN_TOTALS_HAS_MARKED_1566;
    }
    totals->unk_2a += acre->lines[1][1] + acre->lines[0][1] + acre->lines[0][0] + acre->lines[1][0];
    totals->unk_26 += acre->family_codes;
    totals->unk_28 += acre->codes_21;
    if (acre->items_1320 > 0) {
        totals->flags |= TOWN_TOTALS_HAS_1320;
    }
    if (acre->flags & TOWN_ACRE_HAS_154A) {
        totals->flags |= TOWN_TOTALS_HAS_154A;
    }
    town_bands()[TownAcreCount_ScoreBand(acres, acre->score)]++;
    if (acre->flags & TOWN_ACRE_HAS_SPOT) {
        acres->spot_acre_x = acre_x;
        acres->spot_acre_z = acre_z;
        acres->spot_x = acre->spot_x;
        acres->spot_z = acre->spot_z;
    }
}

/* func_0204a3cc: the summary of the town's inner acres made anew as the town is loaded: each
 * acre counted (TownAcreCount_Count) column by column, the totals added up, the acre with the
 * lowest score (the first of equal ones) and its worst deduction, and the town's grade, which
 * is kept at byte 0 and answered.
 *
 * QUIRK: the bands are counted in the town's object (data_021c779c), whatever `acres` is. */
int TownAcreCount_Summarize(TownDayAcres *acres, AcreMap *map)
{
    TownDayTile lowest = {-1, -1};
    int lowest_score = TOWN_ACRE_NO_LOW_SCORE;
    clear_totals(acres);
    int wide = map->acres_wide - 2;
    int high = map->acres_high - 2;
    for (int acre_x = 0; acre_x < wide; acre_x++) {
        for (int acre_z = 0; acre_z < high; acre_z++) {
            TownAcreCount *acre = (TownAcreCount *) (void *) &acres->acres[acre_x][acre_z];
            TownAcreCount_Count(acre, map, acre_x + 1, acre_z + 1);
            int score = acre->score;
            add_acre(acres, acre, acre_x, acre_z, 0);
            if (score < lowest_score) {
                lowest.x = acre_x;
                lowest.z = acre_z;
                lowest_score = score;
            }
        }
    }
    TownAcreCount_FindWorst(worst_of(acres), &lowest, acre_record(acres, lowest.x, lowest.z));
    int grade = TownAcreCount_Grade(acres, town_bands(), wide, high);
    acres->unk_00 = grade;
    return grade;
}
CLEAN_AS(func_0204a3cc, TownAcreCount_Summarize)

/* func_0204a5d4: the summary made anew by the day's change over `wide` x `high` inner acres,
 * row by row (TownAcreCount_CountDay), also adding up the rocks, the kinds of money rock and
 * item 0x1548.
 *
 * QUIRK: the lowest score starts at 0, so the worst acre is only one whose score is below 0
 * (else none, reason -1). The bands are counted in the town's object, whatever `acres` is. */
void TownAcreCount_SummarizeDay(TownDayAcres *acres, AcreMap *map, int wide, int high)
{
    TownDayTile lowest = {-1, -1};
    int lowest_score = 0;
    clear_totals(acres);
    for (int acre_z = 0; acre_z < high; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            TownAcreCount *acre = (TownAcreCount *) (void *) &acres->acres[acre_x][acre_z];
            TownAcreCount_CountDay(acre, map, acre_x + 1, acre_z + 1);
            int score = acre->score;
            add_acre(acres, acre, acre_x, acre_z, 1);
            if (score < lowest_score) {
                lowest.x = acre_x;
                lowest.z = acre_z;
                lowest_score = score;
            }
        }
    }
    TownAcreCount_FindWorst(worst_of(acres), &lowest, acre_record(acres, lowest.x, lowest.z));
    acres->unk_00 = TownAcreCount_Grade(acres, town_bands(), wide, high);
}
CLEAN_AS(func_0204a5d4, TownAcreCount_SummarizeDay)

/* func_0204b15c: the worst acre record's destructor (nothing to do). */
void TownAcreCount_DestroyWorst(TownAcreWorst *worst)
{
    (void) worst;
}
CLEAN_AS(func_0204b15c, TownAcreCount_DestroyWorst)

/* func_0204b160: the worst acre record's constructor: the acre first set to 0, 0 (its own
 * constructor), then all of it to -1 (none). */
void TownAcreCount_InitWorst(TownAcreWorst *worst)
{
    worst->acre_x = 0;
    worst->acre_z = 0;
    worst->acre_x = -1;
    worst->acre_z = -1;
    worst->reason = -1;
}
CLEAN_AS(func_0204b160, TownAcreCount_InitWorst)

/* func_0204b170: the summary's destructor (registered for data_021c79c4): its worst acre
 * record's. */
TownDayAcres *TownAcreCount_DestroyAcres(TownDayAcres *acres)
{
    TownAcreCount_DestroyWorst(worst_of(acres));
    return acres;
}
CLEAN_AS(func_0204b170, TownAcreCount_DestroyAcres)

/* func_0204b184: the town's object's destructor (registered for data_021c779c; nothing to do). */
void TownAcreCount_DestroyTown(TownDay *town)
{
    (void) town;
}
CLEAN_AS(func_0204b184, TownAcreCount_DestroyTown)
