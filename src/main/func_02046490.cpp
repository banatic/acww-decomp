/* func_02046490 @ 0x02046490, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// An inclusive item-id range.
struct ItemRange {
    u16 lo;
    u16 hi;
    ItemRange(u16 l, u16 h) : lo(l), hi(h) {}
    ~ItemRange() {}
    bool contains(u16 id) const
    {
        return id >= lo && id <= hi;
    }
};

struct UnkStruct_02046490 {
    char pad_00[0xa];
    u16 id;
};

extern "C" u8 data_021c776c[];

extern "C" void func_02046490(UnkStruct_02046490 *self)
{
    u16 id = self->id;
    ItemRange a(0x154a, 0x1553);
    ItemRange b(0x1320, 0x1322);
    if (a.contains(id)) {
        data_021c776c[1] = 1;
    } else if (b.contains(id)) {
        data_021c776c[0] = 1;
    }
}
