/* func_020131dc @ 0x020131dc, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, z;
} Pt;

extern void MI_CpuFill8(void *p, int v, int n);
extern void func_0204f800(int *cx, int *cz, int a, int b, int c, int d);
extern int func_0204ed58(void *ctx, int x, int z);
extern int func_020644cc(int n);

void func_020131dc(Pt *out, int unused, int *p, void *ctx)
{
    int k;
    int x;
    int z;
    u16 *row2;
    u16 *row;
    int x2;
    int cx;
    int cz;
    int n;
    int z2;
    u16 grid[16];

    n = 0;
    cx = 0;
    cz = 0;
    MI_CpuFill8(grid, 0, 0x20);
    func_0204f800(&cx, &cz, p[0], p[1], 0, 0);
    for (z = 0; z < 16; z++) {
        x = 0;
        row = &grid[z];
        for (; x < 16; x++) {
            if (func_0204ed58(ctx, cx + x, cz + z) != 0) {
                *row = (u16) (*row | (1 << x));
                n++;
            }
        }
    }
    if (n > 0) {
        k = func_020644cc(n);
        for (z2 = 0; z2 < 16; z2++) {
            x2 = 0;
            row2 = &grid[z2];
            for (; x2 < 16; x2++) {
                if ((*row2 >> x2) & 1) {
                    if (k == 0) {
                        out->x = 0;
                        out->z = 0;
                        out->x = cx + x2;
                        out->z = cz + z2;
                        return;
                    }
                    k--;
                }
            }
        }
    }
    out->x = 0;
    out->z = 0;
}
