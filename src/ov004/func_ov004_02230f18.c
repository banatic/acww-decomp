/* func_ov004_02230f18 @ 0x02230f18, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02230db8(void *, void *, int);
extern void *data_ov004_022558ac;

int func_ov004_02230f18(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02230db8(self, &data_ov004_022558ac, 0xe);
    *(u8 *) (self + 0x63c) = 0x1;
    return 0x63c;
}
