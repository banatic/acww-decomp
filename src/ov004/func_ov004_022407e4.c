/* func_ov004_022407e4 @ 0x022407e4, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_02244f90(void);
extern int func_ov004_02240f2c(void *, int, int, int, void *, int, int);
extern int func_020644cc(int);

void func_ov004_022407e4(char *self, int a, int b, int c, u8 d, u8 e, int f)
{
    void *h = func_ov004_02244f90();
    int q = 0x1000 / d;
    int *s;
    int *dst;
    func_ov004_02240f2c(self, a, b, 0, h, c, q);
    *(u8 *) (self + 0xa4) = e;
    *(int *) (self + 0x4c) = f;
    s = (int *) (self + 0x2c8);
    dst = (int *) (self + 0x40);
    dst[0] = s[0];
    dst[1] = s[1];
    dst[2] = s[2];
    if (*(u8 *) (self + 0x22) != 0 && func_020644cc(0x64) > 0x32) {
        *(int *) (self + 0x174) = 0x64;
    } else {
        *(u8 *) (self + 0xae) = 1;
    }
}
