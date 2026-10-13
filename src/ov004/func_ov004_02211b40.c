/* func_ov004_02211b40 @ 0x02211b40, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_02247684[];

u8 func_ov004_02211b40(void *self, unsigned int i)
{
    if (i < 4) {
        return data_ov004_02247684[i];
    }
    return 0;
}
