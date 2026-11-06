/* my_designs_use_3: 12 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229ac00 @ 0x0229ac00, 0x140 bytes, Thumb
 * func_ov121_0229abc8 @ 0x0229abc8, 0x38 bytes, Thumb
 * func_ov121_0229abac @ 0x0229abac, 0x1c bytes, Thumb
 * func_ov121_0229ab8c @ 0x0229ab8c, 0x20 bytes, Thumb
 * func_ov121_0229ab80 @ 0x0229ab80, 0xc bytes, Thumb
 * func_ov121_0229aab4 @ 0x0229aab4, 0xcc bytes, Thumb
 * func_ov121_0229a9f8 @ 0x0229a9f8, 0xbc bytes, Thumb
 * func_ov121_0229a940 @ 0x0229a940, 0xb8 bytes, Thumb
 * func_ov121_0229a7c8 @ 0x0229a7c8, 0x178 bytes, Thumb
 * func_ov121_0229a6b4 @ 0x0229a6b4, 0x114 bytes, Thumb
 * func_ov121_0229a63c @ 0x0229a63c, 0x78 bytes, Thumb
 * func_ov121_0229a5c8 @ 0x0229a5c8, 0x72 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xac];
    unsigned char unk_AC;
    unsigned char pad_AD;
    unsigned char unk_AE;
    unsigned char unk_AF;
} UnkStruct_0229ac00;

typedef struct UnkStruct_0229aab4 {
    u8 pad_00[0xae];
    u8 unk_AE;
} UnkStruct_0229aab4;

// Two switches: a 6-entry table over 9..0xE, then 0/1/2 on the result.

typedef struct UnkStruct_0229a6b4 {
    char pad_00[0xae];
    u8 unk_AE;
    u8 unk_AF;
} UnkStruct_0229a6b4;

typedef struct UnkStruct_0229a63c UnkStruct_0229a63c;

struct UnkStruct_0229a63c {
    u8 pad_00[0x98];
    int unk_98;
    u8 pad_9C[4];
    u16 unk_A0;
    u8 pad_A2[12];
    u8 unk_AE;
};

typedef struct UnkStruct_0229a63c_2 {
    u8 p[0x64];
    void *unk_64;
} UnkStruct_0229a63c_2;

typedef struct {
    char pad_00[0xb2];
    unsigned char unk_B2;
} UnkStruct_0229a5c8;

extern void func_0200467c(int);
extern int func_ov121_02299a70(void);
extern void func_ov121_0229a568(UnkStruct_0229ac00 *);
extern int func_020984e8(void);
extern int func_020996b8(int a);
extern int func_02072ba4(int a);
extern void func_02072b74(int a, int i, int j);
extern int func_02072b64(int, int);
extern char data_ov121_0229c258[][11];
extern void MI_CpuCopy8(char *dst, int off, int size);
extern int func_02099fe8(void);
extern u16 *func_020993a8(int a);
extern int func_ov121_0229a50c(void *receiver);
extern void func_0206f190(volatile u16 *out, void *a, void *b, void *c);
extern int func_0209a000(volatile u16 *p, int a);
extern void func_ov121_0229af7c(void *, int, int);
extern unsigned short *func_ov004_022320d8(void);
extern void func_02034adc(void *, void *, int, int);
extern unsigned char *func_ov121_0229afb8(void *);
extern void func_ov121_02299c88(void *, unsigned char);
extern unsigned short *func_ov004_02232080(void);
extern void func_02034b58(void *, void *, int, int);
extern int func_ov121_02299bd4(void *obj, u8 mode);
extern void func_ov121_0229a524(void *receiver);
extern unsigned short func_ov121_02299b20(void *obj, u8 mode, u16 w);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char value);
extern unsigned int func_020b2300(void);
extern int func_ov004_0223c660(void *);
extern int func_ov004_0223b3f8(void **, u8, int);
extern int func_ov004_0223b440(void **, u8, int);
extern int func_ov004_0223b488(void **, u8, int);
extern int func_ov004_0223b4d0(void **, u8, int);
extern UnkStruct_0229a63c_2 *data_020ccf94;
extern int func_0209985c(int);
extern u16 data_ov121_0229c2b8[];
extern int func_020435fc(void *a, int b);

void func_ov121_0229abc8(unsigned char *a, int i, int j);
void func_ov121_0229ab8c(int a, int b);
void func_ov121_0229aab4(UnkStruct_0229aab4 *self);
void func_ov121_0229a7c8(void *obj, u8 mode);
void func_ov121_0229a6b4(UnkStruct_0229a6b4 *o);
void func_ov121_0229a63c(UnkStruct_0229a63c *self);

int func_ov121_0229ac00(UnkStruct_0229ac00 *s)
{
    if (s->unk_AF <= 7) {
        func_0200467c(0xe);
        func_ov121_0229abc8((unsigned char *) s, s->unk_AF, s->unk_AE);
        return 0;
    }
    switch (s->unk_AF) {
        case 8:
            func_ov121_0229aab4((UnkStruct_0229aab4 *) s);
            return 1;
        case 10:
            if (func_ov121_02299a70()) {
                func_ov121_0229ab8c((int) s, 0);
            } else {
                func_ov121_0229af7c((void *) s, 0x17, 1);
                return 1;
            }
            func_ov121_0229a568(s);
            return 1;
        case 11:
            if (func_ov121_02299a70()) {
                func_ov121_0229ab8c((int) s, 1);
            } else {
                func_ov121_0229af7c((void *) s, 0x18, 1);
                return 1;
            }
            func_ov121_0229a568(s);
            return 1;
        case 13:
            switch (s->unk_AC) {
                case 0:
                case 2:
                    func_ov121_0229a7c8((void *) s, 0);
                    break;
                case 1:
                    func_ov121_0229ab8c((int) s, 3);
                    func_ov121_0229a568(s);
                    break;
            }
            return 1;
        case 12:
            switch (s->unk_AC) {
                case 0:
                case 2:
                    func_ov121_0229a7c8((void *) s, 1);
                    break;
                case 1:
                    func_ov121_0229ab8c((int) s, 4);
                    func_ov121_0229a568(s);
                    break;
            }
            return 1;
        case 14:
            switch (s->unk_AC) {
                case 0:
                    func_ov121_0229a7c8((void *) s, 2);
                    break;
                case 1:
                    func_ov121_0229a6b4((UnkStruct_0229a6b4 *) s);
                    return 1;
                default:
                    return 0;
            }
            return 1;
        case 9:
            func_ov121_0229a6b4((UnkStruct_0229a6b4 *) s);
            return 1;
        case 15:
            func_ov121_0229a63c((UnkStruct_0229a63c *) s);
            return 1;
    }
    return 0;
}

void func_ov121_0229abc8(unsigned char *a, int i, int j)
{
    unsigned char *p;
    unsigned char t;
    if (i != j) {
        func_02072b74(func_02072ba4(func_020996b8(func_020984e8())), i, j);
        p = a + 0x118c;
        t = p[i];
        p[i] = p[j];
        p[j] = t;
    }
}

int func_ov121_0229abac(int a, int b)
{
    return func_02072b64(func_02072ba4(func_020996b8(func_020984e8())), b);
}

void func_ov121_0229ab8c(int a, int b)
{
    MI_CpuCopy8(data_ov121_0229c258[b], a + 2320, 11);
}

unsigned char func_ov121_0229ab80(unsigned char *base, unsigned int offset)
{
    return (base + offset)[0x915];
}

void func_ov121_0229aab4(UnkStruct_0229aab4 *self)
{
    volatile u16 t[2];
    int ok;
    u16 lo;
    u16 hi;
    int a;
    int b;
    unsigned int n;
    u16 w;

    a = func_020984e8();
    b = func_02099fe8();
    t[0] = *func_020993a8(a);

    ok = 0;
    lo = t[0];
    hi = t[0];
    if (hi >= 0x11a8 && lo <= 0x12a7) {
        ok = 1;
    }

    if (ok != 0) {
        if (b == -1) {
            func_ov121_0229af7c((void *) self, 4, 1);
            return;
        }
    }

    func_ov121_0229a50c(self);
    n = (unsigned int) func_ov121_0229abac((int) self, (u8) self->unk_AE);
    if (n < 8) {
        w = (u16) (n + 0x12a8);
    } else {
        w = 0x12a8;
    }
    t[1] = w;

    func_0206f190(&t[1], (char *) self + 0x954, (char *) self + 0xd8, (char *) self + 0xb8);

    ok = 0;
    lo = t[0];
    hi = t[0];
    if (hi >= 0x11a8 && lo <= 0x12a7) {
        ok = 1;
    }

    if (ok != 0) {
        func_0209a000(t, 0);
    }

    func_ov121_0229afb8((void *) self);
    func_0200467c(0x6b);
}

void func_ov121_0229a9f8(void *obj, void *arg)
{
    volatile unsigned short h;
    int rc;
    unsigned short v0, v1;
    unsigned int hit;

    if (func_ov121_02299a70() == 0) {
        func_ov121_0229af7c(obj, 0x17, 1);
        return;
    }
    func_020984e8();
    rc = func_02099fe8();
    h = *func_ov004_022320d8();
    hit = 0;
    v0 = h;
    v1 = h;
    if (v1 >= 0x1188 && v0 <= 0x11a7) {
        hit = 1;
    }
    if (hit == 0 && rc == -1) {
        func_ov121_0229af7c(obj, 4, 1);
        return;
    }
    func_ov121_0229a50c(obj);
    func_02034adc((void *) func_ov121_0229abac((int) obj, (unsigned char) (*(unsigned char *) ((char *) obj + 0xae))), arg, 1,
                  1);
    hit = 0;
    v0 = h;
    v1 = h;
    if (v1 >= 0x1188 && v0 <= 0x11a7) {
        hit = 1;
    }
    if (hit == 0) {
        func_0209a000((volatile u16 *) (&h), 0);
    }
    func_ov121_0229afb8(obj);
    func_ov121_02299c88(obj, *(unsigned char *) ((char *) obj + 0xaf));
}

void func_ov121_0229a940(void *obj, void *arg)
{
    volatile unsigned short h;
    int rc;
    unsigned short v0, v1;
    unsigned int hit;

    if (func_ov121_02299a70() == 0) {
        func_ov121_0229af7c(obj, 0x18, 1);
        return;
    }
    rc = func_02099fe8();
    h = *func_ov004_02232080();
    hit = 0;
    v0 = h;
    v1 = h;
    if (v1 >= 0x1188 && v0 <= 0x11a7) {
        hit = 1;
    }
    if (hit == 0 && rc == -1) {
        func_ov121_0229af7c(obj, 4, 1);
        return;
    }
    func_ov121_0229a50c(obj);
    func_02034b58((void *) func_ov121_0229abac((int) obj, (unsigned char) (*(unsigned char *) ((char *) obj + 0xae))), arg, 1,
                  1);
    hit = 0;
    v0 = h;
    v1 = h;
    if (v1 >= 0x1188 && v0 <= 0x11a7) {
        hit = 1;
    }
    if (hit == 0) {
        func_0209a000((volatile u16 *) (&h), 0);
    }
    func_ov121_0229afb8(obj);
    func_ov121_02299c88(obj, *(unsigned char *) ((char *) obj + 0xaf));
}

void func_ov121_0229a7c8(void *obj, u8 mode)
{
    volatile u16 h;
    volatile u16 h2;
    u16 v0, v1;
    unsigned int hit;
    int v;
    unsigned int t;
    u16 w;

    *(u8 *) ((char *) obj + 0xb7) = mode;
    v = func_ov121_02299bd4(obj, *(u8 *) ((char *) obj + 0xb7));
    h = v;
    switch (*(u8 *) ((char *) obj + 0xb7)) {
        case 0:
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x12a8 && v0 <= 0x12af) {
                hit = 1;
            }
            if (hit != 0) {
                v = 0xfff1;
            }
            break;
        case 1:
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x1429 && v0 <= 0x1430) {
                hit = 1;
            }
            if (hit != 0) {
                v = 0xfff1;
            }
            break;
        case 2:
            hit = 0;
            v0 = h;
            v1 = h;
            if (v1 >= 0x13a0 && v0 <= 0x13a7) {
                hit = 1;
            }
            if (hit != 0) {
                v = 0xfff1;
            }
            break;
    }
    if (v != 0xfff1) {
        if (func_02099fe8() == -1) {
            func_ov121_0229af7c(obj, 4, 1);
            return;
        }
        h2 = v;
        func_0209a000(&h2, 0);
    }
    func_ov121_0229a524(obj);
    switch (*(u8 *) ((char *) obj + 0xb7)) {
        case 0:
            t = (unsigned int) func_ov121_0229abac((int) obj, (u8) (*(u8 *) ((char *) obj + 0xae)));
            if (t < 8) {
                w = (u16) (t + 0x12a8);
            } else {
                w = 0x12a8;
            }
            *(u16 *) ((char *) obj + 0xa0) = w;
            break;
        case 1:
            t = (unsigned int) func_ov121_0229abac((int) obj, (u8) (*(u8 *) ((char *) obj + 0xae)));
            if (t < 8) {
                w = (u16) (t + 0x1429);
            } else {
                w = 0x1429;
            }
            *(u16 *) ((char *) obj + 0xa0) = w;
            break;
        case 2:
            t = (unsigned int) func_ov121_0229abac((int) obj, (u8) (*(u8 *) ((char *) obj + 0xae)));
            if (t < 8) {
                w = (u16) (t + 0x13a0);
            } else {
                w = 0x13a0;
            }
            *(u16 *) ((char *) obj + 0xa0) = w;
            break;
    }
    func_ov121_02299b20(obj, *(u8 *) ((char *) obj + 0xb7), *(u16 *) ((char *) obj + 0xa0));
    func_ov002_02208098(obj, 0x11);
    func_ov121_02299c88(obj, (u8) (*(u8 *) ((char *) obj + 0xaf)));
}

void func_ov121_0229a6b4(UnkStruct_0229a6b4 *o)
{
    void *h;
    int r;

    if (func_020b2300() > 1) {
        func_ov121_0229af7c((void *) o, 9, 0);
        func_0200467c(0x73);
        return;
    }
    switch (o->unk_AF) {
        case 0xd:
            r = func_ov004_0223b4d0(&h, (u8) func_ov121_0229abac((int) o, (u8) o->unk_AE), 1);
            break;
        case 0xc:
            r = func_ov004_0223b440(&h, (u8) func_ov121_0229abac((int) o, (u8) o->unk_AE), 1);
            break;
        case 9:
            r = func_ov004_0223b3f8(&h, (u8) func_ov121_0229abac((int) o, (u8) o->unk_AE), 1);
            break;
        case 0xe:
            r = func_ov004_0223b488(&h, (u8) func_ov121_0229abac((int) o, (u8) o->unk_AE), 1);
            break;
        case 0xa:
        case 0xb:
        default:
            func_ov121_0229afb8((void *) o);
            return;
    }
    switch (r) {
        case 0:
        case 1:
            func_ov121_0229af7c((void *) o, 5, 0);
            func_0200467c(0x73);
            break;
        case 2:
            func_ov121_0229af7c((void *) o, 3, 0);
            func_0200467c(0x73);
            break;
        default:
            func_ov121_0229a50c(o);
            func_ov004_0223c660(h);
            func_ov121_0229afb8((void *) o);
            func_ov121_02299c88((void *) o, (u8) o->unk_AF);
            break;
    }
}

void func_ov121_0229a63c(UnkStruct_0229a63c *self)
{
    int k;
    k = func_0209985c((int) func_020984e8());
    self->unk_A0 = (u16) (data_ov121_0229c2b8[k] + func_ov121_0229abac((int) self, self->unk_AE));
    self->unk_98 = func_020435fc(data_020ccf94->unk_64, self->unk_A0);
    if (self->unk_98 == -1) {
        func_ov121_0229af7c((void *) self, 3, 0);
        func_0200467c(0x73);
    } else {
        func_ov002_02208098((void *) self, 0x14);
    }
}

void func_ov121_0229a5c8(UnkStruct_0229a5c8 *p)
{
    switch (p->unk_B2) {
        case 0:
            func_ov121_0229a9f8(p, 0);
            break;
        case 1:
            func_ov121_0229a9f8(p, (void *) 1);
            break;
        case 2:
            func_ov121_0229a940(p, 0);
            break;
        case 3:
            func_ov121_0229a940(p, (void *) 1);
            break;
        case 4:
            func_ov121_0229aab4((UnkStruct_0229aab4 *) p);
            break;
        case 5:
            func_ov121_0229a7c8(p, 0);
            break;
        case 6:
            func_ov121_0229a6b4((UnkStruct_0229a6b4 *) p);
            break;
        case 7:
            func_ov121_0229a7c8(p, 1);
            break;
        default:
            func_ov121_0229afb8(p);
            break;
    }
}
