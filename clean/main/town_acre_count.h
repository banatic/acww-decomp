/* What the town's summary (TownDayAcres, town_day.h) counts in each inner acre and over all of
 * them, as the day's changes to the town's tiles read it (town_day.c, town_spawn.c,
 * town_growth.c).
 *
 * The acre records are counted by func_0204a848 (the town loaded) and func_0204abc8 (the day's
 * change); the totals after them by func_0204a3cc and func_0204a5d4. The score of an acre
 * (func_0204b038) starts from 100 and goes down when the growth lines' codes are fewer than 12
 * or more than 15, with codes 0x21-0x24, with other items and with items 0x1320-0x1322. */
#ifndef CLEAN_MAIN_TOWN_ACRE_COUNT_H
#define CLEAN_MAIN_TOWN_ACRE_COUNT_H

#include <assert.h>

#include "acre_tile.h"
#include "town_day.h"
#include "types.h"

/* One inner acre's record (TownDayAcre, 0x24 bytes). */
typedef struct TownAcreCount {
    int score;        /* 0x00 */
    u8 lines[2][2];   /* 0x04: the growth lines' codes in each quarter, [x / 8][z / 8] */
    u16 codes_21;     /* 0x08: codes 0x21-0x24 */
    u16 others;       /* 0x0a: other items */
    u16 items_1320;   /* 0x0c: items 0x1320-0x1322 */
    u16 family_codes; /* 0x0e: codes 0x00-0x1d and the families' codes */
    int spot_x;       /* 0x10: the tile of code 0x1b in the acre, -1 for none */
    int spot_z;       /* 0x14 */
    u16 rocks;        /* 0x18: codes 0xe3-0xe7 */
    u16 code_6d;      /* 0x1a: codes 0x6d */
    u8 beach_items;   /* 0x1c: items 0x1554-0x155c */
    u8 marked_1549;   /* 0x1d: marked items 0x1549 */
    u8 unk_1e[2];     /* 0x1e */
    u32 flags;        /* 0x20: TOWN_ACRE_* */
} TownAcreCount;

static_assert(sizeof(TownAcreCount) == sizeof(TownDayAcre), "TownAcreCount");

/* TownAcreCount.flags */
#define TOWN_ACRE_HAS_SPOT 0x0001    /* code 0x1b */
#define TOWN_ACRE_HAS_1A 0x0002      /* code 0x1a */
#define TOWN_ACRE_HAS_67 0x0008      /* code 0x67 or 0x6b */
#define TOWN_ACRE_HAS_66 0x0010      /* code 0x66 or 0x6a */
#define TOWN_ACRE_HAS_68 0x0020      /* code 0x68 or 0x6c */
#define TOWN_ACRE_HAS_LINE_26 0x0800 /* a code of 0x26-0x2a or 0x66-0x68 */

/* The totals of the summary from byte 0x24 on (inside TownDayAcres.unk_18). */
typedef struct TownAcreTotals {
    u8 acres_1a;    /* 0x24: acres with code 0x1a */
    u8 unk_25;      /* 0x25 */
    u16 unk_26;     /* 0x26 */
    u16 unk_28;     /* 0x28 */
    u16 unk_2a;     /* 0x2a */
    u8 acres_66;    /* 0x2c: acres with code 0x66 or 0x6a */
    u8 marked_1549; /* 0x2d */
    u8 rocks;       /* 0x2e */
    u8 unk_2f;      /* 0x2f */
    u8 flags;       /* 0x30: TOWN_TOTALS_* */
} TownAcreTotals;

/* TownAcreTotals.flags */
#define TOWN_TOTALS_MONEY_ROCKS 0x0f /* bit n: a code of money rock kind n (0xe8 + 5 n) */
#define TOWN_TOTALS_HAS_1548 0x10
#define TOWN_TOTALS_HAS_MARKED_1566 0x20

#define TOWN_ACRE_TOTALS_OFFSET 0x24

/* Inner acre (acre_x, acre_z) of the town's summary, from 0. */
static inline TownAcreCount *TownAcreCount_Of(TownDay *town, int acre_x, int acre_z)
{
    return (TownAcreCount *) (void *) &town->acres.acres[acre_x][acre_z];
}

static inline TownAcreTotals *TownAcreCount_Totals(TownDay *town)
{
    return (TownAcreTotals *) (void *) ((u8 *) &town->acres + TOWN_ACRE_TOTALS_OFFSET);
}

/* The code of tile (x, z) of the map (layer 0), or NULL. QUIRK: the acre is x >> 4, rounded
 * down as the ARM's arithmetic shift does. */
static inline u16 *TownAcreCount_CodeAt(AcreMap *map, int x, int z)
{
    return AcreTile_ItemInAcre(map, (u32) (x >> 4), (u32) (z >> 4), x & 15, z & 15, 0);
}

#endif
