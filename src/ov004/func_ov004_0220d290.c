/* func_ov004_0220d290 @ 0x0220d290, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220d280(char *self, int t, int a);
int func_ov004_0220d290(char *self, int a)
{
    int t = ((*(u8 *) (self + 1) + 1) & 1) != 0;
    return func_ov004_0220d280(self, t, a);
}
