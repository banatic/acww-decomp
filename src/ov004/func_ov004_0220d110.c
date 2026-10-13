/* func_ov004_0220d110 @ 0x0220d110, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02138d6c(void *, int, int, void *, void *);
extern void func_ov004_0220d258();
extern void func_ov004_0220d268();

void *func_ov004_0220d110(char *self)
{
    // DECLS
    // ENDDECLS
    func_02138d6c(self, 0x3, 0x1c, (void *) func_ov004_0220d268, (void *) func_ov004_0220d258);
    *(u8 *) (self + 0x54) = 0x0;
    return self;
}
