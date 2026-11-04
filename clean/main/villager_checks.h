/* Tests of one of the town's villagers (VillagerTown, villager_town.h) that other code picks
 * villagers by: whether it lives in the town and is not the sick one, whether no player's
 * record holds an object for it, and whether it is the villager with fleas or the one that
 * tells the fox's password, as the running state table (villager_state.h) names them at 0x160
 * and 0x161. */
#ifndef CLEAN_MAIN_VILLAGER_CHECKS_H
#define CLEAN_MAIN_VILLAGER_CHECKS_H

#include "types.h"

int VillagerCheck_IsWellResident(u8 *villager);
int VillagerCheck_NoPlayerHolds(u8 *villager);
int VillagerCheck_TellsFoxPassword(u8 *villager);
void VillagerCheck_ClearFleasIfSelf(u8 *villager);
int VillagerCheck_HasFleas(u8 *villager);

#endif
