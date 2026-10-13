/* func_ov004_02232270 @ 0x02232270, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020b6590(int);
extern int func_020b7d6c(int, void *);

int func_ov004_02232270(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x20) != 0x0) {
        return func_020b7d6c(func_020b6590(*(u8 *) (self + 0x20)), self);
    }
    return *(u8 *) (self + 0x20);
}
