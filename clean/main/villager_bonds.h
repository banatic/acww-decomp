/* How well the town's villagers get on with each other.
 *
 * The town's villagers (data_021e5a2c, eight of 0x7ec bytes) are followed at 0x3f60 by a table
 * of 28 signed bytes, one for each pair of villager indexes: (0,1) to (0,7), then (1,2) to
 * (1,7), and so on to (6,7). Each holds how the two have come to get on, from -128 to 127.
 *
 * VillagerBond_Affinity says how well two villagers suit each other from what they are: their
 * personalities (a 6 x 6 table), the elements of their star signs (a 4 x 4 table), their
 * species (the same, a good pair, a bad pair or other) and 0x3f when both have villager data;
 * from a sum below 200 the difference of the villagers' bytes 4 is taken off. */
#ifndef CLEAN_MAIN_VILLAGER_BONDS_H
#define CLEAN_MAIN_VILLAGER_BONDS_H

#include <stdint.h>

#include "types.h"

#define VILLAGER_BOND_PAIRS 28
/* What VillagerBond_Get gives for no pair. */
#define VILLAGER_BOND_NONE INT32_MIN

int VillagerBond_Compatibility(const s8 *bonds, int first, int second);
int VillagerBond_Affinity(const s8 *bonds, void *first, void *second);
int VillagerBond_ByteDifference(const s8 *bonds, void *first, void *second);
int VillagerBond_BothHaveData(const s8 *bonds, void *first, void *second);
int VillagerBond_SpeciesScore(const s8 *bonds, void *first, void *second);
unsigned char VillagerBond_ElementScore(const s8 *bonds, void *first, void *second);
int VillagerBond_PersonalityScore(const s8 *bonds, const void *first, const void *second);
int VillagerBond_Get(const s8 *bonds, int first, int second);
void VillagerBond_Add(s8 *bonds, int first, int second, int amount);
void VillagerBond_AddAt(s8 *bonds, int index, int amount);
void VillagerBond_ForgetVillager(s8 *bonds, int villager);
int VillagerBond_PairIndex(const s8 *bonds, int first, int second);
int VillagerBond_IsPairIndex(const s8 *bonds, unsigned int index);
void VillagerBond_Clear(s8 *bonds);
void VillagerBond_Destruct(s8 *bonds);
void VillagerBond_Construct(s8 *bonds);

#endif
