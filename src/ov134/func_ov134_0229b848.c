/* func_ov134_0229b848 @ 0x0229b848, 0x3a bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov134_0229b848(int a, unsigned int k, u8 *p)
{
    switch (k) {
        case 0:
            return p[5];
        case 1:
            return p[4];
        case 2:
            return p[3];
        case 3:
            return p[2];
        case 4:
            return p[1];
        case 5:
            return 0;
    }
    return 0xff;
}
