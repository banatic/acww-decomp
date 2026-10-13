/* func_ov003_0222ee10 @ 0x0222ee10, 0x170 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern void func_0204f818(volatile int *px, volatile int *pz, void *p);
extern void *func_0204e414(void);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);

int func_ov003_0222ee10(int unused, char *self)
{
    volatile int px, pz;
    int lx, lz;
    int cx, cz;
    u16 *o;
    void *ctx;
    int j, h, g, f, e, d, c, b, a;
    int k;

    k = *(signed char *) (self + 0x24d);
    if (k < 0) {
        return 0;
    }
    switch (k) {
        case 9:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 31:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 52:
            px = 0;
            pz = 0;
            func_0204f818(&px, &pz, self + 0x204);
            ctx = func_0204e414();
            if (ctx == 0) {
                break;
            }
            lx = px;
            lz = pz;
            cx = lx >> 4;
            cz = lz >> 4;
            o = func_0204f5e0(ctx, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
            if (o == 0) {
                return 0;
            }
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
                return 0;
            }
            break;
    }
    return 1;
}
