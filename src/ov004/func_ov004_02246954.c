/* func_ov004_02246954 @ 0x02246954, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_0225ff50;
extern void *data_ov004_0225ff54;
extern void func_ov093_022994ac(void *, int);

void func_ov004_02246954(int x)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        if (x <= 0) {
            x = 0x125c;
        }
        func_ov093_022994ac(data_ov004_0225ff54, x);
    }
}
