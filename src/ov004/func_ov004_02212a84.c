/* func_ov004_02212a84 @ 0x02212a84, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_02210054(void *, int, int, int);

int func_ov004_02212a84(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    func_ov004_02210054(self, 0x0, 0x3, 0x1000);
    *(u8 *) (self + 0x846) = 0x1;
    return 0x1;
}
