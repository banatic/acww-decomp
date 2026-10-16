/* An object that keeps up to four other objects in fixed slots at 0x2f4 in it. Its caller
 * func_020395a8 puts an object in the last empty slot, unless the object is already in one. */
#ifndef CLEAN_MAIN_SLOTS_H
#define CLEAN_MAIN_SLOTS_H

#include "types.h"

typedef struct SlotOwner {
    u8 unk_000[0x2f4];
    void *slots[4];
} SlotOwner;

/* func_02039444 */
BOOL SlotOwner_Contains(const SlotOwner *owner, const void *item);

#endif
