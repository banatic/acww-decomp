/* func_ov004_02215270 @ 0x02215270, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020040b4(void *);

int func_ov004_02215270(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        func_020040b4(self + 0x844);
        *(u8 *) (self + 0x858) = 0x0;
        return 0x858;
    }
    return *(u8 *) (self + 0x858);
}
