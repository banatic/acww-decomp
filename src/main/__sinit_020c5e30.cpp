/* __sinit_020c5e30 @ 0x020c5e30, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: __sinit___sinit_020c5e30.cpp
 */

#include "types.h"

// With exceptions on the initialiser keeps the object's address in r4 for the cleanup path;
// the ROM reloads it from the pool, so this unit was built without exceptions.
#pragma exceptions off

#define ITEM_NONE 0xfff1

// Each slot is a u32 followed by an item id; the constructors are 0x02082c00 and 0x02082bf0,
// the empty destructors 0x02082bfc and 0x02082bec.
struct Slot_02082c00 {
    u32 unk_00;
    u16 item;
    u16 pad_06;

    Slot_02082c00()
    {
        item = ITEM_NONE;
    }
    ~Slot_02082c00() {}
};

struct Slot_02082bf0 {
    u32 unk_00;
    u16 item;
    u16 pad_06;

    Slot_02082bf0()
    {
        item = ITEM_NONE;
    }
    ~Slot_02082bf0() {}
};

// 0x021d1d4c; its destructor is 0x02082bc0.
struct Store_021d1d4c {
    Slot_02082c00 slots[8];
    Slot_02082bf0 extra[4];
};

Store_021d1d4c data_021d1d4c;
