/* func_ov004_02215a68 @ 0x02215a68, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247694[];

u8 func_ov004_02215a68(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247694[i];
    }
    return 0;
}
