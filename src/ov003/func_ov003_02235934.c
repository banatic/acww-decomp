/* func_ov003_02235934 @ 0x02235934, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov003_02235934(u8 *self, int a)
{
    int v;

    v = *(int *) (self + 0x21c) & 0xf;
    if (v > a) {
        *(self + 0x251) = 9;
    }
}
