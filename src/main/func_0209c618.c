/* func_0209c618 @ 0x0209c618, 0x1f4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_0209cc30(void *self, u32 x, u32 y);
extern void func_0209d01c(void *c, int v);
extern int func_0209d030(void *c);
extern int func_02037b14(int v);
extern u32 func_020644cc(u32 n);

int func_0209c618(void *self)
{
    u32 i;
    u32 n;
    u32 k;
    u32 m;

    func_0209d01c(func_0209cc30(self, 0, 0), 7);
    func_0209d01c(func_0209cc30(self, 1, 0), 0);
    func_0209d01c(func_0209cc30(self, 2, 0), 0);
    func_0209d01c(func_0209cc30(self, 3, 0), 0);
    func_0209d01c(func_0209cc30(self, 4, 0), 0);
    func_0209d01c(func_0209cc30(self, 5, 0), 8);

    func_0209d01c(func_0209cc30(self, 0, 5), 0x35);
    func_0209d01c(func_0209cc30(self, 1, 5), 0x35);
    func_0209d01c(func_0209cc30(self, 2, 5), 0x35);
    func_0209d01c(func_0209cc30(self, 3, 5), 0x35);
    func_0209d01c(func_0209cc30(self, 4, 5), 0x35);
    func_0209d01c(func_0209cc30(self, 5, 5), 0x35);

    func_0209d01c(func_0209cc30(self, 0, 1), 3);
    func_0209d01c(func_0209cc30(self, 0, 2), 3);
    func_0209d01c(func_0209cc30(self, 0, 3), 3);
    func_0209d01c(func_0209cc30(self, 0, 4), 4);

    func_0209d01c(func_0209cc30(self, 5, 1), 5);
    func_0209d01c(func_0209cc30(self, 5, 2), 5);
    func_0209d01c(func_0209cc30(self, 5, 3), 5);
    func_0209d01c(func_0209cc30(self, 5, 4), 6);

    for (i = 1; i < 5; i++) {
        if (func_0209d030(func_0209cc30(self, i, 1)) == 0x14) {
            func_0209d01c(func_0209cc30(self, i, 0), 2);
        }
    }

    n = 0;
    for (i = 2; i <= 3; i++) {
        if (func_02037b14(func_0209d030(func_0209cc30(self, i, 1))) == 0) {
            n++;
        }
    }

    k = func_020644cc(n);

    m = 0;
    for (i = 2; i <= 3; i++) {
        if (func_02037b14(func_0209d030(func_0209cc30(self, i, 1))) == 0) {
            if (m == k) {
                func_0209d01c(func_0209cc30(self, i, 0), 1);
                func_0209d01c(func_0209cc30(self, i, 1), 0xa);
                return 1;
            }
            m++;
        }
    }
    return 0;
}
