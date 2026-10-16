/* The kind each villager is given in its entry of the running state table: the type (byte
 * 0x0a) of the entry's object (VillagerState_Object, villager_state.h).
 *
 * A type is 0-21, and 22 for none. Types 0-4 form group 0 and types 5-21 group 1
 * (func_0209bd10, 2 for none); func_0209bcd4 gives a type's place within its group. The
 * game hands out the 17 types of group 1 so that no two villagers share one
 * (VillagerKind_Deal), when more than half of the villagers that can take one have none
 * (VillagerKind_DealIfNeeded). A villager's type is found by VillagerKind_Of. */
#ifndef CLEAN_MAIN_VILLAGER_KINDS_H
#define CLEAN_MAIN_VILLAGER_KINDS_H

#include "npc_id.h"
#include "types.h"

#define VILLAGER_KIND_NONE 22
#define VILLAGER_KIND_GROUP_1 1
#define VILLAGER_KIND_GROUP_1_FIRST 5
#define VILLAGER_KIND_GROUP_1_COUNT 17

typedef struct VillagerTown VillagerTown;

void VillagerKind_DealIfNeeded(VillagerTown *town);
void VillagerKind_Deal(VillagerTown *town);
void VillagerKind_ClearAll(void);
int VillagerKind_IsDealNeeded(VillagerTown *town);
int VillagerKind_Of(VillagerTown *town, u8 *villager, void *record);
int VillagerKind_Known(VillagerTown *town, u8 *villager, void *record);

#endif
