/* func_ov004_02236110 @ 0x02236110, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02239bb4(void *, int, int);

void func_ov004_02236110(char *self)
{
    // DECLS
    // ENDDECLS
    *(int *) (self + 0x20c) = *(int *) (self + 0x210);
    func_ov004_02239bb4(self + 0x1a8, *(int *) (self + 0x20c), *(short *) (self + 0x1c0));
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x202)) {
        *(void **) (self + 0x158) = 0x0;
        *(u8 *) (self + 0x1ee) = 0x5;
    }
}
