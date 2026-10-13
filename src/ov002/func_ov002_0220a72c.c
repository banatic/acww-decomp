/* func_ov002_0220a72c @ 0x0220a72c, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov002_0220ba68[];

int func_ov002_0220a72c(u8 *self, int i)
{
    int v;

    if (i == -1) {
        i = self[0x1c9];
    }
    v = data_ov002_0220ba68[i];
    switch (self[0x1c8]) {
        case 8:
            v -= 0x1e;
            break;
        case 0xc:
            v -= 0x20;
            break;
        case 0xd:
            v -= 0xe;
            break;
    }
    return v;
}
