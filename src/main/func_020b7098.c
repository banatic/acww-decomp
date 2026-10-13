/* func_020b7098 @ 0x020b7098, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0209df94(void *);

struct RangeEntry {
    u8 lo;
    u8 hi;
    u8 pad[6];
};

struct ValueEntry {
    u32 val;
    u32 pad;
};

extern struct RangeEntry data_020d21ec[13];
extern struct ValueEntry data_020d21f0[13];

u32 func_020b7098(void)
{
    u8 data[8];
    u8 a, b;
    u32 i;

    func_0209df94(data);
    a = data[1];
    b = data[0];

    for (i = 0; i < 13; i++) {
        if (a < data_020d21ec[i].lo) {
            return data_020d21f0[i].val;
        }
        if (a == data_020d21ec[i].lo && b <= data_020d21ec[i].hi) {
            return data_020d21f0[i].val;
        }
    }
    return 0;
}
