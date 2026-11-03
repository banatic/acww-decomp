/* layered_model_2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02054740 @ 0x02054740, 0x26 bytes, Thumb
 * func_02054718 @ 0x02054718, 0x26 bytes, Thumb
 * func_02054700 @ 0x02054700, 0x18 bytes, Thumb
 * func_0205467c @ 0x0205467c, 0x84 bytes, Thumb
 * func_02054630 @ 0x02054630, 0x4c bytes, Thumb
 * func_020545e0 @ 0x020545e0, 0x50 bytes, Thumb
 * func_020545b0 @ 0x020545b0, 0x30 bytes, Thumb
 * func_02054580 @ 0x02054580, 0x30 bytes, Thumb
 * func_02054548 @ 0x02054548, 0x38 bytes, Thumb
 * func_02054524 @ 0x02054524, 0x24 bytes, Thumb
 * func_02054474 @ 0x02054474, 0xb0 bytes, Thumb
 * func_02054430 @ 0x02054430, 0x44 bytes, Thumb
 * func_02054394 @ 0x02054394, 0x9c bytes, Thumb
 * func_02054354 @ 0x02054354, 0x40 bytes, Thumb
 * func_020542e0 @ 0x020542e0, 0x74 bytes, Thumb
 * func_020542c0 @ 0x020542c0, 0x1e bytes, Thumb
 * func_02054240 @ 0x02054240, 0x80 bytes, Thumb
 * func_02054230 @ 0x02054230, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0205467c {
    unsigned int unk_00;
    unsigned char pad_04[0x98];
    unsigned int unk_9C;
    unsigned char pad_A0[0x18];
    unsigned int unk_B8;
    unsigned char pad_BC[0x98];
    unsigned int unk_154;
    unsigned int unk_158;
    unsigned char pad_15C[0x4];
    unsigned int unk_160;
    unsigned int unk_164;
    unsigned int unk_168;
    unsigned char pad_16C[0x4];
    unsigned char arr170[0x3c];
    unsigned int unk_1AC;
    unsigned int unk_1B0;
} UnkStruct_0205467c;

struct SubA {
    void *ptr;
};

struct SubB {
    void *ptr;
};

struct SubC {
    int pad_00;
};

struct SubD {
    int pad_00;
};

struct UnkStruct_02054630 {
    void *unk_00;
    char pad_04[0x9c - 4];
    struct SubA subA;
    char pad_A0[0xb8 - (0x9c + 4)];
    struct SubB subB;
    char pad_BC[0x158 - (0xb8 + 4)];
    struct SubC subC;
    char pad_15C[0x170 - (0x158 + 4)];
    struct SubD subD;
};

typedef struct {
    void *ptr;
} Param;

typedef struct {
    unsigned char pad_00[0xB4];
    u32 unk_B4;                  // 0xB4
    unsigned char pad_B8[0x3C];  // 0xB8 .. 0xF4
    u32 unk_F4;                  // 0xF4
    unsigned char pad_F8[0x54];  // 0xF8 .. 0x14C
    u32 unk_14C;                 // 0x14C
    u32 unk_150;                 // 0x150
    u32 unk_154;                 // 0x154
    unsigned char pad_158[0x54]; // 0x158 .. 0x1AC
    u32 unk_1AC;                 // 0x1AC
    u32 unk_1B0;                 // 0x1B0
} UnkStruct_02054474;

struct Object {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[0x14E];
    int *unk_154;
    int unk_158;
    int unk_15C;
    int unk_160;
    char pad_164[12];
    int unk_170;
    char pad_174[56];
    int unk_1AC;
    int unk_1B0;
};

struct UnkStruct_02054240 {
    char pad_00[4];
    unsigned short unk_04;
    char pad_06[0x56];
    int unk_5C;
    char pad_60[0xf4];
    int unk_154;
    void *unk_158;
    char pad_15C[0x14];
    void *unk_170;
};

extern void func_02054a94(unsigned int, unsigned int);
extern void func_02054a64(unsigned int, unsigned int);
extern void func_02054a98(unsigned int a, unsigned int b);
extern void func_02054a34(unsigned int a, unsigned int b);
extern void *func_02054c2c(void *p);
extern void *func_02056ee0(void *p);
extern int data_020dd184;
extern void func_02056ed4(void *p);
extern void func_02057078(void *p);
extern void *func_02054ad0(void *p);
extern void func_020edb3c(void *);
extern unsigned char data_020dd07c[];
extern unsigned char data_020dd08c[];
extern unsigned char data_020dd09c[];
extern void func_02056aa0(void *addr, int arg);
extern int func_01ffcc10(void *, void *);
extern void func_02054a9c(void *self, void *arg);
extern void func_020549d8(void *self, void *param);
extern void func_02054d80(void *self, void *param);
extern void func_02056b18(void *arg1, void *arg2);
extern int func_020549fc(void *, int);
extern void func_02054944(void *, void *);
extern void func_02054d14(void *, void *);
extern int func_020548cc(void *, int);
extern int func_02056548(int, void *, int);
extern int data_020dd030;
extern void func_02054860(struct Object *);
extern int func_02056e84(int *);
extern void func_02056ffc(int *);
extern void func_02054170(struct Object *);
extern void func_02054828(int, int, int, int, int, unsigned short, unsigned short);
extern void func_02056e60(void *a, int b);
extern unsigned short func_020550b8(int a, int b);
extern void func_02056fcc(void *a, int b, int c, int d, int e);
extern void NNS_G3dAnmObjInit(int a, int b, int c, int d);
extern int func_02056f94(int);

void func_02054740(unsigned int a, unsigned int b, unsigned int c)
{
    while (b <= c) {
        func_02054a94(a, b);
        func_02054a64(a, b);
        b++;
    }
}

void func_02054718(unsigned int a, unsigned int start, unsigned int end)
{
    unsigned int i;
    for (i = start; i <= end; i++) {
        func_02054a98(a, i);
        func_02054a34(a, i);
    }
}

// placeholder, not used
void func_02054700(unsigned int *r0)
{
    unsigned int *r1;
    unsigned int r2;

    r2 = 0;
    r1 = r0 + 0x54; // 0x150 / 4
    *r1 = r2;
    r2 = *r1;
    *(r0 + 0x53) = r2; // 0x14c / 4
}

UnkStruct_0205467c *func_0205467c(UnkStruct_0205467c *p)
{
    func_02054c2c(p);
    p->unk_00 = (unsigned int) ((int *) data_020dd07c);
    p->unk_9C = (unsigned int) ((int *) data_020dd08c);
    p->unk_B8 = (unsigned int) ((int *) data_020dd09c);
    p->unk_158 = (unsigned int) &data_020dd184;
    p->unk_160 = 0;
    p->unk_164 = 0;
    p->unk_168 = 0x1000;
    func_02056ee0(p->arr170);
    p->unk_154 = 0;
    p->unk_1AC = 0;
    p->unk_1B0 = 0;
    return p;
}

struct UnkStruct_02054630 *func_02054630(struct UnkStruct_02054630 *self)
{
    self->unk_00 = ((char *) data_020dd07c);
    self->subA.ptr = ((char *) data_020dd08c);
    self->subB.ptr = ((char *) data_020dd09c);
    func_02056ed4(&self->subD);
    func_02057078(&self->subC);
    func_02054ad0(self);
    return self;
}

void *func_020545e0(void *self)
{
    *(void **) self = (void *) data_020dd07c;
    *(void **) ((char *) self + 0x9c) = (void *) data_020dd08c;
    *(void **) ((char *) self + 0xb8) = (void *) data_020dd09c;
    func_02056ed4((char *) self + 0x170);
    func_02057078((char *) self + 0x158);
    func_02054ad0(self);
    func_020edb3c(self);
    return self;
}

void func_020545b0(unsigned char *base, unsigned int bit)
{
    if (bit >= 32) {
        *(unsigned int *) (base + 0x1B0) |= 1u << (bit - 32);
    } else {
        *(unsigned int *) (base + 0x1AC) |= 1u << bit;
    }
}

void func_02054580(unsigned int *base, unsigned int bit)
{
    if (bit >= 32) {
        *((unsigned int *) ((char *) base + 0x1b0)) &= ~(1u << (bit - 32));
    } else {
        *((unsigned int *) ((char *) base + 0x1ac)) &= ~(1u << bit);
    }
}

unsigned int func_02054548(unsigned int *base, unsigned int index)
{
    if (index >= 32) {
        if (*(unsigned int *) ((unsigned char *) base + 0x1b0) & (1 << (index - 32))) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*(unsigned int *) ((unsigned char *) base + 0x1ac) & (1 << index)) {
            return 1;
        } else {
            return 0;
        }
    }
}

void func_02054524(void *self, int arg)
{
    if (*(int *) ((char *) self + 0x1a8) != 0) {
        func_02056aa0((char *) self + 0x170, arg);
    }
}

void func_02054474(UnkStruct_02054474 *self, void *param)
{
    unsigned char t;
    u32 bit1, bit2;
    Param *p = (Param *) param;

    if (func_01ffcc10(self, param) != 0) {
        return;
    }

    t = ((unsigned char *) p->ptr)[1];

    if (t >= 0x20) {
        bit1 = self->unk_1B0 & (1 << (t - 0x20));
    } else {
        bit1 = self->unk_1AC & (1 << t);
    }
    if (bit1) {
        func_02054a9c(self, (void *) self->unk_154);
        func_02054524(self, (int) param);
        return;
    }

    if (t >= 0x20) {
        bit2 = self->unk_150 & (1 << (t - 0x20));
    } else {
        bit2 = self->unk_14C & (1 << t);
    }
    if (bit2) {
        func_02054a9c(self, (void *) self->unk_F4);
        func_020549d8(self, param);
        return;
    }

    func_02054a9c(self, (void *) self->unk_B4);
    func_02054d80(self, param);
}

void func_02054430(void *p0, void *p1)
{
    if ((*(int *) (*(void **) ((unsigned char *) p1 + 0xb4)) & 4) != 0) {
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x4c) = 0;
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x50) = 0;
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x54) = 0;
    }
    if (*(int *) ((unsigned char *) p0 + 0x1a8) != 0) {
        func_02056b18((unsigned char *) p0 + 0x170, p1);
    }
}

void func_02054394(void *a0, void *a1)
{
    unsigned int f1b0, f1ac, f14c, f150, combined;
    unsigned char c;
    unsigned int shifted;

    if (func_01ffcc10(a0, a1)) {
        return;
    }

    f1b0 = *(unsigned int *) ((char *) a0 + 0x1b0);
    f1ac = *(unsigned int *) ((char *) a0 + 0x1ac);
    f14c = *(unsigned int *) ((char *) a0 + 0x14c);
    f150 = *(unsigned int *) ((char *) a0 + 0x150);
    combined = f1b0 | (f1ac | (f14c | f150));

    if (combined == 0) {
        func_02054d14(a0, a1);
        return;
    }

    c = ((unsigned char *) (*(void **) a1))[1];
    shifted = 1u << (c & 0x1f);

    if ((combined & shifted) == 0) {
        func_02054d14(a0, a1);
        return;
    }

    if ((int) func_02054548((unsigned int *) a0, c)) {
        func_02054430(a0, a1);
        return;
    }
    if (func_020549fc(a0, c)) {
        func_02054944(a0, a1);
        return;
    }
    func_02054d14(a0, a1);
}

int func_02054354(int *obj, int arg)
{
    int val;
    int *p;

    if (!func_020548cc(obj, arg)) {
        return 0;
    }
    val = func_02056548(*(int *) ((char *) obj + 0x5c), &data_020dd030, arg);
    p = (int *) ((char *) obj + 0x154);
    *p = val;
    return *p != 0;
}

void func_020542e0(struct Object *self)
{
    func_02054860(self);
    if (self->unk_1AC != 0 || self->unk_1B0 != 0) {
        if (func_02056e84(&self->unk_170) != 0 && (self->unk_04 & 0x8000) != 0) {
            func_02054170(self);
            self->unk_04 &= ~0x8000;
        }
        func_02056ffc(&self->unk_158);
        *self->unk_154 = self->unk_160;
    }
}

void func_020542c0(int a, int b, int c, int d, int e, unsigned short f, unsigned short g)
{
    func_02054828(a, b, c, d, e, f, g);
}

void func_02054240(struct UnkStruct_02054240 *obj, int p2, int p3, int p4, int p5, unsigned short p6, unsigned short p7,
                   int p8)
{
    func_02056e60(&obj->unk_170, p3);
    if (p7 == 0) {
        p7 = func_020550b8(p4, p2);
    }
    func_02056fcc(&obj->unk_158, p7, p4, p5, p6);
    NNS_G3dAnmObjInit(obj->unk_154, p2, obj->unk_5C, 0);
    if (p8 != 0) {
        obj->unk_04 |= 0x8000;
    } else {
        obj->unk_04 &= ~0x8000;
    }
}

int func_02054230(int param)
{
    return func_02056f94(param + 0x158);
}
