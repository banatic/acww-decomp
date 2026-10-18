/* The town's object and the town's day (town_day.h). */
#include "town_day.h"

#include "acre_tile.h"
#include "block_02042200.h"
#include "board_notices.h"
#include "bottle_mail.h"
#include "clean.h"
#include "clock.h"
#include "date_time.h"
#include "day_plan.h"
#include "event_announce.h"
#include "event_buildings.h"
#include "event_calendar.h"
#include "event_schedule.h"
#include "event_winner.h"
#include "item_code.h"
#include "map_item.h"
#include "mom_letters.h"
#include "museum_record.h"
#include "nook_store.h"
#include "paired_town.h"
#include "player_record.h"
#include "player_records.h"
#include "process_020dabc0.h"
#include "room_cells.h"
#include "room_score.h"
#include "scene_query.h"
#include "session.h"
#include "sky.h"
#include "sky_weather_day.h"
#include "state_block.h"
#include "town_acre_count.h"
#include "town_beach.h"
#include "town_growth.h"
#include "town_item_lists.h"
#include "town_layout.h"
#include "town_objects.h"
#include "town_spawn.h"
#include "town_spoil.h"
#include "town_start_day.h"
#include "turnip_prices.h"
#include "villager_town.h"
#include "villager_day.h"
#include "wfc_stats.h"
#include "worker_thread.h"
#include "house_record.h"
#include "item_form.h"
#include "main_random.h"
#include "scene_map.h"
#include "state_flags.h"
#include "town_family.h"
#include "town_record.h"
#include "town_tile_put.h"

static_assert(sizeof(TileEffectsSource) == 0x18, "TileEffectsSource");
static_assert(sizeof(TownDayAcre) == 0x24, "TownDayAcre");
static_assert(offsetof(TownDayAcres, spot_acre_x) == 0x34, "TownDayAcres.spot_acre_x");
static_assert(offsetof(TownDayAcres, acres) == 0x44, "TownDayAcres.acres");
static_assert(offsetof(TownDay, effects) == 0x04, "TownDay.effects");
static_assert(offsetof(TownDay, no_drop) == 0x1c, "TownDay.no_drop");
static_assert(offsetof(TownDay, job) == 0x20, "TownDay.job");
static_assert(offsetof(TownDay, code_6d) == 0x24, "TownDay.code_6d");
static_assert(offsetof(TownDay, changes) == 0xe4, "TownDay.changes");
static_assert(offsetof(TownDay, acres) == 0x228, "TownDay.acres");
static_assert(offsetof(TownDay, requests) == 0x4ac, "TownDay.requests");
static_assert(sizeof(TownDayEvent) == 12, "TownDayEvent");

extern TownDay data_021c779c;
extern StateBlock data_021dc7a8;
extern NetSession *data_020ccf94;
extern u8 data_021c776c[2];                                     /* block_02042200.h */
extern TileRequestsAction data_021c7788[TILE_REQUESTS_ACTIONS]; /* tile_requests.h */
extern TownDayStamp data_021f39fc;                              /* the state block's record at 0x17254 */
extern TownDayStamp data_021f3a50;                              /* the day the calendar's buildings were set */
extern EventWinner data_021f3aa4;
extern MuseumRecord data_021f38f8;
extern u8 data_021ebcd4[];
extern u8 data_021ebcd3[];
extern u16 data_021f3a68[];
extern u16 data_021f3a86[];
extern u8 data_021e9aac[]; /* the town's layout (town_layout.h) */
extern NookStore data_021f395c;
extern WfcStats data_021f3278;
extern VillagerTown data_021e5a2c;
extern TurnipPrices data_021f3b0c;
/* The events whose buildings TownDay_PutEventBuildings puts up: 0x3d, 0x3f and 0x60's. */
extern const u8 data_020db764[3];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

#define TOWN_DAY_MINUTES_PER_DAY (60 * 24)
#define TOWN_DAY_LINKED_SUMMARY 5 /* TownDay_Summarize's answer without the town's map */
#define TOWN_DAY_EVENT_501E_END 0x62
#define TOWN_DAY_EVENT_FREE 0x63

static AcreMap *TownDay_Map(void)
{
    return (AcreMap *) (uintptr_t) AcreMap_Town();
}

static TownStartDay *TownDay_StartDayOf(StateBlock *block)
{
    return (TownStartDay *) block->part_173dd;
}

/* The town's last day at 6:00, the time its next day starts from. */
static void TownDay_StampTime(DateTime *when, const TownDayStamp *stamp)
{
    *when = (DateTime){0};
    when->hour = TOWN_DAY_START_HOUR;
    when->day = stamp->day;
    when->month = stamp->month;
    when->year = stamp->year;
}

static void TownDay_SetStamp(TownDayStamp *stamp, const DateTime *when)
{
    stamp->year = when->year;
    stamp->month = when->month;
    stamp->day = when->day;
}

/* func_02046600: the requests' money rock and data_021c776c's flags updated, each frame. */
void TownDay_Update(void)
{
    TileRequests_UpdateRock((u32) (uintptr_t) &data_021c779c.requests);
    Block02042200_Apply(data_021c776c);
}
CLEAN_AS(func_02046600, TownDay_Update)

/* func_02046620: the requests and the changes under way reset. */
void TownDay_Init(void)
{
    TileRequests_Reset(&data_021c779c.requests);
    TileChanges_Init(&data_021c779c.changes);
}
CLEAN_AS(func_02046620, TownDay_Init)

/* func_02046640: event `event` marked for the town (TownDay_MarkEvent). */
void TownDay_MarkEventOf(int event)
{
    TownDay_MarkEvent(&data_021c779c, event);
}
CLEAN_AS(func_02046640, TownDay_MarkEventOf)

