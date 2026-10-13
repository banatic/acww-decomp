/* func_ov002_0220b804 @ 0x0220b804, 0x2c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// self is passed even though the callee ignores it.
extern int func_ov002_0220b71c(u8 *self);

int func_ov002_0220b804(u8 *self)
{
    if (self[0x118] == 0) {
        if (func_ov002_0220b71c(self)) {
            self[0x118] = 1;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}
