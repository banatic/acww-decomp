/* func_ov004_02236e9c @ 0x02236e9c, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02236e0c(void *);
extern void func_ov004_02236cfc(void *);
extern void func_ov004_02236c1c(void *);

void func_ov004_02236e9c(char *self)
{
    u8 *st = (u8 *) (self + 0x21c);
    switch (*st) {
        case 2:
            func_ov004_02236e0c(self);
            break;
        case 4:
            func_ov004_02236cfc(self);
            break;
        case 5:
            func_ov004_02236c1c(self);
            break;
        case 6:
            if (*(int *) (self + 0x158) >= *(u16 *) (self + 0x212)) {
                *(int *) (self + 0x158) = 0;
                *st = 2;
            }
            break;
    }
    *(int *) (self + 0x158) += 1;
}
