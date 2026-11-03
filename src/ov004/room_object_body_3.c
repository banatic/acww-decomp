/* room_object_body_3: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220fde0 @ 0x0220fde0, 0xc bytes, Thumb
 * func_ov004_0220fdc8 @ 0x0220fdc8, 0x18 bytes, Thumb
 * func_ov004_0220fdc4 @ 0x0220fdc4, 0x4 bytes, Thumb
 * func_ov004_0220fd98 @ 0x0220fd98, 0x2c bytes, Thumb
 * func_ov004_0220fd8c @ 0x0220fd8c, 0xc bytes, Thumb
 * func_ov004_0220fc98 @ 0x0220fc98, 0xf4 bytes, Thumb
 * func_ov004_0220fb90 @ 0x0220fb90, 0x108 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int m[12];
} Mtx43;

extern void func_ov004_0220d290(unsigned char *self, int pending);
extern Mtx43 data_021fbe48;
extern int func_ov004_0220d4c8(void *p);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0220d4c0(void *p);
extern char *func_ov004_0223cd58(int *a, int b);
extern Vec3 *func_ov004_0220d4bc(void *p);
extern int func_ov004_0220d4b4(void *p);
extern void func_020e9868(Mtx43 *m, int a, int b, int c);
extern void func_020e9744(Mtx43 *m, int a);
extern void VEC_Add(Vec3 *d, void *a, Vec3 *b);
extern void func_020e96c8(Mtx43 *m, int a, int b, int c);
extern short data_ov004_02256c40;
extern short data_ov004_02256c3c;
extern int func_ov004_0220e5c8(void *self);
extern void func_020e9774(Mtx43 *m, int a);
extern int FX_MulFunc(int a, int b);
extern int func_02053658(void *p);

int func_ov004_0220fde0(char *self)
{
    // DECLS
    // ENDDECLS
    return *(int *) (self + 0x284);
}

int func_ov004_0220fdc8(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x77c) = a2;
    *(u8 *) (self + 0x77d) = 0x0;
    return 0x1;
}

int func_ov004_0220fdc4(void)
{
    return 0;
}

int func_ov004_0220fd98(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x77d) == 0x0) {
        func_ov004_0220d290((unsigned char *) self + 0x740, 0x1);
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0220fd8c(char *self)
{
    // DECLS
    // ENDDECLS
    return *(u8 *) (self + 0x288);
}

void func_ov004_0220fc98(char *self, void *p1, int p2)
{
    Vec3 t;
    char *o;
    int px, py, pz;
    short h;

    if (func_ov004_0220d4c8(self + 0x17c) != 0) {
        o = func_ov004_0223cd58(func_ov004_0223ce84(), func_ov004_0220d4c0(self + 0x17c));
        if (p1 != 0 || p2 != 0) {
            func_ov004_0220fc98(o, p1, p2);
        } else {
            data_021fbe48 = *(Mtx43 *) (o + 0x254);
        }
        pz = func_ov004_0220d4bc(self + 0x17c)->z;
        py = func_ov004_0220d4bc(self + 0x17c)->y;
        px = func_ov004_0220d4bc(self + 0x17c)->x;
        func_020e9868(&data_021fbe48, px, py, pz);
        func_020e9744(&data_021fbe48, func_ov004_0220d4b4(self + 0x17c));
    } else {
        t.x = *(int *) (self + 0x5c);
        t.y = *(int *) (self + 0x60);
        t.z = *(int *) (self + 0x64);
        if (p1 != 0) {
            VEC_Add(&t, p1, &t);
        }
        h = (short) (*(short *) (self + 0x8e) + p2);
        func_020e96c8(&data_021fbe48, t.x, t.y, t.z);
        func_020e9744(&data_021fbe48, h);
        func_020e9868(&data_021fbe48, *(int *) (self + 0x144), *(int *) (self + 0x148), *(int *) (self + 0x14c));
    }
}

void func_ov004_0220fb90(char *self)
{
    int q;

    if (func_ov004_0220e5c8(self) != 0) {
        func_020e96c8(&data_021fbe48, *(int *) (self + 0x5c), *(int *) (self + 0x60), *(int *) (self + 0x64));
        func_020e9774(&data_021fbe48, data_ov004_02256c40);
        func_020e9744(&data_021fbe48, (short) (*(short *) (self + 0x8e) + data_ov004_02256c3c));
        if (*(int *) (self + 0x784) == 1) {
            func_020e9868(&data_021fbe48, FX_MulFunc(*(int *) (self + 0x150), -0x1000), 0, 0);
        }
        q = 0x64 * func_02053658((void *) func_ov004_0220fde0((char *) self)) - 0x258;
        func_020e9868(&data_021fbe48, 0, q, 0);
        *(Mtx43 *) (self + 0x59c) = data_021fbe48;
    } else {
        func_ov004_0220fc98((char *) self, 0, 0);
        *(Mtx43 *) (self + 0x254) = data_021fbe48;
        if (*(int *) (self + 0x784) == 1) {
            func_020e9868(&data_021fbe48, FX_MulFunc(0x1000 - *(int *) (self + 0x150), 0x1000), 0, 0);
        }
        *(Mtx43 *) (self + 0x59c) = data_021fbe48;
    }
}
