/* A shop's stock as Nook's store (nook_store.h), shop list A (shop_list_a.h) and the fox's shop
 * (fox_shop.h) keep it: `count` item codes, one per place, and a bit per place in `sold`
 * ((count >> 3) + 1 bytes, bit (place & 7) of byte place >> 3).
 *
 * A place that is sold reads as the marker data_021f49f4 (item 0x1547), a place past the stock
 * as data_021f49f0 (0xfff1, no item); both are set up before main's code runs. Restocking
 * draws codes or items of a lot from the day's random numbers (data_021f4a80) into the places
 * from `*next` on, moving `*next` past them. */
#ifndef CLEAN_MAIN_SHOP_STOCK_H
#define CLEAN_MAIN_SHOP_STOCK_H

#include "types.h"

int ShopStock_Find(u16 *item, u16 *items, u8 *sold, u32 count);
u16 *ShopStock_Item(u32 place, u16 *items, u8 *sold, u32 count, u16 *out);
int ShopStock_MarkSold(u32 place, u32 count, u8 *sold);
int ShopStock_IsSold(u32 place, u32 count, u8 *sold);
void ShopStock_Clear(u16 *items, u8 *sold, u32 count);
void ShopStock_DrawCodes(u16 *items, u32 *next, int first, int range, u32 count, u32 size, u8 convert);
void ShopStock_DrawLot(u16 *items, u32 *next, int kind, int group, u32 count, int size, u8 convert);

#endif
