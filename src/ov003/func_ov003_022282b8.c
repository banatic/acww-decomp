/* func_ov003_022282b8 @ 0x022282b8, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov003_02228150(void *p, void *q);
int func_ov003_022282b8(char *p, void *q)
{
    int r = 0;
    if (p == 0) {
        return r;
    }
    if (*(u8 *) (p + 0x23c) == 1) {
        return r;
    }
    if (func_ov003_02228150(p, q) != 0) {
        r = 1;
    }
    return r;
}
