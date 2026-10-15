/* func_ov002_0220b358 @ 0x0220b358, 0x14 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b2d0(u8 *self, int a, int b);

void func_ov002_0220b358(u8 *self, int v)
{
    self[0x77] = v;
    func_ov002_0220b2d0(self, 0xf, 0);
}
