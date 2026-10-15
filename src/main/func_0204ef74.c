/* func_0204ef74 @ 0x0204ef74, 0x2ec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_0204f5e0(void *b, int cx, int cy, int ox, int oy, int layer);
extern int func_0204bd08(u16 *p);
extern int func_0204bcdc(u16 *p);
extern void func_0203a76c(u16 v);
extern void *func_020b3b50(u16 *o);
extern unsigned int func_020b3eb8(void *l);
extern int func_020b3e08(void *l, int *a, int *b, unsigned int k);
extern unsigned int func_020b3f2c(void *l);
extern int func_020b3e58(void *l, int *a, int *b, unsigned int k);
extern int func_02073d90(void *p);
extern int func_0204bb54(u16 *p);
extern int func_0204bb2c(u16 *p);
extern int func_020b0650(u8 *base, unsigned int idx);
extern int func_0204bc64(u16 *p);
extern int func_0204ba94(u16 *p);
extern int func_0204b5ac(u16 *p);
extern int func_0204f538(void *w, u16 *st, int x, int y, int f);
extern int func_0204f31c(void *w, int x, int y);

extern void *data_020ccf94;
extern u8 data_021f3b56[];

int func_0204ef74(void *grid, u16 *item1, u16 *item2, u16 *item3, volatile int x, volatile int y)
{
    int result;
    void *list = 0;
    unsigned int n;
    unsigned int n2;
    int i, h, g, f, e, d, c, b, a;
    int ty2;
    int px;
    int py;
    void *gp;
    int ty;
    unsigned int j;
    u16 *t3;
    int cx, cy;
    int xl, yl;
    unsigned int k;
    int tx, tx2;
    u16 *tile;
    u16 *t2;
    int ok;
    u16 id;
    int m;
    unsigned int t;
    int cx2, cy2, cx3, cy3;
    u16 buf[3];
    int ox, oy;

    result = 0;
    xl = x;
    yl = y;
    cx = xl >> 4;
    cy = yl >> 4;
    tile = func_0204f5e0(grid, cx, cy, xl - (cx << 4), yl - (cy << 4), 0);
    if (tile != 0) {
        buf[0] = *tile;
        if (func_0204bd08(&buf[0]) != 0 || func_0204bcdc(&buf[0]) != 0) {
            func_0203a76c(buf[0]);
        }
    }
    ok = 0;
    id = *item2;
    if (id >= 0x5000 && id <= 0x5021) {
        ok = 1;
    }
    if (ok != 0) {
        list = func_020b3b50(item2);
    }
    if (list != 0) {
        n = func_020b3eb8(list);
        k = 0;
        px = x;
        py = y;
        gp = data_020ccf94;
        for (; k < n; k++) {
            if (func_020b3e08(list, &ox, &oy, k) != 0) {
                tx = px + ox;
                ty = py + oy;
                cx2 = tx >> 4;
                cy2 = ty >> 4;
                t2 = func_0204f5e0(grid, cx2, cy2, tx - (cx2 << 4), ty - (cy2 << 4), 0);
                if (t2 != 0) {
                    if (func_0204bcdc(t2) != 0 || func_0204bd08(t2) != 0) {
                        if (func_02073d90(gp) == 0) {
                            func_0203a76c(*t2);
                        }
                    } else if (func_0204bb54(t2) != 0) {
                        func_020b0650(data_021f3b56, func_0204bb2c(t2));
                    }
                }
                func_0204f538(grid, item3, tx, ty, 0);
                func_0204f31c(grid, tx, ty);
            }
        }
        func_0204f538(grid, item1, x, y, 0);
        if (func_0204bcdc(item3) != 0) {
            buf[2] = 0xf030;
            m = func_0204bc64(item3) == func_0204bc64(&buf[2]);
        } else {
            m = *item3 == 0xf030;
        }
        if (m != 0) {
            n2 = func_020b3f2c(list);
            j = 0;
            for (; j < n2; j++) {
                if (func_020b3e58(list, &ox, &oy, j) != 0) {
                    tx2 = px + ox;
                    ty2 = py + oy;
                    cx3 = tx2 >> 4;
                    cy3 = ty2 >> 4;
                    t3 = func_0204f5e0(grid, cx3, cy3, tx2 - (cx3 << 4), ty2 - (cy3 << 4), 0);
                    if (t3 != 0) {
                        i = 1;
                        h = 1;
                        g = 1;
                        f = 1;
                        e = 1;
                        d = 1;
                        c = 1;
                        b = 1;
                        a = 0;
                        t = *t3;
                        if (t >= 0x26 && t <= 0x2a) {
                            a = 1;
                        }
                        if (a == 0) {
                            if (t < 0x5d || t > 0x61) {
                                b = 0;
                            }
                        }
                        if (b == 0) {
                            if (t < 0x2f || t > 0x56) {
                                c = 0;
                            }
                        }
                        if (c == 0) {
                            if (t < 0x57 || t > 0x5b) {
                                d = 0;
                            }
                        }
                        if (d == 0) {
                            if (t < 0x66 || t > 0x68) {
                                e = 0;
                            }
                        }
                        if (e == 0) {
                            if (t != 0x69) {
                                f = 0;
                            }
                        }
                        if (f == 0) {
                            if (t < 0x6a || t > 0x6c) {
                                g = 0;
                            }
                        }
                        if (g == 0) {
                            if (t != 0x6d) {
                                h = 0;
                            }
                        }
                        if (h == 0) {
                            if (t < 0xc8 || t > 0xcf) {
                                i = 0;
                            }
                        }
                        if (i == 0 || func_0204ba94(t3) != 0) {
                            if (func_0204b5ac(t3) == -1) {
                                continue;
                            }
                        }
                        buf[1] = 0xfff1;
                        func_0204f538(grid, &buf[1], tx2, ty2, 0);
                    }
                }
            }
        }
        result = 1;
    }
    return result;
}
