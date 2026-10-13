/* func_ov004_0220d94c @ 0x0220d94c, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);

int func_ov004_0220d94c(u16 *p)
{
    u16 t;
    int x;

    if (func_0204bcdc(p + 1)) {
        t = 0xfff1;
        x = (func_0204bc64(p + 1) == func_0204bc64(&t)) ? 1 : 0;
    } else {
        x = (p[1] == 0xfff1) ? 1 : 0;
    }
    if (x == 0) {
        return 1;
    }
    return 0;
}
