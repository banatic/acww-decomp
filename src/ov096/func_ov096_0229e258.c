/* func_ov096_0229e258 @ 0x0229e258, 0x44 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204c878(volatile u16 *p);
extern int func_0206f848(int a);

int func_ov096_0229e258(u8 *self)
{
    volatile u16 id;

    id = *(u16 *) (self + 0xac);
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1492 && hi <= 0x14fd) {
            ok = 1;
        }
        if (ok > 0) {
            return func_0206f848(func_0204c878(&id));
        }
    }
    return func_0206f848(0);
}
