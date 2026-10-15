/* func_ov004_0223e3ec @ 0x0223e3ec, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_ov004_02259a14;
extern int func_02082654(int i);
void func_ov004_0223e3ec(void *receiver)
{
    u8 i = 0;
    int *p = &data_ov004_02259a14;
    do {
        int r = func_02082654(i);
        if (r != 0) {
            *p = r;
        }
        i = i + 1;
    } while (i < 8);
}
