/* func_ov004_0222c558 @ 0x0222c558, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0209d3bc();

int func_ov004_0222c558(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0xea) != 0xff) {
        return func_0209d3bc(*(u8 *) (self + 0xea));
    }
    return 0x0;
}
