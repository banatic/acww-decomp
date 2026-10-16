/* Shop list A (shop_list_a.h). */
#include "shop_list_a.h"

#include "clean.h"
#include "main/session.h"

static_assert(offsetof(ShopListA, stocked) == 0x0c, "stocked");
static_assert(offsetof(ShopListA, sold) == 0x10, "sold");

/* The day turns at this hour. */
#define SHOP_LIST_A_DAY_START_HOUR 6
/* The range the draws record as the size of the list they fill (see func_020b0164). */
#define SHOP_LIST_A_DRAW_SIZE 6

extern NetSession *data_020ccf94;
/* The day's random numbers, seeded from the date by func_02063ce0. */
extern u8 data_021f4a80[];

/* `count` items of the lot (kind, group), at items[*next], *next moved on. */
extern void func_020b0164(u16 *items, u32 *next, int kind, int group, u32 count, int size, u8 convert);
extern u16 *func_020b0038(u32 index, u16 *items, u8 *sold, u32 count, u16 *out);
extern int func_020aff84(u16 *item, u16 *items, u8 *sold, u32 count); /* its place, or -1 */
extern int func_020b0074(int index, int count, u8 *sold);             /* marks it sold, if not */
extern void func_020b00c8(u16 *items, u8 *sold, u32 count);           /* none, none sold */
extern u32 func_02063cd4(void *random, u32 range);                    /* a random number below `range` */
extern void func_02063ce0(void *random, int year, int month, int day);
extern u32 func_02062124(void);
extern u32 func_02062118(void);
extern int func_0204bcdc(u16 *item); /* whether the item is of the kinds compared by number */
extern int func_0204bc64(u16 *item);
extern void func_0209e474(DateTime *now);            /* the clock's date and time */
extern void func_0209e140(DateTime *when, int days); /* minus `days` */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_020051b0(void *object); /* a destructor that does nothing */
extern void func_02034ce0(void *item);   /* an item's constructor: 0xfff1 */
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));

/* Whether two item codes are the same: by func_0204bc64's number for the kinds that have one,
 * else by code. */
static int shop_list_a_same_item(u16 *item, u16 *other)
{
    if (func_0204bcdc(item) != 0) {
        int a = func_0204bc64(item);
        int b = func_0204bc64(other);
        return a == b;
    }
    return *item == *other;
}

/* func_020ae794: the end of a restock; does nothing. */
void ShopListA_StockDone(ShopListA *list)
{
    (void) list;
}
CLEAN_AS(func_020ae794, ShopListA_StockDone)

