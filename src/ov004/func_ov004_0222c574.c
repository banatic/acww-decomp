/* func_ov004_0222c574 @ 0x0222c574, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209d3d0(unsigned int arg0);

int func_ov004_0222c574(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0xea) != 0xff) {
        return func_0209d3d0(*(u8 *) (self + 0xea));
    }
    return 0x0;
}
