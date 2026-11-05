/* More of the tests of the table of impressions (villager_impression.h, data_020cd5c4): each
 * is called with the player's record, how fond the villager is of the player and the byte 0x18
 * of the villager's state entry, and looks at one of them, the clock, the town or the tiles
 * around the player.
 *
 * The item tests compare a code of the player's looks (player_record.h: the held item, the
 * clothes, the head's item, part C's item) with a code or a range of codes. A code of kind 3 or
 * 4 (func_0204bcdc) matches the wanted one whatever side it faces (ItemCode_FurnitureNumber). */
#ifndef CLEAN_MAIN_VILLAGER_IMPRESSION_TESTS_H
#define CLEAN_MAIN_VILLAGER_IMPRESSION_TESTS_H

#include "types.h"

/* How fond the villager must be at most (VillagerImpression_Hated). */
#define VILLAGER_IMPRESSION_HATED (-80)
/* What PlayerPockets_FreeSlot gives for pockets with no free slot. */
#define VILLAGER_IMPRESSION_NO_FREE_SLOT (-1)
/* VillagerImpression_NearFlowers and VillagerImpression_NearWeeds: how many of the nine
 * tiles around the player must hold one of the codes. */
#define VILLAGER_IMPRESSION_NEAR_FLOWERS 2
#define VILLAGER_IMPRESSION_NEAR_WEEDS 3
/* VillagerImpression_FewVillagers: the most villagers the town may have. */
#define VILLAGER_IMPRESSION_FEW_VILLAGERS 4

int VillagerImpression_Hated(u8 *record, int fondness);
int VillagerImpression_PocketsFull(u8 *record);
int VillagerImpression_IsNight(void);
int VillagerImpression_IsMorning(void);
int VillagerImpression_Clothes12A8(u8 *record);
int VillagerImpression_IsSnowing(void);
int VillagerImpression_IsRaining(void);
int VillagerImpression_HeldUmbrella(u8 *record);
int VillagerImpression_HasFlower(u8 *record);
int VillagerImpression_HeadIs1406(u8 *record);
int VillagerImpression_HeadIs13E4(u8 *record);
int VillagerImpression_HeadIs13E3(u8 *record);
int VillagerImpression_HeadIs13F5(u8 *record);
int VillagerImpression_HeadIs13EA(u8 *record);
int VillagerImpression_HeadIs13E6(u8 *record);
int VillagerImpression_HeadIs1405(u8 *record);
int VillagerImpression_HeadIs13BC(u8 *record);
int VillagerImpression_HeadIs13A8(u8 *record);
int VillagerImpression_HeadIs13B2(u8 *record);
int VillagerImpression_HeadIs13C1(u8 *record);
int VillagerImpression_HeldWateringCan(u8 *record);
int VillagerImpression_HeldRod(u8 *record);
int VillagerImpression_HeldAxe(u8 *record);
int VillagerImpression_HeldNet(u8 *record);
int VillagerImpression_MoodIs2Or4(u8 *record, int fondness, int mood);
int VillagerImpression_MoodIs1(u8 *record, int fondness, int mood);
int VillagerImpression_EventToday(void);
int VillagerImpression_FewVillagers(void);
int VillagerImpression_NearFlowers(void);
int VillagerImpression_NearWeeds(void);
void VillagerImpression_IsStung(u8 *record);

#endif
