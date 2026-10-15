/* func_0205e348 @ 0x0205e348, 0xfc bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int data_020dd72c;
extern int data_020dd734;
extern int func_0205e1a8(void *s);
extern int func_0205e700(void);
extern int func_0205e878(int p);
extern int func_02064af4(int a, int base, int cap);
extern void func_0205e174(void *s, int i, int base);
extern void func_0205e118(void *s, int i, int v);
extern int func_0205d6fc(void);
extern void func_0205d3d4(int x, u16 *p3, int a5, int z1, int z2);
extern int func_0205d25c(int x);
extern int func_021077e8(int a);
extern int func_0206439c(int a, int b, int *c, int *d);
extern int func_0206435c(int a, int b, int *c, int *d);

int func_0205e348(void *s, int p1, int p2, u16 *p3, int a5)
{
    int base;
    int cap;
    int cap2;
    int n;
    int w;
    int x;
    int y;
    int z;
    unsigned int ok;
    u16 v;

    base = func_0205e1a8(s);
    cap = func_0205e700();
    n = func_02064af4(func_0205e878(p1), base, cap);
    w = 0;
    if (n != 0) {
        n = (n + 3) & ~3;
        func_0205e174(s, w, base);
        func_0205e118(s, 0, p1);
        func_0205e118(s, 1, p2);
        if (p2 < 0x9e) {
            base = base + n;
            cap2 = cap - n;
            w = func_02064af4(func_0205e878(p2), base, cap2);
            if (w != 0) {
                func_0205e174(s, 1, base);
                ok = 0;
                v = *p3;
                if (v >= 0x1429 && v <= 0x1430) {
                    ok = 1;
                }
                if (ok != 0) {
                    x = func_0205d6fc();
                    func_0205d3d4(x, p3, a5, 0, 0);
                    y = func_021077e8(func_0205d25c(x));
                    z = func_021077e8(base);
                    func_0206439c(y, z, &data_020dd72c, &data_020dd734);
                    func_0206435c(y, z, &data_020dd72c, &data_020dd734);
                }
            } else {
                func_0205e118(s, 1, 0x9e);
            }
        }
    }
    return n + w;
}
