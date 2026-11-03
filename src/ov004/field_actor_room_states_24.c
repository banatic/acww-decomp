/* field_actor_room_states_24: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02229980 @ 0x02229980, 0x60 bytes, Thumb
 * func_ov004_02229960 @ 0x02229960, 0x20 bytes, Thumb
 * func_ov004_02229928 @ 0x02229928, 0x36 bytes, Thumb
 * func_ov004_02229920 @ 0x02229920, 0x6 bytes, Thumb
 * func_ov004_022298e0 @ 0x022298e0, 0x40 bytes, Thumb
 * func_ov004_022298dc @ 0x022298dc, 0x2 bytes, Thumb
 * func_ov004_022298b8 @ 0x022298b8, 0x24 bytes, Thumb
 * func_ov004_02229860 @ 0x02229860, 0x58 bytes, Thumb
 * func_ov004_02229800 @ 0x02229800, 0x60 bytes, Thumb
 * func_ov004_022297d8 @ 0x022297d8, 0x26 bytes, Thumb
 * func_ov004_022297c4 @ 0x022297c4, 0x14 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02229980 {
    u8 pad_00[0x141];
    u8 alt;
    u8 pad_142[0x2d0 - 0x142];
    u8 sub[0x7f0 - 0x2d0];
    int src;
    u8 pad_7F4[0x7fc - 0x7f4];
    int handle;
};

struct UnkStruct_022298e0 {
    int a;
    int b;
    int c;
};

struct UnkStruct_022298e0_2 {
    u8 pad_00[0x5c];
    u8 head[0x8e - 0x5c];
    u8 body[0x7d4 - 0x8e];
    u8 out[4];
};

typedef struct {
    int a, b, c;
} UnkStruct_022298b8;

struct UnkStruct_02229860 {
    int x, y, z;
};

struct VV {
    volatile int x, y, z;
};

struct UnkStruct_02229800 {
    u8 pad_00[0x141];
    u8 alt;
    u8 pad_142[0x2d0 - 0x142];
    u8 sub[0x7f0 - 0x2d0];
    int src;
    u8 pad_7F4[0x7fc - 0x7f4];
    int handle;
};

extern int func_02056f94(void *p);
extern int func_02008258(struct UnkStruct_02229980 *self, int a);
extern int func_0200d4e8(struct UnkStruct_02229980 *self, int a, int b, int c);
extern int func_ov004_0222a23c(struct UnkStruct_02229980 *self, int a, int b, int c, int d);
extern void func_02010f5c(int);
extern void func_02010d64(int);
extern int func_02010ca4(int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern int data_ov004_02254afc;
extern void func_020109a0(struct UnkStruct_022298e0_2 *self, int a, int b, unsigned short d);
extern void func_0200fa1c(struct UnkStruct_022298e0 *v, struct UnkStruct_022298e0_2 *self, void *a, void *b, void *c);
extern int func_0201100c(void *self);

void func_ov004_02229980(struct UnkStruct_02229980 *self)
{
    if (func_02056f94(&self->sub)) {
        self->handle = func_02008258(self, self->src);
        if (self->alt) {
            func_ov004_0222a23c(self, 1, 0, 5, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}

void func_ov004_02229960(int arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
    func_02010ca4(arg);
    func_ov004_02229980((struct UnkStruct_02229980 *) arg);
}

int func_ov004_02229928(void *a0, int a1, int a2)
{
    unsigned char buffer[0x20];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x23, a1, a2);
    result = func_0200e894(a0, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov004_02229920(void *p, int a, int b)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
}

void func_ov004_022298e0(struct UnkStruct_022298e0_2 *self, void *message, int previous)
{
    struct UnkStruct_022298e0 v;

    func_020109a0(self, 0x20, 3, 0);
    func_0200fa1c(&v, self, &self->head, &self->body, &data_ov004_02254afc);
    func_ov004_02229920(&self->out, v.a, v.c);
}

void func_ov004_022298dc(void *callbackObject, int event) {}

void func_ov004_022298b8(char *self)
{
    UnkStruct_022298b8 *q = (UnkStruct_022298b8 *) (self + 0x5c);
    int *p = (int *) (self + 0x7d4);
    *(int *) (self + 0x5c) = p[0];
    q->c = p[1];
    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = q->b;
    *(int *) (self + 0x70) = q->c;
}

void func_ov004_02229860(char *self)
{
    struct VV old;
    struct UnkStruct_02229860 *p;
    int t, nx, nz, ox;

    p = (struct UnkStruct_02229860 *) (self + 0x5c);
    old.x = *(int *) (self + 0x5c);
    t = p->y;
    old.y = t;
    old.z = p->z;
    nz = *(int *) (self + 0x6fc);
    nx = *(int *) (self + 0x6f4);
    *(int *) (self + 0x5c) = nx;
    *(int *) (self + 0x60) = t;
    *(int *) (self + 0x64) = nz;
    *(int *) (self + 0x68) = *(int *) (self + 0x5c);
    *(int *) (self + 0x6c) = *(int *) (self + 0x60);
    *(int *) (self + 0x70) = *(int *) (self + 0x64);
    func_0201100c(self);
    ox = old.x;
    if (ox == *(int *) (self + 0x6f4)) {
        *(int *) (self + 0x64) = old.z;
    } else {
        *(int *) (self + 0x5c) = ox;
    }
}

void func_ov004_02229800(struct UnkStruct_02229800 *self)
{
    if (func_02056f94(&self->sub)) {
        self->handle = func_02008258((struct UnkStruct_02229980 *) self, self->src);
        if (self->alt) {
            func_ov004_0222a23c((struct UnkStruct_02229980 *) self, 1, 0, 5, -1);
        } else {
            func_0200d4e8((struct UnkStruct_02229980 *) self, 3, 1, -1);
        }
    }
}

void func_ov004_022297d8(void *p)
{
    func_02010f5c((int) p);
    func_ov004_02229860((char *) p);
    func_02010d64((int) p);
    func_02010ca4((int) p);
    func_ov004_02229800((struct UnkStruct_02229800 *) p);
}

void func_ov004_022297c4(void *p, int a, int b, short c, unsigned char d)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
    *(short *) ((char *) p + 8) = c;
    *((unsigned char *) p + 0xa) = d;
}