/* func_02046650: unless linked, the tiles' marks cleared and func_020481a0. */
void TownDay_ResetMarks(void)
{
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    TileRequests_ClearMarks(&data_021c779c.requests);
    TownSpawn_ClearCodesFc(&data_021c779c);
}
CLEAN_AS(func_02046650, TownDay_ResetMarks)

/* func_02046680: the list of code 0x6d's tiles emptied. */
void TownDay_ClearCode6d(void)
{
    TownDayTile *tiles = (TownDayTile *) (uintptr_t) TownDay_Code6dTiles();
    for (int i = 0; i < TOWN_DAY_CODE_6D_TILES; i++) {
        tiles[i].x = TOWN_DAY_NO_TILE;
        tiles[i].z = TOWN_DAY_NO_TILE;
    }
}
CLEAN_AS(func_02046680, TownDay_ClearCode6d)

/* func_020466a0: the tile put in the first free place of the list; nothing when it is full. */
void TownDay_AddCode6d(u32 x, u32 z)
{
    TownDayTile *tiles = (TownDayTile *) (uintptr_t) TownDay_Code6dTiles();
    for (int i = 0; i < TOWN_DAY_CODE_6D_TILES; i++) {
        if (tiles[i].x == TOWN_DAY_NO_TILE && tiles[i].z == TOWN_DAY_NO_TILE) {
            tiles[i].x = (int) x;
            tiles[i].z = (int) z;
            return;
        }
    }
}
CLEAN_AS(func_020466a0, TownDay_AddCode6d)

/* func_020466d8: the address of the list of code 0x6d's tiles. */
int TownDay_Code6dTiles(void)
{
    return (int) (uintptr_t) data_021c779c.code_6d;
}
CLEAN_AS(func_020466d8, TownDay_Code6dTiles)

/* func_020466e0: the tile's place in the list, or -1; while linked the list is not kept and
 * the place is (x + z) mod 24. */
int TownDay_FindCode6d(int x, int z)
{
    if (Session_IsLinked(data_020ccf94)) {
        return (x + z) % TOWN_DAY_CODE_6D_TILES;
    }
    const TownDayTile *tiles = (const TownDayTile *) (uintptr_t) TownDay_Code6dTiles();
    for (int i = 0; i < TOWN_DAY_CODE_6D_TILES; i++) {
        if (tiles[i].x == x && tiles[i].z == z) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_020466e0, TownDay_FindCode6d)

/* func_02046730: the position of the summary's spot (in the town's map); whether there is
 * one. */
int TownDay_SpotPosition(Vec3 *position)
{
    const TownDayAcres *acres = &data_021c779c.acres;
    int acre_x = acres->spot_acre_x;
    int acre_z = acres->spot_acre_z;
    int x = acres->spot_x;
    int z = acres->spot_z;
    if (acre_x == TOWN_DAY_NO_TILE || acre_z == TOWN_DAY_NO_TILE || x == TOWN_DAY_NO_TILE || z == TOWN_DAY_NO_TILE) {
        return 0;
    }
    if (TownDay_Map() == NULL) {
        return 0;
    }
    AcreTile_PositionInAcre(position, (u32) (acre_x + 1), (u32) (acre_z + 1), (u32) x, (u32) z);
    return 1;
}
CLEAN_AS(func_02046730, TownDay_SpotPosition)

/* func_0204677c: the address of the town's object. */
int TownDay_Object(void)
{
    return (int) (uintptr_t) &data_021c779c;
}
CLEAN_AS(func_0204677c, TownDay_Object)

/* func_02046784: the address of byte 0x18 of the acre summary (data_021c79dc). */
int TownDay_Acres18(void)
{
    return (int) (uintptr_t) data_021c779c.acres.unk_18;
}
CLEAN_AS(func_02046784, TownDay_Acres18)

/* func_0204678c: the acre summary made anew (func_0204a3cc's answer), or 5 without the town's
 * map. */
int TownDay_Summarize(void)
{
    AcreMap *map = TownDay_Map();
    if (map == NULL) {
        return TOWN_DAY_LINKED_SUMMARY;
    }
    return TownAcreCount_Summarize(&data_021c779c.acres, map);
}
CLEAN_AS(func_0204678c, TownDay_Summarize)

/* func_020467ac: the acre summary made anew, data_021c776c's flags read from it, the marks
 * reset and other systems' actions taken in again. */
void TownDay_Enter(void)
{
    TownDay_Summarize();
    Block02042200_ReadFlags(data_021c776c);
    TownDay_ResetMarks();
    TileChanges_Activate();
}
CLEAN_AS(func_020467ac, TownDay_Enter)

/* func_020467cc: with the town's map, the acre summary updated and the object's work on the
 * acres run, then the marks reset. */
void TownDay_Refresh(void)
{
    AcreMap *map = TownDay_Map();
    if (map == NULL) {
        return;
    }
    int wide = map->acres_wide - 2;
    int high = map->acres_high - 2;
    TownAcreCount_SummarizeDay(&data_021c779c.acres, map, wide, high);
    TownSpawn_PutMarked1549(&data_021c779c, map, wide, high);
    TownSpawn_PutMarked1566(&data_021c779c, map, wide, high);
    TownGrowth_ChangeLastStages(&data_021c779c, map, wide, high);
    TownSpawn_MakeMoneyRocks(&data_021c779c, map, wide, high);
    TownDay_ResetMarks();
}
CLEAN_AS(func_020467cc, TownDay_Refresh)

/* func_02046830: the town brought up when it is loaded: the clock read again (with its check),
 * every inner acre counted and the beach filled, code 0x6d's tiles listed, the day's period
 * noted; unless linked, the counted items spoiled when the clock went back, and the day
 * started (scene 0x3f) or checked as loaded. The marks, the changes, other systems' actions and
 * the money rock are then reset. */
void TownDay_Load(void)
{
    AcreMap *map = TownDay_Map();
    Clock_Refresh(NULL);
    if (map != NULL) {
        int wide = map->acres_wide - 2;
        int high = map->acres_high - 2;
        for (int x = 0; x < wide; x++) {
            for (int z = 0; z < high; z++) {
                TownAcreCount_Count((TownAcreCount *) &data_021c779c.acres.acres[x][z], map, x + 1, z + 1);
            }
        }
        TownBeach_Fill(&data_021c779c, map);
    }
    TownDay_ListCode6d();
    TownDay_SetPeriod();
    if (!Session_IsLinked(data_020ccf94)) {
        if (TownDay_ClockWentBack()) {
            TownSpoil_All(&data_021c779c);
        }
        if (SceneQuery_Current() == 0x3f) {
            TownDay_Start(&data_021c779c, 1);
        } else {
            TownDay_Check(1);
        }
    }
    TileRequests_ClearMarks(&data_021c779c.requests);
    TileChanges_Init(&data_021c779c.changes);
    TileRequests_InitActions(data_021c7788);
    TileRequests_RockReset(&data_021c779c.requests.rock);
}
CLEAN_AS(func_02046830, TownDay_Load)

/* func_02046904: whether the clock is before the town's last day (at 6:00), or func_0206f7a4
 * says so. */
int TownDay_ClockWentBack(void)
{
    if (StateFlags_Test8() != 0) {
        return 1;
    }
    DateTime now = {0};
    DateTime last;
    DateTime_Now(&now);
    TownDay_StampTime(&last, &data_021f39fc);
    return DateTime_MinutesBetween(&now, &last) > 0;
}
CLEAN_AS(func_02046904, TownDay_ClockWentBack)

/* func_0204695c: the list of code 0x6d's tiles made anew from the second and third rows of
 * acres.
 *
 * BUG: the list is not checked for room: a 25th tile goes on past its end (into the changes
 * under way).
 * REQUIRES: every inner acre of those rows has its codes (AcreTile_ItemInAcre is not NULL). */
void TownDay_ListCode6d(void)
{
    AcreMap *map = TownDay_Map();
    TownDay_ClearCode6d();
    if (map == NULL) {
        return;
    }
    int wide = map->acres_wide - 2;
    TownDayTile *tile = (TownDayTile *) (uintptr_t) TownDay_Code6dTiles();
    for (int acre_z = 0; acre_z < 2; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            const u16 *codes = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), 0, 0, 0);
            for (int k = 0; k < TOWN_DAY_ACRE_TILES; k++) {
                if (codes[k] == TOWN_DAY_CODE_6D) {
                    AcreTile_TileOfAcre(&tile->x, &tile->z, acre_x + 1, acre_z + 1, k % 16, k / 16);
                    tile++;
                }
            }
        }
    }
}
CLEAN_AS(func_0204695c, TownDay_ListCode6d)

