/* room_object_parts_2: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220d3c8 @ 0x0220d3c8, 0x94 bytes, Thumb
 * func_ov004_0220d3b8 @ 0x0220d3b8, 0x10 bytes, Thumb
 * func_ov004_0220d3b4 @ 0x0220d3b4, 0x2 bytes, Thumb
 * func_ov004_0220d398 @ 0x0220d398, 0x1c bytes, Thumb
 * func_ov004_0220d38c @ 0x0220d38c, 0xa bytes, Thumb
 * func_ov004_0220d388 @ 0x0220d388, 0x2 bytes, Thumb
 * func_ov004_0220d318 @ 0x0220d318, 0x70 bytes, Thumb
 * func_ov004_0220d300 @ 0x0220d300, 0x18 bytes, Thumb
 * func_ov004_0220d2bc @ 0x0220d2bc, 0x44 bytes, Thumb
 * func_ov004_0220d2b8 @ 0x0220d2b8, 0x4 bytes, Thumb
 * func_ov004_0220d2a8 @ 0x0220d2a8, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int m[12];
} Mtx43;

typedef struct {
    char a;
    volatile signed char b;
    char c;
} UnkStruct_0220d3b8;

typedef struct {
    u8 a;
    volatile u8 b;
} UnkStruct_0220d38c;

typedef struct {
    unsigned char pad_00[1];
    unsigned char unk_01;
} UnkStruct_0220d2b8;

extern Mtx43 data_021fbe48;
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc10(void *o, int a, int b, int c);
extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(void *y, void *x);
extern void func_0204f794(Vec3 *v, int a, int b);
extern void func_ov004_0220fc98(void *x, int a, int b);
extern int MTX_Inverse43(Mtx43 *a, Mtx43 *b);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern int func_ov004_0220e5c8(void *b);
extern int func_ov004_0220e758(void *b, int *x, int *y, int c, int d);
extern int func_020b65c4(void);
extern int func_02052f14(int x, int y, int c, int d);
extern void func_ov004_0220d280(void *p, int a, int b);
extern void func_02052ee8(int x, int y, int c, int d, int t);

int func_ov004_0220d3c8(int *p0, int *p1, short *p2, int p3, int p4, short p5)
{
    Vec3 v;
    Vec3 out;
    void *x;
    int z;

    x = func_ov004_0223cc10(func_ov004_0223cd50(), p3, p4, 0);
    z = func_ov004_0223cd78(func_ov004_0223ce84(), x);
    if (x != 0 && z != -1) {
        func_0204f794(&v, p3, p4);
        v.y = *(int *) ((char *) x + 0x790);
        func_ov004_0220fc98(x, 0, 0);
        MTX_Inverse43(&data_021fbe48, &data_021fbe48);
        MTX_MultVec43(&v, &data_021fbe48, &out);
        *p0 = z;
        p1[0] = out.x;
        p1[1] = out.y;
        p1[2] = out.z;
        *p2 = (short) (p5 - *(short *) ((char *) x + 0x8e));
        return 1;
    }
    return 0;
}

void func_ov004_0220d3b8(UnkStruct_0220d3b8 *p)
{
    p->b = -1;
    p->a = p->b;
    p->c = 0;
}

void func_ov004_0220d3b4(void *object) {}

void func_ov004_0220d398(s8 *self, s8 a, s8 b)
{
    self[0] = a;
    self[1] = b;
    if (self[0] != -1 || self[1] != -1) {
        self[2] = 1;
    }
}

void func_ov004_0220d38c(UnkStruct_0220d38c *p)
{
    p->b = 0;
    p->a = p->b;
}

void func_ov004_0220d388(void *object) {}

void func_ov004_0220d318(void *a, char *b)
{
    int r;
    int x, y;

    r = 0;
    if (*(int *) (b + 0x76c) == 1 || func_ov004_0220e5c8(b) != 0) {
        if (*(u8 *) (b + 0x78d) == 0) {
            r = 1;
        } else {
            r = 0;
        }
    } else if (func_ov004_0220e758(b, &x, &y, 0, 0) != 0) {
        r = func_02052f14(x, y, *(u8 *) (b + 0x288), func_020b65c4());
    }
    func_ov004_0220d280(a, r, 0);
}

int func_ov004_0220d300(char *self, int a1)
{
    // DECLS
    int v1;
    u8 v2;
    // ENDDECLS
    v1 = func_ov004_0220e5c8((void *) ((char *) ((char *) (a1))));
    if (v1 == 0x0) {
        v2 = *(u8 *) (self + 0x1);
        *(u8 *) (self) = v2;
        return v2;
    }
    return v1;
}

void func_ov004_0220d2bc(unsigned char *self, unsigned char *b)
{
    int x, y;
    if (func_ov004_0220e5c8(b) == 0) {
        if (func_ov004_0220e758(b, &x, &y, 0, 0) != 0) {
            func_02052ee8(x, y, b[0x288], self[1], func_020b65c4());
        }
    }
}

unsigned char func_ov004_0220d2b8(UnkStruct_0220d2b8 *p)
{
    return p->unk_01;
}

int func_ov004_0220d2a8(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self) != *(u8 *) (self + 0x1)) {
        return 0x1;
    }
    return 0x0;
}
