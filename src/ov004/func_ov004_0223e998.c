/* func_ov004_0223e998 @ 0x0223e998, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020b67d4(void);
extern int func_02073d90(void *);
extern void func_02060d64(void *, int);
extern void *data_020ccf94;
extern char data_021ebcd4;
extern u8 data_ov004_02259a0c;
extern void *data_ov004_02259a10;

int func_ov004_0223e998(void)
{
    if (func_020b67d4() == 0 || func_02073d90(data_020ccf94) != 0) {
        return 1;
    }
    func_02060d64(&data_021ebcd4, data_ov004_02259a0c);
    data_ov004_02259a10 = 0;
    return 1;
}
