/* town_item_models_3: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02225e00 @ 0x02225e00, 0x98 bytes, Thumb
 * func_ov003_02225da0 @ 0x02225da0, 0x60 bytes, Thumb
 * func_ov003_02225b24 @ 0x02225b24, 0x27c bytes, Thumb
 * func_ov003_02225a90 @ 0x02225a90, 0x94 bytes, Thumb
 * func_ov003_022259e8 @ 0x022259e8, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} UnkStruct_02225e00;

typedef struct {
    volatile unsigned short id;
    Vec3 a;
    Vec3 b;
} UnkStruct_02225da0;

typedef struct {
    int m[12];
} Mtx;

typedef struct {
    volatile u16 id;
    u16 pad_02;
    Vec3 unk_04;
} Draw;

typedef struct {
    int w[12];
} UnkStruct_022259e8;

extern UnkStruct_02225e00 data_021fbe48;
extern int func_0203f8d0(Vec3 *v, void *a);
extern void func_020e96c8(UnkStruct_02225e00 *m, int x, int y, int z);
extern void func_020e9774(UnkStruct_02225e00 *m, int t);
extern void func_020e97a4(UnkStruct_02225e00 *m, int a, int b, int c);
extern void func_020e9838(UnkStruct_02225e00 *m, int x, int y, int z);
extern void func_0210744c(void *h, int a);
extern void func_ov003_022251a4(char *a0, void *r, UnkStruct_02225e00 m);
extern int func_0204c63c(UnkStruct_02225da0 *s);
extern void *func_ov003_02225474(void *g, Draw *d, Mtx m);
extern char *func_ov003_02225598(void *g, Draw *d, Mtx m);
extern void *func_ov003_022251e8(void *g, Draw *d, Mtx m);
extern Vec3 data_ov003_02236b64[];
extern u16 data_ov003_0223667c[];
extern int func_0204b710(u16 *b);
extern int func_020466e0(int a, int b);

void *func_ov003_02225e00(char *a0, int i, void *a2, int a3, Vec3 *p, short s1, short s2, short s3)
{
    Vec3 v;
    void *r;
    int t;
    r = *(void **) (a0 + i * 4 + 0x50);
    t = func_0203f8d0(&v, a2);
    func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
    func_020e9774(&data_021fbe48, t);
    func_020e97a4(&data_021fbe48, s1, s2, s3);
    func_020e9838(&data_021fbe48, p->x, p->y, p->z);
    func_0210744c(*(void **) ((char *) r + 0x5c), a3);
    func_ov003_022251a4(a0, r, data_021fbe48);
    return r;
}

int func_ov003_02225da0(void *a0, int a1, Vec3 *a2, void *a3, Vec3 *a4, short s1, short s2, short s3)
{
    UnkStruct_02225da0 s;
    s.id = 0xfff1;
    s.id = (unsigned short) a1;
    s.a.x = a2->x;
    s.a.y = a2->y;
    s.a.z = a2->z;
    s.b.x = a4->x;
    s.b.y = a4->y;
    s.b.z = a4->z;
    return (int) func_ov003_02225e00((char *) a0, func_0204c63c(&s), (void *) (&s.a), (int) a3, &s.b, s1, s2, s3);
}

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
    r = func_0203f8d0(&d.unk_04, (void *) src);
    func_020e96c8((UnkStruct_02225e00 *) (((Mtx *) &data_021fbe48)), d.unk_04.x, d.unk_04.y, d.unk_04.z);
    func_020e9774((UnkStruct_02225e00 *) (((Mtx *) &data_021fbe48)), r);
    func_020e97a4((UnkStruct_02225e00 *) (((Mtx *) &data_021fbe48)), s1, s2, s3);
    func_020e9838((UnkStruct_02225e00 *) (((Mtx *) &data_021fbe48)), sc->x, sc->y, sc->z);

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
            func_ov003_02225474(self, &d, (*(Mtx *) &data_021fbe48));
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
                func_ov003_02225598(self, &d, (*(Mtx *) &data_021fbe48));
            } else if (lo >= 0xa7 && lo <= 0xc6) {
                func_ov003_022251e8(self, &d, (*(Mtx *) &data_021fbe48));
            }
            break;
        case 1:
        case 3:
        case 4:
            idx = func_0204c63c((UnkStruct_02225da0 *) (&d));
            func_ov003_022251a4((char *) self, (void *) (*(int *) ((char *) self + idx * 4 + 0x50)), *(UnkStruct_02225e00 *) &((*(Mtx *) &data_021fbe48)));
            break;
    }
}

void func_ov003_02225a90(void *a0, u16 *b, Vec3 *base)
{
    struct {
        Vec3 a;
        Vec3 b;
    } o;
    Vec3 s;
    int c;
    u16 v;
    int id;
    int i;
    int z;
    c = 0;
    v = *b;
    if (v >= 0x57 && v <= 0x5b) {
        c = 1;
    }
    if (c) {
        id = 0x14b8;
    } else {
        id = data_ov003_0223667c[func_0204b710(b)];
    }
    i = 0;
    z = 0;
    for (; i < 3; i++) {
        Vec3 *e = &data_ov003_02236b64[i];
        o.a.x = base->x + e->x;
        o.a.y = base->y + e->y;
        o.a.z = base->z + e->z;
        o.b.x = o.a.x;
        o.b.y = o.a.y;
        o.b.z = o.a.z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov003_02225da0(a0, id, &o.b, (void *) 0x1f, &s, z, z, z);
    }
}

void func_ov003_022259e8(char *a0, void *a1, int a2, int a3)
{
    void *p;
    Vec3 v;
    int k;
    int t;
    p = 0;
    k = func_020466e0(a2, a3);
    if (k != -1) {
        k = (k + (*(int *) (a0 + 0x6a6c) + k * 0xf) / 0x14) % 3;
        p = a0 + 0x1014 + k * 0x9c;
    }
    t = func_0203f8d0(&v, a1);
    func_020e96c8((UnkStruct_02225e00 *) (((UnkStruct_022259e8 *) &data_021fbe48)), v.x, v.y, v.z);
    func_020e9774((UnkStruct_02225e00 *) (((UnkStruct_022259e8 *) &data_021fbe48)), t);
    func_ov003_022251a4(a0, p, *(UnkStruct_02225e00 *) &((*(UnkStruct_022259e8 *) &data_021fbe48)));
}
