/* cloth_slots: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205d724 @ 0x0205d724, 0x28 bytes, Thumb
 * func_0205d70c @ 0x0205d70c, 0x18 bytes, Thumb
 * func_0205d6fc @ 0x0205d6fc, 0x10 bytes, Thumb
 * func_0205d6b4 @ 0x0205d6b4, 0x48 bytes, Thumb
 * func_0205d690 @ 0x0205d690, 0x24 bytes, Thumb
 * func_0205d5f0 @ 0x0205d5f0, 0xa0 bytes, Thumb
 * func_0205d5b0 @ 0x0205d5b0, 0x40 bytes, Thumb
 * func_0205d5a8 @ 0x0205d5a8, 0x6 bytes, Thumb
 * func_0205d5a4 @ 0x0205d5a4, 0x4 bytes, Thumb
 * func_0205d598 @ 0x0205d598, 0xa bytes, Thumb
 * func_0205d58c @ 0x0205d58c, 0xa bytes, Thumb
 * func_0205d528 @ 0x0205d528, 0x64 bytes, Thumb
 * func_0205d520 @ 0x0205d520, 0x6 bytes, Thumb
 * func_0205d51c @ 0x0205d51c, 0x2 bytes, Thumb
 * func_0205d4f0 @ 0x0205d4f0, 0x2c bytes, Thumb
 * func_0205d4e8 @ 0x0205d4e8, 0x6 bytes, Thumb
 * func_0205d4e4 @ 0x0205d4e4, 0x4 bytes, Thumb
 * func_0205d3d4 @ 0x0205d3d4, 0x110 bytes, Thumb
 * func_0205d36c @ 0x0205d36c, 0x68 bytes, Thumb
 * func_0205d270 @ 0x0205d270, 0xfc bytes, Thumb
 * func_0205d25c @ 0x0205d25c, 0x14 bytes, Thumb
 */

#include "types.h"

struct _S {
    unsigned char pad_00[0x28];
    unsigned short arr[10];
    unsigned char unk_3C[1];
};

typedef struct {
    unsigned long a[64];
} UnkStruct_0205d5a8;

typedef struct {
    unsigned char pad_00[0x28];
    unsigned short arr[8];
} UnkStruct_0205d598;

typedef struct {
    unsigned char pad_00[0x28];
    unsigned short arr[8];
} UnkStruct_0205d58c;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205d520;

typedef struct {
    unsigned char unk_00;
} UnkStruct_0205d4e8;

