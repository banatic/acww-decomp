/* Which of the town's villagers are out walking, at home or asleep.
 *
 * The town's villagers (data_021e5a2c, eight of 0x7ec bytes) are followed at 0x3f7c by the
 * list below (VillagerOutdoors): the villagers in an order, and the up to four who are out of
 * their houses. Every hour (VillagerOutdoors_Update) the ones out are drawn again; between draws
 * they are kept. Each villager's entry in the running state table (villager_state.h) says where
 * the villager is, in its byte 0x01 (enum VillagerPlace) and its state:
 *
 *   - out walking: place 0, state 1 (overlay 3's houses then find their doors closed);
 *   - at home: place 1, state 0;
 *   - asleep: place 2, state 0, for the hours of the night its personality sleeps
 *     (func_020821d4), unless bit 1 of the current player's record is set;
 *   - no villager: place 3, state 7.
 *
 * At most three quarters of the villagers go out, and four; none while this system holds a
 * slot of a session (func_02082240). The villager the town's table names at 0x16c (the state
 * table's index 0x16c) goes out first, and the one the record at 0x3f90 names never does. */
#ifndef CLEAN_MAIN_VILLAGER_OUTDOORS_H
#define CLEAN_MAIN_VILLAGER_OUTDOORS_H

#include "calendar.h"
#include "types.h"

#define VILLAGER_OUTDOORS_ORDER 8
#define VILLAGER_OUTDOORS_OUTSIDE 4
#define VILLAGER_OUTDOORS_NONE (-1)

/* Byte 0x01 of a villager's entry in the state table. */
enum VillagerPlace { VILLAGER_PLACE_OUTSIDE = 0, VILLAGER_PLACE_HOME = 1, VILLAGER_PLACE_ASLEEP = 2, VILLAGER_PLACE_NONE = 3 };

typedef struct VillagerOutdoors {
    s8 order[VILLAGER_OUTDOORS_ORDER];     /* 0x00: villager indexes, then -1 */
    s8 outside[VILLAGER_OUTDOORS_OUTSIDE]; /* 0x08: villager indexes or -1 */
    DateTime drawn_at;                     /* 0x0c: when the ones out were drawn; all zero for never */
} VillagerOutdoors;

void VillagerOutdoors_Update(VillagerOutdoors *outdoors, u8 *villagers, int keep_time);
void VillagerOutdoors_Restore(VillagerOutdoors *outdoors, u8 *villagers);
void VillagerOutdoors_Draw(VillagerOutdoors *outdoors, u8 *villagers);
void VillagerOutdoors_PutToSleep(VillagerOutdoors *outdoors, u8 *villagers, const DateTime *now);
void VillagerOutdoors_TakeIndex16C(VillagerOutdoors *outdoors, s8 *chosen, int *count, s8 *list, u8 *villagers);
void VillagerOutdoors_SendOut(VillagerOutdoors *outdoors, s8 *chosen, int *count, u8 *states, int chosen_count);
void VillagerOutdoors_KeepHome(VillagerOutdoors *outdoors, s8 *list, int *count, u8 *states);
void VillagerOutdoors_DrawRandom(VillagerOutdoors *outdoors, u8 *chosen, int *count, s8 *list, u8 *villagers, int limit);
int VillagerOutdoors_IsDue(VillagerOutdoors *outdoors, const DateTime *now);
void VillagerOutdoors_ClearTime(VillagerOutdoors *outdoors);
void VillagerOutdoors_ListResidents(VillagerOutdoors *outdoors, u8 *villagers);
int VillagerOutdoors_OutsideSlot(VillagerOutdoors *outdoors, int villager);
void VillagerOutdoors_Remove(VillagerOutdoors *outdoors, int villager);
void VillagerOutdoors_RemoveOutside(VillagerOutdoors *outdoors, int villager);
int VillagerOutdoors_FindOutside(VillagerOutdoors *outdoors, int villager);
int VillagerOutdoors_SetOutside(VillagerOutdoors *outdoors, unsigned int slot, char villager);
void VillagerOutdoors_ClearOutside(VillagerOutdoors *outdoors);
void VillagerOutdoors_RemoveFromOrder(VillagerOutdoors *outdoors, int villager);
void VillagerOutdoors_AddToOrder(VillagerOutdoors *outdoors, int villager);
int VillagerOutdoors_SetOrder(VillagerOutdoors *outdoors, int position, int villager);
void VillagerOutdoors_CopyList(VillagerOutdoors *outdoors, s8 *dst, const s8 *src);
void VillagerOutdoors_ClearList(VillagerOutdoors *outdoors, s8 *list);
void VillagerOutdoors_Init(VillagerOutdoors *outdoors);
void VillagerOutdoors_Destruct(VillagerOutdoors *outdoors);
void VillagerOutdoors_Construct(VillagerOutdoors *outdoors);
void VillagerOutdoors_DrawIndex160(const u8 *villagers, const void *player);
int VillagerOutdoors_MonthChance(void);

#endif
