/* func_02071efc @ 0x02071efc, 0x1b0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int data_021e5a2c;
extern int data_021f3b44;
extern int data_021ed278;

extern void *func_0207cec0(void *g, int a);
extern void func_0208150c(void);
extern int func_02003704(void);
extern u8 *func_020808b0(void *p);
extern void func_0207f1c8(void *p);
extern void func_0209b5ec(void);
extern int func_0209c330(void);
extern u32 func_020644cc(u32 n);
extern void func_020ae8e4(void *tbl, int i, volatile u16 *out);
extern void func_02061e2c(volatile u16 *a, volatile u16 *b);
extern void func_02072a48(void *g, int k);
extern void func_02072d4c(void);
extern int func_02072e30(void);
extern int func_02071d8c(int a, int b, int c, int d, int e);

int func_02071efc(int a, int b)
{
    // DECLS
    void *p;
    int key;
    int mode;
    u32 t;
    int f;
    int g;
    int e;
    u32 i;
    int z;
    int ok;
    u16 hi;
    u16 lo;
    int ok2;
    u16 hi2;
    u16 lo2;
    int r;
    int n;
    u32 k;
    int pick;
    int cnt;
    u32 kk;
    // ENDDECLS
    volatile u16 v[2];

    p = func_0207cec0(&data_021e5a2c, a);
    if (p == 0) {
        goto fail;
    }
    func_0208150c();
    if (func_02003704() == 0) {
        goto fail;
    }
    key = *func_020808b0(p);
    func_0207f1c8(p);
    func_0209b5ec();
    mode = func_0209c330();
    t = func_020644cc(0x64);
    g = 0;
    f = 0;
    e = 0;
    if (mode == 3) {
        if (t < 0xf) {
            f = 1;
            g = 1;
        } else if (t < 0x14) {
            f = 1;
        } else if (t < 0x1e) {
            e = 1;
        }
    } else {
        if (t < 0xa) {
            f = 1;
            g = 1;
        } else if (t < 0xf) {
            e = 1;
        }
    }
    if (e != 0) {
        v[0] = 0xfff1;
        i = 0;
        z = 0;
        for (; i < 6; i++) {
            func_020ae8e4(&data_021f3b44, i, &v[0]);
            ok = z;
            hi = v[0];
            lo = v[0];
            if (lo >= 0x1380 && hi <= 0x139f) {
                ok = 1;
            }
            if (ok != 0) {
                break;
            }
            if (hi >= 0x3e24 && hi <= 0x3ea3) {
                break;
            }
        }
        ok2 = 0;
        hi2 = v[0];
        lo2 = v[0];
        if (lo2 >= 0x1380 && hi2 <= 0x139f) {
            ok2 = 1;
        }
        if (ok2 != 0 || (hi2 >= 0x3e24 && hi2 <= 0x3ea3)) {
            func_02061e2c(&v[1], &v[0]);
        }
    }
    if (f == 0) {
        goto fail;
    }
    k = n = 0;
    do {
        func_02072a48((void *) (int) &data_021ed278, (u8) k);
        func_02072d4c();
        r = func_02072e30();
        if (g != 0) {
            if (r == key) {
                n++;
            }
        } else {
            if (r != key) {
                n++;
            }
        }
        k++;
    } while (k < 8);
    if (n <= 0) {
        goto fail;
    }
    pick = func_020644cc(n);
    kk = cnt = 0;
    for (; kk < 8; kk++) {
        func_02072a48((void *) (int) &data_021ed278, (u8) kk);
        func_02072d4c();
        r = func_02072e30();
        if (g != 0) {
            if (r == key) {
                if (pick == cnt) {
                    break;
                }
                cnt++;
            }
        } else {
            if (r != key) {
                if (pick == cnt) {
                    break;
                }
                cnt++;
            }
        }
    }
    return func_02071d8c(4, (u8) (kk & 7), 6, (u8) a, b);
fail:
    return 0;
}