extern void func_0205c7b4(int);
extern int func_020e9abc(void *);
extern unsigned char data_021c9af4[];
extern unsigned char data_021c9d1c[];
extern void func_0205c798(void);
extern int __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02034ce0(void *);
extern void func_020051b0(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern unsigned char func_020b65c4(void);
extern u32 func_020b5e04(unsigned int);
extern u32 func_020b5df8(unsigned int);
extern u32 func_02085f08(void);
extern u32 func_0203cfc0(void);
extern u32 func_020e9968(void *a, u32 b, int c);
extern void *data_020ccf94;
extern void func_020e9b9c(void *);
extern int func_0204bcdc(void *);
extern int func_0204bc64(void *);
extern int func_0203cfb8(void *x, unsigned short *y, int z);
extern unsigned int data_021c9d00;
extern unsigned short data_021c9cfc;
extern char data_021c9d04;
extern int func_0203cfb0(void *x, void *y);
extern void __register_global_object(void *, void *, void *);
extern void MI_CpuCopy8(void *a, void *b, int n);

void func_0205d5f0(u32 *p);
void func_0205d5b0(void *self);
int func_0205d5a4(int p0);
void func_0205d520(UnkStruct_0205d520 *p);
void func_0205d51c(void *object);
void func_0205d4f0(int arg, int argument1);
void func_0205d4e8(UnkStruct_0205d4e8 *p);
void func_0205d4e4(unsigned char *p0, int p1);
void func_0205d3d4(unsigned char *a, unsigned short *b, int c, int d, int e);
void func_0205d270(unsigned char *a, int k);

void func_0205d724(int argument0)
{
    void *condition_value0;
    unsigned int *ptr;

    func_0205c7b4((int) argument0);
    func_0205d5f0((u32 *) ((void *) data_021c9d1c));
    ptr = (unsigned int *) data_021c9af4;
    if ((condition_value0 = (void *) (*ptr)) != 0) {
        func_020e9abc(condition_value0);
    }
}

void func_0205d70c(void)
{
    func_0205d5b0((void *) data_021c9d1c);
    func_0205c798();
}

int func_0205d6fc(void)
{
    return func_0205d5a4((int) (((unsigned char *) data_021c9d1c)));
}

struct _S *func_0205d6b4(struct _S *p)
{
    __cxa_vec_ctor((void *) (p->arr), 10, 2, (void (*)(void *)) func_02034ce0, (void (*)(void *)) func_020051b0);
    func_0205d520((UnkStruct_0205d520 *) (&p->unk_3C[0]));
    {
        int i;
        for (i = 0; i < 10; i++) {
            p->arr[i] = 0xfff1;
        }
    }
    return p;
}

void *func_0205d690(void *p)
{
    func_0205d51c((void *) ((char *) p + 0x3c));
    __cxa_vec_cleanup((void *) ((void *) ((char *) p + 0x28)), 0xa, 2, (void (*)(void *)) func_020051b0);
    return p;
}

void func_0205d5f0(u32 *p)
{
    void *gA = (*(void * *) data_021c9af4);
    u32 r4 = ((u8 *) data_020ccf94)[0x6c];
    u32 r6;

    r6 = func_020b5e04((unsigned int) func_020b65c4());
    if (r4 < r6) {
        r6 = r4;
    }

    for (r4 = 0; r4 < r6; r4++) {
        p[r4] = func_020e9968(gA, func_0203cfc0(), 4);
    }
    p[4] = func_020e9968(gA, func_0203cfc0(), 4);

    if (r6 == 0) {
        r6 = 1;
    }

    r4 = func_020b5df8((unsigned int) func_020b65c4());
    r6 = r4 + func_02085f08() - r6;

    for (r4 = 5; r4 < r6 + 5; r4++) {
        p[r4] = func_020e9968(gA, func_0203cfc0(), 4);
    }

    func_0205d4f0((int) ((u8 *) p + 0x3c), 4);
}

void func_0205d5b0(void *self)
{
    void *condition_value0;
    volatile unsigned char scratch[8];
    int i;

    (void) &scratch;
    func_0205d4e8((UnkStruct_0205d4e8 *) ((char *) self + 0x3c));
    for (i = 0; i < 10; i++) {
        ((int *) self)[i] = 0;
        *(unsigned short *) ((char *) self + i * 2 + 0x28) = 0xfff1;
    }
    if ((condition_value0 = (void *) ((*(int *) data_021c9af4))) != 0) {
        func_020e9b9c(condition_value0);
    }
}

unsigned long func_0205d5a8(UnkStruct_0205d5a8 *p, int i)
{
    return p->a[i];
}

int func_0205d5a4(int p0)
{
    return ((int) (p0) + (60));
}

void func_0205d598(unsigned short *dst, UnkStruct_0205d598 *p, int i)
{
    *dst = p->arr[i];
}

void func_0205d58c(UnkStruct_0205d58c *p, int i, unsigned short *v)
{
    p->arr[i] = *v;
}

static __inline int EqA(void *a, void *b)
{
    if (func_0204bc64(a) == func_0204bc64(b)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 a, u16 b)
{
    if (a == b) {
        return 1;
    }
    return 0;
}

int func_0205d528(void *self, u16 *key)
{
    void *ptr;
    int i;
    int r;

    for (i = 0; i < 10; i++) {
        ptr = (char *) self + 0x28 + (i << 1);
        if (func_0204bcdc(ptr)) {
            r = EqA(ptr, key);
        } else {
            r = EqB(*(u16 *) ((char *) self + (i << 1) + 0x28), *key);
        }
        if (r != 0) {
            return i;
        }
    }
    return 10;
}

void func_0205d520(UnkStruct_0205d520 *p)
{
    p->unk_00 = 10;
}

void func_0205d51c(void *object) {}

void func_0205d4f0(int arg, int argument1)
{
    unsigned short s;

    func_0205d4e4((unsigned char *) arg, (int) argument1);
    s = 0xFFF1;
    func_0205d3d4((unsigned char *) arg, &s, 0, 0, 0);
}

void func_0205d4e8(UnkStruct_0205d4e8 *p)
{
    p->unk_00 = 10;
}

void func_0205d4e4(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_0205d3d4(unsigned char *a, unsigned short *b, int c, int d, int e)
{
    unsigned char byte = *a;
    unsigned short local;
    int r4, r2, r1;
    int r;
    int st;

    if (*b == 0xfff1) {
        func_0205d58c((UnkStruct_0205d58c *) (((char *) data_021c9d1c)), (unsigned char) byte, b);
    }

    r4 = 1;
    r2 = r4;
    r1 = 0;

    if (*b >= 0x12a8 && *b <= 0x12af) {
        r1 = r4;
    }

    if (r1 == 0) {
        if (!(*b >= 0x1429 && *b <= 0x1430)) {
            r2 = 0;
        }
    }

    if (r2 == 0) {
        if (!(*b >= 0x13a0 && *b <= 0x13a7)) {
            r4 = 0;
        }
    }

    if (e == 0 && r4 == 0) {
        func_0205d598(&local, (UnkStruct_0205d598 *) (((char *) data_021c9d1c)), (unsigned char) byte);
        if (func_0204bcdc(b)) {
            r = EqA(b, &local);
        } else {
            r = EqB(*b, local);
        }
        if (r != 0) {
            return;
        }
    }

    if (d != 0 && r4 == 0) {
        st = func_0205d528(((char *) data_021c9d1c), (u16 *) b);
        if (st != 10) {
            func_0205d270(a, st);
            return;
        }
    }

    if (func_0203cfb8((void *) func_0205d5a8((UnkStruct_0205d5a8 *) (((char *) data_021c9d1c)), (unsigned char) byte), b, c) != 0) {
        func_0205d58c((UnkStruct_0205d58c *) (((char *) data_021c9d1c)), (unsigned char) byte, b);
    }
}

void func_0205d36c(unsigned char *p, void *param1)
{
    unsigned char b = *p;

    if (func_0203cfb0((void *) func_0205d5a8((UnkStruct_0205d5a8 *) (((char *) data_021c9d1c)), (unsigned char) b), param1) != 0) {
        if ((data_021c9d00 & 1) == 0) {
            data_021c9cfc = 0xffff;
            __register_global_object((void *) (&data_021c9cfc), (((void *) func_020051b0)), (void *) (&data_021c9d04));
            data_021c9d00 |= 1;
        }
        func_0205d58c((UnkStruct_0205d58c *) (((char *) data_021c9d1c)), (unsigned char) b, &data_021c9cfc);
    }
}

void func_0205d270(unsigned char *a, int k)
{
    u16 loc[2];
    unsigned char byte;
    int f;
    u16 a0, a1;
    int r;
    void *p1, *p2;

    byte = *a;
    if (k == byte) {
        return;
    }

    func_0205d598(&loc[0], (UnkStruct_0205d598 *) (((char *) data_021c9d1c)), k);
    func_0205d598(&loc[1], (UnkStruct_0205d598 *) (((char *) data_021c9d1c)), byte);

    f = 0;
    a0 = *(volatile u16 *) &loc[0];
    a1 = *(volatile u16 *) &loc[0];
    if (a1 >= 0x12a8 && a0 <= 0x12af) {
        f = 1;
    }
    if (f != 0) {
        if (a0 >= 0x1429 && a0 <= 0x1430) {
            f = 1;
        } else {
            f = 0;
        }
        if (f != 0) {
            if (a0 >= 0x13a0 && a0 <= 0x13a7) {
                f = 1;
            } else {
                f = 0;
            }
            if (f != 0) {
                goto skip;
            }
        }
    }

    if (func_0204bcdc(&loc[0]) != 0) {
        if (func_0204bc64(&loc[0]) == func_0204bc64(&loc[1])) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (loc[0] == loc[1]) {
            r = 1;
        } else {
            r = 0;
        }
    }
    if (r != 0) {
        return;
    }

skip:
    p1 = (void *) func_0205d5a8((UnkStruct_0205d5a8 *) (((char *) data_021c9d1c)), k);
    p2 = (void *) func_0205d5a8((UnkStruct_0205d5a8 *) (((char *) data_021c9d1c)), byte);
    if (p1 == 0) {
        return;
    }
    if (p2 == 0) {
        return;
    }
    MI_CpuCopy8(p1, p2, (int) func_0203cfc0());
    func_0205d58c((UnkStruct_0205d58c *) (((char *) data_021c9d1c)), (unsigned char) byte, &loc[0]);
}

int func_0205d25c(unsigned char *param)
{
    return (int) func_0205d5a8((UnkStruct_0205d5a8 *) (((char *) data_021c9d1c)), (unsigned char) (*param));
}
