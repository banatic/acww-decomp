/* field_actor_8: 11 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220f6d8 @ 0x0220f6d8, 0x2 bytes, Thumb
 * func_ov003_0220f684 @ 0x0220f684, 0x54 bytes, Thumb
 * func_ov003_0220f658 @ 0x0220f658, 0x2c bytes, Thumb
 * func_ov003_0220f5f8 @ 0x0220f5f8, 0x60 bytes, Thumb
 * func_ov003_0220f590 @ 0x0220f590, 0x68 bytes, Thumb
 * func_ov003_0220f57c @ 0x0220f57c, 0x12 bytes, Thumb
 * func_ov003_0220f538 @ 0x0220f538, 0x44 bytes, Thumb
 * func_ov003_0220f524 @ 0x0220f524, 0x12 bytes, Thumb
 * func_ov003_0220f508 @ 0x0220f508, 0x1a bytes, Thumb
 * func_ov003_0220f4f0 @ 0x0220f4f0, 0x18 bytes, Thumb
 * func_ov003_0220f4a8 @ 0x0220f4a8, 0x48 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x7d6 - 0x90];
    short unk_7D6;
} UnkStruct_0220f658;

typedef struct {
    short v[4];
} LocalVec;

typedef struct {
    char pad_00[0x8e];
    short short_8e;
    char pad_90[0x2d0 - 0x90];
    char sub_2d0[0x7e0 - 0x2d0];
    unsigned char unk_7E0;
    char pad_7E1[0x0f];
    unsigned int unk_7F0;
    char pad_7F4[8];
    unsigned int unk_7FC;
} Objs;

struct UnkStruct_0220f590;

typedef struct {
    int a;
    int b;
} UnkStruct_0220f590_2;

typedef struct {
    int pad_00;
    int a;
    int b;
} UnkStruct_0220f590_3;

struct UnkStruct_0220f590 {
    unsigned char pad_00[0x7d4];
    UnkStruct_0220f590_3 sub;
    unsigned char pad_7E0[0x20];
    int unk_800;
};

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
} UnkStruct_0220f538;

typedef struct {
    u8 pad_00[0xc];
    UnkStruct_0220f538 sub;
    u8 pad_12[0xa];
} Buf;

struct UnkStruct_0220f524 {
    int a;
    int b;
    int c;
};

struct S_22f508 {
    int unk_00;
    int unk_04;
    int unk_08;
};

struct UnkStruct_0220f4a8 {
    int x;
    int y;
    int z;
};

extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern void func_ov003_02224384(unsigned int, unsigned int *, int);
extern void func_0200f268(void *, int);
extern unsigned int *func_0200f27c(void *, int);
extern int func_020113e0(LocalVec *vec, short value);
extern void func_020110a0(void *object, short *values);
extern int func_02056f94(void *p);
extern int func_02008258(void *self, unsigned int val);
extern int func_02008dc0(void *self, short a, int b, int c);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern int func_02073908(int *a, int b);
extern void func_02010d64(struct UnkStruct_0220f590 *self);
extern int func_0200f530(struct UnkStruct_0220f590 *self, UnkStruct_0220f590_2 *local);
extern int *data_020ccf94;
extern unsigned int func_0200e92c(Buf *);
extern void func_0200e90c(Buf *, int, unsigned int, short);
extern void *func_0200e894(void *, Buf *);
extern int func_0200e91c(Buf *);
extern void func_02077950(int a, int b, int c, int d, int e);
extern void func_02077928(int a, char *b, char *c, char *d, char *e);
extern void func_020109a0(void *a, int b, int c, unsigned short d);

void func_ov003_0220f6d8(void *receiver, int event) {}

void func_ov003_0220f684(void *obj)
{
    unsigned int local[2];
    unsigned int a, b;
    struct UnkStruct_0220f684 {
        char pad[4];
        unsigned int a;
        unsigned int b;
    } *s;

    func_02010f5c(obj);
    if (func_02056f28((char *) obj + 0x2d0, 5) == 0) {
        return;
    }

    s = (struct UnkStruct_0220f684 *) ((char *) obj + 0x7d4);
    b = s->b;
    a = s->a;
    local[0] = a;
    local[1] = b;

    func_ov003_02224384(*(unsigned int *) ((char *) obj + 0x800), local, 3);
    func_0200f268(obj, 0x12);
    func_0200f27c(obj, 9);
}

void func_ov003_0220f658(UnkStruct_0220f658 *self)
{
    LocalVec vec;
    vec.v[0] = self->unk_8E;
    func_020113e0(&vec, self->unk_7D6);
    func_020110a0((void *) (self), (short *) (&vec));
}

void func_ov003_0220f5f8(Objs *self)
{
    unsigned char flag = self->unk_7E0;
    if (func_02056f94(&self->sub_2d0)) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        if (flag) {
            func_02008dc0(self, self->short_8e, 6, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}

void func_ov003_0220f590(struct UnkStruct_0220f590 *self)
{
    UnkStruct_0220f590_3 *sub = &self->sub;
    int b;
    UnkStruct_0220f590_2 local;

    func_ov003_0220f684((void *) self);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_0220f658((UnkStruct_0220f658 *) self);
        func_02010d64(self);
    } else {
        b = sub->b;
        local.a = sub->a;
        local.b = b;
        if (func_0200f530(self, &local) != 0) {
            func_ov003_0220f658((UnkStruct_0220f658 *) self);
        }
        func_02010d64(self);
    }
    func_ov003_0220f5f8((Objs *) self);
}

void func_ov003_0220f57c(int *out, Vec v)
{
    out[0] = v.x;
    out[1] = v.y;
    out[2] = v.z;
}

void *func_ov003_0220f538(void *a0, Vec v, unsigned int a4, short a5)
{
    Buf buf;
    void *ret;

    func_0200e92c(&buf);
    func_0200e90c(&buf, 0x6a, a4, a5);
    func_ov003_0220f57c((int *) (&buf.sub), v);
    ret = func_0200e894(a0, &buf);
    func_0200e91c(&buf);
    return ret;
}

void func_ov003_0220f524(struct UnkStruct_0220f524 *p, struct UnkStruct_0220f524 v)
{
    p->a = v.a;
    p->b = v.b;
    p->c = v.c;
}

void func_ov003_0220f508(int a, struct S_22f508 *p)
{
    func_02077950(a, p->unk_00, p->unk_04, p->unk_08, 0);
}

void func_ov003_0220f4f0(int a, char *b)
{
    char buf[8];
    func_02077928(a, b, b + 4, b + 8, buf);
}

void func_ov003_0220f4a8(void *self, void *other, int previous)
{
    struct UnkStruct_0220f4a8 local;
    struct UnkStruct_0220f4a8 *src;

    func_020109a0(self, 0x7a, 3, 0);
    src = (struct UnkStruct_0220f4a8 *) ((char *) other + 0xc);
    local.x = src->x;
    local.y = src->y;
    local.z = src->z;
    func_ov003_0220f524((struct UnkStruct_0220f524 *) ((char *) self + 0x7d4), *(struct UnkStruct_0220f524 *) &local);
    func_ov003_0220f508((int) ((char *) self + 0x8f0), (struct S_22f508 *) (&local));
}
