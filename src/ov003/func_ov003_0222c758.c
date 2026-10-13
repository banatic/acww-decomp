/* func_ov003_0222c758 @ 0x0222c758, 0x130 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

extern void *func_0204e414(void);
extern void MI_CpuFill8(void *p, int v, unsigned int n);
extern void *func_0204f5e0(void *h, int gx, int gz, int ox, int oz, int f);
extern int func_0204bbec(void *e);
extern int func_02031b5c(int x, int z);
extern u16 data_ov003_02260794[];
extern u16 data_ov003_02260594[];

void func_ov003_0222c758(void)
{
    u8 k;
    void *h;
    int z;
    int gx;
    u16 *ai, *bi;
    int gz;
    u16 *aj, *bj;
    int cz;
    u16 *ak, *bk;
    int x;
    u8 j;
    u8 i, m;
    int cx;
    void *e;

    h = func_0204e414();
    if (h == 0) {
        return;
    }
    MI_CpuFill8(data_ov003_02260794, 0, 0x200);
    MI_CpuFill8(data_ov003_02260594, 0, 0x200);
    i = 0;
    while (i < 4) {
        gx = (u8) ((i + 1) << 4);
        j = 0;
        ai = data_ov003_02260794 + i * 16;
        bi = data_ov003_02260594 + i * 16;
        while (j < 4) {
            gz = (u8) ((j + 1) << 4);
            k = 0;
            aj = ai + j * 64;
            bj = bi + j * 64;
            while (k < 0x10) {
                m = 0;
                z = gz + k;
                cz = z >> 4;
                ak = aj + k;
                bk = bj + k;
                while (m < 0x10) {
                    x = gx;
                    x += m;
                    cx = x >> 4;
                    e = func_0204f5e0(h, cx, cz, x - (cx << 4), z - (cz << 4), 0);
                    if (e != 0) {
                        if (func_0204bbec(e) != 0 || func_02031b5c(gx + m, z) == 1) {
                            *ak |= 1 << m;
                            *bk |= 1 << m;
                        } else if (func_02031b5c(gx + m, z) == 2) {
                            *bk |= 1 << m;
                        }
                    }
                    m++;
                }
                k++;
            }
            j++;
        }
        i++;
    }
}
