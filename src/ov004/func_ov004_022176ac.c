/* func_ov004_022176ac @ 0x022176ac, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247680[];

u8 func_ov004_022176ac(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247680[i];
    }
    return 0;
}
