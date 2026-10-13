/* func_ov004_0222626c @ 0x0222626c, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0222626c(u8 *self, unsigned int t, unsigned int step)
{
    u8 *p = self + 0x8e9;
    if (*p == t) {
        return;
    }
    if (*p < t) {
        *p = (u8) (*p + step);
        if (*p > t) {
            *p = (u8) t;
        }
    } else {
        *p = (u8) (*p - step);
        if (*(signed char *) p < (int) t) {
            *p = (u8) t;
        }
    }
}
