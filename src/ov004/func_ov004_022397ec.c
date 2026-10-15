/* func_ov004_022397ec @ 0x022397ec, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02239804(void *);

int func_ov004_022397ec(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02239804(self);
    *(u8 *) (self + 0x1fd) = 0x2;
    return 0x1fd;
}
