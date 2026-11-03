/* fish_shadow_state_2: 27 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022288e0 @ 0x022288e0, 0x2 bytes, Thumb
 * func_ov003_0222884c @ 0x0222884c, 0x94 bytes, Thumb
 * func_ov003_02228848 @ 0x02228848, 0x2 bytes, Thumb
 * func_ov003_02228784 @ 0x02228784, 0xc4 bytes, Thumb
 * func_ov003_022286f4 @ 0x022286f4, 0x90 bytes, Thumb
 * func_ov003_022286ac @ 0x022286ac, 0x48 bytes, Thumb
 * func_ov003_0222866c @ 0x0222866c, 0x40 bytes, Thumb
 * func_ov003_02228618 @ 0x02228618, 0x54 bytes, Thumb
 * func_ov003_0222853c @ 0x0222853c, 0xdc bytes, Thumb
 * func_ov003_02228520 @ 0x02228520, 0x1c bytes, Thumb
 * func_ov003_022284a8 @ 0x022284a8, 0x78 bytes, Thumb
 * func_ov003_0222847c @ 0x0222847c, 0x2c bytes, Thumb
 * func_ov003_02228460 @ 0x02228460, 0x1c bytes, Thumb
 * func_ov003_02228400 @ 0x02228400, 0x60 bytes, Thumb
 * func_ov003_022283e4 @ 0x022283e4, 0x1c bytes, Thumb
 * func_ov003_02228380 @ 0x02228380, 0x64 bytes, Thumb
 * func_ov003_02228348 @ 0x02228348, 0x36 bytes, Thumb
 * func_ov003_022282e8 @ 0x022282e8, 0x60 bytes, Thumb
 * func_ov003_022282b8 @ 0x022282b8, 0x30 bytes, Thumb
 * func_ov003_02228150 @ 0x02228150, 0x168 bytes, Thumb
 * func_ov003_0222807c @ 0x0222807c, 0xd4 bytes, Thumb
 * func_ov003_0222803c @ 0x0222803c, 0x3e bytes, Thumb
 * func_ov003_02228018 @ 0x02228018, 0x24 bytes, Thumb
 * func_ov003_02227fe4 @ 0x02227fe4, 0x34 bytes, Thumb
 * func_ov003_02227e94 @ 0x02227e94, 0x150 bytes, Thumb
 * func_ov003_02227cec @ 0x02227cec, 0x1a8 bytes, Thumb
 * func_ov003_02227ab0 @ 0x02227ab0, 0x23c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} Mtx;

typedef struct {
    char pad_00[0x30];
    char unk_30;
    char pad_31[0x27];
    int unk_58;
    char pad_5C[4];
} UnkStruct_02228460;

typedef struct {
    char pad_00[0x28];
} Cell;

typedef struct {
    Cell *cells;
    int w;
    int h;
} UnkStruct_02227cec;

typedef struct {
    u8 x, y;
} UnkStruct_02227cec_2;

typedef struct {
    char pad_00[0x208];
    int a, b;
    char pad_210[0x24c - 0x210];
} UnkStruct_02227ab0;

typedef struct {
    signed char x, y;
} Pt;

extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern int func_ov003_0222799c(void *p, Vec3 *v, int a, int b, int c);
extern void func_ov003_02228cd4(void *a0);
extern void func_ov003_02228d48(void *a0, void *c);
extern u8 data_ov003_0223c01c[];
extern void func_ov003_0222be08(char *obj);
extern void func_02031288(char *a, Vec3 *b, Vec3 *c, short h, int d, int e, int f);
extern void func_02055124(char *p);
extern char data_ov003_0225f220[];
extern void func_02056ffc(void *p);
extern Mtx data_021fbe48;
extern int func_0203f844(Vec3 *v, void *argument1);
extern void func_020e96c8(Mtx *m, int x, int y, int z);
extern void func_020e9774(Mtx *m, int t);
extern void func_020e9744(Mtx *m, int t);
extern char data_ov003_0225f76c[];
void func_ov003_02228ae8(void *self, void *e, int i);
extern void *data_020ccf94;
extern char data_ov003_0225f4dc[];
extern char data_ov003_0225f35c[];
extern char data_ov003_0225f0b4[];
extern int func_02073d90(void *h);
extern void func_ov003_0222924c(void *p);
extern void func_ov003_02229ca8(void *rec, u8 i);
extern void func_ov003_0222c130(void *a, void *b);
extern char data_ov003_0225f278[];
extern u8 data_ov003_0223c014[];
extern void func_0205510c(char *p, Vec3 *v);
extern void func_0209d200(void *a, void *b);
extern int func_020044a0(void *e);
extern void func_02004280(void *e);
extern void func_020e9898(void *p);
extern int func_0209d138(void *p);
int func_ov003_022298c4(void *p, u8 i);
extern int func_020ea990(Vec3 *v, void *a);
int func_ov003_0222ab4c(void *b);
int func_02095794(int k);
extern int func_ov003_02219e58(void *b);
extern int data_020c904c;
extern int func_0200322c(void *a, Vec3 *b);
extern int func_020912d4(int id, Vec3 *v, int a, int b);
extern int func_ov003_0222a330(char *obj);
int FX_MulFunc(int a, int b);
int func_02034270(void *buf, void *p, int a, int b);
void func_0203423c(void *buf);
void *func_020961a8(void *a);
long long func_020ea940(void *p, void *q);
extern u8 data_020cb784[];
extern int func_0204fb3c(int *e, int *f, int flag);
extern int func_ov003_02227a48(char *self, char *rec, int e);
extern void func_0204f794(Vec3 *v, int a, int b);
extern UnkStruct_02227cec *data_021c80bc;
extern int func_02037d9c(Cell *c);
extern int func_02037e70(void *argument0);
extern UnkStruct_02227ab0 data_ov003_0225fe50[];
extern void func_0204f7e0(Vec3 *d, Vec3 *s);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02031b5c(int x, int z);
extern int func_02031ba0(int x, int z);
extern int func_ov003_0222793c(int a, int b);

void func_ov003_022286f4(void *a0, char *src);
void func_ov003_022286ac(void *a0, int a1, char *self, int a3);
void func_ov003_02228618(void *p);
void func_ov003_022284a8(char *self);
void func_ov003_0222847c(char *self);
void func_ov003_02228460(char *self);
void func_ov003_022283e4(void *a, void *b, void *c);
void func_ov003_02228380(char *a, char *b, void *c);
int func_ov003_02228348(void *a, void *b);
int func_ov003_022282e8(void *a0, void *b, void *self);
int func_ov003_022282b8(char *p, void *q);
int func_ov003_02228150(char *obj, void *pos);
void func_ov003_0222807c(char *self, char *obj, int k);
int func_ov003_02228018(void *a);
int func_ov003_02227fe4(void *a, void *b, void *c);
int func_ov003_02227ab0(void *self, int *px, int *pz, int *ox, int *oz, unsigned kind, int mode, UnkStruct_02227ab0 *skip);

void func_ov003_022288e0(void) {}

void func_ov003_0222884c(void *a0, char *b, void *c)
{
    Vec3 v;
    if (data_021c67a4 != 0) {
        v.x = data_021c67d0.x;
        v.y = data_021c67d0.y;
        v.z = data_021c67d0.z;
        if (func_ov003_0222799c(b + 0x120, &v, 0xa000, 0x10000, 0xa000)) {
            *(int *) (b + 0x80) = 3;
            *(int *) (b + 0x244) = -1;
        } else {
            int *p = (int *) (b + 0x244);
            int t = *p;
            if (t != -1) {
                if (t == 0) {
                    if (*(u8 *) (b + 0x7f)) {
                        func_ov003_02228cd4(a0);
                    }
                    func_ov003_02228d48(a0, c);
                } else {
                    *p = t - 1;
                }
            }
        }
    }
}

void func_ov003_02228848(void) {}

void func_ov003_02228784(char *self, char *obj, void *k)
{
    Vec3 *d;
    Vec3 *s;
    Vec3 t;
    func_ov003_0222be08(obj);
    d = (Vec3 *) (obj + 0x218);
    s = (Vec3 *) (obj + 0x120);
    func_02031288(obj + 0x4c, s, d, *(short *) (obj + 0x138), (data_ov003_0223c01c[*(u8 *) (obj + 0x1ff) * 0x14] << 12) / 10,
                  0, 0xb);
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
    t.x = s->x;
    t.y = s->y;
    t.z = s->z;
    t.y = 0xffffeccd;
    func_ov003_022286ac((void *) self, (int) (&t), obj + 0x144, (short) (*(short *) (obj + 0x138)));
    if (*(u8 *) (obj + 0x7f)) {
        func_ov003_022286f4((void *) self, obj);
    } else {
        func_02055124(obj + 0x144);
    }
    func_ov003_022283e4((void *) self, (void *) obj, k);
}

void func_ov003_022286f4(void *a0, char *src)
{
    char (*gp)[] = &data_ov003_0225f220;
    char *g = (char *) (*gp);
    Vec3 *p = (Vec3 *) (src + 0x120);
    char *q;
    char *r;
    int ang;
    *(int *) (g + 0x48) = p->x;
    *(int *) (g + 0x4c) = p->y;
    *(int *) (g + 0x50) = p->z;
    ang = *(short *) (src + 0x138);
    *(short *) (g + 0x54) = ang;
    q = g + 0x58;
    *(int *) (q + 0xac) = *(int *) (src + 0x1f0);
    *(unsigned int *) (q + 0xa4) = (((((unsigned int) *(int *) (src + 0x1e8) << 4) >> 16) + 1) << 16) >> 4;
    func_ov003_022286ac(a0, (int) p, q, ang);
    func_02055124((char *) (src + 0x144));
    func_02055124((char *) q);
    r = g + 0x11c;
    func_02056ffc(r);
    **(int **) (r + 0x18) = *(int *) (r + 8);
}

void func_ov003_022286ac(void *a0, int a1, char *self, int a3)
{
    Vec3 v;
    int t;
    t = func_0203f844(&v, (void *) a1);
    func_020e96c8(&data_021fbe48, v.x, v.y, v.z);
    func_020e9774(&data_021fbe48, t);
    func_020e9744(&data_021fbe48, a3);
    *(Mtx *) (self + 0x64) = data_021fbe48;
}

int func_ov003_0222866c(char *self)
{
    char *p = data_ov003_0225f76c;
    int i;
    for (i = 0; i < 6; i++) {
        func_ov003_02228ae8(self, p, i);
        p += 0x24c;
    }
    *(char *) (self + 0x84) = 0;
    func_ov003_02228618(self);
    return 1;
}

void func_ov003_02228618(void *p)
{

    int i;
    char *a;
    char *b;

    if (func_02073d90(data_020ccf94)) {
        func_ov003_0222924c(p);
    }
    a = data_ov003_0225f4dc;
    b = data_ov003_0225f35c;
    for (i = 0; i < 4; i++) {
        func_ov003_02229ca8(a, (u8) i);
        a += 0xa4;
        func_ov003_0222c130(data_ov003_0225f0b4, b);
        b += 0x60;
    }
}

int func_ov003_0222853c(void)
{
    Vec3 v1;
    Vec3 v2;
    char *rec = data_ov003_0225f76c;
    int i = 0;
    do {
        if (*(int *) (rec + 0x80) == 3) {
            u8 *e = &data_ov003_0223c014[*(u8 *) (rec + 0x1ff) * 0x14];
            char *p;
            char *q;
            int f;
            v1.x = (e[0xe] << 12) / 100;
            v1.y = 0x1000;
            v1.z = (e[0xf] << 12) / 100;
            p = *(char **) (rec + 0x1a0);
            p = p + *(int *) (p + 8);
            q = p + *(u16 *) (p + 0xa);
            q = p + *(int *) (q + 8);
            f = *(u8 *) (rec + 0x1fd);
            if (q != 0 && f > 0) {
                *(int *) (q + 0xc) = *(int *) (q + 0xc) & 0xffe0ffff;
                *(int *) (q + 0xc) = *(int *) (q + 0xc) | ((f & 0x1f) << 16);
            }
            func_0205510c(rec + 0x144, &v1);
            if (*(u8 *) (rec + 0x7f)) {
                v2.x = (e[0xe] << 12) / 100;
                v2.y = 0x1000;
                v2.z = (e[0xf] << 12) / 100;
                func_0205510c(data_ov003_0225f278, &v2);
            }
        }
        rec += 0x24c;
        i++;
    } while (i < 6);
    return 1;
}

int func_ov003_02228520(char *self)
{
    func_ov003_022284a8(self);
    func_ov003_0222847c(self);
    func_ov003_02228460(self);
    return 1;
}

void func_ov003_022284a8(char *self)
{
    int flag;
    char *e;
    int i;
    flag = 0;
    e = data_ov003_0225f76c;
    for (i = 0; i < 6; i++) {
        if (*(u8 *) (e + 0x7f)) {
            flag = 1;
        }
        func_ov003_02228d48((void *) self, (void *) i);
        func_0209d200(self + 0x50, e + 0x7c);
        func_020044a0(e);
        func_02004280(e + 0x40);
        e += 0x24c;
    }
    func_020e9898(*(void **) (self + 0x80));
    func_0209d138(self + 0x50);
    if (flag) {
        func_ov003_02228cd4((void *) self);
    }
    func_0209d138(self + 0x68);
}

void func_ov003_0222847c(char *self)
{
    char *p = data_ov003_0225f4dc;
    int i;
    for (i = 0; i < 4; i++) {
        func_ov003_022298c4(p, (u8) i);
        func_020044a0(p);
        p += 0xa4;
    }
}

void func_ov003_02228460(char *self)
{
    UnkStruct_02228460 *p = ((UnkStruct_02228460 *) data_ov003_0225f35c);
    int i;
    for (i = 0; i < 4; i++) {
        p->unk_30 = 0;
        p->unk_58 = 0;
        p++;
    }
}

int func_ov003_02228400(void *a, int lim)
{

    int i;
    char *e;
    int found;
    Vec3 v;
    Vec3 *p;

    found = 0;
    e = data_ov003_0225f76c;
    for (i = 0; i < 6; i++) {
        p = (Vec3 *) (e + 0x120);
        v.x = p->x;
        v.y = p->y;
        v.z = p->z;
        if (func_020ea990(&v, a) <= lim) {
            if (func_ov003_022282b8((char *) e, a)) {
                found = 1;
            }
        }
        e += 0x24c;
    }
    return found;
}

void func_ov003_022283e4(void *a, void *b, void *c)
{
    func_ov003_02228380((char *) a, (char *) b, c);
    func_ov003_0222807c((char *) a, (char *) b, (int) c);
}

void func_ov003_02228380(char *a, char *b, void *c)
{
    int v = *(u8 *) (b + 0x1fd);
    if (v == 0x1f) {
        func_ov003_02228348(a, b);
    } else if (v != 0x1f) {
        if (*(u8 *) (b + 0x7f) == 0) {
            *(u8 *) (b + 0x1fd) = (u8) (v - 1);
        }
    }
    if (*(u8 *) (b + 0x1fd) <= 1) {
        *(u8 *) (b + 0x1fd) = 0x1f;
        if (func_ov003_0222ab4c(b) == 2) {
            if (*(u8 *) (b + 0x7f) != 0) {
                func_ov003_02228cd4(a);
            }
        }
        func_ov003_02228d48(a, c);
    }
}

int func_ov003_02228348(void *a, void *b)
{
    int r = 0;
    if (func_ov003_022282e8(a, (void *) 4, b) != 0) {
        void *h = (void *) func_02095794(4);
        if (h == 0) {
            return r;
        }
        func_ov003_022282b8((char *) b, h);
        r = 1;
    }
    return r;
}

int func_ov003_022282e8(void *a0, void *b, void *self)
{
    int r = 0;
    if (func_ov003_02227fe4(a0, (char *) self + 0x120, b)) {
        if (func_ov003_02219e58(b)) {
            r = 1;
        } else if (func_ov003_02228018(b)) {
            u8 *p = (u8 *) ((char *) self + 0x214);
            if (*p) {
                *p -= 1;
            } else {
                r = 1;
            }
        } else {
            *(u8 *) ((char *) self + 0x214) = 6;
        }
    } else {
        *(u8 *) ((char *) self + 0x214) = 6;
    }
    return r;
}

int func_ov003_022282b8(char *p, void *q)
{
    int r = 0;
    if (p == 0) {
        return r;
    }
    if (*(u8 *) (p + 0x23c) == 1) {
        return r;
    }
    if (func_ov003_02228150((char *) p, q) != 0) {
        r = 1;
    }
    return r;
}

int func_ov003_02228150(char *obj, void *pos)
{
    Vec3 v;
    Vec3 w;
    short *h;
    Vec3 *p;
    int *hh;
    int k;
    if (obj == 0) {
        return 0;
    }
    if (*(u8 *) (obj + 0x200) == 5 || *(u8 *) (obj + 0x224) == 6 || *(int *) (obj + 0x80) != 3) {
        return 0;
    }
    if (*(u8 *) (obj + 0x23c) == 0) {
        *(u8 *) (obj + 0x200) = 5;
    } else {
        *(u8 *) (obj + 0x224) = 6;
    }
    *(u8 *) (obj + 0x1fd) = 0x1e;
    *(int *) (obj + 0x13c) = 0;
    h = (short *) (obj + 0x138);
    p = (Vec3 *) (obj + 0x120);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    if (*(u8 *) (obj + 0x7f) != 0) {
        *h = 0;
    } else {
        *h = func_0200322c(pos, &v);
    }
    k = *(u8 *) (obj + 0x1ff);
    hh = (int *) (obj + 0x204);
    w.x = v.x;
    w.y = v.y;
    w.z = v.z;
    w.y = data_020c904c;
    switch (k) {
        case 0:
            *hh = func_020912d4(0x1a, &w, 0, 0);
            break;
        case 1:
            *hh = func_020912d4(0x1b, &w, 0, 0);
            break;
        case 2:
            *hh = func_020912d4(0x1c, &w, 0, 0);
            break;
        case 3:
            *hh = func_020912d4(0x1d, &w, 0, 0);
            break;
        case 4:
            *hh = func_020912d4(0x1e, &w, 0, 0);
            break;
        case 5:
            *hh = func_020912d4(0x1f, &w, 0, 0);
            break;
        case 6:
            *hh = func_020912d4(0x21, &w, 0, 0);
            break;
        case 7:
            *hh = func_020912d4(0x20, &w, 0, 0);
            break;
    }
    return 1;
}

void func_ov003_0222807c(char *self, char *obj, int k)
{
    Vec3 t;
    if (*(u8 *) (obj + 0x23c) == 0 || *(u8 *) (obj + 0x224) == 6) {
        if (data_021c67a4 != 0) {
            t.x = data_021c67d0.x;
            t.y = data_021c67d0.y;
            t.z = data_021c67d0.z;
            if (func_ov003_0222799c((void *) (obj + 0x120), &t, 0xa000, 0x10000, 0xa000) == 0) {
                if (*(u8 *) (obj + 0x200) == 5 || *(u8 *) (obj + 0x224) == 6) {
                    if (*(u8 *) (obj + 0x7f)) {
                        func_ov003_02228cd4((void *) self);
                    }
                    func_ov003_02228d48((void *) self, (void *) k);
                } else {
                    if ((unsigned) (*(u8 *) (obj + 0x1fe) - 4) <= 2) {
                        if (func_ov003_0222a330(obj)) {
                            *(int *) (obj + 0x244) = 0x12c;
                        } else {
                            *(int *) (obj + 0x244) = 0x4b0;
                        }
                    } else {
                        *(int *) (obj + 0x244) = 0x4b0;
                    }
                    *(int *) (obj + 0x80) = 4;
                }
            }
        }
    }
}

void func_ov003_0222803c(int *out, int a)
{
    int buf[17];
    func_02034270(buf, out, 0, 0);
    out[0] = out[0] + FX_MulFunc(a, buf[9]);
    out[2] = out[2] + FX_MulFunc(a, buf[11]);
    func_0203423c(buf);
}

int func_ov003_02228018(void *a)
{
    int r = 0;
    char *o = (char *) func_020961a8(a);
    if (o != 0) {
        if (*(int *) (o + 0x98) > 0x548) {
            r = 1;
        }
    }
    return r;
}

int func_ov003_02227fe4(void *a, void *b, void *c)
{
    char *o = (char *) func_020961a8(c);
    if (o == 0) {
        return 0;
    }
    if (func_020ea940(o + 0x5c, b) <= 0x135c3) {
        return 1;
    }
    return 0;
}

int func_ov003_02227e94(char *self, char *rec, int mode)
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    Vec3 v;
    int r;
    int g;
    r = 0;
    a = -1;
    b = -1;
    c = -1;
    d = -1;
    switch (mode) {
        case 0:
            g = 0;
            break;
        default:
            g = 1;
            break;
    }
    if (func_0204fb3c(&e, &f, g)) {
        if (func_ov003_02227ab0((void *) self, &a, &b, &c, &d, f, mode, (UnkStruct_02227ab0 *) rec)) {
            if (func_ov003_02227a48(self, rec, e)) {
                int *p;
                int *q;
                func_0204f794(&v, a, b);
                v.y = 0xffffeccd;
                {
                    int t = e;
                    *(u8 *) (rec + 0x7e) = t;
                    *(u8 *) (rec + 0x7f) = (unsigned) (t - 0x34) <= 2;
                }
                *(u8 *) (rec + 0x1fe) = f;
                *(u8 *) (rec + 0x1ff) = data_020cb784[e * 6];
                *(short *) (rec + 0x138) = 0xffff8000;
                *(int *) (rec + 0x12c) = v.x;
                *(int *) (rec + 0x130) = v.y;
                *(int *) (rec + 0x134) = v.z;
                *(u8 *) (rec + 0x1fc) = mode;
                r = 1;
                *(int *) (rec + 0x80) = r;
                *(u8 *) (rec + 0x200) = 0;
                p = (int *) (rec + 0x218);
                p[0] = v.x;
                p[1] = v.y;
                p[2] = v.z;
                {
                    int dd = d;
                    q = (int *) (rec + 0x208);
                    q[0] = c;
                    q[1] = dd;
                }
                *(int *) (rec + 0x244) = -1;
            }
        } else if (mode == 0) {
            *(u8 *) (rec + 0x1fc) = 3;
        } else if (mode == 1) {
            *(u8 *) (rec + 0x1fc) = 4;
        }
    } else if (mode == 0) {
        *(u8 *) (rec + 0x1fc) = 5;
    } else if (mode == 1) {
        *(u8 *) (rec + 0x1fc) = 6;
    }
    return r;
}

int func_ov003_02227cec(int unused, UnkStruct_02227cec_2 *out, int *n, unsigned kind)
{
    int ret;
    UnkStruct_02227cec *g;
    int x, y;
    Cell *c;
    int f;

    ret = 0;
    g = data_021c80bc;
    if (g != 0) {
        for (x = 1; x < g->h - 1; x++) {
            for (y = 1; y < g->w - 1; y++) {
                c = ((unsigned) x < (unsigned) g->w && (unsigned) y < (unsigned) g->h && g->cells != 0)
                        ? &g->cells[y * g->w + x]
                        : 0;
                if (c == 0) {
                    continue;
                }
                switch (kind) {
                    case 6:
                        if (func_02037d9c(c) & 8) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 0:
                        if (func_02037d9c(c) & 0x7f000) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 1:
                        if (func_02037d9c(c) & 0x100) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 2:
                        if (func_02037d9c(c) & 0x80000) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 3:
                        if (func_02037e70(c) != 0) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                    case 4:
                        f = func_02037d9c(c);
                        if (f & 0x7f000) {
                            if (f & 8) {
                                out[*n].x = x;
                                out[*n].y = y;
                                *n = *n + 1;
                            }
                        }
                        break;
                    case 5:
                        if (func_02037d9c(c) & 8) {
                            out[*n].x = x;
                            out[*n].y = y;
                            *n = *n + 1;
                        }
                        break;
                }
            }
        }
    }
    if (*n > 0) {
        ret = 1;
    }
    return ret;
}

int func_ov003_02227ab0(void *self, int *px, int *pz, int *ox, int *oz, unsigned kind, int mode, UnkStruct_02227ab0 *skip)
{
    UnkStruct_02227ab0 *q;
    int n;
    Pt tiles[16];
    int bx;
    Vec3 d;
    Vec3 v50;
    int cnt;
    int z;
    unsigned kk;
    int iend;
    int jend;
    int by;
    int lo;
    int k;
    int m;
    int *pp;
    int x;
    int i;
    int t;
    int j;
    Vec3 v5c;
    int hi;
    Pt pts[258];

    kk = kind;
    cnt = 0;
    n = 0;
    if ((*(int *) &data_021c67a4) == 0) {
        return cnt;
    }
    d.x = data_021c67d0.x;
    d.y = data_021c67d0.y;
    d.z = data_021c67d0.z;
    func_0204f7e0(&v50, &d);
    if (func_ov003_02227cec((int) self, (UnkStruct_02227cec_2 *) tiles, &n, kk) == 0) {
        return cnt;
    }
    m = func_ov003_0222793c(0, (unsigned short) n);
    *ox = tiles[m].x;
    *oz = tiles[m].y;
    x = *ox;
    z = *oz;
    if (mode == 0) {
        q = ((UnkStruct_02227ab0 *) data_ov003_0225f76c);
        for (k = 0; k < 3; k++) {
            if (skip != q) {
                pp = &q->a;
                if (x == q->a && z == pp[1]) {
                    return 0;
                }
            }
            q++;
        }
    } else if (mode == 1) {
        q = data_ov003_0225fe50;
        for (k = 3; k < 6; k++) {
            if (skip != q) {
                pp = &q->a;
                if (x == q->a && z == pp[1]) {
                    return 0;
                }
            }
            q++;
        }
    }
    func_0204f800(&lo, &hi, x, z, 0, 0);
    t = lo;
    iend = t + 0x10;
    jend = hi + 0x10;
    for (i = lo; i < iend; i++) {
        for (j = hi; j < jend; j++) {
            switch (kk) {
                case 5:
                case 6:
                    if (func_02031b5c(i, j) == 1) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 0:
                case 1:
                    if (func_02031b5c(i, j) == 2) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 2:
                    if (j < hi + 3 && func_02031b5c(i, j) == 2) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 3:
                    if (func_02031ba0(i, j) != 0) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
                case 4:
                    if (func_02031b5c(i, j) == 2 || func_02031b5c(i, j) == 1) {
                        pts[cnt].x = (signed char) i;
                        pts[cnt].y = (signed char) j;
                        cnt++;
                    }
                    break;
            }
        }
    }
    if (cnt == 0) {
        *px = -1;
        *pz = -1;
        return 0;
    }
    m = func_ov003_0222793c(0, (unsigned short) cnt);
    by = pts[(short) m].y;
    bx = pts[(short) m].x;
    func_0204f794(&v5c, bx, by);
    if (func_ov003_0222799c((void *) (&v5c), &v50, 0xa000, 0x10000, 0xa000) != 0) {
        *px = -1;
        *pz = -1;
        return 0;
    }
    *px = bx;
    *pz = by;
    return 1;
}
