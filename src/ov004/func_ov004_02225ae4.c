/* func_ov004_02225ae4 @ 0x02225ae4, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02019c20(void *, int, int, int, int, int);
extern void *data_020c80f8;

int func_ov004_02225ae4(char *self)
{
    // DECLS
    // ENDDECLS
    func_02019c20(self + 0x564, 0x1, 0x100, 0x1, *(u16 *) ((char *) &data_020c80f8), 0x0);
    return 0x1;
}
