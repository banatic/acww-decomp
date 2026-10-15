/* func_ov002_0220b7b8 @ 0x0220b7b8, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220b6d0(u8 *self);
extern void func_ov002_0220b6b0(void *self);

int func_ov002_0220b7b8(u8 *self)
{
    if (self[0x118] == 2) {
        if (func_ov002_0220b6d0(self)) {
            func_ov002_0220b6b0(self);
            self[0x118] = 3;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}
