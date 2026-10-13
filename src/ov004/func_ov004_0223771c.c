/* func_ov004_0223771c @ 0x0223771c, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0223766c(void *);
extern void func_ov004_02237630(void *);
extern void func_ov004_022358c0(void *, int);
extern void func_ov004_02236418(void *);

void func_ov004_0223771c(char *self)
{
    switch (*(u8 *) (self + 0x255)) {
        case 0:
            func_ov004_0223766c(self);
            break;
        case 1:
            func_ov004_02237630(self);
            break;
    }
    func_ov004_022358c0(self, 0x333);
    *(int *) (self + 0x158) += 1;
    func_ov004_02236418(self);
}
