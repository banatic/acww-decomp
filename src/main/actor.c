/* actor: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02003564 @ 0x02003564, 0xb4 bytes, Thumb
 * func_0200354c @ 0x0200354c, 0x18 bytes, Thumb
 * func_02003530 @ 0x02003530, 0x1c bytes, Thumb
 * func_02003518 @ 0x02003518, 0x18 bytes, Thumb
 * func_02003510 @ 0x02003510, 0x8 bytes, Thumb
 * func_02003428 @ 0x02003428, 0xe8 bytes, Thumb
 * func_02003420 @ 0x02003420, 0x8 bytes, Thumb
 * func_020033ec @ 0x020033ec, 0x32 bytes, Thumb
 * func_020033e4 @ 0x020033e4, 0x8 bytes, Thumb
 * func_020033c4 @ 0x020033c4, 0x20 bytes, Thumb
 * func_0200338c @ 0x0200338c, 0x38 bytes, Thumb
 * func_02003378 @ 0x02003378, 0x14 bytes, Thumb
 * func_02003348 @ 0x02003348, 0x30 bytes, Thumb
 * func_02003330 @ 0x02003330, 0x18 bytes, Thumb
 * func_02003300 @ 0x02003300, 0x30 bytes, Thumb
 * func_02003260 @ 0x02003260, 0xa0 bytes, Thumb
 * func_02003244 @ 0x02003244, 0x1c bytes, Thumb
 * func_0200322c @ 0x0200322c, 0x18 bytes, Thumb
 * func_020031d4 @ 0x020031d4, 0x58 bytes, Thumb
 */

#include "types.h"

#define F32(p, o) (*(int *) ((u8 *) (p) + (o)))
#define F16(p, o) (*(unsigned short *) ((u8 *) (p) + (o)))

struct Elem {
    u8 pad_00[8];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
};

struct UnkStruct_02003564 {
    u32 unk_00;
    u8 pad_04[0xc - 0x4];
    u16 unk_0C;
    u8 pad_0E[0x50 - 0xe];
    u32 unk_50;
    u32 unk_54;
    struct UnkStruct_02003564 *unk_58;
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u8 pad_68[0x8c - 0x68];
    s16 unk_8C;
    s16 unk_8E;
    s16 unk_90;
    s16 unk_92;
    s16 unk_94;
    s16 unk_96;
    u8 pad_98[0xb0 - 0x98];
    u32 unk_B0;
};

struct UnkStruct_02003428 {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned int unk_68;
    unsigned int unk_6C;
    unsigned int unk_70;
    unsigned int unk_74;
    unsigned char pad_78[0xb0 - 0x78];
    unsigned int unk_B0;
    unsigned int unk_B4;
    unsigned int unk_B8;
    unsigned int unk_BC;
    unsigned char pad_C0[0xc4 - 0xc0];
    unsigned int unk_C4;
    unsigned int unk_C8;
    unsigned int unk_CC;
    unsigned short unk_D0;
};

struct UnkStruct_020033ec {
    char pad_00[0xb0];
    unsigned int flags;
};

struct UnkStruct_020033c4 {
    char pad_00[8];
    int unk_08;
};

typedef struct UnkStruct_020031d4 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
} UnkStruct_020031d4;

typedef struct Src {
    char pad_00[0x8c];
    short cond;
    short e;
    char pad_90[0x34];
    int a;
    int b;
    int c;
    short d;
} Src;

