/* func_ov003_0222b724 @ 0x0222b724, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov003_0222b724(char *p)
{
    if (*(int *) (p + 0x22c) == 0) {
        return 0;
    }
    *(u8 *) (p + 0x224) = 1;
    return 1;
}
