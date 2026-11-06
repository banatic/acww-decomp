/* flea_market_buyer_3: 22 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222152c @ 0x0222152c, 0x24 bytes, Thumb
 * func_ov004_022214f0 @ 0x022214f0, 0x3c bytes, Thumb
 * func_ov004_02221444 @ 0x02221444, 0xac bytes, Thumb
 * func_ov004_02221410 @ 0x02221410, 0x34 bytes, Thumb
 * func_ov004_0222137c @ 0x0222137c, 0x94 bytes, Thumb
 * func_ov004_0222136c @ 0x0222136c, 0x10 bytes, Thumb
 * func_ov004_02221270 @ 0x02221270, 0xfc bytes, Thumb
 * func_ov004_0222123c @ 0x0222123c, 0x34 bytes, Thumb
 * func_ov004_02221198 @ 0x02221198, 0xa4 bytes, Thumb
 * func_ov004_02221138 @ 0x02221138, 0x60 bytes, Thumb
 * func_ov004_022210fc @ 0x022210fc, 0x3c bytes, Thumb
 * func_ov004_022210c8 @ 0x022210c8, 0x34 bytes, Thumb
 * func_ov004_02220ee0 @ 0x02220ee0, 0x1e8 bytes, Thumb
 * func_ov004_02220ea8 @ 0x02220ea8, 0x38 bytes, Thumb
 * func_ov004_02220e40 @ 0x02220e40, 0x68 bytes, Thumb
 * func_ov004_02220df4 @ 0x02220df4, 0x4c bytes, Thumb
 * func_ov004_02220d5c @ 0x02220d5c, 0x98 bytes, Thumb
 * func_ov004_02220d58 @ 0x02220d58, 0x4 bytes, Thumb
 * func_ov004_02220d54 @ 0x02220d54, 0x4 bytes, Thumb
 * func_ov004_02220d3c @ 0x02220d3c, 0x18 bytes, Thumb
 * func_ov004_02220d24 @ 0x02220d24, 0x18 bytes, Thumb
 * func_ov004_02220d04 @ 0x02220d04, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

struct _Obj {
    void *vtbl;
};

extern int func_020044c0(void *, int, int, int);
extern void func_020b220c(void);
extern unsigned short data_020c80f8;
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_020e8858(void *p);
extern int func_020644cc(int);
extern char *func_020961a8(int a);
extern int func_0203e0a8(void *s, int a);
extern char *func_020682e0(int a);
extern void func_ov004_02221550(void *s, int a);
extern int func_0203e020(char *self);
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern int func_ov004_02220318(void *self);
extern int func_ov004_02220210(void *self);
extern int func_020ea990(void *a, void *b);
extern void func_0201b458(void *buf, void *self, void *p);
extern int func_0200322c(void *a, void *b);
extern int func_020e8b4c(int a, int b);
extern int func_020eaa2c(void *buf, void *p);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern void func_0201b044(void *p, void *m);
extern int func_020eaa6c(void *m, void *p);
extern void func_0204f818(int *x, int *y, int *v);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc5c(void *a, int x, int y, int k);
extern int func_ov004_02220084(void *self, int i);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *a, int b);
extern int func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(int a, int b);
extern void func_ov004_0220fefc(void *e, void *dst);
extern void func_ov004_02220018(void *self, void *e);
extern void func_ov004_0222005c(void *self, int i);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern Vec3 *func_02095794(int a);
extern int func_02014868(void *p);
extern int func_020b5e10(void);
extern int func_020b6098(int h, int a);
extern int func_020b5ee4(int h, int a);
extern void func_0209e474(void *p);
extern void *func_0202decc(void *arg);
extern int data_ov004_02253d80;
extern void *func_0202de4c(void *);
extern void func_020edb3c(void *);

void func_ov004_0222152c(char *self)
{
    // DECLS
    // ENDDECLS
    func_020044c0(self + 0x514, 0x4cb, 0x7f, 0x0);
    func_020b220c();
}

int func_ov004_022214f0(u8 *self)
{
    self[0xac8] = 0;
    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov004_02221444(char *s)
{
    Vec3 v;
    char *o;
    Vec3 *p;
    if (*(u8 *) (s + 0xadd) == 0) {
        if (func_020e8858(s + 0xadf) != 0) {
            return 1;
        }
        if (func_020644cc(0x65) > 0x19) {
            *(u8 *) (s + 0xadf) = 0x64;
            return 1;
        }
        o = func_020961a8(4);
        if (o != 0) {
            p = (Vec3 *) (o + 0x5c);
            v.x = p->x;
            v.y = p->y;
            v.z = p->z;
            if (func_020ea990((void *) (&v), s + 0x5c) > 0x8000) {
                func_020044c0(s + 0x514, 0x4ca, 0x7f, 0);
                *(u8 *) (s + 0xadd) = 0x1e;
            }
        }
    }
    if (*(u8 *) (s + 0xadd) != 0) {
        func_0203e0a8(s, 0);
        if (*(u8 *) (s + 0xadd) > 1) {
            func_020e8858(s + 0xadd);
        }
    }
    return 1;
}

int func_ov004_02221410(char *param)
{
    func_02019d0c(param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov004_0222137c(char *s)
{
    char *p = func_020682e0(0);
    if (p != 0 && *(int *) (p + 4) != 0) {
        return 1;
    }
    if (*(u8 *) (s + 0xadc) == 0x28) {
        func_ov004_0222152c((char *) s);
    }
    *(short *) (s + 0x8c) = 0;
    *(short *) (s + 0x8e) = -0x8000;
    *(short *) (s + 0x90) = 0;
    *(short *) (s + 0x92) = 0;
    *(short *) (s + 0x94) = -0x8000;
    *(short *) (s + 0x96) = 0;
    if (func_020e8858(s + 0xadc) != 0) {
        if (*(u8 *) (s + 0xadc) == 8) {
            *(int *) (s + 0x5c) = 0x10000;
            *(int *) (s + 0x68) = 0x10000;
            *(int *) (s + 0x64) = 0x1f000;
            *(int *) (s + 0x70) = 0x1f000;
        }
        return 1;
    }
    func_ov004_02221550(s, 2);
    return 1;
}

int func_ov004_0222136c(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xadc) = 0x0;
    return 0x1;
}

int func_ov004_02221270(char *self)
{
    // DECLS
    volatile Vec3 v;
    int b;
    int t;
    // ENDDECLS

    *(u16 *) (self + 0x8c) = 0;
    *(short *) (self + 0x8e) = -0x8000;
    *(u16 *) (self + 0x90) = 0;
    *(u16 *) (self + 0x92) = 0;
    *(short *) (self + 0x94) = -0x8000;
    *(u16 *) (self + 0x96) = 0;
    b = *(u8 *) (self + 0xadc);
    if (b == 1) {
        func_02019d0c((void *) (self + 0x564), 0, 2, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        func_0203e020(self);
        func_ov004_02221550((void *) self, 8);
        return 1;
    }
    if (b == 0) {
        v.x = 0;
        v.y = 0;
        v.z = 0;
        t = FX_MulFunc(0x4000, FX_SinCosTable_[(*(u16 *) (self + 0x8e) >> 4) * 2]);
        v.x = t + *(int *) (self + 0x5c);
        t = FX_MulFunc(0x4000, FX_SinCosTable_[(*(u16 *) (self + 0x8e) >> 4) * 2 + 1]);
        t = t + *(int *) (self + 0x64);
        v.z = t;
        func_02019d0c((void *) (self + 0x564), 1, 2, v.x, t, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        *(u8 *) (self + 0xadc) = 0x1e;
        return 1;
    }
    *(u8 *) (self + 0xadc) = (u8) (b - 1);
    return 1;
}

int func_ov004_0222123c(char *param)
{
    func_02019d0c(param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov004_02221198(void *self)
{
    char buf[0x10];
    int d, e;

    if (func_ov004_02220318(self) != 0) {
        return 1;
    }
    if (*((unsigned char *) self + 0xac8) != 2) {
        return 1;
    }
    if (func_ov004_02220210(self) != 0) {
        d = func_020ea990((char *) self + 0x5c, (char *) self + 0x89c);
        func_0201b458(buf, self, (char *) self + 0x89c);
        e = func_020e8b4c(*(short *) ((char *) self + 0x8e), func_0200322c((char *) self + 0x5c, (char *) self + 0x89c));
        if (d > *(int *) ((char *) self + 0xad8) && func_020eaa2c(buf, (char *) self + 0x5c) != 0) {
            func_ov004_02221550(self, 5);
        } else if (e > 0x2000) {
            func_ov004_02221550(self, 4);
        }
    }
    return 1;
}

int func_ov004_02221138(char *s)
{
    Vec3 out;
    func_020ea990(s + 0x5c, s + 0x89c);
    func_0201b458((void *) (&out), s, s + 0x89c);
    func_02019d0c(s + 0x564, 3, 1, 0, 0, 0, func_0200322c(s + 0x5c, s + 0x89c), 0, 0, (*(u16 *) &data_020c80f8), 0);
    return 1;
}

int func_ov004_022210fc(unsigned char *self)
{
    if (func_ov004_02220318(self) != 0) {
        return 1;
    }
    if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564) != 0) {
            func_ov004_02221550(self, 3);
        }
    }
    return 1;
}

int func_ov004_022210c8(int param)
{
    func_02019d0c((void *) ((void *) (param + 0x564)), (int) ((int) (1)), (int) ((int) (1)), (int) ((int) (0)),
                  (int) ((int) (0)), (short) ((short) ((short) (0))), (short) ((short) ((short) (0))), (int) ((int) (0)),
                  (int) ((int) (0)), (unsigned short) ((unsigned short) ((unsigned short) (data_020c80f8))),
                  (unsigned short) ((unsigned short) ((unsigned short) (0))));
    return 1;
}

int func_ov004_02220ee0(void *self)
{
    // DECLS
    int d;
    int a;
    int idx;
    void *e;
    int r0;
    int r1;
    // ENDDECLS
    int x;
    int y;
    char m[12];
    int v[3];

    if (func_ov004_02220318(self) != 0) {
        return 1;
    }
    d = func_020ea990((char *) self + 0x5c, (char *) self + 0x89c);
    func_0201b458(m, self, (char *) self + 0x89c);
    if (d > *(int *) ((char *) self + 0xad8) + 0x1000) {
        if (func_02019e00((char *) self + 0x564) == 1) {
            func_02019d0c((char *) self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    } else {
        if (func_02019e00((char *) self + 0x564) == 2) {
            func_02019d0c((char *) self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    }
    func_0201b044((char *) self + 0x350, m);
    if (d <= *(int *) ((char *) self + 0xad8) || func_020eaa6c(m, (char *) self + 0x5c) != 0) {
        func_ov004_02221550(self, 3);
    }
    v[0] = *(int *) ((char *) self + 0x5c);
    v[1] = *(int *) ((char *) self + 0x60);
    v[2] = *(int *) ((char *) self + 0x64);
    a = *(u16 *) ((char *) self + 0x8e);
    x = 0;
    y = 0;
    idx = (a >> 4) << 1;
    v[0] += FX_MulFunc(0x2000, ((const short *) FX_SinCosTable_)[idx]);
    v[2] += FX_MulFunc(0x2000, ((const short *) FX_SinCosTable_)[idx + 1]);
    func_0204f818(&x, &y, v);
    r0 = (int) func_ov004_0223cc5c(func_ov004_0223cd50(), x, y, 0);
    r1 = (int) func_ov004_0223cc5c(func_ov004_0223cd50(), x, y, 1);
    if (func_ov004_02220084(self, r1) != 0) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), r1);
        *(u16 *) ((char *) self + 0x898) = func_0204bc50(func_ov004_0220fde0(e), 0);
        func_ov004_0220fefc(e, (char *) self + 0x89c);
        func_ov004_02220018(self, e);
        func_ov004_0222005c(self, r1);
        *(int *) ((char *) self + 0x8a8) = r1;
    } else if (func_ov004_02220084(self, r0) != 0) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), r0);
        *(u16 *) ((char *) self + 0x898) = func_0204bc50(func_ov004_0220fde0(e), 0);
        func_ov004_0220fefc(e, (char *) self + 0x89c);
        func_ov004_02220018(self, e);
        func_ov004_0222005c(self, r0);
        *(int *) ((char *) self + 0x8a8) = r0;
    }
    return 1;
}

int func_ov004_02220ea8(u8 *self)
{
    int n;
    int v;

    n = func_02016104(self + 0x918);
    v = 0;
    if (n != 0) {
        v = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, v, 1);
    return 1;
}

int func_ov004_02220e40(char *s)
{
    volatile Vec3 v;
    Vec3 *q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    if (func_02014868(s + 0x618) == 0) {
        if (*(u8 *) (s + 0xac8) == 5) {
            func_020b6098(func_020b5e10(), 0);
        } else {
            func_020b5ee4(func_020b5e10(), 0);
            func_020b6098(func_020b5e10(), 6);
        }
        func_ov004_02221550(s, 8);
    }
    return 1;
}

int func_ov004_02220df4(char *self)
{
    int h;
    int n;
    h = func_02016104(self + 0x918);
    n = 0;
    if (h != 0) {
        n = func_0201c314(self, h);
    }
    *(int *) (self + 0xacc) = 0;
    if (*(u8 *) (self + 0xac8) != 0) {
        func_020147fc(self + 0x618, 0, n, 0);
    }
    return 1;
}

int func_ov004_02220d5c(char *s)
{
    u8 v;
    int h;
    int n;
    v = *(u8 *) (s + 0xadd);
    if (v != 0) {
        if (v == 1) {
            h = func_02016104(s + 0x918);
            n = 0;
            if (h != 0) {
                n = func_0201c314(s, h);
            }
            func_020147fc(s + 0x618, 0, n, 1);
        }
        func_020e8858(s + 0xadd);
        return 1;
    }
    func_0209e474(s + 0xad0);
    if (func_02014868(s + 0x618) == 0) {
        func_0203e020((char *) s);
        if (*(u8 *) (s + 0xac8) == 1) {
            *(u8 *) (s + 0xac8) = 2;
            *(int *) (s + 0xae8) = 0;
        }
        func_ov004_02221550(s, 8);
    }
    return 1;
}

int func_ov004_02220d58(void)
{
    return 1;
}

int func_ov004_02220d54(void)
{
    return 1;
}

void *func_ov004_02220d3c(void *arg)
{
    func_0202decc(arg);
    *(void **) arg = &data_ov004_02253d80;
    return arg;
}

void *func_ov004_02220d24(void *arg)
{
    *((void **) arg) = &data_ov004_02253d80;
    func_0202de4c(arg);
    return arg;
}

void *func_ov004_02220d04(struct _Obj *obj)
{
    obj->vtbl = ((char *) &data_ov004_02253d80);
    func_0202de4c(obj);
    func_020edb3c(obj);
    return obj;
}
