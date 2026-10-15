/* func_ov004_022154b8 @ 0x022154b8, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_022110e4(void *);
extern void *data_ov004_02252ba8;
extern void *data_ov004_02252c54;

void *func_ov004_022154b8(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02252ba8;
    *(void **) (self + 0xec) = &data_ov004_02252c54;
    *(u8 *) (self + 0x77c) = 0xff;
    return self;
}
