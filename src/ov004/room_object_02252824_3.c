/* room_object_02252824_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022148dc @ 0x022148dc, 0x4 bytes, Thumb
 * func_ov004_022148c8 @ 0x022148c8, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_02247690[];

int func_ov004_022148dc(void)
{
    return 1;
}

u8 func_ov004_022148c8(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247690[i];
    }
    return 0;
}
