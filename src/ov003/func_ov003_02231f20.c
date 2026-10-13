/* func_ov003_02231f20 @ 0x02231f20, 0x298 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_propagation off

extern void *func_0209d088(unsigned char *p);
extern int NNS_G3dMdlGetMdlAlpha(void *m, int a);
extern void NNS_G3dMdlSetMdlAlpha(void *m, int a, int b);
extern void func_0204f818(int *px, int *pz, int *p);
extern void *func_0204e414(void);
extern u16 *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_ov003_02232598(unsigned char *self, int a);
extern void func_ov003_02230f60(unsigned char *self);
extern void func_ov003_02233178(unsigned char *self, short *p);
extern void func_ov003_02232f78(unsigned char *self, short *p);
extern int func_ov068_02271068(unsigned char *self);
extern int func_ov068_022710e4(unsigned char *self);
extern void func_02056fcc(unsigned char *p, int a, int b, int c, int d);
extern int func_020644cc(int a);

void func_ov003_02231f20(unsigned char *self)
{
    short *p242;
    int j, h, g, f, e, d, c, b, a;
    int px, pz;
    int v[3];
    int lx, lz, t;
    int cx, cz;
    u16 *o;
    void *ctx;
    unsigned char st;

    p242 = (short *) (self + 0x242);
    NNS_G3dMdlGetMdlAlpha(func_0209d088(self + 0x130), 0);
    st = self[0x251];
    if (st != 0xb && st != 9) {
        t = *(int *) (self + 0x20c) + 0x3e8;
        v[0] = *(int *) (self + 0x21c);
        v[1] = 0;
        v[2] = t;
        func_0204f818(&px, &pz, v);
        ctx = func_0204e414();
        if (ctx != 0) {
            lx = px;
            lz = pz;
            cx = lx >> 4;
            cz = lz >> 4;
            o = func_0204f5e0(ctx, cx, cz, lx - (cx << 4), lz - (cz << 4), 0);
            if (o != 0) {
                j = 1;
                h = 1;
                g = 1;
                f = 1;
                e = 1;
                d = 1;
                c = 1;
                b = 1;
                a = 0;
                if (*o >= 0x26 && *o <= 0x2a) {
                    a = 1;
                }
                if (a == 0) {
                    if (!(*o >= 0x5d && *o <= 0x61)) {
                        b = 0;
                    }
                }
                if (b == 0) {
                    if (!(*o >= 0x2f && *o <= 0x56)) {
                        c = 0;
                    }
                }
                if (c == 0) {
                    if (!(*o >= 0x57 && *o <= 0x5b)) {
                        d = 0;
                    }
                }
                if (d == 0) {
                    if (!(*o >= 0x66 && *o <= 0x68)) {
                        e = 0;
                    }
                }
                if (e == 0) {
                    if (*o != 0x69) {
                        f = 0;
                    }
                }
                if (f == 0) {
                    if (!(*o >= 0x6a && *o <= 0x6c)) {
                        g = 0;
                    }
                }
                if (g == 0) {
                    if (*o != 0x6d) {
                        h = 0;
                    }
                }
                if (h == 0) {
                    if (!(*o >= 0xc8 && *o <= 0xcf)) {
                        j = 0;
                    }
                }
                if (j == 0) {
                    if (func_ov003_02232598(self, 3) != 0) {
                        func_ov003_02230f60(self);
                        return;
                    }
                }
            }
        }
    }
    switch (st) {
        case 2:
            if (*(unsigned char *) (self + 0x24c) != 0) {
                *(unsigned char *) (self + 0x24c) = 0;
                *(short *) (self + 0x23c) = 0x6b;
            } else {
                *(unsigned char *) (self + 0x24c) = 1;
                *(short *) (self + 0x23c) = -0x6b;
            }
            if ((((unsigned int) *(int *) (self + 0xf4)) << 4) >> 16 == 0x38) {
                self[0x251] = 0x13;
                *(short *) (self + 0x23c) = 0;
                *(int *) (self + 0x204) = *(int *) (self + 0x21c);
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0);
            }
            break;
        case 1:
            if ((((unsigned int) *(int *) (self + 0xf4)) << 4) >> 16 == 0x20) {
                *(short *) (self + 0x232) = (short) (0x14 * (func_020644cc(4) + 0xc));
                self[0x251] = 0x12;
                *p242 = 0;
            }
            break;
        case 0xb:
            func_ov003_02233178(self, p242);
            break;
        case 9:
            func_ov003_02232f78(self, p242);
            break;
        case 0x12:
            if (func_ov068_02271068(self) != 0) {
                *(short *) (self + 0x23a) = 0;
                self[0x251] = 2;
                func_02056fcc(self + 0xec, 0x39, 1, 0x1000, 0x20);
            }
            break;
        case 0x13:
            if (func_ov068_022710e4(self) != 0) {
                self[0x251] = 1;
                self[0x254] = 0;
                func_02056fcc(self + 0xec, 0x21, 1, 0x1000, 0);
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0x1f);
            } else {
                self[0x100] = 1;
            }
            break;
    }
}
