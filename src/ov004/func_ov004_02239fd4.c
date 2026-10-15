/* func_ov004_02239fd4 @ 0x02239fd4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223a458(void *);
extern void *data_ov004_02255dcc;

void *func_ov004_02239fd4(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0223a458(self);
    *(void **) (self) = &data_ov004_02255dcc;
    *(u8 *) (self + 0x255) = 0x0;
    *(u8 *) (self + 0x256) = 0x0;
    *(u8 *) (self + 0x258) = 0x0;
    return self;
}
