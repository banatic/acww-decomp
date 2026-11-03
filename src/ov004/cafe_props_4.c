/* cafe_props_4: 20 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222e644 @ 0x0222e644, 0x18 bytes, Thumb
 * func_ov004_0222e5a4 @ 0x0222e5a4, 0xa0 bytes, Thumb
 * func_ov004_0222e5a0 @ 0x0222e5a0, 0x4 bytes, Thumb
 * func_ov004_0222e4fc @ 0x0222e4fc, 0xa4 bytes, Thumb
 * func_ov004_0222e4f8 @ 0x0222e4f8, 0x4 bytes, Thumb
 * func_ov004_0222e450 @ 0x0222e450, 0xa8 bytes, Thumb
 * func_ov004_0222e44c @ 0x0222e44c, 0x4 bytes, Thumb
 * func_ov004_0222e25c @ 0x0222e25c, 0x1f0 bytes, Thumb
 * func_ov004_0222e220 @ 0x0222e220, 0x3c bytes, Thumb
 * func_ov004_0222e1b8 @ 0x0222e1b8, 0x68 bytes, Thumb
 * func_ov004_0222e1b4 @ 0x0222e1b4, 0x4 bytes, Thumb
 * func_ov004_0222e128 @ 0x0222e128, 0x8c bytes, Thumb
 * func_ov004_0222e124 @ 0x0222e124, 0x4 bytes, Thumb
 * func_ov004_0222e0b8 @ 0x0222e0b8, 0x6c bytes, Thumb
 * func_ov004_0222e0a0 @ 0x0222e0a0, 0x18 bytes, Thumb
 * func_ov004_0222df4c @ 0x0222df4c, 0x154 bytes, Thumb
 * func_ov004_0222df3c @ 0x0222df3c, 0x10 bytes, Thumb
 * func_ov004_0222deb4 @ 0x0222deb4, 0x88 bytes, Thumb
 * func_ov004_0222de98 @ 0x0222de98, 0x1c bytes, Thumb
 * func_ov004_0222de14 @ 0x0222de14, 0x84 bytes, Thumb
 */

#include "types.h"

extern unsigned short func_ov004_022236c4(void);
extern int func_ov004_022236a8(void);
extern void func_ov004_0222db14(void *, int, void *, void *, int, int, int, int);
extern void func_02055060(void *, int, int, int, int, int);
extern int func_ov004_0222c3c4(void *, int);
extern int func_0209120c(int, void *, void *, int);
extern void func_0209129c(int);
extern int func_02054ecc(void *);
extern int func_02056f94(void *);
extern void func_0203ab64(void);
extern void func_0203ae98(void);
extern int func_0203aeac(void);
extern void func_ov004_0222e860(char *object);
extern char *data_ov004_02258310;
extern int func_ov004_0222c3f4(void *, void *);
extern int func_ov004_0222c348(void *, void *);
extern void *func_ov004_0222c3a0(void *);
extern void *func_ov004_0222c33c(void *);
extern int func_02055f2c(void *, void *, int);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);

int func_ov004_0222e644(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xef9) = 0x1;
    *(u8 *) (self + 0xef0) = 0x1;
    return 0x1;
}

