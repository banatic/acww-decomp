/* func_ov003_0222ab4c @ 0x0222ab4c, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_0222a3ec(void *self, u8 k);
extern void func_ov003_0222a784(void *self);

int func_ov003_0222ab4c(void *self)
{
    int r = 0;
    if (self == 0) {
        return r;
    }
    if (*(u8 *) ((char *) self + 0x224) != 5) {
        return r;
    }
    if (*(int *) ((char *) self + 0x13c) >= *(u8 *) ((char *) self + 0x23f)) {
        if (func_ov003_0222a3ec(self, *(u8 *) ((char *) self + 0x211))) {
            r = 2;
        } else {
            func_ov003_0222a784(self);
            r = 1;
        }
    }
    return r;
}
