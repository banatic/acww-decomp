/* Where one of the town's villagers (VillagerTown, villager_town.h) stands: its place in the
 * town, its entry of the running state table (villager_state.h), its kind of stay (from the
 * mode of its record at 0x734, villager_mode.h), its status for the house and the session,
 * whether a player's record holds an object for it, and a few of its bytes.
 *
 *   0x734  its mode record (VillagerModeRecord)
 *   0x7a0  its NpcId (func_0208150c)
 *   0x7d6  how it came to the town (villager_residents.h)
 *
 * Its data (func_02082500, by its number) has at 0x4d its song. */
#ifndef CLEAN_MAIN_VILLAGER_STATUS_H
#define CLEAN_MAIN_VILLAGER_STATUS_H

#include "types.h"
#include "villager_mode.h"
#include "villager_state.h"

/* VillagerStatus_Stay: what the villager's mode makes of its stay. */
#define VILLAGER_STAY_LEAVING 0  /* mode 9 */
#define VILLAGER_STAY_ARRIVED 1  /* mode 10 */
#define VILLAGER_STAY_MODE_11 2  /* mode 11 */
#define VILLAGER_STAY_RESIDENT 3 /* any other mode */

/* VillagerStatus_Get: 0 for no villager or a state entry in state 1 or 7 or above; with this
 * system in a session slot 1 or 2 from the entry's byte 0x01; else 1 or 2 from byte 0x01 for
 * state 0, and 3-7 for states 2-6. */
#define VILLAGER_STATUS_NONE 0
#define VILLAGER_STATUS_HOME 1
#define VILLAGER_STATUS_AWAY 2 /* byte 0x01 of the entry is 2 */
#define VILLAGER_STATUS_STATE_2 3

/* The text VillagerStatus_LoadModeText loads for a mode of group 2 or above. */
#define VILLAGER_STATUS_MODE_TEXT_OTHER 7

void VillagerStatus_SetCame(u8 *villager, u8 came);
u8 VillagerStatus_Came(u8 *villager);
int VillagerStatus_PlayerHolds(u8 *villager, u8 *part);
int VillagerStatus_IsFree(u8 *villager);
int VillagerStatus_IsMode11(u8 *villager);
int VillagerStatus_IsArrived(u8 *villager);
int VillagerStatus_IsLeaving(u8 *villager);
int VillagerStatus_Stay(u8 *villager);
int VillagerStatus_LoadModeText(u8 *villager, void *label);
VillagerModeRecord *VillagerStatus_ModeRecord(u8 *villager);
int VillagerStatus_Exists(void *villager);
int VillagerStatus_Get(u8 *villager);
VillagerState *VillagerStatus_StateEntry(u8 *villager);
int VillagerStatus_Index(u8 *villager);
int VillagerStatus_FindIndex(u8 *villager);
int VillagerStatus_Song(u8 *villager);

#endif
