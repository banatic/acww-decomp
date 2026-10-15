/* func_ov003_0220ebe0 @ 0x0220ebe0, 0x144 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern char data_ov003_02238110;
extern char data_ov003_02238118;

extern void func_02054860(void *p);
extern int func_02056f28(void *p, int k);
extern void func_020110c4(u16 *out, void *self);
extern int func_0203f7d0(Vec3 *dst, Vec3 *src);
extern int func_020912d4(int a, Vec3 *v, void *b, int c);
extern int func_02095694(int a, int b);
extern void func_0200fa1c(Vec3 *out, void *self, void *sub, u16 *h, void *tbl);

void func_ov003_0220ebe0(char *self)
{
    u16 h[2];
    Vec3 t;
    Vec3 p;
    Vec3 a;
    Vec3 b;
    int f;
    u16 c0, c1;
    int *q;

    func_02054860(self + 0x234);
    h[0] = (u16) * (short *) (self + 0x8e);
    if (*(u8 *) (self + 0x7d8) != 0) {
        return;
    }

    if (func_02056f28(self + 0x2d0, 0xa) != 0) {
        func_020110c4(&h[1], self);
        f = 0;
        c0 = *(volatile u16 *) &h[1];
        c1 = *(volatile u16 *) &h[1];
        if (c1 >= 0x137c && c0 <= 0x137c) {
            f = 1;
        }
        if (f != 0) {
            if (*(int *) (self + 0x68c) == 0 && *(int *) (self + 0x690) == 0 && *(int *) (self + 0x694) == 0) {
                q = (int *) (self + 0x5c);
                p.x = q[0];
                p.y = q[1];
                p.z = q[2];
            } else {
                p.x = *(int *) (self + 0x68c);
                p.y = *(int *) (self + 0x690);
                p.z = *(int *) (self + 0x694);
                func_0203f7d0(&p, &p);
            }
            func_020912d4(0x32, &p, 0, 0);
            func_02095694(0, *(int *) (self + 0x800));
        }
    }

    if (func_02056f28(self + 0x2d0, 7) != 0) {
        func_0200fa1c(&a, self, self + 0x5c, &h[0], &data_ov003_02238110);
        t.x = a.x;
        t.y = a.y;
        t.z = a.z;
        func_020912d4(0x39, &t, &h[0], 0);
    }

    if (func_02056f28(self + 0x2d0, 9) != 0) {
        func_0200fa1c(&b, self, self + 0x5c, &h[0], &data_ov003_02238118);
        t.x = b.x;
        t.y = b.y;
        t.z = b.z;
        func_020912d4(0x37, &t, &h[0], 0);
    }
}
