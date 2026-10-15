/* func_ov113_02299f10 @ 0x02299f10, 0xf4 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned char data_021eed68;
extern void *func_020781d0(void *, int parameter1);
extern int func_02078288(void *);
extern int func_02078290(void *);
extern int func_02078298(void *);
extern int _s32_div_f(int a, int b);
extern void func_020708e4(void *, void *, int);
extern void func_ov113_02299db8(unsigned char *, int, int, int, int, int);

void func_ov113_02299f10(unsigned char *self, int arg1)
{
    void *r4;
    u16 arr[5];

    r4 = func_020781d0(&data_021eed68, arg1);
    arr[0] = 0xff12;
    arr[1] = 0xff10;
    arr[2] = _s32_div_f(func_02078288(r4), 10) + 0xff10;
    arr[3] = (func_02078288(r4) % 10) + 0xff10;
    arr[4] = 0;
    func_020708e4(self + 0x26e8, arr, 5);
    func_ov113_02299db8(self, 0, 0x111, 4, 0, 1);
    arr[0] = _s32_div_f(func_02078290(r4), 10) + 0xff10;
    arr[1] = (func_02078290(r4) % 10) + 0xff10;
    arr[2] = _s32_div_f(func_02078298(r4), 10) + 0xff10;
    arr[3] = (func_02078298(r4) % 10) + 0xff10;
    func_020708e4(self + 0x2754, arr, 5);
    func_ov113_02299db8(self, 1, 0x116, 4, 0, 1);
}
