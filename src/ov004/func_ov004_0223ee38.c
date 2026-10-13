/* func_ov004_0223ee38 @ 0x0223ee38, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern signed char data_ov004_0225628c;
extern char data_ov004_02259a34[];
char *func_ov004_0223ee38(void)
{
    u8 i;
    char *p;
    signed char c = data_ov004_0225628c;
    if (c >= 0) {
        return data_ov004_02259a34 + 0x2d8 * c;
    }
    p = data_ov004_02259a34;
    for (i = 0; i < 0x20; i++) {
        if (*(signed char *) (p + 0x196) == 0x37 && *(int *) (p + 0x198) != 0) {
            data_ov004_0225628c = i;
            return p;
        }
        p += 0x2d8;
    }
    return 0;
}
