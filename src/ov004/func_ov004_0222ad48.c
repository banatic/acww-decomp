/* func_ov004_0222ad48 @ 0x0222ad48, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02056f94(void *argument0);
extern int func_ov004_0222bdf0(int argument0, int argument1, int argument2, int argument3);

int func_ov004_0222ad48(char *self)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02056f94(self + 0x2d0);
    if (v1 != 0x0) {
        return func_ov004_0222bdf0((int) (self), (int) (*(u8 *) (self + 0x7de)), (int) (0x6), (int) (-0x1));
    }
    return v1;
}
