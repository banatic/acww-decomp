#include <assert.h>
#include <stddef.h>

#include "types.h"

/* An object that keeps up to four other objects in fixed slots; its caller func_020395a8
 * fills the first empty slot. */
typedef struct SlotOwner {
    u8 unk_000[0x2f4];
    void *slots[4];
} SlotOwner;

static_assert(offsetof(SlotOwner, slots) == 0x2f4, "slot array offset");

/* func_02039444: is `item` in one of the owner's slots? */
BOOL func_02039444(const SlotOwner *owner, const void *item)
{
    for (int i = 0; i < 4; i++) {
        if (owner->slots[i] == item) {
            return TRUE;
        }
    }
    return FALSE;
}
