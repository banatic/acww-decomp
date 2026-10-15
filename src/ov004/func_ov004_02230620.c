/* func_ov004_02230620 @ 0x02230620, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov045_02260618(void);

int func_ov004_02230620(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov045_02260618();
    if (v1 == 0x9) {
        *(u8 *) (self + 0x6b0) = 0x1;
        return 0x6b0;
    }
    return v1;
}