/* func_020469f4: what a check of the clock does (Clock_Refresh): when announcements are allowed,
 * a day or more since the town's last day (not linked) asks for announcement 0x63, and the
 * beach is looked at (TownBeach_Update). */
void TownDay_OnClock(void)
{
    if (EventAnnounce_IsAllowed() == 0) {
        return;
    }
    if (!Session_IsLinked(data_020ccf94)) {
        DateTime now = {0};
        DateTime last;
        DateTime_Now(&now);
        TownDay_StampTime(&last, &data_021f39fc);
        if (DateTime_MinutesBetween(&last, &now) / TOWN_DAY_MINUTES_PER_DAY >= 1) {
            EventAnnounce_Request(-1, 0x63, 0);
        }
    }
    TownBeach_Update((int) (uintptr_t) &data_021c779c);
}
CLEAN_AS(func_020469f4, TownDay_OnClock)

/* func_02046a74: the town's day checked against the clock. `loaded`: the town was just loaded
 * (else a check while playing, which moves the town on only in scenes 0 and 0x31).
 *
 * A day or more since the town's last day: the town's schedule updated (while playing), the
 * board's notices, the start day expired (while playing), the town moved on by the days
 * (TownDay_Move, with whether the last day was wet) and the stamp set to today. Less than a
 * day: the town started when loaded; when the clock went back before the last day the counted
 * items spoil, the record's events are moved and the house is judged again; the stamp is set
 * to today. Either way the turnip prices follow the days and the players' records are
 * updated. */
void TownDay_Check(int loaded)
{
    DateTime now = {0};
    DateTime last;
    DateTime_Now(&now);
    TownDay_StampTime(&last, &data_021f39fc);
    int minutes = DateTime_MinutesBetween(&last, &now);
    int days = minutes / 60 / 24;
    TownDay_SetPeriod();
    if (days >= 1 && !loaded && (SceneQuery_CurrentIs0() != 0 || SceneQuery_CurrentIs31() != 0)) {
        EventSchedule_UpdateTown();
    }
    BoardNotices_Update();
    if (days >= 1) {
        int wet = SkyWeatherDay_LastWet();
        if (!loaded && (SceneQuery_CurrentIs0() != 0 || SceneQuery_CurrentIs31() != 0)) {
            TownStartDay_Expire(TownDay_StartDayOf(&data_021dc7a8));
        }
        if (loaded || SceneQuery_CurrentIs0() != 0 || SceneQuery_CurrentIs31() != 0) {
            TownDay_Move(&last, &now, days, wet, loaded);
            DateTime_SubtractHours(&now, TOWN_DAY_START_HOUR);
            TownDay_SetStamp(&data_021f39fc, &now);
        }
    } else {
        if (loaded) {
            TownDay_Start(&data_021c779c, 1);
        }
        if (minutes < 0) {
            TownDayStamp today = {now.day, now.month, now.year};
            RoomScoreRoom house;
            TownSpoil_All(&data_021c779c);
            TownRecord_DrawPelicanDay((TownRecord *) (void *) data_021dc7a8.part_17254, &today);
            RoomScore_InitRoom(&house);
            RoomScore_JudgeHouse(&house);
            RoomScore_DestructRoom(&house);
        }
        DateTime_SubtractHours(&now, TOWN_DAY_START_HOUR);
        TownDay_SetStamp(&data_021f39fc, &now);
    }
    TurnipPrices_Update(&data_021f3b0c, days);
    PlayerRecord_UpdateSinceLastPlay();
}
CLEAN_AS(func_02046a74, TownDay_Check)

