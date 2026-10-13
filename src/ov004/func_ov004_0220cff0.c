/* func_ov004_0220cff0 @ 0x0220cff0, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_ov004_0224fe2c[];
extern int func_0205790c(void *a, int k);
extern void func_ov004_0220cfec(u8 *dst, void *c);

void func_ov004_0220cff0(u8 *dst, void *a, void *c)
{
    unsigned i;

    if (a != 0) {
        for (i = 0; i < 4; i++) {
            dst[i] = (u8) func_0205790c(a, data_ov004_0224fe2c[i]);
        }
        func_ov004_0220cfec(dst, c);
    }
}
