/* func_ov004_02213d84 @ 0x02213d84, 0x8c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d280(void *p, int a, int b);
extern void *func_ov004_0220e220(void *p);
extern void *func_ov004_0220d9bc(void *p);
extern int func_02057a40(void *p, void *d);
extern int func_020579b8(void *p, const char *name);
extern int func_020b9d3c(void *p, int a, void *b, void *c, int d, int e);
extern int data_ov004_022531d4;
extern int data_ov004_022531c8;

int func_ov004_02213d84(char *self)
{
    int a;
    int x;
    int y;

    func_ov004_0220d280(self + 0x740, 0, 0);
    x = func_02057a40(func_ov004_0220d9bc(func_ov004_0220e220(self + 0x6cc)), &data_ov004_022531d4);
    y = func_020579b8(func_ov004_0220d9bc(func_ov004_0220e220(self + 0x6cc)), (const char *) (&data_ov004_022531d4));
    a = *(int *) (self + 0x594);
    if (func_020b9d3c(self + 0x848, a, &data_ov004_022531c8, func_ov004_0220d9bc(func_ov004_0220e220(self + 0x6cc)), x, y) !=
        0) {
        *(u8 *) (self + 0x870) = 0;
    }
    return 1;
}
