/* The errand each villager is given in its entry of the running state table: the type (byte
 * 0x0a) of the entry's errand (VillagerState_Errand, villager_state.h; villager_errand.h).
 *
 * A type is 0-21, and 22 for none. Types 0-4 form group 0 and types 5-21 group 1
 * (VillagerErrand_GroupOfType, 2 for none); VillagerErrand_PlaceInGroupOfType gives a type's
 * place within its group. The game hands out the 17 types of group 1 so that no two villagers
 * share one (VillagerErrands_Deal), when more than half of the villagers that can take one have
 * none (VillagerErrands_DealIfNeeded). A villager's type is found by VillagerErrands_TypeOf. */
#ifndef CLEAN_MAIN_VILLAGER_ERRANDS_H
#define CLEAN_MAIN_VILLAGER_ERRANDS_H

#include "npc_id.h"
#include "types.h"

#define VILLAGER_ERRANDS_NONE 22
#define VILLAGER_ERRANDS_GROUP_1 1
#define VILLAGER_ERRANDS_GROUP_1_FIRST 5
#define VILLAGER_ERRANDS_GROUP_1_COUNT 17

typedef struct VillagerTown VillagerTown;

void VillagerErrands_DealIfNeeded(VillagerTown *town);
void VillagerErrands_Deal(VillagerTown *town);
void VillagerErrands_ClearAll(void);
int VillagerErrands_IsDealNeeded(VillagerTown *town);
int VillagerErrands_TypeOf(VillagerTown *town, u8 *villager, void *record);
int VillagerErrands_KnownType(VillagerTown *town, u8 *villager, void *record);

#endif
