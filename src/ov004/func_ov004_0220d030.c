/* func_ov004_0220d030 @ 0x0220d030, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d150(char *p);
void func_ov004_0220d030(char *self)
{
    char *end;
    if (*(u8 *) (self + 0x54) != 0) {
        end = self + 0x54;
        while (self < end) {
            func_ov004_0220d150(self);
            self += 0x1c;
        }
    }
}
