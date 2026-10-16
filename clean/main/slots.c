/* An object's four slots: see slots.h. */
#include "slots.h"

#include <assert.h>
#include <stddef.h>

#include "clean.h"

/* func_02039444: is `item` in one of the owner's slots? */
BOOL SlotOwner_Contains(const SlotOwner *owner, const void *item)
{
    for (int i = 0; i < 4; i++) {
        if (owner->slots[i] == item) {
            return TRUE;
        }
    }
    return FALSE;
}
CLEAN_AS(func_02039444, SlotOwner_Contains)

static_assert(offsetof(SlotOwner, slots) == 0x2f4, "slot array offset");
