/* Tests of one of the town's villagers (VillagerTown, villager_town.h) that other code picks
 * villagers by: whether it lives in the town and is not the one planning to move away, whether
 * no player's record holds an object for it, and whether it is the villager the running state
 * table (villager_state.h) names at 0x160 or 0x161. */
#ifndef CLEAN_MAIN_VILLAGER_CHECKS_H
#define CLEAN_MAIN_VILLAGER_CHECKS_H

#include "types.h"

int VillagerCheck_IsStayingResident(u8 *villager);
int VillagerCheck_NoPlayerHolds(u8 *villager);
int VillagerCheck_IsIndex161(u8 *villager);
void VillagerCheck_ClearIndex160IfSelf(u8 *villager);
int VillagerCheck_IsIndex160(u8 *villager);

#endif
