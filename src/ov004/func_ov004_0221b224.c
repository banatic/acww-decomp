/* func_ov004_0221b224 @ 0x0221b224, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_ov004_02257914;
extern u16 data_ov004_0225337c;
extern int data_ov004_02257918;
extern int data_ov004_02257928;
extern int data_ov004_02257938;
extern int func_02003348(int a, int b, void *c, u16 *d, int e);

void func_ov004_0221b224(int a0, void *a1, int a2, int a3, s16 a4, int a5, int a6)
{
    u16 v[3];

    data_ov004_02257914 = a0;
    data_ov004_0225337c = a4;
    data_ov004_02257918 = a5;
    data_ov004_02257928 = a6;
    data_ov004_02257938 = a3;
    v[0] = 0;
    v[1] = (u16) a2;
    v[2] = 0;
    func_02003348(0x19, 0, a1, v, 0);
}
