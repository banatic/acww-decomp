/* func_ov004_02224770 @ 0x02224770, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02019d0c(void *, int, int, int, int, int, int, int, int, int, int);
extern void *data_020c80f8;

int func_ov004_02224770(char *self)
{
    // DECLS
    // ENDDECLS
    func_02019d0c(self + 0x564, 0x3, 0x2, 0x0, 0x0, 0x0, *(short *) (self + 0x714), 0x0, 0x0,
                  *(u16 *) ((char *) &data_020c80f8), 0x0);
    return 0x1;
}
