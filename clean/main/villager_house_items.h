/* What one of the town's villagers keeps in its house (villager_furniture.h): which of its ten
 * item places an item goes to, which item gives way, and the room the house is built from.
 *
 * The ten places (0x78c, 0xfff1 for none) are split by the size class of an item of kind 3 or
 * 4 (func_02053bc0, byte 5 of the item's data):
 *
 *   class 0  places 5-9
 *   class 1  places 1-4; 3-4 for a villager in mode 2 (or mode 8 reached from mode 2)
 *   class 2  place 0; 0-2 for a villager in mode 2 (or mode 8 reached from mode 2)
 *
 * The villager's mode (villager_mode.h) also picks what it likes to keep: in modes 0-4 an item
 * "fits" when the filter for the mode accepts it (VillagerHouseItems_FitsMode):
 *
 *   mode 0  (an insect caught)   items 0x12b0-0x12e7 (museum_record.h, group C)
 *   mode 1  (a fish caught)      items 0x12e8-0x131f (group B)
 *   mode 2  (item 0x1549)        items 0x450c-0x45db (group A)
 *   mode 3                       items 0x11a8-0x12a7
 *   mode 4                       items of kind 3 or 4 outside group A that func_02080834 likes
 *
 * Every item fits in the other modes. An item that gives way goes to the town's list of 15
 * items (data_021f3a86, func_0203a6ec) when there is room, or, from VillagerHouseItems_MaybeGiveUp,
 * only half of the time. */
#ifndef CLEAN_MAIN_VILLAGER_HOUSE_ITEMS_H
#define CLEAN_MAIN_VILLAGER_HOUSE_ITEMS_H

#include "ov004/member_pointer.h"
#include "types.h"

#define VILLAGER_HOUSE_ITEMS 10
#define VILLAGER_HOUSE_ITEM_NONE 0xfff1
#define VILLAGER_HOUSE_NO_SLOT (-1)
/* The size classes of an item of kind 3 or 4. */
#define VILLAGER_HOUSE_CLASSES 3
/* The first room model (0x1010-0x1014). */
#define VILLAGER_HOUSE_ROOM_FIRST 0x1010

void VillagerHouseItems_ReplacementFor(u16 *out, const u8 *villager, const u16 *item);
void VillagerHouseItems_ClearSlots1And2(u8 *villager);
void VillagerHouseItems_GiveAwayOne(u8 *villager);
int VillagerHouseItems_Count(const u8 *villager);
int VillagerHouseItems_CountSame(const u8 *villager, const u16 *item);
int VillagerHouseItems_Store(u8 *villager, u16 *item);
int VillagerHouseItems_StoreGroupA(u8 *villager, u16 *item, int size_class, int mode, u8 from_2, u8 fits);
int VillagerHouseItems_GroupAPlace(const u8 *villager, const u16 *item);
int VillagerHouseItems_MakeRoom(u8 *villager, int size_class, int mode, int from_2, u8 fits);
int VillagerHouseItems_MaybeGiveUp(const u16 *item);
int VillagerHouseItems_GiveUp(const u16 *item);
int VillagerHouseItems_PickUnfitting(u8 *villager, int mode, int first, int end);
int VillagerHouseItems_FitsMode(u8 *villager, u16 *item, u32 mode);
MemberPointer VillagerHouseItems_ModeFilter(u32 villager, u32 mode);
int VillagerHouseItems_FitsMode4(u8 *villager, u16 *item);
int VillagerHouseItems_FitsMode3(const u8 *villager, const u16 *item);
int VillagerHouseItems_FitsMode2(const u8 *villager, const u16 *item);
int VillagerHouseItems_FitsMode1(const u8 *villager, const u16 *item);
int VillagerHouseItems_FitsMode0(const u8 *villager, const u16 *item);
int VillagerHouseItems_PickCheapest(u8 *villager, int first, int end);
int VillagerHouseItems_PickEmpty(u8 *villager, int first, int end);
int VillagerHouseItems_SlotRange(const u8 *villager, int *first, int *end, int size_class, int mode, u8 from_2);
u16 *VillagerHouseItems_Items(u8 *villager);
void VillagerHouseItems_Get(u16 *out, const u8 *villager, int slot);
int VillagerHouseItems_SlotOfCode(const u8 *villager, const u16 *code);
int VillagerHouseItems_IsSlot(const u8 *villager, u32 slot);
int VillagerHouseItems_RoomModel(const u8 *villager);
int VillagerHouseItems_Template(u8 *villager, int *template_set, int *variant);

#endif
