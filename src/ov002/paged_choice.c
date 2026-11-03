/* paged_choice: 15 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02208b74 @ 0x02208b74, 0xe4 bytes, Thumb
 * func_ov002_02208b14 @ 0x02208b14, 0x5e bytes, Thumb
 * func_ov002_02208b00 @ 0x02208b00, 0x12 bytes, Thumb
 * func_ov002_02208aec @ 0x02208aec, 0x12 bytes, Thumb
 * func_ov002_02208ae4 @ 0x02208ae4, 0x8 bytes, Thumb
 * func_ov002_02208ad8 @ 0x02208ad8, 0xa bytes, Thumb
 * func_ov002_02208ad4 @ 0x02208ad4, 0x4 bytes, Thumb
 * func_ov002_02208ad0 @ 0x02208ad0, 0x4 bytes, Thumb
 * func_ov002_02208a8c @ 0x02208a8c, 0x44 bytes, Thumb
 * func_ov002_02208a78 @ 0x02208a78, 0x14 bytes, Thumb
 * func_ov002_02208a24 @ 0x02208a24, 0x52 bytes, Thumb
 * func_ov002_02208a14 @ 0x02208a14, 0x10 bytes, Thumb
 * func_ov002_02208a0c @ 0x02208a0c, 0x8 bytes, Thumb
 * func_ov002_02208a04 @ 0x02208a04, 0x8 bytes, Thumb
 * func_ov002_022089ec @ 0x022089ec, 0x18 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02208b74 UnkStruct_02208b74;

typedef void (*VF)(void *);

typedef struct {
    u8 b[0x6c];
} UnkStruct_02208b74_2;

typedef struct {
    u8 b[0x70];
} UnkStruct_02208b74_3;

struct UnkStruct_02208b14 {
    unsigned char pad_00[8];
    int unk_08;
    int unk_0C;
    unsigned char pad_10[0xc];
    unsigned char unk_1C;
};

struct UnkStruct_02208b00 {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
};

typedef struct {
    char pad_00[0x14];
    unsigned short flags;
} UnkStruct_02208a14;

extern void func_ov002_02208f58(UnkStruct_02208b74 *, u8 *, int);
extern void func_ov002_022092e0(UnkStruct_02208b74 *);
extern void *func_02070c08(void *);
extern void func_020708e4(void *, short *, int);
extern void *func_020a8bb8(void *, void *);
extern int func_020a89f8(void *, void *);
extern int func_020a89dc(void *, void *);
extern void func_0208f218(u8 *, void *);
extern int **func_02070be8(void *);
extern u8 data_ov002_0220ba50[];
extern int func_ov002_02209324(void *self);
extern int func_ov002_02209318(void *self);
extern void func_0200467c(int cmd);
extern void func_02066514(int);
extern void func_02066560(int, int);
extern void func_0206658c(int, int);
extern int func_020b4980(const char *s, char *dst, int mode);

void func_ov002_02208a0c(unsigned short *p0, int p1);

void func_ov002_02208b74(UnkStruct_02208b74 *self, u8 *p)
{
    int val;
    short v[4];
    UnkStruct_02208b74_2 a;
    UnkStruct_02208b74_3 b;
    int i;
    int k;
    int t;
    void *obj;

    k = p[0] * 5;
    i = 0;
    *((u8 *) self + 0x1c) = 0;
    for (; i < 5; i++, k++) {
        val = *((u8 *) self + k + 0x3cc);
        if (val != 0) {
            t = i;
            t = t * 0x74;
            func_ov002_02208f58(self, (u8 *) self + 0x28 + t, val);
            *((u8 *) self + 0x1c) = (u8) (*((u8 *) self + 0x1c) + 1);
        } else {
            i = 5;
        }
    }
    func_ov002_022092e0(self);
    v[0] = (short) (p[0] + 0xff11);
    v[1] = 0;
    v[2] = (short) (*((u8 *) self + 0x1d) + 0xff10);
    v[3] = 0;
    func_02070c08(&a);
    func_02070c08(&b);
    func_020708e4(&b, &v[0], 2);
    func_020a8bb8(&a, &b);
    func_020a89f8(&a, data_ov002_0220ba50);
    func_020708e4(&b, &v[2], 2);
    func_020a89dc(&a, &b);
    func_0208f218((u8 *) self + 0x26c, &a);
    obj = (u8 *) self + 0x26c;
    (*(VF *) ((u8 *) *(void **) obj + 0xc))(obj);
    *((u8 *) self + 0x20) = p[0];
    func_02070be8(&b);
    func_02070be8(&a);
}

int func_ov002_02208b14(struct UnkStruct_02208b14 *self, int a, int b, int c)
{
    int r7;
    int r4;
    int w;
    int v;
    int i;
    int n;

    r7 = -self->unk_08;
    r4 = -self->unk_0C;
    w = r7 + func_ov002_02209324(self);
    v = r4 + func_ov002_02209318(self);
    if (r7 > a || w < a) {
        return c;
    }
    if (r4 > b || v < b) {
        return c;
    }
    r4 += 0x18;
    i = 0;
    n = self->unk_1C - 1;
    while (i < n) {
        if (r4 > b) {
            return i;
        }
        r4 += 0x10;
        i++;
    }
    return i;
}

int func_ov002_02208b00(struct UnkStruct_02208b00 *self, int arg1, int arg2)
{
    return func_ov002_02208b14((struct UnkStruct_02208b14 *) self, arg1, arg2, self->unk_1C - 1);
}

int func_ov002_02208aec(int a, int b, int c)
{
    return func_ov002_02208b14((struct UnkStruct_02208b14 *) a, b, c, -1);
}

int func_ov002_02208ae4(int *p0)
{
    return ((int) (16) - (p0[2]));
}

int func_ov002_02208ad8(int *p0, int p1)
{
    return ((p1 + 1) << 4) - p0[3];
}

int func_ov002_02208ad4(unsigned char *p0)
{
    return p0[28];
}

int func_ov002_02208ad0(unsigned char *p0)
{
    return p0[29];
}

int func_ov002_02208a8c(void *base, int index, int offset)
{
    unsigned char v;
    v = *(unsigned char *) ((char *) base + (offset + 5 * index) + 0x3cc);
    if (v != 0xe) {
        func_ov002_02208a0c((unsigned short *) base, 4);
    }
    switch (v) {
        case 0xf:
            func_0200467c(0x28);
            break;
        case 0xe:
            func_0200467c(0x29);
            break;
        default:
            func_0200467c(0x27);
            break;
    }
    return v;
}

int func_ov002_02208a78(int p0, int p1)
{
    switch (p1) {
        case 15:
            return 3;
        case 14:
            return 2;
        default:
            return 1;
    }
}

int func_ov002_02208a24(int unused, int data, unsigned int type)
{
    switch (type) {
        case 0xf:
            return 3;
        case 0xe:
            return 2;
        case 0xd:
            func_02066514(data);
            return 1;
        default:
            if (type >= 1 && type < 5) {
                func_02066560(data, type - 1);
                return 1;
            } else if (type >= 5 && type < 0xd) {
                func_0206658c(data, type - 5);
                return 1;
            } else {
                return 0;
            }
    }
}

int func_ov002_02208a14(UnkStruct_02208a14 *p, int mask)
{
    if (p->flags & mask) {
        return 1;
    }
    return 0;
}

void func_ov002_02208a0c(unsigned short *p0, int p1)
{
    p0[10] = (p0[10] | p1);
}

void func_ov002_02208a04(unsigned short *p0, int p1)
{
    p0[10] = (p0[10] & ~p1);
}

void func_ov002_022089ec(int unused, const char *src, char c)
{
    char temp = c;
    func_020b4980(src, &temp, 0);
}
