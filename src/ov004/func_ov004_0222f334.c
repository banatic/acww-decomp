/* func_ov004_0222f334 @ 0x0222f334, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

u16 func_ov004_0222f334(unsigned int i)
{
    unsigned int v;
    if (i < 0x14) {
        v = i * 4 + 0x3894;
    } else {
        v = 0x3894;
    }
    return (u16) v;
}
