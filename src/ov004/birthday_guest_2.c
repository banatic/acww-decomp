/* birthday_guest_2: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221e080 @ 0x0221e080, 0x5c bytes, Thumb
 * func_ov004_0221e048 @ 0x0221e048, 0x38 bytes, Thumb
 * func_ov004_0221e018 @ 0x0221e018, 0x30 bytes, Thumb
 * func_ov004_0221df94 @ 0x0221df94, 0x84 bytes, Thumb
 * func_ov004_0221df58 @ 0x0221df58, 0x3c bytes, Thumb
 * func_ov004_0221df34 @ 0x0221df34, 0x24 bytes, Thumb
 * func_ov004_0221df1c @ 0x0221df1c, 0x16 bytes, Thumb
 * func_ov004_0221defc @ 0x0221defc, 0x20 bytes, Thumb
 * func_ov004_0221ddf4 @ 0x0221ddf4, 0x108 bytes, Thumb
 * func_ov004_0221ddf0 @ 0x0221ddf0, 0x2 bytes, Thumb
 * func_ov004_0221ddec @ 0x0221ddec, 0x2 bytes, Thumb
 * func_ov004_0221dde8 @ 0x0221dde8, 0x2 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0221e080 {
    void *unk_00;
    u32 unk_04;
    u32 unk_08;
};

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0221e048;

struct UnkStruct_0221e018 {
    u8 pad_00[0x618];
    u8 sub[0x898 - 0x618];
    int phase;
};

typedef struct {
    int x, y, z;
} Vec3;

struct UnkStruct_0221df58_2 {
    u8 pad_00[0x830];
    int handle;
};

struct UnkStruct_0221df58 {
    u8 pad_00[0x1a4];
    struct UnkStruct_0221df58_2 *sub;
};

typedef struct {
    char pad_00[0x1a4];
    int unk_1A4;
} UnkStruct_0221defc;

typedef struct {
    int w[8];
} T20;

extern struct UnkStruct_0221e080 *data_021c80bc;
extern int func_02037e0c(void *, int, int, int);
extern int func_0204bc90(int tile);
extern void func_020308e0(int, int);
extern int func_020984e8(void);
extern int func_02099870(int arg);
extern int func_020804b8(int arg1, int arg2);
extern void func_02081e14(int arg1, int arg2, int arg3, int arg4);
extern int func_02014868(void *p);
extern int func_0203af80(Vec3 *v);
extern int func_0203b144(void);
extern int func_ov004_0221dd24(void *self, int a);
extern int func_020819bc(void *object);
extern void func_020819e0(unsigned short *argument0);
extern void func_0202dc3c(void *ptr, int value, int count);
extern int func_0208150c(int a);
extern int func_0200366c(int a, void *b, int c, void *d);
extern int func_ov004_0221d4c0(void);
extern int func_020644cc(int n);
extern int func_020b66b0(void);
extern int func_0207cee4(void *a, int b);
extern int func_0207cec0(char *a, int b);
extern void *func_02094fd4(T20 *o);
extern void *func_02094fbc(T20 *o);
extern void func_02015e10(char *a, int b, int c);
extern int data_ov004_02257be0;
extern int data_ov004_02253928;
extern int data_021dc7a8;
extern int data_021e5a2c;

void func_ov004_0221e080(void *receiver)
{
    struct UnkStruct_0221e080 *q;
    void *base;
    int y;
    int x;
    int zero;
    int tile;

    zero = 0;
    q = data_021c80bc;
    if (q->unk_04 > zero && q->unk_08 > zero && q->unk_00 != 0) {
        base = q->unk_00;
    } else {
        base = 0;
    }
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            if ((tile = func_02037e0c(base, x, y, zero)) != 0 && func_0204bc90(tile) != 0) {
                func_020308e0(x, y);
            }
        }
    }
}

void func_ov004_0221e048(UnkStruct_0221e048 *param)
{
    int a;
    int b;
    int c;

    a = func_020984e8();
    if (a == 0) {
        return;
    }
    if (param->unk_830 == 0) {
        return;
    }
    b = func_02099870(a);
    c = func_020804b8(param->unk_830, b);
    func_02081e14(c, 0, 0, 0);
}

int func_ov004_0221e018(struct UnkStruct_0221e018 *self)
{
    if (func_02014868(&self->sub)) {
        return 0;
    }
    if (self->phase <= 3) {
        return 1;
    }
    return 0;
}

void func_ov004_0221df94(char *self, unsigned int sel, int a2)
{
    Vec3 v;
    v.x = *(int *) (self + 0x5c);
    v.y = *(int *) (self + 0x60);
    v.z = *(int *) (self + 0x64);
    v.y = v.y + 0x2000;
    switch (sel) {
        case 3:
            *(u8 *) (self + 0x560) = (u8) a2;
            func_ov004_0221dd24(self, 4);
            break;
        case 0:
            *(u8 *) (self + 0x560) = (u8) a2;
            func_0203af80(&v);
            func_ov004_0221dd24(self, 5);
            break;
        case 8:
            func_ov004_0221e048((UnkStruct_0221e048 *) self);
            func_0203b144();
            func_ov004_0221dd24(self, 0);
            break;
        case 4:
            func_ov004_0221dd24(self, 0);
            break;
    }
}

int func_ov004_0221df58(struct UnkStruct_0221df58 *self)
{
    if (self->sub != 0 && self->sub->handle != 0) {
        return func_020804b8(self->sub->handle, func_02099870(func_020984e8()));
    }
    return 0;
}

int func_ov004_0221df34(void *arg0)
{
    int object;
    if ((object = func_ov004_0221df58((struct UnkStruct_0221df58 *) ((void *) arg0))) != 0) {
        if (func_020819bc((void *) object) == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void func_ov004_0221df1c(void *arg0)
{
    unsigned short *conditionInput0;

    if ((conditionInput0 = (unsigned short *) (func_ov004_0221df58((struct UnkStruct_0221df58 *) ((void *) arg0)))) != 0) {
        func_020819e0((unsigned short *) conditionInput0);
    }
}

void func_ov004_0221defc(UnkStruct_0221defc *obj, int val)
{
    func_0202dc3c(obj, val, 0x11);
    obj->unk_1A4 = val;
}

void func_ov004_0221ddf4(char *self, char *out)
{
    // DECLS
    T20 tmp;
    int k;
    int m;
    char *base;
    // ENDDECLS

    func_0200366c(func_0208150c(*(int *) (*(char **) (self + 0x1a4) + 0x830)), &data_ov004_02257be0, 0x28,
                  &data_ov004_02253928);
    *(int **) out = &data_ov004_02257be0;
    k = 2;
    if (func_ov004_0221df34((void *) self) != 0) {
        k = 0;
    } else if (func_ov004_0221d4c0() != 0) {
        k = 1;
    }
    func_ov004_0221df1c((void *) self);
    switch (k) {
        case 0:
            out[4] = (char) (func_020644cc(2) + 0x1a);
            break;
        case 1:
            out[4] = (char) (func_020644cc(4) + 0x1e);
            break;
        default:
            out[4] = (char) (func_020644cc(2) + 0x1c);
            break;
    }
    if (*(int *) (*(char **) (self + 0x1a4) + 0x8dc) != 0) {
        base = (char *) &data_021dc7a8;
        m = func_020b66b0();
        if (func_0207cee4(&data_021e5a2c, m) != 0) {
            func_02094fd4(&tmp);
            func_02015e10(*(char **) (self + 0x1a4) + 0x89c, func_0208150c(func_0207cec0(base + 0x9284, m)), 1);
            func_02094fbc(&tmp);
        }
        if (*(char **) (self + 0x1a4) != 0 && *(int *) (*(char **) (self + 0x1a4) + 0x830) != 0) {
            func_02015e10(*(char **) (self + 0x1a4) + 0x89c, func_0208150c(*(int *) (*(char **) (self + 0x1a4) + 0x830)), 0);
        }
    }
}

void func_ov004_0221ddf0(void) {}

void func_ov004_0221ddec(void) {}

void func_ov004_0221dde8(void) {}
