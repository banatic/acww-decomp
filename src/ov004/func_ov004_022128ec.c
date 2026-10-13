/* func_ov004_022128ec @ 0x022128ec, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223d03c(void);
extern int func_ov004_0223d2ac(void *p);
extern void *func_ov004_0223d054(void *p);
extern void func_020ba1f4(void *p, u16 *q);
extern int func_020ba1ec(void *p);
extern int func_020b9d3c(void *p, int a, void *b, int c, int d, int e);
extern int data_ov004_022531a0;

int func_ov004_022128ec(char *self)
{
    u16 t;
    int a;
    int r;

    *(u16 *) (self + 0x844) = (u16) func_ov004_0223d2ac(func_ov004_0223d03c());
    *(u8 *) (self + 0x846) = 0;
    t = (*(u16 *) (self + 0x844) < 0x44) ? (u16) (*(u16 *) (self + 0x844) + 0x1100) : (u16) 0x1100;
    func_020ba1f4(func_ov004_0223d054(func_ov004_0223d03c()), &t);
    a = *(int *) (self + 0x594);
    r = func_020b9d3c(self + 0x848, a, &data_ov004_022531a0, func_020ba1ec(func_ov004_0223d054(func_ov004_0223d03c())), 0, 0);
    if (r != 0) {
        return 1;
    }
    return 0;
}
