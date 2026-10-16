/* Nook's store (nook_store.h). */
#include "nook_store.h"

#include "clean.h"
#include "main/acre_map.h"
#include "main/session.h"
#include "main/shop_list_a.h"
#include "main/shops.h"
#include "main/state_block.h"

static_assert(offsetof(NookStore, items) == 0x04, "items");
static_assert(offsetof(NookStore, stocked) == 0x4e, "stocked");
static_assert(offsetof(NookStore, bonus_day) == 0x52, "bonus_day");
static_assert(offsetof(NookStore, upgrade) == 0x56, "upgrade");
static_assert(offsetof(NookStore, bits) == 0x5a, "bits");
static_assert(offsetof(NookStore, sold) == 0x5c, "sold");

/* The fields of `bits`. */
#define NOOK_HOUR_MASK 0x1fu
#define NOOK_SERIES_SHIFT 5
#define NOOK_SERIES_MASK 0xfu
#define NOOK_LEVEL_SHIFT 9
#define NOOK_LEVEL_MASK 3u

/* The items of NookStore_StockSeries: 0x1521 plus the count in bits 5-8. */
#define NOOK_SERIES_FIRST 0x1521
#define NOOK_SERIES_COUNT 16
/* The item that marks the first section at level 0 (an index into the seven). */
#define NOOK_SEVEN_MARK 3
/* Items that a sale leaves on sale. */
#define NOOK_KEEP_FIRST 0x1000
#define NOOK_KEEP_LAST 0x10ff
#define NOOK_KEEP_ITEM 0x151f

/* Flags of the state block. */
#define NOOK_FLAG_BONUS_DAY 5    /* a bonus day is planned */
#define NOOK_FLAG_BONUS_NOTICE 6 /* its notice is posted */
#define NOOK_FLAG_VISITOR 7      /* a player of another town has bought something here */

/* The day turns at this hour; the bonus day's notice compares from it too. */
#define NOOK_DAY_START_HOUR 6
#define NOOK_SATURDAY 6
#define NOOK_SUNDAY 0
#define NOOK_EVENT_LIMIT 0x1c
#define NOOK_MAX_EVENTS 7
/* The bonus day's notice goes up this many days before it at the earliest (the days between
 * are the three before it). */
#define NOOK_NOTICE_DAYS 4
/* A bonus day this far back is forgotten. */
#define NOOK_BONUS_DAY_EXPIRES (-7)

/* The town map's cells: 16 by 16, the store's building among them. */
#define NOOK_MAP_CELLS 16
#define NOOK_MAP_LAYER 2

/* What the store's rare day draws (see NookStore_Refresh). */
#define NOOK_HOUR_CHANCE 14
#define NOOK_HOURS 4
#define NOOK_FIRST_HOUR 0x11
#define NOOK_SWAP_CHANCE 5
#define NOOK_SWAP_LOT 4
/* December's lots: from the 10th to the 24th, and from the 26th to the 31st. */
#define NOOK_DECEMBER 12
#define NOOK_DECEMBER_LOT_A 0x2b
#define NOOK_DECEMBER_LOT_B 0x2c
#define NOOK_NO_LOT 0x2e

/* The shop kinds in which NookStore_Refresh does nothing unless the scene is one of Nook's. */
#define NOOK_SKIP_KIND_A 0x2c
#define NOOK_SKIP_KIND_B 0x3f

/* The range the sections drawn by func_020b00fc pick a code from (see func_020637d0). */
#define NOOK_SECTION_SIZE 0x25

/* An item lot: func_02063ccc constructs it, func_020638d4 draws an item of it (taking a copy),
 * func_02063cc8 destroys it. */
typedef struct NookItemLot {
    int kind;
    int group;
} NookItemLot;

/* One of the town's events on a date, as func_0203fea0 lists them. */
typedef struct NookTownEvent {
    u16 id;
    u16 unk_02;
    int unk_04;
    int unk_08;
} NookTownEvent;

extern NetSession *data_020ccf94;
extern u32 data_021dc7a8[]; /* the state block (state_block.h) */
extern u8 data_021dc7bc[];  /* the four players' records */
extern NookStore data_021f395c;
extern ShopListA data_021f3b44;
/* The day's random numbers, seeded from the date by func_02063ce0. */
extern u8 data_021f4a80[];
/* The section sizes, by level. */
extern const u8 data_020d1e10[4];
extern const u8 data_020d1e14[4];
extern const u8 data_020d1e18[4];
extern const u8 data_020d1e1c[4];
extern const u8 data_020d1e20[4];
extern const u8 data_020d1e24[4];
extern const u8 data_020d1e28[4];
extern const u8 data_020d1e2c[4];
extern const u8 data_020d1e30[4];
/* The twelve items NookStore_StockTwelve sells (shops.c picks from them too). */
extern const u16 data_020d1e5c[12];
/* The seven items NookStore_StockSeven sells, a static array built on its first call: its
 * guard (bit 0) and a destruction record for each. */
