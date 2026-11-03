/* furniture_mover_2: 9 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223b1c8 @ 0x0223b1c8, 0x64 bytes, Thumb
 * func_ov004_0223b1b8 @ 0x0223b1b8, 0x10 bytes, Thumb
 * func_ov004_0223b18c @ 0x0223b18c, 0x2a bytes, Thumb
 * func_ov004_0223b174 @ 0x0223b174, 0x18 bytes, Thumb
 * func_ov004_0223b158 @ 0x0223b158, 0x1a bytes, Thumb
 * func_ov004_0223b13c @ 0x0223b13c, 0x1a bytes, Thumb
 * func_ov004_0223b138 @ 0x0223b138, 0x4 bytes, Thumb
 * func_ov004_0223b128 @ 0x0223b128, 0xe bytes, Thumb
 * func_ov004_0223b0a8 @ 0x0223b0a8, 0x80 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0223b1c8 {
    int x, y, z;
};

struct UnkStruct_0223b1c8_2 {
    int w[12];
};

struct UnkStruct_0223b1c8_3 {
    u8 unk_00;
    u8 unk_01;
};

struct UnkStruct_0223b1c8_4 {
    u8 pad[0x4c];
    struct UnkStruct_0223b1c8 unk_4C;
};

struct UnkStruct_0223b1c8_5 {
    u8 pad[0x2c];
    struct UnkStruct_0223b1c8_2 *unk_2C;
};

struct UnkStruct_0223b1c8_6 {
    struct UnkStruct_0223b1c8_3 *unk_00;
    struct UnkStruct_0223b1c8_5 *unk_04;
    u8 pad[0xb4 - 8];
    struct UnkStruct_0223b1c8_4 *unk_B4;
};

typedef struct {
    char pad_00[0x24];
    void (*handler)(void *);
    char pad_28[0x92 - 0x28];
    unsigned char byte;
} UnkStruct_0223b1b8;

struct UnkStruct_0223b0a8 {
    int x, y, z;
};

struct UnkStruct_0223b0a8_2 {
    int w[12];
};

struct UnkStruct_0223b0a8_3 {
    u8 unk_00;
    u8 pad_01[3];
    int unk_04;
    int unk_08;
    int unk_0C;
    u8 pad_10[0x2c - 0x10];
    u8 unk_2C[0x90 - 0x2c];
    struct UnkStruct_0223b0a8_2 unk_90;
};

extern struct UnkStruct_0223b1c8_2 data_021fbe48;
extern void MTX_MultVec43(struct UnkStruct_0223b1c8 *a, struct UnkStruct_0223b1c8_2 *m, struct UnkStruct_0223b1c8 *out);
extern void *func_02055210(void *);
extern void *func_020551e0(void *);
extern int func_ov004_0223afd4(void *self);
extern int func_ov004_0223af18(void *self);
extern int func_ov004_0223ae0c(void *self);
extern int func_ov004_0223ae00(void *self);
extern int func_ov004_0223af08(void *self);
extern int func_ov004_0223afb4(void *self);
extern void func_02055060(void *p, int b, int c, int d, int e, int f);
extern void func_020e96c8(struct UnkStruct_0223b0a8_2 *m, int x, int y, int z);
extern void func_020e9744(struct UnkStruct_0223b0a8_2 *m, s16 a);

void *func_ov004_0223b138(void *self);
void *func_ov004_0223b128(char *self, char *a1);

void func_ov004_0223b1c8(struct UnkStruct_0223b1c8_6 *a)
{
    struct UnkStruct_0223b1c8 v;
    struct UnkStruct_0223b1c8 out;
    struct UnkStruct_0223b1c8_4 *b;
    struct UnkStruct_0223b1c8 *q;
    struct UnkStruct_0223b1c8_2 *m;
    struct UnkStruct_0223b1c8_2 *r;

    if (a == 0) {
        return;
    }
    if (a->unk_00->unk_01 != 0) {
        return;
    }
    b = a->unk_B4;
    q = &b->unk_4C;
    v.x = b->unk_4C.x;
    v.y = q->y;
    v.z = q->z;
    m = a->unk_04->unk_2C;
    if (m == 0) {
        return;
    }
    r = (struct UnkStruct_0223b1c8_2 *) func_ov004_0223b138((void *) m);
    data_021fbe48 = *r;
    MTX_MultVec43(&v, &data_021fbe48, &out);
    func_ov004_0223b128((char *) m, (char *) (&out));
}

void func_ov004_0223b1b8(UnkStruct_0223b1b8 *obj)
{
    obj->handler = (void (*)(void *)) func_ov004_0223b1c8;
    obj->byte = 2;
}

void *func_ov004_0223b18c(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055210(self + 0x2c);
    *(void **) (self + 0x10) = 0x0;
    *(void **) (self + 0x24) = 0x0;
    *(void **) (self + 0x28) = 0x0;
    *(void **) (self + 0x18) = 0x0;
    *(void **) (self + 0x1c) = 0x0;
    *(void **) (self + 0x20) = 0x0;
    *(void **) (self + 0x14) = 0x0;
    *(u8 *) (self) = 0x0;
    *(void **) (self + 0x4) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
    return self;
}

void *func_ov004_0223b174(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self) = 0x0;
    func_020551e0(self + 0x2c);
    return self;
}

void func_ov004_0223b158(void *self)
{
    func_ov004_0223afd4(self);
    func_ov004_0223af18(self);
    func_ov004_0223ae0c(self);
}

void func_ov004_0223b13c(void *self)
{
    func_ov004_0223ae00(self);
    func_ov004_0223af08(self);
    func_ov004_0223afb4(self);
}

void *func_ov004_0223b138(void *self)
{
    return (char *) self + 0x90;
}

void *func_ov004_0223b128(char *self, char *a1)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x4) = *(int *) (a1);
    *(int *) (self + 0x8) = *(int *) (a1 + 0x4);
    *(int *) (self + 0xc) = *(int *) (a1 + 0x8);
    return self;
}

int func_ov004_0223b0a8(struct UnkStruct_0223b0a8_3 *a, int b, u8 *c, struct UnkStruct_0223b0a8 *d, s16 e)
{
    if (*c == 0 && a->unk_00 == 0 && b != 0) {
        func_02055060(a->unk_2C, b, 1, 0x1000, 0, 0);
        a->unk_00 = 1;
        *c = a->unk_00;
        a->unk_04 = d->x;
        a->unk_08 = d->y;
        a->unk_0C = d->z;
        func_020e96c8(((struct UnkStruct_0223b0a8_2 *) &data_021fbe48), d->x, d->y, d->z);
        func_020e9744(((struct UnkStruct_0223b0a8_2 *) &data_021fbe48), e);
        a->unk_90 = (*(struct UnkStruct_0223b0a8_2 *) &data_021fbe48);
        return 1;
    }
    return 0;
}
