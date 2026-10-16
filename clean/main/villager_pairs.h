/* Questions about two of the town's villagers, from how well they get on (the town's table at
 * 0x3f60, villager_bonds.h): the villager a villager gets on best or worst with, the tier of a
 * pair, and changes to a pair's bond. */
#ifndef CLEAN_MAIN_VILLAGER_PAIRS_H
#define CLEAN_MAIN_VILLAGER_PAIRS_H

#include "npc_id.h"
#include "types.h"

/* The tiers VillagerPair_Tier gives: 0 the best, 3 the worst, 4 none. */
#define VILLAGER_PAIR_TIERS 4

typedef struct VillagerTown VillagerTown;

/* What VillagerPair_Pick asks of a score: whether `score` beats `best`. */
typedef int (*VillagerPairBetter)(int best, int score);

u8 *VillagerPair_WorstFor(VillagerTown *town, u8 *villager);
u8 *VillagerPair_BestFor(VillagerTown *town, u8 *villager);
int VillagerPair_IsLower(int best, int score);
int VillagerPair_IsHigher(int best, int score);
u8 *VillagerPair_Pick(VillagerTown *town, u8 *villager, VillagerPairBetter *better, int start);
void VillagerPair_AddBond(VillagerTown *town, const NpcId *first, const NpcId *second, int amount);
int VillagerPair_TierOf(VillagerTown *town, u8 *first, u8 *second);
int VillagerPair_Tier(VillagerTown *town, int first, int second);

#endif
