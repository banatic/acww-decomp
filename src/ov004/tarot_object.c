/* tarot_object: 13 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02230754 @ 0x02230754, 0x2c bytes, Thumb
 * func_ov004_02230750 @ 0x02230750, 0x2 bytes, Thumb
 * func_ov004_022306d0 @ 0x022306d0, 0x80 bytes, Thumb
 * func_ov004_022306a8 @ 0x022306a8, 0x28 bytes, Thumb
 * func_ov004_0223063c @ 0x0223063c, 0x6c bytes, Thumb
 * func_ov004_02230620 @ 0x02230620, 0x1c bytes, Thumb
 * func_ov004_022305a0 @ 0x022305a0, 0x80 bytes, Thumb
 * func_ov004_02230538 @ 0x02230538, 0x68 bytes, Thumb
 * func_ov004_02230518 @ 0x02230518, 0x20 bytes, Thumb
 * func_ov004_022304f8 @ 0x022304f8, 0x20 bytes, Thumb
 * func_ov004_022304d8 @ 0x022304d8, 0x20 bytes, Thumb
 * func_ov004_022304bc @ 0x022304bc, 0x1c bytes, Thumb
 * func_ov004_02230438 @ 0x02230438, 0x84 bytes, Thumb
 */

#include "types.h"

extern void func_02055060(void *, int, int, int, int, int);
extern void func_02056478(void *, int, int, int, int);
extern int func_ov004_0222c3a4(void *, int);
extern int func_ov004_0222c3c4(void *, int arg1);
extern int func_ov045_02260618(void);
extern int func_02056f94(void *);
extern int func_ov004_0223080c(void *, int);
extern void *data_ov004_02258870;
extern void func_ov004_022308dc(char *object);
extern int func_ov004_0222c3f4(void *, void *);
extern int func_ov004_0222c348(void *, void *);
extern void *func_ov004_0222c3a0(void *);
extern void *func_ov004_0222c33c(void *);
extern int func_02055f2c(void *, void *, int);
extern int NNS_G3dBindMdlTex(void *, void *);
extern int NNS_G3dBindMdlPltt(void *, void *);

int func_ov004_02230754(u8 *self)
{
    u8 i = 0;
    u8 z;
    *(self + 0x6d4) = 0;
    z = 0;
    do {
        *(self + i + 0x6b0) = z;
        i = i + 1;
    } while (i < 3);
    return 1;
}

void func_ov004_02230750(void *callbackObject) {}

int func_ov004_022306d0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x6d4) = 0x1;
    *(u8 *) (self + 0x6b0) = 0x0;
    *(u8 *) (self + 0x6b1) = 0x1;
    *(u8 *) (self + 0x6b2) = 0x0;
    func_02055060(self + 0x400, func_ov004_0222c3c4(self + 0x600, 0), 0x1, 0x1000, 0x0, 0x0);
    func_02056478(self + 0x6b4, func_ov004_0222c3a4(self + 0x55c, 0x0), 0x1, 0x1000, 0x0);
    return 0x1;
}

int func_ov004_022306a8(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov045_02260618();
    if (v1 == 0xb) {
        *(u8 *) (self + 0x6d4) = 0x0;
        *(u8 *) (self + 0x6b2) = 0x1;
        return 0x6b2;
    }
    return v1;
}

int func_ov004_0223063c(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x6d4) = 0x0;
    *(u8 *) (self + 0x6b0) = 0x0;
    *(u8 *) (self + 0x6b1) = 0x1;
    *(u8 *) (self + 0x6b2) = 0x1;
    *(int *) (self + 0x4a4) = ((u32) ((*(int *) (self + 0x4a0) >> 12) << 16) >> 4);
    *(void **) (self + 0x4ac) = 0x0;
    *(int *) (self + 0x6bc) = ((u32) ((*(int *) (self + 0x6b8) >> 12) << 16) >> 4);
    *(void **) (self + 0x6c4) = 0x0;
    return 0x1;
}

int func_ov004_02230620(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov045_02260618();
    if (v1 == 0x9) {
        *(u8 *) (self + 0x6b0) = 0x1;
        return 0x6b0;
    }
    return v1;
}

int func_ov004_022305a0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x6d4) = 0x0;
    *(u8 *) (self + 0x6b0) = 0x1;
    *(u8 *) (self + 0x6b1) = 0x1;
    *(u8 *) (self + 0x6b2) = 0x1;
    func_02055060(self + 0x400, func_ov004_0222c3c4(self + 0x600, 1), 0x1, 0x1000, 0x0, 0x0);
    func_02056478(self + 0x6b4, func_ov004_0222c3a4(self + 0x55c, 0x1), 0x1, 0x1000, 0x0);
    return 0x1;
}

void func_ov004_02230538(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov045_02260618() == 0x7) {
        *(u8 *) (self + 0x6b0) = 0x0;
    }
    if (func_ov045_02260618() == 0x12) {
        *(u8 *) (self + 0x6b2) = 0x0;
    }
    if (func_ov045_02260618() == 0x13) {
        *(u8 *) (self + 0x6d4) = 0x1;
    }
    if (func_ov045_02260618() == 0x25) {
        *(u8 *) (self + 0x6d4) = 0x0;
    }
    if (func_02056f94(self + 0x49c) != 0x0) {
        func_ov004_0223080c(self, 0x0);
        return;
    }
}

int func_ov004_02230518(void)
{
    if (data_ov004_02258870 != 0) {
        return func_ov004_0223080c(data_ov004_02258870, 1);
    }
    return 0;
}

int func_ov004_022304f8(void)
{
    if (data_ov004_02258870 != 0) {
        return func_ov004_0223080c(data_ov004_02258870, 2);
    }
    return 0;
}

int func_ov004_022304d8(void)
{
    if (data_ov004_02258870 != 0) {
        return func_ov004_0223080c(data_ov004_02258870, 3);
    }
    return 0;
}

void func_ov004_022304bc(void)
{
    if ((*(char **) &data_ov004_02258870) != 0) {
        func_ov004_022308dc((*(char **) &data_ov004_02258870));
    }
}

void func_ov004_02230438(char *self, int i, void *p2, void *p3)
{
    char *a = self + 0x4b8 + i * 0xa4;
    char *b;
    func_ov004_0222c3f4(a, p2);
    b = self + 0x6a4 + i * 4;
    func_ov004_0222c348(b, p3);
    func_02055f2c(self + 0x290 + i * 0xb8, func_ov004_0222c3a0(a), 0);
    NNS_G3dBindMdlTex(func_ov004_0222c3a0(a), func_ov004_0222c33c(b));
    NNS_G3dBindMdlPltt(func_ov004_0222c3a0(a), func_ov004_0222c33c(b));
}
