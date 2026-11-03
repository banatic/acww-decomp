/* clock_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022168f8 @ 0x022168f8, 0x4 bytes, Thumb
 * func_ov004_022168f0 @ 0x022168f0, 0x8 bytes, Thumb
 * func_ov004_022168e4 @ 0x022168e4, 0xc bytes, Thumb
 * func_ov004_022168d8 @ 0x022168d8, 0xc bytes, Thumb
 */

#include "types.h"

extern void func_ov004_0220e534(char *parameter0, int parameter1, int parameter2);

int func_ov004_022168f8(void)
{
    return 1;
}

void func_ov004_022168f0(char *arg0, int arg1, int arg2)
{
    func_ov004_0220e534((char *) arg0, arg1, arg2);
}

void *func_ov004_022168e4(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x84a) = 0x1;
    return self;
}

void *func_ov004_022168d8(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x84b) = 0x1;
    return self;
}
