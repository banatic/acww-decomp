/* snowball_2: 12 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226f648 @ 0x0226f648, 0xe8 bytes, Thumb
 * func_ov068_0226f5cc @ 0x0226f5cc, 0x7c bytes, Thumb
 * func_ov068_0226f504 @ 0x0226f504, 0xc8 bytes, Thumb
 * func_ov068_0226f4b4 @ 0x0226f4b4, 0x50 bytes, Thumb
 * func_ov068_0226f49c @ 0x0226f49c, 0x18 bytes, Thumb
 * func_ov068_0226f444 @ 0x0226f444, 0x58 bytes, Thumb
 * func_ov068_0226f3b0 @ 0x0226f3b0, 0x94 bytes, Thumb
 * func_ov068_0226f348 @ 0x0226f348, 0x68 bytes, Thumb
 * func_ov068_0226f298 @ 0x0226f298, 0xb0 bytes, Thumb
 * func_ov068_0226f230 @ 0x0226f230, 0x68 bytes, Thumb
 * func_ov068_0226f178 @ 0x0226f178, 0xb8 bytes, Thumb
 * func_ov068_0226f0e0 @ 0x0226f0e0, 0x98 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0226f648 {
    u8 pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    u8 pad_68[0xa8 - 0x68];
    int unk_A8;
    u8 pad_AC[0x26c - 0xac];
    int unk_26C;
    u8 unk_270;
    u8 pad_271[0x278 - 0x271];
    int unk_278;
    u8 pad_27C[0x2f0 - 0x27c];
    int unk_2F0;
    int unk_2F4;
    u8 pad_2F8[0x368 - 0x2f8];
    unsigned char unk_368;
};

struct UnkStruct_0226f648_2 {
    u8 lpad[0x3c];
    int value;
};

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Global;

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
} Elem;

struct UnkStruct_0226f504 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x26c - 0x68];
    int unk_26C;
    unsigned char pad_270[0x30c - 0x270];
    int unk_30C;
    unsigned char pad_310[0x396 - 0x310];
    short unk_396;
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
} ArrayElem;

struct UnkStruct_0226f444 {
    char pad_00[8];
    unsigned int flag;
    char pad_0C[0x50];
    char unk_5C;
    char pad_5D[0x31b];
    unsigned short u16field;
    char pad_37A[0xe];
    char unk_388;
};

struct Quad {
    int a;
    int b;
    int c;
    int d;
};

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x26c - 0x68];
    int unk_26C;
    int unk_270;
    char pad_274[0x388 - 0x274];
    char unk_388[32];
} UnkStruct_0226f3b0;

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0226f3b0_2;

struct UnkStruct_0226f348 {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x50];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x310];
    unsigned short unk_378;
    char pad_37A[2];
    int unk_37C;
    int unk_380;
    int unk_384;
};

struct UnkStruct_0226f348_2 {
    int a;
    int b;
    int c;
    int d;
};

struct UnkStruct_0226f298 {
    unsigned char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    unsigned char pad_68[0x288];
    int unk_2F0;
    int unk_2F4;
    unsigned char pad_2F8[0x8c];
    int unk_384;
};

struct UnkStruct_0226f230 {
    char pad_00[8];
    int unk_08;
    char pad_0C[0x2e8];
    int unk_2F4;
    char pad_2F8[0x80];
    unsigned short unk_378;
    char pad_37A[0x1c];
    unsigned short unk_396;
};

struct UnkStruct_0226f230_2 {
    int a;
    int b;
    int c;
    int d;
};

struct UnkStruct_0226f178 {
    u8 pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    u8 pad_68[0x204];
    int unk_26C;
    u8 pad_270[0x9c];
    int unk_30C;
    u8 pad_310[0x86];
    s16 unk_396;
};

extern void func_020e8b60(void *dst, int a, int b, int c);
extern int FX_Div(int a, int b);
extern void func_ov068_0226fc48(struct UnkStruct_0226f648 *self);
extern int func_ov003_0221a35c(struct UnkStruct_0226f648 *self, int a);
extern int func_02034270(void *a, void *b, int c, int d);
extern void func_0203423c(void *a);
extern Global data_021fbee8;
extern void *func_020b03f8(void);
extern int FX_MulFunc(int, int);
extern void func_020ee470(void *);
extern void func_ov068_0226fd80(void *);
extern short FX_SinCosTable_[][2];
extern void func_ov068_0226fcbc(void *self);
extern void func_0204f7e0(void *a, void *b);
extern void func_020eaca0(UnkStruct_0226f3b0_2 *, char *, int *);
extern int func_020ea838(UnkStruct_0226f3b0_2 *);
extern void func_020eabc8(UnkStruct_0226f3b0_2 *, int);
extern int func_020ea990(int *, char *);
extern int _s32_div_f(int, int);
extern int func_ov003_0221abf8(void *object, int flag);
extern int data_ov068_022786b8;
extern int data_ov068_022786bc;

void func_ov068_0226f648(struct UnkStruct_0226f648 *self)
{
    int v;
    int ret;
    struct UnkStruct_0226f648_2 local;
    int r;

    v = self->unk_26C;
    v += v >> 1;
    func_020e8b60(&self->unk_270, v, 0xcc, v);

    self->unk_5C += self->unk_2F0;
    self->unk_64 += self->unk_2F4;

    if (self->unk_368 < 0xc) {
        self->unk_A8++;
        self->unk_60 -= 0x100;
        self->unk_368++;
    } else {
        ret = FX_Div(0, 0x02710000);
        self->unk_A8 += ret + 0xe9;
        self->unk_60 -= self->unk_A8;
    }

    if (self->unk_278 & 2) {
        func_02034270(&local, &self->unk_5C, 0, 0);
        r = (local.value - self->unk_26C) - 0x200;
        if (self->unk_60 < r) {
            func_ov068_0226fc48(self);
            self->unk_60 = r;
            func_ov003_0221a35c(self, 2);
        }
        func_0203423c(&local);
    }
}

int func_ov068_0226f5cc(unsigned char *self)
{
    int idx;
    Elem *arr;

    *(unsigned short *) (self + 0x378) |= 0x10;
    *(unsigned short *) (self + 0x378) &= ~0x20;
    *(unsigned short *) (self + 0x396) = 0;

    idx = *(unsigned int *) (self + 8) & 1;
    arr = (Elem *) func_020b03f8();
    idx &= 1;

    arr[idx].a = 0;
    arr[idx].b = 0;
    arr[idx].c = 0;
    arr[idx].d = 0x800;

    *(unsigned int *) (self + 0x308) = data_021fbee8.a;
    *(unsigned int *) (self + 0x30c) = data_021fbee8.b;
    *(unsigned int *) (self + 0x310) = data_021fbee8.c;

    *(unsigned int *) (self + 0xa8) = 0;

    return 1;
}

void func_ov068_0226f504(struct UnkStruct_0226f504 *self)
{
    unsigned char buf[0x40];
    int val;

    val = self->unk_26C;
    val = val + (val >> 1);
    func_020e8b60((char *) self + 0x270, val, 0x200, val);

    func_02034270(buf, (char *) self + 0x5c, 0, 0);

    {
        int *out = (int *) (buf + 0x24);
        self->unk_5C = self->unk_5C + (out[0] >> 5);
        self->unk_64 = self->unk_64 + (out[2] >> 5);
    }

    self->unk_26C = FX_MulFunc(self->unk_26C, 0xfd7);

    self->unk_30C = FX_MulFunc(0x100, FX_SinCosTable_[(unsigned short) self->unk_396 >> 4][0]);

    self->unk_396 = (short) (self->unk_396 + 0x400);

    if (self->unk_26C < 0x80) {
        self->unk_26C = 0;
        func_020ee470(self);
    }

    func_ov068_0226fd80(self);

    self->unk_60 = *(int *) (buf + 0x3c) - self->unk_26C - 0x200;

    func_0203423c(buf);
}

int func_ov068_0226f4b4(void *self)
{
    volatile unsigned short *flag = (volatile unsigned short *) ((char *) self + 0x378);
    int idx;
    ArrayElem *arr;

    *flag |= 0x10;
    *flag &= ~0x20;

    idx = *(unsigned int *) ((char *) self + 8) & 1;
    arr = (ArrayElem *) func_020b03f8();
    idx &= 1;

    arr[idx].unk_00 = 0;
    arr[idx].unk_04 = 0;
    arr[idx].unk_08 = 0;
    arr[idx].unk_0C = 0x800;

    func_ov068_0226fcbc(self);
    return 1;
}

void func_ov068_0226f49c(void *r0)
{
    *(unsigned int *) ((char *) r0 + 0x270) = *(unsigned int *) ((char *) r0 + 0x26c);
    func_020ee470(r0);
}

int func_ov068_0226f444(struct UnkStruct_0226f444 *self)
{
    int flag;
    void *p;
    struct Quad *arr;

    self->u16field &= ~0x10;
    self->u16field |= 0x20;
    func_0204f7e0(&self->unk_388, &self->unk_5C);
    flag = (self->flag & 1);
    p = func_020b03f8();
    flag &= 1;
    arr = (struct Quad *) p;
    arr[flag].a = 0;
    arr[flag].b = 0;
    arr[flag].c = 0;
    arr[flag].d = 0x800;
    return 1;
}

void func_ov068_0226f3b0(UnkStruct_0226f3b0 *self)
{
    UnkStruct_0226f3b0_2 local;
    int r4;
    int v;

    self->unk_270 = self->unk_26C;

    func_020eaca0(&local, self->unk_388, &self->unk_5C);
    func_020ea838(&local);
    func_020eabc8(&local, 0x80);

    self->unk_5C += local.a;
    self->unk_64 += local.c;

    func_ov068_0226fd80((void *) self);

    r4 = func_020ea990(&self->unk_5C, self->unk_388);

    v = 0;
    if (r4 < 0x1000) {
        v = -_s32_div_f(0x1000 - r4, 5);
    }

    if (self->unk_60 < v) {
        self->unk_60 = v;
        if (r4 < 0x333) {
            func_ov003_0221abf8(self, 1);
        }
    }
}

int func_ov068_0226f348(struct UnkStruct_0226f348 *p)
{
    unsigned short *flags;
    int idx;
    struct UnkStruct_0226f348_2 *arr;

    flags = (unsigned short *) ((char *) p + 0x378);
    *flags &= ~0x10;
    *flags |= 0x20;

    idx = p->unk_08 & 1;
    arr = (struct UnkStruct_0226f348_2 *) func_020b03f8();
    idx = idx & 1;

    arr[idx].a = 0;
    arr[idx].b = 0;
    arr[idx].c = 0;
    arr[idx].d = 0x800;

    p->unk_37C = p->unk_5C;
    p->unk_380 = p->unk_60;
    p->unk_384 = p->unk_64;

    return 1;
}

void func_ov068_0226f298(struct UnkStruct_0226f298 *self)
{
    int *p = &self->unk_2F4;
    int diff;

    *p += FX_Div(0, 0x3e8000) + 0x158;
    self->unk_5C += self->unk_2F0;
    self->unk_64 += *p;

    diff = self->unk_64 - self->unk_384;
    if (diff < 0) {
        diff = -diff;
    }

    self->unk_60 = -FX_MulFunc(diff, 0x3d7);

    if ((data_ov068_022786bc & 1) == 0) {
        data_ov068_022786b8 = FX_Div(0, 0x64000) + 0x3000;
        data_ov068_022786bc |= 1;
    }

    if (diff >= data_ov068_022786b8) {
        func_ov003_0221a35c((struct UnkStruct_0226f648 *) self, 6);
    }
}

int func_ov068_0226f230(struct UnkStruct_0226f230 *p)
{
    unsigned short *flags;
    int idx;
    struct UnkStruct_0226f230_2 *arr;

    flags = (unsigned short *) ((char *) p + 0x378);
    *flags &= ~0x10;
    *flags |= 0x20;

    idx = p->unk_08 & 1;
    arr = (struct UnkStruct_0226f230_2 *) func_020b03f8();
    idx = idx & 1;

    arr[idx].a = 0;
    arr[idx].b = 0;
    arr[idx].c = 0;
    arr[idx].d = 0x800;

    p->unk_396 = 0;
    p->unk_2F4 = p->unk_2F4 >> 1;
    func_ov068_0226fc48((struct UnkStruct_0226f648 *) p);

    return 1;
}

void func_ov068_0226f178(struct UnkStruct_0226f178 *self)
{
    int buf[0x10];
    int *p;

    func_02034270((void *) buf, (void *) (&self->unk_5C), 0, 0);
    p = &buf[9];
    self->unk_5C += p[0] >> 5;
    self->unk_64 += p[2] >> 5;
    self->unk_26C = FX_MulFunc(self->unk_26C, 0xf85);
    self->unk_30C = FX_MulFunc(0x100, ((const short *) FX_SinCosTable_)[((unsigned short) self->unk_396 >> 4) * 2]);
    self->unk_396 += 0x400;
    if (self->unk_26C < 0x100) {
        self->unk_26C = 0;
        func_020ee470((void *) self);
    }
    {
        int t = buf[15] - self->unk_26C - 0x200;
        self->unk_60 -= 0x400;
        if (self->unk_60 < t) {
            self->unk_60 = t;
        }
    }
    func_0203423c((void *) buf);
}

int func_ov068_0226f0e0(void *self)
{
    unsigned short *p;
    void *base;
    unsigned int (*arr)[4];
    int mask;
    int diff_x;
    int diff_y;

    p = (unsigned short *) ((char *) self + 0x378);
    *p &= ~0x10;
    *p |= 0x20;

    func_0204f7e0((char *) self + 0x37C, (char *) self + 0x5C);

    mask = *(unsigned int *) ((char *) self + 8) & 1;
    base = func_020b03f8();
    mask = mask & 1;
    arr = (unsigned int (*)[4]) base;

    arr[mask][0] = 0;
    arr[mask][1] = 0;
    arr[mask][2] = 0;
    arr[mask][3] = 0x800;

    diff_x = *(int *) ((char *) self + 0x37C) - *(int *) ((char *) self + 0x5C);
    *(int *) ((char *) self + 0x314) = FX_Div(diff_x, 0x10000);

    diff_y = *(int *) ((char *) self + 0x384) - *(int *) ((char *) self + 0x64);
    *(int *) ((char *) self + 0x318) = FX_Div(diff_y, 0x10000);

    *(unsigned char *) ((char *) self + 0x399) = 0;

    return 1;
}
