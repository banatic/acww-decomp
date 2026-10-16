/* What the town's day puts on and takes off its tiles (town_spawn.h). */
#include "town_spawn.h"

#include "acre_tile.h"
#include "clean.h"
#include "event_calendar.h"
#include "sky.h"
#include "tile_changes.h"
#include "tile_requests.h"
#include "villager_home.h"
#include "villager_mode_record.h"
#include "villager_move.h"
#include "villager_object.h"
#include "villager_plot_tile.h"
#include "villager_roster.h"
#include "villager_status.h"
#include "villager_town.h"

extern TownDay data_021c779c;
extern VillagerTown data_021e5a2c;
/* The first code of each money rock kind: 0xe8, 0xed, 0xf2, 0xf7 (five codes each). */
extern const u16 data_020ca59c[4];
/* The 17 tiles around a villager's house a family A code may go on: x + 8 in the high nibble,
 * z + 8 in the low one. */
extern const u8 data_020cab28[17];
/* The family A codes put around the houses and by TownSpawn_PutFamilyA: the first three of
 * each line (0x00-0x02, 0x06-0x08, 0x0c-0x0e, 0x12-0x14). */
extern const u16 data_020cabc4[12];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern u32 func_020644cc(int range); /* a random number below `range` */
/* Item `code` put on tile (x, z) of acre (acre_x, acre_z), marked or not. */
extern void func_0204a200(TownDay *town, AcreMap *map, int acre_x, int acre_z, int x, int z, u16 code, int marked);
/* Item `code` put on tile (x, z) of the map, marked or not. */
extern void func_0204a25c(AcreMap *map, int x, int z, u16 code, int marked);
/* An item drawn among `count` from `first`. */
extern void func_02063414(u16 *item, int first, int count, int c, int d, u8 *record, int f, int g, int h, int i);

#define TOWN_SPAWN_RANGE_PERCENT 100
#define TOWN_SPAWN_ITEM_1369 0x1369
#define TOWN_SPAWN_ITEM_136A 0x136a
#define TOWN_SPAWN_WET_ITEMS 3
#define TOWN_SPAWN_WET_FIRST 0x45dc
#define TOWN_SPAWN_WET_COUNT 0x7f
#define TOWN_SPAWN_BEACH_ROW 4
#define TOWN_SPAWN_ITEM_1548 0x1548
#define TOWN_SPAWN_ROCK 0xe3 /* the rocks 0xe3-0xe7 */
#define TOWN_SPAWN_ROCK_CODES 5
#define TOWN_SPAWN_MONEY_ROCK_KINDS 4
#define TOWN_SPAWN_MARKED_1549 3 /* marked items 0x1549 the town keeps */
#define TOWN_SPAWN_ITEM_1549 0x1549
#define TOWN_SPAWN_ITEM_1566 0x1566
#define TOWN_SPAWN_CODE_SPOT 0x1b
#define TOWN_SPAWN_CODE_89 0x89
#define TOWN_SPAWN_STATE_1A 4 /* the summary's state that may bring code 0x1a */
#define TOWN_SPAWN_CODE_1A 0x1a
#define TOWN_SPAWN_CODE_1D 0x1d
#define TOWN_SPAWN_CODE_1F 0x1f
#define TOWN_SPAWN_CODE_20 0x20
#define TOWN_SPAWN_CODE_21 0x21 /* codes 0x21-0x24 */
#define TOWN_SPAWN_FAMILY_A_CODES 12
#define TOWN_SPAWN_EVENT_0E 14
#define TOWN_SPAWN_HOUSE_DAYS 7
#define TOWN_SPAWN_VILLAGERS 8
#define TOWN_SPAWN_MODE_5 5
#define TOWN_SPAWN_RING 17

/* func_02047e54: each marked item 0x1369 on the inner acres becomes a marked 0x136a. */
void TownSpawn_AdvanceMarked1369(TownDay *town, AcreMap *map, int wide, int high)
{
    for (int acre_z = 1; acre_z < high + 1; acre_z++) {
        for (int acre_x = 1; acre_x < wide + 1; acre_x++) {
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    const u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x, z, 0);
                    if (code == NULL || *code != TOWN_SPAWN_ITEM_1369) {
                        continue;
                    }
                    if (AcreTile_IsMarkedInAcre(map, (u32) acre_x, (u32) acre_z, (u32) x, (u32) z) != 0) {
                        func_0204a200(town, map, acre_x, acre_z, x, z, TOWN_SPAWN_ITEM_136A, 1);
                    }
                }
            }
        }
    }
}
CLEAN_AS(func_02047e54, TownSpawn_AdvanceMarked1369)

