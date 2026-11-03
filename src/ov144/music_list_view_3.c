/* music_list_view_3: 10 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229a540 @ 0x0229a540, 0x48 bytes, Thumb
 * func_ov144_0229a4c8 @ 0x0229a4c8, 0x78 bytes, Thumb
 * func_ov144_0229a4b8 @ 0x0229a4b8, 0x10 bytes, Thumb
 * func_ov144_0229a42c @ 0x0229a42c, 0x8c bytes, Thumb
 * func_ov144_0229a404 @ 0x0229a404, 0x28 bytes, Thumb
 * func_ov144_0229a3dc @ 0x0229a3dc, 0x28 bytes, Thumb
 * func_ov144_0229a3a4 @ 0x0229a3a4, 0x36 bytes, Thumb
 * func_ov144_0229a378 @ 0x0229a378, 0x2c bytes, Thumb
 * func_ov144_0229a328 @ 0x0229a328, 0x50 bytes, Thumb
 * func_ov144_0229a29c @ 0x0229a29c, 0x8c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229a4c8 {
    char pad_00[0xa8];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    char pad_B4[0x128 - 0xb4];
} UnkStruct_0229a4c8;

struct UnkStruct_0229a42c {
    char pad_00[0xa8];
    int unk_A8;
};

typedef struct {
    unsigned char pad_00[0x128];
    char unk_128[4];
} UnkStruct_0229a404;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    int unk_A8;
} OV144_0229A3A4_STRUCT;

typedef struct UnkStruct_0229a378 UnkStruct_0229a378;

struct UnkStruct_0229a378 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    unsigned char pad_A0[0x4];
    int unk_A4;
    int unk_A8;
};

struct Work {
    unsigned char pad_00[0xb8];
    short count;
    unsigned char pad_BA[0x7b2];
    unsigned short table[0x46];
};

extern int func_ov002_0220a58c(void *, int arg1, int arg2);
extern void func_ov002_0220a574(void *);
extern void *func_020e895c(void *s, int c, unsigned int n);
extern void func_ov002_0220a4c8(void *receiver);
extern int func_ov002_0220a568(int arg);
extern unsigned short data_021fbe40;
extern int func_0208e930(void *ptr);
extern void func_ov002_0220a580(void *ptr);
extern void func_0208ea70(void *, int, int);
extern void func_ov144_02299e6c(OV144_0229A3A4_STRUCT *, int);
extern int _s32_div_f(int a, int b);
extern int func_02060a34(unsigned short key);
extern u16 *func_02060b70(void);

void func_ov144_0229a3dc(char *p);
void func_ov144_0229a3a4(OV144_0229A3A4_STRUCT *self);

int func_ov144_0229a540(void *self, int a2, int a3)
{
    int result;
    int *p;
    int *q;

    if (func_ov002_0220a58c((char *) self + 0x128, a2, a3)) {
        p = (int *) ((char *) self + 0xa8);
        *((int *) ((char *) self + 0xac)) = *p - a3;
        func_ov002_0220a574((char *) self + 0x128);
        q = (int *) ((char *) self + 0xa8);
        *((int *) ((char *) self + 0xb0)) = *q;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_ov144_0229a4c8(UnkStruct_0229a4c8 *self, int a, int flag)
{
    int d;

    if (flag) {
        a -= 0x1d;
    } else {
        a += self->unk_AC;
    }

    if (a < 0) {
        a = 0;
    }
    if (a > 0x78) {
        a = 0x78;
    }

    if (flag) {
        func_020e895c((char *) self + 0xa8, a, 8);
    } else {
        self->unk_A8 = a;
    }

    func_ov144_0229a3a4((OV144_0229A3A4_STRUCT *) self);
    func_ov144_0229a3dc((char *) self);

    d = self->unk_B0 - self->unk_A8;
    if (d >= 4 || d <= -4) {
        func_ov002_0220a4c8((char *) self + 0x128);
        self->unk_B0 = self->unk_A8;
    }
}

int func_ov144_0229a4b8(int arg)
{
    return func_ov002_0220a568(arg + 0x128);
}

void func_ov144_0229a42c(struct UnkStruct_0229a42c *self)
{
    int original = self->unk_A8;
    unsigned short flags = data_021fbe40;

    if (flags & 0x40) {
        self->unk_A8 -= 4;
        if (self->unk_A8 < 0) {
            self->unk_A8 = 0;
        }
    } else if (flags & 0x80) {
        self->unk_A8 += 4;
        if (self->unk_A8 > 0x78) {
            self->unk_A8 = 0x78;
        }
    }

    if (original != self->unk_A8) {
        func_ov144_0229a3a4((OV144_0229A3A4_STRUCT *) self);
        func_ov144_0229a3dc((char *) self);
        func_ov002_0220a4c8((char *) self + 0x128);
    }
}

int func_ov144_0229a404(UnkStruct_0229a404 *self)
{
    if (func_0208e930(self->unk_128)) {
        func_ov002_0220a580(self->unk_128);
        return 1;
    }
    return 0;
}

void func_ov144_0229a3dc(char *p)
{
    char *base;
    int a;
    int b;
    base = p + 0x128;
    a = *(int *) (p + 0x94);
    p += 0xa8;
    b = *(int *) p;
    func_0208ea70(base, 0x4f, a + (b - 0x4b));
}

void func_ov144_0229a3a4(OV144_0229A3A4_STRUCT *self)
{
    int result;
    int a = self->unk_A4;
    result = (self->unk_A8 * a) / 0x78;
    if (result < 0) {
        result = 0;
    }
    if (result > a) {
        result = a;
    }
    func_ov144_02299e6c(self, result);
    self->unk_A0 = result;
}

void func_ov144_0229a378(UnkStruct_0229a378 *s)
{
    if (s->unk_A4 > 0) {
        s->unk_A8 = _s32_div_f(0x78 * s->unk_9C, s->unk_A4);
        func_ov144_0229a3dc((char *) s);
    }
}

void func_ov144_0229a328(struct Work *p)
{
    int i;
    unsigned short key = 0x1323;

    p->count = 0;
    for (i = 0; i < 0x46; i++) {
        if (func_02060a34(key)) {
            p->table[p->count] = key;
            p->count++;
        }
        key++;
    }
}

void func_ov144_0229a29c(u8 *self)
{
    u16 *p;
    u16 v;
    int limit;
    int k;
    int n;
    u16 id;
    unsigned int ok;

    id = 0x1323;
    n = 0;
    *(short *) (self + 0xbc) = -1;
    p = func_02060b70();
    if (*p != 0xfff1) {
        p = func_02060b70();
        ok = 0;
        v = *p;
        if (v >= 0x1323 && v <= 0x1368) {
            ok = 1;
        }
        if (ok != 0) {
            limit = v - 0x1323;
        } else {
            limit = -1;
        }
        for (k = 0; k < 0x46; k++) {
            if (func_02060a34((u16) id) != 0) {
                if (k == limit) {
                    *(u16 *) (self + 0xbc) = (u16) n;
                    k = 0x46;
                }
                n++;
            }
            id = (u16) (id + 1);
        }
    }
    *(u16 *) (self + 0xba) = *(short *) (self + 0xbc);
}
