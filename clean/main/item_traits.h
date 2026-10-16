/* What the game asks of an item code beyond its group (item_group.h): the worn pairs, the bag
 * of bells for an amount, the records of item_info.h and furniture_info.h read for an item in
 * any of its forms (item_form.h), the creatures' sizes and values, and the store's price.
 *
 * The worn pairs: the items 0x1408-0x1428 (worn on the head) and 0x1471-0x1491 (worn as part C)
 * are paired by their index and share the codes they are placed as. Of each pair (but the one
 * of index 30, never paired) the head item counts when its always.bin flag bit 1 is set
 * (ItemTraits_IsPairHeadItem), else the part C item does (ItemTraits_IsPairFaceItem); the items
 * that count are numbered in order (ItemTraits_PairHeadItem, ItemTraits_PairFaceItem and the
 * numbers back). ItemInfo_CountSharedPairs counts them. */
#ifndef CLEAN_MAIN_ITEM_TRAITS_H
#define CLEAN_MAIN_ITEM_TRAITS_H

#include "lookups.h" /* ItemCode */
#include "types.h"

void ItemTraits_ConstructCode(ItemCode *item, int code);
void ItemTraits_CopyCode(ItemCode *dst, const ItemCode *src);

int ItemTraits_IsPairHeadItem(const ItemCode *item);
int ItemTraits_IsPairFaceItem(const ItemCode *item);
void ItemTraits_PairFaceItem(ItemCode *out, u32 number);
void ItemTraits_PairHeadItem(ItemCode *out, u32 number);
int ItemTraits_PairFaceNumber(const ItemCode *item);
int ItemTraits_PairHeadNumber(const ItemCode *item);

int ItemTraits_BellBagFor(int bells, int round_up, int *rest);
int ItemTraits_StorePrice(const ItemCode *item);

u32 ItemTraits_ClothStyle(const ItemCode *item);
int ItemTraits_FlagBit4(const ItemCode *item);
int ItemTraits_FlagBit3(const ItemCode *item);
int ItemTraits_HasHeldModel(const ItemCode *item);
int ItemTraits_Class(const ItemCode *item);
int ItemTraits_Unk07(const ItemCode *item);
int ItemTraits_Unk02(const ItemCode *item);
int ItemTraits_IsHeadAUnk07Is8(const ItemCode *item);
int ItemTraits_CarriedNonCreature(const ItemCode *item, ItemCode *out);

u16 ItemTraits_InsectSize(const ItemCode *item);
int ItemTraits_FishValue(const ItemCode *item);
int ItemTraits_FishGroupOrder(const ItemCode *item);

int ItemTraits_StateBlockAddress(void);
int ItemTraits_IsBellBag(const ItemCode *item);
int ItemTraits_MemberPrice(const ItemCode *item);
int ItemTraits_ShopPointsLevel(const u16 *count);
int ItemTraits_Price(const ItemCode *item);
int ItemTraits_SameItem(const ItemCode *a, const ItemCode *b);
u16 ItemTraits_Fruit(u32 index);
int ItemTraits_IsFruit(const ItemCode *item);

#endif
