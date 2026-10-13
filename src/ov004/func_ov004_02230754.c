/* func_ov004_02230754 @ 0x02230754, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_02230754(u8 *self)
{
    u8 i = 0;
    u8 z;
    *(self + 0x6d4) = 0;
    z = 0;
    do {
        *(self + i + 0x6b0) = z;
        i = i + 1;
    } while (i < 3);
    return 1;
}
