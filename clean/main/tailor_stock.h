/* The tailor's stock (data_021f3b44, at 0x1739c of the state block data_021dc7a8): six items
 * with a bit each in `sold`, sold in the shop of kind 10 (shops.h, the Able Sisters' tailor
 * shop: overlay 49's talk sells from it, overlay 4's display shows it in scene 0xa) and read by
 * Design (design.c).
 *
 * Each morning (the day turns at 6:00), when not linked, TailorStock_Refresh restocks them from
 * the day's random numbers (data_021f4a80, seeded from the date): one item of the lot (7, 0x1d),
 * three of (2, 0), one of (6, 0x1d) or (8, 0x1d) weighted by the two counts func_02062124 and
 * func_02062118 give, and one of (5, 0x1d); then it records the date in `stocked`. */
#ifndef CLEAN_MAIN_TAILOR_STOCK_H
#define CLEAN_MAIN_TAILOR_STOCK_H

#include "main/calendar.h"
#include "types.h"

#define TAILOR_STOCK_ITEMS 6

typedef struct TailorStock {
    u16 items[TAILOR_STOCK_ITEMS];
    Date stocked; /* 0x0c: the day of the stock; `extra` 1 asks for a restock */
    u8 sold[1];   /* 0x10: a bit for each item */
} TailorStock;

void TailorStock_StockDone(TailorStock *list);
void TailorStock_StockLot5(TailorStock *list, u32 *next);
void TailorStock_StockLot6Or8(TailorStock *list, u32 *next);
void TailorStock_StockLot2(TailorStock *list, u32 *next);
void TailorStock_StockLot7(TailorStock *list, u32 *next);
int TailorStock_TakeItem(TailorStock *list, u16 *item);
int TailorStock_MarkSold(TailorStock *list, int index);
int TailorStock_FindItem(TailorStock *list, u16 *item);
u16 *TailorStock_Item(TailorStock *list, u32 index, u16 *out);
void TailorStock_SetStockDate(TailorStock *list, const DateTime *when);
int TailorStock_StockDateDiffers(TailorStock *list, const DateTime *when);
void TailorStock_Restock(TailorStock *list, int year, int month, int day);
void TailorStock_Refresh(TailorStock *list);
void TailorStock_Reset(TailorStock *list);
void TailorStock_Init(TailorStock *list);
void TailorStock_Clear(TailorStock *list);
TailorStock *TailorStock_Destruct(TailorStock *list);
TailorStock *TailorStock_Construct(TailorStock *list);

#endif
