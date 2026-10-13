/* func_ov003_022334d8 @ 0x022334d8, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern void func_ov003_02233178(void *self, short *p);
extern void func_ov003_02232f78(void *self, short *p);
extern int func_ov003_02232598(void *self, int a);
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *m, int a, int b);
extern void func_02042200(int a);
extern void *func_0204e414(void *a);
extern void func_0204f818(int *x, int *y, int *p);
extern u16 *func_0204f5e0(void *hnd, int i, int j, int u, int v, int w);
extern int func_ov003_0222d738(int *p);

void func_ov003_022334d8(char *self)
{
    int *p;
    void *hnd;
    int x, y, i, j, px, py;
    u16 v;
    u16 *e;
    int ok;

    switch (*(u8 *) (self + 0x251)) {
        case 0xb:
            func_ov003_02233178(self, (short *) (self + 0x242));
            break;
        case 9:
            func_ov003_02232f78(self, (short *) (self + 0x242));
            break;
        case 7:
        case 8:
            if (func_ov003_02232598(self, 4) != 0) {
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
                *(u8 *) (self + 0x251) = 0x13;
                p = (int *) (self + 0x204);
                p[0] = 0;
                p[1] = 0;
                p[2] = 0;
                func_02042200(0);
            }
            break;
        case 0x12:
            hnd = func_0204e414(self);
            p = (int *) (self + 0x204);
            func_0204f818(&x, &y, p);
            px = x;
            py = y;
            i = px >> 4;
            j = py >> 4;
            e = func_0204f5e0(hnd, i, j, px - (i << 4), py - (j << 4), 0);
            ok = 0;
            v = *e;
            if (v >= 0x154a && v <= 0x1553) {
                ok = 1;
            }
            if (ok == 0 || func_ov003_0222d738(p) != 0) {
                *(u8 *) (self + 0x251) = 7;
            }
            break;
    }
}
