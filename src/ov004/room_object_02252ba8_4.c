/* room_object_02252ba8_4: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02215360 @ 0x02215360, 0x14 bytes, Thumb
 * func_ov004_02215350 @ 0x02215350, 0x10 bytes, Thumb
 * func_ov004_0221533c @ 0x0221533c, 0x14 bytes, Thumb
 * func_ov004_022152f8 @ 0x022152f8, 0x44 bytes, Thumb
 * func_ov004_022152d0 @ 0x022152d0, 0x28 bytes, Thumb
 * func_ov004_02215298 @ 0x02215298, 0x38 bytes, Thumb
 * func_ov004_02215270 @ 0x02215270, 0x28 bytes, Thumb
 * func_ov004_0221524c @ 0x0221524c, 0x24 bytes, Thumb
 * func_ov004_02215228 @ 0x02215228, 0x24 bytes, Thumb
 * func_ov004_02215200 @ 0x02215200, 0x28 bytes, Thumb
 * func_ov004_022151d8 @ 0x022151d8, 0x28 bytes, Thumb
 * func_ov004_022151c4 @ 0x022151c4, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02215360 UnkStruct_02215360;

struct UnkStruct_02215360 {
    void (**vt)(UnkStruct_02215360 *);
};

struct UnkStruct_022152f8 {
    int a;
    int b;
    int c;
};

extern void func_02054d60(char *p, int b);
extern void func_02054cf4(void *p, unsigned char *c);
extern void func_02004110(void *, unsigned short parameter1);
extern int func_020040bc(void *dst, int *v);
extern void func_020040b4(void *);
extern void func_02004108(void *, int);
extern void func_020040ac(void *, int);
extern unsigned char func_020040a4(char *receiver);
extern int func_0200409c(void *object);
extern const u8 data_ov004_02247678[];

int func_ov004_02215270(char *self);

int func_ov004_02215360(UnkStruct_02215360 *self)
{
    self->vt[32](self);
    return 1;
}

int func_ov004_02215350(char *arg0)
{
    func_ov004_02215270((char *) arg0);
    return 1;
}

void func_ov004_0221533c(char *self, int a, int b)
{
    func_02054d60(self + 0x538, b);
}

void func_ov004_022152f8(unsigned char *self, int idx, unsigned char *c)
{
    unsigned char *base, *p, *q;
    struct UnkStruct_022152f8 *v;
    int *dst;
    int off, n;

    base = *(unsigned char **) (c + 0xd4);
    off = *(unsigned short *) (base + 6);
    n = *(unsigned short *) (base + off);
    p = base + off + n * idx;
    q = base + *(int *) (p + 4);
    v = (struct UnkStruct_022152f8 *) (q + 4);
    dst = *(int **) (c + 0xb4);
    dst[0x13] = v->a;
    dst[0x14] = v->b;
    dst[0x15] = v->c;
    func_02054cf4(self + 0x538, c);
}

int func_ov004_022152d0(char *self, unsigned short arg1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) == 0x0) {
        func_02004110(self + 0x844, arg1);
        *(u8 *) (self + 0x858) = 0x1;
        return 0x858;
    }
    return *(u8 *) (self + 0x858);
}

int func_ov004_02215298(char *self, int *src)
{
    int t[3];

    if (*(u8 *) (self + 0x858) != 0) {
        t[0] = src[0];
        t[1] = src[1];
        t[2] = src[2];
        return func_020040bc(self + 0x844, t);
    }
    return -1;
}

int func_ov004_02215270(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        func_020040b4(self + 0x844);
        *(u8 *) (self + 0x858) = 0x0;
        return 0x858;
    }
    return *(u8 *) (self + 0x858);
}

void func_ov004_0221524c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        func_02004108(self + 0x844, a1);
    }
}

void func_ov004_02215228(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        func_020040ac(self + 0x844, a1);
    }
}

int func_ov004_02215200(char *self)
{
    if (*(u8 *) (self + 0x858) != 0x0) {
        return func_020040a4(self + 0x844);
    }
    return 0x0;
}

int func_ov004_022151d8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x858) != 0x0) {
        return func_0200409c(self + 0x844);
    }
    return -0x1;
}

u8 func_ov004_022151c4(void *self, unsigned int i)
{
    if (i < 3) {
        return data_ov004_02247678[i];
    }
    return 0;
}
