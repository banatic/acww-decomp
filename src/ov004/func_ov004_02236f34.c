/* func_ov004_02236f34 @ 0x02236f34, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020e88dc(void *, int, int);

void func_ov004_02236f34(char *self)
{
    // DECLS
    // ENDDECLS
    func_020e88dc(self + 0x1a8, *(int *) (self + 0x264), *(int *) (self + 0x210));
    func_020e88dc(self + 0x1b0, *(int *) (self + 0x26c), *(int *) (self + 0x210));
    if (*(int *) (self + 0x158) > *(int *) (self + 0x270)) {
        *(u8 *) (self + 0x256) = 0x0;
        *(void **) (self + 0x158) = 0x0;
        *(u8 *) (self + 0x1ee) = 0x2;
    }
}
