/* func_ov004_02235e58 @ 0x02235e58, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_02235e58(char *self)
{
    s16 v = *(s16 *) (self + 0x1c0);
    int a = v < 0 ? -v : v;
    if (a > 0x5554) {
        if (v >= 0) {
            *(s16 *) (self + 0x1c0) = 0x5554;
        } else {
            *(s16 *) (self + 0x1c0) = (s16) 0xffffaaac;
        }
    } else if (a < 0x2aac) {
        if (v >= 0) {
            *(s16 *) (self + 0x1c0) = 0x2aac;
        } else {
            *(s16 *) (self + 0x1c0) = (s16) 0xffffd554;
        }
    }
}
