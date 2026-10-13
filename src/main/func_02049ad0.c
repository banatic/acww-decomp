/* func_02049ad0 @ 0x02049ad0, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    u16 unk_00;
} Entry;
typedef struct {
    int a;
    int b;
} UnkStruct_02049ad0;
typedef struct {
    int pad_00;
    UnkStruct_02049ad0 sub;
} UnkStruct_02049ad0_2;

extern Entry *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_020644cc(int n);
extern void func_0204a25c(void *ctx, int x, int z, int k, int m);
extern const int data_020cb4e8[];

void func_02049ad0(int p0, UnkStruct_02049ad0_2 *o)
{
    int z;
    int ok;
    int x;
    Entry *e;
    unsigned int v;
    u16 out;
    int ok2;
    int nx;
    int nz;
    int cz;
    UnkStruct_02049ad0 *s;
    int cx;

    s = &o->sub;
    nx = s->a << 4;
    nz = s->b << 4;
    for (z = 0; z < nz; z++) {
        x = 0;
        if (nx > 0) {
            cz = z >> 4;
            for (; x < nx; x++) {
                cx = x >> 4;
                e = func_0204f5e0(o, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                if (e == 0) {
                    continue;
                }
                out = 0xffff;
                ok = 0;
                v = e->unk_00;
                if (v >= 0x6e && v <= 0x89) {
                    ok = 1;
                }
                if (ok != 0) {
                    out = 0xfff1;
                } else {
                    ok2 = 0;
                    if (v <= 0x1a) {
                        ok2 = 1;
                    }
                    if (ok2 != 0) {
                        if (func_020644cc(100) < data_020cb4e8[v]) {
                            out = e->unk_00 + 0x6e;
                        }
                    } else if (v == 0x1d) {
                        if (func_020644cc(100) < 0x1e) {
                            out = 0x1e;
                        }
                    } else if (v >= 0x8a && v <= 0xa4) {
                        out = v - 0x8a;
                    } else if (v == 0xa5) {
                        out = 0x1c;
                    }
                }
                if (out != 0xffff) {
                    func_0204a25c(o, x, z, out, 0);
                }
            }
        }
    }
}
