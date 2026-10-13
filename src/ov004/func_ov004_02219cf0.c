/* func_ov004_02219cf0 @ 0x02219cf0, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247668[];

u8 func_ov004_02219cf0(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247668[i];
    }
    return 0;
}
