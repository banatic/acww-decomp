/* func_ov004_02213a08 @ 0x02213a08, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0220fde0(void *self);
extern int func_0204bc50(void *p, int a);
extern void *func_02072614(void);
extern void *func_02072628(void *a, u8 b);
extern int func_02057084(int a, void *d, void *p, int c, int e);
extern void func_0200451c(void *p);
extern int data_ov004_022531c8;

int func_ov004_02213a08(char *self)
{
    int m;
    u16 t;
    volatile u16 v;
    void *r;
    int idx;

    v = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    *(int *) (self + 0x844) = 0;
    m = 0;
    t = v;
    if (t >= 0x3e04 && t <= 0x3e23) {
        m = 1;
    }
    if (m != 0) {
        if (t >= 0x3e04 && t <= 0x3e23) {
            idx = (t - 0x3e04) >> 2;
        } else {
            idx = -1;
        }
        *(int *) (self + 0x844) = idx & 7;
        r = func_02072628(func_02072614(), (u8) * (int *) (self + 0x844));
        if (r != 0) {
            func_02057084(*(int *) (self + 0x594), &data_ov004_022531c8, r, 0, 0);
            if (*(u8 *) (self + 0x888) == 0) {
                func_0200451c(self + 0x848);
                *(u8 *) (self + 0x888) = 1;
            }
            return 1;
        }
    }
    return 0;
}