extern char data_020da13c;
extern char data_020d7244;
extern u32 *data_0213ff74;
extern s16 *data_0213ff70;
extern struct Elem **data_021fd044;
extern void *func_020ee660(void *);
extern int func_020e8ca8(void *, void *);
extern int func_020ee61c(void);
extern void func_0202f144(int, int);
extern int func_020ee550(void *object);
extern void func_020ee4d8(void *, int);
extern int func_01ffd41c(unsigned char *);
extern int FX_MulFunc(int, int);
extern int func_0203a7b8(void *, void *, int *, int, void *);
extern short FX_SinCosTable_[];
extern unsigned char data_0213fee4[];
extern unsigned char data_021f6a6c[];
extern void func_01ffd418(void *object);
extern __arm int func_01ffd3e8(void *ptr);
extern void func_01ffd3e4(void *object);
extern struct UnkStruct_020033c4 *func_020ee7f0(void *a, void *b);
extern void *func_020ee7a4(void *a, void *b, int c);
extern char data_0213ff78[];
extern int data_021f42f4;
extern int func_0202f134(int a, int b, int c, int d);
extern void VEC_Add(void *a, void *b, void *c);
extern short func_020e8ed8(int, int);
extern void func_020e96c8(UnkStruct_020031d4 *p, int a, int b, int c);
extern void func_020e9774(UnkStruct_020031d4 *p, int v);
extern void func_020e9744(UnkStruct_020031d4 *p, int v);

void func_02003330(void *self, int a, int b, int c);

struct UnkStruct_02003564 *func_02003564(struct UnkStruct_02003564 *self)
{
    func_020ee660(self);
    self->unk_00 = (u32) &data_020da13c;
    self->unk_00 = (u32) &data_020d7244;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = self;
    func_020e8ca8(((char *) data_0213ff78), &self->unk_50);
    {
        u32 *p = data_0213ff74;
        if (p != 0) {
            self->unk_5C = p[0];
            self->unk_60 = p[1];
            self->unk_64 = p[2];
        }
    }
    {
        s16 *q = data_0213ff70;
        if (q != 0) {
            self->unk_8C = q[0];
            self->unk_8E = q[1];
            self->unk_90 = q[2];
            q = data_0213ff70;
            self->unk_92 = q[0];
            self->unk_94 = q[1];
            self->unk_96 = q[2];
        }
    }
    {
        struct Elem *e = data_021fd044[self->unk_0C];
        self->unk_B0 = e->unk_08;
        func_02003330((void *) self, e->unk_0C, e->unk_10, e->unk_14);
    }
    return self;
}

