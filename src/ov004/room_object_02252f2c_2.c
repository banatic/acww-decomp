/* room_object_02252f2c_2: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221a2d8 @ 0x0221a2d8, 0x4 bytes, Thumb
 * func_ov004_0221a2c4 @ 0x0221a2c4, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_0224766c[];

int func_ov004_0221a2d8(void)
{
    return 1;
}

u8 func_ov004_0221a2c4(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_0224766c[i];
    }
    return 0;
}
