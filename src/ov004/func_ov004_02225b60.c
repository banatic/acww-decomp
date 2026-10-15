/* func_ov004_02225b60 @ 0x02225b60, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void *data_020c80f8;

int func_ov004_02225b60(char *self)
{
    // DECLS
    // ENDDECLS
    func_02019d0c(self + 0x564, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, *(u16 *) ((char *) &data_020c80f8), 0x0);
    *(u8 *) (self + 0x658) = 0xa;
    return 0x1;
}
