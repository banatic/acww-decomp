/* func_ov004_0223edd8 @ 0x0223edd8, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern signed char data_ov004_02256290;
extern char data_ov004_02259a34[];
char *func_ov004_0223edd8(void)
{
    signed char c;
    u8 i;
    char *p;
    c = data_ov004_02256290;
    i = 0;
    if (c >= 0) {
        return data_ov004_02259a34 + 0x2d8 * c;
    }
    p = data_ov004_02259a34;
    while (i < 0x20) {
        if (*(signed char *) (p + 0x196) == 0x38 && *(int *) (p + 0x198) != 0) {
            data_ov004_02256290 = i;
            return p;
        }
        p += 0x2d8;
        i++;
    }
    return 0;
}
