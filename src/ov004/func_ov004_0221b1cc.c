/* func_ov004_0221b1cc @ 0x0221b1cc, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_02257904;
extern int data_ov004_02257914;
extern u16 data_ov004_0225337c;
extern int data_ov004_02257918;
extern int data_ov004_02257928;
extern int data_ov004_02257938;
extern int data_021fbee8;
extern int func_02003348(int a, int b, void *c, int d, int e);

int func_ov004_0221b1cc(void)
{
    if (data_ov004_02257904 == 0) {
        data_ov004_02257914 = 4;
        data_ov004_0225337c = 0;
        data_ov004_02257918 = 0;
        data_ov004_02257928 = 0;
        data_ov004_02257938 = 0;
        return func_02003348(0x19, 0, &data_021fbee8, 0, 0);
    }
    return 0;
}
