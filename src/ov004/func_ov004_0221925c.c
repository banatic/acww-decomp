/* func_ov004_0221925c @ 0x0221925c, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247698[];

u8 func_ov004_0221925c(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247698[i];
    }
    return 0;
}
