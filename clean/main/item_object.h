/* An object of 12 bytes that the villagers' records keep (the villager's object at 0x24 of the
 * record at 0x734, villager_object.h; the blocks of a player's villager part, villager_part.h;
 * the state table's entries, villager_kinds.h; system commands, system_command.c):
 *
 *   0x00  a date (ItemObject_StampNow sets it; constructing the object zeroes it)
 *   0x08  an item (0xfff1: none)
 *   0x0a  a type: 0-21, 22 for none (ItemObject_IsInUse)
 *   0x0b  two fields: bits 0-4 (ItemObject_Low5) and bits 5-7 (ItemObject_High3)
 *
 * The types fall into groups in two ways:
 *   - groups 0 (types 0-4) and 1 (types 5-21), 2 for none (ItemObject_GroupOfType), with a
 *     place within the group from the group's first type (data_020d1a40: 0, 5);
 *   - classes 0 (types 0-9), 1 (10-19), 2 (20) and 3 (21), 4 for none (ItemObject_ClassOfType),
 *     with a place from the class's first type (data_020d1a6c: 0, 10, 20, 21). Class 1 is split
 *     further by ItemObject_StepBandOfType and ItemObject_Class1SplitOfType. */
#ifndef CLEAN_MAIN_ITEM_OBJECT_H
#define CLEAN_MAIN_ITEM_OBJECT_H

#include "calendar.h"
#include "types.h"

#define ITEM_OBJECT_NO_ITEM 0xfff1
#define ITEM_OBJECT_TYPE_NONE 22

typedef struct ItemObject {
    DateTime date; /* 0x00 */
    u16 item;      /* 0x08 */
    u8 type;       /* 0x0a */
    u8 bits;       /* 0x0b: bits 0-4 and 5-7 */
} ItemObject;

void ItemObject_SetItem(ItemObject *object, const u16 *item);
u16 *ItemObject_Item(ItemObject *object);
void ItemObject_SetHigh3(ItemObject *object, u32 value);
int ItemObject_High3(ItemObject *object);
void ItemObject_SetLow5(ItemObject *object, int value);
int ItemObject_Low5(ItemObject *object);
int ItemObject_StepBand(ItemObject *object);
int ItemObject_StepBandOfType(u32 type);
u8 ItemObject_Class1Split(ItemObject *object);
int ItemObject_Class1SplitOfType(u32 type);
DateTime *ItemObject_Date(ItemObject *object);
void ItemObject_StampNow(ItemObject *object, int minutes);
int ItemObject_Type(ItemObject *object);
int ItemObject_PlaceInClass(ItemObject *object, int *place);
int ItemObject_PlaceInClassOfType(int *place, int type);
int ItemObject_Class(ItemObject *object);
int ItemObject_ClassOfType(u32 type);
int ItemObject_IsClass(u32 class_);
int ItemObject_PlaceInGroup(ItemObject *object, int *place);
int ItemObject_PlaceInGroupOfType(int *place, int type);
int ItemObject_Group(ItemObject *object);
int ItemObject_GroupOfType(u32 type);
int ItemObject_IsGroup(u32 group);
void ItemObject_Set(ItemObject *object, u8 type, const u16 *item, u8 low5);
int ItemObject_IsInUse(ItemObject *object);
int ItemObject_IsType(u32 type);
void ItemObject_Clear(ItemObject *object);
void ItemObject_Destruct(ItemObject *object);
void ItemObject_Construct(ItemObject *object);

#endif
