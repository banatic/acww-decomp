/* soft_keyboard_draw: 18 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229b394 @ 0x0229b394, 0xc bytes, Thumb
 * func_ov095_0229b388 @ 0x0229b388, 0xc bytes, Thumb
 * func_ov095_0229b324 @ 0x0229b324, 0x64 bytes, Thumb
 * func_ov095_0229b280 @ 0x0229b280, 0xa4 bytes, Thumb
 * func_ov095_0229b1c8 @ 0x0229b1c8, 0xb8 bytes, Thumb
 * func_ov095_0229b18c @ 0x0229b18c, 0x3c bytes, Thumb
 * func_ov095_0229b16c @ 0x0229b16c, 0x20 bytes, Thumb
 * func_ov095_0229b0d8 @ 0x0229b0d8, 0x94 bytes, Thumb
 * func_ov095_0229b090 @ 0x0229b090, 0x48 bytes, Thumb
 * func_ov095_0229b058 @ 0x0229b058, 0x38 bytes, Thumb
 * func_ov095_0229aff0 @ 0x0229aff0, 0x68 bytes, Thumb
 * func_ov095_0229afac @ 0x0229afac, 0x44 bytes, Thumb
 * func_ov095_0229afa4 @ 0x0229afa4, 0x6 bytes, Thumb
 * func_ov095_0229af98 @ 0x0229af98, 0xc bytes, Thumb
 * func_ov095_0229af84 @ 0x0229af84, 0x12 bytes, Thumb
 * func_ov095_0229af58 @ 0x0229af58, 0x2c bytes, Thumb
 * func_ov095_0229aeec @ 0x0229aeec, 0x6c bytes, Thumb
 * func_ov095_0229ae84 @ 0x0229ae84, 0x68 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229b280 {
    u8 pad_00[0x18];
    u8 count;
    u8 pad_19[0x3c - 0x19];
    u8 tiles[0x2c28 - 0x3c];
    u8 data[0x8000];
};

typedef struct {
    int a;
    int b;
} Pair;

struct UnkStruct_0229b1c8 {
    unsigned char pad_00[0x16];
    unsigned char flag;
    unsigned char pad_17[0x44 - 0x17];
    Pair *arr;
};

struct Example {
    char pad_00[0x16];
    unsigned char unk_16;
};

typedef struct {
    int a;
    int b;
} UnkStruct_0229b0d8;

struct UnkStruct_0229b0d8_2 {
    char pad_00[0x17];
    unsigned char key;
    unsigned char count;
};

struct UnkStruct_0229aff0 {
    char pad_00[0x16];
    unsigned char unk_16;
    char pad_17[0x2d];
    int unk_44;
};

typedef struct {
    unsigned char pad_00[0x17];
    unsigned char unk_17;
    unsigned char unk_18;
} UnkStruct_0229afac;

typedef struct {
    unsigned char pad_00[23];
    unsigned char unk_17;
} UnkStruct_0229afa4;

typedef struct {
    unsigned char pad_00[0x19];
    unsigned char unk_19;
    unsigned char unk_1A;
} UnkStruct_0229aeec;

extern void func_ov095_022999a8(int a, int b);
extern void func_ov095_022999a0(int, int);
extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_02002c6c(void *, void *, int, int, int, int);
extern void *data_021fbe94;
extern unsigned char data_ov095_0229ee08[];
extern unsigned char data_ov095_0229ee24[];
extern unsigned char data_ov095_0229ee40[];
extern u8 func_0203fa58(void);
extern u8 func_0203fa14(int x);
extern int func_02064af4(const void *src, void *dst, unsigned int size);
extern int func_02002a88(void *dst, int a, int b, int c, int d);
extern const u8 data_ov095_0229edf4[];
extern int func_020896b8(int, const void *, int, int, int, int, int);
extern void func_02088df8(int, void *, int, int, int, int, int, int, int, int, int, int);
extern int func_ov095_022999b0(void *, int);
extern void *data_ov095_0229e424[];
extern char data_ov095_0229ea84;
extern UnkStruct_0229b0d8 data_ov095_0229e814[];
extern unsigned char data_ov095_0229e380[];
extern int data_ov095_0229e390;
extern int func_02088d34(void *, int, int, int, int);
extern unsigned char data_021f6c54[];
extern unsigned char data_021f6c58[];
extern int func_02088cf4(int, int, int, int, int, int);
extern void func_0200467c(int);
extern unsigned char data_ov095_0229e834[];
extern unsigned char data_ov095_0229e388[];
extern char data_ov095_0229e664;
extern char data_ov095_0229e68c;
extern char data_ov095_0229e714;
extern char data_ov095_0229e744;

void func_ov095_0229b18c(int a0, int a1, int a2);
void *func_ov095_0229b16c(struct Example *self);

void func_ov095_0229b394(int a0)
{
    func_ov095_022999a8(a0, 2);
}

void func_ov095_0229b388(int arg)
{
    func_ov095_022999a0(arg, 2);
}

int func_ov095_0229b324(void *receiver)
{
    void *obj = data_021fbe94;

    func_02002d14((void *) data_ov095_0229ee08, obj, 8, 4, 4, 0xe);
    func_02002c6c((void *) data_ov095_0229ee24, obj, 8, 0xc0, 0xc0, 0x13f);
    return func_02002c6c((void *) data_ov095_0229ee40, obj, 8, 0x180, 0x180, 0x1ff);
}

void func_ov095_0229b280(struct UnkStruct_0229b280 *self)
{
    int i;

    self->count = func_0203fa58();

    for (i = 0; i < self->count; i++) {
        self->tiles[i] = func_0203fa14(i);
    }

    func_02064af4(data_ov095_0229edf4, self->data, 0x1000);

    for (i = 0; i < self->count; i++) {
        int b = self->tiles[i] - 1;
        int off = ((b & 0xf) << 6) + ((b >> 4) << 11);
        int n = (i << 1) + 0x109;

        func_02002a88(self->data + off, 8, n, n, n + 1);
        func_02002a88(self->data + (off + 0x400), 8, n + 0x20, n + 0x20, n + 0x21);
    }
}

void func_ov095_0229b1c8(struct UnkStruct_0229b1c8 *self, int a, int b, int c)
{
    int mode;
    int v0;
    int v1;
    int i;

    mode = 0;
    v0 = 0;
    v1 = 0;

    switch (self->flag) {
        case 1:
            mode = 1;
            break;
        case 2:
            mode = 2;
            break;
        case 4:
            break;
        default:
            break;
    }

    for (i = 0; i < 3; i++) {
        if (mode == i) {
            func_020896b8(1, (const void *) (self->arr + i), a, b + 2, 0xb, c, v0);
        } else {
            func_020896b8(1, (const void *) (self->arr + i), a, b, 0xa, c, v1);
        }
    }
    func_02088df8(1, self->arr + 3, a, b, -1, c, 0x1000, 0x1000, 0, -1, 0, 0);
    if (func_ov095_022999b0(self, 4) == 0) {
        b -= 8;
    }
    func_ov095_0229b18c((int) self, a, b);
}

void func_ov095_0229b18c(int a0, int a1, int a2)
{
    int ret = (int) func_ov095_0229b16c((struct Example *) a0);
    func_02088df8(1, (void *) ret, a1, a2, -1, 3, 0x1000, 0x1000, 0, -1, 0, 0);
}

void *func_ov095_0229b16c(struct Example *self)
{
    unsigned char idx;
    void *val;

    idx = self->unk_16;
    if (idx >= 5) {
        return 0;
    }
    val = data_ov095_0229e424[idx];
    if (val != 0) {
        return val;
    }
    return (void *) &data_ov095_0229ea84;
}

void func_ov095_0229b0d8(struct UnkStruct_0229b0d8_2 *self, int param1, int param2)
{
    int local0 = 0;
    int local1 = 0;
    int local2 = 0;
    int i;
    for (i = 0; i < self->count; i++) {
        int v0 = -1;
        int v1 = param2;
        if (self->key == i) {
            v0 = 0xb;
            v1 = param2 + 2;
        }
        func_020896b8(1, &data_ov095_0229e814[i], param1, v1, -1, 2, local0);
        func_020896b8(1, &data_ov095_0229e814[i + 4], param1, v1, v0, 2, local1);
        func_020896b8(1, &data_ov095_0229e814[i + 8], param1, param2, -1, 2, local2);
    }
}

void func_ov095_0229b090(int p0, int p1, int p2, int p3, int p4)
{
    func_020896b8(1, (const void *) ((int) ((int *) data_ov095_0229e380)), p1, p2 + p4, p3, 2, 0);
    func_020896b8(1, (const void *) ((int) &data_ov095_0229e390), p1, p2, -1, 2, 0);
}

int func_ov095_0229b058(void *p)
{
    return func_02088d34((void *) data_ov095_0229e380, *((const unsigned char *) data_021f6c58) - 0x80,
                         *((const unsigned char *) data_021f6c54) - 0x60, 0, 0) != 0;
}

int func_ov095_0229aff0(struct UnkStruct_0229aff0 *self)
{
    int result, val;
    result = func_02088cf4(self->unk_44, 3, (int) (*(unsigned char *) data_021f6c58) - 0x80, (int) (*(unsigned char *) data_021f6c54) - 0x60, 2, 2);
    if (result == -1) {
        return 0;
    }
    val = result;
    switch (result) {
        case 0:
            val = 4;
            break;
        case 1:
            val = 1;
            break;
        case 2:
            val = 2;
            break;
    }
    if (val == self->unk_16) {
        return 0;
    }
    self->unk_16 = (unsigned char) val;
    func_0200467c(0x18);
    return 1;
}

int func_ov095_0229afac(UnkStruct_0229afac *p)
{
    int res = func_02088cf4((int) data_ov095_0229e834, (unsigned char) p->unk_18, (*(unsigned char *) data_021f6c58) - 0x80, (*(unsigned char *) data_021f6c54) - 0x60, 0, 0);
    if (res == -1) {
        return 0;
    }
    p->unk_17 = (unsigned char) res;
    return 1;
}

void func_ov095_0229afa4(UnkStruct_0229afa4 *p)
{
    p->unk_17 = 255;
}

unsigned char *func_ov095_0229af98(unsigned char *r0, int r1)
{
    r0[0x17] = (unsigned char) (r1 - 0x11b);
    return r0;
}

unsigned char func_ov095_0229af84(unsigned char *p)
{
    unsigned int idx = p[0x17];
    if (idx >= 4) {
        return 0xFF;
    }
    return *(p + idx + 0x3c);
}

int func_ov095_0229af58(int unused, int b, int c, int d)
{
    return func_020896b8(1, (const void *) data_ov095_0229e388, b, c, -1, d, 0);
}

void func_ov095_0229aeec(UnkStruct_0229aeec *p1, int p2, int p3)
{
    func_02088df8(1, (void *) (&data_ov095_0229e664), p2, p3, p1->unk_19, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, (void *) (&data_ov095_0229e68c), p2, p3, p1->unk_1A, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_ov095_0229ae84(void *p1, void *p2, void *p3)
{
    func_02088df8(1, (void *) (&data_ov095_0229e714), (int) p2, (int) p3, ((unsigned char *) p1)[0x19], 1, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, (void *) (&data_ov095_0229e744), (int) p2, (int) p3, ((unsigned char *) p1)[0x1a], 1, 0x1000, 0x1000, 0, -1, 0, 0);
}
