/* Questions about two of the town's villagers (villager_pairs.h). */
#include "villager_pairs.h"

#include <stdint.h>

#include "clean.h"
#include "session.h"
#include "villager_bonds.h"
#include "villager_town.h"
#include "actor_table.h"
#include "main_random.h"
#include "town_villager.h"
#include "villager_roster.h"

extern NetSession *data_020ccf94; /* the game's session */
/* The lowest score of each tier, the best first. */
extern const int data_020cd474[VILLAGER_PAIR_TIERS];

/* The game's own tests for VillagerPair_Pick, handed to it as it hands them. */
extern int func_0207ba24(int best, int score);
extern int func_0207ba30(int best, int score);

/* func_0207b9e4: the villager that gets on worst with `villager` (VillagerPair_Pick). */
u8 *VillagerPair_WorstFor(VillagerTown *town, u8 *villager)
{
    VillagerPairBetter better = func_0207ba24;
    return VillagerPair_Pick(town, villager, &better, INT32_MAX);
}
CLEAN_AS(func_0207b9e4, VillagerPair_WorstFor)

/* func_0207ba04: the villager that gets on best with `villager` (VillagerPair_Pick). */
u8 *VillagerPair_BestFor(VillagerTown *town, u8 *villager)
{
    VillagerPairBetter better = func_0207ba30;
    return VillagerPair_Pick(town, villager, &better, INT32_MIN);
}
CLEAN_AS(func_0207ba04, VillagerPair_BestFor)

/* func_0207ba24 */
int VillagerPair_IsLower(int best, int score)
{
    return score < best;
}
CLEAN_AS(func_0207ba24, VillagerPair_IsLower)

/* func_0207ba30 */
int VillagerPair_IsHigher(int best, int score)
{
    return score > best;
}
CLEAN_AS(func_0207ba30, VillagerPair_IsHigher)

/* func_0207ba3c: of the other villagers, the one whose score with `villager`
 * (VillagerBond_Compatibility) `better` finds best, starting from `start`. A later villager of
 * the same score takes the place of the one found with one chance in two. NULL when there is
 * none, or `villager` is not one of the town's. */
u8 *VillagerPair_Pick(VillagerTown *town, u8 *villager, VillagerPairBetter *better, int start)
{
    int index = VillagerRoster_IndexOf(town, TownVillager_NpcId(villager));
    u8 *chosen = NULL;
    int best = start;
    if (!NpcId_IsValid(TownVillager_NpcId(villager)) || !ActorTable_IsKindESlot((u32) index)) {
        return NULL;
    }
    for (int i = 0; i < VILLAGER_TOWN_VILLAGERS; i++) {
        if (i == index || !VillagerRoster_IsFilled(town, i)) {
            continue;
        }
        int score = VillagerBond_Compatibility(town->bonds, index, i);
        if ((*better)(best, score)) {
            chosen = VillagerRoster_At(town, i);
            best = score;
        } else if (score == best && (chosen == NULL || (MainRandom_Below(4) & 1) == 1)) {
            chosen = VillagerRoster_At(town, i);
        }
    }
    return chosen;
}
CLEAN_AS(func_0207ba3c, VillagerPair_Pick)

/* func_0207bae8: `amount` added to the bond of the two villagers the NpcIds name
 * (VillagerBond_Add), unless this system is linked with others. */
void VillagerPair_AddBond(VillagerTown *town, const NpcId *first, const NpcId *second, int amount)
{
    if (Session_IsLinked(data_020ccf94)) {
        return;
    }
    int a = VillagerRoster_IndexOf(town, first);
    int b = VillagerRoster_IndexOf(town, second);
    VillagerBond_Add(town->bonds, a, b, amount);
}
CLEAN_AS(func_0207bae8, VillagerPair_AddBond)

/* func_0207bb30: the tier of two different villagers of the town (VillagerPair_Tier); 4 for
 * the same villager or one not of the town. */
int VillagerPair_TierOf(VillagerTown *town, u8 *first, u8 *second)
{
    int a = VillagerRoster_IndexOf(town, TownVillager_NpcId(first));
    int b = VillagerRoster_IndexOf(town, TownVillager_NpcId(second));
    if (a != b && ActorTable_IsKindESlot((u32) a) && ActorTable_IsKindESlot((u32) b)) {
        return VillagerPair_Tier(town, a, b);
    }
    return VILLAGER_PAIR_TIERS;
}
CLEAN_AS(func_0207bb30, VillagerPair_TierOf)

/* func_0207bb84: the first tier whose lowest score the pair's score reaches; 4 for none. */
int VillagerPair_Tier(VillagerTown *town, int first, int second)
{
    int score = VillagerBond_Compatibility(town->bonds, first, second);
    for (int i = 0; i < VILLAGER_PAIR_TIERS; i++) {
        if (score >= data_020cd474[i]) {
            return i;
        }
    }
    return VILLAGER_PAIR_TIERS;
}
CLEAN_AS(func_0207bb84, VillagerPair_Tier)
