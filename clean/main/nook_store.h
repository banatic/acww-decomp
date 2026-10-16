/* Nook's store (data_021f395c, at 0x171b4 of the state block data_021dc7a8): what it sells, how
 * much has been spent there, its level and the days it plans.
 *
 * Stock: 37 places, each an item code with a bit in `sold` (NookStore_Item gives a sold one as
 * the marker data_021f49f4). Each morning (the day turns at 6:00) NookStore_Refresh restocks
 * them from the day's random numbers (data_021f4a80, seeded from the date) in ten sections whose
 * sizes depend on the level (tables data_020d1e10 to data_020d1e30), and records the date in
 * `stocked`. A sold place stays sold until then, except for the items 0x1000-0x10ff and 0x151f.
 *
 * Level: 0 to 3, in bits 9-10 of `bits`. The amount spent is capped by the level's cap (25000,
 * 90000, then 240000); reaching it makes the next level due, the last one only once a player of
 * another town has bought something here (flag 7 of the state block). An upgrade is planned two
 * days ahead (`upgrade`, func_020afad4), posted as a notice, and NookStore_UpgradeIfDue puts the
 * new building (item 0x500d + level) on the town map on its day.
 *
 * Bonus day: the coming Saturday or Sunday, when neither has one of the town's events below
 * 0x1c, planned on a weekday when none is (`bonus_day`, flag 5 of the state block); the store
 * posts a notice in the three days before it (flag 6 says it did). Shop points count five times on it (shop_points.h).
 *
 * Bits 0-4 of `bits` hold an hour (17 to 20) set on one day in fourteen at random: from it until
 * 23:00 func_020afb90 answers 1; 0 for none. Bits 5-8 count on through the items 0x1521 to
 * 0x1530, one of which each restock may sell. */
#ifndef CLEAN_MAIN_NOOK_STORE_H
#define CLEAN_MAIN_NOOK_STORE_H

#include "main/calendar.h"
#include "types.h"

#define NOOK_STORE_PLACES 0x25
#define NOOK_STORE_TOP_LEVEL 3

/* The day of the planned upgrade, as func_020afad4 gives it. */
typedef struct NookUpgrade {
    u8 day;
    u8 month;
    u8 year;
    u8 pending; /* 1 while an upgrade is planned */
} NookUpgrade;

typedef struct NookStore {
    u32 spent;                             /* what has been spent here, capped by the level's cap */
    u16 items[NOOK_STORE_PLACES];          /* 0x04 */
    Date stocked;                          /* 0x4e: the day of the stock; `unused` 1 asks for a restock */
    Date bonus_day;                        /* 0x52 */
    NookUpgrade upgrade;                   /* 0x56 */
    u16 bits;                              /* 0x5a: the hour (bits 0-4), the next 0x1521 item (5-8), the level (9-10) */
    u8 sold[(NOOK_STORE_PLACES >> 3) + 1]; /* 0x5c: a bit for each place */
} NookStore;

void NookStore_StockFixed155e(NookStore *store, u32 *next);
void NookStore_Stock151f(NookStore *store, u32 *next);
void NookStore_StockSeries(NookStore *store, u32 *next);
void NookStore_StockKind1(NookStore *store, u32 *next);
void NookStore_StockKind3(NookStore *store, u32 *next);
void NookStore_StockKind4(NookStore *store, u32 *next);
void NookStore_StockPair(NookStore *store, u32 *next);
void NookStore_StockTwelve(NookStore *store, u32 *next);
void NookStore_StockKind0(NookStore *store, u32 *next);
void NookStore_StockSeven(NookStore *store, u32 *next);
int NookStore_Count155e(void);
int NookStore_Count151f(NookStore *store);
int NookStore_CountSeries(NookStore *store);
int NookStore_CountKind1(NookStore *store);
u8 NookStore_CountKind3(NookStore *store);
u8 NookStore_CountKind4(NookStore *store);
int NookStore_CountPair(NookStore *store);
u8 NookStore_CountTwelve(NookStore *store);
int NookStore_CountKind0(NookStore *store);
int NookStore_CountSeven(NookStore *store);
void NookStore_SetLevel(NookStore *store, u16 level);
u32 NookStore_Level(NookStore *store);
void NookStore_StockDone(NookStore *store);
void NookStore_PlanBonusDay(NookStore *store, const DateTime *now);
int NookStore_EventBlocksBonusDay(int event);
void NookStore_SetStockDate(NookStore *store, const DateTime *when);
int NookStore_StockDateDiffers(NookStore *store, const DateTime *when);
void NookStore_Restock(NookStore *store, u8 year, u8 month, u8 day);
void NookStore_Refresh(NookStore *store, int force);
int NookStore_VisitorHasShopped(NookStore *store);
void NookStore_NoteBuyer(NookStore *store, int local);
int NookStore_Sell(NookStore *store, u32 place, u32 amount, int local);
void NookStore_AddSpent(NookStore *store, u32 amount, u32 local);
void NookStore_PlanUpgrade(NookStore *store);
int NookStore_FindItem(NookStore *store, u16 *item);
u16 *NookStore_Item(NookStore *store, u32 place, u16 *out);
int NookStore_IsSold(NookStore *store, int place);
void NookStore_ClearStock(NookStore *store);
void NookStore_Reset(NookStore *store);
int NookStore_NextLevel(NookStore *store);
u32 NookStore_Cap(NookStore *store, int level);
int NookStore_UpgradeIfDue(void);

#endif
