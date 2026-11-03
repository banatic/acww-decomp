/* rmo_model: 17 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222c3d4 @ 0x0222c3d4, 0x20 bytes, Thumb
 * func_ov004_0222c3c4 @ 0x0222c3c4, 0x10 bytes, Thumb
 * func_ov004_0222c3b4 @ 0x0222c3b4, 0x10 bytes, Thumb
 * func_ov004_0222c3a4 @ 0x0222c3a4, 0x10 bytes, Thumb
 * func_ov004_0222c3a0 @ 0x0222c3a0, 0x4 bytes, Thumb
 * func_ov004_0222c398 @ 0x0222c398, 0x6 bytes, Thumb
 * func_ov004_0222c394 @ 0x0222c394, 0x2 bytes, Thumb
 * func_ov004_0222c348 @ 0x0222c348, 0x4c bytes, Thumb
 * func_ov004_0222c340 @ 0x0222c340, 0x6 bytes, Thumb
 * func_ov004_0222c33c @ 0x0222c33c, 0x4 bytes, Thumb
 * func_ov004_0222c32c @ 0x0222c32c, 0x10 bytes, Thumb
 * func_ov004_0222c31c @ 0x0222c31c, 0x10 bytes, Thumb
 * func_ov004_0222c314 @ 0x0222c314, 0x8 bytes, Thumb
 * func_ov004_0222c2f8 @ 0x0222c2f8, 0x1c bytes, Thumb
 * func_ov004_0222c2f0 @ 0x0222c2f0, 0x8 bytes, Thumb
 * func_ov004_0222c2dc @ 0x0222c2dc, 0x12 bytes, Thumb
 * func_ov004_0222c2c8 @ 0x0222c2c8, 0x12 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_0222c3a0;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0222c398;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0222c340;

typedef struct {
    unsigned long unk_00;
} UnkStruct_0222c33c;

typedef struct {
    int x, y, z;
} Vec3;

extern void func_020e993c(int, int);
extern void *data_021c9b24;
extern void *func_02064b2c(void *a, int b, int c, int d);
extern int func_021077e8(void *h);
extern int func_02056064(int t, int k);
extern int func_020561cc(int t, int p);
extern void func_020e9898(void *h);
extern int data_021fbe94;
extern void func_020f5958(int);
extern void func_020f5948(int);
extern void func_0200451c(void *parameter0);
extern void func_020044d0(void *a, Vec3 *v);
extern int func_020044a0(void *parameter0);
extern int func_020044c0(void *, int, int, int);
extern int func_020044b0(void *, int, int, int);

void func_ov004_0222c3d4(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e993c(*(int *) ((char *) &data_021c9b24), *(int *) (self));
        *(void **) (self) = 0x0;
    }
}

int func_ov004_0222c3c4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((u32) a1 < 0xd) {
        return *(int *) (self + (a1 << 2) + 0x8);
    }
    return 0x0;
}

int func_ov004_0222c3b4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((u32) a1 < 0xd) {
        return *(int *) (self + (a1 << 2) + 0x3c);
    }
    return 0x0;
}

int func_ov004_0222c3a4(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((u32) a1 < 0xd) {
        return *(int *) (self + (a1 << 2) + 0x70);
    }
    return 0x0;
}

unsigned long func_ov004_0222c3a0(UnkStruct_0222c3a0 *p)
{
    return p->unk_04;
}

void func_ov004_0222c398(UnkStruct_0222c398 *p)
{
    p->unk_00 = 0;
}

void func_ov004_0222c394(void *object) {}

int func_ov004_0222c348(int *out, void *a)
{
    void *h;
    int t;
    h = func_02064b2c(a, data_021fbe94, -4, 0);
    if (h != 0) {
        t = func_021077e8(h);
        func_02056064(t, 0);
        *out = func_020561cc(t, (*(int *) &data_021c9b24));
        func_020e9898(h);
        return 1;
    }
    return 0;
}

void func_ov004_0222c340(UnkStruct_0222c340 *p)
{
    p->unk_00 = 0;
}

unsigned long func_ov004_0222c33c(UnkStruct_0222c33c *p)
{
    return p->unk_00;
}

int func_ov004_0222c32c(int arg)
{
    func_020f5958(arg);
    return arg;
}

int func_ov004_0222c31c(int arg)
{
    func_020f5948(arg);
    return arg;
}

void func_ov004_0222c314(void *arg0)
{
    func_0200451c((void *) arg0);
}

void func_ov004_0222c2f8(void *a, Vec3 *src)
{
    Vec3 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;
    func_020044d0(a, &v);
}

void func_ov004_0222c2f0(void *arg0)
{
    func_020044a0((void *) arg0);
}

int func_ov004_0222c2dc(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    return func_020044c0(self, a1, 0x7f, 0x0);
}

int func_ov004_0222c2c8(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    return func_020044b0(self, a1, 0x7f, 0x0);
}
