/* Four bytes of a player's record (at 0x23e8, PlayerRecord_Bytes23e8): four slots, each the
 * number of a villager's motion (1 to 59, as Obj020d8c64_TakeNewMotionNumber hands them out)
 * or MOTION_SLOT_EMPTY. A new player's are all empty (MotionSlots_Clear); overlays 88 and 95
 * read and set them for the current player. */
#ifndef CLEAN_MAIN_MOTION_SLOTS_H
#define CLEAN_MAIN_MOTION_SLOTS_H

#include "types.h"

#define MOTION_SLOTS 4
#define MOTION_SLOT_EMPTY 0xff

int MotionSlots_Find(int number);
int MotionSlots_Get(int slot);
void MotionSlots_Set(int slot, int number);
int MotionSlots_FindEmpty(void);
int MotionSlots_Count(void);
void MotionSlots_Clear(u8 *slots);
void MotionSlots_Put(u8 *slots, int slot, int number);
int MotionSlots_Read(u8 *slots, int slot);

#endif
