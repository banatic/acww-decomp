/* snowball: 8 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226ef04 @ 0x0226ef04, 0xf8 bytes, Thumb
 * func_ov068_0226ee54 @ 0x0226ee54, 0xb0 bytes, Thumb
 * func_ov068_0226ee0c @ 0x0226ee0c, 0x48 bytes, Thumb
 * func_ov068_0226ed9c @ 0x0226ed9c, 0x70 bytes, Thumb
 * func_ov068_0226ed38 @ 0x0226ed38, 0x64 bytes, Thumb
 * func_ov068_0226eca8 @ 0x0226eca8, 0x90 bytes, Thumb
 * func_ov068_0226ec54 @ 0x0226ec54, 0x54 bytes, Thumb
 * func_ov068_0226ebc4 @ 0x0226ebc4, 0x90 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0226ef04_2 {
    u8 pad_00[0x5c];
    u32 unk_5C;
    u8 pad_60[0x26c - 0x60];
    u32 unk_26C;
} UnkStruct_0226ef04_2;

typedef struct UnkStruct_0226ef04_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x5c - 0xc];
    u32 unk_5C;
    u8 pad_60[0x64 - 0x60];
    u32 unk_64;
    u8 pad_68[0xa8 - 0x68];
    u32 unk_A8;
    u8 pad_AC[0x26c - 0xac];
    u32 unk_26C;
    u8 pad_270[0x314 - 0x270];
    u32 unk_314;
    u32 unk_318;
    u8 pad_31C[0x328 - 0x31c];
    u8 unk_328[0x378 - 0x328];
    u16 unk_378;
    u8 pad_37A[0x37c - 0x37a];
    u32 unk_37C;
    u32 unk_380;
    u32 unk_384;
    u8 pad_388[0x399 - 0x388];
    u8 unk_399;
} UnkStruct_0226ef04_3;

typedef struct UnkStruct_0226ef04 {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
} UnkStruct_0226ef04;

typedef struct {
    unsigned char pad_00[0x5c];
    int unk_5C; // 0x5c
    int unk_60; // 0x60
    int unk_64; // 0x64
    unsigned char pad_68[0xa8 - 0x68];
    int unk_A8; // 0xa8
    unsigned char pad_AC[0x26c - 0xac];
    int unk_26C; // 0x26c
    int unk_270; // 0x270
    unsigned char pad_274[0x314 - 0x274];
    int unk_314; // 0x314
    int unk_318; // 0x318
    unsigned char pad_31C[0x37c - 0x31c];
    int unk_37C; // 0x37c
    int unk_380; // 0x380
    int unk_384; // 0x384
    unsigned char pad_388[0x399 - 0x388];
    unsigned char unk_399; // 0x399
} UnkStruct_0226ee54;

typedef struct {
    char pad_00[0x60];
    int unk_60;
    char pad_64[0x44];
    int unk_A8;
    char pad_AC[0x2cc];
    unsigned short unk_378;
    char pad_37A[0x6];
    int unk_380;
    char pad_384[0x12];
    unsigned short unk_396;
} UnkStruct_0226ee0c;

struct UnkStruct_0226ed9c {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0xa8 - 0x68];
    int unk_A8;
    char pad_AC[0x26c - 0xac];
    int unk_26C;
    int unk_270;
    char pad_274[0x314 - 0x274];
    int unk_314;
    int unk_318;
    char pad_31C[0x380 - 0x31c];
    int unk_380;
    char pad_384[0x399 - 0x384];
    unsigned char unk_399;
};

typedef struct {
    char pad_00[0x5c];
    char sub[4];
    char pad_60[0x308 - 0x60];
    int unk_308;
    int unk_30C;
    int unk_310;
    char pad_314[0x378 - 0x314];
    unsigned short unk_378;
    char pad_37A[0x396 - 0x37a];
    unsigned short unk_396;
    unsigned char unk_398;
} UnkStruct_0226ed38;

typedef struct UnkStruct_0226eca8 {
    char pad_00[0x26c];
    int unk_26C;
    int unk_270;
    char pad_274[0x94];
    int unk_308;
    char pad_30C[0x4];
    int unk_310;
    char pad_314[0x82];
    short unk_396;
    unsigned char unk_398;
} UnkStruct_0226eca8;

struct UnkStruct_0226ec54 {
    unsigned char pad_00[0x308];
    int vec[3];
    unsigned char pad_314[0x64];
    unsigned short flags;
    unsigned char pad_37A[0x1c];
    unsigned short half;
    unsigned char byte;
};

extern void *func_ov003_02236128(void *self);
extern void func_0204f7e0(void *a, void *b);
extern int FX_Div(int a, int b);
extern void *func_020b03f8(void);
extern int func_020044c0(int, int, int, int);
extern int func_ov003_0221a35c(void *self, int n);
extern int func_ov003_0221a4f0(void *p);
extern int data_021fbee8[3];
extern short FX_SinCosTable_[];
extern int FX_MulFunc(int, int);
extern void func_ov068_0226fcbc(UnkStruct_0226eca8 *);
extern void func_020ee470(UnkStruct_0226eca8 *);

int func_ov068_0226ef04(UnkStruct_0226ef04_3 *self)
{
    UnkStruct_0226ef04_2 *sub;
    int x;
    int y;
    int idx;
    UnkStruct_0226ef04 *p;
    UnkStruct_0226ef04_3 *ptr2;
    ptr2 = self;
    ptr2->unk_378 &= ~0x10;
    ptr2->unk_378 |= 0x20;
    sub = (UnkStruct_0226ef04_2 *) func_ov003_02236128(ptr2);
    func_0204f7e0(&ptr2->unk_37C, &sub->unk_5C);
    x = sub->unk_26C;
    y = ptr2->unk_26C;
    ptr2->unk_380 = ptr2->unk_380 + ((((2 * x) - (x >> 3)) - (y >> 3)) - 0x400);
    ptr2->unk_A8 = -(FX_Div(0, 0x3e8000) + 0x8f2);
    idx = ptr2->unk_08 & 1;
    p = (UnkStruct_0226ef04 *) func_020b03f8();
    p[idx & 1].a = 3 * 0;
    p[idx & 1].b = 0;
    p[idx & 1].c = 0;
    p[idx & 1].d = 0x800;
    ptr2->unk_314 = FX_Div(ptr2->unk_37C - ptr2->unk_5C, 0x10000);
    ptr2->unk_318 = FX_Div(ptr2->unk_384 - ptr2->unk_64, 0x10000);
    ptr2->unk_399 = 0;
    func_020044c0((int) (&ptr2->unk_328[0]), (int) (0x81e), (int) (0x7f), 0);
    return 1;
}

void func_ov068_0226ee54(UnkStruct_0226ee54 *self)
{
    int ret;
    int limit;
    unsigned char old;

    self->unk_270 = self->unk_26C;
    self->unk_5C = self->unk_5C + self->unk_314;
    self->unk_64 = self->unk_64 + self->unk_318;

    ret = FX_Div(0, 0x02710000);

    self->unk_A8 = self->unk_A8 + (ret + 0xdf);
    self->unk_60 = self->unk_60 - self->unk_A8;

    if (self->unk_A8 >= 0) {
        limit = self->unk_380 - 0x200;
        if (self->unk_60 < limit) {
            self->unk_60 = limit;
            func_ov003_0221a35c(self, 10);
        }
    }

    old = self->unk_399;
    self->unk_399 = old + 1;
    if (old >= 0x10) {
        self->unk_5C = self->unk_37C;
        self->unk_64 = self->unk_384;
    }
}

int func_ov068_0226ee0c(UnkStruct_0226ee0c *s)
{
    s->unk_378 &= ~0x10;
    s->unk_378 |= 0x20;
    s->unk_396 = 0;
    s->unk_A8 = FX_Div(s->unk_380 - s->unk_60, 0x1333);
    return 1;
}

void func_ov068_0226ed9c(struct UnkStruct_0226ed9c *obj)
{
    unsigned char c;

    obj->unk_270 = obj->unk_26C;
    obj->unk_5C += obj->unk_314;
    obj->unk_64 += obj->unk_318;
    obj->unk_60 += obj->unk_A8;
    if (obj->unk_60 > obj->unk_380) {
        obj->unk_60 = obj->unk_380;
    }
    c = obj->unk_399;
    obj->unk_399 = c + 1;
    if (c >= 16) {
        obj->unk_60 = obj->unk_380;
        func_ov003_0221a35c((void *) obj, 11);
    }
}

int func_ov068_0226ed38(UnkStruct_0226ed38 *p)
{
    p->unk_378 &= ~0x10;
    p->unk_378 |= 0x20;
    func_ov003_0221a4f0(&p->sub);
    p->unk_308 = data_021fbee8[0];
    p->unk_30C = data_021fbee8[1];
    p->unk_310 = data_021fbee8[2];
    p->unk_396 = 0;
    p->unk_398 = 0xc;
    return 1;
}

void func_ov068_0226eca8(UnkStruct_0226eca8 *obj)
{
    short val;
    obj->unk_270 = obj->unk_26C;
    val = FX_SinCosTable_[((unsigned short) obj->unk_396 >> 4) * 2 + 1];
    obj->unk_308 = -FX_MulFunc(0x100, val);
    obj->unk_310 = FX_MulFunc(0x100, val);
    obj->unk_396 += 0x3800;
    if (obj->unk_398 != 0) {
        obj->unk_398--;
    }
    if (obj->unk_398 == 0) {
        func_ov068_0226fcbc(obj);
        func_020ee470(obj);
    }
}

int func_ov068_0226ec54(struct UnkStruct_0226ec54 *p)
{
    p->flags &= ~0x10;
    p->flags |= 0x20;
    p->vec[0] = data_021fbee8[0];
    p->vec[1] = data_021fbee8[1];
    p->vec[2] = data_021fbee8[2];
    p->half = 0;
    p->byte = 0xc;
    return 1;
}

void func_ov068_0226ebc4(char *a0)
{
    short cos;

    *(int *) (a0 + 0x270) = *(int *) (a0 + 0x26c);
    cos = FX_SinCosTable_[(*(unsigned short *) (a0 + 0x396) >> 4) * 2 + 1];
    *(int *) (a0 + 0x308) = FX_MulFunc(0x100, cos);
    *(int *) (a0 + 0x310) = -FX_MulFunc(0x100, cos);
    *(unsigned short *) (a0 + 0x396) = *(short *) (a0 + 0x396) + 0x5000;
    if (*(unsigned char *) (a0 + 0x398) != 0) {
        *(unsigned char *) (a0 + 0x398) -= 1;
    }
    if (*(unsigned char *) (a0 + 0x398) == 0) {
        func_ov068_0226fcbc((UnkStruct_0226eca8 *) a0);
        func_020ee470((UnkStruct_0226eca8 *) a0);
    }
}