/* func_02047ee8: after a wet day, unless rain or snow falls now (weather 3 or 4), three items
 * drawn from 0x45dc on, each marked on a free tile of an acre drawn after the last.
 *
 * QUIRK: the first acre is drawn below wide - 1 and high - 1, the later steps below them too,
 * then taken modulo wide and high. */
void TownSpawn_AfterWetDay(TownDay *town, AcreMap *map, int wide, int high, u8 wet)
{
    if (wet == 0) {
        return;
    }
    int weather = Sky_WeatherNow();
    if (weather != 0 && weather != 1 && weather != 2) {
        return;
    }
    int acre_x = (int) func_020644cc(wide - 1);
    int acre_z = (int) func_020644cc(high - 1);
    for (int i = 0; i < TOWN_SPAWN_WET_ITEMS; i++) {
        u16 item;
        func_02063414(&item, TOWN_SPAWN_WET_FIRST, TOWN_SPAWN_WET_COUNT, 0, 0, NULL, 1, 10, 0, 1);
        acre_x = (acre_x + 1 + (int) func_020644cc(wide - 1)) % wide;
        acre_z = (acre_z + 1 + (int) func_020644cc(high - 1)) % high;
        TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, item, func_02048e54, 1);
    }
}
CLEAN_AS(func_02047ee8, TownSpawn_AfterWetDay)

/* func_02047fac: unless the town has an item 0x1548, one chance in ten of one on a beach acre
 * drawn at random. */
void TownSpawn_Put1548OnBeach(TownDay *town, AcreMap *map, int wide)
{
    if (TownAcreCount_Totals(&data_021c779c)->flags & TOWN_TOTALS_HAS_1548) {
        return;
    }
    if (func_020644cc(TOWN_SPAWN_RANGE_PERCENT) >= 10) {
        return;
    }
    int acre_x = (int) func_020644cc(wide) + 1;
    TownPlace_PutInAcre(town, map, acre_x, TOWN_SPAWN_BEACH_ROW, TOWN_SPAWN_ITEM_1548, func_02048e4c, 0);
}
CLEAN_AS(func_02047fac, TownSpawn_Put1548OnBeach)

/* func_02048000: every tile of the map (borders included) moved on by a day, unmarked: codes
 * 0xd4-0xda become 0xe2; 0xdb-0xe1 become 0xe2 after more than a day, else go back to
 * 0xd5-0xda (0xe1 to 0xda); 0xe2 and items 0x154a-0x1553 are taken off. */
void TownSpawn_AdvanceCodesD4(TownDay *town, AcreMap *map, int days)
{
    (void) town;
    int tiles_wide = map->acres_wide * 16;
    int tiles_high = map->acres_high * 16;
    for (int z = 0; z < tiles_high; z++) {
        for (int x = 0; x < tiles_wide; x++) {
            const u16 *at = TownAcreCount_CodeAt(map, x, z);
            if (at == NULL) {
                continue;
            }
            u16 code = *at;
            if (code >= 0xd4 && code <= 0xda) {
                func_0204a25c(map, x, z, 0xe2, 0);
            } else if (code >= 0xdb && code <= 0xe1) {
                if (days > 1) {
                    func_0204a25c(map, x, z, 0xe2, 0);
                } else if (code != 0xe1) {
                    func_0204a25c(map, x, z, (u16) (code - 6), 0);
                } else {
                    func_0204a25c(map, x, z, (u16) (code - 7), 0);
                }
            } else if (code == 0xe2) {
                func_0204a25c(map, x, z, ACRE_MAP_ITEM_NONE, 0);
            } else if (code >= 0x154a && code <= 0x1553) {
                func_0204a25c(map, x, z, ACRE_MAP_ITEM_NONE, 0);
            }
        }
    }
}
CLEAN_AS(func_02048000, TownSpawn_AdvanceCodesD4)

/* func_0204811c: with the town's map, the tile under `position` emptied when it holds code 0xfc
 * or 0xfd and no change is under way there. */
