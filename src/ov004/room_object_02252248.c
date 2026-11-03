/* room_object_02252248: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219654 @ 0x02219654, 0x4 bytes, Thumb
 * func_ov004_02219640 @ 0x02219640, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_0224768c[];

int func_ov004_02219654(void)
{
    return 1;
}

u8 func_ov004_02219640(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_0224768c[i];
    }
    return 0;
}