/* func_02046bc8: the period of the town's day (Calendar_PeriodBOf) noted. */
void TownDay_SetPeriod(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    DateTime_SubtractHours(&now, TOWN_DAY_START_HOUR);
    TownRecord_SetPeriod((u8) Calendar_PeriodBOf(&now));
}
CLEAN_AS(func_02046bc8, TownDay_SetPeriod)

/* func_02046bf4: the town moved on from one day to another: handed to the worker thread when
 * there is one, else done here. */
void TownDay_Move(const DateTime *from, const DateTime *to, int days, int wet, int loaded)
{
    if (data_021c779c.job != NULL) {
        WorkerThread_SetDays(from, to, (u32) days, (u32) wet);
    } else {
        TownDay_Pass(&data_021c779c, from, to, days, (u8) wet, loaded);
    }
}
CLEAN_AS(func_02046bf4, TownDay_Move)

static int TownDay_AtMost(int value, int most)
{
    return value > most ? most : value;
}

/* Whether the period of the day (Calendar_PeriodBOf) is one of 0, 1, 2 and 0x16. */
static int TownDay_QuietPeriod(int period)
{
    return period == 0 || period == 1 || period == 2 || period == 0x16;
}

/* func_0204714c: the town moved on by `days` days, from `from` to `to` (the days start at
 * 6:00), with the town's map:
 * - the acres: family B codes turned to family C when the last day was wet
 *   (TownDay_ChangeFamilyB), the summary updated, then up to 5 days of func_02048fdc;
 * - each of the last 365 days (at most) func_020489c4, and outside the periods 0, 1, 2 and
 *   0x16 one chance in two of func_0204864c; each of the last 30, outside them, one chance in
 *   five of func_02048698;
 * - up to 60 days of func_020486d8 and func_020487d8 (the first after func_02049ad0, each
 *   other after func_020499cc with its number);
 * - then the town's other records each by the days, in a fixed order: footprints, the
 *   calendar's buildings (TownDay_UpdateEvents), the object's acres, the event letters, the
 *   museum, the house rooms, Nook's store, the item lists, the house's score, the layout, the
 *   sky, the bottle, mom's letters, the day plan, the room cells, the paired town, the
 *   statistics record (status 1 becomes 2) and the villagers;
 * - the counted items spoil when `to` is a Sunday, a week or more passed or `to`'s weekday is
 *   before `from`'s.
 * The marks are cleared and func_020481a0 run in any case. */
void TownDay_Pass(TownDay *town, const DateTime *from, const DateTime *to, int days, u8 wet, int loaded)
{
    AcreMap *map = TownDay_Map();
    if (map != NULL) {
        int wide = map->acres_wide - 2;
        int high = map->acres_high - 2;
        SceneMap_ClearRimGrowth(map);
        if (wet != 0) {
            TownDay_ChangeFamilyB(town, map, wide, high);
        }
        TownAcreCount_SummarizeDay(&data_021c779c.acres, map, wide, high);
        TownRecord_CountSummaryDays((TownRecord *) (void *) ((u8 *) &data_021f39fc), data_021c779c.acres.unk_00, days);

        int grow_days = TownDay_AtMost(days, 5);
        for (int i = 0; i < grow_days; i++) {
            TownGrowth_Day(town, map, wide, high);
        }

        DateTime day = {0};
        MI_CpuCopy8(to, &day, sizeof day);
        int year_days = TownDay_AtMost(days, 365);
        DateTime_SubtractDays(&day, year_days);
        for (int i = 0; i < year_days; i++) {
            int quiet = TownDay_QuietPeriod(Calendar_PeriodBOf(&day));
            TownSpawn_Put21(town, map);
            if (!quiet && MainRandom_Below(100) < 50) {
                TownSpawn_Put1f(town, map, wide, high);
            }
            DateTime_AddDays(&day, 1);
        }

        DateTime month_day = {0};
        MI_CpuCopy8(to, &month_day, sizeof month_day);
        int month_days = TownDay_AtMost(days, 30);
        DateTime_SubtractDays(&month_day, month_days);
        for (int i = 0; i < month_days; i++) {
            if (!TownDay_QuietPeriod(Calendar_PeriodBOf(&month_day)) && MainRandom_Below(100) < 20) {
                TownSpawn_Put1d(town, map, wide, high);
            }
            DateTime_AddDays(&month_day, 1);
        }

        int long_days = TownDay_AtMost(days, 60);
        TownFamily_FirstDay(town, map);
        TownGrowth_SpreadFamilyA(town, map, wide, high);
        TownSpawn_PutFamilyA(town, map, wide, high);
        for (int i = 1; i < long_days; i++) {
            TownFamily_Day(town, map, i);
            TownGrowth_SpreadFamilyA(town, map, wide, high);
            TownSpawn_PutFamilyA(town, map, wide, high);
        }

        TownSpawn_HousesForDays(town, map, to, days);
        MomDate mom_date = {to->year, to->month, to->day};
        TownObjects_MarkFootprints();
        TownDay_UpdateEvents(town, map, wide, high, to, loaded);
        TownGrowth_ChangeLastStages(town, map, wide, high);
        TownSpawn_Maybe1a(town, map, wide, high);
        TownSpawn_UpdateSpot(town, map, wide, high);
        TownSpawn_PutMarked1549(town, map, wide, high);
        TownSpawn_PutMarked1566(town, map, wide, high);
        TownSpawn_MakeMoneyRocks(town, map, wide, high);
        TownSpawn_AdvanceCodesD4(town, map, days);
        TownSpawn_Put1548OnBeach(town, map, wide);
        TownSpawn_AfterWetDay(town, map, wide, high, wet);
        TownSpawn_AdvanceMarked1369(town, map, wide, high);
        EventWinner_SendLetters(&data_021f3aa4);
        MuseumRecord_CheckLetters(&data_021f38f8);
        HouseRecord_Build((HouseRecord *) (void *) data_021ebcd4);
        NookStore_UpgradeIfDue();
        HouseRecord_AddRoachesForAbsence((HouseRecord *) (void *) data_021ebcd4, days);
        ItemForm_ReplaceEverywhere();
        TownItemLists_FillListA(data_021f3a68, days);
        TownItemLists_EmptyListBOnDays(data_021f3a86, to, days);
        RoomScoreRoom house;
        RoomScore_InitRoom(&house);
        RoomScore_JudgeHouse(&house);
        TownLayout_SetUpperSettings((unsigned int) (uintptr_t) data_021e9aac);
        Sky_Objects020bdfd8(days);
        BottleMail_DailyCheck(days);
        MomLetters_DailyCheck(&mom_date, days);
        DayPlan_Draw(data_021ebcd3);
        NookStore_Refresh(&data_021f395c, 0);
        RoomCells_ResetOther();
        PairedTown_PassDays(days);
        if (days > 0 && WfcStats_Status(&data_021f3278) == 1) {
            WfcStats_SetStatus(&data_021f3278, 2);
        }
        VillagerDay_Begin((u8 *) &data_021e5a2c, to);
        int from_weekday = Calendar_Weekday(from->year, from->month, from->day);
        int to_weekday = Calendar_Weekday(to->year, to->month, to->day);
        if (to_weekday == 0 || days >= 7 || to_weekday - from_weekday < 0) {
            TownSpoil_All(town);
        }
        RoomScore_DestructRoom(&house);
    }
    TileRequests_ClearMarks(&data_021c779c.requests);
    TownSpawn_ClearCodesFc(town);
}
CLEAN_AS(func_0204714c, TownDay_Pass)

