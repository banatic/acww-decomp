/* scene_look_2: 22 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201adec @ 0x0201adec, 0x54 bytes, Thumb
 * func_0201ade4 @ 0x0201ade4, 0x6 bytes, Thumb
 * func_0201addc @ 0x0201addc, 0x6 bytes, Thumb
 * func_0201adbc @ 0x0201adbc, 0x1e bytes, Thumb
 * func_0201ad8c @ 0x0201ad8c, 0x30 bytes, Thumb
 * func_0201ad88 @ 0x0201ad88, 0x4 bytes, Thumb
 * func_0201ad78 @ 0x0201ad78, 0xe bytes, Thumb
 * func_0201ad18 @ 0x0201ad18, 0x60 bytes, Thumb
 * func_0201acbc @ 0x0201acbc, 0x5c bytes, Thumb
 * func_0201ac28 @ 0x0201ac28, 0x94 bytes, Thumb
 * func_0201ac10 @ 0x0201ac10, 0x16 bytes, Thumb
 * func_0201abe8 @ 0x0201abe8, 0x28 bytes, Thumb
 * func_0201abd0 @ 0x0201abd0, 0x16 bytes, Thumb
 * func_0201abac @ 0x0201abac, 0x24 bytes, Thumb
 * func_0201ab94 @ 0x0201ab94, 0x16 bytes, Thumb
 * func_0201ab70 @ 0x0201ab70, 0x24 bytes, Thumb
 * func_0201aa94 @ 0x0201aa94, 0xda bytes, Thumb
 * func_0201aa5c @ 0x0201aa5c, 0x36 bytes, Thumb
 * func_0201aa10 @ 0x0201aa10, 0x4c bytes, Thumb
 * func_0201a9f4 @ 0x0201a9f4, 0x1a bytes, Thumb
 * func_0201a9d8 @ 0x0201a9d8, 0x1a bytes, Thumb
 * func_0201a98c @ 0x0201a98c, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0201ade4;

typedef struct {
    unsigned char pad_00[24];
    unsigned char unk_18;
} UnkStruct_0201addc;

typedef struct {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Src;

typedef struct {
    unsigned char pad_00[8];
    unsigned int a;
    unsigned int b;
    unsigned int c;
} Dst;

struct Src {
    int a;
    int b;
    int c;
};

struct UnkStruct_0201ad18 {
    unsigned char unk_00;
    char pad_01[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    char pad_19[3];
    unsigned short unk_1C;
    unsigned short unk_1E;
    char pad_20[4];
    unsigned short unk_24;
    unsigned short unk_26;
    char pad_28[2];
    unsigned char unk_2A;
    char pad_2B[0x31];
    int unk_5C;
    unsigned char unk_60;
    char pad_61[3];
    int unk_64;
};

typedef struct {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    unsigned char unk_18;
    unsigned char pad_19[3];
    unsigned short unk_1C;
    unsigned short unk_1E;
    unsigned char pad_20[4];
    unsigned short unk_24;
    unsigned short unk_26;
    unsigned char pad_28[2];
    unsigned char unk_2A;
    unsigned char pad_2B[0x5c - 0x2b];
    unsigned int unk_5C;
    unsigned char unk_60;
    unsigned char pad_61[3];
    unsigned int unk_64;
} UnkStruct_0201acbc;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    u8 type; // 0x00
    u8 pad_01[0x5c - 1];
    int unk_5C; // 0x5c
    u8 unk_60;  // 0x60
    u8 pad_61[0x64 - 0x61];
    int unk_64; // 0x64
} UnkStruct_0201ac28;

typedef struct {
    u8 pad_00[0x5c];
    Vec3 pos; // 0x5c
    u8 pad_68[0x8e - 0x68];
    short unk_8E; // 0x8e
} Target;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0201abe8;

typedef struct {
    char pad_00[0x28];
    short unk_28;
} UnkStruct_0201abac;

typedef struct {
    char pad_00[0x1a];
    short unk_1A;
    short unk_1C;
    char pad_1E[4];
    short unk_22;
    short unk_24;
    char pad_26[4];
    char flag;
} UnkStruct_0201aa94;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
} SomeB;

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned char unk_60;
    unsigned int unk_64;
} UnkStruct_0201a9f4;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    unsigned char unk_60;
} UnkStruct_0201a9d8;

typedef struct {
    int pad_00;
    int unk_04;
    char pad_08[0x54];
    int unk_5C;
    unsigned char unk_60;
} UnkStruct_0201a98c_2;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0201a98c;

extern int func_02055d0c(unsigned char *p1, unsigned char *p2, int p3);
extern int func_0203f7d0(void *, void *);
extern int data_021fbee8[3];
extern void *func_02096190(int);
extern int func_020eaa2c(int *a, int *b);
extern int func_020ea9e4(Vec3 *a, Vec3 *b);
extern int func_0201a814(void *s, int a);
extern short func_0200322c(int *a, int *b);
extern int func_020e8ed8(int a, int b);
extern int func_020e8870(short *target, int val, short other);
extern int func_020954c0(int *arr, int c);

int func_0201ac10(int p1, int p2, int p3, int p4);
int func_0201abac(UnkStruct_0201abac *p, int a);
int func_0201ab70(char *ptr, int value);

void func_0201adec(char *r0)
{
    *r0 = 1;
    *(int *) (r0 + 4) = 0;
    *(int *) (r0 + 8) = 0;
    *(int *) (r0 + 12) = 0;
    *(int *) (r0 + 16) = 0;
    *(int *) (r0 + 20) = 0;
    *(short *) (r0 + 26) = 0;
    *(short *) (r0 + 28) = 0x200;
    *(short *) (r0 + 30) = 0;
    *(short *) (r0 + 32) = 0x1a00;
    *(short *) (r0 + 34) = 0;
    *(short *) (r0 + 36) = 0x400;
    *(short *) (r0 + 38) = 0;
    *(short *) (r0 + 40) = 0x3000;
    *(char *) (r0 + 24) = 0;
    *(char *) (r0 + 42) = 0;
    *(int *) (r0 + 92) = 0x8000;
    *(char *) (r0 + 96) = 1;
    *(int *) (r0 + 100) = 4;
}

void func_0201ade4(UnkStruct_0201ade4 *p)
{
    p->unk_04 = 0;
}

void func_0201addc(UnkStruct_0201addc *p)
{
    p->unk_18 = 1;
}

void func_0201adbc(unsigned char *a, unsigned char *b)
{
    if (b) {
        func_02055d0c(b + 0xEC, a + 0x2C, 15);
    }
}

int func_0201ad8c(void *r0, void *r1)
{
    int r4 = 0;
    int r3 = *(int *) ((char *) r0 + 0x50);
    if (r3 != 0) {
        goto label;
    }
    if (*(int *) ((char *) r0 + 0x54) != 0) {
        goto label;
    }
    if (*(int *) ((char *) r0 + 0x58) == 0) {
        goto end;
    }
label:
    *(int *) r1 = r3;
    *(int *) ((char *) r1 + 4) = *(int *) ((char *) r0 + 0x54);
    *(int *) ((char *) r1 + 8) = *(int *) ((char *) r0 + 0x58);
    func_0203f7d0(r1, r1);
    r4 = 1;
end:
    return r4;
}

void func_0201ad88(unsigned short *p0, int p1)
{
    p0[16] = p1;
}

void func_0201ad78(Dst *dst, const Src *src)
{
    dst->a = src->a;
    dst->b = src->b;
    dst->c = src->c;
}

void func_0201ad18(struct UnkStruct_0201ad18 *s, unsigned char b, int arg2, int y, struct Src *src, int arg6, int arg7,
                   unsigned char arg8)
{
    if (s->unk_18 != 0 || s->unk_14 == 4 || arg2 < s->unk_14) {
        return;
    }
    s->unk_00 = b;
    s->unk_04 = y;
    s->unk_08 = src->a;
    s->unk_0C = src->b;
    s->unk_10 = src->c;
    s->unk_14 = arg2;
    s->unk_2A = 0;
    s->unk_5C = arg7;
    s->unk_60 = arg8;
    s->unk_64 = arg6;
    s->unk_1E = 0;
    s->unk_26 = 0;
    s->unk_1C = 0x200;
    s->unk_24 = 0x400;
}

void func_0201acbc(UnkStruct_0201acbc *self, int val, unsigned short a, unsigned short b, signed short c, signed short d)
{
    if (self->unk_18 != 0) {
        return;
    }
    if (self->unk_14 == 4) {
        return;
    }
    if (val < self->unk_14) {
        return;
    }

    self->unk_00 = 5;
    self->unk_04 = 0;
    self->unk_08 = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
    self->unk_14 = val;
    self->unk_2A = 0;
    self->unk_5C = 0x8000;
    self->unk_60 = 1;
    self->unk_64 = 4;
    self->unk_1E = a;
    self->unk_26 = b;
    self->unk_1C = (unsigned short) c;
    self->unk_24 = (unsigned short) d;
}

int func_0201ac28(UnkStruct_0201ac28 *self, Target *other)
{
    volatile Vec3 local;
    Vec3 *vec = 0;

    local.x = 0;
    local.y = 0;
    local.z = 0;

    switch (self->type) {
        case 1: {
            void *p = func_02096190(self->unk_64);
            if (p != 0) {
                vec = (Vec3 *) ((char *) p + 0x5c);
            }
            break;
        }
        case 3:
            vec = (Vec3 *) ((char *) self + 8);
            break;
        default:
            break;
    }

    {
        int dist, threshold, tmp;

        if (vec == 0) {
            goto fail;
        }
        if (func_020eaa2c((int *) vec, data_021fbee8) == 0) {
            goto fail;
        }

        dist = func_020ea9e4(vec, &other->pos);
        threshold = self->unk_5C;
        if (threshold != 0) {
            if (dist < 0) {
                dist = -dist;
            }
            if (dist >= threshold) {
                goto fail;
            }
        }

        tmp = func_0201ac10((int) self, (int) vec, (int) (&other->pos), other->unk_8E);
        if (self->unk_60 != 0 && func_0201a814(self, tmp) == 0) {
            goto fail;
        }

        return 1;
    }

fail:
    return 0;
}

int func_0201ac10(int p1, int p2, int p3, int p4)
{
    return (short) (func_0200322c((int *) p3, (int *) p2) - p4);
}

short func_0201abe8(int param1, UnkStruct_0201abe8 *param2, UnkStruct_0201abe8 *param3, int param4)
{
    int t = func_020ea9e4((Vec3 *) param2, (Vec3 *) param3);
    return func_020e8ed8(param2->unk_04 - param3->unk_04, t) - param4;
}

int func_0201abd0(int a, int position, int target, int angleOffset)
{
    int angle = func_0201ac10(a, position, target, angleOffset);
    return func_0201abac((UnkStruct_0201abac *) ((void *) a), angle);
}

int func_0201abac(UnkStruct_0201abac *p, int a)
{
    int abs_a = a < 0 ? -a : a;
    short limit = p->unk_28;
    if (abs_a > limit) {
        if (a > 0) {
            a = limit;
        } else {
            a = (short) -limit;
        }
    }
    return a;
}

int func_0201ab94(int a, void *argument1, void *argument2, int argument3)
{
    int r4;
    int r0;
    int r1;

    r4 = a;
    r0 = func_0201abe8((int) a, (UnkStruct_0201abe8 *) ((void *) argument1), (UnkStruct_0201abe8 *) ((void *) argument2), (int) argument3);
    r1 = r0;
    r0 = r4;
    return func_0201ab70((char *) r0, r1);
}

int func_0201ab70(char *ptr, int value)
{
    int abs_value;
    short max;

    if (value < 0) {
        abs_value = -value;
    } else {
        abs_value = value;
    }
    max = *(short *) (ptr + 0x20);
    if (abs_value > max) {
        if (value >= 0) {
            value = max;
        } else {
            value = (short) (-max);
        }
    }
    return value;
}

void func_0201aa94(UnkStruct_0201aa94 *a, SomeB *b, void *c, int d, int e, unsigned char f)
{
    char *c_p = (char *) c + 0x5c;
    char *b_p = (char *) b + 0x5c;
    char buffer[16];
    int r4 = 0;
    int r7 = 0;
    int r6;

    a->flag = 0;
    if (c_p != 0) {
        r6 = func_020ea9e4((Vec3 *) c_p, (Vec3 *) b_p);
        if (e != 0) {
            if (r6 < 0) {
                r6 = -r6;
            }
            if (r6 >= e) {
                goto label1;
            }
        }
        r6 = func_0201ac10((int) a, (int) c_p, (int) b_p, (short) b->unk_8E);
        if (f != 0) {
            if (func_0201a814((void *) a, r6) == 0) {
                goto label1;
            }
        }
        if (func_0201ad8c((void *) a, buffer) != 0) {
            r4 = func_0201ab94((int) a, (void *) d, buffer, 0);
        }
        r7 = func_0201abac((UnkStruct_0201abac *) a, r6);
        a->flag = 1;
    }
label1:
    if (a->unk_22 != r7) {
        func_020e8870(&a->unk_22, r7, a->unk_24);
    }
    if (a->unk_1A != r4) {
        func_020e8870(&a->unk_1A, r4, a->unk_1C);
    }
    if (!(a->unk_22 == r7 && a->unk_1A == r4)) {
        a->flag = 0;
    }
}

void func_0201aa5c(void *param0)
{
    short *ptr;
    short value;

    ptr = (short *) param0;
    value = ptr[0x11];
    if (value != 0) {
        func_020e8870((short *) ((char *) param0 + 0x22), 0, ptr[0x12]);
    }
    value = ptr[0x0D];
    if (value != 0) {
        func_020e8870((short *) ((char *) param0 + 0x1A), 0, ptr[0x0E]);
    }
}

void func_0201aa10(int a, int b, int c, int d, unsigned char e)
{
    int tmp1;
    int arr1[3];
    int arr2[3];

    tmp1 = (int) func_02096190(c);
    if (tmp1 != 0) {
        if (func_020954c0(arr1, c) != 0) {
            arr2[0] = arr1[0];
            arr2[1] = arr1[1];
            arr2[2] = arr1[2];
            func_0201aa94((UnkStruct_0201aa94 *) a, (SomeB *) b, (void *) tmp1, (int) arr2, d, e);
        }
    }
}

void func_0201a9f4(void *obj, int a1)
{
    UnkStruct_0201a9f4 *s = (UnkStruct_0201a9f4 *) obj;
    func_0201aa10((int) s, a1, s->unk_64, s->unk_5C, s->unk_60);
}

void func_0201a9d8(UnkStruct_0201a9d8 *self, void *arg2)
{
    func_0201aa10((int) self, (int) arg2, 4, self->unk_5C, self->unk_60);
}

void func_0201a98c(UnkStruct_0201a98c_2 *self, void *param)
{
    UnkStruct_0201a98c local;
    UnkStruct_0201a98c copy;

    if (self->unk_04 == 0) {
        return;
    }
    if (!func_0201ad8c((void *) (self->unk_04 + 0x3b0), (void *) (&local))) {
        return;
    }
    copy.x = local.x;
    copy.y = local.y;
    copy.z = local.z;
    func_0201aa94((UnkStruct_0201aa94 *) self, (SomeB *) param, (void *) self->unk_04, (int) (&copy), self->unk_5C, self->unk_60);
}
