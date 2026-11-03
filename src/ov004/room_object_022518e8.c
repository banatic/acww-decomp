/* room_object_022518e8: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219270 @ 0x02219270, 0x4 bytes, Thumb
 * func_ov004_0221925c @ 0x0221925c, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_02247698[];

int func_ov004_02219270(void)
{
    return 1;
}

u8 func_ov004_0221925c(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247698[i];
    }
    return 0;
}
