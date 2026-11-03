/* snowmen_2: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b0aa8 @ 0x020b0aa8, 0x14 bytes, Thumb
 * func_020b0aa4 @ 0x020b0aa4, 0x2 bytes, Thumb
 * func_020b0a88 @ 0x020b0a88, 0x1c bytes, Thumb
 * func_020b0a84 @ 0x020b0a84, 0x2 bytes, Thumb
 * func_020b0a80 @ 0x020b0a80, 0x2 bytes, Thumb
 * func_020b0a3c @ 0x020b0a3c, 0x44 bytes, Thumb
 * func_020b0a20 @ 0x020b0a20, 0x1a bytes, Thumb
 * func_020b0970 @ 0x020b0970, 0xb0 bytes, Thumb
 * func_020b0918 @ 0x020b0918, 0x58 bytes, Thumb
 * func_020b08c0 @ 0x020b08c0, 0x58 bytes, Thumb
 * func_020b08b8 @ 0x020b08b8, 0x8 bytes, Thumb
 * func_020b0860 @ 0x020b0860, 0x58 bytes, Thumb
 * func_020b0838 @ 0x020b0838, 0x28 bytes, Thumb
 * func_020b081c @ 0x020b081c, 0x1c bytes, Thumb
 * func_020b076c @ 0x020b076c, 0xb0 bytes, Thumb
 * func_020b0730 @ 0x020b0730, 0x3c bytes, Thumb
 * func_020b0698 @ 0x020b0698, 0x98 bytes, Thumb
 * func_020b0678 @ 0x020b0678, 0x1e bytes, Thumb
 * func_020b0650 @ 0x020b0650, 0x28 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020b0a3c {
    unsigned short a : 7;
    unsigned short b : 4;
    unsigned short c : 5;
    unsigned short d : 7;
    unsigned short e : 7;
    unsigned short f : 2;
    unsigned char pad_04;
    unsigned char unk_05;
};

struct UnkStruct_020b0a20 {
    unsigned char pad_00[2];
    unsigned short a : 7;
    unsigned short b : 7;
    unsigned short c : 2;
};

typedef struct UnkStruct_020b0970 {
    unsigned short a0 : 7;
    unsigned short a1 : 4;
    unsigned short a2 : 5;
    unsigned short b0 : 7;
    unsigned short b1 : 7;
    unsigned short b2 : 2;
    unsigned char g;
    unsigned char h;
} UnkStruct_020b0970;

typedef struct DateTime {
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char mon;
    unsigned char year;
    unsigned short pad_06;
} DateTime;

typedef union DateTimeU {
    DateTime t;
    unsigned int w[2];
} DateTimeU;

struct UnkStruct_020b0918 {
    char pad_00[2];
    unsigned short field_2 : 7;
    unsigned short : 9;
    unsigned char unk_04;
};

typedef struct {
    unsigned char pad_00;
    unsigned char pad_01;
    unsigned short lowbit : 7;
    unsigned short fieldbit : 7;
    unsigned char type;
} UnkStruct_020b08c0;

struct bf {
    u16 a : 7;
    u16 b : 4;
    u16 c : 5;
};

typedef struct {
    unsigned char *base;
    unsigned int width;
    unsigned int height;
} UnkStruct_020b076c;

typedef struct UnkStruct_020b0698 {
    unsigned char pad_00[8];
    unsigned char a : 2;
    unsigned char f : 6;
} UnkStruct_020b0698;

typedef struct {
    unsigned char data[6];
} UnkStruct_020b0678;

typedef struct {
    unsigned char data[6];
} Elem;

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0209e474(DateTime *d);
extern void func_0209e140(DateTime *d, int n);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_0209dcdc(void *, void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern UnkStruct_020b076c *func_0204e414(void);
extern void *func_02037e0c(void *ptr, int k, int l, int zero);
extern int func_0204bb54(void *p);
extern int func_0204bb2c(void *p);
extern void func_0204f800(void *p1, void *p2, int j, int i, int k, int l);
extern int func_0204f538(int arg0, unsigned short *arg1, int arg2, int arg3, int arg4);
extern char data_021ebcc8;
extern int func_020b65ac(int);

void func_020b0aa8(unsigned int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x800;
}

void func_020b0aa4(void *object) {}

void *func_020b0a88(void *param0)
{
    __cxa_vec_cleanup((void *) (param0), 2, 16, (void (*)(void *)) func_020b0aa4);
    return param0;
}

void func_020b0a84(void *object) {}

void func_020b0a80(void *object) {}

void func_020b0a3c(struct UnkStruct_020b0a3c *p)
{
    p->a = 0;
    p->b = 0;
    p->c = 0;
    p->d = 0;
    p->e = 0;
    p->f = 0;
    p->unk_05 = 0;
}

int func_020b0a20(struct UnkStruct_020b0a20 *s)
{
    if (s->a != 0 && s->b != 0) {
        return 1;
    }
    return 0;
}

void func_020b0970(UnkStruct_020b0970 *p, unsigned short a, unsigned short b, int c)
{
    DateTimeU d;

    p->b0 = a >> 7;
    p->b1 = b >> 7;
    p->b2 = c;
    p->g = 0;
    d.w[0] = 0;
    d.w[1] = 0;
    func_0209e474(&d.t);
    if (d.t.hour < 6) {
        func_0209e140(&d.t, 1);
    }
    p->a0 = d.t.year;
    p->a1 = d.t.mon;
    p->a2 = d.t.day;
    p->h = 1;
}

int func_020b0918(struct UnkStruct_020b0918 *p)
{
    int r4 = p->field_2 << 7;
    int r1;
    if (r4 == 0) {
        r4 = 0x1000;
    }
    r1 = 0x1000;
    if (p->unk_04 == 1) {
        r1 = FX_Div(0x3000, 0x4000);
    } else if (p->unk_04 == 2) {
        r1 = FX_Div(r1, 0x2000);
    }
    if (r1 > 0x1000) {
        r1 = 0x1000;
    }
    return FX_MulFunc(r4, r1);
}

int func_020b08c0(UnkStruct_020b08c0 *p)
{
    int r4;
    int r1;

    r4 = p->fieldbit << 7;
    if (r4 == 0) {
        r4 = 0x1000;
    }

    r1 = 0x1000;
    if (p->type == 1) {
        r1 = FX_Div(0x3000, 0x4000);
    } else if (p->type == 2) {
        r1 = FX_Div(0x1000, 0x2000);
    }

    if (r1 > 0x1000) {
        r1 = 0x1000;
    }

    return FX_MulFunc(r4, r1);
}

int func_020b08b8(unsigned short *p0)
{
    return (int) ((unsigned int) ((p0[1] << 16)) >> 30);
}

int func_020b0860(u16 *param)
{
    u8 local[16];

    *(u32 *) &local[0] = 0;
    *(u32 *) &local[4] = 0;

    func_0209e474((DateTime *) local);

    if (local[2] < 6) {
        func_0209e140((DateTime *) local, 1);
    }

    local[0xa] = local[5];
    local[9] = local[4];
    local[8] = local[3];

    local[0xe] = (u8) ((struct bf *) param)->a;
    local[0xd] = (u8) ((struct bf *) param)->b;
    local[0xc] = (u8) ((struct bf *) param)->c;

    return func_0209dcdc(&local[8], &local[12]);
}

void *func_020b0838(void *arg)
{
    __cxa_vec_ctor((void *) (arg), 3, 6, (void (*)(void *)) func_020b0a84, (void (*)(void *)) func_020b0a80);
    return arg;
}

int func_020b081c(int a)
{
    __cxa_vec_cleanup((void *) (a), 3, 6, (void (*)(void *)) func_020b0a80);
    return a;
}

int func_020b076c(void *p1, void *p2, int p3)
{
    unsigned char *ptr;
    UnkStruct_020b076c *s;
    int start;
    void *r;
    int i, j, k, l;

    s = func_0204e414();
    start = 1;
    for (i = 1; i <= 4; i++) {
        for (j = start; j <= 4; j++) {
            if (j < s->width && i < s->height && s->base) {
                ptr = s->base + (i * s->width + j) * 0x28;
            } else {
                ptr = 0;
            }
            if (ptr) {
                for (k = 0; k < 16; k++) {
                    for (l = 0; l < 16; l++) {
                        r = func_02037e0c(ptr, l, k, 0);
                        if (r && func_0204bb54(r) && p3 == func_0204bb2c(r)) {
                            func_0204f800(p1, p2, j, i, l, k);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int func_020b0730(int arg0)
{
    unsigned short u16;
    int a, b;
    if (func_020b076c((void *) (&a), (void *) (&b), arg0)) {
        int tmp = (int) func_0204e414();
        u16 = 0xfff1;
        func_0204f538(tmp, &u16, a, b, 0);
        return 1;
    }
    return 1;
}

void func_020b0698(unsigned char *self)
{
    unsigned int i;
    int r;
    unsigned char *p;
    int k = func_020b65ac(((UnkStruct_020b0698 *) &data_021ebcc8)->f);
    int flag = 0;
    for (i = 0; i < 3; i++) {
        if (k == 0) {
            if (func_020b0730(i)) {
                func_020b0a3c((struct UnkStruct_020b0a3c *) (self + i * 6));
            }
        } else {
            p = self + i * 6;
            r = func_020b0a20((struct UnkStruct_020b0a20 *) p);
            if (r != 0) {
                r = func_020b0860((u16 *) p);
                if (((p[5] != 0) ? 1 : *(volatile int *) &flag) == 0) {
                    if (r != 0) {
                        func_020b0a3c((struct UnkStruct_020b0a3c *) p);
                    }
                } else {
                    if (r >= 3 || r < 0) {
                        if (func_020b0730(i)) {
                            func_020b0a3c((struct UnkStruct_020b0a3c *) p);
                        }
                    } else {
                        p[4] = (char) r;
                    }
                }
            }
        }
    }
}

void func_020b0678(UnkStruct_020b0678 *arg)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        func_020b0a3c((struct UnkStruct_020b0a3c *) (&arg[i]));
    }
}

int func_020b0650(Elem *base, unsigned int index)
{
    Elem *p;
    if (index < 3) {
        p = &base[index];
        if (func_020b0a20((struct UnkStruct_020b0a20 *) p) != 0) {
            func_020b0a3c((struct UnkStruct_020b0a3c *) p);
            return 1;
        }
    }
    return 0;
}
