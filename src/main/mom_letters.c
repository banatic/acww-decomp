/* mom_letters: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209751c @ 0x0209751c, 0xa6 bytes, Thumb
 * func_02097430 @ 0x02097430, 0xea bytes, Thumb
 * func_0209737c @ 0x0209737c, 0xb4 bytes, Thumb
 * func_02097300 @ 0x02097300, 0x7a bytes, Thumb
 * func_020972f0 @ 0x020972f0, 0x10 bytes, Thumb
 * func_020972e4 @ 0x020972e4, 0xc bytes, Thumb
 * func_020972b4 @ 0x020972b4, 0x30 bytes, Thumb
 * func_0209727c @ 0x0209727c, 0x38 bytes, Thumb
 * func_02097234 @ 0x02097234, 0x48 bytes, Thumb
 * func_02097204 @ 0x02097204, 0x2e bytes, Thumb
 * func_02097188 @ 0x02097188, 0x7a bytes, Thumb
 * func_020970cc @ 0x020970cc, 0xbc bytes, Thumb
 * func_020970a4 @ 0x020970a4, 0x28 bytes, Thumb
 * func_02096ee4 @ 0x02096ee4, 0x1c0 bytes, Thumb
 * func_02096ebc @ 0x02096ebc, 0x26 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0209737c;

struct UnkStruct_02097300 {
    int unk_00;
    int unk_04;
};

typedef struct {
    unsigned char pad_00[0x58];
    unsigned int unk_58;
} UnkStruct_02096ee4;

extern int func_020984e8(void);
extern int func_0209782c(void);
extern int func_02097ad0(int);
extern int func_02098a0c(int);
extern int func_02097d68(int, u32 *);
extern void func_02097cbc(int, unsigned char);
extern void func_02097d50(int, u32 *);
extern int func_020644cc(int);
extern void *func_020992e4(void *);
extern u32 func_02097cc8(void *);
extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern void func_0209e29c(void *, int);
extern int func_0209e3ac(const void *, const void *, int);
extern int func_0209de44(int a, int b, int c, int d);
extern unsigned char data_020e3030[];
extern unsigned char data_020e303c[];
extern int func_02097cd4(int, int);
extern void func_02097cf8(void *, char *);
extern void func_02097d18(int, int);
extern unsigned char data_021f43ec;
extern void func_02066694(void *);
extern void func_02066650(void *);
extern int func_02099870(int);
extern unsigned char func_0209767c(int, int);
extern void func_02066024(void *, void *, int, void *, void *, int);
extern unsigned short func_02065ed0(void *, int, int);
extern int func_02097a54(void *);
extern void func_02066688(void *);
extern int func_020979f0(void *, int);
extern unsigned char data_020e307c[];
extern unsigned char data_020e3088[];
extern unsigned char data_020e3098[];
extern void func_02063ccc(void *, int, int);
extern void func_020638d4(void *, void *, int, int, int, int, int);
extern void func_02063cc8(void *);
extern void func_02063414(void *, int, int, int, int, int, int, int, int, int);
extern UnkStruct_02096ee4 data_021f39a8;

int func_02097430(u32 *arg);
int func_0209737c(UnkStruct_0209737c *p);
int func_02097300(struct UnkStruct_02097300 *p);
int func_020972f0(int index);
unsigned char func_020972e4(unsigned int param);
void func_020972b4(int param);
int func_0209727c(int r0, int r1);
void func_02097204(char *a, int b);
int func_02097188(int a, int b, int c, int d);
int func_020970cc(int a, int b);
unsigned char *func_020970a4(int param);
int func_02096ee4(int k);
unsigned char func_02096ebc(int r0);

void func_0209751c(u32 *p, int n)
{
    int r6;
    int r4;

    r6 = func_020984e8();
    if (r6 == 0) {
        return;
    }
    if (n < 1) {
        return;
    }

    if (func_0209782c() == 0) {
        if (func_02097ad0(-1) == 1) {
            return;
        }
    }

    r4 = func_02098a0c(r6);
    func_020972b4((unsigned char) ((unsigned char) p[1]));
    if (func_02097d68(r4, p) != 0) {
        return;
    }

    if (func_02097430(p) != 0) {
        func_02097cbc(r4, (unsigned char) p[0]);
        func_02097d50(r4, p);
        return;
    } else {
        if (func_0209737c((UnkStruct_0209737c *) p) != 0) {
            func_02097d50(r4, p);
            return;
        } else {
            if (func_020644cc(0xa) < 2 && func_02097300((struct UnkStruct_02097300 *) p) != 0) {
                func_02097d50(r4, p);
                return;
            }
            func_02097d50(r4, p);
            return;
        }
    }
}

int func_02097430(u32 *arg)
{
    void *h1, *h2;
    u8 *p;
    u64 a, b, c;
    int flag;

    h1 = (void *) func_020984e8();
    h2 = (void *) func_02098a0c((int) h1);
    p = func_020992e4(h1);

    if (*(u16 *) p == 0) {
        return 0;
    }

    if (arg[0] == func_02097cc8(h2)) {
        return 0;
    }

    a = 0;
    a = 0;
    ((u8 *) &a)[5] = (u8) arg[0];
    ((u8 *) &a)[4] = p[1];
    ((u8 *) &a)[3] = p[0];

    b = 0;
    b = 0;
    ((u8 *) &b)[5] = (u8) arg[0];
    ((u8 *) &b)[4] = (u8) arg[1];
    ((u8 *) &b)[3] = (u8) arg[2];

    c = 0;
    MI_CpuCopy8(&a, &c, 8);
    func_0209e29c(&c, 7);

    flag = 0;

    if (((u8 *) &c)[5] != ((u8 *) &a)[5]) {
        ((u8 *) &c)[5] = ((u8 *) &a)[5];
        if (!(func_0209e3ac(&b, &c, 0x38) == 1 && func_0209e3ac(&b, &a, 0x38) == -1)) {
            flag = 1;
        }
    } else {
        if (!(func_0209e3ac(&b, &c, 0x38) == 1 || func_0209e3ac(&b, &a, 0x38) == -1)) {
            flag = 1;
        }
    }

    if (flag) {
        flag = func_02097188(0x20, 2, (u8) ((u8) arg[1]), 1);
    }

    return flag;
}

int func_0209737c(UnkStruct_0209737c *p)
{
    if (p->unk_04 == p->unk_08) {
        return func_02097188(2 * p->unk_08 - 2, 2, (unsigned char) p->unk_04, 1);
    }
    if (p->unk_04 == 4 && p->unk_08 == 1) {
        return func_02097188(0x1c, 2, (unsigned char) p->unk_04, 1);
    }
    if (p->unk_04 == 0xc && p->unk_08 == 0x18) {
        return func_02097188(0x1e, 2, (unsigned char) p->unk_04, 1);
    }
    if (p->unk_04 == 6) {
        if (p->unk_08 == func_0209de44((unsigned char) p->unk_00, (unsigned char) p->unk_04, 0, 3)) {
            return func_02097188(0x1a, 2, (unsigned char) p->unk_04, 1);
        }
    }
    if (p->unk_04 == 5) {
        if (p->unk_08 == func_0209de44((unsigned char) p->unk_00, (unsigned char) p->unk_04, 0, 2)) {
            return func_02097188(0x18, 2, (unsigned char) p->unk_04, 1);
        }
    }
    return 0;
}

int func_02097300(struct UnkStruct_02097300 *p)
{
    int a, b, c;
    int tmp, res;

    a = func_020972f0((unsigned char) p->unk_04);
    b = (int) func_020972e4((unsigned char) p->unk_04);
    c = func_0209727c(a, b);

    if (c == b) {
        return func_02097188(a, b, (unsigned char) p->unk_04, 0);
    } else {
        tmp = func_0209727c(0x22, 0x38) + c;
        res = func_020644cc(tmp);
        if (res < c) {
            return func_02097188(a, b, (unsigned char) p->unk_04, 0);
        } else {
            return func_02097188(0x22, 0x38, (unsigned char) p->unk_04, 1);
        }
    }
}

int func_020972f0(int index)
{
    return data_020e3030[index - 1] + 0x5a;
}

unsigned char func_020972e4(unsigned int param)
{
    return data_020e303c[param - 1];
}

void func_020972b4(int param)
{
    int i;
    for (i = 1; i <= 12; i++) {
        if (i == param) {
            continue;
        }
        func_02097204((char *) (func_020972f0((unsigned char) ((unsigned char) i))),
                      (int) func_020972e4((unsigned char) ((unsigned char) i)));
    }
}

int func_0209727c(int r0, int r1)
{
    int sp;
    int r5;
    int r7;
    int r6;
    int r4;
    int result;

    r5 = r0;
    r7 = r1;
    sp = func_02098a0c((int) func_020984e8());
    r6 = 0;
    r4 = 0;
    while (r4 < r7) {
        if (func_02097cd4(sp, r5) == 0) {
            r6++;
        }
        r5++;
        r4++;
    }
    result = r6;
    return result;
}

char *func_02097234(char *p1, int p2, int p3)
{
    int cnt;
    char *p;
    int i;
    void *x;

    x = (void *) func_02098a0c((int) func_020984e8());

    cnt = 0;
    p = p1;
    i = cnt;
    while (i < p2) {
        if (func_02097cd4((int) x, (int) p) == 0) {
            if (cnt == p3) {
                return p;
            }
            cnt++;
        }
        p++;
        i++;
    }
    return p1;
}

void func_02097204(char *a, int b)
{
    int i;
    void *p;
    p = (void *) func_02098a0c((int) func_020984e8());
    for (i = 0; i < b; i++) {
        func_02097cf8(p, a);
        a++;
    }
}

int func_02097188(int a, int b, int c, int d)
{
    int w0, v1, v2, v3, v4;
    int flag = d;

    w0 = func_02098a0c((int) func_020984e8());
    v1 = func_0209727c(a, b);

    if (v1 != 0) {
        // no change
    } else {
        if (flag == 0) {
            return 0;
        }
        v1 = b;
        func_02097204((char *) a, b);
        flag = 0;
    }

    v2 = func_020644cc(v1);
    v3 = (int) func_02097234((char *) a, b, v2);
    v4 = func_020970cc(v3, c);

    if (v4 != 0) {
        if (v1 == 1 && flag == 1) {
            func_02097204((char *) a, b);
        } else {
            func_02097d18(w0, v3);
        }
    }
    return v4;
}

int func_020970cc(int a, int b)
{
    unsigned char data[3];
    struct {
        unsigned int pad[64];
    } ctx;
    int x;
    int v;
    int r4;

    func_02066694(&ctx);
    func_02066650(&ctx);
    r4 = func_02099870((int) func_020984e8());

    data[0] = data_021f43ec;
    data[0] = func_02096ebc(a);
    data[1] = 1;
    if (a == 0x1a) {
        data[1] = 0x12;
    }
    data[2] = func_0209767c(3, b);

    x = (int) func_020970a4(a);
    func_02066024(&ctx, data, x, &data[1], &data[2], r4);

    v = func_02096ee4(a);
    if (v != 0xfff1) {
        func_02065ed0(&ctx, v, 1);
    }

    if (func_02097a54(&ctx) != 0) {
        func_02066688(&ctx);
        return 1;
    }
    if (func_020979f0(&ctx, 0) != 0) {
        func_02066688(&ctx);
        return 1;
    }
    func_02066688(&ctx);
    return 0;
}

unsigned char *func_020970a4(int param)
{
    if (param >= 0 && param < 0x22) {
        return data_020e307c;
    }
    if (param >= 0x22 && param < 0x5a) {
        return data_020e3088;
    }
    return data_020e3098;
}

static inline unsigned short pick(unsigned int i)
{
    if (i < 5) {
        return (unsigned short) (0x1518 + i);
    }
    return 0x1518;
}

int func_02096ee4(int k)
{
    unsigned short w[4];
    int a[2];
    int b[2];

    w[0] = 0xfff1;
    switch (k) {
        case 0x23:
        case 0x32:
        case 0x5f:
        case 0x73:
            func_02063ccc(a, 2, 0);
            func_020638d4(&w[1], a, 0, 0, 1, 1, 0);
            w[0] = w[1];
            func_02063cc8(a);
            return w[0];
        case 0x4a:
            func_02063414(&w[2], 0x1380, 0x20, 0, 0, 0, 1, 0xa, 0, 1);
            w[0] = w[2];
            return w[0];
        case 0x1e:
        case 0x1f:
            func_02063ccc(b, 0, 0);
            func_020638d4(&w[3], b, 0, 0, 1, 1, 0);
            w[0] = w[3];
            func_02063cc8(b);
            return w[0];
        case 0x25:
        case 0x37:
        case 0x38:
        case 0x51: {
            unsigned short target;
            unsigned short v;
            unsigned int i;
            int n;

            target = pick(data_021f39a8.unk_58);
            n = func_020644cc(4);
            for (i = 0; i < 5; i++) {
                v = pick(i);
                if (v != target) {
                    if (n > 0) {
                        n = n - 1;
                    } else {
                        return v;
                    }
                }
            }
            return 0x1518;
        }
        case 0x2e:
            return 0x149b;
        case 0:
        case 1:
            return 0x14a4;
        case 0x6e:
        case 0x6f:
            return 0x1542;
        case 0x72:
            return 0x1518;
        case 0x48:
            return 0x3648;
        case 0x47:
            return 0x3420;
    }
    return 0xfff1;
}

unsigned char func_02096ebc(int r0)
{
    if (r0 >= 0 && r0 < 0x22) {
        return (unsigned char) r0;
    }
    if (r0 >= 0x22 && r0 < 0x5a) {
        return (unsigned char) (r0 - 0x22);
    }
    return (unsigned char) (r0 - 0x5a);
}
