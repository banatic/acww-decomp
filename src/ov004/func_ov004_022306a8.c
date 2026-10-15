/* func_ov004_022306a8 @ 0x022306a8, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov045_02260618(void);

int func_ov004_022306a8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov045_02260618();
    if (v1 == 0xb) {
        *(u8 *) (self + 0x6d4) = 0x0;
        *(u8 *) (self + 0x6b2) = 0x1;
        return 0x6b2;
    }
    return v1;
}
