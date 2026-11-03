/* chest_2: 18 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217024 @ 0x02217024, 0x4 bytes, Thumb
 * func_ov004_02217020 @ 0x02217020, 0x2 bytes, Thumb
 * func_ov004_0221701c @ 0x0221701c, 0x4 bytes, Thumb
 * func_ov004_02217010 @ 0x02217010, 0xc bytes, Thumb
 * func_ov004_02216fb0 @ 0x02216fb0, 0x5e bytes, Thumb
 * func_ov004_02216f80 @ 0x02216f80, 0x30 bytes, Thumb
 * func_ov004_02216f6c @ 0x02216f6c, 0x14 bytes, Thumb
 * func_ov004_02216f50 @ 0x02216f50, 0x1c bytes, Thumb
 * func_ov004_02216f34 @ 0x02216f34, 0x1a bytes, Thumb
 * func_ov004_02216f18 @ 0x02216f18, 0x1a bytes, Thumb
 * func_ov004_02216ed4 @ 0x02216ed4, 0x44 bytes, Thumb
 * func_ov004_02216eb8 @ 0x02216eb8, 0x1c bytes, Thumb
 * func_ov004_02216eb4 @ 0x02216eb4, 0x4 bytes, Thumb
 * func_ov004_02216ea8 @ 0x02216ea8, 0xc bytes, Thumb
 * func_ov004_02216e50 @ 0x02216e50, 0x56 bytes, Thumb
 * func_ov004_02216e20 @ 0x02216e20, 0x30 bytes, Thumb
 * func_ov004_02216e0c @ 0x02216e0c, 0x14 bytes, Thumb
 * func_ov004_02216df0 @ 0x02216df0, 0x1c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02216ed4 {
    u8 pad_00[4];
};

extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(void *a, void *self);
extern int func_ov004_02217230(void *self);
extern int func_ov004_0223cb18(void *h);
extern char *func_ov004_0223cb24(void *h);
extern int func_ov004_0222c030(int *v, char *a, char *b, u16 *t);
extern int func_ov004_02217124(void *self, int k);
extern int func_ov004_0222c2b0(void);
extern int func_02052738(void *, int, int, int);
extern int func_0206fbf8(int k);
extern int func_0206fbc0(void);
extern int func_ov004_0222c00c(int *p);
extern int func_0203e020(void *);

int func_ov004_02217024(void *callbackObject)
{
    return 1;
}

void func_ov004_02217020(void *callbackObject) {}

int func_ov004_0221701c(void *callbackObject)
{
    return 1;
}

void func_ov004_02217010(int a)
{
    func_ov004_02217124((void *) a, 2);
}

int func_ov004_02216fb0(void *self)
{
    u16 t;
    int v;
    void *h;
    char *a;

    h = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    v = func_ov004_02217230(self);
    if (v != -1) {
        t = func_ov004_0223cb18(h);
        a = func_ov004_0223cb24(h);
        if (func_ov004_0222c030(&v, a, func_ov004_0223cb24(h) + 8, &t)) {
            return 1;
        }
        return 0;
    }
    return 1;
}

void func_ov004_02216f80(void *self)
{
    if (func_ov004_02217230(self) == -1) {
        func_ov004_02217124(self, 3);
    } else if (func_ov004_0222c2b0() != 0) {
        func_ov004_02217124(self, 3);
    }
}

int func_ov004_02216f6c(char *self)
{
    // DECLS
    // ENDDECLS
    return func_02052738(self, 0x1, 0xff, 0x1);
}

void func_ov004_02216f50(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x860) == 0x2) {
        func_ov004_02217124(self, 0x4);
    }
}

int func_ov004_02216f34(void *callbackObject)
{
    if (func_0206fbf8(0x22) != 0) {
        return 1;
    }
    return 0;
}

int func_ov004_02216f18(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_0206fbc0();
    if (v1 != 0x0) {
        return func_ov004_02217124(self, 0x5);
    }
    return v1;
}

int func_ov004_02216ed4(struct UnkStruct_02216ed4 *self)
{
    int v;

    v = func_ov004_02217230((void *) self);
    if (v != -1) {
        if (func_ov004_0222c00c(&v)) {
            return func_02052738((void *) self, 3, 0xff, 1);
        }
        return 0;
    }
    return func_02052738((void *) self, 3, 0xff, 1);
}

void func_ov004_02216eb8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x860) == 0x0) {
        func_0203e020(self);
    }
}

int func_ov004_02216eb4(void *callbackObject)
{
    return 1;
}

void func_ov004_02216ea8(int arg)
{
    func_ov004_02217124((void *) arg, 7);
}

int func_ov004_02216e50(void *self)
{
    short a;
    int t;
    void *h;
    char *p;

    h = func_ov004_0223ca9c((void *) ((int) func_ov004_0223cb10()), self);
    t = func_ov004_02217230(self);
    if (t != -1) {
        a = (short) func_ov004_0223cb18(h);
        p = func_ov004_0223cb24(h);
        func_ov004_0222c030(&t, p, func_ov004_0223cb24(h) + 8, (u16 *) (&a));
        return 1;
    }
    return 1;
}

void func_ov004_02216e20(void *self)
{
    if (func_ov004_02217230(self) == -1) {
        func_ov004_02217124(self, 8);
    } else if (func_ov004_0222c2b0() != 0) {
        func_ov004_02217124(self, 8);
    }
}

int func_ov004_02216e0c(char *self)
{
    // DECLS
    // ENDDECLS
    return func_02052738(self, 0x1, 0xff, 0x1);
}

void func_ov004_02216df0(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x860) == 0x2) {
        func_ov004_02217124(self, 0x9);
    }
}
