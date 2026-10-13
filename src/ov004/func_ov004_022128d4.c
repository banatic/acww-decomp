/* func_ov004_022128d4 @ 0x022128d4, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_022128d4(u8 *self)
{
    self += 0x846;
    if (*self < 2) {
        *self = *self + 1;
    }
    return 1;
}