void TownSpawn_ClearTileAt(TownDay *town, const Position *position)
{
    (void) town;
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return;
    }
    int x = 0;
    int z = 0;
    Position_Tile(&x, &z, position);
    const u16 *code = TownAcreCount_CodeAt(map, x, z);
    if (code == NULL) {
        return;
    }
    if (*code < 0xfc || *code > 0xfd) {
        return;
    }
    TileChangesTile tile = {x, z};
    if (TileChanges_IndexAt(&tile, 0) >= 0) {
        return;
    }
    func_0204a25c(map, x, z, ACRE_MAP_ITEM_NONE, 0);
}
CLEAN_AS(func_0204811c, TownSpawn_ClearTileAt)

/* func_020481a0: with the town's map, codes 0xfc and 0xfd taken off the inner acres. */
void TownSpawn_ClearCodesFc(TownDay *town)
{
    AcreMap *map = (AcreMap *) (uintptr_t) AcreMap_Town();
    if (map == NULL) {
        return;
    }
    int last_x = map->acres_wide - 2;
    int last_z = map->acres_high - 2;
    for (int acre_z = 1; acre_z <= last_z; acre_z++) {
        for (int acre_x = 1; acre_x <= last_x; acre_x++) {
            for (int z = 0; z < 16; z++) {
                for (int x = 0; x < 16; x++) {
                    const u16 *code = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x, z, 0);
                    if (code != NULL && *code >= 0xfc && *code <= 0xfd) {
                        func_0204a200(town, map, acre_x, acre_z, x, z, ACRE_MAP_ITEM_NONE, 0);
                    }
                }
            }
        }
    }
}
CLEAN_AS(func_020481a0, TownSpawn_ClearCodesFc)

/* func_02048238: for each money rock kind the town has none of, one rock made a money rock of
 * that kind while rocks are left; then the day's money rock set up.
 *
 * QUIRK: when the rocks run out before the four kinds are looked at, the day's money rock is
 * not set up. */
void TownSpawn_MakeMoneyRocks(TownDay *town, AcreMap *map, int wide, int high)
{
    const TownAcreTotals *totals = TownAcreCount_Totals(&data_021c779c);
    int rocks = totals->rocks;
    for (int kind = 0; kind < TOWN_SPAWN_MONEY_ROCK_KINDS; kind++) {
        if (rocks <= 0) {
            return;
        }
        if ((totals->flags & TOWN_TOTALS_MONEY_ROCKS & (1 << kind)) == 0) {
            if (TownSpawn_MakeMoneyRock(town, map, wide, high, kind, rocks) != 0) {
                rocks--;
            }
        }
    }
    TileRequests_RockInit(&data_021c779c.requests.rock);
}
CLEAN_AS(func_02048238, TownSpawn_MakeMoneyRocks)

/* func_02048298: a rock drawn among `rocks` by the acres' counts made a money rock of kind
 * `kind`; whether one was. Once the draw is passed, each acre with rocks is tried in turn. */
int TownSpawn_MakeMoneyRock(TownDay *town, AcreMap *map, int wide, int high, int kind, int rocks)
{
    int left = (int) func_020644cc(rocks);
    for (int acre_z = 0; acre_z < high; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            TownAcreCount *acre = TownAcreCount_Of(&data_021c779c, acre_x, acre_z);
            if (acre->rocks == 0) {
                continue;
            }
            left -= acre->rocks;
            if (left < 0 && TownSpawn_MakeMoneyRockIn(town, map, acre, kind, acre_x, acre_z) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
CLEAN_AS(func_02048298, TownSpawn_MakeMoneyRock)

/* func_0204830c: a rock of inner acre (acre_x, acre_z) drawn by the acre's count (which goes
 * down by one) made a money rock of kind `kind`, at the same place of its five codes; whether
 * one was. */
int TownSpawn_MakeMoneyRockIn(TownDay *town, AcreMap *map, TownAcreCount *acre, int kind, int acre_x, int acre_z)
{
    (void) town;
    int rocks = acre->rocks;
    int left = (int) func_020644cc(rocks);
    acre->rocks = (u16) (rocks - 1);
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            const u16 *code = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), x, z, 0);
            if (code == NULL) {
                continue;
            }
            unsigned int value = *code;
            if (value < TOWN_SPAWN_ROCK || value > TOWN_SPAWN_ROCK + TOWN_SPAWN_ROCK_CODES - 1) {
                continue;
            }
            left--;
            if (left >= 0) {
                continue;
            }
            int tile_x;
            int tile_z;
            AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x + 1, acre_z + 1, x, z);
            u16 money = (u16) (data_020ca59c[kind] + (value - TOWN_SPAWN_ROCK) % TOWN_SPAWN_ROCK_CODES);
            func_0204a25c(map, tile_x, tile_z, money, 0);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0204830c, TownSpawn_MakeMoneyRockIn)

