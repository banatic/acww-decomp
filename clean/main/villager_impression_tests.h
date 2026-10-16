/* More of the tests of the table of impressions (villager_impression.h, data_020cd5c4): each
 * is called with the player's record, how fond the villager is of the player and the byte 0x18
 * of the villager's state entry, and looks at one of them, the clock, the town or the tiles
 * around the player.
 *
 * The item tests compare a code of the player's looks (player_record.h: the held item, the
 * clothes, the head's item, part C's item) with a code or a range of codes. A code of kind 3 or
 * 4 (func_0204bcdc) matches the wanted one whatever its variant (func_0204bc64). */
#ifndef CLEAN_MAIN_VILLAGER_IMPRESSION_TESTS_H
#define CLEAN_MAIN_VILLAGER_IMPRESSION_TESTS_H

#include "types.h"

/* How fond the villager must be at most (VillagerImpression_Hated). */
#define VILLAGER_IMPRESSION_HATED (-80)
/* What PlayerPockets_FreeSlot gives for pockets with no free slot. */
#define VILLAGER_IMPRESSION_NO_FREE_SLOT (-1)
/* VillagerImpression_NearFamilyAC and VillagerImpression_NearCodes21To24: how many of the nine
 * tiles around the player must hold one of the codes. */
#define VILLAGER_IMPRESSION_NEAR_FAMILY_AC 2
#define VILLAGER_IMPRESSION_NEAR_CODES_21 3
/* VillagerImpression_FewVillagers: the most villagers the town may have. */
#define VILLAGER_IMPRESSION_FEW_VILLAGERS 4

int VillagerImpression_Hated(u8 *record, int fondness);
int VillagerImpression_PocketsFull(u8 *record);
int VillagerImpression_IsNight(void);
int VillagerImpression_IsMorning(void);
int VillagerImpression_Clothes12A8(u8 *record);
int VillagerImpression_State8AB0Is2(void);
int VillagerImpression_State8AB0Is1(void);
int VillagerImpression_Held1380(u8 *record);
int VillagerImpression_Held137COrHeadOrPartC(u8 *record);
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
int VillagerImpression_Held1378(u8 *record);
int VillagerImpression_Held1374(u8 *record);
int VillagerImpression_Held136B(u8 *record);
int VillagerImpression_Held1376(u8 *record);
int VillagerImpression_Byte18Is2Or4(u8 *record, int fondness, int byte_18);
int VillagerImpression_Byte18Is1(u8 *record, int fondness, int byte_18);
int VillagerImpression_EventToday(void);
int VillagerImpression_FewVillagers(void);
int VillagerImpression_NearFamilyAC(void);
int VillagerImpression_NearCodes21To24(void);
void VillagerImpression_HasFlag0(u8 *record);

#endif