void func_ov004_0222e5a4(char *self)
{
    func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf2) {
        func_ov004_0222db14(self, 0, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf4) {
        func_ov004_0222db14(self, 1, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    }
}

int func_ov004_0222e5a0(void *callbackObject)
{
    return 1;
}

void func_ov004_0222e4fc(char *self)
{
    func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf3) {
        func_ov004_0222db14(self, 0, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf5) {
        func_ov004_0222db14(self, 1, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    }
}

int func_ov004_0222e4f8(void *callbackObject)
{
    return 1;
}

void func_ov004_0222e450(char *self)
{
    func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf3) {
        func_ov004_0222db14(self, 3, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf5) {
        func_ov004_0222db14(self, 4, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    }
}

int func_ov004_0222e44c(void *callbackObject)
{
    return 1;
}

void func_ov004_0222e25c(u8 *self)
{
    unsigned int frame = func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf2) {
        func_ov004_0222db14(self, 0, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf4) {
        func_ov004_0222db14(self, 1, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf6) {
        if (frame <= 6) {
            self[0xef9] = 1;
            self[0xef0] = 1;
        } else {
            self[0xef9] = 0;
            self[0xef0] = 0;
        }
        if (frame >= 18) {
            self[0xef1] = 1;
            self[0xef2] = 1;
        } else {
            self[0xef1] = 0;
            self[0xef2] = 0;
        }
        func_ov004_0222db14(self, 2, self + 0xec, self + 0x1a4, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 2, self + 0x290, self + 0x908, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 2, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 2, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf3) {
        func_ov004_0222db14(self, 0, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 0, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    } else if (func_ov004_022236a8() == 0xf5) {
        func_ov004_0222db14(self, 1, self + 0x348, self + 0x9ac, 0, 0x1000, 0, 0);
        func_ov004_0222db14(self, 1, self + 0x400, self + 0xa50, 0, 0x1000, 0, 0);
    }
}

int func_ov004_0222e220(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055060(self + 0x4b8, func_ov004_0222c3c4(self + 0xaf4, 0x0), 0x1, 0x1000, 0x0, 0x0);
    return 0x1;
}

void func_ov004_0222e1b8(char *self)
{
    // DECLS
    int v2;
    // ENDDECLS
    func_ov004_022236c4();
    v2 = func_ov004_022236a8();
    if (v2 == 0xf7) {
        func_ov004_0222db14((void *) ((int) (self)), (int) (0x5), (void *) ((int) (self + 0x348)), (void *) ((int) (self + 0x9ac)), (unsigned char) ((unsigned char) (0x0)), (int) (0x1000), (unsigned short) ((unsigned short) (0x0)), (unsigned short) ((unsigned short) (0x0)));
        func_ov004_0222db14((void *) ((int) (self)), (int) (0x3), (void *) ((int) (self + 0x400)), (void *) ((int) (self + 0xa50)), (unsigned char) ((unsigned char) (0x0)), (int) (0x1000), (unsigned short) ((unsigned short) (0x0)), (unsigned short) ((unsigned short) (0x0)));
    }
}

int func_ov004_0222e1b4(void *callbackObject)
{
    return 1;
}

void func_ov004_0222e128(char *self)
{
    int a = func_ov004_022236c4();
    if (func_ov004_022236a8() == 0xf8) {
        func_ov004_0222db14(self, 6, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
        func_ov004_0222db14(self, 4, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
        if (a == 0x3b) {
            *(int *) (self + 0xf38) = func_0209120c(0x6b, self + 0xf10, self + 0x8e, 0);
        }
    }
}

int func_ov004_0222e124(void *callbackObject)
{
    return 1;
}

void func_ov004_0222e0b8(char *self)
{
    // DECLS
    unsigned short v1;
    int v2;
    // ENDDECLS
    v1 = func_ov004_022236c4();
    v2 = func_ov004_022236a8();
    if (v2 == 0xf8) {
        func_ov004_0222db14((void *) ((int) self), 0x7, (void *) ((int) (self + 0x348)), (void *) ((int) (self + 0x9ac)), (unsigned char) 0x3, 0x1000, (unsigned short) v1, (unsigned short) 0x0);
        func_ov004_0222db14((void *) ((int) self), 0x5, (void *) ((int) (self + 0x400)), (void *) ((int) (self + 0xa50)), (unsigned char) 0x3, 0x1000, (unsigned short) v1, (unsigned short) 0x0);
    }
}

int func_ov004_0222e0a0(char *self)
{
    // DECLS
    // ENDDECLS
    func_0209129c(*(int *) (self + 0xf38));
    return 0x1;
}

void func_ov004_0222df4c(char *self)
{
    int current;
    current = func_02054ecc(self + 0x348);
    if (current == func_ov004_0222c3c4(self + 0x9ac, 6) && func_02056f94(self + 0x3e4)) {
        func_ov004_0222db14(self, 9, self + 0x348, self + 0x9ac, (unsigned char) 1, 0x1000, 0, 0);
        func_ov004_0222db14(self, 7, self + 0x400, self + 0xa50, (unsigned char) 1, 0x1000, 0, 0);
    } else {
        current = func_02054ecc(self + 0x348);
        if (current == func_ov004_0222c3c4(self + 0x9ac, 9) && func_02056f94(self + 0x3e4)) {
            func_ov004_0222db14(self, 10, self + 0x348, self + 0x9ac, (unsigned char) 1, 0x1000, 0, 0);
            func_ov004_0222db14(self, 8, self + 0x400, self + 0xa50, (unsigned char) 1, 0x1000, 0, 0);
        } else {
            current = func_02054ecc(self + 0x348);
            if (current == func_ov004_0222c3c4(self + 0x9ac, 10) && func_02056f94(self + 0x3e4)) {
                func_0203ab64();
                func_0203ae98();
                func_ov004_0222db14(self, 11, self + 0x348, self + 0x9ac, (unsigned char) 1, 0x1000, 0, 0);
                func_ov004_0222db14(self, 9, self + 0x400, self + 0xa50, (unsigned char) 1, 0x1000, 0, 0);
            }
        }
    }
}

int func_ov004_0222df3c(void *callbackObject)
{
    func_0203aeac();
    return 1;
}

void func_ov004_0222deb4(char *self)
{
    if (func_02054ecc(self + 0x348) == func_ov004_0222c3c4(self + 0x9ac, 0xb)) {
        if (func_02056f94(self + 0x3e4) != 0) {
            func_ov004_0222db14(self, 0xc, self + 0x348, self + 0x9ac, 1, 0x1000, 0, 0);
            func_ov004_0222db14(self, 0xa, self + 0x400, self + 0xa50, 1, 0x1000, 0, 0);
        }
    }
}

void func_ov004_0222de98(void)
{
    if (data_ov004_02258310 != 0) {
        func_ov004_0222e860(data_ov004_02258310);
    }
}

void func_ov004_0222de14(char *self, int i, void *p2, void *p3)
{
    char *a = self + 0x908 + i * 0xa4;
    char *b;
    func_ov004_0222c3f4(a, p2);
    b = self + 0xecc + i * 4;
    func_ov004_0222c348(b, p3);
    func_02055f2c(self + 0x290 + i * 0xb8, func_ov004_0222c3a0(a), 0);
    NNS_G3dBindMdlTex(func_ov004_0222c3a0(a), func_ov004_0222c33c(b));
    NNS_G3dBindMdlPltt(func_ov004_0222c3a0(a), func_ov004_0222c33c(b));
}
