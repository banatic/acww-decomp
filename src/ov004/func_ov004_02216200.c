/* func_ov004_02216200 @ 0x02216200, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247660[];

u8 func_ov004_02216200(void *self, unsigned int i)
{
    if (i < 2) {
        return data_ov004_02247660[i];
    }
    return 0;
}
