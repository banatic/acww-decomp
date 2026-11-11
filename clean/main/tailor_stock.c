/* The tailor's stock (tailor_stock.h). */
#include "tailor_stock.h"

#include "clean.h"
#include "main/session.h"
#include "date_random.h"
#include "date_time.h"
#include "item_code.h"
#include "item_info.h"
#include "shop_stock.h"

static_assert(offsetof(TailorStock, stocked) == 0x0c, "stocked");
static_assert(offsetof(TailorStock, sold) == 0x10, "sold");

/* The day turns at this hour. */
#define TAILOR_STOCK_DAY_START_HOUR 6
/* The range the draws record as the size of the list they fill (see func_020b0164). */
#define TAILOR_STOCK_DRAW_SIZE 6

extern NetSession *data_020ccf94;
/* The day's random numbers, seeded from the date by func_02063ce0. */
extern u8 data_021f4a80[];

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_020051b0(void *object); /* a destructor that does nothing */
extern void func_02034ce0(void *item);   /* an item's constructor: 0xfff1 */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* Whether two item codes are the same: by func_0204bc64's number for the kinds that have one,
 * else by code. */
static int tailor_stock_same_item(u16 *item, u16 *other)
{
    if (ItemCode_IsFurniture(item) != 0) {
        int a = ItemCode_FurnitureNumber(item);
        int b = ItemCode_FurnitureNumber(other);
        return a == b;
    }
    return *item == *other;
}

/* func_020ae794: the end of a restock; does nothing. */
void TailorStock_StockDone(TailorStock *list)
{
    (void) list;
}
CLEAN_AS(func_020ae794, TailorStock_StockDone)

