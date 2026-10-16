/* Shop list A (data_021f3b44, at 0x1739c of the state block data_021dc7a8): six items with a
 * bit each in `sold`, sold in the shop of kind 10 (shops.h's list A) and read by Design
 * (design.c).
 *
 * Each morning (the day turns at 6:00), when not linked, ShopListA_Refresh restocks them from
 * the day's random numbers (data_021f4a80, seeded from the date): one item of the lot (7, 0x1d),
 * three of (2, 0), one of (6, 0x1d) or (8, 0x1d) weighted by the two counts func_02062124 and
 * func_02062118 give, and one of (5, 0x1d); then it records the date in `stocked`. */
#ifndef CLEAN_MAIN_SHOP_LIST_A_H
#define CLEAN_MAIN_SHOP_LIST_A_H

#include "main/calendar.h"
#include "types.h"

#define SHOP_LIST_A_ITEMS 6

typedef struct ShopListA {
    u16 items[SHOP_LIST_A_ITEMS];
    Date stocked; /* 0x0c: the day of the stock; `unused` 1 asks for a restock */
    u8 sold[1];   /* 0x10: a bit for each item */
} ShopListA;

void ShopListA_StockDone(ShopListA *list);
void ShopListA_StockLot5(ShopListA *list, u32 *next);
void ShopListA_StockLot6Or8(ShopListA *list, u32 *next);
void ShopListA_StockLot2(ShopListA *list, u32 *next);
void ShopListA_StockLot7(ShopListA *list, u32 *next);
int ShopListA_TakeItem(ShopListA *list, u16 *item);
int ShopListA_MarkSold(ShopListA *list, int index);
int ShopListA_FindItem(ShopListA *list, u16 *item);
u16 *ShopListA_Item(ShopListA *list, u32 index, u16 *out);
void ShopListA_SetStockDate(ShopListA *list, const DateTime *when);
int ShopListA_StockDateDiffers(ShopListA *list, const DateTime *when);
void ShopListA_Restock(ShopListA *list, int year, int month, int day);
void ShopListA_Refresh(ShopListA *list);
void ShopListA_Reset(ShopListA *list);
void ShopListA_Init(ShopListA *list);
void ShopListA_Clear(ShopListA *list);
ShopListA *ShopListA_Destruct(ShopListA *list);
ShopListA *ShopListA_Construct(ShopListA *list);

#endif
