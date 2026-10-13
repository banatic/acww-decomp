/* func_ov004_0221c224 @ 0x0221c224, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void *data_020c80f8;

int func_ov004_0221c224(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0xa52) = 0x32;
    func_02019d0c(self + 0x564, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, *(u16 *) ((char *) &data_020c80f8), 0x0);
    return 0x1;
}
