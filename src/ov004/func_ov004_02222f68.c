/* func_ov004_02222f68 @ 0x02222f68, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0222fd94(void *);

int func_ov004_02222f68(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222fd94(self);
    *(u16 *) (self + 0x710) = (*(int *) (self + 0x190) >> 12);
    return 0x1;
}
