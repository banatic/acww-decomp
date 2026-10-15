/* func_ov004_0221f9d4 @ 0x0221f9d4, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov004_0221fdf4(void *, int);

int func_ov004_0221f9d4(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_02014868(self + 0x618) == 0x0) {
        if (*(u8 *) (self + 0xa54) == 0x0) {
            *(u8 *) (self + 0xa54) = 0x1;
        }
        *(u16 *) (self + 0x898) = 0xfff1;
        func_0203e020(self);
        func_ov004_0221fdf4(self, 0x2);
    }
    return 0x1;
}
