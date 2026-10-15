/* func_ov004_02239e40 @ 0x02239e40, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a458(void *);
extern void *data_ov004_02255e5c;

void *func_ov004_02239e40(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255e5c;
    *(u8 *) (self + 0x255) = 0x0;
    return self;
}
