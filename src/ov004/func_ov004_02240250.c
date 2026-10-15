/* func_ov004_02240250 @ 0x02240250, 0xa4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_02244f90(void);
extern int func_ov004_02240f2c(void *, int, int, int, void *, int, int);
extern void func_02056fcc(void *, int, int, int, int);
extern void func_ov004_02241008(void *, void *, void *);
extern int func_020644cc(int);
struct Pt {
    int a;
    int b;
};

void func_ov004_02240250(char *self)
{
    struct Pt p;
    struct Pt q;
    void *h = func_ov004_02244f90();
    int zero;
    func_ov004_02240f2c(self, 0x50, 0x50, 0, h, 0, 5);
    zero = 0;
    *(u8 *) (self + 0x170) = (u8) zero;
    func_02056fcc(self + 0x14c, 3, zero, 0x1000, zero);
    p.a = 0x104;
    p.b = 0xc2;
    q.a = 0x1be;
    q.b = 0x15a;
    func_ov004_02241008(self, &p, &q);
    if (*(u8 *) (self + 0x22) != 0) {
        *(int *) (self + 0x174) = (short) (0x14 * (func_020644cc(6) + 1));
    } else {
        *(int *) (self + 0x174) = (short) (0x14 * (func_020644cc(0x1e) + 5));
    }
}
