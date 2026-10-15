/* func_ov004_0221a17c @ 0x0221a17c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d2a8(void *p);
extern int func_0205265c(void *self, u8 a, int b, int c);

void func_ov004_0221a17c(char *self)
{
    if (func_ov004_0220d2a8(self + 0x740) != 0) {
        func_0205265c(self, (u8) ((*(u8 *) (self + 0x844) + 1) & 1), 0xff, 1);
    }
}
