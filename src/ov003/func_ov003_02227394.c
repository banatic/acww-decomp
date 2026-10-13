/* func_ov003_02227394 @ 0x02227394, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_0204f5e0(void *g, int gx, int gz, int ox, int oz, int f);
extern u8 *func_ov003_022273f8(u16 *p);
extern void *data_021c80bc;

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
