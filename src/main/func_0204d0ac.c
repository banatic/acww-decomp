/* func_0204d0ac @ 0x0204d0ac, 0x342 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off
#pragma opt_loop_invariants off

typedef struct UnkStruct_0204d0ac {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0204d0ac;
typedef struct UnkStruct_0204d0ac_2 {
    u16 v;
} UnkStruct_0204d0ac_2;

extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_0204ed08(UnkStruct_0204d0ac *p, int x, int y);
extern UnkStruct_0204d0ac_2 *func_0204f5e0(UnkStruct_0204d0ac *p, int a, int b, int c, int d, int e);
extern int func_0204ba94(UnkStruct_0204d0ac_2 *e);
extern int func_0204f538(UnkStruct_0204d0ac *p, u16 *m, int x, int y, int z);

static __inline int Chk(UnkStruct_0204d0ac_2 *p)
{
    u32 i, h, g, f, e, d, c, b, a;
    u32 v;
    b = c = d = e = f = g = h = i = 1;
    a = 0;
    v = p->v;
    if (v >= 0x26 && v <= 0x2a) {
        a = 1;
    }
    if (a == 0) {
        if (!(v >= 0x5d && v <= 0x61)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(v >= 0x2f && v <= 0x56)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!(v >= 0x57 && v <= 0x5b)) {
            d = 0;
        }
    }
    if (d == 0) {
        if (!(v >= 0x66 && v <= 0x68)) {
            e = 0;
        }
    }
    if (e == 0) {
        if (!(v == 0x69)) {
            f = 0;
        }
    }
    if (f == 0) {
        if (!(v >= 0x6a && v <= 0x6c)) {
            g = 0;
        }
    }
    if (g == 0) {
        if (!(v == 0x6d)) {
            h = 0;
        }
    }
    if (h == 0) {
        if (!(v >= 0xc8 && v <= 0xcf)) {
            i = 0;
        }
    }
    return i;
}

void func_0204d0ac(UnkStruct_0204d0ac *p)
{
    int *q;
    int w, hh;
    int x, y;
    UnkStruct_0204d0ac_2 *e1;
    UnkStruct_0204d0ac_2 *e2;
    UnkStruct_0204d0ac_2 *e3;
    int xi;
    int yi2;
    int yi1;
    u16 mark;
    int x0, y0, x1, y1;

    if (p == 0) {
        return;
    }

    q = (int *) ((int) p + 4);
    w = p->unk_04;
    hh = q[1];

    mark = 0xfff1;
    x0 = 0;
    y0 = 0;
    x1 = 0;
    y1 = 0;
    func_0204f800(&x0, &y0, 1, 1, 0, 0);
    func_0204f800(&x1, &y1, w - 2, hh - 2, 0xf, 0xf);

    y = y0;
    x = x0;
    if (x <= x1) {
        yi1 = y >> 4;
        while (x <= x1) {
            func_0204ed08(p, x, y);
            xi = x >> 4;
            e1 = func_0204f5e0(p, xi, yi1, x - (xi << 4), y - (yi1 << 4), 0);
            if (e1 != 0) {
                if (Chk(e1)) {
                    if (func_0204ba94(e1) == 0) {
                        func_0204f538(p, &mark, x, y, 0);
                    }
                }
            }
            x++;
        }
    }

    for (y = y0; y <= y1; y++) {
        x = x0;
        func_0204ed08(p, x, y);
        xi = x >> 4;
        yi2 = y >> 4;
        e2 = func_0204f5e0(p, xi, yi2, x - (xi << 4), y - (yi2 << 4), 0);
        if (e2 != 0) {
            if (Chk(e2)) {
                if (func_0204ba94(e2) == 0) {
                    func_0204f538(p, &mark, x, y, 0);
                }
            }
        }
        x = x1;
        func_0204ed08(p, x, y);
        xi = x >> 4;
        yi2 = y >> 4;
        e3 = func_0204f5e0(p, xi, yi2, x - (xi << 4), y - (yi2 << 4), 0);
        if (e3 != 0) {
            if (Chk(e3)) {
                if (func_0204ba94(e3) == 0) {
                    func_0204f538(p, &mark, x, y, 0);
                }
            }
        }
    }
}
