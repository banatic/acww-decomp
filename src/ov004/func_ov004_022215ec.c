/* func_ov004_022215ec @ 0x022215ec, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0201b790(char *self);
int func_ov004_022215ec(char *self)
{
    if (*(u8 *) (self + 0xac8) != 0) {
        func_0201b790(self);
    }
    return 1;
}
