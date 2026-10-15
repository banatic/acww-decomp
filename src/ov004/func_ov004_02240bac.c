/* func_ov004_02240bac @ 0x02240bac, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02240f2c(void *, int, int, int, int, int, int);

int func_ov004_02240bac(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov004_02240f2c(self, a1, a2, 0x3556, 0xffff8000, 0x0, 0x0);
    *(u8 *) (self + 0x50) = 0x0;
    return 0x0;
}
