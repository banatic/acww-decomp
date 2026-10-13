/* func_ov004_0221bbf8 @ 0x0221bbf8, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0221b98c(void *self);
extern int data_ov004_0225797c[];
extern u8 data_ov004_02257908;
extern u8 data_ov004_02257904;

int func_ov004_0221bbf8(char *self)
{
    u8 *p;
    u8 v;
    if (func_ov004_0221b98c(self) == 0) {
        p = (u8 *) (self + 0x154);
        v = *p;
        if (v < 0x20) {
            data_ov004_0225797c[v] = 0;
            data_ov004_02257908 = (u8) (data_ov004_02257908 - 1);
            *p = 0xff;
            return 1;
        }
    } else {
        data_ov004_02257904 = 0;
    }
    return 0;
}
