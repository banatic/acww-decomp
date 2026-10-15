/* func_ov004_02239f68 @ 0x02239f68, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a458(void *);
extern void *data_ov004_02255d9c;

void *func_ov004_02239f68(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255d9c;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x257) = 0x0;
    *(u8 *) (self + 0x259) = 0x0;
    return self;
}
