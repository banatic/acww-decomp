/* func_02047500 @ 0x02047500, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 *func_0204f5e0(int ctx, int cx, int cz, int dx, int dz, int layer);
extern u16 func_020475b0(int a, u16 *p, int flag);
extern void func_0204f800(int *px, int *pz, int cx, int cz, int dx, int dz);
extern void func_0204a25c(int ctx, int x, int z, int k, int m);

void func_02047500(int a, int ctx, int nz, int nx)
{
    int j, i, k;
    u16 *q;
    u16 v;
    int ox, oz;

    for (i = 0; i < nx; i++) {
        for (j = 0; j < nz; j++) {
            q = func_0204f5e0(ctx, j + 1, i + 1, 0, 0, 0);
            for (k = 0; k < 256; k++) {
                if (q != 0 && *q != 0xfff1) {
                    v = func_020475b0(a, q, 0);
                    if (v != 0xfff1) {
                        func_0204f800(&ox, &oz, j + 1, i + 1, k % 16, k / 16);
                        func_0204a25c(ctx, ox, oz, v, 0);
                    }
                }
                q++;
            }
        }
    }
}
