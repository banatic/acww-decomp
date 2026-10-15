/* func_ov004_0222d2a4 @ 0x0222d2a4, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02032180(void *);
extern int func_020321bc(void *, int, int, int, int *, int, int);

void func_ov004_0222d2a4(char *self)
{
    int a[3];
    if (*(u8 *) (self + 0x354) != 0) {
        func_02032180(self + 0x2bc);
    }
    if (*(u8 *) (self + 0x490) != 0) {
        int q = *(int *) (self + 0x494) + 0x10000;
        a[0] = 0x10000;
        a[1] = 0;
        a[2] = q;
        func_020321bc(self + 0x2bc, 0x8000, 0, 0x2000, a, 0, 0);
    }
}
