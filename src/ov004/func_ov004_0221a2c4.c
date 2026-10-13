/* func_ov004_0221a2c4 @ 0x0221a2c4, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_0224766c[];

u8 func_ov004_0221a2c4(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_0224766c[i];
    }
    return 0;
}
