/* func_ov004_02213984 @ 0x02213984, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020044a0(char *p);
int func_ov004_02213984(char *self)
{
    if (*(u8 *) (self + 0x888) != 0) {
        func_020044a0(self + 0x848);
    }
    return 1;
}
