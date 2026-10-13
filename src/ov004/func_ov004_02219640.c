/* func_ov004_02219640 @ 0x02219640, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_0224768c[];

u8 func_ov004_02219640(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_0224768c[i];
    }
    return 0;
}
