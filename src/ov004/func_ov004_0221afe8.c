/* func_ov004_0221afe8 @ 0x0221afe8, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_022577ac;
extern int data_ov004_02257804[];
void func_ov004_0221afe8(void)
{
    unsigned int i;
    int z = 0;
    if (data_ov004_022577ac != 0) {
        return;
    }
    for (i = 0; i < 0x40; i++) {
        data_ov004_02257804[i] = z;
    }
}