/* func_02047500: every family B code (and 0x88, 0xd4-0xda) on the town's inner acres changed
 * as TownDay_FamilyCCode says.
 *
 * REQUIRES: every inner acre has its codes (AcreTile_ItemInAcre is not NULL); the ROM would
 * step on from address 0 otherwise. */
void TownDay_ChangeFamilyB(TownDay *town, AcreMap *map, int wide, int high)
{
    for (int acre_z = 0; acre_z < high; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            const u16 *codes = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), 0, 0, 0);
            for (int k = 0; k < TOWN_DAY_ACRE_TILES; k++) {
                if (codes[k] == ITEM_CODE_NONE) {
                    continue;
                }
                u16 code = TownDay_FamilyCCode((int) (uintptr_t) town, &codes[k], 0);
                if (code != ITEM_CODE_NONE) {
                    int x;
                    int z;
                    AcreTile_TileOfAcre(&x, &z, acre_x + 1, acre_z + 1, k % 16, k / 16);
                    TownTilePut_At(map, x, z, code, 0);
                }
            }
        }
    }
}
CLEAN_AS(func_02047500, TownDay_ChangeFamilyB)

/* func_020475b0: the code a tile's code changes to, or 0xfff1 for none: family B's codes
 * (0x6e-0x87) the family C code of the same place (+0x1c), except 0x86 which becomes 0xa5 when
 * `keep_86`; 0x88 becomes 0xa4 and 0xd4-0xda become 0xdb-0xe1. */
u16 TownDay_FamilyCCode(int unused, const u16 *code, int keep_86)
{
    (void) unused;
    unsigned int value = *code;
    if (value >= 0x6e && value <= 0x87) {
        if (value == 0x86 && keep_86 != 0) {
            return 0xa5;
        }
        return (u16) (value + 0x1c);
    }
    if (value == 0x88) {
        return 0xa4;
    }
    if (value >= 0xd4 && value <= 0xda) {
        return (u16) (value + 7);
    }
    return ITEM_CODE_NONE;
}
CLEAN_AS(func_020475b0, TownDay_FamilyCCode)

/* func_0204762c: the town started now, not as loaded. */
void TownDay_StartNow(void)
{
    TownDay_Start(&data_021c779c, 0);
}
CLEAN_AS(func_0204762c, TownDay_StartNow)

/* func_0204763c: with the town's map, the acre summary made anew and the calendar's buildings
 * set for now. */
void TownDay_Start(TownDay *town, int loaded)
{
    AcreMap *map = TownDay_Map();
    if (map == NULL) {
        return;
    }
    DateTime now = {0};
    DateTime_Now(&now);
    int wide = map->acres_wide - 2;
    int high = map->acres_high - 2;
    TownAcreCount_Summarize(&data_021c779c.acres, map);
    TownDay_UpdateEvents(town, map, wide, high, &now, loaded);
}
CLEAN_AS(func_0204763c, TownDay_Start)

/* func_02047688: the calendar's buildings set for `today`. Not done while something holds the
 * process back, unless loaded with no current player. Once a day (data_021f3a50's stamp, the
 * day starting at 6:00) the record's events that are over are ended and today's started;
 * then the buildings of events not on are removed and those of events on are put up. */
