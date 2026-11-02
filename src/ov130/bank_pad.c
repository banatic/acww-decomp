/* bank_pad: 46 functions, module ov130
 * mwccarm 1.2/base -O4,s
 * func_ov130_0229a7ac @ 0x0229a7ac, 0x48 bytes, Thumb
 * func_ov130_0229a790 @ 0x0229a790, 0x1c bytes, Thumb
 * func_ov130_0229a6d8 @ 0x0229a6d8, 0xb6 bytes, Thumb
 * func_ov130_0229a678 @ 0x0229a678, 0x60 bytes, Thumb
 * func_ov130_0229a4c8 @ 0x0229a4c8, 0x1b0 bytes, Thumb
 * func_ov130_0229a3f0 @ 0x0229a3f0, 0xd8 bytes, Thumb
 * func_ov130_0229a3a0 @ 0x0229a3a0, 0x50 bytes, Thumb
 * func_ov130_0229a378 @ 0x0229a378, 0x28 bytes, Thumb
 * func_ov130_0229a32c @ 0x0229a32c, 0x4c bytes, Thumb
 * func_ov130_0229a2b4 @ 0x0229a2b4, 0x78 bytes, Thumb
 * func_ov130_0229a278 @ 0x0229a278, 0x3c bytes, Thumb
 * func_ov130_0229a254 @ 0x0229a254, 0x24 bytes, Thumb
 * func_ov130_0229a24c @ 0x0229a24c, 0x6 bytes, Thumb
 * func_ov130_0229a224 @ 0x0229a224, 0x28 bytes, Thumb
 * func_ov130_0229a1dc @ 0x0229a1dc, 0x48 bytes, Thumb
 * func_ov130_0229a188 @ 0x0229a188, 0x54 bytes, Thumb
 * func_ov130_0229a17c @ 0x0229a17c, 0xc bytes, Thumb
 * func_ov130_0229a168 @ 0x0229a168, 0x14 bytes, Thumb
 * func_ov130_0229a148 @ 0x0229a148, 0x20 bytes, Thumb
 * func_ov130_0229a138 @ 0x0229a138, 0x10 bytes, Thumb
 * func_ov130_0229a124 @ 0x0229a124, 0x12 bytes, Thumb
 * func_ov130_0229a0a4 @ 0x0229a0a4, 0x80 bytes, Thumb
 * func_ov130_0229a080 @ 0x0229a080, 0x24 bytes, Thumb
 * func_ov130_0229a070 @ 0x0229a070, 0xe bytes, Thumb
 * func_ov130_0229a00c @ 0x0229a00c, 0x64 bytes, Thumb
 * func_ov130_02299de8 @ 0x02299de8, 0x224 bytes, Thumb
 * func_ov130_02299de0 @ 0x02299de0, 0x8 bytes, Thumb
 * func_ov130_02299ddc @ 0x02299ddc, 0x4 bytes, Thumb
 * func_ov130_02299dd8 @ 0x02299dd8, 0x4 bytes, Thumb
 * func_ov130_02299dd4 @ 0x02299dd4, 0x4 bytes, Thumb
 * func_ov130_02299dc8 @ 0x02299dc8, 0xc bytes, Thumb
 * func_ov130_02299dbc @ 0x02299dbc, 0xc bytes, Thumb
 * func_ov130_02299d98 @ 0x02299d98, 0x24 bytes, Thumb
 * func_ov130_02299d48 @ 0x02299d48, 0x50 bytes, Thumb
 * func_ov130_02299c08 @ 0x02299c08, 0x140 bytes, Thumb
 * func_ov130_02299bd8 @ 0x02299bd8, 0x2e bytes, Thumb
 * func_ov130_02299b88 @ 0x02299b88, 0x50 bytes, Thumb
 * func_ov130_02299af0 @ 0x02299af0, 0x98 bytes, Thumb
 * func_ov130_02299ac0 @ 0x02299ac0, 0x2e bytes, Thumb
 * func_ov130_02299a58 @ 0x02299a58, 0x68 bytes, Thumb
 * func_ov130_02299a08 @ 0x02299a08, 0x50 bytes, Thumb
 * func_ov130_022999e4 @ 0x022999e4, 0x22 bytes, Thumb
 * func_ov130_022999c0 @ 0x022999c0, 0x24 bytes, Thumb
 * func_ov130_022999b0 @ 0x022999b0, 0x10 bytes, Thumb
 * func_ov130_022999a8 @ 0x022999a8, 0x8 bytes, Thumb
 * func_ov130_022999a0 @ 0x022999a0, 0x8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned short unk_00;
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned int unk_18;
} UnkStruct_0229a6d8;

typedef struct {
    u8 pad_00[7];
    u8 unk_07;
    u8 unk_08;
    u8 pad_09[1];
    u8 unk_0A;
    u8 unk_0B;
    u8 pad_0C[0x290 - 0xc];
    u8 sub290[0x800];
    u8 subA90[4];
} UnkStruct_0229a4c8;

struct UnkStruct_0229a3a0 {
    char pad_00[7];
    unsigned char unk_07;
    char pad_08;
    unsigned char unk_09;
};

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
} UnkStruct_0229a24c;

typedef struct {
    char unk_00[5];
    unsigned char idx;
} UnkStruct_0229a138;

struct UnkStruct_0229a080 {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char unk_05;
};

typedef struct {
    char pad_00[8];
    u8 unk_08;
    u8 unk_09;
    char pad_0A[2];
    int unk_0C;
    char pad_10[0x1c - 0x10];
    int unk_1C;
    int unk_20;
} UnkStruct_02299de8;

typedef struct {
    char pad_00[0x60];
    char unk_60[4];
} UnkStruct_02299de8_2;

struct unknown_ov130_02299d98 {
    int pad_00[3];
    int unk_0C;
};

typedef struct {
    unsigned char pad_00[0x4];
    unsigned char unk_04;
    unsigned char pad_05[0x7];
    int unk_0C;
    int unk_10;
} UnkStruct_02299d48;

typedef struct {
    char pad_00[7];
    u8 unk_07;
    u8 unk_08;
    char pad_09[3];
    int unk_0C;
    char pad_10[4];
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_02299c08;

typedef struct {
    char pad_00[0x290];
    unsigned short arr[0x40];
} UnkStruct_02299af0;

typedef char Elem[108];

typedef struct {
    char pad_00[6];
    unsigned char count;
    char pad_07[37];
    Elem arr[5];
} UnkStruct_022999c0;

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern int **func_02070be8(void *unused0);
extern void *func_02070c08(void *unused0);
extern void *func_020b9cfc(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_020950c0(signed char *value);
extern void func_0200458c(int);
extern int func_02002c6c(const void *, void *, void *, int, int, int);
extern int func_02002d14(const void *, void *, void *, int, int, int);
extern void *data_021fbe94;
extern const unsigned char data_ov130_0229ac80[];
extern const unsigned char data_ov130_0229ac94[];
extern const unsigned char data_ov130_0229aca8[];
extern void *data_ov130_0229aa90[];
extern int func_02064af4(void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern int func_02002b40(void *, u8, int, int);
extern void *data_ov130_0229aa78[];
extern int func_0207094c(void *, int);
extern void func_02070adc(void *, u8, int, int, int, int, int);
extern void func_02070a04(void *, int, int);
extern u8 data_ov130_0229a804[];
extern u8 data_ov130_0229a7f4[];
extern char data_ov130_0229ac30[];
extern char data_ov130_0229ac44[];
extern char data_ov130_0229ac58[];
extern char data_ov130_0229ac6c[];
extern void *data_ov130_0229a980[];
extern void *func_02064b2c(void *t, void *g, int a, int *out);
extern int func_02002a88(void *p, int a, int b, int c, int d);
extern void func_020e993c(void *g, void *h);
extern int func_02002cd8(void *t, void *g, int a, int b, int c);
extern const unsigned char data_ov130_0229a7fc[];
extern void func_020b9ccc(void *);
extern int func_020b9bbc(void *d, void *s, unsigned char c, int size, int opt);
extern unsigned char data_ov130_0229a80c[];
extern char *data_ov130_0229a888[];
extern char *data_ov130_0229a8b4[];
extern char *data_ov130_0229a8e0[];
extern unsigned char *data_ov130_0229a90c[];
extern unsigned int data_ov130_0229a940[];
extern unsigned char data_ov130_0229a848[];
extern unsigned char data_ov130_0229a818[];
extern unsigned char data_ov130_0229a828[];
extern unsigned char data_ov130_0229a838[];
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern void func_02088df8(int a, const void *b, int c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);
extern const char data_ov130_0229aae0[];
extern const char data_ov130_0229ab70[];
extern int func_020896b8(int, void *, int, void *, int, int, int);
extern char data_ov130_0229ab20;
extern char data_ov130_0229abf0;
extern char data_ov130_0229abb0;
extern char data_ov130_0229ab40;
extern char data_ov130_0229ab48;
extern char data_ov130_0229ab50;
extern char data_ov130_0229ab58;
extern char data_ov130_0229ab60;
extern char data_ov130_0229ab68;
extern char data_ov130_0229ab10;
extern char data_ov130_0229ab18;
extern char data_ov130_0229ab00;
extern char data_ov130_0229ab08;
extern int func_0200457c(int arg);
extern void func_0200467c(int cmd);
extern void *data_ov130_0229a870[];
extern char *data_ov130_0229a858[];
extern void func_02070b84(void *);

void func_ov130_0229a1dc(unsigned char *p);
void func_ov130_0229a17c(int a, int b);
void func_ov130_0229a168(int a, int b);
void func_ov130_02299d48(UnkStruct_02299d48 *self);
void func_ov130_02299c08(UnkStruct_02299c08 *s);
void func_ov130_02299bd8(int a, int b, int c, int d, int count);
void func_ov130_02299b88(int a, int b, int c, int d, int e);
void func_ov130_02299af0(UnkStruct_02299af0 *self, int x, int y, int z);
void func_ov130_02299ac0(int a, int b, int c, int d, int n);
void func_ov130_02299a58(int a, int b, int c, int d, int e);
void func_ov130_02299a08(unsigned short *base, int a, int b, int c);
void func_ov130_022999e4(unsigned char *obj);
Elem *func_ov130_022999c0(UnkStruct_022999c0 *obj);
int func_ov130_022999b0(unsigned short *p, unsigned short mask);
void func_ov130_022999a8(unsigned short *p0, int p1);
void func_ov130_022999a0(short *p, int v);

#define VisitElement_02070c08 (void *) func_02070c08
#define VisitElement_02070be8 (void *) func_02070be8

void *func_ov130_0229a7ac(void *self)
{
    char *p, *end;

    __cxa_vec_ctor((char *) self + 0x2C, 5, 0x6C, VisitElement_02070c08, VisitElement_02070be8);
    p = (char *) self + 0x248;
    end = (char *) self + 0x290;
    do {
        func_020b9cfc(p);
        p += 0x24;
    } while (p != end);
    return self;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov130_0229a790(void *arg)
{
    __cxa_vec_cleanup((char *) arg + 0x2c, 5, 0x6c, VisitElement_02070be8);
    return arg;
}

#undef VisitElement_02070be8

void func_ov130_0229a6d8(UnkStruct_0229a6d8 *self, unsigned char idx, unsigned char arg2, unsigned char arg3)
{
    int object;
    self->unk_00 = 0;
    self->unk_07 = idx;

    switch (self->unk_07) {
        case 0:
            self->unk_08 = 2;
            self->unk_09 = 0;
            break;
        case 1:
            self->unk_08 = 2;
            self->unk_09 = 5;
            break;
        case 2:
            self->unk_08 = 2;
            self->unk_09 = 1;
            break;
        case 3:
            self->unk_08 = 3;
            self->unk_09 = 2;
            break;
        case 4:
            self->unk_08 = 5;
            self->unk_09 = 3;
            break;
        case 5:
            self->unk_08 = 3;
            self->unk_09 = 4;
            break;
        case 6:
            self->unk_08 = 4;
            self->unk_09 = 6;
            break;
        default:
            break;
    }

    self->unk_0A = arg2;
    self->unk_0B = arg3;

    func_ov130_022999e4((unsigned char *) self);

    self->unk_05 = 10;
    self->unk_04 = 13;
    self->unk_03 = 0;
    self->unk_02 = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    self->unk_14 = 0;
    self->unk_18 = 0;

    if ((object = func_020984e8()) != 0 && func_020950c0((signed char *) func_02099870(object)) == 0) {
        func_0200458c(0);
    } else {
        func_0200458c(1);
    }
}

int func_ov130_0229a678(void *arg)
{
    void *v;

    v = data_021fbe94;
    func_02002c6c(data_ov130_0229ac80, v, arg, 0x10, 0x10, 0xff);
    func_02002c6c(data_ov130_0229ac94, v, arg, 0x100, 0x100, 0x1a9);
    return func_02002d14(data_ov130_0229aca8, v, arg, 1, 1, 0xd);
}

void func_ov130_0229a4c8(UnkStruct_0229a4c8 *self)
{
    void *elem;

    func_ov130_0229a678((void *) self->unk_0A);
    func_02064af4(data_ov130_0229aa90[self->unk_08], self->sub290, 0x800);

    switch (self->unk_07) {
        case 0:
        case 1:
            func_0206fdd4(self->sub290, 2, 8, 0xd, 9, 0xa);
            break;
        case 2:
            func_0206fdd4(self->sub290, 2, 2, 0xd, 3, 0xa);
            break;
    }
    func_02002b40(self->sub290, self->unk_0A, 0x800, 0);

    func_02064af4(data_ov130_0229aa78[self->unk_08], self->subA90, 0x800);
    func_02002b40(self->subA90, self->unk_0B, 0x800, 0);

    elem = (void *) func_ov130_022999c0((UnkStruct_022999c0 *) self);
    if (self->unk_07 == 6) {
        func_0207094c(elem, 0x51);
    } else {
        func_0207094c(elem, 0xb8);
    }
    func_02070adc(elem, self->unk_0B, 0xec, 4, 0xf, 0, 0);
    func_02070a04(elem, 1, 0);

    elem = (void *) func_ov130_022999c0((UnkStruct_022999c0 *) self);
    switch (self->unk_07) {
        case 2:
            func_0207094c(elem, 0x59);
            break;
        case 4:
            func_0207094c(elem, 0x50);
            break;
        default:
            func_0207094c(elem, 0x54);
            break;
    }
    func_02070adc(elem, self->unk_0B, 0xb0, 0xa, 0xf, 0, 0);
    func_02070a04(elem, 1, 0);

    elem = (void *) func_ov130_022999c0((UnkStruct_022999c0 *) self);
    func_0207094c(elem, data_ov130_0229a804[self->unk_07]);
    func_02070adc(elem, self->unk_0B, 0xc4, 0xa, 0xf, 0, 0);
    func_02070a04(elem, 1, 0);

    if (self->unk_08 == 0 || self->unk_08 == 2) {
        elem = (void *) func_ov130_022999c0((UnkStruct_022999c0 *) self);
        func_0207094c(elem, data_ov130_0229a7f4[self->unk_07]);
        func_02070adc(elem, self->unk_0B, 0xd8, 0xa, 0xf, 0, 0);
        func_02070a04(elem, 1, 0);
    }

    func_ov130_0229a1dc((unsigned char *) self);
    func_ov130_02299c08((UnkStruct_02299c08 *) self);
}

int func_ov130_0229a3f0(int a)
{
    void *g;
    void *h;
    char *p;
    int i;
    int k;
    int tmp;

    g = data_021fbe94;
    func_02002d14((const void *) data_ov130_0229ac30, g, (void *) 8, 4, 4, 0xe);
    func_02002c6c((const void *) data_ov130_0229ac44, g, (void *) 8, 0xc0, 0xc0, 0x15f);
    func_02002c6c((const void *) data_ov130_0229ac58, g, (void *) 8, 0x160, 0x160, 0x1ff);
    h = func_02064b2c(data_ov130_0229a980[a / 5], g, -4, &tmp);
    p = (char *) h + (a % 5) * 0xc0;
    k = 0x15a;
    for (i = 0; i < 6; i++) {
        func_02002a88(p, 8, k, k, k + 5);
        p = p + 0x400;
        k = k + 0x20;
    }
    func_020e993c(g, h);
    return func_02002cd8(data_ov130_0229ac6c, g, 8, a, 4);
}

void func_ov130_0229a3a0(struct UnkStruct_0229a3a0 *p)
{
    int r4;
    func_ov130_0229a3f0((unsigned char) p->unk_09);
    r4 = (int) func_ov130_022999c0((UnkStruct_022999c0 *) p);
    func_0207094c((void *) r4, (unsigned char) data_ov130_0229a7fc[p->unk_07]);
    func_02070adc((void *) r4, 8, 0x14c, 14, 15, 0, 0);
    func_02070a04((void *) r4, 1, 0);
}

void func_ov130_0229a378(void *self)
{
    func_ov130_022999e4((unsigned char *) self);
    func_020b9ccc((char *) self + 0x248);
    func_020b9ccc((char *) self + 0x26c);
}

void func_ov130_0229a32c(void *self)
{
    unsigned char *p = (unsigned char *) self;
    func_ov130_022999e4((unsigned char *) self);
    func_020b9ccc((void *) ((char *) self + 0x248));
    func_020b9ccc((void *) ((char *) self + 0x26c));
    if (p[3] != 0) {
        p[3] = p[3] - 1;
        if (p[3] == 0) {
            if (p[2] != 0) {
                p[3] = 1;
            } else {
                func_ov130_0229a168((int) self, (unsigned char) p[4]);
            }
        }
    }
}

void func_ov130_0229a2b4(void *p)
{
    if (func_ov130_022999b0((unsigned short *) p, 1)) {
        if (func_020b9bbc((char *) p + 0x248, (char *) p + 0x290, ((unsigned char *) p)[0xa], 0x800, 0)) {
            func_ov130_022999a0((short *) p, 1);
        }
    }
    if (func_ov130_022999b0((unsigned short *) p, 2)) {
        if (func_020b9bbc((char *) p + 0x26c, (char *) p + 0xa90, ((unsigned char *) p)[0xb], 0x800, 0)) {
            func_ov130_022999a0((short *) p, 2);
        }
    }
}

int func_ov130_0229a278(unsigned char *p, int x, int y)
{
    int nx = x - 0x50;
    int ny = y - 0x60;

    if (p[8] == 0 || p[8] == 2) {
        nx -= 0x40;
    }

    if (nx >= 0 && nx < 0x60 && ny >= 0 && ny < 0x40) {
        p[4] = data_ov130_0229a80c[(nx >> 5) + 3 * (ny >> 4)];
        return p[4];
    }
    return 13;
}

void func_ov130_0229a254(void *param)
{
    func_ov130_0229a1dc((unsigned char *) param);
    func_ov130_0229a17c((int) param, (unsigned char) (*(unsigned char *) ((char *) param + 4)));
    *(unsigned char *) ((char *) param + 2) = 0xd;
    *(unsigned char *) ((char *) param + 3) = 5;
    func_ov130_02299d48((UnkStruct_02299d48 *) param);
}

void func_ov130_0229a24c(UnkStruct_0229a24c *p)
{
    p->unk_02 = 0;
}

int func_ov130_0229a224(unsigned char *r0)
{
    if (r0[2] != 0) {
        r0[2] = r0[2] - 1;
        if (r0[2] == 0) {
            r0[2] = 2;
            func_ov130_02299d48((UnkStruct_02299d48 *) r0);
            return 1;
        }
    }
    return 0;
}

void func_ov130_0229a1dc(unsigned char *p)
{
    int value;
    if (p[8] == 0 || p[8] == 2) {
        value = 18;
    } else {
        value = 10;
    }
    func_0206fdd4((void *) (p + 0xa90), value, 12, value + 12, 19, 2);
    func_ov130_0229a168((int) p, 10);
    func_ov130_022999a8((unsigned short *) p, 2);
}

void func_ov130_0229a188(void *p, unsigned int index, int arg2)
{
    char *ptr1 = data_ov130_0229a888[index];
    char *ptr2 = data_ov130_0229a8b4[index];
    char *ptr3 = data_ov130_0229a8e0[index];
    char *ptr3_plus = ptr3 + 1;
    unsigned char b = *(unsigned char *) ((char *) p + 8);

    if (b == 0 || b == 2) {
        ptr1 += 8;
        ptr2 += 8;
    }
    func_0206fdd4((char *) p + 0xA90, (int) ptr1, (int) ptr3, (int) ptr2, (int) ptr3_plus, arg2);
    func_ov130_022999a8((unsigned short *) p, 2);
}

void func_ov130_0229a17c(int a, int b)
{
    func_ov130_0229a188((void *) a, b, 3);
}

void func_ov130_0229a168(int a, int b)
{
    func_ov130_0229a188((void *) a, b, (b == 10) ? 1 : 2);
}

unsigned char *func_ov130_0229a148(unsigned char *obj)
{
    unsigned char idx = obj[5];
    unsigned char *ptr = data_ov130_0229a90c[idx];
    unsigned char mode = obj[8];
    if (mode == 0 || mode == 2) {
        if (idx <= 10) {
            ptr += 0x40;
        }
    }
    return ptr;
}

void *func_ov130_0229a138(UnkStruct_0229a138 *obj)
{
    return (void *) data_ov130_0229a940[obj->idx];
}

int func_ov130_0229a124(unsigned char *p)
{
    int result = 1;
    if (p[5] != 0xb && p[5] != 0xc) {
        result = 0;
    }
    return result;
}

int func_ov130_0229a0a4(int param0, int param1)
{
    int r5;
    int r4;
    int r6;
    int r0;
    int r1;

    r5 = param0;
    r4 = param1;
    if (r4 == 0) {
        return 0;
    }
    r6 = *(unsigned char *) (r5 + 5);
    r0 = r4;
    if (func_ov002_022088cc(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a848[r1];
        *(unsigned char *) (r5 + 5) = r0;
        goto label_0229a0da;
    }
    r0 = r4;
    if (func_ov002_022088bc(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a818[r1];
        *(unsigned char *) (r5 + 5) = r0;
    }
label_0229a0da:
    r0 = r4;
    if (func_ov002_022088ac(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a828[r1];
        *(unsigned char *) (r5 + 5) = r0;
        goto label_0229a100;
    }
    r0 = r4;
    if (func_ov002_0220889c(r0) != 0) {
        r1 = *(unsigned char *) (r5 + 5);
        r0 = data_ov130_0229a838[r1];
        *(unsigned char *) (r5 + 5) = r0;
    }
label_0229a100:
    r0 = *(unsigned char *) (r5 + 5);
    if (r6 == r0) {
        return 0;
    }
    return 1;
}

int func_ov130_0229a080(struct UnkStruct_0229a080 *self)
{
    unsigned char b = self->unk_05;
    if ((unsigned char) (b + 0xf5) <= 1) {
        return 0;
    }
    self->unk_04 = b;
    func_ov130_0229a254((void *) self);
    return 1;
}

int func_ov130_0229a070(unsigned char *p)
{
    if (p[5] == 0xb) {
        return 1;
    }
    return 0;
}

void func_ov130_0229a00c(void *param)
{
    void *p = (char *) param + 0x60;
    func_02088df8(1, data_ov130_0229aae0, 0x80, p, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, data_ov130_0229ab70, 0x80, p, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_ov130_02299de8(UnkStruct_02299de8 *a, UnkStruct_02299de8_2 *b)
{
    char *w;
    void *t1;
    void *t2;
    char *v;

    w = b->unk_60;
    if (a->unk_08 == 0 || a->unk_08 == 2) {
        t1 = &data_ov130_0229ab20;
        t2 = &data_ov130_0229abf0;
    } else if (a->unk_08 == 4) {
        t1 = ((char *) data_ov130_0229aae0);
        t2 = &data_ov130_0229abb0;
    } else {
        t1 = ((char *) data_ov130_0229aae0);
        t2 = ((char *) data_ov130_0229ab70);
    }
    if (a->unk_09 == 3) {
        w = w + 0xa;
    }
    func_02088df8(1, (const void *) t1, 0x80, w, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, (const void *) t2, 0x80, w, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);

    v = b->unk_60;
    if (a->unk_08 == 4) {
        return;
    }
    if (a->unk_08 == 0 || a->unk_08 == 2) {
        if (a->unk_0C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab40, 0x80, v, -1, 2, 0);
        }
        if (a->unk_0C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab48, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab50, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab58, 0x80, v, -1, 2, 0);
        }
        if (a->unk_20 >= 1000) {
            func_020896b8(1, &data_ov130_0229ab60, 0x80, v, -1, 2, 0);
        }
        if (a->unk_20 >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab68, 0x80, v, -1, 2, 0);
        }
        return;
    }

    {
        if (a->unk_08 == 5) {
            v = v - 8;
        }
        if (a->unk_0C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab10, 0x80, v, -1, 2, 0);
        }
        if (a->unk_0C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab18, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000) {
            func_020896b8(1, &data_ov130_0229ab00, 0x80, v, -1, 2, 0);
        }
        if (a->unk_1C >= 1000000) {
            func_020896b8(1, &data_ov130_0229ab08, 0x80, v, -1, 2, 0);
        }
    }
}

void func_ov130_02299de0(int *p0, int p1, int p2, int p3)
{
    p0[4] = p1;
    p0[5] = p2;
    p0[6] = p3;
}

int func_ov130_02299ddc(int *p0)
{
    return p0[3];
}

int func_ov130_02299dd8(int *p0)
{
    return p0[5];
}

int func_ov130_02299dd4(int *p0)
{
    return p0[6];
}

int func_ov130_02299dc8(int value)
{
    return func_0200457c(0);
}

void func_ov130_02299dbc(void)
{
    func_0200467c(0x2a);
}

int func_ov130_02299d98(struct unknown_ov130_02299d98 *self)
{
    if (self->unk_0C == 0) {
        return 0;
    }
    self->unk_0C = 0;
    func_ov130_02299dbc();
    func_ov130_02299c08((UnkStruct_02299c08 *) self);
    return 1;
}

void func_ov130_02299d48(UnkStruct_02299d48 *self)
{
    int base;
    int val;
    int max;
    unsigned char idx;

    base = self->unk_0C;
    idx = self->unk_04;

    if (idx == 10) {
        if (func_ov130_02299d98((struct unknown_ov130_02299d98 *) self) != 0) {
            return;
        }
        func_0200467c(0x34);
        return;
    } else {
        val = idx + 10 * base;
        max = self->unk_10;
        if (val > max) {
            val = max;
        }
        if (val == base) {
            func_0200467c(0x34);
        } else {
            func_ov130_02299dc8(idx);
            self->unk_0C = val;
            func_ov130_02299c08((UnkStruct_02299c08 *) self);
        }
    }
}

void func_ov130_02299c08(UnkStruct_02299c08 *s)
{
    void *a;
    char *b;
    int v;

    a = data_ov130_0229a870[s->unk_08];
    b = data_ov130_0229a858[s->unk_08];

    switch (s->unk_08) {
        case 4:
            if (s->unk_0C == 0) {
                func_ov130_02299ac0((int) s, 0xa, (int) a, (int) b, 2);
            } else {
                func_ov130_02299a58((int) s, s->unk_0C, (int) a, (int) b, 2);
            }
            break;
        case 5:
            if (s->unk_0C == 0) {
                func_ov130_02299a58((int) s, 0, (int) a, (int) b, 9);
                func_ov130_02299ac0((int) s, 0xa, (int) a, (int) b, 7);
            } else {
                func_ov130_02299a58((int) s, s->unk_0C, (int) a, (int) b, 7);
            }
            break;
        default:
            s->unk_1C = s->unk_14;
            if (s->unk_08 >= 2) {
                func_ov130_02299a58((int) s, s->unk_1C, (int) a, (int) b, 9);
            } else {
                func_ov130_02299b88((int) s, s->unk_1C, (int) a, (int) b, 6);
            }
            if (s->unk_0C == 0) {
                if (s->unk_08 >= 2) {
                    func_ov130_02299ac0((int) s, 0xa, (int) a, (int) (b + 3), 9);
                } else {
                    func_ov130_02299bd8((int) s, 0xa, (int) a, (int) (b + 3), 6);
                }
            } else {
                if (s->unk_08 >= 2) {
                    func_ov130_02299a58((int) s, s->unk_0C, (int) a, (int) (b + 3), 9);
                } else {
                    func_ov130_02299b88((int) s, s->unk_0C, (int) a, (int) (b + 3), 6);
                }
            }
            if (s->unk_08 == 0 || s->unk_08 == 2) {
                v = s->unk_18;
                if (s->unk_07 != 0) {
                    v = v + s->unk_0C;
                }
                s->unk_20 = v;
                if (s->unk_08 >= 2) {
                    func_ov130_02299a58((int) s, s->unk_20, (int) a, (int) (b + 6), 9);
                } else {
                    func_ov130_02299b88((int) s, s->unk_20, (int) a, (int) (b + 6), 6);
                }
            }
            break;
    }
}

void func_ov130_02299bd8(int a, int b, int c, int d, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        func_ov130_02299af0((UnkStruct_02299af0 *) a, b, c, d);
        c -= 2;
    }
}

void func_ov130_02299b88(int a, int b, int c, int d, int e)
{
    int i;

    for (i = 0; i < e; i++) {
        if (b == 0) {
            func_ov130_02299af0((UnkStruct_02299af0 *) a, 11, c, d);
        } else {
            func_ov130_02299af0((UnkStruct_02299af0 *) a, b % 10, c, d);
            b = b / 10;
        }
        c -= 2;
    }
}

void func_ov130_02299af0(UnkStruct_02299af0 *self, int x, int y, int z)
{
    unsigned short v;
    unsigned int r6;

    if (x != 0xb) {
        v = (unsigned short) (x * 4 + 0x84);
    } else {
        v = 0x176;
    }
    r6 = y + z * 32;
    self->arr[r6] = v | (self->arr[r6] & 0xFC00);
    self->arr[r6 + 1] = (unsigned short) (v + 1) | (self->arr[r6 + 1] & 0xFC00);
    v += 2;
    if (x == 0xb) {
        v = 0x176;
    }
    self->arr[r6 + 0x20] = v | (self->arr[r6 + 0x20] & 0xFC00);
    self->arr[r6 + 0x21] = (unsigned short) (v + 1) | (self->arr[r6 + 0x21] & 0xFC00);
    func_ov130_022999a8((unsigned short *) self, 1);
}

void func_ov130_02299ac0(int a, int b, int c, int d, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        func_ov130_02299a08((unsigned short *) a, b, c, d);
        c--;
    }
}

void func_ov130_02299a58(int a, int b, int c, int d, int e)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < e) {
        if (b == 0) {
            if (i == 0) {
                func_ov130_02299a08((unsigned short *) a, j, c, d);
            } else {
                func_ov130_02299a08((unsigned short *) a, 0xb, c, d);
            }
        } else {
            func_ov130_02299a08((unsigned short *) a, b % 10, c, d);
            b = b / 10;
        }
        c--;
        i++;
    }
}

void func_ov130_02299a08(unsigned short *base, int a, int b, int c)
{
    unsigned short idx;
    int row;
    unsigned short *arr;

    idx = (unsigned short) ((a << 1) + 0x160);
    row = b + (c << 5);
    arr = (unsigned short *) ((char *) base + 0x290);

    arr[row] = (arr[row] & 0xFC00) | idx;

    row += 0x20;
    idx = (unsigned short) (idx + 1);
    arr[row] = (arr[row] & 0xFC00) | idx;

    func_ov130_022999a8(base, 1);
}

void func_ov130_022999e4(unsigned char *obj)
{
    int i;
    obj[6] = 0;
    for (i = 0; i < 5; i++) {
        func_02070b84(obj + 0x2c + i * 0x6c);
    }
}

Elem *func_ov130_022999c0(UnkStruct_022999c0 *obj)
{
    if (obj->count < 5) {
        goto body;
    }
    return &obj->arr[4];
body:
    obj->count++;
    return &obj->arr[obj->count - 1];
}

int func_ov130_022999b0(unsigned short *p, unsigned short mask)
{
    if (*p & mask) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov130_022999a8(unsigned short *p0, int p1)
{
    p0[0] = (p0[0] | p1);
}

void func_ov130_022999a0(short *p, int v)
{
    *(unsigned short *) p &= ~v;
}
