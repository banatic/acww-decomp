/* The item codes of the town map's objects, numbered from a first code like the groups of
 * item_group.h (the code of a number, the first code for a number past the group; whether a
 * code is in the group; a code's number, -1 for one outside it):
 *
 *   0x5000-0x5021  the buildings (34; acre_tile.h)   MapCode_Building, MapCode_IsBuilding
 *   0x5001-0x5008  the villagers' houses (8, by villager index; villager_plots.h)
 *                                                    MapCode_VillagerHouse
 *   0x500d-0x5010  the store, by its level (4; nook_store.h)
 *                                                    MapCode_Store, MapCode_IsStore,
 *                                                    MapCode_StoreLevel
 *   0x5014-0x501a  the players' house, by its size (7; house_record.c)
 *                                                    MapCode_PlayerHouse, MapCode_IsPlayerHouse
 *   0xb001-0xb003  the snowmen (3; snowman.h)        MapCode_Snowman, MapCode_IsSnowman,
 *                                                    MapCode_SnowmanIndex
 *
 * and the special codes 0xf030 (a tile a building covers), 0xf031, 0xfffd, 0xfffe and 0xffff. */
#ifndef CLEAN_MAIN_MAP_CODE_H
#define CLEAN_MAIN_MAP_CODE_H

#include "types.h"

u16 MapCode_PlayerHouse(u32 size);
int MapCode_IsPlayerHouse(const u16 *code);
u16 MapCode_Snowman(u32 index);
int MapCode_IsSnowman(const u16 *code);
int MapCode_SnowmanIndex(const u16 *code);
u16 MapCode_Store(u32 level);
int MapCode_IsStore(const u16 *code);
int MapCode_StoreLevel(const u16 *code);
u16 MapCode_VillagerHouse(u32 villager);
u16 MapCode_Building(u32 index);
int MapCode_IsBuilding(const u16 *code);
int MapCode_IsBuildingOrCovered(const u16 *code);
int MapCode_IsSpecial(const u16 *code);
int MapCode_IsFfff(const u16 *code);

#endif
