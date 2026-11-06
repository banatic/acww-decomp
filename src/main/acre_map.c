/* acre_map: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204dde0 @ 0x0204dde0, 0x34 bytes, Thumb
 * func_0204dd84 @ 0x0204dd84, 0x5c bytes, Thumb
 * func_0204dd78 @ 0x0204dd78, 0xc bytes, Thumb
 * func_0204dcb8 @ 0x0204dcb8, 0xc0 bytes, Thumb
 * func_0204dc9c @ 0x0204dc9c, 0x1c bytes, Thumb
 * func_0204dc88 @ 0x0204dc88, 0x14 bytes, Thumb
 * func_0204dc34 @ 0x0204dc34, 0x54 bytes, Thumb
 * func_0204dbe4 @ 0x0204dbe4, 0x50 bytes, Thumb
 * func_0204dafc @ 0x0204dafc, 0xe8 bytes, Thumb
 * func_0204daac @ 0x0204daac, 0x50 bytes, Thumb
 * func_0204da74 @ 0x0204da74, 0x36 bytes, Thumb
 * func_0204da48 @ 0x0204da48, 0x2c bytes, Thumb
 * func_0204da2c @ 0x0204da2c, 0x1a bytes, Thumb
 * func_0204d9d8 @ 0x0204d9d8, 0x54 bytes, Thumb
 * func_0204d9ac @ 0x0204d9ac, 0x2c bytes, Thumb
 * func_0204d960 @ 0x0204d960, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    void *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned char pad_0C[0x10];
    int unk_1C;
} UnkStruct_0204dd84;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
} UnkStruct_0204dcb8;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_0204dcb8_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char pad_14[8];
    int unk_1C;
    int unk_20;
} UnkStruct_0204dc88;

struct UnkStruct_0204dc34 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
};

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_0204dafc;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
} UnkStruct_0204dafc_2;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x18];
    int unk_1C;
    void *unk_20;
} UnkStruct_0204da74;

struct Pair {
    int a;
    int b;
};

extern void func_020e9b9c(int *ptr);
extern int *data_021c9b34;
extern int *data_021c80e0[5];
extern int func_02037e84(void *x);
extern int func_0203750c(void);
extern int func_020377d8(int a, void *g);
extern void func_02037ecc(void *x, int a, int b, int c);
extern void func_02030bac(unsigned int param);
extern int func_02037e90(int a, int b, int c);
extern UnkStruct_0204dcb8_2 *func_02060eac(int *table, int key1, int key2);
extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern int func_02030ddc(int a, int b, int c, int d);
extern void func_02037f28(int a, int b, int *local, int c, int d, int e, int f, int g, int h, int i, int j);
extern int data_021ebcd4;
extern int data_020ca0ec;
extern int data_020ca0e8;
extern void func_020e993c(void *a, void *b);
extern struct UnkStruct_0204dc34 *func_0204f86c(int, int);
extern int func_0207cec0(int *, int);
extern int func_0207ffac(int object);
extern int data_021e5a2c;
extern int func_0207ffdc(void *arg, int *a, int *b);
extern int func_0204d7f8(void *a, int v1, int v2, void *c);
extern void func_0207f4c8(void *res, void *a);
extern int func_0204d858(int a, int b);
extern int func_0203776c(int a, int b);
extern int data_021c80cc;
extern int func_020e9958(int, int);
extern void *data_021c80c8;
extern void *func_020e9948(int, int);
extern void func_0204d934(int a, int b);
extern u32 data_020cb764[4][2];
extern u32 func_02064b2c(u32 a, u32 b, u32 c, u32 *d);

void func_0204dd84(UnkStruct_0204dd84 *p);
int func_0204dbe4(void *a, void *b, void *c);
void func_0204da48(int param);
void func_0204d9ac(int param);
int func_0204d960(u32 *dst, u32 arg);

void func_0204dde0(void)
{
    int i;
    func_020e9b9c(data_021c9b34);
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] != 0) {
            func_0204dd84((UnkStruct_0204dd84 *) data_021c80e0[i]);
        }
    }
}

void func_0204dd84(UnkStruct_0204dd84 *p)
{
    void *x;
    unsigned int z = 0;
    func_02030ddc(p->unk_04, p->unk_08, 0, p->unk_1C);
    if (p->unk_04 > z && p->unk_08 > z && p->unk_00 != 0) {
        x = p->unk_00;
    } else {
        x = 0;
    }
    if (x != 0) {
        int a = func_02037e84(x);
        void *g = (*(void **) &data_021c9b34);
        func_0203750c();
        func_02037ecc(x, 0, func_020377d8(a, g), p->unk_1C);
    }
}

void func_0204dd78(unsigned int *ptr)
{
    func_02030bac(ptr[7]);
}

int func_0204dcb8(UnkStruct_0204dcb8 *p, int key1, int key2)
{
    UnkStruct_0204dcb8_2 *q;
    int arr[6];
    int result = 0;

    p->unk_1C = key1 + 2;
    if (p->unk_00 == 0) {
        p->unk_00 = func_02037e90(1, key2, 4);
    }
    q = func_02060eac(&data_021ebcd4, key1, key2);
    if (p->unk_00 != 0 && q != 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        p->unk_04 = 1;
        p->unk_08 = 1;
        p->unk_14 = data_020ca0ec;
        p->unk_18 = data_020ca0e8;
        func_0204f800(&p->unk_0C, &p->unk_10, p->unk_04, p->unk_08, 0, 0);
        func_02030ddc(p->unk_04, p->unk_08, 0, p->unk_1C);
        arr[0] = 0;
        arr[2] = 0;
        arr[3] = 0;
        arr[4] = arr[1];
        arr[5] = 0;
        func_02037f28(p->unk_00, q->unk_00, &arr[3], q->unk_04, q->unk_08, q->unk_0C, 0, 0, 0, 0, p->unk_1C);
        func_020e993c((void *) key2, (void *) q);
        result = 1;
    }
    return result;
}

void func_0204dc9c(void *a, void *b)
{
    void *p;
    void *q;

    p = *(void **) a;
    if (p != 0) {
        func_020e993c(b, p);
        *(void **) a = 0;
    }
}

void func_0204dc88(UnkStruct_0204dc88 *s)
{
    s->unk_04 = 0;
    s->unk_08 = 0;
    s->unk_0C = 0;
    s->unk_10 = 0;
    s->unk_00 = 0;
    s->unk_1C = 7;
    s->unk_20 = 0;
}

struct UnkStruct_0204dc34 *func_0204dc34(int a, int b, int c)
{
    int forwarded_value;

    struct UnkStruct_0204dc34 *p;
    p = func_0204f86c(1, c);
    if (p) {
        if ((forwarded_value = (int) func_0207cec0(&data_021e5a2c, b))) {
            p->unk_00 = func_0207ffac((int) forwarded_value);
        } else {
            p->unk_00 = 0x1010;
        }
        func_0204dbe4((void *) a, (void *) b, (void *) c);
        p->unk_04 = a;
        p->unk_08 = 0;
        p->unk_0C = 0;
    }
    return p;
}

int func_0204dbe4(void *a, void *b, void *c)
{
    int v1 = 2;
    void *ptr;
    int v2 = 0;
    int ret = 0;

    ptr = (void *) func_0207cec0((int *) (&data_021e5a2c), (int) b);
    if (ptr != 0) {
        func_0207ffdc(ptr, &v1, &v2);
    }
    if (ptr != 0) {
        if (func_0204d7f8(a, v1, v2, c) != 0) {
            func_0207f4c8(ptr, a);
            ret = 1;
        }
    }
    return ret;
}

int func_0204dafc(UnkStruct_0204dafc *p, int key1, int key2)
{
    UnkStruct_0204dafc_2 *q;
    int arr[6];
    int t;
    int result = 0;

    p->unk_1C = 7;
    if (p->unk_00 == 0) {
        p->unk_00 = func_02037e90(1, key2, -4);
    }
    if (p->unk_20 == 0) {
        p->unk_20 = func_0204d858(key2, -4);
    }
    q = (UnkStruct_0204dafc_2 *) func_0204dc34(p->unk_20, key1, key2);
    if (p->unk_00 != 0 && q != 0 && p->unk_20 != 0) {
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        p->unk_04 = 1;
        p->unk_08 = 1;
        p->unk_14 = data_020ca0ec;
        p->unk_18 = data_020ca0e8;
        func_0204f800(&p->unk_0C, &p->unk_10, p->unk_04, p->unk_08, 0, 0);
        func_02030ddc(p->unk_04, p->unk_08, 0, p->unk_1C);
        arr[0] = 0;
        arr[2] = 0;
        t = func_0203776c(func_0203750c(), q->unk_00);
        arr[3] = arr[0];
        arr[4] = arr[1];
        arr[5] = arr[2];
        func_02037f28(p->unk_00, q->unk_00, &arr[3], q->unk_04, q->unk_08, q->unk_0C, 0, t, 0, 0, p->unk_1C);
        func_020e993c((void *) key2, (void *) q);
        result = 1;
    }
    return result;
}

int func_0204daac(int a, int b)
{
    void *condition_value0;
    int ret = 0;
    if (data_021c80cc == 0) {
        data_021c80cc = func_020e9958(b, 0x24);
        if (data_021c80cc != 0) {
            if ((condition_value0 = (void *) (data_021c80cc)) != 0) {
                func_0204dc88((UnkStruct_0204dc88 *) condition_value0);
            }
            if (func_0204dafc((UnkStruct_0204dafc *) data_021c80cc, a, b) != 0) {
                ret = data_021c80cc;
            } else {
                func_0204da48(b);
            }
        }
    }
    return ret;
}

void func_0204da74(UnkStruct_0204da74 *p, void *q)
{
    if (p->unk_00 != 0) {
        func_020e993c(q, p->unk_00);
        p->unk_00 = 0;
    }
    if (p->unk_20 != 0) {
        func_020e993c(q, p->unk_20);
        p->unk_20 = 0;
    }
    func_02030bac(p->unk_1C);
}

void func_0204da48(int param)
{
    if (data_021c80cc) {
        func_0204da74((UnkStruct_0204da74 *) data_021c80cc, (void *) param);
        func_020e993c((void *) param, (void *) data_021c80cc);
        data_021c80cc = 0;
    }
}

void func_0204da2c(struct Pair *p)
{
    int i;
    for (i = 0; i < 4; i++) {
        p[i].a = 0;
        p[i].b = 0;
    }
}

int func_0204d9d8(int arg)
{
    int ret = 0;
    if (data_021c80c8 == 0) {
        void *p = func_020e9948(arg, 0x20);
        data_021c80c8 = p;
        if (p != 0) {
            if (p != 0) {
                func_0204da2c((struct Pair *) p);
            }
            if (func_0204d960((u32 *) data_021c80c8, arg) != 0) {
                ret = 1;
            } else {
                func_0204d9ac(arg);
                data_021c80c8 = 0;
            }
        }
    }
    return ret;
}

void func_0204d9ac(int param)
{
    if ((*(int *) &data_021c80c8)) {
        func_0204d934((*(int *) &data_021c80c8), param);
        func_020e993c((void *) param, (void *) ((*(int *) &data_021c80c8)));
        (*(int *) &data_021c80c8) = 0;
    }
}

int func_0204d960(u32 *dst, u32 arg)
{
    u32 *src = data_020cb764[0];
    u32 tmp = 0;
    int ok = 1;
    int i;

    for (i = 0; i < 4; i++) {
        dst[0] = func_02064b2c(*src, arg, 4, &tmp);
        if (dst[0] != 0) {
            dst[1] = tmp >> 1;
        } else {
            ok = 0;
            dst[1] = 0;
            break;
        }
        dst += 2;
        src += 2;
    }
    return ok;
}
