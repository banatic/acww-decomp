/* func_ov004_02212578 @ 0x02212578, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_02212578(char *self)
{
    if (*(u8 *) (self + 0x845) != 0) {
        return 1;
    }
    if (*(u8 *) (self + 0x844) == 1) {
        return 1;
    }
    return 0;
}
