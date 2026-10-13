/* func_ov004_02214c50 @ 0x02214c50, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02215298(void *self, void *p);
extern void *func_ov004_0220e220(void *p);
extern void *func_ov004_0220da04(void *p, int a);
extern void func_02055060(void *p, void *o, int a, int b, int c, int d);
extern void func_02054cdc(void *p);
extern int func_ov004_0220d2a8(void *p);
extern void func_ov004_0220d280(void *p, int a, int b);
extern int func_020b65c4(void);
extern int func_ov004_0220fd8c(void *self);
extern void func_02051f4c(int a, void *p, int b);

void func_ov004_02214c50(char *self)
{
    int v;
    int i;
    int x;

    v = func_ov004_02215298(self, self + 0x5c);
    if (v >= 0) {
        i = v >> 12;
        func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0), 0, v - (i << 12), (u16) i, 0);
        func_02054cdc(self + 0x538);
    }
    if (func_ov004_0220d2a8(self + 0x740) != 0) {
        func_ov004_0220d280(self + 0x740, 1, 0);
        x = func_020b65c4();
        func_02051f4c(x, self + 0x5c, func_ov004_0220fd8c(self));
    }
}
