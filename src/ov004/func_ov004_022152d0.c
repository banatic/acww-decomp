/* func_ov004_022152d0 @ 0x022152d0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004110(void *, unsigned short parameter1);

int func_ov004_022152d0(char *self, unsigned short arg1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) == 0x0) {
        func_02004110(self + 0x844, arg1);
        *(u8 *) (self + 0x858) = 0x1;
        return 0x858;
    }
    return *(u8 *) (self + 0x858);
}
