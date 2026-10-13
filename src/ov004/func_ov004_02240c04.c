/* func_ov004_02240c04 @ 0x02240c04, 0x90 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern void func_ov004_02241008(void *, void *, void *);
struct Pt {
    int a;
    int b;
};
struct Pt5 {
    int a;
    int b;
    int c;
    int d;
    int e;
};

void func_ov004_02240c04(char *self)
{
    struct Pt p;
    struct Pt5 q;
    int *v;
    if (*(u8 *) (self + 0x22) != 0) {
        v = (int *) (self + 0x2c8);
        v[0] = 0x7a00;
        v[1] = 0x2d00;
        v[2] = 0x12c00;
        func_ov004_02240f2c(self, 0x5a, 0x50, 0, 0, 0, 4);
        *(u8 *) (self + 0x50) = 0x3c;
        p.a = 0;
        p.b = 0xac;
        q.a = 0x96;
        q.b = 0x1ac;
        func_ov004_02241008(self, &p, &q);
    } else {
        func_ov004_02240f2c(self, 0x5a, 0x50, 0x3556, 0x6000, 0, 4);
    }
}
