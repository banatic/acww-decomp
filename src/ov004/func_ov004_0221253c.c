/* func_ov004_0221253c @ 0x0221253c, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247670[];

u8 func_ov004_0221253c(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247670[i];
    }
    return 0;
}
