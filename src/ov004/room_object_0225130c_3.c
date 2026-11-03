/* room_object_0225130c_3: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02212ed4 @ 0x02212ed4, 0x38 bytes, Thumb
 * func_ov004_02212ed0 @ 0x02212ed0, 0x4 bytes, Thumb
 * func_ov004_02212ebc @ 0x02212ebc, 0x14 bytes, Thumb
 */

#include "types.h"

extern int func_ov004_0220cdf8(void *);
extern int func_ov004_0220e5c8(void *);
extern void func_ov004_0223cf40(void *, int, void *);
extern const u8 data_ov004_0224769c[];

int func_ov004_02212ed4(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0220e5c8(self) == 0x0 && func_ov004_0220cdf8(self) == 0x0) {
        func_ov004_0223cf40(self + 0x798, 0x42a, self + 0x7b8);
    }
    return 0x1;
}

int func_ov004_02212ed0(void)
{
    return 1;
}

u8 func_ov004_02212ebc(void *self, unsigned int i)
{
    if (i < 5) {
        return data_ov004_0224769c[i];
    }
    return 0;
}
