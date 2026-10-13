/* func_ov003_0220cd84 @ 0x0220cd84, 0x150 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern void *data_ov003_02238128;
extern void *data_021c80bc;
extern void func_0200fa1c(int *out, void *self, void *p5c, void *p8e, void *tbl);
extern void func_0204f818(volatile int *px, volatile int *pz, void *p);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_ov003_02224384(int h, int *pos, int k);

void func_ov003_0220cd84(char *self)
{
    volatile int px, pz;
    int tmp[3];
    int pos[2];
    int lx, lz;
    int cx, cz;
    u16 *o;
    int j, h, g, f, e, d, c, b, a;
    unsigned int ok;
    int x;

    px = 0;
    pz = 0;
    func_0200fa1c(tmp, self, self + 0x5c, self + 0x8e, &data_ov003_02238128);
    func_0204f818(&px, &pz, tmp);
    ok = 0;
    x = px;
    if (px == *(int *) (self + 0x8d0) && pz == *(int *) (self + 0x8d4)) {
        ok = 1;
    }
    if (ok > 0) {
        *(int *) (self + 0x8d0) = x;
        *(int *) (self + 0x8d4) = pz;
        return;
    }
    *(int *) (self + 0x8d0) = x;
    *(int *) (self + 0x8d4) = pz;
    lx = px;
    lz = pz;
    cx = lx >> 4;
    cz = lz >> 4;
    o = func_0204f5e0(data_021c80bc, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
    if (o == 0) {
        return;
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
        return;
    }
    pos[0] = px;
    pos[1] = pz;
    func_ov003_02224384(*(int *) (self + 0x800), pos, 1);
}
