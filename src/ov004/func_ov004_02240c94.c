/* func_ov004_02240c94 @ 0x02240c94, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern void func_02056fcc(void *, int, int, int, int);
extern int func_020644cc(int);

void func_ov004_02240c94(char *self)
{
    int *d = (int *) (self + 0x40);
    int *s;
    int one;
    int zero;
    func_ov004_02240f2c(self, 0x96, 0x28, 1, -0x8000, 0, 9);
    if (*(u8 *) (self + 0x22) == 0) {
        *(short *) (self + 0x190) = 0x2aa8;
    }
    *(u8 *) (self + 0x50) = 0x3c;
    *(short *) (self + 0x16a) = (u8) func_020644cc(0x12);
    one = 1;
    *(u8 *) (self + 0x170) = (u8) one;
    zero = 0;
    *(int *) (self + 0x54) = zero;
    s = (int *) (self + 0x2c8);
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    if (*(u8 *) (self + 0x22) == 0) {
        func_02056fcc(self + 0x14c, 8, one, 0x1000, zero);
    }
}