int func_0200354c(void)
{
    if (func_020ee61c() != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02003530(void *arg0, int argument1)
{
    unsigned int *ptr;
    unsigned int val;

    func_0202f144((int) arg0, (int) argument1);
    ptr = (unsigned int *) ((char *) arg0 + 0xb0);
    val = *ptr;
    val |= 4;
    *ptr = val;
}

int func_02003518(void *object)
{
    int result;
    if (func_020ee550(object) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

void func_02003510(void *argument0, int argument1)
{
    func_020ee4d8((void *) argument0, (int) argument1);
}

int func_02003428(struct UnkStruct_02003428 *self)
{
    int r4_var;
    int val;
    if (func_01ffd41c((unsigned char *) self) == 0) {
        return 0;
    }
    self->unk_68 = self->unk_5C;
    self->unk_6C = self->unk_60;
    self->unk_70 = self->unk_64;
    if (((((self->unk_B8 != 0))))) {
        int val1 = FX_MulFunc(self->unk_B4, FX_SinCosTable_[(self->unk_D0 >> 4) * 2]);
        r4_var = self->unk_CC + val1;
        {
            int val2 = FX_MulFunc(self->unk_B4, FX_SinCosTable_[((self->unk_D0 >> 4) * 2) + 1]);
            int triplet[3];
            val = self->unk_C8 + val2;
            triplet[0] = self->unk_C4;
            triplet[1] = val;
            triplet[2] = r4_var;
            r4_var = func_0203a7b8((void *) data_021f6a6c, (void *) data_0213fee4, triplet, self->unk_B8, &self->unk_74);
        }
    }
    self->unk_B0 &= ~4u;
    if ((self->unk_B0 & 3u) == 0) {
        goto ret1;
    }
    if (r4_var <= ((int) self->unk_BC)) {
        goto ret1;
    }
    self->unk_B0 |= 4u;
    if ((self->unk_B0 & 1u) == 0) {
        goto ret1;
    }
    return 0;
ret1:
    return 1;
}

void func_02003420(void *object, int status)
{
    func_01ffd418(object);
}

int func_020033ec(struct UnkStruct_020033ec *s)
{
    if (func_01ffd3e8(s) == 0) {
        return 0;
    }
    if ((s->flags & 4) && (s->flags & 2)) {
        return 0;
    }
    return 1;
}

void func_020033e4(void *object, int status)
{
    func_01ffd3e4(object);
}

int func_020033c4(void *arg)
{
    struct UnkStruct_020033c4 *p;
    p = func_020ee7f0(((char *) data_0213ff78), arg);
    if (p) {
        return p->unk_08;
    } else {
        return 0;
    }
}

void *func_0200338c(void *a, void *b)
{
    void *result;
    void *arg1;
    int arg2;

    arg1 = a;
    if (b != 0) {
        arg2 = (int) b + 0x50;
        result = func_020ee7a4(data_0213ff78, arg1, arg2);
    } else {
        arg2 = 0;
        result = func_020ee7a4(data_0213ff78, arg1, arg2);
    }
    if (result != 0) {
        return *(void **) ((char *) result + 8);
    }
    return 0;
}

void func_02003378(int a, int b)
{
    (*(int *) &data_0213ff74) = a;
    (*(int *) &data_0213ff70) = b;
}

int func_02003348(int p1, int p2, int p3, int p4, int p5)
{
    int local = p5;
    if (local == 0) {
        local = data_021f42f4;
    }
    func_02003378(p3, p4);
    return func_0202f134(p1, local, p2, 3);
}

void func_02003330(void *self, int a, int b, int c)
{
    ((int *) ((char *) self + 0xb4))[0] = a;
    ((int *) ((char *) self + 0xb8))[0] = b;
    ((int *) ((char *) self + 0xbc))[0] = c;
}

void func_02003300(void *param0, void *param1)
{
    void *sp;
    unsigned int *r5;
    unsigned int *r4;
    unsigned int *r0;
    unsigned int *r1;
    unsigned int *r2;

    r5 = param0;
    r4 = param1;
    r0 = (unsigned int *) ((char *) r5 + 0x5c);
    r1 = (unsigned int *) ((char *) r5 + 0xa4);
    r2 = r0;
    VEC_Add(r0, r1, r2);
    if (r4 != 0) {
        r1 = (unsigned int *) ((char *) r5 + 0x5c);
        r0 = (unsigned int *) ((char *) r4 + 0x10);
        *r1 = *r1 + *r0;
        r1 = (unsigned int *) ((char *) r5 + 0x64);
        r0 = (unsigned int *) ((char *) r4 + 0x18);
        *r1 = *r1 + *r0;
    }
    return;
}

void func_02003260(void *a)
{
    int target;
    int np;

    if (F32(a, 0x98) == 0) {
        target = F32(a, 0xa0);
        np = F32(a, 0xa8) + F32(a, 0x9c);
        if (np >= target) {
            target = np;
        }
        F32(a, 0xa4) = 0;
        F32(a, 0xa8) = target;
        F32(a, 0xac) = 0;
    } else {
        int cos = FX_MulFunc(F32(a, 0x98), FX_SinCosTable_[((F16(a, 0x94) >> 4) << 1) + 1]);
        target = F32(a, 0xa0);
        np = F32(a, 0xa8) + F32(a, 0x9c);
        if (np >= target) {
            target = np;
        }

        F32(a, 0xa4) = FX_MulFunc(F32(a, 0x98), FX_SinCosTable_[(F16(a, 0x94) >> 4) << 1]);
        F32(a, 0xa8) = target;
        F32(a, 0xac) = cos;
    }
}

void func_02003244(void *a, void *b)
{
    func_02003260(a);
    func_02003300(a, b);
}

short func_0200322c(int *a, int *b)
{
    int r0, r1;
    int *r3;

    r3 = a;
    r0 = *b - *r3;
    r1 = *(b + 2) - *(r3 + 2);
    return func_020e8ed8(r0, r1);
}

void func_020031d4(Src *s, UnkStruct_020031d4 *out)
{
    UnkStruct_020031d4 local;
    func_020e96c8(&local, s->a, s->b, s->c);
    func_020e9774(&local, s->d);
    func_020e9744(&local, s->e);
    if (s->cond) {
        func_020e9774(&local, s->cond);
    }
    *out = local;
}
