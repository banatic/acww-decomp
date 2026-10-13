/* func_0209c80c @ 0x0209c80c, 0x17c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0209cc30(void *self, u32 a, u32 b);
extern void *func_0209d030(void *p);
extern int func_02037bc4(void *p);
extern int func_02037b14(void *p);
extern int func_020644cc(int n);
extern void *func_0209cc10(void *p);
extern void func_0209d01c(void *p, void *x);

int func_0209c80c(void *self)
{
    int k;
    void *p;
    int sel;
    int count;
    u32 i, j;
    int f;
    unsigned int t1, t2, t3, ok;
    void *x, *y;

    count = 0;
    for (i = 1; i < 5; i++) {
        for (j = 1; j < 5; j++) {
            p = func_0209d030(func_0209cc30(self, j, i));
            f = func_02037bc4(p);
            t1 = (f & 8) ? 1 : 0;
            if (t1 != 0) {
                goto no1;
            }
            t2 = (f & 4) ? 1 : 0;
            if (t2 != 0) {
                goto no1;
            }
            t3 = (f & 0x80000) ? 1 : 0;
            if (t3 != 0) {
                goto no1;
            }
            if (func_02037b14(p) != 1) {
                goto no1;
            }
            ok = 1;
            goto have1;
        no1:
            ok = 0;
        have1:
            if (ok != 0) {
                count++;
            }
        }
    }
    if (count == 0) {
        goto done0;
    }
    sel = func_020644cc(count);
    k = 0;
    for (i = 1; i < 5; i++) {
        for (j = 1; j < 5; j++) {
            p = func_0209d030(func_0209cc30(self, j, i));
            f = func_02037bc4(p);
            t1 = (f & 8) ? 1 : 0;
            if (t1 != 0) {
                goto no2;
            }
            t2 = (f & 4) ? 1 : 0;
            if (t2 != 0) {
                goto no2;
            }
            t3 = (f & 0x80000) ? 1 : 0;
            if (t3 != 0) {
                goto no2;
            }
            if (func_02037b14(p) != 1) {
                goto no2;
            }
            ok = 1;
            goto have2;
        no2:
            ok = 0;
        have2:
            if (ok != 0) {
                if (sel == k) {
                    x = func_0209cc10(func_0209d030(func_0209cc30(self, j, i)));
                    y = func_0209d030(func_0209cc30(self, j, i));
                    if (x != y) {
                        func_0209d01c(func_0209cc30(self, j, i), x);
                        return 1;
                    }
                }
                k++;
            }
        }
    }
done0:
    return 0;
}
