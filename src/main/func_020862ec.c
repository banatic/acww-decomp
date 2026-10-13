/* func_020862ec @ 0x020862ec, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    u16 unk_00;
} Entry;
typedef struct {
    int x;
    int z;
} Pt;

extern int func_0204f490(void *, int *, int *, int *, int *, u16 *, u16 *, int, int);
extern void func_0204f800(int *, int *, int, int, int, int);
extern Entry *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_020864f4(unsigned int *out, Entry *e);
extern int func_020863dc(Pt *pt);
extern int func_020864cc(unsigned int mask);

int func_020862ec(int p0, void *ctx)
{
    u16 h[2];
    int a, b, c, d;
    int px, pz;
    unsigned int out;
    unsigned int mask;
    int count;
    int x, z;
    int cx, cz;
    Entry *e;
    Pt pt;
    int result;

    a = 0;
    b = 0;
    c = 0;
    d = 0;
    h[0] = 0x5014;
    h[1] = 0x501a;
    result = 0;
    if (func_0204f490(ctx, &a, &b, &c, &d, &h[0], &h[1], 1, 0) != 0) {
        mask = 0;
        px = 0;
        pz = 0;
        count = 0;
        out = 0;
        func_0204f800(&px, &pz, a, b, c, d);
        for (z = pz - 1; z < pz + 9; z++) {
            x = px - 5;
            if (x < px + 5) {
                cz = z >> 4;
                for (; x < px + 5; x++) {
                    cx = x >> 4;
                    e = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                    if (e == 0) {
                        continue;
                    }
                    if (func_020864f4(&out, e) == 0) {
                        continue;
                    }
                    pt.x = x;
                    pt.z = z;
                    if (func_020863dc(&pt) == 0) {
                        continue;
                    }
                    if (out < 0x20) {
                        mask |= 1 << out;
                    }
                    count++;
                }
            }
        }
        result = func_020864cc(mask);
        result = count * result;
        result = (result + 2) / 3;
    }
    return result;
}
