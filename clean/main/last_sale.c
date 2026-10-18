/* The last sale of overlay 52's seller (last_sale.h). */
#include "last_sale.h"

#include "clean.h"
#include "player_id.h"

#define LAST_SALE_NO_ITEM 0xfff1

static_assert(offsetof(LastSale, item) == 0x1e && sizeof(LastSale) == 0x20, "LastSale");

/* func_020871cc */
void LastSale_GetItem(u16 *item, const LastSale *sale)
{
    *item = sale->item;
}
CLEAN_AS(func_020871cc, LastSale_GetItem)

/* func_020871d4 */
void LastSale_SetItem(LastSale *sale, const u16 *item)
{
    sale->item = *item;
}
CLEAN_AS(func_020871d4, LastSale_SetItem)

/* A copy a halfword at a time from the first, as the ROM's structure copies are: when the two
 * overlap, the result is the ROM's. */
static void copy_halfwords(void *dst, const void *src, size_t size)
{
    u16 *d = dst;
    const u16 *s = src;
    for (size_t i = 0; i < size / 2; i++) {
        d[i] = s[i];
    }
}

/* func_020871dc */
void LastSale_SetBuyer(LastSale *sale, const DesignCreator *buyer)
{
    copy_halfwords(&sale->buyer, buyer, sizeof sale->buyer);
}
CLEAN_AS(func_020871dc, LastSale_SetBuyer)

/* func_02087228 */
DesignCreator *LastSale_Buyer(LastSale *sale)
{
    return &sale->buyer;
}
CLEAN_AS(func_02087228, LastSale_Buyer)

/* func_0208722c: the town's setting up empties it. */
void LastSale_SetUp(LastSale *sale)
{
    LastSale_Clear(sale);
}
CLEAN_AS(func_0208722c, LastSale_SetUp)

/* func_02087234: no buyer, no item. */
void LastSale_Clear(LastSale *sale)
{
    PlayerId_Clear(&sale->buyer);
    sale->item = LAST_SALE_NO_ITEM;
}
CLEAN_AS(func_02087234, LastSale_Clear)

/* func_0208724c */
LastSale *LastSale_Destruct(LastSale *sale)
{
    PlayerId_Destruct(&sale->buyer);
    return sale;
}
CLEAN_AS(func_0208724c, LastSale_Destruct)

/* func_0208725c: the constructor; no item. */
LastSale *LastSale_Construct(LastSale *sale)
{
    PlayerId_Construct(&sale->buyer);
    sale->item = LAST_SALE_NO_ITEM;
    return sale;
}
CLEAN_AS(func_0208725c, LastSale_Construct)