void TownDay_UpdateEvents(TownDay *town, AcreMap *map, int wide, int high, const DateTime *today, int loaded)
{
    if (Process020dabc0_IsHeldBack() != 0) {
        if (!loaded) {
            return;
        }
        if (PlayerRecords_Current() != NULL) {
            return;
        }
    }
    DateTime now = {0};
    Clock_GetDateTime(&now);
    DateTime_SubtractHours(&now, TOWN_DAY_START_HOUR);
    TownDayStamp *stamp = &data_021f3a50;
    if (stamp->year != now.year || stamp->month != now.month || stamp->day != now.day) {
        TownDay_EndEvents(town, map, wide, high, &data_021dc7a8);
        TownDay_StartEvents(town, map, wide, high, today, loaded, &data_021dc7a8);
        TownDay_SetStamp(stamp, &now);
    }
    TownDay_RemoveEventBuildings(town, loaded);
    TownDay_PutEventBuildings(town, &data_021dc7a8, loaded);
}
CLEAN_AS(func_02047688, TownDay_UpdateEvents)

/* func_02047730: the buildings of events 0x3d, 0x3f, 0x60 and 0x44 removed (0x5020 put back
 * for 0x44) while their event is off now. */
void TownDay_RemoveEventBuildings(TownDay *town, int loaded)
{
    (void) town;
    DateTime now = {0};
    DateTime when;
    DateTime_Now(&now);
    MI_CpuCopy8(&now, &when, sizeof when);
    if (EventCalendar_State(0x3d, &when, loaded) == EVENT_CALENDAR_OFF) {
        EventBuildings_Remove5012();
    }
    MI_CpuCopy8(&now, &when, sizeof when);
    if (EventCalendar_State(0x3f, &when, loaded) == EVENT_CALENDAR_OFF) {
        EventBuildings_Remove5013();
    }
    MI_CpuCopy8(&now, &when, sizeof when);
    if (EventCalendar_State(0x60, &when, loaded) == EVENT_CALENDAR_OFF) {
        EventBuildings_Remove5021();
    }
    MI_CpuCopy8(&now, &when, sizeof when);
    if (EventCalendar_State(0x44, &when, loaded) == EVENT_CALENDAR_OFF) {
        EventBuildings_Revert5020();
    }
}
CLEAN_AS(func_02047730, TownDay_RemoveEventBuildings)

/* func_020477e4: each of the record's events (TownDayEvent) that is not of this year or not on
 * now (the clock's month, day and hour) ended, and set free when TownDay_EndEvent knew it. */
void TownDay_EndEvents(TownDay *town, AcreMap *map, int wide, int high, StateBlock *block)
{
    EventKey now;
    Clock_GetMonthDayHour((u8 *) &now);
    const TownDayEvent *event = (const TownDayEvent *) (uintptr_t) TownRecord_Event(0);
    for (int i = 0; i < TOWN_DAY_EVENTS; i++, event++) {
        u16 id = event->id;
        if (id == TOWN_DAY_NO_EVENT) {
            continue;
        }
        if (event->year != Clock_Year() || event->start > now || event->end < now) {
            if (TownDay_EndEvent(town, id, map, wide, high)) {
                TownRecord_FreeEvent((int) (uintptr_t) block->part_17254, id);
            }
        }
    }
}
CLEAN_AS(func_020477e4, TownDay_EndEvents)

/* func_02047854: what ending event `event` does (func_020479f0 for 0x11 and 0x61, building
 * 0x501e removed for 0x62, nothing for 0x10); whether the event is one of those. */
