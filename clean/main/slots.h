/* The quick messages' board (quick_message.h) as one function sees it: its four shown balloons
 * at 0x2f4. QuickMessage_PlaceBalloon puts a balloon in the last empty entry, unless it is
 * shown already. */
#ifndef CLEAN_MAIN_SLOTS_H
#define CLEAN_MAIN_SLOTS_H

#include "types.h"

typedef struct SlotOwner {
    u8 unk_000[0x2f4];
    void *slots[4];
} SlotOwner;

/* func_02039444 */
BOOL QuickMessage_IsShown(const SlotOwner *owner, const void *item);

#endif
