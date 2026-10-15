/* func_ov004_022187ec @ 0x022187ec, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0220d110(void *);
extern void *func_ov004_022110e4(void *);
extern void *data_ov004_02253058;
extern void *data_ov004_02253104;

void *func_ov004_022187ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02253058;
    *(void **) (self + 0xec) = &data_ov004_02253104;
    *(u16 *) (self + 0x85c) = 0xfff1;
    func_ov004_0220d110(self + 0x860);
    return self;
}
