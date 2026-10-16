/* A shop's stock: item codes and sold bits (shop_stock.h). */
#include "shop_stock.h"

#include "clean.h"

/* An empty place: no item. */
#define SHOP_STOCK_NO_ITEM 0xfff1

/* The draws of ShopStock_DrawCodes: the value func_020637d0 takes after its two zeros. */
#define SHOP_STOCK_CODES_MODE 10

/* What a place past the stock reads as (0xfff1) and what a sold place reads as (0x1547). */
extern u16 data_021f49f0;
extern u16 data_021f49f4;
/* The day's random numbers, seeded from the date by func_02063ce0. */
extern u8 data_021f4a80[];

extern int func_0204bcdc(u16 *item); /* whether the item is of the kinds compared by number */
extern int func_0204bc64(u16 *item); /* that number */
/* `count` different codes from `first` up to first + range - 1, at `out`. */
extern int func_020637d0(u16 *out, u32 count, int first, int range, int a, int b, int mode, u8 *random, int c);
/* `count` items of `lot`, at `out`. */
extern int func_020638b0(u16 *out, u32 count, void *lot, int a, u8 *random, int b, int c, int d);
extern void func_02063ccc(void *lot, int kind, int group); /* builds the lot (kind, group) */
extern void func_02063cc8(void *lot);                      /* destroys it */
/* `*code` as the code its item has in a room (whatever the scene is when `always` is set). */
extern void func_02061b1c(u16 *out, u16 *code, int always);

/* An item lot as func_02063ccc builds it. */
typedef struct ShopStockLot {
    int kind;
    int group;
    int unused;
} ShopStockLot;

/* Whether two codes are the same item: by func_0204bc64's number when func_0204bcdc accepts
 * `item`, else by code. */
static int shop_stock_same(u16 *item, u16 *other)
{
    if (func_0204bcdc(item) != 0) {
        int a = func_0204bc64(item);
        int b = func_0204bc64(other);
        return a == b;
    }
    return *item == *other;
}

/* Each code of the `count` places from `*next` on as its room's code. */
static void shop_stock_convert(u16 *items, const u32 *next, u32 count)
{
    for (u32 i = 0; i < count; i++) {
        u16 *place = &items[i + *next];
        u16 converted;
        func_02061b1c(&converted, place, 1);
        *place = converted;
    }
}

/* func_020aff84: the first place that holds `item` and is not sold, or -1. An `item` that is
 * the sold marker is never found. */
int ShopStock_Find(u16 *item, u16 *items, u8 *sold, u32 count)
{
    for (u32 place = 0; place < count; place++) {
        u16 *here = ShopStock_Item(place, items, sold, count, NULL);
        if (shop_stock_same(here, item) && !shop_stock_same(item, &data_021f49f4)) {
            return (int) place;
        }
    }
    return -1;
}
CLEAN_AS(func_020aff84, ShopStock_Find)

/* func_020b0038: the item of `place`: the sold marker when it is sold, data_021f49f0 past the
 * stock. Its own code also goes to `out` (unless NULL), sold or not. */
u16 *ShopStock_Item(u32 place, u16 *items, u8 *sold, u32 count, u16 *out)
{
    if (place >= count) {
        return &data_021f49f0;
    }
    u16 *item = &items[place];
    if (out != NULL) {
        *out = *item;
    }
    if (ShopStock_IsSold(place, count, sold) != 0) {
        return &data_021f49f4;
    }
    return item;
}
CLEAN_AS(func_020b0038, ShopStock_Item)

/* func_020b0074: marks `place` sold; whether it was not sold before. */
int ShopStock_MarkSold(u32 place, u32 count, u8 *sold)
{
    if (place < count && ShopStock_IsSold(place, count, sold) == 0) {
        sold[place >> 3] |= (u8) (1u << (place & 7));
        return 1;
    }
    return 0;
}
CLEAN_AS(func_020b0074, ShopStock_MarkSold)

/* func_020b00a8: whether `place` is sold; a place past the stock counts as sold. */
int ShopStock_IsSold(u32 place, u32 count, u8 *sold)
{
    if (place >= count) {
        return 1;
    }
    return (sold[place >> 3] >> (place & 7)) & 1;
}
CLEAN_AS(func_020b00a8, ShopStock_IsSold)

/* func_020b00c8: no item in any place, none sold. */
void ShopStock_Clear(u16 *items, u8 *sold, u32 count)
{
    for (u32 i = 0; i < count; i++) {
        items[i] = SHOP_STOCK_NO_ITEM;
    }
    for (u32 i = 0; i < (count >> 3) + 1; i++) {
        sold[i] = 0;
    }
}
CLEAN_AS(func_020b00c8, ShopStock_Clear)

/* func_020b00fc: `count` different codes from `first` up to first + range - 1 at the places
 * from `*next` on, as their room's codes when `convert` is set; `*next` moves past them.
 * `size` is not used. */
void ShopStock_DrawCodes(u16 *items, u32 *next, int first, int range, u32 count, u32 size, u8 convert)
{
    (void) size;
    if (count == 0) {
        return;
    }
    func_020637d0(&items[*next], count, first, range, 0, 0, SHOP_STOCK_CODES_MODE, data_021f4a80, 0);
    if (convert != 0) {
        shop_stock_convert(items, next, count);
    }
    *next += count;
}
CLEAN_AS(func_020b00fc, ShopStock_DrawCodes)

/* func_020b0164: `count` items of the lot (kind, group) at the places from `*next` on, as
 * their room's codes when `convert` is set; `*next` moves past them. `size` is not used. */
void ShopStock_DrawLot(u16 *items, u32 *next, int kind, int group, u32 count, int size, u8 convert)
{
    (void) size;
    if (count == 0) {
        return;
    }
    ShopStockLot lot;
    func_02063ccc(&lot, kind, group);
    func_020638b0(&items[*next], count, &lot, 0, data_021f4a80, 0, 1, 0);
    func_02063cc8(&lot);
    if (convert != 0) {
        shop_stock_convert(items, next, count);
    }
    *next += count;
}
CLEAN_AS(func_020b0164, ShopStock_DrawLot)
