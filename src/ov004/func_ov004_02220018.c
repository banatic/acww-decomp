/* func_ov004_02220018 @ 0x02220018, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220fde0_unk(void *);
extern int func_02053be0(void);

void func_ov004_02220018(u8 *self, void *a)
{
    func_ov004_0220fde0_unk(a);
    switch (func_02053be0()) {
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
