/* func_ov004_0223a040 @ 0x0223a040, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a5e4(void *);
extern void *data_ov004_02255e8c;

void *func_ov004_0223a040(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4(self);
    *(void **) (self) = &data_ov004_02255e8c;
    *(u8 *) (self + 0x21c) = 0x2;
    return self;
}