/* func_020483c4: unless the town has a marked item 0x1566, one marked on an acre drawn at
 * random.
 *
 * QUIRK: the acre is drawn below wide - 1 and high - 1: the last column and row of inner acres
 * never get it. */
void TownSpawn_PutMarked1566(TownDay *town, AcreMap *map, int wide, int high)
{
    if (TownAcreCount_Totals(&data_021c779c)->flags & TOWN_TOTALS_HAS_MARKED_1566) {
        return;
    }
    int acre_x = (int) func_020644cc(wide - 1);
    int acre_z = (int) func_020644cc(high - 1);
    TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, TOWN_SPAWN_ITEM_1566, func_02048ee4, 1);
}
CLEAN_AS(func_020483c4, TownSpawn_PutMarked1566)

/* func_02048418: the marked items 0x1549 made up to three, each on an acre drawn after the
 * last (see TownSpawn_AfterWetDay's QUIRK). */
void TownSpawn_PutMarked1549(TownDay *town, AcreMap *map, int wide, int high)
{
    int missing = TOWN_SPAWN_MARKED_1549 - TownAcreCount_Totals(&data_021c779c)->marked_1549;
    int acre_x = (int) func_020644cc(wide - 1);
    int acre_z = (int) func_020644cc(high - 1);
    for (; missing > 0; missing--) {
        acre_x = (acre_x + 1 + (int) func_020644cc(wide - 1)) % wide;
        acre_z = (acre_z + 1 + (int) func_020644cc(high - 1)) % high;
        TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, TOWN_SPAWN_ITEM_1549, func_02048e54, 1);
    }
}
CLEAN_AS(func_02048418, TownSpawn_PutMarked1549)

/* func_02048498: the summary's spot (code 0x1b): made code 0x89 while the summary's state is
 * not 0; else put on an acre drawn at random when the town has none. */
void TownSpawn_UpdateSpot(TownDay *town, AcreMap *map, int wide, int high)
{
    const TownDayAcres *acres = &data_021c779c.acres;
    if (acres->unk_00 != 0) {
        TownSpawn_SpotTo89(town, map);
        return;
    }
    if (acres->spot_acre_x < 0 && acres->spot_acre_z < 0) {
        TownSpawn_PutSpot(town, map, wide, high);
    }
}
CLEAN_AS(func_02048498, TownSpawn_UpdateSpot)

/* func_020484c8: the summary's spot made code 0x89 (unmarked) when its acre has codes. */
void TownSpawn_SpotTo89(TownDay *town, AcreMap *map)
{
    const TownDayAcres *acres = &data_021c779c.acres;
    int acre_x = acres->spot_acre_x + 1;
    int acre_z = acres->spot_acre_z + 1;
    if (AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, acres->spot_x, acres->spot_z, 0) != NULL) {
        func_0204a200(town, map, acre_x, acre_z, acres->spot_x, acres->spot_z, TOWN_SPAWN_CODE_89, 0);
    }
}
CLEAN_AS(func_020484c8, TownSpawn_SpotTo89)

/* func_0204851c: code 0x1b put on an acre drawn at random; whether it was. */
int TownSpawn_PutSpot(TownDay *town, AcreMap *map, int wide, int high)
{
    int acre_x = (int) func_020644cc(wide);
    int acre_z = (int) func_020644cc(high);
    return TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, TOWN_SPAWN_CODE_SPOT, func_02048ee4, 0);
}
CLEAN_AS(func_0204851c, TownSpawn_PutSpot)

/* func_0204855c: in the summary's state 4, one chance in two of code 0x1a. */
void TownSpawn_Maybe1a(TownDay *town, AcreMap *map, int wide, int high)
{
    if (data_021c779c.acres.unk_00 != TOWN_SPAWN_STATE_1A) {
        return;
    }
    if (func_020644cc(TOWN_SPAWN_RANGE_PERCENT) < 50) {
        TownSpawn_Put1a(town, map, wide, high);
    }
}
CLEAN_AS(func_0204855c, TownSpawn_Maybe1a)

