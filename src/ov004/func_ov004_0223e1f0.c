/* func_ov004_0223e1f0 @ 0x0223e1f0, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern void func_ov004_0223df88(char *self);
extern void func_ov004_0223d87c(char *self);
extern int func_02091254(int a, void *b, int c, int d);
extern void func_ov004_0223dc68(char *self, int parameter1);
extern int func_020644cc(int n);
extern void func_020042c0(void *a, Vec3 *v);

void func_ov004_0223e1f0(char *self)
{
    // DECLS
    Vec3 *q;
    int t;
    // ENDDECLS
    Vec3 v;

    if (*(int *) (self + 0x10c) != 2) {
        func_ov004_0223df88(self);
    }
    switch (*(int *) (self + 0x10c)) {
        case 0:
            func_ov004_0223d87c(self);
            break;
        case 1:
            *(int *) (self + 0x98) = *(int *) (self + 0xd4);
            t = *(s16 *) (self + 0x22c);
            *(s16 *) (self + 0x22c) = (s16) (t - 1);
            if (t <= 0) {
                if (*(u8 *) (self + 0x22a) == 0) {
                    *(int *) (self + 0x10c) = 0;
                    *(s16 *) (self + 0x22c) = (s16) (0x14 * (func_020644cc(0xa) + 3));
                }
            }
            break;
        case 2:
            func_02091254(0x50, self + 0x5c, 0, 0);
            *(int *) (self + 8) -= 1;
            *(int *) (self + 0x110) = 2;
            func_ov004_0223dc68(self, (int) (0x2));
            break;
        case 3:
            if (func_020644cc(0x64) > 0x32) {
                *(int *) (self + 0x10c) = 0;
                *(s16 *) (self + 0x22c) = (s16) (0x14 * (func_020644cc(0xa) + 3));
            } else {
                *(int *) (self + 0x10c) = 1;
                *(s16 *) (self + 0x22c) = (s16) (0x14 * (func_020644cc(4) + 3));
            }
            break;
    }
    q = (Vec3 *) (self + 0x5c);
    v.x = q->x;
    v.y = q->y;
    v.z = q->z;
    func_020042c0(self + 0x114, &v);
}
