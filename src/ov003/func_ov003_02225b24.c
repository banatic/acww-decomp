/* func_ov003_02225b24 @ 0x02225b24, 0x27c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx;
typedef struct {
    volatile u16 id;
    u16 pad_02;
    Vec3 unk_04;
} Draw;

extern Mtx data_021fbe48;

extern int func_0203f8d0(Vec3 *a, Vec3 *b);
extern void func_020e96c8(Mtx *m, int x, int y, int z);
extern void func_020e9774(Mtx *m, int a);
extern void func_020e97a4(Mtx *m, int a, int b, int c);
extern void func_020e9838(Mtx *m, int x, int y, int z);
extern int func_0204c63c(Draw *d);
extern void *func_ov003_02225474(void *g, Draw *d, Mtx m);
extern char *func_ov003_02225598(void *g, Draw *d, Mtx m);
extern void *func_ov003_022251e8(void *g, Draw *d, Mtx m);
extern void func_ov003_022251a4(void *g, int v, Mtx m);

void func_ov003_02225b24(void *self, u16 id, Vec3 *src, Vec3 *sc, short s1, short s2, short s3)
{
    int idx;
    unsigned int h, g, f, e, d2, c, b, a;
    Draw d;
    int r;
    int f1, f2;
    u16 lo, hi;
    u16 k;
    u16 nid;
    int f4;
    u16 kk;

    d.id = 0xfff1;
    d.id = id;
    r = func_0203f8d0(&d.unk_04, src);
    func_020e96c8(&data_021fbe48, d.unk_04.x, d.unk_04.y, d.unk_04.z);
    func_020e9774(&data_021fbe48, r);
    func_020e97a4(&data_021fbe48, s1, s2, s3);
    func_020e9838(&data_021fbe48, sc->x, sc->y, sc->z);

    f2 = 1;
    f1 = 0;
    lo = d.id;
    hi = d.id;
    if (hi >= 0xd4 && lo <= 0xda) {
        f1 = 1;
    }
    if (f1 == 0) {
        if (!(lo >= 0xdb && lo <= 0xe1)) {
            f2 = 0;
        }
    }
    if (f2 != 0) {
        k = (u16) (id - 0xd4);
        if (k < 7) {
            nid = (u16) (k + 0x153b);
        } else {
            nid = 0x153b;
        }
        d.id = nid;
    } else if (id == 0x20) {
        d.id = 0x156a;
    }

    lo = d.id;
    hi = d.id;
    switch ((hi & 0xf000) >> 12) {
        case 0:
            f4 = 0;
            kk = (u16) (lo + 0xffe6);
            if (kk <= 4) {
                if ((1 << kk) & 0x1b) {
                    f4 = 1;
                }
            }
            if (f4 == 0) {
                if (lo != 0x88) {
                    if (lo != 0x89) {
                        goto L2;
                    }
                }
            }
            func_ov003_02225474(self, &d, data_021fbe48);
            break;
        L2:
            h = 1;
            g = 1;
            f = 1;
            e = 1;
            d2 = 1;
            c = 1;
            b = 1;
            a = 0;
            if (lo <= 5) {
                a = 1;
            }
            if (a == 0) {
                if (!(lo >= 6 && lo <= 0xb)) {
                    b = 0;
                }
            }
            if (b == 0) {
                if (!(lo >= 0xc && lo <= 0x11)) {
                    c = 0;
                }
            }
            if (c == 0) {
                if (!((lo >= 0x12 && lo <= 0x19) || lo == 0x1c)) {
                    d2 = 0;
                }
            }
            if (d2 == 0) {
                if (!((lo >= 0x8a && lo <= 0x8f) || (lo >= 0x90 && lo <= 0x95) || (lo >= 0x96 && lo <= 0x9b) ||
                      (lo >= 0x9c && lo <= 0xa3) || lo == 0xa5)) {
                    e = 0;
                }
            }
            if (e == 0) {
                if (lo != 0x1a) {
                    f = 0;
                }
            }
            if (f == 0) {
                if (lo != 0xa4) {
                    g = 0;
                }
            }
            if (g == 0) {
                if (lo != 0x1d) {
                    h = 0;
                }
            }
            if (h != 0) {
                func_ov003_02225598(self, &d, data_021fbe48);
            } else if (lo >= 0xa7 && lo <= 0xc6) {
                func_ov003_022251e8(self, &d, data_021fbe48);
            }
            break;
        case 1:
        case 3:
        case 4:
            idx = func_0204c63c(&d);
            func_ov003_022251a4(self, *(int *) ((char *) self + idx * 4 + 0x50), data_021fbe48);
            break;
    }
}
