/* func_ov004_0221bc98 @ 0x0221bc98, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_02257908;
extern int data_ov004_0225797c[];
void func_ov004_0221bc98(void)
{
    unsigned int i;
    int z = 0;
    if (data_ov004_02257908 != 0) {
        return;
    }
    for (i = 0; i < 0x20; i++) {
        data_ov004_0225797c[i] = z;
    }
}
