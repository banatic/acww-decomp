/* func_ov004_0222d624 @ 0x0222d624, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off
extern char *func_ov004_0222c3a0(void *);
extern int func_02057a50(void *, const char *name);
extern int data_ov004_022478a4;
extern void *data_ov004_02254e28[];

void func_ov004_0222d624(char *self)
{
    char *h;
    unsigned i;
    char *base;
    int m;
    h = func_ov004_0222c3a0(self + 0x1a4);
    base = h + *(int *) (h + 8);
    i = 0;
    m = data_ov004_022478a4;
    for (; i < 7; i++) {
        int idx = func_02057a50(func_ov004_0222c3a0(self + 0x1a4), (const char *) (data_ov004_02254e28[i]));
        char *p = base + 4;
        u16 n = *(u16 *) (base + 0xa);
        char *q = p + n;
        u16 w = *(u16 *) (p + n);
        char *e = base + *(int *) (q + w * idx + 4);
        if (e != 0) {
            *(int *) (e + 0x10) &= ~0xf;
            *(int *) (e + 0x10) |= m;
            *(int *) (e + 0xc) &= ~0xf;
            *(int *) (e + 0xc) |= m;
        }
    }
}
