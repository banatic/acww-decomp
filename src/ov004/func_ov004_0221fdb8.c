/* func_ov004_0221fdb8 @ 0x0221fdb8, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
int func_ov004_0221fdb8(u8 *self)
{
    self[0xa54] = 0;
    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
