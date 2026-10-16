/* Items by their attributes in the item table (func_020535f0 and its neighbours).
 *
 * The items 0x450c-0x45db are 52 items in steps of four (the low two bits a variant); each has
 * a kind (func_020535f0, 0 for other codes). Ten of the kinds are listed in data_020d1a60 (22,
 * 23, 10, 11, 12, 13, 15, 16, 21, 20); a villager's object keeps one of them
 * (villager_object.h). A villager also names an attribute and a value of it (func_02080834),
 * which an item matches by ItemAttributes_Match. */
#ifndef CLEAN_MAIN_ITEM_ATTRIBUTES_H
#define CLEAN_MAIN_ITEM_ATTRIBUTES_H

#include "types.h"

#define ITEM_ATTRIBUTES_KIND_ITEM_FIRST 0x450c
#define ITEM_ATTRIBUTES_KIND_ITEM_LAST 0x45db
#define ITEM_ATTRIBUTES_KIND_ITEMS 0x34
#define ITEM_ATTRIBUTES_KINDS 10

int ItemAttributes_Match(u16 *item, int attribute, int value);
void ItemAttributes_KindItem(u16 *out, u32 kind, u32 offset);
u8 ItemAttributes_PickMissingKind(u16 *items, int count);
int ItemAttributes_KindIndex(int kind);

#endif
