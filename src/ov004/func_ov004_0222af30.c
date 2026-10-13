/* func_ov004_0222af30 @ 0x0222af30, 0x16 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02077978(void *, int, int, int);

int func_ov004_0222af30(char *self, char *a1, int a2, int a3)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (a1) = *(u8 *) (self);
    return func_02077978(self + 0x1, a2, a3, a3);
}
