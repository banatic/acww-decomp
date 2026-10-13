/* func_0205ab10 @ 0x0205ab10, 0x14c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    unsigned int unk_00, z0, x1, z1;
} Rect;

extern void MI_CpuFill8(void *p, int v, int n);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(u16 *e);
extern int func_0204bc64(u16 *e);
extern int func_02053cf0(int v);
extern int func_02053cbc(int v);
extern int FX_Div(int a, int b);

int func_0205ab10(Rect *r, void *ctx)
{
    unsigned int count;
    unsigned int pass;
    int cz;
    u16 *e;
    int v;
    unsigned int i;
    int slot;
    int a;
    int b;
    int z;
    unsigned int m;
    int n;
    int x;
    int scale;
    u8 *p;
    int d;
    u8 counts[0xd];
    u16 ids[0x18];

    MI_CpuFill8(counts, 0, 0xd);
    for (i = 0; i < 0x18; i++) {
        ids[i] = 0xffff;
    }
    count = 0;
    pass = 0;
    slot = 0;
    do {
        for (z = r->z0; z <= r->z1; z++) {
            x = r->unk_00;
            if (x <= r->x1) {
                cz = z >> 4;
                for (; x <= r->x1; x++) {
                    int cx = x >> 4;
                    e = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), pass);
                    if (e == 0) {
                        continue;
                    }
                    if (func_0204bcdc(e) == 0) {
                        continue;
                    }
                    v = func_0204bc64(e);
                    for (i = slot; i < 0x18; i++) {
                        if (v == ids[i]) {
                            break;
                        }
                        if (ids[i] == 0xffff) {
                            ids[i] = (u16) v;
                            break;
                        }
                    }
                    a = func_02053cf0(v);
                    b = func_02053cbc(v);
                    counts[a]++;
                    counts[b]++;
                    count++;
                }
            }
        }
        pass = (u8) (pass + 1);
    } while (pass < 2);
    if (count < 0xa) {
        goto ret0;
    }
    n = 0;
    for (i = 0; i < 0x18; i++) {
        if (ids[i] != 0xffff) {
            n++;
        }
    }
    m = 0;
    scale = count << 0xd;
    p = counts;
    for (; m < 0xd; m++) {
        if (m == 0) {
            continue;
        }
        d = FX_Div(p[m] << 0xc, scale);
        if (d >= 0xe66) {
            return 0x258 * n;
        }
        if (d >= 0xb33) {
            return 0xc8 * n;
        }
    }
ret0:
    return 0;
}
