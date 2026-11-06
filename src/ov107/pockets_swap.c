/* pockets_swap: 15 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229c628 @ 0x0229c628, 0x48 bytes, Thumb
 * func_ov107_0229c5b0 @ 0x0229c5b0, 0x78 bytes, Thumb
 * func_ov107_0229c588 @ 0x0229c588, 0x26 bytes, Thumb
 * func_ov107_0229c4f0 @ 0x0229c4f0, 0x98 bytes, Thumb
 * func_ov107_0229c488 @ 0x0229c488, 0x68 bytes, Thumb
 * func_ov107_0229c414 @ 0x0229c414, 0x74 bytes, Thumb
 * func_ov107_0229c3c4 @ 0x0229c3c4, 0x4e bytes, Thumb
 * func_ov107_0229c378 @ 0x0229c378, 0x4a bytes, Thumb
 * func_ov107_0229c354 @ 0x0229c354, 0x24 bytes, Thumb
 * func_ov107_0229c2c8 @ 0x0229c2c8, 0x8c bytes, Thumb
 * func_ov107_0229c2b4 @ 0x0229c2b4, 0x12 bytes, Thumb
 * func_ov107_0229c2a4 @ 0x0229c2a4, 0xe bytes, Thumb
 * func_ov107_0229c294 @ 0x0229c294, 0xe bytes, Thumb
 * func_ov107_0229c208 @ 0x0229c208, 0x8c bytes, Thumb
 * func_ov107_0229c180 @ 0x0229c180, 0x88 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xBE];
    char unk_BE;
} Struct_ov107_0229c588;

typedef struct {
    char pad_00[0xb9];
    unsigned char unk_B9;
    char pad_BA[0xbe - 0xba];
    unsigned char unk_BE;
    char pad_BF[0xc0 - 0xbf];
    unsigned int unk_C0;
} UnkStruct_0229c4f0;

struct UnkStruct_0229c488 {
    char pad_00[0xc0];
    unsigned int unk_C0;
    char pad_C4[4];
    unsigned int unk_C8;
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
    int unk_68;
} Global;

typedef struct {
    char pad_00[0xac];
    int unk_AC;
    char pad_B0[0xb9 - 0xac - 4];
    unsigned char unk_B9;
    char pad_BA[0xcc - 0xba];
    int unk_CC;
    int unk_D0;
} UnkStruct_0229c414;

struct UnkStruct_0229c3c4;

struct UnkStruct_0229c3c4 {
    char pad_00[0xac];
    int unk_AC;
};

struct UnkStruct_0229c378 {
    char pad_00[0xb9];
    unsigned char b9;
    char pad_BA[0x12];
    int cc;
    int d0;
};

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0229c354;

struct UnkStruct_0229c2a4 {
    char pad_00[0x94];
    unsigned int unk_94;
};

extern void *data_020ccf94;
extern int func_02073d90(void *p);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, const void *buf, int len);
extern void func_02073770(void *p, int a, int b);
extern int func_0206fca4(void);
extern int func_ov003_022278e0(u8 *p, int x);
extern u8 *func_020961a8(int);
extern int func_0203162c(u8 *a, u8 *b, int c, int d, int e, int f);
extern short data_ov107_0229e280[];
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov107_0229d0f0(void *p, int a);
extern int func_ov003_0222780c(int a, int b, void *c);
extern void func_ov107_0229caa8(void *p);
extern void func_020779b8(char *dst, int a, int b);
extern void MI_CpuCopy8(char *dst, char *src, int count);
extern int func_02043d34(int a, int b, int c, int d);
extern void func_ov107_0229d480(void *self);
extern void func_ov107_0229d3a0(void *self, int a, int b);
extern unsigned short *func_02045b5c(int a);
extern int func_020436a8(int);
extern void func_020431b8(int);
extern void func_0204f794(void *out, int a, int b);
extern int func_ov003_02219b90(void *a, void *b);
extern int func_02073dd4(UnkStruct_0229c354 *obj, int val);
extern void func_02045d98(int key);
extern unsigned int *func_0206f7bc(void);
extern void func_ov003_0222e6c4(int a, int b);
extern int func_ov003_0222aae8(void *argument0);
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_0220ba0c(void *p);
extern void *func_ov002_02209ac8(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void *func_ov002_02207e28(void *p);
extern void *func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void *func_ov094_0229afe0(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern int data_ov107_0229e3b8;

void func_ov107_0229c4f0(UnkStruct_0229c4f0 *self);
void func_ov107_0229c488(struct UnkStruct_0229c488 *param0, int param1);
void func_ov107_0229c378(struct UnkStruct_0229c378 *p);
int func_ov107_0229c354(void *receiver);
void func_ov107_0229c2c8(int a, int b);

void func_ov107_0229c628(int arg0, int arg1, int arg2)
{
    if (func_02073d90(data_020ccf94)) {
        unsigned char buf[3];
        void *ctx;
        buf[0] = 1;
        buf[1] = arg1;
        buf[2] = arg2;
        ctx = data_020ccf94;
        func_02073820(ctx);
        func_020737f0(ctx, buf, 3);
        func_02073770(ctx, 0x16, 4);
    }
}

int func_ov107_0229c5b0(u8 *self)
{
    int t;
    int x;
    int i;
    int base;
    u8 *obj;
    u8 *sub;

    t = func_0206fca4();
    x = func_ov107_0229c354(self);
    if (t == 0x2c) {
        return func_ov003_022278e0(self + 0xc0, x);
    }

    obj = func_020961a8(4);
    sub = obj + 0x5c;
    i = 0;
    base = *(short *) (obj + 0x8e);
    for (; i < 8; i++) {
        if (func_0203162c(self + 0xc0, sub, (short) (base + data_ov107_0229e280[i]), 0x7800, 0xa00, 0xc) != 0) {
            return 1;
        }
    }
    return 0;
}

void func_ov107_0229c588(void *p)
{
    func_ov107_0229c2c8((int) p, 1);
    ((Struct_ov107_0229c588 *) p)->unk_BE = 5;
    func_ov002_02208098((void *) (p), 0x11);
    func_ov107_0229c4f0((UnkStruct_0229c4f0 *) p);
}

void func_ov107_0229c4f0(UnkStruct_0229c4f0 *self)
{
    if (self->unk_BE != 0) {
        self->unk_BE--;
        return;
    }
    {
        int r = func_ov107_0229c354(self);
        int w2 = func_ov107_0229d0f0(self, self->unk_B9);
        if (func_ov003_0222780c(r, w2, &self->unk_C0) != 0) {
            volatile u16 w;
            int ok;
            u16 lo;
            u16 hi;
            int v;

            w = (u16) w2;
            ok = 0;
            lo = w;
            hi = w;
            if (hi >= 0x12e8 && lo <= 0x131f) {
                ok = 1;
            }
            if (ok != 0) {
                v = lo - 0x12e8;
            } else {
                v = -1;
            }
            func_ov107_0229c488((struct UnkStruct_0229c488 *) self, (u8) v);
            self->unk_BE = 0x14;
            func_ov002_02208098((void *) (self), 0x13);
            func_ov107_0229caa8(self);
        }
    }
}

void func_ov107_0229c488(struct UnkStruct_0229c488 *param0, int param1)
{
    char a[4];
    char b[5];

    if (func_02073d90((void *) ((*(int *) &data_020ccf94))) != 0) {
        int v;

        a[0] = 2;
        a[1] = param1;
        func_020779b8(&b[3], param0->unk_C0, param0->unk_C8);
        MI_CpuCopy8(&b[3], &a[2], 5);
        v = (*(int *) &data_020ccf94);
        func_02073820((void *) v);
        func_020737f0((void *) v, (const void *) a, 7);
        func_02073770((void *) v, 0x16, 4);
    }
}

void func_ov107_0229c414(UnkStruct_0229c414 *self)
{
    int idx = func_ov107_0229d0f0(self, (unsigned char) self->unk_B9);
    Global *g = (*(Global **) &data_020ccf94);

    self->unk_AC = func_02043d34(g->unk_64, 2, 0, idx);

    if (self->unk_AC == -1) {
        func_ov107_0229d480(self);
        func_ov107_0229d3a0(self, 3, 0xff);
        return;
    }

    {
        unsigned short *p = func_02045b5c(g->unk_68);
        unsigned short v = *p;
        self->unk_CC = v >> 8;
        self->unk_D0 = v & 0xff;
        (int) func_ov002_02208098((void *) (self), 0x16);
        return;
    }
}

void func_ov107_0229c3c4(struct UnkStruct_0229c3c4 *self)
{
    int v = func_020436a8(self->unk_AC);
    if (v == 1) {
        goto case1;
    }
    if (v == 2) {
        goto case2;
    }
    return;
case1:
    func_ov002_02208098((void *) (self), 0x17);
    func_ov107_0229c378((struct UnkStruct_0229c378 *) self);
    goto common;
case2:
    func_ov107_0229d480((void *) self);
    func_ov107_0229d3a0((void *) self, 3, 0xff);
common:
    func_020431b8(self->unk_AC);
    self->unk_AC = -1;
}

void func_ov107_0229c378(struct UnkStruct_0229c378 *p)
{
    unsigned short s;
    int arr[3];
    func_0204f794(arr, p->cc, p->d0);
    s = (unsigned short) func_ov107_0229d0f0((void *) p, (unsigned char) p->b9);
    if (func_ov003_02219b90(arr, &s)) {
        func_ov107_0229caa8((void *) p);
        func_ov002_02208098((void *) (p), 0x14);
    }
}

int func_ov107_0229c354(void *receiver)
{
    int field;
    field = (*(UnkStruct_0229c354 **) &data_020ccf94)->unk_64;
    if (func_02073dd4((*(UnkStruct_0229c354 **) &data_020ccf94), field) != 0) {
        return (unsigned char) field;
    } else {
        return 0;
    }
}

void func_ov107_0229c2c8(int a, int b)
{
    unsigned int r4;
    unsigned int r6;
    unsigned char buf[2];
    void *ptr;

    r4 = func_0206fca4();
    r6 = func_ov107_0229c354((void *) a);
    switch (r4 - 0x29) {
        case 0:
        case 1:
            if (b == 0) {
                return;
            }
            func_02045d98(r6);
            if (func_02073d90(data_020ccf94) == 0) {
                return;
            }
            buf[0] = 0x17;
            buf[1] = (unsigned char) r6;
            ptr = data_020ccf94;
            func_02073820(ptr);
            func_020737f0(ptr, (const void *) buf, 2);
            func_02073770(ptr, 0x16, 4);
            break;
        case 2:
            func_ov003_0222e6c4(r6, 1);
            break;
        case 3:

            func_ov003_0222aae8(func_0206f7bc());
            break;
    }
}

unsigned int func_ov107_0229c2b4(void *self, unsigned int mask)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x94);
    if (*p & mask) {
        return 1;
    }
    return 0;
}

void func_ov107_0229c2a4(struct UnkStruct_0229c2a4 *self, unsigned int mask)
{
    self->unk_94 |= mask;
}

void func_ov107_0229c294(void *self, unsigned int mask)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x94);
    *p &= ~mask;
}

void *func_ov107_0229c208(void *self)
{
    *(void **) self = (void *) &data_ov107_0229e3b8;
    func_ov002_0220afdc((char *) self + 0x2828);
    func_ov002_0220ba0c((char *) self + 0x270c);
    func_ov002_02209ac8((char *) self + 0x2318);
    func_ov002_02209cb4((char *) self + 0x22b4);
    func_ov002_02209e38((char *) self + 0x229c);
    func_ov002_02207e28((char *) self + 0x21cc);
    func_ov094_0229a2d0((char *) self + 0x0b94);
    func_ov094_0229bc30((char *) self + 0x0b6c);
    func_ov094_0229afe0((char *) self + 0x010c);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov107_0229c180(void *param)
{
    *(void **) param = ((char *) &data_ov107_0229e3b8);
    func_ov002_0220afdc((char *) param + 0x2828);
    func_ov002_0220ba0c((char *) param + 0x270c);
    func_ov002_02209ac8((char *) param + 0x2318);
    func_ov002_02209cb4((char *) param + 0x22b4);
    func_ov002_02209e38((char *) param + 0x229c);
    func_ov002_02207e28((char *) param + 0x21cc);
    func_ov094_0229a2d0((char *) param + 0x0b94);
    func_ov094_0229bc30((char *) param + 0x0b6c);
    func_ov094_0229afe0((char *) param + 0x010c);
    func_ov002_0220826c(param);
    return param;
}
