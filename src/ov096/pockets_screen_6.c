/* pockets_screen_6: 17 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229e4a4 @ 0x0229e4a4, 0x54 bytes, Thumb
 * func_ov096_0229e3b0 @ 0x0229e3b0, 0xf4 bytes, Thumb
 * func_ov096_0229e2fc @ 0x0229e2fc, 0xb4 bytes, Thumb
 * func_ov096_0229e2c8 @ 0x0229e2c8, 0x32 bytes, Thumb
 * func_ov096_0229e29c @ 0x0229e29c, 0x2c bytes, Thumb
 * func_ov096_0229e258 @ 0x0229e258, 0x44 bytes, Thumb
 * func_ov096_0229e1ec @ 0x0229e1ec, 0x6c bytes, Thumb
 * func_ov096_0229e170 @ 0x0229e170, 0x7c bytes, Thumb
 * func_ov096_0229e158 @ 0x0229e158, 0x18 bytes, Thumb
 * func_ov096_0229e128 @ 0x0229e128, 0x30 bytes, Thumb
 * func_ov096_0229e0f8 @ 0x0229e0f8, 0x30 bytes, Thumb
 * func_ov096_0229e0a8 @ 0x0229e0a8, 0x50 bytes, Thumb
 * func_ov096_0229defc @ 0x0229defc, 0x1ac bytes, Thumb
 * func_ov096_0229dea4 @ 0x0229dea4, 0x58 bytes, Thumb
 * func_ov096_0229de50 @ 0x0229de50, 0x54 bytes, Thumb
 * func_ov096_0229de0c @ 0x0229de0c, 0x44 bytes, Thumb
 * func_ov096_0229ddfc @ 0x0229ddfc, 0x10 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229e29c {
    unsigned char pad_00[0xc0];
    unsigned char flag;
};

typedef struct UnkStruct_0229e170 {
    u8 pad_00[0xac];
    volatile u16 unk_AC;
    u8 unk_AE[2];
    u8 unk_B0;
    u8 unk_B1;
    u8 unk_B2[2];
    u8 unk_B4;
} UnkStruct_0229e170;

typedef struct UnkStruct_0229dea4 {
    int pad_00;
} UnkStruct_0229dea4;

typedef struct UnkStruct_0229dea4_2 {
    unsigned char pad_00[0xb5];
    unsigned char unk_B5;
    unsigned char pad_B6[0x2500 - 0xb5 - 1];
    UnkStruct_0229dea4 obj;
} UnkStruct_0229dea4_2;

extern void *func_020984e8(void);
extern unsigned short *func_02099710(void *);
extern unsigned short *func_020996e0(void *);
extern unsigned short *func_020996f8(void *);
extern unsigned short *func_02099728(void *);
extern void func_02099704(int, unsigned short *);
extern void func_020996d4(int, unsigned short *);
extern void func_020996ec(int, unsigned short *);
extern int func_02095b9c(u16 *p);
extern int func_02095b90(u16 *p);
extern int func_02095b84(u16 *p);
extern int func_02095b1c(u16 *p);
extern int func_02095aec(u16 *p);
extern int func_02095b64(void);
extern int func_0203ac5c(void);
extern void func_0200467c(int a);
extern int func_02095f4c(void);
extern int func_02096150(void);
extern int func_02095f58(void);
extern void func_ov096_0229fb9c(struct UnkStruct_0229e29c *);
extern void func_ov096_0229e82c(struct UnkStruct_0229e29c *, int);
extern void func_ov096_0229f874(struct UnkStruct_0229e29c *, int, int, int);
extern int func_0204c878(volatile u16 *p);
extern void func_0206f848(int a);
extern void func_ov096_0229e6a0(void *);
extern void func_ov094_0229a99c(void *, unsigned short, unsigned char);
extern unsigned char *func_ov096_0229f90c(void *, unsigned char, int);
extern void *func_02099734(void *);
extern int func_02098cf8(void *, int);
extern void func_02098aa0(int arg, void *arg1, int arg2);
extern void func_ov094_02299cd0(char *arg, int arg2);
extern int func_0204c120(unsigned int, int, unsigned int *);
extern int func_ov096_0229f810(void *self, int flag);
extern void func_ov096_0229dc28(void *self);
extern void func_ov002_0220a0b4(void *obj, int a, int b);
extern void func_ov002_0220a374(void *obj, int v);
extern int func_ov002_02208ad4(void *p);
extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern int func_ov096_0229f290(void *p, unsigned char b);
extern int func_ov096_0229c2fc(void *p, int n);
extern int func_ov096_0229f200(void *p, unsigned char c);

int func_ov096_0229e158(void *receiver);
int func_ov096_0229e0a8(void *a0, unsigned short a1);
int func_ov096_0229de0c(void *p);
int func_ov096_0229ddfc(unsigned char *p);

int func_ov096_0229e4a4(int a, int b)
{
    void *p = func_020984e8();
    switch (b) {
        case 2:
            return *func_02099710(p);
        case 3:
            return *func_020996e0(p);
        case 4:
            return *func_020996f8(p);
        case 5:
            return *func_02099728(p);
        default:
            return 0xFFF1;
    }
}

int func_ov096_0229e3b0(int a0, int a1, int a2)
{
    int h;
    volatile unsigned short v;
    int r;

    r = func_ov096_0229e4a4(a0, a1);
    h = (int) func_020984e8();
    v = (unsigned short) a2;
    switch (a1) {
        case 2:
            func_02099704(h, (unsigned short *) &v);
            v = (unsigned short) r;
            {
                int ok = 0;
                unsigned short lo = v;
                unsigned short hi = v;
                if (hi >= 0x11a8 && lo <= 0x12a7) {
                    ok = 1;
                }
                if (ok == 0) {
                    r = 0xfff1;
                }
            }
            break;
        case 3:
            func_020996d4(h, (unsigned short *) &v);
            break;
        case 6:
            func_020996d4(h, (unsigned short *) &v);
            r = func_ov096_0229e4a4(a0, 4);
            v = 0xfff1;
            func_020996ec(h, (unsigned short *) &v);
            break;
        case 4:
            func_020996ec(h, (unsigned short *) &v);
            v = (unsigned short) r;
            {
                int ok = 0;
                unsigned short lo = v;
                unsigned short hi = v;
                if (hi >= 0x1429 && lo <= 0x1430) {
                    ok = 1;
                }
                if (ok != 0) {
                    r = 0xfff1;
                }
            }
            break;
        case 5:
            v = (unsigned short) r;
            {
                int ok = 0;
                unsigned short lo = v;
                unsigned short hi = v;
                if (hi >= 0x13a0 && lo <= 0x13a7) {
                    ok = 1;
                }
                if (ok != 0) {
                    r = 0xfff1;
                }
            }
            break;
        case 0:
        case 8:
        default:
            break;
    }
    return r;
}

int func_ov096_0229e2fc(void *unused, unsigned int p, u16 x)
{
    u16 t;

    t = x;

    switch (p) {
        case 2:
            if (func_02095b9c(&t) != 0) {
                return 1;
            }
            break;
        case 3:
            if (func_02095b90(&t) != 0) {
                return 1;
            }
            break;
        case 6:
            if (func_02095b90(&t) != 0) {
                t = 0xfff1;
                func_02095b84(&t);
                return 1;
            }
            break;
        case 4:
            if (func_02095b84(&t) != 0) {
                return 1;
            }
            break;
        case 5:
            if (func_02095b1c(&t) != 0) {
                return 1;
            }
            break;
        case 7:
            if (func_02095aec(&t) != 0) {
                if (func_0203ac5c() == 0) {
                    func_0200467c(0x40);
                }
                return 1;
            }
            break;
        case 8:
            if (func_02095b64() != 0) {
                return 1;
            }
            break;
    }
    return 0;
}

int func_ov096_0229e2c8(int a, int b)
{
    switch (b) {
        case 5:
            return func_02095f4c();
        case 7:
        case 8:
            return (func_02096150() == 0) ? 1 : 0;
        default:
            return func_02095f58();
    }
}

void func_ov096_0229e29c(struct UnkStruct_0229e29c *obj)
{
    func_ov096_0229fb9c(obj);
    func_ov096_0229e82c(obj, 1);
    if (obj->flag == 0) {
        func_ov096_0229f874(obj, 7, 0xff, 1);
    }
}

void func_ov096_0229e258(u8 *self)
{
    volatile u16 id;
    int value;

    id = *(u16 *) (self + 0xac);
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1492 && hi <= 0x14fd) {
            ok = 1;
        }
        if (ok > 0) {
            value = func_0204c878(&id);
            func_0206f848(value);
            return;
        }
    }
    func_0206f848(0);
    return;
}

int func_ov096_0229e1ec(void *self)
{
    unsigned short tmp;
    int result;

    tmp = *(unsigned short *) ((char *) self + 0xac);
    func_0204c878((volatile u16 *) (&tmp));
    result = func_ov096_0229e0a8(self, *(unsigned short *) ((char *) self + 0xac));
    if (result == 0xfff1) {
        func_ov096_0229e6a0(self);
        func_ov096_0229fb9c((struct UnkStruct_0229e29c *) self);
    } else {
        *(unsigned short *) ((char *) self + 0xac) = (unsigned short) result;
        func_ov094_0229a99c((char *) self + 0x358, *(unsigned short *) ((char *) self + 0xac),
                            *(unsigned char *) ((char *) self + 0xb0));
        func_ov096_0229f90c(self, *(unsigned char *) ((char *) self + 0xb4), 4);
    }
    return 1;
}

int func_ov096_0229e170(UnkStruct_0229e170 *self, int flag)
{
    volatile u16 id;

    if (self->unk_B1 != 2) {
        return 0;
    }
    if (self->unk_B0 != 0) {
        return 0;
    }
    id = self->unk_AC;
    {
        unsigned int ok = 0;
        u16 hi = id;
        u16 lo = id;
        if (lo >= 0x1492 && hi <= 0x14fd) {
            ok = 1;
        }
        if (ok > 0) {
            if (flag != 0) {
                int x = func_0204c878(&id);
                if ((unsigned int) (x + func_ov096_0229e158(self)) > 0x1869f) {
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}

int func_ov096_0229e158(void *receiver)
{
    void *p;
    p = func_020984e8();
    p = func_02099734(p);
    return func_02098cf8(p, 0);
}

void func_ov096_0229e128(void *arg0, void *arg1)
{
    func_02098aa0((int) func_02099734((void *) ((int) func_020984e8())), arg1, 0);
    func_ov094_02299cd0((char *) arg0 + 0xde0, 0);
}

void func_ov096_0229e0f8(void *a, unsigned short b)
{
    unsigned short value = b;
    int amount = func_0204c878((volatile u16 *) (&value));
    func_ov096_0229e158(a);
    func_ov096_0229e128(a, (void *) (func_ov096_0229e158(a) - amount));
}

int func_ov096_0229e0a8(void *a0, unsigned short a1)
{
    unsigned short local = a1;
    unsigned int total;
    unsigned int amount;
    unsigned int diff;
    unsigned int extra;
    int result;

    amount = (unsigned int) func_0204c878((volatile u16 *) (&local));
    total = amount + func_ov096_0229e158(a0);
    result = 0xfff1;
    if (total > 99999) {
        diff = total - 99999;
        result = func_0204c120(diff, 1, &extra);
        total = total - (diff + extra);
    }
    func_ov096_0229e128(a0, (void *) total);
    return result;
}

int func_ov096_0229defc(void *self, u16 *A, int mode, u16 *B, u8 force)
{
    volatile u16 t[3];
    int spare;
    // DECLS
    u16 b;
    int v2;
    int x;
    int v1;
    unsigned int ok1;
    int j;
    u16 s;
    u16 d;
    unsigned int ok2;
    unsigned int okA;
    int rem;
    u16 a;
    int cap;
    int n;
    int y;
    int p;
    u16 c;
    unsigned int okB;
    int m;
    // ENDDECLS

    if (mode == 0 && force == 0) {
        goto go;
    }
    return 1;
go:
    t[0] = *A;
    t[1] = *B;
    ok1 = 0;
    a = t[0];
    b = t[0];
    if (b >= 0x1531 && a <= 0x153a) {
        ok1 = 1;
    }
    if (ok1 == 0) {
        goto other;
    }
    ok2 = 0;
    c = t[1];
    d = t[1];
    if (d >= 0x1531 && c <= 0x153a) {
        ok2 = 1;
    }
    if (ok2 == 0) {
        goto other;
    }

    if (a >= 0x1531 && a <= 0x153a) {
        x = a - 0x1531;
    } else {
        x = -1;
    }
    n = x + 1;
    if (c >= 0x1531 && c <= 0x153a) {
        y = c - 0x1531;
    } else {
        y = -1;
    }
    y = y + 1;
    n = n + y;
    if (n > 10) {
        rem = n - 10;
        n = 10;
    } else {
        rem = 0;
    }
    j = n - 1;
    if ((unsigned int) j < 10) {
        s = (u16) (0x1531 + j);
    } else {
        s = 0x1531;
    }
    *A = s;
    if (rem > 0) {
        j = rem - 1;
        if ((unsigned int) j < 10) {
            s = (u16) (0x1531 + j);
        } else {
            s = 0x1531;
        }
        *B = s;
    } else {
        *B = 0xfff1;
    }
    return 0;

other:
    okA = (a >= 0x1492 && a <= 0x14fd) ? 1 : 0;
    if (okA == 0) {
        goto ret1;
    }
    okB = 0;
    c = t[1];
    d = t[1];
    if (d >= 0x1492 && c <= 0x14fd) {
        okB = 1;
    }
    if (okB != 0) {
        goto proceed;
    }
ret1:
    return 1;
proceed:
    v1 = func_0204c878(&t[0]);
    v2 = func_0204c878(&t[1]);
    t[2] = 0x14fd;
    cap = func_0204c878(&t[2]);
    m = (v1 < 1000) ? 1 : 0;
    p = (v2 < 1000) ? 1 : 0;
    if (m != p) {
        return 2;
    }
    if (v1 == cap || v2 == cap) {
        return 3;
    }
    if (v1 < 1000) {
        v1 = v1 + v2;
        if (v1 > 1000) {
            v2 = v1 - 1000;
            v1 = 1000;
        } else {
            v2 = 0;
        }
    } else {
        v1 = v1 + v2;
        if (v1 <= cap) {
            v2 = 0;
        } else {
            v2 = v1 - cap;
            v1 = cap;
        }
    }
    *A = (u16) func_0204c120(v1, 1, (unsigned int *) (&spare));
    if (v2 == 0) {
        *B = 0xfff1;
    } else {
        *B = (u16) func_0204c120(v2, 1, (unsigned int *) (&spare));
    }
    return 0;
}

void func_ov096_0229dea4(UnkStruct_0229dea4_2 *self)
{
    int a;
    int b;

    a = func_ov096_0229de0c(self);
    b = func_ov096_0229ddfc((unsigned char *) self);
    func_ov002_0220a0b4(&self->obj, a, b);

    if (func_ov096_0229f810(self, self->unk_B5) != 0) {
        func_ov002_0220a374(&self->obj, 0xd);
    } else {
        func_ov002_0220a374(&self->obj, 1);
    }

    func_ov096_0229dc28(self);
}

void func_ov096_0229de50(char *base)
{
    int result2;
    int result3;

    ((unsigned char *) (base + 0xbc))[0] = (unsigned char) (func_ov002_02208ad4(base + 0x2564) - 1);
    result2 = func_ov002_02208ae4(base + 0x2564);
    result3 = func_ov002_02208ad8(base + 0x2564, *(unsigned char *) (base + 0xbc));
    func_ov002_0220a0b4(base + 0x2500, result2, result3);
    func_ov002_0220a374(base + 0x2500, 7);
}

int func_ov096_0229de0c(void *p)
{
    int val = func_ov096_0229f290(p, ((unsigned char *) p)[0xb5]);
    if (func_ov096_0229c2fc(p, 0x20) != 0) {
        val += 0x100;
    } else if (func_ov096_0229c2fc(p, 0x10) != 0) {
        val -= 0x100;
    }
    val += 8;
    return val;
}

int func_ov096_0229ddfc(unsigned char *p)
{
    unsigned char *q = p;
    q += 0xb5;
    return func_ov096_0229f200(p, *q);
}