extern u32 data_021f4a00;
extern u16 data_021f4abc[7];
extern u8 data_021f4a20[];
extern u8 data_021f4a2c[];
extern u8 data_021f4a38[];
extern u8 data_021f4a50[];
extern u8 data_021f4a5c[];
extern u8 data_021f4a74[];
extern u8 data_021f4a8c[];
/* The lot NookStore_Refresh swaps an item from, a static object built on its first use: its
 * guard (bit 0) and its destruction record. */
extern u32 data_021f4a08;
extern NookItemLot data_021f4a0c;
extern u8 data_021f4a98[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void __register_global_object(void *object, void *destruct, void *record);
extern void func_020051b0(void *object); /* a destructor that does nothing */

/* `count` codes drawn from `first` up to first + range - 1, at items[*next], *next moved on. */
extern void func_020b00fc(u16 *items, u32 *next, int first, int range, u32 count, int size, u8 convert);
/* `count` items of the lot (kind, group), at items[*next], *next moved on. */
extern void func_020b0164(u16 *items, u32 *next, int kind, int group, u32 count, int size, u8 convert);
extern u16 *func_020b0038(u32 place, u16 *items, u8 *sold, u32 count, u16 *out);
extern int func_020aff84(u16 *item, u16 *items, u8 *sold, u32 count);
extern int func_020b00a8(int place, int count, u8 *sold);
extern void func_020b00c8(u16 *items, u8 *sold, u32 count);
extern void func_020afbcc(NookStore *store);
extern NookUpgrade *func_020afad4(NookStore *store);
extern int func_020afb48(NookStore *store, const DateTime *when); /* whether it is the bonus day */
extern int func_020afc84(DateTime *when);                         /* the upgrade's day at 6:00, if planned */
extern int func_020af9f0(NookStore *store);                       /* whether the upgrade is due */
extern void func_020afcd4(void);                                  /* posts the notice of the new store */
extern int func_020afcf4(int month, int day);                     /* posts the notice of the upgrade */
extern void func_020afd24(u16 *item);                             /* posts the notice of a swapped item */
extern void func_020afd58(u8 hour);                               /* posts the notice of the hour */
extern void func_020afd9c(int month, int day);                    /* posts the notice of the bonus day */

extern u32 func_02063cd4(void *random, u32 range); /* a random number below `range` */
extern void func_02063ce0(void *random, u8 year, u8 month, u8 day);
extern void func_02063ccc(NookItemLot *lot, int kind, int group);
extern void func_02063cc8(NookItemLot *lot);
extern void func_020638d4(u16 *out, NookItemLot *lot, int a, void *random, int b, int c, int d);
extern u32 func_020644cc(int range);
extern int func_0204bcdc(u16 *item); /* whether the item is of the kinds compared by number */
extern int func_0204bc64(u16 *item);
extern int func_0204bba8(void *cell); /* whether the cell holds one of the store's buildings */
extern u16 func_0204bb68(u32 level);  /* the store's building at `level` */
extern void *func_0204f694(u32 map, int layer);
extern void *func_02037e0c(void *layer, u32 x, u32 z, int a);
extern int func_02037e44(void *layer, u16 *item, u32 x, u32 z, int a);

extern void func_0209e474(DateTime *now);                                   /* the clock's date and time */
extern void func_0209e140(DateTime *when, int days);                        /* minus `days` */
extern void func_0209e29c(DateTime *when, int days);                        /* plus `days` */
extern int func_0209e3ac(const DateTime *a, const DateTime *b, int fields); /* -1, 0 or 1 */
extern void func_0209df64(Date *today);
extern int func_0209dcdc(const Date *date, const Date *origin);  /* the days from origin to date */
extern int func_0209de88(int year, int month, int day);          /* the weekday, 0 Sunday */
extern int func_0203fea0(NookTownEvent *events, DateTime *when); /* the town's events that day */

extern void func_020ade78(void);
extern int func_020b5e70(void);
extern int func_020b6744(u32 kind);    /* whether the kind is one of Nook's */
extern int func_020b65c4(void);        /* the kind of the shop the player is in */
extern int func_02098880(u8 *players); /* how many there are */
extern void *func_02098844(u8 *players, int player);
extern void *func_020984e8(void);                 /* this system's player record */
extern int func_02099a28(void *player);           /* whether the record's name is valid */
extern int func_02099020(void *player, int flag); /* whether the record has `flag` */

/* The Date fields of DateTime_Compare (date_time.h): day, month and year, and with the hour. */
#define NOOK_COMPARE_DATE 0x38

/* Whether two item codes are the same: by func_0204bc64's number for the kinds that have one,
 * else by code. */
static int nook_same_item(u16 *item, u16 *other)
{
    if (func_0204bcdc(item) != 0) {
        int a = func_0204bc64(item);
        int b = func_0204bc64(other);
        return a == b;
    }
    return *item == *other;
}

static u32 nook_hour(const NookStore *store)
{
    return store->bits & NOOK_HOUR_MASK;
}

static void nook_set_hour(NookStore *store, u32 hour)
{
    store->bits = (u16) ((store->bits & ~NOOK_HOUR_MASK) | (hour & NOOK_HOUR_MASK));
}

/* An item of `lot` into `*item`: the draw takes a copy of the lot, destroyed after. */
static void nook_draw(u16 *item, const NookItemLot *lot)
{
    NookItemLot copy = *lot;
    u16 drawn;
    func_020638d4(&drawn, &copy, 0, data_021f4a80, 0, 1, 0);
    *item = drawn;
    func_02063cc8(&copy);
}

/* func_020aeb6c: the item 0x155e. */
void NookStore_StockFixed155e(NookStore *store, u32 *next)
{
    func_020b00fc(store->items, next, 0x155e, 1, (u32) NookStore_Count155e(), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aeb6c, NookStore_StockFixed155e)

/* func_020aeb9c: the item 0x151f, from level 1 on. */
void NookStore_Stock151f(NookStore *store, u32 *next)
{
    func_020b00fc(store->items, next, NOOK_KEEP_ITEM, 1, (u32) NookStore_Count151f(store), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aeb9c, NookStore_Stock151f)

/* func_020aebcc: the next items of 0x1521 to 0x1530 (at level 3 only), the count going round. */
void NookStore_StockSeries(NookStore *store, u32 *next)
{
    for (u32 i = 0; i < (u32) NookStore_CountSeries(store); i++) {
        u32 series = (store->bits >> NOOK_SERIES_SHIFT) & NOOK_SERIES_MASK;
        store->items[(*next)++] = (u16) (NOOK_SERIES_FIRST + series);
        series = (series + 1) % NOOK_SERIES_COUNT;
        store->bits = (u16) ((store->bits & ~(NOOK_SERIES_MASK << NOOK_SERIES_SHIFT)) | series << NOOK_SERIES_SHIFT);
    }
}
CLEAN_AS(func_020aebcc, NookStore_StockSeries)

/* func_020aec40: items of the lot (1, 0). */
void NookStore_StockKind1(NookStore *store, u32 *next)
{
    func_020b0164(store->items, next, 1, 0, (u32) NookStore_CountKind1(store), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aec40, NookStore_StockKind1)

/* func_020aec68: items of the lot (3, 0). */
void NookStore_StockKind3(NookStore *store, u32 *next)
{
    func_020b0164(store->items, next, 3, 0, NookStore_CountKind3(store), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aec68, NookStore_StockKind3)

/* func_020aec90: items of the lot (4, 0). */
void NookStore_StockKind4(NookStore *store, u32 *next)
{
    func_020b0164(store->items, next, 4, 0, NookStore_CountKind4(store), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aec90, NookStore_StockKind4)

/* func_020aecb8: the items 0x151d and 0x151e (shops.c treats them as a pair). */
void NookStore_StockPair(NookStore *store, u32 *next)
{
    func_020b00fc(store->items, next, 0x151d, 2, (u32) NookStore_CountPair(store), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aecb8, NookStore_StockPair)

/* func_020aece8: items of the twelve of data_020d1e5c (drawn as their indices). */
void NookStore_StockTwelve(NookStore *store, u32 *next)
{
    u32 start = *next;
    func_020b00fc(store->items, next, 0, 12, NookStore_CountTwelve(store), NOOK_SECTION_SIZE, 0);
    for (u32 i = start; i < start + NookStore_CountTwelve(store); i++) {
        store->items[i] = data_020d1e5c[store->items[i]];
    }
}
CLEAN_AS(func_020aece8, NookStore_StockTwelve)

/* func_020aed38: items of the lot (0, 0). */
void NookStore_StockKind0(NookStore *store, u32 *next)
{
    func_020b0164(store->items, next, 0, 0, (u32) NookStore_CountKind0(store), NOOK_SECTION_SIZE, 0);
}
CLEAN_AS(func_020aed38, NookStore_StockKind0)

/* func_020aed60: items of the seven of data_021f4abc (drawn as their indices; at level 0 of the
 * first four only, one of them the fourth: when none drawn is, one of the first two places of
 * the section becomes it). The seven are built on the first call. */
void NookStore_StockSeven(NookStore *store, u32 *next)
{
    static const u16 codes[7] = {0x1369, 0x1378, 0x1376, 0x1374, 0x156c, 0x136b, 0x137a};

    if ((data_021f4a00 & 1) == 0) {
        u8 *records[7] = {data_021f4a20, data_021f4a2c, data_021f4a38, data_021f4a50,
                          data_021f4a5c, data_021f4a74, data_021f4a8c};
        for (int i = 0; i < 7; i++) {
            data_021f4abc[i] = codes[i];
            __register_global_object(&data_021f4abc[i], (void *) func_020051b0, records[i]);
        }
        data_021f4a00 |= 1;
    }

    int range = NookStore_Level(store) == 0 ? 4 : 7;
    u32 start = *next;
    func_020b00fc(store->items, next, 0, range, (u32) NookStore_CountSeven(store), NOOK_SECTION_SIZE, 0);

    if (NookStore_Level(store) == 0) {
        int marks = 0;
        for (u32 i = 0; i < (u32) NookStore_CountSeven(store); i++) {
            u16 mark = NOOK_SEVEN_MARK;
            if (nook_same_item(&store->items[start + i], &mark)) {
                marks++;
            }
        }
        if (marks == 0) {
            store->items[start + func_020644cc(2)] = NOOK_SEVEN_MARK;
        }
    }

    for (u32 i = 0; i < (u32) NookStore_CountSeven(store); i++) {
        store->items[start + i] = data_021f4abc[store->items[start + i]];
    }
}
CLEAN_AS(func_020aed60, NookStore_StockSeven)

/* func_020aef28 */
int NookStore_Count155e(void)
{
    return 1;
}
CLEAN_AS(func_020aef28, NookStore_Count155e)

/* func_020aef2c */
int NookStore_Count151f(NookStore *store)
{
    return data_020d1e30[NookStore_Level(store)];
}
CLEAN_AS(func_020aef2c, NookStore_Count151f)

/* func_020aef44 */
int NookStore_CountSeries(NookStore *store)
{
    return data_020d1e14[NookStore_Level(store)];
}
CLEAN_AS(func_020aef44, NookStore_CountSeries)

/* func_020aef5c */
int NookStore_CountKind1(NookStore *store)
{
    return data_020d1e1c[NookStore_Level(store)];
}
CLEAN_AS(func_020aef5c, NookStore_CountKind1)

/* func_020aef74 */
u8 NookStore_CountKind3(NookStore *store)
{
    return data_020d1e10[(u8) NookStore_Level(store)];
}
CLEAN_AS(func_020aef74, NookStore_CountKind3)

/* func_020aef8c */
u8 NookStore_CountKind4(NookStore *store)
{
    return data_020d1e18[NookStore_Level(store)];
}
CLEAN_AS(func_020aef8c, NookStore_CountKind4)

/* func_020aefa4 */
int NookStore_CountPair(NookStore *store)
{
    return data_020d1e2c[NookStore_Level(store)];
}
CLEAN_AS(func_020aefa4, NookStore_CountPair)

/* func_020aefbc */
u8 NookStore_CountTwelve(NookStore *store)
{
    return data_020d1e28[NookStore_Level(store)];
}
CLEAN_AS(func_020aefbc, NookStore_CountTwelve)

/* func_020aefd4 */
int NookStore_CountKind0(NookStore *store)
{
    return data_020d1e24[NookStore_Level(store)];
}
CLEAN_AS(func_020aefd4, NookStore_CountKind0)

/* func_020aefec */
int NookStore_CountSeven(NookStore *store)
{
    return data_020d1e20[NookStore_Level(store)];
}
CLEAN_AS(func_020aefec, NookStore_CountSeven)

/* func_020af004 */
void NookStore_SetLevel(NookStore *store, u16 level)
{
    store->bits =
        (u16) ((store->bits & ~(NOOK_LEVEL_MASK << NOOK_LEVEL_SHIFT)) | (level & NOOK_LEVEL_MASK) << NOOK_LEVEL_SHIFT);
}
CLEAN_AS(func_020af004, NookStore_SetLevel)

/* func_020af028 */
u32 NookStore_Level(NookStore *store)
{
    return (store->bits >> NOOK_LEVEL_SHIFT) & NOOK_LEVEL_MASK;
}
CLEAN_AS(func_020af028, NookStore_Level)

/* func_020af038: the end of a restock; does nothing. */
void NookStore_StockDone(NookStore *store)
{
    (void) store;
}
CLEAN_AS(func_020af038, NookStore_StockDone)

/* The coming Saturday (`pick` 0) or the Sunday after it as the bonus day, unless `from` is a
 * Saturday or Sunday itself or one of the two days has a town event below 0x1c. Whether it was
 * planned. */
static int nook_pick_bonus_day(NookStore *store, const DateTime *from, u32 pick)
{
    DateTime today;
    MI_CpuCopy8(from, &today, sizeof today);
    int weekday = func_0209de88(today.year, today.month, today.day);
    if (weekday == NOOK_SATURDAY || weekday == NOOK_SUNDAY) {
        return 0;
    }
    int days = NOOK_SATURDAY - weekday;

    DateTime saturday;
    DateTime sunday;
    MI_CpuCopy8(&today, &saturday, sizeof saturday);
    MI_CpuCopy8(&today, &sunday, sizeof sunday);
    func_0209e29c(&saturday, days);
    func_0209e29c(&sunday, days + 1);

    NookTownEvent events_saturday[NOOK_MAX_EVENTS];
    NookTownEvent events_sunday[NOOK_MAX_EVENTS];
    DateTime when;
    MI_CpuCopy8(&saturday, &when, sizeof when);
    int count_saturday = func_0203fea0(events_saturday, &when);
    MI_CpuCopy8(&sunday, &when, sizeof when);
    int count_sunday = func_0203fea0(events_sunday, &when);

    int blocked_saturday = 0;
    int blocked_sunday = 0;
    for (int i = 0; i < count_saturday; i++) {
        if (NookStore_EventBlocksBonusDay(events_saturday[i].id) != 0) {
            blocked_saturday++;
        }
    }
    for (int i = 0; i < count_sunday; i++) {
        if (NookStore_EventBlocksBonusDay(events_sunday[i].id) != 0) {
            blocked_sunday++;
        }
    }
    if (blocked_saturday != 0 || blocked_sunday != 0) {
        return 0;
    }

    const DateTime *day = pick == 0 ? &saturday : &sunday;
    store->bonus_day.year = day->year;
    store->bonus_day.month = day->month;
    store->bonus_day.day = day->day;
    store->bonus_day.unused = 0;
    return 1;
}

/* func_020af03c: forgets a bonus day that has passed or is more than six days off by today's
 * date, plans one when there is none (nook_pick_bonus_day),
 * and when `now` is in the three days before it posts its notice once. */
void NookStore_PlanBonusDay(NookStore *store, const DateTime *now)
{
    DateTime at;
    MI_CpuCopy8(now, &at, sizeof at);
    u32 pick = func_02063cd4(data_021f4a80, 2);

    if (StateBlock_TestFlag(data_021dc7a8, NOOK_FLAG_BONUS_DAY) != 0) {
        Date today;
        func_0209df64(&today);
        int days = func_0209dcdc(&today, &store->bonus_day);
        if (days >= 1 || days <= NOOK_BONUS_DAY_EXPIRES) {
            StateBlock_ClearFlag(data_021dc7a8, NOOK_FLAG_BONUS_DAY);
        }
    }

    if (StateBlock_TestFlag(data_021dc7a8, NOOK_FLAG_BONUS_DAY) == 0) {
        if (nook_pick_bonus_day(store, now, pick)) {
            StateBlock_ClearFlag(data_021dc7a8, NOOK_FLAG_BONUS_NOTICE);
            StateBlock_SetFlag(data_021dc7a8, NOOK_FLAG_BONUS_DAY);
        }
    }

    if (StateBlock_TestFlag(data_021dc7a8, NOOK_FLAG_BONUS_DAY) == 0) {
        return;
    }
    DateTime bonus = {0};
    bonus.year = store->bonus_day.year;
    bonus.month = store->bonus_day.month;
    bonus.day = store->bonus_day.day;
    bonus.hour = NOOK_DAY_START_HOUR;
    if (func_0209e3ac(&bonus, &at, NOOK_COMPARE_DATE) == -1) {
        StateBlock_ClearFlag(data_021dc7a8, NOOK_FLAG_BONUS_DAY);
        return;
    }
    DateTime notice_from;
    MI_CpuCopy8(&bonus, &notice_from, sizeof notice_from);
    func_0209e140(&notice_from, NOOK_NOTICE_DAYS);
    if (func_0209e3ac(&notice_from, &at, NOOK_COMPARE_DATE) == -1 && func_0209e3ac(&at, &bonus, NOOK_COMPARE_DATE) == -1) {
        if (StateBlock_TestFlag(data_021dc7a8, NOOK_FLAG_BONUS_NOTICE) == 0) {
            func_020afd9c(store->bonus_day.month, store->bonus_day.day);
            StateBlock_SetFlag(data_021dc7a8, NOOK_FLAG_BONUS_NOTICE);
        }
    }
}
CLEAN_AS(func_020af03c, NookStore_PlanBonusDay)

/* func_020af28c: whether a town event keeps the bonus day off its day. */
int NookStore_EventBlocksBonusDay(int event)
{
    return event < NOOK_EVENT_LIMIT;
}
CLEAN_AS(func_020af28c, NookStore_EventBlocksBonusDay)

/* func_020af298 */
void NookStore_SetStockDate(NookStore *store, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof copy);
    store->stocked.year = copy.year;
    store->stocked.month = copy.month;
    store->stocked.day = copy.day;
    store->stocked.unused = 0;
}
CLEAN_AS(func_020af298, NookStore_SetStockDate)

/* func_020af2d0: whether the stock is not of `when`'s date (always, when `unused` is set). */
int NookStore_StockDateDiffers(NookStore *store, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof copy);
    return store->stocked.year != copy.year || store->stocked.month != copy.month || store->stocked.day != copy.day ||
           store->stocked.unused != 0;
}
CLEAN_AS(func_020af2d0, NookStore_StockDateDiffers)

/* func_020af31c: a new stock for the date, its sections in the order of the places. */
void NookStore_Restock(NookStore *store, u8 year, u8 month, u8 day)
{
    NookStore_ClearStock(store);
    u32 next = 0;
    func_02063ce0(data_021f4a80, year, month, day);
    NookStore_StockSeven(store, &next);
    NookStore_StockKind0(store, &next);
    NookStore_StockTwelve(store, &next);
    NookStore_StockPair(store, &next);
    NookStore_StockKind4(store, &next);
    NookStore_StockKind3(store, &next);
    NookStore_StockKind1(store, &next);
    NookStore_StockSeries(store, &next);
    NookStore_Stock151f(store, &next);
    NookStore_StockFixed155e(store, &next);
    NookStore_StockDone(store);
}
CLEAN_AS(func_020af31c, NookStore_Restock)

/* Whether every player of the town has flag 1 of the record (this system's player when there
 * is one; true when there is none). */
static int nook_players_have_flag1(void)
{
    int count = func_02098880(data_021dc7bc);
    if (count == 0) {
        return 1;
    }
    if (count == 1) {
        void *player = func_020984e8();
        return player != NULL && func_02099020(player, 1) != 0;
    }
    for (int i = 0; i < 4; i++) {
        void *player = func_02098844(data_021dc7bc, i);
        if (player == NULL || func_02099a28(player) == 0) {
            continue;
        }
        if (func_02099020(player, 1) == 0) {
            return 0;
        }
    }
    return 1;
}

/* The day's extras: the bonus day, the hour (one day in fourteen), and otherwise, when it is
 * not the bonus day, one day in five the first item func_0204bcdc accepts swapped for one of
 * the static lot (0, 4). The notices go up only after 6:00. */
static void nook_plan_extras(NookStore *store, const DateTime *now, int after_six)
{
    NookStore_PlanBonusDay(store, now);
    if (func_02063cd4(data_021f4a80, NOOK_HOUR_CHANCE) == 0) {
        nook_set_hour(store, func_02063cd4(data_021f4a80, NOOK_HOURS) + NOOK_FIRST_HOUR);
        if (after_six) {
            func_020afd58((u8) nook_hour(store));
        }
    }
    if (nook_hour(store) != 0 || func_020afb48(store, now) != 0) {
        return;
    }
    if ((data_021f4a08 & 1) == 0) {
        func_02063ccc(&data_021f4a0c, 0, NOOK_SWAP_LOT);
        __register_global_object(&data_021f4a0c, (void *) func_02063cc8, data_021f4a98);
        data_021f4a08 |= 1;
    }
    if (func_02063cd4(data_021f4a80, NOOK_SWAP_CHANCE) != 0) {
        return;
    }
    for (u32 i = 0; i < NOOK_STORE_PLACES; i++) {
        u16 *item = &store->items[i];
        if (func_0204bcdc(item) != 0) {
            nook_draw(item, &data_021f4a0c);
            if (after_six) {
                func_020afd24(item);
            }
            break;
        }
    }
}

/* In December, the second item func_0204bcdc accepts swapped for one of the season's lot. */
static void nook_december(NookStore *store, const DateTime *now)
{
    if (now->month != NOOK_DECEMBER) {
        return;
    }
    u32 day = now->day;
    int group = NOOK_NO_LOT;
    if (day >= 10 && day <= 24) {
        group = NOOK_DECEMBER_LOT_A;
    } else if (day >= 26 && day <= 31) {
        group = NOOK_DECEMBER_LOT_B;
    }
    if (group == NOOK_NO_LOT) {
        return;
    }
    int seen = 0;
    for (u32 i = 0; i < NOOK_STORE_PLACES; i++) {
        if (func_0204bcdc(&store->items[i]) != 0) {
            if (seen == 1) {
                NookItemLot lot;
                func_02063ccc(&lot, 0, group);
                nook_draw(&store->items[i], &lot);
                func_02063cc8(&lot);
                break;
            }
            seen++;
        }
    }
}

/* func_020af3a0: the morning update: Shop list A's first, then (unless a pending state of 1
 * becomes 2, or the player is in a shop of kind 0x2c or 0x3f outside Nook's scenes) a new stock
 * when the day (from 6:00) is not the stock's or `force` is set, with the day's extras unless
 * every player has flag 1 or an upgrade is planned, and December's item. Nothing changes but
 * the hour's clearing while linked.
 * QUIRK: the hour is cleared before the link is looked at. */
void NookStore_Refresh(NookStore *store, int force)
{
    ShopListA_Refresh(&data_021f3b44);
    if (Shops_PendingState() == 1) {
        Shops_SetPendingState(2);
        return;
    }
    if (func_020b6744((u32) func_020b5e70()) == 0) {
        u32 kind = (u32) func_020b65c4();
        if (kind == NOOK_SKIP_KIND_A || kind == NOOK_SKIP_KIND_B) {
            return;
        }
    }

    int after_six = 1;
    DateTime now = {0};
    func_0209e474(&now);
    if (now.hour < NOOK_DAY_START_HOUR) {
        func_0209e140(&now, 1);
        after_six = 0;
    }
    if (force == 0 && NookStore_StockDateDiffers(store, &now) == 0) {
        return;
    }
    nook_set_hour(store, 0);
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }
    func_020ade78();
    NookStore_SetStockDate(store, &now);
    NookStore_Restock(store, now.year, now.month, now.day);

    if (!nook_players_have_flag1() && func_020afad4(store)->pending == 0) {
        nook_plan_extras(store, &now, after_six);
    }
    nook_december(store, &now);
}
CLEAN_AS(func_020af3a0, NookStore_Refresh)

/* func_020af648: whether a player of another town has bought something here. */
int NookStore_VisitorHasShopped(NookStore *store)
{
    (void) store;
    return StateBlock_TestFlag(data_021dc7a8, NOOK_FLAG_VISITOR);
}
CLEAN_AS(func_020af648, NookStore_VisitorHasShopped)

/* func_020af658: notes a buyer that is not of this town (`local` 0). */
void NookStore_NoteBuyer(NookStore *store, int local)
{
    (void) store;
    if (local == 0) {
        StateBlock_SetFlag(data_021dc7a8, NOOK_FLAG_VISITOR);
    }
}
CLEAN_AS(func_020af658, NookStore_NoteBuyer)

/* `amount` more spent, up to the level's cap. */
static void nook_add_spent(NookStore *store, u32 amount)
{
    u32 cap = NookStore_Cap(store, (int) NookStore_Level(store));
    store->spent += amount;
    if (store->spent > cap) {
        store->spent = cap;
    }
}

/* func_020af674: `amount` spent on place `place`, which is sold unless it is sold already or
 * holds one of the items that stay (0x1000-0x10ff, 0x151f); notes the buyer and plans an
 * upgrade if one is due. Returns whether the place is one of the store's. */
int NookStore_Sell(NookStore *store, u32 place, u32 amount, int local)
{
    if (place < NOOK_STORE_PLACES) {
        nook_add_spent(store, amount);
        if (NookStore_IsSold(store, (int) place) == 0) {
            u16 item = *NookStore_Item(store, place, NULL);
            if (!(item >= NOOK_KEEP_FIRST && item <= NOOK_KEEP_LAST)) {
                item = *NookStore_Item(store, place, NULL);
                if (item != NOOK_KEEP_ITEM) {
                    store->sold[place >> 3] |= (u8) (1u << (place & 7));
                }
            }
        }
        NookStore_NoteBuyer(store, local);
        NookStore_PlanUpgrade(store);
        return 1;
    }
    nook_add_spent(store, amount);
    NookStore_NoteBuyer(store, local);
    NookStore_PlanUpgrade(store);
    return 0;
}
CLEAN_AS(func_020af674, NookStore_Sell)

/* func_020af750: `amount` spent without a place. */
void NookStore_AddSpent(NookStore *store, u32 amount, u32 local)
{
    nook_add_spent(store, amount);
    NookStore_NoteBuyer(store, (int) local);
    NookStore_PlanUpgrade(store);
}
CLEAN_AS(func_020af750, NookStore_AddSpent)

/* func_020af788: when not linked and a higher level is due with none planned, plans the
 * upgrade two days from now (three when the day before it, when the store is closed, would be
 * the bonus day) and posts the notice naming the day before. */
void NookStore_PlanUpgrade(NookStore *store)
{
    int next = NookStore_NextLevel(store);
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }
    if ((int) NookStore_Level(store) >= next) {
        return;
    }
    if (func_020afad4(store)->pending != 0) {
        return;
    }

    DateTime day = {0};
    func_0209e474(&day);
    func_0209e29c(&day, 2);
    DateTime closed;
    MI_CpuCopy8(&day, &closed, sizeof closed);
    func_0209e140(&closed, 1);
    if (func_020afb48(store, &closed) != 0) {
        func_0209e29c(&day, 1);
    }

    func_020afad4(store)->pending = 1;
    func_020afad4(store)->year = day.year;
    func_020afad4(store)->month = day.month;
    func_020afad4(store)->day = day.day;

    func_0209e140(&day, 1);
    func_020afcf4(day.month, day.day);
}
CLEAN_AS(func_020af788, NookStore_PlanUpgrade)

/* func_020af83c: the place of `item`, or -1. */
int NookStore_FindItem(NookStore *store, u16 *item)
{
    return func_020aff84(item, store->items, store->sold, NOOK_STORE_PLACES);
}
CLEAN_AS(func_020af83c, NookStore_FindItem)

/* func_020af854: the item of place `place` (data_021f49f4 when sold); its code also in `out`
 * unless NULL. */
u16 *NookStore_Item(NookStore *store, u32 place, u16 *out)
{
    return func_020b0038(place, store->items, store->sold, NOOK_STORE_PLACES, out);
}
CLEAN_AS(func_020af854, NookStore_Item)

/* func_020af870 */
int NookStore_IsSold(NookStore *store, int place)
{
    return func_020b00a8(place, NOOK_STORE_PLACES, store->sold);
}
CLEAN_AS(func_020af870, NookStore_IsSold)

/* func_020af880: no items, none sold. */
void NookStore_ClearStock(NookStore *store)
{
    func_020b00c8(store->items, store->sold, NOOK_STORE_PLACES);
}
CLEAN_AS(func_020af880, NookStore_ClearStock)

/* func_020af890 */
void NookStore_Reset(NookStore *store)
{
    func_020afbcc(store);
}
CLEAN_AS(func_020af890, NookStore_Reset)

/* func_020af898: the level the store should have: the next one once the spent amount reached
 * the cap, the top one only after a visitor bought something (NookStore_VisitorHasShopped, of
 * data_021f395c whatever `store` is). */
int NookStore_NextLevel(NookStore *store)
{
    u32 level = NookStore_Level(store);
    if (level == NOOK_STORE_TOP_LEVEL) {
        return (int) level;
    }
    if (store->spent < NookStore_Cap(store, (int) level)) {
        return (int) NookStore_Level(store);
    }
    int visitor = NookStore_VisitorHasShopped(&data_021f395c);
    if (level == NOOK_STORE_TOP_LEVEL - 1 && visitor == 0) {
        return (int) NookStore_Level(store);
    }
    return (int) level + 1;
}
CLEAN_AS(func_020af898, NookStore_NextLevel)

/* func_020af8e0: the most that counts as spent at `level`. */
u32 NookStore_Cap(NookStore *store, int level)
{
    (void) store;
    switch (level) {
        case 0:
            return 25000;
        case 1:
            return 90000;
        default:
            return 240000;
    }
}
CLEAN_AS(func_020af8e0, NookStore_Cap)

/* func_020aea84: when no pending state of 1 holds it and the planned upgrade is due, the new
 * level: its building replaces the store's on the town map, the level is set, the notice of the
 * new store goes up when today is the planned day, the plan is cleared and the store restocked.
 * Returns whether it was upgraded. */
int NookStore_UpgradeIfDue(void)
{
    if (Shops_PendingState() == 1) {
        return 0;
    }
    if (func_020af9f0(&data_021f395c) == 0) {
        return 0;
    }
    int level = NookStore_NextLevel(&data_021f395c);
    u32 town = AcreMap_Town();
    if (town == 0) {
        return 0;
    }
    void *layer = func_0204f694(town, NOOK_MAP_LAYER);
    if (layer == NULL) {
        return 0;
    }
    for (u32 z = 0; z < NOOK_MAP_CELLS; z++) {
        for (u32 x = 0; x < NOOK_MAP_CELLS; x++) {
            void *cell = func_02037e0c(layer, x, z, 0);
            if (cell == NULL || func_0204bba8(cell) == 0) {
                continue;
            }
            u16 building = func_0204bb68((u32) level);
            func_02037e44(layer, &building, x, z, 0);
            NookStore_SetLevel(&data_021f395c, (u16) level);

            DateTime due = {0};
            if (func_020afc84(&due) != 0) {
                DateTime now = {0};
                func_0209e474(&now);
                if (now.year == due.year && now.month == due.month && now.day == due.day) {
                    func_020afcd4();
                }
            }
            func_020afad4(&data_021f395c)->pending = 0;
            NookStore_Refresh(&data_021f395c, 1);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020aea84, NookStore_UpgradeIfDue)
