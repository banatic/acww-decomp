/* func_020499cc @ 0x020499cc, 0x104 bytes, Thumb, module main
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
} UnkStruct_020499cc;
typedef struct {
    int pad_00;
    UnkStruct_020499cc sub;
} UnkStruct_020499cc_2;

extern Entry *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_020644cc(int n);
extern void func_0204a25c(void *ctx, int x, int z, int k, int m);
extern const int data_020cb554[];

void func_020499cc(int p0, UnkStruct_020499cc_2 *o, unsigned int seed)
{
    int x;
    int out;
    int z;
    Entry *e;
    unsigned int v;
    int ok;
    int ok2;
    int nx;
    int nz;
    int cz;
    UnkStruct_020499cc *s;
    int cx;
    unsigned int rem;

    s = &o->sub;
    nx = s->a << 4;
    nz = s->b << 4;
    z = 0;
    rem = (int) seed % 7;
    for (; z < nz; z++) {
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
                    if (rem == 0) {
                        out = 0xfff1;
                    }
                } else if (v == 0x1e) {
                    if (rem == 0) {
                        if (func_020644cc(100) < 0x1e) {
                            out = 0xfff1;
                        }
                    }
                } else {
                    ok2 = 0;
                    if (v <= 0x1a) {
                        ok2 = 1;
                    }
                    if (ok2 != 0) {
                        if (func_020644cc(100) < data_020cb554[v]) {
                            out = (u16) (e->unk_00 + 0x6e);
                        }
                    } else if (v == 0x1d) {
                        if (func_020644cc(100) < 0x1e) {
                            out = 0x1e;
                        }
                    }
                }
                if (out != 0xffff) {
                    func_0204a25c(o, x, z, out, 0);
                }
            }
        }
    }
}
