/* held_item_pool_2: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205f6f8 @ 0x0205f6f8, 0x44 bytes, Thumb
 * func_0205f6dc @ 0x0205f6dc, 0x1c bytes, Thumb
 * func_0205f6bc @ 0x0205f6bc, 0x20 bytes, Thumb
 * func_0205f698 @ 0x0205f698, 0x24 bytes, Thumb
 * func_0205f670 @ 0x0205f670, 0x28 bytes, Thumb
 * func_0205f64c @ 0x0205f64c, 0x24 bytes, Thumb
 * func_0205f644 @ 0x0205f644, 0x8 bytes, Thumb
 * func_0205f63c @ 0x0205f63c, 0x8 bytes, Thumb
 * func_0205f634 @ 0x0205f634, 0x8 bytes, Thumb
 * func_0205f630 @ 0x0205f630, 0x4 bytes, Thumb
 * func_0205f62c @ 0x0205f62c, 0x4 bytes, Thumb
 * func_0205f60c @ 0x0205f60c, 0x20 bytes, Thumb
 * func_0205f5ec @ 0x0205f5ec, 0x20 bytes, Thumb
 * func_0205f570 @ 0x0205f570, 0x7c bytes, Thumb
 * func_0205f524 @ 0x0205f524, 0x4c bytes, Thumb
 * func_0205f434 @ 0x0205f434, 0xf0 bytes, Thumb
 * func_0205f3b4 @ 0x0205f3b4, 0x80 bytes, Thumb
 * func_0205f2f8 @ 0x0205f2f8, 0xbc bytes, Thumb
 * func_0205f2f0 @ 0x0205f2f0, 0x6 bytes, Thumb
 * func_0205f2e8 @ 0x0205f2e8, 0x8 bytes, Thumb
 * func_0205f2e0 @ 0x0205f2e0, 0x8 bytes, Thumb
 * func_0205f2c8 @ 0x0205f2c8, 0x16 bytes, Thumb
 * func_0205f2bc @ 0x0205f2bc, 0xa bytes, Thumb
 * func_0205f2b0 @ 0x0205f2b0, 0xa bytes, Thumb
 * func_0205f298 @ 0x0205f298, 0x18 bytes, Thumb
 * func_0205f28c @ 0x0205f28c, 0xa bytes, Thumb
 * func_0205f280 @ 0x0205f280, 0xa bytes, Thumb
 * func_0205f274 @ 0x0205f274, 0xa bytes, Thumb
 * func_0205f240 @ 0x0205f240, 0x34 bytes, Thumb
 * func_0205f20c @ 0x0205f20c, 0x34 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x24];
    unsigned int arr[1];
} UnkStruct_0205f3b4;

struct UnkStruct_0205f2f8 {
    u8 data[0xf4];
};

struct UnkStruct_0205f2f8_2 {
    u8 data[0x14];
};

struct UnkStruct_0205f2f8_3 {
    u32 unk_00[9];
    void *p[9];
    u32 arr1[9];
    u16 h1[9];
    u16 pad_7E;
    u32 arr2[9];
    u16 h2[9];
    u8 pad_B6[0x26];
    struct UnkStruct_0205f2f8_2 b[9];
    u8 pad_190[0xfc];
    struct UnkStruct_0205f2f8 a[9];
    u32 arr3[9];
    u16 c[9];
};

typedef struct {
    unsigned long a[64];
} UnkStruct_0205f2f0;

typedef struct {
    char pad_00[0x48];
    int arr1[9];
    short arr2[1];
} UnkStruct_0205f2c8;

typedef struct {
    unsigned char pad_00[0x6c];
    unsigned short arr[4];
} UnkStruct_0205f2bc;

typedef struct {
    unsigned char pad_00[0x80];
    unsigned long arr[4];
} UnkStruct_0205f2b0;

typedef struct {
    unsigned char pad_00[0xa4];
    unsigned short arr[4];
} UnkStruct_0205f28c;

typedef struct {
    unsigned char pad_00[0xb8];
    unsigned long arr[4];
} UnkStruct_0205f280;

typedef struct {
    unsigned char pad_00[0xb8];
    unsigned long arr[4];
} UnkStruct_0205f274;

extern void func_0205c560(int);
extern unsigned int func_0205c440(int);
extern int func_020e9abc(void *);
extern int data_021c9ad8;
extern int data_021c9acc;
extern void func_0205c424(void);
extern void func_0205c544(void);
extern unsigned char data_021ca16c[];
extern char data_021ca120;
extern char data_020dd798;
extern int func_02064328(void *a, void *b, unsigned int c, unsigned int d);
extern unsigned char data_020cc8c0[];
extern unsigned int func_02062148(unsigned short *);
extern unsigned int func_02062230(void);
extern unsigned short data_020cc940[];
extern unsigned char data_020cc900[];
extern int data_021ca138;
extern int data_020dd780;
extern int data_021ca150;
extern int data_020dd768;
extern void func_02055ce8(void *);
extern void *func_02055cf4(void *);
extern void *func_02054e18(void *);
extern void *func_02054e54(void *);
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void *func_020ba01c(void *p);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_02085f08(void);
extern int func_02055c80(unsigned char *, unsigned int, unsigned int, unsigned int);
extern unsigned int func_020e9968(unsigned int, unsigned int, unsigned int);
extern unsigned char *data_020ccf94;
extern unsigned int func_020ea0e0(unsigned int, unsigned int);
extern int func_02055454(struct UnkStruct_0205f2f8 *);
extern void func_0205f0c0(struct UnkStruct_0205f2f8_3 *, int);
extern void func_02055b40(struct UnkStruct_0205f2f8_2 *);
extern void func_020e9b9c(void *);
extern int func_02064af4(int a, int b, int c);

void func_0205f434(unsigned int *param0);
void func_0205f3b4(UnkStruct_0205f3b4 *data);
void func_0205f2f8(struct UnkStruct_0205f2f8_3 *self);

void func_0205f6f8(int arg)
{
    void *condition_value0;
    void *condition_value1;
    func_0205c560(arg);
    func_0205f434((unsigned int *) (((int *) data_021ca16c)));
    if ((condition_value0 = (void *) (data_021c9ad8))) {
        func_020e9abc(condition_value0);
    }
    func_0205c440(arg);
    func_0205f3b4((UnkStruct_0205f3b4 *) (((int *) data_021ca16c)));
    if ((condition_value1 = (void *) (data_021c9acc))) {
        func_020e9abc(condition_value1);
    }
}

void func_0205f6dc(void)
{
    func_0205f2f8((struct UnkStruct_0205f2f8_3 *) ((void *) data_021ca16c));
    func_0205c424();
    func_0205c544();
}

void *func_0205f6bc(unsigned int p)
{
    func_02064328(&data_021ca120, &data_020dd798, p >> 5, p);
    return &data_021ca120;
}

unsigned char func_0205f698(unsigned short *argument0)
{
    unsigned int a, b;

    a = func_02062148((unsigned short *) argument0);
    b = func_02062230();
    if (a < b) {
        return data_020cc8c0[a];
    } else {
        return 0x32;
    }
}

unsigned int func_0205f670(unsigned short *argument0)
{
    unsigned int a;
    unsigned int b;
    a = func_02062148((unsigned short *) argument0);
    b = func_02062230();
    if (a < b) {
        return data_020cc940[a];
    } else {
        return 0x144;
    }
}

int func_0205f64c(unsigned short *argument0)
{
    unsigned int first, second;
    first = func_02062148((unsigned short *) argument0);
    second = func_02062230();
    if (first < second) {
        return data_020cc900[first];
    } else {
        return 0x2b;
    }
}

int func_0205f644(void)
{
    return 3876;
}

int func_0205f63c(void)
{
    return 2204;
}

int func_0205f634(void)
{
    return 1536;
}

int func_0205f630(void)
{
    return 0;
}

int func_0205f62c(void)
{
    return 80;
}

void *func_0205f60c(unsigned int arg)
{
    func_02064328(&data_021ca138, &data_020dd780, arg >> 5, arg);
    return &data_021ca138;
}

void *func_0205f5ec(unsigned int arg)
{
    func_02064328(&data_021ca150, &data_020dd768, arg >> 5, arg);
    return &data_021ca150;
}

void *func_0205f570(void *self)
{
    char *p, *q;

    __cxa_vec_ctor((void *) ((char *) self + 0xdc), 9, 0x14, (((void (*)(void *)) func_02055cf4)),
                   (void (*)(void *)) func_02055ce8);

    p = (char *) self + 0x190;
    q = (char *) self + 0x28c;

    do {
        func_020ba01c(p);
        p += 0x1c;
    } while (p != q);

    __cxa_vec_ctor((void *) (q), 9, 0xf4, (((void (*)(void *)) func_02054e54)), (((void (*)(void *)) func_02054e18)));
    __cxa_vec_ctor((void *) ((char *) self + 0xb44), 9, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);

    return self;
}

void *func_0205f524(void *p)
{
    __cxa_vec_cleanup((void *) ((char *) p + 0xb44), 9, 2, (void (*)(void *)) func_020051b0);
    __cxa_vec_cleanup((void *) ((char *) p + 0x28c), 9, 0xf4, (((void (*)(void *)) func_02054e18)));
    __cxa_vec_cleanup((void *) ((char *) p + 0xdc), 9, 0x14, (void (*)(void *)) func_02055ce8);
    return p;
}

void func_0205f434(unsigned int *param0)
{
    unsigned char cnt;
    unsigned int i;
    unsigned int count;
    unsigned int countOrOne;
    unsigned int a, b;
    unsigned int end;
    unsigned int g;
    unsigned int r1, r2, r3;

    cnt = data_020ccf94[0x6c];
    count = func_020b5e04((unsigned int) func_020b65c4());
    if (cnt < count) {
        count = cnt;
    }

    if (count != 0) {
        countOrOne = count;
    } else {
        countOrOne = 1;
    }

    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    end = (a + b) - countOrOne;

    for (i = 0; i < count; i++) {
        r1 = (unsigned int) func_0205f634();
        r2 = (unsigned int) func_0205f630();
        r3 = (unsigned int) func_0205f62c();
        func_02055c80((unsigned char *) param0 + 0xdc + i * 0x14, r1, r2, r3);
    }

    for (i = 4; i < end + 4; i++) {
        r1 = (unsigned int) func_0205f634();
        r2 = (unsigned int) func_0205f630();
        r3 = (unsigned int) func_0205f62c();
        func_02055c80((unsigned char *) param0 + 0xdc + i * 0x14, r1, r2, r3);
    }

    g = (*(unsigned int *) &data_021c9ad8);

    for (i = 0; i < count; i++) {
        param0[i] = func_020e9968(g, (unsigned int) func_0205f644(), 4);
    }

    for (i = 4; i < end + 4; i++) {
        param0[i] = func_020e9968(g, (unsigned int) func_0205f644(), 4);
    }
}

void func_0205f3b4(UnkStruct_0205f3b4 *data)
{
    unsigned int g = (*(unsigned int *) &data_021c9acc);
    unsigned char cnt = data_020ccf94[0x6C];
    unsigned int i;
    unsigned int count;
    unsigned int a;
    unsigned int b;
    unsigned int end;
    count = func_020b5e04((unsigned int) func_020b65c4());
    if (cnt < count) {
        count = cnt;
    }
    for (i = 0; i < count; i++) {
        data->arr[i] = func_020ea0e0((unsigned int) func_0205f63c(), g);
    }

    if (count == 0) {
        count = 1;
    }
    a = func_020b5df8((unsigned int) func_020b65c4());
    b = func_02085f08();
    end = (a + b) - count;
    end = end + 4;
    for (i = 4; i < end; i++) {
        data->arr[i] = func_020ea0e0((unsigned int) func_0205f63c(), g);
    }
}

void func_0205f2f8(struct UnkStruct_0205f2f8_3 *self)
{
    int i;

    for (i = 0; i < 9; i++) {
        func_02055454(&self->a[i]);
        func_0205f0c0(self, i);
        func_02055b40(&self->b[i]);
        self->c[i] = 0xfff1;
    }

    for (i = 0; i < 9; i++) {
        if (self->p[i] != 0) {
            func_020e9b9c(self->p[i]);
            self->p[i] = 0;
            self->arr1[i] = 0;
            self->h1[i] = 0;
            self->arr2[i] = 0;
            self->h2[i] = 0;
            self->arr3[i] = 0;
        }
    }

    if ((*(void * *) &data_021c9acc) != 0) {
        func_020e9b9c((*(void * *) &data_021c9acc));
    }

    for (i = 0; i < 9; i++) {
        self->unk_00[i] = 0;
    }

    if ((*(void * *) &data_021c9ad8) != 0) {
        func_020e9b9c((*(void * *) &data_021c9ad8));
    }
}

unsigned long func_0205f2f0(UnkStruct_0205f2f0 *p, int i)
{
    return p->a[i];
}

int func_0205f2e8(int p0, int p1)
{
    return *(int *) ((char *) (((int) (p0) + ((p1 << 2)))) + (36));
}

int func_0205f2e0(int p0, int p1)
{
    return *(int *) ((char *) (((int) (p0) + ((p1 << 2)))) + (72));
}

void func_0205f2c8(UnkStruct_0205f2c8 *s, int index, int val1, short val2)
{
    s->arr1[index] = val1;
    s->arr2[index] = val2;
}

unsigned short func_0205f2bc(UnkStruct_0205f2bc *p, int i)
{
    return p->arr[i];
}

unsigned long func_0205f2b0(UnkStruct_0205f2b0 *p, int i)
{
    return p->arr[i];
}

void func_0205f298(void *r0, int r1, int r2, short r3)
{
    ((int *) ((char *) r0 + (r1 << 2) + 0x80))[0] = r2;
    *(short *) ((char *) r0 + (r1 << 1) + 0xa4) = r3;
}

unsigned short func_0205f28c(UnkStruct_0205f28c *p, int i)
{
    return p->arr[i];
}

unsigned long func_0205f280(UnkStruct_0205f280 *p, int i)
{
    return p->arr[i];
}

void func_0205f274(UnkStruct_0205f274 *p, int i, unsigned long v)
{
    p->arr[i] = v;
}

int func_0205f240(int a0, int a1, int a2)
{
    int v0 = func_0205f2e0((int) ((void *) data_021ca16c), a1);
    int v1 = (int) func_0205f2bc((UnkStruct_0205f2bc *) ((void *) data_021ca16c), a1);
    int v2 = (int) func_0205f60c(a2);
    int v3 = func_02064af4(v2, v0, v1);
    return v1 - v3;
}

int func_0205f20c(int unused, int b, int c)
{
    int t1 = (int) func_0205f2b0((UnkStruct_0205f2b0 *) (((char *) data_021ca16c)), b);
    int t2 = (int) func_0205f28c((UnkStruct_0205f28c *) (((char *) data_021ca16c)), b);
    int t3 = (int) func_0205f5ec(c);
    int t4 = func_02064af4(t3, t1, t2);
    return t2 - t4;
}
