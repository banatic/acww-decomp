/* public_box_4: 38 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229d628 @ 0x0229d628, 0x1e bytes, Thumb
 * func_ov110_0229d600 @ 0x0229d600, 0x28 bytes, Thumb
 * func_ov110_0229d5f0 @ 0x0229d5f0, 0x10 bytes, Thumb
 * func_ov110_0229d5e4 @ 0x0229d5e4, 0xc bytes, Thumb
 * func_ov110_0229d5d4 @ 0x0229d5d4, 0x10 bytes, Thumb
 * func_ov110_0229d5c8 @ 0x0229d5c8, 0xc bytes, Thumb
 * func_ov110_0229d590 @ 0x0229d590, 0x36 bytes, Thumb
 * func_ov110_0229d580 @ 0x0229d580, 0xe bytes, Thumb
 * func_ov110_0229d504 @ 0x0229d504, 0x7c bytes, Thumb
 * func_ov110_0229d4a8 @ 0x0229d4a8, 0x5c bytes, Thumb
 * func_ov110_0229d458 @ 0x0229d458, 0x50 bytes, Thumb
 * func_ov110_0229d43c @ 0x0229d43c, 0x1a bytes, Thumb
 * func_ov110_0229d428 @ 0x0229d428, 0x12 bytes, Thumb
 * func_ov110_0229d3d8 @ 0x0229d3d8, 0x50 bytes, Thumb
 * func_ov110_0229d388 @ 0x0229d388, 0x50 bytes, Thumb
 * func_ov110_0229d1b8 @ 0x0229d1b8, 0x1d0 bytes, Thumb
 * func_ov110_0229d17c @ 0x0229d17c, 0x3c bytes, Thumb
 * func_ov110_0229d13c @ 0x0229d13c, 0x40 bytes, Thumb
 * func_ov110_0229d0fc @ 0x0229d0fc, 0x40 bytes, Thumb
 * func_ov110_0229d0b8 @ 0x0229d0b8, 0x44 bytes, Thumb
 * func_ov110_0229d078 @ 0x0229d078, 0x40 bytes, Thumb
 * func_ov110_0229d054 @ 0x0229d054, 0x24 bytes, Thumb
 * func_ov110_0229cff8 @ 0x0229cff8, 0x5c bytes, Thumb
 * func_ov110_0229cfd4 @ 0x0229cfd4, 0x24 bytes, Thumb
 * func_ov110_0229cf98 @ 0x0229cf98, 0x3c bytes, Thumb
 * func_ov110_0229cf54 @ 0x0229cf54, 0x44 bytes, Thumb
 * func_ov110_0229cea8 @ 0x0229cea8, 0xac bytes, Thumb
 * func_ov110_0229ce44 @ 0x0229ce44, 0x64 bytes, Thumb
 * func_ov110_0229ce0c @ 0x0229ce0c, 0x38 bytes, Thumb
 * func_ov110_0229cde0 @ 0x0229cde0, 0x2c bytes, Thumb
 * func_ov110_0229cdb4 @ 0x0229cdb4, 0x2c bytes, Thumb
 * func_ov110_0229cd8c @ 0x0229cd8c, 0x28 bytes, Thumb
 * func_ov110_0229cd14 @ 0x0229cd14, 0x78 bytes, Thumb
 * func_ov110_0229cce8 @ 0x0229cce8, 0x2a bytes, Thumb
 * func_ov110_0229ccb0 @ 0x0229ccb0, 0x36 bytes, Thumb
 * func_ov110_0229cc58 @ 0x0229cc58, 0x58 bytes, Thumb
 * func_ov110_0229cc14 @ 0x0229cc14, 0x44 bytes, Thumb
 * func_ov110_0229cc04 @ 0x0229cc04, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00;
} UnkStruct_0229ce44_2;

typedef struct {
    unsigned char pad_00[0xf3];
    unsigned char unk_F3;
    unsigned char pad_F4;
    unsigned char unk_F5;
    unsigned char pad_F6[0x2102];
    UnkStruct_0229ce44_2 unk_21F8;
} UnkStruct_0229ce44;

typedef struct UnkStruct_0229cd14 UnkStruct_0229cd14;

struct UnkStruct_0229cd14 {
    unsigned char pad_00[0xEC];
    unsigned short unk_EC;
    unsigned char pad_EE[2];
    unsigned char unk_F0;
    unsigned char unk_F1;
};

struct UnkStruct_ec {
    char pad_00[0xec];
    unsigned short unk_EC;
    unsigned short unk_EE;
    unsigned char unk_F0;
    unsigned char unk_F1;
};

typedef struct UnkStruct_0229cc58 {
    int pad_00;
} UnkStruct_0229cc58;

typedef struct UnkStruct_0229cc58_2 {
    unsigned char pad_00[0xf5];
    unsigned char unk_F5;
    unsigned char pad_F6[0x22e0 - 0xf5 - 1];
    UnkStruct_0229cc58 obj;
} UnkStruct_0229cc58_2;

extern int func_02099fe8(void);
extern void func_020b9ccc(unsigned int);
extern int func_ov094_0229aee8(int, int unused1, int unused2);
extern int func_ov094_0229a69c(int, int);
extern int func_ov094_0229aeb8(int, int, int);
extern void func_ov094_0229aa14(void *p, int v, int c, int d);
extern void func_ov094_0229a9b4(void *p, int v);
extern int func_ov094_0229aba4(int p1, int p2);
extern int func_ov094_0229ab90(char *, int);
extern int func_ov094_02299a54(int id);
extern int func_ov094_02299b04(int id);
extern int func_0206fca4(void);
extern int func_0209ded0(void);
extern void func_ov094_0229a888(char *p, int v);
extern int func_ov094_0229a8bc(char *a, int b);
extern int func_ov094_0229aaac(char *addr, int value);
extern int func_ov094_0229aa84(void *, int);
extern void func_ov094_0229ab5c(void *);
extern void func_ov094_0229b98c(void *);
extern void func_ov094_0229ab1c(void *, int);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_0229aafc(void *addr, int val);
extern unsigned char data_021f6c60;
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c5c;
extern unsigned char data_021f6c54;
extern int func_0206fe54(void);
extern void func_0208aa80(char *addr);
extern void func_0208aa78(char *addr);
extern void func_0208aa60(char *addr, int a, int b);
extern void func_ov094_0229abb8(char *a, char *b, int c);
extern void func_ov002_02207cf0(void *);
extern void func_ov002_02207cf8(void *);
extern int func_ov110_0229c2c8(void *, int);
extern void func_ov094_0229a6bc(void *, void *, void *);
extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);
extern int func_ov002_02209d84(int *);
extern int func_ov002_02209d7c(int *);
extern void func_ov094_0229aa58(void *p, int v);
extern void func_ov094_0229a99c(void *p, int v1, int v2);
extern void func_ov110_0229ca28(void *self);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern void func_ov002_0220a374(void *obj, int v);

void func_ov110_0229d458(void *a, int b, int c, int d);
int func_ov110_0229d43c(int param1, int param2);
unsigned char func_ov110_0229d428(unsigned int unused, unsigned int r1);
int func_ov110_0229d0fc(int param1, int param2);
int func_ov110_0229d0b8(int a, int b);
int func_ov110_0229d078(const char *p, int q);
int func_ov110_0229cce8(struct UnkStruct_ec *this, int arg1);
int func_ov110_0229cc14(void *p);
int func_ov110_0229cc04(void *self);

unsigned char func_ov110_0229d628(void *receiver)
{
    int result = func_02099fe8();
    if (result == -1) {
        return 31;
    }
    return (unsigned char) result;
}

unsigned short func_ov110_0229d600(void *param0)
{
    int r3 = 0;
    unsigned short r1 = 0x0000fff1;
    while (r3 < 15) {
        unsigned short r2 = *(unsigned short *) ((char *) param0 + (r3 << 1) + 0xb0);
        if (r2 == r1) {
            r3 += 15;
            return (unsigned char) r3;
        }
        r3++;
    }
    return 0x1f;
}

void func_ov110_0229d5f0(unsigned int r0)
{
    func_020b9ccc(r0 + 0x100);
}

int func_ov110_0229d5e4(int a, unsigned int b)
{
    if (b > 14) {
        return 0;
    }
    return 1;
}

int func_ov110_0229d5d4(int unused, unsigned int b)
{
    if (b >= 15 && b <= 29) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov110_0229d5c8(int param1, int param2)
{
    if (param2 == 0x1e) {
        return 1;
    }
    return 0;
}

int func_ov110_0229d590(int a, int b)
{
    int result;
    if (func_ov110_0229d5e4(a, b) != 0) {
        result = (unsigned char) b;
    } else {
        if (func_ov110_0229d5d4(a, b) != 0) {
            result = func_ov110_0229d43c(a, b);
        } else {
            result = 0;
        }
    }
    return result;
}

int func_ov110_0229d580(int a, unsigned int b)
{
    if (b <= 14) {
        return (unsigned char) b;
    }
    return 31;
}

int func_ov110_0229d504(int r5, int r7, int r2, int r4)
{
    int r6;
    int sp_val = r2;
    r6 = func_ov094_0229aee8(r5 + 0x138, r7, r2);
    if (r6 != 0x23) {
        if (r4 != 0) {
            if (func_ov094_0229a69c(r5 + 0x138, r6) != 0) {
                return 0x1f;
            }
        }
        return func_ov110_0229d580(r5, r6);
    }
    r6 = func_ov094_0229aeb8(r5 + 0x138, r7, sp_val);
    if (r6 != 0x23) {
        if (r4 != 0) {
            if (func_ov094_0229a69c(r5 + 0x138, r6) != 0) {
                return 0x1f;
            }
        }
        return (int) func_ov110_0229d428(r5, r6);
    }
    return 0x1f;
}

int func_ov110_0229d4a8(void *p0, int p1)
{
    int v;

    if (func_ov110_0229d5e4((int) p0, p1) == 0 && func_ov110_0229d5d4((int) p0, p1) == 0) {
        goto ret0;
    }

    v = func_ov110_0229d0b8((int) p0, p1);
    if (v != 0xfff1) {
        func_ov110_0229d458(p0, *(unsigned char *) ((char *) p0 + 0xf4), v, func_ov110_0229d078((const char *) p0, p1));
    }
    func_ov110_0229cce8((struct UnkStruct_ec *) p0, p1);
    return 1;

ret0:
    return 0;
}

void func_ov110_0229d458(void *a, int b, int c, int d)
{
    if (func_ov110_0229d5e4((int) a, b) != 0 || func_ov110_0229d5d4((int) a, b) != 0) {
        int v;
        v = func_ov110_0229d590((int) a, b);
        func_ov094_0229aa14((char *) a + 0x138, v, c, d);
        func_ov094_0229a9b4((char *) a + 0x138, v);
    }
}

int func_ov110_0229d43c(int param1, int param2)
{
    int result;
    if (func_ov110_0229d5d4(param1, param2) != 0) {
        result = (unsigned char) param2;
    } else {
        result = 0xf;
    }
    return result;
}

unsigned char func_ov110_0229d428(unsigned int unused, unsigned int r1)
{
    if (r1 >= 0xf && r1 <= 0x1d) {
        return (unsigned char) r1;
    }
    return 0x1f;
}

int func_ov110_0229d3d8(int p1, int p2)
{
    if (func_ov110_0229d5e4(p1, p2) != 0 || func_ov110_0229d5d4(p1, p2) != 0) {
        return func_ov094_0229aba4(p1 + 0x138, func_ov110_0229d590(p1, p2));
    } else if (func_ov110_0229d5c8(p1, p2) != 0) {
        return 0xc4;
    } else {
        return 0;
    }
}

int func_ov110_0229d388(char *a, int b)
{
    if (func_ov110_0229d5e4((int) a, b) || func_ov110_0229d5d4((int) a, b)) {
        return func_ov094_0229ab90(a + 0x138, func_ov110_0229d590((int) a, b));
    } else {
        if (func_ov110_0229d5c8((int) a, b) != 0) {
            return 104;
        } else {
            return 0;
        }
    }
}

int func_ov110_0229d1b8(void *a, void *b)
{
    volatile u16 id;
    int v;

    if (func_ov110_0229d0fc((int) a, (int) b) != 0) {
        return 0;
    }
    if (func_ov110_0229d078((const char *) a, (int) b) != 0) {
        return 1;
    }
    v = func_ov110_0229d0b8((int) a, (int) b);
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

void func_ov110_0229d17c(char *p)
{
    unsigned char i = 0;
    char *q = p + 0x138;
    do {
        if (func_ov110_0229d1b8((void *) p, (void *) i)) {
            func_ov094_0229a888(q, func_ov110_0229d590((int) p, i));
        }
        i++;
    } while (i <= 14);
}

int func_ov110_0229d13c(char *a, void *b)
{
    if (func_ov110_0229d5e4((int) a, (unsigned int) b) != 0 || func_ov110_0229d5d4((int) a, (unsigned int) b) != 0) {
        return func_ov094_0229a8bc(a + 0x138, func_ov110_0229d590((int) a, (int) b));
    }
    return 0;
}

int func_ov110_0229d0fc(int param1, int param2)
{
    if (func_ov110_0229d5e4(param1, param2) || func_ov110_0229d5d4(param1, param2)) {
        return func_ov094_0229a69c(param1 + 0x138, func_ov110_0229d590(param1, param2));
    } else {
        return 1;
    }
}

int func_ov110_0229d0b8(int a, int b)
{
    if (func_ov110_0229d5e4(a, b) != 0 || func_ov110_0229d5d4(a, b) != 0) {
        return func_ov094_0229aaac((char *) a + 0x138, func_ov110_0229d590(a, b));
    }
    return 0xfff1;
}

int func_ov110_0229d078(const char *p, int q)
{
    int v;

    if (func_ov110_0229d5e4((int) p, q) == 0 && func_ov110_0229d5d4((int) p, q) == 0) {
        goto return_0xf1;
    }
    v = func_ov110_0229d590((int) p, q);
    return func_ov094_0229aa84((char *) p + 0x138, v);

return_0xf1:
    return 0xF1;
}

void func_ov110_0229d054(void *self)
{
    func_ov094_0229ab5c((char *) self + 0x138);
    func_ov094_0229b98c((char *) self + 0xb98);
}

void func_ov110_0229cff8(void *self, void *param2)
{
    if (func_ov110_0229d5e4((int) self, (unsigned int) param2) != 0 ||
        func_ov110_0229d5d4((int) self, (unsigned int) param2) != 0) {
        int r = func_ov110_0229d590((int) self, (int) param2);
        func_ov094_0229ab1c((char *) self + 0x138, r);
        func_ov094_0229b98c((char *) self + 0xb98);
    } else {
        if (func_ov110_0229d5c8((int) self, (int) param2) != 0) {
            func_ov110_0229d054(self);
        }
    }
}

void func_ov110_0229cfd4(void *self)
{
    func_ov094_0229ab0c((char *) self + 0x138);
    func_ov094_0229b944((char *) self + 0xb98);
}

void func_ov110_0229cf98(int a, int b)
{
    if (func_ov110_0229d5e4(a, b) != 0 || func_ov110_0229d5d4(a, b) != 0) {
        func_ov094_0229aafc((char *) a + 0x138, func_ov110_0229d590(a, b));
    }
}

int func_ov110_0229cf54(void *self)
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

void func_ov110_0229cea8(char *self)
{
    int v6, v4, t;

    v6 = func_ov110_0229d3d8((int) self, (unsigned char) (((unsigned char *) self)[0xf3])) - 0x6d;

    t = func_ov110_0229d388(self, (unsigned char) (((unsigned char *) self)[0xf3]));
    v4 = t - 0x78;
    if (func_0206fe54() != 0) {
        v4 -= 8;
    }

    if (v4 < -92) {
        func_0208aa80(self + 0x21f8);
        v4 = func_ov110_0229d388(self, (unsigned char) (((unsigned char *) self)[0xf3])) - 0x50;
    } else {
        func_0208aa78(self + 0x21f8);
    }

    func_0208aa60(self + 0x21f8, v6, v4);

    if (func_ov110_0229d5e4((int) self, (unsigned char) (((unsigned char *) self)[0xf3])) != 0 ||
        func_ov110_0229d5d4((int) self, (unsigned char) (((unsigned char *) self)[0xf3])) != 0) {
        t = func_ov110_0229d590((int) self, (unsigned char) (((unsigned char *) self)[0xf3]));
        func_ov094_0229abb8(self + 0x138, self + 0x21f8, t);
    }
}

void func_ov110_0229ce44(UnkStruct_0229ce44 *s)
{
    if (func_ov110_0229d5e4((int) s, (unsigned char) s->unk_F5) != 0 ||
        func_ov110_0229d5d4((int) s, (unsigned char) s->unk_F5) != 0) {
        if (func_ov110_0229d0fc((int) s, (unsigned char) s->unk_F5) != 0) {
            func_ov002_02207cf0(&s->unk_21F8);
        } else {
            s->unk_F3 = s->unk_F5;
            func_ov002_02207cf8(&s->unk_21F8);
        }
    } else {
        func_ov002_02207cf0(&s->unk_21F8);
    }
}

void func_ov110_0229ce0c(unsigned char *self)
{
    unsigned char b;

    if (func_ov110_0229c2c8(self, 0x40) != 0) {
        return;
    }

    b = self[0xf1];
    if (b == 0) {
        return;
    }
    if (b != 1) {
        return;
    }

    func_ov094_0229a6bc((void *) (self + 0x138), *(void **) (self + 0xa8), *(void **) (self + 0xac));
}

void func_ov110_0229cde0(unsigned char *param0)
{
    unsigned int val;
    unsigned int val2;

    val2 = *(unsigned int *) (param0 + 0xa0) + data_021f6c58;
    *(unsigned int *) (param0 + 0xa8) = val2;
    val = *(unsigned int *) (param0 + 0xa4) + data_021f6c54;
    *(unsigned int *) (param0 + 0xac) = val;
}

void func_ov110_0229cdb4(void *p)
{
    char *base = (char *) p;
    *(int *) (base + 0xa8) = func_ov002_02209f3c(base + 0x22e0) - 2;
    *(int *) (base + 0xac) = func_ov002_02209f14((int *) base + 0x8b8) - 4;
}

void func_ov110_0229cd8c(int *r0)
{
    int *r4 = r0;
    int *r1 = r4 + 0x22c8 / 4;
    int r0_1 = func_ov002_02209d84(r1);
    r4[0x2a] = r0_1;
    r1 = r4 + 0x22c8 / 4;
    r0_1 = func_ov002_02209d7c(r1);
    r4[0x2b] = r0_1;
}

void func_ov110_0229cd14(UnkStruct_0229cd14 *a, void *b)
{
    if (func_ov110_0229d5e4((int) a, (unsigned int) b) || func_ov110_0229d5d4((int) a, (unsigned int) b)) {
        int ret = func_ov110_0229d590((int) a, (int) b);
        a->unk_F1 = 1;
        a->unk_EC = func_ov094_0229aaac((char *) ((char *) a + 0x138), ret);
        a->unk_F0 = func_ov094_0229aa84((char *) a + 0x138, ret);
        func_ov094_0229aa58((char *) a + 0x138, ret);
        func_ov094_0229a99c((char *) a + 0x138, a->unk_EC, a->unk_F0);
    }
}

int func_ov110_0229cce8(struct UnkStruct_ec *this, int arg1)
{
    if (this->unk_F1 == 1) {
        func_ov110_0229d458(this, arg1, (unsigned short) this->unk_EC, (unsigned char) this->unk_F0);
    }
    this->unk_F1 = 0;
    return 0;
}

void func_ov110_0229ccb0(void *self, int other)
{
    if (((unsigned char *) self)[0xf1] == 1) {
        unsigned short a = *(unsigned short *) ((unsigned char *) self + 0xec);
        unsigned char b = ((unsigned char *) self)[0xf0];
        func_ov110_0229cd14((UnkStruct_0229cd14 *) self, (void *) other);
        func_ov110_0229d458(self, other, (unsigned short) a, (unsigned char) b);
    }
}

void func_ov110_0229cc58(UnkStruct_0229cc58_2 *self)
{
    int a;
    int b;

    a = func_ov110_0229cc14(self);
    b = func_ov110_0229cc04(self);
    func_ov002_0220a0b4(&self->obj, a, b);

    if (func_ov110_0229d5c8((int) self, self->unk_F5) != 0) {
        func_ov002_0220a374(&self->obj, 7);
    } else {
        func_ov002_0220a374(&self->obj, 1);
    }

    func_ov110_0229ca28(self);
}

int func_ov110_0229cc14(void *p)
{
    int v;

    v = func_ov110_0229d3d8((int) p, (unsigned char) (((unsigned char *) p)[0xf5]));
    if (func_ov110_0229c2c8(p, 0x20)) {
        v += 0x100;
    } else if (func_ov110_0229c2c8(p, 0x10)) {
        v -= 0x100;
    }
    v += 8;
    return v;
}

int func_ov110_0229cc04(void *self)
{
    return func_ov110_0229d388((char *) self, (unsigned char) (((unsigned char *) self)[0xf5]));
}