/* func_020ae798: one item of the lot (5, 0x1d). */
void TailorStock_StockLot5(TailorStock *list, u32 *next)
{
    ShopStock_PickLot(list->items, next, 5, 0x1d, 1, TAILOR_STOCK_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae798, TailorStock_StockLot5)

/* func_020ae7b4: one item of the lot (6, 0x1d) or (8, 0x1d), the first with the chance
 * func_02062124 / (func_02062124 + func_02062118). */
void TailorStock_StockLot6Or8(TailorStock *list, u32 *next)
{
    u32 first = ItemInfo_CountTailorHeadB();
    u32 second = ItemInfo_CountTailorHeadA();
    u32 draw = DatedRandom_Below((DatedRandom *) (void *) data_021f4a80, first + second);
    int kind = draw < ItemInfo_CountTailorHeadB() ? 6 : 8;
    ShopStock_PickLot(list->items, next, kind, 0x1d, 1, TAILOR_STOCK_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae7b4, TailorStock_StockLot6Or8)

/* func_020ae814: three items of the lot (2, 0). */
void TailorStock_StockLot2(TailorStock *list, u32 *next)
{
    ShopStock_PickLot(list->items, next, 2, 0, 3, TAILOR_STOCK_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae814, TailorStock_StockLot2)

/* func_020ae834: one item of the lot (7, 0x1d). */
void TailorStock_StockLot7(TailorStock *list, u32 *next)
{
    ShopStock_PickLot(list->items, next, 7, 0x1d, 1, TAILOR_STOCK_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae834, TailorStock_StockLot7)

/* func_020ae850: marks sold the first item that is `*item`. Returns whether one was marked.
 * QUIRK: a sold item reads as data_021f49f4, so that marker matches the first sold item, which
 * stays sold (0). */
int TailorStock_TakeItem(TailorStock *list, u16 *item)
{
    for (u32 i = 0; i < TAILOR_STOCK_ITEMS; i++) {
        u16 *here = TailorStock_Item(list, i, NULL);
        if (tailor_stock_same_item(here, item)) {
            return TailorStock_MarkSold(list, (int) i);
        }
    }
    return 0;
}
CLEAN_AS(func_020ae850, TailorStock_TakeItem)

/* func_020ae8bc: marks item `index` sold; whether it was not yet. */
int TailorStock_MarkSold(TailorStock *list, int index)
{
    return ShopStock_MarkSold(index, TAILOR_STOCK_ITEMS, list->sold);
}
CLEAN_AS(func_020ae8bc, TailorStock_MarkSold)

/* func_020ae8cc: the place of `item` among the items not sold, or -1. */
int TailorStock_FindItem(TailorStock *list, u16 *item)
{
    return ShopStock_Find(item, list->items, list->sold, TAILOR_STOCK_ITEMS);
}
CLEAN_AS(func_020ae8cc, TailorStock_FindItem)

/* func_020ae8e4: item `index` (data_021f49f4 when sold); its code also in `out` unless NULL. */
u16 *TailorStock_Item(TailorStock *list, u32 index, u16 *out)
{
    return ShopStock_Item(index, list->items, list->sold, TAILOR_STOCK_ITEMS, out);
}
CLEAN_AS(func_020ae8e4, TailorStock_Item)

/* func_020ae900 */
void TailorStock_SetStockDate(TailorStock *list, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof copy);
    list->stocked.year = copy.year;
    list->stocked.month = copy.month;
    list->stocked.day = copy.day;
    list->stocked.extra = 0;
}
CLEAN_AS(func_020ae900, TailorStock_SetStockDate)

/* func_020ae92c: whether the stock is not of `when`'s date (always, when `unused` is set). */
int TailorStock_StockDateDiffers(TailorStock *list, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof copy);
    return list->stocked.year != copy.year || list->stocked.month != copy.month || list->stocked.day != copy.day ||
           list->stocked.extra != 0;
}
CLEAN_AS(func_020ae92c, TailorStock_StockDateDiffers)

/* func_020ae96c: a new stock for the date. */
void TailorStock_Restock(TailorStock *list, int year, int month, int day)
{
    TailorStock_Clear(list);
    DatedRandom_SetDate((DatedRandom *) (void *) data_021f4a80, year, month, day);
    u32 next = 0;
    TailorStock_StockLot7(list, &next);
    TailorStock_StockLot2(list, &next);
    TailorStock_StockLot6Or8(list, &next);
    TailorStock_StockLot5(list, &next);
    TailorStock_StockDone(list);
}
CLEAN_AS(func_020ae96c, TailorStock_Restock)

/* func_020ae9c0: when not linked, a new stock when the day (from 6:00) is not the stock's. */
void TailorStock_Refresh(TailorStock *list)
{
    DateTime now = {0};
    DateTime_Now(&now);
    if (now.hour < TAILOR_STOCK_DAY_START_HOUR) {
        DateTime_SubtractDays(&now, 1);
    }
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }
    if (TailorStock_StockDateDiffers(list, &now) == 0) {
        return;
    }
    TailorStock_Restock(list, now.year, now.month, now.day);
    TailorStock_SetStockDate(list, &now);
}
CLEAN_AS(func_020ae9c0, TailorStock_Refresh)

/* func_020aea1c: does nothing (Nook's store's counterpart resets it). */
void TailorStock_Reset(TailorStock *list)
{
    (void) list;
}
CLEAN_AS(func_020aea1c, TailorStock_Reset)

/* func_020aea20: the state block's setting up (func_0209ef7c) clears the list. */
void TailorStock_Init(TailorStock *list)
{
    TailorStock_Clear(list);
}
CLEAN_AS(func_020aea20, TailorStock_Init)

/* func_020aea28: no items, none sold, and a restock asked for. */
void TailorStock_Clear(TailorStock *list)
{
    ShopStock_Clear(list->items, list->sold, TAILOR_STOCK_ITEMS);
    list->stocked.extra = 1;
}
CLEAN_AS(func_020aea28, TailorStock_Clear)

/* func_020aea40: the items' destructor. */
TailorStock *TailorStock_Destruct(TailorStock *list)
{
    __cxa_vec_cleanup(list->items, TAILOR_STOCK_ITEMS, sizeof list->items[0], func_020051b0);
    return list;
}
CLEAN_AS(func_020aea40, TailorStock_Destruct)

/* func_020aea5c: the items' constructor (each 0xfff1). */
TailorStock *TailorStock_Construct(TailorStock *list)
{
    __cxa_vec_ctor(list->items, TAILOR_STOCK_ITEMS, sizeof list->items[0], func_02034ce0, func_020051b0);
    return list;
}
CLEAN_AS(func_020aea5c, TailorStock_Construct)
