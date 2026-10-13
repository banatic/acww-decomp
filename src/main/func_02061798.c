/* func_02061798 @ 0x02061798, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_02061798(unsigned int a)
{
    if (a >= 4 && a <= 7) {
        return 1;
    }
    if (a >= 8 && a <= 0xf) {
        return 2;
    }
    if (a == 0x10) {
        return 3;
    }
    if ((u8) (a + 0xef) <= 1) {
        return 4;
    }
    if (a >= 0x13 && a <= 0x16) {
        return 5;
    }
    return 0;
}
