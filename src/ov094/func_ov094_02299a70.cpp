/* func_ov094_02299a70 @ 0x02299a70, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// An inclusive item-id range.
struct ItemRange {
    u16 lo;
    u16 hi;
    ItemRange(u16 l, u16 h) : lo(l), hi(h) {}
    bool contains(u16 id) const
    {
        return id >= lo && id <= hi;
    }
};

extern "C" int func_ov094_02299a70(u16 id)
{
    ItemRange r(0x155f, 0x1560);
    // A frame slot the code never uses; a pointer to a volatile local keeps it.
    volatile int slot[1];
    volatile int *slot_p = slot;
    if (r.contains(id)) {
        return 1;
    } else {
        return 0;
    }
}
