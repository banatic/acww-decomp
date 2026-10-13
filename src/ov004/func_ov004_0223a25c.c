/* func_ov004_0223a25c @ 0x0223a25c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0223a458(void *);
extern void *data_ov004_02255d6c;

void *func_ov004_0223a25c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255d6c;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x256) = 0x0;
    return self;
}
