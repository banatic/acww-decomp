/* tv_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02215a7c @ 0x02215a7c, 0x4 bytes, Thumb
 * func_ov004_02215a68 @ 0x02215a68, 0x14 bytes, Thumb
 */

#include "types.h"

extern const u8 data_ov004_02247694[];

int func_ov004_02215a7c(void)
{
    return 1;
}

u8 func_ov004_02215a68(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247694[i];
    }
    return 0;
}
