/* func_ov004_02220808 @ 0x02220808, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_020e54a8;

int func_ov004_02220808(u8 *self)
{
    unsigned int t;

    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t == 0 || self[0xade] == 0) {
        return 1;
    }
    return 0;
}
