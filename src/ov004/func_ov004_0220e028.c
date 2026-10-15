/* func_ov004_0220e028 @ 0x0220e028, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055aac(void *);
extern int func_ov004_0220e208(void *);

int func_ov004_0220e028(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x70) = 0xfff1;
    func_ov004_0220e208(self);
    func_02055aac(self + 0x10);
    *(u8 *) (self + 0x72) = 0x0;
    return 0x0;
}
