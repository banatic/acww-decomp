/* A villager's impression of a player: one of the 88 messages of "st_impress", picked by the
 * first rule of a table (data_020cd5c4) whose test the player passes, and kept in the villager's
 * memory of the player (func_020807a8, its byte 0x6d).
 *
 * Each rule is for players of one kind (the signed byte 28 of the player's id, func_020950c0:
 * 0 or 1) or for any (2), and has a test called with the player's record, how fond the villager
 * is of the player (the memory's signed byte 0x6c) and the byte 0x18 of the villager's state
 * entry (villager_state.h). The tests here look at the season, the town's players, the player's
 * looks, bells and collections, and the fondness. */
#ifndef CLEAN_MAIN_VILLAGER_IMPRESSION_H
#define CLEAN_MAIN_VILLAGER_IMPRESSION_H

#include "types.h"

#define VILLAGER_IMPRESSION_COUNT 0x58 /* also what is given for none */
#define VILLAGER_IMPRESSION_ANY_KIND 2

typedef int (*VillagerImpressionTest)(u8 *record, int fondness, int byte_18);

typedef struct VillagerImpressionRule {
    s8 kind; /* 0x00: the player's kind, or VILLAGER_IMPRESSION_ANY_KIND */
    u8 unused_01[3];
    VillagerImpressionTest test; /* 0x04: a function of the game */
} VillagerImpressionRule;

void VillagerImpression_LoadText(u8 *villager, int label, u8 *record);
int VillagerImpression_Choose(u8 *villager, s8 *memory, u8 *record);
int VillagerImpression_Pick(u8 *record, int fondness, int byte_18);

/* The tests */
int VillagerImpression_Always(void);
int VillagerImpression_IsSummer(void);
int VillagerImpression_IsAutumn(void);
int VillagerImpression_IsWinter(void);
int VillagerImpression_IsLocalAmongTwoOrMore(u8 *record);
int VillagerImpression_IsLocalAmongFour(u8 *record);
int VillagerImpression_HeadKind7(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind6(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind5(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind4(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind3(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind2(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind1(u8 *record, int fondness, int byte_18);
int VillagerImpression_HeadKind0(u8 *record, int fondness, int byte_18);
int VillagerImpression_PartCWithHeadKind01357(u8 *record, int fondness, int byte_18);
int VillagerImpression_PartCWithHeadKind246(u8 *record, int fondness, int byte_18);
int VillagerImpression_PartCWithHeadKind236(u8 *record, int fondness, int byte_18);
int VillagerImpression_PartCWithHeadKind01457(u8 *record, int fondness, int byte_18);
int VillagerImpression_Bells60000(u8 *record);
int VillagerImpression_Bells40000(u8 *record);
int VillagerImpression_Bells20000(u8 *record);
int VillagerImpression_Bells10000(u8 *record);
int VillagerImpression_BellsAtMost1000(u8 *record);
int VillagerImpression_BellsAtMost300(u8 *record);
int VillagerImpression_CollectedAllFish(u8 *record, int fondness, int byte_18);
int VillagerImpression_CollectedHalfFish(u8 *record, int fondness, int byte_18);
int VillagerImpression_CollectedAll12B0(void);
int VillagerImpression_CollectedHalf12B0(u8 *record, int fondness, int byte_18);
int VillagerImpression_VeryFond(u8 *record, int fondness);
int VillagerImpression_Fond(u8 *record, int fondness);
int VillagerImpression_Disliked(u8 *record, int fondness);

#endif
