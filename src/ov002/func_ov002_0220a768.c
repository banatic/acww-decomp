/* func_ov002_0220a768 @ 0x0220a768, 0x1c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov002_0220ba5c[];

int func_ov002_0220a768(u8 *self, int i)
{
    if (i == -1) {
        i = self[0x1c9];
    }
    return data_ov002_0220ba5c[i];
}
