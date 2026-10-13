/* func_ov003_0222c4b8 @ 0x0222c4b8, 0x1d4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

typedef struct {
    int x, y, z;
} UnkStruct_0222c4b8;

extern void func_0204f818(int *, int *, UnkStruct_0222c4b8 *);

void func_ov003_0222c4b8(u8 *self, int wx, int wz, int rx, u8 up, u8 dn)
{
    UnkStruct_0222c4b8 v;
    int ox, oy;
    int y1;
    int cx;
    int j;
    int x1;
    u8 *q4;
    int idx;
    int lo;
    int xoff;
    u8 *q;
    u8 *q2;
    int mask;
    int cy;
    int val;
    int i;
    int w;
    int m;
    int y0;
    int fx;
    int fy;
    int h;
    int n;
    u8 *base;
    int x0;
    int ww;
    int X;
    int hh;
    int u;
    int k;
    int Y;

    ox = 0;
    oy = 0;
    v.x = wx;
    v.y = 0;
    v.z = wz;
    func_0204f818(&ox, &oy, &v);

    X = ox;
    x0 = X - rx;
    u = up;
    Y = oy;
    y0 = Y - u;
    x1 = X + rx;
    y1 = Y + dn;

    if (x0 < 0x10) {
        x0 = 0x10;
    }
    if (y0 < 0x10) {
        y0 = 0x10;
    }
    if (x1 > 0x50) {
        x1 = 0x50;
    }
    if (y1 > 0x50) {
        y1 = 0x50;
    }

    if (x0 < 0x10) {
        return;
    }
    if (x0 >= x1) {
        return;
    }
    if (x1 > 0x50) {
        return;
    }
    if (y0 < 0x10) {
        return;
    }
    if (y0 >= y1) {
        return;
    }
    if (y1 > 0x50) {
        return;
    }

    cx = x0 >> 4;
    cy = y0 >> 4;
    fx = x0 - (cx << 4);
    fy = y0 - (cy << 4);

    w = fx + rx * 2;
    ww = (w > 0x10) ? 0x10 : w;
    h = dn + (fy + u);
    hh = (h > 0x10) ? 0x10 : h;

    if (cx == 1) {
        X -= 0x10;
        x0 = X - rx;
        if (x0 < 0) {
            ww += x0;
        }
    }
    if (cy == 1) {
        Y -= 0x10;
        if (Y - u < 0) {
            hh += Y - u;
        }
    }

    lo = (fx > 0) ? (2 << fx) - 1 : 0;
    mask = (u16) (((2 << ww) - 1) - lo);

    xoff = cx * 0x20;
    base = self + (cy - 1) * 0x80 + xoff;
    q = base - 0x20;
    for (j = fy; j < hh; j++) {
        idx = j * 2;
        val = *(u16 *) (q + idx);
        val |= mask;
        *(u16 *) (q + idx) = val;
    }

    if (h > 0x10 && cy < 4) {
        n = h;
        n -= 0x10;
        q2 = self + cy * 0x80 + xoff - 0x20;
        for (i = 0; i < n; i++) {
            idx = i * 2;
            val = *(u16 *) (q2 + idx);
            val |= mask;
            *(u16 *) (q2 + idx) = val;
        }
    }

    if (w > 0x10 && cx < 4) {
        mask = (u16) ((2 << (w - 0x10)) - 1);
        for (k = fy; k < hh; k++) {
            idx = k * 2;
            val = *(u16 *) (base + idx);
            val |= mask;
            *(u16 *) (base + idx) = val;
        }
    }

    if (h > 0x10 && w > 0x10 && cx < 4 && cy < 4) {
        mask = (u16) ((2 << (w - 0x10)) - 1);
        w -= 0x10;
        h -= 0x10;
        q4 = self + cy * 0x80 + xoff;
        for (m = 0; m < h; m++) {
            *(u16 *) (q4 + m * 2) |= mask;
        }
    }
}
