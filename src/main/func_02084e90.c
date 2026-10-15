/* func_02084e90 @ 0x02084e90, 0xf4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_021c80bc;
extern void MI_CpuFill8(void *dst, int fill, unsigned int len);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_0204f794(void *v, int x, int z);
extern int func_02034270(void *a, void *v, int c, int d);
extern int func_020341c8(void *a, int f);
extern void func_0203423c(void *a);
extern int func_02084e20(void *self, int x, int z);
extern int func_02084e40(void *self, int x, int z);
extern int func_02084e68(void *self, int x, int z);

int func_02084e90(void *self)
{
    int v[3];
    int w[16];
    void *ctx;
    u16 *e;
    int z, x;

    ctx = data_021c80bc;
    MI_CpuFill8(self, 0, 0x20);
    if (ctx == 0) {
        goto fail;
    }
    e = func_0204f5e0(ctx, 0, 0, 0, 0, 0);
    if (e == 0) {
        goto fail;
    }
    for (z = 0; z < 16; z++) {
        for (x = 0; x < 16; x++) {
            func_0204f794(v, x, z);
            func_02034270(w, v, 0, 0);
            if (*e == 0xfff1) {
                if (func_020341c8(w, 1) == 0) {
                    func_02084e68(self, x, z);
                }
            }
            e++;
            func_0203423c(w);
        }
    }
    for (z = 0; z < 14; z++) {
        for (x = 0; x < 16; x++) {
            if (func_02084e20(self, x, z) != 0 && func_02084e20(self, x + 1, z) == 0 && func_02084e20(self, x - 1, z) == 0 &&
                func_02084e20(self, x, z + 1) == 0 && func_02084e20(self, x, z - 1) == 0) {
                func_02084e40(self, x, z);
            }
        }
    }
    return 1;
fail:
    return 0;
}
