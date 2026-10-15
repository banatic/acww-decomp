/* func_ov004_0222d280 @ 0x0222d280, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02032180(void *);

void func_ov004_0222d280(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x354) != 0x0) {
        func_02032180(self + 0x2bc);
    }
}
