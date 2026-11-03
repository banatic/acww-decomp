/* room_object_022510b4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02218e28 @ 0x02218e28, 0x4 bytes, Thumb
 * func_ov004_02218e14 @ 0x02218e14, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_02247688[];

int func_ov004_02218e28(void)
{
    return 1;
}

u8 func_ov004_02218e14(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247688[i];
    }
    return 0;
}
