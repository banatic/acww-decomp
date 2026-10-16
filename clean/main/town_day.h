/* The town's object (data_021c779c) and the town's day.
 *
 * The object gathers what the town keeps while it is played: the time beach items were last
 * looked at (town_beach.h), the effects being started (tile_effects.h), the worker thread
 * (worker_thread.h), the tiles of code 0x6d in the second and third rows of acres, the changes
 * to tiles under way (tile_changes.h), a summary of the town's acres made by func_0204a3cc
 * and func_0204a848, and the requests to change tiles (tile_requests.h).
 *
 * The town's day starts at 6:00. The state block keeps the last day the town was brought up to
 * (TownDayStamp, data_021f39fc); each check of the clock compares it with now (TownDay_Check)
 * and, a day or more later, the town is moved on by the days that passed (TownDay_Pass, run by
 * the worker thread when there is one): its acres, items, villagers, shops, letters and the
 * calendar's buildings. A second stamp (data_021f3a50) says the calendar's buildings were set
 * for the day (TownDay_UpdateEvents). */
#ifndef CLEAN_MAIN_TOWN_DAY_H
#define CLEAN_MAIN_TOWN_DAY_H

#include "acre_map.h"
#include "calendar.h"
#include "state_block.h"
#include "tile_changes.h"
#include "tile_effects.h"
#include "tile_requests.h"
#include "types.h"

#define TOWN_DAY_START_HOUR 6
#define TOWN_DAY_CODE_6D 0x6d
#define TOWN_DAY_CODE_6D_TILES 24
#define TOWN_DAY_NO_TILE (-1)
#define TOWN_DAY_ACRE_TILES 256 /* 16 x 16 */

/* A tile of the town's map. */
typedef struct TownDayTile {
    int x;
    int z;
} TownDayTile;

/* What func_0204a848 counts in one inner acre (0x24 bytes). */
typedef struct TownDayAcre {
    u8 unk_00[0x1c];
    u8 beach_items; /* 0x1c: items 0x1554-0x155c lying in the acre */
    u8 unk_1d[7];
} TownDayAcre;

#define TOWN_DAY_ACRES_WIDE 4
#define TOWN_DAY_ACRES_HIGH 4
#define TOWN_DAY_BEACH_ROW 3 /* the last row of inner acres (acre row 4 of the map) */

/* data_021c79c4: the summary of the town's inner acres (func_0204a3cc). */
typedef struct TownDayAcres {
    int unk_00; /* 0x00: handed to func_0204cac0 by the day's change */
    u8 unk_04[0x18 - 0x04];
    u8 unk_18[0x34 - 0x18]; /* 0x18: data_021c79dc */
    int spot_acre_x;        /* 0x34: a tile func_0204a3cc picks: its inner acre (from 0), -1 for none */
    int spot_acre_z;        /* 0x38 */
    int spot_x;             /* 0x3c: the tile in the acre */
    int spot_z;             /* 0x40 */
    TownDayAcre acres[TOWN_DAY_ACRES_WIDE][TOWN_DAY_ACRES_HIGH]; /* 0x44: data_021c7a08, by x then z */
} TownDayAcres;

/* data_021c779c */
typedef struct TownDay {
    Time beach_time;                             /* 0x000: when beach items were last looked at */
    u8 unk_02[2];                                /* 0x002 */
    TileEffectsSource effects;                   /* 0x004: data_021c77a0 */
    u8 no_drop;                                  /* 0x01c: no item may drop (tile_requests.c) */
    u8 unk_1d[3];                                /* 0x01d */
    struct WorkerThread *job;                    /* 0x020: worker_thread.h */
    TownDayTile code_6d[TOWN_DAY_CODE_6D_TILES]; /* 0x024: data_021c77c0, -1, -1 for none */
    TileChanges changes;                         /* 0x0e4: data_021c7880 */
    TownDayAcres acres;                          /* 0x228: data_021c79c4 */
    TileRequests requests;                       /* 0x4ac: data_021c7c48 */
} TownDay;

/* The first bytes of the state block's record at 0x17254 (data_021f39fc), and of the one at
 * data_021f3a50: a day of the town. */
typedef struct TownDayStamp {
    u8 day;
    u8 month;
    u8 year;
} TownDayStamp;

/* An event the town took part in (func_0204cc04, four of them after data_021f39fc's stamp). */
typedef struct TownDayEvent {
    u16 id; /* 99 for none */
    u8 year;
    u8 unk_03;
    u32 start; /* 0x04: an EventKey (event_calendar.h) */
    u32 end;   /* 0x08 */
} TownDayEvent;

#define TOWN_DAY_NO_EVENT 99
#define TOWN_DAY_EVENTS 4

void TownDay_Update(void);
void TownDay_Init(void);
void TownDay_MarkEventOf(int event);
void TownDay_ResetMarks(void);
void TownDay_ClearCode6d(void);
void TownDay_AddCode6d(u32 x, u32 z);
int TownDay_Code6dTiles(void);
int TownDay_FindCode6d(int x, int z);
int TownDay_SpotPosition(Vec3 *position);
int TownDay_Object(void);
int TownDay_Acres18(void);
int TownDay_Summarize(void);
void TownDay_Enter(void);
void TownDay_Refresh(void);
void TownDay_Load(void);
int TownDay_ClockWentBack(void);
void TownDay_ListCode6d(void);
void TownDay_OnClock(void);
void TownDay_Check(int loaded);
void TownDay_SetPeriod(void);
void TownDay_Move(const DateTime *from, const DateTime *to, int days, int wet, int loaded);
void TownDay_Pass(TownDay *town, const DateTime *from, const DateTime *to, int days, u8 wet, int loaded);
void TownDay_ChangeFamilyB(TownDay *town, AcreMap *map, int wide, int high);
u16 TownDay_FamilyCCode(int unused, const u16 *code, int keep_86);
void TownDay_StartNow(void);
void TownDay_Start(TownDay *town, int loaded);
void TownDay_UpdateEvents(TownDay *town, AcreMap *map, int wide, int high, const DateTime *today, int loaded);
void TownDay_RemoveEventBuildings(TownDay *town, int loaded);
void TownDay_EndEvents(TownDay *town, AcreMap *map, int wide, int high, StateBlock *block);
int TownDay_EndEvent(TownDay *town, u16 event, AcreMap *map, int wide, int high);
void TownDay_PutEventBuildings(TownDay *town, StateBlock *block, int loaded);
void TownDay_StartEvents(TownDay *town, AcreMap *map, int wide, int high, const DateTime *today, int loaded,
                         StateBlock *block);
void TownDay_MarkEvent(TownDay *town, int event);

#endif
