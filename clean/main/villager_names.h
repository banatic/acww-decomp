/* The name of another of the town's villagers (VillagerTown, villager_town.h) written out for a
 * villager's talk: any other one, the one it gets on worst with, or the one it gets on best
 * with (villager_pairs.h). Nothing is written when there is none. */
#ifndef CLEAN_MAIN_VILLAGER_NAMES_H
#define CLEAN_MAIN_VILLAGER_NAMES_H

#include "types.h"

void VillagerNames_FormatOther(u8 *villager, char *dst);
void VillagerNames_FormatWorstMatch(u8 *villager, char *dst);
void VillagerNames_FormatBestMatch(u8 *villager, char *dst);

#endif
