/* func_ov004_0223a18c @ 0x0223a18c, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a5e4(void *);
extern void *data_ov004_02255e44;

void *func_ov004_0223a18c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a5e4(self);
    *(void **) (self) = &data_ov004_02255e44;
    *(u8 *) (self + 0x20e) = 0x0;
    return self;
}