int TownDay_EndEvent(TownDay *town, u16 event, AcreMap *map, int wide, int high)
{
    (void) high;
    switch (event) {
        case 0x10:
            return 1;
        case 0x11:
        case 0x61:
            TownDay_EndCode6d(town, map, wide);
            return 1;
        case TOWN_DAY_EVENT_501E_END:
            EventBuildings_Remove501e();
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_02047854, TownDay_EndEvent)

/* func_02047898: unless the start day is set, the buildings of the events of data_020db764
 * (0x5012, 0x5013, 0x5021) put up while their event is on now. */
void TownDay_PutEventBuildings(TownDay *town, StateBlock *block, int loaded)
{
    (void) town;
    if (TownStartDay_IsSet(TownDay_StartDayOf(block))) {
        return;
    }
    DateTime now = {0};
    DateTime when;
    DateTime_Now(&now);
    for (int i = 0; i < 3; i++) {
        MI_CpuCopy8(&now, &when, sizeof when);
        int state = EventCalendar_State(data_020db764[i], &when, loaded);
        if (state != EVENT_CALENDAR_ON && state != EVENT_CALENDAR_ENDING) {
            continue;
        }
        switch (i) {
            case 0:
                EventBuildings_Put5012();
                break;
            case 1:
                EventBuildings_Put5013();
                break;
            case 2:
                EventBuildings_Put5021();
                break;
        }
    }
}
CLEAN_AS(func_02047898, TownDay_PutEventBuildings)

/* func_0204790c: each of today's events on now (the clock's month, day and hour, its start
 * passed and its end not) started for the town and marked: 0x10 (func_02047bf8), 0x11 and 0x61
 * (func_02047a8c), 0x62 (building 0x501e put up), 0xe (func_02047bc8). */
void TownDay_StartEvents(TownDay *town, AcreMap *map, int wide, int high, const DateTime *today, int loaded, StateBlock *block)
{
    EventCalendarEvent *event = EventCalendar_Today();
    EventKey now;
    Clock_GetMonthDayHour((u8 *) &now);
    int started = TownStartDay_IsSet(TownDay_StartDayOf(block));
    for (int i = 0; i < 7; i++, event++) {
        u16 id = event->id;
        if (id == TOWN_DAY_EVENT_FREE || event->start > now || event->end <= now) {
            continue;
        }
        switch (id) {
            case 0x10:
                TownDay_StartEvent10(town, map, event, wide, high, today, loaded, started, block);
                break;
            case 0x11:
            case 0x61:
                TownDay_PutCode6d(town, map, wide);
                break;
            case TOWN_DAY_EVENT_501E_END:
                EventBuildings_Put501e();
                break;
            case 0xe:
                TownDay_StartEvent0e(town, map, event, today, loaded, started, block);
                break;
            default:
                continue;
        }
        TownDay_MarkEvent(town, event->id);
    }
}
CLEAN_AS(func_0204790c, TownDay_StartEvents)

/* func_020479e0: event `event` marked in the record of data_021f39fc. */
void TownDay_MarkEvent(TownDay *town, int event)
{
    (void) town;
    TownRecord_MarkEvent((int) (uintptr_t) &data_021f39fc, event);
}
CLEAN_AS(func_020479e0, TownDay_MarkEvent)

#define TOWN_DAY_CODE_6D_PER_ACRE 3
#define TOWN_DAY_LINE_5D_FIRST 0x5d
#define TOWN_DAY_LINE_5D_LAST 0x61
#define TOWN_DAY_EVENT_0E 0x0e
#define TOWN_DAY_EVENT_10 0x10
#define TOWN_DAY_ITEM_1542 0x1542 /* the items TownDay_DrawItem1542 draws, 0x1542-0x1546 */
#define TOWN_DAY_ITEM_1542_KINDS 5
#define TOWN_DAY_AROUND_LINE 3
/* Where in the record of data_021f39fc (the state block's 0x17254) data_021f3a50's day is. */
#define TOWN_DAY_EVENTS_STAMP_OFFSET (0x172a8 - 0x17254)

/* The tiles below, left of and right of a growth line's code an item may drop on: x + 8 in the
 * high nibble, z + 8 in the low one. */
extern const u8 data_020ca57c[TOWN_DAY_AROUND_LINE];

/* func_020479f0: when events 0x11 and 0x61 end, every code 0x6d of the first two rows of
 * inner acres goes back to 0x61 and the list of code 0x6d's tiles is emptied. */
void TownDay_EndCode6d(TownDay *town, AcreMap *map, int wide)
{
    for (int acre_z = 0; acre_z < 2; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            TownDay_RevertCode6dIn(town, map, acre_x, acre_z);
        }
    }
    TownDay_ClearCode6d();
}
CLEAN_AS(func_020479f0, TownDay_EndCode6d)

/* func_02047a28: every code 0x6d of inner acre (acre_x, acre_z) made 0x61, unmarked. */
void TownDay_RevertCode6dIn(TownDay *town, AcreMap *map, int acre_x, int acre_z)
{
    (void) town;
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            const u16 *code = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), x, z, 0);
            if (code != NULL && *code == TOWN_DAY_CODE_6D) {
                int tile_x;
                int tile_z;
                AcreTile_TileOfAcre(&tile_x, &tile_z, acre_x + 1, acre_z + 1, x, z);
                TownTilePut_At(map, tile_x, tile_z, TOWN_DAY_LINE_5D_LAST, 0);
            }
        }
    }
}
CLEAN_AS(func_02047a28, TownDay_RevertCode6dIn)

/* func_02047a8c: when events 0x11 and 0x61 start, code 0x6d put in each inner acre of the
 * first two rows (TownDay_PutCode6dIn). */
void TownDay_PutCode6d(TownDay *town, AcreMap *map, int wide)
{
    for (int acre_z = 0; acre_z < 2; acre_z++) {
        for (int acre_x = 0; acre_x < wide; acre_x++) {
            TownDay_PutCode6dIn(town, map, acre_x, acre_z);
        }
    }
}
CLEAN_AS(func_02047a8c, TownDay_PutCode6d)

/* func_02047ac0: inner acre (acre_x, acre_z) made to hold three codes 0x6d: grown codes of line
 * 0x5d (0x5d-0x61, MapItem_IsGrown) drawn at random become 0x6d, unmarked, and go on the list
 * of code 0x6d's tiles, while there are some.
 *
 * BUG: with more than three codes 0x6d the count of codes to make is below 0; every grown code
 * is then made 0x6d, and the ROM's loop goes round about 2^32 times before it ends (here it
 * stops once no grown code is left). */
void TownDay_PutCode6dIn(TownDay *town, AcreMap *map, int acre_x, int acre_z)
{
    (void) town;
    TownDayTile grown[TOWN_DAY_ACRE_TILES];
    int count = 0;
    int code_6d = 0;
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            const u16 *code = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), x, z, 0);
            if (code == NULL) {
                continue;
            }
            if (*code >= TOWN_DAY_LINE_5D_FIRST && *code <= TOWN_DAY_LINE_5D_LAST) {
                if (MapItem_IsGrown(code)) {
                    AcreTile_TileOfAcre(&grown[count].x, &grown[count].z, acre_x + 1, acre_z + 1, x, z);
                    count++;
                }
            } else if (*code == TOWN_DAY_CODE_6D) {
                code_6d++;
            }
        }
    }
    for (u32 missing = (u32) (TOWN_DAY_CODE_6D_PER_ACRE - code_6d); missing != 0 && count > 0; missing--) {
        int pick = (int) MainRandom_Below(count);
        TownTilePut_At(map, grown[pick].x, grown[pick].z, TOWN_DAY_CODE_6D, 0);
        TownDay_AddCode6d((u32) grown[pick].x, (u32) grown[pick].z);
        grown[pick] = grown[count - 1];
        count--;
    }
}
CLEAN_AS(func_02047ac0, TownDay_PutCode6dIn)

