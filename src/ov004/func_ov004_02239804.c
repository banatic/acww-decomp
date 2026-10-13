/* func_ov004_02239804 @ 0x02239804, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02239820(void *, int);

int func_ov004_02239804(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239820(self, 0x0);
    *(u8 *) (self + 0x22e) = 0x0;
    return 0x22e;
}
