/* The last three session slots the activity process recorded (data_021f3c20, the newest last, 0xff
 * for none): it pushes a slot (func_020a3bc0), forgets one whose block it moved to another slot
 * (func_020a35bc) and clears them (func_020a3e74); overlay 4 reads the newest
 * (func_ov004_02225240) to find that slot's player. */
#ifndef CLEAN_MAIN_RECENT_SLOTS_H
#define CLEAN_MAIN_RECENT_SLOTS_H

#include "types.h"

#define RECENT_SLOTS 3
#define RECENT_SLOT_NONE 0xff
#define RECENT_SLOTS_EMPTY 4 /* RecentSlots_Newest with none */

int RecentSlots_Newest(void);
void RecentSlots_Clear(void);
void RecentSlots_Forget(unsigned char slot);
void RecentSlots_Push(unsigned char slot);

#endif
