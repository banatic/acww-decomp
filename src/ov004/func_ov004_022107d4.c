/* func_ov004_022107d4 @ 0x022107d4, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220e5c8(void *self);
extern int func_ov004_0223a760(int x);
extern u16 data_ov004_0224fd38;
extern void func_ov004_0223cf40(void *p, int v, void *q);

int func_ov004_022107d4(char *self)
{
    if (!func_ov004_0220e5c8(self)) {
        int v = func_ov004_0223a760(*(int *) (self + 0x284));
        if (v != data_ov004_0224fd38) {
            func_ov004_0223cf40(self + 0x798, v, self + 0x7b8);
            return 1;
        }
    }
    return 0;
}
