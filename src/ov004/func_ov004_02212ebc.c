/* func_ov004_02212ebc @ 0x02212ebc, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov004_0224769c[];

u8 func_ov004_02212ebc(void *self, unsigned int i)
{
    if (i < 5) {
        return data_ov004_0224769c[i];
    }
    return 0;
}
