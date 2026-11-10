/* An object's four slots: see quick_message_slots.h. */
#include "quick_message_slots.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

/* func_02039444: whether `item` is one of the board's shown balloons. */
BOOL QuickMessage_IsShown(const SlotOwner *owner, const void *item)
{
    for (int i = 0; i < 4; i++) {
        if (owner->slots[i] == item) {
            return TRUE;
        }
    }
    return FALSE;
}
CLEAN_AS(func_02039444, QuickMessage_IsShown)

static_assert(offsetof(SlotOwner, slots) == 0x2f4, "slot array offset");
