/* func_ov004_02237764 @ 0x02237764, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055dc8(void *, void *, void *);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);

void func_ov004_02237764(char *self)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x1e8) = *(int *) (self + 0x15c);
    func_02055dc8(self + 0x64, (void *) func_ov004_0223653c, self);
    func_ov004_022354e0(self);
}
