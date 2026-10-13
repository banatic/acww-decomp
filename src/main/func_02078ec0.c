/* func_02078ec0 @ 0x02078ec0, 0x17c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021c80bc;
extern u8 data_020e54a8;
extern int func_0204ee20(void *ctx, int x, int z);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bd08(u16 *e);
extern int func_0204bcdc(u16 *e);
extern int func_0204ba94(u16 *e);
extern int func_0207903c(int x, int z);

int func_02078ec0(int x, int z, void *ctx)
{
    int result;
    u16 *e;
    int cx, cz;
    unsigned int p;
    unsigned int q;
    int n, m;
    int h, g, f, ee, d, c, b, a;
    unsigned int v;

    result = 0;
    if (ctx == 0) {
        ctx = data_021c80bc;
    }
    if (ctx == 0) {
        goto end;
    }
    if (func_0204ee20(ctx, x, z) == 0) {
        goto end;
    }
    cx = x >> 4;
    cz = z >> 4;
    e = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (e == 0) {
        goto end;
    }
    if (*e == 0xfff1) {
        goto act;
    }
    if (func_0204bd08(e) != 0) {
        goto act;
    }
    p = 0;
    v = *e;
    if (v >= 0xa7 && v <= 0xc6) {
        p = 1;
    }
    if (p != 0) {
        goto act;
    }
    if (data_020e54a8 == 0) {
        q = 1;
    } else {
        q = 0;
    }
    if (q != 0) {
        if (func_0204bcdc(e) != 0) {
            goto act;
        }
    }
    if (func_0204ba94(e) != 0) {
        goto act;
    }
    n = 1;
    m = 1;
    v = *e;
    if (!(v == 0x25 || v == 0x5c)) {
        m = 0;
    }
    if (m == 0) {
        if (v != 0xc7) {
            n = 0;
        }
    }
    if (n != 0) {
        goto act;
    }
    h = 1;
    g = 1;
    f = 1;
    ee = 1;
    d = 1;
    c = 1;
    b = 1;
    a = 0;
    if (v <= 5) {
        a = 1;
    }
    if (a == 0) {
        if (!(v >= 6 && v <= 0xb)) {
            b = 0;
        }
    }
    if (b == 0) {
        if (!(v >= 0xc && v <= 0x11)) {
            c = 0;
        }
    }
    if (c == 0) {
        if (!((v >= 0x12 && v <= 0x19) || v == 0x1c)) {
            d = 0;
        }
    }
    if (d == 0) {
        if (!((v >= 0x8a && v <= 0x8f) || (v >= 0x90 && v <= 0x95) || (v >= 0x96 && v <= 0x9b) || (v >= 0x9c && v <= 0xa3) ||
              v == 0xa5)) {
            ee = 0;
        }
    }
    if (ee == 0) {
        if (v != 0x1a) {
            f = 0;
        }
    }
    if (f == 0) {
        if (v != 0xa4) {
            g = 0;
        }
    }
    if (g == 0) {
        if (v != 0x1d) {
            h = 0;
        }
    }
    if (h == 0) {
        goto end;
    }
act:
    if (func_0207903c(x, z) == 0) {
        result = 1;
    }
end:
    return result;
}
