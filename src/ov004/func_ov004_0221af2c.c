/* func_ov004_0221af2c @ 0x0221af2c, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);

int func_ov004_0221af2c(char *self, char *other)
{
    int lim = *(int *) (self + 0x158) + 0x2ccd;

    if (other != 0 && func_020ea990(other + 0x5c, self + 0x5c) < lim &&
        func_020e8b4c((s16) (*(s16 *) (self + 0x8e) + 0x8000), *(s16 *) (other + 0x8e)) < 0x1300) {
        return 1;
    }
    return 0;
}
