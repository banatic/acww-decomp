/* room_object_02252ba8: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02214cd8 @ 0x02214cd8, 0x5c bytes, Thumb
 * func_ov004_02214c50 @ 0x02214c50, 0x88 bytes, Thumb
 */

#include "types.h"

extern void func_02055060(void *, int, int, int, int, int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_ov004_0220da04(int, int);
extern int func_ov004_0220e220(void *);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern int func_ov004_02215298(void *self, void *p);
extern void func_02054cdc(void *p);
extern int func_ov004_0220d2a8(void *p);
extern int func_020b65c4(void);
extern int func_ov004_0220fd8c(void *self);
extern void func_02051f4c(int a, void *p, int b);

int func_ov004_02214cd8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x1, 0x0);
    func_ov004_022101e4(self, 0x0, 0x0, 0x1000, 0x0);
    func_02055060(self + 0x538, func_ov004_0220da04(func_ov004_0220e220(self + 0x6cc), 0x0), 0x0, 0x0, 0x0, 0x0);
    return 0x1;
}

void func_ov004_02214c50(char *self)
{
    int v;
    int i;
    int x;

    v = func_ov004_02215298(self, self + 0x5c);
    if (v >= 0) {
        i = v >> 12;
        func_02055060(self + 0x538, (int) ((void *) func_ov004_0220da04((int) ((void *) func_ov004_0220e220(self + 0x6cc)), 0)), 0, v - (i << 12), (u16) i, 0);
        func_02054cdc(self + 0x538);
    }
    if (func_ov004_0220d2a8(self + 0x740) != 0) {
        func_ov004_0220d280(self + 0x740, 1, 0);
        x = func_020b65c4();
        func_02051f4c(x, self + 0x5c, func_ov004_0220fd8c(self));
    }
}
