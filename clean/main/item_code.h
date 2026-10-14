/* Item codes: the 16-bit value the game stores for an item in pockets, on the map and in the
 * actor table. The top four bits are the kind (0xfff1 is "nothing", kind 0xf). The helpers
 * here read and write a code through a pointer to it, as the game passes them. */
#ifndef CLEAN_MAIN_ITEM_CODE_H
#define CLEAN_MAIN_ITEM_CODE_H

#include "lookups.h" /* ItemCode */
#include "types.h"

/* The code of "nothing": an empty pocket, an empty tile, a free actor table entry. */
#define ITEM_CODE_NONE 0xfff1

/* Kind 1 codes 0x1000-0x10ff: 64 items, each in a pile of 1 to 4 (the low two bits are the
 * count less one). */
#define ITEM_CODE_PILE_FIRST 0x1000
#define ITEM_CODE_PILE_LAST 0x10ff
#define ITEM_CODE_PILE_ITEMS 64

/* Kind 3 and 4 codes 0x3000-0x4fff: one numbering in steps of four, the low two bits a variant
 * of the item (func_0204bc28 changes it in place). */
#define ITEM_CODE_VARIANT_BASE 0x3000

/* func_0204b42c */
int ItemCode_Get(const ItemCode *item);
/* func_0204b79c */
void ItemCode_Set(ItemCode *item, int code);
/* func_0204bf18 */
void ItemCode_Copy(ItemCode *dst, const ItemCode *src);
/* func_0204b48c */
BOOL ItemCode_InRange(const ItemCode *item, u16 first, u16 last);
/* func_0204bcf8 */
int ItemCode_Kind(const ItemCode *item);
/* func_0204bd08 */
BOOL ItemCode_IsKind1(const ItemCode *item);
/* func_0204bcb4 */
BOOL ItemCode_IsF031(const ItemCode *item);
/* func_0204bc90 */
BOOL ItemCode_IsF031OrVariant(const ItemCode *item);

/* func_0204bcdc */
BOOL ItemCode_HasVariant(const ItemCode *item);
/* func_0204bcd4 */
void ItemCode_TestHasVariant(const ItemCode *item);
/* func_0204bc64 */
int ItemCode_VariantItem(const ItemCode *item);
/* func_0204bc7c */
int ItemCode_Variant(const ItemCode *item);
/* func_0204bc50 */
u16 ItemCode_MakeVariant(int item, int variant);
/* func_0204bc28 */
void ItemCode_SetVariant(ItemCode *item, int variant);

/* func_0204b268 */
BOOL ItemCode_IsPile(const ItemCode *item);
/* func_0204b260 */
void ItemCode_TestIsPile(const ItemCode *item);
/* func_0204bd20 */
u16 ItemCode_MakePile(u32 item, u32 count);
/* func_0204bd40 */
int ItemCode_PileCount(const ItemCode *item);
/* func_0204bd5c */
int ItemCode_PileItem(const ItemCode *item);

#endif
