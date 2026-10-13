/* func_ov004_02225c68 @ 0x02225c68, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0202ec58(void *);
extern void *data_ov004_02258200;
extern void func_ov004_02225ba4(void *, int);
int func_ov004_02225c68(u8 *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    data_ov004_02258200 = self;
    func_ov004_02225ba4(self, 0);
    *(int *) (self + 0x4e8) |= 2;
    self[0x510] = 0;
    return 1;
}
