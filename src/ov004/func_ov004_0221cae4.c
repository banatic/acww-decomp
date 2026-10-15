/* func_ov004_0221cae4 @ 0x0221cae4, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0221cec8(void *self);
extern u16 func_ov004_0221cb28(int);
extern void func_02015de4(void *self, u16 *p, int a, int b);

void func_ov004_0221cae4(char *self)
{
    u8 v = *(u8 *) (self + 0x1e);
    u16 t;

    switch (v) {
        case 0xf:
        case 0x10:
            t = func_ov004_0221cb28((int) func_ov004_0221cec8(self));
            *(u16 *) (*(char **) (self + 0x1a4) + 0xa50) = t;
            func_02015de4(self, &t, 1, 7);
            break;
    }
}
