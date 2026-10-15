/* func_ov004_02245898 @ 0x02245898, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02095a8c(int, int);
extern int func_ov004_02246a74(void);

int func_ov004_02245898(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02246a74();
    func_02095a8c(0x0, 0x4);
    *(u16 *) (self + 0x324) = 0x5;
    return 0x324;
}
