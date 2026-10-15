/* func_ov002_0220b318 @ 0x0220b318, 0x1e bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b2ac(char *self, int value);
extern void func_ov002_0220b358(void *, unsigned char parameter1);

void func_ov002_0220b318(char *self, unsigned char value)
{
    func_ov002_0220b358(self, value);
    *(u8 *) (self + 0x75) = 0;
    func_ov002_0220b2ac(self, 1);
}
