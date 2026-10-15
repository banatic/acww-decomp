/* func_0207f8a0 @ 0x0207f8a0, 0x19c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0207fe94(void *self, int *lo, int *hi, int a, int b, int c);
extern int func_0207fa3c(void *self, u16 *p);
extern int func_0207ffa0(void *self, int n);
extern int func_0207fc34(void *self, u16 *e, int t);
extern unsigned int func_0207f1c8(void *self);
extern void *func_0209b5e8(int);
extern void *func_0209b91c(void *);
extern int func_0204c878(u16 *p);
extern int func_0209bd44(void *h);
extern int func_0209bc40(void *h);
extern unsigned int func_0209b914(void *h);
extern unsigned int func_0209b8bc(void *h);
extern int func_020535f0(u16 *p);
extern int func_0207fb70(u16 *p);

int func_0207f8a0(void *self, u16 *p, int a2, int a3, u8 a5, u8 a6)
{
    int d;
    int z;
    void *h1;
    void *h2;
    int lo;
    int hi;
    unsigned int ok;
    unsigned int v;
    int n;
    int t;
    u16 *e;
    u16 *base;
    int m;

    ok = 0;
    v = *p;
    if (v >= 0x450c && v <= 0x45db) {
        ok = 1;
    }
    if (ok == 0) {
        goto fail;
    }
    if (a2 != 2) {
        goto fail;
    }
    lo = 0;
    hi = 0;
    if (func_0207fe94(self, &lo, &hi, a2, a3, a5) == 0) {
        goto fail;
    }
    d = hi - lo;
    t = func_0207fa3c(self, p);
    n = 0;
    if (t >= 0) {
        n = lo + (t % d);
    }
    if (func_0207ffa0(self, n) == 0) {
        goto fail;
    }
    base = (u16 *) ((char *) self + 0x78c);
    e = &base[n];
    if (base[n] == 0xfff1) {
        *e = *p;
        return 1;
    }
    z = func_0207fc34(self, e, a3);
    if (a6 != 0) {
        h1 = func_0209b5e8((int) func_0207f1c8(self));
        h2 = func_0209b91c((void *) h1);
        func_0204c878(p);
        func_0204c878(e);
        if (a3 == 2) {
            m = 0x18;
            if (func_0209bd44(h2) != 0 && func_0209bc40(h2) == 2 && func_0209b914(h1) >= 2 && func_0209b8bc(h1) < 0x18) {
                m = func_0209b8bc(h1);
            }
            if (m < 0x18) {
                if (m == func_020535f0(p)) {
                    func_0207fb70(e);
                    *e = *p;
                    return 1;
                }
                if (z != 0) {
                    if (m == func_020535f0(e)) {
                        func_0207fb70(p);
                        goto fail;
                    }
                    func_0207fb70(e);
                    *e = *p;
                    return 1;
                }
                func_0207fb70(e);
                *e = *p;
                return 1;
            }
            func_0207fb70(e);
            *e = *p;
            return 1;
        }
        func_0207fb70(e);
        *e = *p;
        return 1;
    }
    if (z != 0) {
        func_0207fb70(p);
        goto fail;
    }
    func_0207fb70(e);
    *e = *p;
    return 1;
fail:
    return 0;
}
