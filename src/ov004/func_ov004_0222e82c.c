/* func_ov004_0222e82c @ 0x0222e82c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0222c598(void *);
extern void func_ov004_0222dde0(void *, int);
extern int data_ov004_02258310;

int func_ov004_0222e82c(u8 *self)
{
    u8 i;

    func_ov004_0222c598(self);
    for (i = 0; i < 9; i++) {
        func_ov004_0222dde0(self, i);
    }
    data_ov004_02258310 = 0;
    return 1;
}
