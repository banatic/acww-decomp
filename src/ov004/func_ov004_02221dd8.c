/* func_ov004_02221dd8 @ 0x02221dd8, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned short data_020c80f8;
extern int func_02019c6c(void *, int, int);
int func_ov004_02221dd8(u8 *self)
{
    if (func_02019c6c(self + 0x564, 1, data_020c80f8) != 0) {
        self[0xa90] = 0x46;
        return 1;
    }
    return 0;
}
