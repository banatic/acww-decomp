/* func_ov004_02240674 @ 0x02240674, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern void func_ov004_02241008(void *, void *, void *);
extern int func_020644cc(int);
struct Pt {
    int a;
    int b;
};

void func_ov004_02240674(char *self)
{
    struct Pt p;
    struct Pt q;
    int r;
    func_ov004_02240f2c(self, 0x28, 0x50, 0, 0, 0, 1);
    p.a = 0x62;
    p.b = 0x11a;
    q.a = 0x92;
    q.b = 0x13e;
    func_ov004_02241008(self, &p, &q);
    if (*(u8 *) (self + 0x22) != 0) {
        r = func_020644cc(0x14);
        *(u16 *) (self + 0x98) = (u16) (func_020644cc(3) * r);
    } else {
        r = func_020644cc(0x14);
        *(u16 *) (self + 0x98) = (u16) (func_020644cc(0xf) * r);
    }
}
