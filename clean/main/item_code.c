/* Item code helpers. */
#include "item_code.h"
#include "clean.h"

#include <assert.h>

/* An arithmetic shift right, as the ARM's ASR does it, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* func_0204b42c */
int ItemCode_Get(const ItemCode *item)
{
    return *item;
}
CLEAN_AS(func_0204b42c, ItemCode_Get)

/* func_0204b79c: QUIRK: keeps the low 16 bits of `code`. */
void ItemCode_Set(ItemCode *item, int code)
{
    *item = (ItemCode) code;
}
CLEAN_AS(func_0204b79c, ItemCode_Set)

/* func_0204bf18 */
void ItemCode_Copy(ItemCode *dst, const ItemCode *src)
{
    *dst = *src;
}
CLEAN_AS(func_0204bf18, ItemCode_Copy)

/* func_0204b48c: first and last both included. */
BOOL ItemCode_InRange(const ItemCode *item, u16 first, u16 last)
{
    return *item >= first && *item <= last;
}
CLEAN_AS(func_0204b48c, ItemCode_InRange)

/* func_0204bcf8 */
int ItemCode_Kind(const ItemCode *item)
{
    return *item >> 12;
}
CLEAN_AS(func_0204bcf8, ItemCode_Kind)

/* func_0204bd08 */
BOOL ItemCode_IsKind1(const ItemCode *item)
{
    return ItemCode_Kind(item) == 1;
}
CLEAN_AS(func_0204bd08, ItemCode_IsKind1)

/* func_0204bcb4: the code 0xf031, one of the kind 0xf codes next to "nothing". */
BOOL ItemCode_IsF031(const ItemCode *item)
{
    return ItemCode_Get(item) == 0xf031;
}
CLEAN_AS(func_0204bcb4, ItemCode_IsF031)

/* func_0204bc90 */
BOOL ItemCode_IsF031OrFurniture(const ItemCode *item)
{
    return ItemCode_IsF031(item) || ItemCode_IsFurniture(item);
}
CLEAN_AS(func_0204bc90, ItemCode_IsF031OrFurniture)

/* func_0204bcdc: kinds 3 and 4. */
BOOL ItemCode_IsFurniture(const ItemCode *item)
{
    int kind = ItemCode_Kind(item);
    return kind == 3 || kind == 4;
}
CLEAN_AS(func_0204bcdc, ItemCode_IsFurniture)

/* func_0204bcd4. QUIRK: tests the code and drops the answer. */
void ItemCode_TestIsFurniture(const ItemCode *item)
{
    (void) ItemCode_IsFurniture(item);
}
CLEAN_AS(func_0204bcd4, ItemCode_TestIsFurniture)

/* func_0204bc64: the furniture item without its side, numbered from 0x3000 (0-0x7ff for kinds 3 and 4).
 * REQUIRES: a code of kind 3 or 4; the callers test that first. Lower codes give a negative
 * number, rounded down as the ARM's shift does. */
int ItemCode_FurnitureNumber(const ItemCode *item)
{
    return shift_right(ItemCode_Get(item) - ITEM_CODE_FURNITURE_BASE, 2);
}
CLEAN_AS(func_0204bc64, ItemCode_FurnitureNumber)

/* func_0204bc7c: the low two bits, whatever the kind. */
int ItemCode_Side(const ItemCode *item)
{
    return ItemCode_Get(item) & 3;
}
CLEAN_AS(func_0204bc7c, ItemCode_Side)

/* func_0204bc50. QUIRK: neither number is checked; a side past 3 runs into the next item. */
u16 ItemCode_MakeFurniture(int item, int side)
{
    return (u16) ((u32) item * 4 + ITEM_CODE_FURNITURE_BASE + (u32) side);
}
CLEAN_AS(func_0204bc50, ItemCode_MakeFurniture)

/* func_0204bc28: codes of other kinds are left as they are. */
void ItemCode_SetSide(ItemCode *item, int side)
{
    if (ItemCode_IsFurniture(item)) {
        *item = ItemCode_MakeFurniture(ItemCode_FurnitureNumber(item), side);
    }
}
CLEAN_AS(func_0204bc28, ItemCode_SetSide)

/* func_0204b268 */
BOOL ItemCode_IsPile(const ItemCode *item)
{
    return *item >= ITEM_CODE_PILE_FIRST && *item <= ITEM_CODE_PILE_LAST;
}
CLEAN_AS(func_0204b268, ItemCode_IsPile)

/* func_0204b260. QUIRK: tests the code and drops the answer. */
void ItemCode_TestIsPile(const ItemCode *item)
{
    (void) ItemCode_IsPile(item);
}
CLEAN_AS(func_0204b260, ItemCode_TestIsPile)

/* func_0204bd20: an item past the 64 becomes the first.
 * QUIRK: the count is taken modulo 4, so a count of 0 makes a pile of 4. */
u16 ItemCode_MakePile(u32 item, u32 count)
{
    if (item >= ITEM_CODE_PILE_ITEMS) {
        item = 0;
    }
    return (u16) (ITEM_CODE_PILE_FIRST + item * 4 + ((count - 1) & 3));
}
CLEAN_AS(func_0204bd20, ItemCode_MakePile)

/* func_0204bd40: 1 to 4.
 * QUIRK: the range is not checked; any code gives a count from its low two bits. */
int ItemCode_PileCount(const ItemCode *item)
{
    return ((ItemCode_Get(item) - ITEM_CODE_PILE_FIRST) & 3) + 1;
}
CLEAN_AS(func_0204bd40, ItemCode_PileCount)

/* func_0204bd5c: 0-63, or -1 for a code outside the piles. */
int ItemCode_PileItem(const ItemCode *item)
{
    if (!ItemCode_IsPile(item)) {
        return -1;
    }
    return (ItemCode_Get(item) - ITEM_CODE_PILE_FIRST) >> 2;
}
CLEAN_AS(func_0204bd5c, ItemCode_PileItem)

static_assert(sizeof(ItemCode) == 2, "item code size");
