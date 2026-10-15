/* func_ov004_0223a09c @ 0x0223a09c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a458(char *argument0);
extern void *data_ov004_02255de4;

void *func_ov004_0223a09c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255de4;
    *(u8 *) (self + 0x255) = 0x1;
    *(void **) (self + 0x21c) = 0x0;
    *(int *) (self + 0x20c) = 0xa3;
    *(u8 *) (self + 0x264) = 0x0;
    return self;
}
