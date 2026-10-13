/* func_ov004_0223e5f0 @ 0x0223e5f0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_021ebcd4[];
extern u8 data_ov004_02259a0c;
extern int func_02060d70(char *p);
int func_ov004_0223e5f0(void)
{
    int r;
    data_ov004_02259a0c = func_02060d70(data_021ebcd4);
    if (data_ov004_02259a0c != 0) {
        r = 1;
    } else {
        r = 0;
    }
    return r;
}
