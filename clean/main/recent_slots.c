/* The last three session slots recorded (recent_slots.h). */
#include "recent_slots.h"

#include "clean.h"

extern u8 data_021f3c20[RECENT_SLOTS];

/* func_0209fbd0: the newest slot, or RECENT_SLOTS_EMPTY. */
int RecentSlots_Newest(void)
{
    for (int i = RECENT_SLOTS - 1; i >= 0; i--) {
        if (data_021f3c20[i] != RECENT_SLOT_NONE) {
            return data_021f3c20[i];
        }
    }
    return RECENT_SLOTS_EMPTY;
}
CLEAN_AS(func_0209fbd0, RecentSlots_Newest)

/* func_0209fbec */
void RecentSlots_Clear(void)
{
    for (int i = 0; i < RECENT_SLOTS; i++) {
        data_021f3c20[i] = RECENT_SLOT_NONE;
    }
}
CLEAN_AS(func_0209fbec, RecentSlots_Clear)

/* func_0209fc00: the oldest entry equal to `slot` taken out, the newer ones moved down and the
 * newest place emptied. */
void RecentSlots_Forget(unsigned char slot)
{
    for (int i = 0; i < RECENT_SLOTS; i++) {
        if (data_021f3c20[i] == slot) {
            for (; i < RECENT_SLOTS - 1; i++) {
                data_021f3c20[i] = data_021f3c20[i + 1];
            }
            data_021f3c20[RECENT_SLOTS - 1] = RECENT_SLOT_NONE;
            return;
        }
    }
}
CLEAN_AS(func_0209fc00, RecentSlots_Forget)

/* func_0209fc40: `slot` added as the newest; the oldest drops out. */
void RecentSlots_Push(unsigned char slot)
{
    for (int i = 0; i < RECENT_SLOTS - 1; i++) {
        data_021f3c20[i] = data_021f3c20[i + 1];
    }
    data_021f3c20[RECENT_SLOTS - 1] = slot;
}
CLEAN_AS(func_0209fc40, RecentSlots_Push)
