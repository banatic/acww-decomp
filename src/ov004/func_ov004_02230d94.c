/* func_ov004_02230d94 @ 0x02230d94, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_022588c8;
int func_ov004_02230d94(void)
{
    char *p = data_ov004_022588c8;
    if (p != 0) {
        if (*(u8 *) (p + 0x63c) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
