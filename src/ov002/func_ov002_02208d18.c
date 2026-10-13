/* func_ov002_02208d18 @ 0x02208d18, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov002_02208d18(u8 *p)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (p[i] == 0xff) {
            return i;
        }
    }
    return i;
}
