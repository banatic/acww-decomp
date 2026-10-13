/* func_ov004_022227b8 @ 0x022227b8, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02014868(void *);
int func_ov004_022227b8(u8 *self)
{
    if (func_02014868(self + 0x618) != 0) {
        return 0;
    }
    return (*(unsigned int *) (self + 0x89c) <= 1) ? 1 : 0;
}
