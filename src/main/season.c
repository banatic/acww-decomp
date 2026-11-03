/* season: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b7098 @ 0x020b7098, 0x50 bytes, Thumb
 * func_020b7074 @ 0x020b7074, 0x24 bytes, Thumb
 */

#include "types.h"

struct RangeEntry {
    u8 lo;
    u8 hi;
    u8 pad[6];
};

struct ValueEntry {
    u32 val;
    u32 pad;
};

extern void func_0209df94(void *);
extern struct RangeEntry data_020d21ec[13];
extern struct ValueEntry data_020d21f0[13];
extern unsigned short data_020d20d0[];
extern struct {
    unsigned char pad[8];
    unsigned char : 2;
    unsigned char field : 6;
} data_021ebcc8;

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

unsigned short func_020b7074(void)
{
    if ((int) data_021ebcc8.field < 12) {
        return data_020d20d0[data_021ebcc8.field];
    } else {
        return data_020d20d0[0];
    }
}
