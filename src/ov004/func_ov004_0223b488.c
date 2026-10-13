/* func_ov004_0223b488 @ 0x0223b488, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0223b518(void *self);
extern int func_ov004_0223b540(void *self, u16 *p, int c);

int func_ov004_0223b488(void *self, unsigned int b, int c)
{
    unsigned int v = (unsigned int) func_ov004_0223b518(self);
    if (v != (unsigned int) -1) {
        u16 s;
        v = b + (v << 3);
        s = (u16) (v < 0x20 ? 0x3ea4 + v * 4 : 0x3ea4);
        return func_ov004_0223b540(self, &s, c);
    }
    return 2;
}
