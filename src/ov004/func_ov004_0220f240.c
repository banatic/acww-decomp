/* func_ov004_0220f240 @ 0x0220f240, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_0220f240(int x)
{
    u16 v = (u16) x;

    if (v >= 0xe000 || v < 0x2000) {
        return 0;
    }
    if (v < 0x6000) {
        return 1;
    }
    if (v < 0xa000) {
        return 2;
    }
    return 3;
}
