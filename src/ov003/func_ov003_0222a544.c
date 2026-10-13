/* func_ov003_0222a544 @ 0x0222a544, 0x14 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_ov003_0225f0b8;
void func_ov003_0222a544(void)
{
    if (data_ov003_0225f0b8 != 0) {
        data_ov003_0225f0b8 = data_ov003_0225f0b8 - 1;
    }
}
