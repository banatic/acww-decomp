/* func_ov003_0222fa20 @ 0x0222fa20, 0x340 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222fa20;
typedef struct {
    u8 a;
    u8 unk_01;
    u16 b;
    u16 c;
} UnkStruct_0222fa20_2;

extern UnkStruct_0222fa20_2 data_ov003_0223c144[];
extern char data_ov003_0223c2ac[];
extern char data_ov003_0223c2b0[];
extern void *data_021fbe94;
extern char data_ov003_0223c48c[], data_ov003_0223c4a0[], data_ov003_0223c4b4[], data_ov003_0223c4c8[];
extern char data_ov003_0223c4dc[], data_ov003_0223c4f0[], data_ov003_0223c504[], data_ov003_0223c510[];
extern char data_ov003_0223c51c[], data_ov003_0223c528[];

extern void func_02137550(char *p, int n);
extern void func_02064328(char *dst, char *fmt, int a);
extern int func_02064858(char *p);
extern void *func_0209d238(char *p, char *q);
extern int func_0209d0ac(char *p, void *h, char *g);
extern void *func_0209d088(char *p);
extern void func_02055f2c(char *a, void *x, int f);
extern void *func_0209d324(void *h);
extern void *func_02064b2c(char *g, void *m, int n, int f);
extern void *NNS_G3dGetVisAnmSet(void *p);
extern void *func_02107cf0(void *p, int i);
extern void *NNS_G3dGetJntAnmSet(void *p);
extern void *func_02107b44(void *p, int i);
extern int func_02055140(char *a, void *m);
extern void func_02055060(char *a, void *p, int b, int c, int d, int e);
extern void func_02055050(char *a);
extern void func_02056fcc(char *p, int a, int b, int c, int d);
extern void *NNS_G3dGetTexSRTAnmSet(void *p);
extern void *func_02107bbc(void *p, int i);
extern int func_0205650c(char *p, int q, void *m);
extern void func_02056478(char *p, void *q, int b, int c, int d);
extern void *func_02055e00(char *a);
extern void func_020563dc(char *p, void *q);
extern void func_0200430c(char *p);
extern void func_ov003_0222e0ec(char *a, char *self, int k);

void func_ov003_0222fa20(char *a, char *self, int mode)
{
    char sa[0x11];
    char sb[0x17];
    UnkStruct_0222fa20 v;
    UnkStruct_0222fa20 *o;
    void *res;
    int ok;
    char *q;
    char *p;
    UnkStruct_0222fa20_2 *e;
    void *h;
    void *h2;
    void *x;
    void *t;
    int kind;
    int d;

    func_02137550(sa, 0x11);
    func_02137550(sb, 0x17);
    kind = *(signed char *) (self + 0x24d);
    if (kind < 0) {
        return;
    }
    if (kind >= 0x3c) {
        return;
    }
    if (kind < 0xa) {
        func_02064328(sa, data_ov003_0223c48c, kind);
    } else if (kind < 0x14) {
        func_02064328(sa, data_ov003_0223c4a0, kind);
    } else if (kind < 0x1e) {
        func_02064328(sa, data_ov003_0223c4b4, kind);
    } else if (kind < 0x28) {
        func_02064328(sa, data_ov003_0223c4c8, kind);
    } else if (kind < 0x32) {
        func_02064328(sa, data_ov003_0223c4dc, kind);
    } else {
        func_02064328(sa, data_ov003_0223c4f0, kind);
    }
    func_02064328(sb, data_ov003_0223c504, (int) sa);
    if (func_02064858(sb) == 0) {
        return;
    }
    if (mode == 0) {
        h = func_0209d238(a + 0x50, self + 0x230);
    } else if (mode == 1) {
        h = func_0209d238(a + 0x68, self + 0x230);
    } else {
        h = func_0209d238(a + 0x80, self + 0x230);
    }
    q = self + 0x130;
    if (func_0209d0ac(q, h, sb) == 0) {
        return;
    }
    p = self;
    p = p + 0x50;
    func_02055f2c(p, func_0209d088(q), 0);
    e = &data_ov003_0223c144[kind];
    if (data_ov003_0223c144[kind].a != 0) {
        func_02064328(sb, data_ov003_0223c510, (int) sa);
    } else {
        func_02064328(sb, data_ov003_0223c51c, (int) sa);
    }
    if (func_02064858(sb) == 0) {
        return;
    }
    res = func_0209d324(h);
    if (mode == 1) {
        if (kind == 0x3a) {
            *(void **) (a + 0x98) = func_02064b2c(sb, data_021fbe94, 4, 0);
            h2 = *(void **) (a + 0x98);
        } else {
            *(void **) (a + 0x9c) = func_02064b2c(sb, data_021fbe94, 4, 0);
            h2 = *(void **) (a + 0x9c);
        }
    } else {
        h2 = func_02064b2c(sb, res, 4, 0);
    }
    if (h2 == 0) {
        return;
    }
    if (e->a != 0) {
        x = func_02107cf0(NNS_G3dGetVisAnmSet(h2), 0);
    } else {
        x = func_02107b44(NNS_G3dGetJntAnmSet(h2), 0);
    }
    if (func_02055140(p, res) == 0) {
        return;
    }
    ok = 1;
    d = 0x1000;
    if (kind == 0x35 || kind == 9) {
        d = 0;
    }
    func_02055060(p, x, 0, d, 0, 0);
    func_02055050(p);
    if (kind == 9) {
        func_02056fcc(self + 0xec, 9, 1, 0, 9);
    }
    if ((unsigned int) (kind - 0x3a) <= 1) {
        func_02064328(sb, data_ov003_0223c528, kind);
        ok = 0;
        if (func_02064858(sb) != 0) {
            t = func_02064b2c(sb, res, 4, 0);
            if (h2 != 0) {
                h2 = func_02107bbc(NNS_G3dGetTexSRTAnmSet(t), 0);
                if (func_0205650c(self, *(int *) (p + 0x5c), res) != 0) {
                    func_02056478(self, h2, 0, 0x1000, 0);
                    func_020563dc(self, func_02055e00(p));
                    ok = 1;
                }
            }
        }
    }
    if (ok == 0) {
        return;
    }
    v = *(UnkStruct_0222fa20 *) (self + 0x210);
    func_0200430c(self + 0x174);
    kind = kind * 8;
    (*(void (**)(char *))(data_ov003_0223c2ac + kind))(self);
    *(void **) (self + 0x170) = *(void **) (data_ov003_0223c2b0 + kind);
    *(u8 *) (self + 0x250) = 3;
    *(u8 *) (self + 0x24a) = 0;
    func_ov003_0222e0ec(a, self, 0);
    if (mode == 2) {
        o = (UnkStruct_0222fa20 *) (self + 0x210);
        o->x = v.x;
        o->y = v.y;
        o->z = v.z;
    }
}
