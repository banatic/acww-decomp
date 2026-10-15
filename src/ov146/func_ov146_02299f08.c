/* func_ov146_02299f08 @ 0x02299f08, 0xb4 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned int func_ov146_0229a174(void *receiver);
extern int func_ov146_02299ee8(u8 *, u8 *);

int func_ov146_02299f08(u8 *self)
{
    int changed;
    int i;
    int n;
    u8 *p;

    n = 0;
    changed = 0;
    p = (u8 *) func_ov146_0229a174(self);
    for (i = 0; i < 0x20; i++) {
        if (*(self + i * 0x23 + 0x14a) != 6) {
            continue;
        }
        if (i != *(self + n + 0xea)) {
            changed = 1;
            *(self + n + 0xea) = (u8) i;
        }
        if (func_ov146_02299ee8(self, p + 0x180 + i * 0x23) != 0) {
            *(self + i * 0x23 + 0x14c) = *(p + i * 0x23 + 0x1a2);
        }
        *(self + n + 0xca) = *(p + i * 0x23 + 0x1a2);
        n++;
    }
    for (; n < 0x20; n++) {
        if (*(self + n + 0xea) != 0x20) {
            changed = 1;
            *(self + n + 0xea) = 0x20;
            *(self + n + 0xca) = 0;
        }
    }
    return changed;
}
