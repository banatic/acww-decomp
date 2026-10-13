/* func_ov004_0221b4b0 @ 0x0221b4b0, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0203e0a8(void *, int);
extern void func_020ee470(void *);
extern int func_ov004_0221b98c(void *);

void func_ov004_0221b4b0(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0221b98c(self) != 0x0) {
        if (*(u8 *) (self + 0x16c) == 0x0) {
            func_0203e0a8(self, 0x0);
        } else {
            func_020ee470(self);
        }
        return;
    }
}
