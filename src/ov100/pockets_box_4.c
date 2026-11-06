/* pockets_box_4: 38 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229d67c @ 0x0229d67c, 0x1e bytes, Thumb
 * func_ov100_0229d648 @ 0x0229d648, 0x34 bytes, Thumb
 * func_ov100_0229d63c @ 0x0229d63c, 0xc bytes, Thumb
 * func_ov100_0229d630 @ 0x0229d630, 0xc bytes, Thumb
 * func_ov100_0229d620 @ 0x0229d620, 0x10 bytes, Thumb
 * func_ov100_0229d60c @ 0x0229d60c, 0x12 bytes, Thumb
 * func_ov100_0229d5d4 @ 0x0229d5d4, 0x36 bytes, Thumb
 * func_ov100_0229d5c4 @ 0x0229d5c4, 0xe bytes, Thumb
 * func_ov100_0229d550 @ 0x0229d550, 0x74 bytes, Thumb
 * func_ov100_0229d4f4 @ 0x0229d4f4, 0x5c bytes, Thumb
 * func_ov100_0229d4a8 @ 0x0229d4a8, 0x4a bytes, Thumb
 * func_ov100_0229d48c @ 0x0229d48c, 0x1a bytes, Thumb
 * func_ov100_0229d478 @ 0x0229d478, 0x12 bytes, Thumb
 * func_ov100_0229d42c @ 0x0229d42c, 0x4a bytes, Thumb
 * func_ov100_0229d3d8 @ 0x0229d3d8, 0x52 bytes, Thumb
 * func_ov100_0229d208 @ 0x0229d208, 0x1d0 bytes, Thumb
 * func_ov100_0229d1d0 @ 0x0229d1d0, 0x36 bytes, Thumb
 * func_ov100_0229d194 @ 0x0229d194, 0x3a bytes, Thumb
 * func_ov100_0229d158 @ 0x0229d158, 0x3a bytes, Thumb
 * func_ov100_0229d118 @ 0x0229d118, 0x40 bytes, Thumb
 * func_ov100_0229d0dc @ 0x0229d0dc, 0x3a bytes, Thumb
 * func_ov100_0229d0c0 @ 0x0229d0c0, 0x1c bytes, Thumb
 * func_ov100_0229d068 @ 0x0229d068, 0x58 bytes, Thumb
 * func_ov100_0229d04c @ 0x0229d04c, 0x1c bytes, Thumb
 * func_ov100_0229d014 @ 0x0229d014, 0x36 bytes, Thumb
 * func_ov100_0229cfd0 @ 0x0229cfd0, 0x44 bytes, Thumb
 * func_ov100_0229cf30 @ 0x0229cf30, 0xa0 bytes, Thumb
 * func_ov100_0229cecc @ 0x0229cecc, 0x64 bytes, Thumb
 * func_ov100_0229ce90 @ 0x0229ce90, 0x3c bytes, Thumb
 * func_ov100_0229ce58 @ 0x0229ce58, 0x38 bytes, Thumb
 * func_ov100_0229ce24 @ 0x0229ce24, 0x34 bytes, Thumb
 * func_ov100_0229cdf4 @ 0x0229cdf4, 0x30 bytes, Thumb
 * func_ov100_0229cd7c @ 0x0229cd7c, 0x78 bytes, Thumb
 * func_ov100_0229cd4c @ 0x0229cd4c, 0x30 bytes, Thumb
 * func_ov100_0229cd10 @ 0x0229cd10, 0x3c bytes, Thumb
 * func_ov100_0229ccb8 @ 0x0229ccb8, 0x58 bytes, Thumb
 * func_ov100_0229cc70 @ 0x0229cc70, 0x48 bytes, Thumb
 * func_ov100_0229cc60 @ 0x0229cc60, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229d648 {
    char pad_00[0x28DC];
    unsigned short array[15];
};

typedef struct {
    char pad_00[0xcc];
    char unk_CC;
} UnkStruct_0229d1d0;

typedef struct {
    char pad_00[0x218c];
    unsigned char unk_218C;
    char pad_218D[0x792];
    unsigned char unk_291F;
    char pad_2920[0x1];
    unsigned char unk_2921;
} Object;

struct big_struct {
    char pad_00[0x2274];
    char sub[1];
    char pad_2275[0x65f];
    int unk_28D4;
    int unk_28D8;
};

struct UnkStruct_0229cdf4 {
    char pad_00[0x225c];
    char ptr_area[0x678];
    int unk_28D4;
    int unk_28D8;
};

typedef struct {
    char pad_00[0xcc];
    char sub[0x2918 - 0xcc];
    unsigned short unk_2918;
    char pad_291A[2];
    unsigned char unk_291C;
    unsigned char unk_291D;
} UnkStruct_0229cd7c;

struct UnkStruct_0229cd4c;

struct UnkStruct_0229cd4c {
    unsigned char pad_00[0x2918];
    unsigned short unk_2918;
    unsigned char pad_291A[2];
    unsigned char unk_291C;
    unsigned char unk_291D;
};

typedef struct {
    unsigned char pad_00[0x2918];
    unsigned short unk_2918;
    unsigned char pad_291A[2];
    unsigned char unk_291C;
    unsigned char unk_291D;
} UnkStruct_0229cd10;

typedef struct {
    char pad_00[0x2921];
    unsigned char unk_2921;
} UnkStruct_0229cc70;

extern int func_02099fe8(void);
extern void func_020b9ccc(void *obj);
extern int func_ov094_0229aee8(void *ptr, int unused1, int unused2);
extern int func_ov094_0229a69c(void *ptr, int value);
extern int func_ov094_0229aeb8(void *ptr, int a, int b);
extern void func_ov094_0229aa14(int, int, int, int);
extern void func_ov094_0229a9b4(int, int);
extern int func_ov094_0229aba4(void *, int);
extern int func_ov094_0229ab90(int a, int b);
extern int func_ov094_02299a54(int id);
extern int func_ov094_02299b04(int id);
extern int func_0206fca4(void);
extern int func_0209ded0(void);
extern void func_ov094_0229a888(char *p, int v);
extern int func_ov094_0229a8bc(char *a, int b);
extern int func_ov094_0229aaac(unsigned char *p, int q);
extern int func_ov094_0229aa84(void *ptr, int val);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229ab1c(void *p, int x);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_0229aafc(char *a, int b);
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;
extern int func_0206fe54(void);
extern void func_0208aa80(void *);
extern void func_0208aa78(void *);
extern void func_0208aa60(void *, int, int);
extern void func_ov094_0229abb8(void *, void *, int);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);
extern int func_ov100_0229c2c0(void *, int);
extern void func_ov094_0229a6bc(void *, int, int);
extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);
extern int func_ov002_02209d84(void *addr);
extern int func_ov002_02209d7c(void *addr);
extern void func_ov094_0229aa58(void *sub, int v);
extern void func_ov094_0229a99c(void *sub, unsigned short a, unsigned char b);
extern void func_ov100_0229ca7c(unsigned char *p);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int v);

void func_ov100_0229d4a8(int r0, int r1, int r2, int r3);
int func_ov100_0229d48c(int a, int b);
int func_ov100_0229d478(int a, unsigned int b);
int func_ov100_0229d158(int p1, int p2);
int func_ov100_0229d118(unsigned char *p0, int p1);
int func_ov100_0229d0dc(void *p0, int p1);
void func_ov100_0229cd4c(struct UnkStruct_0229cd4c *obj, int param);
int func_ov100_0229cc70(UnkStruct_0229cc70 *p);
int func_ov100_0229cc60(void *p);

int func_ov100_0229d67c(void *receiver)
{
    int r0;
    r0 = func_02099fe8();
    if (r0 == -1) {
        return 0x20;
    }
    return (unsigned char) r0;
}

unsigned char func_ov100_0229d648(struct UnkStruct_0229d648 *obj)
{
    int i;
    for (i = 0; i < 15; i++) {
        if (obj->array[i] == 0xFFF1) {
            i += 15;
            return (unsigned char) i;
        }
    }
    return 0x20;
}

void func_ov100_0229d63c(void *obj)
{
    func_020b9ccc((char *) obj + 0x94);
}

int func_ov100_0229d630(int a, unsigned int b)
{
    if (b > 14) {
        return 0;
    } else {
        return 1;
    }
}

int func_ov100_0229d620(int a, unsigned int b)
{
    if (b >= 15 && b <= 29) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov100_0229d60c(int unused, int value)
{
    if ((unsigned char) (value + 0xe2) <= 1) {
        return 1;
    }
    return 0;
}

int func_ov100_0229d5d4(int a, int b)
{
    if (func_ov100_0229d630(a, b)) {
        return (unsigned char) b;
    }
    if (func_ov100_0229d620(a, b)) {
        return func_ov100_0229d48c(a, b);
    }
    return 0;
}

unsigned char func_ov100_0229d5c4(int p0, unsigned int p1)
{
    if (p1 <= 14) {
        return (unsigned char) p1;
    }
    return 0x20;
}

int func_ov100_0229d550(void *self, int arg1, int arg2, int flag)
{
    int result;
    result = func_ov094_0229aee8((char *) self + 0xcc, arg1, arg2);
    if (result != 0x23) {
        if (flag != 0) {
            if (func_ov094_0229a69c((char *) self + 0xcc, result) != 0) {
                return 0x20;
            }
        }
        return (int) func_ov100_0229d5c4((int) self, result);
    } else {
        result = func_ov094_0229aeb8((char *) self + 0xcc, arg1, arg2);
        if (result != 0x23) {
            if (flag != 0) {
                if (func_ov094_0229a69c((char *) self + 0xcc, result) != 0) {
                    return 0x20;
                }
            }
            return func_ov100_0229d478((int) self, result);
        } else {
            return 0x20;
        }
    }
}

int func_ov100_0229d4f4(unsigned char *a, int b)
{
    if (func_ov100_0229d630((int) a, b) != 0 || func_ov100_0229d620((int) a, b) != 0) {
        int v1 = func_ov100_0229d118(a, b);
        if (v1 != 0xFFF1) {
            int v2 = func_ov100_0229d0dc((void *) a, b);
            func_ov100_0229d4a8((int) a, a[0x2920], v1, v2);
        }
        func_ov100_0229cd4c((struct UnkStruct_0229cd4c *) a, b);
        return 1;
    }
    return 0;
}

void func_ov100_0229d4a8(int r0, int r1, int r2, int r3)
{
    int r4 = r0;
    int r5 = r1;
    int r6 = r2;
    int r7 = r3;

    if (func_ov100_0229d630(r0, r1) == 0) {
        if (func_ov100_0229d620(r4, r5) == 0) {
            return;
        }
    }

    r5 = func_ov100_0229d5d4(r4, r5);
    func_ov094_0229aa14(r4 + 0xcc, r5, r6, r7);
    func_ov094_0229a9b4(r4 + 0xcc, r5);
}

int func_ov100_0229d48c(int a, int b)
{
    if (func_ov100_0229d620(a, b) != 0) {
        return (unsigned char) b;
    }
    return 0xF;
}

int func_ov100_0229d478(int a, unsigned int b)
{
    if (b >= 0x0f && b <= 0x1d) {
        return (unsigned char) b;
    }
    return 0x20;
}

int func_ov100_0229d42c(void *r0, void *r1)
{
    if (func_ov100_0229d630((int) r0, (unsigned int) r1) != 0 || func_ov100_0229d620((int) r0, (unsigned int) r1) != 0) {
        return func_ov094_0229aba4((char *) r0 + 0xcc, func_ov100_0229d5d4((int) r0, (int) r1));
    } else {
        return func_ov100_0229d60c((int) r0, (int) r1) != 0 ? 0xc4 : 0;
    }
}

int func_ov100_0229d3d8(int a, int b)
{
    if (func_ov100_0229d630(a, b) != 0 || func_ov100_0229d620(a, b) != 0) {
        int r = func_ov100_0229d5d4(a, b);
        return func_ov094_0229ab90(a + 0xcc, r);
    } else {
        if (func_ov100_0229d60c(a, b) != 0) {
            if (b == 0x1e) {
                return 0x58;
            } else {
                return 0x68;
            }
        } else {
            return 0;
        }
    }
}

int func_ov100_0229d208(void *a, void *b)
{
    volatile u16 id;
    int v;

    if (func_ov100_0229d158((int) a, (int) b) != 0) {
        return 0;
    }
    if (func_ov100_0229d0dc(a, (int) b) != 0) {
        return 1;
    }
    v = func_ov100_0229d118((unsigned char *) a, (int) b);
    if (func_ov094_02299a54(v) != 0) {
        return 1;
    }
    id = (u16) v;
    switch (func_0206fca4()) {
        case 0x1e: {
            unsigned int ok = 0;
            u16 hi = id;
            u16 lo = id;
            if (lo >= 0x1492 && hi <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                return 1;
            }
            if ((hi >= 0x11a8 && hi <= 0x12a7) || (hi >= 0x13c8 && hi <= 0x1407) || (hi >= 0x13a8 && hi <= 0x13c7) ||
                (hi >= 0x1408 && hi <= 0x1428) || (hi >= 0x1431 && hi <= 0x1470) || (hi >= 0x1471 && hi <= 0x1491) ||
                (hi >= 0x1380 && hi <= 0x139f)) {
                return 0;
            }
            return 1;
        }
        case 0x1d: {
            unsigned int ok = 0;
            u16 hi = id;
            u16 lo = id;
            if (lo >= 0x1492 && hi <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                return 1;
            }
        }
            if (func_0209ded0() == 0) {
                unsigned int ok = 0;
                u16 hi = id;
                u16 lo = id;
                if (lo >= 0x1531 && hi <= 0x153a) {
                    ok = 1;
                }
                if (ok > 0) {
                    return 1;
                }
            }
            return 0;
        case 0x1f:
            return 1;
        case 0x20:
            if (func_ov094_02299b04(v) != 0) {
                unsigned int ok = 0;
                u16 hi = id;
                u16 lo = id;
                if (lo >= 0x1531 && hi <= 0x153a) {
                    ok = 1;
                }
                if (ok || (hi >= 0x153b && hi <= 0x1541) || (hi >= 0x154a && hi <= 0x1553)) {
                    return 0;
                }
                return 1;
            }
            return 0;
    }
    return 0;
}

void func_ov100_0229d1d0(UnkStruct_0229d1d0 *self)
{
    unsigned char i;
    i = 0;
    do {
        if (func_ov100_0229d208(self, (void *) i)) {
            func_ov094_0229a888(&self->unk_CC, func_ov100_0229d5d4((int) self, i));
        }
    } while (++i <= 14);
}

int func_ov100_0229d194(char *a, int b)
{
    if (func_ov100_0229d630((int) a, b) || func_ov100_0229d620((int) a, b)) {
        int r = func_ov100_0229d5d4((int) a, b);
        return func_ov094_0229a8bc(a + 0xcc, r);
    } else {
        return 0;
    }
}

int func_ov100_0229d158(int p1, int p2)
{
    if (func_ov100_0229d630(p1, p2) != 0 || func_ov100_0229d620(p1, p2) != 0) {
        int r = func_ov100_0229d5d4(p1, p2);
        return func_ov094_0229a69c((void *) (p1 + 0xcc), r);
    } else {
        return 1;
    }
}

int func_ov100_0229d118(unsigned char *p0, int p1)
{
    if (func_ov100_0229d630((int) p0, p1) != 0 || func_ov100_0229d620((int) p0, p1) != 0) {
        int t;
        t = func_ov100_0229d5d4((int) p0, p1);
        return func_ov094_0229aaac(p0 + 0xcc, t);
    } else {
        return 0x0000fff1;
    }
}

int func_ov100_0229d0dc(void *p0, int p1)
{
    if (func_ov100_0229d630((int) p0, p1) || func_ov100_0229d620((int) p0, p1)) {
        return func_ov094_0229aa84((char *) p0 + 0xcc, func_ov100_0229d5d4((int) p0, p1));
    }
    return 0xf1;
}

void func_ov100_0229d0c0(void *self)
{
    func_ov094_0229ab5c((char *) self + 0xcc);
    func_ov094_0229b98c((char *) self + 0xb2c);
}

void func_ov100_0229d068(void *a, void *b)
{
    if (func_ov100_0229d630((int) a, (unsigned int) b) || func_ov100_0229d620((int) a, (unsigned int) b)) {
        int r = func_ov100_0229d5d4((int) a, (int) b);
        func_ov094_0229ab1c((char *) a + 0xcc, r);
        func_ov094_0229b98c((char *) a + 0xb2c);
    } else if (func_ov100_0229d60c((int) a, (int) b)) {
        func_ov100_0229d0c0(a);
    }
}

void func_ov100_0229d04c(void *self)
{
    func_ov094_0229ab0c((char *) self + 0xcc);
    func_ov094_0229b944((char *) self + 0xb2c);
}

void func_ov100_0229d014(char *a, int b)
{
    if (func_ov100_0229d630((int) a, b) || func_ov100_0229d620((int) a, b)) {
        func_ov094_0229aafc(a + 0xcc, func_ov100_0229d5d4((int) a, b));
    }
}

int func_ov100_0229cfd0(void *self)
{
    int diff1;
    int diff2;

    diff1 = data_021f6c60 - data_021f6c58;
    if (diff1 < 0) {
        diff1 = -diff1;
    }
    if (diff1 > 8) {
        return 1;
    }

    diff2 = data_021f6c5c - data_021f6c54;
    if (diff2 < 0) {
        diff2 = -diff2;
    }
    if (diff2 > 8) {
        return 1;
    }

    return 0;
}

void func_ov100_0229cf30(unsigned char *self)
{
    int r6, r4;

    r6 = func_ov100_0229d42c(self, (void *) (*(unsigned char *) (self + 0x291f))) - 0x6d;
    r4 = func_ov100_0229d3d8((int) self, (unsigned char) (*(unsigned char *) (self + 0x291f))) - 0x78;

    if (func_0206fe54() != 0) {
        r4 -= 8;
    }

    if (r4 < -92) {
        func_0208aa80(self + 0x218c);
        r4 = func_ov100_0229d3d8((int) self, (unsigned char) (*(unsigned char *) (self + 0x291f))) - 0x50;
    } else {
        func_0208aa78(self + 0x218c);
    }

    func_0208aa60(self + 0x218c, r6, r4);

    if (func_ov100_0229d630((int) self, (unsigned char) (*(unsigned char *) (self + 0x291f))) != 0 ||
        func_ov100_0229d620((int) self, (unsigned char) (*(unsigned char *) (self + 0x291f))) != 0) {
        int tmp = func_ov100_0229d5d4((int) self, (unsigned char) (*(unsigned char *) (self + 0x291f)));
        func_ov094_0229abb8(self + 0xcc, self + 0x218c, tmp);
    }
}

void func_ov100_0229cecc(Object *self)
{
    if (func_ov100_0229d630((int) self, (unsigned char) self->unk_2921) != 0 ||
        func_ov100_0229d620((int) self, (unsigned char) self->unk_2921) != 0) {
        if (func_ov100_0229d158((int) self, (unsigned char) self->unk_2921) != 0) {
            func_ov002_02207cf0((void *) &self->unk_218C);
        } else {
            self->unk_291F = self->unk_2921;
            func_ov002_02207cf8((void *) &self->unk_218C);
        }
    } else {
        func_ov002_02207cf0((void *) &self->unk_218C);
    }
}

void func_ov100_0229ce90(void *s)
{
    if (func_ov100_0229c2c0(s, 0x40) == 0) {
        unsigned char b;
        b = ((unsigned char *) s)[0x291d];
        if (b != 0 && b == 1) {
            func_ov094_0229a6bc((char *) s + 0xcc, *(int *) ((char *) s + 0x28d4), *(int *) ((char *) s + 0x28d8));
        }
    }
}

void func_ov100_0229ce58(unsigned int *r0)
{
    unsigned int r2;
    unsigned int r1;

    r2 = r0[0x28cc / 4];
    r1 = data_021f6c58;
    r2 += r1;
    r0[0x28d4 / 4] = r2;

    r2 = r0[0x28d0 / 4];
    r1 = data_021f6c54;
    r2 += r1;
    r0[0x28d8 / 4] = r2;
}

void func_ov100_0229ce24(struct big_struct *this)
{
    this->unk_28D4 = func_ov002_02209f3c(&this->sub) - 2;
    this->unk_28D8 = func_ov002_02209f14(&this->sub) - 4;
}

void func_ov100_0229cdf4(struct UnkStruct_0229cdf4 *this)
{
    this->unk_28D4 = func_ov002_02209d84(this->ptr_area);
    this->unk_28D8 = func_ov002_02209d7c(this->ptr_area);
}

void func_ov100_0229cd7c(UnkStruct_0229cd7c *p, int n)
{
    int result;

    if (func_ov100_0229d630((int) p, n) == 0 && func_ov100_0229d620((int) p, n) == 0) {
        return;
    }

    result = func_ov100_0229d5d4((int) p, n);
    p->unk_291D = 1;
    p->unk_2918 = (unsigned short) func_ov094_0229aaac((unsigned char *) (&p->sub), result);
    p->unk_291C = (unsigned char) func_ov094_0229aa84(&p->sub, result);
    func_ov094_0229aa58(&p->sub, result);
    func_ov094_0229a99c(&p->sub, p->unk_2918, p->unk_291C);
}

void func_ov100_0229cd4c(struct UnkStruct_0229cd4c *obj, int param)
{
    struct UnkStruct_0229cd4c *self = obj;
    if (self->unk_291D == 1) {
        func_ov100_0229d4a8((int) self, param, (unsigned short) self->unk_2918, (unsigned char) self->unk_291C);
    }
    self->unk_291D = 0;
}

void func_ov100_0229cd10(UnkStruct_0229cd10 *a, int b)
{
    if (a->unk_291D == 1) {
        unsigned short h = a->unk_2918;
        unsigned char c = a->unk_291C;
        func_ov100_0229cd7c((UnkStruct_0229cd7c *) a, b);
        func_ov100_0229d4a8((int) a, b, (unsigned short) h, (unsigned char) c);
    }
}

void func_ov100_0229ccb8(unsigned char *p)
{
    int v4;
    int v2;
    unsigned char b;

    v4 = func_ov100_0229cc70((UnkStruct_0229cc70 *) p);
    v2 = func_ov100_0229cc60((void *) p);
    func_ov002_0220a0b4(p + 0x2274, v4, v2);
    b = *(unsigned char *) (p + 0x2921);
    if (func_ov100_0229d60c((int) p, (unsigned char) b) != 0) {
        func_ov002_0220a374(p + 0x2274, 7);
    } else {
        func_ov002_0220a374(p + 0x2274, 1);
    }
    func_ov100_0229ca7c(p);
}

int func_ov100_0229cc70(UnkStruct_0229cc70 *p)
{
    int r4;
    r4 = func_ov100_0229d42c(p, (void *) p->unk_2921);
    if (func_ov100_0229c2c0(p, 0x20) != 0) {
        r4 += 0x100;
    } else {
        if (func_ov100_0229c2c0(p, 0x10) != 0) {
            r4 -= 0x100;
        }
    }
    r4 += 8;
    return r4;
}

int func_ov100_0229cc60(void *p)
{
    return func_ov100_0229d3d8((int) p, (unsigned char) (((unsigned char *) p)[0x2921]));
}
