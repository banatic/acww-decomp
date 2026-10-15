/* func_ov004_0223653c @ 0x0223653c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0223655c(char *arg0);
extern void func_ov004_02236578(char *self);

void func_ov004_0223653c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x24) = (void *) func_ov004_02236578;
    *(u8 *) (self + 0x92) = 0x1;
    *(void **) (self + 0x24) = (void *) func_ov004_0223655c;
    *(u8 *) (self + 0x92) = 0x2;
}
