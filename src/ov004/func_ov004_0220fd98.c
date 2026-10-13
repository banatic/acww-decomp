/* func_ov004_0220fd98 @ 0x0220fd98, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d290();

int func_ov004_0220fd98(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x77d) == 0x0) {
        func_ov004_0220d290(self + 0x740, 0x1);
        return 0x1;
    }
    return 0x0;
}
