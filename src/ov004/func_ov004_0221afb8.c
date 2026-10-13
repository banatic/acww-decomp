/* func_ov004_0221afb8 @ 0x0221afb8, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_022577ac;
extern void *data_ov004_02257804[];

int func_ov004_0221afb8(void *self)
{
    u8 *p = (u8 *) ((char *) self + 0x154);
    *p = data_ov004_022577ac;
    if (*p < 0x40) {
        data_ov004_02257804[*p] = self;
        data_ov004_022577ac = data_ov004_022577ac + 1;
        return 1;
    }
    return 0;
}
