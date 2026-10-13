/* func_ov004_02215de0 @ 0x02215de0, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d150(void *);
extern void func_ov004_02215c70(void *);

int func_ov004_02215de0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d150(self + 0x848);
    func_ov004_02215c70(self);
    *(u8 *) (self + 0x864) = 0x0;
    return 0x1;
}
