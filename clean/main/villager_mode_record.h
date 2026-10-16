/* The operations on a villager's mode record (VillagerModeRecord, villager_mode.h): its dates,
 * its mode and the group of a mode, the scores and counts of the eight kinds, and the moves
 * from modes 8, 10 and 11 to a kind drawn from the scores.
 *
 * The modes form groups: 0 (modes 0-4), 1 (5-7), 2 (8-11) and 3 (the others); the first three
 * have their first mode in data_020d1a20 (0, 5, 8). Each kind is shown with an item
 * (VillagerModeRecord_KindItem) and a text of the archive "st_boom"
 * (VillagerModeRecord_LoadKindText). */
#ifndef CLEAN_MAIN_VILLAGER_MODE_RECORD_H
#define CLEAN_MAIN_VILLAGER_MODE_RECORD_H

#include "calendar.h"
#include "types.h"
#include "villager_mode.h"

#define VILLAGER_MODE_RECORD_COUNT_MAX 10
#define VILLAGER_MODE_RECORD_SCORE_MAX 0xff

void VillagerModeRecord_KindItem(u16 *out, int kind);
void VillagerModeRecord_LearnTop(VillagerModeRecord *record, const VillagerModeRecord *from, const s16 *weights);
void VillagerModeRecord_AddCount(VillagerModeRecord *record, u32 kind, int amount);
int VillagerModeRecord_DrawScores(VillagerModeRecord *record, const s16 *weights);
void VillagerModeRecord_AddCountsToScores(VillagerModeRecord *record, const s16 *weights);
DateTime *VillagerModeRecord_Counted(VillagerModeRecord *record);
DateTime *VillagerModeRecord_Since(VillagerModeRecord *record);
int VillagerModeRecord_LoadKindText(void *text, int mode);
int VillagerModeRecord_LeaveArrived(VillagerModeRecord *record, const DateTime *now);
int VillagerModeRecord_LeaveMode11(VillagerModeRecord *record, const DateTime *now);
int VillagerModeRecord_LeaveNoneYet(VillagerModeRecord *record);
int VillagerModeRecord_KeepKind(VillagerModeRecord *record);
int VillagerModeRecord_IsKindAWeekOld(VillagerModeRecord *record, const DateTime *now);
int VillagerModeRecord_IsKindDaysOld(VillagerModeRecord *record, const DateTime *now, u32 days);
void VillagerModeRecord_EnterMode11(VillagerModeRecord *record);
void VillagerModeRecord_EnterNoneYet(VillagerModeRecord *record);
int VillagerModeRecord_IsFrom2(VillagerModeRecord *record);
int VillagerModeRecord_PlaceInGroup(u8 *group, u8 mode);
u32 VillagerModeRecord_Group(VillagerModeRecord *record);
u32 VillagerModeRecord_GroupOfMode(u32 mode);
void VillagerModeRecord_SetMode(VillagerModeRecord *record, int mode);
int VillagerModeRecord_Mode(VillagerModeRecord *record);

#endif
