/* func_ov004_0220f8c0 @ 0x0220f8c0, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov004_0220e5c8(void *self);
extern void func_ov004_0220faac(void *self, Vec3 *v);
extern void func_ov004_0220fefc(void *self, Vec3 *v);
extern int func_02032214(void *p, Vec3 *a, int k, Vec3 *b);
extern int FX_MulFunc(int a, int b);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0223cd78(int *a, int v);
extern int func_020b67ac(void);
extern int func_020b6590(void);
extern int func_020b7dc8(int h, void *o, Vec3 *v, int x, int z, int y, int k, int f, int c);
extern int func_020b7e04(int h, void *o);

void func_ov004_0220f8c0(char *self)
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
    int flag;
    int t;
    int idx;

    if (func_ov004_0220e5c8(self) == 0) {
        func_ov004_0220faac(self, &a);
        t = *(int *) (self + 0x15c);
        b.x = t;
        b.y = t;
        b.z = t;
        func_ov004_0220fefc(self, &c);
        flag = 0;
        if (*(u8 *) (self + 0x78c) == 0) {
            if (*(u8 *) (self + 0x6c4) != 0) {
                flag = func_02032214(self + 0x62c, &c, *(short *) (self + 0x8e), &b);
            } else {
                flag = 1;
            }
        }
        a.x = FX_MulFunc(a.x, 0xc00);
        a.z = FX_MulFunc(a.z, 0xc00);
        if (flag != 0) {
            idx = (u8) func_ov004_0223cd78(func_ov004_0223ce84(), (int) self);
            if (func_020b67ac() != 0) {
                flag = 0xf;
            } else {
                flag = 8;
            }
            func_020b7dc8(func_020b6590(), self + 0x28c, &c, a.x, a.z, a.y, *(short *) (self + 0x8e), flag, idx);
        } else {
            func_020b7e04(func_020b6590(), self + 0x28c);
        }
    }
}
