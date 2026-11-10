/* Items by their attributes in the item table (func_020535f0 and its neighbors).
 *
 * The items 0x450c-0x45db are the 52 fossils in steps of four (the low two bits the side, as for any furniture);
 * each has a kind (func_020535f0, 0 for other codes), the creature it is of, which the parts of
 * one dinosaur share. Ten of the kinds, all of fossils in several parts, are listed in
 * data_020d1a60 (22, 23, 10, 11, 12, 13, 15, 16, 21, 20); a villager's object keeps one of them
 * (villager_object.h). A villager also has furniture tastes, each an attribute and a value of
 * it (func_02080834), which an item matches by ItemAttributes_Match: 0 the feel (1 quiet, 2
 * cute), 1 the colors, 2 the era (1 modern, 2 old-fashioned), 3 the theme (0 instrument, 1
 * painting, 2 model, 3 plant), 4 the series (0-11). Lookups_SlotIndex numbers the tastes as
 * the 32 lines of st_furniture_taste. */
#ifndef CLEAN_MAIN_ITEM_ATTRIBUTES_H
#define CLEAN_MAIN_ITEM_ATTRIBUTES_H

#include "types.h"

#define ITEM_ATTRIBUTES_FOSSIL_FIRST 0x450c
#define ITEM_ATTRIBUTES_FOSSIL_LAST 0x45db
#define ITEM_ATTRIBUTES_FOSSILS 0x34
#define ITEM_ATTRIBUTES_PART_FOSSIL_KINDS 10

int ItemAttributes_Match(u16 *item, int attribute, int value);
void ItemAttributes_FossilOfKind(u16 *out, u32 kind, u32 offset);
u8 ItemAttributes_PickMissingFossilKind(u16 *items, int count);
int ItemAttributes_FossilKindIndex(int kind);

#endif
