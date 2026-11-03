/* model_object_3: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056044 @ 0x02056044, 0x20 bytes, Thumb
 * func_0205602c @ 0x0205602c, 0x18 bytes, Thumb
 * func_0205600c @ 0x0205600c, 0x20 bytes, Thumb
 * func_02055ff4 @ 0x02055ff4, 0x18 bytes, Thumb
 * func_02055fcc @ 0x02055fcc, 0x28 bytes, Thumb
 * func_02055f6c @ 0x02055f6c, 0x60 bytes, Thumb
 * func_02055f40 @ 0x02055f40, 0x2a bytes, Thumb
 * func_02055f2c @ 0x02055f2c, 0x14 bytes, Thumb
 * func_02055f1c @ 0x02055f1c, 0x10 bytes, Thumb
 * func_02055e90 @ 0x02055e90, 0x8c bytes, Thumb
 * func_02055e7c @ 0x02055e7c, 0x14 bytes, Thumb
 * func_02055e64 @ 0x02055e64, 0x18 bytes, Thumb
 * func_02055e10 @ 0x02055e10, 0x54 bytes, Thumb
 * func_02055e04 @ 0x02055e04, 0xc bytes, Thumb
 * func_02055e00 @ 0x02055e00, 0x4 bytes, Thumb
 * func_02055de0 @ 0x02055de0, 0x20 bytes, Thumb
 * func_02055dc8 @ 0x02055dc8, 0x18 bytes, Thumb
 * func_02055d80 @ 0x02055d80, 0x48 bytes, Thumb
 * func_02055d38 @ 0x02055d38, 0x48 bytes, Thumb
 * func_02055d0c @ 0x02055d0c, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct Object {
    unsigned int unk_00;
} Object;

typedef struct {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[2];
    char unk_08[0x54];
    int unk_5C;
    int unk_60;
    char unk_64[0x30];
    int unk_94;
} UnkStruct_02055fcc;

typedef struct {
    char pad_00[0x5c];
    u32 unk_5C;
} UnkStruct_02055f6c;

typedef struct {
    char pad_00[8];
    int unk_08;
    char pad_0C[0xc];
    u8 count;
} UnkStruct_02055f6c_2;

typedef struct {
    char pad_00[4];
    u8 table[6];
    u16 idx;
} UnkStruct_02055f6c_3;

typedef struct {
    char pad_00[0xc];
    u32 flags;
} Elem;

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
} UnkStruct_02055f40;

typedef struct {
    int unk_00[0x17];
    int unk_5C;
    int unk_60;
} UnkStruct_02055f2c;

typedef struct Block {
    unsigned int pad_00;
    unsigned int offset;
    unsigned char pad_08[0x1c - 0x8];
    unsigned int val;
} Block;

typedef struct UnkStruct_02055e90 {
    unsigned char pad_00[0x5c];
    Block *blk;
} UnkStruct_02055e90;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char *unk_5C;
} UnkStruct_02055d80;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char *unk_5C;
} UnkStruct_02055d38;

extern void func_020563c0(void *p);
extern void func_02056390(void *obj);
extern void func_020edb3c(Object *self);
extern unsigned char data_020dd13c[];
extern void func_021054e4(void *, int);
extern void MTX_Identity43_(void *);
extern int func_020658c4(void);
extern void NNSi_G3dModifyMatFlag(void *, int, int);
extern int NNS_G3dBindMdlTex(unsigned int, unsigned int);
extern int NNS_G3dBindMdlPltt(unsigned int, unsigned int);
extern unsigned int FX_MulFunc(unsigned int a, unsigned int b);
extern void NNS_G3dDraw1Mat1Shp(void *a, unsigned int b, unsigned int c, unsigned int d);
extern unsigned int NNS_G3dGetSbcCmdLen(const void *p);
extern void func_01ff8ad4(void *);
extern void MI_Copy36B(void *, void *);
extern void func_0210581c(void *);
extern void func_021057f4(void *);
extern void NNS_G3dGlbFlushP(void);
extern unsigned int data_027e0148[];
extern char data_027e0184[];
extern void NNS_G3dRenderObjSetCallBack(char *p, int b, int c, int d, int e);
extern void func_02105294(void *, int);
extern int NNS_G3dGetResultMtx(void *ptr, int a, int b, int c);
extern int NNS_G3dGlbGetInvV(void);
extern void MTX_Concat43(int a, int b, int c);

void func_02055fcc(UnkStruct_02055fcc *self);
void func_02055e10(void *p0, void *p1);
void func_02055e04(char *ptr);

void *func_02056044(void *p)
{
    func_020563c0(p);
    *(void **) p = ((char *) data_020dd13c);
    func_02055fcc((UnkStruct_02055fcc *) p);
    return p;
}

void *func_0205602c(void *self)
{
    ((void **) self)[0] = (void *) ((char *) data_020dd13c);
    func_02056390(self);
    return self;
}

Object *func_0205600c(Object *self)
{
    self->unk_00 = (unsigned int) ((unsigned int *) data_020dd13c);
    func_02056390((void *) self);
    func_020edb3c(self);
    return self;
}

void *func_02055ff4(void *p)
{
    *(void **) p = (void *) data_020dd13c;
    func_02056390(p);
    return p;
}

void func_02055fcc(UnkStruct_02055fcc *self)
{
    func_021054e4(self->unk_08, 0);
    self->unk_5C = 0;
    self->unk_60 = 0;
    MTX_Identity43_(self->unk_64);
    self->unk_04 = 0;
    self->unk_94 = 0;
}

void func_02055f6c(UnkStruct_02055f6c *self)
{
    UnkStruct_02055f6c_2 *in;
    UnkStruct_02055f6c_3 *b;
    int i;

    func_021054e4((char *) self + 8, self->unk_5C);
    in = (UnkStruct_02055f6c_2 *) self->unk_5C;
    b = (UnkStruct_02055f6c_3 *) ((char *) in + in->unk_08);
    for (i = 0; i < ((UnkStruct_02055f6c_2 *) self->unk_5C)->count; i++) {
        u8 *tbl = b->table;
        u16 h = b->idx;
        u8 *base = tbl + h;
        u16 v = *(u16 *) base;
        int w = *(int *) (base + v * i + 4);
        Elem *e = (Elem *) ((char *) b + w);
        if ((e->flags & 0xf) != 0) {
            e->flags &= ~0xf;
            e->flags |= func_020658c4();
        }
    }
    NNSi_G3dModifyMatFlag((void *) self->unk_5C, 0, 0x400);
}

int func_02055f40(UnkStruct_02055f40 *self, unsigned int a, unsigned int b)
{
    self->unk_5C = a;
    self->unk_60 = b;
    if (self->unk_60 != 0) {
        NNS_G3dBindMdlTex(self->unk_5C, self->unk_60);
        NNS_G3dBindMdlPltt(self->unk_5C, self->unk_60);
    }
    func_02055f6c((UnkStruct_02055f6c *) self);
    return 1;
}

int func_02055f2c(UnkStruct_02055f2c *obj, int a, int b)
{
    obj->unk_5C = a;
    obj->unk_60 = b;
    func_02055f6c((UnkStruct_02055f6c *) obj);
    return 1;
}

int func_02055f1c(void *argument0)
{
    func_02055fcc((UnkStruct_02055fcc *) ((void *) argument0));
    return 1;
}

void func_02055e90(UnkStruct_02055e90 *self, const unsigned int *input)
{
    Block *blk;
    unsigned char *ptr;
    unsigned int val;
    unsigned int arg;
    unsigned int arr[3];

    blk = self->blk;
    ptr = (unsigned char *) blk + blk->offset;
    val = blk->val;

    if (val == 0x1000) {
        func_02055e10(self, (void *) input);
    } else {
        if (input == 0) {
            arr[0] = arr[1] = arr[2] = val;
        } else {
            arr[0] = FX_MulFunc(input[0], val);
            arr[1] = FX_MulFunc(input[1], val);
            arr[2] = FX_MulFunc(input[2], val);
        }
        func_02055e10(self, arr);
    }

    while (1) {
        int op = *ptr & 0x1f;
        switch (op) {
            case 1:
                return;
            case 4:
                arg = ptr[1];
                break;
            case 5:
                NNS_G3dDraw1Mat1Shp(self->blk, arg, ptr[1], 1);
        }
        ptr += NNS_G3dGetSbcCmdLen(ptr);
    }
}

void func_02055e7c(void *arg, void *argument1)
{
    func_02055e10(arg, (void *) argument1);
    func_02055e04((char *) arg);
}

void func_02055e64(void *r0)
{
    void *r3 = (char *) r0 + 8;
    unsigned int r2 = *(unsigned int *) ((char *) r0 + 8);
    r2 |= 2;
    *(unsigned int *) ((char *) r0 + 8) = r2;
    func_01ff8ad4(r3);
}

void func_02055e10(void *p0, void *p1)
{
    volatile unsigned int *base;
    unsigned int arr[3];

    base = data_027e0148;
    MI_Copy36B((char *) p0 + 0x64, data_027e0184);
    base[0x1f] &= ~0xa4;
    func_0210581c((char *) p0 + 0x88);

    if (p1 == 0) {
        arr[2] = 0x1000;
        arr[1] = 0x1000;
        arr[0] = 0x1000;
        func_021057f4(arr);
    } else {
        func_021057f4(p1);
    }

    NNS_G3dGlbFlushP();
}

void func_02055e04(char *ptr)
{
    func_01ff8ad4((void *) (ptr + 8));
}

int func_02055e00(int p0)
{
    return ((int) (p0) + (8));
}

void func_02055de0(char *base, int r1, int r2, int r3, int stack0, int stack4)
{
    NNS_G3dRenderObjSetCallBack(base + 8, r1, stack4, r2, r3);
    *(int *) (base + 0x34) = stack0;
}

void func_02055dc8(void *r0, int r1, int r2)
{
    void *r5 = r0;
    int r4 = r2;
    func_02105294((char *) r0 + 8, r1);
    *(int *) ((char *) r5 + 0x34) = r4;
}

void func_02055d80(UnkStruct_02055d80 *self, int v)
{
    int i;
    unsigned char *base;
    unsigned short w;
    unsigned short h;
    unsigned char *p;
    unsigned int val;
    unsigned char *q;
    unsigned int mask;
    unsigned int off;
    unsigned char *arr;
    base = self->unk_5C + *(unsigned int *) (self->unk_5C + 8);
    i = 0;
    val = (unsigned int) v << 24;
    arr = base + 4;
    mask = 0xc0ffffff;
    while (i < (int) *(unsigned char *) (self->unk_5C + 0x18)) {
        h = *(unsigned short *) (base + 0xa);
        q = arr + h;
        w = *(unsigned short *) (arr + h);
        off = *(unsigned int *) (q + w * i + 4);
        p = base + off;
        *(unsigned int *) (p + 0xc) &= mask;
        *(unsigned int *) (p + 0xc) |= val;
        i++;
    }
}

void func_02055d38(UnkStruct_02055d38 *self, int v)
{
    int i;
    unsigned char *base;
    unsigned short w;
    unsigned short h;
    unsigned char *p;
    unsigned int val;
    unsigned char *q;
    unsigned int mask;
    unsigned int off;
    unsigned char *arr;
    base = self->unk_5C + *(unsigned int *) (self->unk_5C + 8);
    i = 0;
    val = (unsigned int) v << 16;
    arr = base + 4;
    mask = 0xffe0ffff;
    while (i < (int) *(unsigned char *) (self->unk_5C + 0x18)) {
        h = *(unsigned short *) (base + 0xa);
        q = arr + h;
        w = *(unsigned short *) (arr + h);
        off = *(unsigned int *) (q + w * i + 4);
        p = base + off;
        *(unsigned int *) (p + 0xc) &= mask;
        *(unsigned int *) (p + 0xc) |= val;
        i++;
    }
}

int func_02055d0c(char *a, int b, int c)
{
    if (!NNS_G3dGetResultMtx(a + 8, b, 0, c)) {
        return 0;
    }
    MTX_Concat43(b, NNS_G3dGlbGetInvV(), b);
    return 1;
}
