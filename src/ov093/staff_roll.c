/* staff_roll: 16 functions, module ov093
 * mwccarm 1.2/base -O4,s
 * func_ov093_022997f8 @ 0x022997f8, 0x68 bytes, Thumb
 * func_ov093_022997b4 @ 0x022997b4, 0x44 bytes, Thumb
 * func_ov093_0229976c @ 0x0229976c, 0x48 bytes, Thumb
 * func_ov093_02299630 @ 0x02299630, 0x13a bytes, Thumb
 * func_ov093_022995b0 @ 0x022995b0, 0x80 bytes, Thumb
 * func_ov093_0229959c @ 0x0229959c, 0x14 bytes, Thumb
 * func_ov093_0229957c @ 0x0229957c, 0x20 bytes, Thumb
 * func_ov093_02299514 @ 0x02299514, 0x68 bytes, Thumb
 * func_ov093_022994ac @ 0x022994ac, 0x68 bytes, Thumb
 * func_ov093_02299490 @ 0x02299490, 0x1a bytes, Thumb
 * func_ov093_02299424 @ 0x02299424, 0x6c bytes, Thumb
 * func_ov093_02299418 @ 0x02299418, 0xc bytes, Thumb
 * func_ov093_022993c0 @ 0x022993c0, 0x58 bytes, Thumb
 * func_ov093_0229939c @ 0x0229939c, 0x24 bytes, Thumb
 * func_ov093_0229937c @ 0x0229937c, 0x20 bytes, Thumb
 * func_ov093_02299338 @ 0x02299338, 0x44 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229976c {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04;
    unsigned char unk_05;
};

typedef struct UnkStruct_02299630 {
    u8 pad_00[5];
    u8 state;
    u8 unk_06;
    u8 pad_07[0xc - 7];
    int unk_0C;
    u8 pad_10[0x14 - 0x10];
    int unk_14;
} UnkStruct_02299630;

typedef struct {
    unsigned char pad_00[5];
    unsigned char unk_05;
    unsigned char pad_06[2];
    unsigned int unk_08;
    unsigned char pad_0C[4];
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18[8];
    unsigned char unk_20[0x800];
    unsigned char unk_820[8];
    unsigned char unk_828[0x800];
    unsigned short unk_1028;
} UnkStruct_022994ac;

typedef struct {
    char pad_00[5];
    char unk_05;
    char unk_06;
    char pad_07[5];
    unsigned int unk_0C;
} UnkStruct_02299424;

extern void func_ov093_02298fd8(void *);
extern void *func_ov093_02298f64(void *);
extern void *func_020b9cfc(void *);
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*callback3)(void *));
extern void *func_ov093_02298f4c(void *p);
extern void func_ov093_02298fd4(void *p);
void func_0200277c(int);
void func_020028bc(int, int, int, int);
extern void func_ov093_02299048(UnkStruct_02299630 *self);
extern void func_ov093_022990b8(UnkStruct_02299630 *self, int a);
extern void func_ov093_02298fdc(void *self);
extern void func_ov093_02298f84(UnkStruct_02299630 *self, int a);
extern void func_02002708(int a);
extern void func_0200284c(int a, int b, int c);
extern void func_020019dc(int a, int b, int c);
extern void func_020019cc(void);
extern void func_02001ba4(int a);
extern void func_02001d1c(int a);
extern void func_02002808(int a, int b, int c, int d, int e);
extern int func_ov093_02298fac(void *a, int b);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov093_02298f9c(void *a, int b);
extern int func_02064af4(void *dst, void *src, unsigned int size);
extern unsigned char data_ov093_0229991c[];
extern int data_021fbe94;
extern int data_ov093_02299880;
extern int data_ov093_02299884;
extern int func_02002d14(int a, int b, int c, int d, int e, int f);
extern int func_02002c6c(int a, int b, int c, int d, int e, int f);
extern void func_ov093_02298fbc(void *ptr);
extern void MIi_CpuClear16(unsigned short value, void *dst, int size);
extern unsigned char func_02001b60(void);
extern void func_02001bb4(int);
extern void func_02001da0(int);
extern int func_ov093_02298f8c(int p, int q);
extern void func_ov093_022990e8(char *a, int b, char *c);
extern void func_ov093_02298fa4(char *a, int b);
extern void MIi_CpuCopy16(void *dst, const void *src, unsigned int size);
extern int func_020b4a20(void *dst, void *src, void *data);
extern int func_020a7bf4(void *dst, int value);
extern int _s32_div_f(int value, int count);
extern unsigned char data_ov093_0229990c[];

void func_ov093_0229957c(void *src);
void func_ov093_02299514(void *self);
void func_ov093_02299490(int param);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov093_022997f8(void *self)
{
    func_ov093_02298fd8((char *) self + 0x18);
    func_ov093_02298fd8((char *) self + 0x820);
    func_ov093_02298f64((char *) self + 0x1828);
    __cxa_vec_ctor((char *) self + 0x19e0, 0x1a, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    {
        char *p = (char *) self + 0x24d8;
        char *end = (char *) self + 0x2520;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);
    }
    return self;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov093_022997b4(void *base)
{
    __cxa_vec_cleanup((char *) base + 0x19e0, 0x1a, 0x6c, DisposeElement_func_02070be8);
    func_ov093_02298f4c((char *) base + 0x1828);
    func_ov093_02298fd4((char *) base + 0x0820);
    func_ov093_02298fd4((char *) base + 0x18);
    return base;
}

#undef DisposeElement_func_02070be8

void func_ov093_0229976c(struct UnkStruct_0229976c *p)
{
    p->unk_00 = 0;
    p->unk_04 = 0;
    func_0200277c(4);
    func_0200277c(0);
    func_020028bc(4, 0, 0, 0);
    *(volatile unsigned short *) 0x0400000a = ((*(volatile unsigned short *) 0x0400000a & 0x43) | 0x0700);
    p->unk_05 = 0;
    func_ov093_0229957c((void *) p);
}

void func_ov093_02299630(UnkStruct_02299630 *self)
{
    int t;
    unsigned int v;

    func_ov093_02299048(self);
    switch (self->state) {
        case 1:
            self->state = 2;
            func_02002708(4);
            func_02002708(0);
            func_0200284c(4, 8, -0xc0);
            func_0200284c(0, 8, -0xc0);
            func_ov093_02299514(self);
            break;
        case 2:
            func_ov093_022990b8(self, 1);
            break;
        case 3:
            func_ov093_022990b8(self, 0);
            func_02002708(0);
            func_020019dc(2, 0x21, 0);
            func_ov093_02298fdc(self);
            self->state = 5;
            break;
        case 4:
            func_ov093_022990b8(self, 0);
            func_02002708(0);
            func_ov093_02298fdc(self);
            self->state = 6;
            break;
        case 5:
            func_ov093_022990b8(self, 0);
            v = self->unk_06;
            if (v < 0x48) {
                if (v >= 0x10) {
                    if (v < 0x38) {
                        v = 0x10;
                    } else {
                        v = 0x48 - v;
                    }
                }
                self->unk_06++;
                func_020019dc(2, 0x21, v);
            } else {
                func_ov093_02299490((int) self);
                func_020019cc();
                func_ov093_02298f84(self, 8);
            }
            break;
        case 6:
            func_ov093_022990b8(self, 0);
            self->unk_0C = self->unk_0C + self->unk_14;
            t = self->unk_0C >> 12;
            if (t >= 0) {
                t = 0;
                self->unk_06 = 0x10;
                func_02001ba4(1);
                func_02001d1c(0x1f);
                self->state = 5;
            } else {
                func_02002808(0, 0, -t, 0xfe, 0xbf);
            }
            func_0200284c(0, 0, t);
            break;
    }
}

void func_ov093_022995b0(void *base)
{
    if (func_ov093_02298fac((char *) base + 0x820, 2) != 0) {
        if (func_020b9bbc((char *) base + 0x24d8, (char *) base + 0x828, 4, 0x800, 0) != 0) {
            func_ov093_02298f9c((char *) base + 0x820, 2);
        }
    }
    if (func_ov093_02298fac((char *) base + 0x18, 2) != 0) {
        if (func_020b9bbc((char *) base + 0x24fc, (char *) base + 0x20, 0, 0x800, 0) != 0) {
            func_ov093_02298f9c((char *) base + 0x18, 2);
        }
    }
}

void func_ov093_0229959c(int arg)
{
    func_ov093_02299490(arg);
    func_ov093_02299048((UnkStruct_02299630 *) arg);
}

void func_ov093_0229957c(void *src)
{
    func_02064af4(data_ov093_0229991c, (char *) src + 0x1028, 0x800);
}

void func_ov093_02299514(void *self)
{
    int r4;
    r4 = data_021fbe94;
    func_02002d14(data_ov093_02299880, r4, 4, 1, 1, 3);
    func_02002d14(data_ov093_02299880, r4, 0, 1, 1, 3);
    func_02002c6c(data_ov093_02299884, r4, 4, 0x10, 0x10, 0x10);
    func_02002c6c(data_ov093_02299884, r4, 0, 0x10, 0x10, 0x10);
}

void func_ov093_022994ac(UnkStruct_022994ac *self, int arg1)
{
    volatile unsigned short v1;
    volatile unsigned short v2;

    self->unk_10 = arg1;
    self->unk_14 = 0x2000;
    self->unk_08 = 0;
    func_ov093_02298fbc(self->unk_18);
    func_ov093_02298fbc(self->unk_820);
    v1 = self->unk_1028;
    MIi_CpuClear16(v1, self->unk_20, 0x800);
    v2 = self->unk_1028;
    MIi_CpuClear16(v2, self->unk_828, 0x800);
    self->unk_05 = 1;
}

void func_ov093_02299490(int param)
{
    int r4 = param;
    func_0200277c(4);
    func_0200277c(0);
    ((unsigned char *) r4)[5] = 0;
}

void func_ov093_02299424(UnkStruct_02299424 *s)
{
    int val;

    func_0200277c(0);
    val = func_02001b60();
    *(volatile unsigned int *) 0x04000000 = (*(volatile unsigned int *) 0x04000000 & 0xffffe0ff) | (val << 8);
    func_02001bb4(1);
    func_02001da0(0x1f);
    func_02001d1c(0x1d);
    func_02002808(0, 0, 0x78, 0xfe, 0xbf);
    func_0200284c(0, 0, ~0x77);
    s->unk_05 = 4;
    s->unk_06 = 0;
    s->unk_0C = 0xfff88000;
}

int func_ov093_02299418(int p)
{
    return func_ov093_02298f8c(p, 8);
}

void func_ov093_022993c0(char *a1, int a2, int a3)
{
    int count;
    char *p;

    if (a3 < 0) {
        return;
    }
    count = (a3 >> 3) + 1;
    if (a2 == 4) {
        p = a1 + 0x820;
    } else {
        p = a1 + 0x18;
    }
    while (count > *(short *) p) {
        func_ov093_022990e8(a1, a2, p);
        func_ov093_02298fa4(p, 2);
    }
    func_0200284c(a2, 8, a3 - 0xc0);
}

void func_ov093_0229939c(void *arg0, void *arg1, int arg2)
{
    volatile unsigned short local;
    local = *(unsigned short *) ((char *) arg0 + 0x1028);
    MIi_CpuClear16(local, (char *) arg1 + (arg2 << 6), 0x40);
}

void func_ov093_0229937c(void *dst, const void *src, int a, int b)
{
    MIi_CpuCopy16((char *) dst + 0x1028 + (a << 6), (char *) src + (b << 6), 0x40);
}

int func_ov093_02299338(void *self, int param)
{
    int result;
    unsigned char byte;
    void *ptr;

    result = _s32_div_f(param, 6);
    byte = (unsigned char) result;
    ptr = &byte;
    func_020b4a20((char *) self + 0x1828, ptr, (void *) data_ov093_0229990c);
    return func_020a7bf4((char *) self + 0x183a, param - result * 6);
}
