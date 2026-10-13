/* func_ov004_0221b938 @ 0x0221b938, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);

int func_ov004_0221b938(char *self, char *other)
{
    if (other != 0 && func_020ea990(other + 0x5c, self + 0x5c) < 0x2333 &&
        func_020e8b4c((s16) (*(s16 *) (self + 0x8e) + 0x8000), *(s16 *) (other + 0x8e)) < *(int *) (self + 0x158)) {
        return 1;
    }
    return 0;
}
