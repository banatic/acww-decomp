/* func_ov004_022206c0 @ 0x022206c0, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

int func_ov004_022206c0(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) ((char *) *(int *) (self + 0x1a4) + 0x898) = 0xfff1;
    return 0x898;
}
