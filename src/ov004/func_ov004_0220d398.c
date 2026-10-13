/* func_ov004_0220d398 @ 0x0220d398, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0220d398(s8 *self, s8 a, s8 b)
{
    self[0] = a;
    self[1] = b;
    if (self[0] != -1 || self[1] != -1) {
        self[2] = 1;
    }
}
