/* player_fish_3: 8 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022298f0 @ 0x022298f0, 0xc8 bytes, Thumb
 * func_ov003_022298c4 @ 0x022298c4, 0x2a bytes, Thumb
 * func_ov003_02229874 @ 0x02229874, 0x50 bytes, Thumb
 * func_ov003_022297f0 @ 0x022297f0, 0x84 bytes, Thumb
 * func_ov003_02229590 @ 0x02229590, 0x260 bytes, Thumb
 * func_ov003_022294b4 @ 0x022294b4, 0xdc bytes, Thumb
 * func_ov003_02229428 @ 0x02229428, 0x8a bytes, Thumb
 * func_ov003_022293b0 @ 0x022293b0, 0x78 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} UnkStruct_022298f0;

typedef struct {
    char pad_00[0x24c];
} UnkStruct_02229874;

typedef struct {
    u8 a;
    u8 pad_01;
    s16 b;
} UnkStruct_02229590;

typedef struct {
    UnkStruct_02229590 *p;
    int pad_04;
} UnkStruct_02229590_2;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5C;
    char pad_60[0x24];
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    u8 unk_94;
    char pad_95[7];
    int unk_9C;
} UnkStruct_02229590_3;

extern void *func_02096190(void *obj);
extern void func_ov003_0222933c(char *self, void *o, Vec3 *v);
extern int func_0205fb28(Vec3 *w, int a, void *b, void *c, int d);
extern int func_ov003_0222a88c(char *self, void *obj);
extern void func_0209549c(UnkStruct_022298f0 *m, void *obj);
extern void func_ov003_02219668(UnkStruct_022298f0 *m, Vec3 *axis);
extern int func_0203f7d0(Vec3 *a, Vec3 *b);
extern UnkStruct_02229874 data_ov003_0225f76c[];
extern void func_0204fdbc(int h);
extern void func_0209129c(int h);
extern u8 data_020cb784[];
extern u8 data_020cb785[];
extern u8 data_ov003_0223c022[];
extern u8 data_ov003_0223c023[];
extern int data_020c904c;
extern void *data_020ccf94;
extern UnkStruct_02229590_2 data_ov003_0223bf00[];
extern int func_020912d4(int a, Vec3 *v, int c, int d);
extern int func_020044c0(UnkStruct_02229590_3 *self, int a, int b, int c);
extern int func_02073d90(void *a);
extern int func_02073918(void *a, int b);
extern int func_ov003_02228400(Vec3 *v, int lim);
extern int func_ov003_0222796c(Vec3 *a, Vec3 *b, Vec3 *c);
int func_020ea990(void *a, void *b);
int func_0200322c(void *a, void *b);
void func_ov003_0222be78(void *dst, int q, int w);
extern void func_02091278(void *h, Vec3 *v, int a, int b);

int func_ov003_02229874(char *self);
void func_ov003_022297f0(char *self, void *b);
void func_ov003_02229590(UnkStruct_02229590_3 *self, int p1);
int func_ov003_02229428(char *dst, char *a, char *b, int s, int h, int n);

int func_ov003_022298f0(char *self, void *obj)
{
    Vec3 v;
    UnkStruct_022298f0 m1;
    Vec3 u;
    Vec3 w;
    UnkStruct_022298f0 mtx;
    int r;
    void *o = func_02096190(obj);
    if (o == 0) {
        *(int *) (self + 0x40) = 4;
        return 0;
    }
    if (*(u8 *) (self + 0x80) == 0) {
        func_ov003_0222933c(self, o, &v);
        r = 1;
        w.x = v.x;
        w.y = v.y;
        w.z = v.z;
        if (func_0205fb28(&w, *(int *) (self + 0x4c), self + 0x54, self + 0x50, r)) {
            *(u8 *) (self + 0x80) = r;
            *(int *) (self + 0x6c) = v.x;
            *(int *) (self + 0x70) = v.y;
            *(int *) (self + 0x74) = v.z;
        }
    } else {
        func_ov003_0222a88c(self, obj);
        func_0209549c(&mtx, obj);
        m1 = mtx;
        func_ov003_02219668(&m1, 0);
        u.x = m1.w[9];
        u.y = m1.w[10];
        u.z = m1.w[11];
        func_0203f7d0(&u, &u);
        *(int *) (self + 0x54) = u.x;
        *(int *) (self + 0x58) = u.y;
        *(int *) (self + 0x5c) = u.z;
        *(int *) (self + 0x6c) = u.x;
        *(int *) (self + 0x70) = u.y;
        *(int *) (self + 0x74) = u.z;
        r = 1;
    }
    return r;
}

int func_ov003_022298c4(void *self, void *a)
{
    int st = *(int *) ((char *) self + 0x48);
    if (st == 1 || st == 3) {
        func_ov003_02229874((char *) self);
    }
    func_ov003_022297f0((char *) self, a);
    return 1;
}

int func_ov003_02229874(char *self)
{
    int r = 0;
    s8 k;
    char *e;
    k = *(s8 *) (self + 0x78);
    if (k != -1) {
        e = (char *) &data_ov003_0225f76c[k];
        if (*(int *) (e + 0x22c) != 0) {
            *(int *) (e + 0x22c) = r;
        }
        *(s8 *) (e + 0x227) = -1;
        *(u8 *) (e + 0x23c) = 0;
        *(u8 *) (e + 0x224) = 0;
        r = 1;
    }
    return r;
}

void func_ov003_022297f0(char *self, void *b)
{
    func_0204fdbc(*(int *) (self + 0x44));
    *(int *) (self + 0x44) = -1;
    *(int *) (self + 0x40) = 0;
    *(char *) (self + 0x78) = -1;
    *(u8 *) (self + 0x80) = 0;
    *(u8 *) (self + 0xa0) = 0;
    *(int *) (self + 0x7c) = 0;
    *(int *) (self + 0x84) = 0x1333;
    *(int *) (self + 0x88) = 0x1333;
    *(int *) (self + 0x8c) = 0x1333;
    *(u16 *) (self + 0x96) = 0;
    *(u16 *) (self + 0x98) = 0;
    *(u16 *) (self + 0x9a) = 0;
    func_0209129c(*(int *) (self + 0x9c));
    *(int *) (self + 0x9c) = -1;
    if (*(u8 *) (self + 0x94)) {
        func_ov003_02229590((UnkStruct_02229590_3 *) self, (int) b);
    }
}

void func_ov003_02229590(UnkStruct_02229590_3 *self, int p1)
{
    Vec3 v;
    void *g;
    int t, kind, j, k, q;
    int *pf9c;

    self->unk_40 = 1;
    self->unk_94 = 0;
    t = self->unk_90 * 6;
    kind = data_020cb784[t];
    j = kind * 0x14;
    self->unk_84 = ((int) data_ov003_0223c022[j] << 12) / 100;
    self->unk_88 = 0x1000;
    self->unk_8C = ((int) data_ov003_0223c023[j] << 12) / 100;
    self->unk_58 = data_020c904c;
    self->unk_90 = 0x3b;
    v.x = self->unk_54;
    v.y = self->unk_58;
    v.z = self->unk_5C;
    pf9c = &self->unk_9C;

    switch (kind) {
        case 0:
            func_020912d4(0x12, &v, 0, 0);
            *pf9c = func_020912d4(0x1a, &v, 0, 0);
            func_020044c0(self, 0x7e2, 0x7f, 0);
            break;
        case 1:
            func_020912d4(0x13, &v, 0, 0);
            *pf9c = func_020912d4(0x1b, &v, 0, 0);
            func_020044c0(self, 0x7e2, 0x7f, 0);
            break;
        case 2:
            func_020912d4(0x14, &v, 0, 0);
            *pf9c = func_020912d4(0x1c, &v, 0, 0);
            func_020044c0(self, 0x7e2, 0x7f, 0);
            break;
        case 3:
            func_020912d4(0x15, &v, 0, 0);
            *pf9c = func_020912d4(0x1d, &v, 0, 0);
            func_020044c0(self, 0x7e3, 0x7f, 0);
            break;
        case 4:
            func_020912d4(0x16, &v, 0, 0);
            *pf9c = func_020912d4(0x1e, &v, 0, 0);
            func_020044c0(self, 0x7e3, 0x7f, 0);
            break;
        case 5:
            func_020912d4(0x17, &v, 0, 0);
            *pf9c = func_020912d4(0x1f, &v, 0, 0);
            func_020044c0(self, 0x7e4, 0x7f, 0);
            break;
        case 6:
            func_020912d4(0x19, &v, 0, 0);
            *pf9c = func_020912d4(0x21, &v, 0, 0);
            func_020044c0(self, 0x7e4, 0x7f, 0);
            break;
        case 7:
            func_020912d4(0x18, &v, 0, 0);
            *pf9c = func_020912d4(0x20, &v, 0, 0);
            func_020044c0(self, 0x7e3, 0x7f, 0);
            break;
    }

    self->unk_48 = 5;
    g = data_020ccf94;
    if (func_02073d90(g) != 0) {
        if (func_02073918(g, p1) != 0) {
            k = data_020cb785[t];
            q = ((int) data_ov003_0223bf00[0].p[k].a << 12) / 10;
            func_ov003_02228400(&v, q);
        }
    } else {
        k = data_020cb785[t];
        q = ((int) data_ov003_0223bf00[0].p[k].a << 12) / 10;
        func_ov003_02228400(&v, q);
    }
}

void func_ov003_022294b4(char *self, int flag)
{
    volatile Vec3 a;
    volatile Vec3 b;
    Vec3 c;
    Vec3 d;
    Vec3 e;
    Vec3 f;
    Vec3 g;
    int k;
    if (flag) {
        a.x = *(int *) (self + 0x6c);
        a.y = *(int *) (self + 0x70);
        a.z = *(int *) (self + 0x74);
        b.x = *(int *) (self + 0x60);
        b.y = *(int *) (self + 0x64);
        b.z = *(int *) (self + 0x68);
        b.y = *(int *) (self + 0x64) - 0x1800;
        k = 0x14;
    } else {
        a.x = *(int *) (self + 0x60);
        a.y = *(int *) (self + 0x64);
        a.z = *(int *) (self + 0x68);
        b.x = *(int *) (self + 0x6c);
        b.y = *(int *) (self + 0x70);
        b.z = *(int *) (self + 0x74);
        b.y = *(int *) (self + 0x70) - *(int *) (self + 0x64);
        k = 0x14;
    }
    c.x = *(int *) (self + 0x54);
    c.y = *(int *) (self + 0x58);
    c.z = *(int *) (self + 0x5c);
    d.x = a.x;
    d.y = a.y;
    d.z = a.z;
    e.x = b.x;
    e.y = b.y;
    e.z = b.z;
    if (func_ov003_0222796c(&c, &d, &e)) {
        *(int *) (self + 0x40) = 4;
        *(u8 *) (self + 0x94) = 1;
    } else {
        f.x = a.x;
        f.y = a.y;
        f.z = a.z;
        g.x = b.x;
        g.y = b.y;
        g.z = b.z;
        if (func_ov003_02229428(self + 0x54, (char *) (&f), (char *) (&g), *(int *) (self + 0x7c), 0x14cd, k) == 0) {
            *(int *) (self + 0x40) = 4;
            *(u8 *) (self + 0x94) = 1;
        }
        *(int *) (self + 0x7c) = *(int *) (self + 0x7c) + 1;
    }
}

int func_ov003_02229428(char *dst, char *a, char *b, int s, int h, int n)
{
    int nn;
    int v;
    volatile int t;
    volatile int p;
    int q;
    int w;
    int z;
    if (n <= s) {
        return 0;
    }
    v = *(int *) (b + 4);
    nn = n * n;
    t = ((h - (v >> 1)) << 3) / nn;
    p = func_020ea990(a, b);
    w = func_0200322c(a, b);
    nn = t * nn;
    q = (v + (nn >> 1)) / n;
    z = s * s;
    *(int *) (dst + 4) = *(int *) (a + 4) + (s * q - ((z * t) >> 1));
    func_ov003_0222be78(dst, p / n, w);
    return 1;
}

int func_ov003_022293b0(char *self, int a1)
{
    int t;
    int d;
    Vec3 v;
    t = *(int *) (self + 0x7c);
    d = (t + 2) << 7;
    if (t == 0) {
        *(short *) (self + 0x98) = (short) func_0200322c((void *) a1, self + 0x54);
    } else if (t >= 0x1e) {
        *(int *) (self + 0x40) = 4;
    }
    if (d > 0x214) {
        d = 0x214;
    }
    func_ov003_0222be78(self + 0x54, d, *(short *) (self + 0x98));
    *(int *) (self + 0x7c) += 1;
    v.x = *(int *) (self + 0x54);
    v.y = *(int *) (self + 0x58);
    v.z = *(int *) (self + 0x5c);
    v.y = data_020c904c;
    func_02091278(*(void **) (self + 0x9c), &v, 0, 0);
    return 1;
}
