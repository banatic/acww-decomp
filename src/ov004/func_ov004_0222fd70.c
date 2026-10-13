/* func_ov004_0222fd70 @ 0x0222fd70, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *data_ov004_02258558;
int func_ov004_0222fd70(void)
{
    char *p = data_ov004_02258558;
    if (p != 0) {
        int v = *(u8 *) (p + 0x24c);
        if (v == 3 || v == 0) {
            return 1;
        }
    }
    return 0;
}
