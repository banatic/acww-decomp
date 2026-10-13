/* func_ov133_0229b320 @ 0x0229b320, 0x24 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov133_0229ad78(char *self, int a);

void func_ov133_0229b320(char *self, u8 v)
{
    *(u8 *) (self + 0x9f) = v;
    *(u8 *) (self + 0xa1) = 0x10;
    *(u8 *) (self + 0xa2) = v;
    *(u8 *) (self + 0xa3) = v;
    func_ov133_0229ad78(self, 0x10);
}
