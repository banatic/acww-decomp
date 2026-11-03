/* room_object_022525cc_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022199a4 @ 0x022199a4, 0x4 bytes, Thumb
 * func_ov004_02219990 @ 0x02219990, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_0224767c[];

int func_ov004_022199a4(void)
{
    return 1;
}

u8 func_ov004_02219990(void *self, unsigned int i)
{
    if (i < 3) {
        return data_ov004_0224767c[i];
    }
    return 0;
}
