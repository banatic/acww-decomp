/* The four items one of the town's villagers keeps at 0x7b0 (VillagerTown, villager_town.h),
 * 0xfff1 for an empty place.
 *
 * Items are kept packed to the front (VillagerItems_Pack); a new one goes into the first empty
 * place, or when all four are taken pushes the oldest (the first) out. Every change is sent to
 * the other systems of a linked session (SessionVillager_SendItems, session_villager.h). An
 * item of kind 3 or 4 matches whatever its variant (func_0204bc64). */
#ifndef CLEAN_MAIN_VILLAGER_ITEMS_H
#define CLEAN_MAIN_VILLAGER_ITEMS_H

#include "types.h"

#define VILLAGER_ITEMS_COUNT 4
#define VILLAGER_ITEMS_NONE 0xfff1
#define VILLAGER_ITEMS_NOT_FOUND (-1)

void VillagerItems_MostValuable(u16 *out, u8 *villager);
void VillagerItems_Random(u16 *out, u8 *villager);
int VillagerItems_Remove(u8 *villager, u16 *item);
int VillagerItems_Find(u8 *villager, u16 *item);
void VillagerItems_Add(u8 *villager, u16 *item);
void VillagerItems_Pack(u8 *villager);
u16 *VillagerItems_At(u8 *villager, unsigned int index);
void VillagerItems_Clear(u8 *villager);

#endif
