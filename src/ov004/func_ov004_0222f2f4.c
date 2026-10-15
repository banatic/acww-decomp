/* func_ov004_0222f2f4 @ 0x0222f2f4, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0222f304(void *arg0);

void func_ov004_0222f2f4(char *self)
{
    *(void **) (self + 0x14) = (void *) func_ov004_0222f304;
    *(u8 *) (self + 0x8e) = 2;
}
