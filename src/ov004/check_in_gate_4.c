/* check_in_gate_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222d320 @ 0x0222d320, 0xc bytes, Thumb
 * func_ov004_0222d30c @ 0x0222d30c, 0x14 bytes, Thumb
 * func_ov004_0222d2a4 @ 0x0222d2a4, 0x68 bytes, Thumb
 * func_ov004_0222d280 @ 0x0222d280, 0x24 bytes, Thumb
 */

#include "types.h"

extern int func_02032180(void *);
extern int func_020321bc(void *, int, int, int, int *, int, int);

void *func_ov004_0222d320(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x490) = 0x0;
    return self;
}

void func_ov004_0222d30c(char *self, int v)
{
    *(u8 *) (self + 0x490) = 1;
    *(int *) (self + 0x494) = v;
}

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

void func_ov004_0222d280(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x354) != 0x0) {
        func_02032180(self + 0x2bc);
    }
}
