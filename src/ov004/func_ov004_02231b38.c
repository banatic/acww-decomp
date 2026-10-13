/* func_ov004_02231b38 @ 0x02231b38, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02231b58();
extern void func_ov004_02231b78();

void func_ov004_02231b38(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x1c) = (void *) func_ov004_02231b78;
    *(u8 *) (self + 0x90) = 0x2;
    *(void **) (self + 0x24) = (void *) func_ov004_02231b58;
    *(u8 *) (self + 0x92) = 0x2;
}
