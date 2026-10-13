/* func_ov003_022243d0 @ 0x022243d0, 0x1d8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern int data_ov003_0223cf70;
extern void *func_0204e414(void);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204ba94(u16 *o);
extern void func_0204f794(int *t, int x, int z);
extern int func_0203adc4(int *t, int b, int c);
extern int func_02044858(int a);
extern int func_0204b910(u16 *o);
extern int func_02045bb8(unsigned char n, unsigned char i);
extern void *func_02045bac(int r);
extern void func_0204629c(void *e);
extern void func_02045ea8(int *t, int n, int k);

int func_ov003_022243d0(int a, int *pos)
{
    int ret;
    void *ctx;
    u16 *o;
    int lx, lz;
    int cx, cz;
    int j, h, g, f, e, d, c, b, aa;
    int n, m, i, r;
    int t2[2];
    int t[4];

    ret = 0;
    if (data_ov003_0223cf70 != 0) {
        ctx = func_0204e414();
        if (ctx != 0) {
            lx = pos[0];
            lz = pos[1];
            cx = lx >> 4;
            cz = lz >> 4;
            o = func_0204f5e0(ctx, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
            if (o != 0) {
                j = 1;
                h = 1;
                g = 1;
                f = 1;
                e = 1;
                d = 1;
                c = 1;
                b = 1;
                aa = 0;
                if (*o >= 0x26 && *o <= 0x2a) {
                    aa = 1;
                }
                if (aa == 0) {
                    if (!(*o >= 0x5d && *o <= 0x61)) {
                        b = 0;
                    }
                }
                if (b == 0) {
                    if (!(*o >= 0x2f && *o <= 0x56)) {
                        c = 0;
                    }
                }
                if (c == 0) {
                    if (!(*o >= 0x57 && *o <= 0x5b)) {
                        d = 0;
                    }
                }
                if (d == 0) {
                    if (!(*o >= 0x66 && *o <= 0x68)) {
                        e = 0;
                    }
                }
                if (e == 0) {
                    if (*o != 0x69) {
                        f = 0;
                    }
                }
                if (f == 0) {
                    if (!(*o >= 0x6a && *o <= 0x6c)) {
                        g = 0;
                    }
                }
                if (g == 0) {
                    if (*o != 0x6d) {
                        h = 0;
                    }
                }
                if (h == 0) {
                    if (!(*o >= 0xc8 && *o <= 0xcf)) {
                        j = 0;
                    }
                }
                if (j != 0) {
                    if (func_0204ba94(o) == 0) {
                        func_0204f794(t, pos[0], pos[1]);
                        if (func_0203adc4(t, 0x2000, 0x2000) == 0) {
                            ret = 1;
                        }
                    }
                }
            }
        }
    }
    if (ret == 0) {
        ctx = func_0204e414();
        if (ctx != 0) {
            lx = pos[0];
            lz = pos[1];
            cx = lx >> 4;
            cz = lz >> 4;
            o = func_0204f5e0(ctx, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
            if (o != 0) {
                n = func_02044858(a);
                m = 0;
                if (*o >= 0x2f && *o <= 0x56) {
                    m = 1;
                }
                if (m != 0 || (*o >= 0xc8 && *o <= 0xcf) || (*o >= 0x57 && *o <= 0x5b)) {
                    if (func_0204b910(o) != 0) {
                        i = 0;
                        do {
                            r = func_02045bb8((unsigned char) n, (unsigned char) i);
                            if (r >= 0) {
                                func_0204629c(func_02045bac(r));
                            }
                            i++;
                        } while (i < 3);
                    }
                } else if ((*o >= 0x66 && *o <= 0x68) || (*o >= 0x6a && *o <= 0x6c)) {
                    r = func_02045bb8((unsigned char) n, 0);
                    if (r >= 0) {
                        func_0204629c(func_02045bac(r));
                    }
                }
            }
        }
        t2[0] = pos[0];
        t2[1] = pos[1];
        func_02045ea8(t2, func_02044858(a), 0);
    }
    return ret;
}
