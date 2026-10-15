/* func_ov004_0223cf18 @ 0x0223cf18, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02004320(void *object, short value);

void func_ov004_0223cf18(char *self, short value)
{
    if (*(u8 *) (self + 0x1c) != 0) {
        func_02004320(self, value);
    }
}
