/* func_ov004_022115b4 @ 0x022115b4, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_02062b14(void);
extern void func_ov004_0221041c(void *self, int a, int b, int c, u16 d);
extern int func_ov004_0220ffbc(void *self);

int func_ov004_022115b4(char *self)
{
    int *p = (int *) (self + 0x844);

    *p = func_02062b14();
    func_ov004_0221041c(self, 0, 0, 0, (u16) *p);
    func_ov004_0220ffbc(self);
    return 1;
}
