/* func_ov004_0220f9c8 @ 0x0220f9c8, 0xe4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov004_0220e5c8(void *self);
extern void func_ov004_0220faac(void *self, Vec3 *v);
extern void func_ov004_0220fefc(void *self, Vec3 *v);
extern void func_ov004_0220dfe8(void *p, void *self);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0220d4c0(void *p);
extern void func_ov004_0223cd58(int *a, int b);
extern void func_020321bc(void *p, int x, int z, int k, Vec3 *c, int h, Vec3 *b);
extern int func_ov004_0223cd78(int *a, int v);
extern int FX_MulFunc(int a, int b);
extern int func_020b67ac(void);
extern int func_020b6590(void);
extern void func_020b7dc8(int h, void *o, Vec3 *v, int x, int z, int y, int k, int f, int c);

void func_ov004_0220f9c8(char *self)
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
    int t;
    int f;
    int idx;

    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0220faac(self, &a);
        t = *(int *) (self + 0x15c);
        b.x = t;
        b.y = t;
        b.z = t;
        func_ov004_0220fefc(self, &c);
        if (*(u8 *) (self + 0x78c) == 0) {
            func_ov004_0220dfe8(self + 0x62c, self);
            func_ov004_0223cd58(func_ov004_0223ce84(), func_ov004_0220d4c0(self + 0x17c));
            func_020321bc(self + 0x62c, a.x, a.z, 0x4000, &c, *(short *) (self + 0x8e), &b);
        }
        idx = (u8) func_ov004_0223cd78(func_ov004_0223ce84(), (int) self);
        a.x = FX_MulFunc(a.x, 0xc00);
        a.z = FX_MulFunc(a.z, 0xc00);
        if (func_020b67ac() != 0) {
            f = 0xf;
        } else {
            f = 8;
        }
        func_020b7dc8(func_020b6590(), self + 0x28c, &c, a.x, a.z, a.y, *(short *) (self + 0x8e), f, idx);
    }
}
