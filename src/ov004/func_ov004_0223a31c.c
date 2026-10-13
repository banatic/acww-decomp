/* func_ov004_0223a31c @ 0x0223a31c, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0223a458();
extern void *data_ov004_02255e14;

void *func_ov004_0223a31c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255e14;
    *(u8 *) (self + 0x255) = 0x1;
    *(void **) (self + 0x21c) = 0x0;
    *(int *) (self + 0x20c) = 0x41;
    *(int *) (self + 0x278) = 0x14;
    *(int *) (self + 0x27c) = 0xccd;
    *(u8 *) (self + 0x284) = 0x0;
    return self;
}