/* func_020ae798: one item of the lot (5, 0x1d). */
void ShopListA_StockLot5(ShopListA *list, u32 *next)
{
    func_020b0164(list->items, next, 5, 0x1d, 1, SHOP_LIST_A_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae798, ShopListA_StockLot5)

/* func_020ae7b4: one item of the lot (6, 0x1d) or (8, 0x1d), the first with the chance
 * func_02062124 / (func_02062124 + func_02062118). */
void ShopListA_StockLot6Or8(ShopListA *list, u32 *next)
{
    u32 first = func_02062124();
    u32 second = func_02062118();
    u32 draw = func_02063cd4(data_021f4a80, first + second);
    int kind = draw < func_02062124() ? 6 : 8;
    func_020b0164(list->items, next, kind, 0x1d, 1, SHOP_LIST_A_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae7b4, ShopListA_StockLot6Or8)

/* func_020ae814: three items of the lot (2, 0). */
void ShopListA_StockLot2(ShopListA *list, u32 *next)
{
    func_020b0164(list->items, next, 2, 0, 3, SHOP_LIST_A_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae814, ShopListA_StockLot2)

/* func_020ae834: one item of the lot (7, 0x1d). */
void ShopListA_StockLot7(ShopListA *list, u32 *next)
{
    func_020b0164(list->items, next, 7, 0x1d, 1, SHOP_LIST_A_DRAW_SIZE, 1);
}
CLEAN_AS(func_020ae834, ShopListA_StockLot7)

/* func_020ae850: marks sold the first item that is `*item`. Returns whether one was marked.
 * QUIRK: a sold item reads as data_021f49f4, so that marker matches the first sold item, which
 * stays sold (0). */
int ShopListA_TakeItem(ShopListA *list, u16 *item)
{
    for (u32 i = 0; i < SHOP_LIST_A_ITEMS; i++) {
        u16 *here = ShopListA_Item(list, i, NULL);
        if (shop_list_a_same_item(here, item)) {
            return ShopListA_MarkSold(list, (int) i);
        }
    }
    return 0;
}
CLEAN_AS(func_020ae850, ShopListA_TakeItem)

/* func_020ae8bc: marks item `index` sold; whether it was not yet. */
int ShopListA_MarkSold(ShopListA *list, int index)
{
    return func_020b0074(index, SHOP_LIST_A_ITEMS, list->sold);
}
CLEAN_AS(func_020ae8bc, ShopListA_MarkSold)

/* func_020ae8cc: the place of `item` among the items not sold, or -1. */
int ShopListA_FindItem(ShopListA *list, u16 *item)
{
    return func_020aff84(item, list->items, list->sold, SHOP_LIST_A_ITEMS);
}
CLEAN_AS(func_020ae8cc, ShopListA_FindItem)

/* func_020ae8e4: item `index` (data_021f49f4 when sold); its code also in `out` unless NULL. */
u16 *ShopListA_Item(ShopListA *list, u32 index, u16 *out)
{
    return func_020b0038(index, list->items, list->sold, SHOP_LIST_A_ITEMS, out);
}
CLEAN_AS(func_020ae8e4, ShopListA_Item)

/* func_020ae900 */
void ShopListA_SetStockDate(ShopListA *list, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof copy);
    list->stocked.year = copy.year;
    list->stocked.month = copy.month;
    list->stocked.day = copy.day;
    list->stocked.unused = 0;
}
CLEAN_AS(func_020ae900, ShopListA_SetStockDate)

/* func_020ae92c: whether the stock is not of `when`'s date (always, when `unused` is set). */
int ShopListA_StockDateDiffers(ShopListA *list, const DateTime *when)
{
    DateTime copy;
    MI_CpuCopy8(when, &copy, sizeof copy);
    return list->stocked.year != copy.year || list->stocked.month != copy.month || list->stocked.day != copy.day ||
           list->stocked.unused != 0;
}
CLEAN_AS(func_020ae92c, ShopListA_StockDateDiffers)

/* func_020ae96c: a new stock for the date. */
void ShopListA_Restock(ShopListA *list, int year, int month, int day)
{
    ShopListA_Clear(list);
    func_02063ce0(data_021f4a80, year, month, day);
    u32 next = 0;
    ShopListA_StockLot7(list, &next);
    ShopListA_StockLot2(list, &next);
    ShopListA_StockLot6Or8(list, &next);
    ShopListA_StockLot5(list, &next);
    ShopListA_StockDone(list);
}
CLEAN_AS(func_020ae96c, ShopListA_Restock)

/* func_020ae9c0: when not linked, a new stock when the day (from 6:00) is not the stock's. */
void ShopListA_Refresh(ShopListA *list)
{
    DateTime now = {0};
    func_0209e474(&now);
    if (now.hour < SHOP_LIST_A_DAY_START_HOUR) {
        func_0209e140(&now, 1);
    }
    if (Session_IsLinked(data_020ccf94) != 0) {
        return;
    }
    if (ShopListA_StockDateDiffers(list, &now) == 0) {
        return;
    }
    ShopListA_Restock(list, now.year, now.month, now.day);
    ShopListA_SetStockDate(list, &now);
}
CLEAN_AS(func_020ae9c0, ShopListA_Refresh)

/* func_020aea1c: does nothing (Nook's store's counterpart resets it). */
void ShopListA_Reset(ShopListA *list)
{
    (void) list;
}
CLEAN_AS(func_020aea1c, ShopListA_Reset)

/* func_020aea20: the state block's setting up (func_0209ef7c) clears the list. */
void ShopListA_Init(ShopListA *list)
{
    ShopListA_Clear(list);
}
CLEAN_AS(func_020aea20, ShopListA_Init)

/* func_020aea28: no items, none sold, and a restock asked for. */
void ShopListA_Clear(ShopListA *list)
{
    func_020b00c8(list->items, list->sold, SHOP_LIST_A_ITEMS);
    list->stocked.unused = 1;
}
CLEAN_AS(func_020aea28, ShopListA_Clear)

/* func_020aea40: the items' destructor. */
ShopListA *ShopListA_Destruct(ShopListA *list)
{
    __cxa_vec_cleanup(list->items, SHOP_LIST_A_ITEMS, sizeof list->items[0], func_020051b0);
    return list;
}
CLEAN_AS(func_020aea40, ShopListA_Destruct)

/* func_020aea5c: the items' constructor (each 0xfff1). */
ShopListA *ShopListA_Construct(ShopListA *list)
{
    __cxa_vec_ctor(list->items, SHOP_LIST_A_ITEMS, sizeof list->items[0], func_02034ce0, func_020051b0);
    return list;
}
CLEAN_AS(func_020aea5c, ShopListA_Construct)
