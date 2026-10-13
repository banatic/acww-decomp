/* func_ov004_02238f70 @ 0x02238f70, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_022594d4[];

void func_ov004_02238f70(char *self)
{
    char *p = data_ov004_022594d4[*(u8 *) (self + 0x1e8)];
    if (p != 0) {
        *(short *) (self + 0x282) = *(short *) (p + 0x1c0) + 0x4000;
    }
    *(char *) (self + 0x281) = 2;
    *(int *) (self + 0x158) = 0;
}
