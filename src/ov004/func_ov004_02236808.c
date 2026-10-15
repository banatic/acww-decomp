/* func_ov004_02236808 @ 0x02236808, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02055dc8(void *, void *, void *);
extern void func_ov004_022354e0(void *);
extern void func_ov004_0223653c(char *arg0);

void func_ov004_02236808(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x50) = self;
    if ((u32) (*(int *) (self + 0x15c) - 0x2d) <= (u32) 0x1) {
        *(u8 *) (self + 0x1c8) = 0x0;
    } else {
        if (*(int *) (self + 0x15c) == 0x37) {
            *(u8 *) (self + 0x1c8) = 0x2;
        } else {
            *(u8 *) (self + 0x1c8) = 0x1;
        }
    }
    *(u8 *) (self + 0x1e8) = *(int *) (self + 0x15c);
    *(u8 *) (self + 0x1e9) = *(int *) (self + 0x15c);
    func_ov004_022354e0(self);
    if (*(u8 *) (self + 0x1c6) != 0x0) {
        func_02055dc8(self + 0x64, (void *) func_ov004_0223653c, self);
    }
    return;
}
