/* func_ov004_0222bf20 @ 0x0222bf20, 0x2e bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02096718();
extern int func_ov004_02227324();

int func_ov004_0222bf20(char *self, char *a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02096718(0x4, a1);
    if (v1 != 0x0) {
        return func_ov004_02227324(v1, *(u8 *) (self), *(u8 *) (a1), 0x6, -0x1);
    }
    return 0x0;
}
