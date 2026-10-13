/* func_ov004_02236168 @ 0x02236168, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_02239bb4(void *, int, int);

void func_ov004_02236168(char *self)
{
    *(int *) (self + 0x20c) = *(int *) (self + 0x214) * *(int *) (self + 0x158);
    func_ov004_02239bb4(self + 0x1a8, *(int *) (self + 0x20c), *(s16 *) (self + 0x1c0));
    if (*(int *) (self + 0x20c) >= *(int *) (self + 0x210)) {
        *(int *) (self + 0x158) = 0;
        *(u8 *) (self + 0x1ee) = 4;
    }
}
