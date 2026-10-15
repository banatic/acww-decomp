/* func_ov004_02233918 @ 0x02233918, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;
extern void func_0204f794(void *, int, int);
extern int _s32_div_f(int, int);
extern int func_020044c0(void *, int, int, int);

void func_ov004_02233918(char *self, int *p1, Vec3 *p2, Vec3 *p3, u16 a5)
{
    volatile u16 t = 0xfff1;
    int buf[4];
    int q;
    u16 v;
    u16 m;
    int k;
    func_0204f794(buf, p1[0], p1[1]);
    if (p3->y == 0) {
        q = _s32_div_f(p3->z - p2->z, 9);
        *(int *) (self + 0x30) = _s32_div_f(p3->x - p2->x, 9);
        *(int *) (self + 0x34) = 0x1000;
        *(int *) (self + 0x38) = q;
    } else {
        q = _s32_div_f(p3->z - p2->z, 0xc);
        *(int *) (self + 0x30) = _s32_div_f(p3->x - p2->x, 0xc);
        *(int *) (self + 0x34) = 0x1800;
        *(int *) (self + 0x38) = q;
    }
    v = a5;
    *(u16 *) (self + 8) = v;
    *(u16 *) (self + 0xa) = v;
    *(int *) (self + 0x24) = p2->x;
    *(int *) (self + 0x28) = p2->y;
    *(int *) (self + 0x2c) = p2->z;
    *(int *) (self + 0x3c) = 0;
    *(int *) (self + 0x40) = 0x1000;
    *(int *) (self + 0x44) = 0;
    t = v;
    m = t;
    k = (m & 0xf000) >> 12;
    switch (k) {
        case 3:
        case 4:
            *(unsigned char *) (self + 0x8e) = 0;
            break;
        default:
            func_020044c0(self + 0x4c, 0x75, 0x7f, 0);
            break;
    }
}
