/* Items by their attributes in the item table (item_attributes.h). */
#include "item_attributes.h"

#include "clean.h"
#include "furniture_info.h"
#include "item_code.h"
#include "main_random.h"

#define ITEM_ATTRIBUTES_NONE 0xfff1
/* The attributes ItemAttributes_Match compares. */
enum {
    ITEM_ATTRIBUTE_0 = 0, /* func_020539e4 */
    ITEM_ATTRIBUTE_1 = 1, /* func_02053cf0 and func_02053cbc of the item without its variant */
    ITEM_ATTRIBUTE_2 = 2, /* func_02053a88 */
    ITEM_ATTRIBUTE_3 = 3, /* func_02053b6c */
    ITEM_ATTRIBUTE_4 = 4  /* func_02053c68 */
};
/* What a match is worth: a whole one, or each of attribute 1's two halves. */
#define ITEM_ATTRIBUTES_FULL 2
#define ITEM_ATTRIBUTES_HALF 1

extern const u8 data_020d1a60[ITEM_ATTRIBUTES_KINDS]; /* the ten kinds */

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* The index-th item of the kinds' items; the first one past the end. */
static u16 item_attributes_kind_item(u32 index)
{
    return index < ITEM_ATTRIBUTES_KIND_ITEMS ? (u16) (ITEM_ATTRIBUTES_KIND_ITEM_FIRST + index * 4)
                                              : ITEM_ATTRIBUTES_KIND_ITEM_FIRST;
}

/* func_0209b6c0: how well an item with a variant matches `value` of attribute `attribute`: 2 for
 * a match, or for attribute 1 one for each of its two halves that matches; 0 for other codes and
 * attributes. */
int ItemAttributes_Match(u16 *item, int attribute, int value)
{
    int score = 0;
    if (ItemCode_HasVariant(item) == 0) {
        return score;
    }
    switch (attribute) {
        case ITEM_ATTRIBUTE_0:
            if (value == FurnitureInfo_ItemFlagBits23(item)) {
                score = ITEM_ATTRIBUTES_FULL;
            }
            break;
        case ITEM_ATTRIBUTE_1: {
            int base = ItemCode_VariantItem(item);
            if (value == FurnitureInfo_Unk01(base)) {
                score = ITEM_ATTRIBUTES_HALF;
            }
            if (value == FurnitureInfo_Unk02(base)) {
                score += ITEM_ATTRIBUTES_HALF;
            }
            break;
        }
        case ITEM_ATTRIBUTE_2:
            if (value == FurnitureInfo_ItemFlagBits01(item)) {
                score = ITEM_ATTRIBUTES_FULL;
            }
            break;
        case ITEM_ATTRIBUTE_3:
            if (value == FurnitureInfo_ItemUnk03(item)) {
                score = ITEM_ATTRIBUTES_FULL;
            }
            break;
        case ITEM_ATTRIBUTE_4:
            if (value == FurnitureInfo_ItemGroup(item)) {
                score = ITEM_ATTRIBUTES_FULL;
            }
            break;
        default:
            break;
    }
    return score;
}
CLEAN_AS(func_0209b6c0, ItemAttributes_Match)

/* func_0209b750: into `out` the first of the items 0x450c-0x45db of kind `kind`, moved on by
 * `offset` items (0x450c when that passes the end); 0xfff1 when no item is of the kind. */
void ItemAttributes_KindItem(u16 *out, u32 kind, u32 offset)
{
    *out = ITEM_ATTRIBUTES_NONE;
    for (u32 i = 0; i < ITEM_ATTRIBUTES_KIND_ITEMS; i++) {
        u16 item = item_attributes_kind_item(i);
        if ((u32) FurnitureInfo_MuseumKind(&item) == kind) {
            *out = item_attributes_kind_item(i + offset);
            return;
        }
    }
}
CLEAN_AS(func_0209b750, ItemAttributes_KindItem)

/* func_0209b7ac: one of the ten kinds drawn at random among those none of the `count` items
 * is of.
 * REQUIRES: the items leave at least one of the ten kinds out.
 * BUG: when they cover all ten, the original reads on past its ten flags into its stack, and
 * then past the kinds' table; Clean gives 0, what it gives when the first byte after the flags
 * is 0. */
u8 ItemAttributes_PickMissingKind(u16 *items, int count)
{
    int left = ITEM_ATTRIBUTES_KINDS;
    u8 seen[ITEM_ATTRIBUTES_KINDS];
    MI_CpuFill8(seen, 0, ITEM_ATTRIBUTES_KINDS);
    for (int i = 0; i < count; i++, items++) {
        if (*items < ITEM_ATTRIBUTES_KIND_ITEM_FIRST || *items > ITEM_ATTRIBUTES_KIND_ITEM_LAST) {
            continue;
        }
        for (int j = 0; j < ITEM_ATTRIBUTES_KINDS; j++) {
            if (FurnitureInfo_MuseumKind(items) == data_020d1a60[j] && seen[j] == 0) {
                seen[j] = 1;
                left--;
                break;
            }
        }
    }

    int n = MainRandom_Below(left);
    int k = 0;
    while (n >= 0) {
        if (k >= ITEM_ATTRIBUTES_KINDS) {
            return 0;
        }
        if (seen[k] == 0) {
            if (n == 0) {
                break;
            }
            n--;
        }
        k++;
    }
    return data_020d1a60[k];
}
CLEAN_AS(func_0209b7ac, ItemAttributes_PickMissingKind)

/* func_0209b850: the index of `kind` among the ten kinds, or -1. */
int ItemAttributes_KindIndex(int kind)
{
    for (int i = 0; i < ITEM_ATTRIBUTES_KINDS; i++) {
        if (kind == data_020d1a60[i]) {
            return i;
        }
    }
    return -1;
}
CLEAN_AS(func_0209b850, ItemAttributes_KindIndex)
