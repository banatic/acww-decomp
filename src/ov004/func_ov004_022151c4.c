/* func_ov004_022151c4 @ 0x022151c4, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247678[];

u8 func_ov004_022151c4(void *self, unsigned int i)
{
    if (i < 3) {
        return data_ov004_02247678[i];
    }
    return 0;
}