/* func_02048594: code 0x1a put on an acre drawn among those without one. */
void TownSpawn_Put1a(TownDay *town, AcreMap *map, int wide, int high)
{
    TownSpawnAcre acre;
    TownSpawn_PickAcreWithout1a(&acre, town, wide, high);
    if (acre.x == -1) {
        return;
    }
    TownPlace_PutInAcre(town, map, acre.x + 1, acre.z + 1, TOWN_SPAWN_CODE_1A, func_02048ee4, 0);
}
CLEAN_AS(func_02048594, TownSpawn_Put1a)

/* func_020485d4: an inner acre without code 0x1a drawn at random, row by row, or -1, -1 when
 * the summary counts none. */
void TownSpawn_PickAcreWithout1a(TownSpawnAcre *out, TownDay *town, int wide, int high)
{
    (void) town;
    int count = wide * high - TownAcreCount_Totals(&data_021c779c)->acres_1a;
    if (count > 0) {
        int left = (int) func_020644cc(count);
        for (int acre_z = 0; acre_z < high; acre_z++) {
            for (int acre_x = 0; acre_x < wide; acre_x++) {
                if (TownAcreCount_Of(&data_021c779c, acre_x, acre_z)->flags & TOWN_ACRE_HAS_1A) {
                    continue;
                }
                if (left == 0) {
                    out->x = acre_x;
                    out->z = acre_z;
                    return;
                }
                left--;
            }
        }
    }
    out->x = -1;
    out->z = -1;
}
CLEAN_AS(func_020485d4, TownSpawn_PickAcreWithout1a)

/* func_0204864c: code 0x1f (0x20 two times in a hundred) put on an acre drawn at random. */
void TownSpawn_Put1f(TownDay *town, AcreMap *map, int wide, int high)
{
    int acre_x = (int) func_020644cc(wide);
    int acre_z = (int) func_020644cc(high);
    u16 code = func_020644cc(TOWN_SPAWN_RANGE_PERCENT) < 2 ? TOWN_SPAWN_CODE_20 : TOWN_SPAWN_CODE_1F;
    TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, code, func_02048f6c, 0);
}
CLEAN_AS(func_0204864c, TownSpawn_Put1f)

/* func_02048698: code 0x1d put on an acre drawn at random. */
void TownSpawn_Put1d(TownDay *town, AcreMap *map, int wide, int high)
{
    int acre_x = (int) func_020644cc(wide);
    int acre_z = (int) func_020644cc(high);
    TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, TOWN_SPAWN_CODE_1D, func_02048f54, 0);
}
CLEAN_AS(func_02048698, TownSpawn_Put1d)

/* func_020487d8: one of data_020cabc4's family A codes put on an acre drawn at random. */
void TownSpawn_PutFamilyA(TownDay *town, AcreMap *map, int wide, int high)
{
    int acre_x = (int) func_020644cc(wide);
    int acre_z = (int) func_020644cc(high);
    int index = (int) func_020644cc(TOWN_SPAWN_FAMILY_A_CODES);
    TownPlace_PutInAcre(town, map, acre_x + 1, acre_z + 1, data_020cabc4[index], func_02048ec8, 0);
}
CLEAN_AS(func_020487d8, TownSpawn_PutFamilyA)

/* func_02048824: unless event 0xe is on at `today` (by the calendar's rules), family A codes
 * around the houses of the villagers in mode 5, for the days that passed (at most 7). */
void TownSpawn_HousesForDays(TownDay *town, AcreMap *map, const DateTime *today, int days)
{
    DateTime when;
    MI_CpuCopy8(today, &when, sizeof when);
    if (EventCalendar_State(TOWN_SPAWN_EVENT_0E, &when, 0) == EVENT_CALENDAR_ON) {
        return;
    }
    if (days > TOWN_SPAWN_HOUSE_DAYS) {
        days = TOWN_SPAWN_HOUSE_DAYS;
    }
    TownSpawn_AroundHouses(town, map, 0, days);
}
CLEAN_AS(func_02048824, TownSpawn_HousesForDays)

