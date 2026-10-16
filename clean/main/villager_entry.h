/* One of the town's villagers (0x7ec bytes, eight at data_021e5a2c, villager_town.h): what is
 * done to a single villager that has a valid NpcId.
 *
 *   0x000  eight memories of players (0x80 bytes each, func_020807a8): the signed byte 0x6c how
 *          fond the villager is of the player, the halfword 0x7c flags
 *   0x78c  ten item codes (0xfff1: none)
 *   0x7a0  its NpcId
 *   0x7d0  one bit for each of the ten items: the items marked (VillagerEntry_MarkItems)
 *
 * Its entry of the running state table (villager_state.h, func_0207f270) has a byte at 0x1e
 * from 0 to 32 that the functions here raise, halve, double, clear and set from how fond the
 * villager is of a player. */
#ifndef CLEAN_MAIN_VILLAGER_ENTRY_H
#define CLEAN_MAIN_VILLAGER_ENTRY_H

#include "calendar.h"
#include "types.h"

#define VILLAGER_ENTRY_ITEMS 10
#define VILLAGER_ENTRY_MEMORIES 8
#define VILLAGER_ENTRY_MEMORY_SIZE 0x80
#define VILLAGER_ENTRY_BYTE_1E_MAX 32

void VillagerEntry_AddByte1E(u8 *villager, int amount);
void VillagerEntry_DoubleByte1E(u8 *villager);
void VillagerEntry_HalveByte1E(u8 *villager);
void VillagerEntry_ClearByte1E(u8 *villager);
int VillagerEntry_IsByte1EFull(u8 *villager, void *record);
void VillagerEntry_RaiseByte1E(u8 *villager, void *record);
int VillagerEntry_IsByte18Low(u8 *villager);
void VillagerEntry_SetByte1E(u8 *villager, void *record);
int VillagerEntry_NoteVisitor(u8 *villager, void *record);
void VillagerEntry_FlagMemory(u8 *villager, const void *player);
int VillagerEntry_IsSleepTime(u8 *villager, const DateTime *when);
void VillagerEntry_ClearMemoryFlag6(u8 *villager);
void VillagerEntry_UnmarkItem(u8 *villager, int item);
int VillagerEntry_IsItemMarked(u8 *villager, int item);
void VillagerEntry_MarkItems(u8 *villager);

#endif
