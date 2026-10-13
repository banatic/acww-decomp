/* func_ov068_02266b3c @ 0x02266b3c, 0x2e bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_0222f524(u8 *, u8);

int func_ov068_02266b3c(int unused, int a1, int a2)
{
    u8 t;
    int res;

    if (a2 != -1) {
        t = 0;
        res = func_ov003_0222f524(&t, (u8) a1);
        if (res == a2) {
            return 1;
        }
    }
    return 0;
}
