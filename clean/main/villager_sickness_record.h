/* The record of a villager sick in bed (VillagerSickness, villager_sickness.h): set up, cleared,
 * and the player ids of its stages (DesignCreator, 30 bytes: a town and a player).
 *
 * A villager falls sick (VillagerSicknessRecord_Start) at stage 1 or 2, with an object of type 9
 * and item 0x155e, the medicine; stage 5 is well. Each stage may name the player who handed it
 * the medicine (VillagerSicknessRecord_SetStagePlayer); the player named most often is found by
 * VillagerSicknessRecord_MostNamedPlayer. */
#ifndef CLEAN_MAIN_VILLAGER_SICKNESS_RECORD_H
#define CLEAN_MAIN_VILLAGER_SICKNESS_RECORD_H

#include "calendar.h"
#include "design.h"
#include "npc_id.h"
#include "types.h"
#include "villager_sickness.h"

/* The object a sickness starts with: the medicine the villager asks for. */
#define VILLAGER_SICKNESS_OBJECT_TYPE 9
#define VILLAGER_SICKNESS_MEDICINE 0x155e
/* How many days after the last step a villager well again counts as recently cured. */
#define VILLAGER_SICKNESS_RECENT_DAYS 3

DesignCreator *VillagerSicknessRecord_MostNamedPlayer(VillagerSickness *sickness);
int VillagerSicknessRecord_IsRecentlyCured(VillagerSickness *sickness, const Date *today);
int VillagerSicknessRecord_IsWell(const VillagerSickness *sickness);
void VillagerSicknessRecord_SetStagePlayer(VillagerSickness *sickness, const DesignCreator *player);
int VillagerSicknessRecord_HasStagePlayer(VillagerSickness *sickness);
int VillagerSicknessRecord_NamesPlayer(VillagerSickness *sickness, const DesignCreator *player);
DesignCreator *VillagerSicknessRecord_StagePlayer(VillagerSickness *sickness);
DesignCreator *VillagerSicknessRecord_Player(VillagerSickness *sickness, u32 stage);
void VillagerSicknessRecord_Start(VillagerSickness *sickness, const NpcId *npc, const Date *today);
NpcId *VillagerSicknessRecord_Npc(VillagerSickness *sickness);
u8 *VillagerSicknessRecord_Errand(VillagerSickness *sickness);
void VillagerSicknessRecord_Clear(VillagerSickness *sickness);
VillagerSickness *VillagerSicknessRecord_Destruct(VillagerSickness *sickness);
VillagerSickness *VillagerSicknessRecord_Construct(VillagerSickness *sickness);

#endif
