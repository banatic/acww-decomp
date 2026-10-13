/* func_ov072_022792e4 @ 0x022792e4, 0x140 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern void func_0204f800(int *px, int *pz, int a, int b, int c, int d);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204c71c(u16 *o);
extern int func_0204ba94(u16 *o);

int func_ov072_022792e4(int *a0, int *a1, void *ctx)
{
    int px, pz;
    int lx, lz;
    int cx, cz;
    int i;
    u16 *o;
    int j, h, g, f, e, d, c, b, a;
    int ok;

    px = 0;
    pz = 0;
    for (i = 1; i <= 2; i++) {
        func_0204f800(&px, &pz, a0[0], a0[1], a1[0], a1[1] + i);
        lx = px;
        lz = pz;
        cx = lx >> 4;
        cz = lz >> 4;
        o = func_0204f5e0(ctx, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
        if (o == 0) {
            goto fail;
        }
        ok = 0;
        if (*o >= 0x5000 && *o <= 0x5021) {
            ok = 1;
        }
        if (ok != 0) {
            goto fail;
        }
        if (func_0204c71c(o) != 0) {
            goto fail;
        }
        if (func_0204ba94(o) != 0) {
            continue;
        }
        {
            j = 1;
            h = 1;
            g = 1;
            f = 1;
            e = 1;
            d = 1;
            c = 1;
            b = 1;
            a = 0;
            if (*o >= 0x26 && *o <= 0x2a) {
                a = 1;
            }
            if (a == 0) {
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
            if (j == 0) {
                continue;
            }
        }
    fail:
        return 0;
    }
    return 1;
}
