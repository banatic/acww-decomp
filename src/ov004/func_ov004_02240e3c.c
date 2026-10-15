/* func_ov004_02240e3c @ 0x02240e3c, 0xe8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int FX_MulFunc(int a, int b);
extern int func_ov004_02240f2c(void *, int, int, int, int, int, int);
extern int func_020644cc(int);
extern void func_02056fcc(void *, int, int, int, int);
extern void func_020550e4(void *, int);

void func_ov004_02240e3c(char *self, int a, int b, int c, int e, int f)
{
    int v = FX_MulFunc(FX_MulFunc((c + 8) << 12, 0x1000), 0x100);
    int *s;
    int *d;
    int one;
    signed char t;
    s = (int *) (self + 0x2c8);
    d = (int *) (self + 0x40);
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    func_ov004_02240f2c(self, a, b, 0, 0, 0, e);
    *(u8 *) (self + 0x50) = 0x28;
    *(int *) (self + 0x174) = 0x14 * (func_020644cc(0xa) + 0x10);
    *(short *) (self + 0x16a) = (u8) func_020644cc(0x12);
    one = 1;
    *(u8 *) (self + 0x170) = (u8) one;
    *(int *) (self + 0x4c) = f;
    *(short *) (self + 0x98) = 0;
    *(int *) (self + 0xa8) = v;
    *(int *) (self + 0x54) = v;
    if (*(u8 *) (self + 0x22) == 0) {
        *(short *) (self + 0x172) = 6;
        t = *(signed char *) (self + 0x196);
        if (t != 0xa && t != 0x33) {
            func_02056fcc(self + 0x14c, 0x11, one, 0x1000, 9);
        } else {
            func_020550e4(self + 0xb0, 0);
        }
    }
}
