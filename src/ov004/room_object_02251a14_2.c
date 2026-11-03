/* room_object_02251a14_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219d04 @ 0x02219d04, 0x4 bytes, Thumb
 * func_ov004_02219cf0 @ 0x02219cf0, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_02247668[];

int func_ov004_02219d04(void)
{
    return 1;
}

u8 func_ov004_02219cf0(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247668[i];
    }
    return 0;
}
