/* func_ov004_02215298 @ 0x02215298, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020040bc(void *dst, int *v);

int func_ov004_02215298(char *self, int *src)
{
    int t[3];

    if (*(u8 *) (self + 0x858) != 0) {
        t[0] = src[0];
        t[1] = src[1];
        t[2] = src[2];
        return func_020040bc(self + 0x844, t);
    }
    return -1;
}
