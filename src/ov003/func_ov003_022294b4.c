/* func_ov003_022294b4 @ 0x022294b4, 0xdc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern int func_ov003_0222796c(Vec3 *a, Vec3 *b, Vec3 *c);
extern int func_ov003_02229428(char *p, Vec3 *a, Vec3 *b, int n, int q, int k);

void func_ov003_022294b4(char *self, int flag)
{
    volatile Vec3 a;
    volatile Vec3 b;
    Vec3 c;
    Vec3 d;
    Vec3 e;
    Vec3 f;
    Vec3 g;
    int k;
    if (flag) {
        a.x = *(int *) (self + 0x6c);
        a.y = *(int *) (self + 0x70);
        a.z = *(int *) (self + 0x74);
        b.x = *(int *) (self + 0x60);
        b.y = *(int *) (self + 0x64);
        b.z = *(int *) (self + 0x68);
        b.y = *(int *) (self + 0x64) - 0x1800;
        k = 0x14;
    } else {
        a.x = *(int *) (self + 0x60);
        a.y = *(int *) (self + 0x64);
        a.z = *(int *) (self + 0x68);
        b.x = *(int *) (self + 0x6c);
        b.y = *(int *) (self + 0x70);
        b.z = *(int *) (self + 0x74);
        b.y = *(int *) (self + 0x70) - *(int *) (self + 0x64);
        k = 0x14;
    }
    c.x = *(int *) (self + 0x54);
    c.y = *(int *) (self + 0x58);
    c.z = *(int *) (self + 0x5c);
    d.x = a.x;
    d.y = a.y;
    d.z = a.z;
    e.x = b.x;
    e.y = b.y;
    e.z = b.z;
    if (func_ov003_0222796c(&c, &d, &e)) {
        *(int *) (self + 0x40) = 4;
        *(u8 *) (self + 0x94) = 1;
    } else {
        f.x = a.x;
        f.y = a.y;
        f.z = a.z;
        g.x = b.x;
        g.y = b.y;
        g.z = b.z;
        if (func_ov003_02229428(self + 0x54, &f, &g, *(int *) (self + 0x7c), 0x14cd, k) == 0) {
            *(int *) (self + 0x40) = 4;
            *(u8 *) (self + 0x94) = 1;
        }
        *(int *) (self + 0x7c) = *(int *) (self + 0x7c) + 1;
    }
}