/* func_0204886c: family A codes around the house of each villager that counts for the calendar
 * (EventCalendar_VillagerCounts, the one moving away left out) and has a house; unless `all`,
 * only the villagers whose record is in mode 5. */
void TownSpawn_AroundHouses(TownDay *town, AcreMap *map, int all, int days)
{
    int moving = VillagerMove_VillagerIndex(&data_021e5a2c);
    for (int i = 0; i < TOWN_SPAWN_VILLAGERS; i++) {
        u8 *villager = VillagerRoster_At(&data_021e5a2c, i);
        if (EventCalendar_VillagerCounts(villager, moving) == 0) {
            continue;
        }
        if (all == 0) {
            VillagerRecord *record = (VillagerRecord *) (void *) VillagerStatus_ModeRecord(villager);
            if (VillagerModeRecord_Mode(VillagerObject_RecordMode(record)) != TOWN_SPAWN_MODE_5) {
                continue;
            }
        }
        const VillagerPlot *plot = VillagerHome_Tile(villager);
        if (VillagerPlotTile_IsSet(plot) == 0) {
            continue;
        }
        TownPlaceTile house = {plot->x, plot->z};
        TownSpawn_AroundHouse(town, map, &house, days);
    }
}
CLEAN_AS(func_0204886c, TownSpawn_AroundHouses)

/* func_020488e4: up to two family A codes for each day (data_020cabc4, drawn) put on the free
 * tiles of the ring around the house (data_020cab28) that TownPlace_TestWord06Low accepts, each
 * tile drawn among those left.
 *
 * QUIRK: with `days` 0 or less one code is put all the same. */
void TownSpawn_AroundHouse(TownDay *town, AcreMap *map, const TownPlaceTile *house, int days)
{
    TownPlaceTile free_tiles[TOWN_SPAWN_RING];
    int count = 0;
    for (int i = 0; i < TOWN_SPAWN_RING; i++) {
        u8 offset = data_020cab28[i];
        int x = house->x + ((offset >> 4) - 8);
        int z = house->z + ((offset & 0xf) - 8);
        const u16 *code = TownAcreCount_CodeAt(map, x, z);
        if (code != NULL && *code == ACRE_MAP_ITEM_NONE && TownPlace_TestWord06Low(map, x, z) != 0) {
            free_tiles[count].x = x;
            free_tiles[count].z = z;
            count++;
        }
    }
    int left = days * 2;
    while (count > 0) {
        u16 code = data_020cabc4[func_020644cc(TOWN_SPAWN_FAMILY_A_CODES)];
        int used = TownPlace_PutOneOf(town, map, count, free_tiles, code, 0);
        left--;
        if (left <= 0) {
            break;
        }
        for (int i = used; i < TOWN_SPAWN_RING - 1; i++) {
            free_tiles[i] = free_tiles[i + 1];
        }
        count--;
    }
}
CLEAN_AS(func_020488e4, TownSpawn_AroundHouse)

/* func_020489c4: codes 0x21-0x24 (drawn) put on three different acres of a 4 x 4 grid drawn
 * at random.
 *
 * QUIRK: the acres are drawn from 4 x 4 whatever the map's size. */
void TownSpawn_Put21(TownDay *town, AcreMap *map)
{
    TownSpawnAcre used[3];
    int count = 0;
    for (int i = 0; i < 3; i++) {
        TownSpawnAcre acre;
        do {
            int value = (int) func_020644cc(16);
            acre.x = value % 4;
            acre.z = value / 4;
        } while (TownSpawn_IsListed(town, &acre, used, count) != 0);
        u16 code = (u16) (func_020644cc(4) + TOWN_SPAWN_CODE_21);
        TownPlace_PutInAcre(town, map, acre.x + 1, acre.z + 1, code, func_02048ee4, 0);
        used[count] = acre;
        count++;
    }
}
CLEAN_AS(func_020489c4, TownSpawn_Put21)

/* func_02048a54: whether `acre` is among the first `count` of `list`.
 *
 * QUIRK: the count is taken as unsigned: below 0 the list is searched on past its end until a
 * match. */
int TownSpawn_IsListed(TownDay *town, const TownSpawnAcre *acre, const TownSpawnAcre *list, int count)
{
    (void) town;
    for (u32 left = (u32) count; left != 0; left--, list++) {
        if (acre->x == list->x && acre->z == list->z) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_02048a54, TownSpawn_IsListed)
