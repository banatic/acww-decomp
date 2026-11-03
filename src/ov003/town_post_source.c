/* town_post_source: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022273f8 @ 0x022273f8, 0x5c bytes, Thumb
 * func_ov003_02227394 @ 0x02227394, 0x64 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 *p;
    u8 kind;
    u8 pad_05;
    u16 count;
} UnkStruct_022273f8;

extern UnkStruct_022273f8 data_ov003_02236b0c[];
extern u16 *func_0204f5e0(void *g, int gx, int gz, int ox, int oz, int f);
extern void *data_021c80bc;

u8 *func_ov003_022273f8(u16 *pv)
{
    u8 *r;
    u16 v;
    int hi;
    UnkStruct_022273f8 *e;
    int lo;

    r = 0;
    if (pv != 0) {
        v = *pv;
        hi = (v & 0xf000) >> 12;
        lo = v & 0xfff;
        e = data_ov003_02236b0c;
        while (e->p != 0) {
            if (hi == e->kind) {
                if (e->count > lo) {
                    r = e->p + 3 * lo;
                }
                break;
            }
            e++;
        }
        if (r != 0 && *r == 0) {
            r = 0;
        }
    }
    return r;
}

int func_ov003_02227394(void *a, int *p1, int *p2, int *p3, int x, int z)
{
    void *g;
    u8 *r;
    int ok;
    int gx, gz, lx, lz;

    g = data_021c80bc;
    ok = 0;
    if (g != 0) {
        lx = *(volatile int *) &x;
        lz = *(volatile int *) &z;
        gx = lx >> 4;
        gz = lz >> 4;
        r = func_ov003_022273f8(func_0204f5e0(g, gx, gz, lx - (gx << 4), lz - (gz << 4), 0));
        if (r != 0 && r[2] != 0) {
            *p1 = ((int) r[0] << 12) >> 4;
            *p2 = ((int) r[1] << 12) >> 4;
            *p3 = r[2];
            ok = 1;
        }
    }
    return ok;
}