/* func_02047bc8: when event 0xe starts, family A codes around the house of every villager that
 * counts (TownSpawn_AroundHouses), for the event's days. */
void TownDay_StartEvent0e(TownDay *town, AcreMap *map, EventCalendarEvent *event, const DateTime *today, int loaded,
                          int started, StateBlock *block)
{
    int days = TownDay_EventDays(town, TOWN_DAY_EVENT_0E, event, today, loaded, started, block);
    TownSpawn_AroundHouses(town, map, 1, days);
}
CLEAN_AS(func_02047bc8, TownDay_StartEvent0e)

/* func_02047bf8: when event 0x10 starts, TownDay_DropAroundLines. */
void TownDay_StartEvent10(TownDay *town, AcreMap *map, EventCalendarEvent *event, int wide, int high, const DateTime *today,
                          int loaded, int started, StateBlock *block)
{
    TownDay_DropAroundLines(town, map, event, wide, high, today, loaded, started, block);
}
CLEAN_AS(func_02047bf8, TownDay_StartEvent10)

/* func_02047c1c: for each of event 0x10's days, items dropped around a growth line's code in
 * every inner acre with codes of 0x26-0x2a or 0x66-0x68 (TownDay_DropAroundLine), row by row.
 *
 * QUIRK: a count of days below 0 (an event started later in the year than today) makes the
 * loop go round until it wraps to 0, about 2^32 times. */
void TownDay_DropAroundLines(TownDay *town, AcreMap *map, EventCalendarEvent *event, int wide, int high, const DateTime *today,
                             int loaded, int started, StateBlock *block)
{
    int days = TownDay_EventDays(town, TOWN_DAY_EVENT_10, event, today, loaded, started, block);
    for (u32 round = (u32) days; round != 0; round--) {
        for (int acre_z = 0; acre_z < high; acre_z++) {
            for (int acre_x = 0; acre_x < wide; acre_x++) {
                if (TownAcreCount_Of(&data_021c779c, acre_x, acre_z)->flags & TOWN_ACRE_HAS_LINE_26) {
                    TownDay_DropAroundLine(town, map, acre_x, acre_z);
                }
            }
        }
    }
}
CLEAN_AS(func_02047c1c, TownDay_DropAroundLines)

/* func_02047c98: one grown code (MapItem_IsGrown) of 0x26-0x2a or 0x66-0x68 of inner acre
 * (acre_x, acre_z) drawn at random; on each free tile below, left of and right of it
 * (data_020ca57c) an item 0x1542-0x1546 drawn at random, unmarked. */
void TownDay_DropAroundLine(TownDay *town, AcreMap *map, int acre_x, int acre_z)
{
    TownDayTile lines[TOWN_DAY_ACRE_TILES];
    int count = 0;
    for (int z = 0; z < 16; z++) {
        for (int x = 0; x < 16; x++) {
            const u16 *code = AcreTile_ItemInAcre(map, (u32) (acre_x + 1), (u32) (acre_z + 1), x, z, 0);
            if (code == NULL) {
                continue;
            }
            u16 value = *code;
            if (((value >= 0x26 && value <= 0x2a) || (value >= 0x66 && value <= 0x68)) && MapItem_IsGrown(code)) {
                AcreTile_TileOfAcre(&lines[count].x, &lines[count].z, acre_x + 1, acre_z + 1, x, z);
                count++;
            }
        }
    }
    if (count <= 0) {
        return;
    }
    const TownDayTile *line = &lines[MainRandom_Below(count)];
    for (int i = 0; i < TOWN_DAY_AROUND_LINE; i++) {
        u8 offset = data_020ca57c[i];
        int x = line->x + ((offset >> 4) - 8);
        int z = line->z + ((offset & 0xf) - 8);
        const u16 *code = TownAcreCount_CodeAt(map, x, z);
        if (code != NULL && *code == ACRE_MAP_ITEM_NONE) {
            TownTilePut_At(map, x, z, TownDay_DrawItem1542(town), 0);
        }
    }
}
CLEAN_AS(func_02047c98, TownDay_DropAroundLine)

/* func_02047db8: one of the items 0x1542-0x1546, drawn at random. */
u16 TownDay_DrawItem1542(TownDay *town)
{
    (void) town;
    return (u16) (TOWN_DAY_ITEM_1542 + MainRandom_Below(TOWN_DAY_ITEM_1542_KINDS));
}
CLEAN_AS(func_02047db8, TownDay_DrawItem1542)

/* func_02047dd4: the days an event that starts now covers: 1 unless loaded; when the record of
 * data_021f39fc already has the event, the days from the day the calendar's buildings were
 * last set (data_021f3a50) to today, at least 0; else 1 when the start day is set, or the days
 * from the event's start (its month and day in today's year) to today, plus 1. */
int TownDay_EventDays(TownDay *town, int event, const EventCalendarEvent *entry, const DateTime *today, int loaded,
                      int started, StateBlock *block)
{
    (void) town;
    if (loaded == 0) {
        return 1;
    }
    if (TownRecord_FindEvent((int) (uintptr_t) block->part_17254, event) < 0) {
        if (started != 0) {
            return 1;
        }
        DateTime start = {0};
        start.year = today->year;
        start.month = EVENT_KEY_MONTH(entry->start);
        start.day = EVENT_KEY_DAY(entry->start);
        return DateTime_DaysBetween(&start, today) + 1;
    }
    Date date = {today->day, today->month, today->year, 0};
    const Date *last = (const Date *) (const void *) (block->part_17254 + TOWN_DAY_EVENTS_STAMP_OFFSET);
    int days = Calendar_DaysFrom(&date, last);
    return days >= 0 ? days : 0;
}
CLEAN_AS(func_02047dd4, TownDay_EventDays)
