/* func_ov004_0220e578 @ 0x0220e578, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(void *p, int a);

void func_ov004_0220e578(u16 *dst, char *p)
{
    if (*(int *) (p + 0x780) == 0x1c) {
        *dst = 0xfff1;
    } else {
        *dst = func_0204bc50(func_ov004_0220fde0(p), 0);
    }
}
