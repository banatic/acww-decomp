/* How a chat between two villagers out walking in the town (behaviour 9,
 * outdoor_villager_chat.h) changes the town: the bonds of the town's pairs of villagers (the
 * town's table, main's villager_pairs.h), the moods of the two, and the order the pair is
 * taken in. Also two of the chat's seven exchanges, the ones that only touch bonds and moods.
 *
 * A bond changes by an amount drawn from a table of five signed bytes, one for each tier of
 * the pair (VillagerPair_Tier: 0 the best, 3 the worst, 4 none). A chat changes the pair's own
 * bond (OutdoorVillagerBonds_ChangePair) or, as gossip, the bond of two other villagers of the
 * town drawn at random (OutdoorVillagerBonds_ChangeOthers).
 *
 * The two exchanges here first sort the pair (OutdoorVillagerBonds_Sort: the one fonder of the
 * current player first) and make the second learn from the first, as the others do:
 * - learn: gossip that lowers the bond of two others (data_ov068_02276764: -6, -10, -16, -8,
 *   -2), and both moods asked for (0, 0) and applied;
 * - talk about how they get on: gossip that raises the bond of two others
 *   (data_ov068_0227674c: 2, 8, 16, 10, 6); then by the pair's own tier (VillagerPair_TierOf)
 *   both moods asked for (1, 2) when they get on well (0, 1), one of the moods 2 and 3 when they
 *   get on badly (3, 4), nothing at tier 2. */
#ifndef CLEAN_OV068_OUTDOOR_VILLAGER_BONDS_H
#define CLEAN_OV068_OUTDOOR_VILLAGER_BONDS_H

#include "main/npc_id.h"
#include "outdoor_villager.h"
#include "types.h"

/* The amounts of a bond change: one for each tier, 0 to 4. */
#define OUTDOOR_VILLAGER_BONDS_TIERS 5

int OutdoorVillagerBonds_TalkOfBond(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerBonds_Learn(OutdoorVillagerBehaviour *self, u8 *villager);
u8 *OutdoorVillagerBonds_DrawShopDesign(OutdoorVillagerBehaviour *self, u8 *design);
int OutdoorVillagerBonds_Sort(OutdoorVillagerBehaviour *self, u8 **first, u8 **second, u8 *a, u8 *b);
void OutdoorVillagerBonds_AskMoodOf(OutdoorVillagerBehaviour *self, u8 *villager, const u8 *moods, int count, u8 units,
                                    u8 apply);
void OutdoorVillagerBonds_AskMood(OutdoorVillagerBehaviour *self, u8 *villager, int which, int units, u8 apply);
void OutdoorVillagerBonds_ChangeOthers(OutdoorVillagerBehaviour *self, u8 *villager, const s8 *amounts);
void OutdoorVillagerBonds_ChangePair(OutdoorVillagerBehaviour *self, u8 *villager, const s8 *amounts);
void OutdoorVillagerBonds_Change(OutdoorVillagerBehaviour *self, const NpcId *a, const NpcId *b, const s8 *amounts);
int OutdoorVillagerBonds_PairTier(OutdoorVillagerBehaviour *self, u8 *villager);
int OutdoorVillagerBonds_Tier(const NpcId *a, const NpcId *b);

#endif
