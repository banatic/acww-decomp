/* func_ov004_02236bd4 @ 0x02236bd4, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055dc8(void *, void *, void *);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);

void func_ov004_02236bd4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x50) = self;
    *(u8 *) (self + 0x1e8) = *(int *) (self + 0x15c);
    *(u8 *) (self + 0x1e9) = *(int *) (self + 0x15c);
    *(u8 *) (self + 0x1c8) = 0x1;
    func_ov004_022354e0(self);
    func_02055dc8(self + 0x64, (void *) func_ov004_0223653c, self);
}
