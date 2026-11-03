/* flea_market_villager_5: 14 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221fdb8 @ 0x0221fdb8, 0x3c bytes, Thumb
 * func_ov004_0221fda4 @ 0x0221fda4, 0x12 bytes, Thumb
 * func_ov004_0221fd70 @ 0x0221fd70, 0x34 bytes, Thumb
 * func_ov004_0221fcdc @ 0x0221fcdc, 0x94 bytes, Thumb
 * func_ov004_0221fca8 @ 0x0221fca8, 0x34 bytes, Thumb
 * func_ov004_0221fbf8 @ 0x0221fbf8, 0xb0 bytes, Thumb
 * func_ov004_0221fbc4 @ 0x0221fbc4, 0x34 bytes, Thumb
 * func_ov004_0221fad4 @ 0x0221fad4, 0xf0 bytes, Thumb
 * func_ov004_0221fa9c @ 0x0221fa9c, 0x38 bytes, Thumb
 * func_ov004_0221fa58 @ 0x0221fa58, 0x44 bytes, Thumb
 * func_ov004_0221fa20 @ 0x0221fa20, 0x38 bytes, Thumb
 * func_ov004_0221f9d4 @ 0x0221f9d4, 0x4c bytes, Thumb
 * func_ov004_0221f9d0 @ 0x0221f9d0, 0x4 bytes, Thumb
 * func_ov004_0221f990 @ 0x0221f990, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern int func_0203e0a8(void *, int);
extern Vec3 *func_02095794(int a);
extern int func_0201c378(void *s, int a);
extern int func_0201c2c8(void *s, int a);
extern int func_020e8b4c(int a, int b);
extern void func_0201b458(Vec3 *out, void *s, Vec3 *v);
extern int func_020eaa2c(Vec3 *w, void *p);
extern void func_ov004_0221fdf4(void *s, int a);
extern int func_ov004_0221ef2c(void *s);
extern int func_ov004_0221ef70(void *s);
extern void func_0201aff4(void *p, int a);
extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern void func_0201b044(char *p, Vec3 *v);
extern int func_020eaa6c(Vec3 *a, char *b);
extern int func_02016104(void *);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int func_02014868(void *p);
extern int func_020b5e10(void);
extern int func_020b6098(int x, int k);
extern int func_0203e020(void *);

int func_ov004_0221fdb8(u8 *self)
{
    self[0xa54] = 0;
    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov004_0221fda4(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203e0a8(self, 0x0);
    return 0x1;
}

int func_ov004_0221fd70(char *param)
{
    func_02019d0c(param + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}

int func_ov004_0221fcdc(char *s)
{
    Vec3 v;
    Vec3 w;
    Vec3 *q;
    int a;
    int b;
    q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    a = func_0201c378(s, 4);
    b = func_020e8b4c(*(short *) (s + 0x8e), func_0201c2c8(s, 4));
    func_0201b458(&w, s, &v);
    if (a > 0x3000 && func_020eaa2c(&w, s + 0x5c) != 0) {
        func_ov004_0221fdf4(s, 6);
    } else if (b > 0x2000) {
        func_ov004_0221fdf4(s, 5);
    }
    if (func_ov004_0221ef2c(s) != 0) {
        return 1;
    }
    func_ov004_0221ef70(s);
    return 1;
}

int func_ov004_0221fca8(char *ptr)
{
    func_02019d0c((void *) (ptr + 0x564), 3, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov004_0221fbf8(char *s)
{
    Vec3 v;
    Vec3 w;
    Vec3 *q;
    int a;
    int b;
    if (func_ov004_0221ef2c(s) != 0) {
        return 1;
    }
    if (func_ov004_0221ef70(s) != 0) {
        return 1;
    }
    q = func_02095794(4);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    a = func_0201c378(s, 4);
    b = func_0201c2c8(s, 4);
    func_0201b458(&w, s, &v);
    if (a > 0x3000 && func_020eaa2c(&w, s + 0x5c) != 0) {
        func_ov004_0221fdf4(s, 6);
        return 1;
    }
    func_0201aff4(s + 0x350, b);
    if (func_02019e00(s + 0x564) == 3) {
        if (func_02019de8(s + 0x564) != 0) {
            func_ov004_0221fdf4(s, 4);
        }
    }
    return 1;
}

int func_ov004_0221fbc4(int param)
{
    func_02019d0c((void *) ((void *) (param + 0x564)), (int) ((int) (1)), (int) ((int) (1)), (int) ((int) (0)), (int) ((int) (0)), (short) ((short) ((short) (0))), (short) ((short) ((short) (0))), (int) ((int) (0)), (int) ((int) (0)), (unsigned short) ((unsigned short) ((unsigned short) (data_020c80f8))), (unsigned short) ((unsigned short) ((unsigned short) (0))));
    return 1;
}

int func_ov004_0221fad4(char *self)
{
    // DECLS
    Vec3 v;
    Vec3 w;
    int h;
    int *p;
    // ENDDECLS

    if (func_ov004_0221ef2c((void *) self) != 0) {
        return 1;
    }
    if (func_ov004_0221ef70((void *) self) != 0) {
        return 1;
    }
    p = (int *) func_02095794(4);
    v.x = p[0];
    v.y = p[1];
    v.z = p[2];
    h = func_0201c378((void *) self, 4);
    func_0201b458(&w, (void *) self, &v);
    if (h > 0x4000) {
        if (func_02019e00((void *) (self + 0x564)) == 1) {
            func_02019d0c((void *) (self + 0x564), 2, 1, 0, 0, 0x800, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
        }
    } else if (func_02019e00((void *) (self + 0x564)) == 2) {
        func_02019d0c((void *) (self + 0x564), 1, 1, 0, 0, 0, 0, 0, 0, (*(u16 *) &data_020c80f8), 0);
    }
    func_0201b044(self + 0x350, &w);
    if (h <= 0x3000 || func_020eaa6c(&w, self + 0x5c) != 0) {
        func_ov004_0221fdf4((void *) self, 4);
    }
    return 1;
}

int func_ov004_0221fa9c(u8 *self)
{
    int n;
    int v;

    n = func_02016104(self + 0x8a8);
    v = 0;
    if (n != 0) {
        v = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, v, 1);
    return 1;
}

int func_ov004_0221fa58(void *self)
{
    volatile int t[3];
    int *p = (int *) func_02095794(4);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    if (func_02014868((char *) self + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov004_0221fdf4(self, 2);
    }
    return 1;
}

int func_ov004_0221fa20(u8 *self)
{
    int n;
    int v;

    n = func_02016104(self + 0x8a8);
    v = 0;
    if (n != 0) {
        v = func_0201c314(self, n);
    }
    func_020147fc(self + 0x618, 0, v, 0);
    return 1;
}

int func_ov004_0221f9d4(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02014868(self + 0x618) == 0x0) {
        if (*(u8 *) (self + 0xa54) == 0x0) {
            *(u8 *) (self + 0xa54) = 0x1;
        }
        *(u16 *) (self + 0x898) = 0xfff1;
        func_0203e020(self);
        func_ov004_0221fdf4(self, 0x2);
    }
    return 0x1;
}

int func_ov004_0221f9d0(void)
{
    return 1;
}

int func_ov004_0221f990(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xa55) = 0x32;
    func_02019d0c(self + 0x564, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, *(u16 *) ((char *) ((void * *) &data_020c80f8)), 0x0);
    return 0x1;
}
