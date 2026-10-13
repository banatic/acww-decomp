/* func_ov004_022160b0 @ 0x022160b0, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d280(void *, int, int);
extern void func_ov004_022101e4(void *, int, int, int, int);
extern void func_ov004_02210744(void *);
extern void func_ov004_02216598(void *, int, int);

int func_ov004_022160b0(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02210744(self);
    func_ov004_0220d280(self + 0x740, 0x0, 0x0);
    if (*(u8 *) (self + 0x77e) == 0x0) {
        func_ov004_02216598(self, *(u8 *) (self + 0x845), 0x1);
    }
    if (*(int *) (self + 0x780) == 0x29) {
        func_ov004_022101e4(self, 0x0, 0x1, 0x1000, 0x0);
    }
    return 0x1;
}
