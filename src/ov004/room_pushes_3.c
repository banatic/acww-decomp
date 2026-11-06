/* room_pushes_3: 22 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223cbe4 @ 0x0223cbe4, 0x2 bytes, Thumb
 * func_ov004_0223cbe0 @ 0x0223cbe0, 0x2 bytes, Thumb
 * func_ov004_0223cbb8 @ 0x0223cbb8, 0x28 bytes, Thumb
 * func_ov004_0223cb60 @ 0x0223cb60, 0x56 bytes, Thumb
 * func_ov004_0223cb5c @ 0x0223cb5c, 0x4 bytes, Thumb
 * func_ov004_0223cb58 @ 0x0223cb58, 0x4 bytes, Thumb
 * func_ov004_0223cb54 @ 0x0223cb54, 0x4 bytes, Thumb
 * func_ov004_0223cb30 @ 0x0223cb30, 0x22 bytes, Thumb
 * func_ov004_0223cb2c @ 0x0223cb2c, 0x4 bytes, Thumb
 * func_ov004_0223cb28 @ 0x0223cb28, 0x4 bytes, Thumb
 * func_ov004_0223cb24 @ 0x0223cb24, 0x4 bytes, Thumb
 * func_ov004_0223cb20 @ 0x0223cb20, 0x4 bytes, Thumb
 * func_ov004_0223cb18 @ 0x0223cb18, 0x6 bytes, Thumb
 * func_ov004_0223cb10 @ 0x0223cb10, 0x8 bytes, Thumb
 * func_ov004_0223cadc @ 0x0223cadc, 0x34 bytes, Thumb
 * func_ov004_0223ca9c @ 0x0223ca9c, 0x40 bytes, Thumb
 * func_ov004_0223ca6c @ 0x0223ca6c, 0x2e bytes, Thumb
 * func_ov004_0223c9d4 @ 0x0223c9d4, 0x96 bytes, Thumb
 * func_ov004_0223c9b4 @ 0x0223c9b4, 0x1e bytes, Thumb
 * func_ov004_0223c994 @ 0x0223c994, 0x1e bytes, Thumb
 * func_ov004_0223c984 @ 0x0223c984, 0x10 bytes, Thumb
 * func_ov004_0223c974 @ 0x0223c974, 0x10 bytes, Thumb
 */

#include "types.h"

#define g_x0 (*(int *) 0xffffc000)

typedef struct {
    long x, y, z;
} UnkStruct_0223cb60;

typedef struct {
    long id;
    UnkStruct_0223cb60 a;
    UnkStruct_0223cb60 b;
    long unk_1C;
    UnkStruct_0223cb60 c;
    UnkStruct_0223cb60 d;
    short unk_38;
    short pad_3A;
    long unk_3C;
} UnkStruct_0223cb60_2;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0223cb5c;

typedef struct {
    unsigned char pad_00[28];
    unsigned long unk_1C;
} UnkStruct_0223cb2c;

typedef struct {
    unsigned char pad_00[60];
    unsigned long unk_3C;
} UnkStruct_0223cb20;

struct Slot {
    u8 pad_00[0x40];
};

extern int func_020ea990(void *argument0, void *argument1);
extern char data_ov004_02259784[];
extern int func_ov004_0223c72c(void);
extern int func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(int a, int b);
extern int func_ov004_0223cd58(int *argument0, unsigned int argument1);
extern int func_ov004_0220fde0(void *p);
extern int func_02053b2c(int x);
extern int func_ov004_0220fd98(void *p);
extern int func_ov004_0220ebe0(int arg0, int arg1);
extern int func_ov004_0220cf90(void *argument0, int argument1);

void func_ov004_0223cbe4(void *object) {}

void func_ov004_0223cbe0(void *object) {}

void *func_ov004_0223cbb8(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self) = -0x1;
    *(void **) (self + 0x4) = 0x0;
    *(void **) (self + 0x8) = 0x0;
    *(void **) (self + 0xc) = 0x0;
    *(void **) (self + 0x10) = 0x0;
    *(void **) (self + 0x14) = 0x0;
    *(void **) (self + 0x18) = 0x0;
    *(void **) (self + 0x1c) = 0x0;
    *(void **) (self + 0x20) = 0x0;
    *(void **) (self + 0x24) = 0x0;
    *(void **) (self + 0x28) = 0x0;
    *(void **) (self + 0x2c) = 0x0;
    *(void **) (self + 0x30) = 0x0;
    *(void **) (self + 0x34) = 0x0;
    *(u16 *) (self + 0x38) = 0x0;
    *(int *) (self + 0x3c) = 0x4;
    return self;
}

