/* func_02046df4 @ 0x02046df4, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    int nx;
    int nz;
} Size;
typedef struct {
    u8 pad_00[0xc];
    Size sz;
} UnkStruct_02046df4;

extern u16 *func_0204f5e0(UnkStruct_02046df4 *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204f538(UnkStruct_02046df4 *ctx, u16 *w, int x, int z, int layer);

void func_02046df4(int p0, UnkStruct_02046df4 *o)
{
    u16 t;
    int cx;
    unsigned int idx;
    int nx;
    u16 w;
    u16 *e;
    int x;
    Size *s;
    int nz;
    unsigned int v;
    int z;
    int cz;
    int ok;
    u8 layer;

    if (o == 0) {
        return;
    }
    s = &o->sz;
    nx = s->nx;
    nz = s->nz;
    layer = 0;
    do {
        z = 0;
        while (z < nz) {
            x = 0;
            if (nx > 0) {
                cz = z >> 4;
                for (; x < nx; x++) {
                    cx = x >> 4;
                    e = func_0204f5e0(o, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (e != 0) {
                        ok = 0;
                        v = *e;
                        if (v >= 0x1531 && v <= 0x153a) {
                            ok = 1;
                        }
                        if (ok != 0) {
                            if (v >= 0x1531 && v <= 0x153a) {
                                idx = v - 0x1531;
                            } else {
                                idx = -1;
                            }
                            if (idx < 10) {
                                t = idx + 0x154a;
                            } else {
                                t = 0x154a;
                            }
                            w = t;
                            func_0204f538(o, &w, x, z, layer);
                        }
                    }
                }
            }
            z++;
        }
        layer++;
    } while (layer < 2);
}
