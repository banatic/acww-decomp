/* pockets_wallet_3: 28 functions, module ov094
 * mwccarm 1.2/base -O4,s
 * func_ov094_0229a2b0 @ 0x0229a2b0, 0x1e bytes, Thumb
 * func_ov094_0229a29c @ 0x0229a29c, 0x14 bytes, Thumb
 * func_ov094_0229a204 @ 0x0229a204, 0x98 bytes, Thumb
 * func_ov094_0229a1c0 @ 0x0229a1c0, 0x44 bytes, Thumb
 * func_ov094_0229a110 @ 0x0229a110, 0xb0 bytes, Thumb
 * func_ov094_0229a098 @ 0x0229a098, 0x78 bytes, Thumb
 * func_ov094_0229a084 @ 0x0229a084, 0x14 bytes, Thumb
 * func_ov094_0229a05c @ 0x0229a05c, 0x26 bytes, Thumb
 * func_ov094_0229a038 @ 0x0229a038, 0x22 bytes, Thumb
 * func_ov094_0229a018 @ 0x0229a018, 0x20 bytes, Thumb
 * func_ov094_02299ff8 @ 0x02299ff8, 0x20 bytes, Thumb
 * func_ov094_02299fb8 @ 0x02299fb8, 0x40 bytes, Thumb
 * func_ov094_02299f88 @ 0x02299f88, 0x30 bytes, Thumb
 * func_ov094_02299f64 @ 0x02299f64, 0x24 bytes, Thumb
 * func_ov094_02299f40 @ 0x02299f40, 0x24 bytes, Thumb
 * func_ov094_02299e1c @ 0x02299e1c, 0x124 bytes, Thumb
 * func_ov094_02299dcc @ 0x02299dcc, 0x50 bytes, Thumb
 * func_ov094_02299d8c @ 0x02299d8c, 0x40 bytes, Thumb
 * func_ov094_02299d88 @ 0x02299d88, 0x2 bytes, Thumb
 * func_ov094_02299d84 @ 0x02299d84, 0x2 bytes, Thumb
 * func_ov094_02299d7c @ 0x02299d7c, 0x8 bytes, Thumb
 * func_ov094_02299d40 @ 0x02299d40, 0x3c bytes, Thumb
 * func_ov094_02299d34 @ 0x02299d34, 0xc bytes, Thumb
 * func_ov094_02299cd0 @ 0x02299cd0, 0x64 bytes, Thumb
 * func_ov094_02299c74 @ 0x02299c74, 0x5c bytes, Thumb
 * func_ov094_02299c5c @ 0x02299c5c, 0x18 bytes, Thumb
 * func_ov094_02299c40 @ 0x02299c40, 0x1c bytes, Thumb
 * func_ov094_02299b74 @ 0x02299b74, 0xcc bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229a1c0 {
    char pad_00[14];
    unsigned char flag;
} UnkStruct_0229a1c0;

typedef struct {
    char data[0x38];
} Unit;

typedef struct {
    char pad_00[0x38];
    Unit units[3];
} Container;

typedef struct UnkStruct_02299d8c UnkStruct_02299d8c;

struct UnkStruct_02299d8c {
    unsigned char pad_00[0xe];
    unsigned char unk_0E;
    unsigned char pad_0F[0x70 - 0xf];
};

typedef struct {
    int unk_00;
    int unk_04;
    char pad_08[11];
    unsigned char unk_13;
} UnkStruct_02299cd0;

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char pad_08[0x0b];
    unsigned char unk_13;
    unsigned char pad_14[0x43a];
    unsigned short unk_44E[0x21];
} UnkStruct_02299b74;

extern unsigned char data_ov094_0229bedc[];
extern unsigned char data_ov094_0229bef8[];
extern unsigned char data_ov094_0229bf18[];
extern unsigned char data_ov094_0229bf38[];
extern unsigned char data_ov094_0229bf54[];
extern void *data_021fbe94;
extern int func_02002d14(const void *, void *, int, int, int, int);
extern int func_02064af4(const void *, void *, int);
extern int func_02002b40(void *, int, int, int);
extern int func_02002c6c(const void *, void *, int, int, int, int);
extern char data_ov094_0229bec0[];
extern int func_020984e8(void);
extern int func_02099870(int a);
extern void *func_020641c8(void *a);
extern int func_02095040(int a);
extern void func_02064210(int a, void *b);
extern void *func_020b496c(int a, void *b);
extern void func_02070adc(void *p, u8 b, int c, int d, int e, int f, int g);
extern int func_0207094c(void *p, int a);
extern void func_02070a04(void *p, int a, int b);
extern void *func_02094fd4(void *a);
extern void *func_02095074(int a, void *b);
extern void *func_020a8bb8(void *p, void *b);
extern void *func_02094fbc(void *a);
extern void *func_020641b0(void *a);
extern char data_ov094_0229be58[];
extern char data_ov094_0229be78[];
extern char data_ov094_0229be90[];
extern char data_ov094_0229bea8[];
extern void func_ov094_02299ad0(void *);
extern void func_02004644(int, int);
extern void func_020b9ccc(void *);
extern void func_02070b84(void *p);
extern int func_ov094_022999b0(void *a, int b);
extern void func_ov094_022999a0(void *a, int b);
extern int func_020b9bbc(void *a, void *b, unsigned char c, int d, int e);
extern void func_0206fdd4(int, int, int, int, int, int);
extern int func_020950c0(void *a);
extern u16 *func_02099728(void *a);
extern int func_02064328(void *dst, const void *src, int len);
extern void func_ov094_022999a8(void *self, int arg);
extern const char data_ov094_0229be20[];
extern const char data_ov094_0229be3c[];
extern int func_020b9c10(char *a, char *b, int c, int d, int e, int f);
extern void func_ov094_02299ac4(void *);
extern void func_ov094_02299acc(void *, unsigned char);
extern void func_02004658(int);
extern int func_02099734(int);
extern int func_02098cf8(int a, int b);
extern void func_0200467c(int);

void func_ov094_0229a204(void *param1, int param2);
void func_ov094_0229a1c0(UnkStruct_0229a1c0 *s);
void func_ov094_0229a110(void *self);
void func_ov094_0229a018(Container *c);
void func_ov094_02299ff8(void *p);
void func_ov094_02299fb8(void *p);
void func_ov094_02299e1c(void *self);
void func_ov094_02299dcc(void *self, const void *src, int flag);
void func_ov094_02299d8c(UnkStruct_02299d8c *p);
void func_ov094_02299d88(void *self);
void func_ov094_02299c74(void *arg, int idx);
int func_ov094_02299c5c(void);
void func_ov094_02299c40(void *arg);
void func_ov094_02299b74(UnkStruct_02299b74 *self);

void func_ov094_0229a2b0(void *r0, unsigned char r1)
{
    unsigned char *r4 = (unsigned char *) r0;
    r4[0xe] = r1;
    *(unsigned short *) (r4 + 8) = 0;
    func_ov094_02299c40(r4);
    r4[0xf] = 2;
    r4[0x10] = 2;
    r4[0x14] = 8;
}

void func_ov094_0229a29c(void *arg, int arg1)
{
    func_ov094_0229a204(arg, arg1);
    func_ov094_0229a1c0((UnkStruct_0229a1c0 *) arg);
}

void func_ov094_0229a204(void *param1, int param2)
{
    void *g_ptr;
    const unsigned char *data;

    g_ptr = data_021fbe94;
    func_02002d14(data_ov094_0229bedc, g_ptr, ((unsigned char *) param1)[0xe], 0, 1, 13);

    data = param2 ? data_ov094_0229bef8 : data_ov094_0229bf18;
    func_02064af4(data, (char *) param1 + 0x1b8, 0x800);

    func_02002b40((char *) param1 + 0x1b8, ((unsigned char *) param1)[0xe], 0x800, 0);

    func_02002c6c(data_ov094_0229bf38, g_ptr, ((unsigned char *) param1)[0xe], 0, 0x10, 0xff);
    func_02002c6c(data_ov094_0229bf54, g_ptr, ((unsigned char *) param1)[0xe], 0x100, 0x100, 0x1ff);
}

void func_ov094_0229a1c0(UnkStruct_0229a1c0 *s)
{
    func_02002c6c((const void *) data_ov094_0229bec0, (void *) ((*(int *) &data_021fbe94)), s->flag, 0x200, 0x200, 0x2ff);
    func_ov094_0229a110((void *) s);
    func_ov094_02299c40((void *) s);
    func_ov094_02299e1c((void *) s);
}

void func_ov094_0229a110(void *self)
{
    char local1[0x20];
    char local2[0x20];
    int v;

    v = func_02099870(func_020984e8());
    func_020641c8(local1);
    func_02064210(func_02095040(v), local1);
    func_020b496c(0, local1);
    func_02070adc((char *) self + 0xe0, ((u8 *) self)[0xe], 17, 10, 15, 12, 0);
    func_0207094c((char *) self + 0xe0, 102);
    func_02070a04((char *) self + 0xe0, 1, 0);
    func_02094fd4(local2);
    func_02095074(v, local2);
    func_02070adc((char *) self + 0x14c, ((u8 *) self)[0xe], 37, 8, 15, 12, 0);
    func_020a8bb8((char *) self + 0x14c, local2);
    func_02070a04((char *) self + 0x14c, 1, 0);
    func_02094fbc(local2);
    func_020641b0(local1);
}

int func_ov094_0229a098(void *receiver)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov094_0229be58, (void *) p, 8, 4, 4, 6);
    func_02002d14(data_ov094_0229be78, (void *) p, 8, 7, 7, 0xe);
    func_02002c6c(data_ov094_0229be90, (void *) p, 8, 0xc0, 0xc0, 0x15f);
    return func_02002c6c(data_ov094_0229bea8, (void *) p, 8, 0x160, 0x160, 0x1ff);
}

void func_ov094_0229a084(int arg)
{
    func_ov094_0229a018((Container *) arg);
    func_ov094_02299ff8((void *) arg);
}

void func_ov094_0229a05c(void *p)
{
    func_ov094_02299b74((UnkStruct_02299b74 *) p);
    func_ov094_02299ad0(p);
    func_ov094_02299fb8(p);
    func_ov094_02299d8c((UnkStruct_02299d8c *) p);
    func_ov094_02299d88(p);
}

void func_ov094_0229a038(void *p)
{
    func_ov094_0229a018((Container *) p);
    func_ov094_02299ff8(p);
    if (*(unsigned char *) ((char *) p + 0x13) != 0) {
        func_02004644(0x2d, 1);
    }
}

void func_ov094_0229a018(Container *c)
{
    int i;
    for (i = 0; i < 3; i++) {
        func_020b9ccc(&c->units[i]);
    }
}

void func_ov094_02299ff8(void *p)
{
    int i;
    for (i = 0; i < 2; i++) {
        func_02070b84((char *) p + 0xe0 + i * 0x6c);
    }
}

void func_ov094_02299fb8(void *p)
{
    if (func_ov094_022999b0(p, 1)) {
        if (func_020b9bbc((char *) p + 0x38, (char *) p + 0x1b8, ((unsigned char *) p)[0xe], 0x800, 0)) {
            func_ov094_022999a0(p, 1);
        }
    }
}

void func_ov094_02299f88(int r4)
{
    int sp[2];
    sp[0] = 0xc;
    sp[1] = 2;
    func_0206fdd4(r4 + 0x1b8, 0xe, 3, 0x17, sp[0], sp[1]);
    func_ov094_022999a8((void *) r4, 1);
}

void func_ov094_02299f64(int param)
{
    func_0206fdd4(param + 0x1b8, 0xe, 3, 0x17, 0xc, 7);
}

void func_ov094_02299f40(int a0)
{
    func_0206fdd4(a0 + 0x1b8, 0xe, 0x3, 0x17, 0xc, 0x6);
}

void func_ov094_02299e1c(void *self)
{
    void *a;
    u16 *p;
    int b;
    unsigned int v;
    int ret;
    int ok;

    a = (void *) func_020984e8();
    b = func_020950c0((void *) func_02099870((int) a));
    p = func_02099728(a);
    ret = 0;
    ok = 0;
    v = *p;
    if (v >= 0x1369 && v <= 0x1369) {
        ok = 1;
    }
    if (ok || (v >= 0x136a && v <= 0x136a)) {
        ret = 1;
    } else if ((v >= 0x136b && v <= 0x1372) || (v >= 0x1373 && v <= 0x1373)) {
        ret = 2;
    } else if ((v >= 0x1374 && v <= 0x1374) || (v >= 0x1375 && v <= 0x1375)) {
        ret = 3;
    } else if ((v >= 0x1380 && v <= 0x139f) || (v >= 0x13a0 && v <= 0x13a7)) {
        ret = 4;
    } else if ((v >= 0x1377 && v <= 0x1377) || (v >= 0x1376 && v <= 0x1376)) {
        ret = 5;
    } else if ((v >= 0x1379 && v <= 0x1379) || (v >= 0x1378 && v <= 0x1378)) {
        ret = 6;
    } else if ((v >= 0x137a && v <= 0x137a) || (v >= 0x137b && v <= 0x137b)) {
        ret = 7;
    }
    func_ov094_02299dcc(self, (const void *) ret, b);
}

void func_ov094_02299dcc(void *self, const void *src, int flag)
{
    char local[0x2c];
    void *dst;

    if (flag == 0) {
        func_02064328(local, data_ov094_0229be20, (int) src);
    } else {
        func_02064328(local, data_ov094_0229be3c, (int) src);
    }

    dst = (char *) self + 0x9b8;
    func_02064af4((const void *) local, (void *) dst, 0xc80);

    *(unsigned char *) ((char *) self + 0x14) = (unsigned char) (unsigned int) src;

    func_ov094_022999a8(self, 4);
}

void func_ov094_02299d8c(UnkStruct_02299d8c *p)
{
    if (func_ov094_022999b0((void *) p, 4) != 0) {
        if (func_020b9c10((char *) p + 0x70, (char *) p + 0x9b8, p->unk_0E, 0x35, 0x35, 0x98) != 0) {
            func_ov094_022999a0((void *) p, 4);
        }
    }
}

void func_ov094_02299d88(void *self) {}

void func_ov094_02299d84(void *receiver, int value) {}

void func_ov094_02299d7c(unsigned char *p0, int p1)
{
    p0[17] = p1;
    p0[18] = 14;
}

int func_ov094_02299d40(void *p)
{
    int rem;

    if (*(unsigned char *) ((char *) p + 0x12) == 0) {
        goto ret1;
    }
    *(unsigned char *) ((char *) p + 0x12) -= 1;
    rem = *(unsigned char *) ((char *) p + 0x12) % 5;
    switch (rem) {
        case 3:
            func_ov094_02299acc(p, *(unsigned char *) ((char *) p + 0x11));
            break;
        case 0:
            func_ov094_02299ac4(p);
            break;
    }
    goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}

void func_ov094_02299d34(void *r0)
{
    *(unsigned char *) ((char *) r0 + 0x12) = 0;
    func_ov094_02299ac4((void *) r0);
}

void func_ov094_02299cd0(UnkStruct_02299cd0 *p, UnkStruct_02299cd0 *q)
{
    int a;
    int diff;
    a = func_ov094_02299c5c();
    if (a == p->unk_00) {
        return;
    }
    if (a > p->unk_00) {
        diff = a - p->unk_00;
    } else {
        diff = p->unk_00 - a;
    }
    if (diff < 30) {
        p->unk_13 = 1;
        return;
    }
    p->unk_13 = 14;
    p->unk_04 = diff / 13;
    if (p->unk_04 % 5 == 0) {
        p->unk_04--;
    }
    if (p->unk_04 <= 1) {
        p->unk_13 = 1;
    }
    func_ov094_02299c74(p, (int) q);
    func_02004658(0x2d);
}

void func_ov094_02299c74(void *arg, int idx)
{
    int a = 7;
    int b = 9;

    switch (idx) {
        case 0:
            break;
        case 1:
            b = 8;
            a = 9;
            break;
        case 2:
            b = 8;
            a = 8;
            break;
        case 3:
            b = 8;
            break;
    }

    func_0206fdd4((int) ((char *) arg + 0x1b8), a, 0xa, 0xb, 0xb, b);
    func_ov094_022999a8(arg, 1);
}

int func_ov094_02299c5c(void)
{
    return func_02098cf8(func_02099734((int) func_020984e8()), 0);
}

void func_ov094_02299c40(void *arg)
{
    int *p = (int *) arg;
    *p = func_ov094_02299c5c();
    ((char *) arg)[0x13] = 0;
    func_ov094_022999a8(arg, 2);
}

void func_ov094_02299b74(UnkStruct_02299b74 *self)
{
    int ret = func_ov094_02299c5c();
    if (self->unk_13 != 0) {
        self->unk_13--;
        if (self->unk_13 == 0) {
            self->unk_00 = ret;
            func_ov094_02299c74(self, 0);
            func_02004644(0x2d, 1);
            func_0200467c(0x3e);
        } else {
            if (self->unk_00 >= ret) {
                goto subtract;
            }
            self->unk_00 = self->unk_00 + self->unk_04;
            goto done;
        subtract:
            self->unk_00 = self->unk_00 - self->unk_04;
        done:;
        }
        func_ov094_022999a8(self, 2);
    }
    if (func_ov094_022999b0(self, 2) != 0) {
        int value = self->unk_00;
        unsigned short *p;
        int i;
        func_ov094_022999a8(self, 1);
        p = &self->unk_44E[0];
        for (i = 0; i < 5; i++) {
            int rem = value % 10;
            int v = rem * 2;
            p[0] = (p[0] & 0xfc00) | (v + 0x2d8);
            p[0x20] = (p[0x20] & 0xfc00) | (v + 0x2d9);
            p--;
            value = value / 10;
        }
        func_ov094_022999a0(self, 2);
    }
}
