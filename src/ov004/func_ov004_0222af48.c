/* func_ov004_0222af48 @ 0x0222af48, 0x10 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020779b8(char *p, int b, int c);
void func_ov004_0222af48(char *self, u8 a, int b, int c)
{
    *self = a;
    func_020779b8(self + 1, b, c);
}
