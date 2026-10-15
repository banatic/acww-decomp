/* func_ov004_02237794 @ 0x02237794, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02239bb4(void *, int, int);

void func_ov004_02237794(char *self)
{
    func_ov004_02239bb4(self + 0x1a8, 0xcd, (s16) (-*(s16 *) (self + 0x1c0)));
    if (*(int *) (self + 0x158) % 4 == 1) {
        *(u8 *) (self + 0x257) = 1;
    }
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x258)) {
        *(u8 *) (self + 0x257) = 0;
    }
}
