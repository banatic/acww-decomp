/* func_ov004_0223cd04 @ 0x0223cd04, 0x36 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

void func_ov004_0223cd04(u8 *self)
{
    unsigned int k, j, i;
    for (k = 0; k < 2; k++) {
        for (j = 0; j < 0x10; j++) {
            for (i = 0; i < 0x10; i++) {
                *(self + (k << 8) + (j << 4) + i) = 0xff;
            }
        }
    }
}
