/* func_ov004_02220018 @ 0x02220018, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220fde0(void *);
extern int func_02053be0(int);

void func_ov004_02220018(u8 *self, void *a)
{
    switch (func_02053be0((int) func_ov004_0220fde0(a))) {
        case 0:
            *(int *) (self + 0xad8) = 0x3000;
            break;
        case 1:
            *(int *) (self + 0xad8) = 0x4000;
            break;
        case 2:
            *(int *) (self + 0xad8) = 0x4000;
            break;
    }
}
