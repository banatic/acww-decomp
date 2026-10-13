/* func_ov003_022279d8 @ 0x022279d8, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020e8840(void *p);

void func_ov003_022279d8(void *self)
{
    if (func_020e8840((char *) self + 0x212) == 0) {
        if (*(unsigned int *) ((char *) self + 0x80) <= 1) {
            u8 v;
            *(unsigned int *) ((char *) self + 0x80) = 0;
            v = *(u8 *) ((char *) self + 0x211);
            if (v < 3) {
                *(u8 *) ((char *) self + 0x1fc) = 3;
            } else if (v < 6) {
                *(u8 *) ((char *) self + 0x1fc) = 4;
            }
        }
        *(short *) ((char *) self + 0x212) = 0x960;
    }
}