void func_ov004_0223cb60(UnkStruct_0223cb60_2 *out, long id, UnkStruct_0223cb60 *a, UnkStruct_0223cb60 *b, long e,
                         UnkStruct_0223cb60 *c, UnkStruct_0223cb60 *d, short g, long h)
{
    if (id == -1) {
        return;
    }
    out->id = id;
    out->a.x = a->x;
    out->a.y = a->y;
    out->a.z = a->z;
    out->b.x = b->x;
    out->b.y = b->y;
    out->b.z = b->z;
    out->unk_1C = e;
    out->c.x = c->x;
    out->c.y = c->y;
    out->c.z = c->z;
    out->d.x = d->x;
    out->d.y = d->y;
    out->d.z = d->z;
    out->unk_38 = g;
    out->unk_3C = h;
}

unsigned long func_ov004_0223cb5c(UnkStruct_0223cb5c *p)
{
    return p->unk_00;
}

void *func_ov004_0223cb58(void *self)
{
    return (char *) self + 0x4;
}

void *func_ov004_0223cb54(void *self)
{
    return (char *) self + 0x10;
}

int func_ov004_0223cb30(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = (int) func_ov004_0223cb54(self);
    return func_020ea990((void *) (v1), (void *) ((int) func_ov004_0223cb58(self)));
}

unsigned long func_ov004_0223cb2c(UnkStruct_0223cb2c *p)
{
    return p->unk_1C;
}

void *func_ov004_0223cb28(void *self)
{
    return (char *) self + 0x20;
}

void *func_ov004_0223cb24(void *self)
{
    return (char *) self + 0x2c;
}

unsigned long func_ov004_0223cb20(UnkStruct_0223cb20 *p)
{
    return p->unk_3C;
}

int func_ov004_0223cb18(void *self)
{
    return *(short *) ((char *) self + 0x38);
}

void *func_ov004_0223cb10(void)
{
    return data_ov004_02259784;
}

void *func_ov004_0223cadc(char *self, int i)
{
    char *p;
    if (func_ov004_0223c72c() != 0) {
        p = self + (i & 1) * 0x40;
        if ((int) func_ov004_0223cb5c((UnkStruct_0223cb5c *) p) != -1) {
            return p;
        }
    }
    return 0;
}

struct Slot *func_ov004_0223ca9c(struct Slot *self, int arg)
{
    int id;
    u32 i;

    id = func_ov004_0223cd78(func_ov004_0223ce84(), arg);
    if (id != -1) {
        for (i = 0; i < 2; i++) {
            if (id == (int) func_ov004_0223cb5c((UnkStruct_0223cb5c *) (&self[i]))) {
                return &self[i];
            }
        }
    }
    return 0;
}

int func_ov004_0223ca6c(char *self, int index)
{
    // DECLS
    int v1;
    int v2;
    // ENDDECLS
    v1 = (int) func_ov004_0223cadc((char *) (self), (int) (index));
    if (v1 != 0x0) {
        v2 = func_ov004_0223ce84();
        return func_ov004_0223cd58((int *) (v2),
                                   (unsigned int) ((int) func_ov004_0223cb5c((UnkStruct_0223cb5c *) ((void *) (v1)))));
    }
    return 0x0;
}

void func_ov004_0223c9d4(void *self)
{
    void *a, *b;
    int ok;

    a = (void *) func_ov004_0223ca6c((char *) self, 1);
    b = func_ov004_0223cadc((char *) self, 1);
    if (a != 0 && b != 0) {
        ok = 1;
        if (func_02053b2c(func_ov004_0220fde0(a)) != 0 && (int) func_ov004_0223cb20((UnkStruct_0223cb20 *) b) != 0) {
            ok = 0;
        }
        if (ok != 0 && func_ov004_0220fd98(a) != 0) {
            return;
        }
    }
    a = (void *) func_ov004_0223ca6c((char *) self, 0);
    b = func_ov004_0223cadc((char *) self, 0);
    if (a != 0 && b != 0) {
        ok = 1;
        if (func_02053b2c(func_ov004_0220fde0(a)) != 0 && (int) func_ov004_0223cb20((UnkStruct_0223cb20 *) b) != 0) {
            ok = 0;
        }
        if (ok != 0 && func_ov004_0220fd98(a) != 0) {
            return;
        }
    }
}

int func_ov004_0223c9b4(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223ca6c((char *) ((char *) (self)), (int) ((int) (0x0)));
    if (v1 != 0x0) {
        return func_ov004_0220ebe0(v1, a1);
    }
    return 0x0;
}

int func_ov004_0223c994(char *self, int a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_ov004_0223ca6c((char *) ((char *) (self)), (int) ((int) (0x0)));
    if (v1 != 0x0) {
        return func_ov004_0220cf90((void *) (v1), (int) (a1));
    }
    return 0x0;
}

int func_ov004_0223c984(int p0)
{
    return func_ov004_0223c9b4((char *) p0, (int) &g_x0);
}

void func_ov004_0223c974(int p0)
{
    func_ov004_0223c994((char *) p0, (int) &g_x0);
}
