/* func_ov004_0221780c @ 0x0221780c, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_ov004_0220d268(void *);
extern void *func_ov004_022110e4(void *);
extern void *data_ov004_0225211c;
extern void *data_ov004_022521c8;

void *func_ov004_0221780c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_0225211c;
    *(void **) (self + 0xec) = &data_ov004_022521c8;
    func_ov004_0220d268(self + 0x844);
    *(u8 *) (self + 0x860) = 0x0;
    return self;
}
